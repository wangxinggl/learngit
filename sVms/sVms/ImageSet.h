#pragma once

#include <QDialog>
#include "ui_ImageSet.h"
#include "AnalyseVideoAreaDlg.h"

class ImageSet : public QDialog
{
	Q_OBJECT

public:
	ImageSet(QWidget *parent = Q_NULLPTR);
	~ImageSet();
	void init();
	void GetDevParam();
public slots:
	void on_btnClose_clicked();
	void on_comboBox_activated(int index);
public:
	int m_nChannelNum;
	CJLNDevice* m_pDevObj;
	SDK_VIDEOCOLOR_PARAM *m_pVideoColorArea;
	
private:
	Ui::ImageSet ui;
	long m_lSelChannel;
	long m_lStreamType;
	AnalyseVideoAreaDlg* m_pAnalyseVideoAreaDlg;
};
