#include "AnalysisDlg.h"

AnalysisDlg::AnalysisDlg(QWidget *parent)
	: QDialog(parent)
	, m_pAnalyseVideoAreaDlg(NULL)
	, m_pDevObj(NULL)
	, m_pFaDectectArea(NULL)
	, m_pFaShieldArea(NULL)
	, m_pFaTempArea(NULL)
	, m_nAreaType(0)
	, m_lStreamType(0)
	, m_lSelChannel(0)
	, m_bStartCheck(FALSE)
	, m_nDrawType(DRAW_PEN_Rectangle)
	, m_bStartAreaSet(FALSE)
{
	ui.setupUi(this);


	m_pFaDectectArea = new SDK_FA_VI_DECTECT;
	m_pFaShieldArea = new SDK_FA_VI_SHIELDED;
	m_pFaTempArea = new SDK_FA_VI_TEMPERATURE;

	memset(m_pFaDectectArea, 0, sizeof(SDK_FA_VI_DECTECT));
	memset(m_pFaShieldArea, 0, sizeof(SDK_FA_VI_SHIELDED));
	memset(m_pFaTempArea, 0, sizeof(SDK_FA_VI_TEMPERATURE));

	for (int i = 0; i < DRAW_RECTANGLE_COUNT; i ++)
	{
		memset(&m_stFaceArea[i], 0, sizeof(SDK_AREA_RECT));
	}

	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setStyleSheet(".AnalysisDlg{border:2px solid black;}");
}

AnalysisDlg::~AnalysisDlg()
{
	if (m_pAnalyseVideoAreaDlg)
	{
		delete m_pAnalyseVideoAreaDlg;
		m_pAnalyseVideoAreaDlg = NULL;
	}
	if (m_pFaDectectArea)
	{
		delete m_pFaDectectArea;
		m_pFaDectectArea = NULL;
	}
	if (m_pFaShieldArea)
	{
		delete m_pFaShieldArea;
		m_pFaShieldArea = NULL;
	}
	if (m_pFaTempArea)
	{
		delete m_pFaTempArea;
		m_pFaTempArea = NULL;
	}
}

void AnalysisDlg::init()
{
	if (!m_pAnalyseVideoAreaDlg)
	{
		m_pAnalyseVideoAreaDlg = new AnalyseVideoAreaDlg(this);
	}
	m_pAnalyseVideoAreaDlg->resize(m_pDevObj->m_nWidth, m_pDevObj->m_nHeight);
	m_pAnalyseVideoAreaDlg->move(10, 30);
	m_pAnalyseVideoAreaDlg->show();

	ui.comboBox->clear();

	for (int i = 0; i < m_pDevObj->m_stDevInfo.byChanNum; i++)
	{
		QString str;
		str = QString("%1").arg(i + 1);
		ui.comboBox->insertItem(i, str);
	}
	ui.comboBox->setCurrentIndex(0);

	EnableWindowAnalyse(m_bStartCheck);
	on_comboBox_AreaType_activated(0);
}

long AnalysisDlg::EnableWindowAnalyse(BOOL bEnable)
{
	ui.btnAll->setEnabled(bEnable);
	ui.btnClear->setEnabled(bEnable);
	return 0;
}

long AnalysisDlg::SaveChannelParam(long lChannel)
{
	int nEnable = (ui.checkBox->isChecked() == true) ? 1 : 0;
	int nLaserEnable = (ui.checkBox_Laser->isChecked() == true) ? 1 : 0;

	double dbWScale = 1;
	double dbHscale = 1;
	if (m_pDevObj->m_pDevInfo->nSubDevType == SDK_DEV_TYPE_MJIPC)
	{
		dbWScale = 576 / (double)m_pDevObj->m_nWidth;
		dbHscale = 704 / (double)m_pDevObj->m_nHeight;
	}
	
	for (int i = 0; i < DRAW_RECTANGLE_COUNT; i ++)
	{
		memset(&m_stFaceArea[i], 0, sizeof(SDK_AREA_RECT));
		if (m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].bDrawFinish)
		{
			m_stFaceArea[i].x = min(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[0].x(),
				m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[1].x()) * dbWScale;
			m_stFaceArea[i].y = min(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[0].y(),
				m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[1].y()) * dbHscale;
			m_stFaceArea[i].w = abs(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[1].x() -
				m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[0].x()) * dbWScale;
			m_stFaceArea[i].h = abs(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[1].y() -
				m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[0].y()) * dbHscale;
		}
	}

	switch (m_nAreaType)
	{
	case 0:
		m_pFaDectectArea->bEnable = nEnable;
		memcpy(&m_pFaDectectArea->stFaceMaskArea, &m_stFaceArea[0], sizeof(SDK_AREA_RECT));
		break;

	case 1:
		m_pFaShieldArea->bEnable = nEnable;
		memcpy(&m_pFaShieldArea->stFaceArea, &m_stFaceArea, 4 * sizeof(SDK_AREA_RECT));
		break;

	case 2:
		m_pFaTempArea->nEnable = nEnable;
		m_pFaTempArea->nLaserEnable = nLaserEnable;
		m_pFaTempArea->fTemperature = atof(ui.lineEdit_Temperature->text().toLatin1().data());
		memcpy(&m_pFaTempArea->stFaceMaskArea, &m_stFaceArea[0], sizeof(SDK_AREA_RECT));
		break;
	default:
		break;
	}
	return 0;
}

void AnalysisDlg::on_btnClear_clicked()
{
	memset(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate, 0, sizeof(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate));//清除
	memset(m_pFaDectectArea, 0, sizeof(SDK_FA_VI_DECTECT));
	memset(m_pFaShieldArea, 0, sizeof(SDK_FA_VI_SHIELDED));
	memset(m_pFaTempArea, 0, sizeof(SDK_FA_VI_TEMPERATURE));
	memset(&m_stFaceArea, 0, sizeof(m_stFaceArea));
}

long AnalysisDlg::GetDevParam()
{
	DWORD dwRetLen = 0;
	BOOL bSuccess = FALSE;
	DWORD dwTime = 5000;

	switch (m_nAreaType)
	{
	case 0:
		bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_AREADETECTION, m_lSelChannel,
			(char *)m_pFaDectectArea, sizeof(SDK_FA_VI_DECTECT), &dwRetLen, dwTime);
		memcpy(&m_stFaceArea[0], &m_pFaDectectArea->stFaceMaskArea, sizeof(SDK_AREA_RECT));
		break;
	case 1:
		bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_AREASHIELDED, m_lSelChannel,
			(char *)m_pFaShieldArea, sizeof(SDK_FA_VI_SHIELDED), &dwRetLen, dwTime);
		memcpy(&m_stFaceArea, &m_pFaShieldArea->stFaceArea, sizeof(m_stFaceArea));
		break;
	case 2:
		bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_TEMPERATURE, m_lSelChannel,
			(char *)m_pFaTempArea, sizeof(SDK_FA_VI_TEMPERATURE), &dwRetLen, dwTime);
		memcpy(&m_stFaceArea, &m_pFaTempArea->stFaceMaskArea, sizeof(SDK_AREA_RECT));
		break;
	}
	
	if (!bSuccess)
	{
		DWORD dwRetError = VideoNet_GetLastError();
		OutputDebugString("CAnalyseShelterDetDlg::GetDevParam failed!\r\n");
	}

	return 0;
}

long AnalysisDlg::ShowChannelParam(long lChannel)
{
	ui.checkBox->setChecked(m_pFaTempArea->nEnable);
	ui.checkBox_Laser->setChecked(m_pFaTempArea->nLaserEnable);
	ui.lineEdit_Temperature->setText(QString("%1").arg(m_pFaTempArea->fTemperature));
	memset(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate, 0, sizeof(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate));//清除

	double dbWScale = 1;
	double dbHscale = 1;
	if (m_pDevObj->m_pDevInfo->nSubDevType == SDK_DEV_TYPE_MJIPC)
	{
		double dbWidth = m_pDevObj->m_nWidth;
		double dbHeight = m_pDevObj->m_nHeight;
		dbWScale = dbWidth / 576;
		dbHscale = dbHeight / 704;
	}

	for (int i = 0; i < DRAW_RECTANGLE_COUNT; i ++)
	{
		if (m_stFaceArea[i].w != 0 && m_stFaceArea[i].h != 0)
		{
			m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].bDrawFinish = TRUE;
			m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[0].rx() = m_stFaceArea[i].x * dbWScale;
			m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[0].ry() = m_stFaceArea[i].y * dbHscale;
			m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[1].rx() = (m_stFaceArea[i].x + m_stFaceArea[i].w) * dbWScale;
			m_pAnalyseVideoAreaDlg->m_RectangleCoordinate[i].RectanglePoint[1].ry() = (m_stFaceArea[i].y + m_stFaceArea[i].h) * dbHscale;
		}

		if (m_pAnalyseVideoAreaDlg->m_nArrowDirection == 3)
		{
			m_pAnalyseVideoAreaDlg->m_nArrowDirectionTwoWay = 1;
		}
		m_pAnalyseVideoAreaDlg->m_ArrowPrevPoint.rx() = -1;
		m_pAnalyseVideoAreaDlg->m_ArrowPrevPoint.ry() = -1;
		m_pAnalyseVideoAreaDlg->m_bArrowStart = TRUE;
	}

	return 0;
}

void AnalysisDlg::on_comboBox_activated(int index)
{
	m_lSelChannel = index;
	//SaveChannelParam(index);
	on_btnClear_clicked();
	GetDevParam();
	ShowChannelParam(index);
	m_pAnalyseVideoAreaDlg->StopPlay(m_pDevObj);
	m_pAnalyseVideoAreaDlg->OpenPlay(m_pDevObj, index, m_lStreamType);
}

void AnalysisDlg::on_comboBox_AreaType_activated(int index)
{
	m_nAreaType = index;
	if (m_nAreaType == 2)
	{
		ui.checkBox_Laser->setVisible(true);
		ui.label_Temp->setVisible(true);
		ui.lineEdit_Temperature->setVisible(true);
	}
	else
	{
		ui.checkBox_Laser->setVisible(false);
		ui.label_Temp->setVisible(false);
		ui.lineEdit_Temperature->setVisible(false);
	}
	on_comboBox_activated(m_lSelChannel);
}

void AnalysisDlg::on_btnAreaSet_clicked()
{
	if (m_bStartCheck)
	{
		m_bStartCheck = FALSE;
	}
	else
	{
		m_bStartCheck = TRUE;
	}

	EnableWindowAnalyse(m_bStartCheck);
	m_bStartAreaSet = TRUE;
	ui.checkBox->setChecked(true);
	ui.checkBox_Laser->setChecked(true);
}

void AnalysisDlg::on_btnAll_clicked()
{
	memset(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate, 0, sizeof(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate));//清除
	switch (m_nAreaType)
	{
	case 0:
		memset(m_pFaDectectArea, 0, sizeof(SDK_FA_VI_DECTECT));
		break;
	case 1:
		memset(m_pFaShieldArea, 0, sizeof(SDK_FA_VI_SHIELDED));
		break;
	case 2:
		memset(m_pFaTempArea, 0, sizeof(SDK_FA_VI_TEMPERATURE));
		break;
	}

	QPoint pos(0, 0);
	QPoint posEnd(m_pDevObj->m_nWidth, m_pDevObj->m_nHeight);
	QMouseEvent event(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::sendEvent(m_pAnalyseVideoAreaDlg, &event);
	QMouseEvent eventEnd(QEvent::MouseButtonRelease, posEnd, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::sendEvent(m_pAnalyseVideoAreaDlg, &eventEnd);
}


void AnalysisDlg::on_btnClose_clicked()
{
	m_pAnalyseVideoAreaDlg->StopPlay(m_pDevObj);
	close();
}

void AnalysisDlg::on_btnSave_clicked()
{
	SaveChannelParam(m_lSelChannel);
	if (m_pDevObj->GetLoginID() > 0)
	{
		long bResult = 0;
		int nWaitTime = 5000;
		switch (m_nAreaType)
		{
		case 0:
			bResult = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_AREADETECTION, m_lSelChannel,
				(char *)m_pFaDectectArea, sizeof(SDK_FA_VI_DECTECT), nWaitTime);
			break;
		case 1:
			bResult = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_AREASHIELDED, m_lSelChannel,
				(char *)m_pFaShieldArea, sizeof(SDK_FA_VI_SHIELDED), nWaitTime);
			break;
		case 2:
			bResult = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_TEMPERATURE, m_lSelChannel,
				(char *)m_pFaTempArea, sizeof(SDK_FA_VI_TEMPERATURE), nWaitTime);
			break;

		}
		if (VIDEONET_SUCCESS == bResult)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("保存配置数据成功!\r\n"));
		}
		else
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("保存配置数据失败!\r\n"));
		}
	}
}
