#include "client.h"

#include <QDateTime>
#include <QObject>
#include "db.h"
#include <QMutex>
#include "showcpumemory.h"
#include <QTranslator>
#include <QDesktopWidget>
#include "login.h"

DB *g_pDatabase;
QMutex g_csAlarmList;
QMutex g_mutexDevObj;
std::map<LONG, CJLNDevice *> g_mapDevObj;

vector<TabDevInfo_t*>			g_vectorDevInfo;
vector<TabChannelInfo_t*>		g_vectorChannelInfo;
list<TabUserDevGroup_t*>		g_lstDevGroup;
vector<TabDevGroup_t*>			g_vectorGroupChannel;

map<int, CJLNDevice*> g_mapDevInfo;//主设备ID对应的设备类

BOOL g_bExist = FALSE;

Client* g_pInstance = NULL;

Client::Client(QWidget *parent)
	: QMainWindow(parent)
	, g_bExitAlarmThread(FALSE)
	, g_bHideAlarm(FALSE)
	, m_nAutoSnap(0)
	, m_pModifyDev(NULL)
{
	ui.setupUi(this);
	initUsrSet();

	initSDK();
	initForm();
	initCPUMemery();
	inithomePage();
	initAlarm();
	connect(ui.tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));

	ui.tabWidget->setCurrentIndex(1);

	max = false;
	
	ui.tabWidget->tabBar()->installEventFilter(this);
	
	g_hEventAlarm = CreateEvent(NULL, FALSE, FALSE, NULL);

	QDesktopWidget* desktopWidget = QApplication::desktop();
	
	setGeometry(desktopWidget->availableGeometry());
	setWindowIcon(QIcon(QPixmap("main.ico")));

	m_bTranslator = false;	
	
	setWindowTitle("Smart VMS");
	strLogfile = QString("%1\\clientlog.txt").arg(QCoreApplication::applicationDirPath());
	mlogInit(strLogfile.toLatin1().data());
	
	QWidget::setAttribute(Qt::WA_QuitOnClose, true);
}

Client::~Client()
{
	UninitForm();
}

void Client::UninitForm()
{
	if (m_pPreviewPro)
	{
		delete m_pPreviewPro;
		m_pPreviewPro = NULL;
	}
	if (m_pVideoPlayBack)
	{
		delete m_pVideoPlayBack;
		m_pVideoPlayBack = NULL;
	}
	if (m_pDlgExport)
	{
		delete m_pDlgExport;
		m_pDlgExport = NULL;
	}
	if (m_pEqment)
	{
		delete m_pEqment;
		m_pEqment = NULL;
	}
	if (m_pUserMgt)
	{
		delete m_pUserMgt;
		m_pUserMgt = NULL;
	}
	if (m_pDlgSystemSet)
	{
		delete m_pDlgSystemSet;
		m_pDlgSystemSet = NULL;
	}
	if (m_pLogSearch)
	{
		delete  m_pLogSearch;
		m_pLogSearch = NULL;
	}
	if (m_pDlgDeviceConfig)
	{
		delete m_pDlgDeviceConfig;
		m_pDlgDeviceConfig = NULL;
	}
	if (m_pModifyDev)
	{
		delete m_pModifyDev;
		m_pModifyDev = NULL;
	}

	VideoNet_Cleanup();
}

void Client::inittabWindow()
{
	m_pDlgSystemSet = new systemSet();
	m_pTreeDev = new DevTreePro;

	m_pPreviewPro = new PreView();
	m_pPreviewPro->m_pTreeDev = m_pTreeDev;

	m_pVideoPlayBack = new videoPlayback();//items.count();
	m_pVideoPlayBack->m_pTreeDev = m_pTreeDev;
	m_pVideoPlayBack->initTree();

	m_pDlgExport = new CompareRecord();
	m_pDlgExport->m_pTreeDev = m_pTreeDev;

	m_pEqment = new equimentMgt();
	m_pEqment->m_pTreeDev = m_pTreeDev;

	m_pLogSearch = new LogSearch();		
	m_pLogSearch->m_pTreeDev = m_pTreeDev;


	m_pDlgDeviceConfig = new BehaviorAnalyseDlg;
	m_pDlgDeviceConfig->m_pTreeDev = m_pTreeDev;
	
	m_pUserMgt = new UserMgt();	
}

void Client::initAlarm()
{
	memset(&g_AlarmAudioCfg, 0, sizeof(g_AlarmAudioCfg));
	QString file;
	file = QString("%1\\LoginMsg.ini").arg(QCoreApplication::applicationDirPath());

	TCHAR buff[256];
	memset(buff, 0, sizeof(buff));
	for (int i = 0; i < 5; i++)
	{
		QString csAlarmSource;
		csAlarmSource = QString("%1").arg(i);
		g_AlarmAudioCfg[i].nPlayAudio = ::GetPrivateProfileInt(csAlarmSource.toLatin1().data(), "audio", 0, file.toLatin1().data());
		g_AlarmAudioCfg[i].nAudioLoop = ::GetPrivateProfileInt(csAlarmSource.toLatin1().data(), "loop", 0, file.toLatin1().data());
		::GetPrivateProfileString(csAlarmSource.toLatin1().data(), "file", NULL, g_AlarmAudioCfg[i].szFileName, 256, file.toLatin1().data());
	}
	m_nAutoSnap = ::GetPrivateProfileInt("LoginMsg", "AutoSnap", 0, file.toLatin1().data());
}
void Client::initCPUMemery()
{
	ShowCPUMemory *showCPUMemory = new ShowCPUMemory(this);
	showCPUMemory->SetLab(ui.labCPUMemory);
#ifdef __arm__
	showCPUMemory->Start(3000);
#else
	showCPUMemory->Start(1000);
#endif

	/*setFont(QFont("Microsoft Yahei", 13));

	QString qss1 = QString("QLabel{background-color:rgb(0,0,0);color:rgb(%1);}").arg("100,184,255");
	

	ui.labCPUMemory->setStyleSheet(qss1);

	connect(ui.labCPUMemory, SIGNAL(textChanged(QString)), ui.labCPUMemory, SLOT(setText(QString)));

	ui.labCPUMemory->start(1500);*/
}

static void __stdcall DisConnectBackCallFunc(JVT_LONG lLoginID, char *pchDVRIP, LONG nDVRPort, JVT_DWORD dwUser)
{
	Client* pDlg = (Client*)dwUser;
	LONG lDevId;
	CJLNDevice *pDev = NULL;
	std::map<LONG, CJLNDevice *>::iterator dev_iter;
	char szLog[1024] = { 0 };
	sprintf(szLog, "Device lost IP is %s \r\n", pchDVRIP);
	OutputDebugString(szLog);

	g_mutexDevObj.lock();
	dev_iter = g_mapDevObj.find(lLoginID);
	if (dev_iter != g_mapDevObj.end())
	{
		pDev = dev_iter->second;
	}
	if (pDev == NULL)
	{
		g_mutexDevObj.unlock();
		return;
	}
	lDevId = pDev->GetDevInfo()->nDevId;
	g_mutexDevObj.unlock();
	mlog(LOG_NOTICE, "ReConnect LoginID = %d,DevID = %d!", lLoginID, lDevId);

	pDlg->OnDeviceLost(pDev);
}

static void __stdcall SubDisConnectCallBack(JVT_LONG lLoginID, SubConnType type, long nChannel, JVT_DWORD dwUser)
{
	return;
}

static bool __stdcall JVTMessCallBack(JVT_LONG lLoginID, char *pBuf, unsigned long dwBufLen, JVT_DWORD dwUser)
{
	Client* pDlg = (Client*)dwUser;
	LONG lAlarmType = -1;
	LONG lAlarmChannel = -1;
	if (dwBufLen != sizeof(SDK_AlarmInfo))
	{
		return FALSE;
	}
	SDK_AlarmInfo alarmInfo;
	memcpy(&alarmInfo, pBuf, dwBufLen);

	switch (alarmInfo.iEvent)
	{
	case SDK_EVENT_CODE_NET_ALARM:
	case SDK_EVENT_CODE_MANUAL_ALARM:
	case SDK_EVENT_CODE_LOCAL_ALARM:
		lAlarmType = ALARM_SOURCE_ALARMIN;
		break;
	case SDK_EVENT_CODE_VIDEO_MOTION:
		lAlarmType = ALARM_SOURCE_MOVING_DETECT;
		break;
	case SDK_EVENT_CODE_VIDEO_LOSS:
		lAlarmType = ALARM_SOURCE_LOSE_SIGNAL;
		break;
	case SDK_EVENT_CODE_VIDEO_BLIND:
		lAlarmType = ALARM_SOURCE_VIDEO_BLIND;
		break;
	case SDK_EVENT_CODE_STORAGE_FAILURE:
		lAlarmType = ALARM_DISK_BAD;
		break;
	case SDK_EVENT_CODE_LOW_SPACE:
		lAlarmType = ALARM_DISK_LOW;
		break;
	case SDK_EventBrightness:
		lAlarmType = ALARM_EventBrightness;
		break;
	case SDK_EventShelter:
		lAlarmType = ALARM_EventShelter;
		break;
	case SDK_EventCrossLine:
		lAlarmType = ALARM_EventCrossLine;
		break;
	case SDK_EventCrossArea:
		lAlarmType = ALARM_EventCrossArea;
		break;
	case SDK_EventColor:
		lAlarmType = ALARM_EventColor;
		break;
	case SDK_EventSound:
		lAlarmType = ALARM_EventSound;
		break;
	case SDK_EventLoseOBJ:
		lAlarmType = ALARM_EventLoseOBJ;
		break;
	}

	if (lAlarmType == -1)
		return TRUE;

	lAlarmChannel = alarmInfo.nChannel + 1;

	LONG lDevId;
	CJLNDevice *pDev = NULL;
	std::map<LONG, CJLNDevice *>::iterator dev_iter;
	g_mutexDevObj.lock();
	dev_iter = g_mapDevObj.find(lLoginID);
	if (dev_iter != g_mapDevObj.end())
	{
		pDev = dev_iter->second;
	}
	if (pDev == NULL)
	{
		g_mutexDevObj.unlock();
		return 0;
	}
	lDevId = pDev->GetDevInfo()->nDevId;


	g_mutexDevObj.unlock();

	pDlg->alarm_callback(lDevId, lAlarmType, lAlarmChannel, "");

	return TRUE;
}

void Client::initSDK()
{
	//initialize
	BOOL bResult = VideoNet_Init((fDisConnect)DisConnectBackCallFunc, (JVT_DWORD)this,TRUE);
	VideoNet_SetDVRMessCallBack(JVTMessCallBack, (JVT_DWORD)this);
	VideoNet_SetSubDisconnectCallBack(SubDisConnectCallBack ,(JVT_DWORD)this);
	VideoNet_SetConnectTime(5000, 3);	
}

static DWORD WINAPI AlarmThread(LPVOID lpParam)
{
	Client* pDevice = (Client*)lpParam;
	if (NULL == pDevice)
	{
		return -1;
	}
	pDevice->AlarmThreadPro();
	return 0;
}

void Client::initDlag()
{
	
	DWORD dwThreadId = 0;
	HANDLE hThread = CreateThread(NULL, 0, AlarmThread, this, 0, &dwThreadId);
	if (hThread)
	{
		CloseHandle(hThread);
		hThread = NULL;
	}
}

void Client::initUsrSet()
{
	QMenu *menu = new QMenu;
	actionAbout = new QAction(this);
	actionAbout->setText(QObject::tr("关于"));
	menu->addAction(actionAbout);
	connect(actionAbout, SIGNAL(triggered()), this, SLOT(actionAboutSlot()));

	/*menuLanguage = new QMenu();
	menuLanguage->setTitle(QObject::tr("语言"));
	menu->addMenu(menuLanguage);
	actionChinese = new QAction(this);
	actionChinese->setText(QObject::tr("中文"));
	
	actionEnglish = new QAction(this);
	actionEnglish->setText(QObject::tr("英文"));
	menuLanguage->addAction(actionChinese);
	menuLanguage->addAction(actionEnglish);
	actionChinese->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
	actionEnglish->setIcon(QIcon(QPixmap("")));
	connect(actionChinese, SIGNAL(triggered()), this, SLOT(actionChineseSlot()));
	connect(actionEnglish, SIGNAL(triggered()), this, SLOT(actionEnglishSlot()));*/
	ui.btnSetLanguage->setMenu(menu);
}

static DWORD WINAPI ConnectThread(LPVOID lpParam)
{
	JVT_LONG lLoginID = 0;
	CJLNDevice* pDevInfo = (CJLNDevice*)lpParam;
	if (pDevInfo)
	{
		while (pDevInfo->m_bReconnecting)
		{
			if (WaitForSingleObject(pDevInfo->m_hExsitEvent, 1000) == WAIT_OBJECT_0)
			{
				break;
			}
			lLoginID = pDevInfo->Login();
			if (lLoginID > 0)
			{
				break;
			}
		}
	}
	CloseHandle(pDevInfo->m_hConnectThread);
	pDevInfo->m_hConnectThread = NULL;
	return 1;
}

void Client::InitUI()
{
	inittabWindow();
	InitDataBase();

	m_pTreeDev->init();
}

void Client::InitDataBase()
{
	g_pDatabase->QueryAllMainDev(g_vectorDevInfo);
	g_pDatabase->QueryAllSlaveDev(g_vectorChannelInfo);
	g_pDatabase->QueryAllDevGroup(g_lstDevGroup);
	g_pDatabase->QueryAllGroupChannel(g_vectorGroupChannel);
	
	for (size_t i = 0; i < g_vectorDevInfo.size(); i++)
	{
		AddDevice(g_vectorDevInfo[i]);
	}
}

void Client::AddDevice(TabDevInfo_t* pDevInfo)
{
	if (!pDevInfo)
	{
		return;
	}

	CJLNDevice* pDevObj;
	pDevObj = new CJLNDevice();
	pDevObj->SetDevInfo(pDevInfo);
	g_mapDevInfo[pDevInfo->nDevId] = pDevObj;

	vector<TabChannelInfo_t*>::iterator iterSlave;
	for (iterSlave = g_vectorChannelInfo.begin(); iterSlave != g_vectorChannelInfo.end(); ++iterSlave)
	{
		if ((*iterSlave)->DevId == pDevInfo->nDevId)
		{
			pDevObj->SetChannelInfo(*iterSlave);
			m_pTreeDev->m_mapChannelInfo[(*iterSlave)->SlaveDevId] = *iterSlave;
		}
	}

	pDevObj->m_bReconnecting = TRUE;
	pDevObj->m_hConnectThread = CreateThread(NULL, 0, ConnectThread, pDevObj, 0, NULL);
}

void Client::DeleteDevice(int nDevId)
{
	vector<TabChannelInfo_t *>::iterator iterChannel = g_vectorChannelInfo.begin();
	vector<TabDevInfo_t *>::iterator iterDev = g_vectorDevInfo.begin();

	while (g_vectorChannelInfo.end() != iterChannel)
	{
		if ((*iterChannel)->DevId == nDevId)
		{
			delete *iterChannel;
			*iterChannel = NULL;
			g_vectorChannelInfo.erase(iterChannel);
			continue;
		}
		iterChannel++;
	}

	while (g_vectorDevInfo.end() != iterDev)
	{
		if ((*iterDev)->nDevId == nDevId)
		{
			delete *iterDev;
			*iterDev = NULL;
			g_vectorDevInfo.erase(iterDev);
			break;
		}
		iterDev++;
	}

	map<int, CJLNDevice*>::iterator iterDevObj = g_mapDevInfo.find(nDevId);
	if (iterDevObj != g_mapDevInfo.end())
	{
		CJLNDevice* pDevObj = iterDevObj->second;
		DeleteDevObj(pDevObj);
		g_mapDevInfo.erase(iterDevObj);
	}
}

static DWORD WINAPI DeleteThread(LPVOID lpParam)
{
	CJLNDevice* pDevObj = (CJLNDevice*)lpParam;
	if (pDevObj)
	{
		delete pDevObj;
		pDevObj = NULL;
	}
	return 1;
}

void Client::DeleteDevObj(CJLNDevice* pDevObj)
{
	HANDLE hThread = CreateThread(NULL, 0, DeleteThread, pDevObj, 0, NULL);
	if (hThread)
	{
		CloseHandle(hThread);
		hThread = NULL;
	}
}

void Client::closeEvent(QCloseEvent *event)
{	
	if(myHelper::ShowMessageBoxQuesion(QObject::tr("确定退出程序吗？")) == 1)
	{
		event->accept();
		UninitForm();
		mlog(LOG_DEBUG, QObject::tr("程序退出").toLocal8Bit().data());
		mlogClose();
	}
	else
	{
		event->ignore();
	}
}



void Client::alarm_callback(JVT_LONG lDevId, JVT_LONG lAlarmType, JVT_LONG lChannel, char* szMsg)
{
	AlarmInfo_t* pAlarm = new AlarmInfo_t;
	ZeroMemory(pAlarm, sizeof(AlarmInfo_t));

	pAlarm->nDevId = lDevId;
	pAlarm->nAlarmChannel = lChannel;
	pAlarm->nAlarmSource = lAlarmType;
	CompareEvent *custevent = new CompareEvent(CET_ALARMNOTIFY);
	QApplication::postEvent(g_pInstance, custevent);	
}


void Client::AlarmThreadPro()
{	
	BOOL bGetAlarmConf = FALSE;
	std::list<TabAlarmConf_t*> lstAlarmConf;
	std::map<int, int> mapAlarmDev;
	list<TabAlarmConf_t *>::iterator  iterAlarm;
	AlarmInfo_t* pAlarm = new AlarmInfo_t;

	while (!g_bExitAlarmThread)
	{
		WaitForSingleObject(g_hEventAlarm, INFINITE);
		if (g_pDatabase->QueryAlarmDev(lstAlarmConf, -1) <= 0) //1.获取alarmconf表中的设备
		{	
 			for (list<AlarmInfo_t*>::iterator it = g_listAlarm.begin(); it != g_listAlarm.end(); ++it)
			{
				AlarmInfo_t* pTmp = (*it);
				if (NULL != pTmp)
				{
					delete *it;
				}
			}
			g_listAlarm.clear();
			continue;
		}
		//4.获取告警配置并进行联动
		while (1)
		{
			g_csAlarmList.lock();
			if (g_listAlarm.empty())
			{
				ResetEvent(g_hEventAlarm);
				g_csAlarmList.unlock();
				break;
			}
			AlarmInfo_t* pTmp = g_listAlarm.front();
			g_listAlarm.pop_front();
			g_csAlarmList.unlock();

			memcpy(pAlarm, pTmp, sizeof(AlarmInfo_t));
			delete pTmp;

			//获取配置
			TabAlarmConf_t tabAlarmConf;
			int nChannel;
			if (pAlarm->nAlarmSource == ALARM_DISK_BAD || pAlarm->nAlarmSource == ALARM_DISK_LOW)
				nChannel = 1;
			else
				nChannel = pAlarm->nAlarmChannel;
			if (g_pDatabase->GetAlarmConf(&tabAlarmConf, pAlarm->nDevId, pAlarm->nAlarmSource, nChannel) <= 0)
				continue;
			if (pAlarm->nAlarmSource == ALARM_DISK_BAD)
				tabAlarmConf.Channel = pAlarm->nAlarmChannel;
			//保存告警记录
			//TODO:保存告警记录
			TabAlarmLog_t  tabLog;
			QString        HandleTime;
			memset(&tabLog, 0, sizeof tabLog);
			tabLog.AlarmConfId = tabAlarmConf.Id;

			if (pAlarm->nAlarmSource < ALARM_EventCount && g_AlarmAudioCfg[pAlarm->nAlarmSource].nPlayAudio)
			{
				int flg = SND_FILENAME | SND_ASYNC;
				if (g_AlarmAudioCfg[pAlarm->nAlarmSource].nAudioLoop)
					flg = flg | SND_LOOP;
				//m_pPreviewPro->OpenAlarmSound();
			}

			 m_pLogSearch->AddMsg(pAlarm->nDevId, &tabAlarmConf); //TODO:优化，不直接操作界面，改为postmsg
			 m_pLogSearch->show();
			if (g_pDatabase->AddAlarmLog(&tabLog) <= 0)
				continue;
		}



		for (iterAlarm = lstAlarmConf.begin(); iterAlarm != lstAlarmConf.end(); ++iterAlarm)
		{
			delete (*iterAlarm);
		}
		lstAlarmConf.clear();

	}

	delete pAlarm;
	pAlarm = NULL;
}

bool Client::event(QEvent* e)
{
	CompareEvent *pEvent = static_cast<CompareEvent *>(e);

	
	if (e->type() == CET_ALARMNOTIFY)
	{
		OnAlarmNotify();
	}
	QWidget::event(pEvent);
	return true;
}

void Client::OnDeviceLost(CJLNDevice *wParam)
{
	CJLNDevice* pDevInfo = wParam;
	if (pDevInfo)
	{
		pDevInfo->m_bReconnecting = TRUE;
		pDevInfo->Reconnect();
	}	
}

void Client::OnAlarmNotify()
{
	AlarmInfo_t* pAlarm = new AlarmInfo_t;
	if (pAlarm->nDevId == 0 && pAlarm->nAlarmChannel == -1)
	{
		return ;
	}

	if (pAlarm == NULL)
	{
		return ;
	}

	g_csAlarmList.lock();
	g_listAlarm.push_back(pAlarm);
	g_csAlarmList.unlock();
	SetEvent(g_hEventAlarm);
	return;
}



void Client::btnPrew_clicked()
{	
	if (m_TabWidget.m_bPreview == false)
	{
		ui.tabWidget->addTab(m_pPreviewPro, QObject::tr("预览"));
		
		m_TabWidget.m_bPreview = true;
		
	}
	m_pPreviewPro->initTree();
	ui.tabWidget->setCurrentWidget(m_pPreviewPro);	
}

void Client::btnPlayBack_clicked()
{	
	if (m_TabWidget.m_bVideoPlayback == false)
	{
		ui.tabWidget->addTab(m_pVideoPlayBack, QObject::tr("视频回放"));
		
		m_TabWidget.m_bVideoPlayback = true;		
	}
	m_pVideoPlayBack->initTree();
	ui.tabWidget->setCurrentWidget(m_pVideoPlayBack);	
}

void Client::btnFace_clicked()
{
	if (m_TabWidget.m_bFaceMgt == false)
	{
		ui.tabWidget->addTab(m_pDlgExport, QObject::tr("人脸管理"));

		m_TabWidget.m_bFaceMgt = true;
	}
	m_pDlgExport->initTree();
	ui.tabWidget->setCurrentWidget(m_pDlgExport);
}
void Client::btnParamete_clicked()
{
	if (m_TabWidget.m_bParamete == false)
	{
		ui.tabWidget->addTab(m_pDlgDeviceConfig, QObject::tr("设备配置"));

		m_TabWidget.m_bParamete = true;

	}
	m_pDlgDeviceConfig->initTree();
	ui.tabWidget->setCurrentWidget(m_pDlgDeviceConfig);
}
void Client::btnSet_clicked()
{	
	m_pDlgSystemSet->setWindowFlags(windowFlags());
	m_pDlgSystemSet->exec();
}

void Client::btnEquiment_clicked()
{
	if (m_TabWidget.m_bEqmentMgt == false)
	{
		ui.tabWidget->addTab(m_pEqment, QObject::tr("设备管理"));

		m_pEqment->CreateWidget();
		m_pEqment->on_btnSearch_clicked();

		m_TabWidget.m_bEqmentMgt = true;

	}
	m_pEqment->initTree();
	ui.tabWidget->setCurrentWidget(m_pEqment);
}

void Client::btnLogsearch_clicked()
{
	if (m_TabWidget.m_bLogMgt == false)
	{
		ui.tabWidget->addTab(m_pLogSearch, QObject::tr("日志搜索"));

		m_TabWidget.m_bLogMgt = true;
	}
	ui.tabWidget->setCurrentWidget(m_pLogSearch);
}

void Client::btnUser_clicked()
{
	if (m_TabWidget.m_bUserMgt == false)
	{
		ui.tabWidget->addTab(m_pUserMgt, QObject::tr("用户管理"));

		m_TabWidget.m_bUserMgt = true;

	}
	ui.tabWidget->setCurrentWidget(m_pUserMgt);
}

void Client::getTabState(int index)
{
	if (ui.tabWidget->tabText(index) == QObject::tr("日志搜索"))
	{
		m_TabWidget.m_bLogMgt = false;
	}
	else if (ui.tabWidget->tabText(index) == QObject::tr("设备管理"))
	{
		m_TabWidget.m_bEqmentMgt = false;
	}
	else if (ui.tabWidget->tabText(index) == QObject::tr("人脸管理"))
	{
		m_TabWidget.m_bFaceMgt = false;
	}
	else if (ui.tabWidget->tabText(index) == QObject::tr("用户管理"))
	{
		m_TabWidget.m_bUserMgt = false;
	}
	
	else if (ui.tabWidget->tabText(index) == QObject::tr("视频回放"))
	{
		m_TabWidget.m_bVideoPlayback = false;
	}
	else if (ui.tabWidget->tabText(index) == QObject::tr("预览"))
	{
		m_TabWidget.m_bPreview = false;
		m_pPreviewPro->StopAllWatch();
	}
	else if (ui.tabWidget->tabText(index) == QObject::tr("设备配置"))
	{
		m_TabWidget.m_bParamete = false;
	}	
}

void Client::removeSubTab(int index)
{
	if (index == 0)
		return;
	getTabState(index);
	ui.tabWidget->removeTab(index);
}

void Client::initForm()
{	
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);	

	IconHelper::Instance()->setIcon(ui.btnSetLanguage, QChar(0xf0d7),15);
	memset(&m_TabWidget, 0, sizeof(TabWidget));
	m_TabWidget.m_bFaceMgt = false;
	
	m_TabWidget.m_bEqmentMgt = false;

	m_TabWidget.m_bLogMgt = false;
	
	m_TabWidget.m_bPreview = false;
	
	m_TabWidget.m_bSystemSet = false;

	m_TabWidget.m_bUserMgt = false;
	
	m_TabWidget.m_bVideoPlayback = false;
}

void Client::on_btnMenu_Min_clicked()
{
	showMinimized();	
}

void Client::on_btnMenu_Max_clicked()
{
	if (max) {
		this->setGeometry(qApp->desktop()->availableGeometry());
	}
	else {
		this->setGeometry(QRect(400,200,1027,727));
		this->setProperty("canMove", true);
	}

	max = !max;	
}

void Client::on_btnMenu_Close_clicked()
{
	close();
}

void Client::btnDuijiang_clicked()
{

}

void Client::btnAlarmLog_clicked()
{
	/*DeviceLog *m_deviceLog = new DeviceLog();

	ui.tabWidget->addTab(m_deviceLog, QStringLiteral("预览"));

	ui.tabWidget->setCurrentWidget(m_deviceLog);*/
}

bool Client::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::Enter)
	{
		ui.tabWidget->setTabsClosable(true);
	}
	else if (event->type() == QEvent::Leave)
	{
		ui.tabWidget->setTabsClosable(false);
	}
	return QObject::eventFilter(object, event);
}

void Client::inithomePage()
{
	//ui.widget_user->setText(QObject::tr("用户管理"));
	ui.widget_user->setImage(":/res/SoftIcon/image/user.png");
	connect(ui.widget_user, SIGNAL(widget_clicked()), this, SLOT(btnUser_clicked()));

	//ui.widget_face->setText(QObject::tr("人脸管理"));
	ui.widget_face->setImage(":/res/SoftIcon/image/face.png");
	connect(ui.widget_face, SIGNAL(widget_clicked()), this, SLOT(btnFace_clicked()));

	//ui.widget_equiment->setText(QObject::tr("设备管理"));
	ui.widget_equiment->setImage(":/res/SoftIcon/image/device.png");
	connect(ui.widget_equiment, SIGNAL(widget_clicked()), this, SLOT(btnEquiment_clicked()));

	//ui.widget_Log->setText(QObject::tr("告警日志"));
	ui.widget_Log->setImage(":/res/SoftIcon/image/Log.png");
	connect(ui.widget_Log, SIGNAL(widget_clicked()), this, SLOT(btnLogsearch_clicked()));

	//ui.widget_Prew->setText(QObject::tr("预览"));
	ui.widget_Prew->setImage(":/res/SoftIcon/image/Prew.png");
	connect(ui.widget_Prew, SIGNAL(widget_clicked()), this, SLOT(btnPrew_clicked()));

	//ui.widget_PlayBack->setText(QObject::tr("视频回放"));
	ui.widget_PlayBack->setImage(":/res/SoftIcon/image/playblack.png");
	connect(ui.widget_PlayBack, SIGNAL(widget_clicked()), this, SLOT(btnPlayBack_clicked()));

	//ui.widget_set->setText(QObject::tr("设置"));
	ui.widget_set->setImage(":/res/SoftIcon/image/set.png");
	connect(ui.widget_set, SIGNAL(widget_clicked()), this, SLOT(btnSet_clicked()));

	//ui.widget_skin->setText(QObject::tr("切换皮肤"));
	//ui.widget_skin->setImage(":/res/SoftIcon/image/Skin.png");
	//connect(ui.widget_skin, SIGNAL(widget_clicked()), this, SLOT(on_btnSkin_clicked()));

	ui.widget_DevicePara->setImage(":/res/SoftIcon/image/DevicePara.png");
	connect(ui.widget_DevicePara, SIGNAL(widget_clicked()), this, SLOT(btnParamete_clicked()));
	
}

//切换中文
void Client::actionChineseSlot()
{
	if (ui.tabWidget->count() > 1)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请关闭多余的窗口"));
		return;
	}
	if (m_bTranslator == true)
	{
		actionChinese->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
		actionEnglish->setIcon(QIcon(QPixmap("")));
		actionAbout->setText(QObject::tr("关于"));
		actionChinese->setText(QObject::tr("中文"));
		actionEnglish->setText(QObject::tr("英文"));
		menuLanguage->setTitle(QObject::tr("语言"));
		qApp->removeTranslator(&translator);
		ui.retranslateUi(this);
		m_bTranslator = false;
	}
}

//切换英文
void Client::actionEnglishSlot()
{
	if (ui.tabWidget->count() > 1)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请关闭多余的窗口"));
		return;
	}
	if (m_bTranslator == false)
	{
		actionEnglish->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
		actionChinese->setIcon(QIcon(QPixmap("")));
		actionAbout->setText("About");
		actionChinese->setText("Chinese");
		actionEnglish->setText("English");
		menuLanguage->setTitle("Language");
	
		translator.load("svms_en.qm");
		qApp->installTranslator(&translator);
		ui.retranslateUi(this);
		m_bTranslator = true;
	}

}

//关于
void Client::actionAboutSlot()
{
	About m_about(this);
	m_about.setWindowFlags(windowFlags());
	m_about.exec();
}

void Client::showEvent(QShowEvent *e)
{
	this->setAttribute(Qt::WA_Mapped);
	QWidget::showEvent(e);
}

void Client::ModifyDev(char* pszDevIP)
{
	//查找设备信息
	TabDevInfo_t* pDevInfo = NULL;
	vector<TabDevInfo_t*>::iterator iterDev = g_vectorDevInfo.begin();

	while (g_vectorDevInfo.end() != iterDev)
	{
		if (memcmp((*iterDev)->szIpAddr, pszDevIP, strlen(pszDevIP)) == 0)
		{
			pDevInfo = *iterDev;
			break;
		}
		iterDev++;
	}
	if (!pDevInfo)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("查询数据失败!"));
		return;
	}
	if (!m_pModifyDev)
	{
		m_pModifyDev = new ModifyDevice;
	}
	m_pModifyDev->m_pDevInfo = pDevInfo;
	memcpy(m_pModifyDev->m_pNewDevInfo, pDevInfo, sizeof(TabDevInfo_t));

	int ChannelNum = g_pDatabase->QueryDeviceChannelMsg(pDevInfo->nDevId);
	m_pModifyDev->m_displayName->setText(pDevInfo->szDevName);
	m_pModifyDev->m_displayIP->setText(pDevInfo->szIpAddr);
	m_pModifyDev->m_displayUsr->setText(pDevInfo->szLoginName);
	m_pModifyDev->m_displayPwd->setText(pDevInfo->szPassword);
	m_pModifyDev->m_displayPort->setText(QString::number(pDevInfo->nPort));
	m_pModifyDev->m_displySubType->setCurrentIndex(getDeviceID(pDevInfo->nSubDevType));
	m_pModifyDev->m_displayChannel->setCurrentIndex(getCurIndex(ChannelNum));
	m_pModifyDev->show();
}

int Client::getDeviceType(int nIndex)
{
	int subtype = SDK_DEV_TYPE_BSIPC;
	switch (nIndex)
	{
	case 0:
		subtype = SDK_DEV_TYPE_BSIPC;
		break;
	case 1:
		subtype = SDK_DEV_TYPE_FPIPC;
		break;
	case 2:
		subtype = SDK_DEV_TYPE_MJIPC;
		break;
	case 3:
		subtype = SDK_DEV_TYPE_IPC;
		break;
	default:
		subtype = SDK_DEV_TYPE_BSIPC;
		break;
	}
	return subtype;
}

int Client::getDeviceID(int nSubType)
{
	int nIndex = 0;
	switch (nSubType)
	{
	case SDK_DEV_TYPE_BSIPC:
		nIndex = 0;
		break;
	case SDK_DEV_TYPE_FPIPC:
		nIndex = 1;
		break;
	case SDK_DEV_TYPE_MJIPC:
		nIndex = 2;
		break;
	case SDK_DEV_TYPE_IPC:
		nIndex = 3;
		break;
	default:
		nIndex = 0;
		break;
	}
	return nIndex;
}

int Client::getCurIndex(int mode)
{
	int count = 0;
	switch (mode)
	{
	case 1:
		count = 0;
		break;
	case 4:
		count = 1;
		break;
	case 8:
		count = 2;
		break;
	case 16:
		count = 3;
		break;
	case 32:
		count = 4;
		break;
	default:
		break;
	}
	return count;
}

void Client::OnReFreshOtherTree()
{
	m_pTreeDev->ReInit(FALSE);
	if (m_TabWidget.m_bEqmentMgt)
	{
		m_pEqment->OnTreeReFresh();
	}
	if (m_TabWidget.m_bPreview)
	{
		m_pPreviewPro->OnTreeReFresh();
	}
	if (m_TabWidget.m_bVideoPlayback)
	{
		m_pVideoPlayBack->OnTreeReFresh();
	}
	if (m_TabWidget.m_bFaceMgt)
	{		
		m_pDlgExport->OnTreeReFresh();
	}
	if (m_TabWidget.m_bParamete)
	{
		m_pDlgDeviceConfig->OnTreeReFresh();
	}
}

QString Client::GetModeType(int nMode)
{

	QString strMode = QObject::tr("陌生人");
	switch (nMode)
	{
	case 0:
		strMode = QObject::tr("陌生人");
		break;
	case 1:
		strMode = QObject::tr("黑名单");
		break;
	case 2:
		strMode = QObject::tr("白名单");
		break;
	case 3:
		strMode = QObject::tr("VIP名单");
		break;
	default:
		break;
	}
	return strMode;
}
