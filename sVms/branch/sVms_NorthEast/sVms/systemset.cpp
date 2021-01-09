#include "systemset.h"
#include <QFileDialog>
#include <QMessageBox>
#include "DB.h"
#include <stdio.h>
#include <string.h>
#include "myhelper.h"
#include <QCoreApplication>

systemSet::systemSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	initPreSet();
	QString szPicPath,szDowPath,szSnapPath;
	DB *db = new DB;
	bool ret = db->getFilePath(szPicPath,szDowPath,szSnapPath);
	if (ret)
	{
		ui.lineEdit_screen->setText(szPicPath);
		ui.lineEdit_downed->setText(szDowPath);
		ui.lineEdit_face->setText(szSnapPath);
	}

	memcpy(g_ClientCfg.szPicPath, szPicPath.toLatin1().data(), sizeof(g_ClientCfg.szPicPath) - 1);
	//sprintf_s(g_ClientCfg.szPicPath,"%s",szPicPath.toLatin1().data(),sizeof(g_ClientCfg.szPicPath) - 1);
	sprintf_s(g_ClientCfg.szDownPath,"%s",szDowPath.toLatin1().data(),sizeof(g_ClientCfg.szDownPath) - 1);
	sprintf_s(g_ClientCfg.szSnapPath, "%s",szSnapPath.toLatin1().data(), sizeof(g_ClientCfg.szSnapPath) - 1);
	
	g_strLibPath="./LibPicture";
	g_ClientCfg.nBeginDriver = 1;
	g_ClientCfg.nEndDriver = 1;
	g_ClientCfg.nFileTimeLen = 15 * 60;
	g_ClientCfg.nCycleRecord = 0;
	GetDriverInfo();
	ShowAlarmAudioCfg(0);
	connect(ui.comboBox_Alarm, SIGNAL(currentIndexChanged(int)), this, SLOT(CbnSelchangeCmbAlarmsource(int)));
	setStyleSheet(".systemSet{border:2px solid black;}");
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setProperty("canMove", true);

}

systemSet::~systemSet()
{

}

void systemSet::on_toolButton_Face_clicked()
{
	QString pszPath = QFileDialog::getExistingDirectory(this,QObject::tr("请选择路径"),"/");
	if (!pszPath.isEmpty())
	{
		ui.lineEdit_face->setText(pszPath);
	}
}

void systemSet::on_toolButton_download_clicked()
{
	QString pszPath = QFileDialog::getExistingDirectory(this,QObject::tr("请选择路径"),"/");
	if (!pszPath.isEmpty())
	{
		ui.lineEdit_downed->setText(pszPath);
	}
}

void systemSet::on_toolButton_screen_clicked()
{
	QString pszPath = QFileDialog::getExistingDirectory(this,QObject::tr("请选择路径"),"/");
	if (!pszPath.isEmpty())
	{
		ui.lineEdit_screen->setText(pszPath);
	}
}

void systemSet::on_btnSet_clicked()
{
	QString screenPath = ui.lineEdit_screen->text();
	QString downloadPath = ui.lineEdit_downed->text();
	QString facePath = ui.lineEdit_face->text();
	QString videoPath = "d:\\smp\\Run\\Record";
	if (screenPath.isEmpty()||downloadPath.isEmpty()||facePath.isEmpty())
	{
		//QMessageBox::information(this,QObject::tr("警告"),QObject::tr("路径不合法，请重新选择路径!"));
		myHelper::ShowMessageBoxWarning(QObject::tr("路径不合法，请重新选择路径!"));
		return;
	}

	DB *db = new DB;
	bool ret = db->changeFilePath(screenPath,videoPath,downloadPath,facePath);
	if (!ret)
	{
		//QMessageBox::information(this,QObject::tr("警告"),QObject::tr("更新路径失败!"));
		myHelper::ShowMessageBoxWarning(QObject::tr("更新路径失败!"));
		return;
	}
	sprintf_s(g_ClientCfg.szPicPath,"%s",screenPath,sizeof(g_ClientCfg.szPicPath) - 1);
	sprintf_s(g_ClientCfg.szVideoPath,"%s",videoPath,sizeof(g_ClientCfg.szVideoPath) - 1);
	sprintf_s(g_ClientCfg.szDownPath,"%s",downloadPath,sizeof(g_ClientCfg.szDownPath) - 1);
	sprintf_s(g_ClientCfg.szSnapPath, "%s",facePath, sizeof(g_ClientCfg.szSnapPath) - 1);
}

void systemSet::on_btnRecordSet_clicked()
{
	
	int nFileLen;
	QString str;
	m_strFileTimeLen = ui.lineEdit_Length->text();
	m_strFileTimeLen.trimmed();
	if (m_strFileTimeLen.isEmpty())
	{
		//QMessageBox::warning(this, "Error", QObject::tr("录像文件长度不能为空"));
		myHelper::ShowMessageBoxWarning(QObject::tr("录像文件长度不能为空!"));
		return;
	}
	nFileLen = m_strFileTimeLen.toInt();
	if ((nFileLen < 1) || (nFileLen > 30))
	{
		//QMessageBox::warning(this, "Error", QObject::tr("录像文件长度范围:1~30!"));
		myHelper::ShowMessageBoxWarning(QObject::tr("录像文件长度范围:1~30!!"));
		return;
	}

	if (ui.combox_StartDriver->currentIndex() > ui.combox_EndDriver->currentIndex())
	{
		//QMessageBox::warning(this, "Error", QObject::tr("请选择正确的录像结束驱动器"));
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择正确的录像结束驱动器!"));
		return;
		
	}
	if (ui.checkBoxCycle->isChecked() == true)
	{
		m_bCycleRecord = 1;
	}
	else
	{
		m_bCycleRecord = 0;
	}

	g_ClientCfg.nBeginDriver = ui.combox_StartDriver->currentIndex();
	g_ClientCfg.nEndDriver = ui.combox_EndDriver->currentIndex();
	g_ClientCfg.nCycleRecord = m_bCycleRecord;
	g_ClientCfg.nFileTimeLen = nFileLen * 60;
	DB *db = new DB;
	if (db->SetCommonCfg(&g_ClientCfg)<0)
	{
		//QMessageBox::warning(this, "Error", QObject::tr("保存客户端参数失败"));

		myHelper::ShowMessageBoxError(QObject::tr("保存客户端参数失败!"));
		return;
	}

}

void systemSet::GetDriverInfo()
{
	QFileInfoList list = QDir::drives();
	for (int i = 0; i < list.count(); i++)
	{

		QString str = list.at(i).absoluteDir().absolutePath();
		ui.combox_StartDriver->addItem(str);
		ui.combox_EndDriver->addItem(str);
	}
	ui.lineEdit_Length->setText("15");
	ui.combox_StartDriver->setCurrentIndex(1);
	ui.combox_EndDriver->setCurrentIndex(1);
}

void systemSet::on_btnAlarmOpen_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		QObject::tr("请选择音乐文件"),
		".",
		"*.wav ");
	if (!fileName.isEmpty())
	{
		ui.lineEdit_Alarm->setText(fileName);
	}
}

void systemSet::on_btnAlarmSet_clicked()
{
	int nAlarmSource = ui.comboBox_Alarm->currentIndex();
	SaveAlarmAudioCfg(nAlarmSource);
}

int systemSet::SaveAlarmAudioCfg(int nAlarmSource)
{
	QString file;
	file = QString("%1\\LoginMsg.ini").arg(QCoreApplication::applicationDirPath());

	QString csAlarmSource, csValue;

	csAlarmSource = QString("%1").arg(nAlarmSource);

	if (ui.checkBox_Voice->checkState())
		csValue = "1";
	else
		csValue = "0";
	if (!::WritePrivateProfileString(csAlarmSource.toLatin1().data(), "audio", csValue.toLatin1().data(), file.toLatin1().data()))
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("保存失败"));
		return -1;
	}

	if (ui.checkBox_Prety->checkState())
		csValue = "1";
	else
		csValue = "0";
	if (!::WritePrivateProfileString(csAlarmSource.toLatin1().data(), "loop", csValue.toLatin1().data(), file.toLatin1().data()))
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("保存失败"));
		return -1;
	}

	csValue = "";

	csValue = ui.lineEdit_Alarm->text();
	if (!::WritePrivateProfileString(csAlarmSource.toLatin1().data(), "file", csValue.toLatin1().data(), file.toLatin1().data()))
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("保存失败"));
		return -1;
	}

	g_AlarmAudioCfg[nAlarmSource].nPlayAudio = ui.checkBox_Voice->checkState();
	g_AlarmAudioCfg[nAlarmSource].nAudioLoop = ui.checkBox_Prety->checkState();
	strcpy(g_AlarmAudioCfg[nAlarmSource].szFileName, csValue.toLocal8Bit().data());
	return 1;
}

void systemSet::ShowAlarmAudioCfg(int nAlarmSource)
{
	ui.checkBox_Voice->setChecked(g_AlarmAudioCfg[nAlarmSource].nPlayAudio);
	ui.checkBox_Prety->setChecked(g_AlarmAudioCfg[nAlarmSource].nAudioLoop);
	ui.lineEdit_Alarm->setWindowTitle(g_AlarmAudioCfg[nAlarmSource].szFileName);
}
void systemSet::initPreSet()
{
	QString file;
	file = QString("%1\\TvMode.ini").arg(QCoreApplication::applicationDirPath());
	int VideoSet = -1;
	VideoSet = ::GetPrivateProfileInt("VideoSet", "VideoSet", 0, file.toLatin1().data());
	ui.checkBox_Prew->setChecked(VideoSet);
	
}
void systemSet::on_btnpreSet_clicked()
{
	QString file;
	file = QString("%1\\TvMode.ini").arg(QCoreApplication::applicationDirPath());
	QString szString;
	QString strLoginType;
	szString = QString("%1").arg(ui.checkBox_Prew->checkState());
	::WritePrivateProfileString("VideoSet", "VideoSet", szString.toLatin1().data(), file.toLatin1().data());
}

void systemSet::CbnSelchangeCmbAlarmsource(int nSel)
{
	ShowAlarmAudioCfg(nSel);
}

void systemSet::on_btnClose_clicked()
{
	close();
}