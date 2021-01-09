#include "DevTree.h"
#include <list>
#include "DB.h"
#include <QVariant>
#include <QMutex>

QMutex tree_mutex;
using namespace std;

CDevTree::CDevTree(void)
{
	
}

void CDevTree::init()
{
	EnterCriticalSection(&m_DevTreeLock);
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
		CBaseDeviceInfo* devInfo;
		switch(m_lstMasterDev[i]->nManufaceturer)
		{
		case DEVINFO_MANUFACTURER_SJ:
			//devInfo = new CSJDevice();
			break;
		case DEVINFO_MANUFACTURER_HIK:
			//devInfo	 = new CHKDevice();
			break;
		case DEVINFO_MANUFACTURER_HH:
			//devInfo = new CHHDevice();
			break;
		case DEVINFO_MANUFACTURER_JL:
			//devInfo = new CJNDevice();
			break;
		case DEVINFO_MANUFACTURER_JL_NEW:
			devInfo = new CJLNDevice();
			break;
		case DEVINFO_MANUFACTURER_TST:
			//devInfo = new CTSTDevice();
			break;
		case DEVINFO_MANUFACTURER_BC:
			//devInfo = new CRTSPDevice();
			break;
		default:
			devInfo = NULL;
			//mlog(LOG_ERR,"error deviceinfo id:%d Manufacturer:%d",(*iterMaster)->nDevId,(*iterMaster)->nManufacturer);
			break;

		}
		if (devInfo == NULL)
		{
			continue;
		}

		devInfo->SetDevInfo(m_lstMasterDev[i]);
		m_mapDevInfo[m_lstMasterDev[i]->nDevId] = devInfo;
		TreeData_t* pDev = new TreeData_t;
		m_lstTreeData.push_back(pDev);
		pDev->Channel = -1;
		pDev->DevInfo = devInfo;
		m_mapMasterData[m_lstMasterDev[i]->nDevId] = pDev;
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
	LeaveCriticalSection(&m_DevTreeLock);
}

CDevTree::~CDevTree(void)
{
	if (fDeviceInfoArray != NULL)
	{
		for (int i = 0;i < m_lstMasterDev.size();i++)
		{
			delete fDeviceInfoArray[i];
			fDeviceInfoArray[i] = NULL;
		}
	}
	delete []fDeviceInfoArray;
}




TreeData_t* CDevTree::GetTreeData(int nDevId,BOOL bMasterDev)
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

int CDevTree::DestroyData()
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
	
	return 0;
}

void CDevTree::ShowTreebyType(QTreeWidget *widget)
{
	
	QString strEncDev = QStringLiteral("编码设备");
	QString strDecDev = QStringLiteral("解码设备");
	QString strNVRDev = QStringLiteral("NVR设备");
	QString strIPCAMDev = QStringLiteral("IPC设备");
	QString strNVTDev = QStringLiteral("智能设备");
	QString strCRTDev = QStringLiteral("告警设备");

	//根节点
	QTreeWidgetItem *rootNodeEnc = new QTreeWidgetItem(QStringList(strEncDev));
	rootNodeEnc->setIcon(0,QIcon(":/Client/res/net.ico"));
	QTreeWidgetItem *rootNodeDEc = new QTreeWidgetItem(QStringList(strDecDev));
	rootNodeDEc->setIcon(0,QIcon(":/Client/res/net.ico"));
	QTreeWidgetItem *rootNodeNVR = new QTreeWidgetItem(QStringList(strNVRDev));
	rootNodeNVR->setIcon(0,QIcon(":/Client/res/net.ico"));
	QTreeWidgetItem *rootNodeIPC = new QTreeWidgetItem(QStringList(strIPCAMDev));
	rootNodeIPC->setIcon(0,QIcon(":/Client/res/net.ico"));
	QTreeWidgetItem *rootNodeNVT = new QTreeWidgetItem(QStringList(strNVTDev));
	rootNodeNVT->setIcon(0,QIcon(":/Client/res/net.ico"));
	QTreeWidgetItem *rootNodeCRT  = new QTreeWidgetItem(QStringList(strCRTDev));
	rootNodeCRT->setIcon(0,QIcon(":/Client/res/net.ico"));
	widget->addTopLevelItem(rootNodeIPC);
	widget->addTopLevelItem(rootNodeNVR);
	widget->addTopLevelItem(rootNodeDEc);

	EnterCriticalSection(&m_DevTreeLock);
	for (int i = 0;i < m_lstMasterDev.size();i++)
	{
		fDeviceInfoArray = new TreeData_t* [m_lstMasterDev.size()];

		QTreeWidgetItem *child =  new QTreeWidgetItem(QStringList(m_lstMasterDev[i]->szIpAddr));
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
					fDeviceInfoArray[j] = new TreeData_t();
					TreeData_t* pChannel = GetTreeData(item->GetChannelInfo()[j]->SlaveDevId,FALSE);
					fDeviceInfoArray[j]->DevInfo = pChannel->DevInfo;
					fDeviceInfoArray[j]->Channel = pChannel->Channel;

					QTreeWidgetItem *treeNode = new QTreeWidgetItem(QStringList(item->GetChannelInfo()[j]->szChannelName));
					treeNode->setIcon(0,QIcon(":/Client/res/cameraitem.ico"));
					treeNode->setCheckState(0,Qt::Unchecked);
					treeNode->setData(1,0,QVariant::fromValue((void *) fDeviceInfoArray[j]));
					QTreeWidgetItem *rootNode = NULL;

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

void CDevTree::ShowTreebyType1(QTreeWidget *widget)
{
	QString strEncDev = QStringLiteral("编码设备");
	QString strDecDev = QStringLiteral("解码设备");
	QString strNVRDev = QStringLiteral("NVR设备");
	QString strIPCAMDev = QStringLiteral("IPC设备");
	QString strNVTDev = QStringLiteral("智能设备");
	QString strCRTDev = QStringLiteral("告警设备");

	//根节点
	QTreeWidgetItem *rootNodeEnc = new QTreeWidgetItem(QStringList(strEncDev));
	rootNodeEnc->setIcon(0,QIcon(":/Client/res/net.ico"));
	QTreeWidgetItem *rootNodeDEc = new QTreeWidgetItem(QStringList(strDecDev));
	rootNodeDEc->setIcon(0,QIcon(":/Client/res/net.ico"));
	QTreeWidgetItem *rootNodeNVR = new QTreeWidgetItem(QStringList(strNVRDev));
	rootNodeNVR->setIcon(0,QIcon(":/Client/res/net.ico"));
	QTreeWidgetItem *rootNodeIPC = new QTreeWidgetItem(QStringList(strIPCAMDev));
	rootNodeIPC->setIcon(0,QIcon(":/Client/res/net.ico"));
	QTreeWidgetItem *rootNodeNVT = new QTreeWidgetItem(QStringList(strNVTDev));
	rootNodeNVT->setIcon(0,QIcon(":/Client/res/net.ico"));
	QTreeWidgetItem *rootNodeCRT  = new QTreeWidgetItem(QStringList(strCRTDev));
	rootNodeCRT->setIcon(0,QIcon(":/Client/res/net.ico"));
	widget->addTopLevelItem(rootNodeIPC);
	widget->addTopLevelItem(rootNodeNVR);
	widget->addTopLevelItem(rootNodeDEc);

	for (int i = 0;i < m_lstMasterDev.size();i++)
	{
		QTreeWidgetItem *child =  new QTreeWidgetItem(QStringList(m_lstMasterDev[i]->szIpAddr));
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
					treeNode->setIcon(0,QIcon(":/Client/res/cameraitem.ico"));
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
void CDevTree::QStringList_removeDuplicates(QStringList *that)
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

