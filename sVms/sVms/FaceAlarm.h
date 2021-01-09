#pragma once

#include <QDialog>
#include "ui_FaceAlarm.h"
#include <QTime>
#include "VideoNetAPI.h"
#include "Device/JLNDevice.h"
#pragma execution_character_set("utf-8") 

class FaceAlarm : public QDialog
{
	Q_OBJECT
public:
	FaceAlarm(QWidget *parent = Q_NULLPTR);
	~FaceAlarm();
	void init();
	void OnCbnSelchangeComChannel();
private slots:
	void on_btnClose_clicked();
	void on_btnSave_clicked();
	void on_btnUpgrade_clicked();
public:
	CJLNDevice* m_pDevObj;
private:
	Ui::FaceAlarm ui;
	bool	m_bAlarmEnble;
	bool	m_bAlarmWhite;
	bool	m_bAlarmBlack;
	bool	m_bIoEnable;
	QTime	m_tEndTime1;
	QTime	m_tEndTime2;
	QTime	m_tStartTime1;
	QTime	m_tStartTime2;
	int		m_nOutTime;
	int		m_nOutType;
	int		m_nSimilarity;
	bool	m_bTime1Compare;
	bool	m_bTime2Compare;
};
