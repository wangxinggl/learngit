#include "DB.h"
#include <QDebug>
#include <QSqlError>
#include <qicon.h>
#include <QMessageBox>
#include <QString>
#include <QCoreApplication>
#include <QSqlRecord>
#include "myhelper.h"

QSqlDatabase db1;//A1600Client.db
QSqlDatabase db2;//JVTIAC.db
DB::DB(void)
{
	//createConnection();

}


DB::~DB(void)
{
}

DWORD WINAPI DB::DBClearThread(LPVOID Para)
{
	DB *pDb = (DB*)Para;
	pDb->DBThreadProc();
	return 0;
}

QSqlDatabase DB::getDB()
{
	return db1;
}
void DB::DBThreadProc()
{
	CreateConnectionDB(db1,m_szDBPath);
	CreateConnectionDB(db2,m_szJVTIACDBPath);

}

void DB::CreateConnectionDB(QSqlDatabase& db,QString szDBPath)
{
	if(QSqlDatabase::contains("qt_sql_default_connection"))
		db = QSqlDatabase::database("qt_sql_default_connection");
	else
		db = QSqlDatabase::addDatabase("QSQLITE",szDBPath); //创建一个数据库

	qDebug()<<szDBPath;
	db.setDatabaseName(szDBPath);
	
	if(!db.open())
	{
		qDebug()<<"Open database error"<<db.lastError().text();
		//myHelper::ShowMessageBoxWarning(QObject::tr("打开数据库%1失败%2").arg(szDBPath).arg(db.lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
	}

}
bool DB::CheckUser(QString szName,QString szPassword)
{
	query = new QSqlQuery(db1);
	
	QString strLogin = QString("select * from UserInfo where UserName = '%1' and Password = '%2'").arg(szName).arg(szPassword);
	qDebug()<<strLogin;
	query->exec(strLogin);
	if (!query->first())
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}

int DB::getUserCount()
{
	query = new QSqlQuery(db1);
	int nCount = 0;
	QString strSql = QString("select * from UserInfo");
	bool ret = query->exec(strSql);
	if (!ret)
	{
		
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	while (query->next())
	{
		nCount++;
	}
	return nCount;
}
bool DB::CheckLock(QString szPassword)
{
	query = new QSqlQuery(db1);

	QString strLogin = QString("select * from UserInfo where  Password = '%1'").arg(szPassword);
	query->exec(strLogin);
	if (!query->first())
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}
bool DB::createConnection()
{
	/*
	QSqlDatabase db;
	if(QSqlDatabase::contains("qt_sql_default_connection"))
		db = QSqlDatabase::database("qt_sql_default_connection");
	else
		db = QSqlDatabase::addDatabase("QSQLITE"); //创建一个数据库

	db.setDatabaseName("./DB/A1600Client.db");

	if(!db.open())
	{
		qDebug()<<"Open database error"<<db.lastError().text();
		return false;
		
	}
	return true;*/
	m_nCmpInfoSize = 0;
	m_hThread = NULL;
	m_szDBPath = "./DB/A1600Client.db";
	m_szJVTIACDBPath = "./DB/JVTIAC.db";
	DWORD dwThreadId = 0;
	m_hThread = CreateThread(0, 0, DBClearThread, this, 0, &dwThreadId);
	return true;
}

bool DB::ModifyUser(QString szName,QString szPassword)
{
	query = new QSqlQuery(db1);

	
	QString strLogin = QString("update UserInfo set Password = '%1' where UserName = '%2'")
				.arg(szPassword).arg(szName);
	if (query->first())
	{
		return false;
	}
	query->exec(strLogin);
	return true;
}

bool DB::AddUser(QString szUserName,QString szPassword)
{
	query = new QSqlQuery(db1);
	QString strLogin  = QString("select * from UserInfo where UserName = '%1'").arg(szUserName);
	query->exec(strLogin);
	if (query->first())
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	strLogin = QString("insert into UserInfo values(NULL,'%1','%2')").arg(szUserName).arg(szPassword);
	query->exec(strLogin);
	return true;
}


/*
int DB::getDeviceNum()
{
	query = new QSqlQuery;
	QString strLogin  = QString("select cout(*) from DevInfo DevInfo");
	int ret = query->exec(strLogin);
	return ret;
}

*/
bool DB::AddDevice(QString IP,int Port,QString strName,QString Password,QString dvrname, int Type,int Company,QString DeviceType,int devState,int nSubType)
{
	query = new QSqlQuery(db1);
	QString strDevInfo  = QString("select * from DevInfo where IpAddr = '%1'").arg(IP);
	query->exec(strDevInfo);
	if (query->first())
	{
		return false;
	}

	strDevInfo = QString("insert into DevInfo values(NULL,'%1','%2','%3','%4','%5','%6','%7','%8','%9','%10',NULL)")
				.arg(IP).arg(Port).arg(strName).arg(Password).arg(dvrname).arg(Type).arg(Company).arg(DeviceType).arg(devState).arg(nSubType);
	bool ret = query->exec(strDevInfo);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}

bool DB::ChangeDevice(QString IP,int Port,QString strName,QString Password,QString dvrname,int Company,QString DeviceType,int devState,int nSubType)
{
	query = new QSqlQuery(db1);
	QString strDevInfo = QString("update DevInfo set IpAddr ='%1',Port = '%2',LoginName = '%3',Password='%4',DevName = '%5',Manufacturer = '%6',DevType = '%7',DevStatus = '%8',SubDevType = '%9' where IpAddr = '%10'")
		.arg(IP).arg(Port).arg(strName).arg(Password).arg(dvrname).arg(Company).arg(DeviceType).arg(devState).arg(nSubType).arg(IP);
	bool ret = query->exec(strDevInfo);
	if (!ret)
	{

		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}
bool DB::addChannelInfo(int Devid,int DeviceNum,QString channelName,int nSubType,int state)
{
	query = new QSqlQuery(db1);
	QString strDevInfo  = QString("insert into ChannelInfo values(NULL,'%1','%2','%3','%4','%5')").arg(Devid).arg(DeviceNum).arg(channelName).arg(nSubType).arg(state);
	bool ret = query->exec(strDevInfo);
	if (!ret)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		return false;
	}
	return true;
}
bool DB::delAllDevInfo()
{
	query = new QSqlQuery(db1);
	QString strSql = QString("delete from ChannelInfo");
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		strSql = QString("delete from DevInfo");
		bool ret = query->exec(strSql);
		if (!ret)
		{
			//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
			mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
			return false;
		}
	}
	return true;
}

int DB::getDeviceID(QString strIP)
{
	int devid = 0;
	query = new QSqlQuery(db1);
	QString strSql = QString("select * from DevInfo where IpAddr = '%1'").arg(strIP);
	bool ret  = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	while(query->next())
	{
		devid =  query->value("DevId").toInt();
	}
	return devid;
}

bool DB::DelAllDevice(int DeviceId)
{
	query = new QSqlQuery(db1);

	QString	strDel = QString("delete from ChannelInfo where DevId = '%1'").arg(DeviceId);
		bool ret = query->exec(strDel);
		if (!ret)
		{
			//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
			mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
			return false;
		}
		else
		{
			strDel = QString("delete from DevInfo where DevId = '%1'").arg(DeviceId);
			ret = query->exec(strDel);
			if (!ret)
			{
				//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
				mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
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
	query = new QSqlQuery(db1);
	QString querySql = QString("select IpAddr,Type,DevType from DevInfo");
	bool isOk = query->exec(querySql);
	if(!isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	while(query->next())
	{
		treeNode data;
		
		QString IpAddr = query->value("IpAddr").toString();
		int Type = query->value("Type").toInt();
		QString DevType = query->value("DevType").toString();

		
		data.IpAddr = IpAddr;
		data.Type = Type;
		data.DevType = DevType;
		vTreeNodes.push_back(data);
	}
	return true;
}

bool DB::queryChildNodesById(int id,vector<treeNode> &vNodesID)
{
	query = new QSqlQuery(db1);
	QString querySql = QString("select IpAddr,Type,DevType from DevInfo where Type = '%1'").arg(id);
	bool isOk = query->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}

	while(query->next())
	{
		treeNode data;
	
		QString IpAddr = query->value("IpAddr").toString();
		int Type = query->value("Type").toInt();
		QString DevType = query->value("DevType").toString();

		data.IpAddr = IpAddr;
		data.Type = Type;
		data.DevType = DevType;
		vNodesID.push_back(data);
	}
	return true;
}

bool DB::getAllTreeMessage(vector<TabDevInfo_t> &vTreeMessage)
{
	query = new QSqlQuery(db1);
	QString querySql = QString("select * from DevInfo");
	bool isOk = query->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}

	while(query->next())
	{
		TabDevInfo_t data;
		int devId = query->value("DevId").toInt();
		QString szIpAddr = query->value("IpAddr").toString();
		int nPort = query->value("Port").toInt();
		QString szLoginName = query->value("LoginName").toString();
		QString szPassword = query->value("Password").toString();
		QString szDevName = query->value("DevName").toString();
	    int nType = query->value("Type").toInt();
		int nManufaceturer = query->value("Manufacturer").toInt();
		QString szDevType = query->value("DevType").toString();
		int nDevStatus = query->value("DevStatus").toInt();
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

int DB::QueryAllMainDev(std::vector<TabDevInfo_t *>& lstDevice)
{
	int nCount = 0;
	query = new QSqlQuery(db1);
	QString querySql = QString("select * from DevInfo");
	bool isOk = query->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -1;
	}

	while(query->next())
	{
		TabDevInfo_t *data = new TabDevInfo_t;
		data->nDevId = query->value("DevId").toInt();
		strcpy(data->szIpAddr,query->value("IpAddr").toString().toLatin1().data());
		data->nPort = query->value("Port").toInt();
		strcpy(data->szLoginName,query->value("LoginName").toString().toLocal8Bit().data());
		strcpy(data->szPassword,query->value("Password").toString().toLatin1().data());
		strcpy(data->szDevName ,query->value("DevName").toString().toLocal8Bit().data());
		data->nType = query->value("Type").toInt();
		data->nManufacturer = query->value("Manufacturer").toInt();
		strcpy(data->szDevType , query->value("DevType").toString().toLatin1().data());
		data->nDevStatus = query->value("DevStatus").toInt();
		data->nSubDevType = query->value("SubDevType").toInt();
		//QString szUUID = query->value("UUID").toString();

		
		//data.szUUID = szUUID;
		lstDevice.push_back(data);
		nCount ++;
	}
	return nCount;
}

int DB::QueryAllSlaveDev(std::vector<TabChannelInfo_t *>& lstChannelInfo,int nDevId /* = -1 */)
{
	query = new QSqlQuery(db1);
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

	bool isOk = query->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	while(query->next())
	{
		TabChannelInfo_t *channelData =new TabChannelInfo_t;
		channelData->SlaveDevId = query->value("SlaveDevId").toInt();
		channelData->DevId = query->value("DevId").toInt();
		channelData->Channel = query->value("Channel").toInt();
		strcpy(channelData->szChannelName ,query->value("ChannelName").toString().toLatin1().data());
		channelData->Type = query->value("Type").toInt();
		channelData->Status = query->value("Status").toInt();

		lstChannelInfo.push_back(channelData);
		nCount++;
	}
	return nCount;
}

int DB::QueryAllDevGroup(std::list<TabUserDevGroup_t *>& lstDevGroup)
{
	int nCount = 0;
	query = new QSqlQuery(db1);
	QString querySql = QString("select * from UserDevGroup");
	bool isOk = query->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	while(query->next())
	{
		TabUserDevGroup_t *DevGroup =new TabUserDevGroup_t;
		DevGroup->Id = query->value("Id").toInt();
		strcpy(DevGroup->szGroupName ,query->value("GroupName").toString().toLatin1().data());
		DevGroup->ParentId = query->value("ParentId").toInt();
		lstDevGroup.push_back(DevGroup);
		nCount ++;
	}
	return nCount;
}

int DB::QueryAllGroupChannel(std::vector<TabDevGroup_t *>& lstGroupChannel)
{
	int nCount = 0;
	query = new QSqlQuery(db1);
	QString querySql = QString("select * from DevGroup");
	bool isOk = query->exec(querySql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	while(query->next())
	{
		TabDevGroup_t *DevGroup = new TabDevGroup_t;
		DevGroup->Id = query->value("Id").toInt();
		DevGroup->GroupId = query->value("GroupId").toInt();
		DevGroup->SlaveDevId = query->value("SlaveDevId").toInt();
		lstGroupChannel.push_back(DevGroup);
	}
	return nCount;
}

bool DB::changeFilePath(QString picPath,QString videoPath,QString DownPath,QString snapPath)
{
	query = new QSqlQuery(db1);
	QString strSql = QString("update CommonCfg set PicPath = '%1',VideoPath = '%2',DownPath = '%3',SnapPath = '%4' where Id = 1")
		.arg(picPath).arg(videoPath).arg(DownPath).arg(snapPath);

	bool isOk = query->exec(strSql);
	if(false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return true;
}

bool DB::getFilePath(QString &picPath,QString &DownPath,QString &snapPath)
{
	query = new QSqlQuery(db1);
	QString strSql = QString("select * from CommonCfg where Id = 1");
	bool isOk = query->exec(strSql);
	if (false == isOk)
	{
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (query->next())
		{
			picPath = query->value("PicPath").toString();
			DownPath = query->value("DownPath").toString();
			snapPath = query->value("SnapPath").toString();
		}
	}
	return true;
}


bool DB::checkDevice(QString nIP,int port,QString UUID)
{
	query = new QSqlQuery(db1);
	QString strCheck = QString("select DevId from DevInfo where IpAddr = '%1' and port = '%2' and UUID = '%3';").arg(nIP).arg(port).arg(UUID);
	query->exec(strCheck);
	if (!query->first())
	{
		return false;
	}
	return true;
}

int DB::QueryAllDeviceMsg(std::vector<DevInfo *>& listDev,QString IpAddr)
{
	int nCount = 0;
	query = new QSqlQuery(db1);
	QString querySql = QString("select * from DevInfo where IpAddr = '%1'").arg(IpAddr);
	bool isOk = query->exec(querySql);
	if(false == isOk)
	{
		qDebug()<<"sql select * from DevGroup error";
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -1;
	}
	while(query->next())
	{
		DevInfo *DevGroup = new DevInfo	;
		DevGroup->DevId = query->value("DevId").toInt();
		DevGroup->IpAddr = query->value("IpAddr").toString();
		DevGroup->port = query->value("Port").toInt();
		DevGroup->szName = query->value("LoginName").toString();
		DevGroup->szPassWord = query->value("Password").toString();
		DevGroup->devName = query->value("DevName").toString();
		DevGroup->Type = query->value("Type").toInt();
		DevGroup->manfacturer = query->value("Manufacturer").toInt();
		DevGroup->DevType = query->value("DevType").toInt();
		DevGroup->DevStatus = query->value("DevStatus").toInt();
		DevGroup->SubType = query->value("SubDevType").toInt();
		DevGroup->UUID = query->value("UUID").toString();
		listDev.push_back(DevGroup);
	}
	return 0;
}


int DB::GetCmpFindInfo(FS_FIND_INFO *find_info, std::vector<SMART_FACE_CMP_QUERY_INFO *>& vectorCompare)
{
	int offsetnum;
	int nCount = 0;
	char chTemp[256] = {0};
	std::string strIP;
	char chIP[32] = {0};
	char temp[5]="%";

	std::string strName;

	if (find_info->nDevNumber > 0)
	{
		sprintf(chTemp, "(DeviceIP = ");
		strIP = chTemp;
		memset(&chTemp, 0, sizeof(chTemp));
		for (int i = 0; i < find_info->nDevNumber; i ++)
		{
			strIP.append(chTemp);
			memset(&chIP, 0, sizeof(chIP));
			sprintf(chIP, "'%s'", find_info->fsDevInfo[i].cDeviceIP);
			strIP.append(chIP);
			sprintf(chTemp, "%s", " or DeviceIP = ");
		}
		strIP.append(")");
	}
	QString strSql=NULL;
	qDebug()<<find_info->IpAddr;
	switch(find_info->cmd)
	{
	case CONDITION_EIG:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and '%3';").arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime))).arg(QString(QLatin1String(find_info->IpAddr)));
		break;
	case CONDITION_NINE:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and '%3'  and userId = '%4';")
			.arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime))).arg(QString(QLatin1String(find_info->IpAddr))).arg(QString(QLatin1String(find_info->number)));
		break;
	case CONDITION_TEN:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and '%3' and name like '%4';")
			.arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime))).arg(QString(QLatin1String(find_info->IpAddr))).arg(QString::fromLocal8Bit(find_info->name));
		break;
	case CONDITION_ELEVEN:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and name like '%3' and userId = '%4' and %5 ;;")
			.arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime))).arg(QString::fromLocal8Bit(find_info->name)).arg(QString(QLatin1String(find_info->number))).arg(QString(QLatin1String(find_info->IpAddr)));
		break;
	case  CONDITION_TWELVE:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and '%3' and face_mode = '%4';")
			.arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime))).arg(QString(QLatin1String(find_info->IpAddr))).arg(find_info->Wbmode);
		break;
	case CONDITION_THIRTEEN:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2'  and userId = '%3' and face_mode = '%4' and '%5';")
			.arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime))).arg(QString(QLatin1String(find_info->number)))
			.arg(find_info->Wbmode).arg(QString(QLatin1String(find_info->IpAddr)));
		break;
	case CONDITION_FOURTEEN:
		strSql = QString("SELECT * FROM %s where time>='%1' and time <='%2' and name like '%3' and face_mode = '%7' and '%8' ;")
			.arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime))).arg(QString(QLatin1String(find_info->name)))
			.arg(find_info->Wbmode).arg(QString(QLatin1String(find_info->IpAddr)));
		break;
	case CONDITION_FIFTEEN:
		strSql = QString("SELECT * FROM %s where time>='%1' and time <='%2' and name like '%3' and face_mode = '%4' and '%5';")
			.arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime))).arg(QString(QLatin1String(find_info->name)))
			.arg(QString(QLatin1String(find_info->number))).arg(find_info->Wbmode).arg(QString(QLatin1String(find_info->IpAddr)));
		break;

	default:
		return 0;
		break;

	}

	qDebug()<<strSql;
	query = new QSqlQuery(db2);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		qDebug()<<query->lastError().text();
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	while(query->next())
	{
		SMART_FACE_CMP_QUERY_INFO* pCompareInfo = new SMART_FACE_CMP_QUERY_INFO;
		memset(pCompareInfo, 0, sizeof(SMART_FACE_CMP_QUERY_INFO));
		pCompareInfo->sLibSimilarity = query->value("Similarity").toFloat();
		pCompareInfo->sLibMode = query->value("face_mode").toInt();
		pCompareInfo->sLibRowid = query->value("libindex").toInt();
		pCompareInfo->nLibGuest = query->value("guest").toInt();
		pCompareInfo->cLibGender = query->value("sex").toInt();
		pCompareInfo->cLibAge = query->value("age").toInt();
		pCompareInfo->cLibGlasses = query->value("glasses").toInt();
		pCompareInfo->cLibEye = query->value("eye").toInt();
		pCompareInfo->cLibMask = query->value("mask").toInt();
		pCompareInfo->cLibRace = query->value("race").toInt();
		pCompareInfo->cLibAttractive = query->value("charm").toInt();
		strcpy((char *)pCompareInfo->sLibSnapTime, query->value("time").toString().toLatin1().data());
		strcpy((char *)pCompareInfo->sSnappicname,query->value("SnapName").toString().toLatin1().data());
		pCompareInfo->cLibBeard = query->value("Beard").toInt();
		pCompareInfo->cLibEmotion = query->value("Emotion").toInt();
		pCompareInfo->sLibChannelid= query->value("channelId").toInt();
		strcpy((char *)pCompareInfo->cDeviceIP,  query->value("DeviceIP").toString().toLatin1().data());
		strcpy((char *)pCompareInfo->sLibPicName,  query->value("libName").toString().toLocal8Bit().data());
		strcpy((char *)pCompareInfo->cPath,  query->value("path").toString().toLatin1().data());
		strcpy((char *)pCompareInfo->sUserID,  query->value("userId").toString().toLatin1().data());
		strcpy((char *)pCompareInfo->sName,  query->value("name").toString().toLocal8Bit().data());
	
		pCompareInfo->sSysListID = query->value("sysListId").toInt();
		vectorCompare.push_back(pCompareInfo);
		nCount ++;
	}
	return nCount;
}

int DB::QueryComparison(FS_FIND_INFO *find_info,  std::vector<SMART_FACE_CMP_QUERY_INFO *>& vectorCompare)
{
	int nFindRow = 0;
	char str1[256] = {0};
	char chIP[32] = {0};
	std::string strIP;
	int offsetnum;
	int ret = 0;
	char temp[5]="%";
	int nCount = 0;
	if(find_info->flag == FLAG_SEARCH_FIRST || find_info->flag == FLAG_SEARCH_EXPORT)
	{
		nFindRow = GetCmpFindInfo(find_info, vectorCompare);
		m_nCmpInfoSize = nFindRow;
		find_info->curpage = 1;
		if(find_info->flag == FLAG_SEARCH_EXPORT || nFindRow <= 0)
		{
			return nFindRow;
		}
	}

	if (find_info->nDevNumber > 0)
	{
		sprintf(str1, "(DeviceIP = ");
		strIP = str1;
		memset(&str1, 0, sizeof(str1));
		for (int i = 0; i < find_info->nDevNumber; i ++)
		{
			strIP.append(str1);
			memset(&chIP, 0, sizeof(chIP));
			sprintf(chIP, "'%s'", find_info->fsDevInfo[i].cDeviceIP);
			strIP.append(chIP);
			sprintf(str1, "%s", " or DeviceIP = ");
		}
		strIP.append(")");
	}
	offsetnum = m_nCmpInfoSize - find_info->curpage * find_info->pagecount;
	if(offsetnum < 0)
	{
		offsetnum=0;
	}

	QString strSql=NULL;
	switch(find_info->cmd)
	{
	case CONDITION_EIG:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and '%3'  limit '%4' offset '%5';").arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime)))
			.arg(QString(QLatin1String(find_info->IpAddr))).arg(find_info->pagecount).arg(offsetnum);
		break;
	case CONDITION_NINE:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and userId = '%3'and '%4'  limit '%5' offset '%6' ;").arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime)))
			.arg(QString(QLatin1String(find_info->number))).arg(QString(QLatin1String(find_info->IpAddr))).arg(find_info->pagecount).arg(offsetnum);
		break;
	case CONDITION_TEN:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and name like '%3'and '%4'  limit '%5' offset '%6'").arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime)))
			.arg(QString::fromLocal8Bit(find_info->name)).arg(QString(QLatin1String(find_info->IpAddr))).arg(find_info->pagecount).arg(offsetnum);
		break;
	case CONDITION_ELEVEN:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and libName like '%3' and '%4'  limit '%5' offset '%6'").arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime)))
			.arg(QString::fromLocal8Bit(find_info->name)).arg(QString(QLatin1String(find_info->number))).arg(QString(QLatin1String(find_info->IpAddr))).arg(find_info->pagecount).arg(offsetnum);
		break;
	case CONDITION_TWELVE:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and face_mode = '%3'  and '%4'  limit '%5' offset '%6';").arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime)))
			.arg(find_info->Wbmode).arg(QString(QLatin1String(find_info->IpAddr))).arg(find_info->pagecount).arg(offsetnum);
		break;
	case CONDITION_THIRTEEN:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and userId = '%3' and face_mode = '%4' and '%5'  limit '%6' offset '%7' ;").arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime)))
			.arg(QString(QLatin1String(find_info->number))).arg(find_info->Wbmode).arg(QString(QLatin1String(find_info->IpAddr))).arg(find_info->pagecount).arg(offsetnum);
		break;
	case CONDITION_FOURTEEN:
		strSql = QString("SELECT * FROM CmpInfoList where time>='%1' and time <='%2' and name like '%3' and face_mode = '%4' and '%5'  limit '%6' offset '%7';").arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime)))
			.arg(QString::fromLocal8Bit(find_info->name)).arg(find_info->Wbmode).arg(QString(QLatin1String(find_info->IpAddr))).arg(find_info->pagecount).arg(offsetnum);
		break;
	case CONDITION_FIFTEEN:
		strSql = QString("SELECT * FROM %s where time>='%1' and time <='%2' and name like '%3' and userId = '%4' and face_mode = '%5' and '%6'  limit '%7' offset '%8' ;").arg(QString(QLatin1String(find_info->StartTime))).arg(QString(QLatin1String(find_info->EndTime)))
			.arg(QString::fromLocal8Bit(find_info->name)).arg(QString(QLatin1String(find_info->number))).arg(find_info->Wbmode)
			.arg(QString(QLatin1String(find_info->IpAddr))).arg(find_info->pagecount).arg(offsetnum);
		break;
	default:
		//FaceCmpkPrintf("error  !!!!!!!!!!!!!!!!!!!!!!\n");
		return ret;

	}
	query = new QSqlQuery(db2);
	bool retResult = query->exec(strSql);
	if (!retResult)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (query->next())
		{
			SMART_FACE_CMP_QUERY_INFO* pCompareInfo = new SMART_FACE_CMP_QUERY_INFO;
			memset(pCompareInfo, 0, sizeof(SMART_FACE_CMP_QUERY_INFO));

			pCompareInfo->sLibSimilarity = query->value("Similarity").toFloat();
			pCompareInfo->sLibMode = query->value("face_mod").toInt();
			pCompareInfo->sLibRowid = query->value("libindex").toInt();
			pCompareInfo->nLibGuest = query->value("guest").toInt();
			pCompareInfo->cLibGender = query->value("sex").toInt();
			pCompareInfo->cLibAge = query->value("age").toInt();
			pCompareInfo->cLibGlasses = query->value("glasses").toInt();
			pCompareInfo->cLibEye = query->value("eye").toInt();
			pCompareInfo->cLibMask = query->value("mask").toInt();
			pCompareInfo->cLibRace = query->value("race").toInt();
			pCompareInfo->cLibAttractive = query->value("charm").toInt();
			strcpy((char *)pCompareInfo->sLibSnapTime, query->value("time").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sSnappicname,query->value("SnapName").toString().toLatin1().data());
			pCompareInfo->cLibBeard = query->value("Beard").toInt();
			pCompareInfo->cLibEmotion = query->value("Emotion").toInt();
			pCompareInfo->sLibChannelid= query->value("channelId").toInt();
			strcpy((char *)pCompareInfo->cDeviceIP,  query->value("DeviceIP").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sLibPicName,  query->value("libName").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->cPath,  query->value("path").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sUserID,  query->value("userId").toString().toLatin1().data());
			strcpy((char *)pCompareInfo->sName,  query->value("name").toString().toLocal8Bit().data());
			pCompareInfo->sSysListID = query->value("sysListId").toInt();
			vectorCompare.push_back(pCompareInfo);

		}
	}
	
	return m_nCmpInfoSize;
}

bool DB::AddCMPInfo(SMART_FACE_CMP_QUERY_INFO* pCompareInfo)
{	
	query = new QSqlQuery(db2);
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
	QString strSql=QString("INSERT INTO CmpInfoList VALUES('%1','%2', '%3','%4','%5','%6', '%7','%8','%9','%10','%11','%12', '%13','%14','%15','%16', '%17', '%18', '%19', '%20', '%21', '%22', '%23', %24);")
		.arg(pCompareInfo->sLibSimilarity).arg(pCompareInfo->sLibMode).arg(pCompareInfo->sLibRowid).arg(pCompareInfo->sLibRowid).arg(pCompareInfo->nLibGuest).arg((int)(pCompareInfo->cLibGender)).arg((int)(pCompareInfo->cLibAge))
		.arg((int)pCompareInfo->cLibGlasses).arg((int)pCompareInfo->cLibEye).arg((int)pCompareInfo->cLibMask).arg((int)pCompareInfo->cLibRace).arg((int)pCompareInfo->cLibAttractive).arg(QString(QLatin1String(pCompareInfo->sLibSnapTime))).arg(QString::fromLocal8Bit(pCompareInfo->sLibPicName))
		.arg(QString(QLatin1String(pCompareInfo->sSnappicname))).arg((int)pCompareInfo->cLibBeard).arg((int)pCompareInfo->cLibEmotion).arg(0).arg(pCompareInfo->sLibChannelid).arg(QString(QLatin1String(pCompareInfo->cDeviceIP))).arg(QString(QLatin1String(pCompareInfo->cPath))).arg(QString::fromLocal8Bit(pCompareInfo->sName))
		.arg(QString(QLatin1String(pCompareInfo->sUserID))).arg(pCompareInfo->sSysListID);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
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
	query = new QSqlQuery(db1);
	QString strSql = QString("SELECT * FROM AlarmLog where BeginTime > '%1'and BeginTime < '%2'").arg(pBeginTime).arg(pEndTime);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return 0;
	}
	while(query->next())
	{
		TabAlarmLog_t* pAlarmLog = new TabAlarmLog_t;
		memset(pAlarmLog, 0, sizeof(TabAlarmLog_t));
		pAlarmLog->Id = query->value("Id").toInt();
		pAlarmLog->AlarmConfId = query->value("AlarmConfId").toInt();
		strcpy((char *)pAlarmLog->szBeginTime, query->value("BeginTime").toString().toLatin1().data());
		strcpy((char *)pAlarmLog->szEndTime, query->value("EndTime").toString().toLatin1().data());
		lstAlarmLog.push_back(pAlarmLog);
		ncount ++;
	}
	return ncount;
}

int DB::getAlarmConfMsg(int nAlarmConfId, int& devId, int &alarmSrc, int& channel, int &alarmType, int &alarmLevel)
{

	query = new QSqlQuery(db1);
	QString strSql  =  QString("select c.DevId,c.AlarmName, c.AlarmSource, c.Channel, c.AlarmType ,c.AlarmLevel,c.Video from  AlarmConf as c  left join AlarmLog as l on l.AlarmConfId = c.Id where  l.AlarmConfId = '%1';").arg(nAlarmConfId);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return 0;
	}
	else
	{
		while(query->next())
		{
			devId = query->value("DevId").toInt();
			alarmSrc = query->value("AlarmSource").toInt();
			channel = query->value("Channel").toInt();
			alarmType = query->value("AlarmType").toInt();
			alarmLevel = query->value("AlarmLevel").toInt();
		}
		QSqlRecord sqlRecord = query->record();
		return sqlRecord.count();

	}
	
}

int DB::getDevInfo(int devId, QString& szDevName)
{
	int nCount = 0;
	query = new QSqlQuery(db1);
	QString strSql = QString("select * from DevInfo where DevId = '%1';").arg(devId);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return 0;
	}
	else
	{
		while (query->next())
		{
			szDevName = query->value("IpAddr").toString();
			nCount++;
		}
	}
	return nCount;
}

bool DB::QueryDevInfo(std::vector<DevInfo>&  lstDevInfo)
{
	query = new QSqlQuery(db1);
	QString strSql = QString("select * from DevInfo ;");
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (query->next())
		{
			DevInfo m_DevInfo;
			m_DevInfo.DevId = query->value("DevId").toInt();
			m_DevInfo.IpAddr = query->value("IpAddr").toString();
			m_DevInfo.port = query->value("Port").toInt();
			m_DevInfo.szName = query->value("LoginName").toString();
			m_DevInfo.szPassWord = query->value("Password").toString();
			m_DevInfo.devName = query->value("DevName").toString();
			m_DevInfo.Type = query->value("Type").toInt();
			m_DevInfo.manfacturer = query->value("Manufacturer").toInt();
			m_DevInfo.DevType = query->value("DevType").toString();
			m_DevInfo.DevStatus = query->value("DevStatus").toInt();
			m_DevInfo.SubType = query->value("SubDevType").toInt();
			m_DevInfo.UUID = query->value("UUID").toString();
			lstDevInfo.push_back(m_DevInfo);
		}
	}
	return true;
}

int DB::SetCommonCfg(TabCommonCfg_t* pClientCfg)
{
	query = new QSqlQuery(db1);
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
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::DeleteAlarmLog(int nId, bool bDeleteAll /* = false */)
{
	query = new QSqlQuery(db1);
	QString strSql = NULL;
	if (bDeleteAll)
		strSql = QString("delete  from AlarmLog ;");
	else
		strSql = QString("delete  from AlarmLog where Id=%1;").arg(nId);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;

}

int DB::QueryPrestPos(TabPresetPos_t* pPresetPos, int nSlaveDev, int nPresetPosId /* = -1 */)
{
	query = new QSqlQuery(db1);
	QString strSql = NULL;
	if (nPresetPosId == -1)
		strSql = QString("SELECT * FROM [PresetPos] where SlaveDevId=%1;").arg(nSlaveDev);
	else
		strSql = QString("SELECT * FROM [PresetPos] where id=%1;").arg(nPresetPosId);
	int nCount = 0;
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	else
	{
		while (query->next())
		{
			int nPresetNo = query->value("PresetNo").toInt();
			if (nPresetNo <= 0 || nPresetNo > 256)
				continue;
			TabPresetPos_t *pPos = pPresetPos + nPresetNo;
			pPos->Id = query->value("Id").toInt();
			pPos->SlaveDevId = query->value("SlaveDevId").toInt();
			pPos->PresetNo = query->value("PresetNo").toInt();
			strcpy(pPos->szPresetDesc, query->value("PresetDesc").toString().toLatin1().data());
			nCount++;
		}
	}

	return nCount;
}

int DB::QueryTrackSequence(TabTrackSequence_t* pTrackSeq, int nSlaveDev)
{
	int nCount = 0;
	query = new QSqlQuery(db1);
	QString strSql = QString("SELECT * FROM [TrackSequence] where SlaveDevId=%1").arg(nSlaveDev);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (query->next())
		{
			int nTrackNo = query->value("TrackNo").toInt();
			if (nTrackNo <= 0 || nTrackNo > 30)
				continue;
			TabTrackSequence_t* pSeq = pTrackSeq + nTrackNo;
			pSeq->Id = query->value("Id").toInt();
			pSeq->SlaveDevId = query->value("SlaveDevId").toInt();
			pSeq->TrackNo = query->value("TrackNo").toInt();
			strcpy(pSeq->szTrackDesc, query->value("TrackDesc").toString().toLatin1().data());
			nCount++;
		}
	}
	return nCount;
}

long long DB::AddTrackSequence(TabTrackSequence_t* pTrackSeq)
{
	query = new QSqlQuery(db1);
	QString strSql = QString("insert into[TrackSequence](SlaveDevId,TrackNo,TrackDesc)values(%1,%2,'%3');")
		.arg(pTrackSeq->SlaveDevId).arg(pTrackSeq->TrackNo).arg(pTrackSeq->szTrackDesc);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::UpdateTrackSequence(TabTrackSequence_t* pTrackSeq)
{
	query = new QSqlQuery(db1);
	QString strSql = QString("update [TrackSequence] set TrackDesc='%1' where Id=%2;")
		.arg(pTrackSeq->szTrackDesc).arg(pTrackSeq->Id);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

long long DB::AddTrackPos(TabTrackPos_t* pTrackPos)
{
	query = new QSqlQuery(db1);
	QString strSql = QString("insert into[TrackPos](TrackSeq,PresetPos,StayTime,PatrolIndex) values(%1,%2,%3,%4);")
		.arg(pTrackPos->TrackSeq).arg(pTrackPos->PresetPos).arg(pTrackPos->StayTime).arg(pTrackPos->PatrolIndex);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::DeleteTrackPos(int nId, int nTrackSeq)
{
	query = new QSqlQuery(db1);
	QString strSql = NULL;
	if (nId == -1)
		strSql = QString("delete  from TrackPos where TrackSeq=%1;").arg(nTrackSeq);
	else
		strSql = QString("delete  from TrackPos where Id=%1;").arg(nId);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::DeleteTrackSequence(int nTrackSeqINo, int nSlaveDev)
{
	query = new QSqlQuery(db1);
	QString strSql = NULL;
	if (nTrackSeqINo == -1)
		strSql = QString("delete  from TrackSequence where SlaveDevId=%1;").arg(nSlaveDev);
	else
		strSql = QString("delete  from TrackSequence where TrackNo=%1 and SlaveDevId=%2;").arg(nTrackSeqINo).arg(nSlaveDev);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::UpdateTrackPos(TabTrackPos_t* pTrackPos)
{
	query = new QSqlQuery(db1);
	QString strSql = QString("update [TrackPos] set PresetPos=%1,StayTime=%2,PatrolIndex=%3 where Id=%4;")
		.arg(pTrackPos->PresetPos).arg(pTrackPos->StayTime).arg(pTrackPos->PatrolIndex).arg(pTrackPos->Id);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

long long DB::AddPresetPos(TabPresetPos_t* pPresetPos)
{
	query = new QSqlQuery(db1);
	QString strSql = QString("insert into[PresetPos](SlaveDevId,PresetNo,PresetDesc) values(%1,%2,'%3');")
		.arg(pPresetPos->SlaveDevId).arg(pPresetPos->PresetNo).arg(pPresetPos->szPresetDesc);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::UpdatePresetPos(TabPresetPos_t* pPresetPos)
{
	query = new QSqlQuery(db1);
	QString strSql = QString("update [PresetPos] set PresetNo=%1,PresetDesc='%2' where Id=%3;")
		.arg(pPresetPos->PresetNo).arg(pPresetPos->szPresetDesc).arg(pPresetPos->Id);
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::QueryAlarmDev(std::list<TabAlarmConf_t *>& lstAlarmConf, int nDevId)
{
	query = new QSqlQuery(db1);
	QString strSql = NULL;
	if (nDevId == -1)
		strSql = QString("SELECT * FROM [AlarmConf] order by DevId;");
	else
		strSql = QString("SELECT * FROM [AlarmConf] where DevId=%1 order by DevId;").arg(nDevId);

	int nCount = 0;
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (query->next())
		{
			
			TabAlarmConf_t* pAlarmConf = new TabAlarmConf_t;
			memset(pAlarmConf, '\0', sizeof(TabAlarmConf_t));
			pAlarmConf->Id = query->value("Id").toInt();
			pAlarmConf->DevId = query->value("DevId").toInt();
			pAlarmConf->AlarmSource = query->value("AlarmSource").toInt();
			strcpy(pAlarmConf->szAlarmName, query->value("AlarmName").toString().toLocal8Bit().data());
			pAlarmConf->AlarmType = query->value("AlarmType").toInt();
			pAlarmConf->AlarmLevel = query->value("AlarmLevel").toInt();
			pAlarmConf->Video = query->value("Video").toInt();
			pAlarmConf->Audio = query->value("Audio").toInt();
			pAlarmConf->Email = query->value("Email").toInt();
			pAlarmConf->Emap = query->value("Emap").toInt();
			pAlarmConf->TVWall = query->value("TVWall").toInt();
			pAlarmConf->AlarmOut = query->value("AlarmOut").toInt();
			lstAlarmConf.push_back(pAlarmConf);
			nCount++;
		}
	}
	return nCount;
}

int DB::GetAlarmConf(TabAlarmConf_t* pAlarmConf, int nDevId, int nAlarmSource, int nChannel, int nDevAddr /* = 0 */)
{
	query = new QSqlQuery(db1);
	QString	strSql = QString("SELECT * FROM [AlarmConf] where DevId=%1 and AlarmSource=%2 and Channel=%3;")
		.arg(nDevId).arg(nAlarmSource).arg(nChannel);

	int nCount = 0;
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (query->next())
		{

			TabAlarmConf_t* pAlarmConf = new TabAlarmConf_t;
			memset(pAlarmConf, '\0', sizeof(TabAlarmConf_t));
			pAlarmConf->Id = query->value("Id").toInt();
			pAlarmConf->DevId = query->value("DevId").toInt();
			pAlarmConf->AlarmSource = query->value("AlarmSource").toInt();
			strcpy(pAlarmConf->szAlarmName, query->value("AlarmName").toString().toLocal8Bit().data());
			pAlarmConf->AlarmType = query->value("AlarmType").toInt();
			pAlarmConf->AlarmLevel = query->value("AlarmLevel").toInt();
			pAlarmConf->Video = query->value("Video").toInt();
			pAlarmConf->Audio = query->value("Audio").toInt();
			pAlarmConf->Email = query->value("Email").toInt();
			pAlarmConf->Emap = query->value("Emap").toInt();
			pAlarmConf->TVWall = query->value("TVWall").toInt();
			pAlarmConf->AlarmOut = query->value("AlarmOut").toInt();
			
			nCount++;
		}
	}
	return nCount;
}

int DB::GetAlarmVideo(TabAlarmVideo_t* pAlarmVideo, int nId)
{
	query = new QSqlQuery(db1);
	QString	strSql = QString("SELECT * FROM [AlarmVideo] where Id=%1;").arg(nId);

	int nCount = 0;
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	else
	{
		while (query->next())
		{
			pAlarmVideo->Id = query->value("Id").toInt();
			pAlarmVideo->PresetPosId = query->value("PresetPosId").toInt();
			pAlarmVideo->SlaveDevId = query->value("SlaveDevId").toInt();
			nCount++;
		}
	}
	return nCount;
}

long long DB::AddAlarmLog(TabAlarmLog_t* pAlarmLog)
{
	query = new QSqlQuery(db1);
	QString	strSql = QString("insert into[AlarmLog](AlarmConfId) values(%d);").arg(pAlarmLog->AlarmConfId);


	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}

	return 0;
}

int DB::DeleteAlarmVideo(int nId)
{
	if (nId == -1)
		return -1;
	query = new QSqlQuery(db1);
	QString	strSql = QString("delete  from AlarmVideo where Id=%1;").arg(nId);

	int nCount = 0;
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return 0;
}

int DB::DeleteAlarmAudio(int nId)
{
	if (nId == -1)
		return -1;
	query = new QSqlQuery(db1);
	QString	strSql = QString("delete  from AlarmAudio where Id=%1;;").arg(nId);

	int nCount = 0;
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}
	return 0;
}

int DB::DeleteAlarmConf(int nDevId, int nId)
{
	query = new QSqlQuery(db1);
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
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}

	return 0;
}

int DB::DeletePresetPos(int nPresetId, int nSlaveDev)
{
	query = new QSqlQuery(db1);
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
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}

	return 0;
}

int DB::DeleteDevGroupChannle(int nSlaveDev)
{
	query = new QSqlQuery(db1);
	QString	strSql = QString("delete  from DevGroup where SlaveDevId=%1;").arg(nSlaveDev);
	
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return false;
	}

	return 0;
}

int DB::DeleteVideoPatrol(int nId, int SlaveDevId, int nWinIndex)
{
	query = new QSqlQuery(db1);
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
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	return 0;
}

int DB::deleteChannelInfo(int nDevId)
{
	query = new QSqlQuery(db1);
	QString	strSql = QString("delete from ChannelInfo where DevId=%1;").arg(nDevId);

	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}

	return 0;
}

int DB::GetMainDevID(QString pIP, int nPort, QString pUUID)
{
	query = new QSqlQuery(db1);
	QString	strSql = QString("select DevId from DevInfo where IpAddr = '%1' and port = %2;").arg(pIP).arg(nPort);
	int nCount = 0;
	bool ret = query->exec(strSql);
	if (!ret)
	{
		//myHelper::ShowMessageBoxWarning(QObject::tr("数据库出错%1").arg(query->lastError().text()));
		mlog(LOG_ERR, QObject::tr("数据库出错%1").arg(query->lastError().text()).toLocal8Bit().data());
		return -2;
	}
	else
	{
		while (query->next())
		{
			nCount++;
		}
	}

	return nCount;
}