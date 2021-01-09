#ifndef CAPACITYSET_H
#define CAPACITYSET_H

#include <QWidget>
#include "ui_capacityset.h"
#include "VideoNetAPI.h"
#pragma execution_character_set("utf-8") 
class capacitySet : public QWidget
{
	Q_OBJECT

public:
	capacitySet(QWidget *parent = 0);
	~capacitySet();
	int m_recNum;
	int m_unRecNum;	
	
private slots:
	void on_btnSet_clicked();
	void on_btnClose_clicked();
private:
	Ui::capacitySet ui;
	
	void LoadConfig();
	void SetConfig();
};

#endif // CAPACITYSET_H
