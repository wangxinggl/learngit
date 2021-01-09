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
