#ifndef ADDUSER_H
#define ADDUSER_H

#include <QWidget>
#include "ui_adduser.h"
#include "clickedlabel.h"

#pragma execution_character_set("utf-8") 
class addUser : public QWidget
{
	Q_OBJECT

public:
	addUser(QWidget *parent = 0);
	~addUser();
	bool Otherchar(char* str);




private slots:
	void on_btnOk_clicked();
	void on_btnCancel_clicked();
	void on_btnClose_clicked();
signals:
	void sendMsg(bool);
private:
	Ui::addUser ui;

	
};

#endif // ADDUSER_H
