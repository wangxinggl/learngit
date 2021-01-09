#include "ModifyChannel.h"
#include "table_structs.h"
#include "DB.h"
#include "myhelper.h"
#include "client.h"

extern Client* g_pInstance;
ModifyChannel::ModifyChannel(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	initForm();
	
	setStyleSheet(".ModifyChannel{border:2px solid black;}");
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setProperty("canMove", true);

}

ModifyChannel::~ModifyChannel()
{
}

void ModifyChannel::initForm()
{
	displayChannelNum = new QLineEdit;
	displayChannelNum = ui.lineEdit_Num;
	displayChannelName = new QLineEdit;
	displayChannelName = ui.lineEdit_Name;
}

void ModifyChannel::on_btnSure_clicked()
{
	if (g_pInstance->m_TabWidget.m_bPreview != FALSE)
	{
		g_pInstance->m_pPreviewPro->StopAllWatch();
	}

	int channelNum = ui.lineEdit_Num->text().toInt();
	QString channelName = ui.lineEdit_Name->text();
	int ret = g_pDatabase->ChangeChannelInfo(channelNum, channelName, m_nChannelType);
	if (ret)
	{
		myHelper::ShowMessageBoxInfo(QObject::tr("修改信息成功!"));
		g_pInstance->OnReFreshOtherTree();

		close();
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("修改信息失败!"));
	}
}
void ModifyChannel::on_btnCancel_clicked()
{
	close();
}
void ModifyChannel::on_btnClose_clicked()
{
	close();
}
