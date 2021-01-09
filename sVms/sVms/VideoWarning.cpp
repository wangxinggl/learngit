#include "VideoWarning.h"
#include "myhelper.h"


VideoWarning::VideoWarning(QWidget *parent)
	: QDialog(parent)
	, m_pDevObj(NULL)
{
	ui.setupUi(this);
	m_pAnalyseVideoAreaDlg = NULL;
	m_lSelChannel = 0;
	m_lStreamType = 0;
	m_bStartCheck = FALSE;
	m_nDrawType = DRAW_PEN_Rectangle;
	m_bStartAreaSet = FALSE;
	m_pFaShielded = NULL;

	m_pFaShielded = new SDK_FA_VI_SHIELDED;
	memset(m_pFaShielded, 0, sizeof(SDK_FA_VI_SHIELDED));

	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setStyleSheet(".VideoWarning{border:2px solid black;}");
}

VideoWarning::~VideoWarning()
{
}

void VideoWarning::init()
{
	if (NULL == m_pAnalyseVideoAreaDlg)
	{
		m_pAnalyseVideoAreaDlg = new AnalyseVideoAreaDlg(this);
		m_pAnalyseVideoAreaDlg->move(10, 30);
		m_pAnalyseVideoAreaDlg->show();
	}

	ui.comboBox->clear();

	for (int ix = 0; ix < m_pDevObj->m_stDevInfo.byChanNum; ix++)
	{
		QString str;
		str = QString("%1").arg(ix + 1);
		ui.comboBox->insertItem(ix, str);
	}
	ui.comboBox->setCurrentIndex(0);



	EnableWindowAnalyse(m_bStartCheck);
	OnCbnSelchangeComChannel();
}

long VideoWarning::EnableWindowAnalyse(BOOL bEnable)
{
	ui.btnAll->setEnabled(bEnable);
	ui.btnClear->setEnabled(bEnable);
	return 0;
}

void VideoWarning::OnCbnSelchangeComChannel()
{
	int lSelChannel = ui.comboBox->currentIndex();
	if (lSelChannel < 0)
	{
		m_lSelChannel = 0;
		SaveChannelParam(m_lSelChannel);
	}
	else
	{
		SaveChannelParam(m_lSelChannel);
	}
	on_btnClear_clicked();
	m_lSelChannel = lSelChannel;
	GetDevParam();
	ShowChannelParam(lSelChannel);
	m_pAnalyseVideoAreaDlg->StopPlay(m_pDevObj);
	m_pAnalyseVideoAreaDlg->OpenPlay(m_pDevObj, m_lSelChannel, m_lStreamType);
}

void VideoWarning::on_btnClear_clicked()
{
	memset(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate, 0, sizeof(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate));//清除
	memset(m_pFaShielded, 0, sizeof(SDK_FA_VI_SHIELDED));
}

long VideoWarning::SaveChannelParam(long lChannel)
{
	m_pFaShielded->bEnable = ui.checkBox->checkState();
	if (m_pFaShielded->bEnable > 1)
	{
		m_pFaShielded->bEnable = 1;
	}
	for (int ix = 0; ix < DRAW_RECTANGLE_COUNT; ix++)
	{
		if (m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].bDrawFinish)
		{
			m_pFaShielded->stFaceArea[ix].x = min(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[0].x(), m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[1].x());
			m_pFaShielded->stFaceArea[ix].y = min(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[0].y(), m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[1].y());
			m_pFaShielded->stFaceArea[ix].w = abs(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[1].x() - m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[0].x());
			m_pFaShielded->stFaceArea[ix].h = abs(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[1].y() - m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[0].y());
		}

	}
	return 0;
}

long VideoWarning::GetDevParam()
{
	memset(m_pFaShielded, 0, sizeof(SDK_FA_VI_SHIELDED));
	memset(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate, 0, sizeof(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate));//清除

	DWORD dwRetLen = 0;
	int nWaitTime = 10000;

	BOOL bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_AREASHIELDED, m_lSelChannel,
		(char *)m_pFaShielded, sizeof(SDK_FA_VI_SHIELDED), &dwRetLen, nWaitTime);
	if (!bSuccess)
	{
		DWORD dwRetError = VideoNet_GetLastError();
		OutputDebugString("CAnalyseShelterDetDlg::GetDevParam failed!\r\n");
	}
	return 0;
}

long VideoWarning::SetDevParam()
{
	SaveChannelParam(m_lSelChannel);
	if (m_pDevObj->m_lUserLoginID > 0)
	{
		long bResult = 0;
		int nWaitTime = 10000;
		bResult = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_AREASHIELDED, m_lSelChannel,
			(char *)m_pFaShielded, sizeof(SDK_FA_VI_SHIELDED), nWaitTime);
		if (VIDEONET_SUCCESS == bResult)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("保存配置数据成功!\r\n"));
		}
		else
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("保存配置数据失败!\r\n"));
		}
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("设备不在线!\r\n"));
	}

	return 0;
}

long VideoWarning::ShowChannelParam(long lChannel)
{
	ui.checkBox->setChecked(m_pFaShielded->bEnable);

	memset(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate, 0, sizeof(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate));//清除

	for (int ix = 0; ix < DRAW_RECTANGLE_COUNT; ix++)
	{

		if (m_pFaShielded->stFaceArea[ix].w != 0 && m_pFaShielded->stFaceArea[ix].h != 0)
		{
			m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].bDrawFinish = TRUE;
			m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[0].rx() = m_pFaShielded->stFaceArea[ix].x;
			m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[0].ry() = m_pFaShielded->stFaceArea[ix].y;
			m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[1].rx() = m_pFaShielded->stFaceArea[ix].x + m_pFaShielded->stFaceArea[ix].w;
			m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[ix].RectanglePoint[1].ry() = m_pFaShielded->stFaceArea[ix].y + m_pFaShielded->stFaceArea[ix].h;

			if (m_pAnalyseVideoAreaDlg->m_nArrowDirection == 3)
			{
				m_pAnalyseVideoAreaDlg->m_nArrowDirectionTwoWay = 1;
			}
			m_pAnalyseVideoAreaDlg->m_ArrowPrevPoint.rx() = -1;
			m_pAnalyseVideoAreaDlg->m_ArrowPrevPoint.ry() = -1;
			m_pAnalyseVideoAreaDlg->m_bArrowStart = TRUE;
		}
	}
	return 0;
}

void VideoWarning::on_btnClose_clicked()
{
	m_pAnalyseVideoAreaDlg->StopPlay(m_pDevObj);
	close();
}

void VideoWarning::on_comboBox_activated(int index)
{
	int lSelChannel = ui.comboBox->currentIndex();
	if (lSelChannel < 0)
	{
		m_lSelChannel = 0;
		SaveChannelParam(m_lSelChannel);
	}
	else
	{
		SaveChannelParam(m_lSelChannel);
	}
	on_btnClear_clicked();
	m_lSelChannel = lSelChannel;
	GetDevParam();
	ShowChannelParam(lSelChannel);
	m_pAnalyseVideoAreaDlg->StopPlay(m_pDevObj);
	m_pAnalyseVideoAreaDlg->OpenPlay(m_pDevObj, m_lSelChannel, m_lStreamType);
}