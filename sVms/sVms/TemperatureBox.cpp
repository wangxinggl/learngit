#include "TemperatureBox.h"
#include "client.h"

extern Client* g_pInstance;

CTemperatureBox::CTemperatureBox(QWidget *parent)
	: QWidget(parent)
	, m_bShow(FALSE)
{
	ui.setupUi(this);

	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setStyleSheet(".CTemperatureBox{border:2px solid black;}");

	ui.label_Temperature->setStyleSheet("color:rgb(255, 0, 0)");
}

CTemperatureBox::~CTemperatureBox()
{
}

void CTemperatureBox::on_btnClose_clicked()
{
	m_bShow = FALSE;
	close();
}

void CTemperatureBox::ShowInfo(SMART_FACE_CMP_QUERY_INFO *pCompareInfoTmp, QString pszStatus)
{
	memset(m_szPicName, 0, 520);
	memset(m_szSnapPath, 0, 520);
	memset(m_chTime, 0, 16);

	memcpy(m_chTime, pCompareInfoTmp->sLibSnapTime, 10);
	sprintf(m_szSnapPath, "%s\\%s\\%s\\%d", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szSnapPath, m_chTime,
		pCompareInfoTmp->cDeviceIP, pCompareInfoTmp->sLibChannelid);

	sprintf_s(m_szPicName, "%s\\%s", m_szSnapPath, (char*)pCompareInfoTmp->sSnappicname);
	m_strImagePath = QString::fromLocal8Bit(m_szPicName);
	m_strSnapTime = QString(QLatin1String(pCompareInfoTmp->sLibSnapTime));

	m_Image.load(m_strImagePath);
	m_Image.scaled(ui.label->size(), Qt::KeepAspectRatio);

	ui.label->setPixmap(QPixmap::fromImage(m_Image));
	ui.label_displayTime->setText(m_strSnapTime);
	ui.label_Temperature->setText(pszStatus);
}
