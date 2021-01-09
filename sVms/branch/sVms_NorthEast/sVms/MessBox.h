#pragma once

#include <QDialog>
#include <QWidget>

#include "ui_MessBox.h"

class MessBox : public QDialog
{
	Q_OBJECT

public:
	MessBox(QWidget *parent = Q_NULLPTR);
	~MessBox();
	void SetMessage(const QString &msg, int type);
	
private slots:
	void on_btnMenu_Close_clicked();
	void onSure();

private:
	Ui::MessBox ui;

	
};
