#ifndef USERMGT_H
#define USERMGT_H

#include <QWidget>
#include "ui_usermgt.h"
#include "adduser.h"
#include "modifyuser.h"
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QItemSelectionModel>


#pragma execution_character_set("utf-8") 
class UserMgt : public QWidget
{
	Q_OBJECT

public:
	UserMgt(QWidget *parent = 0);
	~UserMgt();
	void initFresh();
	void initSearchButton();//…Ë÷√À—À˜øÚ—˘ Ω
private slots:
	void on_btnAdd_clicked();
	void on_btnModify_clicked();
	void on_btnDel_clicked();
	void slotRowDoubleClicked();
	void on_btnSearch_clicked();
	void timerupdate();

	void getMsg(bool Flag);
private:
	Ui::UserMgt ui;
	QSqlTableModel *model;
	modifyUser *mod;
	addUser *add;

};

#endif // USERMGT_H
