#define  _CRT_SECURE_NO_WARNINGS
#include "OneVideoPro.h"
#include <QMutex>
#include <QDebug>
#include <QDateTime>
#include <QDir>
#include <io.h>
#include <tchar.h>
#include "myhelper.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsOpacityEffect>
#include "client.h"

QMutex onevideo_lock;
long g_nMinRecFreeSpace = 500 * (1 << 20); //500M
extern Client* g_pInstance;
OneVideoPro::OneVideoPro(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//this->setStyleSheet(".OneVideoPro{ border:1px solid black}");
	setStyleSheet(".OneVideoPro{background:transparent;border:2px solid black;}");
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	createTab();
	initAction();
	initForm();
	setCentralWidget(ui.label);
	//label = new QLabel();
	label = ui.label;
	ui.label->winId();
	isMax = false;
	GetDriverInfo();
	m_pDev = NULL;
	m_bTipBox = FALSE;

	m_vmtool = new VMTools(this);
	//this->setWindowFlags(Qt::SubWindow);
	connect(m_vmtool, SIGNAL(StopWatchEvent()), this, SLOT(StopWatch()));
	connect(m_vmtool, SIGNAL(screenshotEvent()), this, SLOT(cameraBtnSlot()));
	connect(m_vmtool, SIGNAL(videotapeEvent()), this, SLOT(recordBtnSlot()));
	connect(m_vmtool, SIGNAL(soundEvent()), this, SLOT(soundBtnSlot()));
	connect(m_vmtool, SIGNAL(talkEvent()), this, SLOT(talkBtnSlot()));
	m_vmtool->move(0,0);

}

OneVideoPro::~OneVideoPro()
{
}

void OneVideoPro::paintEvent(QPaintEvent *event)
{

}
void OneVideoPro::initForm()
{
	isPlay = false;

	memset(&m_dspWndinfo, 0, sizeof(DspWndInfoPro));
	m_dspWndinfo.TSStatus = 0;
	m_dspWndinfo.bSound = FALSE;
	m_dspWndinfo.bSpeak = FALSE;
	m_dspWndinfo.bRecord = FALSE;
	m_dspWndinfo.bLocRecord = FALSE;
	m_dspWndinfo.bBroadcast = FALSE;
	m_dspWndinfo.bManulRecord = FALSE;
	m_dspWndinfo.bVideo = FALSE;
	m_dspWndinfo.bTimeshift = FALSE;
	m_dspWndinfo.bPause = FALSE;
	m_dspWndinfo.bVideoStop = TRUE;
	m_dspWndinfo.bMainStream = TRUE;
	m_dspWndinfo.nDevId = -1;
	m_dspWndinfo.bVS = FALSE;
	m_dspWndinfo.bPS = FALSE;
	strcpy(m_dspWndinfo.szDevName, "");

	toolBarHide = true;
	m_bTalk = FALSE;
	m_bVideoThreadExit = TRUE;
	this->statusBar()->hide();
}

void OneVideoPro::initAction()
{
	
}
void OneVideoPro::createTab()
{	
	this->statusBar()->setSizeGripEnabled(false);//去掉状态栏右下角的三角

	this->statusBar()->setWindowOpacity(0.5);

	/*m_talkBtn = new ClickedLabel(this);
	m_talkBtn->setPixmap(QPixmap(":/res/SoftIcon/z_talk.png"));
	m_talkBtn->setScaledContents(true);
	m_talkBtn->setMaximumSize(20, 20);
	this->statusBar()->addPermanentWidget(m_talkBtn);
	connect(m_talkBtn, SIGNAL(on_clicked()), this, SLOT(talkBtnSlot()));*/
	QLabel * label = new QLabel;
	
	this->statusBar()->addPermanentWidget(label);
	label->setMinimumWidth(10);

	talkBtn = new QPushButton();
	talkBtn->setStyleSheet("QPushButton{border-radius:3px;color:#DCDCDC;padding:3px;margin:0px;background:none;border-style:none;}"
		"QPushButton:hover{color:#FFFFFF;margin:1px 1px 2px 1px;background-color:rgba(51, 127, 209, 230);}");
	talkBtn->setMaximumSize(25, 25);
	talkBtn->setIcon(QIcon(":/res/SoftIcon/talkClose.png"));
	talkBtn->setIconSize(QSize(25, 25));
	this->statusBar()->addPermanentWidget(talkBtn);
	connect(talkBtn, SIGNAL(clicked(bool)), SLOT(talkBtnSlot()));

	/*m_soundBtn = new ClickedLabel(this);
	m_soundBtn->setPixmap(QPixmap(":/res/SoftIcon/z_voice.png"));
	m_soundBtn->setScaledContents(true);
	m_soundBtn->setMaximumSize(20, 20);
	this->statusBar()->addPermanentWidget(m_soundBtn);
	connect(m_soundBtn, SIGNAL(on_clicked()), this, SLOT(soundBtnSlot()));*/
	soundBtn = new QPushButton();
	soundBtn->setStyleSheet("QPushButton{border-radius:3px;color:#DCDCDC;padding:3px;margin:0px;background:none;border-style:none;}"
		"QPushButton:hover{color:#FFFFFF;margin:1px 1px 2px 1px;background-color:rgba(51, 127, 209, 230);}");
	soundBtn->setMaximumSize(25, 25);
	soundBtn->setIcon(QIcon(":/res/SoftIcon/voiceClose.png"));
	soundBtn->setIconSize(QSize(25, 25));
	this->statusBar()->addPermanentWidget(soundBtn);
	connect(soundBtn, SIGNAL(clicked(bool)), SLOT(soundBtnSlot()));

	/*m_recordBtn = new ClickedLabel(this);
	m_recordBtn->setPixmap(QPixmap(":/res/SoftIcon/z_video.png"));
	m_recordBtn->setScaledContents(true);
	m_recordBtn->setMaximumSize(20, 20);
	this->statusBar()->addPermanentWidget(m_recordBtn);
	connect(m_recordBtn, SIGNAL(on_clicked()), this, SLOT(recordBtnSlot()));*/
	recordBtn = new QPushButton();
	recordBtn->setStyleSheet("QPushButton{border-radius:3px;color:#DCDCDC;padding:3px;margin:0px;background:none;border-style:none;}"
		"QPushButton:hover{color:#FFFFFF;margin:1px 1px 2px 1px;background-color:rgba(51, 127, 209, 230);}");
	recordBtn->setMaximumSize(25, 25);
	recordBtn->setIcon(QIcon(":/res/SoftIcon/VideoClose.png"));
	recordBtn->setIconSize(QSize(25, 25));
	this->statusBar()->addPermanentWidget(recordBtn);
	connect(recordBtn, SIGNAL(clicked(bool)), SLOT(recordBtnSlot()));

	/*m_cameraBtn = new ClickedLabel(this);
	m_cameraBtn->setPixmap(QPixmap(":/res/SoftIcon/z_camrea.png"));
	m_cameraBtn->setScaledContents(true);
	m_cameraBtn->setMaximumSize(20, 20);
	this->statusBar()->addPermanentWidget(m_cameraBtn);
	connect(m_cameraBtn, SIGNAL(on_clicked()), this, SLOT(cameraBtnSlot()));*/
	cameraBtn = new QPushButton(this);
	cameraBtn->setStyleSheet("QPushButton{border-radius:3px;color:#DCDCDC;padding:3px;margin:0px;background:none;border-style:none;}"
		"QPushButton:hover{color:#FFFFFF;margin:1px 1px 2px 1px;background-color:rgba(51, 127, 209, 230);}");
	cameraBtn->setMaximumSize(20, 20);
	cameraBtn->setIcon(QIcon(":/res/SoftIcon/Camera.png"));
	cameraBtn->setIconSize(QSize(25, 25));
	this->statusBar()->addPermanentWidget(cameraBtn);
	connect(cameraBtn, SIGNAL(clicked(bool)), SLOT(cameraBtnSlot()));

	/*m_maxBtn = new ClickedLabel(this);
	m_maxBtn->setPixmap(QPixmap(":/res/images/max.ico"));
	m_maxBtn->setScaledContents(true);
	m_maxBtn->setMaximumSize(20, 20);
	this->statusBar()->addPermanentWidget(m_maxBtn);
	connect(m_maxBtn, SIGNAL(on_clicked()), this, SLOT(maxBtnSlot()));*/
	/*maxButton = new QPushButton();
	maxButton->setMaximumSize(20, 20);
	maxButton->setIcon(QIcon(":/res/images/max.ico"));
	this->statusBar()->addPermanentWidget(maxButton);
	connect(maxButton, SIGNAL(clicked(bool)), SLOT(maxBtnSlot(bool)));*/

	ch_Label = new QLabel();
	this->statusBar()->addWidget(ch_Label);
	IPLabel = new QLabel();
	this->statusBar()->addWidget(IPLabel);

	this->statusBar()->setMaximumHeight(25);
}


int OneVideoPro::AddWatch(TreeData_t* pDev, int nPatrolId, BOOL bTipBox, int nWndNum )
{
	if (pDev == NULL)
		return  -1;
	
	if (m_dspWndinfo.bVideo)
	{
		StopWatch();
	}
	if (m_dspWndinfo.bVideo == 2)
	{
		return -1;
	}
	//轮巡屏蔽，暂未做此功能
	//BOOL bThreadExit;
	//onevideo_lock.lock();
	//bThreadExit = m_bVideoThreadExit;
	//onevideo_lock.unlock();
	//if (!bThreadExit)
	//{
	//	myHelper::ShowMessageBoxWarning(QObject::tr("视频轮询正在结束，请稍后再试!"));
	//	return -1;
	//}
	//if (!m_dspWndinfo.bVS)
	//{
	//	setWindowTitle("connect ...");
	//}
	if (pDev->pDevObj->m_pDevInfo->nType == SDK_DEV_TYPE_NVR)
	{
		TabChannelInfo_t* pChennel = pDev->pDevObj->GetChannelInfo(pDev->Channel);
		if (pChennel == NULL)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("AddWatch 获取通道信息出错 id:%1 channel:%2!\n").arg(pDev->pDevObj->GetDevInfo()->nDevId).arg(pDev->Channel));
			return -1;
		}
		strcpy(m_dspWndinfo.szDevName, pChennel->szChannelName);
	}
	else
	{
		strcpy(m_dspWndinfo.szDevName, pDev->pDevObj->m_pDevInfo->szDevName);
	}
	m_dspWndinfo.nDevId = pDev->pDevObj->m_pDevInfo->nDevId;
	m_dspWndinfo.bVideoStop = false;

	m_pDevTemp = pDev;
	m_bTipBox = bTipBox;

	DWORD dwThreadId = 0;
	HANDLE hThread = NULL;

	m_dspWndinfo.bVideo = 2;		//正在打开视频

	StartWatch();

	return 0;
}

void OneVideoPro::StartWatch()
{
	int nStream = m_dspWndinfo.bMainStream ? DEVICE_MAIN_STREAM : DEVICE_SUB_STREAM;

	if (!m_pDevTemp)
	{
		return;
	}

	if (m_pDevTemp->pDevObj->OpenChannel(m_pDevTemp->Channel, nStream, (HWND)ui.label->winId(), m_nWndNum) < 0)
	{
		if (m_bTipBox)
		{

			//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("打开视频失败"));
			CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
			custevent->setId(1);
			QApplication::postEvent(this, custevent);
		}

		QString strWndNum;
		strWndNum = QString("#%1").arg(m_ndspIndex + 1);
		m_dspWndinfo.bVideo = FALSE;

		return;
	}
	CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
	custevent->setId(2);
	QApplication::postEvent(this, custevent);
	m_vmtool->m_labelIP->setText(QString("%1").arg(m_pDevTemp->pDevObj->GetDevInfo()->szIpAddr));
	m_dspWndinfo.bVideo = true;
	m_pDev = m_pDevTemp;
	onevideo_lock.lock();
	g_nRealPlayCount++;
	onevideo_lock.unlock();
}

void OneVideoPro::StopWatch()
{
	if (m_pDev == NULL)
		return;

	if (!m_dspWndinfo.bVideo)
		return;

	QString  strWndNum;

	//if (m_dspWndinfo.bManulRecord)
	//	ManulRecord();
	if (m_dspWndinfo.bSound)
		OpenSound();
	if (m_dspWndinfo.bLocRecord)
		LocalRecord();
	Speak(FALSE);
	
	m_bAudioEnable = TRUE;
	if (m_pDev != NULL)
	{
		m_pDev->pDevObj->CloseChannel((HWND)ui.label->winId());
	}
	m_dspWndinfo.bVideo = FALSE;
	OnRecordStatus(FALSE);
	m_dspWndinfo.bSound = FALSE;
	m_dspWndinfo.bSpeak = FALSE;
	m_dspWndinfo.bRecord = FALSE;
	m_dspWndinfo.bBroadcast = FALSE;
	m_dspWndinfo.bVideo = FALSE;
	m_dspWndinfo.bVideoStop = TRUE;
	m_szShowMsg = "";
	m_dspWndinfo.nDevId = -1;

	ui.label->setUpdatesEnabled(true);
	onevideo_lock.lock();
	g_nRealPlayCount--;
	onevideo_lock.unlock();

	//m_pDev = NULL;
	strWndNum = QString("#%1").arg(m_ndspIndex + 1);
	m_vmtool->m_labelIP->setText("");
}


void OneVideoPro::ManulRecord()
{
	//if (m_pDev == NULL)
	//	return;

	//int nChannel = m_pDev->pDevObj->GetPlayChannel((HWND)ui.label->winId());
	//if (m_dspWndinfo.bManulRecord)
	//{
	//	if (m_pDev->pDevObj->ManulRecord((HWND)ui.label->winId(), nChannel, TRUE) == 0)
	//	{
	//		m_dspWndinfo.bManulRecord = FALSE;
	//	}
	//}
	//else
	//{
	//	if (m_pDev->pDevObj->ManulRecord((HWND)ui.label->winId(), nChannel, FALSE) == 0)
	//	{
	//		m_dspWndinfo.bManulRecord = TRUE;
	//	}
	//	else
	//	{
	//		//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("远程手动录像失败"));
	//		myHelper::ShowMessageBoxWarning(QObject::tr("远程手动录像失败!"));
	//		
	//	}
	//}
}

int OneVideoPro::OpenSound()
{
	if (m_pDev == NULL)
		return -1;

	if (m_dspWndinfo.bSound)
	{
		if (m_pDev->pDevObj->EnableAudio((HWND)ui.label->winId(), FALSE) == 0)
		{
			m_dspWndinfo.bSound = FALSE;
			m_vmtool->m_sound->setIcon(QIcon(":/res/SoftIcon/voiceClose.png"));
			return 0;
		}
	}
	else
	{
		if (m_pDev->pDevObj->EnableAudio((HWND)ui.label->winId(), TRUE) == 0)
		{
			m_dspWndinfo.bSound = TRUE;
			m_vmtool->m_sound->setIcon(QIcon(":/res/SoftIcon/voiceOpen.png"));
			return 1;
		}
	}
	return 0;
}

int OneVideoPro::LocalRecord()
{
	if (m_pDev == NULL)
		return -1;

	static char  szRecFilePath[1024];

	if (m_dspWndinfo.bLocRecord)
	{
		if (m_pDev->pDevObj->LocalRecord((HWND)ui.label->winId(), szRecFilePath, TRUE) == 0)
		{
			killTimer(RECORD_TIMER);
			killTimer(CHKDISK_TIMER);

			m_dspWndinfo.bLocRecord = FALSE;
			m_vmtool->m_record->setIcon(QIcon(":/res/SoftIcon/VideoClose.png"));
			return 0;
		}
	}
	else
	{
		
		int i = 0;
		QString sDir = GetAvailDisk(g_nMinRecFreeSpace);
		if (g_pInstance->m_pDlgSystemSet->m_ClientCfg.nCycleRecord)
		{
		while (sDir.isEmpty())
		{
			clearFiles(sDir);
			sDir = GetAvailDisk(g_nMinRecFreeSpace);
		if (i++ > 10) break;
		}
		}

		if (!sDir.isEmpty())
		{
		m_sCurRecDisk = sDir;
		sDir += "JVTSMPRecord";
		QDir dir;
		if (!dir.exists(sDir))
		{
			dir.mkpath(sDir);
		}
		QString sfile;
		QDateTime current_time = QDateTime::currentDateTime();
		QString str;
		str = current_time.toString("yyyyMMddhhmmss");
		QString szFile(m_dspWndinfo.szDevName);
		QString szFileType;

		szFileType = "h264";

		sprintf(szRecFilePath, "%s\\%s_%s.%s", sDir.toLatin1().data(), szFile.toLatin1().data(), str.toLatin1().data(), szFileType.toLatin1().data());
		//int i = 0;
		//while ((_access(szRecFilePath, 0)) != -1 && ++i < 100)
		//{//存在同名文件，不做覆盖，修改文件名，
		//	sprintf(szRecFilePath, "%s\\%s_%s_%d.%s", sDir.toLatin1().data(), szFile.toLatin1().data(), str.toLatin1().data(), i, szFileType.toLatin1().data());
		//}
		//if (i >= 100)
		//{
		//	sprintf(szRecFilePath, "%s\\%s_%s_temp.%s", sDir.toLatin1().data(), szFile.toLatin1().data(), str.toLatin1().data(), i, szFileType.toLatin1().data());
		//}

		if (m_pDev->pDevObj->LocalRecord((HWND)ui.label->winId(), szRecFilePath, FALSE) == 0)
		{
			m_dspWndinfo.bLocRecord = TRUE;
			m_vmtool->m_record->setIcon(QIcon(":/res/SoftIcon/VideoOpen.png"));
			RECORD_TIMER = g_pInstance->m_pDlgSystemSet->m_ClientCfg.nFileTimeLen * 1000;
			CHKDISK_TIMER = 15000;
			return 1;
		}
		else
		{
			//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("本地录像失败"));
			myHelper::ShowMessageBoxWarning(QObject::tr("本地录像失败!"));

		}
		}
		else
		{
			//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("本地录像失败"));
			myHelper::ShowMessageBoxWarning(QObject::tr("本地录像失败!"));
		}

		
		
	}

	return 0;
}

QString OneVideoPro::GetAvailDisk(unsigned long nMinAvailBytes)
{
	int i;
	ULARGE_INTEGER FreeSpace, CallerSpace, TotalSpace;
	QString root;
	QString sLogicalDrive;

	for (i = g_pInstance->m_pDlgSystemSet->m_ClientCfg.nBeginDriver; i <= g_pInstance->m_pDlgSystemSet->m_ClientCfg.nEndDriver; i++)
	{
		root = QString("%1:\\").arg(g_strDriverName[i]);	//从录像起始驱动器开始	
		if (GetDiskFreeSpaceEx(root.toLatin1().data(), &CallerSpace, &TotalSpace, &FreeSpace) && CallerSpace.QuadPart > nMinAvailBytes)
		{
			sLogicalDrive = root;
			break;
		}
	}

	return sLogicalDrive;
}

bool OneVideoPro::GetDriverInfo()
{
	DWORD dw = GetLogicalDriveStrings(0, NULL);
	LPTSTR all_drivers = new char[dw];
	memset(all_drivers, 0, dw);
	::GetLogicalDriveStrings(dw, all_drivers);

	LPTSTR p_all_drivers = all_drivers;
	char tmp[26] = { 0 };
	DWORD num = 0;
	while (p_all_drivers[0] != 0)
	{
		tmp[num++] = *p_all_drivers;
		p_all_drivers = _tcschr(p_all_drivers, 0) + 1;  //定位到下一个盘符    
	}

	//volume information
	TCHAR lpVolumeNameBuffer[200];
	DWORD dwVolumeSerialNumber, dwMaxComLength;
	DWORD dwFileSystemFlags;
	TCHAR lpFileSystemNameBuffer[50];

	DWORD HardNum = 0;
	for (DWORD i = 0; i < num; i++)
	{
		QString csRootPath;
		csRootPath = QString("%1%2").arg( tmp[i]).arg(":\\");
		if (GetDriveType(csRootPath.toLatin1().data()) == DRIVE_FIXED)  //只要硬盘
		{
			if (GetVolumeInformation(csRootPath.toLatin1().data(), lpVolumeNameBuffer, sizeof(lpVolumeNameBuffer), &dwVolumeSerialNumber,
				&dwMaxComLength, &dwFileSystemFlags, lpFileSystemNameBuffer, sizeof(lpFileSystemNameBuffer)))
			{
				g_strDriverName[HardNum++] = QString("%1").arg(tmp[i]);
			}
		}
	}

	g_nDriverNum = HardNum;
	delete[] all_drivers;
	return TRUE;
}
int OneVideoPro::Speak(BOOL bStart)
{
	if (m_pDev == NULL)
		return 0;

	if (!bStart)
	{
		if (m_dspWndinfo.bSpeak)
		{
			if (m_pDev->pDevObj->Speak(m_hWnd, bStart) == 0)
			{
				m_dspWndinfo.bSpeak = FALSE;
				m_vmtool->m_talk->setIcon(QIcon(":/res/SoftIcon/talkClose.png"));

			}
		}
	}
	else
	{
		if (!m_dspWndinfo.bSpeak)
		{
			if (m_pDev->pDevObj->Speak(m_hWnd, bStart) == 0)
			{
				m_dspWndinfo.bSpeak = TRUE;
				m_vmtool->m_talk->setIcon(QIcon(":/res/SoftIcon/talkOpen.png"));
			}
		}
	}

	return 0;
}

void OneVideoPro::OnRecordStatus(int result)
{
	if (result == 1)
	{
		m_dspWndinfo.bRecord = TRUE;
	}
	else
	{
		m_dspWndinfo.bRecord = FALSE;
	}
}

void OneVideoPro::talkBtnSlot()
{
	if (m_dspWndinfo.bVideo)
		return;
	if (m_dspWndinfo.bBroadcast)
		return;
	Speak(!m_bTalk);
	m_bTalk = !m_bTalk;
}

void OneVideoPro::maxBtnSlot()
{
	if (!isMax)
	{
		//maxButton->setCheckable(true);
		//fullScreenBtn->setToolTip("最小化");
		//parentWinPtr = this->parentWidget();
		//this->winRect = this->geometry();
		//this->setParent(NULL);
		// this->move(QApplication::desktop()->width()/2-this->width()/2,
		//            QApplication::desktop()->height()/2-this->height()/2);
		//this->showFullScreen();
		//setWindowFlags(Qt::Window);
		//showFullScreen();
		isMax = true;
	}
	else
	{
		//maxButton->setCheckable(false);
		//fullScreenBtn->setToolTip("全屏");
		//this->setParent(parentWinPtr);
		//this->setGeometry(this->winRect);
		//this->showNormal();
		//setWindowFlags(Qt::SubWindow);
		//showNormal();
		isMax = false;
	}
}

void OneVideoPro::soundBtnSlot()
{
	OpenSound();

}

void OneVideoPro::recordBtnSlot()
{
	LocalRecord();
}

void OneVideoPro::cameraBtnSlot()
{
	CapturePic();
}
void OneVideoPro::isHideToolBar()
{
	if (toolBarHide = !toolBarHide)
	{
		this->statusBar()->hide();
		toolBarHide = true;
	}
	else
	{
		this->statusBar()->show();
		toolBarHide = false;
	}

}

void OneVideoPro::OnMenuStreamMain()
{
	if (m_pDev == NULL)
		return;

	if (m_dspWndinfo.bMainStream)
		return;
	m_pDev->pDevObj->ChangeChannelStream((HWND)ui.label->winId(), DEVICE_MAIN_STREAM);
	m_dspWndinfo.bMainStream = TRUE;
}

void OneVideoPro::OnMenuStreamSub()
{
	if (m_pDev == NULL)
		return;

	if (!m_dspWndinfo.bMainStream)
		return;
	m_pDev->pDevObj->ChangeChannelStream((HWND)ui.label->winId(), DEVICE_SUB_STREAM);
	m_dspWndinfo.bMainStream = FALSE;

}

void OneVideoPro::CapturePic()
{
	if (m_pDev == NULL)
		return;

	TCHAR  szPicFilePath[1024];
	QDateTime current_time = QDateTime::currentDateTime();
	QString str;
	str = current_time.toString("yyyyMMddhhmmss");
	
	QString szFile(m_dspWndinfo.szDevName);

	sprintf(szPicFilePath, "%s\\", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szPicPath);
	QDir dir;
	if (!dir.exists(szPicFilePath))
	{
		dir.mkpath(szPicFilePath);
	}
	sprintf(szPicFilePath,"%s\\%s_%s.bmp", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szPicPath, szFile.toLatin1().data(), str.toLatin1().data());
	if (m_pDev->pDevObj->CapturePic((HWND)ui.label->winId(), szPicFilePath) < 0)
		//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("抓图失败"));
		myHelper::ShowMessageBoxWarning(QObject::tr("抓图失败!"));
	else
	{
		//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("抓图成功，文件路径:%1").arg(szPicFilePath));
		myHelper::ShowMessageBoxInfo(QObject::tr("抓图成功，文件路径:%1").arg(szPicFilePath));
	}
}

void OneVideoPro::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == RECORD_TIMER)
	{
		//还录像文件
		if (m_dspWndinfo.bLocRecord)
		{
			LocalRecord();//停
			LocalRecord();//重新开始
		}
		
	}
	else if (event->timerId() == CHKDISK_TIMER)
	{
		if (m_dspWndinfo.bLocRecord)
		{
			//检查当前录像磁盘的剩余空间
			ULARGE_INTEGER a, b, c;
			if (GetDiskFreeSpaceEx(m_sCurRecDisk.toLatin1().data(), &a, &b, &c) && a.QuadPart > g_nMinRecFreeSpace)
			{
			}
			else
			{
				//换盘
				LocalRecord(); //停
				LocalRecord();//重新开始
			}
		}
	}
}

void OneVideoPro::clearFiles(const QString &folderFullPath)
{
	QDir dir(folderFullPath);
	dir.setFilter(QDir::Files);
	int fileCount = dir.count();
	for (int i = 0; i < fileCount; i++)
		dir.remove(dir[i]);
}

int OneVideoPro::BroadCast(BOOL bStart)
{
	if (m_pDev == NULL)
		return 0;

	if (!bStart)
	{
		if (m_dspWndinfo.bSpeak)
		{
			if (m_pDev->pDevObj->Speak(m_hWnd, bStart) == 0)
			{
				m_dspWndinfo.bSpeak = FALSE;
				
			}
		}
	}
	else
	{
		if (!m_dspWndinfo.bSpeak)
		{
			if (m_pDev->pDevObj->Speak(m_hWnd, bStart) == 0)
			{
				m_dspWndinfo.bSpeak = TRUE;
				
			}
		}
	}

	return 0;
}

bool OneVideoPro::event(QEvent *e)
{
	CompareEvent *event = static_cast<CompareEvent *>(e);

	if (e->type() == static_cast <QEvent::Type>(CET_MESSAGEBOX))
	{
		int messId = event->getId();
		if (messId == 1)
		{
			m_pDevTemp->pDevObj->GetLoginID();
			//myHelper::ShowMessageBoxWarning(QObject::tr("打开视频失败"));
			ui.label->setUpdatesEnabled(true);
		}
		else
		{
			ui.label->setUpdatesEnabled(false);
		}
		
	}
	return QWidget::event(event);
}

void OneVideoPro::resizeEvent(QResizeEvent* size)
{
	m_vmtool->resize(this->geometry().width(), 18);
}

void OneVideoPro::OnReconnectNotifyMsg(long lType)
{
	if (RECONNECT_NOTIFY_LOCALRECORD == lType)
	{
		//重连
		LocalRecord(); //停
		LocalRecord();//重新开始
	}
}