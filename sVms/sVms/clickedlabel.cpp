#include "clickedlabel.h"
#include <QMouseEvent>

ClickedLabel::ClickedLabel(QWidget *parent)
	: QLabel(parent)
{
	
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

