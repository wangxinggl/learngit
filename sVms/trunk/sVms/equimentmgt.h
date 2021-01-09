#ifndef EQUIMENTMGT_H
#define EQUIMENTMGT_H

#include <QWidget>
#include "ui_equimentmgt.h"
#include <QThread>
#include <QDebug>
#include <QStandardItemModel>
#include <map>
#include <QSqlTableModel>
#include "DB.h"
#include <QRadioButton>
#include <QTimer>
#include <QTreeWidgetItem>
#include <QString>
#include "devtreepro.h"


using namespace std;
#define  MAX_JL_SEARCH_COUNT 100
typedef struct 
{
	char dvrname[64];
	char   ip[32];
	char    username[64];
	char    password[64];
	char    sSn[64];
	int port;
	int channel;
	char channelname[320][128];
	char devtype[256];
	int nManufacturer;  //by zjh 
	int userid;
	int nDevType;		// by zjh 20170807
	int nSubDevType;	//设备子类型，区分比对机抓拍机 by jfp 20190227
	char szUUID[64];	//设备UUID
}DevItem;

enum Net_Search_DevType   //by zjh 20170807
{
	DEV_TYPE_IPC,
	DEV_TYPE_DVR,
	DEV_TYPE_HVR,
	DEV_TYPE_POEIPC,
	DEV_TYPE_NVR,
	DEV_TYPE_RTSPIPC,

	DEV_TYPE_BSIPC,			//比对机
	DEV_TYPE_FPIPC,			//抓拍机
	DEV_TYPE_CPIPC,			//车牌抓拍机
	DEV_TYPE_NR
};

class equimentMgt : public QWidget
{
	Q_OBJECT

public:
	equimentMgt(QWidget *parent = 0);
	~equimentMgt();
	void initTree();
	void initForm();
	QString GetDeviceType(int type);
	
	int getDeviceID(int mode);
	void clearCurrAge(QTableWidget *m_table);
	void OnTreeReFresh();

	static  DWORD WINAPI SearchDeviceThread(LPVOID Para);
	long   OnJLNDeviceSearchAdd();
	void  DisplaySearchDevice(DevItem *item);
	void  addDevice(int nChannel, char* ip, int nPort, char* devType, char* username, char* password, char *sSn,int nManufacturer = -1, int nDevType = -1, int nSubDevType = -1, char* pszUUID = NULL);
	bool  event(QEvent *e);
	SDK_CONFIG_NET_COMMON_V2 m_Device[MAX_JL_SEARCH_COUNT];

	
	long m_lDevNum;
public slots:
	void on_btnRefresh_clicked();//刷新
private slots:
	void on_btnSearch_clicked();//搜索设备
	
	void on_btnAdd_clicked();//添加设备

	
	void on_btnAddall_clicked();//添加所有设备
	void on_btnDel_clicked();//删除选中的设备
	void slotRowDoubleClicked();
	void on_btnClear_clicked(); //清空列表

	void on_btnaddEq_clicked();//添加设备
	void on_btnModify_clicked();//修改设备信息

	void on_checkBox_stateChanged(int state);

	//设备日志
	//void on_btnDeviceLog_clicked();
	void treeItemChanged(QTreeWidgetItem *item, int column);
	
	void on_btnSearchIP_clicked();

signals:
	void startMyThread();//启动子线程
	
private:
	Ui::equimentMgt ui;

	QCheckBox *comBox;
	QSqlTableModel *model_online_info;
	QTableWidgetItem *check; 
	QSqlTableModel *model_manage;

	QTimer *timerSignal;

	bool isClicked;
	int DevId;
private:
	map<QString,DevItem> deviceMap;
	std::map<QString, DevItem*>  g_DevMap;
	vector<DevInfo *> deviceVec;
	DevTreePro *treeeqment;
	TreeData_t *pChannelTmp;
	int nCheckNum;
	QString g_strPath;

	BOOL m_bShowGroup;
};

#endif // EQUIMENTMGT_H
