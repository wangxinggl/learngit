#include "unrecognition.h"
#include "client.h"

extern Client* g_pInstance;

unRecognition::unRecognition(QWidget *parent)
	: QWidget(parent)
	, m_pPicName(NULL)
	, m_pSnapPath(NULL)
	, m_pszTime(NULL)
{
	ui.setupUi(this);

	m_pPicName = new char[520];
	m_pSnapPath = new char[520];
	m_pszTime = new char[16];
}

unRecognition::~unRecognition()
{
	if (m_pPicName)
	{
		delete m_pPicName;
		m_pPicName = NULL;
	}
	if (m_pSnapPath)
	{
		delete m_pSnapPath;
		m_pSnapPath = NULL;
	}
	if (m_pszTime)
	{
		delete m_pszTime;
		m_pszTime = NULL;
	}
}

void unRecognition::ShowInfo(SMART_FACE_CMP_QUERY_INFO *pCompareInfoTmp, BOOL bInVailid, QString pszStatus)
{
	memset(m_pPicName, 0, 520);
	memset(m_pSnapPath, 0, 520);
	memset(m_pszTime, 0, 16);

	memcpy(m_pszTime, pCompareInfoTmp->sLibSnapTime, 10);
	sprintf(m_pSnapPath, "%s\\%s\\%s\\%d", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szSnapPath, m_pszTime, 
		pCompareInfoTmp->cDeviceIP, pCompareInfoTmp->sLibChannelid);

	sprintf(m_pPicName, "%s\\%s", m_pSnapPath, (char*)pCompareInfoTmp->sSnappicname);
	m_strImagePath = QString::fromLocal8Bit(m_pPicName);
	m_strSnapTime = QString(QLatin1String(pCompareInfoTmp->sLibSnapTime));
	
	m_Image.load(m_strImagePath);
	resize(QSize(m_Image.width(), m_Image.height()));
	m_Image.scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setPixmap(QPixmap::fromImage(m_Image));
	ui.label_displayTime->setText(m_strSnapTime);
	ui.label_Temperature->setText(pszStatus);
	if (bInVailid)
	{
		ui.label_Temperature->setStyleSheet("color:rgb(255, 0, 0)");
	}
	else
	{
		ui.label_Temperature->setStyleSheet("color:rgb(255, 251, 240)");
	}
}
