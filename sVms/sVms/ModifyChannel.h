#pragma once

#include <QWidget>
#include "ui_ModifyChannel.h"
#include <QLineEdit>
#include <QComboBox>
#include <QDialog>

#pragma execution_character_set("utf-8") 
class ModifyChannel : public QDialog
{
	Q_OBJECT

public:
	ModifyChannel(QWidget *parent = Q_NULLPTR);
	~ModifyChannel();
	void initForm();
private slots:
	void on_btnSure_clicked();
	void on_btnCancel_clicked();
	void on_btnClose_clicked();
public:
	QLineEdit *displayChannelNum;
	QLineEdit *displayChannelName;
	int m_nChannelType;
private:
	Ui::ModifyChannel ui;

};
