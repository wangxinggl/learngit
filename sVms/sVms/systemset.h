#ifndef SYSTEMSET_H
#define SYSTEMSET_H

#include <QWidget>
#include "ui_systemset.h"
#include "table_structs.h"
#include <QDialog>
#include "VideoNetAPI.h"


#pragma execution_character_set("utf-8") 
typedef struct
{
	int nAlarmSource;
	int nPlayAudio;
	int nAudioLoop;
	char szFileName[1024];
}AlarmAudioCfg_t;


class systemSet : public QDialog
{
	Q_OBJECT

public:
	systemSet(QWidget *parent = 0);
	~systemSet();
	void initPreSet();
	TabCommonCfg_t m_ClientCfg;
	QString g_strLibPath;
	void GetDriverInfo();
	int SaveAlarmAudioCfg(int nAlarmSource);
	void ShowAlarmAudioCfg(int nAlarmSource);
	void GetConfig();
	void SetConfig();
	
private slots:
	void on_toolButton_Face_clicked();//获取人脸路径
	void on_toolButton_screen_clicked();//获取抓图路径
	void on_toolButton_download_clicked();//获取下载路径

	void on_btnSet_clicked();
	void on_btnRecordSet_clicked();

	void on_btnAlarmOpen_clicked(); //打开声音文件
	void on_btnAlarmSet_clicked();//保存声音设置
	//预览设置
	void on_btnpreSet_clicked();

	void CbnSelchangeCmbAlarmsource(int nSel);

	void on_btnClose_clicked();
private:
	Ui::systemSet ui;
	QString m_strFileTimeLen;
	int g_nDriverNum;
	BOOL m_bCycleRecord;
	AlarmAudioCfg_t g_AlarmAudioCfg[6];

	
};

#endif // SYSTEMSET_H
