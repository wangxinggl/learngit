
#include "JLNDevice.h"
#include <Windows.h>
#include <assert.h>
#include <iostream>
#include <QMutex>
#include <QDebug>
#include <stdio.h>
#include <QDir>
#include <QFile>
#include "capacityset.h"
#include "client.h"
#include <QMessageBox>
#include <QCoreApplication>

//void alarm_callback(JVT_LONG lDevId,JVT_LONG lAlarmType,JVT_LONG lChannel,char* szMsg);

#define RUN_LOG_FILE "sVMS"
#define  JVT_LONG LONG 
#define  STOP_START 100
#define MAX_JL_PLAYER 256



std::map<LONG, CJLNDevice *> g_JLNDevMap;

st_playerInfo g_JlnPlayerInfo[MAX_JL_PLAYER] = {0};
std::map<HANDLE ,int> g_mapJlnPlayerInfo;



QMutex jln_mutex;

typedef struct  
{
	UCHAR rsv;//0x00;
	UCHAR code;//0x01
	UCHAR len; //80的整数倍 A0 
	UCHAR seq;//0~255;  00
}hisi_audio_head_t;

static S32  GetPortId(HANDLE lHandle)
{
	jln_mutex.lock();

	std::map<HANDLE, int>::const_iterator it = g_mapJlnPlayerInfo.find(lHandle);
	if(it != g_mapJlnPlayerInfo.end())
	{
		jln_mutex.unlock();
		return it->second;
	}
	jln_mutex.unlock();
	return -1;
}


bool __stdcall JVTMessCallBack(LONG lLoginID, char *pBuf,
							unsigned long dwBufLen, DWORD dwUser)
{
	LONG lAlarmType = -1;
	LONG lAlarmChannel = -1;
    if (dwBufLen != sizeof(SDK_AlarmInfo))
    {
		return FALSE;
    }
	SDK_AlarmInfo alarmInfo;
	memcpy (&alarmInfo, pBuf, dwBufLen);

	switch (alarmInfo.iEvent)
	{
	case SDK_EVENT_CODE_NET_ALARM:
	case SDK_EVENT_CODE_MANUAL_ALARM:
	case SDK_EVENT_CODE_LOCAL_ALARM:
		lAlarmType = ALARM_SOURCE_ALARMIN;
		break;
	case SDK_EVENT_CODE_VIDEO_MOTION:
		lAlarmType = ALARM_SOURCE_MOVING_DETECT;
		break;
	case SDK_EVENT_CODE_VIDEO_LOSS:
		lAlarmType = ALARM_SOURCE_LOSE_SIGNAL;
		break;
	case SDK_EVENT_CODE_VIDEO_BLIND:
		lAlarmType = ALARM_SOURCE_VIDEO_BLIND;
		break;
	case SDK_EVENT_CODE_STORAGE_FAILURE:
		lAlarmType = ALARM_DISK_BAD;
		break;
	case SDK_EVENT_CODE_LOW_SPACE:
		lAlarmType = ALARM_DISK_LOW;
		break;
	case SDK_EventBrightness:
		lAlarmType = ALARM_EventBrightness;
		break;
	case SDK_EventShelter:
		lAlarmType = ALARM_EventShelter;
		break;
	case SDK_EventCrossLine:
		lAlarmType = ALARM_EventCrossLine;
		break;
	case SDK_EventCrossArea:
		lAlarmType = ALARM_EventCrossArea;
		break;
	case SDK_EventColor:
		lAlarmType = ALARM_EventColor;
		break;
	case SDK_EventSound:
		lAlarmType = ALARM_EventSound;
		break;
	case SDK_EventLoseOBJ:
		lAlarmType = ALARM_EventLoseOBJ;
		break;
	}

	if(lAlarmType == -1)
		return TRUE;
	
	lAlarmChannel = alarmInfo.nChannel + 1;

	LONG lDevId;
	CJLNDevice *pDev = NULL;
	std::map<LONG,CJLNDevice *>::iterator dev_iter;
	jln_mutex.lock();
	dev_iter = g_JLNDevMap.find(lLoginID);
	if(dev_iter != g_JLNDevMap.end())
	{
		pDev = dev_iter->second;
	}
	if(pDev == NULL)
	{
		jln_mutex.unlock();
		return 0;
	}
	lDevId= pDev->GetDevInfo()->nDevId;

	
	jln_mutex.unlock();
    
	Client::instance()->alarm_callback(lDevId, lAlarmType, lAlarmChannel, "");

	return TRUE;
}

CJLNDevice::CJLNDevice()
{
	  
	m_lUserLoginID = 0;
	m_lDevType = 0;
	m_hReconnectThread = NULL;
	m_bReconnecting = FALSE;
	m_nChannelNum = 0;
	m_hAlarmConfigThread = NULL;
	m_bStopAlarmConfig = FALSE;
	m_bSupportNew = FALSE;
	m_bBrush = FALSE;
	m_bLight = FALSE;
	for (int i = 0; i < MAX_CHANNEL; i ++)
	{
		m_lCompareID[i] = -1;
		m_lSnapID[i] = -1;
		m_lImExID[i] = -1;
		m_lFaceMonitorID[i] = -1;
	}
	memset(&m_stDevInfo, 0, sizeof(VIDEONET_DEVICEINFO));
	set = new systemSet;
	InitializeCriticalSection(&m_lockSubOperation);
}

CJLNDevice::~CJLNDevice()
{
	m_bReconnecting = FALSE;

	m_bStopAlarmConfig = TRUE;

	if (NULL != m_hAlarmConfigThread)
	{
		WaitForSingleObject(m_hAlarmConfigThread, INFINITE);
		CloseHandle(m_hAlarmConfigThread);
		m_hAlarmConfigThread = NULL;
	}

	for (int i = 0; i < MAX_CHANNEL; i++)
	{
		if (m_lCompareID[i] > 0)
		{
			StopReceiveFaceCompareResult(m_lCompareID[i], i);
		}
		if (m_lSnapID[i] > 0)
		{
			StopReceiveSanpResult(m_lSnapID[i], i);
		}
		if (m_lImExID[i] > 0)
		{
			StopImportAndExport(m_lImExID[i], i);
		}
		if (m_lFaceMonitorID[i] > 0)
		{
			StopFaceMonitor(i);
		}
	}

	Logout();
	DeleteCriticalSection(&m_lockSubOperation);
}


int __stdcall RealDataCallBack_V2(JVT_LONG lRealHandle,const PACKET_INFO_EX *pFrame, JVT_DWORD dwUser)
{
//	CJLNDevice *pDataChnl = (CJLNDevice*)dwUser;
	bool ret=VideoPlayer_InputData(dwUser /*pDataChnl->m_nPlaydecHandle*/ , (unsigned char*)pFrame->pPacketBuffer, pFrame->dwPacketSize);
	if (dwUser == 1)
	{
		int i = 1;
	}

	return 1;
}

//device disconnect callback
void __stdcall DisConnectBackCallFunc(LONG lLoginID, char *pchDVRIP,
	LONG nDVRPort, DWORD dwUser)
{
	
	LONG lDevId;
	CJLNDevice *pDev = NULL;
	std::map<LONG, CJLNDevice *>::iterator dev_iter;
	jln_mutex.lock();
	dev_iter = g_JLNDevMap.find(lLoginID);
	if (dev_iter != g_JLNDevMap.end())
	{
		pDev = dev_iter->second;
	}
	if (pDev == NULL)
	{
		jln_mutex.unlock();
		return;
	}
	lDevId = pDev->GetDevInfo()->nDevId;
	jln_mutex.unlock();
	mlog(LOG_NOTICE, "ReConnect LoginID = %d,DevID = %d!", lLoginID, lDevId);
	
	Client::instance()->deiceLostEvent = new CompareEvent(CompareEvent::getType(CET_DEVICELOST));
	QApplication::postEvent(NULL, Client::instance()->deiceLostEvent);
}


void CALLBACK CJLNDevice::videoInfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser)
{
	CJLNDevice *pThis = (CJLNDevice*)nUser;
	//收到信息帧, 0x03 代表GPRS信息
	if ( nType == 0x03 )
	{
		pThis->m_strInfoFrame[nPort] = pBuf;
	}
}

void CALLBACK drawOSDCall(LONG nPort,HDC hDc,LONG nUser)
{
	CJLNDevice *pThis = (CJLNDevice*)nUser;
	
}

void __stdcall pProc(LONG nPort,LPCSTR pBuf,LONG nSize,LONG nWidth,LONG nHeight, LONG nStamp,LONG nType,LONG nUser)
{

}


S32 CJLNDevice::OpenChannel(U32 nChannel,U32 nStream,HWND hwnd, int nWndNum)
{
	
	if (0 == m_lUserLoginID)
	{
		if(Login() <= 0)
		{
			return -1;
		}
	}

	LONG lPlayhandle = -1;
    long lPlaydecHandle = -1;

	jln_mutex.lock();
	int iPort;
	for (iPort = 0;iPort < MAX_JL_PLAYER;iPort++)
	{
		if(!g_JlnPlayerInfo[iPort].bUsed)
		{
			g_JlnPlayerInfo[iPort].bUsed = TRUE;
			break;
		}
	}
	if(iPort == MAX_JL_PLAYER)
	{
		jln_mutex.unlock();
		mlog(LOG_ERR, "OpenChannel Port over max vaule  longID = %d\n", m_lUserLoginID);
		CloseChannel(hwnd);
		return -1;
	}
	jln_mutex.unlock();

	//open decoder
	BYTE byFileHeadBuf;
	if (VideoPlayer_OpenStream(iPort, &byFileHeadBuf, 1, SOURCE_BUF_MIN*50))
	{	
		//设置信息帧回调
		VideoPlayer_SetInfoFrameCallBack(iPort, videoInfoFramCallback,(DWORD)this);

		
		VideoPlayer_SetStreamOpenMode(iPort, STREAME_REALTIME);	
		
		if ( VideoPlayer_Play(iPort, hwnd) )
		{
			VideoPlayer_SetDisplayCallBack(iPort, pProc, (LONG)this);
			lPlaydecHandle = iPort;
		}
		else
		{
			mlog(LOG_ERR,"VideoPlayer_OpenStream  failed  longID = %d channel = %d\n",m_lUserLoginID,nChannel);
		}
		
	}


	if (-1 == lPlaydecHandle)
	{
		mlog(LOG_ERR,"OpenChannel PlaydecHandle failed  longID = %d channel = %d\n",m_lUserLoginID,nChannel);
		VideoPlayer_CloseStream(iPort);
		return -2;
	}

	VIDEONET_CLIENTINFO playstru = {0};

	playstru.nChannel = nChannel - 1;
	playstru.nStream = nStream;
	playstru.nMode = 0;
	lPlayhandle = VideoNet_RealPlay(m_lUserLoginID, &playstru);	
	if(lPlayhandle <= 0 )
	{
		DWORD dwErr = VideoNet_GetLastError();
		mlog(LOG_ERR,"VideoNet_RealPlay failed  ip addr = %s,DevName = %s,channel= %d,longID = %d,error = %d\n"
			,m_pDevInfo->szIpAddr,m_pDevInfo->szDevName,nChannel,m_lUserLoginID,dwErr);

		if (lPlaydecHandle != -1)
		{
			VideoPlayer_CloseStream(lPlaydecHandle);
			VideoPlayer_Stop(lPlaydecHandle);
		}

		jln_mutex.lock();
		g_JlnPlayerInfo[lPlaydecHandle].bUsed = FALSE;
		jln_mutex.unlock();
		return -1;
	}
	else
	{
		//VideoNet_MakeKeyFrame(m_lUserLoginID, playstru.nChannel, nStream);

		VideoNet_SetRealDataCallBack_V2(lPlayhandle, RealDataCallBack_V2, lPlaydecHandle/*(long)this*/);
		
	}

	jln_mutex.lock();
	m_mapPlayHandle[hwnd] = lPlayhandle;
	m_mapPlayChannel[hwnd] = nChannel;
	/*****************************************/
	g_JlnPlayerInfo[iPort].port = iPort;
	g_JlnPlayerInfo[iPort].nChannel = nChannel;
	g_JlnPlayerInfo[iPort].nStreamType = nStream;
	g_JlnPlayerInfo[iPort].hPlayWnd = hwnd;
	g_JlnPlayerInfo[iPort].nDevID = m_lUserLoginID;
	g_JlnPlayerInfo[iPort].nWndNum = nWndNum;
	/*****************************************/
	g_mapJlnPlayerInfo[hwnd] = iPort;

	jln_mutex.unlock();
	return lPlayhandle;
}

S32 CJLNDevice::ChangeChannelStream(HWND hwnd,U32 nStream)
{
	int lRealHandle;
	std::map<HWND, int>::const_iterator it = m_mapPlayHandle.find(hwnd);
	if(it != m_mapPlayHandle.end())
	{
		lRealHandle = it->second;
		int nChannel = GetPlayChannel(hwnd);
		if(nChannel != -1)
		{
			CloseChannel(hwnd);
			return OpenChannel(nChannel,nStream,hwnd);
		}
	}
	return -1;
}

S32 CJLNDevice::CloseChannel(HWND hwnd)
{

	std::map<HWND, int>::const_iterator it = m_mapPlayHandle.find(hwnd);
	if (it == m_mapPlayHandle.end())
	{
		return -1;
	}

	int lPlayhandle = it->second;
	int i = GetPortId(hwnd);
	jln_mutex.lock();
	g_mapJlnPlayerInfo.erase((HANDLE)lPlayhandle);
	jln_mutex.unlock();

	if (lPlayhandle > 0)
	{
		VideoNet_DelRealDataCallBack_V2(lPlayhandle, RealDataCallBack_V2, (JVT_DWORD)i);
		BOOL bRet = VideoNet_StopRealPlay(lPlayhandle);
		if (!bRet)
		{
			return -1;
		}
	}

	m_mapPlayHandle.erase(it);

	//channel
	std::map<HWND, int>::const_iterator itChannel = m_mapPlayChannel.find(hwnd);
	if (itChannel != m_mapPlayChannel.end())
		m_mapPlayChannel.erase(itChannel);
	//close decode

	if (i != -1)
	{
		VideoPlayer_CloseStream(i);
		VideoPlayer_Stop(i);
	}

	jln_mutex.lock();
	if (i != -1)
	{
		g_JlnPlayerInfo[i].port = 0;
		g_JlnPlayerInfo[i].bUsed = FALSE;
		g_JlnPlayerInfo[i].bSaveStream = FALSE;
		g_JlnPlayerInfo[i].bEnableAudio = FALSE;

		g_JlnPlayerInfo[i].nChannel = -1;
		g_JlnPlayerInfo[i].nStreamType = -1;
		g_JlnPlayerInfo[i].hPlayWnd = NULL;
		g_JlnPlayerInfo[i].nDevID = -1;
		g_JlnPlayerInfo[i].bSpeak = FALSE;
	}
	jln_mutex.unlock();

	if (m_mapPlayHandle.empty())
	{
		m_mapPlayChannel.clear();
	}
	return TRUE;
}

S32 CJLNDevice::PtzCtrl(HWND hwnd, int nPtzType,U32 nStop,U32 nSpeed)
{
	if(m_lUserLoginID == 0)
		return -1;
	S32 bRet = 0;

	int nChannel = GetPlayChannel(hwnd);
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

		bRet = VideoNet_PTZControl(m_lUserLoginID, 0, nPtzType, nStop, nSpeed);
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

	if(m_lUserLoginID != 0)
	{
		return m_lUserLoginID;
	}
	
	if ( m_lUserLoginID <= 0 )
	{
		VIDEONET_DEVICEINFO OutDev = {0};
		int nError = 0;
		JVT_LONG lLogin = 0;
		if (IsIPAvailed(m_pDevInfo->szIpAddr))
		{
			lLogin = VideoNet_Login(m_pDevInfo->szIpAddr, m_pDevInfo->nPort, m_pDevInfo->szLoginName, m_pDevInfo->szPassword, &m_stDevInfo, &nError );
		}
		else
		{
			lLogin = VideoNet_Login_P2P(m_pDevInfo->szIpAddr, 0, m_pDevInfo->szLoginName, m_pDevInfo->szPassword, &m_stDevInfo, &nError);
		}

		if ( lLogin <= 0 )
		{
			
			lRet = VideoNet_GetLastError();  //VIDEONET_PASSWORD_NOT_VALID
			mlog(LOG_ERR,"devcie login failed error code = %d,ip addr = %s,port = %d,UserName = %s,Pwd = %s\n",lRet,m_pDevInfo->szIpAddr,m_pDevInfo->nPort,m_pDevInfo->szLoginName,m_pDevInfo->szPassword);
			return lRet;
		}

		m_lUserLoginID = lLogin;
		m_lDevType = OutDev.deviceTye;
		VideoNet_SetupAlarmChan(lLogin);

		//判断是否支持新协议
		if (strcmp(m_stDevInfo.sProtocol, "v2.0") == 0)
		{
			m_bSupportNew = TRUE;
		}

		mlog(LOG_INFO, "devcie login success  ip addr = %s,port = %d,UserName = %s,Pwd = %s,User loginID = %d\n",
			m_pDevInfo->szIpAddr,m_pDevInfo->nPort,m_pDevInfo->szLoginName,m_pDevInfo->szPassword,m_lUserLoginID);
		if (OutDev.iDigChannel > 0)
		{
			m_nChannelNum = OutDev.iDigChannel;
		}
		else
		{
			m_nChannelNum = OutDev.byChanNum+OutDev.iDigChannel;
		}

		m_bStopAlarmConfig = TRUE;
		
		m_bStopAlarmConfig = FALSE;
		m_hAlarmConfigThread = ::CreateThread(NULL,0,AlarmConfigThread,this,0,NULL);
		if (NULL != m_hAlarmConfigThread)
		{
			WaitForSingleObject(m_hAlarmConfigThread, INFINITE);
			CloseHandle(m_hAlarmConfigThread);
			m_hAlarmConfigThread = NULL;
		}
	}
	jln_mutex.lock();
	g_JLNDevMap[m_lUserLoginID] = this;
	jln_mutex.unlock();

	return m_lUserLoginID;
}

S32 CJLNDevice::Logout()
{
	

	if (m_lUserLoginID == 0 /*|| !m_mapPlayHandle.empty() || m_bRecvAlarm*/)
	{
		return 0;
	}
	QString strLog =NULL;

	long lRet = VideoNet_Logout(m_lUserLoginID);
	if (lRet == VIDEONET_SUCCESS)
	{
		mlog(LOG_ERR, "VideoNet_Logout success  ip addr = %s,DevName = %s,longID = %d\n"
			, m_pDevInfo->szIpAddr, m_pDevInfo->szDevName, m_lUserLoginID);

		jln_mutex.lock();
		g_JLNDevMap.erase(m_lUserLoginID);
		jln_mutex.unlock();
		m_lUserLoginID = 0;
	}
	else
	{
		DWORD dwErr = VideoNet_GetLastError();
		mlog(LOG_ERR, "VideoNet_Logout failed  ip addr = %s,DevName = %s,longID = %d,error = %d\n"
			, m_pDevInfo->szIpAddr, m_pDevInfo->szDevName, m_lUserLoginID, dwErr);
	}
	return lRet;
}




S32 CJLNDevice::Reconnect()
{
	if (m_bReconnecting)
	{
		return 0;
	}
	m_bReconnecting = TRUE;
	m_hReconnectThread = ::CreateThread(NULL,0,ReconnectThread,this,0,NULL);
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
	ConstractSubLink();

	OperateSubPlay(FALSE);
	OperateSubImExLink(FALSE);
	OperateSubSnapLink(FALSE);
	OperateSubCompareLink(FALSE);
	OperateSubFaceMonitorLink(FALSE);

	Logout();

	while (m_bReconnecting)
	{
		//重连
		if (0 == m_lUserLoginID)
		{
			Login();
		}
		else
		{
			if (m_listPlayInfo.size() <= 0 && m_vectorImExInfo.size() <= 0
				&& m_vectorSnapInfo.size() <= 0 && m_vectorCompareInfo.size() <= 0)
			{
				m_bReconnecting = FALSE;
				break;
			}

			OperateSubPlay(TRUE);
			OperateSubImExLink(TRUE);
			OperateSubSnapLink(TRUE);
			OperateSubCompareLink(TRUE);
			OperateSubFaceMonitorLink(TRUE);
		}
	}

	if (NULL != m_hReconnectThread)
	{
		CloseHandle(m_hReconnectThread);
		m_hReconnectThread = NULL;
	}
	return 0;
}

void CJLNDevice::OperateSubCompareLink(BOOL bOpen)
{
	vector<st_faceManageInfo>::iterator iter;
	st_faceManageInfo* pstFaceManageInfo;
	BOOL bRet = FALSE;

	if (m_vectorCompareInfo.size() > 0)
	{
		iter = m_vectorCompareInfo.begin();
		while (iter != m_vectorCompareInfo.end())
		{
			pstFaceManageInfo = &*iter;
			if (bOpen)
			{
				bRet = StartReceiveFaceCompareResult(m_lUserLoginID, pstFaceManageInfo->nChannel);
				if (bRet)
				{
					iter = m_vectorCompareInfo.erase(iter);
					continue;
				}
			}
			else
			{
				bRet = StopReceiveFaceCompareResult(pstFaceManageInfo->lFaceManageID, pstFaceManageInfo->nChannel);
			}

			iter++;
		}
	}
}

void CJLNDevice::OperateSubFaceMonitorLink(BOOL bOpen)
{

	vector<st_faceManageInfo>::iterator iter;
	st_faceManageInfo* pstFaceManageInfo;
	BOOL bRet = FALSE;



	if (m_vectorFaceMonitorInfo.size() > 0)
	{
		iter = m_vectorFaceMonitorInfo.begin();
		while (iter != m_vectorFaceMonitorInfo.end())
		{
			pstFaceManageInfo = &*iter;
			if (bOpen)
			{
				bRet = StartReceiveFaceCompareResult(m_lUserLoginID, pstFaceManageInfo->nChannel);
				if (bRet)
				{
					iter = m_vectorFaceMonitorInfo.erase(iter);
					continue;
				}
			}
			else
			{
				bRet = StopReceiveFaceCompareResult(pstFaceManageInfo->lFaceManageID, pstFaceManageInfo->nChannel);
			}

			iter++;
		}
	}
}


void CJLNDevice::OperateSubSnapLink(BOOL bOpen)
{
	vector<st_faceManageInfo>::iterator iter;
	st_faceManageInfo* pstFaceManageInfo;
	BOOL bRet = FALSE;

	if (m_vectorSnapInfo.size() > 0)
	{
		iter = m_vectorSnapInfo.begin();
		while (iter != m_vectorSnapInfo.end())
		{
			pstFaceManageInfo = &*iter;
			if (bOpen)
			{
				bRet = StartReceiveSnapResult(m_lUserLoginID, pstFaceManageInfo->nChannel);
				if (bRet)
				{
					iter = m_vectorSnapInfo.erase(iter);
					continue;
				}
			}
			else
			{
				bRet = StopReceiveSanpResult(pstFaceManageInfo->lFaceManageID, pstFaceManageInfo->nChannel);
			}

			iter++;

		}
	}
}


void CJLNDevice::OperateSubPlay(BOOL bOpen)			//播放链路
{
	list<st_playerInfoSimple>::iterator iterPlay;
	JVT_LONG lRet = 0;
	char strLog[2048] = { 0 };
	SYSTEMTIME sysTime = { 0 };
	GetLocalTime(&sysTime);

	//视频通道处理
	if (m_listPlayInfo.size() > 0)
	{
		for (iterPlay = m_listPlayInfo.begin(); iterPlay != m_listPlayInfo.end();)
		{
			st_playerInfoSimple stPlayInfo = *iterPlay;
			if (bOpen)
			{

				if (Client::instance()->PreviewPro->widgets[stPlayInfo.nWndNum].widget->m_dspWndinfo.bVideo)
				{
					break;
				}
				lRet = OpenChannel(stPlayInfo.nChannel, stPlayInfo.nStreamType, stPlayInfo.hPlayWnd, stPlayInfo.nChannel);

				if (-1 == lRet)
				{
					mlog(LOG_ERR, "[%4d-%02d-%02d %02d:%02d:%02d] Open Channel failed result channel = %d,iRet = %d\n", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
						sysTime.wHour, sysTime.wMinute, sysTime.wSecond, stPlayInfo.nChannel, lRet);
				}
				else
				{
					if (stPlayInfo.bEnableAudio)
					{
						EnableAudio(stPlayInfo.hPlayWnd, FALSE);
						EnableAudio(stPlayInfo.hPlayWnd, TRUE);
					}

					if (stPlayInfo.bSaveStream)
					{
						//::PostMessage(::GetParent(stPlayInfo.hPlayWnd), RECONNECT_NOTIFY_MSG, 0, RECONNECT_NOTIFY_LOCALRECORD);
						Client::instance()->deiceLostEvent = new CompareEvent(CompareEvent::getType(CET_DEVICELOST));
						QApplication::postEvent(NULL, Client::instance()->deiceLostEvent);
					}
					iterPlay = m_listPlayInfo.erase(iterPlay);

					mlog(LOG_INFO, "[%4d-%02d-%02d %02d:%02d:%02d] Open Channel success result channel = %d,iRet = %d\n", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
						sysTime.wHour, sysTime.wMinute, sysTime.wSecond, stPlayInfo.nChannel, lRet);

				}

			}
			else
			{
				CloseChannel(stPlayInfo.hPlayWnd);
			}
			iterPlay++;
		}
	}
}
void CJLNDevice::ConstractSubLink()		//保存子链路
{
	//记录播放信息
	jln_mutex.lock();
	int iPort;
	for (iPort = 0; iPort < MAX_JL_PLAYER; iPort++)
	{
		if (g_JlnPlayerInfo[iPort].nDevID == m_lUserLoginID && NULL != g_JlnPlayerInfo[iPort].hPlayWnd)
		{
			st_playerInfoSimple stPlayInfoTemp;
			memset(&stPlayInfoTemp, 0, sizeof(stPlayInfoTemp));
			stPlayInfoTemp.bSaveStream = g_JlnPlayerInfo[iPort].bSaveStream;
			stPlayInfoTemp.bEnableAudio = g_JlnPlayerInfo[iPort].bEnableAudio;
			stPlayInfoTemp.nStreamType = g_JlnPlayerInfo[iPort].nStreamType;
			stPlayInfoTemp.nChannel = g_JlnPlayerInfo[iPort].nChannel;
			stPlayInfoTemp.nMode = g_JlnPlayerInfo[iPort].nMode;
			stPlayInfoTemp.hPlayWnd = g_JlnPlayerInfo[iPort].hPlayWnd;
			stPlayInfoTemp.bSpeak = g_JlnPlayerInfo[iPort].bSpeak;
			m_listPlayInfo.push_back(stPlayInfoTemp);
		}
	}
	jln_mutex.unlock();
	//记录比对信息

	for (int i = 0; i < MAX_CHANNEL; i++)
	{
		if (m_lCompareID[i] > 0)
		{
			st_faceManageInfo stFaceManageInfo = { 0 };
			stFaceManageInfo.nChannel = i;
			stFaceManageInfo.lFaceManageID = m_lCompareID[i];
			m_vectorCompareInfo.push_back(stFaceManageInfo);
		}

		if (m_lSnapID[i] > 0)
		{
			st_faceManageInfo stFaceManageInfo = { 0 };
			stFaceManageInfo.nChannel = i;
			stFaceManageInfo.lFaceManageID = m_lSnapID[i];
			m_vectorSnapInfo.push_back(stFaceManageInfo);
		}

		if (m_lImExID[i] > 0)
		{
			st_faceManageInfo stFaceManageInfo = { 0 };
			stFaceManageInfo.nChannel = i;
			stFaceManageInfo.lFaceManageID = m_lImExID[i];
			m_vectorImExInfo.push_back(stFaceManageInfo);
		}
		if (m_lFaceMonitorID[i] > 0)
		{
			st_faceManageInfo stFaceManageInfo = { 0 };
			stFaceManageInfo.nChannel = i;
			stFaceManageInfo.lFaceManageID = m_lFaceMonitorID[i];
			m_vectorFaceMonitorInfo.push_back(stFaceManageInfo);
		}
	}
}

void CJLNDevice::OperateSubImExLink(BOOL bOpen)
{
	vector<st_faceManageInfo>::iterator iter;
	st_faceManageInfo* pstFaceManageInfo;
	BOOL bRet = FALSE;

	if (m_vectorImExInfo.size() > 0)
	{
		iter = m_vectorImExInfo.begin();
		while (iter != m_vectorImExInfo.end())
		{
			pstFaceManageInfo = &*iter;
			if (bOpen)
			{
				bRet = StartImportAndExport(m_lUserLoginID, pstFaceManageInfo->nChannel);
				if (bRet)
				{
					iter = m_vectorImExInfo.erase(iter);
					continue;
				}
			}
			else
			{
				bRet = StopImportAndExport(pstFaceManageInfo->lFaceManageID, pstFaceManageInfo->nChannel);
			}

			iter++;

		}
	}
}

BOOL CJLNDevice::StopImportAndExport(JVT_LONG lImExID, int nChannel)
{
	if (m_bSupportNew)
	{
		StopListManagement(lImExID, nChannel);
	}
	else
	{
		if (m_lImExID[nChannel] > 0)
		{
			VideoNet_DeleteBlackAndWhiteListCallBack(m_lImExID[nChannel], FacePicImportExportCallback, (JVT_DWORD)this);
			VideoNet_StopSendBlackAndWhiteList(m_lImExID[nChannel]);
			m_lImExID[nChannel] = -1;
		}
	}
	return TRUE;
}

BOOL CJLNDevice::StopListManagement(JVT_LONG lListID, int nChannel)
{
	if (m_lImExID[nChannel] > 0)
	{
		VideoNet_DeleteListManagementCallBack(m_lImExID[nChannel], ListManagementCallBack, (JVT_DWORD)this);
		VideoNet_StopListManagement(m_lImExID[nChannel]);
		m_lImExID[nChannel] = -1;
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
	char strLog[2048] = {0};

	time_t tmNow = time(NULL);
	struct tm tmLocal;
	tmLocal = *localtime(&tmNow);
	DWORD dwTickTime = GetTickCount();
	while(!m_bStopAlarmConfig)
	{
		for (int ix = 0; ix < m_nChannelNum;ix++)
		{

			for(int ij = 0; ij < ALARM_EventCount;ij++)
			{

				TabAlarmConf_t stTabAlarmConf;
				memset(&stTabAlarmConf,0,sizeof(stTabAlarmConf));
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
              

				if (m_bStopAlarmConfig)
				{
					break;
				}
				
				Sleep(10);
			}
		}
		Sleep(100);
		break;
	}

	
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

	StopReceiveFaceCompareResult(m_lCompareID[nChannel], nChannel);

	m_lCompareID[nChannel] = VideoNet_StartReceiveFaceCompareResultEx(lLoginID, nChannel, &compinfo);
	if (m_lCompareID[nChannel] > 0)
	{
		bRet = VideoNet_SetFaceCompareResultCallBack(m_lCompareID[nChannel], FaceCompareResultCallback, (JVT_DWORD)this);
		if (!bRet)
		{
			VideoNet_StopReceiveFaceCompareResult(m_lCompareID[nChannel]);
			m_lCompareID[nChannel] = -1;
		}
	}

	return bRet;
}

int CJLNDevice::FaceCompareResultCallback(JVT_LONG lRealFaceHandle,char *pBuf, long nDataLen, JVT_DWORD dwUser)
{
	CJLNDevice *pJLNDevice = (CJLNDevice *)dwUser;
	SDK_FACECOMPARE_RESULT *pstResulAlarm = (SDK_FACECOMPARE_RESULT *)pBuf;
	SMART_FACE_CMP_QUERY_INFO stCMPInfo = {0};
	
	QString strName =NULL;
	QString strUserId = NULL;
	int nTemp = 0;
	strUserId = QString::fromLocal8Bit(pstResulAlarm->picnameComp);
	if (strUserId.length() > 0)
	{
		nTemp = strUserId.indexOf("_");
		strName = QString("%1-%2").arg(strUserId.left(nTemp), strUserId.mid(nTemp + 1));
	}

	stCMPInfo.sLibRowid			= 0;				//库行号
	stCMPInfo.sLibSimilarity	= pstResulAlarm->result;			//相似度
	strcpy(stCMPInfo.sName, strUserId.left(nTemp).toLocal8Bit().data());				//名称(可选)
	strcpy(stCMPInfo.sUserID, strUserId.mid(nTemp + 1, strUserId.indexOf(".") - nTemp - 1).toLocal8Bit().data());				//用户ID(可选)
	strcpy(stCMPInfo.sLibSnapTime, (char*)pstResulAlarm->SnapTime);		//抓拍时间
	stCMPInfo.sLibChannelid		= pstResulAlarm->channelid;			//通道号
	stCMPInfo.sLibMode			= pstResulAlarm->wbmode;				//名单	类型		
	stCMPInfo.sSysListID		= 0;				//系统ID
	stCMPInfo.nLibGuest			= pstResulAlarm->guest;				//客流统计
	stCMPInfo.cLibAge			= pstResulAlarm->Age;      			//年龄 
	stCMPInfo.cLibGender		= pstResulAlarm->Gender;				//性别
	stCMPInfo.cLibGlasses		= pstResulAlarm->Glasses; 			//眼镜  
	stCMPInfo.cLibMask			= pstResulAlarm->Mask; 				//面具
	stCMPInfo.cLibRace			= pstResulAlarm->Race;				//种族  
	stCMPInfo.cLibEye			= pstResulAlarm->Eye;				//眼睛 	
	stCMPInfo.cLibAttractive	= pstResulAlarm->Attractive;			//魅力值
	stCMPInfo.cLibBeard			= pstResulAlarm->Beard;				//胡子
	stCMPInfo.cLibEmotion		= pstResulAlarm->Emotion;			//表情	
	strcpy(stCMPInfo.sSnappicname, pstResulAlarm->picnameSnap);		//实时比对图片名字
	strcpy(stCMPInfo.sLibPicName, pstResulAlarm->picnameComp);		//库图片名称
	strcpy(stCMPInfo.cDevName, pJLNDevice->m_pDevInfo->szDevName);
	strcpy(stCMPInfo.cDeviceIP, pJLNDevice->m_pDevInfo->szIpAddr);
	stCMPInfo.pLibPicBuf		= pstResulAlarm->pCompImgData;			//库图数据
	stCMPInfo.dwLibPicLen		= pstResulAlarm->iCompImgSize;
	stCMPInfo.dwSnapPicLen		= pstResulAlarm->iSnapImgSize;
	stCMPInfo.pSnapPicBuf		= pstResulAlarm->pSnapImgData;				//抓拍图数据

	pJLNDevice->ProcessSnapData(&stCMPInfo);
	
	return 0;	
}


BOOL CJLNDevice::StopCompare(int nChannel)
{
	BOOL bRet = FALSE;
	EnterCriticalSection(&m_lockSubOperation);
	if (m_lCompareID[nChannel] > 0)
	{
		bRet = StopReceiveFaceCompareResult(m_lCompareID[nChannel], nChannel);
	}
	if (bRet)
	{
		m_lCompareID[nChannel] = -1;
	}

	LeaveCriticalSection(&m_lockSubOperation);
	return bRet;
}

int CJLNDevice::SavePicture(SDK_FACECOMPARE_RESULT* pCompareInfo)
{
	FILE *pPicsnapFile = NULL;
	FILE *pPiccompFile = NULL;
	FILE *pIndexFile = NULL;
	QString strFailed = NULL;
	QString stringMsg = NULL;
	char chSnapfilename[MAX_PATH] = {0};	//抓拍图
	char chCompfilename[MAX_PATH] = {0};	//库图
	char chSnapPath[MAX_PATH] = {0};		//路径
	char chIndexFileName[MAX_PATH] = {0};//索引文件名
	char chTime[16] = {0};
	memcpy(chTime, pCompareInfo->SnapTime, 10);

	sprintf(m_szSnapPath, "%s\\%s\\%s\\%d",set->g_ClientCfg.szSnapPath, chTime, pCompareInfo->cDeviceIP, pCompareInfo->channelid);	//路径
	sprintf(chSnapfilename,"%s\\%s",m_szSnapPath, pCompareInfo->picnameSnap);
	sprintf(chCompfilename,"%s\\%s",m_szSnapPath, pCompareInfo->picnameComp);
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
			int iRet = fwrite(pCompareInfo->pSnapImgData, 1, pCompareInfo->iSnapImgSize,pPicsnapFile);
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
				qDebug()<<"strFailed";
			    stringMsg = QString("'%1':'%2'").arg(strFailed).arg(QString(QLatin1String(chSnapfilename)));
				mlog(LOG_ERR, stringMsg.toLatin1().data());
			}
		}
	}


	if(0 < strlen(pCompareInfo->picnameComp) && 0 < pCompareInfo->iCompImgSize)  //库图片
	{
		pPiccompFile = fopen(chCompfilename,"wb+");
		if(NULL != pPiccompFile)
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

BOOL CJLNDevice::StopReceiveFaceCompareResult(JVT_LONG lCompareID, int nChannel)
{
	if (lCompareID > 0)
	{
		VideoNet_DeleteFaceCompareResultCallBack(lCompareID, FaceCompareResultCallback, (JVT_DWORD)this);
		VideoNet_StopReceiveFaceCompareResult(lCompareID);
		m_lCompareID[nChannel] = -1;
	}
	return TRUE;
}

S32 CJLNDevice::CapturePic(HWND hwnd,const char* szFileName)
{

	int i = GetPortId(hwnd);
	if(i == -1)
		return -1;

	BOOL bRet = VideoPlayer_CatchPic(i, szFileName,0); //0:BMP 1:JPG
	if (!bRet)
	{
		return -1;
	}


	return bRet;
}

//开始接受抓拍
JVT_LONG CJLNDevice::StartReceiveSnapResult(JVT_LONG lLoginID, int nChannel)	
{	
	JVT_LONG lSnapID = 0;
	int nEnable = 1;

	lSnapID = VideoNet_StartReceiveFaceImageFileEx(lLoginID, nChannel, nEnable);
	if (lSnapID > 0)
	{
		BOOL bRet = VideoNet_SetFaceImageDataCallBack(lSnapID, FaceSnapCallback, (JVT_DWORD)this);
		if (!bRet)
		{
			VideoNet_StopReceiveFaceImageFile(lSnapID);
			lSnapID = -1;
		}
		else
		{
			m_lSnapID[nChannel] = lSnapID;
		}
	}
	return lSnapID;

}

BOOL CJLNDevice::FaceSnapCallback(JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize,
	SDK_FA_PICTURE_HEAD *pPictureHead, SDK_FACE_ATTR* pPictureAttr, JVT_DWORD dwUser)
{
	CJLNDevice *pJLNDevice = (CJLNDevice *)dwUser;
	SMART_FACE_CMP_QUERY_INFO stCMPInfo = {0};

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

BOOL CJLNDevice::StartImportAndExport(JVT_LONG lLoginID, int nChannel)
{
	JVT_LONG lImExID = 0;
	BOOL bRet = FALSE;

	EnterCriticalSection(&m_lockSubOperation);
	if (m_lImExID[nChannel] > 0)
	{
		LeaveCriticalSection(&m_lockSubOperation);
		return TRUE;
	}

	if (m_bSupportNew)
	{
		bRet = StartListManagement(lLoginID, nChannel);
	}
	else
	{
		m_lImExID[nChannel] = VideoNet_StartSendBlackAndWhiteList(lLoginID, nChannel);
		if (m_lImExID[nChannel] > 0)
		{
			bRet = VideoNet_SetBlackAndWhiteListCallBack(m_lImExID[nChannel], FacePicImportExportCallback, (JVT_DWORD)this);
			if (!bRet)
			{
				VideoNet_StopSendBlackAndWhiteList(m_lImExID[nChannel]);
				m_lImExID[nChannel] = -1;
			}
		}
	}
	LeaveCriticalSection(&m_lockSubOperation);
	return bRet;
}

BOOL CJLNDevice::StartListManagement(JVT_LONG lLoginID, int nChannel)
{
	BOOL bRet = FALSE;

	if (m_lImExID[nChannel] > 0)
	{
		return m_lImExID[nChannel];
	}

	m_lImExID[nChannel] = VideoNet_StartListManagement(lLoginID, nChannel);
	if (m_lImExID[nChannel] > 0)
	{
		BOOL bRet = VideoNet_SetListManagementCallBack(m_lImExID[nChannel], ListManagementCallBack, (JVT_DWORD)this);
		if (!bRet)
		{
			VideoNet_StopListManagement(m_lImExID[nChannel]);
			m_lImExID[nChannel] = -1;
		}
	}
	return bRet;
}

int CJLNDevice::ListManagementCallBack(JVT_LONG lSubFaceHandle, char* pBuffer, long lbufsize, char* pConfig, JVT_DWORD dwUser)
{
	CJLNDevice* pDevice = (CJLNDevice*)dwUser;
	SDK_SMART_WB_CONFIG_EX* pConfigEx = (SDK_SMART_WB_CONFIG_EX*)pConfig;
	if (Client::instance()->m_dlgExport != NULL)
	{
		if (pConfigEx->iOpMode == OUT_PICTURE)
		{
			if (Client::instance()->m_dlgExport->m_bQueryStat)
			{
				SetEvent(Client::instance()->m_dlgExport->m_hQueryEvent);
				pDevice->SaveLibPic(pConfigEx, pBuffer, lbufsize);
				return 0;
			}
			if (Client::instance()->m_dlgExport->attend_bQueryStat)
			{
				SetEvent(Client::instance()->m_dlgExport->m_hWorkWaitEvent);
				memcpy(Client::instance()->m_dlgExport->m_pAttendInfo, pConfigEx, sizeof(SDK_SMART_WB_CONFIG_EX));
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
			Client::instance()->m_dlgExport->ListManageCallBack_Export(lSubFaceHandle, pBuffer, lbufsize, pConfigEx, dwUser);
			break;
		case IN_PICTURE_ADD:		//通过抓拍添加黑白名单
		case IN_PICTURE_ADD_SNAP:	//导出黑白名单库中单张图片
			if (Client::instance()->m_dlgExport->m_bImport)
			{
				Client::instance()->m_dlgExport->AddCallBackMessage(pBuffer, lbufsize, pConfigEx);
			}
			else
			{
				Client::instance()->m_dlgExport->ListManageCallBack_Inport(lSubFaceHandle, pBuffer, lbufsize, pConfigEx, dwUser);
			}
			break;
		case OUT_ATTENDANCE:
			Client::instance()->m_dlgExport->FaceWorkListCallBack(pBuffer, lbufsize, pConfigEx);
			break;
		case OUT_CMP_INFO:
			Client::instance()->m_dlgExport->CmpRecordCallBack(pBuffer, lbufsize, pConfigEx);
			break;
		}
	}
	return 0;
}

int CJLNDevice::FacePicImportExportCallback(JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize,SDK_FA_BLACKANDWHITELIST_CONFIG *pConfig,JVT_DWORD dwUser)
{
	if (Client::instance() != NULL)
	{
		switch (pConfig->byOutMode)
		{
		case OUT_INDEX:
		case OUT_PICTURE:
		case OUT_PICTURE_COMP:
		case OUT_PICTURE_DEL:
		case OUT_PICTURE_DELALL:
			Client::instance()->m_dlgExport->FaceCallBack(lSubFaceHandle, pBuffer,lbufsize,pConfig,dwUser);
			break;
		case IN_PICTURE_ADD:		//通过抓拍添加黑白名单
		case IN_PICTURE_ADD_SNAP:	//导出黑白名单库中单张图片
			if (Client::instance()->m_dlgExport->m_bImport)
			{
				Client::instance()->m_dlgExport->AddCallBackMessage(pBuffer, lbufsize, pConfig);
			}
			else
			{
				Client::instance()->m_dlgExport->FaceCallBack_Import(lSubFaceHandle, pBuffer,lbufsize,pConfig,dwUser);
			}
			break;
		}		
	}
	return 0;
}

BOOL CJLNDevice::StartSnapLink(JVT_LONG lLoginID, int nChannel, int nChannelType)
{
	if (m_bSupportNew)
	{
		return StartFaceMonitor(lLoginID, nChannel);
	}
	else
	{
		if (nChannelType == CHANNELINFO_TYPE_COMPARE)
		{
			return StartReceiveFaceCompareResult(lLoginID, nChannel);
		}
		else
		{
			return StartReceiveSnapResult(lLoginID, nChannel);
		}
	}
}

BOOL CJLNDevice::StopSnapLink(int nChannel, int nChannelType)
{
	if (m_bSupportNew)
	{
		return StopFaceMonitor(nChannel);
	}
	else
	{
		if (nChannelType == CHANNELINFO_TYPE_COMPARE)
		{
			return StopCompare(nChannel);
		}
		else
		{
			return StopSnap(nChannel);
		}
	}
}

BOOL CJLNDevice::StartFaceMonitor(JVT_LONG lLoginID, int nChannel)
{
	BOOL bRet = FALSE;
	SDK_FACEMONITOR_INFO_FLAG stCompinfoFlag = {0};

	stCompinfoFlag.nCaptureEn = 1;
	stCompinfoFlag.nFaceAttrEn = 1;
	stCompinfoFlag.nFaceCmpInfoEn = 1;
	stCompinfoFlag.nLibPicEn = 1;
	StopFaceMonitor(m_lFaceMonitorID[nChannel]);

	EnterCriticalSection(&m_lockSubOperation);
	m_lFaceMonitorID[nChannel] = VideoNet_StartReceiveFaceMonitor(lLoginID, 0, &stCompinfoFlag);
	if (m_lFaceMonitorID[nChannel] > 0)
	{
		bRet = VideoNet_SetFaceMonitorCallBack(m_lFaceMonitorID[nChannel], FaceMonitorCallBack, (JVT_DWORD)this);
		if (!bRet)
		{
			VideoNet_StopReceiveFaceMonitor(m_lFaceMonitorID[nChannel]);
			m_lFaceMonitorID[nChannel] = -1;
		}
	}
	else
	{	
		int nErr = VideoNet_GetLastError();
		QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("打开图片失败，返回值'%1'").arg(nErr));
		return false;
	}
	LeaveCriticalSection(&m_lockSubOperation);
	return bRet;
}

BOOL CJLNDevice::StopFaceMonitor(int nChannel)
{
	EnterCriticalSection(&m_lockSubOperation);
	if (m_lFaceMonitorID[nChannel] > 0)
	{
		VideoNet_DeleteFaceMonitorCallBack(m_lFaceMonitorID[nChannel], FaceMonitorCallBack, (JVT_DWORD)this);
		VideoNet_StopReceiveFaceMonitor(m_lFaceMonitorID[nChannel]);
		m_lFaceMonitorID[nChannel] = -1;
	}
	LeaveCriticalSection(&m_lockSubOperation);
	return TRUE;
}

int CJLNDevice::FaceMonitorCallBack(JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize, JVT_DWORD dwUser)
{
	CJLNDevice* pJLNDevice = (CJLNDevice*)dwUser;
	if (pJLNDevice)
	{
		pJLNDevice->ProcessMonitorData(pBuffer, lbufsize);
	}
	return 0;
}

void CJLNDevice::ProcessMonitorData(char* pBuffer, unsigned long dwDatalen)
{
	SDK_FACE_MONITOR_INFO* pMonitorInfo = (SDK_FACE_MONITOR_INFO*)pBuffer;
	unsigned long dwLen = 0;
	if (!pMonitorInfo || (dwDatalen < sizeof(SDK_FACE_MONITOR_INFO)))
	{
		return;
	}


	SMART_FACE_CMP_QUERY_INFO stCMPInfo = { 0 };

	stCMPInfo.sLibRowid = pMonitorInfo->stFaceCompareInfo.stIndexInfo.libindex;				//库行号
	stCMPInfo.sLibSimilarity = pMonitorInfo->stFaceCompareInfo.fCompareResult;			//相似度
	strcpy(stCMPInfo.sName, pMonitorInfo->stFaceCompareInfo.stIndexInfo.name);				//名称(可选)
	strcpy(stCMPInfo.sUserID, pMonitorInfo->stFaceCompareInfo.stIndexInfo.usrid);				//用户ID(可选)
	strcpy(stCMPInfo.sLibSnapTime, pMonitorInfo->stFaceAttr.stFaceTime);		//抓拍时间
	stCMPInfo.sLibChannelid = pMonitorInfo->stPictureHead.channelid;			//通道号
	stCMPInfo.sLibMode = pMonitorInfo->stFaceCompareInfo.stIndexInfo.listmode;				//名单	类型		
	stCMPInfo.sSysListID = pMonitorInfo->stFaceCompareInfo.stIndexInfo.syslistid;				//系统ID
	stCMPInfo.nLibGuest = pMonitorInfo->stFaceCompareInfo.stIndexInfo.count;				//客流统计
	stCMPInfo.cLibAge = pMonitorInfo->stFaceAttr.stFaceAttribute.byAge;      			//年龄 
	stCMPInfo.cLibGender = pMonitorInfo->stFaceAttr.stFaceAttribute.byGender;				//性别
	stCMPInfo.cLibGlasses = pMonitorInfo->stFaceAttr.stFaceAttribute.byGlasses; 			//眼镜  
	stCMPInfo.cLibMask = pMonitorInfo->stFaceAttr.stFaceAttribute.byMask; 				//面具
	stCMPInfo.cLibRace = pMonitorInfo->stFaceAttr.stFaceAttribute.byEye;				//种族  
	stCMPInfo.cLibEye = pMonitorInfo->stFaceAttr.stFaceAttribute.byEye;				//眼睛 	
	stCMPInfo.cLibAttractive = pMonitorInfo->stFaceAttr.stFaceAttribute.byAttractive;			//魅力值
	stCMPInfo.cLibBeard = pMonitorInfo->stFaceAttr.stFaceAttribute.byBeard;				//胡子
	stCMPInfo.cLibEmotion = pMonitorInfo->stFaceAttr.stFaceAttribute.byEmotion;			//表情
	stCMPInfo.nFaceAlarm = pMonitorInfo->stFaceCompareInfo.nFaceAlarm;
	strcpy(stCMPInfo.cDeviceIP, m_pDevInfo->szIpAddr);
	strcpy(stCMPInfo.sLibSnapTime, pMonitorInfo->stFaceAttr.stFaceTime);
	strcpy(stCMPInfo.cDevName, m_pDevInfo->szDevName);

	dwLen = sizeof(SDK_FACE_MONITOR_INFO);

	if (pMonitorInfo->stPictureHead.nUserInfo1Len)											//用户定义数据
	{
		dwLen += MAX_USER_DATA_LEN;
	}

	if (pMonitorInfo->stPictureHead.nFacePicLen > 0)		//抓拍图
	{
		stCMPInfo.pSnapPicBuf = (char*)(pBuffer + dwLen);
		stCMPInfo.dwSnapPicLen = pMonitorInfo->stPictureHead.nFacePicLen;
		strcpy(stCMPInfo.sSnappicname, pMonitorInfo->stFaceAttr.stFacePicname);
		dwLen += pMonitorInfo->stPictureHead.nFacePicLen;
	}

	if (pMonitorInfo->stPictureHead.nFramePicLen > 0)		//背景图
	{
		stCMPInfo.pBackPicBuf = (char*)(pBuffer + dwLen);
		stCMPInfo.dwBackPicLen = pMonitorInfo->stPictureHead.nFramePicLen;
		strcpy(stCMPInfo.sBackPicName, pMonitorInfo->stFaceAttr.stFramePicname);
		dwLen += pMonitorInfo->stPictureHead.nFramePicLen;
	}

	if (pMonitorInfo->stPictureHead.nLibPicLen > 0)			//底库图片
	{
		stCMPInfo.pLibPicBuf = (char*)(pBuffer + dwLen);
		stCMPInfo.dwLibPicLen = pMonitorInfo->stPictureHead.nLibPicLen;
		strcpy(stCMPInfo.sLibPicName, pMonitorInfo->stFaceCompareInfo.stIndexInfo.picname);
		dwLen += pMonitorInfo->stPictureHead.nLibPicLen;
	}
	ProcessSnapData(&stCMPInfo);
}

int CJLNDevice::ProcessSnapData(SMART_FACE_CMP_QUERY_INFO* pCompareInfo)
{
	char chSnapfilename[MAX_PATH] = {0};	//抓拍图
	char chCompfilename[MAX_PATH] = {0};	//库图
	char chIndexFileName[MAX_PATH] = {0};//索引文件名
	char chTime[16] = {0};
	memcpy(chTime, pCompareInfo->sLibSnapTime, 10);

	int iRet = 0;

	sprintf(m_szSnapPath, "%s\\%s\\%s\\%d", set->g_ClientCfg.szSnapPath, chTime, pCompareInfo->cDeviceIP, pCompareInfo->sLibChannelid);	//路径
	sprintf(chSnapfilename,"%s\\%s",m_szSnapPath, pCompareInfo->sSnappicname);
	sprintf(chCompfilename,"%s\\%s",m_szSnapPath, pCompareInfo->sLibPicName);
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
	
	if(pCompareInfo->pLibPicBuf && 0 < pCompareInfo->dwLibPicLen
		&& !fileInfo.exists())												//库图片
	{
		WriteFile(chCompfilename, pCompareInfo->pLibPicBuf, pCompareInfo->dwLibPicLen);
	}

	if (Client::instance() != NULL)
	{
		Client::instance()->PreviewPro->ReceiveSnap((char*)pCompareInfo);
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
	if(NULL != pFile)
	{
		fwrite(pFileData, 1, nDatalen, pFile);
	}
	else
	{
		
		strErr = QStringLiteral("创建文件失败'%1'").arg(QString::fromLocal8Bit(pFileName));
		mlog(LOG_ERR, strErr.toLatin1().data());
	}

	if(pFile)
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

	LONG lRealHandle = GetPlayHandle(hwnd);
	if (lRealHandle == 0)
		return -1;

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
		jln_mutex.lock();
		g_JlnPlayerInfo[i].bSaveStream = FALSE;
		memset(g_JlnPlayerInfo[i].szFileName, '\0', sizeof(g_JlnPlayerInfo[i].szFileName));
		jln_mutex.unlock();
	}
	else
	{

		BOOL bRet = VideoPlayer_StartDataRecord(i, szFileName, MEDIA_FILE_NONE);
		if (!bRet)
		{
			return -1;
		}
		jln_mutex.lock();
		strcpy(g_JlnPlayerInfo[i].szFileName, szFileName);
		g_JlnPlayerInfo[i].SerialNum = 1;
		g_JlnPlayerInfo[i].TimeStamp = 40;
		g_JlnPlayerInfo[i].ASerialNum = 1;
		g_JlnPlayerInfo[i].ATimeStamp = 40;

		g_JlnPlayerInfo[i].bSaveStream = TRUE;
		jln_mutex.unlock();
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
	jln_mutex.lock();
	g_JlnPlayerInfo[i].bEnableAudio = bEnable;
	jln_mutex.unlock();
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

S32 CJLNDevice::Speak(HWND hwnd, BOOL bStart)
{
	int nChannel = GetPlayChannel(hwnd);
	if (-1 == nChannel)
	{
		return -1;
	}

	if (!bStart)
	{
		if (!bDevTalk)
		{
			return -1;
		}
		BOOL bRet = VideoNet_StopDevTalk(m_lUserLoginID, nChannel - 1);
		if (!bRet)
		{
			return -1;
		}
		bDevTalk = FALSE;
	}
	else
	{
		BOOL bRet = VideoNet_StartDevTalk(m_lUserLoginID, nChannel - 1);
		if (!bRet)
		{
			return -1;
		}
		bDevTalk = TRUE;
	}
	return 0;
}

S32 CJLNDevice::GetDeviceRecordStatus(HWND hwnd)
{
	return -1;
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
