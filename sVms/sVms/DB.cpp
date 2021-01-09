#define  _CRT_SECURE_NO_WARNINGS
#include "DB.h"
#include <QDebug>
#include <QSqlError>
#include <qicon.h>
#include <QMessageBox>
#include <QString>
#include <QCoreApplication>
#include "myhelper.h"

QSqlDatabase dbClient;//A1600Client.db
QSqlDatabase dbRecord;//JVTIAC.db

DB::DB(QWidget* parent)
:QWidget(parent)
{
}


DB::~DB(void)
{
	if (m_pQueryClient)
	{
		delete m_pQueryClient;
		m_pQueryClient = NULL;
	}
	if (m_pQueryRecord)
	{
		delete m_pQueryRecord;
		m_pQueryRecord = NULL;
	}
}

DWORD WINAPI DB::DBClearThread(LPVOID Para)
{
	DB *pDb = (DB*)Para;
	pDb->DBThreadProc();
	return 0;
}


void DB::DbCmpVacuumTbl()
{
	char sql_cmd[256] = { 0 };
	memset(sql_cmd, 0, sizeof(sql_cmd));
	strcat(sql_cmd, "vacuum;");
	m_pQueryClient->exec(sql_cmd);
	m_pQueryRecord->exec(sql_cmd);
	if (!m_pQueryClient->first())
	{
		return ;
	}
}

QSqlDatabase DB::getDB()
{
	return dbClient;
}
void DB::DBThreadProc()
{
	CreateConnectionDB(dbClient,m_szDBPath);
	CreateConnectionDB(dbRecord,m_szJVTIACDBPath);

	m_pQueryClient = new QSqlQuery(dbClient);
	m_pQueryRecord = new QSqlQuery(dbRecord);

	DbCmpVacuumTbl();

	return;
}

void DB::CreateConnectionDB(QSqlDatabase& db,QString szDBPath)
{
	if(QSqlDatabase::contains("qt_sql_default_connection"))
		db = QSqlDatabase::database("qt_sql_default_connection");
	else
	{
		db = QSqlDatabase::addDatabase("QSQLITE",szDBPath); //创建一个数据库

		//szDBPath = QCoreApplication::applicationDirPath() + "/" + szDBPath;
		db.setDatabaseName(szDBPath);

		if (!db.open())
		{
			CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
			QApplication::postEvent(this, custevent);
		}	
	}
	
}
bool DB::CheckUser(QString szName,QString szPassword)
{	
	QString strLogin = QString("select * from UserInfo where UserName = '%1' and Password = '%2'").arg(szName).arg(szPassword);
	qDebug()<<strLogin;
	m_pQueryClient->exec(strLogin);
	if (!m_pQueryClient->first())
	{
		return false;
	}

	return true;

}

int DB::getUserCount()
{
	int nCount = 0;
	QString strSql = QString("select * from UserInfo");
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	while (m_pQueryClient->next())
	{
		nCount++;
	}
	return nCount;
}
bool DB::CheckLock(QString szPassword)
{
	QString strLogin = QString("select * from UserInfo where  Password = '%1'").arg(szPassword);
	m_pQueryClient->exec(strLogin);
	if (!m_pQueryClient->first())
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}
bool DB::createConnection()
{
	m_nCmpInfoSize = 0;
	m_hThread = NULL;
	m_szDBPath = QCoreApplication::applicationDirPath()+"/bak/A1600Client.db";
	m_szJVTIACDBPath = QCoreApplication::applicationDirPath()+"/bak/JVTIAC.db";
	DWORD dwThreadId = 0;
	m_hThread = CreateThread(0, 0, DBClearThread, this, 0, &dwThreadId);
	
	return true;
}

bool DB::ModifyUser(QString szName,QString szPassword)
{	
	QString strLogin = QString("update UserInfo set Password = '%1' where UserName = '%2'")
				.arg(szPassword).arg(szName);
	if (m_pQueryClient->first())
	{
		return false;
	}
	m_pQueryClient->exec(strLogin);
	return true;
}

bool DB::AddUser(QString szUserName,QString szPassword)
{
	QString strLogin  = QString("select * from UserInfo where UserName = '%1'").arg(szUserName);
	m_pQueryClient->exec(strLogin);
	if (m_pQueryClient->first())
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	strLogin = QString("insert into UserInfo values(NULL,'%1','%2')").arg(szUserName).arg(szPassword);
	m_pQueryClient->exec(strLogin);
	return true;
}

bool DB::AddDevice(TabDevInfo_t* pDevInfo)
{
	QString strDevInfo  = QString("select * from DevInfo where IpAddr = '%1'").arg(pDevInfo->szIpAddr);
	m_pQueryClient->exec(strDevInfo);
	if (m_pQueryClient->first())
	{
		return false;
	}

	strDevInfo = QString("insert into DevInfo values(NULL,'%1','%2','%3','%4','%5','%6','%7','%8','%9','%10',NULL)")
				.arg(pDevInfo->szIpAddr).arg(pDevInfo->nPort).arg(pDevInfo->szLoginName).arg(pDevInfo->szPassword).arg(pDevInfo->szDevName).arg(pDevInfo->nType).arg(pDevInfo->nManufacturer).arg(pDevInfo->szDevType).arg(pDevInfo->nDevStatus).arg(pDevInfo->nSubDevType);
	bool ret = m_pQueryClient->exec(strDevInfo);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}

bool DB::ChangeDevice(TabDevInfo_t* pDevInfo)
{
	QString strDevInfo = QString("update DevInfo set IpAddr ='%1',Port = '%2',LoginName = '%3',Password='%4',DevName = '%5',Manufacturer = '%6',DevType = '%7',DevStatus = '%8',SubDevType = '%9' where IpAddr = '%10'")
		.arg(pDevInfo->szIpAddr).arg(pDevInfo->nPort).arg(pDevInfo->szLoginName).arg(pDevInfo->szPassword).arg(pDevInfo->szDevName).arg(pDevInfo->nManufacturer).arg(pDevInfo->szDevType).arg(pDevInfo->nDevStatus).arg(pDevInfo->nSubDevType).arg(pDevInfo->szIpAddr);
	bool ret = m_pQueryClient->exec(strDevInfo);
	if (!ret)
	{

		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}

bool DB::ChangeChannelInfo(int ChannelNum, QString ChannelName, int Type)
{
	QString strDevInfo = QString("update ChannelInfo set ChannelName = '%1',Type = %2 where Channel = %3" )
		.arg(ChannelName).arg(Type).arg(ChannelNum);
	bool ret = m_pQueryClient->exec(strDevInfo);
	if (!ret)
	{

		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}

bool DB::AddChannelInfo(TabChannelInfo_t* pChInfo)
{
	QString strDevInfo  = QString("insert into ChannelInfo values(NULL,'%1','%2','%3','%4','%5')").arg(pChInfo->DevId).arg(pChInfo->Channel).arg(pChInfo->szChannelName).arg(pChInfo->Type).arg(pChInfo->Status);
	qDebug() << strDevInfo;
	bool ret = m_pQueryClient->exec(strDevInfo);
	if (!ret)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}

bool DB::delAllDevInfo()
{
	QString strSql = QString("delete from ChannelInfo");
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		strSql = QString("delete from DevInfo");
		bool ret = m_pQueryClient->exec(strSql);
		if (!ret)
		{
			//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
			mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
			return false;
		}
	}
	return true;
}

int DB::getDeviceID(QString strIP)
{
	int devid = 0;
	QString strSql = QString("select * from DevInfo where IpAddr = '%1'").arg(strIP);
	bool ret  = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	while(m_pQueryClient->next())
	{
		devid =  m_pQueryClient->value("DevId").toInt();
	}
	return devid;
}

bool DB::DelChannelInfo(int DeviceId)
{
	QString	strDel = QString("delete from ChannelInfo where DevId = '%1'").arg(DeviceId);
		bool ret = m_pQueryClient->exec(strDel);
		if (!ret)
		{
			//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
			mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
			return false;
		}
		else
		{
			strDel = QString("delete from DevInfo where DevId = '%1'").arg(DeviceId);
			ret = m_pQueryClient->exec(strDel);
			if (!ret)
			{
				//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
				mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
				return false;
			}
			else
			{
				return true;
			}
		}
	
}

bool DB::getAllTreeNodes(vector<treeNode> &vTreeNodes)
{
	QString querySql = QString("select IpAddr,Type,DevType from DevInfo");
	bool isOk = m_pQueryClient->exec(querySql);
	if(!isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	while(m_pQueryClient->next())
	{
		treeNode data;
		
		QString IpAddr = m_pQueryClient->value("IpAddr").toString();
		int Type = m_pQueryClient->value("Type").toInt();
		QString DevType = m_pQueryClient->value("DevType").toString();

		
		data.IpAddr = IpAddr;
		data.Type = Type;
		data.DevType = DevType;
		vTreeNodes.push_back(data);
	}
	return true;
}

bool DB::queryChildNodesById(int id,vector<treeNode> &vNodesID)
{
	QString querySql = QString("select IpAddr,Type,DevType from DevInfo where Type = '%1'").arg(id);
	bool isOk = m_pQueryClient->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}

	while(m_pQueryClient->next())
	{
		treeNode data;
	
		QString IpAddr = m_pQueryClient->value("IpAddr").toString();
		int Type = m_pQueryClient->value("Type").toInt();
		QString DevType = m_pQueryClient->value("DevType").toString();

		data.IpAddr = IpAddr;
		data.Type = Type;
		data.DevType = DevType;
		vNodesID.push_back(data);
	}
	return true;
}

bool DB::getAllTreeMessage(vector<TabDevInfo_t> &vTreeMessage)
{
	QString querySql = QString("select * from DevInfo");
	bool isOk = m_pQueryClient->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}

	while(m_pQueryClient->next())
	{
		TabDevInfo_t data;
		int devId = m_pQueryClient->value("DevId").toInt();
		QString szIpAddr = m_pQueryClient->value("IpAddr").toString();
		int nPort = m_pQueryClient->value("Port").toInt();
		QString szLoginName = m_pQueryClient->value("LoginName").toString();
		QString szPassword = m_pQueryClient->value("Password").toString();
		QString szDevName = m_pQueryClient->value("DevName").toString();
	    int nType = m_pQueryClient->value("Type").toInt();
		int nManufaceturer = m_pQueryClient->value("Manufacturer").toInt();
		QString szDevType = m_pQueryClient->value("DevType").toString();
		int nDevStatus = m_pQueryClient->value("DevStatus").toInt();
		//int nSubDevType = query->value("SubDevType").toInt();
		//QString szUUID = query->value("UUID").toString();

		data.nDevId = devId;
		strcpy(data.szIpAddr,szIpAddr.toLatin1().data());
		data.nPort = nPort;
		strcpy(data.szLoginName,szLoginName.toLatin1().data());
		strcpy(data.szPassword,szPassword.toLatin1().data());
		strcpy(data.szDevName,szDevName.toLatin1().data());
		data.nType = nType;
		data.nManufacturer = nManufaceturer;
		strcpy(data.szDevType,szDevType.toLatin1().data());
		data.nDevStatus = nDevStatus;
		//data.nSubDevType = nSubDevType;
		//data.szUUID = szUUID;
		vTreeMessage.push_back(data);

		qDebug()<<szIpAddr;
	}

	return true;
}

int DB::QueryAllMainDev(std::vector<TabDevInfo_t *>& vectorDevice)
{
	int nCount = 0;
	QString querySql = QString("select * from DevInfo");
	bool isOk = m_pQueryClient->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -1;
	}

	while(m_pQueryClient->next())
	{
		TabDevInfo_t *data = new TabDevInfo_t;
		data->nDevId = m_pQueryClient->value("DevId").toInt();
		strncpy(data->szIpAddr, m_pQueryClient->value("IpAddr").toString().toLatin1().data(), sizeof(data->szIpAddr)-1);
		data->nPort = m_pQueryClient->value("Port").toInt();
		strncpy(data->szLoginName, m_pQueryClient->value("LoginName").toString().toLocal8Bit().data(), sizeof(data->szLoginName) - 1);
		strncpy(data->szPassword, m_pQueryClient->value("Password").toString().toLatin1().data(), sizeof(data->szPassword) - 1);
		strncpy(data->szDevName, m_pQueryClient->value("DevName").toString().toLocal8Bit().data(), sizeof(data->szDevName) - 1);
		data->nType = m_pQueryClient->value("Type").toInt();
		data->nManufacturer = m_pQueryClient->value("Manufacturer").toInt();
		strncpy(data->szDevType, m_pQueryClient->value("DevType").toString().toLatin1().data(), sizeof(data->szDevType)-1);
		data->nDevStatus = m_pQueryClient->value("DevStatus").toInt();
		data->nSubDevType = m_pQueryClient->value("SubDevType").toInt();
		strncpy(data->szUUID, m_pQueryClient->value("UUID").toString().toLatin1().data(), sizeof(data->szUUID) - 1);
		
		vectorDevice.push_back(data);
		nCount ++;
	}
	return nCount;
}

int DB::QueryAllSlaveDev(std::vector<TabChannelInfo_t *>& vectorChannelInfo,int nDevId /* = -1 */)
{
	int nCount = 0;
	QString querySql;
	if (nDevId == -1)
	{
		querySql = QString("SELECT * FROM ChannelInfo order by Channel asc;");
	}
	else
	{
		querySql = QString("SELECT * FROM ChannelInfo where DevId=%1 order by Channel asc").arg(nDevId);
	}

	bool isOk = m_pQueryClient->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	while(m_pQueryClient->next())
	{
		TabChannelInfo_t *channelData =new TabChannelInfo_t;
		memset(channelData->szChannelName, '\0', sizeof(channelData->szChannelName));
		channelData->SlaveDevId = m_pQueryClient->value("SlaveDevId").toInt();
		channelData->DevId = m_pQueryClient->value("DevId").toInt();
		channelData->Channel = m_pQueryClient->value("Channel").toInt();
		strncpy(channelData->szChannelName, m_pQueryClient->value("ChannelName").toString().toLatin1().data(), sizeof(channelData->szChannelName));
		channelData->Type = m_pQueryClient->value("Type").toInt();
		channelData->Status = m_pQueryClient->value("Status").toInt();

		vectorChannelInfo.push_back(channelData);
		nCount++;
	}
	return nCount;
}

int DB::GetChannelID(int nDevId, int nChannelId)
{
	int nChId = 0;
	QString strSql = QString("select * from ChannelInfo where DevId = %1 and Channel = %2").arg(nDevId).arg(nChannelId);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	while (m_pQueryClient->next())
	{
		nChId = m_pQueryClient->value("SlaveDevId").toInt();
	}
	return nChId;
}

int DB::QueryAllDevGroup(std::list<TabUserDevGroup_t *>& lstDevGroup)
{
	int nCount = 0;
	QString querySql = QString("select * from UserDevGroup");
	bool isOk = m_pQueryClient->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	while(m_pQueryClient->next())
	{
		TabUserDevGroup_t *DevGroup =new TabUserDevGroup_t;
		DevGroup->Id = m_pQueryClient->value("Id").toInt();
		strcpy(DevGroup->szGroupName ,m_pQueryClient->value("GroupName").toString().toLatin1().data());
		DevGroup->ParentId = m_pQueryClient->value("ParentId").toInt();
		lstDevGroup.push_back(DevGroup);
		nCount ++;
	}
	return nCount;
}

int DB::QueryAllGroupChannel(std::vector<TabDevGroup_t *>& lstGroupChannel)
{
	int nCount = 0;
	QString querySql = QString("select * from DevGroup");
	bool isOk = m_pQueryClient->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	while(m_pQueryClient->next())
	{
		TabDevGroup_t *DevGroup = new TabDevGroup_t;
		DevGroup->Id = m_pQueryClient->value("Id").toInt();
		DevGroup->GroupId = m_pQueryClient->value("GroupId").toInt();
		DevGroup->SlaveDevId = m_pQueryClient->value("SlaveDevId").toInt();
		lstGroupChannel.push_back(DevGroup);
	}
	return nCount;
}

bool DB::changeFilePath(QString picPath,QString videoPath,QString DownPath,QString snapPath)
{
	QString strSql = QString("update CommonCfg set PicPath = '%1',VideoPath = '%2',DownPath = '%3',SnapPath = '%4' where Id = 1")
		.arg(picPath).arg(videoPath).arg(DownPath).arg(snapPath);

	bool isOk = m_pQueryClient->exec(strSql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}

bool DB::getFilePath(QString &picPath,QString &DownPath,QString &snapPath)
{
	QString strSql = QString("select * from CommonCfg where Id = 1");
	bool isOk = m_pQueryClient->exec(strSql);
	if (false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (m_pQueryClient->next())
		{
			picPath = m_pQueryClient->value("PicPath").toString();
			DownPath = m_pQueryClient->value("DownPath").toString();
			snapPath = m_pQueryClient->value("SnapPath").toString();
		}
	}
	return true;
}


bool DB::checkDevice(QString nIP,int port)
{
	QString strCheck = QString("select DevId from DevInfo where IpAddr = '%1' and port = '%2';").arg(nIP).arg(port);
	m_pQueryClient->exec(strCheck);
	if (!m_pQueryClient->first())
	{
		return false;
	}
	return true;
}

int DB::QueryAllDeviceMsg(std::vector<pDevObj *>& listDev,QString IpAddr)
{
	int nCount = 0;
	QString querySql = QString("select * from DevInfo where IpAddr = '%1'").arg(IpAddr);
	bool isOk = m_pQueryClient->exec(querySql);
	if(false == isOk)
	{
		qDebug()<<"sql select * from DevGroup error";
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	while(m_pQueryClient->next())
	{
		pDevObj *DevGroup = new pDevObj	;
		DevGroup->DevId = m_pQueryClient->value("DevId").toInt();
		DevGroup->IpAddr = m_pQueryClient->value("IpAddr").toString();
		DevGroup->port = m_pQueryClient->value("Port").toInt();
		DevGroup->szName = m_pQueryClient->value("LoginName").toString();
		DevGroup->szPassWord = m_pQueryClient->value("Password").toString();
		DevGroup->devName = m_pQueryClient->value("DevName").toString();
		DevGroup->Type = m_pQueryClient->value("Type").toInt();
		DevGroup->manfacturer = m_pQueryClient->value("Manufacturer").toInt();
		DevGroup->DevType = m_pQueryClient->value("DevType").toInt();
		DevGroup->DevStatus = m_pQueryClient->value("DevStatus").toInt();
		DevGroup->SubType = m_pQueryClient->value("SubDevType").toInt();
		DevGroup->UUID = m_pQueryClient->value("UUID").toString();
		listDev.push_back(DevGroup);
	}
	return 0;
}

int DB::QueryDeviceChannelMsg(int Devid)
{
	int nCount = 0;
	QString querySql = QString("select * from ChannelInfo where DevId = '%1'").arg(Devid);
	bool isOk = m_pQueryClient->exec(querySql);
	if (false == isOk)
	{
		qDebug() << "sql select * from DevGroup error";
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	while (m_pQueryClient->next())
	{
		nCount++;
	}
	return nCount;
}
int DB::QueryAllChannelMsg(std::vector<ChannelInfo *>& listDev, int DevId, int ch)
{
	listDev.clear();
	QString querySql = QString("select * from ChannelInfo where DevId = '%1' and Channel = '%2';").arg(DevId).arg(ch);
	bool isOk = m_pQueryClient->exec(querySql);
	if (false == isOk)
	{
		qDebug() << "sql select * from DevGroup error";
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	while (m_pQueryClient->next())
	{
	
		ChannelInfo *chinfo = new ChannelInfo;
		chinfo->szChannel = m_pQueryClient->value("Channel").toInt();
		chinfo->szChannelName = m_pQueryClient->value("ChannelName").toString();
		chinfo->ChannelType = m_pQueryClient->value("Type").toInt();
		listDev.push_back(chinfo);
	}
	return 0;
}

int DB::GetCmpFindInfo(FS_FIND_INFO *find_info, std::vector<SMART_FACE_CMP_QUERY_INFO *>& vectorCompare, char* pszBuf)
{
	int nCount = 0;
	QString strSql = "";
	if (pszBuf)
	{
		strSql = QString("SELECT * FROM CmpInfoList WHERE time>='%1' AND time <='%2' %3;").arg(QString(QLatin1String(find_info->StartTime)))
			.arg(QString(QLatin1String(find_info->EndTime))).arg(QString::fromLocal8Bit(pszBuf));

		qDebug() << strSql;
		bool ret = m_pQueryRecord->exec(strSql);
		if (!ret)
		{
			QString str = m_pQueryRecord->lastError().text();
			qDebug() << m_pQueryRecord->lastError().text();
			mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryRecord->lastError().text()).toLocal8Bit().data());
			return false;
		}
		while (m_pQueryRecord->next())
		{
			SMART_FACE_CMP_QUERY_INFO* pCompareInfo = new SMART_FACE_CMP_QUERY_INFO;
			memset(pCompareInfo, 0, sizeof(SMART_FACE_CMP_QUERY_INFO));
			pCompareInfo->sLibSimilarity = m_pQueryRecord->value("Similarity").toFloat();
			pCompareInfo->sLibMode = m_pQueryRecord->value("face_mode").toInt();
			pCompareInfo->nLibGuest = m_pQueryRecord->value("guest").toInt();
			pCompareInfo->cLibGender = m_pQueryRecord->value("sex").toInt();
			pCompareInfo->cLibAge = m_pQueryRecord->value("age").toInt();
			pCompareInfo->cLibGlasses = m_pQueryRecord->value("glasses").toInt();
			pCompareInfo->cLibEye = m_pQueryRecord->value("eye").toInt();
			pCompareInfo->cLibMask = m_pQueryRecord->value("mask").toInt();
			pCompareInfo->cLibRace = m_pQueryRecord->value("race").toInt();
			pCompareInfo->cLibAttractive = m_pQueryRecord->value("charm").toInt();
			strcpy((char *)pCompareInfo->sLibSnapTime, m_pQueryRecord->value("time").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sSnappicname, m_pQueryRecord->value("SnapName").toString().toLatin1().data());
			pCompareInfo->cLibBeard = m_pQueryRecord->value("Beard").toInt();
			pCompareInfo->cLibEmotion = m_pQueryRecord->value("Emotion").toInt();
			pCompareInfo->sLibChannelid = m_pQueryRecord->value("channelId").toInt();
			strcpy((char *)pCompareInfo->cDeviceIP, m_pQueryRecord->value("DeviceIP").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sLibPicName, m_pQueryRecord->value("libName").toString().toLocal8Bit().data());
			strcpy((char *)pCompareInfo->cPath, m_pQueryRecord->value("path").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sUserID, m_pQueryRecord->value("userId").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sName, m_pQueryRecord->value("name").toString().toLocal8Bit().data());
			pCompareInfo->sSysListID = m_pQueryRecord->value("sysListId").toInt();
			pCompareInfo->fTemperature = m_pQueryRecord->value("Temperature").toFloat();
			vectorCompare.push_back(pCompareInfo);
			nCount++;
		}
	}

	return nCount;
}

int DB::QueryComparison(FS_FIND_INFO *find_info,  std::vector<SMART_FACE_CMP_QUERY_INFO *>& vectorCompare)
{
	QString strSql = NULL;
	int nFindRow = 0;
	char szTemp[256] = {0};
	char szIP[32] = {0};
	std::string strTemp;
	int offsetnum;

	if (find_info->nDevNumber > 0)
	{
		sprintf(szTemp, "AND (%s", "DeviceIP = ");		
		strTemp = szTemp;
		memset(&szTemp, 0, sizeof(szTemp));
		for (int i = 0; i < find_info->nDevNumber; i++)
		{
			strTemp.append(szTemp);
			memset(&szIP, 0, sizeof(szIP));
			sprintf(szIP, "'%s'", find_info->fsDevInfo[i].cDeviceIP);
			strTemp.append(szIP);
			sprintf(szTemp, "%s", " or DeviceIP = ");
		}
		strTemp.append(")");
	}
	if (find_info->Wbmode)
	{
		sprintf(szTemp, " AND face_mode = %d", find_info->Wbmode - 1);
		strTemp.append(szTemp);
	}
	if (strlen(find_info->name) > 0)
	{
		sprintf(szTemp, " AND name LIKE '%s'", find_info->name);
		strTemp.append(szTemp);
	}
	if (strlen(find_info->number) > 0)
	{
		sprintf(szTemp, " AND userId = '%s'", find_info->number);
		strTemp.append(szTemp);
	}

	if(find_info->flag == FLAG_SEARCH_FIRST || find_info->flag == FLAG_SEARCH_EXPORT)
	{
		nFindRow = GetCmpFindInfo(find_info, vectorCompare, (char*)strTemp.c_str());
		m_nCmpInfoSize = nFindRow;
		find_info->curpage = 1;
		if(find_info->flag == FLAG_SEARCH_EXPORT || nFindRow <= 0)
		{
			return nFindRow;
		}
	}

	offsetnum = m_nCmpInfoSize - find_info->curpage * find_info->pagecount;
	if(offsetnum < 0)
		offsetnum = 0;

	strSql = QString("SELECT * FROM CmpInfoList WHERE time>='%1' AND time <='%2' %3 limit '%4' offset '%5';").arg(QString(QLatin1String(find_info->StartTime)))
		.arg(QString(QLatin1String(find_info->EndTime))).arg(QString::fromLocal8Bit(strTemp.c_str())).arg(find_info->pagecount).arg(offsetnum);

	qDebug() << strSql;

	bool retResult = m_pQueryRecord->exec(strSql);
	if (!retResult)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryRecord->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (m_pQueryRecord->next())
		{
			SMART_FACE_CMP_QUERY_INFO* pCompareInfo = new SMART_FACE_CMP_QUERY_INFO;
			memset(pCompareInfo, 0, sizeof(SMART_FACE_CMP_QUERY_INFO));

			pCompareInfo->sLibSimilarity = m_pQueryRecord->value("Similarity").toFloat();
			pCompareInfo->sLibMode = m_pQueryRecord->value("face_mod").toInt();
			pCompareInfo->nLibGuest = m_pQueryRecord->value("guest").toInt();
			pCompareInfo->cLibGender = m_pQueryRecord->value("sex").toInt();
			pCompareInfo->cLibAge = m_pQueryRecord->value("age").toInt();
			pCompareInfo->cLibGlasses = m_pQueryRecord->value("glasses").toInt();
			pCompareInfo->cLibEye = m_pQueryRecord->value("eye").toInt();
			pCompareInfo->cLibMask = m_pQueryRecord->value("mask").toInt();
			pCompareInfo->cLibRace = m_pQueryRecord->value("race").toInt();
			pCompareInfo->cLibAttractive = m_pQueryRecord->value("charm").toInt();
			strcpy((char *)pCompareInfo->sLibSnapTime, m_pQueryRecord->value("time").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sSnappicname, m_pQueryRecord->value("SnapName").toString().toLatin1().data());
			pCompareInfo->cLibBeard = m_pQueryRecord->value("Beard").toInt();
			pCompareInfo->cLibEmotion = m_pQueryRecord->value("Emotion").toInt();
			pCompareInfo->sLibChannelid= m_pQueryRecord->value("channelId").toInt();
			strcpy((char *)pCompareInfo->cDeviceIP, m_pQueryRecord->value("DeviceIP").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sLibPicName, m_pQueryRecord->value("libName").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->cPath, m_pQueryRecord->value("path").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sUserID, m_pQueryRecord->value("userId").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sName, m_pQueryRecord->value("name").toString().toLocal8Bit().data());
			pCompareInfo->sSysListID = m_pQueryRecord->value("sysListId").toInt();
			pCompareInfo->fTemperature = m_pQueryRecord->value("Temperature").toFloat();
			vectorCompare.push_back(pCompareInfo);
		}
	}
	
	return m_nCmpInfoSize;
}

bool DB::AddCMPInfo(SMART_FACE_CMP_QUERY_INFO* pCompareInfo)
{	
	char* pUTF8 = NULL;
	std::string strName;
	std::string strSnapName;

	int nLength = strlen(pCompareInfo->sName);
	if (nLength > 0 && nLength < 1024)
	{
		pUTF8 = new char[nLength * 2 + 2];
		if (pUTF8)
		{
			memset(pUTF8, 0, nLength * 2 + 2);
			Change_Unicode_UTF8(pCompareInfo->sName, nLength, pUTF8, nLength * 2 + 2);
			strName = pUTF8;
			delete [] pUTF8;
			pUTF8 = NULL;
		}
	}
	nLength = strlen(pCompareInfo->sLibPicName);
	if (nLength > 0 && nLength < 1024)
	{
		pUTF8 = new char[nLength * 2 + 2];
		if (pUTF8)
		{
			memset(pUTF8, 0, nLength * 2 + 2);
			Change_Unicode_UTF8(pCompareInfo->sLibPicName, nLength, pUTF8, nLength * 2 + 2);
			strSnapName = pUTF8;
			delete [] pUTF8;
			pUTF8 = NULL;
		}
	}
	
	QString str = QString::fromLocal8Bit(strName.data());
	QString strSql=QString("INSERT INTO CmpInfoList VALUES('%1','%2', '%3','%4', '%5','%6','%7','%8','%9','%10', '%11','%12','%13','%14', '%15', '%16', '%17', '%18', '%19', '%20', '%21', %22, '%23');")
		.arg(pCompareInfo->sLibSimilarity).arg(pCompareInfo->sLibMode)
		.arg(pCompareInfo->nLibGuest).arg((int)(pCompareInfo->cLibGender)).arg((int)(pCompareInfo->cLibAge))
		.arg((int)pCompareInfo->cLibGlasses).arg((int)pCompareInfo->cLibEye).arg((int)pCompareInfo->cLibMask)
		.arg((int)pCompareInfo->cLibRace).arg((int)pCompareInfo->cLibAttractive).arg(QString(QLatin1String(pCompareInfo->sLibSnapTime)))
		.arg(QString::fromLocal8Bit(pCompareInfo->sLibPicName)).arg(QString(QLatin1String(pCompareInfo->sSnappicname)))
		.arg((int)pCompareInfo->cLibBeard).arg((int)pCompareInfo->cLibEmotion).arg(0).arg(pCompareInfo->sLibChannelid)
		.arg(QString(QLatin1String(pCompareInfo->cDeviceIP))).arg(QString(QLatin1String(pCompareInfo->cPath)))
		.arg(QString::fromLocal8Bit(pCompareInfo->sName)).arg(QString(QLatin1String(pCompareInfo->sUserID)))
		.arg(pCompareInfo->sSysListID).arg(pCompareInfo->fTemperature);
	//qDebug() << strSql;
	bool ret = m_pQueryRecord->exec(strSql);
	if (!ret)
	{
		qDebug() << m_pQueryRecord->lastError();
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryRecord->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}

void DB::Change_Unicode_UTF8(char *pStrGBKData, int nlen, char *pbuf, int buflen)
{
#ifdef WIN32

	int oldlen = 0;
	int newlen = 0;
	char *pUTF8 = new char[nlen*2+2];
	memset(pUTF8, 0 , nlen*2+2);

	while(oldlen < nlen)
	{
		if(*(pStrGBKData + oldlen) >= 0)
		{
			*(pUTF8 + newlen) = *(pStrGBKData + oldlen);
			newlen ++;
			oldlen ++;
		}
		else
		{
			char tmpbuf[8] = {0};
			wchar_t pUnicode;
			A2W_Mine(pStrGBKData + oldlen, &pUnicode);
			Single_UNICODE_UTF8(tmpbuf, pUnicode);
			*(pUTF8 + newlen) = tmpbuf[0];
			*(pUTF8 + newlen + 1) = tmpbuf[1];
			*(pUTF8 + newlen + 2) = tmpbuf[2];
			newlen += 3;
			oldlen += 2;
		}
	}

	pUTF8[newlen] = '\0';
	memcpy(pbuf, pUTF8, (nlen*2+2 > buflen)? buflen : nlen*2+2);
	delete pUTF8;

#else	//linux
	iconv_t cd = iconv_open("utf-8","gbk"); 
	if(cd==(iconv_t)-1)
	{
		printf("iconv_t fail.\n");
	}

	size_t inLen = nlen;
	size_t outLen = buflen;
	unsigned int nconv = iconv(cd, &pStrGBKData, &inLen, &pbuf, &outLen);

	iconv_close(cd);
#endif

	return ;
}

void DB::A2W_Mine(char *lpszA, wchar_t *lpszW)
{
#ifdef WIN32
	int nLen = MultiByteToWideChar(CP_ACP, 0, lpszA, 2, NULL, NULL);
	int nRet = MultiByteToWideChar(CP_ACP, 0, lpszA, 2, lpszW, nLen);
	if (!nRet) 
	{
		//TRACE("convert error");
		int error = GetLastError();
	}
#else	//linux
	size_t result = mbstowcs(lpszW, lpszA, (size_t)1);
#endif
}

size_t DB::Single_UNICODE_UTF8(char * dest_str, wchar_t src_wchar)
{
	int count_bytes = 0;
	wchar_t byte_one = 0, byte_other = 0x3f; // 用于位与运算以提取位值 0x3f--->00111111
	unsigned char utf_one = 0, utf_other = 0x80; // 用于"位或"置标UTF-8编码 0x80--->1000000
	wchar_t tmp_wchar = L'0'; // 用于宽字符位置析取和位移(右移6位)
	unsigned char tmp_char = '0';

	if (!src_wchar)//
		return (size_t)-1;

	for (;;) // 检测字节序列长度
	{
		if (src_wchar <= 0x7f)
		{ // <=01111111
			count_bytes = 1; // ASCII字符: 0xxxxxxx( ~ 01111111)
			byte_one = 0x7f; // 用于位与运算, 提取有效位值, 下同
			utf_one = 0x0;
			break;
		}
		if ( (src_wchar > 0x7f) && (src_wchar <= 0x7ff) )
		{ // <=0111,11111111
			count_bytes = 2; // 110xxxxx 10xxxxxx[1](最多11个1位, 简写为11*1)
			byte_one = 0x1f; // 00011111, 下类推(1位的数量递减)
			utf_one = 0xc0; // 11000000
			break;
		}
		if ( (src_wchar > 0x7ff) && (src_wchar <= 0xffff) )
		{ //0111,11111111<=11111111,11111111
			count_bytes = 3; // 1110xxxx 10xxxxxx[2](MaxBits: 16*1)
			byte_one = 0xf; // 00001111
			utf_one = 0xe0; // 11100000
			break;
		}
		if ( (src_wchar > 0xffff) && (src_wchar <= 0x1fffff) )
		{ //对UCS-4的支持..
			count_bytes = 4; // 11110xxx 10xxxxxx[3](MaxBits: 21*1)
			byte_one = 0x7; // 00000111
			utf_one = 0xf0; // 11110000
			break;
		}
		if ( (src_wchar > 0x1fffff) && (src_wchar <= 0x3ffffff) )
		{
			count_bytes = 5; // 111110xx 10xxxxxx[4](MaxBits: 26*1)
			byte_one = 0x3; // 00000011
			utf_one = 0xf8; // 11111000
			break;
		}
		if ( (src_wchar > 0x3ffffff) && (src_wchar <= 0x7fffffff) )
		{
			count_bytes = 6; // 1111110x 10xxxxxx[5](MaxBits: 31*1)
			byte_one = 0x1; // 00000001
			utf_one = 0xfc; // 11111100
			break;
		}
		return (size_t)-1; 
	}

	tmp_wchar = src_wchar;
	for (int i = count_bytes; i > 1; i--)
	{ // 一个宽字符的多字节降序赋值
		tmp_char = (unsigned char)(tmp_wchar & byte_other);///后6位与byte_other 00111111
		dest_str[i - 1] = (tmp_char | utf_other);/// 在前面加10----跟10000000或
		tmp_wchar >>= 6;//右移6位
	}

	tmp_char = (unsigned char)(tmp_wchar & byte_one);
	dest_str[0] = (tmp_char | utf_one);

	return count_bytes;
}

int DB::QuerryAlarmLog(std::list<TabAlarmLog_t *>& lstAlarmLog, QString pBeginTime, QString pEndTime )
{
	int ncount = 0;
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = QString("SELECT * FROM AlarmLog where BeginTime > '%1'and BeginTime < '%2'").arg(pBeginTime).arg(pEndTime);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return 0;
	}
	while(m_pQueryClient->next())
	{
		TabAlarmLog_t* pAlarmLog = new TabAlarmLog_t;
		memset(pAlarmLog, 0, sizeof(TabAlarmLog_t));
		pAlarmLog->Id = m_pQueryClient->value("Id").toInt();
		pAlarmLog->AlarmConfId = m_pQueryClient->value("AlarmConfId").toInt();
		strcpy((char *)pAlarmLog->szBeginTime, m_pQueryClient->value("BeginTime").toString().toLatin1().data());
		strcpy((char *)pAlarmLog->szEndTime, m_pQueryClient->value("EndTime").toString().toLatin1().data());
		lstAlarmLog.push_back(pAlarmLog);
		ncount ++;
	}
	return ncount;
}

int DB::getAlarmConfMsg(int nAlarmConfId, int& devId, int &alarmSrc, int& channel, int &alarmType, int &alarmLevel)
{

	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql  =  QString("select c.DevId,c.AlarmName, c.AlarmSource, c.Channel, c.AlarmType ,c.AlarmLevel,c.Video from  AlarmConf as c  left join AlarmLog as l on l.AlarmConfId = c.Id where  l.AlarmConfId = '%1';").arg(nAlarmConfId);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return 0;
	}
	else
	{
		while(m_pQueryClient->next())
		{
			devId = m_pQueryClient->value("DevId").toInt();
			alarmSrc = m_pQueryClient->value("AlarmSource").toInt();
			channel = m_pQueryClient->value("Channel").toInt();
			alarmType = m_pQueryClient->value("AlarmType").toInt();
			alarmLevel = m_pQueryClient->value("AlarmLevel").toInt();
		}
		QSqlRecord sqlRecord = m_pQueryClient->record();
		return sqlRecord.count();

	}
	
}

int DB::getDevInfo(int devId, QString& szDevName)
{
	int nCount = 0;
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = QString("select * from DevInfo where DevId = '%1';").arg(devId);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return 0;
	}
	else
	{
		while (m_pQueryClient->next())
		{
			szDevName = m_pQueryClient->value("IpAddr").toString();
			nCount++;
		}
	}
	return nCount;
}

bool DB::QueryDevInfo(std::vector<pDevObj>&  lstDevInfo)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = QString("select * from DevInfo ;");
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (m_pQueryClient->next())
		{
			pDevObj m_DevInfo;
			m_DevInfo.DevId = m_pQueryClient->value("DevId").toInt();
			m_DevInfo.IpAddr = m_pQueryClient->value("IpAddr").toString();
			m_DevInfo.port = m_pQueryClient->value("Port").toInt();
			m_DevInfo.szName = m_pQueryClient->value("LoginName").toString();
			m_DevInfo.szPassWord = m_pQueryClient->value("Password").toString();
			m_DevInfo.devName = m_pQueryClient->value("DevName").toString();
			m_DevInfo.Type = m_pQueryClient->value("Type").toInt();
			m_DevInfo.manfacturer = m_pQueryClient->value("Manufacturer").toInt();
			m_DevInfo.DevType = m_pQueryClient->value("DevType").toString();
			m_DevInfo.DevStatus = m_pQueryClient->value("DevStatus").toInt();
			m_DevInfo.SubType = m_pQueryClient->value("SubDevType").toInt();
			m_DevInfo.UUID = m_pQueryClient->value("UUID").toString();
			lstDevInfo.push_back(m_DevInfo);
		}
	}
	return true;
}

int DB::SetCommonCfg(TabCommonCfg_t* pClientCfg)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = NULL;
	if (pClientCfg->nId <= 0)
	{
		strSql = QString("insert into[CommonCfg](PicPath,VideoPath,DownPath,TVWallV,TVWallH,[BeginDriver],[EndDriver],[FileTimeLen],[CycleRecord],SnapPath, PlayType) \
				values('%1','%2','%3',%4,%5,%6,%7,%8,%9,'%10',%11);").arg(pClientCfg->szPicPath).arg(pClientCfg->szVideoPath).arg(pClientCfg->szDownPath).arg(pClientCfg->nTVWallV)
				.arg(pClientCfg->nTVWallH).arg(pClientCfg->nBeginDriver).arg(pClientCfg->nEndDriver).arg(pClientCfg->nFileTimeLen).arg(pClientCfg->nCycleRecord).arg(pClientCfg->szSnapPath)
				.arg(pClientCfg->nPlayType);
	}
	else
	{
		strSql = QString("update [CommonCfg] set PicPath = '%1',VideoPath = '%2',DownPath = '%3',TVWallV = '%4',TVWallH = '%5',[BeginDriver] = '%6',[EndDriver] = '%7',"
			"[FileTimeLen]= '%8',[CycleRecord] = '%9', SnapPath = '%10', PlayType = '%11'").arg(pClientCfg->szPicPath).arg(pClientCfg->szVideoPath).arg(pClientCfg->szDownPath)
			.arg(pClientCfg->nTVWallV).arg(pClientCfg->nTVWallH).arg(pClientCfg->nBeginDriver).arg(pClientCfg->nEndDriver).arg(pClientCfg->nFileTimeLen)
			.arg(pClientCfg->nCycleRecord).arg(pClientCfg->szSnapPath).arg(pClientCfg->nPlayType);
	}
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::DeleteAlarmLog(int nId, bool bDeleteAll /* = false */)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = NULL;
	if (bDeleteAll)
		strSql = QString("delete  from AlarmLog ;");
	else
		strSql = QString("delete  from AlarmLog where Id=%1;").arg(nId);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;

}

int DB::QueryPrestPos(TabPresetPos_t* pPresetPos, int nSlaveDev, int nPresetPosId /* = -1 */)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = NULL;
	if (nPresetPosId == -1)
		strSql = QString("SELECT * FROM [PresetPos] where SlaveDevId=%1;").arg(nSlaveDev);
	else
		strSql = QString("SELECT * FROM [PresetPos] where id=%1;").arg(nPresetPosId);
	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	else
	{
		while (m_pQueryClient->next())
		{
			int nPresetNo = m_pQueryClient->value("PresetNo").toInt();
			if (nPresetNo <= 0 || nPresetNo > 256)
				continue;
			TabPresetPos_t *pPos = pPresetPos + nPresetNo;
			pPos->Id = m_pQueryClient->value("Id").toInt();
			pPos->SlaveDevId = m_pQueryClient->value("SlaveDevId").toInt();
			pPos->PresetNo = m_pQueryClient->value("PresetNo").toInt();
			strcpy(pPos->szPresetDesc, m_pQueryClient->value("PresetDesc").toString().toLatin1().data());
			nCount++;
		}
	}

	return nCount;
}

int DB::QueryTrackSequence(TabTrackSequence_t* pTrackSeq, int nSlaveDev)
{
	int nCount = 0;
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = QString("SELECT * FROM [TrackSequence] where SlaveDevId=%1").arg(nSlaveDev);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (m_pQueryClient->next())
		{
			int nTrackNo = m_pQueryClient->value("TrackNo").toInt();
			if (nTrackNo <= 0 || nTrackNo > 30)
				continue;
			TabTrackSequence_t* pSeq = pTrackSeq + nTrackNo;
			pSeq->Id = m_pQueryClient->value("Id").toInt();
			pSeq->SlaveDevId = m_pQueryClient->value("SlaveDevId").toInt();
			pSeq->TrackNo = m_pQueryClient->value("TrackNo").toInt();
			strcpy(pSeq->szTrackDesc, m_pQueryClient->value("TrackDesc").toString().toLatin1().data());
			nCount++;
		}
	}
	return nCount;
}

long long DB::AddTrackSequence(TabTrackSequence_t* pTrackSeq)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = QString("insert into[TrackSequence](SlaveDevId,TrackNo,TrackDesc)values(%1,%2,'%3');")
		.arg(pTrackSeq->SlaveDevId).arg(pTrackSeq->TrackNo).arg(pTrackSeq->szTrackDesc);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::UpdateTrackSequence(TabTrackSequence_t* pTrackSeq)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = QString("update [TrackSequence] set TrackDesc='%1' where Id=%2;")
		.arg(pTrackSeq->szTrackDesc).arg(pTrackSeq->Id);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

long long DB::AddTrackPos(TabTrackPos_t* pTrackPos)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = QString("insert into[TrackPos](TrackSeq,PresetPos,StayTime,PatrolIndex) values(%1,%2,%3,%4);")
		.arg(pTrackPos->TrackSeq).arg(pTrackPos->PresetPos).arg(pTrackPos->StayTime).arg(pTrackPos->PatrolIndex);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::DeleteTrackPos(int nId, int nTrackSeq)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = NULL;
	if (nId == -1)
		strSql = QString("delete  from TrackPos where TrackSeq=%1;").arg(nTrackSeq);
	else
		strSql = QString("delete  from TrackPos where Id=%1;").arg(nId);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::DeleteTrackSequence(int nTrackSeqINo, int nSlaveDev)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = NULL;
	if (nTrackSeqINo == -1)
		strSql = QString("delete  from TrackSequence where SlaveDevId=%1;").arg(nSlaveDev);
	else
		strSql = QString("delete  from TrackSequence where TrackNo=%1 and SlaveDevId=%2;").arg(nTrackSeqINo).arg(nSlaveDev);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::UpdateTrackPos(TabTrackPos_t* pTrackPos)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = QString("update [TrackPos] set PresetPos=%1,StayTime=%2,PatrolIndex=%3 where Id=%4;")
		.arg(pTrackPos->PresetPos).arg(pTrackPos->StayTime).arg(pTrackPos->PatrolIndex).arg(pTrackPos->Id);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

long long DB::AddPresetPos(TabPresetPos_t* pPresetPos)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = QString("insert into[PresetPos](SlaveDevId,PresetNo,PresetDesc) values(%1,%2,'%3');")
		.arg(pPresetPos->SlaveDevId).arg(pPresetPos->PresetNo).arg(pPresetPos->szPresetDesc);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::UpdatePresetPos(TabPresetPos_t* pPresetPos)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = QString("update [PresetPos] set PresetNo=%1,PresetDesc='%2' where Id=%3;")
		.arg(pPresetPos->PresetNo).arg(pPresetPos->szPresetDesc).arg(pPresetPos->Id);
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::QueryAlarmDev(std::list<TabAlarmConf_t *>& lstAlarmConf, int nDevId)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString strSql = NULL;
	if (nDevId == -1)
		strSql = QString("SELECT * FROM [AlarmConf] order by DevId;");
	else
		strSql = QString("SELECT * FROM [AlarmConf] where DevId=%1 order by DevId;").arg(nDevId);

	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (m_pQueryClient->next())
		{
			
			TabAlarmConf_t* pAlarmConf = new TabAlarmConf_t;
			memset(pAlarmConf, '\0', sizeof(TabAlarmConf_t));
			pAlarmConf->Id = m_pQueryClient->value("Id").toInt();
			pAlarmConf->DevId = m_pQueryClient->value("DevId").toInt();
			pAlarmConf->AlarmSource = m_pQueryClient->value("AlarmSource").toInt();
			strcpy(pAlarmConf->szAlarmName, m_pQueryClient->value("AlarmName").toString().toLocal8Bit().data());
			pAlarmConf->AlarmType = m_pQueryClient->value("AlarmType").toInt();
			pAlarmConf->AlarmLevel = m_pQueryClient->value("AlarmLevel").toInt();
			pAlarmConf->Video = m_pQueryClient->value("Video").toInt();
			pAlarmConf->Audio = m_pQueryClient->value("Audio").toInt();
			pAlarmConf->Email = m_pQueryClient->value("Email").toInt();
			pAlarmConf->Emap = m_pQueryClient->value("Emap").toInt();
			pAlarmConf->TVWall = m_pQueryClient->value("TVWall").toInt();
			pAlarmConf->AlarmOut = m_pQueryClient->value("AlarmOut").toInt();
			lstAlarmConf.push_back(pAlarmConf);
			nCount++;
		}
	}
	return nCount;
}

int DB::GetAlarmConf(TabAlarmConf_t* pAlarmConf, int nDevId, int nAlarmSource, int nChannel, int nDevAddr /* = 0 */)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql = QString("SELECT * FROM [AlarmConf] where DevId=%1 and AlarmSource=%2 and Channel=%3;")
		.arg(nDevId).arg(nAlarmSource).arg(nChannel);

	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (m_pQueryClient->next())
		{

			TabAlarmConf_t* pAlarmConf = new TabAlarmConf_t;
			memset(pAlarmConf, '\0', sizeof(TabAlarmConf_t));
			pAlarmConf->Id = m_pQueryClient->value("Id").toInt();
			pAlarmConf->DevId = m_pQueryClient->value("DevId").toInt();
			pAlarmConf->AlarmSource = m_pQueryClient->value("AlarmSource").toInt();
			strcpy(pAlarmConf->szAlarmName, m_pQueryClient->value("AlarmName").toString().toLocal8Bit().data());
			pAlarmConf->AlarmType = m_pQueryClient->value("AlarmType").toInt();
			pAlarmConf->AlarmLevel = m_pQueryClient->value("AlarmLevel").toInt();
			pAlarmConf->Video = m_pQueryClient->value("Video").toInt();
			pAlarmConf->Audio = m_pQueryClient->value("Audio").toInt();
			pAlarmConf->Email = m_pQueryClient->value("Email").toInt();
			pAlarmConf->Emap = m_pQueryClient->value("Emap").toInt();
			pAlarmConf->TVWall = m_pQueryClient->value("TVWall").toInt();
			pAlarmConf->AlarmOut = m_pQueryClient->value("AlarmOut").toInt();
			
			nCount++;
		}
	}
	return nCount;
}

int DB::GetAlarmVideo(TabAlarmVideo_t* pAlarmVideo, int nId)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql = QString("SELECT * FROM [AlarmVideo] where Id=%1;").arg(nId);

	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (m_pQueryClient->next())
		{
			pAlarmVideo->Id = m_pQueryClient->value("Id").toInt();
			pAlarmVideo->PresetPosId = m_pQueryClient->value("PresetPosId").toInt();
			pAlarmVideo->SlaveDevId = m_pQueryClient->value("SlaveDevId").toInt();
			nCount++;
		}
	}
	return nCount;
}

long long DB::AddAlarmLog(TabAlarmLog_t* pAlarmLog)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql = QString("insert into[AlarmLog](AlarmConfId) values(%d);").arg(pAlarmLog->AlarmConfId);


	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}

	return 0;
}

int DB::DeleteAlarmVideo(int nId)
{
	if (nId == -1)
		return -1;
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql = QString("delete  from AlarmVideo where Id=%1;").arg(nId);

	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return 0;
}

int DB::DeleteAlarmAudio(int nId)
{
	if (nId == -1)
		return -1;
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql = QString("delete  from AlarmAudio where Id=%1;;").arg(nId);

	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return 0;
}

int DB::DeleteAlarmConf(int nDevId, int nId)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql;
	if (nId != -1)
	{
		strSql = QString("SELECT * FROM [AlarmVideo] where Id=%1;").arg(nId);
	}
	else
	{
		if (nDevId == -1)
			strSql = QString("delete  from AlarmConf;");
		else
			strSql = QString("delete  from AlarmConf where DevId=%1;").arg(nId);
	}
	

	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}

	return 0;
}

int DB::DeletePresetPos(int nPresetId, int nSlaveDev)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql;
	if (nSlaveDev == -1)
	{
		strSql = QString("delete  from PresetPos where Id=%1;").arg(nPresetId);
	}
	else
	{
		strSql = QString("delete  from PresetPos where SlaveDevId=%1;").arg(nSlaveDev);
	}


	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}

	return 0;
}

int DB::DeleteDevGroupChannle(int nSlaveDev)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql = QString("delete  from DevGroup where SlaveDevId=%1;").arg(nSlaveDev);
	
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return false;
	}

	return 0;
}

int DB::DeleteVideoPatrol(int nId, int SlaveDevId, int nWinIndex)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql;
	if (SlaveDevId != -1)
	{
		strSql = QString("delete  from VideoPatrol where SlaveDevId=%1;").arg(SlaveDevId);
	}
	else if (nId != -1)
	{
		strSql = QString("delete  from VideoPatrol where Id=%1;").arg(nId);
	}
	else if (nWinIndex != -1)
	{
		strSql = QString("delete  from VideoPatrol where WinIndex=%1;").arg(nWinIndex);
	}

	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::deleteChannelInfo(int nDevId)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql = QString("delete from ChannelInfo where DevId=%1;").arg(nDevId);

	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}

	return 0;
}

int DB::GetMainDevID(QString pIP, int nPort)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql = QString("select DevId from DevInfo where IpAddr = '%1' and port = %2;").arg(pIP).arg(nPort);
	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	else
	{
		while (m_pQueryClient->next())
		{
			nCount++;
		}
	}

	return nCount;
}

bool DB::event(QEvent *e)
{
	CompareEvent *event = static_cast<CompareEvent *>(e);

	if (e->type() == static_cast <QEvent::Type>(CET_MESSAGEBOX))
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("打开数据库失败'%1'").arg(dbClient.lastError().text()));

	}
	return QWidget::event(event);
}

int DB::QueryAlarmConfigIsEixst(int nDevId, int nChannel, int nAlarmEventSource)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql;
	if (nDevId == -1)
		return -1;
	else
		strSql = QString("SELECT * FROM [AlarmConf] where DevId=%1 and Channel=%2 and AlarmSource=%3 order by DevId;").arg(nDevId).arg(nChannel).arg(nAlarmEventSource);
	int nCount = 0;
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错'%1'").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	else
	{
		while (m_pQueryClient->next())
		{
			nCount++;
		}
	}
	return nCount;
}

long long DB::UpdateAlarmConf(TabAlarmConf_t* pAlarmConf)
{
	m_pQueryClient = new QSqlQuery(dbClient);
	QString	strSql;
	if (pAlarmConf->Id <= 0)
	{
		strSql = QString("insert into[AlarmConf](DevId,AlarmSource,Channel,AlarmName,AlarmType,AlarmLevel,\
						 Video,Audio,Email,Emap,TVWall, AlarmOut) \
						values(%1,%2,%2,'%4',%5,%6,%7,%8,%9,%10,%11,%12);")
						.arg(pAlarmConf->DevId)
						.arg(pAlarmConf->AlarmSource)
						.arg(pAlarmConf->Channel)
						.arg(pAlarmConf->szAlarmName)
						.arg(pAlarmConf->AlarmType)
						.arg(pAlarmConf->AlarmLevel)
						.arg(pAlarmConf->Video)
						.arg(pAlarmConf->Audio)
						.arg(pAlarmConf->Email)
						.arg(pAlarmConf->Emap)
						.arg(pAlarmConf->TVWall)
						.arg(pAlarmConf->AlarmOut);
	}
	else
	{
		strSql = QString("insert into[AlarmConf](DevId,AlarmSource,Channel,AlarmName,AlarmType,AlarmLevel,\
						  Video,Audio,Email,Emap,TVWall, AlarmOut) \
						  values(%1,%2,%2,'%4',%5,%6,%7,%8,%9,%10,%11,%12);")
						.arg(pAlarmConf->DevId)
						.arg(pAlarmConf->AlarmSource)
						.arg(pAlarmConf->Channel)
						.arg(pAlarmConf->szAlarmName)
						.arg(pAlarmConf->AlarmType)
						.arg(pAlarmConf->AlarmLevel)
						.arg(pAlarmConf->Video)
						.arg(pAlarmConf->Audio)
						.arg(pAlarmConf->Email)
						.arg(pAlarmConf->Emap)
						.arg(pAlarmConf->TVWall)
						.arg(pAlarmConf->AlarmOut);
	}
	bool ret = m_pQueryClient->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错'%1'").arg(m_pQueryClient->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	if (pAlarmConf->Id <= 0)
		return -1;
	else
		return pAlarmConf->Id;
}