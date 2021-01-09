#include "RePlayDownDlg.h"
#include <QList>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include <QStringList>
#include "myhelper.h"


int FileLen = 0;
RePlayDownDlg::RePlayDownDlg(QWidget *parent)
	: QWidget(parent)
	, m_lFileHandle(-1)
	, m_Down(false)
	, m_cur_file(1)
	, m_file_count(0)
	, m_bStart(false)
	, m_bPicture(0)
{
	ui.setupUi(this);
	setWindowTitle(QObject::tr("下载"));
	this->setWindowFlags(Qt::FramelessWindowHint);
	set = new systemSet();
	m_totalFile = 0;

	m_file_count = Client::instance()->m_videoPlayBack->m_tableWidget->rowCount();//items.count();
	for (int i = 0; i < m_file_count;i++)
	{
		if (Client::instance()->m_videoPlayBack->m_tableWidget->item(i, 0)->checkState())
		{
			m_totalFile++;
		}
	}

	if (m_bPicture != -1)
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

void RePlayDownDlg::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == DOWNLOAD_TIMER)
	{
		if (m_bStart)
		{
			QString file_name;
			int fileselpos = 0;
			m_bStart = false;
			for (int i = 0; i < m_file_count;i++)
			{
				if (Client::instance()->m_videoPlayBack->m_tableWidget->item(i,0)->checkState())
				{

					QString sText = Client::instance()->m_videoPlayBack->m_tableWidget->item(i, 4)->text();
					m_lFileSize = atol(sText.toLatin1().data()) << 20;
					file_name = Client::instance()->m_videoPlayBack->m_tableWidget->item(i, 3)->text();
					if (file_name.isEmpty())
					{
						m_cur_file++;
						continue;
					}
					QString sFile;
					if (Client::instance()->m_videoPlayBack->m_lFindType == FIND_TYPE_SJ)
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
					else if (Client::instance()->m_videoPlayBack->m_lFindType == FIND_TYPE_HIK)
					{
						sFile = file_name;
					}
					else if (Client::instance()->m_videoPlayBack->m_lFindType == FIND_TYPE_JL_NEW)
					{
						sFile = file_name;
					}
					QString ip;
					QString sDir = set->g_ClientCfg.szDownPath;
					m_sDownloadDisk = set->g_ClientCfg.szDownPath[0];
					m_sDownloadDisk += ":\\";
					m_sSavePath = sDir + "\\" + sFile;

					int j = 0;
					QFileInfo fileInfo(m_sSavePath);
					if (fileInfo.isFile() && ++j < 100)
					{
						m_sSavePath = sDir + j + sFile;
					}
					if (j >= 100)
					{
						m_sSavePath = sDir + "temp_" + sFile;
					}

					m_lFileSize = atol(sText.toLatin1().data());
					VIDEONET_FILE_DATA stVideoNetFileData;
					memset(&stVideoNetFileData, 0, sizeof(stVideoNetFileData));
					stVideoNetFileData.ch = Client::instance()->m_videoPlayBack->m_lChannel - 1;
					stVideoNetFileData.size = m_lFileSize;
					strncpy(stVideoNetFileData.sFileName, sFile.toLatin1().data(), sizeof(stVideoNetFileData.sFileName) - 1);
					QString csStartTime = Client::instance()->m_videoPlayBack->m_tableWidget->item(i, 1)->text();
					QString csEndTime = Client::instance()->m_videoPlayBack->m_tableWidget->item(i, 2)->text();
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
							sDir = set->g_ClientCfg.szPicPath;

						}
					}
					strFileName = QString("%1_%2_%3%4%5_%6%7%8.%9").arg(Client::instance()->m_videoPlayBack->m_strDevName).arg(stVideoNetFileData.ch + 1, 2, 10, QLatin1Char('0'))
						.arg(stVideoNetFileData.stBeginTime.year, 4, 10, QLatin1Char('0')).arg(stVideoNetFileData.stBeginTime.month, 2, 10, QLatin1Char('0'))
						.arg(stVideoNetFileData.stBeginTime.day, 2, 10, QLatin1Char('0')).arg(stVideoNetFileData.stBeginTime.hour, 2, 10, QLatin1Char('0'))
						.arg(stVideoNetFileData.stBeginTime.minute, 2, 10, QLatin1Char('0')).arg(stVideoNetFileData.stBeginTime.second, 2, 10, QLatin1Char('0'))
						.arg(strFileTpye);
					m_sSavePath = sDir + "\\" + strFileName;
					m_lFileHandle = VideoNet_GetFileByName(Client::instance()->m_videoPlayBack->m_lUserID, &stVideoNetFileData, m_sSavePath.toLatin1().data());

					if (m_lFileHandle < 0)
					{
						m_Down = false;
						killTimer(DOWNLOAD_TIMER);
						ui.btnStop->setText(QObject::tr("关闭"));
						QMessageBox::information(this, QObject::tr("警告"), QObject::tr("下载失败"));

					}
				}
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
				if (m_cur_file >=m_file_count)
				{
					m_Down = false;
					killTimer(DOWNLOAD_TIMER);

					VideoNet_StopGetFile(m_lFileHandle);

					m_lFileHandle = -1;
					ui.btnStop->setText(QObject::tr("关闭"));
					if (m_bPicture == 1)
					{
						//g_pReplayDlg->ShowPicture(m_sSavePath, IDC_STATIC_PICTURE);
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

/*
bool RePlayDownDlg::event(QEvent *e)
{
	CompareEvent *event = static_cast<CompareEvent *>(e);
	if (e->type() == static_cast <QEvent::Type>(CompareEvent::getType(CustomEventType::CET_DOWNLOAD)))
	{
		int searchId = event->getId();
		OnCovertFinish();
	}
	return true;
}
*/
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