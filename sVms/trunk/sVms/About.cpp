#include "About.h"

About::About(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	
}

About::~About()
{
}


void About::on_btnClose_clicked()
{
	close();
}