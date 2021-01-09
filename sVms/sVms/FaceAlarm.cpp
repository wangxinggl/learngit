#include "FaceAlarm.h"
#include "myhelper.h"

FaceAlarm::FaceAlarm(QWidget *parent)
	: QDialog(parent)
	, m_pDevObj(NULL)
{
	ui.setupUi(this);
	init();

	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setStyleSheet(".FaceAlarm{border:2px solid black;}");
}

FaceAlarm::~FaceAlarm()
{
}

void FaceAlarm::on_btnClose_clicked()
{
	close();
}

void FaceAlarm::init()
{
	m_bAlarmEnble = false;
	m_bAlarmWhite = false;
	m_bAlarmBlack = false;
	m_bIoEnable = false;
	m_tEndTime1 = QTime::currentTime();
	m_tEndTime2 = QTime::currentTime();
	m_tStartTime1 = QTime::currentTime();
	m_tStartTime2 = QTime::currentTime();
	m_nOutTime = 0;
	m_nOutType = 0;
	m_nSimilarity = 0;
	m_bTime1Compare = false;
	m_bTime2Compare = false;


	ui.timeEdit_DATETIMEPICKER_START1_COMPARE->setDisplayFormat("H:mm");
	ui.timeEdit_DATETIMEPICKER_END1_COMPARE->setDisplayFormat("H:mm");
	ui.timeEdit_DATETIMEPICKER_START1_COMPARE->setTime(QTime(0, 0));
	ui.timeEdit_DATETIMEPICKER_END1_COMPARE->setTime(QTime(23, 59));

	ui.timeEdit_DATETIMEPICKER_START2_COMPARE->setDisplayFormat("H:mm");
	ui.timeEdit_DATETIMEPICKER_END2_COMPARE->setDisplayFormat("H:mm");
	ui.timeEdit_DATETIMEPICKER_START2_COMPARE->setTime(QTime(0, 0));
	ui.timeEdit_DATETIMEPICKER_END2_COMPARE->setTime(QTime(23, 59));
}

void FaceAlarm::OnCbnSelchangeComChannel()
{
	unsigned long lBytesRet = 0;
	lBytesRet = 0;
	SDK_SMART_ALARM stFaceAlarm;
	memset(&stFaceAlarm, 0, sizeof(SDK_SMART_ALARM));
	VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_ALARM, 0, (char *)&stFaceAlarm, sizeof(SDK_SMART_ALARM), &lBytesRet);

	ui.checkBox_ALARMENABLE->setChecked(stFaceAlarm.aEnable);
	ui.checkBox_ALARM_WHITE->setChecked(stFaceAlarm.aWEnable);
	ui.checkBox_ENABLE_BLACK->setChecked(stFaceAlarm.aBEnable);
	ui.checkBox_IOENABLE->setChecked(stFaceAlarm.aIoEnable);
	
	ui.lineEdit_OUTPUTTIME->setText(QString::number(stFaceAlarm.aIoTime));
	ui.comboBox_OUTPUTTYPE->setCurrentIndex(stFaceAlarm.aIoType);
	ui.lineEdit_SIMILARITY->setText(QString::number(stFaceAlarm.aSimilarity));
	
	ui.timeEdit_DATETIMEPICKER_START1_COMPARE->setTime(QTime(stFaceAlarm.aTime.stSegTime[0][0].stBgnTime.hour, stFaceAlarm.aTime.stSegTime[0][0].stBgnTime.minute));
	ui.timeEdit_DATETIMEPICKER_END1_COMPARE->setTime(QTime(stFaceAlarm.aTime.stSegTime[0][0].stEndTime.hour, stFaceAlarm.aTime.stSegTime[0][0].stEndTime.minute));

	ui.timeEdit_DATETIMEPICKER_START2_COMPARE->setTime(QTime(stFaceAlarm.aTime.stSegTime[0][1].stBgnTime.hour, stFaceAlarm.aTime.stSegTime[0][1].stBgnTime.minute));
	ui.timeEdit_DATETIMEPICKER_END2_COMPARE->setTime(QTime(stFaceAlarm.aTime.stSegTime[0][1].stEndTime.hour, stFaceAlarm.aTime.stSegTime[0][1].stEndTime.minute));

	ui.checkBox_TIME1_COMPARE->setChecked(stFaceAlarm.aTime.stSegTime[0][0].bEnable);
	ui.checkBox_TIME2_COMPARE->setChecked(stFaceAlarm.aTime.stSegTime[0][1].bEnable);

}

void FaceAlarm::on_btnSave_clicked()
{
	unsigned long lBytesRet = 0;
	lBytesRet = 0;
	SDK_SMART_ALARM stFaceAlarm;
	memset(&stFaceAlarm, 0, sizeof(SDK_SMART_ALARM));
	VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_ALARM, 0, (char *)&stFaceAlarm, sizeof(SDK_SMART_ALARM), &lBytesRet);


	stFaceAlarm.aEnable = ui.checkBox_ALARMENABLE->checkState();
	stFaceAlarm.aWEnable = ui.checkBox_ALARM_WHITE->checkState();
	stFaceAlarm.aBEnable = ui.checkBox_ENABLE_BLACK->checkState();
	stFaceAlarm.aIoEnable = ui.checkBox_IOENABLE->checkState();
	stFaceAlarm.aIoTime = ui.lineEdit_OUTPUTTIME->text().toInt();
	stFaceAlarm.aIoType = ui.comboBox_OUTPUTTYPE->currentIndex();
	stFaceAlarm.aSimilarity = ui.lineEdit_SIMILARITY->text().toInt();

	stFaceAlarm.aTime.stSegTime[0][0].bEnable = ui.checkBox_TIME1_COMPARE->checkState();
	stFaceAlarm.aTime.stSegTime[0][1].bEnable = ui.checkBox_TIME2_COMPARE->checkState();

	stFaceAlarm.aTime.stSegTime[0][0].stBgnTime.hour = ui.timeEdit_DATETIMEPICKER_START1_COMPARE->time().hour();
	stFaceAlarm.aTime.stSegTime[0][0].stBgnTime.minute = ui.timeEdit_DATETIMEPICKER_START1_COMPARE->time().minute();
	stFaceAlarm.aTime.stSegTime[0][0].stBgnTime.second = ui.timeEdit_DATETIMEPICKER_START1_COMPARE->time().second();

	stFaceAlarm.aTime.stSegTime[0][0].stEndTime.hour = ui.timeEdit_DATETIMEPICKER_END1_COMPARE->time().hour();
	stFaceAlarm.aTime.stSegTime[0][0].stEndTime.minute = ui.timeEdit_DATETIMEPICKER_END1_COMPARE->time().minute();
	stFaceAlarm.aTime.stSegTime[0][0].stEndTime.second = ui.timeEdit_DATETIMEPICKER_END1_COMPARE->time().second();

	stFaceAlarm.aTime.stSegTime[0][1].stBgnTime.hour = ui.timeEdit_DATETIMEPICKER_START2_COMPARE->time().hour();
	stFaceAlarm.aTime.stSegTime[0][1].stBgnTime.minute = ui.timeEdit_DATETIMEPICKER_START2_COMPARE->time().minute();
	stFaceAlarm.aTime.stSegTime[0][1].stBgnTime.second = ui.timeEdit_DATETIMEPICKER_START2_COMPARE->time().second();
	stFaceAlarm.aTime.stSegTime[0][1].stEndTime.hour = ui.timeEdit_DATETIMEPICKER_END2_COMPARE->time().hour();
	stFaceAlarm.aTime.stSegTime[0][1].stEndTime.minute = ui.timeEdit_DATETIMEPICKER_END2_COMPARE->time().minute();
	stFaceAlarm.aTime.stSegTime[0][1].stEndTime.second = ui.timeEdit_DATETIMEPICKER_END2_COMPARE->time().second();

	
	int nRet = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CFG_SMARTFACE_ALARM, 0, (char *)&stFaceAlarm, sizeof(SDK_SMART_ALARM));
	if (nRet == 1)
	{
		myHelper::ShowMessageBoxInfo(QObject::tr("保存设置信息成功"));
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("保存设置信息失败"));
	}
}

void FaceAlarm::on_btnUpgrade_clicked()
{
	OnCbnSelchangeComChannel();
}