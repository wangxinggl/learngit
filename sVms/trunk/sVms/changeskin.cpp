#include "changeskin.h"
#include <QDebug>
#include <QMessageBox>
#include <QObject>

changeSkin::changeSkin(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() &~ Qt::WindowMaximizeButtonHint);
	
	myHelper::FormInCenter(this);
	
	//label点击事件
	connect(ui.black_label,SIGNAL(on_clicked()),this,SLOT(on_black_label_clicked()));
	connect(ui.hui_label,SIGNAL(on_clicked()),this,SLOT(on_hui_label_clicked()));
	connect(ui.mei_label,SIGNAL(on_clicked()),this,SLOT(on_mei_label_clicked()));
	connect(ui.sky_label,SIGNAL(on_clicked()),this,SLOT(on_sky_label_clicked()));
	connect(ui.gray_label, SIGNAL(on_clicked()), this, SLOT(on_gray_label_clicked()));
	connect(ui.wathetgray_label, SIGNAL(on_clicked()), this, SLOT(on_wathetgray_label_clicked()));
	connect(ui.darkgray_label, SIGNAL(on_clicked()), this, SLOT(on_darkgray_label_clicked()));
	connect(ui.sliver_label, SIGNAL(on_clicked()), this, SLOT(on_sliver_label_clicked()));
	connect(ui.flatblack_label, SIGNAL(on_clicked()), this, SLOT(on_flatblack_label_clicked()));
	connect(ui.darkblack_label, SIGNAL(on_clicked()), this, SLOT(on_darkblack_label_clicked()));
	
	this->setWindowFlags(Qt::FramelessWindowHint);
	
	this->setProperty("canMove", true);
}

changeSkin::~changeSkin()
{

}


//切换黑色皮肤
void changeSkin::on_black_label_clicked()
{
	 myHelper::SetStyle("psblack");//黑色风格
	/*m_videoLine->m_timeScaleControlWidget->color = QColor(31, 32, 38);
	m_videoLine->m_timeScaleControlWidget->repaint();
	m_videoLine->m_timeHeaderWidget->color = QColor(31, 32, 38);
	m_videoLine->m_timeHeaderWidget->repaint();
	m_videoLine->m_timeLineWidget->color = QColor(31, 32, 38);*/
	
}

//切换深蓝色皮肤
void changeSkin::on_hui_label_clicked()
{
	myHelper::SetStyle("darkblue");//灰色风格
}

//切换浅蓝色风格
void changeSkin::on_sky_label_clicked()
{
	myHelper::SetStyle("wathetblue");//天蓝色风格
}

//切换蓝色风格
void changeSkin::on_mei_label_clicked()
{
	 myHelper::SetStyle("blue");//蓝色风格
}

//切换灰色皮肤
void changeSkin::on_gray_label_clicked()
{
	myHelper::SetStyle("gray");
}

//切换浅灰色
void changeSkin::on_wathetgray_label_clicked()
{
	myHelper::SetStyle("wathetgray");
}

//切换深灰色
void changeSkin::on_darkgray_label_clicked()
{
	myHelper::SetStyle("darkgray");
}

//切换银色
void changeSkin::on_sliver_label_clicked()
{
	myHelper::SetStyle("sliver");
}

//切换浅黑色风格
void changeSkin::on_flatblack_label_clicked()
{
	myHelper::SetStyle("flatblack");
}
//切换深黑色风格
void changeSkin::on_darkblack_label_clicked()
{
	myHelper::SetStyle("darkblack");
}


void changeSkin::on_btnClose_clicked()
{
	close();
}