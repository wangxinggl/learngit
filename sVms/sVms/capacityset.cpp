#include "capacityset.h"
#include "myhelper.h"

capacitySet::capacitySet(QWidget *parent)
	: QWidget(parent)
	, m_recNum(0)
	, m_unRecNum(0)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() &~ Qt::WindowMaximizeButtonHint);
	
	LoadConfig();
	ui.lineEdit_Rec->setText(QString::number(m_recNum));
	ui.lineEdit_unRec->setText(QString::number(m_unRecNum));

	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint);	
}

capacitySet::~capacitySet()
{

}

void capacitySet::on_btnSet_clicked()
{
	if (ui.lineEdit_Rec->text().isEmpty()||ui.lineEdit_unRec->text().isEmpty())
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("输入不能为空"));
		return;
	}
	if (ui.lineEdit_Rec->text().toInt()<=0 || ui.lineEdit_unRec->text().toInt()<=0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("输入数据至少为1"));
		return;
	}
	m_unRecNum = ui.lineEdit_unRec->text().toInt();
	m_recNum = ui.lineEdit_Rec->text().toInt();
	SetConfig();
	this->close();
}

void capacitySet::on_btnClose_clicked()
{
	close();
}

void capacitySet::LoadConfig()
{
	QString file;
	file = QString("%1\\LoginMsg.ini").arg(QCoreApplication::applicationDirPath());
	m_recNum = ::GetPrivateProfileInt("CapShowMsg", "RecNum", 0, file.toLatin1().data());
	m_unRecNum = ::GetPrivateProfileInt("CapShowMsg", "UnRecNum", 0, file.toLatin1().data());
}

void capacitySet::SetConfig()
{
	QString strfile;
	strfile = QString("%1\\LoginMsg.ini").arg(QCoreApplication::applicationDirPath());

	QString csValue;
	csValue = QString("%1").arg(m_recNum);
	::WritePrivateProfileString("CapShowMsg", "RecNum", csValue.toLatin1().data(), strfile.toLatin1().data());

	csValue = QString("%1").arg(m_unRecNum);
	::WritePrivateProfileString("CapShowMsg", "UnRecNum", csValue.toLatin1().data(), strfile.toLatin1().data());
}
