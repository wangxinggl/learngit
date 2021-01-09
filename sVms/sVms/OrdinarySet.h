#pragma once

#include <QDialog>
#include "ui_OrdinarySet.h"
#include "Configsetting.h"
#include "devtreepro.h"
#include "AnalyseVideoAreaDlg.h"
class OrdinarySet : public QDialog
{
	Q_OBJECT

public:
	OrdinarySet(QWidget *parent = Q_NULLPTR);
	~OrdinarySet();
	void InitComboBox();
	void InitDlgInfo();
	void SetDeviceConfigInfo(SDK_CONFIG_NORMAL* pConfigNormal);
	
public:
	CJLNDevice* m_pDevObj;
	SDK_CONFIG_NORMAL* m_pstConfigNormal;
public slots:
	void on_btnClose_clicked();
	void on_btnSave_clicked();
	void on_btnUpgrade_clicked();
private:
	Ui::OrdinarySet ui;
};
