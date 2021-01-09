#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include "ui_display.h"

 
class Display : public QWidget
{
	Q_OBJECT

public:
	Display(QWidget *parent = 0);
	~Display();
	HWND hWnd;
private:
	Ui::Display ui;
};

#endif // DISPLAY_H
