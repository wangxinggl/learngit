#include "WorkThread.h"



//全局变量g_mutex，用来防止线程间对资源的抢夺
QMutex  g_mutex;


WorkThread::WorkThread(void)
{
	isStop = false;
	memset(&m_Device, 0, sizeof(m_Device));

}


WorkThread::~WorkThread(void)
{
}

void WorkThread::SearchDevice()
{
	WorkThread *pThis = new WorkThread;
	int nRetLength = 0;
	bool bRet = VideoNet_SearchDevice((char *)m_Device, sizeof(pThis->m_Device), &nRetLength, 5000 );

	if ( bRet && nRetLength > 0 )
	{
		pThis->m_nDevNum = nRetLength / sizeof(SDK_CONFIG_NET_COMMON_V2);	
	}
	int m_DeviceNum = pThis->m_nDevNum;
	
	emit sendDeviceThread(m_Device,m_DeviceNum);
	
}

void WorkThread::setFlag(bool flag)
{
	isStop = flag;
}

