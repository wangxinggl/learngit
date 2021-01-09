#ifndef MODIFYUSER_H
#define MODIFYUSER_H

#include <QWidget>
#include "ui_modifyuser.h"
#include "DB.h"
#include <QLineEdit>

#pragma execution_character_set("utf-8") 
class modifyUser : public QWidget
{
	Q_OBJECT

public:
	modifyUser(QWidget *parent = 0);
	~modifyUser();
	bool Otherchar(char* str);
	QLineEdit *lineEdit_user;
private slots:
	void on_btnSure_clicked();
	void on_btnCancel_clicked();
	void on_btnClose_clicked();
private:
	Ui::modifyUser ui;
	
};

#endif // MODIFYUSER_H
