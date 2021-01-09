#pragma once

#include <QMainWindow>
#include "ui_OneVideo.h"
#include <QLabel>
#include <QMouseEvent>

class OneVideo : public QMainWindow
{
	Q_OBJECT

public:
	OneVideo(QWidget *parent = Q_NULLPTR);
	~OneVideo();
	void createTab();
protected:
	void mousePressEvent(QMouseEvent *event);
signals:
	void clickedEvent(); //点击信号
private:
	Ui::OneVideo ui;
public:
	QString ipAddr;
	QLabel *speed_Label;
	QLabel *m_displayScreen;
	QLabel *ip_Label;
	QLabel *ch_Label;
};
