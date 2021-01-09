#include "MessBox.h"
#include "myhelper.h"

#pragma execution_character_set("utf-8")

MessBox::MessBox(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//设置窗体标题栏隐藏
	this->setWindowFlags(Qt::FramelessWindowHint);
	//关联关闭按钮
	connect(ui.btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(close()));
	//窗体居中显示
	myHelper::FormInCenter(this);
	setStyleSheet(".MessBox{border:2px solid black;}");
	this->setProperty("canMove", true);
	
}

MessBox::~MessBox()
{
}

void MessBox::on_btnMenu_Close_clicked()
{
	close();
}

void MessBox::SetMessage(const QString &msg, int type)
{
	if (type == 0) {
		ui.labIcoMain->setStyleSheet("border-image: url(:/res/SoftIcon/info.png);");
		ui.btnCancel->setVisible(false);
		ui.lab_Title->setText(QObject::tr("提示"));
	}
	else if (type == 1) {
		ui.labIcoMain->setStyleSheet("border-image: url(:/res/SoftIcon/gantanhao1.png);");
		ui.btnCancel->setVisible(false);
		ui.lab_Title->setText(QObject::tr("警告"));
	}
	else if (type == 2) {
		ui.labIcoMain->setStyleSheet("border-image: url(:/res/SoftIcon/error.png);");
		ui.btnCancel->setVisible(false);
		ui.lab_Title->setText(QObject::tr("错误"));
	}
	else if (type == 3)
	{
		ui.labIcoMain->setStyleSheet("border-image: url(:/res/SoftIcon/question.png);");
		connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(onSure()));
		ui.lab_Title->setText(QObject::tr("询问"));
	}
	ui.labInfo->setText(msg);
}


void MessBox::onSure()
{
	
	done(1);
	close();
}

