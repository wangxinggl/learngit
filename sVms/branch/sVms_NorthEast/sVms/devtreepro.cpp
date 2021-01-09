#include "devtreepro.h"
#include <list>
#include "DB.h"
#include <QVariant>
#include <QMutex>

QMutex treePro_mutex;
using namespace std;

DevTreePro::DevTreePro(QWidget *parent)
	: QWidget(parent)
{
	
	
}



bool DevTreePro::init()
{
	treePro_mutex.lock();
	DestroyData();
	list<TabDevInfo_t *>::iterator  iterMaster;
	vector<TabChannelInfo_t *>::iterator  iterSlave;
	vector<TabDevGroup_t *>::iterator  iterGroupChannel;
	
	DB *db =new DB;
	int ret = db->QueryAllMainDev(m_lstMasterDev);
	ret = db->QueryAllSlaveDev(m_lstChannelInfo);
	ret = db->QueryAllDevGroup(m_lstDevGroup);
	ret = db->QueryAllGroupChannel(m_lstGroupChannel);

	for (int i = 0;i < m_lstMasterDev.size();i++)
	{
		int m = m_lstMasterDev.size();
		CBaseDeviceInfo* pDevInfo;
		pDevInfo = new CJLNDevice();
		if (!pDevInfo)
		{
			continue;
		}		
		pDevInfo->SetDevInfo(m_lstMasterDev[i]);
		m_mapDevInfo[m_lstMasterDev[i]->nDevId] = pDevInfo;
		TreeData_t* pDev = new TreeData_t;
		m_lstTreeData.push_back(pDev);
		pDev->Channel = -1;
		pDev->DevInfo = pDevInfo;
		m_mapMasterData[m_lstMasterDev[i]->nDevId] = pDev;		
	}

	if (m_mapDevInfo.size() == 0)
	{
		treePro_mutex.unlock();
		return false;
		
	}
	for (iterSlave = m_lstChannelInfo.begin();iterSlave != m_lstChannelInfo.end(); ++iterSlave)
	{
		m_mapChannelInfo[(*iterSlave)->SlaveDevId] = *iterSlave;
		map<int,CBaseDeviceInfo*>::const_iterator it = m_mapDevInfo.find((*iterSlave)->DevId);
		if (it != m_mapDevInfo.end())
		{
			CBaseDeviceInfo* item = it->second;
			
			item->SetChannelInfo(*iterSlave);

			TreeData_t* pChannel = new TreeData_t;
			m_lstTreeData.push_back(pChannel);
			pChannel->Channel = (*iterSlave)->Channel;
			pChannel->DevInfo = it->second;
			m_mapSlaveData[(*iterSlave)->SlaveDevId] = pChannel;
		}
	}

	for(iterGroupChannel = m_lstGroupChannel.begin(); iterGroupChannel != m_lstGroupChannel.end(); ++iterGroupChannel)
		m_mapGroupStatus[(*iterGroupChannel)->SlaveDevId] = TRUE;
	treePro_mutex.unlock();

	return true;
}

DevTreePro::~DevTreePro(void)
{
	
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

int DevTreePro::DestroyData()
{

	for(vector<TabDevInfo_t *>::iterator iter = m_lstMasterDev.begin(); m_lstMasterDev.end() != iter; ++ iter  )
	{
		if((*iter)!=NULL)
			delete (*iter);
	}
	for(vector<TabChannelInfo_t *>::iterator it = m_lstChannelInfo.begin(); m_lstChannelInfo.end() != it; ++ it  )
	{
		if((*it)!=NULL)
			delete (*it);
	}
	for(list<TabUserDevGroup_t *>::iterator it = m_lstDevGroup.begin(); m_lstDevGroup.end() != it; ++ it  )
	{
		if((*it)!=NULL)
			delete (*it);
	}
	for(vector<TabDevGroup_t *>::iterator it = m_lstGroupChannel.begin(); m_lstGroupChannel.end() != it; ++ it  )
	{
		if((*it)!=NULL)
			delete (*it);
	}
	for(vector<TreeData_t *>::iterator it = m_lstTreeData.begin(); m_lstTreeData.end() != it; ++ it  )
	{
		if((*it)!=NULL)
			delete (*it);
	}
	for (map<int, CBaseDeviceInfo*>::iterator it = m_mapDevInfo.begin(); it != m_mapDevInfo.end();it ++)  
	{  
		if (it->second->m_pDevInfo != NULL)
			delete (it->second);
	}  
	m_lstMasterDev.clear();
	m_lstChannelInfo.clear();
	m_lstDevGroup.clear();
	m_lstGroupChannel.clear();
	m_lstTreeData.clear();
	m_mapDevInfo.clear();

	m_mapChannelInfo.clear();
	m_mapGroupStatus.clear();
	return 0;

	
}


void DevTreePro::ShowTreebyType1(QTreeWidget *widget)
{
	QString strEncDev = QObject::tr("编码设备");
	QString strDecDev = QObject::tr("解码设备");
	QString strNVRDev = QObject::tr("NVR设备");
	QString strIPCAMDev = QObject::tr("IPC设备");
	QString strNVTDev = QObject::tr("智能设备");
	QString strCRTDev = QObject::tr("告警设备");

	//根节点
	QTreeWidgetItem *rootNodeEnc = new QTreeWidgetItem(QStringList(strEncDev));
	rootNodeEnc->setIcon(0,QIcon(":/res/SoftIcon/shebei.png"));
	QTreeWidgetItem *rootNodeDEc = new QTreeWidgetItem(QStringList(strDecDev));
	rootNodeDEc->setIcon(0,QIcon(":/res/SoftIcon/shebei.png"));
	QTreeWidgetItem *rootNodeNVR = new QTreeWidgetItem(QStringList(strNVRDev));
	rootNodeNVR->setIcon(0,QIcon(":/res/SoftIcon/shebei.png"));
	QTreeWidgetItem *rootNodeIPC = new QTreeWidgetItem(QStringList(strIPCAMDev));
	rootNodeIPC->setIcon(0,QIcon(":/res/SoftIcon/shebei.png"));
	QTreeWidgetItem *rootNodeNVT = new QTreeWidgetItem(QStringList(strNVTDev));
	rootNodeNVT->setIcon(0,QIcon(":/res/SoftIcon/shebei.png"));
	QTreeWidgetItem *rootNodeCRT  = new QTreeWidgetItem(QStringList(strCRTDev));
	rootNodeCRT->setIcon(0,QIcon(":/res/SoftIcon/shebei.png"));
	widget->addTopLevelItem(rootNodeIPC);
	widget->addTopLevelItem(rootNodeNVR);
	widget->addTopLevelItem(rootNodeDEc);


	for (int i = 0;i < m_lstMasterDev.size();i++)
	{
		QTreeWidgetItem *child =  new QTreeWidgetItem(QStringList(m_lstMasterDev[i]->szDevName));
		child->setIcon(0,QIcon(":/Client/res/shexiangji.ico"));

		switch(m_lstMasterDev[i]->nType)
		{
		case DEVINFO_TYPE_NVR:
			rootNodeNVR->addChild(child);
			break;
		case DEVINFO_TYPE_IPCAM:
			rootNodeIPC->addChild(child);
			break;
		case DEVINFO_TYPE_DECODER:
			rootNodeDEc->addChild(child);
			break;
		default:
			break;
		}
		if (m_lstMasterDev[i]->nType == DEVINFO_TYPE_DECODER)
		{
			TreeData_t* pDev = GetTreeData(m_lstMasterDev[i]->nDevId,TRUE);
			int nImgID = 0;
			if(!pDev->DevInfo->GetDevStatus())
				nImgID+=8;
		}
		else
		{
			TreeData_t* pDev = GetTreeData(m_lstMasterDev[i]->nDevId,TRUE);
			if(pDev == NULL)
				continue;
			CBaseDeviceInfo* item = pDev->DevInfo;
			int m = item->GetChannelInfo().size();
			for (int j = 0;j < item->GetChannelInfo().size();j++)
			{
				if(item->GetChannelInfo()[j]->Type >= CHANNELINFO_TYPE_QIUJI && item->GetChannelInfo()[j]->Type <= CHANNELINFO_TYPE_COMPARE)
				{
					QTreeWidgetItem *treeNode = new QTreeWidgetItem(QStringList(item->GetChannelInfo()[j]->szChannelName));
					treeNode->setIcon(0,QIcon(":/res/SoftIcon/shexiangtou.png"));
					treeNode->setCheckState(0,Qt::Unchecked);
					TreeData_t* pChannel = GetTreeData(item->GetChannelInfo()[j]->SlaveDevId,FALSE);
					QVariant v = QVariant::fromValue((void *) pChannel);
					treeNode->setData(j,Qt::UserRole,v);
					switch(pChannel->DevInfo->m_pDevInfo->nType)
					{
					case DEVINFO_TYPE_NVR:
						child->addChild(treeNode);
						break;
					case DEVINFO_TYPE_IPCAM:
						child->addChild(treeNode);
						break;
					default:
						break;
					}
				}
			}
		}
	}
	LeaveCriticalSection(&m_DevTreeLock);

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

	EnterCriticalSection(&m_DevTreeLock);
	map<int, TabChannelInfo_t*>::const_iterator itChannel = m_mapChannelInfo.find(nSlaveDevid);
	if (itChannel == m_mapChannelInfo.end())
	{
		LeaveCriticalSection(&m_DevTreeLock);
		return NULL;
	}
	LeaveCriticalSection(&m_DevTreeLock);
	return (TabChannelInfo_t*)itChannel->second;
}

CBaseDeviceInfo* DevTreePro::GetBaseDeviceInfo(int nSlaveDevid, int nDevId)
{
	//EnterCriticalSection(&m_DevTreeLock);
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
	map<int, CBaseDeviceInfo*>::const_iterator it = m_mapDevInfo.find(nDevId);
	if (it != m_mapDevInfo.end())
	{
		treePro_mutex.unlock();
		//LeaveCriticalSection(&m_DevTreeLock);
		return (CBaseDeviceInfo*)it->second;
	}
	//LeaveCriticalSection(&m_DevTreeLock);
	treePro_mutex.unlock();
	return NULL;
}

int DevTreePro::RefreshDevTree(QTreeWidget* pTree, BOOL bShowGroup)
{

	DB *db = new DB;
	//TODO:删除和修改设备后资源回收
#if 1
	vector<TabDevInfo_t*>				lstMasterDev;
	vector<TabDevInfo_t *>::iterator  iterMaster;


	
	if (db->QueryAllMainDev(lstMasterDev) < 0)
		return 0;
	map<int, int> mapNewMasterDev;
	for (iterMaster = lstMasterDev.begin(); iterMaster != lstMasterDev.end();)
	{
		mapNewMasterDev[(*iterMaster)->nDevId] = 1;
		map<int, CBaseDeviceInfo*>::const_iterator it = m_mapDevInfo.find((*iterMaster)->nDevId);
		if (it == m_mapDevInfo.end())
			AddDev(*iterMaster); //新加设备
		else
		{
			//是否有修改
			TabDevInfo_t* pNewDevInfo = (TabDevInfo_t*)*iterMaster;
			TabDevInfo_t* pDevInfo = it->second->GetDevInfo();
			if (strcmp(pNewDevInfo->szDevName, pDevInfo->szDevName) != 0 ||
				strcmp(pNewDevInfo->szIpAddr, pDevInfo->szIpAddr) != 0 ||
				pNewDevInfo->nPort != pDevInfo->nPort ||
				strcmp(pNewDevInfo->szLoginName, pDevInfo->szLoginName) != 0 ||
				strcmp(pNewDevInfo->szPassword, pDevInfo->szPassword) != 0 ||
				pNewDevInfo->nManufacturer != pDevInfo->nManufacturer ||
				pNewDevInfo->nType != pDevInfo->nType)
			{
				DelDev(pDevInfo);
				vector<TabDevInfo_t *>::iterator  iter;
				for (iter = m_lstMasterDev.begin(); iter != m_lstMasterDev.end(); ++iter)
				{
					if ((*iter)->nDevId == pDevInfo->nDevId)
					{
						delete *iter;
						m_lstMasterDev.erase(iter);
						break;
					}
				}
				AddDev(pNewDevInfo);
				continue;
			}
		}
		++iterMaster;
	}

	for (iterMaster = m_lstMasterDev.begin(); iterMaster != m_lstMasterDev.end();)
	{
		map<int, int>::const_iterator it = mapNewMasterDev.find((*iterMaster)->nDevId);
		if (it == mapNewMasterDev.end()) //删除
		{
			map<int, CBaseDeviceInfo*>::const_iterator it = m_mapDevInfo.find((*iterMaster)->nDevId);
			if (it == m_mapDevInfo.end())
				continue;
			DelDev(*iterMaster);
			delete *iterMaster;
			iterMaster = m_lstMasterDev.erase(iterMaster);
		}
		else
		{
			iterMaster++;
		}
	}

	//重新显示树
	if (bShowGroup)//是否更新分组
	{
		for (list<TabUserDevGroup_t *>::iterator it = m_lstDevGroup.begin(); m_lstDevGroup.end() != it; ++it)
		{
			if ((*it) != NULL)
				delete (*it);
		}
		for (vector<TabDevGroup_t *>::iterator it = m_lstGroupChannel.begin(); m_lstGroupChannel.end() != it; ++it)
		{
			if ((*it) != NULL)
				delete (*it);
		}
		m_lstDevGroup.clear();
		m_lstGroupChannel.clear();
		db->QueryAllDevGroup(m_lstDevGroup);
		db->QueryAllGroupChannel(m_lstGroupChannel);
		ShowTreebyType1(pTree);
		return 0;
	}
	ShowTreebyType1(pTree);
#else
	if (m_bRealplay != NULL)
		return -2;
	if (m_bReplay)
		return -3;
	EnterCriticalSection(&m_DevTreeLock);
	Init();
	if (bShowGroup)
		ShowTreebyGroup(pTree);
	else
		ShowTreebyType(pTree);
	LeaveCriticalSection(&m_DevTreeLock);
#endif
	return 0;
}

int DevTreePro::AddDev(TabDevInfo_t* pDevInfo)
{
	DB *db = new DB;
	m_lstMasterDev.push_back(pDevInfo);
	CBaseDeviceInfo* devInfo;
	devInfo = new CJLNDevice();

	if (devInfo == NULL)
		return 0;

	devInfo->SetDevInfo((pDevInfo));
	m_mapDevInfo[(pDevInfo)->nDevId] = devInfo;
	TreeData_t* pDev = new TreeData_t;
	m_lstTreeData.push_back(pDev);
	pDev->Channel = -1;
	pDev->DevInfo = devInfo;
	m_mapMasterData[pDevInfo->nDevId] = pDev;

	vector<TabChannelInfo_t *>::iterator  iterSlave;
	vector<TabChannelInfo_t*>		lstChannelInfo;
	if (db->QueryAllSlaveDev(lstChannelInfo, (pDevInfo)->nDevId) <= 0)
		return 0;
	
	for (iterSlave = lstChannelInfo.begin(); iterSlave != lstChannelInfo.end(); ++iterSlave)
	{
		m_lstChannelInfo.push_back(*iterSlave);
		m_mapChannelInfo[(*iterSlave)->SlaveDevId] = *iterSlave;
		map<int, CBaseDeviceInfo*>::const_iterator it = m_mapDevInfo.find((*iterSlave)->DevId);
		if (it != m_mapDevInfo.end())
		{
			CBaseDeviceInfo* item = it->second;
			item->SetChannelInfo(*iterSlave);
		}
		TreeData_t* pChannel = new TreeData_t;
		m_lstTreeData.push_back(pChannel);
		pChannel->Channel = (*iterSlave)->Channel;
		pChannel->DevInfo = devInfo;
		m_mapSlaveData[(*iterSlave)->SlaveDevId] = pChannel;
	}
	return 0;
}

int DevTreePro::DelDev(TabDevInfo_t* pDevInfo)
{
	map<int, CBaseDeviceInfo*>::const_iterator it = m_mapDevInfo.find(pDevInfo->nDevId);
	if (it != m_mapDevInfo.end())
	{
		m_mapDevInfo.erase(it);
	}
	vector<TabChannelInfo_t *>::iterator  iterSlave;
	for (iterSlave = m_lstChannelInfo.begin(); iterSlave != m_lstChannelInfo.end();)
	{
		if ((*iterSlave)->DevId == pDevInfo->nDevId)
		{
			map<int, TabChannelInfo_t*>::const_iterator it = m_mapChannelInfo.find((*iterSlave)->DevId);
			if (it != m_mapChannelInfo.end())
			{
				m_mapChannelInfo.erase(it);
			}
			delete *iterSlave;
			iterSlave = m_lstChannelInfo.erase(iterSlave);
		}
		else
			iterSlave++;
	}
	return 0;
}
