#define  _CRT_SECURE_NO_WARNINGS
#include "StreamSet.h"
#include <stdio.h>
#include <QDebug>

#define BITMSK(bit)				(int)(1 << (bit))
#define  IFRAME_EQ_PFRAME 10

static CONFIG_PAIR s_PvideoResolutionMap[] =
{
	{ SDK_CAPTURE_SIZE_D1, "704*576" },
	{ SDK_CAPTURE_SIZE_HD1, "352*576" },
	{ SDK_CAPTURE_SIZE_BCIF, "720*288" },
	{ SDK_CAPTURE_SIZE_CIF, "352*288" },
	{ SDK_CAPTURE_SIZE_QCIF, "176*144" },
	{ SDK_CAPTURE_SIZE_VGA, "640*480" },
	{ SDK_CAPTURE_SIZE_QVGA, "320*240" },
	{ SDK_CAPTURE_SIZE_SVCD, "480*480" },
	{ SDK_CAPTURE_SIZE_QQVGA, "160*128" },
	{ SDK_CAPTURE_SIZE_ND1, " 240*192" },
	{ SDK_CAPTURE_SIZE_650TVL, "926*576" },
	{ SDK_CAPTURE_SIZE_720P, "1280*720" },
	{ SDK_CAPTURE_SIZE_1_3M, "1280*960" },
	{ SDK_CAPTURE_SIZE_UXGA, "1600*1200" },
	{ SDK_CAPTURE_SIZE_1080P, "1920*1080" },
	{ SDK_CAPTURE_SIZE_WUXGA, "1920*1200" },
	{ SDK_CAPTURE_SIZE_2_5M, "1872*1408" },
	{ SDK_CAPTURE_SIZE_3M, "2048*1536" },
	{ SDK_CAPTURE_SIZE_5M, "3744*1408" },
	{ SDK_CAPTURE_SIZE_1080N, "960*1080" },
	{ SDK_CAPTURE_SIZE_4M, "2592*1520" },
	{ SDK_CAPTURE_SIZE_6M, "3072×2048" },
	{ SDK_CAPTURE_SIZE_8M, "3264×2448" },
	{ SDK_CAPTURE_SIZE_12M, "4000*3000" },
	{ SDK_CAPTURE_SIZE_4K, "4096 * 2160" },
	{ SDK_CAPTURE_SIZE_720N, "640*720" },
	{ SDK_CAPTURE_SIZE_WSVGA, "1024*576" },
	{ NULL, }
};

static CONFIG_PAIR s_NvideoResolutionMap[] =
{
	{ SDK_CAPTURE_SIZE_D1, "720*480" },
	{ SDK_CAPTURE_SIZE_HD1, "352*480" },
	{ SDK_CAPTURE_SIZE_BCIF, "720*240" },
	{ SDK_CAPTURE_SIZE_CIF, "352*240" },
	{ SDK_CAPTURE_SIZE_QCIF, "176*120" },
	{ SDK_CAPTURE_SIZE_VGA, "640*480" },
	{ SDK_CAPTURE_SIZE_QVGA, "320*240" },
	{ SDK_CAPTURE_SIZE_SVCD, "480*480" },
	{ SDK_CAPTURE_SIZE_QQVGA, "160*128" },
	{ SDK_CAPTURE_SIZE_ND1, " 240*192" },
	{ SDK_CAPTURE_SIZE_650TVL, "926*576" },
	{ SDK_CAPTURE_SIZE_720P, "1280*720" },
	{ SDK_CAPTURE_SIZE_1_3M, "1280*960" },
	{ SDK_CAPTURE_SIZE_UXGA, "1600*1200" },
	{ SDK_CAPTURE_SIZE_1080P, "1920*1080" },
	{ SDK_CAPTURE_SIZE_WUXGA, "1920*1200" },
	{ SDK_CAPTURE_SIZE_2_5M, "1872*1408" },
	{ SDK_CAPTURE_SIZE_3M, "2048*1536" },
	{ SDK_CAPTURE_SIZE_5M, "3744*1408" },
	{ SDK_CAPTURE_SIZE_1080N, "960*1080" },
	{ SDK_CAPTURE_SIZE_4M, "2592*1520" },
	{ SDK_CAPTURE_SIZE_6M, "3072×2048" },
	{ SDK_CAPTURE_SIZE_8M, "3264×2448" },
	{ SDK_CAPTURE_SIZE_12M, "4000*3000" },
	{ SDK_CAPTURE_SIZE_4K, "4096 * 2160" },
	{ SDK_CAPTURE_SIZE_720N, "640*720" },
	{ SDK_CAPTURE_SIZE_WSVGA, "1024*576" },
	{ NULL, }
};

StreamSet::StreamSet(QWidget *parent)
	: QDialog(parent)
	, m_pstConfigNormal(NULL)
	, m_pstCfgEncodeAll(NULL)
	, m_pDevObj(NULL)
{												  
	m_pstCfgEncodeAll = new SDK_EncodeConfigAll_SIMPLIIFY;/// 全通道编码配置

	memset(m_pstCfgEncodeAll, 0, sizeof(SDK_EncodeConfigAll_SIMPLIIFY));

	ui.setupUi(this);
	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setStyleSheet(".StreamSet{border:2px solid black;}");

	
}

StreamSet::~StreamSet()
{
	if (m_pstCfgEncodeAll)
	{
		delete m_pstCfgEncodeAll;
		m_pstCfgEncodeAll = NULL;
	}
}

void StreamSet::InitResolution()
{
	ui.comboBox_ResoLution->clear();
	ui.comboBox_Expand_ResoLution->clear();
	if (m_pDevObj->m_pDevInfo->nSubDevType == SDK_DEV_TYPE_MJIPC)
	{
		ui.comboBox_ResoLution->addItem(s_PvideoResolutionMap[SDK_CAPTURE_SIZE_1080P].name);
		ui.comboBox_Expand_ResoLution->addItem(s_PvideoResolutionMap[SDK_CAPTURE_SIZE_1080P].name);
	}
	else
	{
		if (m_pstConfigNormal->iVideoFormat == 0)	//PAL
		{
			ui.comboBox_ResoLution->addItem(s_PvideoResolutionMap[SDK_CAPTURE_SIZE_1080P].name);
			ui.comboBox_ResoLution->addItem(s_PvideoResolutionMap[SDK_CAPTURE_SIZE_720P].name);

			ui.comboBox_Expand_ResoLution->addItem(s_PvideoResolutionMap[SDK_CAPTURE_SIZE_720P].name);
			ui.comboBox_Expand_ResoLution->addItem(s_PvideoResolutionMap[SDK_CAPTURE_SIZE_D1].name);
			ui.comboBox_Expand_ResoLution->addItem(s_PvideoResolutionMap[SDK_CAPTURE_SIZE_VGA].name);
			ui.comboBox_Expand_ResoLution->addItem(s_PvideoResolutionMap[SDK_CAPTURE_SIZE_QVGA].name);
		}
		else
		{
			ui.comboBox_ResoLution->addItem(s_NvideoResolutionMap[SDK_CAPTURE_SIZE_1080P].name);
			ui.comboBox_ResoLution->addItem(s_NvideoResolutionMap[SDK_CAPTURE_SIZE_720P].name);

			ui.comboBox_Expand_ResoLution->addItem(s_NvideoResolutionMap[SDK_CAPTURE_SIZE_720P].name);
			ui.comboBox_Expand_ResoLution->addItem(s_NvideoResolutionMap[SDK_CAPTURE_SIZE_D1].name);
			ui.comboBox_Expand_ResoLution->addItem(s_NvideoResolutionMap[SDK_CAPTURE_SIZE_VGA].name);
			ui.comboBox_Expand_ResoLution->addItem(s_NvideoResolutionMap[SDK_CAPTURE_SIZE_QVGA].name);
		}
	}
}

void StreamSet::on_btnClose_clicked()
{
	close();
}
void StreamSet::on_comboBox_ChanNo_activated(int index)
{
	if (CB_ERR == index)
	{
		return;
	}
	InitDlgInfo(index);
}

long StreamSet::GetChannelConfigInfo(long m_lChannel)
{
	memset(m_pstCfgEncodeAll, 0, sizeof(SDK_EncodeConfigAll_SIMPLIIFY));
	if (m_pDevObj->m_lUserLoginID > 0)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;
	
		if (m_pDevObj->m_pDevInfo->nType == SDK_DEV_TYPE_NVR)
		{
			bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, -1,
				(char *)m_pstCfgEncodeAll, sizeof(SDK_EncodeConfigAll_SIMPLIIFY), &dwRetLen, nWaitTime);
		}
		else
		{
			bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, m_lChannel,
				(char *)&m_pstCfgEncodeAll->vEncodeConfigAll[0], sizeof(SDK_CONFIG_ENCODE_SIMPLIIFY), &dwRetLen, nWaitTime);
		}
		if (!bSuccess)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("获取编码器参数失败"));
		}

		InitDlgInfo(0);
		InitDlgUI();
	}
	return 0;
}

void StreamSet::InitDlgUI()
{
	int i = 0;
	
	//编码模式
	QString strCodeMode[] = { QObject::tr("H.264"), QObject::tr("H.265"), QObject::tr("H.265+"), QObject::tr("MJPEG") };
	ui.comboBox_CodeFormat->clear();
	ui.comboBox_Expand->clear();
	for (i = 0; i < 4; i ++)
	{
		ui.comboBox_CodeFormat->insertItem(i, strCodeMode[i]);
		ui.comboBox_Expand->insertItem(i, strCodeMode[i]);		
	}
	
	//码流控制
	QString strTextBitControl[] = { QObject::tr("定码率"), QObject::tr("变码率") };
	ui.comboBox_BitControl->clear();
	ui.comboBox_Expand_BitControl->clear();
	for (i = 0; i < 2; i++)
	{
		ui.comboBox_BitControl->insertItem(i, strTextBitControl[i]);
		ui.comboBox_Expand_BitControl->insertItem(i, strTextBitControl[i]);		
	}

	//质量
	QString strQuality[] = {QObject::tr("最差"), QObject::tr("更差"),QObject::tr("差"), QObject::tr("好"),QObject::tr("更好"),QObject::tr("最好")};
	ui.comboBox_QuAlity->clear();
	ui.comboBox_Expand_QuaLity->clear();
	for (i = 0; i < 6; i++)
	{
		ui.comboBox_QuAlity->insertItem(i, strQuality[i]);
		ui.comboBox_Expand_QuaLity->insertItem(i, strQuality[i]);
	}

	ui.comboBox_CodeFormat->setCurrentIndex(0);
	ui.comboBox_BitControl->setCurrentIndex(0);
	ui.comboBox_QuAlity->setCurrentIndex(4);
	ui.comboBox_Expand->setCurrentIndex(0);
	ui.comboBox_Expand_BitControl->setCurrentIndex(0);
	ui.comboBox_Expand_QuaLity->setCurrentIndex(4);
}

void StreamSet::InitChannel()
{
	ui.comboBox_Channel->clear();
	for (int i = 0; i < m_pDevObj->m_stDevInfo.byChanNum; i++)
	{
		QString str;
		str = QString("%1").arg(i + 1);
		ui.comboBox_Channel->insertItem(i, str);
	}
	ui.comboBox_Channel->setCurrentIndex(0);
}

void StreamSet::InitDlgInfo(int lChannel)
{
	ui.comboBox_Channel->setCurrentIndex(lChannel);
	
	//主码流	
	ui.comboBox_CodeFormat->setCurrentIndex(SetCodeFormat(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iCompression));
	ui.comboBox_ResoLution->setCurrentIndex(SetResolutionIndex(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iResolution));
	ui.comboBox_BitControl->setCurrentIndex(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iBitRateControl);
	ui.comboBox_QuAlity->setCurrentIndex(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iQuality - 1);
	ui.lineEdit_FramRate->setText(QString::number(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.nBitRate));
	ui.lineEdit_FPS->setText(QString::number(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.nFPS));
	ui.lineEdit_GOP->setText(QString::number(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.nFPS * 
		m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iGOP));

	//副码流
	ui.comboBox_Expand->setCurrentIndex(SetCodeFormat(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iCompression));
	ui.comboBox_Expand_ResoLution->setCurrentIndex(SetExpandResolutionIndex1(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iResolution));
	ui.comboBox_Expand_BitControl->setCurrentIndex(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iBitRateControl);
	ui.comboBox_Expand_QuaLity->setCurrentIndex(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iQuality - 1);
	ui.lineEdit_Expand_FrameRate->setText(QString::number(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.nBitRate));
	ui.lineEdit_Expand_FPS->setText(QString::number(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.nFPS));
	ui.lineEdit_Expand_GOP->setText(QString::number(m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.nFPS *
		m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iGOP));

	if (m_pDevObj->m_pDevInfo->nSubDevType == SDK_DEV_TYPE_MJIPC)
	{
		ui.comboBox_ResoLution->setCurrentIndex(0);
		ui.comboBox_Expand_ResoLution->setCurrentIndex(0);
	}
}

void StreamSet::GetDlgInfo(int lChannel)
{
	//主码流	
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iCompression = GetCodeFormat(ui.comboBox_CodeFormat->currentIndex());
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iResolution = GetResolutionIndex(ui.comboBox_ResoLution->currentIndex());
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iBitRateControl = ui.comboBox_BitControl->currentIndex();
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iQuality = ui.comboBox_QuAlity->currentIndex() + 1;
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.nBitRate = ui.lineEdit_FramRate->text().toInt();
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.nFPS = ui.lineEdit_FPS->text().toInt();
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iGOP = ui.lineEdit_GOP->text().toUInt() / ui.lineEdit_FPS->text().toInt();

	
	//副码流
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iCompression = GetCodeFormat(ui.comboBox_Expand->currentIndex());
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iResolution = GetExpandResolutionIndex(ui.comboBox_Expand_ResoLution->currentIndex());
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iBitRateControl = ui.comboBox_Expand_BitControl->currentIndex();
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iQuality = ui.comboBox_Expand_QuaLity->currentIndex() + 1;
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.nBitRate = ui.lineEdit_Expand_FrameRate->text().toInt();
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.nFPS = ui.lineEdit_Expand_FPS->text().toInt();
	m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iGOP = ui.lineEdit_Expand_GOP->text().toUInt() / ui.lineEdit_Expand_FPS->text().toInt();

	if (m_pDevObj->m_pDevInfo->nSubDevType == SDK_DEV_TYPE_MJIPC)
	{
		m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstMainFmt.vfFormat.iResolution = GetResolutionIndex(ui.comboBox_ResoLution->currentIndex());
		m_pstCfgEncodeAll->vEncodeConfigAll[lChannel].dstExtraFmt.vfFormat.iResolution = GetResolutionIndex(ui.comboBox_ResoLution->currentIndex());	
	}
}

long StreamSet::SetCodeFormat(long lCompression)
{
	long lIndex = 0;
	switch (lCompression)
	{
	case SDK_CAPTURE_COMP_H264:
		lIndex = 0;
		break;
	case SDK_CAPTURE_COMP_H265:
		lIndex = 1;		
		break;
	case SDK_CAPTURE_COMPRESS_H265_S:
		lIndex = 2;
		break;
	case SDK_CAPTURE_COMP_MJPG:
		lIndex = 3;
		break;
	}
	return lIndex;
}

long StreamSet::GetCodeFormat(long lIndex)
{
	long lCompression = SDK_CAPTURE_COMP_H264;
	switch (lIndex)
	{
	case 0:
		lCompression = SDK_CAPTURE_COMP_H264;
		break;
	case 1:
		lCompression = SDK_CAPTURE_COMP_H265;
		break;
	case 2:
		lCompression = SDK_CAPTURE_COMPRESS_H265_S;
		break;
	case 3:
		lCompression = SDK_CAPTURE_COMP_MJPG;
		break;
	}
	return lCompression;
}

long StreamSet::SetResolutionIndex(long lResolution)	//获取分辨率
{
	long lIndex = 0;
	switch (lResolution)
	{
	case SDK_CAPTURE_SIZE_1080P:
		lIndex = 0;
		break;
	case SDK_CAPTURE_SIZE_720P:
		lIndex = 1;
		break;
	}
	return lIndex;
}
long StreamSet::GetResolutionIndex(long lIndex)
{
	long lResolution = SDK_CAPTURE_SIZE_1080P;
	switch (lIndex)
	{
	case 0:
		lResolution = SDK_CAPTURE_SIZE_1080P;
		break;
	case 1:
		lResolution = SDK_CAPTURE_SIZE_720P;
		break;
	}
	return lResolution;
}

long StreamSet::SetExpandResolutionIndex1(long lResolution)
{
	long lIndex = 0;
	switch (lResolution)
	{
	case SDK_CAPTURE_SIZE_720P:
		lIndex = 0;
		break;
	case SDK_CAPTURE_SIZE_D1:
		lIndex = 1;
		break;
	case SDK_CAPTURE_SIZE_VGA:
		lIndex = 2;
		break;
	case SDK_CAPTURE_SIZE_QVGA:
		lIndex = 3;
		break;
	}
	return lIndex;
}

long StreamSet::GetExpandResolutionIndex(long lIndex)
{
	long lResolution = SDK_CAPTURE_SIZE_720P;
	switch (lIndex)
	{
	case 0:
		lResolution = SDK_CAPTURE_SIZE_720P;
		break;
	case 1:
		lResolution = SDK_CAPTURE_SIZE_D1;
		break;
	case 2:
		lResolution = SDK_CAPTURE_SIZE_VGA;
		break;
	case 3:
		lResolution = SDK_CAPTURE_SIZE_QVGA;
		break;
	}
	return lResolution;
}

void StreamSet::on_comboBox_CodeFormat_activated(int index)
{
	ui.comboBox_QuAlity->setEnabled(true);
	if (index == 3)  //MJPEG
	{
		ui.comboBox_QuAlity->setEnabled(false);
	}
}

void StreamSet::on_comboBox_Expand_activated(int index)
{
	ui.comboBox_Expand_QuaLity->setEnabled(true);
	if (index == 3)  //MJPEG
	{
		ui.comboBox_Expand_QuaLity->setEnabled(false);
	}
}

void StreamSet::on_btnSave_clicked()
{
	BOOL bSuccess = FALSE;
	int nWaitTime = 5000;
	int nChannel = ui.comboBox_Channel->currentIndex();
	if (CB_ERR == nChannel)
	{
		nChannel = 0;
	}
	GetDlgInfo(nChannel);

	if (m_pDevObj->m_pDevInfo->nType == SDK_DEV_TYPE_NVR)
	{
		bSuccess = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, -1,
			(char *)m_pstCfgEncodeAll, sizeof(SDK_EncodeConfigAll_SIMPLIIFY), nWaitTime);
	}
	else
	{
		bSuccess = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, 0,
			(char *)&m_pstCfgEncodeAll->vEncodeConfigAll[0], sizeof(SDK_CONFIG_ENCODE_SIMPLIIFY), nWaitTime);
	}
	if (!bSuccess)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("设置编码器参数失败"));
	}
}

void StreamSet::on_btnUpGrade_clicked()
{
	GetChannelConfigInfo(0);
}
