#ifndef EQUIMENTLIST_H
#define EQUIMENTLIST_H

#include <QWidget>
#include "ui_equimentlist.h"


class equimentList : public QWidget
{
	Q_OBJECT

public:
	equimentList(QWidget *parent = 0);
	~equimentList();
private slots:
	void on_btnClose_clicked();
private:
	Ui::equimentList ui;
	
};

#endif // EQUIMENTLIST_H
