#define  _CRT_SECURE_NO_WARNINGS
#include "RePlayDownDlg.h"
#include <QList>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include <QStringList>
#include "myhelper.h"
#include <QRegExp>
#include <QDebug>
#include <string>
#include "client.h"

extern Client* g_pInstance;
int FileLen = 0;
RePlayDownDlg::RePlayDownDlg(QWidget *parent)
: QDialog(parent)
	, m_lFileHandle(-1)
	, m_Down(false)
	, m_cur_file(1)
	, m_file_count(0)
	, m_bStart(false)
	, m_bPicture(0)
	, m_pDevObj(NULL)
{
	ui.setupUi(this);
	setWindowTitle(QObject::tr("下载"));
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setProperty("canMove", true);
	setStyleSheet(".RePlayDownDlg{border:2px solid black;}");
	m_strSnapPath = QCoreApplication::applicationDirPath();
	m_strSnapPath = m_strSnapPath.replace(QRegExp("/"), "\\") +"\\Snap";
	QDir dir;
	if (!dir.exists(m_strSnapPath))
	{
		bool res = dir.mkpath(m_strSnapPath);
		
	}
	filecount = 0;
	m_totalFile = 0;
	itemtype = 0;
	m_file_count = g_pInstance->m_pVideoPlayBack->m_tableWidget->rowCount();//items.count();
	
	for (int i = 0; i < m_file_count;i++)
	{
		if (g_pInstance->m_pVideoPlayBack->m_tableWidget->item(i, 0)->checkState())
		{
			
			m_vecInt.push_back(i);
			 m_totalFile++;
		}
	}

	if (m_bPicture != 1)
	{
		if (m_totalFile == 0)
		{
			this->close();
		}
		else
		{
			ui.btnStop->setText(QObject::tr("停止下载"));

			m_bStart = true;
			m_Down = true;

			DOWNLOAD_TIMER = startTimer(500);
		}
	}

}

RePlayDownDlg::~RePlayDownDlg()
{
}

void RePlayDownDlg::on_btnStop_clicked()
{
	if (!m_Down)
	{
		close();
	}
	else
	{
		m_Down = false;
		killTimer(DOWNLOAD_TIMER);
		if (m_lFileHandle >= 0)
		{
			VideoNet_StopGetFile(m_lFileHandle);

			m_lFileHandle = -1;
		}
		ui.btnStop->setText(QObject::tr("关闭"));
	}
}
void RePlayDownDlg::StartDownPicture()
{
	m_bStart = true;
	m_Down = true;
	itemtype = 1;
	items = g_pInstance->m_pVideoPlayBack->m_tableWidget->selectedRanges();
	DOWNLOAD_TIMER = startTimer(100);
}

void RePlayDownDlg::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == DOWNLOAD_TIMER)
	{
		if (m_bStart)
		{
			QString file_name;
			int fileselpos = 0;
			m_bStart = false;
			while (1)
			{
				if (filecount == m_totalFile && m_totalFile != 0)
				{
					m_Down = false;
					killTimer(DOWNLOAD_TIMER);
					ui.btnStop->setText(QObject::tr("关闭"));
					myHelper::ShowMessageBoxInfo(QObject::tr("下载完成"));
					break;
				}
				QString sText;
				if (itemtype == 0)
				{
					sText = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(m_vecInt[filecount], 4)->text();
					m_lFileSize = atol(sText.toLatin1().data()) << 20;
					file_name = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(m_vecInt[filecount], 3)->text();
				}
				else if (itemtype == 1)
				{
					tmprow = items.at(filecount).bottomRow();
					sText = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(tmprow, 4)->text();
					m_lFileSize = atol(sText.toLatin1().data()) << 20;
					file_name = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(tmprow, 3)->text();

				}
				if (file_name.isEmpty())
				{
					m_cur_file++;
					continue;
				}
				QString sFile;
				sFile = file_name;

				QString sDir = g_pInstance->m_pDlgSystemSet->m_ClientCfg.szDownPath;
				m_sDownloadDisk = g_pInstance->m_pDlgSystemSet->m_ClientCfg.szDownPath[0];
				m_sDownloadDisk += ":\\";
				m_sSavePath = QString("%1\\%2").arg(sDir).arg(sFile);

				int j = 0;
				QFileInfo fileInfo(m_sSavePath);
				if (fileInfo.isFile() && ++j < 100)
				{
					m_sSavePath = QString("%1\\%2_%3").arg(sDir).arg(j).arg(sFile);
				}
				if (j >= 100)
				{
					m_sSavePath = QString("%1\\temp_%2").arg(sDir).arg(sFile);
				}

				m_lFileSize = atol(sText.toLocal8Bit().data());
				VIDEONET_FILE_DATA stVideoNetFileData;
				memset(&stVideoNetFileData, 0, sizeof(stVideoNetFileData));
				stVideoNetFileData.ch = g_pInstance->m_pVideoPlayBack->m_lChannel - 1;
				stVideoNetFileData.size = m_lFileSize;
				strncpy(stVideoNetFileData.sFileName, sFile.toLocal8Bit().data(), sizeof(stVideoNetFileData.sFileName) - 1);
				QString csStartTime;
				QString csEndTime;
				if (itemtype == 0)
				{
					csStartTime = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(m_vecInt[filecount], 1)->text();
					csEndTime = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(m_vecInt[filecount], 2)->text();
				}
				else
				{
					csStartTime = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(tmprow, 1)->text();
					csEndTime = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(tmprow, 2)->text();
				}
				sscanf(csStartTime.toLatin1().data(), "%d-%d-%d   %d:%d:%d ", &stVideoNetFileData.stBeginTime.year, &stVideoNetFileData.stBeginTime.month,
					&stVideoNetFileData.stBeginTime.day, &stVideoNetFileData.stBeginTime.hour, &stVideoNetFileData.stBeginTime.minute, &stVideoNetFileData.stBeginTime.second);
				sscanf(csEndTime.toLatin1().data(), "%d-%d-%d   %d:%d:%d ", &stVideoNetFileData.stEndTime.year, &stVideoNetFileData.stEndTime.month,
					&stVideoNetFileData.stEndTime.day, &stVideoNetFileData.stEndTime.hour, &stVideoNetFileData.stEndTime.minute, &stVideoNetFileData.stEndTime.second);

				QString strFileTpye("h264");
				QString strFileName("");
				if (strstr(stVideoNetFileData.sFileName, ".h264"))
				{
					strFileTpye = "h264";
				}
				else
				{
					strFileTpye = "jpg";
					if (m_bPicture == 1)
					{
						sDir = m_strSnapPath;
					}
					else
					{
						sDir = g_pInstance->m_pDlgSystemSet->m_ClientCfg.szPicPath;
					}
				}
				strFileName = QString("%1_%2_%3%4%5_%6%7%8.%9").arg(g_pInstance->m_pVideoPlayBack->m_strDevName).arg(stVideoNetFileData.ch + 1, 2, 10, QLatin1Char('0'))
					.arg(stVideoNetFileData.stBeginTime.year, 4, 10, QLatin1Char('0')).arg(stVideoNetFileData.stBeginTime.month, 2, 10, QLatin1Char('0'))
					.arg(stVideoNetFileData.stBeginTime.day, 2, 10, QLatin1Char('0')).arg(stVideoNetFileData.stBeginTime.hour, 2, 10, QLatin1Char('0'))
					.arg(stVideoNetFileData.stBeginTime.minute, 2, 10, QLatin1Char('0')).arg(stVideoNetFileData.stBeginTime.second, 2, 10, QLatin1Char('0'))
					.arg(strFileTpye);
				//sDir.replace("\\", "/");
				m_sSavePath = QString("%1\\%2").arg(sDir).arg(strFileName);


				m_lFileHandle = VideoNet_GetFileByName(m_pDevObj->m_lUserLoginID, &stVideoNetFileData, m_sSavePath.toLocal8Bit().data());

				if (m_lFileHandle < 0)
				{
					m_Down = false;
					killTimer(DOWNLOAD_TIMER);
					ui.btnStop->setText(QObject::tr("关闭"));
					QMessageBox::information(this, QObject::tr("警告"), QObject::tr("下载失败"));
				}
				break;
				
			}	

		}
		if (m_lFileHandle >= 0)
		{
			QString sText;
			int nPos = 0;
			nPos = VideoNet_GetDownloadPos(m_lFileHandle);

			if (nPos < 0 || nPos > 100) //失败
			{
				m_Down = false;
				killTimer(DOWNLOAD_TIMER);
				VideoNet_StopGetFile(m_lFileHandle);
				m_lFileHandle = -1;

				ui.btnStop->setText(QObject::tr("关闭"));
				myHelper::ShowMessageBoxWarning(QObject::tr("下载异常:nPos = %1!").arg(nPos));
				

			}
			else if (nPos == 100)
			{
				ui.progressBarDowned->setValue(nPos);
				if (m_cur_file >=m_totalFile)
				{
					m_Down = false;
					killTimer(DOWNLOAD_TIMER);

					VideoNet_StopGetFile(m_lFileHandle);

					m_lFileHandle = -1;
					ui.btnStop->setText(QObject::tr("关闭"));
					if (m_bPicture == 1)
					{
						g_pInstance->m_pVideoPlayBack->ShowPicture(m_sSavePath);
					}
					else
					{
						//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("下载完成"));
						myHelper::ShowMessageBoxInfo(QObject::tr("下载完成!"));
						//ChangeOldRecordFile();
					}
				}
				else
				{
					VideoNet_StopGetFile(m_lFileHandle);

					m_lFileHandle = -1;
					//下载下一个文件
					m_cur_file++;
					filecount++;
					m_bStart = true;;
				}
			}
			else
			{
				ui.progressBarDowned->setValue(nPos);
				sText = QString("%1/%2:%3").arg(m_cur_file).arg(m_totalFile).arg(m_sSavePath);
				ui.display_Process->setText(sText);
				//检查磁盘的剩余空间
				ULARGE_INTEGER a, b, c;
				BOOL bRet = GetDiskFreeSpaceEx(m_sDownloadDisk.toLatin1().data(), &a, &b, &c);
				if (bRet && a.QuadPart > (m_lFileSize / 100.0 * (100 - nPos)))
				{
				}
				else
				{
					m_Down = false;
					killTimer(DOWNLOAD_TIMER);

					VideoNet_StopGetFile(m_lFileHandle);


					m_lFileHandle = -1;
					ui.btnStop->setText(QObject::tr("关闭"));

					//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("磁盘空间不足"));
					myHelper::ShowMessageBoxWarning(QObject::tr("磁盘空间不足!"));
				}
			}
		}
		
	}
	
}

DWORD WINAPI RePlayDownDlg::DownLoadPictureThread(LPVOID lpParam)
{
	RePlayDownDlg *pDlg = (RePlayDownDlg  *)lpParam;
	pDlg->DownLoadFile();
	return TRUE;
}

void RePlayDownDlg::DownLoadFile()
{
	if (m_bStart)
	{
	QString file_name;
	int fileselpos = 0;
	m_bStart = false;
	while (1)
	{
	if (filecount == m_totalFile && m_totalFile != 0)
	{
	m_Down = false;
	killTimer(DOWNLOAD_TIMER);
	ui.btnStop->setText(QObject::tr("关闭"));
	myHelper::ShowMessageBoxInfo(QObject::tr("下载完成"));
	break;
	}		QString sText;
	if (itemtype == 0)
	{
	sText = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(m_vecInt[filecount], 4)->text();
	m_lFileSize = atol(sText.toLatin1().data()) << 20;
	file_name = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(m_vecInt[filecount], 3)->text();
	}
	else if (itemtype == 1)
	{
	tmprow = items.at(filecount).bottomRow();
	sText = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(tmprow, 4)->text();
	m_lFileSize = atol(sText.toLatin1().data()) << 20;
	file_name = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(tmprow, 3)->text();

	}
	if (file_name.isEmpty())
	{
	m_cur_file++;
	continue;
	}
	QString sFile;
	if (g_pInstance->m_pVideoPlayBack->m_lFindType == FIND_TYPE_SJ)
	{
	int index1 = file_name.lastIndexOf('/');
	int index2 = file_name.lastIndexOf('\\');
	if (index1 == -1 && index2 == -1)
	{
	m_cur_file++;
	continue;
	}
	sFile = file_name.right(file_name.length() - max(index1, index2) - 1);
	}
	else if (g_pInstance->m_pVideoPlayBack->m_lFindType == FIND_TYPE_HIK)
	{
	sFile = file_name;
	}
	else if (g_pInstance->m_pVideoPlayBack->m_lFindType == FIND_TYPE_JL_NEW)
	{
	sFile = file_name;
	}
	QString ip;
	QString sDir = g_pInstance->m_pDlgSystemSet->m_ClientCfg.szDownPath;
	m_sDownloadDisk = g_pInstance->m_pDlgSystemSet->m_ClientCfg.szDownPath[0];
	m_sDownloadDisk += ":\\";
	m_sSavePath = QString("%1\\%2").arg(sDir).arg(sFile);

	int j = 0;
	QFileInfo fileInfo(m_sSavePath);
	if (fileInfo.isFile() && ++j < 100)
	{
	m_sSavePath = QString("%1\\%2_%3").arg(sDir).arg(j).arg(sFile);
	}
	if (j >= 100)
	{
	m_sSavePath = QString("%1\\temp_%2").arg(sDir).arg(sFile);
	}

	m_lFileSize = atol(sText.toLocal8Bit().data());
	VIDEONET_FILE_DATA stVideoNetFileData;
	memset(&stVideoNetFileData, 0, sizeof(stVideoNetFileData));
	stVideoNetFileData.ch = g_pInstance->m_pVideoPlayBack->m_lChannel - 1;
	stVideoNetFileData.size = m_lFileSize;
	strncpy(stVideoNetFileData.sFileName, sFile.toLocal8Bit().data(), sizeof(stVideoNetFileData.sFileName) - 1);
	QString csStartTime;
	QString csEndTime ;
	if (itemtype == 0)
	{
	csStartTime = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(m_vecInt[filecount], 1)->text();
	csEndTime = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(m_vecInt[filecount], 2)->text();
	}
	else
	{
	csStartTime = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(tmprow, 1)->text();
	csEndTime = g_pInstance->m_pVideoPlayBack->m_tableWidget->item(tmprow, 2)->text();
	}
	sscanf(csStartTime.toLatin1().data(), "%d-%d-%d   %d:%d:%d ", &stVideoNetFileData.stBeginTime.year, &stVideoNetFileData.stBeginTime.month,
	&stVideoNetFileData.stBeginTime.day, &stVideoNetFileData.stBeginTime.hour, &stVideoNetFileData.stBeginTime.minute, &stVideoNetFileData.stBeginTime.second);
	sscanf(csEndTime.toLatin1().data(), "%d-%d-%d   %d:%d:%d ", &stVideoNetFileData.stEndTime.year, &stVideoNetFileData.stEndTime.month,
	&stVideoNetFileData.stEndTime.day, &stVideoNetFileData.stEndTime.hour, &stVideoNetFileData.stEndTime.minute, &stVideoNetFileData.stEndTime.second);

	QString strFileTpye("h264");
	QString strFileName("");
	if (strstr(stVideoNetFileData.sFileName, ".h264"))
	{
		strFileTpye = "h264";
	}
	else
	{
		strFileTpye = "jpg";
		if (m_bPicture == 1)
		{
			sDir = m_strSnapPath;
		}
		else
		{
			sDir = g_pInstance->m_pDlgSystemSet->m_ClientCfg.szPicPath;

		}
	}
	strFileName = QString("%1_%2_%3%4%5_%6%7%8.%9").arg(g_pInstance->m_pVideoPlayBack->m_strDevName).arg(stVideoNetFileData.ch + 1, 2, 10, QLatin1Char('0'))
	.arg(stVideoNetFileData.stBeginTime.year, 4, 10, QLatin1Char('0')).arg(stVideoNetFileData.stBeginTime.month, 2, 10, QLatin1Char('0'))
	.arg(stVideoNetFileData.stBeginTime.day, 2, 10, QLatin1Char('0')).arg(stVideoNetFileData.stBeginTime.hour, 2, 10, QLatin1Char('0'))
	.arg(stVideoNetFileData.stBeginTime.minute, 2, 10, QLatin1Char('0')).arg(stVideoNetFileData.stBeginTime.second, 2, 10, QLatin1Char('0'))
	.arg(strFileTpye);
	sDir.replace("\\", "/");
	m_sSavePath = QString("%1/%2").arg(sDir).arg(strFileName);
	m_lFileHandle = VideoNet_GetFileByName(m_pDevObj->m_lUserLoginID, &stVideoNetFileData, m_sSavePath.toLocal8Bit().data());

	if (m_lFileHandle < 0)
	{
	m_Down = false;
	killTimer(DOWNLOAD_TIMER);
	ui.btnStop->setText(QObject::tr("关闭"));
	QMessageBox::information(this, QObject::tr("警告"), QObject::tr("下载失败"));

	}
	break;

	}


	}
	if (m_lFileHandle >= 0)
	{
	QString sText;
	int nPos = 0;
	nPos = VideoNet_GetDownloadPos(m_lFileHandle);

	if (nPos < 0 || nPos > 100) //失败
	{
	m_Down = false;
	killTimer(DOWNLOAD_TIMER);
	VideoNet_StopGetFile(m_lFileHandle);
	m_lFileHandle = -1;

	ui.btnStop->setText(QObject::tr("关闭"));
	//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("下载异常:nPos = %1").arg(nPos));
	myHelper::ShowMessageBoxWarning(QObject::tr("下载异常:nPos = %1!").arg(nPos));


	}
	else if (nPos == 100)
	{
	ui.progressBarDowned->setValue(nPos);
	if (m_cur_file >=m_totalFile)
	{
	m_Down = false;
	killTimer(DOWNLOAD_TIMER);

	VideoNet_StopGetFile(m_lFileHandle);

	m_lFileHandle = -1;
	ui.btnStop->setText(QObject::tr("关闭"));
	if (m_bPicture == 1)
	{
	g_pInstance->m_pVideoPlayBack->ShowPicture(m_sSavePath);
	}
	else
	{
	//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("下载完成"));
	myHelper::ShowMessageBoxInfo(QObject::tr("下载完成!"));
	//ChangeOldRecordFile();
	}
	}
	else
	{
	VideoNet_StopGetFile(m_lFileHandle);

	m_lFileHandle = -1;
	//下载下一个文件
	m_cur_file++;
	filecount++;
	m_bStart = true;;
	}
	}
	else
	{
	ui.progressBarDowned->setValue(nPos);
	sText = QString("%1/%2:%3").arg(m_cur_file).arg(m_totalFile).arg(m_sSavePath);
	ui.display_Process->setText(sText);
	//检查磁盘的剩余空间
	ULARGE_INTEGER a, b, c;
	BOOL bRet = GetDiskFreeSpaceEx(m_sDownloadDisk.toLatin1().data(), &a, &b, &c);
	if (bRet && a.QuadPart > (m_lFileSize / 100.0 * (100 - nPos)))
	{
	}
	else
	{
	m_Down = false;
	killTimer(DOWNLOAD_TIMER);

	VideoNet_StopGetFile(m_lFileHandle);


	m_lFileHandle = -1;
	ui.btnStop->setText(QObject::tr("关闭"));

	//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("磁盘空间不足"));
	myHelper::ShowMessageBoxWarning(QObject::tr("磁盘空间不足!"));
	}
	}
	}
}
void CALLBACK ConvertProcess(DWORD CurrentPos, DWORD TotoalPos, DWORD dwUser)
{
	int nIndex = (int)dwUser;
	if (CurrentPos == TotoalPos)
	{
		
	}

}

void RePlayDownDlg::ChangeOldRecordFile()
{
	QString g_strDriverName[26];
	QStringList files;
	QString strfileName;
	LONG lConverId = 0;
	QString sDir = QString("D:\\smp\\Run\\Download");
	QDir dir(sDir);
	QStringList nameFilters;
	nameFilters << "*.h264";
	files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
	FileLen = files.length();
	for (int i = 0; i < files.length(); i++)
	{
		QFileInfo fileinfo = files.at(i);
		strfileName = sDir + "\\"+fileinfo.fileName();
		FILE_CONVERT_AVI stFileConvert = { 0 };
		memcpy(stFileConvert.szFileName, strfileName.toLatin1().data(), strfileName.length());
		m_vecConverFile.push_back(stFileConvert);
		QString strDstFile = strfileName.left(strfileName.length() - 4) + "avi";
		lConverId = VideoPlayer_ConvertFile(strfileName.toLatin1().data(), strDstFile.toLatin1().data(), MEDIA_FILE_AVI, ConvertProcess, (DWORD)i);
	}

}

void RePlayDownDlg::DElh264File()
{
	QStringList files;
	QString sDir = QString("D:\\smp\\Run\\Download");
	QDir dir(sDir);
	QStringList nameFilters;
	nameFilters << "*.h264";
	files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
	FileLen = files.length();
	for (int i = 0; i < files.length(); i++)
	{
		files.removeAt(i);	
	}
}
void RePlayDownDlg::OnCovertFinish()
{
	static int nCount = 0;
	nCount++;
	if (nCount == FileLen)
	{
		DElh264File();
		//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("AVI格式中转换完成!"));
		myHelper::ShowMessageBoxWarning(QObject::tr("AVI格式中转换完成!"));
	}
}