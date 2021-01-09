#include "unrecognition.h"

unRecognition::unRecognition(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	displayLabel = new QLabel();
	displayLabelTime = new QLabel();
	displayLabel = ui.label;
	displayLabelTime = ui.label_displayTime;
	
}

unRecognition::~unRecognition()
{

}
