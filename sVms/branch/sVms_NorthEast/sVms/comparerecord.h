#ifndef COMPARERECORD_H
#define COMPARERECORD_H

#include <QWidget>
#include "ui_comparerecord.h"
#include <Windows.h>
#include "../include/VideoNetAPI.h"
#include "devtreepro.h"
#include "systemset.h"
#include <QLabel>
#include <QList>
#include "DB.h"
#include "table_structs.h"
#include <vector>
#include <QEvent>


class CompareRecord : public QWidget
{
	Q_OBJECT

public:
	CompareRecord(QWidget *parent = 0);
	~CompareRecord();
	void initTree();
	void initExportWidget();
	void initImportWidget();
	void initCompareWidget();
	

	void SetChannel(int iChannel);
	BOOL SearchSnap(char* pchDevIP, int nChannel = 0);
	void ShowSearchFile(int iPage, int nChannel = 0);
	void SetPageInfo(int iPage, int iPageCount);
	void SetPicInfo(QString strPath, QString strPicTime,int i);
	void ShowPicture(int i);
	void ShowPageInfo();
	void initDisplay();
	void initAttendance();
	int BeginSearch(int nFlag, int nPage);
	void ShowPageInfoRecord(int nPage);
	BOOL GetFindInfo(FS_FIND_INFO* pFsFindInfo);
	
	void Change_Unicode_UTF8(char *pStrGBKData, int nlen, char *pbuf, int buflen);
	void A2W_Mine(char *lpszA, wchar_t *lpszW);
	size_t Single_UNICODE_UTF8(char * dest_str, wchar_t src_wchar);

	void AddWBLogInfo(QString strLog);
	void FaceCallBack(long lSubFaceHandle, char *pBuffer,long lbufsize,SDK_FA_BLACKANDWHITELIST_CONFIG *pConfig,long dwUser);
	void FaceCallBack_Import(long lSubFaceHandle, char *pBuffer,long lbufsize,SDK_FA_BLACKANDWHITELIST_CONFIG *pConfig,long dwUser);
	void AddCallBackMessage(char *pBuffer,long lbufsize,SDK_FA_BLACKANDWHITELIST_CONFIG *pParm);
	void AddCallBackMessage(char* pBuffer, long lbufsize, SDK_SMART_WB_CONFIG_EX* pParam);

	void ShowPicRefresh(QString strPath);//显示图片
	void ShowPic_Import(QString strpath);//显示图片
	bool isChildStr(char *pstr,char *p);
	bool GetDevInfo();
	void GetColumnText(SMART_FACE_CMP_QUERY_INFO* pCompareInfo, int nCol, QString &strName);
	void OnTreeReFresh();

	TreeData_t* pChannelTmp;
	int nCheckNum;
	systemSet *set;

private slots:
	void on_btnSearch_clicked();
	void treeItemChanged(QTreeWidgetItem *item,int column);
	void on_btnPrepage_clicked();
	void on_btnNextpage_clicked();
	void on_btnJump_clicked();
	
	void on_btnSearchRecord_clicked();

	void on_btnExportIndex_clicked();

	void DisplyFaceExport(SDK_FILEINDEX_INFO *pConfig);

	void on_toolButton_clicked();

	void ExImageinfo(int row,int column);

	void on_checkBox_White_clicked();
	void on_checkBox_Black_clicked();
	void on_checkBox_VIP_clicked();
	void on_checkBox_VIP_Import_clicked();
	void on_checkBox_Black_Import_clicked();
	void on_checkBox_Whilte_Import_clicked();

	//void on_checkBox_All_clicked();
	void on_btnExtend_clicked();
	void on_btnSearchImage_clicked();
	void on_btnDowned_clicked(); //下载图片
	void on_btnDelPic_clicked(); //删除图片
	void on_btnClear_clicked();//清空
	void onStateChanged(int state);

	void on_btnAdd_Import_clicked();// 选择要上传的图片
	void on_btnImport_clicked();//上传图片
	void on_btnStop_Import_clicked();//停止

	void on_btnCompre_clicked();//比对记录里跳到上一页
	void on_btnComNext_clicked();
	void on_btnComJump_clicked();

	void on_btnCompareExport_clicked();

	void on_btnAttendSearch_clicked(); //考勤搜索
	void on_comboBox_Attend_currentIndexChanged(int index);

	void on_btnAttendPre_clicked();
	void on_btnAttendNext_clicked();
	void on_btnAttendJump_clicked();

	void on_btnAttendExport_clicked();//考勤导出
	void on_btnSearchIP_clicked();

	//void on_btnExcelImport_clicked();
private:
	Ui::CompareRecord ui;
	typedef std::vector<SMART_FACE_CMP_QUERY_INFO> AlarmList;
	vector<SMART_FACE_CMP_QUERY_INFO*> m_vectorListinfo;

	
	AlarmList m_vecFindResult;//告警缓存
	
	
	int m_iChannel;
	int m_iPage;
	int m_iPageCount;
	QString m_strPicPath;
	QString m_strPicTime;
	
	char m_szSnapPath[MAX_PATH];

	
	char* m_pchIndexBuf;
	DWORD dwTime;
	QString m_TimeBegin ;
	QString m_TimeEnd ;
	QString dataMsg;

	QList<QLabel *> VideoLab;       //通道显示图片lab载体
	QList<QLabel *> timeLab;      //显示时间的lab载体
	int m_nCmpInfoSize;		//
	int m_nPageCount;		//总页数
	int m_nCurPage;
	int m_nTotalCount;		//总条数
	int m_nChannel;
	
	int m_nOutputIndex;		//1---黑，2---白, 3---VIP
	int m_bListMod;//1.白名单 2.黑名单 3.VIP名单
	int nCount; //查找数量
	BOOL m_bBrowse;
	QString downedPath; //下载图片路径
	CJLNDevice *m_pDevInfo;
	QTableWidgetItem *check;//插入复选框
	int m_nErrorCode;
	int nSourceType;//名单模式

	DevTreePro *treecompare;
	void clearCurrAge(QTableWidget *m_table);
	int m_iErrorCode;
public:
	HANDLE m_hExportWaitIndexEvent;		//导出索引事件
	HANDLE m_hDeletePictureEvent;		//删除图片事件
	HANDLE m_hExportWaitEvent;			//下载图片事件
	HANDLE m_hImportWaitEvent;          //上传图片事件
	HANDLE m_hQueryEvent;
	HANDLE m_hWorkWaitEvent;
	
	SDK_SMART_WB_CONFIG_EX m_stSmarkConfig;
	
	FS_FIND_INFO m_stFindInfo;
	BOOL m_bImport;
	BOOL m_bExport;
	BOOL m_bImporting;
	BOOL m_bSelectAll;
	BOOL m_bQueryStat;		//查询状态
	bool attend_bQueryStat;
	SDK_FA_BLACKANDWHITELIST_CONFIG m_stBWListCofig;
	SDK_SMART_WB_CONFIG_EX m_stSmartConfig;
	SDK_SMART_WB_CONFIG_EX* m_pAttendInfo;
	CRITICAL_SECTION m_CriticalSection; 
	static DWORD WINAPI DeletePictureThread(LPVOID lpParam);
	static DWORD WINAPI DownLoadPictureThread(LPVOID lpParam);
	static DWORD WINAPI ImportFaceImageProc(LPVOID lpParam);

	static  DWORD WINAPI fQueryThread(LPVOID Para);
	void fQueryProc();
	static DWORD WINAPI RQueryThread(LPVOID lPvoid);//查找比对记录
	BOOL GetConfigInfo(char* pFileName);
	void ImportFaceImage();
	BOOL DeletePicturePro();
	void DownLoadPicturePro();
	
	BOOL WaitForCallBack(int i,QString str);
	void SearchRecord();
	void fDownLoadLibPic();
	void OnSearchShow(int nPage);
	void SearchEnd(int nPage);
	QString GetAbility(int nValue);
	QString GetModeType(int nMode);		//获取名单类型
	void LoadPicture(SMART_FACE_CMP_QUERY_INFO* pCompareInfo,QString& libPicName,QString& SnapPicName);
	void LoadPicture(SDK_SMART_PERSON_ATTEND_INFO* pAttendInfo, QString& libPicName);	//加载图片

	void ExportIndex();
	void GetAttendState(int nState, QString& strState);
	bool event(QEvent *e);
	void ListManageCallBack_Export(long lSubFaceHandle, char *pBuffer, long lbufsize, SDK_SMART_WB_CONFIG_EX *pConfig, long dwUser);
	void ListManageCallBack_Inport(long lSubFaceHandle, char *pBuffer, long lbufsize, SDK_SMART_WB_CONFIG_EX *pConfig, long dwUser);
	int GetResultCode(int nRet, QString& pCode);
	int FaceWorkListCallBack(char *pBuffer, long lbufsize, void* pAttend);
	int CmpRecordCallBack(char *pBuffer, long lbufsize, void* pConfigBuf);
	bool GetDevInfo_Atd();
	vector<SDK_SMART_PERSON_ATTEND_INFO> m_vListinfo;
	int m_nCountPage;
	int m_nType;
	int m_nDeleteErrorCode;
	char* m_pBufferIndex;
	HANDLE m_hOperationMutex;

	int importMode;
	vector<SDK_FILEINDEX_INFO> m_vectorFileInfo;
	vector<QString> m_vectorPersonInfo;
	BOOL  m_bShowGroup;
	LONG m_lFaceBlackAndWhiteList;
};


#endif // COMPARERECORD_H
