#define  _CRT_SECURE_NO_WARNINGS
#include "adddevice.h"
#include <QMessageBox>
#include "table_structs.h"
#include <stdio.h>
#include <QDebug>
#include "myhelper.h"
#include <QObject>
#include "client.h"
#include <QTextCodec>
extern vector<TabDevInfo_t*>			g_vectorDevInfo;
extern vector<TabChannelInfo_t*>		g_vectorChannelInfo;
extern Client* g_pInstance;

AddDevice::AddDevice(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.radioButton_name->setChecked(true);
	m_Select = 0;
	m_nCompany = 0;
	connect(ui.comboBox_Type,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxCurrentIndexChanged(int)));

	ui.lineEdit_Port->setText("36123");
	ui.lineEdit_Usr->setText("admin");
	ui.lineEdit_Pwd->setText("admin");
	//setWindowTitle(QObject::tr("添加设备"));
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setProperty("canMove", true);

}

AddDevice::~AddDevice()
{

}

void AddDevice::on_btnSure_clicked()
{
	QString strIpAddr = ui.lineEdit_Addr->text();
	QString strName = ui.lineEdit_Name->text().toUtf8();
	if (strIpAddr.isEmpty() || strName.isEmpty())
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("地址信息不能为空"));
		return;
	}
	TabDevInfo_t* pDevInfo = NULL;
	TabChannelInfo_t* pChannelInfo = NULL;
	
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

	if (g_pInstance->m_TabWidget.m_bPreview != FALSE)
	{
		g_pInstance->m_pPreviewPro->StopAllWatch();
	}
	
	for (int i = startipNum;i<endipNum;i++)
	{
		pDevInfo = new TabDevInfo_t;
		memset(pDevInfo, 0, sizeof(TabDevInfo_t));
		int nSubType = 0;
		pDevInfo->nPort = ui.lineEdit_Port->text().toInt();
		strcpy(pDevInfo->szLoginName, ui.lineEdit_Usr->text().toLocal8Bit().data());
		strcpy(pDevInfo->szPassword, ui.lineEdit_Pwd->text().toLatin1().data());
		pDevInfo->nDevStatus = DEVINFO_DEVSTATUS_ONLINE;

		QString EachIp = startIp.section('.',0,2)+"."+QString("%1").arg(i);
		if (ui.radioButton_paragr->isChecked() == true)
		{
			strcpy(pDevInfo->szIpAddr , EachIp.toLatin1().data());
			strcpy(pDevInfo->szDevName, EachIp.toLatin1().data());
		}
		else
		{
			strcpy(pDevInfo->szIpAddr , endIP.toLatin1().data());
			strcpy(pDevInfo->szDevName, ui.lineEdit_Name->text().toLocal8Bit().data());
		}
		int ret = g_pDatabase->checkDevice(pDevInfo->szIpAddr, pDevInfo->nPort);
		if (ret)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("设备已经存在"));
			delete pDevInfo;
			pDevInfo = NULL;
			continue;
		}

		m_nCompany = DEVINFO_MANUFACTURER_JL_NEW;

		nChanNum = ui.comboBox_ChannelNo->currentText().toInt();
		nSubType = g_pInstance->getDeviceType(ui.comboBox_Type->currentIndex());
		pDevInfo->nSubDevType = nSubType;

		pDevInfo->nType = SDK_DEV_TYPE_IPC;
		strcpy(pDevInfo->szDevType, "JVT IP Camera");
		if (nChanNum > 1)
		{
			pDevInfo->nType = SDK_DEV_TYPE_NVR;
			strcpy(pDevInfo->szDevType, "JVT NVR");
			pDevInfo->nSubDevType = nSubType;
		}
		pDevInfo->nManufacturer = m_nCompany;
		 ret = g_pDatabase->AddDevice(pDevInfo);
		if (!ret)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("'%1'插入到数据库失败").arg(pDevInfo->szIpAddr));
			delete pDevInfo;
			pDevInfo = NULL;
			continue;
		}

		int nDevId = g_pDatabase->getDeviceID(pDevInfo->szIpAddr);
		pDevInfo->nDevId = nDevId;
		g_vectorDevInfo.push_back(pDevInfo);


		for (int nChannelNo = 1;nChannelNo <= nChanNum;nChannelNo++)
		{
			pChannelInfo = new TabChannelInfo_t;
			pChannelInfo->DevId = nDevId;
			pChannelInfo->Status = CHANNELINFO_STATUS_OPEN;
			pChannelInfo->Type = nSubType;
			pChannelInfo->Channel = nChannelNo;

			sprintf(pChannelInfo->szChannelName, "ch%02d", nChannelNo);
			 ret = g_pDatabase->AddChannelInfo(pChannelInfo);
			if (!ret)
			{
				myHelper::ShowMessageBoxWarning(QObject::tr("channelinfo信息插入到插入到数据库失败!"));
				delete pChannelInfo;
				pChannelInfo = NULL;
				continue;
			}
			pChannelInfo->SlaveDevId = g_pDatabase->GetChannelID(pChannelInfo->DevId, pChannelInfo->Channel);
			g_vectorChannelInfo.push_back(pChannelInfo);			
		}
		g_pInstance->AddDevice(pDevInfo);
	}

	g_pInstance->OnReFreshOtherTree();

	this->close();
}

void AddDevice::on_radioButton_paragr_clicked()
{
	ui.label_Name->setText(QObject::tr("开始IP:"));
	ui.label_Addr->setText(QObject::tr("结束IP:"));	
}

void AddDevice::on_radioButton_name_clicked()
{
	ui.label_Name->setText(QObject::tr("设备名称:"));
	ui.label_Addr->setText(QObject::tr("IP/UUID:"));
}

void AddDevice::on_btnCancel_clicked()
{
	this->close();
}

void AddDevice::on_btnClose_clicked()
{
	close();
}