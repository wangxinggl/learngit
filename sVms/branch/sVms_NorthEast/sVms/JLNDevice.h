#ifndef __JLN_DEVICE_H__
#define __JLN_DEVICE_H__

#include "Device.h"
#include <vector>
#include <Windows.h>
#include "../include/VideoNetAPI.h"
#include "../include/VideoPlayerAPI.h"
#include "systemset.h"
#include "mlog/mlog.h"


using namespace  std;
#define MAX_FRAME_INFO_COUNT 100
//JL New Protocol

typedef struct
{
	BOOL bSaveStream;
	BOOL bEnableAudio;
	int nStreamType;
	int nChannel;
	int nMode;
	HWND hPlayWnd;
	BOOL bSpeak;
	int nWndNum;
}st_playerInfoSimple;

typedef struct
{
	int nChannel;
	JVT_LONG lFaceManageID;
}st_faceManageInfo;

extern void __stdcall DisConnectBackCallFunc(JVT_LONG lLoginID, char *pchDVRIP,
	LONG nDVRPort, JVT_DWORD dwUser);

extern bool __stdcall JVTMessCallBack(JVT_LONG lLoginID, char *pBuf,
	unsigned long dwBufLen, JVT_DWORD dwUser);
class CJLNDevice : public CBaseDeviceInfo 
{
public:
    CJLNDevice();
    virtual ~CJLNDevice();

	S32 Login();
	S32 OpenChannel(U32 nChannel,U32 nStream,HWND hwnd, int nWndNum = 0);
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
	BOOL DisconnectDevice(long lDevID);
public:
	static void CALLBACK videoInfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser);
	static DWORD WINAPI ReconnectThread(LPVOID lpParam);
	long   OnReconnect();


	static DWORD WINAPI AlarmConfigThread(LPVOID lpParam);

	void ProcessMonitorData(char* pBuffer, unsigned long dwDatalen);
	int ProcessSnapData(SMART_FACE_CMP_QUERY_INFO* pCompareInfo);


	long   OnAlarmConfig();
	BOOL StartSnapLink(JVT_LONG lLoginID, int nChannel, int nChannelType);
	BOOL StopSnapLink(int nChannel, int nChannelType);
	void ConstractSubLink();		//保存子链路
	void OperateSubImExLink(BOOL bOpen);

	BOOL StartFaceMonitor(JVT_LONG lLoginID, int nChannel);
	BOOL StopFaceMonitor(int nChannel);

	list<st_playerInfoSimple> m_listPlayInfo;
	vector<st_faceManageInfo> m_vectorImExInfo;
	vector<st_faceManageInfo> m_vectorSnapInfo;
	vector<st_faceManageInfo> m_vectorCompareInfo;
	vector<st_faceManageInfo> m_vectorFaceMonitorInfo;

	void OperateSubPlay(BOOL bOpen);			//播放链路
	void OperateSubSnapLink(BOOL bOpen);
	void OperateSubCompareLink(BOOL bOpen);
	void OperateSubFaceMonitorLink(BOOL bOpen);


	BOOL StartListManagement(JVT_LONG lLoginID, int nChannel);
	static int __stdcall FaceMonitorCallBack(JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize, JVT_DWORD dwUser);
	
	int WriteFile(char* pFileName, char* pFileData, unsigned long dwDatalen);		//保存抓拍图片
	static int __stdcall ListManagementCallBack(JVT_LONG lSubFaceHandle, char* pBuffer, long lbufsize, char* pConfig, JVT_DWORD dwUser);		//新协议名单管理
	//添加比对
	JVT_LONG StartReceiveFaceCompareResult(JVT_LONG lLoginID, int nChannel);//开始接收人脸比对结果
	static int  __stdcall FaceCompareResultCallback(JVT_LONG lRealFaceHandle,char *pBuf, long nDataLen, JVT_DWORD dwUser);//比对回调
	BOOL StopReceiveFaceCompareResult(JVT_LONG lCompareID, int nChannel);
	int SavePicture(SDK_FACECOMPARE_RESULT* pCompareInfo);
	
	JVT_LONG StartReceiveSnapResult(JVT_LONG lLoginID, int nChannel);	//开始接收抓拍
	BOOL StopReceiveSanpResult(JVT_LONG lSnapID, int nChannel);					//停止接收抓拍
	static int  __stdcall FaceSnapCallback(JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize,
		SDK_FA_PICTURE_HEAD *pPictureHead,SDK_FACE_ATTR* pPictureAttr, JVT_DWORD dwUser);//抓拍回调
	
	//JVT_LONG StartImportAndExport(JVT_LONG lLoginID, int nChannel);//导入导出
	//BOOL StopImportAndExport(JVT_LONG lImExID, int nChannel);
	BOOL StartImportAndExport(JVT_LONG lLoginID, int nChannel);//导入导出
	BOOL StopImportAndExport(JVT_LONG lImExID, int nChannel);
	BOOL StopListManagement(JVT_LONG lListID, int nChannel);

	static int  __stdcall FacePicImportExportCallback(JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize,SDK_FA_BLACKANDWHITELIST_CONFIG *pConfig,JVT_DWORD dwUser);

	

	void SaveLibPic(SDK_SMART_WB_CONFIG_EX* pConfig, char* pBuffer, long lbufsize);
public:
	LONG m_nHHDeviceType;
	HWND m_hwnd;
	LONG m_lUserLoginID;
	BOOL bDevTalk;
	QString m_strInfoFrame[MAX_FRAME_INFO_COUNT];
	long m_lDevType;
	HANDLE m_hReconnectThread;
	volatile BOOL m_bReconnecting;
	int m_nChannelNum;  
	BOOL m_bSupportNew;
	HANDLE m_hAlarmConfigThread;
	BOOL m_bStopAlarmConfig;
	
	char m_szSnapPath[MAX_PATH];

	LONG m_lCompareID[MAX_CHANNEL];
	LONG m_lSnapID[MAX_CHANNEL];
	LONG m_lImExID[MAX_CHANNEL];
	JVT_LONG m_lFaceMonitorID[MAX_CHANNEL];

	CRITICAL_SECTION m_lockSubOperation;
	VIDEONET_DEVICEINFO m_stDevInfo;

	BOOL StopSnap(int nChannel);
	BOOL StopCompare(int nChannel);

	systemSet *set;


	BOOL m_bLight;		//灯光
	BOOL m_bBrush;		//雨刷
	
};


#endif


