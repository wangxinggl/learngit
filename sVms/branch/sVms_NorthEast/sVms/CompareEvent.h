﻿#pragma once
#include "qcoreevent.h"

enum CustomEventType {
	CET_COMPARISON = 900,
	CET_DISPLAYIMG,
	CET_DISPLAYPERMSG,
	CET_ATTEND,
	CET_COMPARESEARCH,
	CET_DOWNLOAD,
	CET_MESSAGEBOX,
	CET_ALARMNOTIFY,
	CET_DEVICELOST,
	CET_INDEXINFO,
	CET_ATTENDENCE,
	CET_DEVMNG_UPDATELIST
	
};

class CompareEvent :
	public QEvent
{
public:
	CompareEvent(int type);
	~CompareEvent(void);
public:
	inline int getId() {return m_id;}
	inline void setId(int id) {m_id = id;}
	inline char* getPARAM() { return m_param; }
	inline void setParam(char* param) { m_param = param; }
	static int getType(CustomEventType eType);
	inline void setItem(void *param) { m_item = param; }
	inline void* getItem() { return m_item; }
private:
	int m_id;
	char *m_param;
	void *m_item;
};

