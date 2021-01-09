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
#include "adddevice.h"


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

class equimentMgt : public QWidget
{
	Q_OBJECT

public:
	equimentMgt(QWidget *parent = 0);
	~equimentMgt();
	void initTree();
	void initForm();
	void initSearchButton();//设置搜索框样式
	
	void clearCurrAge(QTableWidget *m_table);
	void OnTreeReFresh();

	static  DWORD WINAPI SearchDeviceThread(LPVOID Para);
	void  DisplaySearchDevice(SDK_CONFIG_NET_COMMON_V2* pDevice);
	bool  event(QEvent *e);
	SDK_CONFIG_NET_COMMON_V2 m_Device[MAX_JL_SEARCH_COUNT];	
	long m_lDevNum;

	int AddDeviceInfo(BOOL bAll);
public slots:
	void on_btnRefresh_clicked();//刷新
	void on_btnSearch_clicked();//搜索设备
private slots:
	
	void on_btnAdd_clicked();//添加设备	
	void on_btnAddall_clicked();//添加所有设备
	void on_btnDel_clicked();//删除选中的设备
	void slotRowDoubleClicked();
	void on_btnClear_clicked(); //清空列表

	void on_btnaddEq_clicked();//添加设备
	void on_btnModify_clicked();//修改设备信息

	void on_checkBox_stateChanged(int state);
		
	void on_btnSearchIP_clicked();

signals:
	void startMyThread();//启动子线程
	
public:
	AddDevice* m_pAddDev;
	DevTreePro *m_pTreeDev;
	void CreateWidget();
	void ClearWidget();
private:
	Ui::equimentMgt ui;

	QPushButton *m_pSearchButton;
	QHBoxLayout *m_pSearchLayout;
	QSqlTableModel* m_pModel_manage;
	QTimer* m_pTimerSignal;

	bool m_bClicked;
	QList<QTableWidgetItem*> m_listWidget;
	BOOL m_bShowGroup;
};

#endif // EQUIMENTMGT_H
