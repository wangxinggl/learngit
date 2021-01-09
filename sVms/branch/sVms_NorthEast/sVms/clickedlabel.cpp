#include "clickedlabel.h"
#include <QMouseEvent>

ClickedLabel::ClickedLabel(QWidget *parent)
	: QLabel(parent)
{
	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::black);
	setPalette(pa);
}

ClickedLabel::ClickedLabel(const QString &text, QWidget *parent):
QLabel(parent)
{
	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::blue);
	setPalette(pa);
	setText(text);
}
ClickedLabel::~ClickedLabel()
{

}

void ClickedLabel::mousePressEvent(QMouseEvent *ev)
{
	
	if (ev->button() == Qt::LeftButton)
	{
		
		emit on_clicked();
	}
		
	

}

/*
void ClickedLabel::enterEvent(QEvent *)
{
	//QPalette pa;
	//pa.setColor(QPalette::WindowText, Qt::red);
	//setPalette(pa);
	
}

void ClickedLabel::leaveEvent(QEvent *)
{
	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::black);
	setPalette(pa);
}*/

void ClickedLabel::mouseReleaseEvent(QMouseEvent *ev)
{
	if (ev->button() == Qt::LeftButton)
	{
		QPalette pa;
		pa.setColor(QPalette::WindowText, Qt::red);
		setPalette(pa);
	}
		
}