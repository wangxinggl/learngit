#include "Upgrade.h"
#include <QFileDialog>
#include <QStringList>
#include "myhelper.h"
#include "CompareEvent.h"

Upgrade::Upgrade(QWidget *parent)
	: QDialog(parent)
	, m_pDevObj(NULL)
	, m_bSendStatus(FALSE)
	, m_bUpgradeStatus(FALSE)
{
	ui.setupUi(this);
	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setStyleSheet(".Upgrade{border:2px solid black;}");
	this->setWindowFlags(Qt::FramelessWindowHint);
	ui.progressBar->setRange(0, 100);
	m_lUpgradeHandle = 0;
}

Upgrade::~Upgrade()
{
}

void Upgrade::on_btnClose_clicked()
{
	close();
}

void Upgrade::initUPgradeInfo()
{
	QString  strSoftwareVersion = m_pDevObj->m_stDevInfo.sSoftWareVersion;
	ui.label_Version->setText(strSoftwareVersion);
}

void Upgrade::on_btnSelect_clicked()
{
	upGradeFileName = QFileDialog::getOpenFileName(this, QObject::tr("选择文件"), ".", "*"); //选择路径
	ui.lineEdit->setText(upGradeFileName);
}

void Upgrade::on_btnUpgrade_clicked()
{
	if (m_lUpgradeHandle > 0)
	{
		return;
	}
	if (upGradeFileName.isEmpty())
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择升级文件"));
		return;
	}
	m_lUpgradeHandle = VideoNet_Upgrade(m_pDevObj->m_lUserLoginID, upGradeFileName.toLocal8Bit().data(), 0, UpgradeCallBack, (JVT_DWORD)this);
	if (m_lUpgradeHandle <= 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("升级失败"));
		return;
	}
	ui.progressBar->setValue(0);
	m_bSendStatus = FALSE;
	m_bUpgradeStatus = FALSE;
	EnableBtn(false);
}

void CALL_METHOD Upgrade::UpgradeCallBack(JVT_LONG lLoginID, long lUpgradechannel, int nTotalSize, int nSendSize, JVT_DWORD dwUser)
{
	Upgrade* pUpgradeDlg = (Upgrade*)dwUser;
	QString strStatus;
	if (NULL == pUpgradeDlg)
	{
		return;
	}
	int nPos = 0;
	if (nTotalSize > 0)	//发送数据进度
	{
		nPos = (nSendSize * 100) / nTotalSize;
		if (nPos > 100)
		{
			nPos = 100;
		}
	}
	else if (nTotalSize == 0)	//升级进度
	{
		if (nSendSize > 0)
		{
			nPos = nSendSize;
		}
		else if (nSendSize == -1)
		{
			nPos = 100;		//升级完成
			pUpgradeDlg->EnableBtn(true);
		}
		else if (nSendSize == -2)
		{
			nPos = 0;		//升级失败
		}
	}
	pUpgradeDlg->OnUpgradeStaus(nPos);
	return;
}


long Upgrade::OnUpgradeStaus(int nPos)
{
	ui.progressBar->setValue(nPos);
	return 0;
}

void Upgrade::on_btnRestart_clicked()
{
	BOOL bRet = FALSE;
	char chBuf[1024] = { 0 };
	bRet = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_REBOOT_DEV, -1, chBuf, 1024);
	if (bRet == VIDEONET_SUCCESS)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("重启成功!"));
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("重启失败!"));
	}
}

void Upgrade::on_btnRestore_clicked()
{
	BOOL bRet = FALSE;
	char chBuf[1024] = { 0 };

	bRet = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_EXPORT_V2, -1, chBuf, 1024);
	if (bRet == VIDEONET_SUCCESS)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("恢复出厂成功!"));
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("恢复出厂失败!"));
	}
}

void Upgrade::on_btnFormat_clicked()
{
	BOOL bRet = FALSE;
	char chBuf[1024] = { 0 };
	DWORD dwTime = 30 * 1000;
	SDK_FORMAT_SD_INFO stFormatParam = { 0 };
	stFormatParam.nFormatNum = 1;
	stFormatParam.nCardNumber[0] = ui.comboBox->currentIndex();

	bRet = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_FORMAT, 0, (char*)&stFormatParam, sizeof(SDK_FORMAT_SD_INFO), dwTime);
	if (bRet == VIDEONET_SUCCESS)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("格式化成功!"));
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("格式化失败!"));
	}
}

void Upgrade::EnableBtn(bool bStatus)
{
	ui.btnSelect->setEnabled(bStatus);
	ui.btnClose->setEnabled(bStatus);
	ui.btnFormat->setEnabled(bStatus);
	ui.btnUpgrade->setEnabled(bStatus);
	ui.btnRestore->setEnabled(bStatus);
	ui.btnRestart->setEnabled(bStatus);
}
