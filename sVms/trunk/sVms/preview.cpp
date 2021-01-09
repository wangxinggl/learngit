#include "PreView.h"
#include <QDebug>
#include <QMessageBox>
#include <QQueue>
#include <QMutex>
#include "CompareEvent.h"
#include "db.h"
#include <QPushButton>
#include "myhelper.h"
#include <QCoreApplication>
#include <QObject>
#include <QPalette>
#include <QVBoxLayout>
#include <QHBoxLayout>

int			g_nRealPlayCount = 0;
QMutex mutex;
QQueue<SMART_FACE_CMP_QUERY_INFO> g_CompareInfoArm;
QQueue<SMART_FACE_CMP_QUERY_INFO> g_CompareInfoImg;

PreView::PreView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initForm();
	initMenu();
	treePrew = new DevTreePro();
	initTreeWidget();
	show_video_all();
	initFaceResult();
	initTvmode();
	nNumTmp = 0;
	m_nfousWnd = 0;
	pChannelTmp = NULL;

	bFullScreen = false;
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

	actionRefresh = new QAction(this);
	actionRefresh->setText(QObject::tr("刷新设备树"));
	actionComparison = new QAction(this);
	actionComparison->setText(QObject::tr("开启比对"));
	actionComparisonStop = new QAction(this);
	actionComparisonStop->setText(QObject::tr("关闭比对"));
	//右键弹出菜单-右键菜单支持
	
	ui.treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnWidgetContextMeun(QPoint)));
	connect(actionRefresh, SIGNAL(triggered(bool)), this, SLOT(OnMenuReFresh()));
	connect(actionComparison, SIGNAL(triggered()), this, SLOT(OnMenuComparison()));
	connect(actionComparisonStop, SIGNAL(triggered()), this, SLOT(OnMenuComparisonStop()));
	if (ui.treeWidget)
	{
	}
	actionComparison->setEnabled(true);
	actionComparisonStop->setEnabled(false);
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


}

void PreView::initTreeWidget()
{
	ui.treeWidget->clear();

	

	treePrew->init();
	treePrew->ShowTreebyType1(ui.treeWidget);
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
	
	/*else if (event->type() == QEvent::Enter && widget->m_dspWndinfo.bVideo)
	{
		widget->statusBar()->show();
		//widget->setUpdatesEnabled(false);
		
	}
	else if (event->type() == QEvent::Leave && widget->m_dspWndinfo.bVideo)
	{
		widget->statusBar()->hide();
		//widget->setUpdatesEnabled(true);
		
	}*/
	else if (event->type() == QEvent::MouseButtonPress) {
		if (qApp->mouseButtons() == Qt::RightButton) {
			if (widgets[m_nfousWnd].isVideoOpen == true)
			{
				actionStopWatch->setEnabled(true);
				actionStopAllWatch->setEnabled(true);
				actionVoice->setEnabled(true);
				actionRecord->setEnabled(true);
				actionCapTure->setEnabled(true);
				actionBroadCast->setEnabled(true);

			}
			else
			{
				actionStopWatch->setEnabled(false);
				actionStopAllWatch->setEnabled(false);
				actionVoice->setEnabled(false);
				actionRecord->setEnabled(false);
				actionCapTure->setEnabled(false);
				actionBroadCast->setEnabled(false);
			}
			videoMenu->exec(QCursor::pos());
			return true;
		}
		else
		{
		

			HWND hWnd;
			hWnd = (HWND)qobject_cast<OneVideoPro *>(watched)->winId();
			for (int i = 0; i < videoCount;i++)
			{
			
				if ((HWND)widgets[i].widget->winId() == hWnd)
				{
					if (i == m_nfousWnd)
						return false;
					
					if (widgets[m_nfousWnd].widget->m_dspWndinfo.bSound)
					{
						widgets[m_nfousWnd].widget->m_pDev->DevInfo->EnableAudio((HWND)widgets[i].widget->winId(), FALSE);
					}
				
					widgets[nNumTmp].widget->setStyleSheet(".OneVideoPro{ border:1px solid black}");
					
					m_nfousWnd = i;
				
					nNumTmp = m_nfousWnd;
					widgets[m_nfousWnd].widget->setStyleSheet(".OneVideoPro{ border:1px solid white}");
					
				}
			}

		}
		
	}

	return QWidget::eventFilter(watched, event);
}

void PreView::initForm()
{
	//设置样式表

	videoMax = false;
	videoCount = 16;
	videoType = "1_4";

	for (int i = 0; i < videoCount; i++) {

		m_videoWnd.widget = new OneVideoPro();
	

		m_videoWnd.widget->setObjectName(QString("video%1").arg(i + 1));
		m_videoWnd.widget->ch_Label->setText(QString("#%1").arg(i + 1));
		m_videoWnd.widget->installEventFilter(this);
		m_videoWnd.isVideoOpen = false;
		
		widgets.append(m_videoWnd);
	}
	widgets[0].widget->setStyleSheet(".OneVideoPro{ border:1px solid white}");
	
}

void PreView::initMenu()
{
	videoMenu = new QMenu(this);
	videoMenu->setStyleSheet("QMenu::item:!enabled{color:grey;}");
	actionFullScreen = new QAction(this);
	actionFullScreen->setText(QObject::tr("全屏"));
	videoMenu->addAction(actionFullScreen);
	connect(actionFullScreen, SIGNAL(triggered()), this, SLOT(snapshot_video_one()));

	actionToolbar = new QAction(this);
	actionToolbar->setText(QObject::tr("工具栏"));
	videoMenu->addAction(actionToolbar);
	actionToolbar->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
	connect(actionToolbar, SIGNAL(triggered()), this, SLOT(ShowToolBar()));

	QMenu *menuStream = videoMenu->addMenu(QObject::tr("码流"));
	actonMainsream = new QAction(this);
	menuStream->addAction(actonMainsream);
	actonMainsream->setText(QObject::tr("主码流"));

	actionSecStream = new QAction(this);
	menuStream->addAction(actionSecStream);
	actionSecStream->setText(QObject::tr("次码流"));
	actonMainsream->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
	actionSecStream->setIcon(QIcon(QPixmap("")));
	connect(actonMainsream, SIGNAL(triggered()), this, SLOT(MainStream()));
	connect(actionSecStream, SIGNAL(triggered()), this, SLOT(SecStream()));
	videoMenu->addSeparator();

	actionStopWatch = new QAction(this);
	actionStopWatch->setText(QObject::tr("停止监视"));
	videoMenu->addAction(actionStopWatch);
	actionStopWatch->setEnabled(false);
	connect(actionStopWatch, SIGNAL(triggered()), this, SLOT(StopWatch()));
	actionStopAllWatch = new QAction(this);
	actionStopAllWatch->setText(QObject::tr("停止所有监视"));
	actionStopAllWatch->setEnabled(false);
	videoMenu->addAction(actionStopAllWatch);

	connect(actionStopAllWatch, SIGNAL(triggered()), this, SLOT(StopAllWatch()));

	actionRestorePrew = new QAction(this);
	actionRestorePrew->setText(QObject::tr("恢复预览"));
	videoMenu->addAction(actionRestorePrew);
	connect(actionRestorePrew, SIGNAL(triggered()), this, SLOT(storePrew()));

	actionCapTure = new QAction(this);
	actionCapTure->setText(QObject::tr("抓图"));
	videoMenu->setStyleSheet("QMenu::item:disabled{color:grey;}");
	actionCapTure->setEnabled(false);
	videoMenu->addAction(actionCapTure);
	connect(actionCapTure, SIGNAL(triggered()), this, SLOT(CapTure()));

	actionVoice = new QAction(this);
	actionVoice->setText(QObject::tr("打开声音"));
	videoMenu->addAction(actionVoice);
	actionVoice->setEnabled(false);
	connect(actionVoice, SIGNAL(triggered()), this, SLOT(OpenSound()));

	actionRecord = new QAction(this);
	actionRecord->setText(QObject::tr("开始本地录像"));
	videoMenu->addAction(actionRecord);
	actionRecord->setEnabled(false);
	connect(actionRecord, SIGNAL(triggered()), this, SLOT(LocalRecord()));

	actionBroadCast = new QAction(this);
	actionBroadCast->setText(QObject::tr("广播"));
	actionBroadCast->setEnabled(false);
	videoMenu->addAction(actionBroadCast);
	connect(actionBroadCast, SIGNAL(triggered()), this, SLOT(BroadcastSlot()));


	videoMenu->addSeparator();
	QMenu *menu4 = videoMenu->addMenu(QObject::tr("切换到4画面"));
	menu4->addAction(QObject::tr("通道1-通道4"), this, SLOT(show_video_4()));
	menu4->addAction(QObject::tr("通道5-通道8"), this, SLOT(show_video_4()));
	menu4->addAction(QObject::tr("通道9-通道12"), this, SLOT(show_video_4()));
	menu4->addAction(QObject::tr("通道13-通道16"), this, SLOT(show_video_4()));

	QMenu *menu6 = videoMenu->addMenu(QObject::tr("切换到6画面"));
	menu6->addAction(QObject::tr("通道1-通道6"), this, SLOT(show_video_6()));
	menu6->addAction(QObject::tr("通道6-通道11"), this, SLOT(show_video_6()));
	menu6->addAction(QObject::tr("通道11-通道16"), this, SLOT(show_video_6()));

	QMenu *menu8 = videoMenu->addMenu(QObject::tr("切换到8画面"));
	menu8->addAction(QObject::tr("通道1-通道8"), this, SLOT(show_video_8()));
	menu8->addAction(QObject::tr("通道9-通道16"), this, SLOT(show_video_8()));

	QMenu *menu9 = videoMenu->addMenu(QObject::tr("切换到9画面"));
	menu9->addAction(QObject::tr("通道1-通道9"), this, SLOT(show_video_9()));
	menu9->addAction(QObject::tr("通道8-通道16"), this, SLOT(show_video_9()));

	videoMenu->addAction(QObject::tr("切换到16画面"), this, SLOT(show_video_16()));

	
}

void PreView::initFaceResult()
{
	capSet = new capacitySet();
	set = new systemSet();
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
		//	m_pVideoArea->RestoreVideoParam(); //
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
	file = QString("%1\\rtvideo.dat").arg(QCoreApplication::applicationDirPath());
	FILE *fp = NULL;
	if ((fp = fopen(file.toLatin1().data(), "rb")) == NULL)
	{
		return -1;
	}
	m_IsRestoreVideoParam = true;
	long Dspmode;
	fread(&Dspmode, sizeof(long), 1, fp);

	BOOL bVS = FALSE;

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
			pVideoPlayParam->DevInfo = treePrew->GetBaseDeviceInfo(SlaveDevId);
			if (NULL == pVideoPlayParam->DevInfo) //by zjh 20170927
			{
				continue;
			}
			m_TreeData.insert(std::make_pair(lIndex, pVideoPlayParam));

			pVideoPlayParam = new TreeData_t;
			memset(pVideoPlayParam, 0, sizeof(TreeData_t));
		}
		else
		{
			widgets[i].widget->m_dspWndinfo.bMainStream = true;
		}
		++i;
	}
	delete pVideoPlayParam;
	fclose(fp);
	map<long, TreeData_t*>::iterator itVideoParam;
	for (itVideoParam = m_TreeData.begin(); itVideoParam != m_TreeData.end(); itVideoParam++)
	{

		AddWatch_t(itVideoParam->first, itVideoParam->second);
	}

	m_IsRestoreVideoParam = false;

	return 0;
}
void PreView::ReceiveSnap(char* pBuf)
{
	SMART_FACE_CMP_QUERY_INFO stFaceCompareInfo = { 0 };
	memcpy(&stFaceCompareInfo, pBuf, sizeof(SMART_FACE_CMP_QUERY_INFO));
	mutex.lock();
	g_CompareInfoImg.enqueue(stFaceCompareInfo);
	mutex.unlock();
	SetEvent(m_hSnapEvent);
	if (stFaceCompareInfo.sLibSimilarity > 0.00001f&& stFaceCompareInfo.sLibMode != 0)
	{
		DB *db = new DB;
		if(!db->AddCMPInfo(&stFaceCompareInfo))
		{
			CompareEvent *custevent = new CompareEvent(CompareEvent::getType(CET_MESSAGEBOX));
			QApplication::postEvent(this, custevent);
		}
		mutex.lock();
		g_CompareInfoArm.enqueue(stFaceCompareInfo);
		mutex.unlock();
		SetEvent(m_hCompEvent);
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
	CompareEvent *custevent = new CompareEvent(CompareEvent::getType(CET_DISPLAYIMG));
	QApplication::postEvent(this, custevent);
}
void PreView::startDisplayPerMsg()
{
	CompareEvent *custevent = new CompareEvent(CompareEvent::getType(CET_DISPLAYPERMSG));
	QApplication::postEvent(this, custevent);
}

void PreView::play_video_all()
{

}

void PreView::snapshot_video_one()
{
	if (bFullScreen = !bFullScreen)
	{
		ui.widget_main->setWindowFlags(Qt::Window);
		ui.widget_main->showFullScreen();
		actionFullScreen->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
		bFullScreen = true;
	}
	else
	{
		ui.widget_main->setWindowFlags(Qt::SubWindow);
		ui.widget_main->showNormal();
		actionFullScreen->setIcon(QIcon(QPixmap("")));
		bFullScreen = false;
	}
}


void PreView::show_video_all()
{
	if (videoType == "1_4") {
		change_video_4(0);
	}
	else if (videoType == "5_8") {
		change_video_4(4);
	}
	else if (videoType == "9_12") {
		change_video_4(8);
	}
	else if (videoType == "13_16") {
		change_video_4(12);
	}
	else if (videoType == "1_6") {
		change_video_6(0);
	}
	else if (videoType == "6_11") {
		change_video_6(5);
	}
	else if (videoType == "11_16") {
		change_video_6(10);
	}
	else if (videoType == "1_8") {
		change_video_8(0);
	}
	else if (videoType == "9_16") {
		change_video_8(8);
	}
	else if (videoType == "1_9") {
		change_video_9(0);
	}
	else if (videoType == "8_16") {
		change_video_9(7);
	}
	else if (videoType == "1_16") {
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

	if (this->videoType != videoType) {
		this->videoType = videoType;
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

	if (this->videoType != videoType) {
		this->videoType = videoType;
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

	if (this->videoType != videoType) {
		this->videoType = videoType;
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

	if (this->videoType != videoType) {
		this->videoType = videoType;
		change_video_9(index);
	}
}

void PreView::show_video_16()
{
	videoMax = false;
	QString videoType;
	int index = 0;
	videoType = "1_16";

	if (this->videoType != videoType) {
		this->videoType = videoType;
		change_video_16(index);
	}
}

void PreView::hide_video_all()
{
	for (int i = 0; i < videoCount; i++) {
		ui.gridLayout->removeWidget(widgets.at(i).widget);
		widgets.at(i).widget->setVisible(false);
	}
}

void PreView::change_video(int index, int flag)
{
	int count = 0;
	int row = 0;
	int column = 0;

	for (int i = 0; i < videoCount; i++) {
		if (i >= index) {
			ui.gridLayout->addWidget(widgets.at(i).widget, row, column);
			widgets.at(i).widget->setVisible(true);
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
		ui.gridLayout->addWidget(widgets.at(0).widget, 0, 0, 2, 2);
		ui.gridLayout->addWidget(widgets.at(1).widget, 0, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(2).widget, 1, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(3).widget, 2, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(4).widget, 2, 1, 1, 1);
		ui.gridLayout->addWidget(widgets.at(5).widget, 2, 0, 1, 1);

		
		for (int i = 0; i < 6; i++) {
			widgets.at(i).widget->setVisible(true);
			
		}
	}
	else if (index == 5) {
		ui.gridLayout->addWidget(widgets.at(5).widget, 0, 0, 2, 2);
		ui.gridLayout->addWidget(widgets.at(6).widget, 0, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(7).widget, 1, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(8).widget, 2, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(9).widget, 2, 1, 1, 1);
		ui.gridLayout->addWidget(widgets.at(10).widget, 2, 0, 1, 1);

	
		for (int i = 5; i < 11; i++) {
			widgets.at(i).widget->setVisible(true);
			
		}
	}
	else if (index == 10) {
		ui.gridLayout->addWidget(widgets.at(10).widget, 0, 0, 2, 2);
		ui.gridLayout->addWidget(widgets.at(11).widget, 0, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(12).widget, 1, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(13).widget, 2, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(14).widget, 2, 1, 1, 1);
		ui.gridLayout->addWidget(widgets.at(15).widget, 2, 0, 1, 1);

		
		for (int i = 10; i < 16; i++) {
			widgets.at(i).widget->setVisible(true);
			
		}
	}
}

void PreView::change_video_8(int index)
{
	hide_video_all();
	if (index == 0) {
		ui.gridLayout->addWidget(widgets.at(0).widget, 0, 0, 3, 3);
		ui.gridLayout->addWidget(widgets.at(1).widget, 0, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(2).widget, 1, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(3).widget, 2, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(4).widget, 3, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(5).widget, 3, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(6).widget, 3, 1, 1, 1);
		ui.gridLayout->addWidget(widgets.at(7).widget, 3, 0, 1, 1);

		
		for (int i = 0; i < 8; i++) {
			widgets.at(i).widget->setVisible(true);
			
		}
	}
	else if (index == 8) {
		ui.gridLayout->addWidget(widgets.at(8).widget, 0, 0, 3, 3);
		ui.gridLayout->addWidget(widgets.at(9).widget, 0, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(10).widget, 1, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(11).widget, 2, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(12).widget, 3, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(13).widget, 3, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(14).widget, 3, 1, 1, 1);
		ui.gridLayout->addWidget(widgets.at(15).widget, 3, 0, 1, 1);

		
		for (int i = 8; i < 16; i++) {
			widgets.at(i).widget->setVisible(true);
			
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
	int itemtemp = str.right(1).toInt()-1;
	QString par = QObject::tr("%1").arg(index.parent().data().toString());
	
	QVariant var = ui.treeWidget->currentItem()->data(itemtemp, Qt::UserRole);
	pChannelTmp = (TreeData_t *)var.value<void *>();


	if (str == NULL || par == QObject::tr("解码设备"))
	{
		return;
	}

	if ((!pChannelTmp) || (pChannelTmp->Channel == 0))
		return;
	StopWatch();
	AddWatch(pChannelTmp, TRUE);
	treePrew->SelectTreeData(pChannelTmp);
}

int PreView::AddWatch(TreeData_t* pDev, BOOL bTipBox /* = FALSE */)
{
	
	if (!m_IsRestoreVideoParam)
	{
		m_TreeData[m_nfousWnd] = pDev;
	}
	int ret = widgets[m_nfousWnd].widget->AddWatch(pDev, 0, bTipBox);
	
	if (ret >= 0)
	{
		widgets[m_nfousWnd].isVideoOpen = true;
		SaveVideoParam();
	}
	
	
	return 0;
}

int PreView::AddWatch_t(int nWnd, TreeData_t* pDev)
{
	
	if (!m_IsRestoreVideoParam)
	{
		m_TreeData[nWnd] = pDev;
	}
	
	int ret = widgets[nWnd].widget->AddWatch(pDev, 0, FALSE, nWnd);
	if (ret >= 0)
	{
	
		widgets[nWnd].isVideoOpen = true;
	
		SaveVideoParam();
	}
	return ret;
}
void PreView::SaveVideoParam()
{
	QString file;
	file = QString("%1\\rtvideo.dat").arg(QCoreApplication::applicationDirPath());
	FILE *fp = NULL;
	if ((fp = fopen(file.toLatin1().data(), "wb")) == NULL)
	{
		return;
	}

	long dspmode = 16;
	fwrite(&dspmode, sizeof(long), 1, fp);

	for (int ix = 0; ix < 16; ix++)
	{
		fwrite(&widgets[ix].widget->m_dspWndinfo.bVS, sizeof(BOOL), 1, fp);
	}

	map<long, TreeData_t*>::iterator itPlayParam;
	for (itPlayParam = m_TreeData.begin(); itPlayParam != m_TreeData.end(); itPlayParam++)
	{
		if (itPlayParam->second != NULL)
		{
			fwrite(&(itPlayParam->first), sizeof(long), 1, fp);
			fwrite(&(itPlayParam->second->Channel), sizeof(U32), 1, fp);
			fwrite(&(itPlayParam->second->DevInfo->GetChannelInfo(itPlayParam->second->Channel)->SlaveDevId), sizeof(U32), 1, fp);
			fwrite(&((widgets[itPlayParam->first].widget)->m_dspWndinfo.bMainStream), sizeof(BOOL), 1, fp);
		}
	}

	fclose(fp);
}

int PreView::OnWidgetContextMeun(const QPoint& pt)
{
	int qs;
	QTreeWidgetItem *selected = ui.treeWidget->itemAt(pt);
	actionComparison->setEnabled(false);
	actionComparisonStop->setEnabled(false);
	if (selected != NULL)
	{
		QString var = ui.treeWidget->currentItem()->text(0);
		if (var.left(2) != "ch")
		{
			actionComparison->setEnabled(false);
			actionComparisonStop->setEnabled(false);

		}
		else
		{

			int qs = var.right(1).toInt()-1;
			QVariant var1 = ui.treeWidget->currentItem()->data(qs, Qt::UserRole);
			pChannelTmp = (TreeData_t *)var1.value<void *>();
			if (pChannelTmp != NULL)
			{
				
				if (pChannelTmp->DevInfo->GetChannelInfo(pChannelTmp->Channel)->Type == CHANNELINFO_TYPE_COMPARE)
				{
					actionComparison->setEnabled(true);
					actionComparisonStop->setEnabled(false);
					for (int i = 0; i < m_treeIp.size(); i++)
					{
						if (m_treeIp[i] == pChannelTmp->DevInfo->GetDevInfo()->szIpAddr)
						{
							actionComparison->setEnabled(false);
							actionComparisonStop->setEnabled(true);
						}
						else
						{
							actionComparison->setEnabled(true);
							actionComparisonStop->setEnabled(false);
						}

					}
				}
				else
				{
					actionComparison->setEnabled(false);
					actionComparisonStop->setEnabled(false);
				}

			}
			else
			{
				actionComparison->setEnabled(true);
				actionComparisonStop->setEnabled(false);
			}
		}
		
	}
	
	/*int qs = var.toInt();
	if (qs > 2)
	{
		actionComparison->setEnabled(false);
		actionComparisonStop->setEnabled(false);
	}
	else
	{
		actionComparison->setEnabled(true);
		actionComparisonStop->setEnabled(false);
	}*/
	
	QMenu menu;
	menu.setStyleSheet("QMenu::item:!enabled{color:grey;}");
	menu.addAction(actionRefresh);
	menu.addSeparator();

	if (selected){
		menu.addAction(actionComparison);
		menu.addAction(actionComparisonStop);
		menu.addSeparator();
	
	}
	//显示菜单
	menu.exec(ui.treeWidget->mapToGlobal(pt));
	return 0;
}

void PreView::OnMenuReFresh()
{
	ui.treeWidget->clear();
	treePrew->RefreshDevTree(ui.treeWidget, m_bShowGroup);
}

void PreView::OnMenuComparison()
{
	
	bool bRet = TRUE;
	StartCompare(TRUE);

}

void PreView::OnTreeReFresh()
{
	ui.treeWidget->clear();
	treePrew->RefreshDevTree(ui.treeWidget, m_bShowGroup);
}


void PreView::OnMenuComparisonStop()
{
	
	bool bRet = TRUE;
	StartCompare(FALSE);

}

void PreView::StartCompare(BOOL bStart)
{

	BOOL bRet = FALSE;
	TreeData_t *pChannel = NULL;

	QVariant var = ui.treeWidget->currentItem()->data(0, Qt::UserRole);
	pChannel = (TreeData_t *)var.value<void *>();
	if (pChannel == NULL)
	{
		//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("请在设备列表中选择设备"));
		myHelper::ShowMessageBoxWarning(QObject::tr("请在设备列表中选择设备!"));
		return;
	}
	QString ip = pChannel->DevInfo->GetDevInfo()->szIpAddr;
	vector<QString>::iterator it;
	if (bStart)
	{
		m_treeIp.push_back(ip);
		sort(m_treeIp.begin(), m_treeIp.end());
		m_treeIp.erase(unique(m_treeIp.begin(), m_treeIp.end()), m_treeIp.end());
	}
	else
	{
		for (it = m_treeIp.begin(); it != m_treeIp.end();)
		{
			if (*it == ip)
			{
				m_treeIp.erase(it);
			}
		}
	}

	int nUserId = pChannel->DevInfo->Login();
	if (nUserId <= 0)
	{
		//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("连接设备失败"));
		myHelper::ShowMessageBoxWarning(QObject::tr("连接设备失败!"));
		return;
	}

	CJLNDevice* pDevInfo = (CJLNDevice*)pChannel->DevInfo;

	EnterCriticalSection(&pDevInfo->m_lockSubOperation);
	if (bStart)
	{
		bRet = pDevInfo->StartSnapLink(nUserId, pChannel->Channel - 1, pDevInfo->GetChannelInfo(pChannel->Channel)->Type);
	}
	else
	{
		bRet = pDevInfo->StopSnapLink(pChannel->Channel - 1, pDevInfo->GetChannelInfo(pChannel->Channel)->Type);
	}
	LeaveCriticalSection(&pDevInfo->m_lockSubOperation);
	
}


bool PreView::event(QEvent *e)
{
	CompareEvent *event = static_cast<CompareEvent *>(e);

	if (e->type() == static_cast <QEvent::Type>(CompareEvent::getType(CET_DISPLAYIMG)))
	{
		DisplayImage();
	}
	else if (e->type() == static_cast <QEvent::Type>(CompareEvent::getType(CET_DISPLAYPERMSG)))
	{
		DisPlayPersonMessage();
	}
	else if (e->type() == static_cast <QEvent::Type>(CompareEvent::getType(CET_MESSAGEBOX)))
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("比对记录数据插入到数据库失败"));
		//ui.label->setUpdatesEnabled(true);
	}
	return QWidget::event(event);
}

void PreView::DisplayImage()
{
	if (g_CompareInfoImg.count() > 0)
	{
		SMART_FACE_CMP_QUERY_INFO *pCompareInfoTmp = &g_CompareInfoImg.dequeue();
		if (NULL == pCompareInfoTmp)
		{
			return;
		}

		char cpicName[MAX_PATH] = { 0 };
		char cLibName[MAX_PATH] = { 0 };
		char szSnapPath[MAX_PATH] = { 0 };

		char chTime[16] = { 0 };

		memcpy(chTime, pCompareInfoTmp->sLibSnapTime, 10);
		sprintf(szSnapPath, "%s\\%s\\%s\\%d", set->g_ClientCfg.szSnapPath, chTime, pCompareInfoTmp->cDeviceIP, pCompareInfoTmp->sLibChannelid);
		sprintf_s(cpicName, "%s\\%s", szSnapPath, (char*)pCompareInfoTmp->sSnappicname);
		QString strimagePath = QString::fromLocal8Bit(cpicName);
		string strTime = (char *)pCompareInfoTmp->sLibSnapTime;
		QString m_strSnapTime = QString::fromStdString(strTime);
		unRecognition *unRec = new unRecognition();

		list_unrecog.append(unRec);

		ui.horizontalLayout->addWidget(unRec);
		ui.horizontalLayout->setDirection(QBoxLayout::RightToLeft);
		unRecNum = ui.horizontalLayout->count();             // 获取布局中的item的数量

		if (unRecNum > capSet->m_unRecNum)
		{
			displayunRec();
		}
		//黑名单打开报警声音
		if (pCompareInfoTmp->sLibMode == 1)
		{
			OpenAlarmSound();
		}
		QImage image;
		image.load(strimagePath);

		unRec->resize(QSize(image.width(), image.height()));
		image.scaled(unRec->displayLabel->size(), Qt::KeepAspectRatio);
		unRec->displayLabel->setPixmap(QPixmap::fromImage(image));
		unRec->displayLabelTime->setText(m_strSnapTime);
	}

}

void PreView::DisPlayPersonMessage()
{
	if (g_CompareInfoArm.count() > 0)
	{
		SMART_FACE_CMP_QUERY_INFO *pCompareInfoTmp = &g_CompareInfoArm.dequeue();
		if (NULL == pCompareInfoTmp)
		{
			return;
		}

		char cpicName[MAX_PATH] = { 0 };
		char cLibName[MAX_PATH] = { 0 };
		char szSnapPath[MAX_PATH] = { 0 };

		char chTime[16] = { 0 };

		memcpy(chTime, pCompareInfoTmp->sLibSnapTime, 10);
		sprintf(szSnapPath, "%s\\%s\\%s\\%d", set->g_ClientCfg.szSnapPath, chTime, pCompareInfoTmp->cDeviceIP, pCompareInfoTmp->sLibChannelid);
		sprintf_s(cpicName, "%s\\%s", szSnapPath, (char*)pCompareInfoTmp->sSnappicname);
		sprintf_s(cLibName, "%s\\%s", szSnapPath, (char*)pCompareInfoTmp->sLibPicName);
		char *str1 = cLibName;
		QString strPic = QString::fromLocal8Bit(cpicName);
		QString strLib = QString::fromLocal8Bit(str1);
		qDebug() << strLib;

		Recognition *rec = new Recognition();
		list_recog.append(rec);
		
		ui.verticalLayout->addWidget(rec);
		ui.verticalLayout->setDirection(QBoxLayout::BottomToTop);
		RecNum = ui.verticalLayout->count();             // 获取布局中的item的数量
		if (RecNum > capSet->m_recNum)
		{
			displayRec();
		}


		QString strName = QString::fromLocal8Bit(pCompareInfoTmp->sName);
		QString strNo = QString::fromLocal8Bit(pCompareInfoTmp->sUserID);
		QString strMode = GetModeType(pCompareInfoTmp->sLibMode);
		string strTime = (char *)pCompareInfoTmp->sLibSnapTime;
		QString m_strSnapTime = QString::fromStdString(strTime);
		string strIP = (char *)pCompareInfoTmp->cDevName;
		QString strDevIP = QString::fromStdString(strIP);
		float m_strsimilarity = pCompareInfoTmp->sLibSimilarity * 100;
		QString strsimilarity = QString::number(m_strsimilarity, 'f', 2);

		QImage imagePic, imageLib;
		imagePic.load(strPic);
		imageLib.load(strLib);

		rec->displayPic->setScaledContents(true);
		rec->displayLib->setScaledContents(true);


		rec->displayPic->setPixmap(QPixmap::fromImage(imagePic));
		rec->displayLib->setPixmap(QPixmap::fromImage(imageLib));
		rec->displayName->setText(strName);
		rec->displayNo->setText(strNo);
		rec->displayDevice->setText(strDevIP);
		rec->displayTime->setText(m_strSnapTime);
		rec->displayType->setText(strMode);
		rec->g_progressBar->setValue(m_strsimilarity);
		rec->displayProgress->setText(strsimilarity);
	}

}

void PreView::displayunRec()
{
	if (unRecNum){
		QWidget *widget = ui.horizontalLayout->itemAt(0)->widget();
		ui.horizontalLayout->removeWidget(widget);
		delete widget;
	}
}

void PreView::displayRec()
{
	if (RecNum){
		QWidget *widget = ui.verticalLayout->itemAt(0)->widget();
		ui.verticalLayout->removeWidget(widget);
		delete widget;
	}
}

QString PreView::GetModeType(int nMode)
{

	QString strMode = QObject::tr("所有人");
	switch (nMode)
	{
	case 0:
		strMode = QObject::tr("所有人");
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


	capSet->show();
}

void PreView::StopWatch()
{
	if (m_TreeData[m_nfousWnd] != NULL)
	{
		m_TreeData[m_nfousWnd] = pChannelTmp;
	}
	
	widgets[m_nfousWnd].widget->StopWatch();
	widgets[m_nfousWnd].widget->IPLabel->setText("");
	
	SaveVideoParam();
	widgets[m_nfousWnd].isVideoOpen = false;
}

void PreView::StopAllWatch()
{
	for (int ix = 0; ix < (int)videoCount; ix++)
	{
		if (m_TreeData[ix] != NULL)
			m_TreeData[ix] = NULL;
	}
	for (int i = 0; i < videoCount; i++)
	{
		if (widgets[i].widget->m_dspWndinfo.bVideo)
		{
			widgets[i].widget->StopWatch();
			
		}
		
	}
	widgets[m_nfousWnd].isVideoOpen = false;
}

void PreView::storePrew()
{

	OnRestoreRealtime();
}
void PreView::ShowToolBar()
{
	for (int i = 0; i < videoCount; i++)
	{
		widgets[i].widget->isHideToolBar();
		if (widgets[i].widget->toolBarHide)
		{
			actionToolbar->setIcon(QIcon(QPixmap("")));
		}
		else
		{
			actionToolbar->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
		}
	}
	
}

void PreView::MainStream()
{
	if (!widgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	widgets[m_nfousWnd].widget->OnMenuStreamMain();
	actonMainsream->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
	actionSecStream->setIcon(QIcon(QPixmap("")));

}
void PreView::SecStream()
{
	if (!widgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	widgets[m_nfousWnd].widget->OnMenuStreamSub();
	actionSecStream->setIcon(QIcon(QPixmap(":/res/SoftIcon/check.ico")));
	actonMainsream->setIcon(QIcon(QPixmap("")));
}

//抓图
void PreView::CapTure()
{
	if (!widgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	widgets[m_nfousWnd].widget->CapturePic();
}

//打开声音
void PreView::OpenSound()
{
	if (!widgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	if (widgets[m_nfousWnd].widget->OpenSound() == 0)
	{
		actionVoice->setText(QObject::tr("打开声音"));
	}
	else
	{
		actionVoice->setText(QObject::tr("关闭声音"));
	}
}

//本地录像
void PreView::LocalRecord()
{
	if (!widgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	if (widgets[m_nfousWnd].widget->LocalRecord() == 0)
	{
		actionRecord->setText(QObject::tr("开始本地录像"));
	}
	else
	{
		actionRecord->setText(QObject::tr("停止本地录像"));
	}
}

//广播
void PreView::BroadcastSlot()
{
	if (!widgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return;
	}
	if (widgets[m_nfousWnd].widget->m_bTalk)
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
	if (!widgets[m_nfousWnd].widget->m_dspWndinfo.bVideo)
	{
		return 0;
	}
	for (int i = 0; i < videoCount; i++)
	{

		if (widgets[i].widget->m_dspWndinfo.bVideo)
		{
			widgets[i].widget->BroadCast(bStart);
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
			(*it)->setBackground(0, treePrew->m_itemBrush);
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
			treePrew->parentExpand(*it);
		}
		else{
			(*it)->setBackground(0, treePrew->m_itemBrush);
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
void PreView::on_m_btnPtzUp_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eTILT_UP, 0, m_speed);
	
}

//向下
void PreView::on_m_btnPtzDown_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eTILT_DOWN, 0, m_speed);
}
//向左
void PreView::on_m_btnPtzLeft_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, ePAN_LEFT, 0, m_speed);
}
//向右
void PreView::on_m_btnPtzRight_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, ePAN_RIGHT, 0, m_speed);
}
//自动
void PreView::on_m_btnPtzAuto_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, ePAN_AUTO, 0, m_speed);
}
//变倍+
void PreView::on_m_btnPtzFocus_A_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eFOCUS_NEAR, 0, m_speed);
}
//变倍-
void PreView::on_m_btnPtzFocus_S_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eFOCUS_FAR, 0, m_speed);
}
//聚焦+
void PreView::on_m_btnPtzZoom_A_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eZOOM_IN, 0, m_speed);
}
//聚焦-
void PreView::on_m_btnPtzZoom_S_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eZOOM_OUT, 0, m_speed);
}
//光圈+
void PreView::on_m_btnPtzApe_A_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eIRIS_OPEN, 0, m_speed);
}
//光圈-
void PreView::on_m_btnPtzApe_S_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eIRIS_CLOSE, 0, m_speed);
}

//灯光
void PreView::on_PtzLight_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eLIGHT_PWRON, 0, m_speed);
}
//预置
void PreView::on_PtzPreset_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eSET_PRESET, 0, m_speed);
}
//雨刷
void PreView::on_PtzRain_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eWIPER_PWRON, 0, m_speed);
}
//调用
void PreView::on_PtzRecall_clicked()
{
	if (pChannelTmp == NULL)
		return;
	pChannelTmp->DevInfo->PtzCtrl((HWND)pChannelTmp->Channel, eGOTO_PRESET, 0, m_speed);
}

void PreView::OpenAlarmSound()
{
	QSound *sound = new QSound(m_strSoundPath, this); //构建对象

	sound->play();//播放
}

void PreView::showEvent(QShowEvent *e)
{
	this->setAttribute(Qt::WA_Mapped);
	widgets[m_nfousWnd].widget->label->setUpdatesEnabled(true);
	QWidget::showEvent(e);
}