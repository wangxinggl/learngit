#pragma once
#include <Windows.h>
#define  FRAME_BUF_LEN 300 /*10S*30Ö¡*/
typedef struct  
{
	char* pBuf;
	int nBufSize;
	int nFrameType; 
}FrameBuf_t;

class CFrameBuf
{
public:
	CFrameBuf(void);
	~CFrameBuf(void);
	
	int CreateBuf(int nSizeMB = 20); 
	int DeleteBuf();
	int PutFrame(char* pDdata,int nDataSize,int nStreamType);
	int EnableWriteFrame(BOOL bEnable);
	char* GetFrame(int* nFramSize);
private:
	BOOL m_bEnableWriteFrame;//½ûÖ¹Ð´Èë
	char* m_buf;
	unsigned int m_curBuf;
	int m_nReadIndex;
	int m_nWriteIndex;
	CRITICAL_SECTION m_csLock;
	FrameBuf_t m_stFrameBuf[FRAME_BUF_LEN];

	int m_nBufSize;
	char* m_Rpbuf;
	int m_nRpReadIndex;
	int m_nRpWriteIndex;
	FrameBuf_t m_stRpFrameBuf[FRAME_BUF_LEN];
public:
	int BkBuffer();
	char* GetBkFrame(int* nFramSize);
};
