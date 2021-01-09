#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTreeWidgetItem>
#include <qstring.h>
#include <qvector.h>
#include <vector>
#include "table_structs.h"
#include <list>
#include "mlog/mlog.h"
#include <QWidget>
#include "CompareEvent.h"
#include <QEvent>
#include <QTemporaryFile>

#pragma execution_character_set("utf-8") 
using namespace std;

typedef struct UserInfo
{
	QString id;
	QString name;
	QString sex;
	QString password;
	QString phonenumber;


}my_user;

struct treeNode
{
    QString IpAddr; //IP地址
    int Type;       //设备类型
    QString DevType;
};

typedef struct ChannelInfo_
{
	int szChannel;
	QString szChannelName;
	int ChannelType;
}ChannelInfo;
typedef struct Devinfo_
{
	int DevId;
	QString IpAddr;
	int port;
	QString szName;
	QString szPassWord;
	QString devName;
	int Type;
	int manfacturer;
	QString DevType;
	int DevStatus;
	int SubType;
	QString UUID;
}pDevObj;


class DB:public QWidget
{
	Q_OBJECT
public:

	DB(QWidget *parent = 0);
	~DB();

	bool createConnection();
	void DbCmpVacuumTbl();
	bool CheckUser(QString szName,QString szPassword);  //验证登录信息
	int getUserCount();
	bool CheckLock(QString szPassword);//验证密码
	bool ModifyUser(QString szName,QString szPassword);	//修改用户信息
	bool AddUser(QString szUserName,QString szPassword);	//添加用户
	
	//设备检索信息
	bool AddDevice(TabDevInfo_t* pDevInfo);
	bool ChangeDevice(TabDevInfo_t* pDevInfo);
	bool AddChannelInfo(TabChannelInfo_t* pChannelInfo);
	bool ChangeChannelInfo(int ChannelNum, QString ChannelName, int Type);
	int getDeviceID(QString strIP); 
	int GetChannelID(int nDevId, int nChannelId);
	bool delAllDevInfo();
	//删除所有设备
	bool DelChannelInfo(int DeviceId);

	bool getAllTreeNodes(vector<treeNode> &vTreeNodes);
	bool queryChildNodesById(int id,vector<treeNode> &vNodesID);
	bool getAllTreeMessage(vector<TabDevInfo_t> &vTreeMessage);

	//检索所有主设备信息
	int QueryAllMainDev(std::vector<TabDevInfo_t *>& vectorDevice);
	int QueryAllSlaveDev(std::vector<TabChannelInfo_t *>& vectorChannelInfo,int nDevId = -1);
	int GetMainDevID(QString pIP, int nPort);

	/*检索所有分组*/
	int QueryAllDevGroup(std::list<TabUserDevGroup_t *>& lstDevGroup);
	int SetCommonCfg(TabCommonCfg_t* pClientCfg);
	/*检索所有分组*/
	int QueryAllGroupChannel(std::vector<TabDevGroup_t *>& lstGroupChannel);

	//获取文件夹路径
	bool getFilePath(QString &picPath,QString &DownPath,QString &snapPath);
	//更改文件夹路径
	bool changeFilePath(QString picPath,QString videoPath,QString DownPath,QString snapPath);

	//检查设备信息
	bool checkDevice(QString nIP,int port);

	int QueryAllDeviceMsg(std::vector<pDevObj *>& listDev,QString IpAddr);
	int QueryDeviceChannelMsg(int Devid);

	int QueryAllChannelMsg(std::vector<ChannelInfo *>& listDev, int DevId, int ch);
	//添加比对记录
	bool AddCMPInfo(SMART_FACE_CMP_QUERY_INFO* pCompareInfo);				
	//查询比对记录
	int QueryComparison(FS_FIND_INFO *find_info,  std::vector<SMART_FACE_CMP_QUERY_INFO *>& vectorCompare);
	int GetCmpFindInfo(FS_FIND_INFO *find_info, std::vector<SMART_FACE_CMP_QUERY_INFO *>& vectorCompare, char* pszBuf);

	static DWORD WINAPI DBClearThread(LPVOID Para);
	void DBThreadProc();

	void CreateConnectionDB(QSqlDatabase& db,QString szDBPath);

	void Change_Unicode_UTF8(char *pStrGBKData, int nlen, char *pbuf, int buflen);
	void A2W_Mine(char *lpszA, wchar_t *lpszW);
	size_t Single_UNICODE_UTF8(char * dest_str, wchar_t src_wchar);
	//检搜所有设备日志信息
	int QuerryAlarmLog(std::list<TabAlarmLog_t *>& lstAlarmLog, QString pBeginTime, QString pEndTime );
	int getAlarmConfMsg(int nAlarmConfId, int& devId, int &alarmSrc, int& channel, int &alarmType, int &alarmLevel);
	int getDevInfo(int devId,QString& szDevName);
	//删除设备信息
	int DeleteAlarmLog(int nId, bool bDeleteAll = false);
	bool QueryDevInfo(std::vector<pDevObj>& lstDevInfo);

	QSqlDatabase getDB();

	int QueryPrestPos(TabPresetPos_t* pPresetPos, int nSlaveDev, int nPresetPosId = -1);
	int QueryTrackSequence(TabTrackSequence_t* pTrackSeq, int nSlaveDev);
	long long AddTrackSequence(TabTrackSequence_t* pTrackSeq);
	int UpdateTrackSequence(TabTrackSequence_t* pTrackSeq);
	long long AddTrackPos(TabTrackPos_t* pTrackPos);
	int DeleteTrackPos(int nId, int nTrackSeq);
	int DeleteTrackSequence(int nTrackSeqINo, int nSlaveDev = -1);
	int UpdateTrackPos(TabTrackPos_t* pTrackPos);
	long long AddPresetPos(TabPresetPos_t* pPresetPos);
	int UpdatePresetPos(TabPresetPos_t* pPresetPos);


	//查询警告信息
	int QueryAlarmDev(std::list<TabAlarmConf_t *>& lstAlarmConf, int nDevId);
	int GetAlarmConf(TabAlarmConf_t* pAlarmConf, int nDevId, int nAlarmSource, int nChannel, int nDevAddr = 0);
	int GetAlarmVideo(TabAlarmVideo_t* pAlarmVideo, int nId);
	long long AddAlarmLog(TabAlarmLog_t* pAlarmLog);

	int DeleteAlarmVideo(int nId);
	int DeleteAlarmAudio(int nId);
	int DeleteAlarmConf(int nDevId, int nId = -1);
	int DeletePresetPos(int nPresetId, int nSlaveDev = -1);
	int DeleteDevGroupChannle(int nSlaveDev);
	int DeleteVideoPatrol(int nId, int SlaveDevId = -1, int nWinIndex = -1);
	int deleteChannelInfo(int nDevId);
	bool event(QEvent *e);
	
	int QueryAlarmConfigIsEixst(int nDevId, int nChannel, int nAlarmEventSource);
	long long UpdateAlarmConf(TabAlarmConf_t* pAlarmConf);
private:
	QSqlQuery *m_pQueryClient;//A1600Client.db
	QSqlQuery *m_pQueryRecord;//JVTIAC.db
	int m_nCmpInfoSize;				//总记录数
	QString m_szDBPath ;
	QString m_szJVTIACDBPath ;
public:
	HANDLE m_hThread;
	
	BOOL m_bExit;
	//QString m_szDBPath;
	//QString m_szJVTIACDBPath;
	//QSqlDatabase db1;//A1600Client.db
	//QSqlDatabase db2;//JVTIAC.db
};

extern DB *g_pDatabase;

