#define  _CRT_SECURE_NO_WARNINGS
#include "modifydevice.h"
#include <QMessageBox>
#include "myhelper.h"
#include "client.h"

extern Client* g_pInstance;

ModifyDevice::ModifyDevice(QWidget *parent)
: QWidget(parent)
, m_pDevInfo(NULL)
{
	ui.setupUi(this);
	ui.radioButton_name->setChecked(true);
	ui.radioButton_name->setEnabled(false);
	ui.radioButton_paragr->setEnabled(false);

	initForm();
	m_pNewDevInfo = new TabDevInfo_t;
	memset(m_pNewDevInfo, 0, sizeof(TabDevInfo_t));
	
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setProperty("canMove", true);
	setStyleSheet(".ModifyChannel{border:2px solid black;}");
}

ModifyDevice::~ModifyDevice()
{
	if (m_pNewDevInfo)
	{
		delete m_pNewDevInfo;
		m_pNewDevInfo = NULL;
	}
}

void ModifyDevice::on_btnSure_clicked()
{
	if (g_pInstance->m_TabWidget.m_bPreview != FALSE)
	{
		g_pInstance->m_pPreviewPro->StopAllWatch();
	}
	strcpy(m_pNewDevInfo->szDevName , ui.lineEdit_Name->text().toUtf8().data());
	strcpy(m_pNewDevInfo->szIpAddr , ui.lineEdit_Addr->text().toLatin1().data());
	m_pNewDevInfo->nPort = ui.lineEdit_Port->text().toInt();
	strcpy(m_pNewDevInfo->szPassword , ui.lineEdit_Pwd->text().toLocal8Bit().data());
	strcpy(m_pNewDevInfo->szLoginName, ui.lineEdit_Usr->text().toLocal8Bit().data());
	m_pNewDevInfo->nDevStatus = DEVINFO_DEVSTATUS_ONLINE;
	int subType = g_pInstance->getDeviceType(ui.comboBox_Type->currentIndex());
	m_pNewDevInfo->nSubDevType = subType;

	bool ret = g_pDatabase->ChangeDevice(m_pNewDevInfo);
	if (ret)
	{
		myHelper::ShowMessageBoxInfo(QObject::tr("修改信息成功!"));
		memcpy(m_pDevInfo, m_pNewDevInfo, sizeof(TabDevInfo_t));
		g_pInstance->OnReFreshOtherTree();
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("修改信息失败!"));
	}

	this->close();
}

void ModifyDevice::initForm()
{
	m_displayName = new QLineEdit;
	m_displayName = ui.lineEdit_Name;
	m_displayIP = new QLineEdit();
	m_displayIP= ui.lineEdit_Addr;
	m_displayIP->setEnabled(false);
	m_displayPort = new QLineEdit;
	m_displayPort = ui.lineEdit_Port;
	m_displayUsr = new QLineEdit;
	m_displayUsr = ui.lineEdit_Usr;
	m_displayPwd = new QLineEdit;
	m_displayPwd = ui.lineEdit_Pwd;
	m_displySubType = new QComboBox;
	m_displySubType = ui.comboBox_Type;
	m_displayChannel = new QComboBox;
	m_displayChannel = ui.comboBox_ChannelNo;
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