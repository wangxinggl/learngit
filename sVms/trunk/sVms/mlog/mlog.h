#ifndef _M_LOG_H_
#define _M_LOG_H_

#define LOGFILENAME	  "clientlog.txt"
#define PRE_LOGFILENAME	  "clientlog"
#define POST_LOGFILENAME	  ".txt"
#define MAX_CLIENT_LOGFILE_SIZE (10<<20)

#define LOG_EMERG   0   /* system is unusable */
#define LOG_ALERT   1   /* action must be taken immediately */
#define LOG_CRIT    2   /* critical conditions */
#define LOG_ERR     3   /* error conditions */
#define LOG_WARNING 4   /* warning conditions */
#define LOG_NOTICE  5   /* normal but significant condition */
#define LOG_INFO    6   /* informational */
#define LOG_DEBUG   7   /* debug-level messages */

#define LOG_ALREADY_INITED	-1
#define LOG_ERROR			-2
#define LOG_NOT_INITED		-3
#define LOG_GETSIZE_ERROR	-4

int mlogInit(char *localFile);
int mlogClose();
void mlog(unsigned int level,const char *format_str,...);
void mlogRotate();

#endif