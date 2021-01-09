#include "adddevice.h"
#include <QMessageBox>
#include "table_structs.h"
#include <stdio.h>
#include <QDebug>
#include "myhelper.h"
#include <QObject>
#include "client.h"

AddDevice::AddDevice(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.radioButton_name->setChecked(true);
	m_Select = 0;
	m_nCompany = 0;
	connect(ui.comboBox_Type,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxCurrentIndexChanged(int)));

	ui.lineEdit_Port->setText("36123");
	//setWindowTitle(QObject::tr("添加设备"));
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setProperty("canMove", true);

}

AddDevice::~AddDevice()
{

}

void AddDevice::on_btnSure_clicked()
{
	QString m_IpAddr = ui.lineEdit_Addr->text();
	QString m_Name = ui.lineEdit_Name->text();
	if (m_IpAddr.isEmpty() || m_Name.isEmpty())
	{
		//QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("地址信息不能为空"));
		myHelper::ShowMessageBoxWarning(QObject::tr("地址信息不能为空"));
		return;
	}
	TabDevInfo_t devInfo;
	int nSubType = 0;
	devInfo.nPort = ui.lineEdit_Port->text().toInt();
	strcpy(devInfo.szLoginName , ui.lineEdit_Usr->text().toLocal8Bit().data());
	strcpy(devInfo.szPassword , ui.lineEdit_Pwd->text().toLatin1().data());
	devInfo.nDevStatus = DEVINFO_DEVSTATUS_ONLINE;
	
	int Type;
	int startipNum = 0;
	int endipNum = 1;
	int nChanNum = 1;
	QString startIp = ui.lineEdit_Name->text();
	QString endIP = ui.lineEdit_Addr->text();
	if (ui.radioButton_paragr->isChecked() == true)
	{
		
		startipNum = startIp.section('.',3,3).toInt();
		endipNum = endIP.section('.',3,3).toInt();
		if (startIp.section('.',0,2) !=  endIP.section('.',0,2))
		{
			
			myHelper::ShowMessageBoxWarning(QObject::tr("开始IP和结束IP必须处于同一网段!"));
			return;
		}
	}
	
	
	for (int i = startipNum;i<endipNum;i++)
	{
		QString EachIp = startIp.section('.',0,2)+"."+QString("%1").arg(i);
		if (ui.radioButton_paragr->isChecked() == true)
		{
			strcpy(devInfo.szIpAddr , EachIp.toLatin1().data());
			qDebug()<<devInfo.szIpAddr;
		}
		else
		{
			strcpy(devInfo.szIpAddr , endIP.toLatin1().data());
		}
		DB * db = new DB;
		int ret = db->checkDevice(devInfo.szIpAddr,devInfo.nPort,devInfo.szUUID);
		if (ret)
		{
			//QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("设备已经存在!"));
			myHelper::ShowMessageBoxWarning(QObject::tr("设备已经存在"));
			continue;
		}

		m_nCompany = DEVINFO_MANUFACTURER_JL_NEW;
		Type = DEVINFO_TYPE_IPCAM;

		nChanNum = ui.comboBox_ChannelNo->currentText().toInt();
		nSubType = getDeviceType(ui.comboBox_Type->currentIndex());
		if (nChanNum > 1)
		{
			Type = DEVINFO_TYPE_NVR;
		}
		devInfo.nManufacturer = m_nCompany;
		devInfo.nType = Type;
		devInfo.nSubDevType = nSubType;
		strcpy(devInfo.szDevName, m_Name.toLocal8Bit().data());
		 ret = db->AddDevice(devInfo.szIpAddr,devInfo.nPort,devInfo.szLoginName,
			devInfo.szPassword,devInfo.szDevName,devInfo.nType,devInfo.nManufacturer,
			QString::number(devInfo.nType),devInfo.nDevStatus,devInfo.nSubDevType);
		if (!ret)
		{
			//QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("插入到数据库失败!"));
			myHelper::ShowMessageBoxWarning(QObject::tr("插入到数据库失败"));
			continue;
		}
		if (Type == DEVINFO_TYPE_DECODER)
		{
			continue;
		}
		int nDevId = db->getDeviceID(devInfo.szIpAddr);
		TabChannelInfo_t channelInfo;
		channelInfo.DevId = nDevId;
		channelInfo.Status = CHANNELINFO_STATUS_OPEN;
		channelInfo.Type = nSubType;

		for (int nChannelNo = 1;nChannelNo <= nChanNum;nChannelNo++)
		{
			if(m_nCompany == DEVINFO_MANUFACTURER_BC)
			{
				if(nChannelNo == 1)
					channelInfo.Type = CHANNELINFO_TYPE_QIANGJI;
				if(nChannelNo == 2)
					channelInfo.Type = CHANNELINFO_TYPE_GAOSUQIU;
			}
			channelInfo.Channel = nChannelNo;
			strcpy(channelInfo.szChannelName , ("ch0"+QString::number(nChannelNo)).toLatin1().data());
			 ret = db->addChannelInfo(nDevId,channelInfo.Channel,channelInfo.szChannelName,channelInfo.Type,CHANNELINFO_STATUS_OPEN);
			if (!ret)
			{
				//QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("channelinfo信息插入到插入到数据库失败!"));
				myHelper::ShowMessageBoxWarning(QObject::tr("channelinfo信息插入到插入到数据库失败!"));
				continue;
			}
			
		}
	}
	if (Client::instance()->m_TabWidget.m_PREVIEW != FALSE)
	{
		Client::instance()->PreviewPro->OnTreeReFresh();
	}
	if (Client::instance()->m_TabWidget.m_VIDEOPLAY != FALSE)
	{
		Client::instance()->m_videoPlayBack->OnTreeReFresh();
	}
	if (Client::instance()->m_TabWidget.m_COMPARECORD != FALSE)
	{

		Client::instance()->m_dlgExport->OnTreeReFresh();
	}
	if (Client::instance()->m_TabWidget.m_EQMENTMGT != FALSE)
	{
		Client::instance()->eqment->OnTreeReFresh();
		Client::instance()->eqment->on_btnRefresh_clicked();
	}
	this->close();
	//QMessageBox::warning(NULL, QStringLiteral("提示"), QStringLiteral("添加设备信息成功!"));
	myHelper::ShowMessageBoxInfo(QObject::tr("添加设备信息成功"));
}

void AddDevice::on_radioButton_paragr_clicked()
{
	ui.label_Name->setText(QObject::tr("开始IP:"));
	ui.label_Addr->setText(QObject::tr("结束IP:"));
	
}

void AddDevice::on_radioButton_name_clicked()
{
	ui.label_Name->setText(QObject::tr("设备名:"));
	ui.label_Addr->setText(QObject::tr("IP/UUID:"));
}


int AddDevice::getDeviceType(int mode)
{
	int subtype = 0;
	switch(mode)
	{
	case 0:
		subtype = CHANNELINFO_TYPE_QIUJI;
		break;
	case 1:
		subtype = CHANNELINFO_TYPE_QIANGJI;
		break;
	case 2:
		subtype = CHANNELINFO_TYPE_GAOSUQIU;
		break;
	case 3:
		subtype = CHANNELINFO_TYPE_SHEXIANGTOU;
		break;
	case 4:
		subtype = CHANNELINFO_TYPE_SNAP;
		break;
	case 5:
		subtype = CHANNELINFO_TYPE_COMPARE;
		break;
	default:
		subtype = CHANNELINFO_TYPE_COMPARE;
		break;
	}
	return subtype;
}

void AddDevice::on_btnCancel_clicked()
{
	this->close();
}

void AddDevice::on_btnClose_clicked()
{
	close();
}