#ifndef UNRECOGNITION_H
#define UNRECOGNITION_H

#include <QWidget>
#include "ui_unrecognition.h"
#include <QLabel>

class unRecognition : public QWidget
{
	Q_OBJECT

public:
	unRecognition(QWidget *parent = 0);
	~unRecognition();

public:
	Ui::unRecognition ui;
	QLabel *displayLabel;
	QLabel *displayLabelTime;
};

#endif // UNRECOGNITION_H
