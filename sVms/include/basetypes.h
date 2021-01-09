#ifndef _DATA_TYPE_H
#define _DATA_TYPE_H


#ifdef __cplusplus
extern "C"
{
#endif 

/*------------------------------ Const definitions --------------------------*/
#ifdef FALSE
#undef FALSE
#define FALSE       0         /* for booleans */
#else
#define FALSE       0         /* for booleans */
#endif

#ifdef TRUE
#undef TRUE
#define TRUE        1         /* for booleans */
#else
#define TRUE        1         /* for booleans */
#endif

/*------------------------------- Type definitions --------------------------*/
#ifndef _DEF_Bool_
#define _DEF_Bool_
	typedef unsigned char Bool;
#endif /*_DEF_Bool_*/

#ifndef NULL
#ifdef __cplusplus
#define NULL  (0)
#else
#define NULL  ((void *)0)
#endif
#endif /* !NULL */


#if (!defined WIN32 && !defined VXWORKS)
#ifndef _DEF_BOOL_
#define _DEF_BOOL_
	typedef unsigned char BOOL;
#endif
#endif

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
	typedef short int S16;
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

#ifdef WIN32
	typedef __int64           S64;
	typedef unsigned __int64  U64;
#endif

#ifdef LINUX
	typedef long long         S64;
	typedef unsigned long long U64;
#endif

#if ( defined(ALPHA) || defined(BIT_64) )
	typedef long          S64;      /* signed - 64 bits */
	typedef unsigned long U64;      /* unsigned - 64 bits */
#endif /* ALPHA  & BIT_64 */

#ifndef WIN32
#ifndef HAVE_HANDLE
#define HAVE_HANDLE
	typedef U32 HANDLE;
#endif

#ifndef HAVE_BYTE
#define HAVE_BYTE
	typedef U8 BYTE;
#endif

#ifndef HAVE_WORD
#define HAVE_WORD
	typedef U16 WORD;
#endif

#ifndef HAVE_DWORD
#define HAVE_DWORD
	typedef U32 DWORD;
#endif
#endif /* #ifndef WIN32 */



#ifdef __cplusplus
}
#endif 

#endif

