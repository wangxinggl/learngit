#pragma once
#include "qwidget.h"
#include "ui_TempratureBox.h"
#include "table_structs.h"
class CTemperatureBox : public QWidget
{
	Q_OBJECT
public:
	CTemperatureBox(QWidget *parent = 0);
	~CTemperatureBox();

private slots:

	void on_btnClose_clicked();

private:
	Ui::Temperature_Box ui;
	char m_szPicName[520];
	char m_szLibName[520];
	char m_szSnapPath[520];
	char m_chTime[16];
	QString m_strImagePath;
	QString m_strSnapTime;
	QImage m_Image;
public:
	void ShowInfo(SMART_FACE_CMP_QUERY_INFO *pCompareInfoTmp, QString pszStatus);
	BOOL m_bShow;
};

