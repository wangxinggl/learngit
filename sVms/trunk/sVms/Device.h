#pragma once


#include <vector>
#include <map>
#include <stdio.h>
#include "table_structs.h"
#include "FrameBuf.h"
#include "../include/VideoPlayerAPI.h"
#define DVR_MAX_VIDEO_CHANNEL 1024
#define DEVICE_MAIN_STREAM 0
#define DEVICE_SUB_STREAM 1
#define MAX_CHANNEL 64

typedef enum
{
	eLIGHT_PWRON = 2,	// 接通灯光电源 
	eWIPER_PWRON,	// 接通雨刷开关 
	eFAN_PWRON,	// 接通风扇开关
	eHEATER_PWRON,	// 接通加热器开关 
	eAUX_PWRON,	// 接通辅助设备开关 

	eSET_PRESET = 8,// 设置预置点 
	eCLE_PRESET,	// 清除预置点 

	eZOOM_IN = 11,//焦距以速度SS变大(倍率变大) 
	eZOOM_OUT,// 焦距以速度SS变小(倍率变小)
	eFOCUS_NEAR,// 焦点以速度SS前调
	eFOCUS_FAR,// 焦点以速度SS后调
	eIRIS_OPEN,	//光圈以速度SS扩大
	eIRIS_CLOSE,	// 光圈以速度SS缩小 

	eTILT_UP = 21,//云台以SS的速度上仰 
	eTILT_DOWN,// 云台以SS的速度下俯 
	ePAN_LEFT,	// 云台以SS的速度左转 
	ePAN_RIGHT,	// 云台以SS的速度右转 

	ePAN_AUTO = 29,	// 云台以SS的速度左右自动扫描 

	eRUN_CRUISE = 36,// 开始轨迹 
	eRUN_SEQ,// 开始巡航 
	eSTOP_SEQ,	// 停止巡航
	eGOTO_PRESET
}PTZ_COMMAND_TYPE;


typedef struct
{
	int port;
	BOOL bSaveStream;
	BOOL bUsed;
	BOOL bEnableAudio;
	char szFileName[512];
	FILE* pf;
	unsigned int SerialNum;
	unsigned int TimeStamp;
	unsigned int ASerialNum;
	unsigned int ATimeStamp;
	std::map<unsigned long ,char*> mapRecvbuf; 
	int nStreamType;
	int nChannel;
	int nMode;
	HWND hPlayWnd;
	int nDevID;
	BOOL bSpeak;
	int nWndNum;	//播放窗口序号，重练后判断窗口是否有视频播放过
}st_playerInfo;


#define DECODER_CMD_WIN 0
#define DECODER_CMD_MODE 1

class CBaseDeviceInfo 
{

public:
	CBaseDeviceInfo();
    virtual ~CBaseDeviceInfo();
	virtual S32 Login() = 0;
	virtual S32 OpenChannel(U32 nChannel,U32 nStream,HWND hwnd, int nWndNum) = 0;
	virtual S32 ChangeChannelStream(HWND hwnd,U32 nStream) = 0;
	virtual S32 CloseChannel(HWND hwnd) = 0;
	virtual S32 PtzCtrl(HWND hwnd, int nPtzType,U32 nStop,U32 nSpeed) = 0;
	virtual S32 Logout() = 0;
	virtual S32 EnableAudio(HWND hwnd,BOOL bEnable) = 0;
	virtual S32 LocalRecord(HWND hwnd,const char* szFileName,BOOL bStop) = 0;
	virtual S32 ManulRecord(HWND hwnd,U32 nChannel,BOOL bStop) = 0;
	virtual S32 CapturePic(HWND hwnd,const char* szFileName) = 0;
	virtual S32 GetDeviceRecordStatus(HWND hwnd) = 0;
	virtual S32 Speak(HWND hwnd,BOOL bStart) = 0;
	virtual S32 RefreshPlay(HWND hwnd) = 0;
	virtual S32 GetDecoderPara(int nCmd,int nPara1,int nPara2,int* pOut1,int* pOut2) = 0;
	virtual S32 SetDecoderPara(int nCmd,int nPara1,int nPara2,int* pOut1,int* pOut2) = 0;
	virtual S32 Reconnect() = 0;

	S32 GetPlayHandle(HWND hwnd);
	void SetDevInfo(TabDevInfo_t* pDevInfo) { m_pDevInfo = pDevInfo;}
	TabDevInfo_t* GetDevInfo() {return m_pDevInfo;}
	void SetChannelInfo(TabChannelInfo_t* pChannelInfo) {m_lstChannel.push_back(pChannelInfo);}
	std::vector<TabChannelInfo_t*>& GetChannelInfo(){ return m_lstChannel;}
	TabChannelInfo_t* GetChannelInfo(int nChannel);
	S32 GetPlayChannel(HWND hwnd);
	CFrameBuf* GetPlayBuf(HWND hwnd);
	void SetRecvAlarm(BOOL bRecvAlarm){m_bRecvAlarm = bRecvAlarm;}
	void SetDevStatus(BOOL bOnline)
	{
		if(bOnline)
			m_nDevStatus = 0;
		else
			m_nDevStatus --;
	}
	BOOL GetDevStatus()
	{
		if(m_nDevStatus >-3)
			return TRUE;
		return FALSE;
	}

	BOOL IsIPAvailed(const char* chIPAddr);

public:
	int m_nDevStatus; //0 在线  <-3 不在线
	S32 m_nUserID;
	std::vector<TabChannelInfo_t*> m_lstChannel;
	
	std::map<HWND ,int> m_mapPlayHandle;
	std::map<HWND ,int> m_mapPlayChannel;
	std::map<HWND ,CFrameBuf*> m_mapPlayBuf;
	TabDevInfo_t* m_pDevInfo;
	char m_PTZCmdMap[256];
	BOOL m_bRecvAlarm;

};

