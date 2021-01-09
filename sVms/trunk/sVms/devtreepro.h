#ifndef DEVTREEPRO_H
#define DEVTREEPRO_H

#include <QWidget>
#include"Device.h"
#include "JLNDevice.h"
#include <list>
#include <map>
#include <QTreeWidget>
using namespace  std;
#include <QBrush>


#pragma execution_character_set("utf-8") 
typedef struct
{
	CBaseDeviceInfo* DevInfo;
	unsigned int Channel; //-1表示主设备
}TreeData_t;

class DevTreePro : public QWidget
{
	Q_OBJECT

public:
	DevTreePro(QWidget *parent = 0);
	~DevTreePro();
	bool init();

	void SelectTreeData(TreeData_t* pTreeData) {m_CurTreeData = pTreeData;}
	void ShowTreebyType();
	TreeData_t* GetTreeData(int nDevId,BOOL bMasterDev);
	int DestroyData();
	
	void ShowTreebyType1(QTreeWidget *widget);  //另一种方法给treeitem节点赋值
	void QStringList_removeDuplicates(QStringList *that);
	TreeData_t* GetCurDev() {return m_CurTreeData;}
	int RefreshDevTree(QTreeWidget* pTree, BOOL bShowGroup);
	int AddDev(TabDevInfo_t* pDevInfo);
	int DelDev(TabDevInfo_t* pDevInfo);
	void SetRealplayStatus(BOOL bStatus){m_bRealplay = bStatus;}
	BOOL GetDevStatus()
	{
		if(m_nDevStatus >-3)
			return TRUE;
		return FALSE;
	}
	
	void searchChild(QTreeWidgetItem *cItem, const QString &txt);
	void parentExpand(QTreeWidgetItem *item);
	CBaseDeviceInfo* GetBaseDeviceInfo(int nSlaveDevid, int nDevId = -1);
	TabChannelInfo_t* GetChannelInfo(int nSlaveDevid);
	QBrush m_itemBrush;
protected:

	vector<TabDevInfo_t*>				m_lstMasterDev;
	vector<TabChannelInfo_t*>		m_lstChannelInfo;
	list<TabUserDevGroup_t*>	m_lstDevGroup;
	vector<TabDevGroup_t*>			m_lstGroupChannel;
	vector<TreeData_t*>					m_lstTreeData;

	map<int ,CBaseDeviceInfo*> m_mapDevInfo;//主设备ID对应的设备类
	map<int ,TabChannelInfo_t*> m_mapChannelInfo;//通道ID对应的通道

	TreeData_t* m_CurTreeData; 
	map<int ,TreeData_t*>						m_mapMasterData;
	map<int ,TreeData_t*>						m_mapSlaveData;
	CRITICAL_SECTION m_DevTreeLock;
	map<int ,BOOL>						m_mapGroupStatus;//已分组的通道ID
	int m_nDevStatus; //0 在线  <-3 不在线
	
	BOOL m_bRealplay;
	
};

#endif // DEVTREEPRO_H

