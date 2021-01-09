
#include "Device/JLNDevice.h"
#include <Windows.h>
#include <assert.h>
#include <iostream>
#include <QMutex>
#include <QDebug>
#include <stdio.h>
#include <QDir>
#include <QFile>
#include "capacityset.h"
#include "AnalyseVideoAreaDlg.h"
#include <QMessageBox>
#include <QCoreApplication>
#include "Alaw_encoder.c"
#include "client.h"

#define RUN_LOG_FILE "sVMS"
#define  JVT_LONG LONG 
#define  STOP_START 100
#define MAX_JL_PLAYER 256



extern QMutex g_mutexDevObj;
extern std::map<LONG, CJLNDevice *> g_mapDevObj;
extern Client* g_pInstance;

st_playerInfo g_JlnPlayerInfo[MAX_JL_PLAYER] = { 0 };
std::map<HANDLE, int> g_mapJlnPlayerInfo;

AnalyseVideoAreaDlg* g_pAnalyseDlg = NULL;

typedef struct
{
	UCHAR rsv;//0x00;
	UCHAR code;//0x01
	UCHAR len; //80的整数倍 A0 
	UCHAR seq;//0~255;  00
}hisi_audio_head_t;

static S32  GetPortId(HWND hwnd)
{
	int iPort = -1;
	g_mutexDevObj.lock();
	for (int i = 0; i < MAX_JL_PLAYER; i ++)
	{
		if (g_JlnPlayerInfo[i].hPlayWnd == hwnd)
		{
			iPort = i;
			break;
		}
	}
	g_mutexDevObj.unlock();
	return iPort;
}

CJLNDevice::CJLNDevice()
	: m_nLoginError(0)
	//, m_nLoginError(NULL)
{
	memset(m_PTZCmdMap, 0, sizeof(m_PTZCmdMap));
	m_hwnd = NULL;
	m_PTZCmdMap[eLIGHT_PWRON] = EXTPTZ_LAMP_ON;
	m_PTZCmdMap[eWIPER_PWRON] = EXTPTZ_LAMP_OFF;
	m_PTZCmdMap[eFAN_PWRON] = EXTPTZ_AUXIOPEN;
	m_PTZCmdMap[eHEATER_PWRON] = EXTPTZ_AUXIOPEN;
	m_PTZCmdMap[eAUX_PWRON] = EXTPTZ_AUXIOPEN;
	m_PTZCmdMap[eSET_PRESET] = EXTPTZ_POINT_SET_CONTROL;
	m_PTZCmdMap[eCLE_PRESET] = EXTPTZ_POINT_DEL_CONTROL;
	m_PTZCmdMap[eZOOM_IN] = PTZ_ZOOM_IN;
	m_PTZCmdMap[eZOOM_OUT] = PTZ_ZOOM_OUT;
	m_PTZCmdMap[eFOCUS_NEAR] = PTZ_FOCUS_NEAR;
	m_PTZCmdMap[eFOCUS_FAR] = PTZ_FOCUS_FAR;
	m_PTZCmdMap[eIRIS_OPEN] = PTZ_IRIS_OPEN;
	m_PTZCmdMap[eIRIS_CLOSE] = PTZ_IRIS_CLOSE;
	m_PTZCmdMap[eTILT_UP] = PTZ_TILT_UP;
	m_PTZCmdMap[eTILT_DOWN] = PTZ_TILT_DOWN;
	m_PTZCmdMap[ePAN_LEFT] = PTZ_PAN_LEFT;
	m_PTZCmdMap[ePAN_RIGHT] = PTZ_PAN_RIGHT;
	m_PTZCmdMap[ePAN_AUTO] = PTZ_PAN_AUTO;
	m_PTZCmdMap[eRUN_CRUISE] = EXTPTZ_POINT_LOOP_CONTROL;
	m_PTZCmdMap[eRUN_SEQ] = EXTPTZ_POINT_LOOP_CONTROL;
	m_PTZCmdMap[eSTOP_SEQ] = EXTPTZ_POINT_STOP_LOOP_CONTROL;
	m_PTZCmdMap[eGOTO_PRESET] = EXTPTZ_POINT_MOVE_CONTROL;
	m_lUserLoginID = 0;
	m_lDevType = 0;
	m_hConnectThread = NULL;
	m_bReconnecting = FALSE;
	m_nChannelNum = 0;
	m_hAlarmConfigThread = NULL;
	m_bStopAlarmConfig = FALSE;
	m_bSupportNew = FALSE;
	m_bBrush = FALSE;
	m_bLight = FALSE;
	m_pTalkDecodeBuf = NULL;
	m_lTalkHandle = -1;
	for (int i = 0; i < MAX_CHANNEL; i++)
	{
		m_lSnapID[i] = -1;
	}
	m_lImExID = -1; 
	m_lUpgradeHandle = -1;
	m_hImportWaitEvent = NULL;
	m_hExsitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_nErrorCode = 0;
	m_pVoid = NULL;
	memset(&m_stDevInfo, 0, sizeof(VIDEONET_DEVICEINFO));
	InitializeCriticalSection(&m_lockSubOperation);
	//m_pszLoginError = new char[ERROR_STRING_LEN];
	//memset(m_pszLoginError, 0, ERROR_STRING_LEN);
	m_strLoginError == NULL;
}

CJLNDevice::~CJLNDevice()
{	
	if (m_hExsitEvent)
	{
		SetEvent(m_hExsitEvent);
		CloseHandle(m_hExsitEvent);
		m_hExsitEvent = NULL;
	}
	m_bReconnecting = FALSE;
	m_bStopAlarmConfig = TRUE;

	std::map<LONG, CJLNDevice *>::iterator dev_iter;
	g_mutexDevObj.lock();
	dev_iter = g_mapDevObj.find(m_lUserLoginID);
	if (dev_iter != g_mapDevObj.end())
	{
		g_mapDevObj.erase(dev_iter);
	}
	g_mutexDevObj.unlock();

	Logout();

	if (NULL != m_hAlarmConfigThread)
	{
		WaitForSingleObject(m_hAlarmConfigThread, INFINITE);
		CloseHandle(m_hAlarmConfigThread);
		m_hAlarmConfigThread = NULL;
	}
	if (m_hImportWaitEvent)
	{
		CloseHandle(m_hImportWaitEvent);
		m_hImportWaitEvent = NULL;
	}
	if (m_hConnectThread)
	{
		WaitForSingleObject(m_hConnectThread, INFINITE);
	}
	/*if (m_pszLoginError)
	{
		delete m_pszLoginError;
		m_pszLoginError = NULL;
	}*/
	DeleteCriticalSection(&m_lockSubOperation);
}


int __stdcall RealDataCallBack_V2(JVT_LONG lRealHandle, const PACKET_INFO_EX *pFrame, JVT_DWORD dwUser)
{
	int iPort = dwUser;
	bool ret = VideoPlayer_InputData(iPort, (unsigned char*)pFrame->pPacketBuffer, pFrame->dwPacketSize);
	if (g_pAnalyseDlg)
	{
		g_pAnalyseDlg->m_lVideoAreaWidth = pFrame->uWidth;
		g_pAnalyseDlg->m_lVdieoAreaHeight = pFrame->uHeight;
	}
	return 1;
}

void CALLBACK CJLNDevice::videoInfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf, LONG nSize, LONG nUser)
{
	CJLNDevice *pThis = (CJLNDevice*)nUser;
	//收到信息帧, 0x03 代表GPRS信息
	if (nType == 0x03)
	{
		pThis->m_strInfoFrame[nPort] = pBuf;
	}
}

//void CALLBACK drawOSDCall(LONG nPort, HDC hDc, LONG nUser)
//{
//	CJLNDevice* pThis = (CJLNDevice*)nUser;
//	pThis->drawOSD(nPort, hDc);
//}

void CALLBACK CJLNDevice::VideoOnDrawCallback(LONG nPort, HDC hdc, LONG nUser)
{
	if (g_pAnalyseDlg)
	{
		g_pAnalyseDlg->OnDraw(nPort, hdc);
	}
}

void CJLNDevice::drawOSD(LONG nPort, HDC hDc)
{
	if (m_strInfoFrame[nPort] != "")
	{
		HFONT oldfont;
		oldfont = (HFONT)::GetCurrentObject(hDc, OBJ_FONT);


		//改变字体颜色
		::SetTextColor(hDc, RGB(255, 0, 0));

		//更改字体
		LOGFONT lf;
		::GetObject(oldfont, sizeof(lf), &lf);
		strcpy(lf.lfFaceName, "Arial");
		lf.lfWeight = FW_BOLD;
		HFONT out_ft;		//创建的字体对象
		out_ft = ::CreateFontIndirect(&lf);

		::SelectObject(hDc, out_ft);

		TextOut(hDc, 10, 10, "testtesttest", strlen("testtesttest"));

		::SelectObject(hDc, oldfont);
	}
}

void __stdcall pProc(LONG nPort, LPCSTR pBuf, LONG nSize, LONG nWidth, LONG nHeight, LONG nStamp, LONG nType, LONG nUser)
{

}


S32 CJLNDevice::OpenChannel(U32 nChannel, U32 nStream, HWND hwnd, int nWndNum, void* pVoid)
{
	if (0 == m_lUserLoginID)
	{
		return -1;		
	}

	JVT_LONG lPlayhandle = -1;

	g_mutexDevObj.lock();
	int iPort = 0;
	for (iPort = 0; iPort < MAX_JL_PLAYER; iPort++)
	{
		if (!g_JlnPlayerInfo[iPort].bUsed)
		{
			break;
		}
	}
	g_mutexDevObj.unlock();
	
	if (iPort >= MAX_JL_PLAYER)
	{
		mlog(LOG_ERR, "OpenChannel Port over max vaule  longID = %d\n", m_lUserLoginID);
		CloseChannel(hwnd);
		return -1;
	}

	//open decoder
	BYTE byFileHeadBuf;
	if (VideoPlayer_OpenStream(iPort, &byFileHeadBuf, 1, SOURCE_BUF_MIN * 50))
	{
		//设置信息帧回调
		VideoPlayer_SetInfoFrameCallBack(iPort, videoInfoFramCallback, (DWORD)this);

		if (pVoid)
		{
			m_pVoid = pVoid;
			//设置osd叠加回调
			VideoPlayer_RigisterDrawFun(iPort, VideoOnDrawCallback, (DWORD)this);//用于画图
		}

		VideoPlayer_SetStreamOpenMode(iPort, STREAME_REALTIME);

		if (VideoPlayer_Play(iPort, hwnd))
		{
			VideoPlayer_SetDisplayCallBack(iPort, pProc, (LONG)this);
		}
		else
		{
			mlog(LOG_ERR, "VideoPlayer_OpenStream  failed  longID = %d channel = %d\n", m_lUserLoginID, nChannel);
		}
	}


	if (-1 == iPort)
	{
		mlog(LOG_ERR, "OpenChannel PlaydecHandle failed  longID = %d channel = %d\n", m_lUserLoginID, nChannel);
		VideoPlayer_CloseStream(iPort);
		return -2;
	}

	VIDEONET_CLIENTINFO playstru = { 0 };

	playstru.nChannel = nChannel - 1;
	playstru.nStream = nStream;
	playstru.nMode = 0;
	lPlayhandle = VideoNet_RealPlay(m_lUserLoginID, &playstru);
	if (lPlayhandle <= 0)
	{
		DWORD dwErr = VideoNet_GetLastError();
		mlog(LOG_ERR, "VideoNet_RealPlay failed  ip addr = %s,DevName = %s,channel= %d,longID = %d,error = %d\n"
			, m_pDevInfo->szIpAddr, m_pDevInfo->szDevName, nChannel, m_lUserLoginID, dwErr);

		if (iPort != -1)
		{
			VideoPlayer_CloseStream(iPort);
			VideoPlayer_Stop(iPort);
		}
		return -1;
	}
	else
	{
		//VideoNet_MakeKeyFrame(m_lUserLoginID, playstru.nChannel, nStream);

		VideoNet_SetRealDataCallBack_V2(lPlayhandle, RealDataCallBack_V2, iPort);
	}

	g_mutexDevObj.lock();
	/*****************************************/
	g_JlnPlayerInfo[iPort].bUsed = TRUE;
	g_JlnPlayerInfo[iPort].port = iPort;
	g_JlnPlayerInfo[iPort].nDevID = m_pDevInfo->nDevId;
	g_JlnPlayerInfo[iPort].nChannel = nChannel;
	g_JlnPlayerInfo[iPort].nStreamType = nStream;
	g_JlnPlayerInfo[iPort].hPlayWnd = hwnd;
	g_JlnPlayerInfo[iPort].nWndNum = nWndNum;
	g_JlnPlayerInfo[iPort].lPlayHandle = lPlayhandle;
	/*****************************************/

	g_mutexDevObj.unlock();
	return lPlayhandle;
}

S32 CJLNDevice::ChangeChannelStream(HWND hwnd, U32 nStream)
{
	int nChannel = 0;
	int iPort = GetPortId(hwnd);
	if (iPort != -1)
	{
		g_mutexDevObj.lock();
		nChannel = g_JlnPlayerInfo[iPort].nChannel;
		g_mutexDevObj.unlock();

		CloseChannel(hwnd);
		return OpenChannel(nChannel, nStream, hwnd);
	}
	return -1;
}

S32 CJLNDevice::CloseChannel(HWND hwnd)
{
	int iPort = GetPortId(hwnd);

	if (iPort != -1)
	{
		if (g_JlnPlayerInfo[iPort].lPlayHandle > 0)
		{
			VideoNet_DelRealDataCallBack_V2(g_JlnPlayerInfo[iPort].lPlayHandle, RealDataCallBack_V2, iPort);
			VideoNet_StopRealPlay(g_JlnPlayerInfo[iPort].lPlayHandle);
		}

		VideoPlayer_CloseStream(iPort);
		VideoPlayer_Stop(iPort);

		g_mutexDevObj.lock();
		memset(&g_JlnPlayerInfo[iPort], 0, sizeof(st_playerInfo));
		g_mutexDevObj.unlock();
	}

	return TRUE;
}

S32 CJLNDevice::PtzCtrl(HWND hwnd, int nPtzType, U32 nStop, U32 nSpeed)
{
	if (m_lUserLoginID == 0)
		return -1;
	S32 bRet = 0;
	int iPort = GetPortId(hwnd);
	if (iPort == -1)
	{
		return -1;
	}
	int nChannel = g_JlnPlayerInfo[iPort].nChannel;
	//调用预置位时nSpeed代表预置位号
	if (nPtzType == EXTPTZ_POINT_SET_CONTROL || nPtzType == EXTPTZ_POINT_MOVE_CONTROL)
	{
		if (!nStop)
		{
			bRet = VideoNet_PTZControlEx(m_lUserLoginID, 0, nPtzType, nSpeed, 0, 0, nStop);
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		if (nPtzType == EXTPTZ_LAMP_ON && m_bLight)
		{
			nPtzType = EXTPTZ_LAMP_OFF;

		}
		else if (nPtzType == EXTPTZ_BRUSH_ON && m_bBrush)
		{
			nPtzType = EXTPTZ_BRUSH_OFF;
		}

		bRet = VideoNet_PTZControl(m_lUserLoginID, nChannel - 1, m_PTZCmdMap[nPtzType], nStop, nSpeed);
		if (bRet)
		{
			if (nPtzType == EXTPTZ_LAMP_ON || nPtzType == EXTPTZ_LAMP_OFF)
			{
				m_bLight = !m_bLight;
			}
			else if (nPtzType == EXTPTZ_BRUSH_ON || nPtzType == EXTPTZ_BRUSH_OFF)
			{
				m_bBrush = !m_bBrush;
			}
		}
	}

	return bRet;
}

S32 CJLNDevice::Login()
{
	long lRet = -1;

	if (m_lUserLoginID > 0)
	{
		return m_lUserLoginID;
	}

	if (m_lUserLoginID <= 0)
	{
		m_nLoginError = 0;
		if (IsIPAvailed(m_pDevInfo->szIpAddr))
		{
			m_lUserLoginID = VideoNet_Login(m_pDevInfo->szIpAddr, m_pDevInfo->nPort, m_pDevInfo->szLoginName, m_pDevInfo->szPassword, &m_stDevInfo, &m_nLoginError);
		}
		else
		{
			m_lUserLoginID = VideoNet_Login_P2P(m_pDevInfo->szIpAddr, 0, m_pDevInfo->szLoginName, m_pDevInfo->szPassword, &m_stDevInfo, &m_nLoginError);
		}

		if (m_lUserLoginID <= 0)
		{

			lRet = VideoNet_GetLastError();  //VIDEONET_PASSWORD_NOT_VALID
			mlog(LOG_ERR, "devcie login failed error code = %d,ip addr = %s,port = %d,UserName = %s,Pwd = %s\n", lRet, m_pDevInfo->szIpAddr, m_pDevInfo->nPort, m_pDevInfo->szLoginName, m_pDevInfo->szPassword);
			return lRet;
		}

		m_lDevType = m_stDevInfo.deviceTye;
		m_nLoginError = 1;
		//VideoNet_SetupAlarmChan(m_lUserLoginID);

		//判断是否支持新协议
		if (strcmp(m_stDevInfo.sProtocol, "v2.0") == 0)
		{
			m_bSupportNew = TRUE;
		}

		mlog(LOG_INFO, "devcie login success  ip addr = %s,port = %d,UserName = %s,Pwd = %s,User loginID = %d\n",
			m_pDevInfo->szIpAddr, m_pDevInfo->nPort, m_pDevInfo->szLoginName, m_pDevInfo->szPassword, m_lUserLoginID);
		if (m_stDevInfo.iDigChannel > 0)
		{
			m_nChannelNum = m_stDevInfo.iDigChannel;
		}
		else
		{
			m_nChannelNum = m_stDevInfo.byChanNum + m_stDevInfo.iDigChannel;
		}

		m_bStopAlarmConfig = TRUE;
		if (NULL != m_hAlarmConfigThread)
		{
			WaitForSingleObject(m_hAlarmConfigThread, INFINITE);
			CloseHandle(m_hAlarmConfigThread);
			m_hAlarmConfigThread = NULL;
		}
		m_bStopAlarmConfig = FALSE;
		//m_hAlarmConfigThread = ::CreateThread(NULL, 0, AlarmConfigThread, this, 0, NULL);
		
		//自动开启比对
		if (g_pInstance->m_pDlgSystemSet->m_ClientCfg.nAutoSnap)
		{
			for (int i = 0; i < m_nChannelNum; i++)
			{
				StartSnapLink(m_lUserLoginID, i);
			}
		}
	}


	g_mutexDevObj.lock();
	g_mapDevObj[m_lUserLoginID] = this;
	g_mutexDevObj.unlock();

	return m_lUserLoginID;
}

S32 CJLNDevice::Logout()
{
	for (int i = 0; i < MAX_CHANNEL; i++)
	{
		if (m_lSnapID[i] > 0)
		{
			StopSnapLink(i);
		}
	}
	if (m_lImExID > 0)
	{
		StopImportAndExport();
	}


	if (m_lUserLoginID == 0 /*|| !m_mapPlayHandle.empty() || m_bRecvAlarm*/)
	{
		return 0;
	}
	QString strLog = NULL;

	long lRet = VideoNet_Logout(m_lUserLoginID);
	if (lRet == VIDEONET_SUCCESS)
	{
		mlog(LOG_ERR, "VideoNet_Logout success  ip addr = %s,DevName = %s,longID = %d\n"
			, m_pDevInfo->szIpAddr, m_pDevInfo->szDevName, m_lUserLoginID);
		m_nLoginError = 0;
		g_mutexDevObj.lock();
		g_mapDevObj.erase(m_lUserLoginID);
		g_mutexDevObj.unlock();
		m_lUserLoginID = 0;
	}
	else
	{
		m_nLoginError = VideoNet_GetLastError();
		mlog(LOG_ERR, "VideoNet_Logout failed  ip addr = %s,DevName = %s,longID = %d,error = %d\n"
			, m_pDevInfo->szIpAddr, m_pDevInfo->szDevName, m_lUserLoginID, m_nLoginError);
	}
	return lRet;
}

S32 CJLNDevice::Reconnect()
{
	m_bReconnecting = TRUE;

	ConstractSubLink();
	OperateSubPlay(FALSE);

	Logout();
	if (!m_hConnectThread)
	{
		m_hConnectThread = ::CreateThread(NULL, 0, ReconnectThread, this, 0, NULL);
	}
	
	return 0;
}

DWORD WINAPI CJLNDevice::ReconnectThread(LPVOID lpParam)
{
	
	CJLNDevice* pDevice = (CJLNDevice*)lpParam;
	if (NULL == pDevice)
	{
		return -1;
	}
	pDevice->OnReconnect();
	return 0;
}

long CJLNDevice::OnReconnect()
{
	while (m_bReconnecting)
	{
		//重连
		if (WaitForSingleObject(m_hExsitEvent, 1000) == WAIT_OBJECT_0)
		{
			break;
		}
		
		if (0 == m_lUserLoginID)
		{
			Login();
		}

		if (m_lUserLoginID > 0)
		{
			if (m_listPlayInfo.size() <= 0)
			{
				m_bReconnecting = FALSE;
				break;
			}

			OperateSubPlay(TRUE);
		}
	}

	if (NULL != m_hConnectThread)
	{
		CloseHandle(m_hConnectThread);
		m_hConnectThread = NULL;
	}
	return 0;
}

void CJLNDevice::OperateSubPlay(BOOL bOpen)			//播放链路
{
	list<st_playerInfoSimple>::iterator iterPlay;
	JVT_LONG lRet = 0;
	char strLog[2048] = { 0 };
	SYSTEMTIME sysTime = { 0 };
	GetLocalTime(&sysTime);
	st_playerInfoSimple stPlayInfo = { 0 };

	//视频通道处理
	if (m_listPlayInfo.size() > 0)
	{
		for (iterPlay = m_listPlayInfo.begin(); iterPlay != m_listPlayInfo.end();)
		{
			stPlayInfo = *iterPlay;
			if (bOpen)
			{
				CompareEvent *custevent = new CompareEvent(CET_START_WATCH);
				custevent->setId(stPlayInfo.nWndNum);
				QApplication::postEvent(g_pInstance->m_pPreviewPro, custevent);
				iterPlay = m_listPlayInfo.erase(iterPlay);
				continue;
			}
			if (!bOpen)
			{
				stPlayInfo = *iterPlay;
				CloseChannel(stPlayInfo.hPlayWnd);
				CompareEvent *custevent = new CompareEvent(CET_STOP_WATCH);
				custevent->setId(stPlayInfo.nWndNum);
				QApplication::postEvent(g_pInstance->m_pPreviewPro, custevent);
			}
			iterPlay++;
		}
	}
}
void CJLNDevice::ConstractSubLink()		//保存子链路
{
	//记录播放信息
	g_mutexDevObj.lock();
	int iPort;
	for (iPort = 0; iPort < MAX_JL_PLAYER; iPort++)
	{
		if (g_JlnPlayerInfo[iPort].nDevID == m_pDevInfo->nDevId && NULL != g_JlnPlayerInfo[iPort].hPlayWnd)
		{
			st_playerInfoSimple stPlayInfoTemp;
			memset(&stPlayInfoTemp, 0, sizeof(stPlayInfoTemp));
			stPlayInfoTemp.bSaveStream = g_JlnPlayerInfo[iPort].bSaveStream;
			stPlayInfoTemp.bEnableAudio = g_JlnPlayerInfo[iPort].bEnableAudio;
			stPlayInfoTemp.nStreamType = g_JlnPlayerInfo[iPort].nStreamType;
			stPlayInfoTemp.nChannel = g_JlnPlayerInfo[iPort].nChannel;
			stPlayInfoTemp.hPlayWnd = g_JlnPlayerInfo[iPort].hPlayWnd;
			stPlayInfoTemp.bSpeak = g_JlnPlayerInfo[iPort].bSpeak;
			stPlayInfoTemp.nWndNum = g_JlnPlayerInfo[iPort].nWndNum;
			m_listPlayInfo.push_back(stPlayInfoTemp);
		}
	}
	g_mutexDevObj.unlock();
	//记录比对信息
}


static int __stdcall FaceImportExportCallback(JVT_LONG lSubFaceHandle, char *pBuffer, long lbufsize, SDK_FA_BLACKANDWHITELIST_CONFIG *pConfig, JVT_DWORD dwUser)
{
	CJLNDevice* pDevice = (CJLNDevice*)dwUser;
	pDevice->m_nErrorCode = pConfig->byErrorCode;
	SetEvent(pDevice->m_hImportWaitEvent);

	if (g_pInstance != NULL)
	{
		switch (pConfig->byOutMode)
		{
		case OUT_INDEX:
		case OUT_PICTURE:
		case OUT_PICTURE_COMP:
		case OUT_PICTURE_DEL:
		case OUT_PICTURE_DELALL:
			g_pInstance->m_pDlgExport->FaceCallBack(lSubFaceHandle, pBuffer, lbufsize, pConfig, dwUser);
			break;
		
		case IN_PICTURE_ADD_SNAP:	//导出黑白名单库中单张图片
	
			g_pInstance->m_pDlgExport->FaceCallBack_Import(lSubFaceHandle, pBuffer, lbufsize, pConfig, dwUser);
			break;
		}
	}
	return 0;
}

BOOL CJLNDevice::StopImportAndExport()
{
	if (m_bSupportNew)
	{
		StopListManagement();
	}
	else
	{
		if (m_lImExID > 0)
		{
			VideoNet_DeleteBlackAndWhiteListCallBack(m_lImExID, FaceImportExportCallback, (JVT_DWORD)this);
			VideoNet_StopSendBlackAndWhiteList(m_lImExID);
			m_lImExID = -1;
		}
	}
	return TRUE;
}

DWORD WINAPI CJLNDevice::AlarmConfigThread(LPVOID lpParam)
{
	CJLNDevice* pDevice = (CJLNDevice*)lpParam;
	if (NULL == pDevice)
	{
		return -1;
	}
	pDevice->OnAlarmConfig();
	return 0;
}

long CJLNDevice::OnAlarmConfig()
{
	char strLog[2048] = { 0 };

	time_t tmNow = time(NULL);
	struct tm tmLocal;
	tmLocal = *localtime(&tmNow);
	DWORD dwTickTime = GetTickCount();
	while (!m_bStopAlarmConfig)
	{
		for (int ix = 0; ix < m_nChannelNum; ix++)
		{
			for (int ij = 0; ij < ALARM_EventCount; ij++)
			{
				TabAlarmConf_t stTabAlarmConf;
				memset(&stTabAlarmConf, 0, sizeof(stTabAlarmConf));
				stTabAlarmConf.Id = 0;
				stTabAlarmConf.DevId = m_pDevInfo->nDevId;
				stTabAlarmConf.Channel = ix + 1;
				if (ij == ALARM_CRT_SERVER)
				{
					stTabAlarmConf.Channel = 0;
				}
				stTabAlarmConf.AlarmSource = ij;
				stTabAlarmConf.AlarmType = 6;
				stTabAlarmConf.AlarmLevel = 3;

				if (g_pDatabase->QueryAlarmConfigIsEixst(stTabAlarmConf.DevId, stTabAlarmConf.Channel, stTabAlarmConf.AlarmSource) <= 0)
				{
					if (g_pDatabase->UpdateAlarmConf(&stTabAlarmConf) < 0)
					{
						OutputDebugString("Device Class UpdateAlarmConf failed");
					}
				}

				
				if (m_bStopAlarmConfig)
				{
					break;
				}
				//Sleep(10);
			}
		}
		//Sleep(100);
		break;
	}


	return 0;
}

static int __stdcall FaceCompareResultCallback(JVT_LONG lRealFaceHandle, char *pBuf, long nDataLen, JVT_DWORD dwUser)
{
	CJLNDevice *pJLNDevice = (CJLNDevice *)dwUser;
	SDK_FACECOMPARE_RESULT *pstResulAlarm = (SDK_FACECOMPARE_RESULT *)pBuf;
	SMART_FACE_CMP_QUERY_INFO stCMPInfo = { 0 };

	QString strName = NULL;
	QString strUserId = NULL;
	int nTemp = 0;
	strUserId = QString::fromLocal8Bit(pstResulAlarm->picnameComp);
	if (strUserId.length() > 0)
	{
		nTemp = strUserId.indexOf("_");
		strName = QString("%1-%2").arg(strUserId.left(nTemp), strUserId.mid(nTemp + 1));
	}

	stCMPInfo.sLibSimilarity = pstResulAlarm->result;			//相似度
	strcpy(stCMPInfo.sName, strUserId.left(nTemp).toLocal8Bit().data());				//名称(可选)
	strcpy(stCMPInfo.sUserID, strUserId.mid(nTemp + 1, strUserId.indexOf(".") - nTemp - 1).toLocal8Bit().data());				//用户ID(可选)
	strcpy(stCMPInfo.sLibSnapTime, (char*)pstResulAlarm->SnapTime);		//抓拍时间
	stCMPInfo.sLibChannelid = pstResulAlarm->channelid;			//通道号
	stCMPInfo.sLibMode = pstResulAlarm->wbmode;				//名单	类型		
	stCMPInfo.sSysListID = 0;				//系统ID
	stCMPInfo.nLibGuest = pstResulAlarm->guest;				//客流统计
	stCMPInfo.cLibAge = pstResulAlarm->Age;      			//年龄 
	stCMPInfo.cLibGender = pstResulAlarm->Gender;				//性别
	stCMPInfo.cLibGlasses = pstResulAlarm->Glasses; 			//眼镜  
	stCMPInfo.cLibMask = pstResulAlarm->Mask; 				//面具
	stCMPInfo.cLibRace = pstResulAlarm->Race;				//种族  
	stCMPInfo.cLibEye = pstResulAlarm->Eye;				//眼睛 	
	stCMPInfo.cLibAttractive = pstResulAlarm->Attractive;			//魅力值
	stCMPInfo.cLibBeard = pstResulAlarm->Beard;				//胡子
	stCMPInfo.cLibEmotion = pstResulAlarm->Emotion;			//表情	
	strcpy(stCMPInfo.sSnappicname, pstResulAlarm->picnameSnap);		//实时比对图片名字
	strcpy(stCMPInfo.sLibPicName, pstResulAlarm->picnameComp);		//库图片名称
	strcpy(stCMPInfo.cDevName, pJLNDevice->m_pDevInfo->szDevName);
	strcpy(stCMPInfo.cDeviceIP, pJLNDevice->m_pDevInfo->szIpAddr);
	stCMPInfo.pLibPicBuf = pstResulAlarm->pCompImgData;			//库图数据
	stCMPInfo.dwLibPicLen = pstResulAlarm->iCompImgSize;
	stCMPInfo.dwSnapPicLen = pstResulAlarm->iSnapImgSize;
	stCMPInfo.pSnapPicBuf = pstResulAlarm->pSnapImgData;				//抓拍图数据

	pJLNDevice->ProcessSnapData(&stCMPInfo);

	return 0;
}

JVT_LONG CJLNDevice::StartReceiveFaceCompareResult(JVT_LONG lLoginID, int nChannel)
{
	JVT_LONG lCompareID = 0;
	BOOL bRet = FALSE;
	SDK_COMPINFO_FLAG compinfo;
	memset(&compinfo, 1, sizeof(SDK_COMPINFO_FLAG));
	//compinfo.iAlarmEn = 1;
	//compinfo.iCaptureEn = 1;
	//compinfo.iFeatureEn = 1;
	//compinfo.iLibPicEn = 1;

	StopReceiveFaceCompareResult(m_lSnapID[nChannel], nChannel);

	m_lSnapID[nChannel] = VideoNet_StartReceiveFaceCompareResultEx(lLoginID, nChannel, &compinfo);
	if (m_lSnapID[nChannel] > 0)
	{
		bRet = VideoNet_SetFaceCompareResultCallBack(m_lSnapID[nChannel], FaceCompareResultCallback, (JVT_DWORD)this);
		if (!bRet)
		{
			VideoNet_StopReceiveFaceCompareResult(m_lSnapID[nChannel]);
			m_lSnapID[nChannel] = -1;
		}
	}

	return bRet;
}

BOOL CJLNDevice::StopReceiveFaceCompareResult(JVT_LONG lCompareID, int nChannel)
{
	if (lCompareID > 0)
	{
		VideoNet_DeleteFaceCompareResultCallBack(lCompareID, FaceCompareResultCallback, (JVT_DWORD)this);
		VideoNet_StopReceiveFaceCompareResult(lCompareID);
		m_lSnapID[nChannel] = -1;
	}
	return TRUE;
}
BOOL CJLNDevice::StopCompare(int nChannel)
{
	EnterCriticalSection(&m_lockSubOperation);
	if (m_lSnapID[nChannel] > 0)
	{
		StopReceiveFaceCompareResult(m_lSnapID[nChannel], nChannel);
	}
	LeaveCriticalSection(&m_lockSubOperation);
	return TRUE;
}

int CJLNDevice::SavePicture(SDK_FACECOMPARE_RESULT* pCompareInfo)
{
	FILE *pPicsnapFile = NULL;
	FILE *pPiccompFile = NULL;
	FILE *pIndexFile = NULL;
	QString strFailed = NULL;
	QString stringMsg = NULL;
	char chSnapfilename[MAX_PATH] = { 0 };	//抓拍图
	char chCompfilename[MAX_PATH] = { 0 };	//库图
	char chSnapPath[MAX_PATH] = { 0 };		//路径
	char chIndexFileName[MAX_PATH] = { 0 };//索引文件名
	char chTime[16] = { 0 };
	memcpy(chTime, pCompareInfo->SnapTime, 10);

	sprintf(m_szSnapPath, "%s\\%s\\%s\\%d", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szSnapPath, chTime, pCompareInfo->cDeviceIP, pCompareInfo->channelid);	//路径
	sprintf(chSnapfilename, "%s\\%s", m_szSnapPath, pCompareInfo->picnameSnap);
	sprintf(chCompfilename, "%s\\%s", m_szSnapPath, pCompareInfo->picnameComp);
	sprintf(chIndexFileName, "%s\\index.ini", m_szSnapPath);
	strFailed = QStringLiteral("创建路径失败");
	QDir dir;
	if (!dir.exists(m_szSnapPath))
	{
		dir.mkpath(m_szSnapPath);
	}
	if (0 < strlen(pCompareInfo->picnameSnap) && 0 < pCompareInfo->iSnapImgSize)	//抓拍图
	{
		pPicsnapFile = fopen(chSnapfilename, "wb+");
		if (NULL != pPicsnapFile)
		{
			int iRet = fwrite(pCompareInfo->pSnapImgData, 1, pCompareInfo->iSnapImgSize, pPicsnapFile);
			if (iRet == pCompareInfo->iSnapImgSize)
			{
				pIndexFile = fopen(chIndexFileName, "ab+");
				if (pIndexFile)
				{
					iRet = fwrite(pCompareInfo, 1, sizeof(SDK_FACECOMPARE_RESULT), pIndexFile);
				}
				else
				{
					stringMsg = QString("'%1':'%2'").arg(strFailed).arg(QString(QLatin1String(chIndexFileName)));
					mlog(LOG_ERR, stringMsg.toLatin1().data());
				}
			}
			else
			{
				qDebug() << "strFailed";
				stringMsg = QString("'%1':'%2'").arg(strFailed).arg(QString(QLatin1String(chSnapfilename)));
				mlog(LOG_ERR, stringMsg.toLatin1().data());
			}
		}
	}


	if (0 < strlen(pCompareInfo->picnameComp) && 0 < pCompareInfo->iCompImgSize)  //库图片
	{
		pPiccompFile = fopen(chCompfilename, "wb+");
		if (NULL != pPiccompFile)
		{
			fwrite(pCompareInfo->pCompImgData, 1, pCompareInfo->iCompImgSize, pPiccompFile);
		}
		else
		{

			stringMsg = QString("'%1':'%2'").arg(strFailed).arg(QString(QLatin1String(chSnapfilename)));
			mlog(LOG_ERR, stringMsg.toLatin1().data());
		}
	}

	if (pIndexFile)
	{
		fclose(pIndexFile);
		pIndexFile = NULL;
	}

	if (pPiccompFile)
	{
		fclose(pPiccompFile);
		pPiccompFile = NULL;
	}
	if (pPicsnapFile)
	{
		fclose(pPicsnapFile);
		pPicsnapFile = NULL;
	}
	return TRUE;
}

S32 CJLNDevice::CapturePic(HWND hwnd, const char* szFileName)
{
	int i = GetPortId(hwnd);
	if (i == -1)
		return -1;

	BOOL bRet = VideoPlayer_CatchPic(i, szFileName, 0); //0:BMP 1:JPG
	if (!bRet)
	{
		return -1;
	}

	return bRet;
}

static int __stdcall FaceSnapCallback(JVT_LONG lSubFaceHandle, char *pBuffer, long lbufsize,
	SDK_FA_PICTURE_HEAD *pPictureHead, SDK_FACE_ATTR* pPictureAttr, JVT_DWORD dwUser)
{
	CJLNDevice *pJLNDevice = (CJLNDevice *)dwUser;
	SMART_FACE_CMP_QUERY_INFO stCMPInfo = { 0 };

	stCMPInfo.sLibChannelid = pPictureHead->channelid;
	strcpy(stCMPInfo.sSnappicname, (char*)pPictureHead->filename);
	strcpy(stCMPInfo.cDeviceIP, pJLNDevice->m_pDevInfo->szIpAddr);
	strcpy(stCMPInfo.sLibSnapTime, pPictureAttr->stFaceTime);
	strcpy(stCMPInfo.cDevName, pJLNDevice->m_pDevInfo->szDevName);
	stCMPInfo.dwSnapPicLen = lbufsize;
	stCMPInfo.pSnapPicBuf = pBuffer;

	pJLNDevice->ProcessSnapData(&stCMPInfo);

	return 0;
}
//开始接受抓拍
JVT_LONG CJLNDevice::StartReceiveSnapResult(JVT_LONG lLoginID, int nChannel)
{
	int nEnable = 1;
	BOOL bRet = FALSE;
	StopReceiveSanpResult(m_lSnapID[nChannel], nChannel);
	m_lSnapID[nChannel] = VideoNet_StartReceiveFaceImageFileEx(lLoginID, nChannel, nEnable);
	if (m_lSnapID[nChannel] > 0)
	{
		bRet = VideoNet_SetFaceImageDataCallBack(m_lSnapID[nChannel], FaceSnapCallback, (JVT_DWORD)this);
		if (!bRet)
		{
			VideoNet_StopReceiveFaceImageFile(m_lSnapID[nChannel]);
			m_lSnapID[nChannel] = -1;
		}
	}
	return bRet;

}

BOOL CJLNDevice::StopSnap(int nChannel)
{
	EnterCriticalSection(&m_lockSubOperation);
	if (m_lSnapID[nChannel] > 0)
	{
		StopReceiveSanpResult(m_lSnapID[nChannel], nChannel);
	}

	LeaveCriticalSection(&m_lockSubOperation);

	return TRUE;
}

//停止接收抓拍
BOOL CJLNDevice::StopReceiveSanpResult(JVT_LONG lSnapID, int nChannel)
{
	if (m_lSnapID[nChannel] > 0)
	{
		VideoNet_DeleteFaceImageDataCallBack(m_lSnapID[nChannel], FaceSnapCallback, (JVT_DWORD)this);
		VideoNet_StopReceiveFaceImageFile(m_lSnapID[nChannel]);
		m_lSnapID[nChannel] = -1;
	}
	return TRUE;
}

JVT_LONG CJLNDevice::StartImportAndExport(BOOL bCreateHandle)
{	
	EnterCriticalSection(&m_lockSubOperation);
	if (m_lImExID > 0)
	{
		LeaveCriticalSection(&m_lockSubOperation);
		return m_lImExID;
	}

	if (m_bSupportNew)
	{
		m_lImExID = StartListManagement();
	}
	else
	{
		m_lImExID = VideoNet_StartSendBlackAndWhiteList(m_lUserLoginID, 0);
		if (m_lImExID > 0)
		{
			VideoNet_SetBlackAndWhiteListCallBack(m_lImExID, FaceImportExportCallback, (JVT_DWORD)this);			
		}
	}
	if (!m_hImportWaitEvent)
	{
		m_hImportWaitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	}
	LeaveCriticalSection(&m_lockSubOperation);
	return m_lImExID;
}


static int __stdcall ListManagementCallBack(JVT_LONG lSubFaceHandle, char* pBuffer, long lbufsize, char* pConfig, JVT_DWORD dwUser)
{
	CJLNDevice* pDevice = (CJLNDevice*)dwUser;
	SDK_SMART_WB_CONFIG_EX* pConfigEx = (SDK_SMART_WB_CONFIG_EX*)pConfig;
	pDevice->m_nErrorCode = pConfigEx->iErrorCode;
	SetEvent(pDevice->m_hImportWaitEvent);

	if (g_pInstance->m_pDlgExport != NULL)
	{
		if (pConfigEx->iOpMode == OUT_PICTURE)
		{
			if (g_pInstance->m_pDlgExport->m_bQueryStat)
			{
				pDevice->SaveLibPic(pConfigEx, pBuffer, lbufsize);
				return 0;
			}
			if (g_pInstance->m_pDlgExport->attend_bQueryStat)
			{
				memcpy(g_pInstance->m_pDlgExport->m_pAttendInfo, pConfigEx, sizeof(SDK_SMART_WB_CONFIG_EX));
				pDevice->SaveLibPic(pConfigEx, pBuffer, lbufsize);
				return 0;
			}
		}
		switch (pConfigEx->iOpMode)
		{
		case OUT_INDEX:
		case OUT_PICTURE:
		case OUT_PICTURE_COMP:
		case OUT_PICTURE_DEL:
		case OUT_PICTURE_DELALL:
			g_pInstance->m_pDlgExport->ListManageCallBack_Export(lSubFaceHandle, pBuffer, lbufsize, pConfigEx, dwUser);
			break;
		
		case IN_PICTURE_ADD_SNAP:	//导出黑白名单库中单张图片

			g_pInstance->m_pDlgExport->ListManageCallBack_Inport(lSubFaceHandle, pBuffer, lbufsize, pConfigEx, dwUser);
			break;
		case OUT_ATTENDANCE:
			g_pInstance->m_pDlgExport->FaceWorkListCallBack(pBuffer, lbufsize, pConfigEx);
			break;
		case OUT_CMP_INFO:
			g_pInstance->m_pDlgExport->CmpRecordCallBack(pBuffer, lbufsize, pConfigEx);
			break;
		}
	}
	return 0;
}

BOOL CJLNDevice::StartListManagement()
{
	if (m_lImExID > 0)
	{
		return m_lImExID;
	}

	m_lImExID = VideoNet_StartListManagement(m_lUserLoginID, 0);
	if (m_lImExID > 0)
	{
		BOOL bRet = VideoNet_SetListManagementCallBack(m_lImExID, ListManagementCallBack, (JVT_DWORD)this);
		if (!bRet)
		{
			VideoNet_StopListManagement(m_lImExID);
			m_lImExID = -1;
		}
	}
	return m_lImExID;
}

BOOL CJLNDevice::StopListManagement()
{
	if (m_lImExID > 0)
	{
		VideoNet_DeleteListManagementCallBack(m_lImExID, ListManagementCallBack, (JVT_DWORD)this);
		VideoNet_StopListManagement(m_lImExID);
		m_lImExID = -1;
	}
	return TRUE;
}

BOOL CJLNDevice::StartSnapLink(JVT_LONG lLoginID, int nChannel)
{
	if (m_bSupportNew)
	{
		return StartFaceMonitor(lLoginID, nChannel);
	}
	else if (m_pDevInfo)
	{
		if (m_pDevInfo->nSubDevType == SDK_DEV_TYPE_BSIPC || m_pDevInfo->nSubDevType == SDK_DEV_TYPE_MJIPC)
		{
			return StartReceiveFaceCompareResult(lLoginID, nChannel);
		}
		else if (m_pDevInfo->nSubDevType == SDK_DEV_TYPE_FPIPC)
		{
			return StartReceiveSnapResult(lLoginID, nChannel);
		}
	}
	return FALSE;
}

BOOL CJLNDevice::StopSnapLink(int nChannel)
{
	if (m_bSupportNew)
	{
		return StopFaceMonitor(nChannel);
	}
	else if (m_pDevInfo)
	{
		if (m_pDevInfo->nSubDevType == SDK_DEV_TYPE_BSIPC || m_pDevInfo->nSubDevType == SDK_DEV_TYPE_MJIPC)
		{
			return StopCompare(nChannel);
		}
		else if (m_pDevInfo->nSubDevType == SDK_DEV_TYPE_FPIPC)
		{
			return StopSnap(nChannel);
		}
	}
	return FALSE;
}

static int __stdcall FaceMonitorCallBack(JVT_LONG lSubFaceHandle, char *pBuffer, long lbufsize, JVT_DWORD dwUser)
{
	CJLNDevice* pJLNDevice = (CJLNDevice*)dwUser;
	if (pJLNDevice)
	{
		pJLNDevice->ProcessMonitorData(pBuffer, lbufsize);
	}
	return 0;
}

BOOL CJLNDevice::StartFaceMonitor(JVT_LONG lLoginID, int nChannel)
{
	BOOL bRet = FALSE;
	SDK_FACEMONITOR_INFO_FLAG stCompinfoFlag = { 0 };

	stCompinfoFlag.nCaptureEn = 1;
	stCompinfoFlag.nFaceAttrEn = 1;
	stCompinfoFlag.nFaceCmpInfoEn = 1;
	stCompinfoFlag.nLibPicEn = 1;
	StopFaceMonitor(m_lSnapID[nChannel]);

	EnterCriticalSection(&m_lockSubOperation);
	m_lSnapID[nChannel] = VideoNet_StartReceiveFaceMonitor(lLoginID, 0, &stCompinfoFlag);
	if (m_lSnapID[nChannel] > 0)
	{
		bRet = VideoNet_SetFaceMonitorCallBack(m_lSnapID[nChannel], FaceMonitorCallBack, (JVT_DWORD)this);
		if (!bRet)
		{
			VideoNet_StopReceiveFaceMonitor(m_lSnapID[nChannel]);
			m_lSnapID[nChannel] = -1;
		}
	}
	else
	{
		int nErr = VideoNet_GetLastError();
		myHelper::ShowMessageBoxWarning(QObject::tr("打开图片失败，返回值'%1'").arg(nErr));
		//QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("打开图片失败，返回值'%1'").arg(nErr));
		return false;
	}
	LeaveCriticalSection(&m_lockSubOperation);
	return bRet;
}

BOOL CJLNDevice::StopFaceMonitor(int nChannel)
{
	EnterCriticalSection(&m_lockSubOperation);
	if (m_lSnapID[nChannel] > 0)
	{
		VideoNet_DeleteFaceMonitorCallBack(m_lSnapID[nChannel], FaceMonitorCallBack, (JVT_DWORD)this);
		VideoNet_StopReceiveFaceMonitor(m_lSnapID[nChannel]);
		m_lSnapID[nChannel] = -1;
	}
	LeaveCriticalSection(&m_lockSubOperation);
	return TRUE;
}

void CJLNDevice::ProcessMonitorData(char* pBuffer, unsigned long dwDatalen)
{
	SDK_FACE_MONITOR_INFO* pMonitorInfo = (SDK_FACE_MONITOR_INFO*)pBuffer;
	unsigned long dwLen = 0;
	if (!pMonitorInfo || (dwDatalen < sizeof(SDK_FACE_MONITOR_INFO)))
	{
		return;
	}

	memset(&m_stCMPInfo, 0, sizeof(SMART_FACE_CMP_QUERY_INFO));
	if (m_pDevInfo->nSubDevType == SDK_DEV_TYPE_BSIPC || m_pDevInfo->nSubDevType == SDK_DEV_TYPE_MJIPC)
	{
		m_stCMPInfo.sLibSimilarity = pMonitorInfo->stFaceCompareInfo.fCompareResult;			//相似度
		strcpy(m_stCMPInfo.sName, pMonitorInfo->stFaceCompareInfo.stIndexInfo.name);				//名称(可选)
		strcpy(m_stCMPInfo.sUserID, pMonitorInfo->stFaceCompareInfo.stIndexInfo.usrid);				//用户ID(可选)
		m_stCMPInfo.sLibMode = pMonitorInfo->stFaceCompareInfo.stIndexInfo.listmode;				//名单	类型		
		m_stCMPInfo.sSysListID = pMonitorInfo->stFaceCompareInfo.stIndexInfo.syslistid;				//系统ID
		m_stCMPInfo.nLibGuest = pMonitorInfo->stFaceCompareInfo.stIndexInfo.count;				//客流统计
		m_stCMPInfo.nFaceAlarm = pMonitorInfo->stFaceCompareInfo.nFaceAlarm;
	}

	strcpy(m_stCMPInfo.sLibSnapTime, pMonitorInfo->stFaceAttr.stFaceTime);		//抓拍时间
	m_stCMPInfo.sLibChannelid = pMonitorInfo->stPictureHead.channelid;			//通道号
	m_stCMPInfo.cLibAge = pMonitorInfo->stFaceAttr.stFaceAttribute.byAge;      			//年龄 
	m_stCMPInfo.cLibGender = pMonitorInfo->stFaceAttr.stFaceAttribute.byGender;				//性别
	m_stCMPInfo.cLibGlasses = pMonitorInfo->stFaceAttr.stFaceAttribute.byGlasses; 			//眼镜  
	m_stCMPInfo.cLibMask = pMonitorInfo->stFaceAttr.stFaceAttribute.byMask; 				//面具
	m_stCMPInfo.cLibRace = pMonitorInfo->stFaceAttr.stFaceAttribute.byEye;				//种族  
	m_stCMPInfo.cLibEye = pMonitorInfo->stFaceAttr.stFaceAttribute.byEye;				//眼睛 	
	m_stCMPInfo.cLibAttractive = pMonitorInfo->stFaceAttr.stFaceAttribute.byAttractive;			//魅力值
	m_stCMPInfo.cLibBeard = pMonitorInfo->stFaceAttr.stFaceAttribute.byBeard;				//胡子
	m_stCMPInfo.cLibEmotion = pMonitorInfo->stFaceAttr.stFaceAttribute.byEmotion;			//表情
	m_stCMPInfo.fTemperatureSet = pMonitorInfo->stFaceAttr.fTempSet;
	m_stCMPInfo.fTemperature = pMonitorInfo->stFaceAttr.fTempBody;
	strcpy(m_stCMPInfo.cDeviceIP, m_pDevInfo->szIpAddr);
	strcpy(m_stCMPInfo.sLibSnapTime, pMonitorInfo->stFaceAttr.stFaceTime);
	strcpy(m_stCMPInfo.cDevName, m_pDevInfo->szDevName);

	dwLen = sizeof(SDK_FACE_MONITOR_INFO);
	//DWORD dwHead = sizeof(SDK_PICTURE_HEAD);
	//DWORD dwAttr = sizeof(SDK_FACE_ATTR);
	//DWORD dwComp = sizeof(SDK_FACE_COMPARE_INFO);
	//DWORD dwFloat = sizeof(float);

	if (pMonitorInfo->stPictureHead.nUserInfo1Len)											//用户定义数据
	{
		dwLen += MAX_USER_DATA_LEN;
	}

	if (pMonitorInfo->stPictureHead.nFacePicLen > 0)		//抓拍图
	{
		m_stCMPInfo.pSnapPicBuf = (char*)(pBuffer + dwLen);
		m_stCMPInfo.dwSnapPicLen = pMonitorInfo->stPictureHead.nFacePicLen;
		strcpy(m_stCMPInfo.sSnappicname, pMonitorInfo->stFaceAttr.stFacePicname);
		dwLen += pMonitorInfo->stPictureHead.nFacePicLen;
	}

	if (pMonitorInfo->stPictureHead.nFramePicLen > 0)		//背景图
	{
		m_stCMPInfo.pBackPicBuf = (char*)(pBuffer + dwLen);
		m_stCMPInfo.dwBackPicLen = pMonitorInfo->stPictureHead.nFramePicLen;
		strcpy(m_stCMPInfo.sBackPicName, pMonitorInfo->stFaceAttr.stFramePicname);
		dwLen += pMonitorInfo->stPictureHead.nFramePicLen;
	}

	if (pMonitorInfo->stPictureHead.nLibPicLen > 0)			//底库图片
	{
		m_stCMPInfo.pLibPicBuf = (char*)(pBuffer + dwLen);
		m_stCMPInfo.dwLibPicLen = pMonitorInfo->stPictureHead.nLibPicLen;
		strcpy(m_stCMPInfo.sLibPicName, pMonitorInfo->stFaceCompareInfo.stIndexInfo.picname);
		dwLen += pMonitorInfo->stPictureHead.nLibPicLen;
	}
	ProcessSnapData(&m_stCMPInfo);
}

int CJLNDevice::ProcessSnapData(SMART_FACE_CMP_QUERY_INFO* pCompareInfo)
{
	char chSnapfilename[MAX_PATH] = { 0 };	//抓拍图
	char chCompfilename[MAX_PATH] = { 0 };	//库图
	char chIndexFileName[MAX_PATH] = { 0 };//索引文件名
	char chTime[16] = { 0 };
	memcpy(chTime, pCompareInfo->sLibSnapTime, 10);

	int iRet = 0;

	sprintf(m_szSnapPath, "%s\\%s\\%s\\%d", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szSnapPath, chTime, pCompareInfo->cDeviceIP, pCompareInfo->sLibChannelid);	//路径
	sprintf(chSnapfilename, "%s\\%s", m_szSnapPath, pCompareInfo->sSnappicname);
	sprintf(chCompfilename, "%s\\%s", m_szSnapPath, pCompareInfo->sLibPicName);
	sprintf(chIndexFileName, "%s\\index.ini", m_szSnapPath);

	strcpy(pCompareInfo->cPath, m_szSnapPath);

	if (pCompareInfo->pSnapPicBuf && 0 < pCompareInfo->dwSnapPicLen)	//抓拍图
	{
		if (WriteFile(chSnapfilename, pCompareInfo->pSnapPicBuf, pCompareInfo->dwSnapPicLen))
		{
			WriteFile(chIndexFileName, (char*)pCompareInfo, sizeof(SMART_FACE_CMP_QUERY_INFO));
		}
	}
	QFile fileInfo(QString::fromLocal8Bit(chCompfilename));

	if (pCompareInfo->pLibPicBuf && 0 < pCompareInfo->dwLibPicLen
		&& !fileInfo.exists())												//库图片
	{
		WriteFile(chCompfilename, pCompareInfo->pLibPicBuf, pCompareInfo->dwLibPicLen);
	}

	if (g_pInstance != NULL)
	{
		if (pCompareInfo == NULL)
		{
			return FALSE;
		}
		g_pInstance->m_pPreviewPro->ReceiveSnap((char*)pCompareInfo);
	}
	return TRUE;
}

int CJLNDevice::WriteFile(char* pFileName, char* pFileData, unsigned long nDatalen)
{
	if (!pFileName || !pFileData || nDatalen == 0)
	{
		return FALSE;
	}
	FILE* pFile = NULL;
	QString strFailed = NULL;
	QString strErr = NULL;

	//创建路径
	QDir dir;
	if (!dir.exists(m_szSnapPath))
	{
		dir.mkpath(m_szSnapPath);
	}
	pFile = fopen(pFileName, "ab+");
	if (NULL != pFile)
	{
		fwrite(pFileData, 1, nDatalen, pFile);
	}
	else
	{

		strErr = QStringLiteral("创建文件失败'%1'").arg(QString::fromLocal8Bit(pFileName));
		mlog(LOG_ERR, strErr.toLatin1().data());
	}

	if (pFile)
	{
		fclose(pFile);
		pFile = NULL;
	}
	return TRUE;
}

void CJLNDevice::SaveLibPic(SDK_SMART_WB_CONFIG_EX* pConfig, char* pBuffer, long lbufsize)
{
	char chFilename[MAX_PATH] = { 0 };
	QString strPath = NULL;

	//创建路径
	strPath = QString("%1\\%2").arg(QCoreApplication::applicationDirPath() + "/" + "LibPicture").arg(m_pDevInfo->szIpAddr);
	QDir dir;
	if (!dir.exists(strPath))
	{
		dir.mkpath(strPath);
	}
	sprintf(chFilename, "%s\\%d.jpg", strPath.toLatin1().data(), pConfig->stUserInfo.syslistid);
	if (pConfig->iErrorCode == WB_OK)
	{
		FILE * pFile = fopen(chFilename, "wb");
		if (pFile)
		{
			fwrite(pBuffer, 1, lbufsize, pFile);
			fclose(pFile);
			pFile = NULL;
		}
	}
}

S32 CJLNDevice::LocalRecord(HWND hwnd, const char* szFileName, BOOL bStop)
{
	int i = GetPortId(hwnd);
	if (i == -1)
		return -1;
	if (bStop)
	{
		BOOL bRet = VideoPlayer_StopDataRecord(i);
		if (!bRet)
		{
			return -1;
		}
		g_mutexDevObj.lock();
		g_JlnPlayerInfo[i].bSaveStream = FALSE;
		memset(g_JlnPlayerInfo[i].szFileName, '\0', sizeof(g_JlnPlayerInfo[i].szFileName));
		g_mutexDevObj.unlock();
	}
	else
	{
		BOOL bRet = VideoPlayer_StartDataRecord(i, szFileName, MEDIA_FILE_NONE);
		if (!bRet)
		{
			return -1;
		}
		g_mutexDevObj.lock();
		strcpy(g_JlnPlayerInfo[i].szFileName, szFileName);
		g_JlnPlayerInfo[i].SerialNum = 1;
		g_JlnPlayerInfo[i].TimeStamp = 40;
		g_JlnPlayerInfo[i].ASerialNum = 1;
		g_JlnPlayerInfo[i].ATimeStamp = 40;

		g_JlnPlayerInfo[i].bSaveStream = TRUE;
		g_mutexDevObj.unlock();
	}
	return 0;
}

S32 CJLNDevice::RefreshPlay(HWND hwnd)
{
	int i = GetPortId(hwnd);
	if (i < 0)
		return -1;
	BOOL bRet = VideoPlayer_RefreshPlay(i);
	if (!bRet)
	{
		return -1;
	}
	return 0;
}

S32 CJLNDevice::EnableAudio(HWND hwnd, BOOL bEnable)
{

	int i = GetPortId(hwnd);
	if (i == -1)
		return -1;
	g_mutexDevObj.lock();
	g_JlnPlayerInfo[i].bEnableAudio = bEnable;
	g_mutexDevObj.unlock();
	//int err = PLAY_SetAudio((USHORT)i, bEnable);
	if (bEnable)
	{
		VideoPlayer_PlaySoundShare(i);
	}
	else
	{
		VideoPlayer_StopSoundShare(i);
	}

	return 0;
}

S32 CJLNDevice::ManulRecord(HWND hwnd, U32 nChannel, BOOL bStop)
{
	return -1;
}

void __stdcall AudioDataCallBack(LPBYTE pDataBuffer, DWORD dwDataLength, long nUser)
{
	CJLNDevice* pDevice = (CJLNDevice*)nUser;
	if (pDevice)
	{
		pDevice->SendTalkData(pDataBuffer, dwDataLength);
	}
}

S32 CJLNDevice::Speak(HWND hwnd, BOOL bStart)
{
	int i = GetPortId(hwnd);
	if (i == -1)
	{
		return -1;
	}
	int nLen = 640;
	DWORD dwAudioBit = 16;
	DWORD dwSampleRate = 8000;

	if (!bStart)
	{
		if (!bDevTalk)
		{
			return -1;
		}
		VideoNet_StopVoiceCom(m_lTalkHandle);
		m_lTalkHandle = -1;

		m_bDevTalk = FALSE;
		VideoPlayer_StopAudioCapture();
		VideoPlayer_StopSound();
	}
	else
	{
		m_lTalkHandle = VideoNet_StartVoiceCom_MR(m_lUserLoginID, NULL, (JVT_DWORD)this);
		if (m_lTalkHandle <= 0)
		{
			return -1;
		}

		BOOL bRet = VideoPlayer_StartAudioCapture(AudioDataCallBack, dwAudioBit, dwSampleRate, nLen, (LONG)this);
		if (!bRet)
		{
			return -1;
		}
		m_bDevTalk = TRUE;
		VideoPlayer_PlaySound(i);
	}
	return 0;
}

S32 CJLNDevice::GetDeviceRecordStatus(HWND hwnd)
{
	return -1;
}



BOOL CJLNDevice::SendTalkData(LPBYTE pDataBuffer, DWORD dwDataLength)
{
	if (NULL == m_pTalkDecodeBuf)
	{
		m_pTalkDecodeBuf = new BYTE[TALK_BUFFER_LENGTH];
	}
	memset(m_pTalkDecodeBuf, 0, TALK_BUFFER_LENGTH);
	int iCbLen = 0;
	if (g711a_Encode((char*)pDataBuffer, (char*)m_pTalkDecodeBuf + 8, dwDataLength, &iCbLen) != 1)
	{
		return FALSE;
	}
	
	m_pTalkDecodeBuf[0] = 0x00;
	m_pTalkDecodeBuf[1] = 0x00;
	m_pTalkDecodeBuf[2] = 0x01;
	m_pTalkDecodeBuf[3] = 0xFA;

	m_pTalkDecodeBuf[4] = 0x0E; //G711A
	m_pTalkDecodeBuf[5] = 0x02;
	m_pTalkDecodeBuf[6] = BYTE(iCbLen & 0xff);
	m_pTalkDecodeBuf[7] = BYTE(iCbLen >> 8);

	iCbLen += 8;
	bool ret = VideoNet_VoiceComSendData(m_lTalkHandle, (char*)m_pTalkDecodeBuf, iCbLen);
	return ret;
}


S32 CJLNDevice::GetDecoderPara(int nCmd, int nPara1, int nPara2, int* pOut1, int* pOut2)
{
	return -1;
}

S32 CJLNDevice::SetDecoderPara(int nCmd, int nPara1, int nPara2, int* pOut1, int* pOut2)
{
	return -1;
}

BOOL CJLNDevice::DisconnectDevice(long lDevID)
{
	// 断开所有通道连接.
	//..................
	// 	for( int i = 0 ;  i < CHANNELS_MAX ; i++)
	// 	{
	// 		DisconnectChannel( pDevInfo ,i, NULL, NULL, nNetHalt );
	// 	}
	// 
	// 	bResult = pDev->Disconnect( nNetHalt );
	return 0;
}

S32 CJLNDevice::SetOutput(int nChannel, int nStatus)
{
	return -2;
}

int CJLNDevice::ProcessListManage(SDK_SMART_WB_CONFIG_EX* pConfig, char* pFileName)
{
	int nRet = FALSE;
	if (m_bSupportNew)
	{
		nRet = VideoNet_ListManagementData(m_lImExID, (char*)pConfig, sizeof(SDK_SMART_WB_CONFIG_EX), pFileName);
	}
	else
	{
		nRet = VideoNet_OperationBlackAndWhiteListData(m_lImExID, (WBLIST_ACTION_TYPE)pConfig->iOpMode, pConfig->iWbmode, 0, 0, pFileName, 0);
	}
	return nRet;
}

JVT_LONG CJLNDevice::StartUpgrade()
{
	//return m_lUpgradeHandle = VideoNet_Upgrade(m_lUserLoginID, upGradeFileName.toLocal8Bit().data(), 0, UpgradeCallBack, (JVT_DWORD)this);
	return 0;
}

int CJLNDevice::GetLoginError(int nError, QString &strError)
{
	/*if (strError == NULL)
	{
		//sprintf(pszError, "未知错误");
		strError = QObject::tr("未知错误");
	}*/
	if (nError == VIDEONET_USER_NOT_LOGIN)
	{
		strError = QObject::tr("用户没有登陆");
	}
	else if (nError == VIDEONET_NOPOWER)
	{
		strError = QObject::tr("权限不够");
	}
	else if(nError == VIDEONET_PASSWORD_NOT_VALID)
	{
		strError = QObject::tr("密码错误");
	}
	else if (nError == VIDEONET_LOGIN_USER_NOEXIST)
	{
		strError = QObject::tr("用户不存在");
	}
	else if (nError == VIDEONET_USER_LOCKED)
	{
		strError = QObject::tr("用户账号被锁定");
	}
	else if (nError == VIDEONET_USER_IN_BLACKLIST)
	{
		strError = QObject::tr("名单中禁止访问的用户");
	}
	else if (nError == VIDEONET_USER_HAS_USED)
	{
		strError = QObject::tr("账号已经登录");
	}
	else if (nError == VIDEONET_ACCOUNT_INPUT_NOT_VALID)
	{
		strError = QObject::tr("用户管理输入不合法");
	}
	else if (nError == VIDEONET_ACCOUNT_OVERLAP)
	{
		strError = QObject::tr("索引重复");
	}
	else if (nError == VIDEONET_ACCOUNT_OBJECT_NONE)
	{
		strError = QObject::tr("不存在对象，用于查询时");
	}
	else if (nError == VIDEONET_ACCOUNT_OBJECT_NOT_VALID)
	{
		strError = QObject::tr("不存在对象");
	}
	else if (nError == VIDEONET_ACCOUNT_OBJECT_IN_USE)
	{
		strError = QObject::tr("对象正在使用");
	}
	else if (nError == VIDEONET_ACCOUNT_SUBSET_OVERLAP)
	{
		strError = QObject::tr("没有权限");
	}
	else if (nError == VIDEONET_ACCOUNT_PWD_NOT_VALID)
	{
		strError = QObject::tr("密码不正确");
	}
	else if (nError == VIDEONET_ACCOUNT_PWD_NOT_MATCH)
	{
		strError = QObject::tr("密码不匹配");
	}
	else if (nError == VIDEONET_ACCOUNT_RESERVED)
	{
		strError = QObject::tr("保留账号");
	}
	else if (nError == VIDEONET_OPT_FILE_ERROR)
	{
		strError = QObject::tr("写文件出错");
	}
	else if (nError == VIDEONET_OPT_CAPS_ERROR)
	{
		strError = QObject::tr("配置特性不支持");
	}
	else if (nError == VIDEONET_OPT_VALIDATE_ERROR)
	{
		strError = QObject::tr("配置校验失败");
	}
	else if (nError == VIDEONET_SDK_UNKNOWNERROR)
	{
		strError = QObject::tr("未知错误");
	}
	else if (nError == VIDEONET_SDK_NOTSUPPORT)
	{
		strError = QObject::tr("版本不支持");
	}
	else if (nError == VIDEONET_SDK_NOTVALID)
	{
		strError = QObject::tr("非法请求");
	}
	else if (nError == VIDEONET_PASSWORD_NOT_VALID)
	{
		strError = QObject::tr("用户名密码错误");
	}
	else if (nError == VIDEONET_SDK_TIMEOUT)
	{
		strError = QObject::tr("超时");
	}
	else if (nError == 0)
	{
		strError = QObject::tr("设备不在线");
	}
	
	/*int nMapSize = sizeof(s_errorMap) / sizeof(CONFIG_ERROR_PAIR);

	for (int i = 0; i < nMapSize; i++)
	{
		if (s_errorMap[i].iDevErrorNo == nError)
		{
			strError = s_errorMap[i].strError;
			//memcpy(pszError, s_errorMap[i].szError, strlen(s_errorMap[i].szError));
			break;
		}
	}*/

	return nError;
}
JVT_LONG CJLNDevice::GetLoginID()
{

	if (m_lUserLoginID <= 0)
	{
		GetLoginError(m_nLoginError, m_strLoginError);

		myHelper::ShowMessageBoxWarning(m_strLoginError);
	}
	return m_lUserLoginID;
}
