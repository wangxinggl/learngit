#ifndef __JLN_DEVICE_H__
#define __JLN_DEVICE_H__

#include "Device/Device.h"
#include <vector>
#include <Windows.h>
#include <Shlwapi.h>
#include "systemset.h"
#include "mlog/mlog.h"

using namespace  std;
#define MAX_FRAME_INFO_COUNT 100
#define TALK_BUFFER_LENGTH		4096



enum
{
	RECONNECT_NOTIFY_LOCALRECORD,
	RECONNECT_NOTIFY_SOUND,
	RECONNECT_NOTIFY_SPEAK,
	RECONNECT_NOTIFY_COUNT,
};

typedef struct
{
	BOOL bSaveStream;
	BOOL bEnableAudio;
	int nStreamType;
	int nChannel;
	HWND hPlayWnd;
	BOOL bSpeak;
	int nWndNum;
}st_playerInfoSimple;


class CJLNDevice : public CBaseDeviceInfo 
{
public:
    CJLNDevice();
    virtual ~CJLNDevice();

	S32 Login();
	S32 OpenChannel(U32 nChannel,U32 nStream,HWND hwnd, int nWndNum = 0, void* pVoid = NULL);
	S32 ChangeChannelStream(HWND hwnd,U32 nStream);
	S32 CloseChannel(HWND hwnd);
	S32 PtzCtrl(HWND hwnd, int nPtzType,U32 nStop,U32 nSpeed);
	S32 Logout();
	S32 EnableAudio(HWND hwnd,BOOL bEnable);
	S32 LocalRecord(HWND hwnd,const char* szFileName,BOOL bStop);
	S32 ManulRecord(HWND hwnd,U32 nChannel,BOOL bStop);
	S32 CapturePic(HWND hwnd,const char* szFileName);
	S32 GetDeviceRecordStatus(HWND hwnd);
	S32 Speak(HWND hwnd,BOOL bStart);
	S32 RefreshPlay(HWND hwnd);
	S32 GetDecoderPara(int nCmd,int nPara1,int nPara2,int* pOut1,int* pOut2);
	S32 SetDecoderPara(int nCmd,int nPara1,int nPara2,int* pOut1,int* pOut2);

	HANDLE GetServerHandle(){return (HANDLE)m_lUserLoginID;}
	S32 SetOutput(int nChannel,int nStatus);
	S32 Reconnect();
	void   drawOSD(LONG nPort, HDC hDc);
	BOOL DisconnectDevice(long lDevID);
public:
	static void CALLBACK videoInfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser);
	static void CALLBACK VideoOnDrawCallback(LONG nPort, HDC hdc, LONG nUser);
	static DWORD WINAPI ReconnectThread(LPVOID lpParam);
	long   OnReconnect();


	static DWORD WINAPI AlarmConfigThread(LPVOID lpParam);

	void ProcessMonitorData(char* pBuffer, unsigned long dwDatalen);
	int ProcessSnapData(SMART_FACE_CMP_QUERY_INFO* pCompareInfo);


	long   OnAlarmConfig();
	BOOL StartSnapLink(JVT_LONG lLoginID, int nChannel);
	BOOL StopSnapLink(int nChannel);
	void ConstractSubLink();		//保存子链路


	list<st_playerInfoSimple> m_listPlayInfo;

	void OperateSubPlay(BOOL bOpen);			//播放链路
	
	int WriteFile(char* pFileName, char* pFileData, unsigned long dwDatalen);		//保存抓拍图片
	
	JVT_LONG StartImportAndExport(BOOL bCreateHandle = FALSE);//导入导出
	BOOL StopImportAndExport();

	JVT_LONG StartReceiveFaceCompareResult(JVT_LONG lLoginID, int nChannel);//开始接收人脸比对结果
	BOOL StopReceiveFaceCompareResult(JVT_LONG lCompareID, int nChannel);
	int SavePicture(SDK_FACECOMPARE_RESULT* pCompareInfo);
	
	JVT_LONG StartReceiveSnapResult(JVT_LONG lLoginID, int nChannel);	//开始接收抓拍
	BOOL StopReceiveSanpResult(JVT_LONG lSnapID, int nChannel);					//停止接收抓拍	
	JVT_LONG StartUpgrade();												//升级

	//新协议名单管理和图片接收链路
	BOOL StartListManagement();
	BOOL StopListManagement();
	BOOL StartFaceMonitor(JVT_LONG lLoginID, int nChannel);
	BOOL StopFaceMonitor(int nChannel);

	void SaveLibPic(SDK_SMART_WB_CONFIG_EX* pConfig, char* pBuffer, long lbufsize);
	int ProcessListManage(SDK_SMART_WB_CONFIG_EX* pConfig, char* pFileName = NULL);
	int GetLoginError(int nError, QString& strError);
public:
	LONG m_nHHDeviceType;
	HWND m_hwnd;
	BOOL bDevTalk;
	BOOL m_bDevTalk;
	QString m_strInfoFrame[MAX_FRAME_INFO_COUNT];
	long m_lDevType;
	HANDLE m_hConnectThread;
	volatile BOOL m_bReconnecting;
	int m_nChannelNum;  
	BOOL m_bSupportNew;
	HANDLE m_hAlarmConfigThread;
	BOOL m_bStopAlarmConfig;
	
	char m_szSnapPath[MAX_PATH];

	JVT_LONG m_lImExID;
	JVT_LONG m_lSnapID[MAX_CHANNEL];	//抓拍比对句柄
	JVT_LONG m_lUpgradeHandle;

	CRITICAL_SECTION m_lockSubOperation;
	VIDEONET_DEVICEINFO m_stDevInfo;

	BOOL StopSnap(int nChannel);
	BOOL StopCompare(int nChannel);

	int m_nErrorCode; 
	int m_nLoginError;
	HANDLE m_hImportWaitEvent;
	HANDLE m_hExsitEvent;
	BOOL m_bLight;		//灯光
	BOOL m_bBrush;		//雨刷

	BYTE*	m_pTalkDecodeBuf;
	JVT_LONG m_lTalkHandle;
	//char* m_pszLoginError;
	QString m_strLoginError;
	void* m_pVoid;
	long m_lVideoAreaWidth;
	long m_lVdieoAreaHeight;
	SMART_FACE_CMP_QUERY_INFO m_stCMPInfo;

	BOOL SendTalkData(LPBYTE pDataBuffer, DWORD dwDataLength);

	JVT_LONG GetLoginID(); 
};


#endif


