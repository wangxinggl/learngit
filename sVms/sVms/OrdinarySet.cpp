#include "OrdinarySet.h"

#include "myhelper.h"
OrdinarySet::OrdinarySet(QWidget *parent)
	: QDialog(parent)
	, m_pstConfigNormal(NULL)
	, m_pDevObj(NULL)
{
	ui.setupUi(this);
	InitComboBox();
	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setStyleSheet(".OrdinarySet{border:2px solid black;}");
}

OrdinarySet::~OrdinarySet()
{
}

void OrdinarySet::InitComboBox()
{
	//视频制式
	ui.comboBox_vFormat->clear();
	ui.comboBox_vFormat->addItem("PAL");
	ui.comboBox_vFormat->addItem("NTSC");
	//日期格式
	ui.comboBox_dFormat->clear();
	ui.comboBox_dFormat->addItem("YYYY-MM-DD");
	ui.comboBox_dFormat->addItem("MM-DD-YYYY");
	ui.comboBox_dFormat->addItem("DD-MM-YYYY");
	//日期分隔符
	ui.comboBox_dInterval->clear();
	ui.comboBox_dInterval->addItem("\" . \"");
	ui.comboBox_dInterval->addItem("\" - \"");
	ui.comboBox_dInterval->addItem("\" / \"");
	//时间格式

	QString strTime[] = { QObject::tr("24小时"), QObject::tr("12小时")};
	ui.comboBox_tFormat->clear();
	for (int i = 0; i < 2; i ++)
	{
		ui.comboBox_tFormat->insertItem(i, strTime[i]);
	}
	ui.comboBox_tFormat->setCurrentIndex(0);
}

void OrdinarySet::on_btnClose_clicked()
{
	close();
}

void OrdinarySet::InitDlgInfo()
{
	QString strCodeMode[] = { QObject::tr("English"), QObject::tr("Chinese")};

	ui.comboBox_Language->clear();
	for (int i = 0; i < 2; i ++)
	{
		ui.comboBox_Language->insertItem(i, strCodeMode[i]);
	}
	ui.comboBox_Language->setCurrentIndex(m_pstConfigNormal->iLanguage);


	QString strInfo;
	strInfo = m_pstConfigNormal->sMachineName;
	ui.lineEdit_Device->setText(strInfo);
	ui.comboBox_dFormat->setCurrentIndex(m_pstConfigNormal->iDateFormat);
	ui.comboBox_dInterval->setCurrentIndex(m_pstConfigNormal->iDateFormat);
	ui.comboBox_tFormat->setCurrentIndex(m_pstConfigNormal->iTimeFormat);
	ui.comboBox_vFormat->setCurrentIndex(m_pstConfigNormal->iVideoFormat);

}

void OrdinarySet::on_btnSave_clicked()
{
	SDK_CONFIG_NORMAL stConfigNormal = {0};
	memcpy(&stConfigNormal, m_pstConfigNormal, sizeof(SDK_CONFIG_NORMAL));
	QString str = ui.lineEdit_Device->text();
	strcpy(stConfigNormal.sMachineName, str.toLocal8Bit().data());

	stConfigNormal.iDateFormat = ui.comboBox_dFormat->currentIndex();
	stConfigNormal.iTimeFormat = ui.comboBox_tFormat->currentIndex();
	stConfigNormal.iDateSeparator = ui.comboBox_dInterval->currentIndex();

	stConfigNormal.iVideoFormat = ui.comboBox_vFormat->currentIndex();
	int i = 0;
	stConfigNormal.iLanguage = ui.comboBox_Language->currentIndex();

	SetDeviceConfigInfo(&stConfigNormal);
}

void OrdinarySet::SetDeviceConfigInfo(SDK_CONFIG_NORMAL* pConfigNormal)
{
	int nWaitTime = 5000;
	if (m_pDevObj->m_lUserLoginID > 0)
	{
		BOOL bSuccess = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_SYSNORMAL, 0, (char *)pConfigNormal, sizeof(SDK_CONFIG_NORMAL), nWaitTime);
		if (bSuccess == VIDEONET_OPT_REBOOT)
		{
			bSuccess = VideoNet_ControlDVR(m_pDevObj->m_lUserLoginID, 0, nWaitTime);
			if (!bSuccess)
			{
				myHelper::ShowMessageBoxWarning(QObject::tr("重启失败"));
			}
		}
		else if (bSuccess > 0)
		{
			myHelper::ShowMessageBoxInfo(QObject::tr("保存配置成功"));
		}
		else {
			myHelper::ShowMessageBoxWarning(QObject::tr("保存配置失败"));
		}
	}
}

void OrdinarySet::on_btnUpgrade_clicked()
{
	if (m_pDevObj->GetLoginID() > 0)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_SYSNORMAL, 0,
			(char *)m_pstConfigNormal, sizeof(SDK_CONFIG_NORMAL), &dwRetLen, nWaitTime);
		if (!bSuccess)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("获取系统信息失败"));
		}

		InitDlgInfo();
	}
}