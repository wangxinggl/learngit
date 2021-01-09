#pragma once

#include <QWidget>
#include "ui_PreView.h"
#include <QList>
#include <QMenu>
#include <QEvent>
#include <QLabel>
#include <QApplication>
#include "devtreepro.h"
#include <QHBoxLayout>
#include "OneVideoPro.h"
#include "capacityset.h"
#include "systemset.h"
#include "unrecognition.h"
#include "recognition.h"
#include <Windows.h>
#include "VideoNetAPI.h"
#include <QMouseEvent>
#include <QSound>
#include "db.h"
#include "TemperatureBox.h"


#pragma execution_character_set("utf-8") 
typedef void(CALLBACK *btn_callback)(int, int);
typedef struct  _VIDEOWND
{
	OneVideoPro* widget;
	bool isVideoOpen;
}VideoWnd;

class PreView : public QWidget
{
	Q_OBJECT

public:
	PreView(QWidget *parent = Q_NULLPTR);
	~PreView();
	void initForm();
	void initMenu();
	void initTree();
	void initFaceResult();
	void initTvmode();
	void initPTZ();
	void initSearchButton();//设置搜索框样式
	void ReceiveSnap(char* pBuf);
	static DWORD WINAPI ShowPicThread(LPVOID lPvoid);
	static DWORD WINAPI ShowResultThread(LPVOID lpVoid);

	void startDisplayImg();
	void startDisplayPerMsg();
	bool event(QEvent *e);
	static DWORD WINAPI RestoreRealtimeThread(LPVOID lpParam);
	long   OnRestoreRealtime();
	DevTreePro *m_pTreeDev;
	map<long, TreeData_t*>	m_mapPlayTreeData;
	BOOL m_bStopRestore;
	bool m_IsRestoreVideoParam;
	HANDLE m_hRestoreThread;
	HWND hWnd;
public:
	int AddWatch(TreeData_t* pDev, int nWnd, BOOL bTipBox = FALSE);
	int AddWatch_t(int nWnd, TreeData_t* pDev);
	void DisPlayAlarmMessage();   //显示比对信息
	void DisplayImage();		   //显示抓拍信息
	void OpenAlarmSound();
	void OnTreeReFresh();
	int getIndex(int mode);

	QList<VideoWnd> m_listwidgets;
	VideoWnd m_videoWnd;
public slots:
	void StopAllWatch();
private slots:
	void play_video_all();
	void snapshot_video_one();
	
	
	void MainStream();
	void SecStream();

	void show_video_all();
	void show_video_4();
	void show_video_6();
	void show_video_8();
	void show_video_9();
	void show_video_16();

	void hide_video_all();
	void change_video(int index, int flag);
	void change_video_4(int index);
	void change_video_6(int index);
	void change_video_8(int index);
	void change_video_9(int index);
	void change_video_16(int index);

	void StopWatch();
	void storePrew();
	void CapTure();
	void OpenSound();
	void LocalRecord();
	void BroadcastSlot();
	//tree点击事件
	void OnlineTreeViewDoubleClick(const QModelIndex & index);
	int OnWidgetContextMeun(const QPoint& pt);  //右键弹出菜单
	
	void OnMenuComparison();//开启比对
	void OnMenuComparisonStop();//关闭比对
	void OnMenuTreeAttribute();//属性

	void on_btnClearRec_clicked();//清空告警窗口
	void on_btnClearUnrec_clicked();//清空抓拍窗口
	void on_btnSet_clicked();//设置缓冲区容量

	void on_btnExtendLeft_clicked();
	void on_btnExtendDown_clicked();
	int Broadcast(BOOL bStart);

	void on_btnSearch_clicked();
protected:
	bool eventFilter(QObject *watched, QEvent *event);
	void showEvent(QShowEvent *e);
	
	
private:
	void StartCompare(BOOL bStart);
	
	
	unRecognition* GetDisplayunRec(); //设置未识别容量
	Recognition* GetDisplayRec();

	void SaveVideoParam();//保存当前播放视图

	void UnInitWnd();		
	CTemperatureBox* GetTempBox();
private:
	Ui::PreView ui;
	bool videoMax;
	int m_nVideoCount;
	int  m_nfousWnd;      //Focus Window index  
	int m_nNumTmp;
	QString m_strVideoType;

	int m_nUnRecNum;
	int m_nRecNum;
	bool m_bFullScreen;
	BOOL  m_bBroadcast;
	bool isPlay;
	int m_speed;
	QString m_strSoundPath;
	BOOL  m_bShowGroup;
	int m_nCmd;
	bool m_bStart;

	HANDLE m_hSnapThread;							//抓拍图片显示线程
	HANDLE m_hCompThread;							//比对记录显示线程
	HANDLE m_hSnapEvent;							//抓拍图片显示事件
	HANDLE m_hCompEvent;							//比对记录显示事件
	HANDLE m_hExitEvent;
	BOOL m_bExitThread;

	QMenu *m_pVideoMenu;
	OneVideoPro *m_pOneVideo;
	TreeData_t *m_pTreeData;

	QAction *m_pActionComparison;//开启比对按钮
	QAction *m_pActionComparisonStop;
	QAction *m_pActionAttribute; //属性

	QAction *m_pActionStopWatch;
	QAction *m_pActionStopAllWatch;
	QAction *m_pActonMainsream;//主码流
	QAction *m_pActionSecStream;//次码流
	QAction *m_pActionFullScreen;//全屏
	QAction *m_pActionCapTure; //抓图
	QAction *m_pActionVoice;//打开声音
	QAction *m_pActionRecord;//本地录像
	QAction *m_pActionRestorePrew;//恢复预览
	QAction *m_pActionBroadCast;
	capacitySet *m_pCapSet;
	QPushButton *m_pSearchButton;
	QHBoxLayout *m_pSearchLayout;

	QList<CTemperatureBox*> m_listTemperatureBox;//温度异常显示框

	QString m_strAlarmInfo;
	QString m_strAlarmTemp;
	QString m_strAlarmStatus;

	QString m_strSnapInfo;
	QString m_strSnapTemp;
	QString m_strSnapStatus;

	vector<ChannelInfo *>deviceCh;
	btn_callback m_btnCB;
//云台控制
private slots:
	
	void on_m_btnPtzUp_pressed();
	void on_m_btnPtzUp_released();

	void on_m_btnPtzDown_pressed();
	void on_m_btnPtzDown_released();

	void on_m_btnPtzLeft_pressed();
	void on_m_btnPtzLeft_released();

	void on_m_btnPtzRight_pressed();
	void on_m_btnPtzRight_released();

	void on_m_btnPtzAuto_pressed();
	void on_m_btnPtzAuto_released();

	void on_m_btnPtzFocus_A_pressed();
	void on_m_btnPtzFocus_A_released();

	void on_m_btnPtzFocus_S_pressed();
	void on_m_btnPtzFocus_S_released();

	void on_m_btnPtzZoom_A_pressed();
	void on_m_btnPtzZoom_A_released();

	void on_m_btnPtzZoom_S_pressed();
	void on_m_btnPtzZoom_S_released();

	void on_m_btnPtzApe_A_pressed();
	void on_m_btnPtzApe_A_released();

	void on_m_btnPtzApe_S_pressed();
	void on_m_btnPtzApe_S_released();
	
	void on_PtzLight_clicked();
	void on_PtzPreset_clicked();
	void on_PtzRain_clicked();
	void on_PtzRecall_clicked();

	void setLineEditValue(int speed);
	
};
