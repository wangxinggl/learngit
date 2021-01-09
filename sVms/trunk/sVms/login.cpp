#include "login.h"
#include <QMessageBox>
#include <assert.h>
#include "DB.h"
#include "JLNDevice.h"
#include <Windows.h>
#include "myhelper.h"
#include "iconhelper.h"
#include <qmutex.h>
#include <WinNls.h>
#include <QCoreApplication>
QMutex login_mutex;
#pragma comment(lib, "Shell32.lib")




Login::Login(QDialog *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle(QObject::tr("登录"));
	setWindowFlags(windowFlags() &~ Qt::WindowMaximizeButtonHint);
	initForm();
	loadcfg();
	//ui->userComboBox  用户名输入框QComboBox   ui->passwordEdit 密码输入框 QLineEdit      
	connect(ui.txtUserName,SIGNAL(currentTextChanged(QString)),
		ui.txtUserPwd,SLOT(clear()));

	connect(ui.txtUserName,SIGNAL(currentIndexChanged(int)),
		this,SLOT(setlogint(int)));
	if (autologin == "true")
		m_isAutoLogin = 2;
	else 
		m_isAutoLogin = 0;
	
	//initSDK();
	
	
	int addWidth = 20;
	int addHeight = 10;
	int rbtnWidth = 15;
	int ckWidth = 13;
	int scrWidth = 12;
	int borderWidth = 3;
	
	ui.txtUserPwd->setFocus();
	connect(
		ui.txtUserPwd,
		SIGNAL(returnPressed()),
		ui.btnLogin,
		SIGNAL(clicked()),
		Qt::UniqueConnection
		);

	
	GetLanguageMode();
	if (g_IsEnglish)
	{
		translator.load("svms_en.qm");
		qApp->installTranslator(&translator);
		ui.retranslateUi(this);
		
	}


}

Login::~Login()
{

}

bool Login::ChangeRemberStateSlots(int state)
{
	if (state != Qt::Checked)
	{
		return false;
	}

	UserName = ui.txtUserName->currentText();
	PassWord = ui.txtUserPwd->text();
	if (UserName.isEmpty() || PassWord.isEmpty())
	{
		
		myHelper::ShowMessageBoxWarning(QObject::tr("用户名或密码输入不能为空！"));
		return false;
	}
	else if (!Otherchar(PassWord.toLatin1().data()))
	{

		myHelper::ShowMessageBoxWarning(QObject::tr("不能输入特殊字符"));
		return false;
	}

	DB *db = new DB;
	bool ret = db->CheckUser(UserName, PassWord);
	if (ret)
	{
		WriteInit("username", m_userNameList);
		WriteInit("password", m_passwdList);
		WriteInit("isrembered", m_isremberList);//可以在登录成功返回的地方记录
		WriteInit("autologin", m_autologin);
		
		
		Client::instance()->show();
		
		
	}
	else
	{

		//QMessageBox::warning(this, "Error", QObject::tr("用户名或者密码错误"));
		myHelper::ShowMessageBoxWarning(QObject::tr("用户名或者密码错误"));
		return false;


	}
	return true;
}
void Login::on_btnLogin_clicked()
{
	UserName = ui.txtUserName->currentText();
	PassWord = ui.txtUserPwd->text();
	if (UserName == NULL||PassWord == NULL)
	{
		//QMessageBox::warning(this,"Error",QObject::tr("输入不能为空"));
		myHelper::ShowMessageBoxWarning(QObject::tr("输入不能为空"));
		return;
	}
	else if (!Otherchar(PassWord.toLatin1().data()))
	{
		//QMessageBox::warning(this,"Error",QObject::tr("不能输入特殊字符"));
		myHelper::ShowMessageBoxWarning(QObject::tr("不能输入特殊字符"));
		return;
	}
	
	if(m_userNameList.contains(UserName)){
		for(int i=0;i<m_userNameList.size();i++){
			QString user = m_userNameList.at(i);
			if(user == UserName){
				m_userNameList.removeAt(i);
				m_passwdList.removeAt(i);
				m_isremberList.removeAt(i);
				m_autologin.removeAt(i);
				m_userNameList.push_front(UserName);
				m_passwdList.push_front(PassWord);
				m_isremberList.push_front(isrembered);
				m_autologin.push_front(autologin);
			}
		}
	}else{
		if(UserName != ""){
			m_userNameList.push_front(UserName);
			if(m_userNameList.size()>5)
				m_userNameList.pop_back();
			m_passwdList.push_front(PassWord);
			if(m_passwdList.size()>5)
				m_passwdList.pop_back();
		
			m_isremberList.push_front(isrembered);
			if(m_isremberList.size()>5)
				m_isremberList.pop_back();

			m_autologin.push_front(autologin);
			if (m_autologin.size() > 5)
			{
				m_autologin.pop_back();
			}
			
		}
	}

	
	DB *db = new DB;
	bool ret = db->CheckUser(UserName,PassWord);
	if (ret)
	{
		WriteInit("username",m_userNameList);
		WriteInit("password",m_passwdList);
		WriteInit("isrembered",m_isremberList);//可以在登录成功返回的地方记录
		WriteInit("autologin",m_autologin);
		this->close();
		Client::instance()->show();
		
	} 
	else
	{

		//QMessageBox::warning(this, "Error", QObject::tr("用户名或者密码错误"));
		myHelper::ShowMessageBoxWarning(QObject::tr("用户名或者密码错误"));
		return;
		
		
	}
	
}

bool Login::Otherchar(char* str)
{
	for (int ix = 0;str[ix] != '\0';ix++)
	{
		if (str[ix] >= '0'&&str[ix] <= '9'||
			str[ix] >= 'A' &&str[ix] <= 'Z'||
			str[ix] >= 'a' &&str[ix] <= 'z')
		{
			return true;
		}
	}
	return false;
}

void Login::on_checkBox_Auto_clicked()
{
	if(ui.checkBox_Auto->isChecked())
	{
		autologin = "true";
	}
	else
	{
		autologin = "false";
	}
}

void Login::on_checkBox_Pwd_clicked()
{
	if(ui.checkBox_Pwd->isChecked())
	{
		isrembered = "true";
	}
	else
	{
		ui.txtUserPwd->clear();
		isrembered  = "false";
	}
}

/*保存登录信息*/
void Login::WriteInit(QString key,QStringList value)
{
	QSettings *config = new QSettings(QCoreApplication::applicationDirPath()+"/"+"log.ini",QSettings::IniFormat);
	QVariant variant;
	variant.setValue(value);

	//将信息写入配置文件
	config->beginGroup("config");
	config->setValue(key,variant);
	config->endGroup();
	delete config;
}

void Login::setlogint(int index)
{
	if(m_passwdList.size()>index){
		 PassWord = m_passwdList.at(index);

		isrembered = m_isremberList.at(index);
		if(isrembered== "true")
		{
			ui.checkBox_Pwd->setChecked(true);//勾选记住用户名密码
			ui.txtUserPwd->setText(PassWord);
		}else{
			ui.checkBox_Pwd->setChecked(false);
			ui.txtUserPwd->setText("");
		}
	}
}

void Login::ReadInit(QString key, QStringList& value)
{
	value.clear();
	

	//创建配置文件操作对象
	QSettings *config = new QSettings(QCoreApplication::applicationDirPath() + "/" + "log.ini", QSettings::IniFormat);

	//读取配置信息

	QVariant variant = config->value(QString("config/") + key);
	value = variant.value<QStringList>();

}

void Login::loadcfg()
{
	
	ReadInit("username",m_userNameList);
	ReadInit("password",m_passwdList);
	ReadInit("isrembered",m_isremberList);
	ReadInit("autologin", m_autologin);

	ui.txtUserName->addItems(m_userNameList);
	if(m_userNameList.size()>0)
		UserName = m_userNameList.at(0);
	if(m_passwdList.size()>0)
		PassWord = m_passwdList.at(0);
	if(m_isremberList.size()>0)
		isrembered = m_isremberList.at(0);
	if (m_autologin.size() > 0)
	{
		autologin = m_autologin.at(0);
	}
	if(isrembered == "true")
	{
		ui.checkBox_Pwd->setChecked(true);
		ui.txtUserName->setCurrentText(UserName);
		ui.txtUserPwd->setText(PassWord);
		
	}
	if (autologin == "true")
	{
		ui.checkBox_Auto->setChecked(true);
	}

}


void Login::sendSignal()
{
	QString UserName = ui.txtUserName->currentText();
	QString PassWord = ui.txtUserPwd->text();
	emit SendUserMessage(UserName,PassWord);
}

void Login::initForm()
{
	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	
	
}


/*
void Login::on_btnClose_clicked()
{
	close();
}
*/
void Login::on_btnresgister_clicked()
{
	close();
}

//判断操作系统是中文还是英文
void Login::GetLanguageMode()
{
	LANGID langID = GetSystemDefaultLangID(); //得到系统语言
	switch (langID)
	{
	case 0x0804:// Chinese (PRC)
	case 0x1004://Singapore
		g_IsEnglish = 0;
		break;
		//case 0x0419 :// Russian
		//	g_IsEnglish = 2;
		//	break;
		//case 0x0410 :
		//	g_IsEnglish =3;//意大利
		//	break;
		//case 0x040c :
		//	g_IsEnglish=4;//法国
		//	break;
		//case 0x0415 :   //波兰语
		//	g_IsEnglish=5;
		//	break;
		//case 0x0411:   //Japanese
		//	g_IsEnglish = 6;
		//	break;
		//case 0x0412:  //Korean
		//	g_IsEnglish = 7;
		//	break;
	case 0x0404:	//(Taiwan Region)
	case 0x0c04:	//Hong Kong SAR
		g_IsEnglish = 8;
		break;
	default:     // English
		g_IsEnglish = 1;
		break;
	}
}