#include "Device.h"


CBaseDeviceInfo::CBaseDeviceInfo(): 
m_nUserID(-1)
,m_bRecvAlarm(FALSE)
,m_nDevStatus(0)
{
	
}

CBaseDeviceInfo::~CBaseDeviceInfo()
{
	m_lstChannel.clear();
}

TabChannelInfo_t* CBaseDeviceInfo::GetChannelInfo(int nChannel)
{
	if(nChannel <= 0 || nChannel > DVR_MAX_VIDEO_CHANNEL)
		return NULL;

	std::vector<TabChannelInfo_t *>::iterator  iterSlave;
	for(iterSlave = m_lstChannel.begin(); iterSlave != m_lstChannel.end(); ++iterSlave)
	{
		if((*iterSlave)->Channel == nChannel)
			return (*iterSlave);
	}
	return NULL;
}

S32 CBaseDeviceInfo::GetPlayHandle(HWND hwnd)
{
	int lRealHandle = -1;
	std::map<HWND, int>::const_iterator it = m_mapPlayHandle.find(hwnd);
	if(it != m_mapPlayHandle.end())
	{
		lRealHandle = it->second;
	}
	return lRealHandle;
}

S32 CBaseDeviceInfo::GetPlayChannel(HWND hwnd)
{
	LONG lChannel = -1;
	std::map<HWND, int>::const_iterator it = m_mapPlayChannel.find(hwnd);
	if(it != m_mapPlayChannel.end())
	{
		lChannel = it->second;
	}
	return lChannel;
}

CFrameBuf* CBaseDeviceInfo::GetPlayBuf(HWND hwnd)
{
	CFrameBuf* pBuf = NULL;
	std::map<HWND, CFrameBuf*>::const_iterator it = m_mapPlayBuf.find(hwnd);
	if(it != m_mapPlayBuf.end())
	{
		pBuf = it->second;
	}
	return pBuf;
}

BOOL CBaseDeviceInfo::IsIPAvailed(const char* pszIPAddr)
{
	if (!pszIPAddr)
	{
		return FALSE;
	}

	int nIP[4] = {0};
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


