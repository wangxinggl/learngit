#include "equimentlist.h"

equimentList::equimentList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_WState_WindowOpacitySet);
	setWindowOpacity(0.4);
}

equimentList::~equimentList()
{

}

void equimentList::on_btnClose_clicked()
{
	this->close();
}