#ifndef DEVTREEPRO_H
#define DEVTREEPRO_H

#include <QWidget>
#include "Device/JLNDevice.h"
#include <list>
#include <map>
#include <QTreeWidget>
using namespace  std;
#include <QBrush>


#pragma execution_character_set("utf-8") 
typedef struct
{
	CJLNDevice* pDevObj;
	unsigned int Channel; //-1表示主设备
}TreeData_t;

class DevTreePro : public QWidget
{
	Q_OBJECT

public:
	DevTreePro(QWidget *parent = 0);
	~DevTreePro();
	bool init();
	bool ReInit(BOOL bClear);
	int itemCount;
	void SelectTreeData(TreeData_t* pTreeData) {m_CurTreeData = pTreeData;}
	TreeData_t* GetTreeData(int nDevId,BOOL bMasterDev);
	int DestroyData(BOOL bDevData = TRUE);
	
	void ShowTreebyType(QTreeWidget *widget, BOOL bCheck = FALSE);  //另一种方法给treeitem节点赋值,bCheck是否增加Check选项
	void QStringList_removeDuplicates(QStringList *that);
	TreeData_t* GetCurDev() {return m_CurTreeData;}
	int RefreshDevTree(QTreeWidget* pTree, BOOL bShowGroup);
	void SetRealplayStatus(BOOL bStatus){m_bRealplay = bStatus;}
	BOOL GetDevStatus()
	{
		if(m_nDevStatus >-3)
			return TRUE;
		return FALSE;
	}
	
	void searchChild(QTreeWidgetItem *cItem, const QString &txt);
	void parentExpand(QTreeWidgetItem *item);
	CJLNDevice* GetBaseDeviceInfo(int nSlaveDevid, int nDevId = -1);
	TabChannelInfo_t* GetChannelInfo(int nSlaveDevid);
	QBrush m_itemBrush;
	map<int ,TabChannelInfo_t*> m_mapChannelInfo;//通道ID对应的通道
protected:

	vector<TreeData_t*>			m_lstTreeData;

	TreeData_t* m_CurTreeData; 
	map<int ,TreeData_t*>						m_mapMasterData;
	map<int ,TreeData_t*>						m_mapSlaveData;
	CRITICAL_SECTION m_DevTreeLock;
	map<int ,BOOL>						m_mapGroupStatus;//已分组的通道ID
	int m_nDevStatus; //0 在线  <-3 不在线
	
	BOOL m_bRealplay;
	
};

#endif // DEVTREEPRO_H

