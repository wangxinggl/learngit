#include "recognition.h"
#include "client.h"

extern Client* g_pInstance;

Recognition::Recognition(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.progressBar->setMinimum(0);
	ui.progressBar->setMaximum(100);
	setStyleSheet(".Recognition{background:transparent;border:2px solid green;}");

	m_pPicName = new char[520];
	m_pLibName = new char[520];
	m_pSnapPath = new char[520];
	m_pTime = new char[16];
	memset(m_pPicName, 0, 520);
	memset(m_pLibName, 0, 520);
	memset(m_pSnapPath, 0, 520);
	memset(m_pTime, 0, 16);
	m_pTime = new char[16];
	memset(m_pTime, 0, 16);
}

Recognition::~Recognition()
{
	if (m_pPicName)
	{
		delete m_pPicName;
		m_pPicName = NULL;
	}
	if (m_pLibName)
	{
		delete m_pLibName;
		m_pLibName = NULL;
	}
	if (m_pSnapPath)
	{
		delete m_pSnapPath;
		m_pSnapPath = NULL;
	}
	if (m_pTime)
	{
		delete m_pTime;
		m_pTime = NULL;
	}
}

void Recognition::ShowInfo(SMART_FACE_CMP_QUERY_INFO *pCompareInfoTmp, int nInvalid, QString strStatus)
{
	memset(m_pTime, 0, 16);

	memcpy(m_pTime, pCompareInfoTmp->sLibSnapTime, 10);
	memset(m_pPicName, 0, 520);
	memset(m_pLibName, 0, 520);
	memset(m_pSnapPath, 0, 520);

	sprintf(m_pSnapPath, "%s\\%s\\%s\\%d", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szSnapPath, m_pTime, pCompareInfoTmp->cDeviceIP, pCompareInfoTmp->sLibChannelid);
	sprintf(m_pPicName, "%s\\%s", m_pSnapPath, (char*)pCompareInfoTmp->sSnappicname);
	sprintf(m_pLibName, "%s\\%s", m_pSnapPath, (char*)pCompareInfoTmp->sLibPicName);

	if (m_pImagePic.load(QString::fromLocal8Bit(m_pPicName)))
	{
		ui.label_pic->setScaledContents(true);
		ui.label_pic->setPixmap(QPixmap::fromImage(m_pImagePic));
	}
	else
	{
		OutputDebugString("Load Snap picture failed");
	}
	if (m_pImageLib.load(QString::fromLocal8Bit(m_pLibName)))
	{
		ui.label_Lib->setScaledContents(true);
		ui.label_Lib->setPixmap(QPixmap::fromImage(m_pImageLib));
	}	
	else
	{
		OutputDebugString("Load Lib picture failed");
	}

	ui.label_Name->setText(QString::fromLocal8Bit(pCompareInfoTmp->sName));
	ui.label_Number->setText(QString::fromLocal8Bit(pCompareInfoTmp->sUserID));
	ui.label_Device->setText(QString::fromLocal8Bit(pCompareInfoTmp->cDevName));
	ui.label_Time->setText(pCompareInfoTmp->sLibSnapTime);
	ui.label_Type->setText(g_pInstance->GetModeType(pCompareInfoTmp->sLibMode));
	ui.label_temperature->setText(strStatus);
	ui.progressBar->setValue(pCompareInfoTmp->sLibSimilarity * 100);
	ui.label_progress->setText(QString::number(pCompareInfoTmp->sLibSimilarity, 'f', 2));
	if (nInvalid)
	{
		ui.label_temperature->setStyleSheet("color:rgb(255, 0, 0)");
	}
	else
	{
		ui.label_temperature->setStyleSheet("color:rgb(255, 251, 240)");
	}
}
