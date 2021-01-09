#include "CompareEvent.h"

static const int cet1=QEvent::registerEventType(CET_COMPARISON);

static const int cetDisplayImg = QEvent::registerEventType(CET_DISPLAYIMG);
static const int cetDisplayPerMsg = QEvent::registerEventType(CET_DISPLAYPERMSG);

CompareEvent::CompareEvent(int type)
	 : QEvent(static_cast<QEvent::Type>(type))
	 , m_id(0)
{
}


CompareEvent::~CompareEvent(void)
{
}

int CompareEvent::getType(CustomEventType eType)
{
	int iRet = 0;
	switch (eType){
	case CET_COMPARISON:
		iRet = CET_COMPARISON;
		break;
	case CET_ATTENDENCE:
		iRet = CET_ATTENDENCE;
		break;
	case CET_DISPLAYIMG:
		iRet = CET_DISPLAYIMG;
		break;
	case CET_DISPLAYPERMSG:
		iRet = CET_DISPLAYPERMSG;
		break;
	case CET_MESSAGEBOX:
		iRet = CET_MESSAGEBOX;
		break;
	case CET_ALARMNOTIFY:
		iRet = CET_ALARMNOTIFY;
		break;
	case CET_COMPARESEARCH:
		iRet = CET_COMPARESEARCH;
		break;
	case CET_DEVICELOST:
		iRet = CET_DEVICELOST;
		break;
	case CET_DOWNLOAD:
		iRet = CET_DOWNLOAD;
		break;
	case CET_INDEXINFO:
		iRet = CET_INDEXINFO;
		break;
	case CET_DEVMNG_UPDATELIST:
		iRet = CET_DEVMNG_UPDATELIST;
		break;
	
	}
	return iRet;
}