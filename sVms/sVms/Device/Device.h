#pragma once


#include <vector>
#include <map>
#include <stdio.h>
#include "../../include/table_structs.h"
#include "FrameBuf.h"
#include "VideoNetAPI.h"
#include "VideoPlayerAPI.h"
#define DVR_MAX_VIDEO_CHANNEL 1024
#define DEVICE_MAIN_STREAM 0
#define DEVICE_SUB_STREAM 1
#define MAX_CHANNEL 64

/*
struct CONFIG_ERROR_PAIR
{
int iDevErrorNo;
QString strError;
};

static CONFIG_ERROR_PAIR s_errorMap[] =
{
{ VIDEONET_USER_NOT_LOGIN, QObject::tr("用户没有登陆") },	// 用户没有登陆
{ VIDEONET_NOPOWER, QObject::tr("权限不够") },					// 权限不够
{ VIDEONET_PASSWORD_NOT_VALID, QObject::tr("密码错误") },	// 密码错误
{ VIDEONET_LOGIN_USER_NOEXIST, QObject::tr("用户不存在") },		// 用户不存在
{ VIDEONET_USER_LOCKED, QObject::tr("用户账号被锁定") },		// 用户账号被锁定
{ VIDEONET_USER_IN_BLACKLIST, QObject::tr("名单中禁止访问的用户") }, // 名单中禁止访问的用户
{ VIDEONET_USER_HAS_USED, QObject::tr("账号已经登陆") },			// 账号已经登陆
{ VIDEONET_ACCOUNT_INPUT_NOT_VALID, QObject::tr("用户管理输入不合法") },	//用户管理输入不合法
{ VIDEONET_ACCOUNT_OVERLAP, QObject::tr("索引重复") },					//索引重复
{ VIDEONET_ACCOUNT_OBJECT_NONE, QObject::tr("不存在对象, 用于查询时") },			//不存在对象, 用于查询时
{ VIDEONET_ACCOUNT_OBJECT_NOT_VALID, QObject::tr("不存在对象") },//不存在对象
{ VIDEONET_ACCOUNT_OBJECT_IN_USE, QObject::tr("对象正在使用") },		//对象正在使用
{ VIDEONET_ACCOUNT_SUBSET_OVERLAP, QObject::tr("没有权限") },	//子集超范围 (如组的权限超过权限表，用户权限超出组的权限范围等等)
{ VIDEONET_ACCOUNT_PWD_NOT_VALID, QObject::tr("密码不正确") },		//密码不正确
{ VIDEONET_ACCOUNT_PWD_NOT_MATCH, QObject::tr("密码不匹配") },	//密码不匹配
{ VIDEONET_ACCOUNT_RESERVED, QObject::tr("保留帐号") },			//保留帐号
{ VIDEONET_OPT_FILE_ERROR, QObject::tr("写文件出错") },	// 写文件出错
{ VIDEONET_OPT_CAPS_ERROR, QObject::tr("配置特性不支持") },	// 配置特性不支持
{ VIDEONET_OPT_VALIDATE_ERROR, QObject::tr("配置校验失败") },	// 配置校验失败
{ VIDEONET_SDK_UNKNOWNERROR, QObject::tr("未知错误") },				//未知错误
{ VIDEONET_SDK_NOTSUPPORT, QObject::tr("版本不支持") },					//版本不支持
{ VIDEONET_SDK_NOTVALID, QObject::tr("非法请求") },						//非法请求
{ VIDEONET_USER_HAS_USED, QObject::tr("用户已登陆") },								//用户已登陆
{ VIDEONET_PASSWORD_NOT_VALID, QObject::tr("用户名密码错误") },				//用户名密码错误
{ VIDEONET_SDK_TIMEOUT, QObject::tr("超时") },
{ 0, QObject::tr("设备不在线") }
};
*/
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
	unsigned int SerialNum;
	unsigned int TimeStamp;
	unsigned int ASerialNum;
	unsigned int ATimeStamp;
	int nDevID;			//设备ID
	int nChannel;		//设备通道
	int nStreamType;
	HWND hPlayWnd;
	BOOL bSpeak;
	int nWndNum;	//播放窗口序号，重练后判断窗口是否有视频播放过
	JVT_LONG lPlayHandle;	//播放句柄
}st_playerInfo;
/*
struct CONFIG_ERROR_PAIR
{
	int iDevErrorNo;
	QString strError;
};

static CONFIG_ERROR_PAIR s_errorMap[] =
{
	{VIDEONET_USER_NOT_LOGIN, QObject::tr("用户没有登陆") },	// 用户没有登陆
	{VIDEONET_NOPOWER, QObject::tr("权限不够") },					// 权限不够
	{VIDEONET_PASSWORD_NOT_VALID, QObject::tr("密码错误") },	// 密码错误
	{VIDEONET_LOGIN_USER_NOEXIST, QObject::tr("用户不存在") },		// 用户不存在
	{VIDEONET_USER_LOCKED, QObject::tr("用户账号被锁定") },		// 用户账号被锁定
	{VIDEONET_USER_IN_BLACKLIST, QObject::tr("名单中禁止访问的用户") }, // 名单中禁止访问的用户
	{VIDEONET_USER_HAS_USED, QObject::tr("账号已经登陆") },			// 账号已经登陆
	{VIDEONET_ACCOUNT_INPUT_NOT_VALID, QObject::tr("用户管理输入不合法") },	//用户管理输入不合法
	{VIDEONET_ACCOUNT_OVERLAP, QObject::tr("索引重复") },					//索引重复
	{VIDEONET_ACCOUNT_OBJECT_NONE, QObject::tr("不存在对象, 用于查询时") },			//不存在对象, 用于查询时
	{VIDEONET_ACCOUNT_OBJECT_NOT_VALID, QObject::tr("不存在对象") },//不存在对象
	{VIDEONET_ACCOUNT_OBJECT_IN_USE, QObject::tr("对象正在使用") },		//对象正在使用
	{VIDEONET_ACCOUNT_SUBSET_OVERLAP, QObject::tr("没有权限") },	//子集超范围 (如组的权限超过权限表，用户权限超出组的权限范围等等)
	{VIDEONET_ACCOUNT_PWD_NOT_VALID, QObject::tr("密码不正确") },		//密码不正确
	{VIDEONET_ACCOUNT_PWD_NOT_MATCH, QObject::tr("密码不匹配") },	//密码不匹配
	{VIDEONET_ACCOUNT_RESERVED, QObject::tr("保留帐号") },			//保留帐号
	{VIDEONET_OPT_FILE_ERROR, QObject::tr("写文件出错") },	// 写文件出错
	{VIDEONET_OPT_CAPS_ERROR, QObject::tr("配置特性不支持") },	// 配置特性不支持
	{VIDEONET_OPT_VALIDATE_ERROR, QObject::tr("配置校验失败") },	// 配置校验失败
	{VIDEONET_SDK_UNKNOWNERROR, QObject::tr("未知错误") },				//未知错误
	{VIDEONET_SDK_NOTSUPPORT, QObject::tr("版本不支持") },					//版本不支持
	{VIDEONET_SDK_NOTVALID, QObject::tr("非法请求") },						//非法请求
	{VIDEONET_USER_HAS_USED, QObject::tr("用户已登陆") },								//用户已登陆
	{VIDEONET_PASSWORD_NOT_VALID, QObject::tr("用户名密码错误") },				//用户名密码错误
	{VIDEONET_SDK_TIMEOUT, QObject::tr("超时") },
	{0, QObject::tr("设备不在线")}
};
*/

#define DECODER_CMD_WIN 0
#define DECODER_CMD_MODE 1

class CBaseDeviceInfo 
{

public:
	CBaseDeviceInfo();
    virtual ~CBaseDeviceInfo();
	virtual S32 Login() = 0;
	virtual S32 OpenChannel(U32 nChannel,U32 nStream,HWND hwnd, int nWndNum, void* pVoid) = 0;
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

	void SetDevInfo(TabDevInfo_t* pDevInfo);
	TabDevInfo_t* GetDevInfo() {return m_pDevInfo;}
	void SetChannelInfo(TabChannelInfo_t* pChannelInfo) {m_lstChannel.push_back(pChannelInfo);}
	std::vector<TabChannelInfo_t*>& GetChannelInfo(){ return m_lstChannel;}
	TabChannelInfo_t* GetChannelInfo(int nChannel);
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
	JVT_LONG m_lUserLoginID;
	std::vector<TabChannelInfo_t*> m_lstChannel;
	
	TabDevInfo_t* m_pDevInfo;
	char m_PTZCmdMap[256];
	BOOL m_bRecvAlarm;
	int m_nWidth;
	int m_nHeight;
};

