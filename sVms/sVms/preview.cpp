#define  _CRT_SECURE_NO_WARNINGS
#include "PreView.h"
#include <QDebug>
#include <QMessageBox>
#include <QQueue>
#include <QMutex>
#include "CompareEvent.h"

#include <QPushButton>
#include "myhelper.h"
#include <QCoreApplication>
#include <QObject>
#include <QPalette>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBitmap>
#include <QPixmap>
#include "modifydevice.h"
#include "ModifyChannel.h"
#include <stdio.h>
#include "client.h"

int			g_nRealPlayCount = 0;
extern Client* g_pInstance;
QMutex mutex;
QMutex g_mutexTempBox;
QQueue<SMART_FACE_CMP_QUERY_INFO*> g_queueAlarm;
QQueue<SMART_FACE_CMP_QUERY_INFO*> g_queueSnap;

PreView::PreView(QWidget *parent)
	: QWidget(parent)
	, m_nVideoCount(16)
	, m_pVideoMenu(NULL)
	, m_pOneVideo(NULL)
	, m_pTreeData(NULL)
	, m_pActionComparison(NULL)//开启比对按钮
	, m_pActionComparisonStop(NULL)
	, m_pActionAttribute(NULL) //属性
	, m_pActionStopWatch(NULL)
	, m_pActionStopAllWatch(NULL)
	, m_pActonMainsream(NULL)//主码流
	, m_pActionSecStream(NULL)//次码流
	, m_pActionFullScreen(NULL)//全屏
	, m_pActionCapTure(NULL) //抓图
	, m_pActionVoice(NULL)//打开声音
	, m_pActionRecord(NULL)//本地录像
	, m_pActionRestorePrew(NULL)//恢复预览
	, m_pActionBroadCast(NULL)
	, m_pCapSet(NULL)
	, m_pSearchButton(NULL)
	, m_pSearchLayout(NULL)
	, m_nRecNum(0)
	, m_nUnRecNum(0)
	, m_strAlarmInfo(QObject::tr("正常"))
{
	ui.setupUi(this);
	initPTZ();
	initForm();
	initMenu();
	show_video_all();
	initFaceResult();
	initSearchButton();
	m_nNumTmp = 0;
	m_nfousWnd = 0;
	m_pTreeData = NULL;

	m_bFullScreen = false;
	m_bBroadcast = FALSE;
	m_bStopRestore = FALSE;
	isPlay = false;
	m_IsRestoreVideoParam = false;
	ui.scrollArea->setStyleSheet(" border:1px solid black");
	ui.scrollArea_2->setStyleSheet(" border:1px solid black");
	
	
	m_speed = 50;
	ui.nPTZSpeed->setMinimum(0);      // 设置滑动条的最小值
	ui.nPTZSpeed->setMaximum(100);   // 设置滑动条的最大值
	ui.nPTZSpeed->setValue(m_speed);
	connect(ui.nPTZSpeed, SIGNAL(valueChanged(int)), this, SLOT(setLineEditValue(int)));

	m_pActionComparison = new QAction(this);
	m_pActionComparison->setText(QObject::tr("开启比对"));
	m_pActionComparisonStop = new QAction(this);
	m_pActionComparisonStop->setText(QObject::tr("关闭比对"));
	m_pActionAttribute = new QAction(this);
	m_pActionAttribute->setText(QObject::tr("属性"));
	//右键弹出菜单-右键菜单支持
	
	ui.treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnWidgetContextMeun(QPoint)));
	connect(m_pActionComparison, SIGNAL(triggered()), this, SLOT(OnMenuComparison()));
	connect(m_pActionComparisonStop, SIGNAL(triggered()), this, SLOT(OnMenuComparisonStop()));
	connect(m_pActionAttribute, SIGNAL(triggered()), this, SLOT(OnMenuTreeAttribute()));
	m_pActionComparison->setEnabled(true);
	m_pActionComparisonStop->setEnabled(false);
	ui.treeWidget->setHeaderHidden(true);

	m_bShowGroup = FALSE;
}

PreView::~PreView()
{
	m_bExitThread = TRUE;
	if (m_hExitEvent)
	{
		SetEvent(m_hExitEvent);
	}	

	if (m_hSnapEvent)
	{
		CloseHandle(m_hSnapEvent);
		m_hSnapEvent = NULL;
	}
	if (m_hSnapThread)
	{
		CloseHandle(m_hSnapThread);
		m_hSnapThread = NULL;
	}

	if (m_hCompEvent)
	{
		CloseHandle(m_hCompEvent);
		m_hCompEvent = NULL;
	}

	if (m_hCompThread)
	{
		CloseHandle(m_hCompThread);
		m_hCompThread = NULL;
	}

	if (m_hExitEvent)
	{
		CloseHandle(m_hExitEvent);
		m_hExitEvent = NULL;
	}

	UnInitWnd();
}

void PreView::UnInitWnd()
{
	if (m_pVideoMenu)
	{
		delete m_pVideoMenu;
		m_pVideoMenu = NULL;
	}
	if (m_pOneVideo)
	{
		delete m_pOneVideo;
		m_pOneVideo = NULL;
	}
	if (m_pTreeData)
	{
		delete m_pTreeData;
		m_pTreeData = NULL;
	}
	if (m_pActionComparison)
	{
		delete m_pActionComparison;
		m_pActionComparison = NULL;
	}
	if (m_pActionComparisonStop)
	{
		delete m_pActionComparisonStop;
		m_pActionComparisonStop = NULL;
	}
	if (m_pActionAttribute)
	{
		delete m_pActionAttribute;
		m_pActionAttribute = NULL;
	}
	if (m_pActionStopWatch)
	{
		delete m_pActionStopWatch;
		m_pActionStopWatch = NULL;
	}
	if (m_pActionStopAllWatch)
	{
		delete m_pActionStopAllWatch;
		m_pActionStopAllWatch = NULL;
	}
	if (m_pActonMainsream)
	{
		delete m_pActonMainsream;
		m_pActonMainsream = NULL;
	}
	if (m_pActionSecStream)
	{
		delete m_pActionSecStream;
		m_pActionSecStream = NULL;
	}
	if (m_pActionFullScreen)
	{
		delete m_pActionFullScreen;
		m_pActionFullScreen = NULL;
	}
	if (m_pActionCapTure)
	{
		delete m_pActionCapTure;
		m_pActionCapTure = NULL;
	}
	if (m_pActionVoice)
	{
		delete m_pActionVoice;
		m_pActionVoice = NULL;
	}
	if (m_pActionRecord)
	{
		delete m_pActionRecord;
		m_pActionRecord = NULL;
	}
	if (m_pActionRestorePrew)
	{
		delete m_pActionRestorePrew;
		m_pActionRestorePrew = NULL;
	}
	if (m_pActionBroadCast)
	{
		delete m_pActionBroadCast;
		m_pActionBroadCast = NULL;
	}
	if (m_pCapSet)
	{
		delete m_pCapSet;
		m_pCapSet = NULL;
	}
	if (m_pSearchButton)
	{
		delete m_pSearchButton;
		m_pSearchButton = NULL;
	}
	if (m_pSearchLayout)
	{
		delete m_pSearchLayout;
		m_pSearchLayout = NULL;
	}
	if (m_pSearchButton)
	{
		delete m_pSearchButton;
		m_pSearchButton = NULL;
	}
	if (m_pSearchLayout)
	{
		delete m_pSearchLayout;
		m_pSearchLayout = NULL;
	}
}

void PreView::initSearchButton()
{
	m_pSearchButton = new QPushButton(this);

	m_pSearchButton->setCursor(Qt::PointingHandCursor);
	m_pSearchButton->setFixedSize(22, 22);
	m_pSearchButton->setToolTip(QObject::tr("搜索"));
	m_pSearchButton->setStyleSheet("QPushButton{border-image:url(:/res/SoftIcon/icon_search_normal.png); background:transparent;} \
								  QPushButton:hover{border-image:url(:/res/SoftIcon/icon_search_hover.png)} \
								 QPushButton:pressed{border-image:url(:/res/SoftIcon/icon_search_press.png)}");
	QMargins margins = ui.lineEdit_Search->textMargins();
	ui.lineEdit_Search->setTextMargins(margins.left(), margins.top(), m_pSearchButton->width(), margins.bottom());
	ui.lineEdit_Search->setPlaceholderText(QObject::tr("请输入搜索内容"));

	m_pSearchLayout = new QHBoxLayout();
	m_pSearchLayout->addStretch();
	m_pSearchLayout->addWidget(m_pSearchButton);
	m_pSearchLayout->setSpacing(0);
	m_pSearchLayout->setContentsMargins(0, 0, 0, 0);
	ui.lineEdit_Search->setLayout(m_pSearchLayout);
	connect(m_pSearchButton, SIGNAL(clicked(bool)), this, SLOT(on_btnSearch_clicked()));
}

void PreView::initPTZ()
{	
	QPixmap maskUp(":/res/PTZPro/PTZMax_UP.png");
	ui.m_btnPtzUp->setMask(maskUp.mask());
	

	QPixmap maskDown(":/res/PTZPro/PTZMax_Down.png");
	ui.m_btnPtzDown->setMask(maskDown.mask());


	QPixmap maskLeft(":/res/PTZPro/PTZMax_Left.png");
	ui.m_btnPtzLeft->setMask(maskLeft.mask());


	QPixmap maskRight(":/res/PTZPro/PTZMax_Right.png");
	ui.m_btnPtzRight->setMask(maskRight.mask());


	QPixmap maskUpAuto(":/res/PTZPro/PTZMax_Auto.png");
	ui.m_btnPtzAuto->setMask(maskUpAuto.mask());

	QPixmap maskAdd(":/res/PTZPro/AddHui.png");
	QPixmap maskDel(":/res/PTZPro/DelHui.png");
	ui.m_btnPtzFocus_A->setMask(maskAdd.createHeuristicMask());
	ui.m_btnPtzFocus_S->setMask(maskDel.mask());
	ui.m_btnPtzZoom_A->setMask(maskAdd.mask());
	ui.m_btnPtzZoom_S->setMask(maskDel.mask());
	ui.m_btnPtzApe_A->setMask(maskAdd.mask());
	ui.m_btnPtzApe_S->setMask(maskDel.mask());
	
}
void PreView::initTree()
{
	ui.treeWidget->clear();

	m_pTreeDev->ShowTreebyType(ui.treeWidget);
	connect(ui.treeWidget, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(OnlineTreeViewDoubleClick(const QModelIndex)));	
}


bool PreView::eventFilter(QObject *watched, QEvent *event)
{
	OneVideoPro *widget = (OneVideoPro *)watched;
	if (event->type() == QEvent::MouseButtonDblClick) {
		
		if (!videoMax) {
			videoMax = true;
			hide_video_all();
			ui.gridLayout->addWidget(widget, 0, 0);
			widget->setVisible(true);
		}
		else {
			videoMax = false;
			show_video_all();
		}
	}
	
	else if (event->type() == QEvent::Enter)
	{
		widget->m_vmtool->show();		
	}
	else if (event->type() == QEvent::Leave)
	{
		widget->m_vmtool->hide();
	}
	else if (event->type() == QEvent::MouseButtonPress) 
	{
		hWnd = (HWND)qobject_cast<OneVideoPro *>(watched)->winId();
		for (int i = 0; i < m_nVideoCount; i++)
		{
			if ((HWND)m_listwidgets[i].widget->winId() == hWnd)
			{
				if (i == m_nfousWnd)
					break;

				if (m_listwidgets[m_nfousWnd].widget->m_dspWndinfo.bSound)
				{
					m_listwidgets[m_nfousWnd].widget->m_pDev->pDevObj->EnableAudio((HWND)m_listwidgets[i].widget->winId(), FALSE);
				}

				m_listwidgets[m_nNumTmp].widget->setStyleSheet(".OneVideoPro{ border:1px solid black}");

				m_nfousWnd = i;

				m_nNumTmp = m_nfousWnd;
				m_listwidgets[m_nfousWnd].widget->setStyleSheet(".OneVideoPro{ border:1px solid white}");
			}
		}
		if (qApp->mouseButtons() == Qt::RightButton) 
		{
			if (m_listwidgets[m_nfousWnd].isVideoOpen == true)
			{
				m_pActionStopWatch->setEnabled(true);
				m_pActionStopAllWatch->setEnabled(true);
				m_pActionVoice->setEnabled(true);
				m_pActionRecord->setEnabled(true);
				m_pActionCapTure->setEnabled(true);
				m_pActionBroadCast->setEnabled(true);
			}
			else
			{
				m_pActionStopWatch->setEnabled(false);
				m_pActionStopAllWatch->setEnabled(false);
				m_pActionVoice->setEnabled(false);
				m_pActionRecord->setEnabled(false);
				m_pActionCapTure->setEnabled(false);
				m_pActionBroadCast->setEnabled(false);
			}
			m_pVideoMenu->exec(QCursor::pos());
			return true;
		}
	}

	return QWidget::eventFilter(watched, event);
}

void PreView::initForm()
{
	//设置样式表

	videoMax = false;
	m_strVideoType = "1_4";

	for (int i = 0; i < m_nVideoCount; i++) {

		m_videoWnd.widget = new OneVideoPro();
		m_videoWnd.widget->m_nWndNum = i;

		m_videoWnd.widget->setObjectName(QString("video%1").arg(i + 1));
		m_videoWnd.widget->m_vmtool->m_labelNum->setText(QString("#%1").arg(i + 1));
		m_videoWnd.widget->installEventFilter(this);
		m_videoWnd.isVideoOpen = false;
		m_listwidgets.append(m_videoWnd);
	}
	m_listwidgets[0].widget->setStyleSheet(".OneVideoPro{ border:1px solid white}");
	
}

void PreView::initMenu()
{
	m_pVideoMenu = new QMenu(this);
	m_pVideoMenu->setStyleSheet("QMenu::item:!enabled{color:grey;}");
	m_pActionFullScreen = new QAction(this);
	m_pActionFullScreen->setText(QObject::tr("全屏"));
	m_pVideoMenu->addAction(m_pActionFullScreen);
	connect(m_pActionFullScreen, SIGNAL(triggered()), this, SLOT(snapshot_video_one()));

	QMenu *menuStream = m_pVideoMenu->addMenu(QObject::tr("码流"));
	m_pActonMainsream = new QAction(this);
	menuStream->addAction(m_pActonMainsream);
	m_pActonMainsream->setText(QObject::tr("主码流"));

	m_pActionSecStream = new QAction(this);
	menuStream->addAction(m_pActionSecStream);
	m_pActionSecStream->setText(QObject::tr("次码流"));
	m_pActonMainsream->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
	m_pActionSecStream->setIcon(QIcon(QPixmap("")));
	connect(m_pActonMainsream, SIGNAL(triggered()), this, SLOT(MainStream()));
	connect(m_pActionSecStream, SIGNAL(triggered()), this, SLOT(SecStream()));
	m_pVideoMenu->addSeparator();

	m_pActionStopWatch = new QAction(this);
	m_pActionStopWatch->setText(QObject::tr("停止监视"));
	m_pVideoMenu->addAction(m_pActionStopWatch);
	m_pActionStopWatch->setEnabled(false);
	connect(m_pActionStopWatch, SIGNAL(triggered()), this, SLOT(StopWatch()));

	m_pActionStopAllWatch = new QAction(this);
	m_pActionStopAllWatch->setText(QObject::tr("停止所有监视"));
	m_pActionStopAllWatch->setEnabled(false);
	m_pVideoMenu->addAction(m_pActionStopAllWatch);
	connect(m_pActionStopAllWatch, SIGNAL(triggered()), this, SLOT(StopAllWatch()));

	m_pActionRestorePrew = new QAction(this);
	m_pActionRestorePrew->setText(QObject::tr("恢复预览"));
	m_pVideoMenu->addAction(m_pActionRestorePrew);
	connect(m_pActionRestorePrew, SIGNAL(triggered()), this, SLOT(storePrew()));

	m_pActionCapTure = new QAction(this);
	m_pActionCapTure->setText(QObject::tr("抓图"));
	m_pVideoMenu->setStyleSheet("QMenu::item:disabled{color:grey;}");
	m_pActionCapTure->setEnabled(false);
	m_pVideoMenu->addAction(m_pActionCapTure);
	connect(m_pActionCapTure, SIGNAL(triggered()), this, SLOT(CapTure()));

	m_pActionVoice = new QAction(this);
	m_pActionVoice->setText(QObject::tr("打开声音"));
	m_pVideoMenu->addAction(m_pActionVoice);
	m_pActionVoice->setEnabled(false);
	connect(m_pActionVoice, SIGNAL(triggered()), this, SLOT(OpenSound()));

	m_pActionRecord = new QAction(this);
	m_pActionRecord->setText(QObject::tr("开始本地录像"));
	m_pVideoMenu->addAction(m_pActionRecord);
	m_pActionRecord->setEnabled(false);
	connect(m_pActionRecord, SIGNAL(triggered()), this, SLOT(LocalRecord()));

	m_pActionBroadCast = new QAction(this);
	m_pActionBroadCast->setText(QObject::tr("广播"));
	m_pActionBroadCast->setEnabled(false);
	m_pVideoMenu->addAction(m_pActionBroadCast);
	connect(m_pActionBroadCast, SIGNAL(triggered()), this, SLOT(BroadcastSlot()));


	m_pVideoMenu->addSeparator();
	QMenu *menu4 = m_pVideoMenu->addMenu(QObject::tr("切换到4画面"));
	menu4->addAction(QObject::tr("通道1-通道4"), this, SLOT(show_video_4()));
	menu4->addAction(QObject::tr("通道5-通道8"), this, SLOT(show_video_4()));
	menu4->addAction(QObject::tr("通道9-通道12"), this, SLOT(show_video_4()));
	menu4->addAction(QObject::tr("通道13-通道16"), this, SLOT(show_video_4()));

	QMenu *menu6 = m_pVideoMenu->addMenu(QObject::tr("切换到6画面"));
	menu6->addAction(QObject::tr("通道1-通道6"), this, SLOT(show_video_6()));
	menu6->addAction(QObject::tr("通道6-通道11"), this, SLOT(show_video_6()));
	menu6->addAction(QObject::tr("通道11-通道16"), this, SLOT(show_video_6()));

	QMenu *menu8 = m_pVideoMenu->addMenu(QObject::tr("切换到8画面"));
	menu8->addAction(QObject::tr("通道1-通道8"), this, SLOT(show_video_8()));
	menu8->addAction(QObject::tr("通道9-通道16"), this, SLOT(show_video_8()));

	QMenu *menu9 = m_pVideoMenu->addMenu(QObject::tr("切换到9画面"));
	menu9->addAction(QObject::tr("通道1-通道9"), this, SLOT(show_video_9()));
	menu9->addAction(QObject::tr("通道8-通道16"), this, SLOT(show_video_9()));

	m_pVideoMenu->addAction(QObject::tr("切换到16画面"), this, SLOT(show_video_16()));	
}

void PreView::initFaceResult()
{
	m_pCapSet = new capacitySet();
	m_hSnapEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hCompEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hExitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hSnapThread = NULL;
	m_hCompThread = NULL;
	m_bExitThread = FALSE;

	DWORD dwThreadID = 0;
	m_hSnapThread = CreateThread(NULL, 0, ShowPicThread, this, CREATE_SUSPENDED, &dwThreadID);
	if (m_hSnapThread)
	{
		ResumeThread(m_hSnapThread);
	}

	m_hCompThread = CreateThread(NULL, 0, ShowResultThread, this, CREATE_SUSPENDED, &dwThreadID);
	if (m_hCompThread)
	{
		ResumeThread(m_hCompThread);
	}

	m_strSoundPath = QString("%1\\jing.wav").arg(QCoreApplication::applicationDirPath());
}

void PreView::initTvmode()
{
	
	QString file;
	file = QString("%1\\TvMode.ini").arg(QCoreApplication::applicationDirPath());
	int VideoSet = -1;
	VideoSet = ::GetPrivateProfileInt("VideoSet", "VideoSet", 0, file.toLatin1().data());
	if (VideoSet == 2)
	{
		m_bStopRestore = FALSE;
		m_hRestoreThread = ::CreateThread(NULL, 0, RestoreRealtimeThread, this, 0, NULL);		
	}
	else
	{
		//m_pVideoArea->Displaymode(MODE_4X4, false);
	}
}
DWORD WINAPI PreView::RestoreRealtimeThread(LPVOID lpParam)
{
	PreView* pDlg = (PreView*)lpParam;
	if (NULL == pDlg)
	{
		return -1;
	}
	pDlg->OnRestoreRealtime();
	return 0;
}


long PreView::OnRestoreRealtime()
{

	QString file;
	file = QString("%1/rtvideo.dat").arg(QCoreApplication::applicationDirPath());
	FILE *fp = NULL;
	if ((fp = fopen(file.toLatin1().data(), "rb")) == NULL)
	{
		return -1;
	}
	m_IsRestoreVideoParam = true;
	long Dspmode;
	fread(&Dspmode, sizeof(long), 1, fp);

	BOOL bVS = FALSE;
	for (int ix = 0; ix < Dspmode; ix++)
	{
		fread(&bVS, sizeof(BOOL), 1, fp);
		m_listwidgets[ix].widget->m_dspWndinfo.bVS = bVS;
		if (bVS)
		{
			m_listwidgets[ix].widget->m_dspWndinfo.bVS = !bVS;
		}
	}

	TreeData_t* pVideoPlayParam = new TreeData_t;
	memset(pVideoPlayParam, 0, sizeof(TreeData_t));
	long lIndex = 0;
	U32 SlaveDevId = 0;
	U32 Channel = 0;
	BOOL bMainStream = FALSE;
	int i = 0;
	while (i < 16)
	{
		if (fread(&lIndex, sizeof(long), 1, fp) == 0)
			break;
		fread(&Channel, sizeof(U32), 1, fp);
		fread(&SlaveDevId, sizeof(U32), 1, fp);
		fread(&bMainStream, sizeof(BOOL), 1, fp);
		if (SlaveDevId > 0)
		{
			
			
			pVideoPlayParam->Channel = Channel;
			pVideoPlayParam->pDevObj = m_pTreeDev->GetBaseDeviceInfo(SlaveDevId);
			if (NULL == pVideoPlayParam->pDevObj) //by zjh 20170927
			{
				continue;
			}
			m_mapPlayTreeData.insert(std::make_pair(lIndex, pVideoPlayParam));
			m_listwidgets[i].widget->m_dspWndinfo.bMainStream = bMainStream;
			pVideoPlayParam = new TreeData_t;
			memset(pVideoPlayParam, 0, sizeof(TreeData_t));
		}
		else
		{
			m_listwidgets[i].widget->m_dspWndinfo.bMainStream = true;
		}
		++i;
	}
	delete pVideoPlayParam;
	fclose(fp);
	map<long, TreeData_t*>::iterator itVideoParam;
	for (itVideoParam = m_mapPlayTreeData.begin(); itVideoParam != m_mapPlayTreeData.end(); itVideoParam++)
	{

		AddWatch_t(itVideoParam->first, itVideoParam->second);
	}

	m_IsRestoreVideoParam = false;

	return 0;
}
void PreView::ReceiveSnap(char* pBuf)
{
	if (!pBuf)
	{
		return;
	}

	SMART_FACE_CMP_QUERY_INFO* pCMPInfo = (SMART_FACE_CMP_QUERY_INFO*)pBuf;
	SMART_FACE_CMP_QUERY_INFO* pCMPInfoTmep = NULL;

	//所有记录都加进数据库
	if (!g_pDatabase->AddCMPInfo(pCMPInfo))
	{
		CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
		QApplication::postEvent(this, custevent);
	}

	if (pCMPInfo->sLibMode != 0)
	{
		mutex.lock();
		if (g_queueAlarm.count() > 0)
		{
			pCMPInfoTmep = g_queueAlarm.dequeue();
		}
		else
		{
			pCMPInfoTmep = new SMART_FACE_CMP_QUERY_INFO;
			memset(pCMPInfoTmep, 0, sizeof(SMART_FACE_CMP_QUERY_INFO));
		}
		memcpy(pCMPInfoTmep, pCMPInfo, sizeof(SMART_FACE_CMP_QUERY_INFO));
		g_queueAlarm.enqueue(pCMPInfoTmep);
		mutex.unlock();
		SetEvent(m_hCompEvent);
	}
	else
	{
		mutex.lock();
		if (g_queueSnap.count() > 0)
		{
			pCMPInfoTmep = g_queueSnap.dequeue();
		}
		else
		{
			pCMPInfoTmep = new SMART_FACE_CMP_QUERY_INFO;
			memset(pCMPInfoTmep, 0, sizeof(SMART_FACE_CMP_QUERY_INFO));
		}
		memcpy(pCMPInfoTmep, pCMPInfo, sizeof(SMART_FACE_CMP_QUERY_INFO));
		g_queueSnap.enqueue(pCMPInfoTmep);
		mutex.unlock();
		SetEvent(m_hSnapEvent);
	}
}

DWORD WINAPI PreView::ShowPicThread(LPVOID lPvoid)
{
	BOOL bRet = 0;
	PreView* pDlg = (PreView*)lPvoid;
	HANDLE hWaitHanld[2];
	hWaitHanld[0] = pDlg->m_hExitEvent;
	hWaitHanld[1] = pDlg->m_hSnapEvent;
	if (pDlg)
	{
		while (!pDlg->m_bExitThread)
		{
			bRet = WaitForMultipleObjects(2, hWaitHanld, FALSE, 1000);
			if (WAIT_OBJECT_0 == bRet)
			{
				break;
			}
			else if (WAIT_OBJECT_0 + 1 == bRet)
			{
				pDlg->startDisplayImg();
			}
		}
	}
	return TRUE;
}

DWORD WINAPI PreView::ShowResultThread(LPVOID lpVoid)
{
	BOOL bRet = 0;
	PreView* pDlg = (PreView*)lpVoid;

	HANDLE hWaitHanld[2];
	hWaitHanld[0] = pDlg->m_hExitEvent;
	hWaitHanld[1] = pDlg->m_hCompEvent;
	if (pDlg)
	{
		while (!pDlg->m_bExitThread)
		{
			bRet = WaitForMultipleObjects(2, hWaitHanld, FALSE, 1000);
			if (WAIT_OBJECT_0 == bRet)
			{
				break;
			}
			else if (WAIT_OBJECT_0 + 1 == bRet)
			{
				pDlg->startDisplayPerMsg();
			}
		}
	}
	return TRUE;
}

void PreView::startDisplayImg()
{
	CompareEvent *custevent = new CompareEvent(CET_DISPLAYIMG);
	QApplication::postEvent(this, custevent);
}
void PreView::startDisplayPerMsg()
{
	CompareEvent *custevent = new CompareEvent(CET_DISPLAYPERMSG);
	QApplication::postEvent(this, custevent);
}

void PreView::play_video_all()
{

}

void PreView::snapshot_video_one()
{
	if (m_bFullScreen = !m_bFullScreen)
	{
		ui.widget_main->setWindowFlags(Qt::Window);
		ui.widget_main->showFullScreen();
		m_pActionFullScreen->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
		m_bFullScreen = true;
	}
	else
	{
		ui.widget_main->setWindowFlags(Qt::SubWindow);
		ui.widget_main->showNormal();
		m_pActionFullScreen->setIcon(QIcon(QPixmap("")));
		m_bFullScreen = false;
	}
}


void PreView::show_video_all()
{
	if (m_strVideoType == "1_4") {
		change_video_4(0);
	}
	else if (m_strVideoType == "5_8") {
		change_video_4(4);
	}
	else if (m_strVideoType == "9_12") {
		change_video_4(8);
	}
	else if (m_strVideoType == "13_16") {
		change_video_4(12);
	}
	else if (m_strVideoType == "1_6") {
		change_video_6(0);
	}
	else if (m_strVideoType == "6_11") {
		change_video_6(5);
	}
	else if (m_strVideoType == "11_16") {
		change_video_6(10);
	}
	else if (m_strVideoType == "1_8") {
		change_video_8(0);
	}
	else if (m_strVideoType == "9_16") {
		change_video_8(8);
	}
	else if (m_strVideoType == "1_9") {
		change_video_9(0);
	}
	else if (m_strVideoType == "8_16") {
		change_video_9(7);
	}
	else if (m_strVideoType == "1_16") {
		change_video_16(0);
	}
}

void PreView::show_video_4()
{
	videoMax = false;
	QString videoType;
	int index = 0;

	QAction *action = (QAction *)sender();
	QString name = action->text();

	if (name == QObject::tr("通道1-通道4")) {
		index = 0;
		videoType = "1_4";
	}
	else if (name == QObject::tr("通道5-通道8")) {
		index = 4;
		videoType = "5_8";
	}
	else if (name == QObject::tr("通道9-通道12")) {
		index = 8;
		videoType = "9_12";
	}
	else if (name == QObject::tr("通道13-通道16")) {
		index = 12;
		videoType = "13_16";
	}

	if (this->m_strVideoType != videoType) {
		this->m_strVideoType = videoType;
		change_video_4(index);
	}
}

void PreView::show_video_6()
{
	videoMax = false;
	QString videoType;
	int index = 0;

	QAction *action = (QAction *)sender();
	QString name = action->text();

	if (name == QObject::tr("通道1-通道6")) {
		index = 0;
		videoType = "1_6";
	}
	else if (name == QObject::tr("通道6-通道11")) {
		index = 5;
		videoType = "6_11";
	}
	else if (name == QObject::tr("通道11-通道16")) {
		index = 10;
		videoType = "11_16";
	}

	if (this->m_strVideoType != videoType) {
		this->m_strVideoType = videoType;
		change_video_6(index);
	}
}

void PreView::show_video_8()
{
	videoMax = false;
	QString videoType;
	int index = 0;

	QAction *action = (QAction *)sender();
	QString name = action->text();

	if (name == QObject::tr("通道1-通道8")) {
		index = 0;
		videoType = "1_8";
	}
	else if (name == QObject::tr("通道9-通道16")) {
		index = 8;
		videoType = "9_16";
	}

	if (this->m_strVideoType != videoType) {
		this->m_strVideoType = videoType;
		change_video_8(index);
	}
}

void PreView::show_video_9()
{
	videoMax = false;
	QString videoType;
	int index = 0;

	QAction *action = (QAction *)sender();
	QString name = action->text();

	if (name == QObject::tr("通道1-通道9")) {
		index = 0;
		videoType = "1_9";
	}
	else if (name == QObject::tr("通道8-通道16")) {
		index = 7;
		videoType = "8_16";
	}

	if (this->m_strVideoType != videoType) {
		this->m_strVideoType = videoType;
		change_video_9(index);
	}
}

void PreView::show_video_16()
{
	videoMax = false;
	QString videoType;
	int index = 0;
	videoType = "1_16";

	if (this->m_strVideoType != videoType) {
		this->m_strVideoType = videoType;
		change_video_16(index);
	}
}

void PreView::hide_video_all()
{
	for (int i = 0; i < m_nVideoCount; i++) {
		ui.gridLayout->removeWidget(m_listwidgets.at(i).widget);
		m_listwidgets.at(i).widget->setVisible(false);
	}
}

void PreView::change_video(int index, int flag)
{
	int count = 0;
	int row = 0;
	int column = 0;

	for (int i = 0; i < m_nVideoCount; i++) {
		if (i >= index) {
			ui.gridLayout->addWidget(m_listwidgets.at(i).widget, row, column);
			m_listwidgets.at(i).widget->setVisible(true);
		
			
		
			
			count++;
			column++;
			if (column == flag) {
				row++;
				column = 0;
			}
		}

		if (count == (flag * flag)) {
			break;
		}
	}
}

void PreView::change_video_4(int index)
{
	hide_video_all();
	change_video(index, 2);
}

void PreView::change_video_6(int index)
{
	hide_video_all();
	if (index == 0) {
		ui.gridLayout->addWidget(m_listwidgets.at(0).widget, 0, 0, 2, 2);
		ui.gridLayout->addWidget(m_listwidgets.at(1).widget, 0, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(2).widget, 1, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(3).widget, 2, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(4).widget, 2, 1, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(5).widget, 2, 0, 1, 1);

		
		for (int i = 0; i < 6; i++) {
			m_listwidgets.at(i).widget->setVisible(true);

		}
	}
	else if (index == 5) {
		ui.gridLayout->addWidget(m_listwidgets.at(5).widget, 0, 0, 2, 2);
		ui.gridLayout->addWidget(m_listwidgets.at(6).widget, 0, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(7).widget, 1, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(8).widget, 2, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(9).widget, 2, 1, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(10).widget, 2, 0, 1, 1);


		for (int i = 5; i < 11; i++) {
			m_listwidgets.at(i).widget->setVisible(true);

		}
	}
	else if (index == 10) {
		ui.gridLayout->addWidget(m_listwidgets.at(10).widget, 0, 0, 2, 2);
		ui.gridLayout->addWidget(m_listwidgets.at(11).widget, 0, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(12).widget, 1, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(13).widget, 2, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(14).widget, 2, 1, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(15).widget, 2, 0, 1, 1);


		for (int i = 10; i < 16; i++) {
			m_listwidgets.at(i).widget->setVisible(true);

		}
	}
}

void PreView::change_video_8(int index)
{
	hide_video_all();
	if (index == 0) {
		ui.gridLayout->addWidget(m_listwidgets.at(0).widget, 0, 0, 3, 3);
		ui.gridLayout->addWidget(m_listwidgets.at(1).widget, 0, 3, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(2).widget, 1, 3, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(3).widget, 2, 3, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(4).widget, 3, 3, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(5).widget, 3, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(6).widget, 3, 1, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(7).widget, 3, 0, 1, 1);


		for (int i = 0; i < 8; i++) {
			m_listwidgets.at(i).widget->setVisible(true);

		}
	}
	else if (index == 8) {
		ui.gridLayout->addWidget(m_listwidgets.at(8).widget, 0, 0, 3, 3);
		ui.gridLayout->addWidget(m_listwidgets.at(9).widget, 0, 3, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(10).widget, 1, 3, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(11).widget, 2, 3, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(12).widget, 3, 3, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(13).widget, 3, 2, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(14).widget, 3, 1, 1, 1);
		ui.gridLayout->addWidget(m_listwidgets.at(15).widget, 3, 0, 1, 1);


		for (int i = 8; i < 16; i++) {
			m_listwidgets.at(i).widget->setVisible(true);

		}
	}
}

void PreView::change_video_9(int index)
{
	hide_video_all();
	change_video(index, 3);
}

void PreView::change_video_16(int index)
{
	hide_video_all();
	change_video(index, 4);
}

void PreView::OnlineTreeViewDoubleClick(const QModelIndex & index)
{
	QString str;
	str += QString("%1").arg(index.data().toString());
	QString par = QObject::tr("%1").arg(index.parent().data().toString());

	QVariant var = ui.treeWidget->currentItem()->data(0, Qt::UserRole);
	m_pTreeData = (TreeData_t *)var.value<void *>();

	if (m_pTreeData && m_pTreeData->Channel != -1)
	{
		StopWatch();
		//OutputDebugString("AddWatch\n");
		AddWatch(m_pTreeData, m_nfousWnd, TRUE);
		m_pTreeDev->SelectTreeData(m_pTreeData);
	}
}

int PreView::AddWatch(TreeData_t* pDev, int nWnd, BOOL bTipBox)
{	
	if (!m_IsRestoreVideoParam)
	{
		m_mapPlayTreeData[nWnd] = pDev;
	}
	int ret = m_listwidgets[nWnd].widget->AddWatch(pDev, 0, bTipBox, nWnd);
	
	if (ret >= 0)
	{
		m_listwidgets[nWnd].isVideoOpen = true;
		SaveVideoParam();
	}	
	
	return 0;
}

int PreView::AddWatch_t(int nWnd, TreeData_t* pDev)
{
	
	if (!m_IsRestoreVideoParam)
	{
		m_mapPlayTreeData[nWnd] = pDev;
	}
	if (pDev == NULL)
	{
		return -1;
	}
	int ret = m_listwidgets[nWnd].widget->AddWatch(pDev, 0, FALSE, nWnd);
	if (ret >= 0)
	{
	
		m_listwidgets[nWnd].isVideoOpen = true;
	
		SaveVideoParam();
	}
	return ret;
}
void PreView::SaveVideoParam()
{
	QString file;
	file = QString("%1/rtvideo.dat").arg(QCoreApplication::applicationDirPath());
	FILE *fp = NULL;
	if ((fp = fopen(file.toLocal8Bit().data(), "wb")) == NULL)
	{
		return;
	}

	long dspmode = 16;
	fwrite(&dspmode, sizeof(long), 1, fp);

	for (int ix = 0; ix < 16; ix++)
	{
		fwrite(&m_listwidgets[ix].widget->m_dspWndinfo.bVS, sizeof(BOOL), 1, fp);
	}

	map<long, TreeData_t*>::iterator itPlayParam;
	for (itPlayParam = m_mapPlayTreeData.begin(); itPlayParam != m_mapPlayTreeData.end(); itPlayParam++)
	{
		if (itPlayParam->second != NULL)
		{
			fwrite(&(itPlayParam->first), sizeof(long), 1, fp);
			fwrite(&(itPlayParam->second->Channel), sizeof(U32), 1, fp);
			fwrite(&(itPlayParam->second->pDevObj->GetChannelInfo(itPlayParam->second->Channel)->SlaveDevId), sizeof(U32), 1, fp);
			fwrite(&((m_listwidgets[itPlayParam->first].widget)->m_dspWndinfo.bMainStream), sizeof(BOOL), 1, fp);
		}
	}

	fclose(fp);
}

int PreView::OnWidgetContextMeun(const QPoint& pt)
{
	QTreeWidgetItem *selected = ui.treeWidget->itemAt(pt);
	m_pActionComparison->setEnabled(false);
	m_pActionComparisonStop->setEnabled(false);
	m_pActionAttribute->setEnabled(false);
	if (selected != NULL)
	{
		QString strText = ui.treeWidget->currentItem()->text(0);
		QVariant var1 = ui.treeWidget->currentItem()->data(0, Qt::UserRole);
		m_pTreeData = (TreeData_t *)var1.value<void *>();

		if (m_pTreeData != NULL && m_pTreeData->Channel != -1)
		{
			m_pActionAttribute->setEnabled(true);
			QString str = m_pTreeData->pDevObj->m_pDevInfo->szIpAddr + strText;
			m_pActionComparison->setEnabled(true);
			m_pActionComparisonStop->setEnabled(false);

			if (m_pTreeData->pDevObj->m_lSnapID[m_pTreeData->Channel - 1] > 0)
			{
				m_pActionComparison->setEnabled(false);
				m_pActionComparisonStop->setEnabled(true);
			}
			else
			{
				m_pActionComparison->setEnabled(true);
				m_pActionComparisonStop->setEnabled(false);
			}

			//int nTreeSize = m_treeIp.size();
			//for (int i = 0; i < nTreeSize; i++)
			//{
			//	if (m_treeIp[i].compare(str) == 0)
			//	{
			//		actionComparison->setEnabled(false);
			//		actionComparisonStop->setEnabled(true);
			//	}
			//	else
			//	{
			//		actionComparison->setEnabled(true);
			//		actionComparisonStop->setEnabled(false);
			//	}
			//}
		}
	}
	
	QMenu menu;
	menu.setStyleSheet("QMenu::item:!enabled{color:grey;}");
	menu.addSeparator();

	if (selected){
		menu.addAction(m_pActionComparison);
		menu.addAction(m_pActionComparisonStop);
		menu.addAction(m_pActionAttribute);
		menu.addSeparator();
	
	}
	//显示菜单
	menu.exec(ui.treeWidget->mapToGlobal(pt));
	return 0;
}

void PreView::OnMenuComparison()
{	
	bool bRet = TRUE;
	StartCompare(TRUE);
}

void PreView::OnTreeReFresh()
{
	m_mapPlayTreeData.clear();
	ui.treeWidget->clear();
	for (int i = 0; i < m_nVideoCount; i ++)
	{
		m_listwidgets[i].widget->m_pDev = NULL;
	}
	m_pTreeDev->RefreshDevTree(ui.treeWidget, m_bShowGroup);
}

void PreView::OnMenuComparisonStop()
{	
	bool bRet = TRUE;
	StartCompare(FALSE);
}

void PreView::OnMenuTreeAttribute()
{
	if (ui.treeWidget->currentItem()->text(0) == QObject::tr("IPC设备")
		|| ui.treeWidget->currentItem()->text(0) == QObject::tr("NVR设备")
		|| ui.treeWidget->currentItem()->text(0) == QObject::tr("解码设备"))
			return;
	if (ui.treeWidget->currentItem()->parent()->text(0)== QObject::tr("IPC设备")
		|| ui.treeWidget->currentItem()->parent()->text(0) == QObject::tr("NVR设备")
		|| ui.treeWidget->currentItem()->parent()->text(0) == QObject::tr("解码设备"))
	{
		QString strIP = ui.treeWidget->currentItem()->text(0);
		g_pInstance->ModifyDev(strIP.toLatin1().data());
	}
	else if (ui.treeWidget->currentItem()->text(0).left(2) == "ch")
	{
		ModifyChannel *ch = new ModifyChannel();
		if (m_pTreeData != NULL)
		{
			int ret = g_pDatabase->QueryAllChannelMsg(deviceCh, m_pTreeData->pDevObj->GetDevInfo()->nDevId, m_pTreeData->Channel);
			ch->displayChannelNum->setText(QString::number(deviceCh[0]->szChannel));
			ch->displayChannelName->setText(deviceCh[0]->szChannelName);
			ch->show();
		}
	}
}
int PreView::getIndex(int mode)
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

void PreView::StartCompare(BOOL bStart)
{
	BOOL bRet = FALSE;
	TreeData_t *pChannel = NULL;

	QString str = ui.treeWidget->currentItem()->text(0);
	QVariant var = ui.treeWidget->currentItem()->data(0, Qt::UserRole);
	pChannel = (TreeData_t *)var.value<void *>();
	if (pChannel == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请在设备列表中选择设备!"));
		return;
	}
	QString ip = pChannel->pDevObj->m_pDevInfo->szIpAddr;

	//QString IPStr = ip + str;
	//vector<QString>::iterator it;
	//if (bStart)
	//{
	//	m_treeIp.push_back(IPStr);
	//	sort(m_treeIp.begin(), m_treeIp.end());
	//	
	//	m_treeIp.erase(unique(m_treeIp.begin(), m_treeIp.end()), m_treeIp.end());
	//	
	//}
	//else
	//{
	//	for (it = m_treeIp.begin(); it != m_treeIp.end();)
	//	{
	//		if (*it == IPStr)
	//		{
	//			m_treeIp.erase(it);
	//		}
	//	}
	//}

	
	if (pChannel->pDevObj->m_lUserLoginID <= 0)
	{
		//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("连接设备失败"));
		myHelper::ShowMessageBoxWarning(QObject::tr("连接设备失败!"));
		return;
	}

	CJLNDevice* pDevInfo = (CJLNDevice*)pChannel->pDevObj;

	EnterCriticalSection(&pDevInfo->m_lockSubOperation);
	if (bStart)
	{
		bRet = pDevInfo->StartSnapLink(pChannel->pDevObj->m_lUserLoginID, pChannel->Channel - 1);
	}
	else
	{
		bRet = pDevInfo->StopSnapLink(pChannel->Channel - 1);
	}
	LeaveCriticalSection(&pDevInfo->m_lockSubOperation);
	
}


bool PreView::event(QEvent *e)
{
	CompareEvent *pEvent = static_cast<CompareEvent *>(e);

	if (e->type() == static_cast <QEvent::Type>(CET_DISPLAYIMG))
	{
		DisplayImage();
	}
	else if (e->type() == static_cast <QEvent::Type>(CET_DISPLAYPERMSG))
	{
		DisPlayAlarmMessage();
	}
	else if (e->type() == static_cast <QEvent::Type>(CET_MESSAGEBOX))
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("比对记录数据插入到数据库失败"));
	}
	else if (e->type() == static_cast<QEvent::Type>(CET_STOP_WATCH))
	{
		m_nfousWnd = pEvent->getId();
		StopWatch(); 
	}
	else if (e->type() == static_cast<QEvent::Type>(CET_START_WATCH))
	{
		m_nfousWnd = pEvent->getId();
		if (!m_listwidgets[m_nfousWnd].widget->m_dspWndinfo.bVideo && m_listwidgets[m_nfousWnd].widget->m_pDev)
		{
			AddWatch(m_listwidgets[m_nfousWnd].widget->m_pDev, m_nfousWnd, TRUE);
		}
		//m_pTreeDev->SelectTreeData(m_pTreeData);
	}
	QWidget::event(pEvent);

	return true;
}

void PreView::DisplayImage()
{
	if (g_queueSnap.count() > 0)
	{
		SMART_FACE_CMP_QUERY_INFO *pCompareInfoTmp = g_queueSnap.head();
		if (NULL == pCompareInfoTmp)
		{
			return;
		}

		BOOL bInVailid = FALSE;
		if (pCompareInfoTmp->fTemperature > pCompareInfoTmp->fTemperatureSet)
		{
			m_strSnapInfo = QObject::tr("异常");
			bInVailid = TRUE;
		}
		else
		{
			m_strSnapInfo = QObject::tr("正常");
		}
		m_strSnapTemp = QString::number(pCompareInfoTmp->fTemperature, 'f', 2);
		m_strSnapStatus  = QString("体温: %1  %2").arg(m_strSnapTemp).arg(m_strSnapInfo);

		unRecognition *pUnRecWidget = GetDisplayunRec();
		if (pUnRecWidget)
		{
			pUnRecWidget->ShowInfo(pCompareInfoTmp, bInVailid, m_strSnapStatus);
		}

		if (bInVailid)
		{
			CTemperatureBox* pTempBox = GetTempBox();
			if (pTempBox)
			{
				pTempBox->m_bShow = TRUE;
				pTempBox->ShowInfo(pCompareInfoTmp, m_strSnapStatus);
				pTempBox->show();
			}
			OpenAlarmSound();
		}
	}
}

void PreView::DisPlayAlarmMessage()
{
	if (g_queueAlarm.count() > 0)
	{
		SMART_FACE_CMP_QUERY_INFO *pCompareInfoTmp = g_queueAlarm.head();
		if (NULL == pCompareInfoTmp)
		{
			return;
		}
		BOOL bInvalid = FALSE;
		Recognition* pRecWidget = NULL;
		pRecWidget = GetDisplayRec();
		if (pRecWidget)
		{
			if (pCompareInfoTmp->fTemperature > pCompareInfoTmp->fTemperatureSet)
			{
				m_strAlarmInfo = QObject::tr("异常");
				bInvalid = TRUE;
			}
			else
			{
				m_strAlarmInfo = QObject::tr("正常");
			}
			m_strAlarmTemp = QString::number(pCompareInfoTmp->fTemperature, 'f', 2);
			m_strAlarmStatus = QString("%1: %2").arg(m_strAlarmTemp).arg(m_strAlarmInfo);

			pRecWidget->ShowInfo(pCompareInfoTmp, bInvalid, m_strAlarmStatus);
		}

		//黑名单打开报警声音
		if (pCompareInfoTmp->sLibMode == 1 || bInvalid)
		{
			OpenAlarmSound();
		}

		if (bInvalid)
		{
			CTemperatureBox* pTempBox = GetTempBox();
			if (pTempBox)
			{
				pTempBox->m_bShow = TRUE;
				pTempBox->ShowInfo(pCompareInfoTmp, m_strAlarmStatus);
				pTempBox->show();
			}
		}
	}
}

unRecognition* PreView::GetDisplayunRec()
{
	unRecognition* pUnRecWidget = NULL;
	m_nUnRecNum = ui.horizontalLayout->count();             // 获取布局中的item的数量
	if (m_nUnRecNum >= m_pCapSet->m_unRecNum)
	{
		pUnRecWidget = (unRecognition*)ui.horizontalLayout->itemAt(0)->widget();
		ui.horizontalLayout->removeWidget(pUnRecWidget);
	}
	else
	{
		pUnRecWidget = new unRecognition;
	}

	ui.horizontalLayout->addWidget(pUnRecWidget);
	ui.horizontalLayout->setDirection(QBoxLayout::RightToLeft);
	return pUnRecWidget;
}

Recognition* PreView::GetDisplayRec()
{
	Recognition* pRecWidget = NULL;
	m_nRecNum = ui.verticalLayout->count();
	if (m_nRecNum > m_pCapSet->m_recNum)
	{
		pRecWidget = (Recognition*)ui.verticalLayout->itemAt(0)->widget();
		ui.verticalLayout->removeWidget(pRecWidget);
	}
	else
	{
		pRecWidget = new Recognition;
	}

	ui.verticalLayout->addWidget(pRecWidget);
	ui.verticalLayout->setDirection(QBoxLayout::BottomToTop);
	return pRecWidget;
}

CTemperatureBox* PreView::GetTempBox()
{
	CTemperatureBox* pTempBox = NULL;
	BOOL bFind = FALSE;

	//g_mutexTempBox.lock();
	int nSize = m_listTemperatureBox.size();
	for (int i = 0; i < nSize; i ++)
	{
		pTempBox = m_listTemperatureBox.at(i);
		if (!pTempBox->m_bShow)
		{
			bFind = TRUE;
			break;
		}
	}

	if (!bFind)
	{
		pTempBox = new CTemperatureBox;
		m_listTemperatureBox.push_back(pTempBox);
	}
	//g_mutexTempBox.unlock();

	return pTempBox;
}

//清空告警窗口
void PreView::on_btnClearRec_clicked()
{
	QLayoutItem  *child;
	while ((child = ui.verticalLayout->takeAt(0)) != 0)
	{
		if (child->widget())
		{
			child->widget()->setParent(NULL);
		}
		delete child;
	}

}

//清空抓拍窗口
void PreView::on_btnClearUnrec_clicked()
{

	QLayoutItem  *child;
	while ((child = ui.horizontalLayout->takeAt(0)) != 0)
	{
		if (child->widget())
		{
			child->widget()->setParent(NULL);
		}
		delete child;
	}


}

void PreView::on_btnSet_clicked()
{


	m_pCapSet->show();
}

void PreView::StopWatch()
{	
	m_listwidgets[m_nfousWnd].widget->StopWatch();
	m_listwidgets[m_nfousWnd].widget->IPLabel->setText("");
	
	SaveVideoParam();
	m_listwidgets[m_nfousWnd].isVideoOpen = false;
}

void PreView::StopAllWatch()
{
	for (int ix = 0; ix < (int)m_nVideoCount; ix++)
	{
		if (m_mapPlayTreeData[ix] != NULL)
			m_mapPlayTreeData[ix] = NULL;
	}
	for (int i = 0; i < m_nVideoCount; i++)
	{
		if (m_listwidgets[i].widget->m_dspWndinfo.bVideo)
		{
			m_listwidgets[i].widget->StopWatch();
			
		}
		
	}
	m_listwidgets[m_nfousWnd].isVideoOpen = false;
}

void PreView::storePrew()
{

	OnRestoreRealtime();
}

void PreView::MainStream()
{
	if (!m_listwidgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	m_listwidgets[m_nfousWnd].widget->OnMenuStreamMain();
	m_pActonMainsream->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
	m_pActionSecStream->setIcon(QIcon(QPixmap("")));

}
void PreView::SecStream()
{
	if (!m_listwidgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	m_listwidgets[m_nfousWnd].widget->OnMenuStreamSub();
	m_pActionSecStream->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
	m_pActonMainsream->setIcon(QIcon(QPixmap("")));
}

//抓图
void PreView::CapTure()
{
	if (!m_listwidgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	m_listwidgets[m_nfousWnd].widget->CapturePic();
}

//打开声音
void PreView::OpenSound()
{
	if (!m_listwidgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	if (m_listwidgets[m_nfousWnd].widget->OpenSound() == 0)
	{
		m_pActionVoice->setText(QObject::tr("打开声音"));
	}
	else
	{
		m_pActionVoice->setText(QObject::tr("关闭声音"));
	}
}

//本地录像
void PreView::LocalRecord()
{
	if (!m_listwidgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	if (m_listwidgets[m_nfousWnd].widget->LocalRecord() == 0)
	{
		m_pActionRecord->setText(QObject::tr("开始本地录像"));
	}
	else
	{
		m_pActionRecord->setText(QObject::tr("停止本地录像"));
	}
}

//广播
void PreView::BroadcastSlot()
{
	if (!m_listwidgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	if (m_listwidgets[m_nfousWnd].widget->m_bTalk)
	{
		//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("请先停止对讲"));
	
		myHelper::ShowMessageBoxWarning(QObject::tr("请先停止对讲!"));

		return;
	}
	Broadcast(!m_bBroadcast);
	m_bBroadcast = !m_bBroadcast;
}

int PreView::Broadcast(BOOL bStart)
{
	if (!m_listwidgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return 0;
	}
	for (int i = 0; i < m_nVideoCount; i++)
	{

		if (m_listwidgets[i].widget->m_dspWndinfo.bVideo)
		{
			m_listwidgets[i].widget->BroadCast(bStart);
		}
	}
	return 0;
}

void PreView::on_btnSearch_clicked()
{
	ui.treeWidget->collapseAll();
	QString txt = ui.lineEdit_Search->text();
	bool isEmptyTxt = txt.isEmpty();
	bool isEmptyTree = ui.treeWidget->topLevelItemCount(); //非零个为true
	if (isEmptyTxt) {
		QTreeWidgetItemIterator it(ui.treeWidget);
		while (*it) {
			(*it)->setBackground(0, m_pTreeDev->m_itemBrush);
			it++;
		}
		return;
	}
	if (!isEmptyTree) { return; }


#if 0
	int count = ui->treeWidget->topLevelItemCount();
	for (int i = 0; i < count; ++i) {
		QTreeWidgetItem *cItem = ui->treeWidget->topLevelItem(i);
		if (-1 != cItem->text(0).indexOf(txt)) {
			cItem->setBackground(0, Qt::green);
		}
		else {
			cItem->setBackground(0, m_itemBrush);
		}
		searchChild(cItem, txt);
	}
#else

	QTreeWidgetItemIterator it(ui.treeWidget);
	while (*it) {
		QString str = (*it)->text(0);
		if (-1 != str.indexOf(txt)) {
			QTreeWidgetItem *pItem = (*it)->parent();
			if (pItem != NULL) {
				bool isExpanded = pItem->isExpanded();
				if (!isExpanded){
					ui.treeWidget->expandItem(pItem);
				}
			}
			(*it)->setBackground(0, Qt::green);
			m_pTreeDev->parentExpand(*it);
		}
		else{
			(*it)->setBackground(0, m_pTreeDev->m_itemBrush);
		}
		it++;
	}
#endif

	
}


void PreView::setLineEditValue(int speed)
{
	m_speed = speed;
}

//向上
void PreView::on_m_btnPtzUp_pressed()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_listwidgets[m_nfousWnd].widget->label->winId(), (PTZ_COMMAND_TYPE)eTILT_UP, 0, m_speed);
	
}

void PreView::on_m_btnPtzUp_released()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_listwidgets[m_nfousWnd].widget->label->winId(), (PTZ_COMMAND_TYPE)eTILT_UP, 1, 1);
}
//向下
void PreView::on_m_btnPtzDown_pressed()
{
	if (m_pTreeData == NULL)
		return;

	m_pTreeData->pDevObj->PtzCtrl((HWND)m_listwidgets[m_nfousWnd].widget->label->winId(), (PTZ_COMMAND_TYPE)eTILT_DOWN, 0, m_speed);
}
void PreView::on_m_btnPtzDown_released()
{
	if (m_pTreeData == NULL)
		return;

	m_pTreeData->pDevObj->PtzCtrl((HWND)m_listwidgets[m_nfousWnd].widget->label->winId(), (PTZ_COMMAND_TYPE)eTILT_DOWN, 1, 1);
}
//向左
void PreView::on_m_btnPtzLeft_pressed()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_listwidgets[m_nfousWnd].widget->label->winId(), (PTZ_COMMAND_TYPE)ePAN_LEFT, 0, m_speed);
}
void PreView::on_m_btnPtzLeft_released()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_listwidgets[m_nfousWnd].widget->label->winId(), (PTZ_COMMAND_TYPE)ePAN_LEFT, 1, 1);
}
//向右
void PreView::on_m_btnPtzRight_pressed()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_listwidgets[m_nfousWnd].widget->label->winId(), (PTZ_COMMAND_TYPE)ePAN_RIGHT, 0, m_speed);
}
void PreView::on_m_btnPtzRight_released()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_listwidgets[m_nfousWnd].widget->label->winId(), (PTZ_COMMAND_TYPE)ePAN_RIGHT, 1, 1);
}
//自动
void PreView::on_m_btnPtzAuto_pressed()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, ePAN_AUTO, 0, m_speed);
}
void PreView::on_m_btnPtzAuto_released()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, ePAN_AUTO, 1, 1);
}
//变倍+
void PreView::on_m_btnPtzFocus_A_pressed()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eZOOM_OUT, 0, m_speed);
}
void PreView::on_m_btnPtzFocus_A_released()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eZOOM_OUT, 1, 1);
}

//变倍-
void PreView::on_m_btnPtzFocus_S_pressed()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eZOOM_IN, 0, m_speed);
}
void PreView::on_m_btnPtzFocus_S_released()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eZOOM_IN, 1, 1);
}
//聚焦+
void PreView::on_m_btnPtzZoom_A_pressed()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eFOCUS_FAR, 0, m_speed);
}
void PreView::on_m_btnPtzZoom_A_released()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eFOCUS_FAR, 1, 1);
}
//聚焦-
void PreView::on_m_btnPtzZoom_S_pressed()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eFOCUS_NEAR, 0, m_speed);
}
void PreView::on_m_btnPtzZoom_S_released()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eFOCUS_NEAR, 1, 1);
}
//光圈+
void PreView::on_m_btnPtzApe_A_pressed()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eIRIS_CLOSE, 0, m_speed);
}
void PreView::on_m_btnPtzApe_A_released()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eIRIS_CLOSE, 1, 1);
}
//光圈-
void PreView::on_m_btnPtzApe_S_pressed()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eIRIS_OPEN, 0, m_speed);
}
void PreView::on_m_btnPtzApe_S_released()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eIRIS_OPEN, 1, 1);
}

//灯光
void PreView::on_PtzLight_clicked()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eLIGHT_PWRON, 0, m_speed);
}
//预置
void PreView::on_PtzPreset_clicked()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eSET_PRESET, 0, m_speed);
}
//雨刷
void PreView::on_PtzRain_clicked()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eWIPER_PWRON, 0, m_speed);
}
//调用
void PreView::on_PtzRecall_clicked()
{
	if (m_pTreeData == NULL)
		return;
	m_pTreeData->pDevObj->PtzCtrl((HWND)m_pTreeData->Channel, eGOTO_PRESET, 0, m_speed);
}

void PreView::OpenAlarmSound()
{
	QSound *sound = new QSound(m_strSoundPath, this); //构建对象

	sound->play();//播放
}

void PreView::showEvent(QShowEvent *e)
{
	update();
	this->setAttribute(Qt::WA_Mapped);
	QWidget::showEvent(e);
}
void PreView::on_btnExtendLeft_clicked()
{
	static bool v_flag = false;
	if (!v_flag)
	{
		ui.widget_Manage->setVisible(false);
		v_flag = true;
		ui.btnExtendLeft->setIcon(QPixmap(":/res/SoftIcon/you.png"));
	}
	else
	{
		ui.widget_Manage->setVisible(true);

		v_flag = false;

		ui.btnExtendLeft->setIcon(QPixmap(":/res/SoftIcon/zou.png"));
	}
}

void PreView::on_btnExtendDown_clicked()
{
	static bool v_flag = false;
	if (!v_flag)
	{
		ui.widget_Ptz->setVisible(false);
		v_flag = true;
		ui.btnExtendDown->setIcon(QPixmap(":/res/SoftIcon/shang.png"));
	}
	else
	{
		ui.widget_Ptz->setVisible(true);

		v_flag = false;
		ui.btnExtendDown->setIcon(QPixmap(":/res/SoftIcon/xia.png"));
	}
}