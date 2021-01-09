#pragma once
#include <windows.h>
#include <DbgHelp.h>
#pragma comment(lib,"Dbghelp.lib")
long  __stdcall CrashInfocallback(_EXCEPTION_POINTERS *pexcp)
{
	//创建 Dump 文件
	HANDLE hDumpFile = ::CreateFile(
		"Error.dmp",
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