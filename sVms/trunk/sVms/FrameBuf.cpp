
#include "FrameBuf.h"
#include "frameHead.h"

CFrameBuf::CFrameBuf(void)
{
	m_buf = NULL;
	m_nReadIndex = m_nWriteIndex = 1;
	m_bEnableWriteFrame = TRUE;
	m_curBuf = 0;
	InitializeCriticalSection(&m_csLock);	
	memset(&m_stFrameBuf,0,sizeof(m_stFrameBuf));

	m_nBufSize = 0;
	m_Rpbuf = NULL;
	m_nRpReadIndex = m_nRpWriteIndex = 1;
	memset(&m_stRpFrameBuf,0,sizeof(m_stRpFrameBuf));
}

CFrameBuf::~CFrameBuf(void)
{
	if(m_buf != NULL)
		delete[] m_buf;
	m_buf = NULL;
	m_Rpbuf = NULL;
	m_nReadIndex = m_nWriteIndex = 1;
	m_bEnableWriteFrame = TRUE;
	m_curBuf = 0;
	DeleteCriticalSection(&m_csLock);

	if(m_Rpbuf != NULL)
		delete []m_Rpbuf;
	m_Rpbuf = NULL;
	m_nBufSize = 0;
	m_nRpReadIndex = m_nRpWriteIndex = 1;
}

int CFrameBuf::CreateBuf(int nSizeMB)
{
	int nSize = nSizeMB;
	if(nSizeMB <= 0 || nSizeMB >20)
		nSize = 20;
	m_nBufSize = nSize*1024*1024;
	m_buf = new char[m_nBufSize];
	m_Rpbuf = new char[m_nBufSize];
	if(m_buf == NULL || m_Rpbuf == NULL)
		return -1;
	return 0;
}

int CFrameBuf::DeleteBuf()
{
	if(m_buf != NULL)
		delete[] m_buf;
	m_buf = NULL;
	m_nReadIndex = m_nWriteIndex = 1;
	m_bEnableWriteFrame = TRUE;
	m_curBuf = 0;
	memset(&m_stFrameBuf,0,sizeof(m_stFrameBuf));

	if(m_Rpbuf != NULL)
		delete[] m_Rpbuf;
	m_Rpbuf = NULL;
	m_nBufSize = 0;
	m_nRpReadIndex = m_nRpWriteIndex = 1;
	memset(&m_stRpFrameBuf,0,sizeof(m_stRpFrameBuf));
	return 0;
}

//为空时要保证第一帧为I帧 覆盖I帧m_nReadIndex下移至另一I帧
int CFrameBuf::PutFrame(char* pDdata,int nDataSize,int nStreamType)
{
	if(!m_bEnableWriteFrame)
		return -3;
	if(pDdata == NULL || nDataSize <= 0 || m_buf == NULL)
		return 0;
	unsigned int uEndBuf = (unsigned int) (m_buf + m_nBufSize/*20*1024*1024*/);
	Codec_Head_t* pHead = (Codec_Head_t*)pDdata;
	EnterCriticalSection(&m_csLock);
	if(m_nReadIndex == m_nWriteIndex && pHead->FrameType != 0/*I_FRAME*/)
	{
		LeaveCriticalSection(&m_csLock);
		return 0; //缓存为空,第一帧应为I帧
	}
	if((m_nWriteIndex +1)%FRAME_BUF_LEN == m_nReadIndex)
	{
		//满 
		while(1)
		{
			m_nReadIndex = (m_nReadIndex+1)%FRAME_BUF_LEN;
			Codec_Head_t* pStreamHead = (Codec_Head_t*)m_stFrameBuf[m_nReadIndex].pBuf; 
			if(pStreamHead == NULL || pStreamHead->FrameType == 0)
				break;
			if((m_nReadIndex +1)%FRAME_BUF_LEN == m_nWriteIndex)
			{
				LeaveCriticalSection(&m_csLock);
				return -1;
			}
		}	
	}

	//写入缓存
	if((unsigned int)m_buf + m_curBuf + nDataSize < uEndBuf)
		m_stFrameBuf[m_nWriteIndex].pBuf = m_buf + m_curBuf;
	else 
	{      //不使用底部的内存
		if((unsigned int)m_buf + nDataSize < (unsigned int)m_stFrameBuf[m_nReadIndex].pBuf )
		{
			m_curBuf = 0;
			m_stFrameBuf[m_nWriteIndex].pBuf = m_buf + m_curBuf;
		}
		else
			return -2;
	}
	memcpy(m_stFrameBuf[m_nWriteIndex].pBuf,pDdata,nDataSize);
	m_stFrameBuf[m_nWriteIndex].nBufSize = nDataSize;
	m_stFrameBuf[m_nWriteIndex].nFrameType = pHead->FrameType;
	m_nWriteIndex = (m_nWriteIndex+1)%FRAME_BUF_LEN;
	m_curBuf += nDataSize;
	LeaveCriticalSection(&m_csLock);
	return 0;
}


char* CFrameBuf::GetFrame(int* nFramSize)
{
	EnterCriticalSection(&m_csLock);
	//m_bEnableWriteFrame = TRUE; //禁止写入
	char* buf = m_stFrameBuf[m_nReadIndex].pBuf;
	if(buf == NULL)
	{
		m_nReadIndex = 1;
		buf = m_stFrameBuf[m_nReadIndex].pBuf;
	}
	*nFramSize = m_stFrameBuf[m_nReadIndex].nBufSize;
	m_nReadIndex = (m_nReadIndex+1)%FRAME_BUF_LEN;
	LeaveCriticalSection(&m_csLock);
	return buf;
}

int CFrameBuf::EnableWriteFrame(BOOL bEnable)
{
	EnterCriticalSection(&m_csLock);
	m_bEnableWriteFrame = bEnable; 
	LeaveCriticalSection(&m_csLock);
	return 0;
}
int CFrameBuf::BkBuffer()
{
	EnableWriteFrame(false);
	EnterCriticalSection(&m_csLock);
	memcpy(m_Rpbuf,m_buf,m_nBufSize);
	m_nRpReadIndex = m_nReadIndex;
	for(int i = 0;i<FRAME_BUF_LEN;i++)
	{
		m_stRpFrameBuf[i].pBuf = m_stFrameBuf[i].pBuf + (m_Rpbuf-m_buf);
		m_stRpFrameBuf[i].nBufSize = m_stFrameBuf[i].nBufSize;
		m_stRpFrameBuf[i].nFrameType = m_stFrameBuf[i].nFrameType;
	}
	LeaveCriticalSection(&m_csLock);
	EnableWriteFrame(true);
	return 0;
}

char* CFrameBuf::GetBkFrame(int* nFramSize)
{
	char* buf = m_stRpFrameBuf[m_nRpReadIndex].pBuf;
	if(buf == NULL)
	{
		m_nRpReadIndex = 1;
		buf = m_stRpFrameBuf[m_nRpReadIndex].pBuf;
	}
	*nFramSize = m_stRpFrameBuf[m_nRpReadIndex].nBufSize;
	m_nRpReadIndex = (m_nRpReadIndex+1)%FRAME_BUF_LEN;
	return buf;
}
//