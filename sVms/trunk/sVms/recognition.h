#ifndef RECOGNITION_H
#define RECOGNITION_H

#include <QWidget>
#include "ui_recognition.h"
#include <QLabel>
#include <QProgressBar>
#include <QLineEdit>

class Recognition : public QWidget
{
	Q_OBJECT

public:
	Recognition(QWidget *parent = 0);
	~Recognition();
	QLabel *displayPic;
	QLabel *displayLib;
	QLabel *displayName;
	QLabel *displayNo;
	QLabel *displayDevice;
	QLabel *displayType;
	QLabel *displayTime;
	QProgressBar *g_progressBar;
	QLabel *displayProgress;
private:
	Ui::Recognition ui;
	
};

#endif // RECOGNITION_H
