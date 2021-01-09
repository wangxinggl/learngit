#define  _CRT_SECURE_NO_WARNINGS
#include "Device/Device.h"


CBaseDeviceInfo::CBaseDeviceInfo()
	: m_bRecvAlarm(FALSE)
	, m_nDevStatus(0)
	, m_nWidth(704)
	, m_nHeight(576)
	, m_lUserLoginID(0)
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

void CBaseDeviceInfo::SetDevInfo(TabDevInfo_t* pDevInfo)
{ 
	m_pDevInfo = pDevInfo; 
	if (m_pDevInfo->nSubDevType == SDK_DEV_TYPE_MJIPC)
	{
		m_nWidth = 480;
		m_nHeight = 768;
	}
}


