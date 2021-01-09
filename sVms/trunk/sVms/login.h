#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "ui_login.h"
#include "client.h"
#include <QSettings>
#include <QObject>
#include<QDialog>
#include <QTranslator>

class Login : public QDialog
{
	Q_OBJECT

public:
	Login(QDialog *parent = 0);
	~Login();
	void initForm();
	bool Otherchar(char* str);
	void WriteInit(QString key,QStringList value);
	void ReadInit(QString, QStringList&);
    void loadcfg();
	void GetLanguageMode();

	int m_isAutoLogin;
public slots:
	void on_btnLogin_clicked();
	void on_checkBox_Pwd_clicked();
	void on_checkBox_Auto_clicked();

	void setlogint(int index);

	//void on_btnClose_clicked();
	void on_btnresgister_clicked();
	bool ChangeRemberStateSlots(int state);
	//void initSDK();
public slots:
	void sendSignal();
	
signals:
	void SendUserMessage(QString, QString);
private:
	Ui::Login ui;
	
	
	QString UserName;
	QString PassWord;
	int g_IsEnglish;

	QString		AutoLogin;
	QString		RemeberPasswd;

	QStringList m_passwdList;//保存密码
	QStringList m_IPList;//保存IP
	QStringList m_isremberList;
	QStringList m_userNameList;
	QStringList m_autologin;
	QString isrembered;//是否记住密码
	QString autologin;//是否自动登录
	
	QTranslator translator;
	
};

#endif // LOGIN_H
