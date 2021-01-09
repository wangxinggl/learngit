#define  _CRT_SECURE_NO_WARNINGS
#include "videoplayback.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTime>
#include <QFileDialog>
#include <QStringList>
#include <QStandardPaths>
#include <QStandardItem>
#include <QDebug>
#include <QDateTime>
#include <QDir>
#include <QPoint>
#include <QContextMenuEvent>
#include <QTableWidgetSelectionRange>
#include <QTime>
#include <QHeaderView> 
#include "myhelper.h"
#include <QIcon>
#include <QPixmap>
#include <QDate>
#include "client.h"

extern Client* g_pInstance;

videoPlayback::videoPlayback(QWidget *parent)
	: QWidget(parent)
	, itemCount(16)
	, m_pDownLoadDlg(NULL)
{
	ui.setupUi(this);
	
	
	initForm();
	initMenu();
	inittableWidget();
	initSearchButton();//设置搜索框样式
	nCheckNum =0;
	ui.dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
	ui.dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
	QString strBuffer = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	strBuffer = strBuffer.left(11) + "00:00:00";
	QDateTime time = QDateTime::fromString(strBuffer, "yyyy-MM-dd hh:mm:ss");
	ui.dateTimeEdit->setDateTime(time);

	ui.dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
	//ui.label_displayTime->setText("00:00:00/00:00:00");
	//ui.label_Speed->setText(QObject::tr("正常速度"));
	m_nVideoNum = 4;
	m_iSelectCount = 0;
	m_bDragging = FALSE;
	ResetPlayData(-1);
	initTimeLine();
	pFindFileInfo = NULL;
	m_bShowGroup = FALSE;
	m_bShowDev = FALSE;

	PLAY_TIMER = startTimer(1000);
	m_ckSelCount = 0;
	for (int i = 0; i < REPLAY_MAX_NUM; i++)
	{
		memset(&m_ReplayWnd[i], 0, sizeof(ReplayWndInfo));
		m_ReplayWnd[i].nPlayHandle = -1;
		m_ReplayWnd[i].nDecHandle = -1;
	}

	m_bSound = FALSE;
	nNumTmp = 0;
	m_tableWidget = new QTableWidget();
	m_tableWidget = ui.tableWidget;
	ui.treeWidget->setHeaderHidden(true);
	m_pChannelInfo = NULL;
	itemTemp = NULL;
	m_lFindHandle = -1;
	timelineCount = 0;
	m_videoTimeLine_tmp = NULL;
}

videoPlayback::~videoPlayback()
{
	m_vtVideoNetFile.clear();
	if (m_pDownLoadDlg)
	{
		delete m_pDownLoadDlg;
		m_pDownLoadDlg = NULL;
	}
	// 释放资源
	/*for (auto iter = m_mapVideoLine.begin(); iter != m_mapVideoLine.end(); )
	{
		auto second = iter->second;
		if (second)
		{
			delete second;				  // 释放指针
			second = NULL;
			m_mapVideoLine.erase(iter++);	  // 从map中删除元素，注意iter++的写法
		}
	}
	m_mapVideoLine.clear();

	for (auto iter = m_mapChannelTmp.begin(); iter != m_mapChannelTmp.end(); )
	{
		auto second = iter->second;
		if (second)
		{
			delete second;				  // 释放指针
			second = NULL;
			m_mapChannelTmp.erase(iter++);	  // 从map中删除元素，注意iter++的写法
		}
	}
	m_mapChannelTmp.clear();*/
}

void videoPlayback::initSearchButton()
{
	QPushButton *pSearchButton = new QPushButton(this);

	pSearchButton->setCursor(Qt::PointingHandCursor);
	pSearchButton->setFixedSize(22, 22);
	pSearchButton->setToolTip(QObject::tr("搜索"));
	pSearchButton->setStyleSheet("QPushButton{border-image:url(:/res/SoftIcon/icon_search_normal.png); background:transparent;} \
								 								QPushButton:hover{border-image:url(:/res/SoftIcon/icon_search_hover.png)} \
																QPushButton:pressed{border-image:url(:/res/SoftIcon/icon_search_press.png)}");
	QMargins margins = ui.lineEdit_Search->textMargins();
	ui.lineEdit_Search->setTextMargins(margins.left(), margins.top(), pSearchButton->width(), margins.bottom());
	ui.lineEdit_Search->setPlaceholderText(QObject::tr("请输入搜索内容"));

	QHBoxLayout *pSearchLayout = new QHBoxLayout();
	pSearchLayout->addStretch();
	pSearchLayout->addWidget(pSearchButton);
	pSearchLayout->setSpacing(0);
	pSearchLayout->setContentsMargins(0, 0, 0, 0);
	ui.lineEdit_Search->setLayout(pSearchLayout);
	connect(pSearchButton, SIGNAL(clicked(bool)), this, SLOT(on_btnSearchIP_clicked()));
}
void videoPlayback::initMenu()
{
	videoMenu = new QMenu(this);
	videoMenu->addSeparator();
	videoMenu->addAction(QObject::tr("全屏"), this, SLOT(screen_full()));
	videoMenu->addAction(QObject::tr("退出全屏"), this, SLOT(screen_normal()));
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
void videoPlayback::initForm()
{
	//设置样式表

	videoMax = false;
	videoCount = 16;
	videoType = "1_4";

	m_nfousWnd = 0;
	for (int i = 0; i < videoCount; i++) {

		widget = new OneVideo();
		connect(widget, SIGNAL(clickedEvent()), this, SLOT(OneVideoClicked()));
		widget->setObjectName(QString("video%1").arg(i + 1));
		widget->installEventFilter(this);
		widgets.append(widget);
	}
	
	widgets[0]->setStyleSheet(".OneVideo{ border:1px solid white}");
	show_video_all();
}

void videoPlayback::OnTreeReFresh()
{
	ui.treeWidget->clear();
	m_pTreeDev->RefreshDevTree(ui.treeWidget, m_bShowGroup);
}
void videoPlayback::hide_video_all()
{
	for (int i = 0; i < videoCount; i++) {
		ui.gridLayout_main->removeWidget(widgets.at(i));
		widgets.at(i)->setVisible(false);
	}
	
}
void videoPlayback::initTimeLine()
{
	if (itemCount <= 0)
	{
		itemCount = 1;
	}
	for (int i = 0; i < itemCount; i++) {

		m_videoTimeLine = new VideoTimeLine;
		videoTimeLineList.append(m_videoTimeLine);
		
	}
	//ui.hLayout = new QHBoxLayout(ui.VideoTimeLineBackFrame);
	ui.hLayout->addWidget(videoTimeLineList[0]);
	ui.hLayout->setMargin(0);

	
}
void videoPlayback::inittableWidget()
{
	ui.tableWidget->setColumnCount(7);
	QStringList header;
	header <<QObject::tr("")<<QObject::tr("开始时间")<<QObject::tr("结束时间")<<QObject::tr("文件名")<<QObject::tr("文件大小")<<QObject::tr("文件信息")<<QObject::tr("时间差");
	ui.tableWidget->setHorizontalHeaderLabels(header);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget->setColumnWidth(0, 20);
	ui.tableWidget->setColumnWidth(1, 140);
	ui.tableWidget->verticalHeader()->hide();
	ui.tableWidget->horizontalHeader()->hide();
	ui.tableWidget->setColumnHidden(2, true);
	ui.tableWidget->setColumnHidden(3, true);
	ui.tableWidget->setColumnHidden(4, true);
	ui.tableWidget->setColumnHidden(5, true);
	connect(ui.tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slotSelectChanged(int,int)));

	/*menu = new QMenu(); //创建菜单项
	actionDownLoad = new QAction(this);
	actionPicSearch = new QAction(this);
	actionVideoSearch = new QAction(this);
	actionDownLoad->setText(QObject::tr("下载"));
	actionPicSearch->setText(QObject::tr("以图搜图"));
	actionVideoSearch->setText(QObject::tr("以图搜录像"));
	connect(actionDownLoad, SIGNAL(triggered(bool)), this, SLOT(actionDownLoadClick()));
	connect(actionPicSearch, SIGNAL(triggered(bool)), this, SLOT(actionPicSearchClick()));
	connect(actionVideoSearch, SIGNAL(triggered(bool)), this, SLOT(actionVideoSearchClick()));*/

	

	
}


void videoPlayback::initTree()
{
	ui.treeWidget->clear();

	m_pTreeDev->ShowTreebyType(ui.treeWidget);
	connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(slotItemClicked()));
}

void videoPlayback::slotItemClicked()
{
	QString str = ui.treeWidget->currentItem()->text(0);
	QVariant var1 = ui.treeWidget->currentItem()->data(0, Qt::UserRole);

	m_pChannelInfo = (TreeData_t *)var1.value<void *>();
	
	if (str == NULL)
	{
		return;
	}

	if ((!m_pChannelInfo) || (m_pChannelInfo->Channel == 0))
		return;

	m_mapChannelTmp[m_nfousWnd] = m_pChannelInfo;	
}

void videoPlayback::cleaLayout()
{
	QLayoutItem  *child;
	while ((child = ui.hLayout->takeAt(0)) != 0)
	{
		if (child->widget())
		{
			child->widget()->setParent(NULL);
		}
		delete child;
	}
}

void videoPlayback::initVideoplay()
{
	m_lFindHandle = -1;
}

void videoPlayback::treeItemChanged(QTreeWidgetItem *item,int column)
{
	QTreeWidgetItem *parent = item->parent();
	if (parent == NULL){
		return;
	}
	
	int childCount = parent->childCount();
	for (int i = 0; i < childCount; i++){
		QTreeWidgetItem *childItem = parent->child(i);


		if (childItem->checkState(0) == Qt::Checked){

			QVariant var = item->data(i, Qt::UserRole);
			TreeData_t* pChannel = (TreeData_t *)var.value<void *>();
			if (itemTemp != NULL)
			{
				itemTemp->setCheckState(0, Qt::Unchecked);
			}

			itemTemp = item;
			m_pChannelInfo = pChannel;
			if (m_pChannelInfo == NULL)
			{
				return;
			}

			nCheckNum++;


		}
	}
}


void videoPlayback::on_btnVSearch_clicked()
{
	//停止检索
	if (m_lFindHandle >= 0)
	{
		killTimer(FIND_TIMER);
		Sleep(100);
		return;
	}
	
	
	if (m_pChannelInfo == NULL)
	{
		//QMessageBox::information(this,QObject::tr("警告"),QObject::tr("请勾选要选择的摄像头"));
		myHelper::ShowMessageBoxWarning(QObject::tr("请勾选要选择的摄像头!"));
		return;
	}

	if (m_pChannelInfo->pDevObj->m_lUserLoginID < 0)
	{
		//QMessageBox::information(this,QObject::tr("警告"),QObject::tr("检索录像文件失败,无法连接到设备!"));
		myHelper::ShowMessageBoxWarning(QObject::tr("检索录像文件失败,无法连接到设备!!"));
		return;
	}
	
	TabDevInfo_t *pTabDevInfo = m_pChannelInfo->pDevObj->GetDevInfo();
	if (pTabDevInfo != NULL)
	{
		m_strDevName = pTabDevInfo->szDevName;
	}
	m_lChannel = m_pChannelInfo->Channel;
	if (m_pChannelInfo->Channel <= 0 || m_pChannelInfo->Channel>1024) //hik CVR 
		return;
	m_nRecordtype = ui.comboBox->currentIndex();
	switch (m_nRecordtype)
	{
	case 0:
		m_nRecordtype = SDK_RECORD_ALL;
		break;
	case 1:
		m_nRecordtype = SDK_RECORD_ALARM;
		break;
	case 2:
		m_nRecordtype = SDK_RECORD_REGULAR;
		break;
	case 3:
		m_nRecordtype = SDK_PIC_ALL;
		break;
	case 4:
		m_nRecordtype = SDK_PIC_FACE;
		ui.tableWidget->setColumnHidden(4, false);
		ui.tableWidget->setColumnHidden(6, true);
		break;
	case 5:
		m_nRecordtype = SDK_PIC_CARNO;
		break;
	case 6:
		m_nRecordtype = SDK_PIC_WIFI;
		break;
	default:
		m_nRecordtype = SDK_RECORD_ALL;
		break;
	}

	m_lFindFileType = m_nRecordtype;
	mlog(LOG_INFO, "PlayBack Query channel = %d,type = %d,login ID = %d,ip = %s", m_pChannelInfo->Channel, m_lFindFileType, m_pChannelInfo->pDevObj->m_lUserLoginID, pTabDevInfo->szIpAddr);

	QString TimeBegin = ui.dateTimeEdit->text();
	QString TimeEnd = ui.dateTimeEdit_2->text();
	

	QDate m_DateBegin = ui.dateTimeEdit->date();
	QDate m_DateEnd = ui.dateTimeEdit_2->date();
	QTime m_TimeBegin = ui.dateTimeEdit->time();
	QTime m_TimeEnd = ui.dateTimeEdit_2->time();
	VIDEONET_TIME startTime = { 0 }, stopTime = { 0 };
	startTime.dwYear = m_DateBegin.year();
	startTime.dwMonth = m_DateBegin.month();
	startTime.dwDay = m_DateBegin.day();
	startTime.dwHour = m_TimeBegin.hour();
	startTime.dwMinute = m_TimeBegin.minute();
	startTime.dwSecond = m_TimeBegin.second();

	stopTime.dwYear =m_DateEnd.year();
	stopTime.dwMonth = m_DateEnd.month();
	stopTime.dwDay = m_DateEnd.day();
	stopTime.dwHour = m_TimeEnd.hour();
	stopTime.dwMinute = m_TimeEnd.minute();
	stopTime.dwSecond = m_TimeEnd.second();
	if (QString::compare(TimeBegin,TimeEnd) > 0)
	{
		//QMessageBox::information(this,QObject::tr("警告"),QObject::tr("开始时间不能大于结束时间!"));
		myHelper::ShowMessageBoxWarning(QObject::tr("开始时间不能大于结束时间!"));
		return;
	}
	else if (QString::compare(TimeBegin, TimeEnd) == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("开始时间和结束时间不能一样!"));
		return;
	}
	else
	{
		QDateTime m_beginTime = QDateTime::fromString(TimeBegin, "yyyy-MM-dd hh:mm:ss");
		QDateTime m_endTime = QDateTime::fromString(TimeEnd, "yyyy-MM-dd hh:mm:ss");
		if (m_beginTime.secsTo(m_endTime) > 1*24*60*60)
		{
			//QMessageBox::information(this,QObject::tr("警告"),QObject::tr("时间不能超过1天!"));
			myHelper::ShowMessageBoxWarning(QObject::tr("时间不能超过1天!"));
			return;
		}
	}
	

	VIDEONET_FINDINFO searchInfo;
	memset(&searchInfo, 0, sizeof(VIDEONET_FINDINFO));
	searchInfo.nChannelN0 = m_pChannelInfo->Channel - 1;
	searchInfo.nFileType = m_nRecordtype;
	searchInfo.startTime.dwYear = m_DateBegin.year();
	searchInfo.startTime.dwMonth = m_DateBegin.month();
	searchInfo.startTime.dwDay = m_DateBegin.day();
	searchInfo.startTime.dwHour = m_TimeBegin.hour();
	searchInfo.startTime.dwMinute = m_TimeBegin.minute();
	searchInfo.startTime.dwSecond = m_TimeBegin.second();


	searchInfo.endTime.dwYear = m_DateEnd.year();
	searchInfo.endTime.dwMonth = m_DateEnd.month();
	searchInfo.endTime.dwDay = m_DateEnd.day();
	searchInfo.endTime.dwHour = m_TimeEnd.hour();
	searchInfo.endTime.dwMinute = m_TimeEnd.minute();
	searchInfo.endTime.dwSecond = m_TimeEnd.second();
	/*memcpy( &searchInfo.startTime, &startTime, sizeof(searchInfo.startTime));
	memcpy( &searchInfo.endTime, &stopTime, sizeof(searchInfo.endTime));*/
	searchInfo.szFileName[0] = 1;

	if (m_lFindFileType == SDK_PIC_FACE || m_lFindFileType == SDK_PIC_CARNO
		|| m_lFindFileType == SDK_PIC_WIFI)
	{
		FindPictureFile(&searchInfo);
	}
	else
	{
		FindRecordFile(&searchInfo);
	}
	m_lFindType = FIND_TYPE_JL_NEW;
	   
	FIND_TIMER = startTimer(100);
}


void videoPlayback::handleTimeout()
{
	videoSegmentList.clear();
	clearCurrAge(ui.tableWidget);
	int startHour, startMinute,endHhour,endMinute = 0;
	long index = 0;
	FILE* pFWifi = NULL;
	int nFileSize = m_vtVideoNetFile.size();
	if (m_lFindFileType == SDK_PIC_WIFI)
	{
		m_strWifiPath = "%s\\WifiInformation.ini";
		pFWifi = fopen(m_strWifiPath.toLatin1().data(),"wb+");
	}
	if (nFileSize < 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("搜索录像信息为0"));
	}
	for (int ix = 0;ix < nFileSize;ix++)
	{
		VIDEONET_FILE_DATA* pVideoNetFileData = &m_vtVideoNetFile[ix];
		int RowCont=ui.tableWidget->rowCount();
		ui.tableWidget->insertRow(RowCont);//增加一行
		QString startTime = QString("%1-%2-%3 %4:%5:%6").arg(pVideoNetFileData->stBeginTime.year, 4, 10, QLatin1Char('0')).arg(pVideoNetFileData->stBeginTime.month, 2, 10, QLatin1Char('0'))
				.arg(pVideoNetFileData->stBeginTime.day, 2, 10, QLatin1Char('0')).arg(pVideoNetFileData->stBeginTime.hour, 2, 10, QLatin1Char('0'))
				.arg(pVideoNetFileData->stBeginTime.minute, 2, 10, QLatin1Char('0')).arg(pVideoNetFileData->stBeginTime.second, 2, 10, QLatin1Char('0'));
		QString endTime = QString("%1-%2-%3 %4:%5:%6").arg(pVideoNetFileData->stEndTime.year, 4, 10, QLatin1Char('0')).arg(pVideoNetFileData->stEndTime.month, 2, 10, QLatin1Char('0'))
				.arg(pVideoNetFileData->stEndTime.day, 2, 10, QLatin1Char('0')).arg(pVideoNetFileData->stEndTime.hour, 2, 10, QLatin1Char('0'))
				.arg(pVideoNetFileData->stEndTime.minute, 2, 10, QLatin1Char('0')).arg(pVideoNetFileData->stEndTime.second, 2, 10, QLatin1Char('0'));

		QString strFileName = QString(QLatin1String(pVideoNetFileData->sFileName));
		QString strName;
		if (m_lFindFileType == SDK_PIC_FACE || m_lFindFileType == SDK_PIC_CARNO)
		{
			int nSeg = strFileName.lastIndexOf("+");
			if (nSeg > 0)
			{
				strFileName = strFileName.left(nSeg);
				strName = strFileName.mid(nSeg+1);
			}

		}
		if (m_lFindFileType == SDK_PIC_WIFI)
		{
			int nSeg = strFileName.lastIndexOf("S:");
			if (nSeg > 0)
			{
				strFileName = strFileName.left(nSeg);
				strFileName.append(QObject::tr("强度"));

				strName = strFileName.mid(nSeg+2);
			}
		}
		QString fileSize = QString::number(pVideoNetFileData->size)+"KB";

		m_Vcheck = new QTableWidgetItem();
		m_Vcheck->setCheckState(Qt::Unchecked);

		ui.tableWidget->setItem(ix, 0, m_Vcheck); //插入复选框
		ui.tableWidget->setItem(ix,1,new QTableWidgetItem(startTime));
		getTimeInt(startHour, startMinute, startTime.right(8));
		ui.tableWidget->setItem(ix,2,new QTableWidgetItem(endTime));
		getTimeInt(endHhour, endMinute, endTime.right(8));
		ui.tableWidget->setItem(ix,3,new QTableWidgetItem(strFileName));
		ui.tableWidget->setItem(ix,4,new QTableWidgetItem(fileSize));
		ui.tableWidget->setItem(ix,5,new QTableWidgetItem(strName));
			
		QTime t_beginTime = QTime::fromString(startTime.right(8), "hh:mm:ss");
		QTime t_endTime = QTime::fromString(endTime.right(8), "hh:mm:ss");
		QTime m_time;
		m_time.setHMS(0, 0, 0, 0);
		QString strTimeText = m_time.addSecs(t_beginTime.secsTo(t_endTime)).toString("hh:mm:ss");
		if (strTimeText.right(8).section(':',0,0).trimmed().toInt()>0)
		{
			strTimeText = QObject::tr("%1时%2分%3秒").arg(strTimeText.right(8).section(':', 0, 0).trimmed().toInt())
					.arg(strTimeText.right(8).section(':', 1, 1).trimmed().toInt()).arg(strTimeText.right(8).section(':', 2, 2).trimmed().toInt());
		}
		else
		{
			if (strTimeText.right(8).section(':', 1, 1).trimmed().toInt()>0)
			{
				strTimeText = QObject::tr("%1分%2秒").arg(strTimeText.right(8).section(':', 1, 1).trimmed().toInt())
						.arg(strTimeText.right(8).section(':', 2, 2).trimmed().toInt());
			}
			else
			{
				strTimeText = QObject::tr("%1秒").arg(strTimeText.right(8).section(':', 2, 2).trimmed().toInt());
			}
		}
		ui.tableWidget->setItem(ix, 6, new QTableWidgetItem(strTimeText));
			
		VideoSegmentInfo data;
		data.videoStartTime = QTime(startHour, startMinute);
		data.videoEndTime = QTime(endHhour, endMinute);
		videoSegmentList.append(data);
			
	}
	if (pFWifi)
	{
		fclose(pFWifi);
		pFWifi = NULL;
	}
	m_lFindHandle = -1;
	
	if (videoSegmentList.size() < 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("搜索数据为0!"));
		return;
	}
	if (videoSegmentList.size() > 0)
	{
		//m_videoTimeLine->addLayerVideoSegemntData(0, videoSegmentList);
		videoTimeLineList[timelineCount]->addLayerVideoSegemntData(0, videoSegmentList);
		//m_mapVideoLine.insert(make_pair(pChannelTmp->DevInfo->GetDevInfo()->szIpAddr + QString::number(pChannelTmp->Channel), videoTimeLineList[timelineCount]));
		//m_mapVideoLine[pChannelTmp->DevInfo->GetDevInfo()->szIpAddr + QString::number(pChannelTmp->Channel)] = videoTimeLineList[timelineCount];
		m_mapVideoLine[m_nfousWnd] = videoTimeLineList[timelineCount];
		cleaLayout();
		ui.hLayout->addWidget(videoTimeLineList[timelineCount]);
		ui.hLayout->setMargin(0);
		timelineCount++;
	}
	
}

void videoPlayback::getTimeInt(int& hour, int& sec, QString srcTime)
{
	hour = srcTime.section(':', 0, 0).trimmed().toInt();
	sec =  srcTime.section(':', 1, 1).trimmed().toInt();
}

void videoPlayback::drawWarning(int startHour, int startMin, int endHour, int endMin)
{
	
	
}
/*
void videoPlayback::on_btnExtend_clicked()
{
	 static bool v_flag = false;
	 if (!v_flag)
	 {
		 ui.listView->setVisible(false);
		 v_flag=true;
		 ui.btnExtend->setText("<<");
	 }
	 else
	 {
		 ui.listView->setVisible(true);
		
		 v_flag=false;
		 ui.btnExtend->setText(">>");
	 }
	
}

void videoPlayback::on_btnExtend_2_clicked()
{
	static bool v_flag = false;
	if (!v_flag)
	{
		ui.widget_2->setVisible(false);
		v_flag=true;
		ui.btnExtend_2->setText(">>");
	}
	else
	{
		ui.widget_2->setVisible(true);
		
		v_flag=false;
		ui.btnExtend_2->setText("<<");
	}
}
*/

void videoPlayback::on_btnPlay_clicked()
{
	if (m_videoTimeLine_tmp == NULL)
	{
		return;
	}
	bool bControlAll = false;
	if (ui.m_chkReplay->isChecked() == true)
		bControlAll = true;
	bool bControlPause = false;
	
	for (int i = 0;i < REPLAY_MAX_NUM;i++)
	{
		if (!bControlAll)
		{
			i = m_nfousWnd;
		}
		if (m_ReplayWnd[i].nPlayHandle != -1)
		{
			if (m_ReplayWnd[i].nStreamtype == 1)
			{
				VideoPlayer_Pause(m_ReplayWnd[i].nDecHandle, !m_ReplayWnd[i].bPause);
				m_ReplayWnd[i].bPause = !m_ReplayWnd[i].bPause;
			}
			else
			{
				if (!m_ReplayWnd[i].bPause)
				{
					VideoNet_PlayBackControl(m_ReplayWnd[i].nPlayHandle, SDK_PLAY_BACK_PAUSE, 0);
					m_videoTimeLine_tmp->m_layerDrawWidget->onStopMoveNeedle();
				
					//m_videoTimeLine->m_layerDrawWidget->onStopMoveNeedle();
				}		
				else
				{
					VideoNet_PlayBackControl(m_ReplayWnd[i].nPlayHandle, SDK_PLAY_BACK_CONTINUE, 0);
					m_videoTimeLine_tmp->m_layerDrawWidget->onStartMoveNeedle();
					
					//m_videoTimeLine->m_layerDrawWidget->onStartMoveNeedle();
				}
				
				VideoPlayer_Pause(m_ReplayWnd[i].nDecHandle, !m_ReplayWnd[i].bPause);
				m_ReplayWnd[i].bPause = !m_ReplayWnd[i].bPause;

			}
			bControlPause = true;
		}
		if (!bControlAll)
		{
			break;
		}
	}
	
	if (m_ReplayWnd[m_nfousWnd].nPlayHandle >= 0)
	{
		if (!m_ReplayWnd[m_nfousWnd].bPause)
		{
			
			ui.btnPlay->setIcon(QIcon(QPixmap(":/res/SoftIcon/z_pase.png")));
			//ui.btnPlay->setStyleSheet("border-image: url(:/res/SoftIcon/z_pase.png);");
		}	
		else
		{
			
			ui.btnPlay->setIcon(QIcon(QPixmap(":/res/SoftIcon/z_play.png")));
			//ui.btnPlay->setStyleSheet("border-image: url(:/res/SoftIcon/z_play.png);");
		}
			
			
	}

	if (bControlPause)
		return;

	for (int i = 0;i < REPLAY_MAX_NUM;i++)
	{
		if (!bControlAll)
		{
			i = m_nfousWnd;
		}
		if (m_ReplayWnd[i].nPlayHandle >= 0)
		{
			if (!bControlAll)
			{
				return;
			}
			continue;
		}
		m_ReplayWnd[i].nErrorCount = 0;

		if (m_ReplayWnd[i].nStreamtype == -1)
		{
			if(!bControlAll)
				return;
			continue;
		}

		if (m_ReplayWnd[i].nStreamtype == 1)
		{
			PlayJLLocalFile(i);
		}
		else
		{
			if (m_ReplayWnd[i].pPlayInfo == NULL)
			{
				if (!bControlAll)
					return;
				continue;
			}

			if (m_ReplayWnd[i].nStreamtype == 0)
			{
				m_ReplayWnd[i].nPlayHandle = PlayBackJLByName(i, m_lChannel, m_ReplayWnd[i].szBeginTime, m_ReplayWnd[i].szEndTime);
			}			
			
			if (m_ReplayWnd[i].nStreamtype == PLAYBACK_TYPE_PICTURE)
			{
				if (m_lFindFileType == SDK_PIC_FACE || m_lFindFileType == SDK_PIC_CARNO || m_lFindFileType == SDK_PIC_ALL)
				{
					QString strLicense = m_ReplayWnd[i].szFileName;
					if (!m_pDownLoadDlg)
					{
						m_pDownLoadDlg = new RePlayDownDlg();
					}
					m_pDownLoadDlg->m_pDevObj = m_pChannelInfo->pDevObj;
					m_pDownLoadDlg->m_bPicture = TRUE;	//人脸车牌图片标识
					m_strPicPath = "";
					m_pDownLoadDlg->StartDownPicture();
				}
			}
			
		}

		if (m_ReplayWnd[i].nPlayHandle >= 0)
		{
			m_ReplayWnd[i].bPlay = TRUE;
			if (m_ReplayWnd[i].nStreamtype == 1)
			{
				ui.btnPlay->setIcon(QIcon(QPixmap(":/res/SoftIcon/z_play.png"))); 
			}
			else
			{
				ui.btnPlay->setIcon(QIcon(QPixmap(":/res/SoftIcon/z_pase.png")));
				m_videoTimeLine_tmp->m_layerDrawWidget->onStartMoveNeedle(m_CurrData);
				widgets[i]->m_displayScreen->setUpdatesEnabled(false);
				
			}
			
		}
		else if (m_ReplayWnd[i].nStreamtype != -1)
		{
			
			m_ReplayWnd[i].bPlay = FALSE;
			m_ReplayWnd[i].nPlayHandle = -1;
			StopPlay(i);
		}
		if(!bControlAll)
			break;
	}
}
void videoPlayback::ShowPicture(QString& strPath)
{
	m_strPicPath = strPath;
	m_Image.load(strPath);
	m_Image.scaled(widgets[m_nfousWnd]->m_displayScreen->size(), Qt::KeepAspectRatio);
	widgets[m_nfousWnd]->m_displayScreen->setScaledContents(true);
	widgets[m_nfousWnd]->m_displayScreen->setPixmap(QPixmap::fromImage(m_Image));

}
void CALLBACK videoPlayback::InfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser)
{
	
}

void __stdcall videoPlayback::pProc(LONG nPort,LPCSTR pBuf,LONG nSize,LONG nWidth,LONG nHeight, LONG nStamp,LONG nType,LONG nUser)
{

}

void videoPlayback::StopPlay(int nIndex)
{
	int i = nIndex;
	m_ReplayWnd[i].nErrorCount = 0;
	widgets[i]->m_displayScreen->setUpdatesEnabled(true);
	if (m_ReplayWnd[i].nPlayHandle >= 0 && m_ReplayWnd[i].pPlayInfo)
	{
		BOOL bRet;
		if (m_ReplayWnd[i].nStreamtype == 1)
			bRet = TRUE;


		if (m_ReplayWnd[i].nStreamtype == 1)
		{
			VideoPlayer_CloseFile(m_ReplayWnd[i].nDecHandle);
			VideoPlayer_CloseStream(m_ReplayWnd[i].nDecHandle);
			VideoPlayer_Stop(m_ReplayWnd[i].nDecHandle);
			m_ReplayWnd[i].nDecHandle = -1;
		}
		else
		{
			if (m_ReplayWnd[i].nPlayHandle >= 0)
			{
				VideoNet_StopPlayBack(m_ReplayWnd[i].nPlayHandle);
				m_ReplayWnd[i].nPlayHandle = -1;
			}

			if (m_ReplayWnd[i].nDecHandle)
			{
				VideoPlayer_CloseStream(m_ReplayWnd[i].nDecHandle);
				VideoPlayer_Stop(m_ReplayWnd[i].nDecHandle);
				m_ReplayWnd[i].nDecHandle = -1;
			}
		}

		if (m_ReplayWnd[i].nStreamtype == 2)
		{
			//SetTreeItemCheck(m_ReplayWnd[i].pPlayInfo, FALSE);
			m_ReplayWnd[i].pPlayInfo = NULL;
			m_iSelectCount--;
		}
		else if (m_ReplayWnd[i].nStreamtype == 0)
			m_ReplayWnd[i].pPlayInfo = NULL; //远程文件回放也要清

		//ui.label_Speed->setText(QObject::tr("正常速度"));
		widgets[m_nfousWnd]->speed_Label->setText("Normal");
		m_ReplayWnd[i].bPlay = FALSE;
		m_ReplayWnd[i].nStreamtype = -1;
		m_ReplayWnd[i].nSpeed = 0;


		if (i == m_nfousWnd)
		{
			//ui.btnPlay->setStyleSheet("border-image: url(:/res/SoftIcon/z_play.png);");
			ui.btnPlay->setIcon(QIcon(QPixmap(":/res/SoftIcon/z_play.png")));
		}

		m_ReplayWnd[i].nPlayHandle = -1;
	}
}
int CALLBACK videoPlayback::NetDataCallBack_V2(JVT_LONG lRealHandle, const PACKET_INFO_EX *pFrame, JVT_DWORD dwUser)
{
	BOOL bResult = TRUE;
	LONG lPort = dwUser;

	bResult = VideoPlayer_InputData(lPort, (unsigned char*)pFrame->pPacketBuffer, pFrame->dwPacketSize);

	return bResult;
}

int CALLBACK videoPlayback::ByTimeNetDataCallBack(JVT_LONG lRealHandle, long dwDataType, unsigned char *pBuffer,long lbufsize,JVT_DWORD dwUser)
{
	BOOL bResult = TRUE;
	LONG lPort = dwUser;
	if ( 0 == dwDataType )
	{
		if (lPort >= 0 )
		{
			return VideoPlayer_InputData(lPort,pBuffer,lbufsize);
		}	
	}
	return bResult;
}
LONG videoPlayback::PlayBackJLByName(int nIndex,int lChannel,char* szBeginTime,char* szEndTime)
{
	int i = nIndex;
	int nPort = PLAY_DEC_PORT_START + i;
	if (m_ReplayWnd[i].nDecHandle == -1)
	{
		BYTE byFileHeadBuf;
		if (VideoPlayer_OpenStream(nPort, &byFileHeadBuf, 1, SOURCE_BUF_MIN*50))
		{
			VideoPlayer_SetInfoFrameCallBack(nPort, InfoFramCallback,(DWORD)this);
			VideoPlayer_SetStreamOpenMode(nPort, STREAME_FILE);	
			BOOL bPlay = VideoPlayer_Play(nPort, (HWND)widgets[i]->m_displayScreen->winId());
			if (bPlay)
			{
				VideoPlayer_SetDisplayCallBack(nPort, pProc, (LONG)this);
				m_ReplayWnd[i].nDecHandle = nPort;
			}				
		}
		if (m_ReplayWnd[i].nDecHandle < 0)
		{
			m_ReplayWnd[i].bPlay = FALSE;
			VideoPlayer_CloseStream(nPort);
			myHelper::ShowMessageBoxWarning(QObject::tr("回放失败!"));
			return -1;
		}	
	}
	VIDEONET_FILE_DATA stVideoNetFileData;
	memset(&stVideoNetFileData,0,sizeof(stVideoNetFileData));
	strncpy(stVideoNetFileData.sFileName, m_ReplayWnd[i].szFileName, sizeof(stVideoNetFileData.sFileName) - 1);
	stVideoNetFileData.ch = lChannel - 1;

	sscanf(m_ReplayWnd[i].szBeginTime, "%04d-%02d-%02d %02d:%02d:%02d", &stVideoNetFileData.stBeginTime.year, &stVideoNetFileData.stBeginTime.month,
		&stVideoNetFileData.stBeginTime.day, &stVideoNetFileData.stBeginTime.hour, &stVideoNetFileData.stBeginTime.minute, &stVideoNetFileData.stBeginTime.second);

	sscanf(m_ReplayWnd[i].szEndTime, "%04d-%02d-%02d %02d:%02d:%02d", &stVideoNetFileData.stEndTime.year, &stVideoNetFileData.stEndTime.month,
		&stVideoNetFileData.stEndTime.day, &stVideoNetFileData.stEndTime.hour, &stVideoNetFileData.stEndTime.minute, &stVideoNetFileData.stEndTime.second);
	long lPlayHandle = VideoNet_PlayBackByName_V2(m_pChannelInfo->pDevObj->m_lUserLoginID, &stVideoNetFileData, NULL, NetDataCallBack_V2, nPort);
	
	if(lPlayHandle <= 0 )
	{
		DWORD dwError = VideoNet_GetLastError();
		VideoPlayer_CloseStream(m_ReplayWnd[i].nDecHandle);
		VideoPlayer_Stop(m_ReplayWnd[i].nDecHandle);
		m_ReplayWnd[i].nDecHandle = -1;
		//QMessageBox::information(this,QObject::tr("警告"),QObject::tr("回放失败"));
		myHelper::ShowMessageBoxWarning(QObject::tr("回放失败!"));
		return -1;
	}
	return lPlayHandle;	
}


long videoPlayback::PlayBackJLByTime(int nIndex)
{
	int i = nIndex;
	VIDEONET_FINDINFO info;

	memset(&info, 0, sizeof(info));
	info.nChannelN0 = m_ReplayWnd[i].pPlayInfo->Channel - 1;
	
	info.nFileType = SDK_RECORD_ALL;

	sscanf(m_ReplayWnd[i].szBeginTime, "%04d-%02d-%02d %02d:%02d:%02d", &info.startTime.dwYear, &info.startTime.dwMonth,
		&info.startTime.dwDay,&info.startTime.dwHour,&info.startTime.dwMinute,&info.startTime.dwSecond);

	sscanf(m_ReplayWnd[i].szEndTime, "%04d-%02d-%02d %02d:%02d:%02d", &info.endTime.dwYear, &info.endTime.dwMonth,
		&info.endTime.dwDay,&info.endTime.dwHour,&info.endTime.dwMinute,&info.endTime.dwSecond);

	int nPort = PLAY_DEC_PORT_START + i;
	if (m_ReplayWnd[i].nDecHandle == -1)
	{
		BYTE byFileHeadBuf;
		if (VideoPlayer_OpenStream(nPort, &byFileHeadBuf, 1, SOURCE_BUF_MIN*50))
		{	
			VideoPlayer_SetInfoFrameCallBack(nPort, InfoFramCallback,(DWORD)this);
			VideoPlayer_SetStreamOpenMode(nPort, STREAME_FILE);	
			BOOL bPlay = VideoPlayer_Play(nPort, (HWND)widgets[i]->m_displayScreen->winId());
			if (bPlay)
			{
				VideoPlayer_SetDisplayCallBack(nPort, pProc, (LONG)this);
				m_ReplayWnd[i].nDecHandle = nPort;
			}


		}	
	}
	if (m_ReplayWnd[i].nDecHandle < 0)
	{
		m_ReplayWnd[i].bPlay = FALSE;
		VideoPlayer_CloseStream(nPort);
		return -1;
	}		


	/*long lPlayHandle = VideoNet_PlayBackByTimeEx(m_lUserID, &info, 

		NULL, ByTimeNetDataCallBack, nPort);

	if(lPlayHandle <= 0 )
	{
		DWORD dwError = VideoNet_GetLastError();
		VideoPlayer_CloseStream(m_ReplayWnd[i].nDecHandle);
		VideoPlayer_Stop(m_ReplayWnd[i].nDecHandle);
		m_ReplayWnd[i].nDecHandle = -1;
		mlog(LOG_ERR, "VideoNet_PlayBackByTime failed  dwError = %d,channel = %d\n", dwError, m_lChannel);

		myHelper::ShowMessageBoxWarning(QObject::tr("回放失败!"));
		return -1;
	}*/
	return 0;
}
void videoPlayback::on_btnImport_clicked()
{
	QFileDialog fileDialog(this);
	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setWindowTitle("Open Files");
	
}
void videoPlayback::FindPictureFile(VIDEONET_FINDINFO* lpFindInfo)
{
	int lNumCount = 0;
	long lAllocSize = SERACH_MAX_FILE_NUM;
	SDK_VIDEONET_PICTURE_DATA *pResPictureData = new SDK_VIDEONET_PICTURE_DATA[SERACH_MAX_FILE_NUM];
	memset(pResPictureData, 0, sizeof(SDK_VIDEONET_PICTURE_DATA)* SERACH_MAX_FILE_NUM);

	SDK_PICTURE_FINDINFO picFindInfo;
	QString strLicense = "";
	memset(&picFindInfo, 0, sizeof(SDK_PICTURE_FINDINFO));
	picFindInfo.lChannel = lpFindInfo->nChannelN0;
	picFindInfo.byFileType = lpFindInfo->nFileType;

	picFindInfo.startTime.year = lpFindInfo->startTime.dwYear;
	picFindInfo.startTime.month = lpFindInfo->startTime.dwMonth;
	picFindInfo.startTime.day = lpFindInfo->startTime.dwDay;
	picFindInfo.startTime.hour = lpFindInfo->startTime.dwHour;
	picFindInfo.startTime.minute = lpFindInfo->startTime.dwMinute;
	picFindInfo.startTime.second = lpFindInfo->startTime.dwSecond;

	picFindInfo.endTime.year = lpFindInfo->endTime.dwYear;
	picFindInfo.endTime.month = lpFindInfo->endTime.dwMonth;
	picFindInfo.endTime.day = lpFindInfo->endTime.dwDay;
	picFindInfo.endTime.hour = lpFindInfo->endTime.dwHour;
	picFindInfo.endTime.minute = lpFindInfo->endTime.dwMinute;
	picFindInfo.endTime.second = lpFindInfo->endTime.dwSecond;
	//m_editLicenseNumber.GetWindowText(strLicense);
	picFindInfo.dwTrafficType = JVT_VCA_LICENSE_TYPE;
	//strcpy((char*)picFindInfo.sLicense, strLicense.GetBuffer());

	m_lFindHandle = VideoNet_FindPicture(m_pChannelInfo->pDevObj->m_lUserLoginID, &picFindInfo, pResPictureData, SERACH_MAX_FILE_NUM, &lNumCount, 10000);

	if (m_lFindHandle < 0)
	{

		if (NULL != pResPictureData)
		{
			delete[] pResPictureData;
			pResPictureData = NULL;
		}
		int err = VideoNet_GetLastError();
		QString strError = QString(QObject::tr("检索文件失败 %d!").arg(err));
		myHelper::ShowMessageBoxWarning(strError);
		return;
	}

	m_vtVideoNetFile.clear();

	for (int ix = 0; ix < lNumCount; ix++)
	{
		VIDEONET_FILE_DATA VideoFileData;
		memset(&VideoFileData, 0, sizeof(VIDEONET_FILE_DATA));
		VideoFileData.ch = pResPictureData[ix].nChannel;
		VideoFileData.size = pResPictureData[ix].dwFileSize;
		memcpy(&VideoFileData.sFileName, &pResPictureData[ix].sFileName, RECORDE_FILE_LENGTH);
		memcpy(&VideoFileData.stBeginTime, &pResPictureData[ix].netTime, sizeof(SDK_SYSTEM_TIME));
		memcpy(&VideoFileData.stEndTime, &pResPictureData[ix].netTime, sizeof(SDK_SYSTEM_TIME));
		m_vtVideoNetFile.push_back(VideoFileData);

	}

	//递归查询
	if (lNumCount == PLAYBACK_MAX_FILE_NUM)
	{
		memcpy(&picFindInfo.startTime, &pResPictureData[lNumCount - 1].netTime, sizeof(SDK_SYSTEM_TIME));

		BOOL bFind = TRUE;
		while (bFind)
		{
		
			memset(pResPictureData, 0, sizeof(SDK_VIDEONET_PICTURE_DATA)* SERACH_MAX_FILE_NUM);
			m_lFindHandle = VideoNet_FindPicture(m_pChannelInfo->pDevObj->m_lUserLoginID, &picFindInfo, pResPictureData, SERACH_MAX_FILE_NUM, &lNumCount, 10000);
			if (m_lFindHandle < 0)
			{
				bFind = FALSE;
			}

			for (int ix = 0; ix < lNumCount; ix++)
			{
				VIDEONET_FILE_DATA VideoFileData;
				memset(&VideoFileData, 0, sizeof(VIDEONET_FILE_DATA));
				VideoFileData.ch = pResPictureData[ix].nChannel;
				VideoFileData.size = pResPictureData[ix].dwFileSize;
				memcpy(&VideoFileData.sFileName, &pResPictureData[ix].sFileName, RECORDE_FILE_LENGTH);
				memcpy(&VideoFileData.stBeginTime, &pResPictureData[ix].netTime, sizeof(SDK_SYSTEM_TIME));
				memcpy(&VideoFileData.stEndTime, &pResPictureData[ix].netTime, sizeof(SDK_SYSTEM_TIME));
				m_vtVideoNetFile.push_back(VideoFileData);


			}

			if (lNumCount == PLAYBACK_MAX_FILE_NUM)
			{
				memcpy(&picFindInfo.startTime, &pResPictureData[lNumCount - 1].netTime, sizeof(SDK_SYSTEM_TIME));

			}
			else
			{
				bFind = FALSE;
			}

		}
	}


	if (NULL != pResPictureData)
	{
		delete[] pResPictureData;
		pResPictureData = NULL;
	}
	/*QString strLog;
	int lNumCount = 0;
	long lAllocSize = SERACH_MAX_FILE_NUM;
	SDK_VIDEONET_PICTURE_DATA *pResPictureData = new SDK_VIDEONET_PICTURE_DATA[SERACH_MAX_FILE_NUM];
	memset(pResPictureData, 0, sizeof(SDK_VIDEONET_PICTURE_DATA)* SERACH_MAX_FILE_NUM);

	
	SDK_PICTURE_FINDINFO picFindInfo;
	QString strLicense = "";
	memset(&picFindInfo, 0, sizeof(SDK_PICTURE_FINDINFO));
	picFindInfo.lChannel = lpFindInfo->nChannelN0;
	picFindInfo.byFileType = lpFindInfo->nFileType;
	picFindInfo.startTime.year = lpFindInfo->startTime.dwYear;
	picFindInfo.startTime.month = lpFindInfo->startTime.dwMonth;
	picFindInfo.startTime.day = lpFindInfo->startTime.dwDay;
	picFindInfo.startTime.hour = lpFindInfo->startTime.dwHour;
	picFindInfo.startTime.minute = lpFindInfo->startTime.dwMinute;
	picFindInfo.startTime.second = lpFindInfo->startTime.dwSecond;

	picFindInfo.endTime.year = lpFindInfo->endTime.dwYear;
	picFindInfo.endTime.month = lpFindInfo->endTime.dwMonth;
	picFindInfo.endTime.day = lpFindInfo->endTime.dwDay;
	picFindInfo.endTime.hour = lpFindInfo->endTime.dwHour;
	picFindInfo.endTime.minute = lpFindInfo->endTime.dwMinute;
	picFindInfo.endTime.second = lpFindInfo->endTime.dwSecond;
	//m_editLicenseNumber.GetWindowText(strLicense);
	picFindInfo.dwTrafficType = JVT_VCA_LICENSE_TYPE;
	m_lFindHandle = VideoNet_FindPicture(m_lUserID, &picFindInfo, pResPictureData, SERACH_MAX_FILE_NUM, &lNumCount, 10000);

	if (m_lFindHandle < 0)
	{
		if (NULL != pResPictureData)
		{
			delete[] pResPictureData;
			pResPictureData = NULL;
		}
		int err = VideoNet_GetLastError();
	
		 QString strError = QString(QObject::tr("检索文件失败 %d!").arg( err));
		 myHelper::ShowMessageBoxWarning(strError);
		return;
	}

	m_vtVideoNetFile.clear();

	for (int ix = 0; ix < lNumCount; ix++)
	{
		VIDEONET_FILE_DATA VideoFileData;
		memset(&VideoFileData, 0, sizeof(VIDEONET_FILE_DATA));
		VideoFileData.ch = pResPictureData[ix].nChannel;
		VideoFileData.size = pResPictureData[ix].dwFileSize;
		memcpy(&VideoFileData.sFileName, &pResPictureData[ix].sFileName, RECORDE_FILE_LENGTH);
		memcpy(&VideoFileData.stBeginTime, &pResPictureData[ix].netTime, sizeof(SDK_SYSTEM_TIME));
		memcpy(&VideoFileData.stEndTime, &pResPictureData[ix].netTime, sizeof(SDK_SYSTEM_TIME));
		m_vtVideoNetFile.push_back(VideoFileData);

	}

	//递归查询
	if (lNumCount == PLAYBACK_MAX_FILE_NUM)
	{
		memcpy(&picFindInfo.startTime, &pResPictureData[lNumCount - 1].netTime, sizeof(SDK_SYSTEM_TIME));

		BOOL bFind = TRUE;
		while (bFind)
		{
			memset(pResPictureData, 0, sizeof(SDK_VIDEONET_PICTURE_DATA)* SERACH_MAX_FILE_NUM);
			m_lFindHandle = VideoNet_FindPicture(m_lUserID, &picFindInfo, pResPictureData, SERACH_MAX_FILE_NUM, &lNumCount, 10000);
			if (m_lFindHandle < 0)
			{
				bFind = FALSE;
			}

			for (int ix = 0; ix < lNumCount; ix++)
			{
				VIDEONET_FILE_DATA VideoFileData;
				memset(&VideoFileData, 0, sizeof(VIDEONET_FILE_DATA));
				VideoFileData.ch = pResPictureData[ix].nChannel;
				VideoFileData.size = pResPictureData[ix].dwFileSize;
				memcpy(&VideoFileData.sFileName, &pResPictureData[ix].sFileName, RECORDE_FILE_LENGTH);
				memcpy(&VideoFileData.stBeginTime, &pResPictureData[ix].netTime, sizeof(SDK_SYSTEM_TIME));
				memcpy(&VideoFileData.stEndTime, &pResPictureData[ix].netTime, sizeof(SDK_SYSTEM_TIME));
				m_vtVideoNetFile.push_back(VideoFileData);

			}

			if (lNumCount == PLAYBACK_MAX_FILE_NUM)
			{
				memcpy(&picFindInfo.startTime, &pResPictureData[lNumCount - 1].netTime, sizeof(SDK_SYSTEM_TIME));

			}
			else
			{
				bFind = FALSE;
			}

		}
	}


	if (NULL != pResPictureData)
	{
		delete[] pResPictureData;
		pResPictureData = NULL;
	}*/
}

void videoPlayback::FindRecordFile(VIDEONET_FINDINFO* lpFindInfo)
{
	int lNumCount = 0;
	long lAllocSize = SERACH_MAX_FILE_NUM;
	VIDEONET_FILE_DATA *pResVideoFileData = new VIDEONET_FILE_DATA[SERACH_MAX_FILE_NUM];
	memset(pResVideoFileData, 0, sizeof(VIDEONET_FILE_DATA) * SERACH_MAX_FILE_NUM);
	m_lFindHandle = VideoNet_FindFile(m_pChannelInfo->pDevObj->m_lUserLoginID, lpFindInfo, pResVideoFileData, SERACH_MAX_FILE_NUM, &lNumCount, 10000);

	if (m_lFindHandle < 0)
	{
		
		if (NULL != pResVideoFileData)
		{
			delete [] pResVideoFileData;
			pResVideoFileData = NULL;
		}
		int err = VideoNet_GetLastError();
		
		myHelper::ShowMessageBoxWarning(QObject::tr("检索文件失败%1!").arg(err));
		return;
	}

	m_vtVideoNetFile.clear();

	for( int ix = 0;ix < lNumCount;ix++ )
	{
		VIDEONET_FILE_DATA VideoFileData;
		memset(&VideoFileData, 0, sizeof(VIDEONET_FILE_DATA));
		memcpy(&VideoFileData, pResVideoFileData + ix, sizeof(VIDEONET_FILE_DATA));
		m_vtVideoNetFile.push_back(VideoFileData);
	
	} 

	//递归查询
	if (lNumCount == PLAYBACK_MAX_FILE_NUM)
	{
		lpFindInfo->startTime.dwYear=pResVideoFileData[lNumCount-1].stEndTime.year;
		lpFindInfo->startTime.dwMonth=pResVideoFileData[lNumCount-1].stEndTime.month;
		lpFindInfo->startTime.dwDay=pResVideoFileData[lNumCount-1].stEndTime.day;
		lpFindInfo->startTime.dwHour=pResVideoFileData[lNumCount-1].stEndTime.hour;
		lpFindInfo->startTime.dwMinute=pResVideoFileData[lNumCount-1].stEndTime.minute;
		lpFindInfo->startTime.dwSecond=pResVideoFileData[lNumCount-1].stEndTime.second;
		//
		BOOL bFind = TRUE;
		while(bFind)
		{
			memset(pResVideoFileData, 0, sizeof(VIDEONET_FILE_DATA) * SERACH_MAX_FILE_NUM);
			m_lFindHandle = VideoNet_FindFile(m_pChannelInfo->pDevObj->m_lUserLoginID,lpFindInfo, pResVideoFileData,lAllocSize,&lNumCount);
			if (m_lFindHandle < 0)
			{
				bFind = FALSE;
			}				

			for( int ix = 0;ix < lNumCount;ix++ )
			{
				VIDEONET_FILE_DATA VideoFileData;
				memset(&VideoFileData, 0, sizeof(VIDEONET_FILE_DATA));
				memcpy(&VideoFileData, pResVideoFileData + ix, sizeof(VIDEONET_FILE_DATA));
				m_vtVideoNetFile.push_back(VideoFileData);
				
			} 

			if (lNumCount == PLAYBACK_MAX_FILE_NUM)
			{
				lpFindInfo->startTime.dwYear = pResVideoFileData[lNumCount-1].stEndTime.year;
				lpFindInfo->startTime.dwMonth = pResVideoFileData[lNumCount-1].stEndTime.month;
				lpFindInfo->startTime.dwDay = pResVideoFileData[lNumCount-1].stEndTime.day;
				lpFindInfo->startTime.dwHour = pResVideoFileData[lNumCount-1].stEndTime.hour;
				lpFindInfo->startTime.dwMinute = pResVideoFileData[lNumCount-1].stEndTime.minute;
				lpFindInfo->startTime.dwSecond = pResVideoFileData[lNumCount-1].stEndTime.second;
			}
			else
			{
				bFind = FALSE;
			}

		}
	}

	//m_videoFile.insert(make_pair(pChannelTmp->DevInfo->GetDevInfo()->szIpAddr + QString::number(pChannelTmp->Channel), m_vtVideoNetFile));
	m_videoFile[m_nfousWnd] = m_vtVideoNetFile;
	if (NULL != pResVideoFileData)
	{
		delete [] pResVideoFileData;
		pResVideoFileData = NULL;
	}
}

static bool isPlaylist(const QUrl &url) // Check for ".m3u" playlists.
{
	if (!url.isLocalFile())
		return false;
	const QFileInfo fileInfo(url.toLocalFile());
	return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
}

void videoPlayback::addToPlaylist(const QList<QUrl> urls)
{
	
}

void videoPlayback::jump(const QModelIndex &index)
{
	
}

void videoPlayback::playlistPositionChanged(int currentItem)
{
	qDebug()<<QObject::tr("播放第'%d'行").arg(currentItem);
}


void videoPlayback::on_btnStop_clicked()
{
	if (!m_ReplayWnd[m_nfousWnd].bPlay)
	{
		//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("当前窗口没有进行回放!错误"));
		myHelper::ShowMessageBoxWarning(QObject::tr("当前窗口没有进行回放"));
		return;
	}
	BOOL bControlAll = FALSE;

	for (int i = 0; i < REPLAY_MAX_NUM; i++)
	{
		if (!bControlAll)
			i = m_nfousWnd;
		StopPlay(i);
		//widgets[i]->ch_Label->setText("00:00:00/00:00:00");
		widgets[m_nfousWnd]->ip_Label->setText("IP:");
		widgets[m_nfousWnd]->ch_Label->setText("通道:");
		m_videoTimeLine_tmp->m_layerDrawWidget->onStopMoveNeedle();
		
		if (!bControlAll)
			break;
	}
	if (m_bSingleVideo)
		SetSingleVideoWndPos(m_nfousWnd);
}

void videoPlayback::SetSingleVideoWndPos(int nSelected)
{
	for (int i = 0; i < REPLAY_MAX_NUM; i++)
	{
		if (i == nSelected)
		{
			if (!m_ReplayWnd[i].bPlay)
				continue;
			if (m_ReplayWnd[i].nStreamtype == -1)
				continue;
		}
		else
		{
			m_ReplayWnd[i].bShow = false;
		}
	}
}
void videoPlayback::on_btnPre_clicked()
{
	if (!m_ReplayWnd[m_nfousWnd].bPlay)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("当前窗口没有进行回放"));
		return;
	}
	
	BOOL bControlAll = FALSE;

	int nSpeed;
	if (m_ReplayWnd[m_nfousWnd].nSpeed > 0)
		nSpeed = m_ReplayWnd[m_nfousWnd].nSpeed / 2;
	else if (m_ReplayWnd[m_nfousWnd].nSpeed == 0)
		nSpeed = -2;
	else
		nSpeed = m_ReplayWnd[m_nfousWnd].nSpeed * 2;

	for (int i = 0; i < REPLAY_MAX_NUM; i++)
	{
		if (!bControlAll)
			i = m_nfousWnd;

		if (m_ReplayWnd[i].nPlayHandle != -1)
		{
			if (m_ReplayWnd[i].nStreamtype == 1)
			{
				VideoPlayer_Slow(m_ReplayWnd[i].nDecHandle);
				m_ReplayWnd[i].nSpeed = nSpeed;
			}
			else
			{
				long nSpeedTemp = 0;

				if (nSpeed >= 0)
				{
					nSpeedTemp = 1;
					nSpeed = 0;
				}
				else
				{
					switch (nSpeed)
					{
					case -2:
						nSpeedTemp = 1;
						break;
					case -4:
						nSpeedTemp = 2;
						break;
					case -8:
						nSpeedTemp = 3;
						break;
					case -16:
						nSpeedTemp = 4;
						break;
					default:
						break;
					}

				}

				//OutputDebugStringLog("slow fast speed = %d,speed temp = %d\r\n",nSpeed,nSpeedTemp);

				mlog(LOG_NOTICE, "slow fast speed = %d,speed temp = %d", nSpeed, nSpeedTemp);
				VideoNet_PlayBackControl(m_ReplayWnd[i].nPlayHandle, SDK_PLAY_BACK_SLOW, nSpeedTemp);
				VideoPlayer_Slow(m_ReplayWnd[i].nDecHandle);

				m_ReplayWnd[i].nSpeed = nSpeed;
			}

		}
		if (!bControlAll)
		{
			break;
		}
	}
	ShowSpeed();
}

void videoPlayback::ShowSpeed()
{
	QString strSpeed;
	int nSpeed = m_ReplayWnd[m_nfousWnd].nSpeed;
	switch (nSpeed)
	{
	case -16:
		strSpeed = "1/16X";
		break;
	case -8:
		strSpeed = "1/8X";
		break;
	case -4:
		strSpeed = "1/4X";
		break;
	case -2:
		strSpeed = "1/2X";
		break;
	case 0:
		strSpeed = QObject::tr("正常速度");
		break;
	case 2:
		strSpeed = "2X";
		break;
	case 4:
		strSpeed = "4X";
		break;
	case 8:
		strSpeed = "8X";
		break;
	case 16:
		strSpeed = "16X";
		break;
	default:
		strSpeed = QObject::tr("正常速度");
		break;
	}
	//ui.label_Speed->setText(strSpeed);
	widgets[m_nfousWnd]->speed_Label->setText(strSpeed);
}
void videoPlayback::on_btnNext_clicked()
{
	if (!m_ReplayWnd[m_nfousWnd].bPlay || m_videoTimeLine_tmp == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("当前窗口没有进行回放"));
		return;
	}
	
	BOOL bControlAll = FALSE;

	int nSpeed;
	if (m_ReplayWnd[m_nfousWnd].nSpeed > 0)
		nSpeed = m_ReplayWnd[m_nfousWnd].nSpeed * 2;
	else if (m_ReplayWnd[m_nfousWnd].nSpeed == 0)
		nSpeed = 2;
	else
		nSpeed = m_ReplayWnd[m_nfousWnd].nSpeed / 2;

	for (int i = 0; i < REPLAY_MAX_NUM; i++)
	{
		if (!bControlAll)
			i = m_nfousWnd;

		if (m_ReplayWnd[i].nPlayHandle != -1)
		{
			if (m_ReplayWnd[i].nStreamtype == 1)
			{

				VideoPlayer_Fast(m_ReplayWnd[i].nDecHandle);
				m_ReplayWnd[i].nSpeed = nSpeed;
			}
			else
			{
				long nSpeedTemp = 0;

				if (nSpeed <= 0)
				{
					nSpeedTemp = 1;
					nSpeed = 0;
					m_videoTimeLine_tmp->m_layerDrawWidget->m_LayerSpeed = 1;
					
					
					//VideoNet_PlayBackControl(m_ReplayWnd[i].nPlayHandle, SDK_PLAY_BACK_PAUSE, nSpeedTemp);
				}
				if (nSpeed >= 2)
				{
					switch (nSpeed)
					{
					case 2:
						nSpeedTemp = 1;
						m_videoTimeLine_tmp->m_layerDrawWidget->m_LayerSpeed = 2;
						
						//m_videoTimeLine->m_layerDrawWidget->m_LayerSpeed = 2;
						break;
					case 4:
						nSpeedTemp = 2;
						m_videoTimeLine_tmp->m_layerDrawWidget->m_LayerSpeed = 4;
						//m_videoTimeLine->m_layerDrawWidget->m_LayerSpeed = 4;
						break;
					case 8:
						nSpeedTemp = 3;
						m_videoTimeLine_tmp->m_layerDrawWidget->m_LayerSpeed = 8;
						//m_videoTimeLine->m_layerDrawWidget->m_LayerSpeed = 8;
						break;
					case 16:
						nSpeedTemp = 4;
						m_videoTimeLine_tmp->m_layerDrawWidget->m_LayerSpeed = 16;
						//m_videoTimeLine->m_layerDrawWidget->m_LayerSpeed = 16;
						break;
					default:
						break;
					}

				}

				if (1 != nSpeedTemp)
				{
					mlog(LOG_NOTICE, "slow fast speed = %d,speed temp = %d", nSpeed, nSpeedTemp);
					//OutputDebugStringLog("slow fast speed = %d,temp speed = %d\r\n",nSpeed,nSpeedTemp);
					VideoNet_PlayBackControl(m_ReplayWnd[m_nfousWnd].nPlayHandle, SDK_PLAY_BACK_FAST, nSpeedTemp);
					VideoPlayer_Fast(m_ReplayWnd[m_nfousWnd].nDecHandle);
				}


				m_ReplayWnd[m_nfousWnd].nSpeed = nSpeed;
			}
		}
		if (!bControlAll)
		{
			break;
		}
	}
	ShowSpeed();

}


LONG videoPlayback::ShowPlayPos(int nIndex)
{
	QString sTime;
	DWORD dwTime = 0;
	DWORD dwPos = 0;
	int i = nIndex;
	long lOffStartSecond = 0;
	QString strBegingTime;
	if (m_ReplayWnd[i].nPlayHandle == -1)
		return -1;
	if (m_ReplayWnd[i].pPlayInfo == NULL)
	{
		return -1;
	}

	if (m_ReplayWnd[i].nStreamtype == 1) //本地文件
	{
		float fPos = VideoPlayer_GetPlayPos(m_ReplayWnd[i].nDecHandle) * 100;
		if (fPos > 99.9)
		{
			fPos = 100;
		}
		dwPos = (DWORD)fPos;
		dwTime = VideoPlayer_GetPlayedTimeEx(m_ReplayWnd[i].nDecHandle) / 1000;

	}
	else
	{
		dwTime = VideoPlayer_GetPlayedTime(m_ReplayWnd[i].nDecHandle);
		float flPos = VideoPlayer_GetPlayPos(m_ReplayWnd[i].nDecHandle);
		dwPos = (DWORD)flPos;

		
		strBegingTime = m_ReplayWnd[i].szBeginTime;
		QString strEndTime = m_ReplayWnd[i].szEndTime;

		QDateTime  timeBegin = QDateTime::fromString(strBegingTime, "yyyy-MM-dd hh:mm:ss");
		QDateTime  timeEnd = QDateTime::fromString(strEndTime, "yyyy-MM-dd hh:mm:ss");

		int elapsed = timeBegin.secsTo(timeEnd); 
		if (elapsed <= dwTime + 1 )
		{
			dwPos = 100;
		}

		lOffStartSecond = (strBegingTime.mid(17, 2)).toInt();
	}

	if (dwPos > 100)		//由于网络原因或DVR忙,回放异常终止
	{
		StopPlay(i);
		return 0;
	}
	else if (dwPos <= 100)
	{
		for (int i = 0; i < REPLAY_MAX_NUM;i++)
		{
			/*sTime = QString("%1:%2:%3/%4:%5:%6").arg(dwTime / 3600, 2, 10, QLatin1Char('0')).arg((dwTime % 3600) / 60, 2, 10, QLatin1Char('0')).arg(dwTime % 60, 2, 10, QLatin1Char('0')).arg(m_ReplayWnd[i].lTotalTime / 3600, 2, 10, QLatin1Char('0')).arg((m_ReplayWnd[i].lTotalTime % 3600) / 60, 2, 10, QLatin1Char('0'))
				.arg(m_ReplayWnd[i].lTotalTime % 60, 2, 10, QLatin1Char('0'));
			if (!m_ReplayWnd[i].bPause)
				widgets[i]->ch_Label->setText(sTime);*/

			if (dwPos == 100)
			{
				StopPlay(i);
				return 0;
			}
		}
			//m_myTinerShaft.SetPos(m_ReplayWnd[i].nMonth, m_ReplayWnd[i].nDay, m_ReplayWnd[i].nHour, m_ReplayWnd[i].nMinute, dwTime + lOffStartSecond);
		
	}
	return dwPos;
}

VOID videoPlayback::slotSelectChanged(int row ,int col)
{
	
	if (row < 0||col < 0 )
	{
		return;
	}

	QString beginTime = ui.tableWidget->item(row,1)->text();
	QString endTime = ui.tableWidget->item(row,2)->text();
	QString playFileName = ui.tableWidget->item(row,3)->text();
	QString strLicense = ui.tableWidget->item(row,5)->text();
	int startHour,startSec,endHour,endSec = 0;  
	getTimeInt(startHour,startSec, beginTime.right(8));
	getTimeInt(endHour, endSec, endTime.right(8));
	m_CurrData.videoStartTime = QTime(startHour, startSec);
	m_CurrData.videoEndTime = QTime(endHour, endSec);
	for (map<int, VideoTimeLine*>::iterator i = m_mapVideoLine.begin(); i != m_mapVideoLine.end(); i++)
	{
		if (i->first == m_nfousWnd)
		{
			m_videoTimeLine_tmp = i->second;
		}
	}

	if (m_videoTimeLine_tmp == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("时间轴数据为空"));
		return;
	}
	m_videoTimeLine_tmp->m_timeHeaderWidget->setDate(beginTime);

	
	//m_videoTimeLine->m_timeHeaderWidget->setDate(beginTime);
	AddRemoteFile(playFileName.toLocal8Bit().data(),beginTime.toLatin1().data(),endTime.toLatin1().data(),strLicense.toLatin1().data());

}

void videoPlayback::AddRemoteFile(const char* szFileName,const char* szBeginTime,const char* szEndTime, const char* szLicense)
{
	if (m_ReplayWnd[m_nfousWnd].bPlay)
	{
		StopPlay(m_nfousWnd);
	}
	
	if (m_ReplayWnd[m_nfousWnd].nStreamtype == 2)
	{
	
		m_ReplayWnd[m_nfousWnd].pPlayInfo = NULL;
		m_iSelectCount--;
	}

	memset(m_ReplayWnd[m_nfousWnd].szFileName, '\0', 512);
	strncpy(m_ReplayWnd[m_nfousWnd].szFileName, szFileName, 511);
	m_ReplayWnd[m_nfousWnd].nStreamtype = 0;
	if (m_lFindFileType == SDK_PIC_FACE || m_lFindFileType == SDK_PIC_CARNO
		|| m_lFindFileType == SDK_PIC_WIFI || m_lFindFileType == SDK_PIC_ALL)//如果查找类型为人脸，车牌，wifi信息则按时间回放
	{
		m_ReplayWnd[m_nfousWnd].nStreamtype = PLAYBACK_TYPE_PICTURE;
	}
	setWindowTitle(szFileName);

	int s;
	int nYear;
	sscanf(szBeginTime, "%04d-%02d-%02d %02d:%02d:%02d", &nYear, &m_ReplayWnd[m_nfousWnd].nMonth,
		&m_ReplayWnd[m_nfousWnd].nDay, &m_ReplayWnd[m_nfousWnd].nHour, &m_ReplayWnd[m_nfousWnd].nMinute, &s);
	strcpy(m_ReplayWnd[m_nfousWnd].szBeginTime, szBeginTime);
	strcpy(m_ReplayWnd[m_nfousWnd].szEndTime, szEndTime);
	memcpy(m_ReplayWnd[m_nfousWnd].szLicense, szLicense, MAX_LICENSE_LEN);
	for (map<int, TreeData_t*>::iterator mapChannel = m_mapChannelTmp.begin(); mapChannel != m_mapChannelTmp.end(); mapChannel++)
	{
		if (mapChannel->first == m_nfousWnd)
		{
			m_ReplayWnd[m_nfousWnd].pPlayInfo = mapChannel->second;
			m_lChannel = mapChannel->second->Channel;
			//m_pChannelInfo->DevInfo->m_lUserLoginID = mapChannel->second->DevInfo->m_lUserLoginID;
			m_ReplayWnd[m_nfousWnd].lTotalTime = StringToTime(szEndTime) - StringToTime(szBeginTime);
			widgets[m_nfousWnd]->ip_Label->setText(QString("IP:%1").arg(mapChannel->second->pDevObj->GetDevInfo()->szIpAddr));
			widgets[m_nfousWnd]->ch_Label->setText(QString("通道:%1").arg(mapChannel->second->Channel));
			on_btnPlay_clicked();
		}
	}

}

inline time_t StringToTime(const string& strTime)
{
	struct tm tmLocal;

	sscanf(strTime.c_str(), "%4d-%2d-%2d %2d:%2d:%2d",     
		&tmLocal.tm_year, 
		&tmLocal.tm_mon, 
		&tmLocal.tm_mday, 
		&tmLocal.tm_hour, 
		&tmLocal.tm_min,
		&tmLocal.tm_sec);

	tmLocal.tm_year -= 1900;
	tmLocal.tm_mon--;
	tmLocal.tm_isdst = -1;

	return mktime(&tmLocal);
}

LONG videoPlayback::PlayJLLocalFile(int nIndex)
{
	int i = nIndex;
	int nPort = PLAY_DEC_PORT_START +i;
	VideoPlayer_SetFileRefCallBack(nPort,NULL,(DWORD)this);
	if (VideoPlayer_OpenFile(nPort, m_ReplayWnd[i].szFileName))
	{
		VideoPlayer_SetInfoFrameCallBack(nPort, InfoFramCallback,(DWORD)this);

		m_ReplayWnd[i].lTotalTime = VideoPlayer_GetFileTime(nPort); // Total play time

		VideoPlayer_SetFileEndCallBack(nPort,SDKPlayFileEndCallback,(DWORD)this);

		VideoPlayer_RigisterDrawFun(nPort, PlaybackdrawOSDCall, (DWORD)this);	
		if (VideoPlayer_Play(nPort, (HWND)widgets[i]->m_displayScreen->winId()) == false)
		{
			//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("回放失败"));
			myHelper::ShowMessageBoxWarning(QObject::tr("回放失败"));
			return -1;
		}
	}
	else
	{
		int nErr = VideoPlayer_GetLastError(nPort);
		if (nErr == VIDEOPLAYER_CHECK_FILE_ERROR)
		{
			//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("检查文件失败"));
			myHelper::ShowMessageBoxWarning(QObject::tr("检查文件失败"));
		}
		else
		{
			//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("打开文件失败"));
			myHelper::ShowMessageBoxWarning(QObject::tr("打开文件失败"));
		}
		return -1;

	}

	m_ReplayWnd[i].nDecHandle = nPort;
	m_ReplayWnd[i].nPlayHandle = nPort;

	return m_ReplayWnd[i].nPlayHandle;
}

void CALLBACK videoPlayback::PlaybackdrawOSDCall(LONG nPort, HDC hDc, LONG nUser)
{

}

void CALLBACK videoPlayback::SDKPlayFileEndCallback(LONG nPort, LONG nUser)
{
	videoPlayback * p = (videoPlayback*)nUser;
	if (NULL == p)
	{
		return;
	}

	p->PlayEndCallback(nPort);
}

void videoPlayback::PlayEndCallback(int nPort)
{

}
void videoPlayback::ResetPlayData(int nIndex)
{
	for (int i = 0; i < REPLAY_MAX_NUM; i++)
	{
		if (nIndex != -1)
			i = nIndex;
		ReplayWnd[i] =  + i;
		m_ReplayWnd[i].bPlay = FALSE;
		m_ReplayWnd[i].bAudio = FALSE;
		m_ReplayWnd[i].bShow = TRUE;
		m_ReplayWnd[i].bPause = FALSE;
		m_ReplayWnd[i].pPlayInfo = NULL;
		m_ReplayWnd[i].nStreamtype = -1;
		m_ReplayWnd[i].nPlayHandle = -1;
		m_ReplayWnd[i].nSpeed = 0;
		m_ReplayWnd[i].lTotalTime = 0;
		m_ReplayWnd[i].nErrorCount = 0;
		m_ReplayWnd[i].nDecHandle = -1;
		if (nIndex != -1)
			return;
	}
}

void videoPlayback::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == FIND_TIMER)
	{
		if (m_lFindHandle < 0)
		{
			myHelper::ShowMessageBoxWarning("搜索录像失败");
			return;
		}
			
	
		killTimer(FIND_TIMER);
		handleTimeout();
	}
	else if (event->timerId() == PLAY_TIMER)
	{
		for (int i = 0; i < REPLAY_MAX_NUM; i++)
		{
			if (m_bSingleVideo)
			{
				if (i == m_nfousWnd)
					ShowPlayPos(i);
			}
			else
				ShowPlayPos(i);
		}
	
	}
	
}

void videoPlayback::on_btnShear_clicked()
{
	if (!m_ReplayWnd[m_nfousWnd].bPlay)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("当前窗口没有进行回放"));
		return;
	}

	char  szPicFilePath[1024];
	sprintf(szPicFilePath, "%s\\", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szPicPath);
	QDir dir;
	if (!dir.exists(szPicFilePath))
	{
		dir.mkpath(szPicFilePath);
	}

	BOOL bControlAll = FALSE;
	if (ui.m_chkReplay->isChecked() == true)
		bControlAll = TRUE;
	BOOL ret;
	int nCount = 0;
	QString str;

	for (int i = 0; i < REPLAY_MAX_NUM; i++)
	{
		if (!bControlAll)
			i = m_nfousWnd;
		if (m_ReplayWnd[i].nPlayHandle != -1)
		{
			QDateTime current_date_time = QDateTime::currentDateTime();
			QString strTime = current_date_time.toString("yyyyMMddhhmmss");
			sprintf(szPicFilePath, "%s\\%s_%d.bmp", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szPicPath, strTime.toLatin1().data(), i);

			if (m_ReplayWnd[i].nStreamtype == 1)
			{
				ret = VideoPlayer_CatchPic(m_ReplayWnd[i].nDecHandle, szPicFilePath, 0); //0:BMP 1:JPG
				//ret = DVR_NET_PlayBackCaptureFile(m_ReplayWnd[i].nPlayHandle,szPicFilePath);
			}
			else
			{
				ret = VideoPlayer_CatchPic(m_ReplayWnd[i].nDecHandle, szPicFilePath, 0); //0:BMP 1:JPG

			}
			if (ret)
			{
				nCount++;
				if (nCount != 1)
					str += ",";
				str += szPicFilePath;
			}
		}
		if (!bControlAll)
			break;
	}
	if (nCount == 0)
		myHelper::ShowMessageBoxWarning(QObject::tr("抓图失败"));
	else
	{
		myHelper::ShowMessageBoxInfo(QObject::tr("成功保存了'%1'个文件:'%2").arg(nCount).arg(str));
	}
}

void videoPlayback::on_btnVoice_clicked()
{
	if (!m_ReplayWnd[m_nfousWnd].bPlay)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("当前窗口没有进行回放"));
		return;
	}

	int i = m_nfousWnd;
	if (m_ReplayWnd[i].nPlayHandle != -1)
	{
		if (m_ReplayWnd[i].nStreamtype != 1)
		{
			if (m_bSound)
			{
				VideoPlayer_StopSoundShare(m_ReplayWnd[i].nDecHandle);
			}
			else
			{
				VideoPlayer_PlaySoundShare(m_ReplayWnd[i].nDecHandle);
			}

		}
	}
	if (!m_bSound)
		ui.btnVoice->setIcon(QIcon(QPixmap(":/res/images/voiceOpen.png")));
	else
		ui.btnVoice->setIcon(QIcon(QPixmap(":/res/images/voiceClose.png")));
		
	m_bSound = !m_bSound;
}


void videoPlayback::screen_full()
{
	ui.widge_Main->setWindowFlags(Qt::Window);
	ui.widge_Main->showFullScreen();
}
void videoPlayback::screen_normal()
{
	ui.widge_Main->setWindowFlags(Qt::SubWindow);
	ui.widge_Main->showNormal();
}

void videoPlayback::contextMenuEvent(QContextMenuEvent *event)
{
	QPoint point = event->pos(); //得到窗口坐标
	QTableWidgetItem *item = ui.tableWidget->itemAt(point);
	if (item != NULL)
	{
		qDebug() << "row" << item->row(); //当前行

		menu->clear(); //清除原有菜单
		menu->addAction(actionDownLoad);
		menu->addAction(actionPicSearch);
		menu->addAction(actionVideoSearch);
		menu->addSeparator();

		//菜单出现的位置为当前鼠标的位置
		menu->exec(QCursor::pos());
		event->accept();
	}
}




void videoPlayback::actionDownLoadClick()
{
	if (ui.tableWidget->rowCount() == 0)
	{
		//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("请选择要下载的文件"));
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择要下载的文件"));
		return;
	}
	char  szFilePath[1024];
	sprintf(szFilePath, "%s\\", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szDownPath);
	QDir dir;
	if (!dir.exists(szFilePath))
	{
		dir.mkpath(szFilePath);
	}
	sprintf(szFilePath, "%s\\", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szPicPath);
	m_strWifiPath = QCoreApplication::applicationDirPath() + "\\WifiInformation.ini";
	if (!dir.exists(szFilePath))
	{
		dir.mkpath(szFilePath);
	}
	if (!m_pDownLoadDlg)
	{
		m_pDownLoadDlg = new RePlayDownDlg();
	}
	m_pDownLoadDlg->m_pDevObj = m_pChannelInfo->pDevObj;
	m_pDownLoadDlg->m_lChannel = m_lChannel;
	if (m_lFindFileType == SDK_PIC_FACE || m_lFindFileType == SDK_PIC_CARNO)
	{
		m_pDownLoadDlg->m_bPicture = 2;
	}
	if (m_lFindFileType == SDK_PIC_WIFI)
	{
		ShellExecute(NULL, "open", m_strWifiPath.toLatin1().data(), NULL, NULL, SW_SHOWNORMAL);
		return;
	}
	
	m_pDownLoadDlg->show();
}

void videoPlayback::actionPicSearchClick()
{
	vector<int> vecItemIndex;
	QItemSelectionModel *selections = ui.tableWidget->selectionModel();//返回当前的选择模式  
	QModelIndexList selectedsList = selections->selectedIndexes();
	for (int i = 0; i < selectedsList.count(); i++)
	{
		vecItemIndex.push_back(selectedsList.at(i).row());
	}

	return;
}

void videoPlayback::actionVideoSearchClick()
{

}

void videoPlayback::SaveTableItem(vector<int> &vecItemIndex)
{
	QItemSelectionModel *selections = ui.tableWidget->selectionModel();//返回当前的选择模式  
	QModelIndexList selectedsList = selections->selectedIndexes();
	for (int i = 0; i < selectedsList.count(); i++)
	{
		vecItemIndex.push_back(selectedsList.at(i).row());
	}

	return;
}


void videoPlayback::on_btnExtend_clicked()
{
	static bool v_flag = false;
	if (!v_flag)
	{
		ui.widge_Search->setVisible(false);
		v_flag = true;
		ui.btnExtend->setIcon(QPixmap(":/res/SoftIcon/zou.png"));
	}
	else
	{
		ui.widge_Search->setVisible(true);

		v_flag = false;
		
		ui.btnExtend->setIcon(QPixmap(":/res/SoftIcon/you.png"));
		
	}
}


bool videoPlayback::eventFilter(QObject *watched, QEvent *event)
{
	OneVideo *widget = (OneVideo *)watched;
	if (event->type() == QEvent::MouseButtonDblClick) {
		
		if (!videoMax) {
			videoMax = true;
			hide_video_all();
			ui.gridLayout_main->addWidget(widget, 0, 0);
			widget->setVisible(true);
		}
		else {
			videoMax = false;
			show_video_all();
		}
	}
	else if (event->type() == QEvent::Enter)
	{
		widget->statusBar()->show();

	}
	else if (event->type() == QEvent::Leave)
	{
		widget->statusBar()->hide();

	}
	else if (event->type() == QEvent::MouseButtonPress) {
	
		
		if (qApp->mouseButtons() == Qt::RightButton) {
			videoMenu->exec(QCursor::pos());
		}
		else
		{
			HWND hWnd;
			hWnd = (HWND)qobject_cast<OneVideo *>(watched)->winId();
			for (int i = 0; i < videoCount; i++)
			{
				if ((HWND)widgets[i]->winId() == hWnd)
				{
					if (i == m_nfousWnd)
						return false;


					widgets[nNumTmp]->setStyleSheet(".OneVideo{ border:1px solid black}");
			
					m_nfousWnd = i;
					nNumTmp = m_nfousWnd;
					widgets[m_nfousWnd]->setStyleSheet(".OneVideo{ border:1px solid white}");
					
					
					
				}
			}

		}

	}

	return QWidget::eventFilter(watched, event);
}

void videoPlayback::OneVideoClicked()
{

	
	for (map<int, VideoTimeLine*>::iterator i = m_mapVideoLine.begin(); i != m_mapVideoLine.end(); i++)
	{
		if (i->first  == m_nfousWnd)
		{
			cleaLayout();
			ui.hLayout->addWidget(i->second);
			ui.hLayout->setMargin(0);
			m_videoTimeLine_tmp = i->second;
		}
		
	}


	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(0);
	for (map<int, vector<VIDEONET_FILE_DATA>>::iterator i = m_videoFile.begin(); i != m_videoFile.end(); i++)
	{
		if (i->first  == m_nfousWnd)
		{
			for (int ix = 0; ix < i->second.size(); ix++)
			{
				VIDEONET_FILE_DATA* pVideoNetFileData = &i->second[ix];
				ui.tableWidget->insertRow(ix);//增加一行
				QString startTime = QString("%1-%2-%3 %4:%5:%6").arg(pVideoNetFileData->stBeginTime.year, 4, 10, QLatin1Char('0')).arg(pVideoNetFileData->stBeginTime.month, 2, 10, QLatin1Char('0'))
					.arg(pVideoNetFileData->stBeginTime.day, 2, 10, QLatin1Char('0')).arg(pVideoNetFileData->stBeginTime.hour, 2, 10, QLatin1Char('0'))
					.arg(pVideoNetFileData->stBeginTime.minute, 2, 10, QLatin1Char('0')).arg(pVideoNetFileData->stBeginTime.second, 2, 10, QLatin1Char('0'));
				QString endTime = QString("%1-%2-%3 %4:%5:%6").arg(pVideoNetFileData->stEndTime.year, 4, 10, QLatin1Char('0')).arg(pVideoNetFileData->stEndTime.month, 2, 10, QLatin1Char('0'))
					.arg(pVideoNetFileData->stEndTime.day, 2, 10, QLatin1Char('0')).arg(pVideoNetFileData->stEndTime.hour, 2, 10, QLatin1Char('0'))
					.arg(pVideoNetFileData->stEndTime.minute, 2, 10, QLatin1Char('0')).arg(pVideoNetFileData->stEndTime.second, 2, 10, QLatin1Char('0'));

				QString strFileName = QString(QLatin1String(pVideoNetFileData->sFileName));
				QString strName;
				if (m_lFindFileType == SDK_PIC_FACE || m_lFindFileType == SDK_PIC_CARNO)
				{
					int nSeg = strFileName.lastIndexOf("+");
					if (nSeg > 0)
					{
						strFileName = strFileName.left(nSeg);
						strName = strFileName.mid(nSeg + 1);
					}

				}
				if (m_lFindFileType == SDK_PIC_WIFI)
				{
					int nSeg = strFileName.lastIndexOf("S:");
					if (nSeg > 0)
					{
						strFileName = strFileName.left(nSeg);
						strFileName.append(QObject::tr("强度"));

						strName = strFileName.mid(nSeg + 2);
					}
				}
				QString fileSize = QString::number(pVideoNetFileData->size) + "KB";

				m_Vcheck = new QTableWidgetItem();
				m_Vcheck->setCheckState(Qt::Unchecked);

				ui.tableWidget->setItem(ix, 0, m_Vcheck); //插入复选框
				ui.tableWidget->setItem(ix, 1, new QTableWidgetItem(startTime));

				ui.tableWidget->setItem(ix, 2, new QTableWidgetItem(endTime));

				ui.tableWidget->setItem(ix, 3, new QTableWidgetItem(strFileName));
				ui.tableWidget->setItem(ix, 4, new QTableWidgetItem(fileSize));
				ui.tableWidget->setItem(ix, 5, new QTableWidgetItem(strName));

				QTime t_beginTime = QTime::fromString(startTime.right(8), "hh:mm:ss");
				QTime t_endTime = QTime::fromString(endTime.right(8), "hh:mm:ss");
				QTime m_time;
				m_time.setHMS(0, 0, 0, 0);
				QString strTimeText = m_time.addSecs(t_beginTime.secsTo(t_endTime)).toString("hh:mm:ss");
				if (strTimeText.right(8).section(':', 0, 0).trimmed().toInt() > 0)
				{
					strTimeText = QObject::tr("%1时%2分%3秒").arg(strTimeText.right(8).section(':', 0, 0).trimmed().toInt())
						.arg(strTimeText.right(8).section(':', 1, 1).trimmed().toInt()).arg(strTimeText.right(8).section(':', 2, 2).trimmed().toInt());
				}
				else
				{
					if (strTimeText.right(8).section(':', 1, 1).trimmed().toInt() > 0)
					{
						strTimeText = QObject::tr("%1分%2秒").arg(strTimeText.right(8).section(':', 1, 1).trimmed().toInt())
							.arg(strTimeText.right(8).section(':', 2, 2).trimmed().toInt());
					}
					else
					{
						strTimeText = QObject::tr("%1秒").arg(strTimeText.right(8).section(':', 2, 2).trimmed().toInt());
					}
				}
				ui.tableWidget->setItem(ix, 6, new QTableWidgetItem(strTimeText));


			}
		}
		
	}
}
void videoPlayback::seeTimeline()
{
	for (int i = 0; i < itemCount; i++)
	{
		if (widgets[i]->ipAddr == NULL)
		{
			return;
		}
		if (m_pChannelInfo->pDevObj->GetDevInfo()->szIpAddr + QString::number(m_pChannelInfo->Channel) == widgets[i]->ipAddr)
		{
			cleaLayout();
			//ui.hLayout->addWidget(videoTimeLineList[i].m_videoTimeLine);
			ui.hLayout->setMargin(0);
		}
	}

}
void videoPlayback::TimeLineMove()
{

}

void videoPlayback::show_video_all()
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

void videoPlayback::show_video_4()
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

void videoPlayback::show_video_6()
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

void videoPlayback::show_video_8()
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

void videoPlayback::show_video_9()
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

void videoPlayback::show_video_16()
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


void videoPlayback::change_video(int index, int flag)
{
	int count = 0;
	int row = 0;
	int column = 0;

	for (int i = 0; i < videoCount; i++) {
		if (i >= index) {
			ui.gridLayout_main->addWidget(widgets.at(i), row, column);
			widgets.at(i)->setVisible(true);
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

void videoPlayback::change_video_4(int index)
{
	hide_video_all();
	change_video(index, 2);
}

void videoPlayback::change_video_6(int index)
{
	hide_video_all();
	if (index == 0) {
		ui.gridLayout_main->addWidget(widgets.at(0), 0, 0, 2, 2);
		ui.gridLayout_main->addWidget(widgets.at(1), 0, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(2), 1, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(3), 2, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(4), 2, 1, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(5), 2, 0, 1, 1);


		for (int i = 0; i < 6; i++) {
			widgets.at(i)->setVisible(true);

		}
	}
	else if (index == 5) {
		ui.gridLayout_main->addWidget(widgets.at(5), 0, 0, 2, 2);
		ui.gridLayout_main->addWidget(widgets.at(6), 0, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(7), 1, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(8), 2, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(9), 2, 1, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(10), 2, 0, 1, 1);


		for (int i = 5; i < 11; i++) {
			widgets.at(i)->setVisible(true);

		}
	}
	else if (index == 10) {
		ui.gridLayout_main->addWidget(widgets.at(10), 0, 0, 2, 2);
		ui.gridLayout_main->addWidget(widgets.at(11), 0, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(12), 1, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(13), 2, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(14), 2, 1, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(15), 2, 0, 1, 1);


		for (int i = 10; i < 16; i++) {
			widgets.at(i)->setVisible(true);

		}
	}
}

void videoPlayback::change_video_8(int index)
{
	hide_video_all();
	if (index == 0) {
		ui.gridLayout_main->addWidget(widgets.at(0), 0, 0, 3, 3);
		ui.gridLayout_main->addWidget(widgets.at(1), 0, 3, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(2), 1, 3, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(3), 2, 3, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(4), 3, 3, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(5), 3, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(6), 3, 1, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(7), 3, 0, 1, 1);


		for (int i = 0; i < 8; i++) {
			widgets.at(i)->setVisible(true);

		}
	}
	else if (index == 8) {
		ui.gridLayout_main->addWidget(widgets.at(8), 0, 0, 3, 3);
		ui.gridLayout_main->addWidget(widgets.at(9), 0, 3, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(10), 1, 3, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(11), 2, 3, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(12), 3, 3, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(13), 3, 2, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(14), 3, 1, 1, 1);
		ui.gridLayout_main->addWidget(widgets.at(15), 3, 0, 1, 1);


		for (int i = 8; i < 16; i++) {
			widgets.at(i)->setVisible(true);

		}
	}
}

void videoPlayback::change_video_9(int index)
{
	hide_video_all();
	change_video(index, 3);
}

void videoPlayback::change_video_16(int index)
{
	hide_video_all();
	change_video(index, 4);
}

void videoPlayback::on_btnDowned_clicked()
{
	actionDownLoadClick();
}

void videoPlayback::on_btnSearchPic_clicked()
{
	m_lFindFileType = SDK_FACE_QUERY_RECORD;
	FindFileByPicture(SDK_PIC_FACE);
}

void videoPlayback::FindFileByPicture(int nFindType)
{


	int nIndex = -1;
	QString strBeginTime ;
	QString strEndTime ;

	killTimer(FIND_TIMER);
	m_vtVideoNetFile.clear();

	int nSelect = 0;
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		if (g_pInstance->m_pVideoPlayBack->m_tableWidget->item(i, 0)->checkState())
		{
			nSelect++;
			strBeginTime = ui.tableWidget->item(i, 1)->text();
			strEndTime = ui.tableWidget->item(i, 2)->text();

			PICTURE_FINDINFO findinfo = { 0 };
			findinfo.lChannel = 1;
			//channel  掩码，支持组合通道，比如你想搜索2 3两通道，对应的二进制位110，转成十进制是6
			sscanf(strBeginTime.toLatin1().data(), "%04d-%02d-%02d %02d:%02d:%02d", &findinfo.startTime.year, &findinfo.startTime.month, &findinfo.startTime.day,
				&findinfo.startTime.hour, &findinfo.startTime.minute, &findinfo.startTime.second);
			sscanf(strEndTime.toLatin1().data(), "%04d-%02d-%02d %02d:%02d:%02d", &findinfo.endTime.year, &findinfo.endTime.month, &findinfo.endTime.day,
				&findinfo.endTime.hour, &findinfo.endTime.minute, &findinfo.endTime.second);
			findinfo.endTime.minute += 5;

			findinfo.byFileType = nFindType;
			findinfo.similarity = 80;
			if ((m_strPicPath.length() > 0) )
			{
				QDir dir;
				if(!dir.exists(m_strPicPath))
				{
					return;
				}
				sprintf(findinfo.filepath, m_strPicPath.toLocal8Bit().data());

				int maxcount = 5000;
				VIDEONET_PICTURE_DATA pdata = { 0 };
				m_lFindHandle = VideoNet_Query_Photo_Record(m_pChannelInfo->pDevObj->m_lUserLoginID, &findinfo, &pdata, maxcount, 20000);

				for (int i = 0; i < pdata.photonum; i++)
				{
					if (pdata.photodata[i].size > 0)
					{
						VIDEONET_FILE_DATA VideoFileData;
						memset(&VideoFileData, 0, sizeof(VIDEONET_FILE_DATA));
						memcpy(&VideoFileData.sFileName, &pdata.photodata[i].filepath, RECORDE_FILE_LENGTH);
						memcpy(&VideoFileData.stBeginTime, &pdata.photodata[i].capturetime, sizeof(SDK_SYSTEM_TIME));
						memcpy(&VideoFileData.stEndTime, &pdata.photodata[i].capturetime, sizeof(SDK_SYSTEM_TIME));
						VideoFileData.size = pdata.photodata[i].size / 1024;

						m_vtVideoNetFile.push_back(VideoFileData);
					}
				}

				clearCurrAge(ui.tableWidget);
				
				//开始检索
				FIND_TIMER = startTimer(100);
			}
			else
			{
				myHelper::ShowMessageBoxWarning(QObject::tr("请双击图片索引信息!"));
			}

			nSelect++;
		}
	}
	if (nSelect == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择要下载的文件!"));
		return;
	}
	
}

void videoPlayback::clearCurrAge(QTableWidget *m_table)
{
	int iLen = m_table->rowCount();
	for (int i = 0; i < iLen; i++)
	{
		m_table->removeRow(0);
	}
}
void videoPlayback::on_btnSearchVideo_clicked()
{
	m_lFindFileType = SDK_RECORD_ALL;
	FindFileByPicture(SDK_FACE_QUERY_RECORD);
}


void videoPlayback::on_btnSearchIP_clicked()
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

