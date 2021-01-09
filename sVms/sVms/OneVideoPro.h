#pragma once

#include <QMainWindow>
#include "ui_OneVideoPro.h"
#include <QPaintEvent>
#include <QPushButton>
#include <QLabel>
#include "devtreepro.h"
#include <QVector>
#include <QRect>
#include <QAction>
#include "systemset.h"
#include <QTimerEvent>
#include "clickedlabel.h"
#include "CompareEvent.h"
#include <QStatusBar>
#include <QMenu>
#include "VMTools.h"
#include <QResizeEvent>
#include <QPainter>

typedef struct
{
	BOOL   bSound;		//Sound open or not
	BOOL   bRecord;		//Server Record or not
	BOOL   bLocRecord;  //Local Record
	BOOL   bManulRecord;  //Manul Record
	BOOL   bSpeak;        //Remote Speak or not
	BOOL   bBroadcast;    //broadcast
	BOOL   bVideo;        //Watch or not Watching 2
	
	BOOL   bTimeshift;
	BOOL   bPause;
	BOOL   bVideoStop;

	//TS     TSStatus;
	int		TSStatus; //-8 -4 -2 0pause 1 2x 4x 8x 16x
	BOOL   bPS; //预置点巡航
	int  nPatrol;

	int    VSDuration;       //potrol
	int    VSCurStaytime;
	int    VSCurIndex;
	BOOL   bVS;
	BOOL bMainStream;

	//char   szDevId[256];		//Camera Device
	int	nDevId;
	char   szDevName[256];
}DspWndInfoPro;


extern int			g_nRealPlayCount;
class OneVideoPro : public QMainWindow
{
	Q_OBJECT

public:
	OneVideoPro(QWidget *parent = Q_NULLPTR);
	~OneVideoPro();
	void createTab();
	void initForm();
	void initAction();
	
	int AddWatch(TreeData_t* pDev, int nPatrolId, BOOL bTipBox = FALSE, int nWndNum = 0);
public slots:
	void StopWatch();
public:
	void StartWatch();
	void ManulRecord();
	int OpenSound();
	int LocalRecord();
	int Speak(BOOL bStart);
	void OnRecordStatus(int result);

	void isHideToolBar();
	void OnMenuStreamMain();
	void OnMenuStreamSub();
	void CapturePic();
	int BroadCast(BOOL  bStart);

	void timerEvent(QTimerEvent* event);
	bool event(QEvent *e);
	void resizeEvent(QResizeEvent* size);
	void OnReconnectNotifyMsg(long lType);
private slots:
	void talkBtnSlot();
	void maxBtnSlot();
	void soundBtnSlot();
	void recordBtnSlot();
	void cameraBtnSlot();
public:
	QPushButton *closeBtn;
	QPushButton *talkBtn;
	QLabel *m_talkBtn;
	QPushButton *soundBtn;
	QLabel *m_soundBtn;
	QPushButton *recordBtn;
	QLabel *m_recordBtn;
	QPushButton *cameraBtn;
	QLabel *m_cameraBtn;
	QPushButton *maxButton;
	QLabel *m_maxBtn;

	QLabel *ch_Label;
	QLabel *IPLabel;
	QLabel *label;
	DspWndInfoPro m_dspWndinfo;
	TreeData_t* m_pDev;
	TreeData_t* m_pDevTemp;	//临时存放播放设备
	int m_nWndNum;			//临时存放播放窗口号
	BOOL m_bTipBox;
	HWND m_hWnd;
	BOOL m_bAudioEnable;

	//是否正在运行
	bool isPlay;
	bool isMax;
	BOOL  m_bTalk;
	BOOL m_bVideoThreadExit;
	int m_ndspIndex;
	QString m_szShowMsg;

	
	QRect  winRect;

	bool toolBarHide;

	int RECORD_TIMER;
	int CHKDISK_TIMER;
	
	QMenu *videoMenu;
	VMTools *m_vmtool;

private:
	Ui::OneVideoPro ui;
	QString g_strDriverName[26];//盘符
	int g_nDriverNum;//本地驱动器个数
	QString m_sCurRecDisk;
	QString GetAvailDisk(unsigned long nMinAvailBytes);
	void clearFiles(const QString &folderFullPath);
	bool GetDriverInfo();
	void paintEvent(QPaintEvent *event);
};
