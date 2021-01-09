#include "adduser.h"
#include <QMessageBox>
#include "DB.h"
#include "myhelper.h"
#include <QObject>

addUser::addUser(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setProperty("canMove", true);
}

addUser::~addUser()
{

}

void addUser::on_btnOk_clicked()
{
	
	QString userName = ui.CustomerName->text();
	QString Password = ui.CustomerPwd->text();
	QString PassReWord = ui.CustomerRePwd->text();
	if (userName == NULL||PassReWord == NULL||PassReWord==NULL)
	{
		//QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("输入不能为空"));
		myHelper::ShowMessageBoxWarning(QObject::tr("输入不能为空"));
		return;
	}
	else if (!Otherchar(Password.toLatin1().data())||!Otherchar(PassReWord.toLatin1().data()))
	{
		//QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("不能输入特殊字符"));
		myHelper::ShowMessageBoxWarning(QObject::tr("不能输入特殊字符"));
		return;
	}
	else if (Password != PassReWord)
	{
		//QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("两次输入密码不一致"));
		myHelper::ShowMessageBoxWarning(QObject::tr("两次输入密码不一致"));
		return;
	}
	if (Password.size() > 16 || Password.size() < 6)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("密码长度必须在6到16之间!"));
		return;
	}
	DB *db = new DB;
	bool ret = db->AddUser(userName,Password);
	if (!ret)
	{
		
		myHelper::ShowMessageBoxWarning(QObject::tr("用户已存在"));
		return;
	}
	else
	{
		emit sendMsg(true);
		close();
		return;
	}

}

bool addUser::Otherchar(char* str)
{
	int ix;
	for (ix = 0;str[ix] != '\0';ix++)
	{
		if (str[ix] >= '0'&&str[ix] <= '9'||
			str[ix] >= 'A' &&str[ix] <= 'Z'||
			str[ix] >= 'a' &&str[ix] <= 'z')
		{
			ix++;
		}
		
	}
	if (ix  == sizeof(str))
	{
		return true;
	}
	return false;
}

void addUser::on_btnCancel_clicked()
{
	close();
}

void addUser::on_btnClose_clicked()
{
	close();
}