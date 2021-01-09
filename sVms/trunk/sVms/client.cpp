#include "client.h"

#include <QDateTime>
#include <QObject>
#include "db.h"
#include <QMutex>
#include "showcpumemory.h"
#include "JLNDevice.h"
#include <QTranslator>
#include <QDesktopWidget>
#include "login.h"


QMutex g_csAlarmList;
Client *Client::m_pInstance = NULL;

Client::Client(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initUsrSet();
	
	initForm();
	initSDK();
	initCPUMemery();
	inithomePage();
	initAlarm();
	connect(ui.tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));

	ui.tabWidget->setCurrentIndex(1);

	max = false;
	
	ui.tabWidget->tabBar()->installEventFilter(this);
	
	g_hEventAlarm = CreateEvent(NULL, FALSE, FALSE, NULL);

	QDesktopWidget *widget = QApplication::desktop();

	// 触发resizeEvent函数调用
	setGeometry(qApp->desktop()->availableGeometry());

	setWindowIcon(QIcon(QPixmap("main.ico")));

	m_bTranslator = false;
	
	
	setWindowTitle("Smart VMS");
	strLogfile = QString("%1\\clientlog.txt").arg(QCoreApplication::applicationDirPath());
	mlogInit(strLogfile.toLatin1().data());

	inittabWindow();
	initDlag();
	
	
}

Client::~Client()
{
	if(m_pInstance)
		delete m_pInstance;

}

void Client::inittabWindow()
{
	log = new LogSearch();
	
	m_dlgExport = new CompareRecord();
	
	user = new UserMgt();
	
	m_videoPlayBack = new videoPlayback();//items.count();
	
	PreviewPro = new PreView();
	
	eqment = new equimentMgt();
	
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
void Client::initSDK()
{
	//initialize
	BOOL bResult = VideoNet_Init((fDisConnect)DisConnectBackCallFunc, (JVT_DWORD)this);
	VideoNet_SetDVRMessCallBack(JVTMessCallBack, (JVT_DWORD)this);
	VideoNet_SetConnectTime(5000, 3);

	
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
void Client ::closeEvent(QCloseEvent *event)
{
	
	if(myHelper::ShowMessageBoxQuesion(QObject::tr("确定退出程序吗？")) == 1)
	{
		event->accept();
		mlog(LOG_DEBUG, QObject::tr("程序退出").toLocal8Bit().data());
		mlogClose();
	}
	else
	{
		event->ignore();
	}
}


DWORD WINAPI Client::AlarmThread(LPVOID lpParam)
{
	Client* pDevice = (Client*)lpParam;
	if (NULL == pDevice)
	{
		return -1;
	}
	pDevice->AlarmThreadPro();
	return 0;
}

void Client::alarm_callback(LONG lDevId, LONG lAlarmType, LONG lChannel, char* szMsg)
{
	AlarmInfo_t* pAlarm = new AlarmInfo_t;
	ZeroMemory(pAlarm, sizeof(AlarmInfo_t));

	pAlarm->nDevId = lDevId;
	pAlarm->nAlarmChannel = lChannel;
	pAlarm->nAlarmSource = lAlarmType;
	CompareEvent *custevent = new CompareEvent(CompareEvent::getType(CET_ALARMNOTIFY));
	QApplication::postEvent(NULL, custevent);
}


void Client::AlarmThreadPro()
{
	DB *db = new DB;
	
	BOOL bGetAlarmConf = FALSE;
	while (1)
	{
		//1.获取alarmconf表中的设备
		std::list<TabAlarmConf_t*> lstAlarmConf;
		std::map<int, int> mapAlarmDev;
		if (db->QueryAlarmDev(lstAlarmConf, -1) <= 0) //TODO:释放lstAlarmConf
		{
			WaitForSingleObject(g_hEventAlarm, INFINITE);

			//by zjh add delete alarm list*****************************/
		
			for (list<AlarmInfo_t*>::iterator it = g_AlarmList.begin(); it != g_AlarmList.end(); ++it)
			{
				AlarmInfo_t* pTmp = (*it);
				if (NULL != pTmp)
				{
					delete *it;
				}

			}
			g_AlarmList.clear();
			/*************************************/

			if (g_bExitAlarmThread)
				return;   //列表为空
			continue;
		}
		bGetAlarmConf = FALSE;
		//2.login设备
		list<TabAlarmConf_t *>::iterator  iterAlarm;
		for (iterAlarm = lstAlarmConf.begin(); iterAlarm != lstAlarmConf.end(); ++iterAlarm)
		{
			CBaseDeviceInfo* devInfo;
			devInfo = PreviewPro->treePrew->GetBaseDeviceInfo(-1, (*iterAlarm)->DevId);
			if (devInfo != NULL)
				devInfo->SetRecvAlarm(TRUE); //先设置再login
		}
		for (iterAlarm = lstAlarmConf.begin(); iterAlarm != lstAlarmConf.end(); ++iterAlarm)
		{
			CBaseDeviceInfo* devInfo;
			devInfo = PreviewPro->treePrew->GetBaseDeviceInfo(-1, (*iterAlarm)->DevId);
			if (devInfo != NULL)
			{
				int lUserID = devInfo->Login();
				if (lUserID < 0)
					continue;
				if ((*iterAlarm)->AlarmSource == ALARM_DISK_BAD)
				{
					//获取硬盘数,容量
					LONG num = 0;
					//by zjh add 20170831   
					DWORD dwRet;
					SDK_StorageDeviceInformationAll stdiskinfo;			//硬盘信息:
					int nRet = VideoNet_GetDevConfig(lUserID, E_SDK_CONFIG_DISK_INFO, -1, (char *)&stdiskinfo, sizeof(stdiskinfo), &dwRet, 5000);
					if (TRUE == nRet && sizeof(stdiskinfo) == dwRet)
					{
						continue;
					}


					if (stdiskinfo.iDiskNumber == 0)
					{
						alarm_callback((*iterAlarm)->DevId, ALARM_DISK_BAD, -1, ""); //无硬盘
						continue;
					}
				}
			}
		}
		//3.等待告警事件
		while (!g_bExitAlarmThread)
		{
			WaitForSingleObject(g_hEventAlarm, INFINITE);
			if (g_bExitAlarmThread)
			{
				for (iterAlarm = lstAlarmConf.begin(); iterAlarm != lstAlarmConf.end(); ++iterAlarm)
				{
					CBaseDeviceInfo* devInfo;
					devInfo = PreviewPro->treePrew->GetBaseDeviceInfo(-1, (*iterAlarm)->DevId);
					if (devInfo != NULL)
					{
						devInfo->SetRecvAlarm(FALSE);
						devInfo->Logout();  //TODO:崩溃
					}
					delete (*iterAlarm);
				}
				lstAlarmConf.clear();
				return ;
			}

			//4.获取告警配置并进行联动
			while (1)
			{
				g_csAlarmList.lock();
				if (g_AlarmList.empty())
				{
					g_csAlarmList.unlock();
					break;
				}
				AlarmInfo_t* pTmp = g_AlarmList.front();
				g_AlarmList.pop_front();
				g_csAlarmList.unlock();

				AlarmInfo_t alarm;
				AlarmInfo_t* pAlarm = &alarm;
				memcpy(pAlarm, pTmp, sizeof(AlarmInfo_t));
				delete pTmp;

				if (pAlarm->nDevId == -1) //更新告警配置或修改了设备参数(IP,port等) 
				{
					for (iterAlarm = lstAlarmConf.begin(); iterAlarm != lstAlarmConf.end(); ++iterAlarm)
					{
						CBaseDeviceInfo* devInfo;
						devInfo = PreviewPro->treePrew->GetBaseDeviceInfo(-1, (*iterAlarm)->DevId);
						if (devInfo != NULL)
						{
							devInfo->SetRecvAlarm(FALSE);
							//devInfo->Logout();  //优化性能 暂不logout
						}

						delete (*iterAlarm);
					}
					lstAlarmConf.clear();
					bGetAlarmConf = TRUE;
					break;
				}
				//获取配置
				TabAlarmConf_t tabAlarmConf;
				int nChannel;
				if (pAlarm->nAlarmSource == ALARM_DISK_BAD || pAlarm->nAlarmSource == ALARM_DISK_LOW)
					nChannel = 1;
				else
					nChannel = pAlarm->nAlarmChannel;
				if (db->GetAlarmConf(&tabAlarmConf, pAlarm->nDevId, pAlarm->nAlarmSource, nChannel) <= 0)
					continue;
				if (pAlarm->nAlarmSource == ALARM_DISK_BAD)
					tabAlarmConf.Channel = pAlarm->nAlarmChannel;
				//保存告警记录
				//TODO:保存告警记录
				TabAlarmLog_t  tabLog;
				QString        HandleTime;
				memset(&tabLog, 0, sizeof tabLog);

				tabLog.AlarmConfId = tabAlarmConf.Id;

				//进行联动
#if 0
				if (tabAlarmConf.Audio > 0)
				{
					TabAlarmAudio_t tabAudio;
					if (CDB::instance()->GetAlarmAudio(&tabAudio, tabAlarmConf.Audio) <= 0)
						continue;

					PlaySound(tabAudio.szFileName, NULL, SND_ASYNC | SND_FILENAME);
					/*PlaySound("name.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP );
					结束
					PlaySound(NULL,NULL,SND_FILENAME);*/
				}
#else
				if (pAlarm->nAlarmSource < ALARM_EventCount && g_AlarmAudioCfg[pAlarm->nAlarmSource].nPlayAudio)
				{
					int flg = SND_FILENAME | SND_ASYNC;
					if (g_AlarmAudioCfg[pAlarm->nAlarmSource].nAudioLoop)
						flg = flg | SND_LOOP;
					//PlaySound(g_AlarmAudioCfg[pAlarm->nAlarmSource].szFileName, NULL, flg);
					PreviewPro->OpenAlarmSound();
				}
#endif
				//if (g_pAlarmMsgDlg != NULL)
				//{
					//g_pAlarmMsgDlg->ShowWindow(SW_SHOW);
					TabAlarmVideo_t tabVideo;
					TabAlarmVideo_t* pTabVideo = NULL;
					if (tabAlarmConf.Video > 0)
					{
						if (db->GetAlarmVideo(&tabVideo, tabAlarmConf.Video) == 1)
							pTabVideo = &tabVideo;
					}
					//没有配置视频也要显示告警消息
					log->AddMsg(pAlarm->nDevId, &tabAlarmConf, pTabVideo); //TODO:优化，不直接操作界面，改为postmsg
					log->show();
					if (!g_bHideAlarm)
					{
					
					}
					else
					{
						
					}
				//}
				if (db->AddAlarmLog(&tabLog) <= 0)
					continue;
			}
			if (bGetAlarmConf)
				break;
		}
	}
	
}

bool Client::event(QEvent* e)
{
	CompareEvent *event = static_cast<CompareEvent *>(e);

	if (e->type() == static_cast <QEvent::Type>(CompareEvent::getType(CET_ALARMNOTIFY)))
	{
		OnAlarmNotify();
	}
	return QWidget::event(event);
}

void Client::OnAlarmNotify()
{
	AlarmInfo_t* pAlarm = new AlarmInfo_t;
	if (pAlarm->nDevId == 0 && pAlarm->nAlarmChannel == -1)
	{
		//	DVR_NET_SetupAlarmChan(pAlarm->nAlarmSource);
		return ;
	}

	if (pAlarm == NULL)
	{
		return ;
	}

	g_csAlarmList.lock();
	g_AlarmList.push_back(pAlarm);
	g_csAlarmList.unlock();
	SetEvent(g_hEventAlarm);
	return;
}

void Client::btnLogsearch_clicked()
{
	//LogSearch *log = new LogSearch();
	if (m_TabWidget.m_LOGSEARCH == false)
	{
		log = new LogSearch;
		ui.tabWidget->addTab(log, QObject::tr("日志搜索"));
		
		m_TabWidget.m_LOGSEARCH = true;
	}
	ui.tabWidget->setCurrentWidget(log);
	
	
}
void Client::btnEquiment_clicked()
{
	
	if (m_TabWidget.m_EQMENTMGT == false)
	{

		eqment = new equimentMgt;
		ui.tabWidget->addTab(eqment, QObject::tr("设备管理"));
		
		m_TabWidget.m_EQMENTMGT = true;
		 
	}
	ui.tabWidget->setCurrentWidget(eqment);

}

void Client::btnFace_clicked()
{
	
	if (m_TabWidget.m_COMPARECORD == false)
	{
		m_dlgExport = new CompareRecord;
		ui.tabWidget->addTab(m_dlgExport, QObject::tr("人脸管理"));
		
		m_TabWidget.m_COMPARECORD = true;
		
	}
	ui.tabWidget->setCurrentWidget(m_dlgExport);
	
}

void Client::btnUser_clicked()
{
	
	if (m_TabWidget.m_USSERMGT == false)
	{
		user = new UserMgt;
		ui.tabWidget->addTab(user, QObject::tr("用户管理"));
		
		m_TabWidget.m_USSERMGT = true;
		
	}
	ui.tabWidget->setCurrentWidget(user);
	
}

void Client::btnPlayBack_clicked()
{
	
	if (m_TabWidget.m_VIDEOPLAY == false)
	{
		m_videoPlayBack = new videoPlayback;
		ui.tabWidget->addTab(m_videoPlayBack, QObject::tr("视频回放"));
		
		m_TabWidget.m_VIDEOPLAY = true;
		
	}
	
	ui.tabWidget->setCurrentWidget(m_videoPlayBack);
	
}

void Client::btnPrew_clicked()
{

	
	if (m_TabWidget.m_PREVIEW == false)
	{
		PreviewPro = new PreView;
		ui.tabWidget->addTab(PreviewPro, QObject::tr("预览"));
		
		m_TabWidget.m_PREVIEW = true;
		
	}
	ui.tabWidget->setCurrentWidget(PreviewPro);
	
}

void Client::btnSet_clicked()
{
	systemSet system(this);
	system.setWindowFlags(windowFlags());
	system.exec();
}

void Client::getTabState(int index)
{
	if (ui.tabWidget->tabText(index) == QObject::tr("日志搜索"))
	{
		m_TabWidget.m_LOGSEARCH = false;
		//delete log;
	}
	else if (ui.tabWidget->tabText(index) == QObject::tr("设备管理"))
	{
		m_TabWidget.m_EQMENTMGT = false;
		//delete eqment;
	}
	else if (ui.tabWidget->tabText(index) == QObject::tr("人脸管理"))
	{
		m_TabWidget.m_COMPARECORD = false;
		//delete m_dlgExport;
	}
	else if (ui.tabWidget->tabText(index) == QObject::tr("用户管理"))
	{
		m_TabWidget.m_USSERMGT = false;
		//delete user;
	}
	
	else if (ui.tabWidget->tabText(index) == QObject::tr("视频回放"))
	{
		m_TabWidget.m_VIDEOPLAY = false;
		//delete m_videoPlayBack;
	}
	else if (ui.tabWidget->tabText(index) == QObject::tr("预览"))
	{
		m_TabWidget.m_PREVIEW = false;
		//delete PreviewPro;
	}
	
}
void Client::removeSubTab(int index)
{
	if (index == 0)
		return;
	getTabState(index);
	//ui.tabWidget->removeTab(index);
	QWidget * pWidget = ui.tabWidget->widget(index);
	if (NULL != pWidget)
	{
		delete pWidget;
		pWidget = NULL;
	}
}

/*
void Client::on_btnSkin_clicked()
{

	changeSkin m_chSkin(this);
	m_chSkin.setWindowFlags(windowFlags());
	m_chSkin.exec();
}
*/

void Client::initForm()
{
	
	
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	


	memset(&m_TabWidget, 0, sizeof(TabWidget));
	m_TabWidget.m_COMPARECORD = false;
	
	m_TabWidget.m_EQMENTMGT = false;

	m_TabWidget.m_LOGSEARCH = false;
	
	m_TabWidget.m_PREVIEW = false;
	
	m_TabWidget.m_SYSTEM = false;

	m_TabWidget.m_USSERMGT = false;
	
	m_TabWidget.m_VIDEOPLAY = false;
	
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

	//this->setProperty("canMove", max);
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

	/*ui.widget_DevicePara->setImage(":/res/SoftIcon/image/DevicePara.png");
	connect(ui.widget_DevicePara, SIGNAL(widget_clicked()), this, SLOT(btnSet_clicked()));*/
	
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

