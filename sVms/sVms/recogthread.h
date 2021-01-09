#ifndef RECOGTHREAD_H
#define RECOGTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QVariant>
#include <Windows.h>
#include "VideoNetAPI.h"

class RecogThread : public QObject
{
	Q_OBJECT

public:
	RecogThread();
	~RecogThread();
	void ReceiveSnap(char* pBuf, int nDatelen);
private:
	
};


class ThreadConsumer : public QThread
{
	Q_OBJECT
public:
	ThreadConsumer(QObject *parent = 0);

	void run() Q_DECL_OVERRIDE;
	void setThreadStatus(bool status);
	~ThreadConsumer();

private:
	bool m_threadStatus;
	
};

class ThreadProducer : public QThread
{
	Q_OBJECT
public:
	ThreadProducer(QObject *parent = 0);
	~ThreadProducer();
	void run() Q_DECL_OVERRIDE;
	void setThreadStatus(bool status);

private:
	bool m_threadStatus;
signals:
	void sendImagResult(QVariant permsg);
	void sendAlarmResult(QVariant perMsg);
};

class ThreadProducer1 : public QThread
{
	Q_OBJECT
public:
	ThreadProducer1(QObject *parent = 0);
	~ThreadProducer1();
	void run() Q_DECL_OVERRIDE;
	void setThreadStatus(bool status);

private:
	bool m_threadStatus;
signals:
	void sendImagResult(QVariant permsg);

};

class ThreadConsumer1 : public QThread
{
	Q_OBJECT
public:
	ThreadConsumer1(QObject *parent = 0);

	void run() Q_DECL_OVERRIDE;
	void setThreadStatus(bool status);
	~ThreadConsumer1();

private:
	bool m_threadStatus;

};

#endif // RECOGTHREAD_H
