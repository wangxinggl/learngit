#pragma once
#include"Device.h"
//#include "SJDevice.h"
//#include "HKDevice.h"
//#include "HHDevice.h"
//#include "TSTDevice.h"
//#include "RTSPDevice.h"
//#include "JNDevice.h"
#include "JLNDevice.h"
#include <list>
#include <map>
#include <QTreeWidget>

using namespace  std;

typedef struct
{
	CBaseDeviceInfo* DevInfo;
	unsigned int Channel; //-1表示主设备
}TreeData_t;
class CDevTree
{
public:
	CDevTree(void);
	~CDevTree(void);
	void init();
	static CDevTree* instance()  {if(!m_pInstance) m_pInstance=new CDevTree(); return m_pInstance;};
	void SelectTreeData(TreeData_t* pTreeData) {m_CurTreeData = pTreeData;}
	//void ShowTreebyType();
	TreeData_t* GetTreeData(int nDevId,BOOL bMasterDev);
	int DestroyData();
	void ShowTreebyType(QTreeWidget *widget);
	void QStringList_removeDuplicates(QStringList *that);
	TreeData_t* GetCurDev() {return m_CurTreeData;}
	void SetRealplayStatus(BOOL bStatus){m_bRealplay = bStatus;}
	BOOL GetDevStatus()
	{
		if(m_nDevStatus >-3)
			return TRUE;
		return FALSE;
	}
protected:
	vector<TabDevInfo_t*>				m_lstMasterDev;
	vector<TabChannelInfo_t*>		m_lstChannelInfo;
	list<TabUserDevGroup_t*>	m_lstDevGroup;
	vector<TabDevGroup_t*>			m_lstGroupChannel;
	vector<TreeData_t*>					m_lstTreeData;

	map<int ,CBaseDeviceInfo*> m_mapDevInfo;//主设备ID对应的设备类
	map<int ,TabChannelInfo_t*> m_mapChannelInfo;//通道ID对应的通道
	static CDevTree* m_pInstance;
	TreeData_t* m_CurTreeData; 
	map<int ,TreeData_t*>						m_mapMasterData;
	map<int ,TreeData_t*>						m_mapSlaveData;
	CRITICAL_SECTION m_DevTreeLock;
	map<int ,BOOL>						m_mapGroupStatus;//已分组的通道ID
	int m_nDevStatus; //0 在线  <-3 不在线
	TreeData_t **fDeviceInfoArray;
	BOOL m_bRealplay;

};

