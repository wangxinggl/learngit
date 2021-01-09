#pragma once
#include "Device.h"

class CRTSPDevice : public CBaseDeviceInfo
{
public:
	CRTSPDevice(void);
	virtual ~CRTSPDevice(void);

	S32 Login();
	S32 OpenChannel(U32 nChannel,U32 nStream,HWND hwnd, int nWndNum = 0);
	S32 ChangeChannelStream(HWND hwnd,U32 nStream);
	S32 CloseChannel(HWND hwnd);
	S32 PtzCtrl(HWND hwnd,PTZ_COMMAND_TYPE cmd,U32 nStop,U32 nSpeed);
	S32 Logout();
public:
	SOCKET m_nBCNVRSocket;
	BOOL m_bSocketCreate;
	BOOL m_bCNVTThreadExit;
	CRITICAL_SECTION rtsp_lock;
	HWND m_hwnd;
};
