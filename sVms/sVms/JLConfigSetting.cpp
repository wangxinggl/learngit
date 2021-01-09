#include "JLConfigSetting.h"
#include "myhelper.h"
#include <stdio.h>
#include "Upgrade.h"
#include <QDebug>


#define BITMSK(bit)				(int)(1 << (bit))
#define  IFRAME_EQ_PFRAME 10

QString Control[STREAM_NUM][CONTROL_NUM] = {
	{"comboBox_M_Resolution","comboBox_M_Frame","comboBox_M_BitControl","comboBox_M_Image",
	"comboBox_M_Stream","comboBox_M_Interal","checkBox_M_Video","checkBox_M_Audio","comboBox__M_EnMode"},
	{ "comboBox_F_Resolution", "comboBox_F_Frame", "comboBox_F_BitControl", "comboBox_F_Image",
	"comboBox_F_Stream", "comboBox_F_Interal", "checkBox_F_Video", "checkBox_F_Audio", "comboBox__F_EnMode" },
	{ "comboBox_F_Resolution", "comboBox_F_Frame", "comboBox_F_BitControl", "comboBox_F_Image",
	"comboBox_F_Stream", "comboBox_F_Interal", "checkBox_F_Video", "checkBox_F_Audio", "comboBox__F_EnMode" }
};
JLConfigSetting::JLConfigSetting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	initreeWidget();
	initConfigChannel();
	InitResData();
	initShieldDetDlg();


	pChannelTmp = NULL;
	m_LoginID = 0;
	m_nChannelNum = 0;
	m_streamChannelNum = 0;
	m_nAlarmInNum = 0;
	m_nAlarmOutNum = 0;
	m_nbyChanNum = 0;
	m_niDigChannel = 0;
	m_lDevType = 0;
	m_nVideoStandard = 0;
	m_bInitChannelComboxed = FALSE;
	m_nLastChannelNum = 0; 

	
	connect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setGroupHidden(int)));
	connect(ui.comboBox_ChanNo, SIGNAL(activated(const QString &)), this, SLOT(OnSelchangeComboChanno(const QString &)));
	//initRegionl();
}

void JLConfigSetting::initConfigChannel()
{
	m_nAudioInNum = 0;
	m_bCombineSet = false;
	m_mapCaptureComp[SDK_CAPTURE_COMP_DIVX_MPEG4] = "DIVX MPEG4";
	m_mapCaptureComp[SDK_CAPTURE_COMP_MS_MPEG4] = "MS MPEG4";
	m_mapCaptureComp[SDK_CAPTURE_COMP_MPEG2] = "MPEG2";
	m_mapCaptureComp[SDK_CAPTURE_COMP_MPEG1] = "MPEG1";
	m_mapCaptureComp[SDK_CAPTURE_COMP_H263] = "H.263";
	m_mapCaptureComp[SDK_CAPTURE_COMP_MJPG] = "MJPG";
	m_mapCaptureComp[SDK_CAPTURE_COMP_FCC_MPEG4] = "FCC MPEG4";
	m_mapCaptureComp[SDK_CAPTURE_COMP_H264] = "H.264";
	m_mapCaptureComp[SDK_CAPTURE_COMP_H265] = "H.265";
	m_mapCaptureComp[SDK_CAPTURE_COMPRESS_H265_S] = "H.265+";

}
JLConfigSetting::~JLConfigSetting()
{
	if (m_pFaShielded)
	{
		delete m_pFaShielded;
		m_pFaShielded = NULL;
	}
}

void JLConfigSetting::initShieldDetDlg()
{
	m_lSelChannel = 0;
	m_lStreamType = 0;
	m_lVideoWidth = 704;
	m_lVideoHeight = 576;
	m_bStartCheck = FALSE;
	m_nDrawType = DRAW_PEN_Rectangle;
	m_bStartAreaSet = FALSE;
	m_pFaShielded = NULL;
	m_pFaShielded = new SDK_FA_VI_SHIELDED;
	memset(m_pFaShielded, 0, sizeof(SDK_FA_VI_SHIELDED));

	if (NULL == m_pAnalyseVideoAreaDlg)
	{
		m_pAnalyseVideoAreaDlg = new AnalyseVideoAreaDlg(this);
		m_pAnalyseVideoAreaDlg->setFixedSize(m_lVideoWidth, m_lVideoHeight);
		m_pAnalyseVideoAreaDlg->move(0, 0);
	}

	/*for (int ix = 0; ix < g_pMaindlg->m_nChannelNum; ix++)
	{
		QString str;
		str.Format(_T("%d"), ix + 1);
		m_comChannel.InsertString(ix, str);
		m_comChannel.SetItemData(ix, ix);
	}*/
	ui.comboBox_Regionl->setCurrentIndex(0);



	//EnableWindowAnalyse(m_bStartCheck);
}
/*
long JLConfigSetting::EnableWindowAnalyse(BOOL bEnable)
{
	ui.btnRegionlAll->setEnabled(bEnable);
	ui.btnRegionlClear->setEnabled(bEnable);
	return 0;
}
*/
void JLConfigSetting::OnSelchangeComboChanno(const QString & nIndex)
{
	int nChannelNum = nIndex.toInt();
	if (CB_ERR == nIndex)
	{
		return;
	}

	/////////
	m_lSelChannelNum = nChannelNum;

	//
	long lRet = OnRefresh(); // by zjh 20170814
	if (-1 == lRet)
	{
		//CleanAll();
		return;
	}


	if (nIndex == m_DevAttribute.deviveInfo.byChanNum)
	{
		memcpy(&m_allData, &m_EncodeConfig.vEncodeConfigAll[0], sizeof(SDK_CONFIG_ENCODE));

		AllStructToWinData(0, &m_allData, MAIN_STREAM);
		AllStructToWinData(0, &m_allData, EXPAND_STREAM);
		m_nLastChannelNum = nChannelNum;
	}
	else if (m_nLastChannelNum == m_DevAttribute.deviveInfo.byChanNum)
	{
		AllWinDataToStruct(0);
		NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
		NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
		m_nLastChannelNum = nChannelNum;
	}
	else
	{
		
	}

	if (m_nAudioInNum != m_DevAttribute.deviveInfo.byChanNum)
	{
		ui.checkBox_M_Audio->setEnabled(nIndex < m_nAudioInNum);
		if (m_bMultiStream)
		{
			ui.checkBox_F_Audio->setEnabled(nIndex < m_nAudioInNum);
		
		}
	}
	if (m_bCombineEncode)
	{
		ui.checkBox_F_Audio->setEnabled(false);
	}

}

bool JLConfigSetting::AllWinDataToStruct(int nChannelNum)
{
	WinDataToStruct(m_allData.dstMainFmt, MAIN_STREAM);
	WinDataToStruct(m_allData.dstExtraFmt, EXPAND_STREAM);
	return true;
}

bool JLConfigSetting::WinDataToStruct(SDK_MEDIA_FORMAT &dstFmt, int nEncodeType)
{
	if (nEncodeType >= STREAM_NUM)
	{
		return false;
	}
	SDK_VIDEO_FORMAT &vfFormat = dstFmt.vfFormat;

	vfFormat.iResolution = GetComboBoxData(Control[nEncodeType][CONTROL_RESOLUTION]);
	vfFormat.nFPS = GetComboBoxData(Control[nEncodeType][CONTROL_FRAME]);
	vfFormat.iBitRateControl = GetComboBoxData(Control[nEncodeType][CONTROL_BITCONTROL]);
	vfFormat.iQuality = GetComboBoxData(Control[nEncodeType][CONTROL_QUALITY]);

	vfFormat.nBitRate = GetComboBoxData(Control[nEncodeType][CONTROL_BIT_RATE]);
	vfFormat.iGOP = GetComboBoxData(Control[nEncodeType][CONTROL_GOP]);
	vfFormat.iCompression = GetComboBoxData(Control[nEncodeType][CONTROL_FORMAT]);



	dstFmt.bVideoEnable = ui.tabWidget->findChild<QCheckBox *>(Control[nEncodeType][CONTROL_VIDEO])->checkState();
	dstFmt.bAudioEnable = ui.tabWidget->findChild<QCheckBox *>(Control[nEncodeType][CONTROL_AUDIO])->checkState();


	if (nEncodeType == COMBINE_STREAM)
	{
		dstFmt.bAudioEnable = false;
		//m_CmbEncodeMode.vEncodeParam[0].iEncodeMode = GetComboBoxData(IDC_COMBO_COMBINEMODE);
	}

	return true;
}

DWORD JLConfigSetting::GetComboBoxData(QString m_comboxID, int nIndex)
{
	DWORD dwData = 0;
	QComboBox *pComboBox = ui.tabWidget->findChild<QComboBox *>(m_comboxID);
	if (pComboBox)
	{
		if (-1 == nIndex)
		{
			nIndex = pComboBox->currentIndex();
		}

		if (-1 != nIndex)
		{
			dwData = pComboBox->currentIndex();
		}
	}

	return dwData;
}

bool JLConfigSetting::AllStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType)
{
	if (nEncodeType == MAIN_STREAM || (nEncodeType == EXPAND_STREAM && m_bMultiStream))
	{
		DWORD lFreePower = m_pEncodeAbility.iMaxEncodePower;
		int nChannelCount = m_DevAttribute.deviveInfo.byChanNum;
		if (nChannelCount <= 0)
		{
			return FALSE;
		}
		DWORD dwPower = lFreePower / nChannelCount;
		DWORD dwMask = m_pEncodeAbility.vEncodeInfo[0].uiResolution;
		DWORD dwBitrate = -1;

		if (nEncodeType == MAIN_STREAM)
		{
			DWORD dwTmpPower = 0xFFFFFFFF;
			DWORD uiResolution = 0xFFFFFFFF;
			int i = 0;

			for (i = 0; i < nChannelCount; i++)
			{
				if (m_pEncodeAbility.ImageSizePerChannel[i] && m_pEncodeAbility.nMaxPowerPerChannel[i])
				{
					dwTmpPower =
						(dwTmpPower < m_pEncodeAbility.nMaxPowerPerChannel[i]) ? dwTmpPower : m_pEncodeAbility.nMaxPowerPerChannel[i];
					uiResolution &= m_pEncodeAbility.ImageSizePerChannel[i];
				}
			}

			for (i = 0; i < SDK_CAPTURE_SIZE_NR; i++)
			{
				if ((1 << i) & uiResolution)
				{
					break;
				}
			}

			if (m_pEncodeAbility.ImageSizePerChannel[nChannelNum])
			{
				dwMask = m_pEncodeAbility.ImageSizePerChannel[nChannelNum] & uiResolution;
			}
			else
			{
				dwMask = m_pEncodeAbility.vEncodeInfo[0].uiResolution;
			}

			dwPower = (dwPower < dwTmpPower) ? dwPower : dwTmpPower;

			pConfigEncode->dstMainFmt.vfFormat.iResolution =
				(i > pConfigEncode->dstMainFmt.vfFormat.iResolution) ? i : pConfigEncode->dstMainFmt.vfFormat.iResolution;


			dwBitrate = m_pEncodeAbility.iMaxBps / nChannelCount;
		}
		else if (nEncodeType == EXPAND_STREAM)
		{
			DWORD uiResolution = 0xFFFFFFFF;
			int i = 0;

			for (i = 0; i < nChannelCount; i++)
			{
				if (m_pEncodeAbility.ExImageSizePerChannel[i])
				{
					uiResolution &= m_pEncodeAbility.ExImageSizePerChannel[i];
				}
			}

			for (i = 0; i < SDK_CAPTURE_SIZE_NR; i++)
			{
				if ((1 << i) & uiResolution)
				{
					break;
				}
			}

			if (m_pEncodeAbility.ExImageSizePerChannel[nChannelNum])
			{
				dwMask = m_pEncodeAbility.ExImageSizePerChannel[nChannelNum] & uiResolution;
			}
			else
			{
				dwMask = m_pEncodeAbility.vEncodeInfo[0].uiResolution;
			}

			pConfigEncode->dstExtraFmt.vfFormat.iResolution =
				(i > pConfigEncode->dstExtraFmt.vfFormat.iResolution) ? i : pConfigEncode->dstExtraFmt.vfFormat.iResolution;
		}
		return StructToWinData(nChannelNum, pConfigEncode, nEncodeType, dwPower, dwMask, dwBitrate);
	}
	return false;
}


void JLConfigSetting::CleanAll()
{
	for (int i = 0; i < STREAM_NUM; i++)
	{
		QComboBox *pComboBox = ui.tabWidget->findChild<QComboBox *>(Control[i][CONTROL_RESOLUTION]);
		if (pComboBox != NULL)
		{
			pComboBox->clear();
			pComboBox = NULL;
		}
		pComboBox = ui.tabWidget->findChild<QComboBox *>(Control[i][CONTROL_FRAME]);
		if (pComboBox != NULL)
		{
			pComboBox->clear();
			pComboBox = NULL;
		}
		pComboBox = ui.tabWidget->findChild<QComboBox *>(Control[i][CONTROL_BITCONTROL]);
		if (pComboBox != NULL)
		{
			pComboBox->clear();
			pComboBox = NULL;
		}
		pComboBox = ui.tabWidget->findChild<QComboBox *>(Control[i][CONTROL_QUALITY]);
		if (pComboBox != NULL)
		{
			pComboBox->clear();
			pComboBox = NULL;
		}
		pComboBox = ui.tabWidget->findChild<QComboBox *>(Control[i][CONTROL_BIT_RATE]);
		if (pComboBox != NULL)
		{
			pComboBox->clear();
			pComboBox = NULL;
		}
		pComboBox = ui.tabWidget->findChild<QComboBox *>(Control[i][CONTROL_GOP]);
		if (pComboBox != NULL)
		{
			pComboBox->clear();
			pComboBox = NULL;
		}
		QCheckBox * pButton = ui.tabWidget->findChild<QCheckBox *>(Control[i][CONTROL_VIDEO]);
		if (pButton != NULL)
		{
			pButton->setCheckable(FALSE);
			pButton = NULL;
		}
		pButton = ui.tabWidget->findChild<QCheckBox *>(Control[i][CONTROL_AUDIO]);
		if (pButton != NULL)
		{
			pButton->setCheckable(FALSE);
			pButton = NULL;
		}
	}
	//by zjh 20170812
	//	m_ChanNo.ResetContent();
	
}

long JLConfigSetting::OnRefresh()
{
	long lRet = GetChannelConfigInfoEX(m_lSelChannelNum);
	return lRet;
}
long  JLConfigSetting::GetChannelConfigInfoEX(long lChannel)
{
	long lRet = -1;
	if (0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NORMAL NormalConfig = { 0 };
		SDK_EncodeStaticParam EncodeStatic = { 0 };
		//编码
		BOOL nStaticCparam = false;
		BOOL  bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_ENCODE_STATICPARAM, lChannel,
			(char *)&EncodeStatic, sizeof(SDK_EncodeStaticParam), &dwRetLen, nWaitTime);

		if ((bSuccess == 1) && sizeof(SDK_EncodeStaticParam) == dwRetLen)
		{
			nStaticCparam = true;
		}

		bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSNORMAL, 0,
			(char *)&NormalConfig, sizeof(SDK_CONFIG_NORMAL), &dwRetLen, nWaitTime);
		if (bSuccess && dwRetLen == sizeof(SDK_CONFIG_NORMAL))
		{
			SDK_SystemFunction SysFunc;
			bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_ABILITY_SYSFUNC, -1,
				(char *)&SysFunc, sizeof(SDK_SystemFunction), &dwRetLen, nWaitTime);
			if (bSuccess && dwRetLen == sizeof(SDK_SystemFunction))
			{
				SDK_CONFIG_ENCODE_SIMPLIIFY  CfgEncode = { 0 };     // SDK_CONFIG_ENCODE_SIMPLIIFY
				bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, lChannel,
					(char *)&CfgEncode, sizeof(SDK_CONFIG_ENCODE_SIMPLIIFY), &dwRetLen, nWaitTime);
				if (bSuccess && dwRetLen == sizeof(SDK_CONFIG_ENCODE_SIMPLIIFY))
				{
					CONFIG_EncodeAbility EncodeAbility = { 0 };
					long lSize = sizeof(CONFIG_EncodeAbility);
					bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_ABILTY_ENCODE, lChannel/*lChannel*//*-1*/,
						(char *)&EncodeAbility, sizeof(CONFIG_EncodeAbility), &dwRetLen, nWaitTime);
					if (bSuccess && dwRetLen == sizeof(CONFIG_EncodeAbility))
					{
						if (nStaticCparam)
						{
							InitDlgInfoEx(lChannel, m_nChannelNum, &CfgEncode, &NormalConfig, &EncodeAbility, &SysFunc, &m_DevAttribute, &EncodeStatic);
							lRet = 0;
						}
						else
						{
							InitDlgInfoEx(lChannel, m_nChannelNum, &CfgEncode, &NormalConfig, &EncodeAbility, &SysFunc, &m_DevAttribute, NULL);
							lRet = 0;
						}

					}
				}
			}
		}
	}
	return lRet;
}

void JLConfigSetting::InitDlgInfoEx(long lChannel, int ChannnelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pEncodeSimpl,
	SDK_CONFIG_NORMAL *pNormalCfg, CONFIG_EncodeAbility *pEncodeAbility, SDK_SystemFunction *pSysFunc,
	DEV_ATTRIBUTE *pDevAttribute, SDK_EncodeStaticParam *pEncodeStatic)
{
	m_nVideoStandard = pNormalCfg->iVideoFormat;
	m_nChannelNum = ChannnelNum;
	InitCombo();
	ui.comboBox_ChanNo->setCurrentIndex(lChannel);
	memcpy(&m_EncodeConfig.vEncodeConfigAll[lChannel], pEncodeSimpl, sizeof(SDK_CONFIG_ENCODE_SIMPLIIFY));
	if (pEncodeAbility->iMaxBps == 0)
	{
		m_pEncodeAbility.iMaxBps = 24 * 1024;
	}
	memcpy(&m_pEncodeAbility, pEncodeAbility, sizeof(CONFIG_EncodeAbility));
	memcpy(&m_DevAttribute, pDevAttribute, sizeof(DEV_ATTRIBUTE));
	strcpy(m_cVersion, pDevAttribute->deviveInfo.sSoftWareVersion);
	m_nAudioInNum = pDevAttribute->deviveInfo.iAudioInChannel;
	InitResData();
	memcpy(&m_SysFunc, pSysFunc, sizeof(SDK_SystemFunction));
	m_bMultiStream = pSysFunc->vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_DOUBLE_STREAM];
	if (m_bMultiStream)
	{
		ui.checkBox_F_Video->setEnabled(true);
		ui.checkBox_F_Audio->setEnabled(true);
	}
	else
	{
		ui.checkBox_F_Video->setEnabled(false);
		ui.checkBox_F_Audio->setEnabled(false);
	}

	if (strcmp(m_cVersion, "V1.22.R03") >= 0 && pSysFunc->vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_COMBINE_STREAM])
	{
		ui.comboBox__F_EnMode->setEnabled(false);
		m_bCombineEncode = true;
		if (strcmp(m_cVersion, "V1.24.R03") >= 0)
		{
			m_bCombineSet = true;
			ui.comboBox_F_Resolution->setEnabled(true);
			ui.comboBox_F_Frame->setEnabled(true);
			ui.comboBox_F_BitControl->setEnabled(true);
			ui.comboBox_F_Image->setEnabled(true);
			ui.comboBox_F_Stream->setEnabled(true);
#ifndef OEM_RAYSHARP
			ui.comboBox_F_Interal->setEnabled(true);
#endif

		}
		else
		{
			m_bCombineSet = false;
			ui.comboBox_F_Resolution->setEnabled(false);
			ui.comboBox_F_Frame->setEnabled(false);
			ui.comboBox_F_BitControl->setEnabled(false);
			ui.comboBox_F_Image->setEnabled(false);
			ui.comboBox_F_Stream->setEnabled(false);
			ui.comboBox_F_Interal->setEnabled(false);

		}
	}
	else
	{

		ui.comboBox__F_EnMode->setEnabled(true);
		ui.comboBox_F_Resolution->setEnabled(true);
		ui.comboBox_F_Frame->setEnabled(true);
		ui.comboBox_F_BitControl->setEnabled(true);
		ui.comboBox_F_Image->setEnabled(true);
		ui.comboBox_F_Stream->setEnabled(true);
#ifndef OEM_RAYSHARP
		ui.comboBox_F_Interal->setEnabled(true);
#endif
		m_bCombineEncode = false;
		m_bCombineSet = false;
	}
	//静态编码
	if (pEncodeStatic)
	{
		ui.comboBox_M__Set->clear();
		ui.comboBox_M__Set->setEnabled(true);

		ui.comboBox_M__Set->insertItem(1, "baseline");
		ui.comboBox_M__Set->insertItem(1, "main profile");
		ui.comboBox_M__Set->insertItem(1, "high profile");

		ui.comboBox_M__Set->setCurrentIndex(pEncodeStatic->profile - 1);
	}
	ui.checkBox_F_Video->setEnabled(false);
	StructToWin();

}


void JLConfigSetting::setGroupHidden(int index)
{
	if (index == 0)
	{
		qDebug() << "0";
	}
	else if (index == 1)
	{
		qDebug() << "1";
	}
	else if (index == 2)
	{
		qDebug() << "2";
	}
}
void JLConfigSetting::initreeWidget()
{
	ui.treeWidget->clear();

	treeSetting = new DevTreePro();

	treeSetting->init();
	treeSetting->ShowTreebyType1(ui.treeWidget);
	connect(ui.treeWidget, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(OnlineTreeViewDoubleClick(const QModelIndex)));
}

void JLConfigSetting::OnlineTreeViewDoubleClick(const QModelIndex & index)
{
	QString str;
	str += QString("%1").arg(index.data().toString());
	int itemtemp = str.right(1).toInt() - 1;
	QString par = QObject::tr("%1").arg(index.parent().data().toString());

	QVariant var = ui.treeWidget->currentItem()->data(itemtemp, Qt::UserRole);
	pChannelTmp = (TreeData_t *)var.value<void *>();


	if (str == NULL || par == QObject::tr("解码设备"))
	{
		return;
	}

	if ((!pChannelTmp) || (pChannelTmp->Channel == 0))
		return;
	LOGIN_TIMER = startTimer(200);
	
	
}

void JLConfigSetting::GetDeviceConfigInfo()
{
	if (0 != m_LoginID)
	{

		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NORMAL NormalConfig = { 0 };
		SDK_MultiLangFunction m_langfunc = { 0 };
		BOOL bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSNORMAL, 0,
			(char *)&NormalConfig, sizeof(SDK_CONFIG_NORMAL), &dwRetLen, nWaitTime);
		if (bSuccess && dwRetLen == sizeof(SDK_CONFIG_NORMAL))
		{
		
			bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_ABILITY_LANG, 0, (char *)&m_langfunc,
				sizeof(SDK_MultiLangFunction), &dwRetLen, nWaitTime);
			if (bSuccess &&dwRetLen == sizeof(SDK_MultiLangFunction))
			{
				m_DevAttribute.NormalConfig = NormalConfig;
				InitDlgInfo(&m_DevAttribute, &m_langfunc);
			}

		}
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("登录失败"));
	}
}

void JLConfigSetting::InitDlgInfo(DEV_ATTRIBUTE *pDevAttribute, SDK_MultiLangFunction *PLang)
{
	if (pDevAttribute != NULL &&PLang != NULL)
	{
		
	
		QString str;

		str = (LPCSTR)(LPSTR)pDevAttribute->deviveInfo.sSerialNumber;
		ui.label_Num->setText(str);

		str = (LPCSTR)(LPSTR)pDevAttribute->deviveInfo.sSoftWareVersion;
		ui.label_Version->setText(str);

		str = pChannelTmp->DevInfo->GetDevInfo()->szIpAddr;
		ui.label_IP->setText(str);

		str = QString::number(pDevAttribute->NormalConfig.iLocalNo);

		ui.label_Type->setText(str);

	}
}

void JLConfigSetting::on_btnWeb_clicked()
{
	if (pChannelTmp == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择设备"));
		return;
	}
	char szSnapPath[125];
	 sprintf(szSnapPath, "%s//%s/%s", "http:", pChannelTmp->DevInfo->GetDevInfo()->szIpAddr, "login.asp");
	QDesktopServices::openUrl(QUrl(QLatin1String(szSnapPath)));
}

void JLConfigSetting::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == LOGIN_TIMER)
	{
		killTimer(LOGIN_TIMER);
		OnBtnLogin();
	}
	
}

void JLConfigSetting::OnBtnLogin()
{
	if (pChannelTmp == NULL)
		return;
	int nError = 0;
	VIDEONET_DEVICEINFO deviceInfo;

	VideoNet_SetConnectTime(3000, 1);//设置尝试连接1次，等待时间3s
	if (IsIPAvailed(pChannelTmp->DevInfo->GetDevInfo()->szIpAddr))
	{
		m_LoginID = VideoNet_Login(pChannelTmp->DevInfo->GetDevInfo()->szIpAddr, pChannelTmp->DevInfo->GetDevInfo()->nPort, pChannelTmp->DevInfo->GetDevInfo()->szLoginName, pChannelTmp->DevInfo->GetDevInfo()->szPassword, &deviceInfo, &nError);
	}
	else
	{
		m_LoginID = VideoNet_Login_P2P(pChannelTmp->DevInfo->GetDevInfo()->szIpAddr, 0, pChannelTmp->DevInfo->GetDevInfo()->szLoginName, pChannelTmp->DevInfo->GetDevInfo()->szPassword, &deviceInfo, &nError);
	}


	if (m_LoginID > 0)
	{
		if (deviceInfo.iDigChannel > 0)
		{
			deviceInfo.byChanNum = deviceInfo.iDigChannel;
			m_nChannelNum = deviceInfo.iDigChannel;
		}
		else
		{
			m_nChannelNum = deviceInfo.byChanNum + deviceInfo.iDigChannel;
		}

		memcpy(&m_DevAttribute.deviveInfo, &deviceInfo, sizeof(deviceInfo));
		m_nAlarmInNum = deviceInfo.byAlarmInPortNum;
		m_nAlarmOutNum = deviceInfo.byAlarmOutPortNum;

		m_nbyChanNum = deviceInfo.byChanNum;
		m_niDigChannel = deviceInfo.iDigChannel;
		m_lDevType = deviceInfo.deviceTye; //SDK_DeviceType
		
		GetDeviceConfigInfo();
		GetChannelConfigInfo();
	}
	else
	{
		m_LoginID = 0;
		//Display log in failure reason 
		ShowLoginErrorReason(nError);
	}
}

BOOL JLConfigSetting::IsIPAvailed(const char* pszIPAddr)
{
	if (!pszIPAddr)
	{
		return FALSE;
	}

	int nIP[4] = { 0 };
	if (sscanf(pszIPAddr, "%d.%d.%d.%d", &nIP[0], &nIP[1], &nIP[2], &nIP[3]) == 4)
	{
		if (nIP[0] >= 0 && nIP[0] <= 255
			&& nIP[1] >= 0 && nIP[1] <= 255
			&& nIP[2] >= 0 && nIP[2] <= 255
			&& nIP[3] >= 0 && nIP[3] <= 255)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void JLConfigSetting::ShowLoginErrorReason(int nError)
{
	int nErr = VideoNet_GetLastError();
	if (nErr == VIDEONET_PASSWORD_NOT_VALID)
	{
		myHelper::ShowMessageBoxError(QObject::tr("密码错误"));
	}
	else
	{
		myHelper::ShowMessageBoxError(QObject::tr("未知错误"));

	}
}

void JLConfigSetting::on_btnUpGrade_clicked()
{
	BOOL bSuccess = FALSE;
	if (pChannelTmp == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择设备"));
		return;
	}
	
	Upgrade *m_upgrade = new Upgrade;
	
	if (m_LoginID > 0)
	{
		VIDEONET_DEVICEINFO *pSysInfo = new VIDEONET_DEVICEINFO;
		if (0 != m_LoginID)
		{
			int nWaitTime = 1000;
			DWORD dwRetlen = 0;
			bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSINFO, -1, (char*)pSysInfo, sizeof(VIDEONET_DEVICEINFO), &dwRetlen, nWaitTime);
			if (bSuccess && dwRetlen == sizeof(VIDEONET_DEVICEINFO))
			{
				m_upgrade->initUPgradeInfo(pSysInfo, m_LoginID);
				delete pSysInfo;
			}
		}
	}
	m_upgrade->show();
}

void JLConfigSetting::GetChannelConfigInfo()
{
	if (0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NORMAL NormalConfig = { 0 };
		SDK_EncodeStaticParamAll EncodeStatic = { 0 };
		//编码
		BOOL nStaticCparam = false;
		BOOL  bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_ENCODE_STATICPARAM, -1,
			(char *)&EncodeStatic, sizeof(SDK_EncodeStaticParamAll), &dwRetLen, nWaitTime);

		if (bSuccess && sizeof(SDK_EncodeStaticParamAll) == dwRetLen)
		{
			nStaticCparam = true;
		}

		bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSNORMAL, 0,
			(char *)&NormalConfig, sizeof(SDK_CONFIG_NORMAL), &dwRetLen, nWaitTime);
		if (bSuccess && dwRetLen == sizeof(SDK_CONFIG_NORMAL))
		{
			SDK_SystemFunction SysFunc;
			bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_ABILITY_SYSFUNC, -1,
				(char *)&SysFunc, sizeof(SDK_SystemFunction), &dwRetLen, nWaitTime);
			if (bSuccess && dwRetLen == sizeof(SDK_SystemFunction))
			{
				SDK_EncodeConfigAll_SIMPLIIFY  CfgEncode = { 0 };     // SDK_CONFIG_ENCODE_SIMPLIIFY
				bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, -1,
					(char *)&CfgEncode, sizeof(SDK_EncodeConfigAll_SIMPLIIFY), &dwRetLen, nWaitTime);
				if (bSuccess && dwRetLen == sizeof(SDK_EncodeConfigAll_SIMPLIIFY))
				{
					CONFIG_EncodeAbility EncodeAbility = { 0 };
					long lSize = sizeof(CONFIG_EncodeAbility);
					bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_ABILTY_ENCODE, -1,
						(char *)&EncodeAbility, sizeof(CONFIG_EncodeAbility), &dwRetLen, nWaitTime);
					if (bSuccess && dwRetLen == sizeof(CONFIG_EncodeAbility))
					{
						SDK_CombineEncodeConfigAll CombineEncodeCfg;
						bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_COMBINEENCODE, -1,
							(char*)&CombineEncodeCfg, sizeof(SDK_CombineEncodeConfigAll), &dwRetLen, nWaitTime);
						if (bSuccess && dwRetLen == sizeof(SDK_CombineEncodeConfigAll))
						{
							SDK_CombEncodeModeAll CmbEncodeMode;
							bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CONFIG_COMBINEENCODEMODE, -1,
								(char *)&CmbEncodeMode, sizeof(SDK_CombEncodeModeAll), &dwRetLen, nWaitTime);
							if (bSuccess && dwRetLen == sizeof(SDK_CombEncodeModeAll))
							{
								if (nStaticCparam)
								{
									InitStramInfo(m_nChannelNum, &CfgEncode, &NormalConfig, &EncodeAbility, &CombineEncodeCfg, &SysFunc, &m_DevAttribute, &CmbEncodeMode, &EncodeStatic);
								}
								else
								{
									InitStramInfo(m_nChannelNum, &CfgEncode, &NormalConfig, &EncodeAbility, &CombineEncodeCfg, &SysFunc, &m_DevAttribute, &CmbEncodeMode, NULL);
								}

							}
						}
					}
				}
			}
		}
	}
}

void JLConfigSetting::InitCombo()
{
	int nIndex = 0;
	int i = 0;
	if (!m_bInitChannelComboxed) // by zjh 20170812
	{
		m_bInitChannelComboxed = TRUE;
		ui.comboBox_ChanNo->clear();
		
		for (; i < m_nChannelNum; i++)
		{
			QString str;
			str = QString("%1").arg(i + 1);
			ui.comboBox_ChanNo->addItem(str);
		}

		if (m_nChannelNum > 0)
		{
			ui.comboBox_ChanNo->setCurrentIndex(0);
			m_nLastChannelNum = 0;
		}
		else
		{
			return;
		}
	}

	QString strTextBitControl[] = { QObject::tr("限定码率"), QObject::tr("可变码率")};
	ui.comboBox_M_BitControl->clear();
	for (i = 0; i < 2; i++)
	{
		ui.comboBox_M_BitControl->insertItem(i,strTextBitControl[i]);
	}
	ui.comboBox_F_BitControl->clear();
	for (i = 0; i < 2; i++)
	{
		ui.comboBox_F_BitControl->insertItem(i, strTextBitControl[i]);
	}

#ifdef OEM_RAYSHARP
	GetDlgItem(IDC_COMBO_GOP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_EXPAND_GOP)->ShowWindow(SW_HIDE);
#endif

	QString strQuality[] = { QObject::tr("很差"), QObject::tr("较差"), QObject::tr("一般"),
		QObject::tr("好"), QObject::tr("很好"), QObject::tr("最好") };
	ui.comboBox_M_Image->clear();
	for (i = 0; i < 6; i++)
	{
		ui.comboBox_M_Image->insertItem(i,strQuality[i]);
	}
	ui.comboBox_F_Image->clear();
	for (i = 0; i < 6; i++)
	{
		ui.comboBox_F_Image->insertItem(i, strQuality[i]);
	}

	ui.comboBox_M_Interal->clear();
	for (i = 0; i < 11; i++)
	{
		QString str;
		str = QString("%1").arg(i + 2);
		ui.comboBox_M_Interal->addItem(str);
	}
	ui.comboBox_F_Interal->clear();
	for (i = 0; i < 11; i++)
	{
		QString str;
		str = QString("%1").arg(i + 2);
		ui.comboBox_F_Interal->addItem(str);
	}
}

void JLConfigSetting::InitResData()
{
	if (m_nVideoStandard == 0)  //PAL
	{
		m_resolution[SDK_CAPTURE_SIZE_D1].strText = "D1(704x576)";
		m_resolution[SDK_CAPTURE_SIZE_HD1].strText = "HD1(704x288)";
		m_resolution[SDK_CAPTURE_SIZE_BCIF].strText = "BCIF(352x576)";
		m_resolution[SDK_CAPTURE_SIZE_CIF].strText = "CIF(352x288)";
		m_resolution[SDK_CAPTURE_SIZE_QCIF].strText = "QCIF(176x144)";
		m_resolution[SDK_CAPTURE_SIZE_VGA].strText = "VGA(640x480)";
		m_resolution[SDK_CAPTURE_SIZE_QVGA].strText = "QVGA(320x240)";
		m_resolution[SDK_CAPTURE_SIZE_SVCD].strText = "SVCD(480x480)";
		m_resolution[SDK_CAPTURE_SIZE_QQVGA].strText = "QQVGA(160x128)";

		m_resolution[SDK_CAPTURE_SIZE_D1].dwSize = 704 * 576;
		m_resolution[SDK_CAPTURE_SIZE_HD1].dwSize = 704 * 288;
		m_resolution[SDK_CAPTURE_SIZE_BCIF].dwSize = 352 * 576;
		m_resolution[SDK_CAPTURE_SIZE_CIF].dwSize = 352 * 288;
		m_resolution[SDK_CAPTURE_SIZE_QCIF].dwSize = 176 * 144;
		m_resolution[SDK_CAPTURE_SIZE_VGA].dwSize = 640 * 480;
		m_resolution[SDK_CAPTURE_SIZE_QVGA].dwSize = 320 * 240;
		m_resolution[SDK_CAPTURE_SIZE_SVCD].dwSize = 480 * 480;
		m_resolution[SDK_CAPTURE_SIZE_QQVGA].dwSize = 160 * 128;

		m_resolution[SDK_CAPTURE_SIZE_ND1].strText = "ND1(240x192)";
		m_resolution[SDK_CAPTURE_SIZE_650TVL].strText = "960H(960x576)";
		m_resolution[SDK_CAPTURE_SIZE_720P].strText = "720(1280x720)";
		m_resolution[SDK_CAPTURE_SIZE_1_3M].strText = "1.3M(1280x960)";
		m_resolution[SDK_CAPTURE_SIZE_UXGA].strText = "UXGA(1600x1200)";
		m_resolution[SDK_CAPTURE_SIZE_1080P].strText = "1080P(1920x1080)";
		m_resolution[SDK_CAPTURE_SIZE_WUXGA].strText = "WUXGA(1920x1200)";
		m_resolution[SDK_CAPTURE_SIZE_2_5M].strText = "2.5M(1872x1408)";
		m_resolution[SDK_CAPTURE_SIZE_3M].strText = "3M(2048x1536)";
		m_resolution[SDK_CAPTURE_SIZE_5M].strText = "5M(2592x1944)";
		m_resolution[SDK_CAPTURE_SIZE_4M].strText = "4M(2592x1520)";

		m_resolution[SDK_CAPTURE_SIZE_6M].strText = "6M(3072x2048)";
		m_resolution[SDK_CAPTURE_SIZE_8M].strText = "8M(3264x2448)";
		m_resolution[SDK_CAPTURE_SIZE_12M].strText = "12M(4000x3000)";
		m_resolution[SDK_CAPTURE_SIZE_4K].strText = "4K(4096x2160)";

		m_resolution[SDK_CAPTURE_SIZE_ND1].dwSize = 240 * 192;
		m_resolution[SDK_CAPTURE_SIZE_650TVL].dwSize = 928 * 576; //960*576;
		m_resolution[SDK_CAPTURE_SIZE_720P].dwSize = 1280 * 720;
		m_resolution[SDK_CAPTURE_SIZE_1_3M].dwSize = 1280 * 960;
		m_resolution[SDK_CAPTURE_SIZE_UXGA].dwSize = 1600 * 1200;
		m_resolution[SDK_CAPTURE_SIZE_1080P].dwSize = 1920 * 1080;
		m_resolution[SDK_CAPTURE_SIZE_WUXGA].dwSize = 1920 * 1200;
		m_resolution[SDK_CAPTURE_SIZE_2_5M].dwSize = 1872 * 1408;
		m_resolution[SDK_CAPTURE_SIZE_3M].dwSize = 2048 * 1536;
		m_resolution[SDK_CAPTURE_SIZE_5M].dwSize = 3744 * 1408;
		m_resolution[SDK_CAPTURE_SIZE_4M].dwSize = 2592 * 1520;

		m_resolution[SDK_CAPTURE_SIZE_6M].dwSize = 3072 * 2048;
		m_resolution[SDK_CAPTURE_SIZE_8M].dwSize = 3264 * 2448;
		m_resolution[SDK_CAPTURE_SIZE_12M].dwSize = 4000 * 3000;
		m_resolution[SDK_CAPTURE_SIZE_4K].dwSize = 4096 * 2160;
	}
	else
	{
		m_resolution[SDK_CAPTURE_SIZE_D1].strText = "D1(704x480)";
		m_resolution[SDK_CAPTURE_SIZE_HD1].strText = "HD1(704x240)";
		m_resolution[SDK_CAPTURE_SIZE_BCIF].strText = "BCIF(352x480)";
		m_resolution[SDK_CAPTURE_SIZE_CIF].strText = "CIF(352x240)";
		m_resolution[SDK_CAPTURE_SIZE_QCIF].strText = "QCIF(176x120)";
		m_resolution[SDK_CAPTURE_SIZE_VGA].strText = "VGA(640x480)";
		m_resolution[SDK_CAPTURE_SIZE_QVGA].strText = "QVGA(320x240)";
		m_resolution[SDK_CAPTURE_SIZE_SVCD].strText = "SVCD(480x480)";
		m_resolution[SDK_CAPTURE_SIZE_QQVGA].strText = "QQVGA(160x128)";

		m_resolution[SDK_CAPTURE_SIZE_D1].dwSize = 704 * 480;
		m_resolution[SDK_CAPTURE_SIZE_HD1].dwSize = 704 * 240;
		m_resolution[SDK_CAPTURE_SIZE_BCIF].dwSize = 352 * 480;
		m_resolution[SDK_CAPTURE_SIZE_CIF].dwSize = 352 * 240;
		m_resolution[SDK_CAPTURE_SIZE_QCIF].dwSize = 176 * 120;
		m_resolution[SDK_CAPTURE_SIZE_VGA].dwSize = 640 * 480;
		m_resolution[SDK_CAPTURE_SIZE_QVGA].dwSize = 320 * 240;
		m_resolution[SDK_CAPTURE_SIZE_SVCD].dwSize = 480 * 480;
		m_resolution[SDK_CAPTURE_SIZE_QQVGA].dwSize = 160 * 128;

		m_resolution[SDK_CAPTURE_SIZE_ND1].strText = "ND1(240x192)";
		m_resolution[SDK_CAPTURE_SIZE_650TVL].strText = "960H(960x480)";
		m_resolution[SDK_CAPTURE_SIZE_720P].strText = "720(1280x720)";
		m_resolution[SDK_CAPTURE_SIZE_1_3M].strText = "1.3M(1280x960)";
		m_resolution[SDK_CAPTURE_SIZE_UXGA].strText = "UXGA(1600x1200)";
		m_resolution[SDK_CAPTURE_SIZE_1080P].strText = "1080P(1920x1080)";
		m_resolution[SDK_CAPTURE_SIZE_WUXGA].strText = "WUXGA(1920x1200)";
		m_resolution[SDK_CAPTURE_SIZE_2_5M].strText = "2.5M(1872x1408)";
		m_resolution[SDK_CAPTURE_SIZE_3M].strText = "3M(2048x1536)";
		m_resolution[SDK_CAPTURE_SIZE_5M].strText = "5M(2592x1944)";
		m_resolution[SDK_CAPTURE_SIZE_4M].strText = "4M(2592x1520)";

		m_resolution[SDK_CAPTURE_SIZE_6M].strText = "6M(3072x2048)";
		m_resolution[SDK_CAPTURE_SIZE_8M].strText = "8M(3264x2448)";
		m_resolution[SDK_CAPTURE_SIZE_12M].strText = "12M(4000x3000)";
		m_resolution[SDK_CAPTURE_SIZE_4K].strText = "4K(4096x2160)";

		m_resolution[SDK_CAPTURE_SIZE_ND1].dwSize = 240 * 192;
		m_resolution[SDK_CAPTURE_SIZE_650TVL].dwSize = 928 * 480;//960*480;
		m_resolution[SDK_CAPTURE_SIZE_720P].dwSize = 1280 * 720;
		m_resolution[SDK_CAPTURE_SIZE_1_3M].dwSize = 1280 * 960;
		m_resolution[SDK_CAPTURE_SIZE_UXGA].dwSize = 1600 * 1200;
		m_resolution[SDK_CAPTURE_SIZE_1080P].dwSize = 1920 * 1080;
		m_resolution[SDK_CAPTURE_SIZE_WUXGA].dwSize = 1920 * 1200;
		m_resolution[SDK_CAPTURE_SIZE_2_5M].dwSize = 1872 * 1408;
		m_resolution[SDK_CAPTURE_SIZE_3M].dwSize = 2048 * 1536;
		m_resolution[SDK_CAPTURE_SIZE_5M].dwSize = 3744 * 1408;
		m_resolution[SDK_CAPTURE_SIZE_4M].dwSize = 2592 * 1520;

		m_resolution[SDK_CAPTURE_SIZE_6M].dwSize = 3072 * 2048;
		m_resolution[SDK_CAPTURE_SIZE_8M].dwSize = 3264 * 2448;
		m_resolution[SDK_CAPTURE_SIZE_12M].dwSize = 4000 * 3000;
		m_resolution[SDK_CAPTURE_SIZE_4K].dwSize = 4096 * 2160;
	}

	m_resolution[SDK_CAPTURE_SIZE_D1].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_HD1].dsMask = BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_BCIF].dsMask = BITMSK(SDK_CAPTURE_SIZE_BCIF) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_CIF].dsMask = BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_QCIF].dsMask = BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_VGA].dsMask = BITMSK(SDK_CAPTURE_SIZE_VGA) | BITMSK(SDK_CAPTURE_SIZE_QVGA);
	m_resolution[SDK_CAPTURE_SIZE_QVGA].dsMask = BITMSK(SDK_CAPTURE_SIZE_QVGA);
	m_resolution[SDK_CAPTURE_SIZE_SVCD].dsMask = BITMSK(SDK_CAPTURE_SIZE_SVCD);
	m_resolution[SDK_CAPTURE_SIZE_QQVGA].dsMask = BITMSK(SDK_CAPTURE_SIZE_QQVGA);
	m_resolution[SDK_CAPTURE_SIZE_ND1].dsMask = BITMSK(SDK_CAPTURE_SIZE_ND1);
	m_resolution[SDK_CAPTURE_SIZE_650TVL].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_720P].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_1_3M].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_UXGA].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_1080P].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_WUXGA].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_2_5M].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_3M].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_5M].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_4M].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);

	m_resolution[SDK_CAPTURE_SIZE_6M].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_8M].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_12M].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_4K].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);

	m_maxBitRate[SDK_CAPTURE_SIZE_D1] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_D1][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_HD1] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_HD1][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_BCIF] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_BCIF][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_CIF] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_CIF][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_QCIF] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_QCIF][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_VGA] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_VGA][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_QVGA] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_QVGA][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_SVCD] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_SVCD][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_QQVGA] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_QQVGA][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_ND1] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_ND1][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_650TVL] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_650TVL][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_720P] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_720P][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_1_3M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_1_3M][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_UXGA] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_UXGA][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_1080P] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_1080P][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_WUXGA] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_WUXGA][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_2_5M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_2_5M][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_3M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_3M][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_5M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_5M][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_4M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_4M][5];

	m_maxBitRate[SDK_CAPTURE_SIZE_6M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_6M][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_8M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_8M][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_12M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_12M][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_4K] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_4K][5];
}
void JLConfigSetting::InitStramInfo(int ChannnelNum, SDK_EncodeConfigAll_SIMPLIIFY *pEncodeSimpl,
	SDK_CONFIG_NORMAL *pNormalCfg, CONFIG_EncodeAbility *pEncodeAbility,
	SDK_CombineEncodeConfigAll *pCmbEncode, SDK_SystemFunction *pSysFunc,
	DEV_ATTRIBUTE *pDevAttribute, SDK_CombEncodeModeAll *pCmbEncodeMode,
	SDK_EncodeStaticParamAll *pEncodeStatic)
{
	m_nVideoStandard = pNormalCfg->iVideoFormat;
	m_streamChannelNum = ChannnelNum;
	InitCombo();

	ui.comboBox_ChanNo->setCurrentIndex(0);
	memcpy(&m_EncodeConfig, pEncodeSimpl, sizeof(SDK_EncodeConfigAll_SIMPLIIFY));
	if (pEncodeAbility->iMaxBps == 0)
	{
		m_pEncodeAbility.iMaxBps = 24 * 1024;
	}
	memcpy(&m_pEncodeAbility, pEncodeAbility, sizeof(CONFIG_EncodeAbility));
	memcpy(&m_CmbEncodeCfg, pCmbEncode, sizeof(SDK_CombineEncodeConfigAll));
	memcpy(&m_CmbEncodeMode, pCmbEncodeMode, sizeof(SDK_CombEncodeModeAll));
	memcpy(&m_DevAttribute, pDevAttribute, sizeof(DEV_ATTRIBUTE));
	strcpy(m_cVersion, pDevAttribute->deviveInfo.sSoftWareVersion);
	m_nAudioInNum = pDevAttribute->deviveInfo.iAudioInChannel;
	InitResData();
	memcpy(&m_SysFunc, pSysFunc, sizeof(SDK_SystemFunction));
	m_bMultiStream = pSysFunc->vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_DOUBLE_STREAM];
	if (m_bMultiStream)
	{
		ui.checkBox_F_Video->setEnabled(true);
		ui.checkBox_F_Audio->setEnabled(true);
	}
	else
	{
		ui.checkBox_F_Video->setEnabled(false);
		ui.checkBox_F_Audio->setEnabled(false);
	}

	if (strcmp(m_cVersion, "V1.22.R03") >= 0 && pSysFunc->vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_COMBINE_STREAM])
	{
		
		ui.comboBox__F_EnMode->setEnabled(false);
		m_bCombineEncode = true;
		if (strcmp(m_cVersion, "V1.24.R03") >= 0)
		{
			m_bCombineSet = true;
			ui.comboBox__F_EnMode->setEnabled(true);
			ui.comboBox_F_Resolution->setEnabled(true);
			ui.comboBox_F_Frame->setEnabled(true);
			ui.comboBox_F_BitControl->setEnabled(true);
			ui.comboBox_F_Image->setEnabled(true);
			ui.comboBox_F_Stream->setEnabled(true);
#ifndef OEM_RAYSHARP
			ui.comboBox_F_Interal->setEnabled(true);
#endif

			//GetDlgItem(IDC_COMBO_COMBINEMODE)->ShowWindow(SW_SHOW);
			//GetDlgItem(IDC_STATIC_COMBINE_MODE)->ShowWindow(SW_SHOW);
		}
		else
		{
			m_bCombineSet = false;
			ui.comboBox__F_EnMode->setEnabled(true);
			ui.comboBox_F_Resolution->setEnabled(true);
			ui.comboBox_F_Frame->setEnabled(true);
			ui.comboBox_F_BitControl->setEnabled(true);
			ui.comboBox_F_Image->setEnabled(true);
			ui.comboBox_F_Stream->setEnabled(true);
			ui.comboBox_F_Interal->setEnabled(true);
		}
	}
	else
	{

		ui.comboBox__F_EnMode->setEnabled(true);
		ui.comboBox_F_Resolution->setEnabled(true);
		ui.comboBox_F_Frame->setEnabled(true);
		ui.comboBox_F_BitControl->setEnabled(true);
		ui.comboBox_F_Image->setEnabled(true);
		ui.comboBox_F_Stream->setEnabled(true);
#ifndef OEM_RAYSHARP
		ui.comboBox_F_Interal->setEnabled(true);
#endif
		m_bCombineEncode = false;
		m_bCombineSet = false;
	}
	//静态编码
	if (pEncodeStatic)
	{
		ui.comboBox_M__Set->clear();
		ui.comboBox_M__Set->setEnabled(true);

		QStringList list;
		list << "baseline" << "main profile" << "high profile";
		ui.comboBox_M__Set->addItems(list);
		ui.comboBox_M__Set->setCurrentIndex(pEncodeStatic->EncodeStaticParamAll[0].profile - 1);
	}
	ui.checkBox_M_Video->setEnabled(false);
	StructToWin();
}

bool JLConfigSetting::StructToWin()
{
	bool bRet = false;

	UpdateCodeFormat(0, ui.comboBox__M_EnMode);
	if (m_bMultiStream)
	{
		UpdateCodeFormat(1, ui.comboBox__F_EnMode);
	}
	else
	{
		UpdateCodeFormat(0, ui.comboBox__F_EnMode);
	}

	ui.comboBox__F_EnMode->setCurrentIndex(0);

	int nChannelNo = ui.comboBox_ChanNo->currentIndex();
	if (nChannelNo == m_DevAttribute.deviveInfo.byChanNum)
	{
		nChannelNo = 0;
	}
	NormalStructToWinData(nChannelNo, &m_EncodeConfig.vEncodeConfigAll[nChannelNo], MAIN_STREAM);
	NormalStructToWinData(nChannelNo, &m_EncodeConfig.vEncodeConfigAll[nChannelNo], EXPAND_STREAM);
	CombineStructToWinData(nChannelNo, &m_EncodeConfig.vEncodeConfigAll[0], COMBINE_STREAM);


	////by zjh 20170731
	map<int, QString>::iterator itCompression = m_mapCaptureComp.find(m_EncodeConfig.vEncodeConfigAll[nChannelNo].dstMainFmt.vfFormat.iCompression);
	if (itCompression != m_mapCaptureComp.end())
	{
		QString strSel = itCompression->second;
		ui.comboBox__M_EnMode->setCurrentText(strSel);
	}

	itCompression = m_mapCaptureComp.find(m_EncodeConfig.vEncodeConfigAll[nChannelNo].dstExtraFmt.vfFormat.iCompression);
	if (itCompression != m_mapCaptureComp.end())
	{
		QString strSel = itCompression->second;
		ui.comboBox__F_EnMode->setCurrentText(strSel);
	}

	return true;
}

bool JLConfigSetting::CombineStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType)
{
	DWORD dwPower = 0;
	if (nEncodeType == COMBINE_STREAM && m_bCombineEncode)
	{
		return StructToWinData(nChannelNum, pConfigEncode, nEncodeType, dwPower, -1, -1);
	}
	return false;
}
void JLConfigSetting::UpdateCodeFormat(int nStream, QComboBox *m_combox)
{
	m_combox->clear();
	unsigned int uiCompression = 0;
	if (nStream == 2)
	{
		uiCompression = m_pEncodeAbility.vCombEncInfo[0].uiCompression ? m_pEncodeAbility.vCombEncInfo[0].uiCompression : m_pEncodeAbility.vEncodeInfo[0].uiCompression;
	}
	else
	{
		uiCompression = m_pEncodeAbility.vEncodeInfo[nStream].uiCompression;
	}

	for (int i = 0; i < SDK_CAPTURE_COMP_NR; i++)
	{
		if (uiCompression & (1 << i))
		{
			QString str = QString("%1").arg(i);
			m_combox->addItem(str);
		}
	}
}

bool JLConfigSetting::NormalStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType)
{
	if (nEncodeType == MAIN_STREAM || (nEncodeType == EXPAND_STREAM && m_bMultiStream))
	{
		DWORD dwPower = GetFreeDspPower(nChannelNum);
		DWORD dwBitrate = -1;
		if (nEncodeType == MAIN_STREAM)
		{
			if (m_pEncodeAbility.nMaxPowerPerChannel[nChannelNum])
			{
				dwPower = (dwPower < m_pEncodeAbility.nMaxPowerPerChannel[nChannelNum]) ? dwPower : m_pEncodeAbility.nMaxPowerPerChannel[nChannelNum];
			}

			int i = 0;
			for (i = 0; m_pEncodeAbility.ImageSizePerChannel[nChannelNum] && i < SDK_CAPTURE_SIZE_NR; i++)
			{
				if ((1 << i) & m_pEncodeAbility.ImageSizePerChannel[nChannelNum])
				{
					break;
				}
			}
			pConfigEncode->dstMainFmt.vfFormat.iResolution =
				(i > pConfigEncode->dstMainFmt.vfFormat.iResolution) ? i : pConfigEncode->dstMainFmt.vfFormat.iResolution;

			dwBitrate = GetFreeBitratePower(nChannelNum);
		}
		else if (nEncodeType == EXPAND_STREAM)
		{
			int i = 0;
			for (i = 0; m_pEncodeAbility.ExImageSizePerChannel[nChannelNum] && i < SDK_CAPTURE_SIZE_NR; i++)
			{
				if ((1 << i) & m_pEncodeAbility.ExImageSizePerChannel[nChannelNum])
				{
					break;
				}
			}
			pConfigEncode->dstExtraFmt.vfFormat.iResolution =
				(i > pConfigEncode->dstExtraFmt.vfFormat.iResolution) ? i : pConfigEncode->dstExtraFmt.vfFormat.iResolution;
		}
		return StructToWinData(nChannelNum, pConfigEncode, nEncodeType, dwPower, -1, dwBitrate);
	}
	return false;
}

bool JLConfigSetting::StructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType, DWORD dwPower, DWORD dwMask, DWORD dwBitrate )
{
	if (nEncodeType >= STREAM_NUM)
	{
		return false;
	}
	SDK_MEDIA_FORMAT &dstMainFmt = pConfigEncode->dstMainFmt;
	SDK_VIDEO_FORMAT &vfFormat = dstMainFmt.vfFormat;

	SDK_MEDIA_FORMAT &dstExtraFmt = pConfigEncode->dstExtraFmt;
	SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;

	SDK_MEDIA_FORMAT dstSetFmt = { 0 };
	SDK_VIDEO_FORMAT vfSetFormat = { 0 };

	int nResolution = 0, nFPS = 25;
	DWORD dwChnUsed = 0, dwChnFree = 0;
	if (nEncodeType == MAIN_STREAM)
	{
		if (dwMask == -1)
		{
			if (m_pEncodeAbility.ImageSizePerChannel[nChannelNum])
			{
				dwMask = m_pEncodeAbility.ImageSizePerChannel[nChannelNum];
			}
			else
			{
				dwMask = m_pEncodeAbility.vEncodeInfo[0].uiResolution;
			}
		}

		if (m_bMultiStream && dstExtraFmt.bVideoEnable && (vfExFormat.iResolution >= SDK_CAPTURE_SIZE_D1 && vfExFormat.iResolution < SDK_CAPTURE_SIZE_NR))
		{
			dwChnUsed = m_resolution[vfExFormat.iResolution].dwSize * vfExFormat.nFPS;
		}
		dwChnFree = dwPower - dwChnUsed;
		if (m_pEncodeAbility.iChannelMaxSetSync)
		{
			DWORD dwAvgPower = (m_pEncodeAbility.iMaxEncodePower - GetExpandUsed()) / m_DevAttribute.deviveInfo.byChanNum;
			dwChnFree = min(dwChnFree, dwAvgPower);
		}


		nResolution = vfFormat.iResolution;
		nFPS = vfFormat.nFPS;
		GetMaxResolAndRate(nResolution, nFPS, dwChnFree);
		EnableMainVideo(dstMainFmt.bVideoEnable);
		dstSetFmt = dstMainFmt;
		vfSetFormat = vfFormat;
	}
	else if (nEncodeType == EXPAND_STREAM)
	{
		if (dwMask == -1)
		{
			if (m_pEncodeAbility.ExImageSizePerChannel[nChannelNum])
			{
				dwMask = m_pEncodeAbility.ExImageSizePerChannel[nChannelNum];
			}
			else
			{
				dwMask = m_pEncodeAbility.vEncodeInfo[0].uiResolution;
			}
		}

		if (m_pEncodeAbility.ExImageSizePerChannelEx[nChannelNum][dstMainFmt.vfFormat.iResolution])
		{
			dwMask &= m_pEncodeAbility.ExImageSizePerChannelEx[nChannelNum][dstMainFmt.vfFormat.iResolution];
		}
		if (dstMainFmt.bVideoEnable)
		{
			dwChnUsed = m_resolution[vfFormat.iResolution].dwSize * vfFormat.nFPS;
		}
		dwChnFree = dwPower - dwChnUsed;
		if (m_pEncodeAbility.iChannelMaxSetSync)
		{
			DWORD dwAvgPower = (m_pEncodeAbility.iMaxEncodePower - GetMainUsed()) / m_DevAttribute.deviveInfo.byChanNum;
			dwChnFree = min(dwChnFree, dwAvgPower);
		}
		nResolution = vfExFormat.iResolution;
		nFPS = vfExFormat.nFPS;
		GetMaxResolAndRate(nResolution, nFPS, dwChnFree);
		EnableExpandVideo(dstExtraFmt.bVideoEnable);
		dstSetFmt = dstExtraFmt;
		vfSetFormat = vfExFormat;
	}
	else
	{
		dwMask = m_pEncodeAbility.vCombEncInfo[0].uiResolution ? m_pEncodeAbility.vCombEncInfo[0].uiResolution : m_pEncodeAbility.vEncodeInfo[0].uiResolution;
		dwChnUsed = 0;
		dwChnFree = dwPower - dwChnUsed;


		nResolution = SDK_CAPTURE_SIZE_D1;
		nFPS = (0 == m_nVideoStandard) ? 25 : 30;

		EnableExpandVideo(dstMainFmt.bVideoEnable);
		dstSetFmt = dstMainFmt;
		vfSetFormat = vfFormat;
	}
	AddCmbResolution(Control[nEncodeType][CONTROL_RESOLUTION], nResolution, dwMask);

	QString strLog = "";
	strLog = QString("EncodeType = %1,MAIN VF Format = %2,ExtraFmt = %3,AddCmbFPS = %4,Resolution = %5\r\n").arg(nEncodeType).arg(vfFormat.nFPS).arg( vfExFormat.nFPS).arg(nFPS).arg(nResolution);

	AddCmbFPS(Control[nEncodeType][CONTROL_FRAME], nFPS);

	SetComBoxCurSel(Control[nEncodeType][CONTROL_RESOLUTION], vfSetFormat.iResolution);

	if (vfSetFormat.nFPS < nFPS)
		SetComBoxCurSel(Control[nEncodeType][CONTROL_FRAME], vfSetFormat.nFPS);
	else
		SetComBoxCurSel(Control[nEncodeType][CONTROL_FRAME], nFPS);

	SetComBoxCurSel(Control[nEncodeType][CONTROL_BITCONTROL], vfSetFormat.iBitRateControl);
	SetComBoxCurSel(Control[nEncodeType][CONTROL_QUALITY], vfSetFormat.iQuality);
	SetComBoxCurSel(Control[nEncodeType][CONTROL_GOP], vfSetFormat.iGOP);


	int nTmpFPS = 25;
	nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	nTmpFPS = min(vfSetFormat.nFPS, nFPS);

	QComboBox *pComboBox = ui.tabWidget->findChild<QComboBox *>(Control[nEncodeType][CONTROL_BIT_RATE]);
	pComboBox->clear();
	for (int j = 0; j < sizeof(STREAM_CODE_VALUE[vfSetFormat.iResolution]) / sizeof(int); ++j)
	{
		TCHAR sBitrate[8];

		int iBitrate = STREAM_CODE_VALUE[vfSetFormat.iResolution][j] * (vfSetFormat.iGOP * nTmpFPS + IFRAME_EQ_PFRAME - 1) / (vfSetFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
		sprintf(sBitrate, "%d", STREAM_CODE_VALUE[vfSetFormat.iResolution][j] * (vfSetFormat.iGOP * nTmpFPS + IFRAME_EQ_PFRAME - 1) / (vfSetFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1));

		if (dwBitrate == -1 || dwBitrate >= iBitrate)
		{
			int nInsert = pComboBox->currentIndex();
			pComboBox->setItemData(nInsert, iBitrate);
		}
	}
	if (0 == vfSetFormat.iBitRateControl)
	{
		if (-1 == dwBitrate)
		{
			SetComBoxCurSel(Control[nEncodeType][CONTROL_BIT_RATE], NearBitrate(Control[nEncodeType][CONTROL_BIT_RATE], vfSetFormat.nBitRate));
		}
		else
		{
			dwBitrate = (dwBitrate > vfSetFormat.nBitRate) ? vfSetFormat.nBitRate : dwBitrate;
			SetComBoxCurSel(Control[nEncodeType][CONTROL_BIT_RATE], NearBitrate(Control[nEncodeType][CONTROL_BIT_RATE], dwBitrate));
		}
	}
	else
	{
		if (-1 == dwBitrate)
		{
			SetComBoxCurSel(Control[nEncodeType][CONTROL_BIT_RATE],
				STREAM_CODE_VALUE[vfSetFormat.iResolution][vfSetFormat.iQuality - 1] * (vfSetFormat.iGOP * nTmpFPS + IFRAME_EQ_PFRAME - 1) / (vfSetFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1));
		}
		else
		{
			DWORD dwCntBitrate = STREAM_CODE_VALUE[vfSetFormat.iResolution][min(vfSetFormat.iQuality - 1, 6)] * (vfSetFormat.iGOP * nTmpFPS + IFRAME_EQ_PFRAME - 1) / (vfSetFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
			dwBitrate = (dwBitrate > dwCntBitrate) ? dwCntBitrate : dwBitrate;
			bool nret = SetComBoxCurSel(Control[nEncodeType][CONTROL_BIT_RATE], NearBitrate(Control[nEncodeType][CONTROL_BIT_RATE], dwBitrate));
		}
	}

	QCheckBox *pCheckBox = ui.tabWidget->findChild<QCheckBox *>(Control[nEncodeType][CONTROL_VIDEO]);
	pCheckBox->setCheckable(dstSetFmt.bVideoEnable);
	ui.tabWidget->findChild<QCheckBox *>(Control[nEncodeType][CONTROL_AUDIO])->setCheckable(dstSetFmt.bAudioEnable && dstSetFmt.bVideoEnable);
	ui.tabWidget->findChild<QComboBox *>(Control[nEncodeType][CONTROL_BIT_RATE])->setEnabled(!vfSetFormat.iBitRateControl && dstSetFmt.bVideoEnable);
	ui.tabWidget->findChild<QComboBox *>(Control[nEncodeType][CONTROL_QUALITY])->setEnabled(vfSetFormat.iBitRateControl && dstSetFmt.bVideoEnable);
	if (nEncodeType == COMBINE_STREAM)
	{
		//SetComBoxCurSel(IDC_COMBO_COMBINEMODE, m_CmbEncodeMode.vEncodeParam[0].iEncodeMode);
		//GetDlgItem(IDC_COMBO_COMBINEMODE)->EnableWindow(dstSetFmt.bVideoEnable);
	}

	return true;
}

void JLConfigSetting::AddCmbFPS(QString m_comboxID, int maxSize)
{
	
	if (m_comboxID == "")
	{
		return;
	}
	QComboBox *m_combox = ui.tabWidget->findChild<QComboBox *>(m_comboxID);
	m_combox->clear();

	for (int i = 0; i < maxSize; i++)
	{
		QString strChannel("");
		strChannel = QString("%1").arg(i + 1);
		m_combox->insertItem(i,strChannel);
	
	}
}

BOOL JLConfigSetting::SetComBoxCurSel(QString m_comboxID, DWORD dwData)
{
	if (m_comboxID == "")
	{
		return FALSE;
	}
	QComboBox *m_combox = ui.tabWidget->findChild<QComboBox *>(m_comboxID);
	int nCount = m_combox->count();
	for (int i = 0; i < nCount; i++)
	{
		if (m_combox->currentIndex() == dwData)
		{
			m_combox->setCurrentIndex(i);
			return TRUE;
		}
	}

	return FALSE;
}

int JLConfigSetting::NearBitrate(QString m_comboxID, DWORD dwData)
{
	if (m_comboxID == "")
	{
		return dwData;
	}
	QComboBox *m_combox = ui.tabWidget->findChild<QComboBox *>(m_comboxID);
	int nCount = m_combox->count();
	int nBitrate = 0;
	for (int i = 0; i < nCount; i++)
	{
		nBitrate = m_combox->currentIndex();
		if (nBitrate >= dwData)
		{
			break;
		}
	}

	return nBitrate;
}

void JLConfigSetting::AddCmbResolution(QString comboxID, int maxSize, DWORD dwMask)
{
	if (comboxID == "")
	{
		return;
	}
	QComboBox *m_combox = ui.tabWidget->findChild<QComboBox *>(comboxID);
	m_combox->clear();

	for (int i = 0; i < SDK_CAPTURE_SIZE_NR; i++)
	{
		if (/* (m_resolution[i].dwSize <= m_resolution[maxSize].dwSize )
			&&*/ (dwMask & (0x01 << i)))
		{
			m_combox->insertItem(i, m_resolution[i].strText);
		}
	}
}
void JLConfigSetting::EnableMainVideo(BOOL bEnable)
{
	ui.comboBox__M_EnMode->setEnabled(bEnable);
	ui.comboBox_M_Resolution->setEnabled(bEnable);
	ui.comboBox_M_Frame->setEnabled(bEnable);
	ui.comboBox_M_BitControl->setEnabled(bEnable);
	ui.comboBox_M_Image->setEnabled(bEnable);
	ui.comboBox_M_Stream->setEnabled(bEnable);
	ui.comboBox_M_Interal->setEnabled(bEnable);
}

void JLConfigSetting::EnableExpandVideo(BOOL bEnable)
{
	ui.comboBox__F_EnMode->setEnabled(bEnable);
	ui.comboBox_F_Resolution->setEnabled(bEnable);
	ui.comboBox_F_Frame->setEnabled(bEnable);
	ui.comboBox_F_BitControl->setEnabled(bEnable);
	ui.comboBox_F_Image->setEnabled(bEnable);
	ui.comboBox_F_Stream->setEnabled(bEnable);
	ui.comboBox_F_Interal->setEnabled(bEnable);
}

DWORD JLConfigSetting::GetMainUsed()
{
	DWORD lUsePower = 0;
	for (int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i++)
	{
		if (m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.bVideoEnable)
		{
			DWORD lSize = m_resolution[m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.iResolution].dwSize;
			lUsePower += lSize * m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.nFPS;
		}
	}
	return lUsePower;
}
void JLConfigSetting::GetMaxResolAndRate(int &nResolu, int &nRate, long lFreePower)
{
	if (lFreePower <= 0)
	{
		return;
	}

	int nSize = m_resolution[nResolu].dwSize;
	if (nSize > lFreePower)
	{
		nResolu = -1;
		nRate = -1;
		return;
	}
	else
	{
		int nTempRate = lFreePower / nSize;
		if (0 == m_nVideoStandard)
		{
			if (nTempRate > 25)
			{
				nTempRate = 25;
			}
		}
		else
		{
			if (nTempRate > 30)
			{
				nTempRate = 30;
			}
		}
		nRate = nTempRate;
	}
	if (nResolu == 0)
	{
		return;
	}

	long lMaxSize = nSize;
	for (int i = 0; i < SDK_CAPTURE_SIZE_NR; i++)
	{
		long lTempsize = m_resolution[i].dwSize;
		if (lFreePower >= lTempsize && lMaxSize < lTempsize)
		{
			nResolu = i;
			lMaxSize = lTempsize;
		}
	}
}

DWORD JLConfigSetting::GetExpandUsed()
{
	DWORD lUsePower = 0;
	if (m_bMultiStream)
	{
		for (int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i++)
		{
			if (m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.bVideoEnable)
			{
				DWORD lSize = m_resolution[m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.iResolution].dwSize;
				lUsePower += lSize * m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.nFPS;
			}
		}
	}

	return lUsePower;
}

DWORD JLConfigSetting::GetFreeDspPower(int nChannelNo)
{
	DWORD lFreePower = m_pEncodeAbility.iMaxEncodePower;

	for (int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i++)
	{
		if (i != nChannelNo)
		{
			//// by zjh 20170815
			if (m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.iResolution >= SDK_CAPTURE_SIZE_NR || m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.iResolution < SDK_CAPTURE_SIZE_D1)
			{
				continue;
			}

			if (m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.bVideoEnable)
			{

				DWORD lSize = m_resolution[m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.iResolution].dwSize;
				lFreePower -= lSize * m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.nFPS;
			}

			if (m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.bVideoEnable)
			{
				DWORD lSize = m_resolution[m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.iResolution].dwSize;
				lFreePower -= lSize * m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.nFPS;
			}
		}
	}

	return lFreePower;
}
DWORD JLConfigSetting::GetFreeBitratePower(int nChannelNo)
{
	DWORD lFreePower = m_pEncodeAbility.iMaxBps;

	for (int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i++)
	{
		if (i != nChannelNo)
		{
			if (m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.bVideoEnable)
			{
				lFreePower -= m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.nBitRate;
			}
		}
	}

	return lFreePower;
}

void JLConfigSetting::on_checkBox_F_Audio_clicked()
{
	if (m_bMultiStream)
	{
		int nChannelNum = ui.comboBox_ChanNo->currentIndex();
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			nChannelNum = 0;
		}

		BOOL bEnable = FALSE;
		BOOL bChoose = ui.checkBox_F_Audio->checkState();
		if (bChoose)
		{
			bEnable = TRUE;
			if (!ui.checkBox_F_Video->checkState())
			{
				ui.checkBox_F_Audio->setCheckState(Qt::Unchecked);
				bEnable = FALSE;
			}
		}
		m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt.bAudioEnable = bEnable;
	}
}

void JLConfigSetting::on_checkBox_M_Audio_clicked()
{
	int nChannelNum = ui.comboBox_ChanNo->currentIndex();
	if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
	{
		nChannelNum = 0;
	}

	BOOL bEnable = FALSE;

	BOOL bChoose = ui.checkBox_M_Audio->checkState();
	if (bChoose)
	{
		bEnable = TRUE;
		if (!ui.checkBox_M_Video->checkState())
		{
			bEnable = FALSE;
			ui.checkBox_M_Video->setCheckState(Qt::Unchecked);
		}
	}

	m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt.bAudioEnable = bEnable;
}

void JLConfigSetting::on_checkBox_F_Video_clicked()
{
	int nChannelNum = ui.comboBox_ChanNo->currentIndex();
	if (m_bMultiStream)
	{
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			SDK_MEDIA_FORMAT &dstExtraFmt = m_allData.dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExtraFormat = dstExtraFmt.vfFormat;
			dstExtraFmt.bVideoEnable = ui.checkBox_M_Video->checkState();
			AllStructToWinData(0, &m_allData, MAIN_STREAM);
			AllStructToWinData(0, &m_allData, EXPAND_STREAM);
		}
		else
		{
			SDK_MEDIA_FORMAT &dstExtraFmt = m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExtraFormat = dstExtraFmt.vfFormat;
			dstExtraFmt.bVideoEnable = ui.checkBox_M_Video->checkState();
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
		}

	}
	else if (m_bCombineEncode)
	{
		SDK_MEDIA_FORMAT &dstMainFmt = m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0];
		SDK_VIDEO_FORMAT &vfFormat = dstMainFmt.vfFormat;
		dstMainFmt.bVideoEnable = false;
		SDK_CONFIG_ENCODE_SIMPLIIFY EncodeSimp;
		memcpy(&EncodeSimp.dstExtraFmt, &m_CmbEncodeCfg.vEncodeConfigAll[0].dstExtraFmt, sizeof(SDK_MEDIA_FORMAT));
		memcpy(&EncodeSimp.dstMainFmt, &m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt, sizeof(SDK_MEDIA_FORMAT));
		CombineStructToWinData(0, &EncodeSimp, COMBINE_STREAM);
	}
}

void JLConfigSetting::on_comboBox_F_Frame_activated(int index)
{
	int nChannelNum = ui.comboBox_ChanNo->currentIndex();
	if (m_bMultiStream)
	{
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			SelchangeComboFrame(m_allData.dstExtraFmt, EXPAND_STREAM);
			AllStructToWinData(0, &m_allData, MAIN_STREAM);
			AllStructToWinData(0, &m_allData, EXPAND_STREAM);
		}
		else
		{
			SelchangeComboFrame(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt, EXPAND_STREAM);
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
		}
	}
	else if (m_bCombineEncode)
	{
		SelchangeComboFrame(m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0], COMBINE_STREAM);
		SDK_CONFIG_ENCODE_SIMPLIIFY EncodeSimp;
		memcpy(&EncodeSimp.dstExtraFmt, &m_CmbEncodeCfg.vEncodeConfigAll[0].dstExtraFmt, sizeof(SDK_MEDIA_FORMAT));
		memcpy(&EncodeSimp.dstMainFmt, &m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt, sizeof(SDK_MEDIA_FORMAT));
		CombineStructToWinData(0, &EncodeSimp, COMBINE_STREAM);
	}
}

void JLConfigSetting::SelchangeComboFrame(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType)
{
	int nChannelNum = ui.comboBox_ChanNo->currentIndex();
	int iResolution = GetComboBoxData(Control[nEncodeType][CONTROL_RESOLUTION]);
	int iQuality = GetComboBoxData(Control[nEncodeType][CONTROL_QUALITY]) - 1;

	SDK_VIDEO_FORMAT &vfFormat = dstFormat.vfFormat;
	int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	int iSrcFPS = vfFormat.nFPS;
	vfFormat.nFPS = GetComboBoxData(Control[nEncodeType][CONTROL_FRAME]);

	if (vfFormat.iBitRateControl)
	{
		vfFormat.nBitRate =
			STREAM_CODE_VALUE[iResolution][iQuality] * (vfFormat.iGOP * vfFormat.nFPS + IFRAME_EQ_PFRAME - 1) / (vfFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
	}
	else
	{
		int nTarget = vfFormat.nBitRate * (vfFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1) / (vfFormat.iGOP * iSrcFPS + IFRAME_EQ_PFRAME - 1);
		vfFormat.nBitRate = nTarget * (vfFormat.iGOP * vfFormat.nFPS + IFRAME_EQ_PFRAME - 1) / (vfFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
	}
}

void JLConfigSetting::on_comboBox_F_Image_activated(int index)
{
	int iResolution =ui.comboBox_F_Resolution->currentIndex();
	int iQuality = ui.comboBox_F_Image->currentIndex();
	int iGOP = ui.comboBox_F_Interal->currentIndex();
	int nTmpFPS = ui.comboBox_F_Frame->currentIndex();
	int nChannelNum = ui.comboBox_ChanNo->currentIndex();
	int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	nTmpFPS = min(nTmpFPS, nFPS);

	int nBitrate = STREAM_CODE_VALUE[iResolution][iQuality - 1] * (iGOP * nTmpFPS + IFRAME_EQ_PFRAME - 1) / (iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
	SetComBoxCurSel(ui.comboBox_F_Stream, nBitrate);
	if (m_bMultiStream)
	{

		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			SDK_MEDIA_FORMAT &dstExtraFmt = m_allData.dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;
			vfExFormat.nBitRate = nBitrate;
			vfExFormat.iQuality = iQuality;
		}
		else
		{
			SDK_MEDIA_FORMAT &dstExtraFmt = m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;
			vfExFormat.nBitRate = nBitrate;
			vfExFormat.iQuality = iQuality;
		}
	}
	else
	{
		SDK_MEDIA_FORMAT &dsCombFmt = m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0];
		SDK_VIDEO_FORMAT &vfCombFormat = dsCombFmt.vfFormat;
		vfCombFormat.nBitRate = nBitrate;
		vfCombFormat.iQuality = iQuality;
	}

}

BOOL JLConfigSetting::SetComBoxCurSel(QComboBox *pComboBox, DWORD dwData)
{
	if (!pComboBox)
	{
		return FALSE;
	}

	int nCount = pComboBox->count();
	for (int i = 0; i < nCount; i++)
	{
		if (pComboBox->currentIndex() == dwData)
		{
			pComboBox->addItem(QString::number(i));
			return TRUE;
		}
	}

	return FALSE;
}

void JLConfigSetting::on_comboBox_F_Resolution_activated(int index)
{
	int nChannelNum = ui.comboBox_ChanNo->currentIndex();
	if (m_bMultiStream)
	{
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			DWORD lFreePower = m_pEncodeAbility.iMaxEncodePower;
			int nChannelCount = m_DevAttribute.deviveInfo.byChanNum;
			DWORD lAvrPower = lFreePower / nChannelCount;

			SDK_MEDIA_FORMAT &dstMainFmt = m_allData.dstMainFmt;
			SDK_VIDEO_FORMAT &vfFormat = dstMainFmt.vfFormat;

			SDK_MEDIA_FORMAT &dstExtraFmt = m_allData.dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;

			int nCurFrame = vfExFormat.nFPS;
			int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
			int nExResolution = 0;
			int nExFPS = 0;
			if (dstMainFmt.bVideoEnable)
			{
				nExResolution = m_resolution[vfFormat.iResolution].dwSize;
				nExFPS = vfFormat.nFPS;
			}
			DWORD dwExpandEnable = nExResolution * nExFPS;
			int nMaxFrame = 0;
			if (lAvrPower - dwExpandEnable <= 0)
			{
				ui.checkBox_F_Video->setCheckState(Qt::Unchecked);
				return;
			}
			lAvrPower = lAvrPower - dwExpandEnable;

			SelchangeComboResolution(m_allData.dstExtraFmt, EXPAND_STREAM, lAvrPower);
			AllStructToWinData(0, &m_allData, MAIN_STREAM);
			AllStructToWinData(0, &m_allData, EXPAND_STREAM);
		}
		else
		{
			DWORD lFreePower = 0;
			if (m_pEncodeAbility.iChannelMaxSetSync)
			{

				lFreePower = (m_pEncodeAbility.iMaxEncodePower - GetMainUsed()) / m_DevAttribute.deviveInfo.byChanNum;
			}
			else
			{

				lFreePower = GetFreeDspPower(nChannelNum);
				lFreePower = lFreePower - GetUsedEnable(ui.comboBox_M_Resolution, ui.comboBox_M_Frame, ui.checkBox_M_Video);
			}
			SelchangeComboResolution(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt, EXPAND_STREAM, lFreePower);
			if (m_pEncodeAbility.iChannelMaxSetSync)
			{
				for (int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i++)
				{
					if (i != nChannelNum)
					{
						m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.iResolution =
							m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt.vfFormat.iResolution;
						m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.nFPS =
							m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt.vfFormat.nFPS;
					}
				}
			}
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
		}
	}
	else if (m_bCombineEncode)
	{

		SelchangeComboResolution(m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0], COMBINE_STREAM, 0);
		SDK_CONFIG_ENCODE_SIMPLIIFY EncodeSimp;
		memcpy(&EncodeSimp.dstExtraFmt, &m_CmbEncodeCfg.vEncodeConfigAll[0].dstExtraFmt, sizeof(SDK_MEDIA_FORMAT));
		memcpy(&EncodeSimp.dstMainFmt, &m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt, sizeof(SDK_MEDIA_FORMAT));
		CombineStructToWinData(0, &EncodeSimp, COMBINE_STREAM);
	}
}

void JLConfigSetting::SelchangeComboResolution(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType, DWORD dwPower)
{
	int nChannelNum = ui.comboBox_ChanNo->currentIndex();
	int nCurFrame = GetComboBoxData(Control[nEncodeType][CONTROL_FRAME]);
	int iResolution = GetComboBoxData(Control[nEncodeType][CONTROL_RESOLUTION]);
	int iQuality = GetComboBoxData(Control[nEncodeType][CONTROL_QUALITY]) - 1;


	SDK_VIDEO_FORMAT &vfFormat = dstFormat.vfFormat;
	int nMaxFrame = 0;
	if (nEncodeType == COMBINE_STREAM)
	{
		nMaxFrame = (0 == m_nVideoStandard) ? 25 : 30;
	}
	else
	{
		nMaxFrame = GetMaxFrame(iResolution, dwPower);
	}
	nCurFrame = min(nCurFrame, nMaxFrame);
	int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	vfFormat.iResolution = iResolution;
	vfFormat.nFPS = nCurFrame;
	vfFormat.nBitRate =
		STREAM_CODE_VALUE[iResolution][iQuality] * (vfFormat.iGOP * nCurFrame + IFRAME_EQ_PFRAME - 1) / (vfFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
}

int JLConfigSetting::GetMaxFrame(int nResolution, long lFreePower)
{
	int nTempRate = lFreePower / m_resolution[nResolution].dwSize;
	if (0 == m_nVideoStandard)
	{
		if (nTempRate > 25)
		{
			nTempRate = 25;
		}
	}
	else
	{
		if (nTempRate > 30)
		{
			nTempRate = 30;
		}
	}
	return nTempRate;
}

DWORD JLConfigSetting::GetUsedEnable(QComboBox* nResID, QComboBox* nFrameID, QCheckBox* nEnableID)
{
	if (!nEnableID->checkState() || !m_bMultiStream)
	{
		return 0;
	}

	int nData = nResID->currentIndex();
	QString str;
	str = nFrameID->currentText();
	int nFrame = atoi(str.toLatin1().data());

	return m_resolution[nData].dwSize * nFrame;
}

void JLConfigSetting::on_comboBox_F_Stream_activated(int index)
{
	int nChannelNum = ui.comboBox_ChanNo->currentIndex();
	if (m_bMultiStream)
	{
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			SDK_MEDIA_FORMAT &dstMainFmt = m_allData.dstMainFmt;
			SDK_VIDEO_FORMAT &vfFormat = dstMainFmt.vfFormat;
			vfFormat.nBitRate = GetComboBoxData("comboBox_F_Stream");
		}
		else
		{

			SDK_MEDIA_FORMAT &dstExtraFmt = m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;
			vfExFormat.nBitRate = GetComboBoxData("comboBox_F_Stream");
		}
	}
	else
	{
		SDK_MEDIA_FORMAT &dsCombFmt = m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0];
		SDK_VIDEO_FORMAT &vfCombFormat = dsCombFmt.vfFormat;
		vfCombFormat.nBitRate = GetComboBoxData("comboBox_F_Stream");
	}
}

void JLConfigSetting::on_comboBox_F_BitControl_clicked(int index)
{
	int nChannelNum = ui.comboBox_ChanNo->currentIndex();
	if (m_bMultiStream)
	{

		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			SelchangeComboBitcontrol(m_allData.dstExtraFmt, EXPAND_STREAM);
			AllStructToWinData(0, &m_allData, EXPAND_STREAM);
		}
		else
		{
			SelchangeComboBitcontrol(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt, EXPAND_STREAM);
			NormalStructToWinData(0, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
		}
	}
	else if (m_bCombineEncode)
	{
		SelchangeComboBitcontrol(m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0], COMBINE_STREAM);
		SDK_CONFIG_ENCODE_SIMPLIIFY EncodeSimp;
		memcpy(&EncodeSimp.dstExtraFmt, &m_CmbEncodeCfg.vEncodeConfigAll[0].dstExtraFmt, sizeof(SDK_MEDIA_FORMAT));
		memcpy(&EncodeSimp.dstMainFmt, &m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt, sizeof(SDK_MEDIA_FORMAT));
		CombineStructToWinData(0, &EncodeSimp, COMBINE_STREAM);
	}
}

void JLConfigSetting::SelchangeComboBitcontrol(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType)
{
	int iResolution = GetComboBoxData(Control[nEncodeType][CONTROL_RESOLUTION]);
	int iQuality = GetComboBoxData(Control[nEncodeType][CONTROL_QUALITY]) - 1;
	int iGOP = GetComboBoxData(Control[nEncodeType][CONTROL_GOP]);
	int nTmpFPS = GetComboBoxData(Control[nEncodeType][CONTROL_FRAME]);
	int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	nTmpFPS = min(nTmpFPS, nFPS);

	dstFormat.vfFormat.iBitRateControl = GetComboBoxData(Control[nEncodeType][CONTROL_BITCONTROL]);
	dstFormat.vfFormat.nBitRate = STREAM_CODE_VALUE[iResolution][iQuality] * (iGOP * nTmpFPS + IFRAME_EQ_PFRAME - 1) / (iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
	if (dstFormat.vfFormat.iBitRateControl)
	{
		ui.tabWidget->findChild<QComboBox *>(Control[nEncodeType][CONTROL_BIT_RATE])->setEnabled(false);
	}
	else
	{
		ui.tabWidget->findChild<QComboBox *>(Control[nEncodeType][CONTROL_BIT_RATE])->setEnabled(TRUE && dstFormat.bVideoEnable);
	}

	ui.tabWidget->findChild<QComboBox *>(Control[nEncodeType][CONTROL_QUALITY])->setEnabled(dstFormat.vfFormat.iBitRateControl && dstFormat.bVideoEnable);

	
}

void JLConfigSetting::on_comboBox_M_Resolution_clicked(int index)
{
	int nChannelNum = ui.comboBox_ChanNo->currentIndex();
	if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
	{
		DWORD lFreePower = m_pEncodeAbility.iMaxEncodePower;
		DWORD lAvrPower = lFreePower / nChannelNum;
		SDK_MEDIA_FORMAT &dstMainFmt = m_allData.dstMainFmt;
		SDK_VIDEO_FORMAT &vfFormat = dstMainFmt.vfFormat;


		SDK_MEDIA_FORMAT &dstExtraFmt = m_allData.dstExtraFmt;
		SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;

		int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
		int nResolution = vfFormat.iResolution;
		int nExResolution = 0;
		int nExFPS = 0;
		if (m_bMultiStream && dstExtraFmt.bVideoEnable)
		{
			nExResolution = m_resolution[vfExFormat.iResolution].dwSize;
			nExFPS = vfExFormat.nFPS;
		}
		DWORD dwExpandEnable = nExResolution * nExFPS;
		int nMaxFrame = 0;
		if (lAvrPower - dwExpandEnable <= 0)
		{
			ui.tabWidget->findChild<QCheckBox *>("checkBox_F_Video")->setEnabled(false);
			return;
		}
		lAvrPower = lAvrPower - dwExpandEnable;

		SelchangeComboResolution(m_allData.dstMainFmt, MAIN_STREAM, lAvrPower);
		AllStructToWinData(0, &m_allData, MAIN_STREAM);
		AllStructToWinData(0, &m_allData, EXPAND_STREAM);
	}
	else
	{
		DWORD lFreePower = 0;
		if (m_pEncodeAbility.iChannelMaxSetSync)
		{

			lFreePower = (m_pEncodeAbility.iMaxEncodePower - GetExpandUsed()) / m_DevAttribute.deviveInfo.byChanNum;
		}
		else
		{
			lFreePower = GetFreeDspPower(nChannelNum);
			lFreePower = lFreePower - GetUsedEnable(ui.comboBox_F_Resolution, ui.comboBox_F_Frame, ui.checkBox_F_Video);
		}
		SelchangeComboResolution(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt, MAIN_STREAM, lFreePower);
		if (m_pEncodeAbility.iChannelMaxSetSync)
		{
			for (int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i++)
			{
				if (i != nChannelNum)
				{
					m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.iResolution =
						m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt.vfFormat.iResolution;
					m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.nFPS =
						m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt.vfFormat.nFPS;
				}
			}
		}
		NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
		NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
	}
}

void JLConfigSetting::on_btnRegionl_clicked()
{
	//ui.stackedWidget->setCurrentIndex(0);
	initRegionl();

}

void JLConfigSetting::initRegionl()
{
	m_pAnalyseVideoAreaDlg = new AnalyseVideoAreaDlg();
	if (ui.gridLayout_Main->count() > 0)
	{
		QWidget *widget = ui.gridLayout_Main->itemAt(0)->widget();
		ui.gridLayout_Main->removeWidget(widget);
		delete widget;
	}

	ui.gridLayout_Main->addWidget(m_pAnalyseVideoAreaDlg);
	OnCbnSelchangeComChannel();
}

void JLConfigSetting::on_comboBox_Regionl_activated(int index)
{
	int lSelChannel = index;
	if (lSelChannel < 0)
	{
		m_lSelChannel = 0;
		SaveChannelParam(m_lSelChannel);
	}
	on_btnRegionlClear_clicked();
	m_lSelChannel = lSelChannel;
	GetDevParam();
	ShowChannelParam(lSelChannel);
	m_pAnalyseVideoAreaDlg->StopPlay();
	m_pAnalyseVideoAreaDlg->OpenPlay(m_lSelChannel, m_lStreamType,m_LoginID);
}
void JLConfigSetting::OnCbnSelchangeComChannel()
{
	int lSelChannel = ui.comboBox_Regionl->currentIndex();
	if (lSelChannel < 0)
	{
		m_lSelChannel = 0;
		SaveChannelParam(m_lSelChannel);
	}
	else
	{
		SaveChannelParam(m_lSelChannel);
	}
	on_btnRegionlClear_clicked();
	m_lSelChannel = lSelChannel;
	GetDevParam();
	ShowChannelParam(lSelChannel);
	m_pAnalyseVideoAreaDlg->StopPlay();
	m_pAnalyseVideoAreaDlg->OpenPlay(m_lSelChannel, m_lStreamType,m_LoginID);
}

long JLConfigSetting::SaveChannelParam(long lChannel)
{
	m_pFaShielded->bEnable = ui.checkBox_Regionl->checkState();
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
void JLConfigSetting::on_btnRegionlClear_clicked()
{
	memset(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate, 0, sizeof(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate));//清除
	memset(m_pFaShielded, 0, sizeof(SDK_FA_VI_SHIELDED));
}

long JLConfigSetting::GetDevParam()
{
	memset(m_pFaShielded, 0, sizeof(SDK_FA_VI_SHIELDED));
	memset(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate, 0, sizeof(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate));//清除

	DWORD dwRetLen = 0;
	int nWaitTime = 10000;

	BOOL bSuccess = VideoNet_GetDevConfig(m_LoginID, E_SDK_CFG_SMARTFACE_AREASHIELDED, m_lSelChannel,
		(char *)m_pFaShielded, sizeof(SDK_FA_VI_SHIELDED), &dwRetLen, nWaitTime);
	if (!bSuccess)
	{
		DWORD dwRetError = VideoNet_GetLastError();
		OutputDebugString("CAnalyseShelterDetDlg::GetDevParam failed!\r\n");
	}
	return 0;
}

long JLConfigSetting::ShowChannelParam(long lChannel)
{
	ui.checkBox_Regionl->setChecked(m_pFaShielded->bEnable);

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
			//m_pAnalyseVideoAreaDlg->m_LineCoordinate[ix].nArrowDirection = m_pFaShielded.smRossLineDetect[lChannel].direction[ix];
			//m_pAnalyseVideoAreaDlg->m_nArrowDirection = m_pFaShielded.smRossLineDetect[lChannel].direction[ix];

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

void JLConfigSetting::on_btnRegionlAll_clicked()
{
	memset(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate, 0, sizeof(m_pAnalyseVideoAreaDlg->m_RectangleCoordinate));//清除

	memset(m_pFaShielded, 0, sizeof(SDK_FA_VI_SHIELDED));
	::SendMessage((HWND)m_pAnalyseVideoAreaDlg->winId(), WM_LBUTTONDOWN, 0, MAKELONG(0, 0));
	::SendMessage((HWND)m_pAnalyseVideoAreaDlg->winId(), WM_LBUTTONUP, 0, MAKELONG(704, 576));
}

void JLConfigSetting::on_btnRegionlSet_clicked()
{
	if (m_bStartCheck)
	{
		m_bStartCheck = FALSE;
		EnableWindowAnalyse(m_bStartCheck);
	}
	else
	{
		m_bStartCheck = TRUE;
		EnableWindowAnalyse(m_bStartCheck);
	}

	m_bStartAreaSet = TRUE;
}

long JLConfigSetting::StopPlay()
{
	m_pAnalyseVideoAreaDlg->StopPlay();
	return 0;
}

long JLConfigSetting::SetDevParam()
{
	SaveChannelParam(m_lSelChannel);
	if (0 == m_LoginID)
	{
		myHelper::ShowMessageBoxWarning("保存配置数据失败!\r\n");
		return -1;
	}

	if (m_lSelChannel == m_nChannelNum) //
	{

	}
	else
	{
		long bResult = 0;
		int nWaitTime = 10000;
		bResult = VideoNet_SetDevConfig(m_LoginID, E_SDK_CFG_SMARTFACE_AREASHIELDED, m_lSelChannel,
			(char *)m_pFaShielded, sizeof(SDK_FA_VI_SHIELDED), nWaitTime);
		if (VIDEONET_SUCCESS != bResult)
		{
			myHelper::ShowMessageBoxWarning("保存配置数据成功!\r\n");
			return -1;
		}
	}
	return 0;
}

void JLConfigSetting::on_btnRegionlSave_clicked()
{
	SetDevParam();
}