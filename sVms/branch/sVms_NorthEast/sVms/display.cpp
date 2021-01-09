#include "display.h"



Display::Display(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	hWnd = (HWND)ui.label->winId();
}

Display::~Display()
{

}
