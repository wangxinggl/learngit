#ifndef VIDEOPLAYBACK_H
#define VIDEOPLAYBACK_H

#include <QWidget>
#include "ui_videoplayback.h"
#include "devtreepro.h"
#include <QLabel>
#include <QMenu>
#include <QList>
#include <vector>
#include "table_structs.h"
#include <Windows.h>
#include "../include/VideoNetAPI.h"
#include <QListView>
#include <QTimerEvent>
#include "systemset.h"
#include <QKeyEvent>
#include <QAction>
#include "VideoTimeLine.h"
#include <QTableWidget>
#include "LayerWidget.h"
#include <QEvent>
#include <QContextMenuEvent>
#include <QPoint>
#include <QTableWidgetItem>
#include "OneVideo.h"


#define PLAYBACK_MAX_FILE_NUM           64
#define SERACH_MAX_FILE_NUM				100

#define REPLAY_MAX_NUM     4
#define FIND_TYPE_SJ 0
#define FIND_TYPE_HIK 1
#define FIND_TYPE_JL_NEW 2

#define PLAY_DEC_PORT_START 420

struct CFileStatus
{
	QTime m_ctime;          // creation date/time of file
	QTime m_mtime;          // last modification date/time of file
	QTime m_atime;          // last access date/time of file
	ULONGLONG m_size;            // logical size of file in bytes
	BYTE m_attribute;       // logical OR of CFile::Attribute enum values
	BYTE _m_padding;        // pad the structure to a WORD
	TCHAR m_szFullName[_MAX_PATH]; // absolute path name

};

enum PlaybackType
{
	PLAYBACK_TYPE_ROMOTE = 0,	//远程回放
	PLAYBACK_TYPE_LOCAL,		//本地回放
	PLAYBACK_TYPE_TIME,			//按时间回放
	PLAYBACK_TYPE_PICTURE,		//回放图片
};

typedef  struct 
{
	BOOL        bPlay;  
	BOOL        bAudio;
	//BOOL		 bTimePlay;
	BOOL		 bPause;

	//BOOL        bSet;
	BOOL        bShow;
	//CString     strDevId;
	//CString     strDevName;
	DWORD       nStreamtype; //-1无 0远程文件名 1本地文件 2时间回放,3回放图片
	LONG        nPlayHandle;
	TreeData_t* pPlayInfo;
	int nSpeed;
	DWORD lTotalTime;
	char szFileName[512];
	char szDevName[512];
	int nHour;//现在的小时
	int nMinute;//现在的分钟
	int nDay;
	int nMonth;
	int nErrorCount;
	char szBeginTime[64]; //hik设备CVR不支持按文件名回放，改为按时间段回放
	char szEndTime[64];
	LONG nDecHandle;
	char szLicense[MAX_LICENSE_LEN];
}ReplayWndInfo;


//时间转换函数
time_t	StringToTime(const string& strTime);

class videoPlayback : public QWidget
{
	Q_OBJECT

public:
	videoPlayback(QWidget *parent = 0);
	~videoPlayback();
	void initTree();
	void initTimeLine();
	void initVideoplay();
	void initForm();
	void initMenu();

	
	void inittableWidget();
	LONG ShowPlayPos(int nIndex);
	
	void StopPlay(int nIndex);
	void FindPictureFile(VIDEONET_FINDINFO* lpFindInfo);
	void FindRecordFile(VIDEONET_FINDINFO* lpFindInfo);
	void addToPlaylist(const QList<QUrl> urls);
	void   AddRemoteFile(const char* szFileName,const char* szBeginTime,const char* szEndTime, const char* szLicense);

	LONG PlayJLLocalFile(int nIndex);
	LONG  PlayBackJLByName(int nIndex,int lChannel,char* szBeginTime,char* szEndTime);
	long  PlayBackJLByTime(int nIndex);
	void ResetPlayData(int nIndex);
	QTableWidget *m_tableWidget;

public:
		static void CALLBACK InfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser);
		static void CALLBACK pProc(LONG nPort,LPCSTR pBuf,LONG nSize,LONG nWidth,LONG nHeight, LONG nStamp,LONG nType,LONG nUser);
		static int CALLBACK NetDataCallBack_V2(JVT_LONG lRealHandle, const PACKET_INFO_EX *pFrame, JVT_DWORD dwUser);
		static int CALLBACK ByTimeNetDataCallBack( JVT_LONG lRealHandle, long dwDataType, unsigned char *pBuffer,long lbufsize,JVT_DWORD dwUser);
		static void CALLBACK SDKPlayFileEndCallback(LONG nPort, LONG nUser);
		void PlayEndCallback(int nPort);
		static void CALLBACK PlaybackdrawOSDCall(LONG nPort, HDC hDc, LONG nUser);
		void	 SetSingleVideoWndPos(int nSelected);
		void ShowSpeed();
		void FindFileByPicture(int nFindType);
		void OnTreeReFresh();
private slots:
	void on_btnSearch_clicked();
	void on_btnImport_clicked();
	void jump(const QModelIndex &index);
	void playlistPositionChanged(int currentItem);
	
	void on_btnVoice_clicked();
	void on_btnPre_clicked();
	//播放视频
	void on_btnPlay_clicked();
	//截屏
	void on_btnShear_clicked();
	//实践轴针的移动
	void TimeLineMove();
	//保存选中行
	void SaveTableItem(vector<int> &vecItemIndex);

	void on_btnDowned_clicked(); //下载
	void on_btnSearchPic_clicked();//以图搜图
	void on_btnSearchVideo_clicked();//以图搜录像

protected:
	void timerEvent(QTimerEvent* event);

private slots:
	void treeItemChanged(QTreeWidgetItem *item,int column);
	void on_btnStop_clicked();
	void on_btnNext_clicked();

	void screen_full();             //全屏模式
	void screen_normal();           //普通模式
	
	void hide_video_all();
public slots:
	void handleTimeout();
	void slotSelectChanged(int ,int);
	void contextMenuEvent(QContextMenuEvent *event); //右键默认槽
	void actionDownLoadClick();//下载录像
	void actionPicSearchClick();
	void actionVideoSearchClick();
	void on_btnExtend_clicked();
	
	void show_video_all();
	void show_video_4();
	void show_video_6();
	void show_video_8();
	void show_video_9();
	void show_video_16();
	void change_video(int index, int flag);
	void change_video_4(int index);
	void change_video_6(int index);
	void change_video_8(int index);
	void change_video_9(int index);
	void change_video_16(int index);

	void on_btnSearchIP_clicked();
private:
	Ui::videoPlayback ui;
	QList<OneVideo *> widgets;
	bool videoMax;
	int videoCount;
	int  m_nfousWnd;      //Focus Window index  
	QString videoType;
protected:
	bool eventFilter(QObject *watched, QEvent *event);
public:
	

	LONG m_lFindHandle;
	LONG m_lFindType; //查找录像的设备厂商
	LONG m_lUserID;
	
	bool flag;
	TreeData_t *pChannelTmp;
	int nCheckNum;
	long lChannel,type;
	QString m_strDevName;
	long m_lFindFileType;		//搜索文件类型
	LONG m_lChannel; //当前查找录像的通道
	std::vector<VIDEONET_FILE_DATA> m_vtVideoNetFile;
	
	
private:
	bool m_bFullScreen;
	BOOL	m_bSingleVideo;
	
	ReplayWndInfo     m_ReplayWnd[REPLAY_MAX_NUM];
	int m_nWait;
	QString m_strWifiPath;
	TreeData_t* pFindFileInfo;
	 QLabel *tempLab; 
	 int     m_nVideoNum;
	 int m_iSelectCount;
	 BOOL    m_bDragging;
	 UINT    ReplayWnd[REPLAY_MAX_NUM];
	 BOOL	m_bShowGroup;
	 BOOL  m_bShowDev;
	 long  m_ckSelCount; //by zjh add 20170831

	 int FIND_TIMER;
	 int PLAY_TIMER;

	 DevTreePro *treevideoblack;
	 BOOL m_bSound;
	 QString sPeedTime;
	 systemSet *set;
	 QMenu *menu;
	 QMenu *videoMenu;
	 int nNumTmp;
	 QAction *actionDownLoad;
	 QAction *actionPicSearch;
	 QAction *actionVideoSearch;
	 VideoTimeLine* m_videoTimeLine;
	 QTableWidgetItem *m_Vcheck;
	 QList<VideoSegmentInfo> videoSegmentList;
	 VideoSegmentInfo m_CurrData;

	 QString m_strPicPath;
	 void getTimeInt(int& hour,int& sec,QString srcTime);
	 void drawWarning(int startHour, int startMin, int endHour, int endMin);
	 void clearCurrAge(QTableWidget *m_table);
};

#endif // VIDEOPLAYBACK_H
