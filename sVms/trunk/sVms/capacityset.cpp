#include "capacityset.h"


capacitySet::capacitySet(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() &~ Qt::WindowMaximizeButtonHint);
	m_recNum = m_unRecNum = 15;
	ui.lineEdit_Rec->setText(QString::number(m_recNum));
	ui.lineEdit_unRec->setText(QString::number(m_unRecNum));

	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint);
	
}

capacitySet::~capacitySet()
{

}


void capacitySet::on_btnSet_clicked()
{
	m_unRecNum = ui.lineEdit_unRec->text().toInt();
	m_recNum = ui.lineEdit_Rec->text().toInt();
	this->close();
}

void capacitySet::on_btnClose_clicked()
{
	close();
}