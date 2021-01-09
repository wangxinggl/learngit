#include "OneVideo.h"
#include <QStatusBar>

OneVideo::OneVideo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	createTab();
	setCentralWidget(ui.m_displayScreen);
	setStyleSheet(".OneVideo{background:transparent;border:2px solid black;}");
	
}

OneVideo::~OneVideo()
{
}

void OneVideo::createTab()
{
	this->statusBar()->setSizeGripEnabled(false);//去掉状态栏右下角的三角
	this->statusBar()->setWindowOpacity(0.5);

	ch_Label = new QLabel();
	this->statusBar()->addPermanentWidget(ch_Label);
	ch_Label->setText("00:00:00/00:00:00");

	m_displayScreen = new QLabel();
	m_displayScreen = ui.m_displayScreen;
	
}