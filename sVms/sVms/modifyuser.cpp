#include "modifyuser.h"
#include "DB.h"
#include <QMessageBox>
#include "myhelper.h"

modifyUser::modifyUser(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() &~ Qt::WindowMaximizeButtonHint);

	this->setProperty("canMove", true);

	this->setWindowFlags(Qt::FramelessWindowHint);

	lineEdit_user = new QLineEdit();
	lineEdit_user = ui.lineEdit;
}

modifyUser::~modifyUser()
{

}

void modifyUser::on_btnSure_clicked()
{
	QString name = ui.lineEdit->text();
	QString oldPassword = ui.lineEditOldPed->text();
	QString newPassword = ui.lineEditNewPwd->text();
	QString newRePassword = ui.lineEditReNewPwd->text();
	if (name  == NULL||oldPassword == NULL||newPassword == NULL||newRePassword == NULL)
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("输入不能为空"));
		myHelper::ShowMessageBoxWarning(QObject::tr("输入不能为空!"));
		return;
	}
	else if (!Otherchar(newPassword.toLocal8Bit().data())||!Otherchar(newRePassword.toLocal8Bit().data()))
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("不能输入特殊字符"));
		myHelper::ShowMessageBoxWarning(QObject::tr("不能输入特殊字符!"));
		return;
	}
	else if (oldPassword == newPassword)
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("不能输入与之前相同的密码"));
		myHelper::ShowMessageBoxWarning(QObject::tr("不能输入与之前相同的密码!"));
		return;
	}
	else if (newPassword != newRePassword)
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("两次输入密码不一致"));
		myHelper::ShowMessageBoxWarning(QObject::tr("两次输入密码不一致!"));
		return;
	}
	else if (newPassword.size()>16||newPassword.size()<6)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("密码长度必须在6到16之间!"));
		return;
	}
	bool ret = g_pDatabase->CheckUser(name, oldPassword);
	if (!ret)
	{
	
		myHelper::ShowMessageBoxWarning(QObject::tr("旧密码或者用户信息输入不正确!"));
		return;
	}
	else
	{
		ret = g_pDatabase->ModifyUser(name, newPassword);
		if (!ret)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("修改密码失败"));
			return;
		}
		else
		{
			myHelper::ShowMessageBoxInfo(QObject::tr("修改用户信息成功!"));
			close();
		}
		
	}
}

bool modifyUser::Otherchar(char* str)
{
	for (int ix = 0; str[ix] != '\0'; ix++)
	{
		if ((str[ix] >= '0'&& str[ix] <= '9') || (str[ix] >= 'A' && str[ix] <= 'Z') || (str[ix] >= 'a' && str[ix] <= 'z'))
		{
			return TRUE;
		}
	}
	return FALSE;
}


void modifyUser::on_btnCancel_clicked()
{
	close();
}

void modifyUser::on_btnClose_clicked()
{
	close();
}