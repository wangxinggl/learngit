#pragma once
#include "qobject.h"
#include <QThread>
#include <QDebug>
#include <QQueue>
#include <QMutex>
#include <Windows.h>
#include "../include/VideoNetAPI.h"
#include <list>
#include <QVector>



using namespace std;

class WorkThread :
	public QObject
{
	Q_OBJECT
public:
	WorkThread(void);
	~WorkThread(void);

	//线程处理函数
	void SearchDevice();
	void setFlag(bool flag);


signals:
	void sendDeviceThread(SDK_CONFIG_NET_COMMON_V2 *,int);
	
	
private:
	bool isStop;
	SDK_CONFIG_NET_COMMON_V2 m_Device[100];
	QQueue<SDK_CONFIG_NET_COMMON_V2 > m_vDevice;

	int m_nDevNum;


};

