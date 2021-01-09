#include "Dmp3b.h"
#include <QThread>

class CrashTest
{
public:
	void Test()
	{
		Crash();
	}

private:
	void Crash()
	{
		int i = 13;
		int j = 0;
		int m = i / j;
		printf("m=%d\n", m);
	}
};

Dmp3b::Dmp3b(QWidget *parent)
	: QWidget(parent)
{
	this->show();
	QThread::msleep(5000);
	CrashTest test;
	test.Test();
}

Dmp3b::~Dmp3b()
{
}
