#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_client.h"
#include "logsearch.h"
#include "usermgt.h"
#include "comparerecord.h"
#include <QTimer>
#include "equimentmgt.h"
#include "videoplayback.h"
#include "systemset.h"
#include "About.h"
#include <qmenu.h>
#include <QTabWidget>
#include "PreView.h"
#include <QMouseEvent>
#include "devtreepro.h"
#include "CompareEvent.h"
#include <QObject>
#include <QTranslator>
#include "myhelper.h"
#include "iconhelper.h"
#include <QDesktopWidget>
#include <QShowEvent>


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
	bool m_EQMENTMGT;
	
	bool m_VIDEOPLAY;
	
	bool m_SYSTEM;

	bool m_COMPARECORD;
	
	bool m_USSERMGT;
	
	bool m_LOGSEARCH;
	
	bool m_PREVIEW;
	
	
}TabWidget;
class Client : public QMainWindow
{
	Q_OBJECT

protected:
	Client(QWidget *parent = 0);
	virtual ~Client();
	static Client* m_pInstance;
	void initForm();
	
	void initSDK();
	void initUsrSet();
	void initCPUMemery();
	void inithomePage();
	void initAlarm();
	void inittabWindow();
	void getTabState(int index);
	static DWORD WINAPI AlarmThread(LPVOID lpParam);
	void AlarmThreadPro();
	void OnAlarmNotify();
public:
	HANDLE g_hEventAlarm;
	std::list<AlarmInfo_t*> g_AlarmList;
	BOOL g_bExitAlarmThread = FALSE;
	AlarmAudioCfg_t g_AlarmAudioCfg[6];
	BOOL g_bHideAlarm = FALSE;
	void initDlag();

	void alarm_callback(LONG lDevId, LONG lAlarmType, LONG lChannel, char* szMsg);
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
	CompareRecord*  m_dlgExport;
	PreView* PreviewPro;
	equimentMgt *eqment;
	videoPlayback *m_videoPlayBack;
	LogSearch *log;

	bool m_bTranslator;
	QTranslator translator;
	QAction *actionAbout;
	QAction *actionChinese;
	QAction *actionEnglish;
	QString strLogfile;
	QMenu *menuLanguage;

	CompareEvent *deiceLostEvent;
	UserMgt *user;

	bool max;
	
	TabWidget m_TabWidget;
	QRect screenRect;
	QDesktopWidget* desktopWidget;
	QRect location;
	static Client* instance()  {if(!m_pInstance) m_pInstance=new Client(); return m_pInstance;};
};

#endif // CLIENT_H
