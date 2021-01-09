#include "modifydevice.h"
#include <QMessageBox>
#include "myhelper.h"
#include "client.h"
ModifyDevice::ModifyDevice(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.radioButton_name->setChecked(true);
	ui.radioButton_name->setEnabled(false);
	ui.radioButton_paragr->setEnabled(false);

	initForm();

	
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setProperty("canMove", true);

}

ModifyDevice::~ModifyDevice()
{

}

void ModifyDevice::on_btnSure_clicked()
{

	
	//memset(&devInfo, 0, sizeof(TabDevInfo_t));
	strcpy(devInfo.szDevName , ui.lineEdit_Name->text().toLocal8Bit().data());
	strcpy(devInfo.szIpAddr , ui.lineEdit_Addr->text().toLatin1().data());
	devInfo.nPort = ui.lineEdit_Port->text().toInt();
	strcpy(devInfo.szPassword , ui.lineEdit_Pwd->text().toLocal8Bit().data());
	strcpy(devInfo.szLoginName, ui.lineEdit_Usr->text().toLocal8Bit().data());
	devInfo.nDevStatus = DEVINFO_DEVSTATUS_ONLINE;
	int subType = ui.comboBox_Type->currentIndex();
	switch (subType)
	{
	case 0:
		devInfo.nSubDevType = CHANNELINFO_TYPE_QIUJI;
		break;
	case 1:
		devInfo.nSubDevType = CHANNELINFO_TYPE_QIANGJI;
		break;
	case 2:
		devInfo.nSubDevType = CHANNELINFO_TYPE_GAOSUQIU;
		break;
	case 3:
		devInfo.nSubDevType = CHANNELINFO_TYPE_SHEXIANGTOU;
		break;
	case 4:
		devInfo.nSubDevType = CHANNELINFO_TYPE_SNAP;
		break;
	case 5:
		devInfo.nSubDevType = CHANNELINFO_TYPE_COMPARE;
		break;
	default:
		devInfo.nSubDevType = CHANNELINFO_TYPE_COMPARE;
		break;
	}

	//strcpy(devInfo.szDevName , devInfo.szIpAddr);
	DB *db = new DB;
	bool ret = db->ChangeDevice(devInfo.szIpAddr,devInfo.nPort,devInfo.szLoginName,
		devInfo.szPassword,devInfo.szDevName,devInfo.nManufacturer,
		QString::number(devInfo.nType),devInfo.nDevStatus,devInfo.nSubDevType);
	if (ret)
	{
		//QMessageBox::question(NULL, QObject::tr("警告"), QObject::tr("修改信息成功"));
		myHelper::ShowMessageBoxInfo(QObject::tr("修改信息成功!"));
	}
	else
	{
		//QMessageBox::question(NULL, QObject::tr("警告"), QObject::tr("修改信息失败"));
		myHelper::ShowMessageBoxWarning(QObject::tr("修改信息失败!"));
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
}

void ModifyDevice::initForm()
{
	m_displayName = new QLineEdit;
	m_displayName = ui.lineEdit_Name;
	m_displayIP = new QLineEdit();
	m_displayIP= ui.lineEdit_Addr;
	m_displayPort = new QLineEdit;
	m_displayPort = ui.lineEdit_Port;
	m_displayUsr = new QLineEdit;
	m_displayUsr = ui.lineEdit_Usr;
	m_displayPwd = new QLineEdit;
	m_displayPwd = ui.lineEdit_Pwd;
	m_displySubType = new QComboBox;
	m_displySubType = ui.comboBox_Type;
	this->setWindowTitle(QObject::tr("添加"));

}

void ModifyDevice::on_btnCancel_clicked()
{
	close();
}

void ModifyDevice::on_btnClose_clicked()
{
	close();
}