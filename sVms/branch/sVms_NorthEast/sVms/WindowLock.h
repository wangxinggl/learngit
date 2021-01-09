#pragma once

#include <QDialog>
#include "ui_WindowLock.h"

#pragma execution_character_set("utf-8") 

class WindowLock : public QDialog
{
	Q_OBJECT

public:
	WindowLock(QWidget *parent = Q_NULLPTR);
	~WindowLock();
	
private slots:
	void on_btnSure_clicked();
private:
	Ui::WindowLock ui;
private:
	
};
