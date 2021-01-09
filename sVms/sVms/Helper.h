#pragma once
#include <windows.h>
#include <DbgHelp.h>
#pragma comment(lib,"Dbghelp.lib")
long  __stdcall CrashInfocallback(_EXCEPTION_POINTERS *pexcp)
{
	//���� Dump �ļ�
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
		//Dump��Ϣ
		MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
		dumpInfo.ExceptionPointers = pexcp;
		dumpInfo.ThreadId = GetCurrentThreadId();
		dumpInfo.ClientPointers = TRUE;
		//д��Dump�ļ�����
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