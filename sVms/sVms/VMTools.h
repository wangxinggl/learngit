#pragma once

#include <QDialog>
#include "ui_VMTools.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QLabel>

class VMTools : public QDialog
{
	Q_OBJECT

public:
	VMTools(QWidget *parent = Q_NULLPTR);
	~VMTools();
	void paintEvent(QPaintEvent *event);
signals:
	void StopWatchEvent();           //子窗口的关闭码流信号信号
	void screenshotEvent();			 //截屏信号
	void videotapeEvent();           //录像信号
	void soundEvent();
	void talkEvent();
private slots:
	void on_btnClose_clicked();
	void on_cameraBtn_clicked();
	void on_recordBtn_clicked();
	void on_soundBtn_clicked();
	void on_talkBtn_clicked();
private:
	Ui::VMTools ui;
public:
	QPushButton *m_record;
	QPushButton *m_sound;
	QPushButton *m_talk;
	QLabel *m_labelNum;
	QLabel *m_labelIP;
};
