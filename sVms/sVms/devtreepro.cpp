#include "devtreepro.h"
#include <list>
#include "DB.h"
#include <QVariant>
#include <QMutex>
#include "client.h"

using namespace std;
QMutex treePro_mutex;
extern vector<TabDevInfo_t*>			g_vectorDevInfo;
extern vector<TabChannelInfo_t*>		g_vectorChannelInfo;
extern list<TabUserDevGroup_t*>		g_lstDevGroup;
extern vector<TabDevGroup_t*>			g_vectorGroupChannel;
extern map<int, CJLNDevice*> g_mapDevInfo;//主设备ID对应的设备类
extern Client* g_pInstance;

DevTreePro::DevTreePro(QWidget *parent)
	: QWidget(parent)
{
	itemCount = 0;
}
bool DevTreePro::init()
{
	treePro_mutex.lock();
	vector<TabChannelInfo_t *>::iterator  iterSlave;
	vector<TabDevGroup_t *>::iterator  iterGroupChannel;
	TabDevInfo_t* pTabDevInfo = NULL;	

	size_t nDevNum = g_vectorDevInfo.size();

	if (nDevNum == 0)
	{
		treePro_mutex.unlock();
		return false;
	}
	for ( size_t i = 0;i < nDevNum;i++)
	{
		pTabDevInfo = g_vectorDevInfo[i];
		TreeData_t* pDev = new TreeData_t;
		m_lstTreeData.push_back(pDev);
		pDev->Channel = -1;
		if (pTabDevInfo->nType == SDK_DEV_TYPE_IPC)
		{
			pDev->Channel = 1;
		}
		pDev->pDevObj = g_mapDevInfo[pTabDevInfo->nDevId];	
		m_mapMasterData[g_vectorDevInfo[i]->nDevId] = pDev;
	}

	for (iterSlave = g_vectorChannelInfo.begin();iterSlave != g_vectorChannelInfo.end(); ++iterSlave)
	{
		m_mapChannelInfo[(*iterSlave)->SlaveDevId] = *iterSlave;
		map<int, CJLNDevice*>::const_iterator it = g_mapDevInfo.find((*iterSlave)->DevId);
		if (it != g_mapDevInfo.end())
		{
			TreeData_t* pChannel = new TreeData_t;
			m_lstTreeData.push_back(pChannel);
			pChannel->Channel = (*iterSlave)->Channel;
			pChannel->pDevObj = it->second;
			m_mapSlaveData[(*iterSlave)->SlaveDevId] = pChannel;
		}
	}

	for(iterGroupChannel = g_vectorGroupChannel.begin(); iterGroupChannel != g_vectorGroupChannel.end(); ++iterGroupChannel)
		m_mapGroupStatus[(*iterGroupChannel)->SlaveDevId] = TRUE;
	treePro_mutex.unlock();

	return true;
}

bool DevTreePro::ReInit(BOOL bClear)
{
	DestroyData(bClear);
	g_pDatabase->QueryAllDevGroup(g_lstDevGroup);
	g_pDatabase->QueryAllGroupChannel(g_vectorGroupChannel);
	init();
	return true;
}

DevTreePro::~DevTreePro(void)
{
	DestroyData();
}

TreeData_t* DevTreePro::GetTreeData(int nDevId,BOOL bMasterDev)
{
	TreeData_t* pData;
	map<int, TreeData_t*>::const_iterator itData;
	if(bMasterDev)
	{
		itData = m_mapMasterData.find(nDevId);
		if(itData == m_mapMasterData.end())
			return  NULL;
	}
	else
	{
		itData = m_mapSlaveData.find(nDevId);
		if(itData == m_mapSlaveData.end())
			return NULL;
	}
	pData = itData->second;
	return pData;
}

int DevTreePro::DestroyData(BOOL bDevData)
{
	if (bDevData)
	{
		for (vector<TabDevInfo_t *>::iterator iter = g_vectorDevInfo.begin(); g_vectorDevInfo.end() != iter; ++iter)
		{
			if ((*iter) != NULL)
				delete (*iter);
		}

		for (vector<TabChannelInfo_t *>::iterator it = g_vectorChannelInfo.begin(); g_vectorChannelInfo.end() != it; ++it)
		{
			if ((*it) != NULL)
				delete (*it);
		}
		for (map<int, CJLNDevice*>::iterator it = g_mapDevInfo.begin(); it != g_mapDevInfo.end(); it++)
		{
			if (it->second->m_pDevInfo != NULL)
				g_pInstance->DeleteDevObj(it->second);
		}

		g_vectorDevInfo.clear();
		g_vectorChannelInfo.clear();
		g_mapDevInfo.clear();
	}

	for(list<TabUserDevGroup_t *>::iterator it = g_lstDevGroup.begin(); g_lstDevGroup.end() != it; ++ it  )
	{
		if((*it)!=NULL)
			delete (*it);
	}
	for(vector<TabDevGroup_t *>::iterator it = g_vectorGroupChannel.begin(); g_vectorGroupChannel.end() != it; ++ it  )
	{
		if((*it)!=NULL)
			delete (*it);
	}
	for(vector<TreeData_t *>::iterator it = m_lstTreeData.begin(); m_lstTreeData.end() != it; ++ it  )
	{
		if((*it)!=NULL)
			delete (*it);
	}

	g_lstDevGroup.clear();
	g_vectorGroupChannel.clear();
	m_lstTreeData.clear();

	m_mapChannelInfo.clear();
	m_mapGroupStatus.clear();
	m_mapMasterData.clear();
	m_mapSlaveData.clear();

	return 0;	
}

void DevTreePro::ShowTreebyType(QTreeWidget *widget, BOOL bCheck)
{
	widget->setStyleSheet("QTreeView::item:hover{background-color:rgb(0,255,0,50)}"

		"QTreeView::item:selected{background-color:rgb(112,128,144,100)}"

		"QTreeView::item:selected{color: #00ff00;}"

		);
	QString strNVRDev = QObject::tr("NVR设备");
	QString strIPCAMDev = QObject::tr("IPC设备");

	//根节点
	QTreeWidgetItem *rootNodeNVR = new QTreeWidgetItem(QStringList(strNVRDev));
	rootNodeNVR->setIcon(0,QIcon(":/res/SoftIcon/shebei.png"));
	QTreeWidgetItem *rootNodeIPC = new QTreeWidgetItem(QStringList(strIPCAMDev));
	rootNodeIPC->setIcon(0,QIcon(":/res/SoftIcon/shebei.png"));

	widget->addTopLevelItem(rootNodeIPC);
	widget->addTopLevelItem(rootNodeNVR);

	size_t nDevNum = g_vectorDevInfo.size();
	for (size_t i = 0;i < nDevNum;i++)
	{
		QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(QString::fromLocal8Bit(g_vectorDevInfo[i]->szDevName)));
		if (bCheck)
		{
			child->setCheckState(0, Qt::Unchecked);
		}

		switch(g_vectorDevInfo[i]->nType)
		{
		case SDK_DEV_TYPE_NVR:
			child->setIcon(0, QIcon(":/res/SoftIcon/shebei.png"));
			rootNodeNVR->addChild(child);
			break;
		case SDK_DEV_TYPE_IPC:
			child->setIcon(0, QIcon(":/res/SoftIcon/shexiangtou.png"));
			rootNodeIPC->addChild(child);
			break;
		default:
			break;
		}

		TreeData_t* pDev = GetTreeData(g_vectorDevInfo[i]->nDevId, TRUE);
		if (pDev == NULL)
			continue;

		QVariant vDev = QVariant::fromValue((void *)pDev);
		child->setData(0, Qt::UserRole, vDev);

		if (g_vectorDevInfo[i]->nType == SDK_DEV_TYPE_NVR)
		{
			CJLNDevice* item = pDev->pDevObj;
			size_t nChnnelNum = item->GetChannelInfo().size();

			for (size_t j = 0; j < nChnnelNum; j++)
			{
				QTreeWidgetItem *treeNode = new QTreeWidgetItem(QStringList(item->GetChannelInfo()[j]->szChannelName));
				treeNode->setIcon(0, QIcon(":/res/SoftIcon/shexiangtou.png"));				
				//treeNode->setCheckState(0,Qt::Unchecked);
				TreeData_t* pChannel = GetTreeData(item->GetChannelInfo()[j]->SlaveDevId, FALSE);
				QVariant v = QVariant::fromValue((void *)pChannel);
				treeNode->setData(0, Qt::UserRole, v);

				child->addChild(treeNode);
			}
		}
	}
}
void DevTreePro::QStringList_removeDuplicates(QStringList *that)
{
	int n = that->size();
	int j = 0;
	QSet<QString> seen;
	seen.reserve(n);
	int setSize = 0;
	for (int i = 0; i < n; ++i) {
		const QString &s = that->at(i);
		seen.insert(s);
		if (setSize == seen.size()) // unchanged size => was already seen
			continue;
		++setSize;
		if (j != i)
			that->swap(i, j);    //将不重复项与重复项交换
		++j;
	}
	if (n != j)
		that->erase(that->begin() + j, that->end());

}

void DevTreePro::searchChild(QTreeWidgetItem *cItem, const QString &txt)
{
	int childCount = cItem->childCount();
	for (int i = 0; i < childCount; ++i) {
		QTreeWidgetItem *item = cItem->child(i);
		if (-1 != item->text(0).indexOf(txt)) {
			item->setExpanded(true);
			item->setBackground(0, Qt::gray);
			parentExpand(item);
		}
		else {
			item->setBackground(0, m_itemBrush);
		}
		searchChild(item, txt);
	}
}

void DevTreePro::parentExpand(QTreeWidgetItem *item)
{
	if (item->parent() != NULL) {
		QTreeWidgetItem *pItem = item->parent();
		if (!pItem->isExpanded()) {
			pItem->setExpanded(true);
		}
		parentExpand(pItem);
	}
}

TabChannelInfo_t* DevTreePro::GetChannelInfo(int nSlaveDevid)
{
	map<int, TabChannelInfo_t*>::const_iterator itChannel = m_mapChannelInfo.find(nSlaveDevid);
	if (itChannel == m_mapChannelInfo.end())
	{
		return NULL;
	}
	return (TabChannelInfo_t*)itChannel->second;
}

CJLNDevice* DevTreePro::GetBaseDeviceInfo(int nSlaveDevid, int nDevId)
{
	
	treePro_mutex.lock();
	if (nDevId == -1)
	{
		TabChannelInfo_t* pChannel = GetChannelInfo(nSlaveDevid);
		if (pChannel == NULL)
		{
			//LeaveCriticalSection(&m_DevTreeLock);
			treePro_mutex.unlock();
			return NULL;
		}
		nDevId = pChannel->DevId;
	}

	map<int, CJLNDevice*>::const_iterator it = g_mapDevInfo.find(nDevId);
	if (it != g_mapDevInfo.end())
	{
		treePro_mutex.unlock();
		return (CJLNDevice*)it->second;
	}
	treePro_mutex.unlock();
	return NULL;
}

int DevTreePro::RefreshDevTree(QTreeWidget* pTree, BOOL bShowGroup)
{
	ShowTreebyType(pTree);

	return 0;
}


