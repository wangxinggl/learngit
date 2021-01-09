#pragma once

#include <QDialog>
#include "ui_VideoWarning.h"
#include "AnalyseVideoAreaDlg.h"

class VideoWarning : public QDialog
{
	Q_OBJECT

public:
	VideoWarning(QWidget *parent = Q_NULLPTR);
	~VideoWarning();
	void init();
	void OnCbnSelchangeComChannel();
	long EnableWindowAnalyse(BOOL bEnable);
	long SaveChannelParam(long lChannel);
	long GetDevParam();
	long SetDevParam();
	long ShowChannelParam(long lChannel);
private slots:
	void on_btnClear_clicked();
	void on_btnClose_clicked();
	void on_comboBox_activated(int index);
public:
	CJLNDevice* m_pDevObj;
private:
	Ui::VideoWarning ui;
	long m_lSelChannel;
	long m_lStreamType;
	int m_nDrawType;
	BOOL m_bStartCheck;
	BOOL m_bStartAreaSet;
	AnalyseVideoAreaDlg* m_pAnalyseVideoAreaDlg;
	SDK_FA_VI_SHIELDED* m_pFaShielded;
};
