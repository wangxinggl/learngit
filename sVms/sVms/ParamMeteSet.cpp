#define  _CRT_SECURE_NO_WARNINGS
#include "ParamMeteSet.h"


ParamMeteSet::ParamMeteSet(QWidget *parent)
	: QDialog(parent)
	, m_pDevObj(NULL)
{
	ui.setupUi(this);
	init();
	
	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setStyleSheet(".ParamMeteSet{border:2px solid black;}");
}

ParamMeteSet::~ParamMeteSet()
{
}

void ParamMeteSet::init()
{
	m_nFacePicQual = 0;
	m_nFaceSize = 0;
	m_nExtendVaule = 0;
	m_nFastSanpFramCount = 0;
	m_tStartTime1 = QTime::currentTime();
	m_tStartTime2 = QTime::currentTime();
	m_tEndTime1 = QTime::currentTime();
	m_tEndTime2 = QTime::currentTime();
	m_nIntervalTime = 0;
	m_sCustomName = "";
	m_sServerIP = "";
	m_nServerPort = 0;
	m_nIntervalFrame = 0;
	m_nSnapCount = 0;
	m_bEnablUse = false;
	m_bEnableTime1 = false;
	m_bEnableTime2 = false;
	m_nIntervalFrameGate = 0;

	ui.timeEdit_Start1->setDisplayFormat("H:mm");
	ui.timeEdit_End1->setDisplayFormat("H:mm");
	ui.timeEdit_Start1->setTime(QTime(0,0));
	ui.timeEdit_End1->setTime(QTime(23, 59));

	ui.timeEdit_Start2->setDisplayFormat("H:mm");
	ui.timeEdit_End2->setDisplayFormat("H:mm");
	ui.timeEdit_Start2->setTime(QTime(0, 0));
	ui.timeEdit_End2->setTime(QTime(23, 59));

	ui.comboBox_SNAPMODE->addItem(QObject::tr("离开后抓拍(距离优先)"));
	ui.comboBox_SNAPMODE->addItem(QObject::tr("快速抓拍"));
	ui.comboBox_SNAPMODE->addItem(QObject::tr("间隔抓拍(以秒为单位)"));
	ui.comboBox_SNAPMODE->addItem(QObject::tr("间隔抓拍(以帧为单位)"));
	ui.comboBox_SNAPMODE->addItem(QObject::tr("单人模式"));
	ui.comboBox_SNAPMODE->addItem(QObject::tr("离开后抓拍(质量优先)"));
	ui.comboBox_SNAPMODE->addItem(QObject::tr("快速+离开后抓拍"));
	ui.comboBox_SNAPMODE->setCurrentIndex(0);

	int i = 0;
	for (i = 0; i <= 10; i++)
	{
		QString str;
		str = QString("%1").arg(i);
		ui.comboBox_SENSITIVITY->addItem(str);
	}
	ui.comboBox_SENSITIVITY->setCurrentIndex(0);

	ui.comboBox_MAXSNAPNUM->addItem("1");
	ui.comboBox_MAXSNAPNUM->addItem("2");
	ui.comboBox_MAXSNAPNUM->addItem("3");
	ui.comboBox_MAXSNAPNUM->setCurrentIndex(0);
	//抓拍次数
	ui.comboBox_SNAPCOUNT->addItem(QObject::tr("持续抓拍"));
	for (int i = 1; i <= 20;i++)
	{
		QString str;
		str = QString("%1").arg(i);
		ui.comboBox_SNAPCOUNT->addItem(str);
	}
	ui.comboBox_SNAPCOUNT->setCurrentIndex(0);

	//抓拍场景
	ui.comboBox_SNAPSCENE->addItem(QObject::tr("常规场景"));
	ui.comboBox_SNAPSCENE->addItem(QObject::tr("大堂场景"));
	ui.comboBox_SNAPSCENE->setCurrentIndex(0);

	//人脸跟踪框
	ui.comboBox_FACETRACKING->addItem(QObject::tr("关闭"));
	ui.comboBox_FACETRACKING->addItem(QObject::tr("开启"));
	ui.comboBox_FACETRACKING->setCurrentIndex(0);

	//私有协议上传
	ui.comboBox_PRIVATEUP->addItem(QObject::tr("关闭"));
	ui.comboBox_PRIVATEUP->addItem(QObject::tr("开启"));
	ui.comboBox_PRIVATEUP->setCurrentIndex(0);

	//FTP上传
	ui.comboBox_FTPENABLE->addItem(QObject::tr("关闭"));
	ui.comboBox_FTPENABLE->addItem(QObject::tr("开启"));
	ui.comboBox_FTPENABLE->setCurrentIndex(0);

	//图片上传格式
	ui.comboBox_PICMODE->addItem(QObject::tr("上传人脸"));
	ui.comboBox_PICMODE->addItem(QObject::tr("上传原图"));
	ui.comboBox_PICMODE->addItem(QObject::tr("上传人脸及原图"));
	ui.comboBox_PICMODE->setCurrentIndex(0);

	ui.comboBox_FACEPICNAME->addItem(QObject::tr("默认"));
	ui.comboBox_FACEPICNAME->addItem(QObject::tr("自定义前缀"));
	ui.comboBox_FACEPICNAME->setCurrentIndex(0);
}


void ParamMeteSet::on_btnClose_clicked()
{
	close();
}

void ParamMeteSet::OnCbnSelchangeComChannel()
{
	unsigned long lBytesRet = 0;
	lBytesRet = 0;
	SDK_FA_SNAP_FACE_CONFIG stFace;
	memset(&stFace, 0, sizeof(SDK_FA_SNAP_FACE_CONFIG));
	VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_COMMON_PARAMETER, 0, (char *)&stFace, sizeof(SDK_FA_SNAP_FACE_CONFIG), &lBytesRet);

	ui.timeEdit_Start1->setTime(QTime(stFace.aTime.stSegTime[0][0].stBgnTime.hour, stFace.aTime.stSegTime[0][0].stBgnTime.minute));
	ui.timeEdit_End1->setTime(QTime(stFace.aTime.stSegTime[0][0].stEndTime.hour, stFace.aTime.stSegTime[0][0].stEndTime.minute));

	ui.timeEdit_Start2->setTime(QTime(stFace.aTime.stSegTime[0][1].stBgnTime.hour, stFace.aTime.stSegTime[0][1].stBgnTime.minute));
	ui.timeEdit_End2->setTime(QTime(stFace.aTime.stSegTime[0][1].stEndTime.hour, stFace.aTime.stSegTime[0][1].stEndTime.minute));

	ui.checkBox_Enable->setChecked(stFace.sSmartFace.nEnable);
	ui.checkBox_Time1->setChecked(stFace.aTime.stSegTime[0][0].bEnable);
	ui.checkBox_Time2->setChecked(stFace.aTime.stSegTime[0][1].bEnable);



	//灵敏度
	ui.comboBox_SENSITIVITY->setCurrentIndex(stFace.sSmartFace.nquality);

	m_nFacePicQual = stFace.sSmartFace.byFacePicQual;
	ui.lineEdit_FRAMEPICQUAL->setText(QString::number(stFace.sSmartFace.byFacePicQual));
	m_nFaceSize = stFace.sSmartFace.nFaceSize;
	ui.lineEdit_FACESIZE->setText(QString::number(stFace.sSmartFace.nFaceSize));
	m_nMaxFaceSize = stFace.sSmartFace.wMaxFaceSize;
	ui.lineEdit_MAXFACESIZE->setText(QString::number(stFace.sSmartFace.wMaxFaceSize));
	m_nExtendVaule = stFace.sSmartFace.byFaceAreaExpand;
	ui.lineEdit_EXTENDVAULE->setText(QString::number(stFace.sSmartFace.byFaceAreaExpand));
	m_nIntervalTime = stFace.sSmartFace.byIntervalTime;
	ui.lineEdit_INTERERAITIME->setText(QString::number(stFace.sSmartFace.byIntervalTime));
	m_nIntervalFrameGate = stFace.sSmartFace.nGateIntervalFrame;
	ui.lineEdit_INTERERAIFRAME_GATE->setText(QString::number(stFace.sSmartFace.nGateIntervalFrame));
	//大堂场景			 0:常规场景 1:大堂场景
	ui.comboBox_SNAPSCENE->setCurrentIndex(stFace.sSmartFace.nFaceBLC);
	//抓拍模式
	ui.comboBox_SNAPMODE->setCurrentIndex(stFace.sSmartFace.nSnapMode);// 2--间隔抓拍（以秒为单位）
	//最大抓拍次数
	ui.comboBox_MAXSNAPNUM->setCurrentIndex(stFace.sSmartFace.bySnapNum - 1);	 // 1--持续抓拍
	//快速抓拍帧数
	m_nFastSanpFramCount = stFace.sSmartFace.nTrackFrameNum;
	ui.lineEdit_FASTSNAPFRAMECOUNT->setText(QString::number(stFace.sSmartFace.nTrackFrameNum));
	//抓拍次数
	ui.comboBox_SNAPCOUNT->setCurrentIndex(stFace.sSmartFace.byIntervalSnapNum);

	m_nIntervalFrame = stFace.sSmartFace.nIntervalFrame;
	ui.lineEdit_INTERERAIFRAME->setText(QString::number(stFace.sSmartFace.nIntervalFrame));
	//	m_nSnapCount = stFace.sSmartFace.bySnapNum;

	//图片上传格式       0:人脸 1:原图 2:人脸及原图
	ui.comboBox_PICMODE->setCurrentIndex(stFace.sSmartFace.nPicMode);
	//FTP上传开关		 0:关闭 1:开启
	ui.comboBox_FTPENABLE->setCurrentIndex(stFace.sSmartFace.nFtpEnable);

	//人脸跟踪  		 0:关闭 1:开启
	ui.comboBox_FACETRACKING->setCurrentIndex(stFace.sSmartFace.nTrackmode);
	//人脸图片命名       0:默认 1:自定义前缀
	ui.comboBox_FACEPICNAME->setCurrentIndex(stFace.sSmartFace.byPicPrefixEnable);

	m_sCustomName = stFace.sSmartFace.szPicPrefix;
	ui.lineEdit_CUSTOMNAME->setText(stFace.sSmartFace.szPicPrefix);
	m_nFacePicQual = stFace.sSmartFace.byFacePicQual;
	ui.lineEdit_FACEPICQUAL->setText(QString::number(stFace.sSmartFace.byFacePicQual));
	m_nFramePicQual = stFace.sSmartFace.byFramePicQual;
	ui.lineEdit_FRAMEPICQUAL->setText(QString::number(stFace.sSmartFace.byFramePicQual));
	//私有协议
	ui.comboBox_PRIVATEUP->setCurrentIndex(stFace.stFsProtocols.nUDPSDKEnable);
	m_sServerIP = stFace.stFsProtocols.szUDPaddr;
	ui.lineEdit_SERVERIP->setText(stFace.stFsProtocols.szUDPaddr);
	m_nServerPort = stFace.stFsProtocols.dwUDPport;
	ui.lineEdit_SERVERPORT->setText(QString::number(stFace.stFsProtocols.dwUDPport));
	if (0 == stFace.stFsProtocols.nUDPSDKEnable)
	{
		ui.lineEdit_SERVERIP->setEnabled(false);
		ui.lineEdit_SERVERPORT->setEnabled(false);
	}
	else
	{
		ui.lineEdit_SERVERIP->setEnabled(false);
		ui.lineEdit_SERVERPORT->setEnabled(false);
	}

	SetComboSnapmode(stFace.sSmartFace.nSnapMode);
	SetComboFacepicname(stFace.sSmartFace.byPicPrefixEnable);


	SDK_FA_VI_DECTECT stVIDectectArea;
	ZeroMemory(&stVIDectectArea, sizeof(SDK_FA_VI_DECTECT));
}

void ParamMeteSet::SetComboSnapmode(int nCurSel)
{
	QString strText;
	QString str;
	//0 = 离开后抓拍(距离优先)   5 = 离开后抓拍(质量优先)
	if (0 == nCurSel || 5 == nCurSel)
	{
		//最大抓拍次数
		ui.label_MAXSNAPNUM->setEnabled(true);
		ui.comboBox_MAXSNAPNUM->setEnabled(true);
		//快速抓拍帧数
		ui.label_FASTSNAPFRAMECOUNT->setEnabled(false);
		ui.lineEdit_FASTSNAPFRAMECOUNT->setEnabled(false);
		//抓拍次数
		ui.label_SNAPCOUNT->setEnabled(false);
		ui.comboBox_SNAPCOUNT->setEnabled(false);
		//时间间隔
		ui.label_INTERERAITIME->setEnabled(false);
		ui.lineEdit_INTERERAITIME->setEnabled(false);
		//间隔帧数(间隔抓拍模式)
		ui.label_INTERERAIFRAME->setEnabled(false);
		ui.lineEdit_INTERERAIFRAME->setEnabled(false);
		//间隔帧数(单人模式)
		ui.label_INTERERAIFRAME_GATE->setEnabled(false);
		ui.lineEdit_INTERERAIFRAME_GATE->setEnabled(false);

		
		ui.comboBox_SNAPMODE->setCurrentIndex(nCurSel);
	}
	//快速抓拍
	else if (1 == nCurSel || 6 == nCurSel)
	{
	
		ui.label_MAXSNAPNUM->setEnabled(false);
		ui.comboBox_MAXSNAPNUM->setEnabled(false);
		ui.label_FASTSNAPFRAMECOUNT->setEnabled(true);
		ui.lineEdit_FASTSNAPFRAMECOUNT->setEnabled(true);
		ui.label_SNAPCOUNT->setEnabled(false);
		ui.comboBox_SNAPCOUNT->setEnabled(false);
		ui.label_INTERERAITIME->setEnabled(false);
		ui.lineEdit_INTERERAITIME->setEnabled(false);
		ui.label_INTERERAIFRAME->setEnabled(false);
		ui.lineEdit_INTERERAIFRAME->setEnabled(false);
		ui.label_INTERERAIFRAME_GATE->setEnabled(false);
		ui.lineEdit_INTERERAIFRAME_GATE->setEnabled(false);

		ui.comboBox_SNAPMODE->setCurrentIndex(nCurSel);
	}
	//间隔抓拍(以秒为单位)
	else if (2 == nCurSel)
	{
		ui.label_MAXSNAPNUM->setEnabled(false);
		ui.comboBox_MAXSNAPNUM->setEnabled(false);
		ui.label_FASTSNAPFRAMECOUNT->setEnabled(false);
		ui.lineEdit_FASTSNAPFRAMECOUNT->setEnabled(false);
		ui.label_SNAPCOUNT->setEnabled(true);
		ui.comboBox_SNAPCOUNT->setEnabled(true);
		ui.label_INTERERAITIME->setEnabled(true);
		ui.lineEdit_INTERERAITIME->setEnabled(true);
		ui.lineEdit_INTERERAIFRAME->setEnabled(false);
		ui.label_INTERERAIFRAME->setEnabled(false);
		ui.label_INTERERAIFRAME_GATE->setEnabled(false);
		ui.lineEdit_INTERERAIFRAME_GATE->setEnabled(false);

		ui.comboBox_SNAPMODE->setCurrentIndex(nCurSel);
	}
	//间隔抓拍(以帧为单位)
	else if (3 == nCurSel)
	{
		
		ui.label_MAXSNAPNUM->setEnabled(false);
		ui.comboBox_MAXSNAPNUM->setEnabled(false);
		ui.lineEdit_FASTSNAPFRAMECOUNT->setEnabled(false);
		ui.label_FASTSNAPFRAMECOUNT->setEnabled(false);
		ui.label_SNAPCOUNT->setEnabled(true);
		ui.comboBox_SNAPCOUNT->setEnabled(true);
		ui.label_INTERERAITIME->setEnabled(false);
		ui.lineEdit_INTERERAITIME->setEnabled(false);
		ui.label_INTERERAIFRAME->setEnabled(true);
		ui.lineEdit_INTERERAIFRAME->setEnabled(true);
		ui.label_INTERERAIFRAME_GATE->setEnabled(false);
		ui.lineEdit_INTERERAIFRAME_GATE->setEnabled(false);
		
		ui.comboBox_SNAPMODE->setCurrentIndex(nCurSel);
	}
	//单人模式
	else if (4 == nCurSel)
	{
		ui.label_MAXSNAPNUM->setEnabled(false);
		ui.comboBox_MAXSNAPNUM->setEnabled(false);
		ui.label_FASTSNAPFRAMECOUNT->setEnabled(false);
		ui.lineEdit_FASTSNAPFRAMECOUNT->setEnabled(false);
		ui.label_SNAPCOUNT->setEnabled(false);
		ui.comboBox_SNAPCOUNT->setEnabled(false);
		ui.label_INTERERAITIME->setEnabled(false);
		ui.lineEdit_INTERERAITIME->setEnabled(false);
		ui.label_INTERERAIFRAME->setEnabled(false);
		ui.lineEdit_INTERERAIFRAME->setEnabled(false);
		ui.label_INTERERAIFRAME_GATE->setEnabled(true);
		ui.lineEdit_INTERERAIFRAME_GATE->setEnabled(true);
	
		ui.comboBox_SNAPMODE->setCurrentIndex(nCurSel);
	}
	//	AfxMessageBox(str);
}

void ParamMeteSet::SetComboFacepicname(int nCurSel)
{
	// TODO: Add your control notification handler code here
	QString strText;
	QString str;
	if (0 == nCurSel)
	{
		ui.label_CUSTOMNAME->setEnabled(false);
		ui.lineEdit_CUSTOMNAME->setEnabled(false);

		ui.comboBox_FACEPICNAME->setCurrentIndex(nCurSel);
	}
	else
	{
		ui.label_CUSTOMNAME->setEnabled(true);
		ui.lineEdit_CUSTOMNAME->setEnabled(true);

		ui.comboBox_FACEPICNAME->setCurrentIndex(nCurSel);
	}
	//	AfxMessageBox(str);

}

void ParamMeteSet::on_comboBox_SNAPMODE_activated(int index)
{
	SetComboSnapmode(index);
}

void ParamMeteSet::on_comboBox_FACEPICNAME_activated(int index)
{
	SetComboFacepicname(index);
}

void ParamMeteSet::on_comboBox_PRIVATEUP_activated(int index)
{
	int nRet = index;
	if (0 == nRet)
	{
		ui.lineEdit_SERVERIP->setEnabled(false);
		ui.lineEdit_SERVERPORT->setEnabled(false);
	}
	else
	{
		ui.lineEdit_SERVERIP->setEnabled(true);
		ui.lineEdit_SERVERPORT->setEnabled(true);
	}
}

void ParamMeteSet::on_comboBox_PICMODE_activated(int index)
{
	int nSel = index;
	if (0 == nSel)
	{
		ui.lineEdit_FRAMEPICQUAL->setEnabled(false);
		ui.lineEdit_FACEPICQUAL->setEnabled(true);
	}
	else if (1 == nSel)
	{
		ui.lineEdit_FRAMEPICQUAL->setEnabled(true);
		ui.lineEdit_FACEPICQUAL->setEnabled(false);
	}
	else
	{
		ui.lineEdit_FRAMEPICQUAL->setEnabled(true);
		ui.lineEdit_FACEPICQUAL->setEnabled(true);
	}
}

void ParamMeteSet::on_btnSave_clicked()
{
	unsigned long lBytesRet = 0;
	SDK_FA_SNAP_FACE_CONFIG stFaceConfig;
	memset(&stFaceConfig, 0, sizeof(SDK_FA_SNAP_FACE_CONFIG));
	VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_COMMON_PARAMETER, 0, (char *)&stFaceConfig, sizeof(SDK_FA_SNAP_FACE_CONFIG), &lBytesRet);

	stFaceConfig.aTime.stSegTime[0][0].bEnable = ui.checkBox_Time1->checkState();
	stFaceConfig.aTime.stSegTime[0][1].bEnable = ui.checkBox_Time2->checkState();

	stFaceConfig.aTime.stSegTime[0][0].stBgnTime.hour = ui.timeEdit_Start1->time().hour();
	stFaceConfig.aTime.stSegTime[0][0].stBgnTime.minute = ui.timeEdit_Start1->time().minute();
	stFaceConfig.aTime.stSegTime[0][0].stBgnTime.second = ui.timeEdit_Start1->time().second();
	stFaceConfig.aTime.stSegTime[0][0].stEndTime.hour = ui.timeEdit_End1->time().hour();
	stFaceConfig.aTime.stSegTime[0][0].stEndTime.minute = ui.timeEdit_End1->time().minute();
	stFaceConfig.aTime.stSegTime[0][0].stEndTime.second = ui.timeEdit_End1->time().second();

	stFaceConfig.aTime.stSegTime[0][1].stBgnTime.hour = ui.timeEdit_Start2->time().hour();
	stFaceConfig.aTime.stSegTime[0][1].stBgnTime.minute = ui.timeEdit_Start2->time().minute();
	stFaceConfig.aTime.stSegTime[0][1].stBgnTime.second = ui.timeEdit_Start2->time().second();
	stFaceConfig.aTime.stSegTime[0][1].stEndTime.hour = ui.timeEdit_End2->time().hour();
	stFaceConfig.aTime.stSegTime[0][1].stEndTime.minute = ui.timeEdit_End2->time().minute();
	stFaceConfig.aTime.stSegTime[0][1].stEndTime.second = ui.timeEdit_End2->time().second();


	stFaceConfig.sSmartFace.nEnable = ui.checkBox_Enable->checkState();			//开关
	stFaceConfig.sSmartFace.nquality = ui.comboBox_SENSITIVITY->currentIndex();			//灵敏度
	//	stFaceConfig.sSmartFace.nExposureMode; 		//人脸曝光模式
	stFaceConfig.sSmartFace.nSnapMode = ui.comboBox_SNAPMODE->currentIndex();			//抓拍模式

	//离开后抓拍模式
	if (0 == stFaceConfig.sSmartFace.nSnapMode || 5 == stFaceConfig.sSmartFace.nSnapMode)
	{
		stFaceConfig.sSmartFace.bySnapNum = ui.comboBox_MAXSNAPNUM->currentIndex() + 1;
	}
	//快速抓拍
	else if (1 == stFaceConfig.sSmartFace.nSnapMode || 6 == stFaceConfig.sSmartFace.nSnapMode)
	{
		stFaceConfig.sSmartFace.nTrackFrameNum = ui.lineEdit_FASTSNAPFRAMECOUNT->text().toInt();
	}
	//间隔抓拍(以秒为单位)
	else if (2 == stFaceConfig.sSmartFace.nSnapMode)
	{
		stFaceConfig.sSmartFace.byIntervalTime = ui.lineEdit_INTERERAITIME->text().toInt();
		stFaceConfig.sSmartFace.byIntervalSnapNum = ui.comboBox_SNAPCOUNT->currentIndex();
	}
	//间隔抓拍(以帧为单位)
	else if (3 == stFaceConfig.sSmartFace.nSnapMode)
	{
		stFaceConfig.sSmartFace.nIntervalFrame = ui.lineEdit_INTERERAIFRAME->text().toInt();
		stFaceConfig.sSmartFace.byIntervalSnapNum = ui.comboBox_SNAPCOUNT->currentIndex();
	}
	//单人模式
	else if (4 == stFaceConfig.sSmartFace.nSnapMode)
	{
		stFaceConfig.sSmartFace.nGateIntervalFrame = ui.lineEdit_INTERERAIFRAME_GATE->text().toInt();
	}

	stFaceConfig.sSmartFace.nTrackmode = ui.comboBox_FACETRACKING->currentIndex();			//人脸跟踪  		 0:关闭 1:开启
	stFaceConfig.sSmartFace.nFtpEnable = ui.comboBox_FTPENABLE->currentIndex();				//FTP上传开关	0:关闭 1:开启


	stFaceConfig.sSmartFace.nFaceSize = ui.lineEdit_FACESIZE->text().toInt();			//人脸识别最小尺寸(60~300)
	stFaceConfig.sSmartFace.wMaxFaceSize = ui.lineEdit_MAXFACESIZE->text().toInt();
	stFaceConfig.sSmartFace.nFaceBLC = ui.comboBox_SNAPSCENE->currentIndex();			//人脸场景
	stFaceConfig.sSmartFace.nPicMode = ui.comboBox_PICMODE->currentIndex();			//图片上传格式(0人脸；1原图；2人脸及原图)


	stFaceConfig.sSmartFace.nParamCheckFlag;
	stFaceConfig.sSmartFace.byFaceAreaExpand = ui.lineEdit_EXTENDVAULE->text().toInt();	//人脸图片周边背景扩展系数


	stFaceConfig.sSmartFace.byFacePicQual = m_nFacePicQual;			//人脸图片编码质量
	stFaceConfig.sSmartFace.byFramePicQual = m_nFramePicQual;		//原图编码质量

	//私有协议
	stFaceConfig.stFsProtocols.nUDPSDKEnable = ui.comboBox_PRIVATEUP->currentIndex();
	strcpy(stFaceConfig.stFsProtocols.szUDPaddr, ui.lineEdit_SERVERIP->text().toLocal8Bit().data());
	stFaceConfig.stFsProtocols.dwUDPport = ui.lineEdit_SERVERPORT->text().toInt();




	stFaceConfig.sSmartFace.byPicPrefixEnable = ui.comboBox_FACEPICNAME->currentIndex();		//自定义前缀开关
	//自定义前缀
	if (stFaceConfig.sSmartFace.byPicPrefixEnable == 1)
	{
		if (ui.lineEdit_CUSTOMNAME->text().length() > 15)
		{
			stFaceConfig.sSmartFace.szPicPrefix[16];
			strncpy(stFaceConfig.sSmartFace.szPicPrefix, ui.lineEdit_CUSTOMNAME->text().toLocal8Bit().data(), 15);
		}
		else
		{
			strcpy(stFaceConfig.sSmartFace.szPicPrefix, ui.lineEdit_CUSTOMNAME->text().left(15).toLocal8Bit().data());
		}
	}


	//	stFaceConfig.sSmartFace.byAttributeEnable;						//人脸属性开关

	int n = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, 
		E_SDK_CFG_SMARTFACE_COMMON_PARAMETER, 0, (char *)&stFaceConfig, sizeof(SDK_FA_SNAP_FACE_CONFIG));
	if (n == 1)
	{
		myHelper::ShowMessageBoxInfo(QObject::tr("保存设置信息成功"));
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("保存设置信息失败"));
	}
}

void ParamMeteSet::on_btnUpdate_clicked()
{
	OnCbnSelchangeComChannel();
}