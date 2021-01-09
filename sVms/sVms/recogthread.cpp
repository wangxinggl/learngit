#include "recogthread.h"
#include <QQueue>
#include <QWaitCondition>
#include <QDebug>

//全局变量g_mutex，用来防止线程间对资源的抢夺
QMutex  recog_mutex;
QMutex unrecog_mutex;
QQueue<SDK_FACECOMPARE_RESULT> g_pCompareInfoAlm;
QQueue<SDK_FACECOMPARE_RESULT> g_pCompareInfoImg;
QWaitCondition numberNotFull;
QWaitCondition numberNotEmpty;
QWaitCondition numberNotFull1;
QWaitCondition numberNotEmpty1;
RecogThread::RecogThread()
{

}

RecogThread::~RecogThread()
{

}

void RecogThread::ReceiveSnap(char* pBuf, int nDatelen)
{
	SDK_FACECOMPARE_RESULT stFaceCompareInfo = {0};
	memcpy(&stFaceCompareInfo, pBuf, sizeof(SDK_FACECOMPARE_RESULT));
	recog_mutex.lock();
	if(stFaceCompareInfo.result > 0.00001f )
	{
		g_pCompareInfoAlm.enqueue(stFaceCompareInfo);
	}
	else
	{
		g_pCompareInfoImg.enqueue(stFaceCompareInfo);
	}
	
	recog_mutex.unlock();

}


ThreadProducer::ThreadProducer(QObject *parent /* = 0 */)
	:QThread(parent)
{
	m_threadStatus = false;
}

ThreadProducer::~ThreadProducer()
{
	m_threadStatus = false;
}
void ThreadProducer::run()
{
	
	while(m_threadStatus)
	{
		qDebug()<<"ThreadProducer";
		recog_mutex.lock();
		if (g_pCompareInfoAlm.size()==0)
			numberNotFull.wait(&recog_mutex);
		if (g_pCompareInfoAlm.size()> 0)
		{
			int m = g_pCompareInfoAlm.size();
			SDK_FACECOMPARE_RESULT  *pCompareInfo = new SDK_FACECOMPARE_RESULT;

			memcpy(pCompareInfo, &g_pCompareInfoAlm.dequeue(), sizeof(SDK_FACECOMPARE_RESULT));
			QVariant perMsg = QVariant::fromValue((void *)pCompareInfo);
			if (!perMsg.isNull())
			{
				emit sendAlarmResult(perMsg);
			}
			
			
		}
		recog_mutex.unlock();
		numberNotEmpty.wakeAll();
		if (m_threadStatus == false)
		{
			break;
		}
	}
	
}

void ThreadProducer::setThreadStatus(bool status)
{
	m_threadStatus = status;
}

/////////////////////////////////////////////////////////////////////////////

ThreadConsumer::ThreadConsumer(QObject *parent /* = 0 */)
	:QThread(parent)
{
	m_threadStatus = false;
}
ThreadConsumer::~ThreadConsumer()
{
	m_threadStatus = false;
}
void ThreadConsumer::run()
{
	
	while (m_threadStatus)
	{
		qDebug()<<"ThreadCosumer";
		recog_mutex.lock();
		if (g_pCompareInfoAlm.size() > 20)
			numberNotEmpty.wait(&recog_mutex);
		sleep(1);
		recog_mutex.unlock();
		numberNotFull.wakeAll();
		if (m_threadStatus == false)
		{
			break;
		}
		
	}
}

void ThreadConsumer::setThreadStatus(bool status)
{
	m_threadStatus = status;
}

////////////////////////////////////////////////////////////

ThreadProducer1::ThreadProducer1(QObject *parent /* = 0 */)
	:QThread(parent)
{
	m_threadStatus = false;
}
ThreadProducer1::~ThreadProducer1()
{
	m_threadStatus = false;
}
void ThreadProducer1::run()
{
	
	while (m_threadStatus)
	{
		qDebug()<<"ThreadProducer1";
		while(m_threadStatus)
		{
			unrecog_mutex.lock();
			if (g_pCompareInfoImg.size()==0)
				numberNotFull1.wait(&unrecog_mutex);
			if (g_pCompareInfoImg.size()> 0)
			{
				
				SDK_FACECOMPARE_RESULT  *pCompareInfo = new SDK_FACECOMPARE_RESULT;

				memcpy(pCompareInfo, &g_pCompareInfoImg.dequeue(), sizeof(SDK_FACECOMPARE_RESULT));
				QVariant perMsg = QVariant::fromValue((void *)pCompareInfo);
				if (!perMsg.isNull())
				{
					emit sendImagResult(perMsg);
				}


			}
			unrecog_mutex.unlock();
			numberNotEmpty1.wakeAll();
			if (m_threadStatus == false)
			{
				break;
			}
		}


	}
}

void ThreadProducer1::setThreadStatus(bool status)
{
	m_threadStatus = status;
}


ThreadConsumer1::ThreadConsumer1(QObject *parent /* = 0 */)
	:QThread(parent)
{
	m_threadStatus = false;
}
ThreadConsumer1::~ThreadConsumer1()
{
	m_threadStatus = false;
}
void ThreadConsumer1::run()
{
	while (m_threadStatus)
	{
		qDebug()<<"ThreadCosumer1";
		unrecog_mutex.lock();
		if (g_pCompareInfoAlm.size() > 20)
			numberNotEmpty1.wait(&unrecog_mutex);
		sleep(1);
		unrecog_mutex.unlock();
		numberNotFull1.wakeAll();
		if (m_threadStatus == false)
		{
			break;
		}

	}
}

void ThreadConsumer1::setThreadStatus(bool status)
{
	m_threadStatus = status;
}

