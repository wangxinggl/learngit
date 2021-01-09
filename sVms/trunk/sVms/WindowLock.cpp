#include "WindowLock.h"
#include <QPalette>
#include "DB.h"
#include "appinit.h"


WindowLock::WindowLock(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setProperty("canMove", true);
	setStyleSheet(".WindowLock{border:2px solid black;}");
	
}

WindowLock::~WindowLock()
{
}

void WindowLock::on_btnSure_clicked()
{
	QString PassWord = ui.lineEdit_Password->text();
	ui.label_displayErr->setStyleSheet("QLabel{color:red;}");
	if (PassWord == NULL)
	{
		ui.label_displayErr->setText(QObject::tr("请输入密码"));
		
		return;
		
	}

	DB *db = new DB;
	bool ret = db->CheckLock(PassWord);
	if (ret)
	{

		this->close();
	}
	else
	{
		ui.lineEdit_Password->clear();
		ui.label_displayErr->setText(QObject::tr("无效密码"));

	}

}
