#pragma once
#include <QDialog>

#include "ui_AnalysisDlg.h"
#include "AnalyseVideoAreaDlg.h"

#pragma execution_character_set("utf-8") 
class AnalysisDlg :	public QDialog
{
	Q_OBJECT
public:
	AnalysisDlg(QWidget *parent = Q_NULLPTR);
	~AnalysisDlg();

	void init();
	long EnableWindowAnalyse(BOOL bEnable);
	long SaveChannelParam(long lChannel);
	long GetDevParam();
	long ShowChannelParam(long lChannel);
	CJLNDevice* m_pDevObj;

private:

	Ui::AnalysisDlg ui;
	AnalyseVideoAreaDlg* m_pAnalyseVideoAreaDlg;

	SDK_AREA_RECT m_stFaceArea[DRAW_RECTANGLE_COUNT];
	SDK_FA_VI_SHIELDED* m_pFaShieldArea;
	SDK_FA_VI_DECTECT* m_pFaDectectArea;
	SDK_FA_VI_TEMPERATURE* m_pFaTempArea;

	long m_lSelChannel;
	long m_lStreamType;
	int m_nDrawType;
	int m_nAreaType;	//区域类型，0：区域识别，1：区域屏蔽，2：温度识别区域
	BOOL m_bStartCheck;
	BOOL m_bStartAreaSet;

private slots:
	void on_btnClear_clicked();
	void on_comboBox_activated(int index);
	void on_comboBox_AreaType_activated(int index);
	void on_btnAreaSet_clicked();
	void on_btnAll_clicked();
	void on_btnClose_clicked();
	void on_btnSave_clicked();
};

