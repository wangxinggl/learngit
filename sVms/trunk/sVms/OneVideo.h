#pragma once

#include <QMainWindow>
#include "ui_OneVideo.h"
#include <QLabel>

class OneVideo : public QMainWindow
{
	Q_OBJECT

public:
	OneVideo(QWidget *parent = Q_NULLPTR);
	~OneVideo();
	void createTab();
private:
	Ui::OneVideo ui;
public:
	QLabel *ch_Label;
	QLabel *m_displayScreen;
};
