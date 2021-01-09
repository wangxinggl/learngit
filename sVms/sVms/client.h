#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_client.h"
#define  _CRT_SECURE_NO_WARNINGS
#include <QTimer>
#include "About.h"
#include <qmenu.h>
#include <QTabWidget>
#include "PreView.h"
#include <QMouseEvent>
#include "devtreepro.h"
#include <QObject>
#include <QTranslator>
#include <QDesktopWidget>
#include <QShowEvent>
#include "myhelper.h"
#include "iconhelper.h"
#include "logsearch.h"
#include "usermgt.h"
#include "comparerecord.h"
#include "equimentmgt.h"
#include "videoplayback.h"
#include "systemset.h"
#include "CompareEvent.h"
#include "BehaviorAnalyseDlg.h"
#include "table_structs.h"
#include "VideoNetAPI.h"
#include "VideoPlayerAPI.h"
#include "modifydevice.h"


#pragma execution_character_set("utf-8") 
typedef struct
{
	int nDevId;
	int nAlarmSource;
	int nAlarmLevel;
	int nAlarmType;
	int nAlarmChannel;
}AlarmInfo_t;

typedef struct _TabWidget
{	
	bool m_bPreview;		//预览
	bool m_bFaceMgt;		//人脸管理
	bool m_bVideoPlayback;	//视频回放
	
	bool m_bEqmentMgt;	//设备管理
	bool m_bUserMgt;	//用户管理
	bool m_bSystemSet;		//设置	
	bool m_bLogMgt;			//日志管理	
	bool m_bParamete;		//设备配置
	
}TabWidget;



class Client : public QMainWindow
{
	Q_OBJECT
public:
	Client(QWidget *parent = 0);
	virtual ~Client();

protected:
	void initForm();
	
	void initSDK();
	void initUsrSet();
	void initCPUMemery();
	void inithomePage();
	void initAlarm();
	void inittabWindow();
	void InitDataBase();
	void getTabState(int index);
	void OnAlarmNotify();

	void UninitForm();

public:
	void InitUI();
	HANDLE g_hEventAlarm;
	std::list<AlarmInfo_t*> g_listAlarm;
	BOOL g_bExitAlarmThread;
	AlarmAudioCfg_t g_AlarmAudioCfg[6];
	int m_nAutoSnap;
	BOOL g_bHideAlarm;
	void initDlag();
	void OnDeviceLost(CJLNDevice *wParam);
	void alarm_callback(JVT_LONG lDevId, JVT_LONG lAlarmType, JVT_LONG lChannel, char* szMsg);
	void AddDevice(TabDevInfo_t* pDevInfo);
	void DeleteDevice(int nDevId);
	void DeleteDevObj(CJLNDevice* pDevObj);
	void AlarmThreadPro();

	void ModifyDev(char* pszDevIP);
	int getDeviceType(int nIndex);
	int getDeviceID(int nSubType);
	int getCurIndex(int mode);
	QString GetModeType(int nMode);		//获取名单类型

	void OnReFreshOtherTree();
	
private slots:
	
	void removeSubTab(int index);
	

	void on_btnMenu_Min_clicked();
	void on_btnMenu_Max_clicked();
	void on_btnMenu_Close_clicked();

	void btnUser_clicked();
	void btnFace_clicked();
	void btnEquiment_clicked();
	void btnPrew_clicked();
	void btnDuijiang_clicked();
	void btnPlayBack_clicked();
	void btnLogsearch_clicked();
	void btnAlarmLog_clicked();
	void btnSet_clicked();
	void btnParamete_clicked();
public slots:
	//切换中英文
	void  actionChineseSlot();
	void  actionEnglishSlot();
	//关于
	void  actionAboutSlot();
private:
	Ui::ClientClass ui;
	
	
protected:
	bool eventFilter(QObject* object, QEvent* event);
	bool event(QEvent *e);
	void showEvent(QShowEvent *e);
protected:
	// 实现QWidget中的虚函数closeEvent(QCloseEvent*);
	void closeEvent(QCloseEvent *event);
public:
	QTabWidget *m_stackwidget;
	PreView* m_pPreviewPro;
	videoPlayback *m_pVideoPlayBack;
	CompareRecord*  m_pDlgExport;

	equimentMgt *m_pEqment;
	UserMgt *m_pUserMgt;
	LogSearch * m_pLogSearch;
	systemSet * m_pDlgSystemSet;
	DevTreePro* m_pTreeDev;

	BehaviorAnalyseDlg *m_pDlgDeviceConfig;		//设备配置
	bool m_bTranslator;
	QTranslator translator;
	QAction *actionAbout;
	QAction *actionChinese;
	QAction *actionEnglish;
	QString strLogfile;
	QMenu *menuLanguage;

	CompareEvent *deiceLostEvent;

	bool max;
	
	TabWidget m_TabWidget;
	QRect screenRect;
	QDesktopWidget* desktopWidget;
	QRect location;
	ModifyDevice* m_pModifyDev;
};

#endif // CLIENT_H
