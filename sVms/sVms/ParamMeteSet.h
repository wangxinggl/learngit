#pragma once

#include <QDialog>
#include "ui_ParamMeteSet.h"
#include <QTime>
#include <QObject>
#include <QWidget>
#include "myhelper.h"
#include "AnalyseVideoAreaDlg.h"
#pragma execution_character_set("utf-8") 

class ParamMeteSet : public QDialog
{
	Q_OBJECT

public:
	ParamMeteSet(QWidget *parent = Q_NULLPTR);
	~ParamMeteSet();
	void init();
	
	void OnCbnSelchangeComChannel();
	void SetComboSnapmode(int nCurSel);
	void SetComboFacepicname(int nCurSel);
	CJLNDevice* m_pDevObj;
private slots:
	void on_btnClose_clicked();
	void on_comboBox_SNAPMODE_activated(int index);
	void on_comboBox_FACEPICNAME_activated(int index);
	void on_comboBox_PRIVATEUP_activated(int index);
	void on_comboBox_PICMODE_activated(int index);
	void on_btnSave_clicked();
	void on_btnUpdate_clicked();
private:
	Ui::ParamMeteSet ui;
	int		m_nFacePicQual;
	int		m_nFaceSize;
	int		m_nExtendVaule;
	int		m_nFastSanpFramCount;
	QTime	m_tStartTime1;
	QTime	m_tStartTime2;
	QTime	m_tEndTime1;
	QTime	m_tEndTime2;
	int		m_nIntervalTime;
	QString	m_sCustomName;
	QString	m_sServerIP;
	int		m_nServerPort;
	int		m_nIntervalFrame;
	int		m_nSnapCount;
	bool	m_bEnablUse;
	bool	m_bEnableTime1;
	bool	m_bEnableTime2;
	int		m_nIntervalFrameGate;
	int		m_nMaxFaceSize;
	int		m_nFramePicQual;
};
