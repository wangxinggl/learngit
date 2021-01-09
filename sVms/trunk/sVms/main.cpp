
#include "login.h"
#include <QtWidgets/QApplication>
#include "appinit.h"
#include "Helper.h"
#include <QMessageBox>



int main(int argc, char *argv[])
{
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CrashInfocallback);
	
	QApplication a(argc, argv);
	
	DB db;
	db.createConnection();
	
	Login w;
	w.setWindowIcon(QIcon("main.ico"));
	a.setFont(QFont("Microsoft Yahei", 9));
	myHelper::SetStyle(":/res/qss/darkblack.css");
	AppInit::Instance()->start();
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);
	if (w.ChangeRemberStateSlots(w.m_isAutoLogin))
	{
		w.close();
	}
	else
	{
		w.show();
	}

	
	return a.exec();
}
