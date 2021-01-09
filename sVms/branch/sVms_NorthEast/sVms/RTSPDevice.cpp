#include "RTSPDevice.h"
#include "rtspClientAPI.h"
#include "AVPlay.h"
#include "player.h"
#include "frameHead.h"
#include <assert.h>
#include <Windows.h>

#define MAX_RTSP_PLAYER 256
st_playerInfo g_RtspPlayerInfo[MAX_RTSP_PLAYER];
std::map<LONG ,int> g_mapRTSPPlayerInfo;

static S32  GetPortId(LONG lHandle)
{


	std::map<LONG, int>::const_iterator it = g_mapRTSPPlayerInfo.find(lHandle);
	if(it != g_mapRTSPPlayerInfo.end())
	{

		return it->second;
	}

	return -1;
}
void  rtsp_callback(void *session, unsigned short seq,unsigned long timestamp,int payloadtype,int packettype,char* buf,unsigned long bufsize,void *userdata)
{
	if(payloadtype != RTP_H264)
	{
		
		return;
	}

	int nPort = (int)userdata;
	Codec_Head_t *videoInfo = (Codec_Head_t *)buf;
	if(videoInfo->Syncode != SYN_START_CODE)
	{
		return;
	}
	bool ret = DVR_PLAYER_WriteStream(nPort, buf,bufsize);
	//	if(!ret)
	//		TRACE("DVR_PLAYER_WriteStream error\n");

	//	TRACE("[%d] [%d] WriteStreamData size:%d buf:%x ...\n",nPort,GetCurrentThreadId(),bufsize,buf);
#if 0

	_LARGE_INTEGER time_start;    /*开始时间*/
	_LARGE_INTEGER time_over;        /*结束时间*/
	double dqFreq;                /*计时器频率*/
	LARGE_INTEGER f;            /*计时器频率*/
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);

	int ret = WriteStreamData ( nPort, buf, bufsize, videoInfo->FrameType , VIDEO_FRAME);
	//int ret = WriteStreamData ( nPort, buf, bufsize, I_FRAME , VIDEO_FRAME);

	QueryPerformanceCounter(&time_over); 
	char str[128];
	sprintf(str,"==frame %d WriteStreamData %lf==\n",videoInfo->FrameType,(time_over.QuadPart-time_start.QuadPart)/dqFreq);
	OutputDebugString(str);
#endif
	//TRACE("WriteStreamData ret:%d\n",ret);
	int i = GetPortId((LONG)session);
	if(g_RtspPlayerInfo[i].bSaveStream)
	{
		if(g_RtspPlayerInfo[i].pf == NULL)
		{
			g_RtspPlayerInfo[i].pf = fopen(g_RtspPlayerInfo[i].szFileName,"w+b");
			if(g_RtspPlayerInfo[i].pf == NULL)
				return ;
		}
		fwrite((BYTE*)buf,1,bufsize ,g_RtspPlayerInfo[i].pf);
		fflush(g_RtspPlayerInfo[i].pf);
	}
	else
	{
		if(g_RtspPlayerInfo[i].pf != NULL)
		{
			fclose(g_RtspPlayerInfo[i].pf);
		}
		g_RtspPlayerInfo[i].pf = NULL;
	}
}


CRTSPDevice::CRTSPDevice(void)
{
}


CRTSPDevice::~CRTSPDevice(void)
{
}

S32 CRTSPDevice::Login()
{
	if(m_pDevInfo->nManufaceturer != DEVINFO_MANUFACTURER_BC)
		return 0;

	if(m_bSocketCreate)
		return 0;
	/*
	m_nBCNVRSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(m_nBCNVRSocket == INVALID_SOCKET )
		return -1;
	//Set option
	char reuse = 1;
	
	int err = setsockopt(m_nBCNVRSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
	if(err < 0)
	{
		closesocket(m_nBCNVRSocket);
		return -1;
	}
	m_bSocketCreate = TRUE;
	//2条线程，1条发送，1条接收
	//创建心跳线程
	m_bCNVTThreadExit = FALSE;
	//CWinThread *pThread = AfxBeginThread(BCNVTThread, this);
	//CWinThread *pThread2 = AfxBeginThread(BCNVTAlarmThread, this);
	return 0;*/
	return 0;
}

S32 CRTSPDevice::OpenChannel(U32 nChannel,U32 nStream,HWND hwnd, int nWndNum)
{
	IPC_TYPE ipc_type;
	switch(m_pDevInfo->nManufaceturer)
	{
	case DEVINFO_MANUFACTURER_HH:
		ipc_type = SZ_HH_IPC;
		break;
	case DEVINFO_MANUFACTURER_JL:
		ipc_type = SZ_JL_IPC;
		break;
	case DEVINFO_MANUFACTURER_TST:
		ipc_type = SZ_TST_IPC;
		break;
	case DEVINFO_MANUFACTURER_HIK:
		ipc_type = HK_IPC;
		break;
	case DEVINFO_MANUFACTURER_BC:
		ipc_type = IPC_MAX;
		break;
	default:
		return -1;
	}
#if 1
	long nPort;
	while(1)
	{
		DVR_PLAYER_GetFreePort(&nPort);
		if(nPort != -1)
		{
			if(	DVR_PLAYER_OpenStream(nPort,10240000))
				break;
		}
	}
	DVR_PLAYER_SetStreamPlayMode(nPort,REAL_MODE);
#else
	RECT rc;
	GetClientRect(hwnd,&rc);

	if (AVP_SUCCESS != OpenStream( &nPort , REAL_STREAM_MODE))
	{
		mlog(LOG_ERR,"CRTSPDevice::OpenStream 解码通道超过最大值!");
		assert(0);
		return -1;
	}
	//TRACE("[%d]OpenStream end\n",nPort);

	SetDisplayHwnd ( nPort, hwnd);
	SetDisplayRegion (nPort, rc.left,rc.top,rc.right,rc.bottom);
	mlog(LOG_DEBUG,"OpenChannel %s decoder port:%d ...",m_pDevInfo->szIpAddr,nPort);
#endif
	void* session;
	server_info_t server;
	memset(&server,'\0',sizeof(server));
	server.port = 554;
	strcpy(server.username,m_pDevInfo->szLoginName.toLatin1().data());
	strcpy(server.password,m_pDevInfo->szPassword.toLatin1().data());
	strcpy(server.url,m_pDevInfo->szIpAddr.toLatin1().data());
	server.ipc_type = ipc_type;

	if(m_pDevInfo->nManufaceturer == DEVINFO_MANUFACTURER_BC)
	{
		char url[256];
		if(nChannel == 1)
			sprintf(url,"rtsp://%s:554/video",m_pDevInfo->szIpAddr);
		else if(nChannel == 2)
			sprintf(url,"rtsp://%s:555/video",m_pDevInfo->szIpAddr);
		else
			return -1;
		strcpy(server.url,url);
		session = rtsp_play_url(&server,NULL,30000+(nPort*2),rtsp_callback,(void *)nPort);
		//session = rtsp_play_url(url,NULL,30000+(nPort*2),rtsp_callback,(void *)nPort);
	}
	else
	{
		session = rtsp_play(&server,NULL,30000+(nPort*2),rtsp_callback,(void *)nPort);
		//session = rtsp_play(m_pDevInfo->szIpAddr,554,ipc_type,NULL,30000+(nPort*2),true,rtsp_callback,(void *)nPort);
	}
	if(session == NULL)
	{
		//	int ret = CloseStream(nPort);
		//	if(ret != 0)
		//		TRACE("CloseStream1 ret:%d\n",ret);

		//	mlog(LOG_ERR,"OpenChannel %s decoder port:%d error!",m_pDevInfo->szIpAddr,nPort);
		return -1;
	}
	//mlog(LOG_DEBUG,"OpenChannel %s decoder port:%d session:%x",m_pDevInfo->szIpAddr,nPort,session);
	LONG lPlayHandle = (LONG)session;
	EnterCriticalSection(&rtsp_lock);
	int i;
	for (i=0;i<MAX_RTSP_PLAYER;i++)
	{
		if(!g_RtspPlayerInfo[i].bUsed)
		{
			g_RtspPlayerInfo[i].bUsed = TRUE;
			break;
		}
	}

	if(i == MAX_RTSP_PLAYER)
	{
		LeaveCriticalSection(&rtsp_lock);
		
		rtsp_stop(session);
		//CloseStream(nPort);
		assert(0);
		return -1;
	}
	m_mapPlayHandle[hwnd] = (long)lPlayHandle;
	m_mapPlayChannel[hwnd] = nChannel;
	m_hwnd = hwnd;
	g_RtspPlayerInfo[i].port = nPort;
	std::map<LONG, int>::const_iterator it = g_mapRTSPPlayerInfo.find(lPlayHandle);
	if(it != g_mapRTSPPlayerInfo.end())
		assert(0);
	g_mapRTSPPlayerInfo[lPlayHandle] = i;
	LeaveCriticalSection(&rtsp_lock);
	DVR_PLAYER_Play(nPort,hwnd);
	return 0;
}

S32 CRTSPDevice::ChangeChannelStream(HWND hwnd,U32 nStream)
{
	return -1;
}

S32 CRTSPDevice::CloseChannel(HWND hwnd)
{
	LONG lRealHandle;
	std::map<HWND, int>::const_iterator it = m_mapPlayHandle.find(hwnd);
	if(it == m_mapPlayHandle.end())
	{
		return -1;
	}
	lRealHandle = it->second;
	int i;
	if(lRealHandle != 0)
	{
		i = GetPortId((LONG)lRealHandle);
		EnterCriticalSection(&rtsp_lock);
		g_mapRTSPPlayerInfo.erase((LONG)lRealHandle);
		LeaveCriticalSection(&rtsp_lock);
		rtsp_stop((void *)lRealHandle);
	}
	m_mapPlayHandle.erase(it);
	std::map<HWND, int>::const_iterator itChannel = m_mapPlayChannel.find(hwnd);
	if(itChannel != m_mapPlayChannel.end())
		m_mapPlayChannel.erase(itChannel);

	assert(i != -1);
	//int ret = CloseStream(g_RtspPlayerInfo[i].port);
	//assert(ret == 0 );
	//if(ret != 0)
	//	TRACE("CloseStream ret:%d\n",ret);
	DVR_PLAYER_Stop(g_RtspPlayerInfo[i].port);
	DVR_PLAYER_CloseStream(g_RtspPlayerInfo[i].port);

	EnterCriticalSection(&rtsp_lock);
	if(i != -1)
	{
		g_RtspPlayerInfo[i].port = 0;
		g_RtspPlayerInfo[i].bUsed = FALSE;
		g_RtspPlayerInfo[i].bSaveStream = FALSE;
		g_RtspPlayerInfo[i].bEnableAudio = FALSE;
	}
	LeaveCriticalSection(&rtsp_lock);
	return 0;
}

S32 CRTSPDevice::PtzCtrl(HWND hwnd,PTZ_COMMAND_TYPE cmd,U32 nStop,U32 nSpeed)
{
	return -1;
}

S32 CRTSPDevice::Logout()
{
	if(m_pDevInfo->nManufaceturer != DEVINFO_MANUFACTURER_BC)
		return 0;

	if (!m_bSocketCreate || !m_mapPlayHandle.empty() || m_bRecvAlarm)
		return 0;

	m_bCNVTThreadExit = TRUE;
	//SetEvent(m_hEvent);
	//SetEvent(m_hEvent2);
	Sleep(1000);
	m_bSocketCreate = FALSE;
	//closesocket(m_nBCNVRSocket);
	return 0;
}