#pragma once
#include "Device.h"

class CSJDevice : public CBaseDeviceInfo
{
public:
	CSJDevice(void);
	virtual ~CSJDevice(void);

	S32 Login();
	S32 OpenChannel(U32 nChannel,U32 nStream,HWND hwnd, int nWndNum = 0);
	S32 ChangeChannelStream(HWND hwnd,U32 nStream);
	S32 CloseChannel(HWND hwnd);
	S32 PtzCtrl(HWND hwnd,PTZ_COMMAND_TYPE cmd,U32 nStop,U32 nSpeed);
	S32 Logout();
};

