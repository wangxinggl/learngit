
#include "login.h"
#include <QtWidgets/QApplication>
#include "appinit.h"
#include "Dmp3b.h"
#include <windows.h>
#include <DbgHelp.h>
#pragma comment(lib,"Dbghelp.lib")
#include "myhelper.h"

long  __stdcall CrashInfocallback(_EXCEPTION_POINTERS *pexcp)
{
	//创建 Dump 文件
	HANDLE hDumpFile = ::CreateFile(
		"ERROR.DMP",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if (hDumpFile != INVALID_HANDLE_VALUE)
	{
		//Dump信息
		MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
		dumpInfo.ExceptionPointers = pexcp;
		dumpInfo.ThreadId = GetCurrentThreadId();
		dumpInfo.ClientPointers = TRUE;
		//写入Dump文件内容
		::MiniDumpWriteDump(
			GetCurrentProcess(),
			GetCurrentProcessId(),
			hDumpFile,
			MiniDumpNormal,
			&dumpInfo,
			NULL,
			NULL
			);
	}
	return 0;
}


int main(int argc, char *argv[])
{
	
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CrashInfocallback);
	
	QApplication a(argc, argv);	
	
	g_pDatabase = new DB;
	g_pDatabase->createConnection();
	
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
