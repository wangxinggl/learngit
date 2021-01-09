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
#include "../include/VideoNetAPI.h"
#include <QMouseEvent>
#include <QSound>

#pragma execution_character_set("utf-8") 

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
	void initTreeWidget();
	void initFaceResult();
	void initTvmode();
	void ReceiveSnap(char* pBuf);
	static DWORD WINAPI ShowPicThread(LPVOID lPvoid);
	static DWORD WINAPI ShowResultThread(LPVOID lpVoid);

	void startDisplayImg();
	void startDisplayPerMsg();
	bool event(QEvent *e);
	static DWORD WINAPI RestoreRealtimeThread(LPVOID lpParam);
	long   OnRestoreRealtime();
	DevTreePro *treePrew;
	map<long, TreeData_t*>	m_TreeData;
	BOOL m_bStopRestore;
	bool m_IsRestoreVideoParam;
	HANDLE m_hRestoreThread;
public:
	int AddWatch(TreeData_t* pDev, BOOL bTipBox = FALSE);
	int AddWatch_t(int nWnd, TreeData_t* pDev);
	void DisPlayPersonMessage();   //显示比对信息
	void DisplayImage();		   //显示抓拍信息
	void OpenAlarmSound();
	QString GetAvailDisk(unsigned long nMinAvailBytes);
	void OnTreeReFresh();
	QList<VideoWnd> widgets;
	VideoWnd m_videoWnd;
public slots:
	void OnMenuReFresh();//刷新设备树
private slots:
	void play_video_all();
	void snapshot_video_one();
	
	void ShowToolBar();
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
	void StopAllWatch();
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
	
	
	void displayunRec(); //设置未识别容量
	void displayRec();

	QString GetModeType(int nMode); //得到名单类型
	void SaveVideoParam();//保存当前播放视图
	
private:
	Ui::PreView ui;
	bool videoMax;
	int videoCount;
	int  m_nfousWnd;      //Focus Window index  
	QString videoType;
	QMenu *videoMenu;
	
	OneVideoPro *oneVideo;
	int nNumTmp;
	TreeData_t *pChannelTmp;
	

	QAction *actionRefresh;   //刷新树按钮
	QAction *actionComparison;//开启比对按钮
	QAction *actionComparisonStop;
	QAction *actionStopWatch;
	QAction *actionStopAllWatch;
	QAction *actionSnap; //开启抓拍
	QAction *actionSnapStop;//关闭抓拍
	QAction *actionToolbar;//工具栏
	QAction *actonMainsream;//主码流
	QAction *actionSecStream;//次码流
	QAction *actionFullScreen;//全屏
	QAction *actionCapTure; //抓图
	QAction *actionVoice;//打开声音
	QAction *actionRecord;//本地录像
	QAction *actionRestorePrew;//恢复预览
	QAction *actionBroadCast;
	capacitySet *capSet;
	systemSet *set;

	int unRecNum;
	int RecNum;

	HANDLE m_hSnapThread;							//抓拍图片显示线程
	HANDLE m_hCompThread;							//比对记录显示线程
	HANDLE m_hSnapEvent;							//抓拍图片显示事件
	HANDLE m_hCompEvent;							//比对记录显示事件
	HANDLE m_hExitEvent;
	BOOL m_bExitThread;


	QList<unRecognition *> list_unrecog;//未识别列表
	QList<Recognition *> list_recog;    //已识别链表

	bool bFullScreen;
	BOOL  m_bBroadcast;

	bool isPlay;
	int m_speed;
	QString m_strSoundPath;
	BOOL  m_bShowGroup;
	vector<QString> m_treeIp;
//云台控制
private slots:
	
	void on_m_btnPtzUp_clicked();
	void on_m_btnPtzDown_clicked();
	void on_m_btnPtzLeft_clicked();
	void on_m_btnPtzRight_clicked();
	void on_m_btnPtzAuto_clicked();
	void on_m_btnPtzFocus_A_clicked();
	void on_m_btnPtzFocus_S_clicked();
	void on_m_btnPtzZoom_A_clicked();
	void on_m_btnPtzZoom_S_clicked();
	void on_m_btnPtzApe_A_clicked();
	void on_m_btnPtzApe_S_clicked();
	
	void on_PtzLight_clicked();
	void on_PtzPreset_clicked();
	void on_PtzRain_clicked();
	void on_PtzRecall_clicked();

	void setLineEditValue(int speed);
};
