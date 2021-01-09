#pragma once

#include <QWidget>
#include "ui_RePlayDownDlg.h"
#include <vector>
#include <QTimerEvent>
#include "systemset.h"
#include <QTableWidgetSelectionRange>
#include <QDialog>
#include "Device/JLNDevice.h"

typedef struct FILE_CONVERT_AVI
{
	char szFileName[256];
	bool bStatus;
}FILE_CONVERT;

class RePlayDownDlg : public QDialog
{
	Q_OBJECT

public:
	RePlayDownDlg(QWidget *parent = 0);
	~RePlayDownDlg();
public:
	long m_lFileSize;
	QString m_sDownloadDisk;
	long m_lFileHandle;
	bool m_Down;//是否下载
	int m_file_count; //文件总数
	int m_cur_file;//当前下载的文件
	QString m_sSavePath;
	bool m_bStart;//是否开始下载下一个文件
	QString m_strSnapPath;
	int DOWNLOAD_TIMER; //下载事件
	int DISPLAY_TIMER;

	int m_totalFile;//要下载的总数
	CJLNDevice* m_pDevObj;
public:
	LONG m_lChannel;
	int m_bPicture;	//人脸车牌图片标识0录像下载，1右键图片下载，2图片下载
	void timerEvent(QTimerEvent* event);
	void ChangeOldRecordFile();
	//bool event(QEvent *e);
	void OnCovertFinish();
	void DElh264File();
	void StartDownPicture();
	static DWORD WINAPI DownLoadPictureThread(LPVOID lpParam);
	void DownLoadFile();
private slots:
	void on_btnStop_clicked();

private:
	Ui::RePlayDownDlg ui;
	QList<QTableWidgetSelectionRange>items;
	vector<FILE_CONVERT_AVI > m_vecConverFile;
	vector<int> m_vecInt;
	int filecount;
	int itemtype;
	int tmprow;
	QString sDir;
};
