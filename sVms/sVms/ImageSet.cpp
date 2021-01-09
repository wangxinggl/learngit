#include "ImageSet.h"
#include "myhelper.h"
#include<QDebug>

ImageSet::ImageSet(QWidget *parent)
	: QDialog(parent)
	, m_pDevObj(NULL)
{
	ui.setupUi(this);
	m_pAnalyseVideoAreaDlg = NULL;
	m_lSelChannel = 0;
	m_lStreamType = 0;

	m_pVideoColorArea = new SDK_VIDEOCOLOR_PARAM();
	memset(m_pVideoColorArea, 0, sizeof(SDK_VIDEOCOLOR_PARAM));
	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setStyleSheet(".ImageSet{border:2px solid black;}");
}

ImageSet::~ImageSet()
{
}

void ImageSet::init()
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
	on_comboBox_activated(m_lSelChannel);
	/*if (NULL == m_pAnalyseVideoAreaDlg)
	{
		m_pAnalyseVideoAreaDlg = new AnalyseVideoAreaDlg(this);
		m_pAnalyseVideoAreaDlg->move(10, 30);
		m_pAnalyseVideoAreaDlg->show();
	}
	m_pAnalyseVideoAreaDlg->StopPlay(m_pDevObj);
	m_pAnalyseVideoAreaDlg->OpenPlay(m_pDevObj, m_nChannelNum, m_lStreamType);*/
}

void ImageSet::on_btnClose_clicked()
{
	m_pAnalyseVideoAreaDlg->StopPlay(m_pDevObj);
	close();
}

void ImageSet::on_comboBox_activated(int index)
{
	m_lSelChannel = index;
	//SaveChannelParam(index);
	
	GetDevParam();
	//ShowChannelParam(index);
	m_pAnalyseVideoAreaDlg->StopPlay(m_pDevObj);
	m_pAnalyseVideoAreaDlg->OpenPlay(m_pDevObj, index, m_lStreamType);
}

void ImageSet::GetDevParam()
{
	/*DWORD dwRetLen = 0;
	
	DWORD dwTime = 5000;
	bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_VIDEOCOLOR, m_lSelChannel,
			(char *)m_pVideoColorArea, sizeof(SDK_VIDEOCOLOR_PARAM), &dwRetLen, dwTime);
*/
	DWORD dwRetLen = 0;
	DWORD dwTime = 5000;
	SDK_VideoColorConfigAll colorConfigAll = { 0 };
	BOOL bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_VIDEOCOLOR, -1,
		(char*)&colorConfigAll, sizeof(SDK_VideoColorConfigAll),&dwRetLen,dwTime);
	qDebug() << colorConfigAll.vVideoColorAll[0].dstVideoColor[0].dstColor.nBrightness;
	qDebug() << colorConfigAll.vVideoColorAll[0].dstVideoColor[0].dstColor.nContrast;
	qDebug() << colorConfigAll.vVideoColorAll[0].dstVideoColor[0].dstColor.nAcutance;
	qDebug() << colorConfigAll.vVideoColorAll[0].dstVideoColor[0].dstColor.nSaturation;
	return;
}