#include "OneVideo.h"
#include <QStatusBar>

OneVideo::OneVideo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	createTab();
	setCentralWidget(ui.m_displayScreen);
	setStyleSheet(".OneVideo{background:transparent;border:2px solid black;}");
	ipAddr == NULL;
	this->statusBar()->hide();
}

OneVideo::~OneVideo()
{
}

void OneVideo::createTab()
{
	this->statusBar()->setSizeGripEnabled(false);//去掉状态栏右下角的三角
	speed_Label = new QLabel();
	this->statusBar()->addPermanentWidget(speed_Label);
	speed_Label->setText(QObject::tr("Normal   "));

	ip_Label = new QLabel();
	this->statusBar()->addWidget(ip_Label);
	ip_Label->setText(QObject::tr("IP:"));

	ch_Label = new QLabel();
	this->statusBar()->addWidget(ch_Label);
	ch_Label->setText(QObject::tr("Channel:"));

	m_displayScreen = new QLabel();
	m_displayScreen = ui.m_displayScreen;
	
}

void OneVideo::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit clickedEvent();
	}
}