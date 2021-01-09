#include "VMTools.h"
#include <QColor>
#include "myhelper.h"

VMTools::VMTools(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	hide();
	setStyleSheet(".VMTools{ border:1px solid black;}");
	
	m_record = new	QPushButton;
	m_record = ui.recordBtn;
	m_sound = new QPushButton;
	m_sound = ui.soundBtn;
	m_talk = new QPushButton;
	m_talk = ui.talkBtn;

	m_labelNum = new QLabel;
	m_labelNum = ui.label_Num;
	m_labelIP = new QLabel;
	m_labelIP = ui.label_IP;
	//setAutoFillBackground(true);
	
	
}

VMTools::~VMTools()
{
}

void VMTools::paintEvent(QPaintEvent *event)
{
	
	Q_UNUSED(event);
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	// QColor最后一个参数80代表alpha通道，一般用作透明度
	painter.fillRect(this->rect(), QColor(0, 0, 0, 0.2));


}

void VMTools::on_btnClose_clicked()
{
	emit StopWatchEvent();
}

void VMTools::on_cameraBtn_clicked()
{
	emit	 screenshotEvent();
}

void VMTools::on_recordBtn_clicked()
{
	emit videotapeEvent();
}

void VMTools::on_soundBtn_clicked()
{
	emit soundEvent();
}

void VMTools::on_talkBtn_clicked()
{
	emit talkEvent();
}