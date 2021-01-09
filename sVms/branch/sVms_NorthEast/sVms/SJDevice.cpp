#include "SJDevice.h"
#include "net_dvr.h"

std::map<LONG,CSJDevice *> g_SJDevMap;
CSJDevice::CSJDevice(void)
{
}


CSJDevice::~CSJDevice(void)
{
}

void CALLBACK RealDataCallBack (LONG lRealHandle, DWORD dwDataType, DWORD dwTimestamp, BYTE *pBuffer,DWORD dwBufSize,LPVOID dwUser)
{
	if(pBuffer == NULL || dwBufSize <= 0)
		return;
	if(dwDataType == 1)
		return; //不缓存音频
	CFrameBuf *pBuf = (CFrameBuf*)dwUser;
	if(pBuf == NULL)
		return;
	pBuf->PutFrame((char*)pBuffer,dwBufSize,dwDataType);
}
S32 CSJDevice::Login()
{

	if(m_pDevInfo->nManufaceturer != DEVINFO_MANUFACTURER_SJ)
		return -1;

	if(m_nUserID != -1)
	{
		return m_nUserID;
	}

	LONG lUserID;
	QString csTemp = m_pDevInfo->szIpAddr;
	csTemp = csTemp.right(7);
	if(csTemp.compare("ipv.com") == 0)
		lUserID = DVR_NET_Login(m_pDevInfo->szIpAddr.toLatin1().data(),m_pDevInfo->nPort,m_pDevInfo->szLoginName.toLatin1().data(),m_pDevInfo->szPassword.toLatin1().data(),NULL,"DDNS");
	else
		lUserID = DVR_NET_Login(m_pDevInfo->szIpAddr.toLatin1().data(),m_pDevInfo->nPort,m_pDevInfo->szLoginName.toLatin1().data(),m_pDevInfo->szPassword.toLatin1().data(),NULL,0);
	if(lUserID<0)
	{
		//int err = DVR_NET_GetLastError();
		return -2;
	}
	//临时解决不能控制云台的问题
	SYS_VERSIONINFO vi;
	DWORD dwReturned;
	DVR_NET_GetDVRConfig(lUserID, DVR_NET_GET_VERSION, 0, &vi, sizeof(SYS_VERSIONINFO), &dwReturned);

	//EnterCriticalSection(&tst_lock);
	g_SJDevMap[lUserID] = this;
	//LeaveCriticalSection(&tst_lock);

	DVR_NET_SetupAlarmChan(lUserID);
	m_nUserID = lUserID;
	return m_nUserID;
}

S32 CSJDevice::OpenChannel(U32 nChannel,U32 nStream,HWND hwnd, int nWndNum)
{
	if(m_nUserID == -1)
	{
		if(Login() < 0)
		{
			return -1;
		}
	}

	LONG lRealHandle;
	DVR_NET_CLIENTINFO ClientInfo;

	ClientInfo.hPlayWnd = hwnd;
	ClientInfo.lChannel = nChannel;
	ClientInfo.lLinkMode = 0;
	ClientInfo.iMajorStream = nStream;
	lRealHandle = DVR_NET_RealPlay(m_nUserID,&ClientInfo);
	if(lRealHandle<0)		
	{
		printf("RealPlay channel 1 error error:%d\n",DVR_NET_GetLastError());
		return -1;
	}
	CFrameBuf* pBuf = new CFrameBuf;
	pBuf->CreateBuf();
	DVR_NET_SetRealDataCallBack(lRealHandle,RealDataCallBack,pBuf);
	DVR_NET_SetPlayerBufNumber(lRealHandle,0);
	m_mapPlayHandle[hwnd] = lRealHandle;
	m_mapPlayChannel[hwnd] = nChannel;
	m_mapPlayBuf[hwnd] = pBuf;
	return 0;
}

S32 CSJDevice::ChangeChannelStream(HWND hwnd,U32 nStream)
{
	LONG lRealHandle = GetPlayHandle(hwnd);
	if(lRealHandle == -1)
		return -1;

	if(DVR_NET_SetRelStreamPara(lRealHandle,nStream))
		return 0;
	return -2;
}

S32 CSJDevice::CloseChannel(HWND hwnd)
{
	LONG lRealHandle;
	std::map<HWND, int>::const_iterator it = m_mapPlayHandle.find(hwnd);
	if(it == m_mapPlayHandle.end())
	{
		return -1;
	}
	lRealHandle = it->second;
	DVR_NET_StopRealPlay(lRealHandle);
	m_mapPlayHandle.erase(it);
	std::map<HWND, int>::const_iterator itChannel = m_mapPlayChannel.find(hwnd);
	if(itChannel != m_mapPlayChannel.end())
		m_mapPlayChannel.erase(itChannel);

	std::map<HWND, CFrameBuf*>::const_iterator itFrameBuf = m_mapPlayBuf.find(hwnd);
	if(itFrameBuf != m_mapPlayBuf.end())
	{
		CFrameBuf* pBuf = itFrameBuf->second;
		if(pBuf != NULL)
			pBuf->DeleteBuf();
		m_mapPlayBuf.erase(itFrameBuf);
		if(m_mapPlayBuf.empty())
			m_mapPlayBuf.clear();
	}

	if(m_mapPlayHandle.empty())
	{
		m_mapPlayChannel.clear();
		Logout();
	}
	return 0;
}

S32 CSJDevice::PtzCtrl(HWND hwnd,PTZ_COMMAND_TYPE cmd,U32 nStop,U32 nSpeed)
{
	LONG lRealHandle = GetPlayHandle(hwnd);
	if(lRealHandle == -1)
		return -1;

	int nSJcmd = m_PTZCmdMap[cmd];
	if(cmd == eGOTO_PRESET || cmd == eSET_PRESET)
	{
		if(DVR_NET_PTZPreset(lRealHandle,nSJcmd,nSpeed))
			return 0;
		return -2;
	}

	nSpeed = nSpeed/20 +1;
	if(DVR_NET_PTZControlEx(lRealHandle,nSJcmd,nStop,nSpeed))
		return 0;
//	mlog(LOG_ERR,"DVR_NET_PTZControlEx error:%d !",DVR_NET_GetLastError()); 
//	TRACE("DVR_NET_PTZControlEx error:%d\n",DVR_NET_GetLastError());
	return -2;
}

S32 CSJDevice::Logout()
{
	if(m_nUserID != -1 && m_mapPlayHandle.empty() && !m_bRecvAlarm)
	{
		DVR_NET_Logout(m_nUserID);
		m_nUserID = -1;
		//EnterCriticalSection(&tst_lock);
		g_SJDevMap.erase(m_nUserID);
		//LeaveCriticalSection(&tst_lock);
	}
	return 0;
}
