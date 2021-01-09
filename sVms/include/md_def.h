/******************************************************************************
********
 * head file of metadata client
 * AUTHOR: alen.wu
 * DATE: 2006-01-23
 * COPYRIGHT: Rockman
 * DESCRIPTION: The file defines data types.

*******************************************************************************
*******
 */

#ifndef MD_DEF_H_
#define MD_DEF_H_

#ifndef _DEF_S8_
#define _DEF_S8_
typedef char S8;
#endif

#ifndef _DEF_U8_
#define _DEF_U8_
typedef unsigned char U8;
#endif

#ifndef _DEF_S16_
#define _DEF_S16_
typedef short S16;
#endif

#ifndef _DEF_U16_
#define _DEF_U16_
typedef unsigned short U16;
#endif

#ifndef _DEF_S32_
#define _DEF_S32_
typedef int S32;
#endif

#ifndef _DEF_U32_
#define _DEF_U32_
typedef unsigned int U32;
#endif

//typedef long long S64;
//typedef unsigned long long U64;


#ifdef WIN32
#include <WinSock.h>
typedef  SOCKET MD_SOCKFD;
#else //LINUX OR UNIX
typedef int MD_SOCKFD;
#endif

#ifdef WIN32
//#include <MAPIWin.h>
typedef HANDLE MD_MUTEX_ID;
#else //LINUX OR UNIX
#include <pthread.h>
typedef pthread_mutex_t MD_MUTEX_ID;
#endif


#ifndef MD_UNUSED_ARG
#define MD_UNUSED_ARG(a) do {/* null */} while (&a == 0)
#endif

#ifndef MAX_MD_COL_ATTR_LEN
#define MAX_MD_COL_ATTR_LEN 4096
#endif


#ifndef MAX_MD_PDU_LEN
#define MAX_MD_PDU_LEN (30*1024)
#endif


#ifndef ASSERT
#define ASSERT(i)		assert(i)
#endif


#ifdef WIN32
#	define SLOG_LVL_FATAL		1
#	define SLOG_LVL_ERROR		3
#	define SLOG_LVL_WARNING		4
#	define SLOG_LVL_INFO		6
#	define SLOG_LVL_TRACE		7
#else
#include <ssi.h>
#include <slog.h>
#include <modules.h>
#endif



#ifdef WIN32
static S32 MD_LOG( S32 level, const S8* str,... )
{
	if( level > SLOG_LVL_INFO )
		return 0;

	va_list ap;
	va_start(ap, str);
	vprintf(str,ap);
	va_end(ap);
	printf("\n");
	return 0;
}
#else

/*
#define MD_LOG(level,  loginfo,...)	\
do{ \
	if( level >  SLOG_LVL_INFO  )	\
		break;	\
		\
    printf(loginfo,##__VA_ARGS__); \
    printf("\n");	\
}while(0)
*/

#define MD_LOG(level,  loginfo,...)	\
do{ \
	slog(level,EVSS_MOD_MDS,loginfo,##__VA_ARGS__ );	\
}while(0)

#endif


#endif /* EMS_TYPES_H */


