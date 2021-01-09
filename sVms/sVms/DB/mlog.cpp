#include "stdio.h"
#include <string.h>
#include <afxmt.h>
#include <stdarg.h>
//#include "../stdafx.h"
#include "mlog.h"
#include <time.h>

#pragma warning(disable:4996) 

bool mlogInited =false;
FILE *mlogLogFp = NULL;
int mlogmask = 0xff;		//print all log
CRITICAL_SECTION mlogmutex;
long lMlogSize = 0;
char szmoduleDir[1024]; // module path without '\' at the end
char* strLevel[]={
	"EMERG",
	"ALERT",
	"CRIT",
	"ERR",
	"WARNING",
	"NOTICE",
	"INFO",
	"DEBUG"
};
int mlogInit(char *localFile)
{
	if (mlogInited)
    {
        return LOG_ALREADY_INITED;
    }

	if (NULL == (mlogLogFp = fopen(localFile, "a")))
    {
        return LOG_ERROR;
    }

	fseek( mlogLogFp, 0L, SEEK_END );
	if ( ( lMlogSize = ftell(mlogLogFp) ) < 0)
		return LOG_GETSIZE_ERROR;
	
	InitializeCriticalSection(&mlogmutex);
	mlogInited = true;

	char szlogFile[1024];
	strcpy(szlogFile, localFile);
	char *pdest;
	pdest = strrchr( szlogFile, '\\' );
	if ( pdest != NULL )
	{
		*pdest = '\0';
		strcpy(szmoduleDir, szlogFile);
	}
//	else
	//	strcpy(szmoduleDir, GetModuleFileDirectory().c_str());

    return 0;
}

int mlogClose()
{
	if (!mlogInited)
    {
        return LOG_NOT_INITED;
    }
	fclose(mlogLogFp);
	DeleteCriticalSection(&mlogmutex);
	mlogInited = false;

	return 0;
}

void mlog(unsigned int level,const char *format_str,...)
{
	if (!mlogInited)
    {
        return ;
    }
	if(!(level&mlogmask))
		return;
	if(level < LOG_EMERG || level > LOG_DEBUG)
		return;

	EnterCriticalSection(&mlogmutex);
	if (lMlogSize >= MAX_CLIENT_LOGFILE_SIZE)
	{
		fclose(mlogLogFp);
		mlogLogFp = NULL;
		mlogRotate();
		lMlogSize = 0;
	}

	va_list ap; 
	va_start(ap,format_str);
	int ret = 0;
	char Message[512];
	char OutMess[512];
	time_t now;
	time(&now);
	struct tm* stm;
	stm = localtime(&now);
	
	ret = vsprintf(Message,format_str,ap);
	sprintf(OutMess,"%.19s <%s> %s\n", asctime(stm), strLevel[level], Message); 
	fwrite(OutMess,strlen(OutMess),1,mlogLogFp);
	lMlogSize += strlen(OutMess);
	va_end(ap);

	fflush(mlogLogFp);
	LeaveCriticalSection(&mlogmutex);
}

void mlogRotate()
{
	char RotatedName[256];
	char CurrentTimeStr[19];

	struct tm *t;
    time_t tsec;	
    time(&tsec);
    t = localtime(&tsec);
	sprintf(CurrentTimeStr, "%02d-%02d-%02d-%02d-%02d-%02d", t->tm_year-100, t->tm_mon+1,
		t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	sprintf(RotatedName, "%s-%s%s", PRE_LOGFILENAME, CurrentTimeStr, POST_LOGFILENAME);
	char szlogFileOld[1024];
	char szlogFileNew[1024];
	sprintf(szlogFileOld, "%s\\%s", szmoduleDir, LOGFILENAME);
	sprintf(szlogFileNew, "%s\\%s", szmoduleDir, RotatedName);
	rename(szlogFileOld, szlogFileNew);
	
	mlogLogFp = fopen(szlogFileOld, "a");    
}