#include "equimentmgt.h"
#include <QModelIndex>
#include <QCheckBox>
#include "DB.h"
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QDebug>
#include <QMessageBox>
#include <QMutex>

#include "adddevice.h"
#include "modifydevice.h"
#include "myhelper.h"
#include "client.h"

QMutex eqmutex;
/*设备类型*/
#define DEVINFO_TYPE_ENCODER				0
#define DEVINFO_TYPE_DECODER				1
#define DEVINFO_TYPE_NVR						2
#define DEVINFO_TYPE_IPCAM                  3
#define DEVINFO_TYPE_NVT                  4
#define DEVINFO_TYPE_CRT                 5

/*设备厂家*/
#define DEVINFO_MANUFACTURER_SJ			0
#define DEVINFO_MANUFACTURER_HIK		1
#define DEVINFO_MANUFACTURER_TST		2
#define DEVINFO_MANUFACTURER_BC			3
#define DEVINFO_MANUFACTURER_JL			4  
#define DEVINFO_MANUFACTURER_SJCRT		5
#define DEVINFO_MANUFACTURER_HH			6 
#define DEVINFO_MANUFACTURER_JL_NEW		7

#define CHANNELINFO_TYPE_ALARM_IN				1
#define CHANNELINFO_TYPE_ALARM_OUT			2
#define CHANNELINFO_TYPE_QIUJI                  3	//球机
#define CHANNELINFO_TYPE_QIANGJI                4	//枪机
#define CHANNELINFO_TYPE_GAOSUQIU               5	//高速球
#define CHANNELINFO_TYPE_SHEXIANGTOU            6	//摄像头
#define CHANNELINFO_TYPE_SNAP					7	//抓拍机
#define CHANNELINFO_TYPE_COMPARE				8	//比对机

/*设备状态*/
#define DEVINFO_DEVSTATUS_ONLINE		0
#define DEVINFO_DEVSTATUS_OFFLINE		1


typedef void(__stdcall *ShowJLDevLogDialog)(long lUserID, long lDevType, char *cIP);
equimentMgt::equimentMgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initForm();
	treeeqment = new DevTreePro();
	initTree();
	

	isClicked = false;
	

	timerSignal = new QTimer(this);
	connect(timerSignal,SIGNAL(timeout()),this,SLOT(on_btnSearch_clicked()));
	ui.treeWidget->setHeaderHidden(true);

	ui.lineEdit_Usr->setText("admin");
	ui.lineEdit_Pwd->setText("admin.123");
	
	m_bShowGroup = FALSE;
	m_lDevNum = 0;
}

void equimentMgt::OnTreeReFresh()
{
	ui.treeWidget->clear();
	treeeqment->RefreshDevTree(ui.treeWidget, m_bShowGroup);
}

equimentMgt::~equimentMgt()
{
	
}

void equimentMgt::initTree()
{

	ui.treeWidget->clear();
	
	nCheckNum = 0;
	pChannelTmp = NULL;
	g_strPath = QCoreApplication::applicationDirPath();

	treeeqment->init();
	treeeqment->ShowTreebyType1(ui.treeWidget);
	connect(ui.treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(treeItemChanged(QTreeWidgetItem*, int)));

}

void equimentMgt::initForm()
{
	ui.label_Displayonline->setText(QObject::tr("在线设备:%1").arg(0));
	ui.label_manage->setText(QObject::tr("管理设备:%1").arg(0));
	//设置初始化时候删除按键不可用
	ui.btnDel->setEnabled(false);
	connect(ui.tableView_manage,SIGNAL(clicked(const QModelIndex &)),this,SLOT(slotRowDoubleClicked()));
	
	on_btnRefresh_clicked();
	//表格中添加控件
	ui.tableWidget_Eq->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
	ui.tableWidget_Eq->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.tableWidget_Eq->horizontalHeader()->setStretchLastSection(true);
	
	//QHeaderView* headerView = ui.tableWidget->horizontalHeader();
	//headerView->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget_Eq->setSortingEnabled(true);
	ui.tableWidget_Eq->resizeColumnsToContents();
	ui.tableWidget_Eq->resizeRowsToContents();
	ui.tableWidget_Eq->horizontalHeader()->setStretchLastSection(true); //就是这个地方
	

	//connect(ui.tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(getCheckState(int, int)));
	ui.tableWidget_Eq->setColumnCount(8);
	QStringList header;
	header <<QObject::tr("选择")<<"IP"<<QObject::tr("设备类型")<<QObject::tr("端口")<<QObject::tr("设备序列号")<<QObject::tr("视频通道数")<<QObject::tr("是否已管理")<<QObject::tr("子类型");
	ui.tableWidget_Eq->setHorizontalHeaderLabels(header);

	
}
void equimentMgt::clearCurrAge(QTableWidget *m_table)
{
	int iLen = m_table->rowCount();
	for (int i = 0; i < iLen; i++)
	{
		m_table->removeRow(0);
	}
}
//启动子线程
void equimentMgt::on_btnSearch_clicked()
{
	clearCurrAge(ui.tableWidget_Eq);
	ui.btnSearch->setEnabled(false);
	ui.label_Displayonline->setText(QObject::tr("正在搜索设备..."));
	HANDLE   hThreadAttend = CreateThread(NULL, 0, SearchDeviceThread, this, 0, NULL);
	CloseHandle(hThreadAttend);
}

DWORD WINAPI equimentMgt::SearchDeviceThread(LPVOID Para)
{
	equimentMgt *pThis = (equimentMgt *)Para;
	pThis->g_DevMap.clear();
	int nRetLength = 0;
	memset(pThis->m_Device, 0, sizeof(pThis->m_Device));
	bool bRet = VideoNet_SearchDevice((char *)&pThis->m_Device, sizeof(pThis->m_Device), &nRetLength, 5000);

	if (bRet && nRetLength > 0)
	{
		pThis->m_lDevNum = nRetLength / sizeof(SDK_CONFIG_NET_COMMON_V2);
		pThis->OnJLNDeviceSearchAdd();
	}
	return 0;
}

long equimentMgt::OnJLNDeviceSearchAdd()
{
	int nIndex = 0;
	for (int ix = 0; ix < m_lDevNum; ix++)
	{
		if (m_Device[ix].TCPPort == 0 || m_Device[ix].HostIP.l == 0)
		{
			continue;
		}


		QString IP = QString("%1.%2.%3.%4").arg( m_Device[ix].HostIP.c[0]).arg( m_Device[ix].HostIP.c[1]).
			arg(m_Device[ix].HostIP.c[2]).arg(m_Device[ix].HostIP.c[3]);
		int nChannelNum = m_Device[ix].ChannelNum;

		int nSubDeviceType = m_Device[ix].DeviceType;
		int nDeviceType = DEVINFO_TYPE_IPCAM;
		QString strMachineType = NULL;
		QString strPassword = "admin";
		QString strUUID = "";
		//strUUID = m_Device[ix]
		QString ssn = QString("%1").arg(m_Device[ix].sSn);
		switch (nSubDeviceType)
		{
		case DEV_TYPE_IPC:
		case DEV_TYPE_POEIPC:
		case DEV_TYPE_RTSPIPC:
		case DEV_TYPE_BSIPC:
		case DEV_TYPE_FPIPC:
		case DEV_TYPE_CPIPC:
			strMachineType = "JVT IP Camera";
			nDeviceType = DEVINFO_TYPE_IPCAM;
			strPassword = "admin.123";
			break;
		case DEV_TYPE_DVR:
			strMachineType = "JVT DVR";//
			break;
		case DEV_TYPE_HVR:
			strMachineType = "JVT HVR";//intelligent device 
			nDeviceType = DEVINFO_TYPE_NVT;
			break;
		case DEV_TYPE_NVR:
			strMachineType = "JVT NVR";
			nDeviceType = DEVINFO_TYPE_NVR;
			break;
		case DEV_TYPE_NR:
			break;
		default:
			strMachineType = "JVT IP Camera";
			nDeviceType = DEVINFO_TYPE_IPCAM;
			break;
		}

		addDevice(nChannelNum, IP.toLatin1().data(), m_Device[ix].TCPPort, strMachineType.toLocal8Bit().data(),"admin",
			strPassword.toLatin1().data(),ssn.toLatin1().data(),DEVINFO_MANUFACTURER_JL_NEW, nDeviceType, nSubDeviceType, strUUID.toLatin1().data());
	}
	
	return 0;
}

void equimentMgt::DisplaySearchDevice(DevItem *item)
{
	DB * db = new DB;
	int index = ui.tableWidget_Eq->rowCount();
	ui.tableWidget_Eq->insertRow(index);
	check = new QTableWidgetItem();
	check->setCheckState(Qt::Unchecked);

	ui.tableWidget_Eq->setItem(index, 0, check); //插入复选框
	QString sTmp;
	sTmp = QString("%1").arg(item->ip);
	ui.tableWidget_Eq->setItem(index, 1, new QTableWidgetItem(sTmp));
	sTmp = QString("%1").arg(item->devtype);
	if (sTmp.isEmpty())				//兼容巨龙协议
	{
		if (item->nDevType == 6)
		{
			sTmp = "JVT IP Camera";
		}
	}
	ui.tableWidget_Eq->setItem(index, 2, new QTableWidgetItem(sTmp));
	sTmp = QString("%1").arg(item->port);
	ui.tableWidget_Eq->setItem(index, 3, new QTableWidgetItem(sTmp));
	sTmp = QString("%1").arg(item->sSn);
	ui.tableWidget_Eq->setItem(index, 4, new QTableWidgetItem(sTmp));
	sTmp = QString("%1").arg(item->channel);
	ui.tableWidget_Eq->setItem(index, 5, new QTableWidgetItem(sTmp));

	int ret = db->GetMainDevID(item->ip, item->port, item->szUUID);
	if (ret <= 0)
		ui.tableWidget_Eq->setItem(index, 6, new QTableWidgetItem(QObject::tr("否")));
	else
		ui.tableWidget_Eq->setItem(index, 6, new QTableWidgetItem(QObject::tr("否")));

	sTmp = QString("%1").arg(item->nManufacturer);
	ui.tableWidget_Eq->setItem(index, 7, new QTableWidgetItem(sTmp));

	sTmp = QString("%1").arg(item->nSubDevType);
	ui.tableWidget_Eq->setItem(index, 8, new QTableWidgetItem(sTmp));

	ui.btnSearch->setEnabled(true);
	ui.label_Displayonline->setText(QObject::tr("在线设备:%1").arg(m_lDevNum));
}

void equimentMgt::addDevice(int nChannel, char* ip, int nPort, char* devType, char* username, char* password, char *sSn,int nManufacturer /* = -1 */, int nDevType /* = -1 */, int nSubDevType /* = -1 */, char* pszUUID /* = NULL */)
{
	
	map<QString, DevItem *>::iterator real_iter;
	QString sTmp;
	sTmp = QString(QLatin1String(ip));
	eqmutex.lock();
	real_iter = g_DevMap.find(sTmp);
	if (real_iter != g_DevMap.end())
	{
		eqmutex.unlock();
		
		return;
	}
	eqmutex.unlock();
	DevItem* item = new DevItem;
	memset(item, 0, sizeof(DevItem));
	strcpy(item->dvrname,ip);
	strcpy(item->ip,ip);
	item->port = nPort;
	strcpy(item->username, username);
	strcpy(item->password, password);
	strcpy(item->devtype,devType);
	item->channel = nChannel;
	item->userid = -1;
	item->nManufacturer = nManufacturer;
	item->nDevType = nDevType;
	item->nSubDevType = nSubDevType;
	strcpy(item->szUUID,pszUUID);
	strcpy(item->sSn, sSn);
	for (int i = 0; i < item->channel; i++)
		sprintf(item->channelname[i], "ch%02d", i + 1);

	eqmutex.lock();
	g_DevMap[sTmp] = item;
	eqmutex.unlock();
#if 0
	sTmp.Format("%s", item->ip);
	int index = pSearchDVSDlg->g_ListDev.InsertItem(pSearchDVSDlg->g_ListDev.GetItemCount(), sTmp, 0);
	sTmp.Format("%s", devType);
	pSearchDVSDlg->g_ListDev.SetItemText(index, 1, sTmp);
	sTmp.Format("%d", item->port);
	pSearchDVSDlg->g_ListDev.SetItemText(index, 2, sTmp);
	pSearchDVSDlg->g_ListDev.SetItemText(index, 3, "");
	sTmp.Format("%d", item->channel);
	pSearchDVSDlg->g_ListDev.SetItemText(index, 4, sTmp);

	int ret = CDB::instance()->GetMainDevID(ip, nPort);
	if (ret <= 0)
		pSearchDVSDlg->g_ListDev.SetItemText(index, 5, _T("否"));
	else
		pSearchDVSDlg->g_ListDev.SetItemText(index, 5, _T("是"));
#else
	//PostMessage(pSearchDVSDlg->m_hWnd, WM_DEVMNG_UPDATELIST, (WPARAM)item, 1);
	CompareEvent *custevent = new CompareEvent(CompareEvent::getType(CET_DEVMNG_UPDATELIST));
	custevent->setItem(item);
	QApplication::postEvent(this, custevent);
#endif

}

QString equimentMgt::GetDeviceType(int type)
{
	QString strMachineType = NULL;
	switch(type)
	{
	case DEV_TYPE_IPC:
	case DEV_TYPE_POEIPC:
	case DEV_TYPE_RTSPIPC:
	case DEV_TYPE_BSIPC:
	case DEV_TYPE_FPIPC:
	case DEV_TYPE_CPIPC:
		strMachineType = "JVT IP Camera";
		break;
	case DEV_TYPE_DVR:
		strMachineType = "JVT DVR";
		break;
	case DEV_TYPE_HVR:
		strMachineType = "JVT HVR";//intelligent device 
		break;
	case DEV_TYPE_NVR:
		strMachineType = "JVT NVR";
		break;
	case DEV_TYPE_NR:
		break;
	default:
		strMachineType = "JVT IP Camera";
		break;
	}
	return strMachineType;
}

//添加设备
void equimentMgt::on_btnAdd_clicked()
{
	if (ui.tableWidget_Eq->rowCount()<0)
	{
		return;
	}
	int Flg = 0;
	int devNum = 0;
	
	int Type = 0;
	int Company = 0;
	QString szUUID = NULL;
	int channelNum =0;
	int nSubType = 0;
	for (int i = 0; i < ui.tableWidget_Eq->rowCount(); i++)
	{
		if (ui.tableWidget_Eq->item(i, 2)->text() == "JVT NVR")
		{
			Type = DEVINFO_TYPE_NVR;
		}
		else if (ui.tableWidget_Eq->item(i, 2)->text() == "JVT IP Camera")
		{
			Type = DEVINFO_TYPE_IPCAM;
		}
		else
		{
			Type = DEVINFO_TYPE_ENCODER;
		}

		Company = DEVINFO_MANUFACTURER_JL_NEW;	

		if (ui.tableWidget_Eq->item(i, 0)->checkState())
		{
			int state = 0;
			DB *db = new DB;

			map<QString,DevItem*>::iterator real_iter;
			real_iter = g_DevMap.find(ui.tableWidget_Eq->item(i, 1)->text());
			if (real_iter != g_DevMap.end())
			{
				switch(real_iter->second->nSubDevType)
				{
				case SDK_DEV_TYPE_DVR:
				case SDK_DEV_TYPE_HVR:
				case SDK_DEV_TYPE_IPC:
				case SDK_DEV_TYPE_POEIPC:
				case SDK_DEV_TYPE_NVR:
				case SDK_DEV_TYPE_RTSPIPC:
					nSubType = CHANNELINFO_TYPE_QIANGJI;
					break;
				case SDK_DEV_TYPE_FPIPC:
				case SDK_DEV_TYPE_CPIPC:
					nSubType = CHANNELINFO_TYPE_SNAP;
					break;
				case SDK_DEV_TYPE_BSIPC:
					nSubType = CHANNELINFO_TYPE_COMPARE;
					break;
				default:
					break;
				}
				bool ret = db->AddDevice(ui.tableWidget_Eq->item(i, 1)->text(), ui.tableWidget_Eq->item(i, 3)->text().toInt(),
					ui.lineEdit_Usr->text(), ui.lineEdit_Pwd->text(), ui.tableWidget_Eq->item(i, 1)->text(), Type, Company, ui.tableWidget_Eq->item(i, 2)->text(), 0, nSubType);
				if (!ret)
				{

					//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("设备'%1'已经存在").arg(ui.tableWidget->item(i,1)->text()));
					myHelper::ShowMessageBoxWarning(QObject::tr("设备%1已经存在").arg(ui.tableWidget_Eq->item(i, 1)->text()));
					return;
				}
				for (int j = 0;j < real_iter->second->channel;j++)
				{
					int DevId = db->getDeviceID(real_iter->second->ip); 
					bool ret1 = db->addChannelInfo(DevId,j+1,real_iter->second->channelname[j],nSubType,CHANNELINFO_STATUS_OPEN);
					if (!ret1)
					{
						//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("插入channelinfo 失败'%1'").arg(real_iter->second.channelname[j]));
						myHelper::ShowMessageBoxWarning(QObject::tr("channelinfo信息插入到插入到数据库失败!").arg(real_iter->second->channelname[j]));
						return;
					}
				}
			}
			
			
			Flg = 1;
			devNum++;
		}
	}
	if (Flg == 0)
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("请选择要添加的设备"));
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择要添加的设备!"));
		return;
	}
	else
	{
		on_btnRefresh_clicked();
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("添加设备成功"));
		myHelper::ShowMessageBoxInfo(QObject::tr("添加设备成功!"));
		if (Client::instance()->m_TabWidget.m_PREVIEW != FALSE)
		{
			Client::instance()->PreviewPro->OnTreeReFresh();
		}
		if (Client::instance()->m_TabWidget.m_VIDEOPLAY != FALSE)
		{
			Client::instance()->m_videoPlayBack->OnTreeReFresh();
		}
		if (Client::instance()->m_TabWidget.m_COMPARECORD != FALSE)
		{

			Client::instance()->m_dlgExport->OnTreeReFresh();
		}
		OnTreeReFresh();
		
	}

	
}

void equimentMgt::on_btnRefresh_clicked()
{
	DB *db = new DB;
	//设置模型
	model_manage = new QSqlTableModel(this,db->getDB());
	model_manage->setTable("DevInfo");
	//把model放在view
	ui.tableView_manage->setModel(model_manage);

	//model显示数据
	model_manage->select();
	model_manage->setHeaderData(1,Qt::Horizontal,QObject::tr("IP"));
	model_manage->setHeaderData(5,Qt::Horizontal,QObject::tr("设备名"));
	
	model_manage->setEditStrategy(QSqlTableModel::OnManualSubmit);
	ui.tableView_manage->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView_manage->verticalHeader()->setVisible(false); 
	ui.tableView_manage->horizontalHeader()->setStretchLastSection(true);
	ui.tableView_manage->setColumnHidden(0,true);
	ui.tableView_manage->setColumnHidden(2,true);
	ui.tableView_manage->setColumnHidden(3,true);
	ui.tableView_manage->setColumnHidden(4,true);
	ui.tableView_manage->setColumnHidden(6,true);
	ui.tableView_manage->setColumnHidden(7,true);
	ui.tableView_manage->setColumnHidden(8,true);
	ui.tableView_manage->setColumnHidden(9,true);
	ui.tableView_manage->setColumnHidden(10, true);
	ui.tableView_manage->setColumnHidden(11, true);
	ui.tableView_manage->setSortingEnabled(true);
	//设置数据库不允许修改
	ui.tableView_manage->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.label_manage->setText(QObject::tr("管理设备:%1").arg(model_manage->rowCount()));
}

void equimentMgt::on_btnAddall_clicked()
{
	if (ui.tableWidget_Eq->rowCount() == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("没有可以添加的设备"));
		return;
	}
	int Flg = 0;
	int devNum = 0;
	int Type = 0;
	int Company = 0;
	QString szUUID = NULL;
	int channelNum =0;
	int nSubType = 0;
	for (int i = 0; i < ui.tableWidget_Eq->rowCount(); i++)
	{
		if (ui.tableWidget_Eq->item(i, 2)->text() == "JVT NVR")
		{
			Type = DEVINFO_TYPE_NVR;
		}
		else if (ui.tableWidget_Eq->item(i, 2)->text() == "JVT IP Camera")
		{
			Type = DEVINFO_TYPE_IPCAM;
		}
		else
		{
			Type = DEVINFO_TYPE_ENCODER;
		}

		Company = DEVINFO_MANUFACTURER_JL_NEW;
	
		int state = 0;
		DB *db = new DB;
		map<QString,DevItem*>::iterator real_iter;
		real_iter = g_DevMap.find(ui.tableWidget_Eq->item(i, 1)->text());
		if (real_iter != g_DevMap.end())
		{
			switch(real_iter->second->nSubDevType)
			{
			case SDK_DEV_TYPE_DVR:
			case SDK_DEV_TYPE_HVR:
			case SDK_DEV_TYPE_IPC:
			case SDK_DEV_TYPE_POEIPC:
			case SDK_DEV_TYPE_NVR:
			case SDK_DEV_TYPE_RTSPIPC:
				nSubType = CHANNELINFO_TYPE_QIANGJI;
				break;
			case SDK_DEV_TYPE_FPIPC:
			case SDK_DEV_TYPE_CPIPC:
				nSubType = CHANNELINFO_TYPE_SNAP;
				break;
			case SDK_DEV_TYPE_BSIPC:
				nSubType = CHANNELINFO_TYPE_COMPARE;
				break;
			default:
				break;
			}
			bool ret = db->AddDevice(ui.tableWidget_Eq->item(i, 1)->text(), ui.tableWidget_Eq->item(i, 3)->text().toInt(),
				ui.lineEdit_Usr->text(), ui.lineEdit_Pwd->text(), ui.tableWidget_Eq->item(i, 1)->text(), Type, Company, ui.tableWidget_Eq->item(i, 2)->text(), 0, nSubType);
			if (!ret)
			{

				//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("设备'%1'已经存在").arg(ui.tableWidget->item(i,1)->text()));
				myHelper::ShowMessageBoxWarning(QObject::tr("设备%1已经存在").arg(ui.tableWidget_Eq->item(i, 1)->text()));
				continue;
			}
			ui.tableWidget_Eq->setItem(i, 6, new QTableWidgetItem(QObject::tr("是")));
			for (int j = 0;j < real_iter->second->channel;j++)
			{
					DevId = db->getDeviceID(real_iter->second->ip); 
				bool ret1 = db->addChannelInfo(DevId,j+1,real_iter->second->channelname[j],nSubType,CHANNELINFO_STATUS_OPEN);
				if (!ret1)
				{
					//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("插入channelinfo 失败'%1'").arg(real_iter->second.channelname[j]));
					myHelper::ShowMessageBoxWarning(QObject::tr("channelinfo信息插入到插入到数据库失败!").arg(real_iter->second->channelname[j]));
					return;
				}
			}
		}
	}

	on_btnRefresh_clicked();
	//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("添加所有设备成功"));
	myHelper::ShowMessageBoxInfo(QObject::tr("添加所有设备成功!"));
	if (Client::instance()->m_TabWidget.m_PREVIEW != FALSE)
	{
		Client::instance()->PreviewPro->OnTreeReFresh();
	}
	if (Client::instance()->m_TabWidget.m_VIDEOPLAY != FALSE)
	{
		Client::instance()->m_videoPlayBack->OnTreeReFresh();
	}
	if (Client::instance()->m_TabWidget.m_COMPARECORD != FALSE)
	{

		Client::instance()->m_dlgExport->OnTreeReFresh();
	}
	OnTreeReFresh();
	
}

void equimentMgt::on_btnDel_clicked()
{
	if (model_manage->rowCount() == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("管理的设备为空"));
		return;
	}
	if (myHelper::ShowMessageBoxQuesion(QObject::tr("确定删除设备吗?")) != 1)
		return;
	if (Client::instance()->m_TabWidget.m_PREVIEW != FALSE)
	{

		for (int i = 0; i < 16; i++)
		{
			if (Client::instance()->PreviewPro->widgets[i].widget->m_pDev == NULL)
				continue;
			if (Client::instance()->PreviewPro->widgets[i].widget->m_dspWndinfo.bVideo)
			{
				myHelper::ShowMessageBoxWarning(QObject::tr("请先停止预览!"));
				return;
			}
		}
	}
	int curRow=ui.tableView_manage->currentIndex().row();//选中行
	QAbstractItemModel *modessl = ui.tableView_manage->model();

	QModelIndex indextemp = modessl->index(curRow,0);//遍历第一行的所有列
	QVariant datatemp = modessl->data(indextemp);
	int  m_DevId = datatemp.toInt();
	DB *db = new DB;
	bool ret = db->DelAllDevice(m_DevId);
	if (ret)
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("删除设备成功"));
		myHelper::ShowMessageBoxWarning(QObject::tr("删除设备成功!"));
	}
	else
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("删除设备失败"));
		myHelper::ShowMessageBoxWarning(QObject::tr("删除设备失败!"));
	}
	on_btnRefresh_clicked();
	if (Client::instance()->m_TabWidget.m_PREVIEW != FALSE)
	{
		Client::instance()->PreviewPro->OnTreeReFresh();
	}
	if (Client::instance()->m_TabWidget.m_VIDEOPLAY != FALSE)
	{
		Client::instance()->m_videoPlayBack->OnTreeReFresh();
	}
	if (Client::instance()->m_TabWidget.m_COMPARECORD != FALSE)
	{

		Client::instance()->m_dlgExport->OnTreeReFresh();
	}
	OnTreeReFresh();
}

void equimentMgt::slotRowDoubleClicked()
{
	ui.btnDel->setEnabled(true);
	isClicked = true;
	

}

//清空
void equimentMgt::on_btnClear_clicked()
{
	if (model_manage->rowCount() == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("管理的设备为空"));
		return;
	}

	if (Client::instance()->m_TabWidget.m_PREVIEW != FALSE)
	{

		for (int i = 0; i < 16; i++)
		{
			if (Client::instance()->PreviewPro->widgets[i].widget->m_pDev == NULL)
				continue;
			if (Client::instance()->PreviewPro->widgets[i].widget->m_dspWndinfo.bVideo)
			{
				myHelper::ShowMessageBoxWarning(QObject::tr("请先停止预览!"));
				return;
			}
		}

	}
	if (myHelper::ShowMessageBoxQuesion(QObject::tr("确定删除所有设备吗?")) == 1)
	{ 
		DB *db = new DB;
		bool ret = db->delAllDevInfo();
		if (ret)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("清空所有设备成功!"));
			on_btnRefresh_clicked();
			if (Client::instance()->m_TabWidget.m_PREVIEW != FALSE)
			{
				Client::instance()->PreviewPro->OnTreeReFresh();
			}
			if (Client::instance()->m_TabWidget.m_VIDEOPLAY != FALSE)
			{
				Client::instance()->m_videoPlayBack->OnTreeReFresh();
			}
			if (Client::instance()->m_TabWidget.m_COMPARECORD != FALSE)
			{

				Client::instance()->m_dlgExport->OnTreeReFresh();
			}
			OnTreeReFresh();
		}
	}

}

void equimentMgt::on_btnaddEq_clicked()
{
	AddDevice *aDev = new AddDevice();
	aDev->show();
	
}

void equimentMgt::on_btnModify_clicked()
{
	if (model_manage->rowCount() == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("管理的设备为空"));
		return;
	}

	deviceVec.clear();
	if (isClicked == false)
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("没有选中设备"));
		myHelper::ShowMessageBoxWarning(QObject::tr("没有选中设备!"));
		return;
	}

	int curRow=ui.tableView_manage->currentIndex().row();//选中行
	QAbstractItemModel *modessl = ui.tableView_manage->model();

	ModifyDevice *dev = new ModifyDevice();
	
	QModelIndex indextemp = modessl->index(curRow,1);//遍历第一行的所有列
	QVariant datatemp = modessl->data(indextemp);
	QString m_IpAddr = datatemp.toString();
	DB *db = new DB;
	
	int ret = db->QueryAllDeviceMsg(deviceVec,m_IpAddr);
	if (ret == -1)
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("查询数据失败"));
		myHelper::ShowMessageBoxWarning(QObject::tr("查询数据失败!"));
		return;
	}
	
	dev->m_displayName->setText(deviceVec[0]->IpAddr);
	dev->m_displayIP->setText(deviceVec[0]->IpAddr);
	dev->m_displayUsr->setText(deviceVec[0]->szName);
	dev->m_displayPwd->setText(deviceVec[0]->szPassWord);
	dev->m_displayPort->setText(QString::number(deviceVec[0]->port));
	dev->m_displySubType->setCurrentIndex(getDeviceID(deviceVec[0]->SubType));
	dev->show();

	

}

int equimentMgt::getDeviceID(int mode)
{
	int subtype = 0;
	switch(mode)
	{
	case CHANNELINFO_TYPE_QIUJI:
		subtype = 0;
		break;
	case CHANNELINFO_TYPE_QIANGJI:
		subtype = 1;
		break;
	case CHANNELINFO_TYPE_GAOSUQIU:
		subtype = 2;
		break;
	case CHANNELINFO_TYPE_SHEXIANGTOU:
		subtype = 3;
		break;
	case CHANNELINFO_TYPE_SNAP:
		subtype = 4;
		break;
	case CHANNELINFO_TYPE_COMPARE:
		subtype = 5;
		break;
	default:
		subtype = 5;
		break;
	}
	return subtype;
}


void equimentMgt::on_checkBox_stateChanged(int state)
{
	if (state == Qt::Checked) // "选中"
	{
		timerSignal->start(1000*60);
		qDebug()<<"Checked";
	}
	else if(state == Qt::Unchecked) // "半选"
	{
		qDebug()<<"Unchecked";
		timerSignal->stop();
	}
	
}

void equimentMgt::treeItemChanged(QTreeWidgetItem *item, int column)
{
	QTreeWidgetItem *parent = item->parent();
	if (parent == NULL){
		return;
	}
	
	int childCount = parent->childCount();
	for (int i = 0; i < childCount; i++){
		QTreeWidgetItem *childItem = parent->child(i);


		if (childItem->checkState(0) == Qt::Checked){

			QVariant var = item->data(i, Qt::UserRole);
			TreeData_t* pChannel = (TreeData_t *)var.value<void *>();

			pChannelTmp = pChannel;
			if (pChannelTmp == NULL)
			{
				return;
			}
			nCheckNum++;


		}
	}
}
/*
void equimentMgt::on_btnDeviceLog_clicked()
{
	if (pChannelTmp == NULL)
	{
		//QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("请在设备列表中选择设备"));
		myHelper::ShowMessageBoxWarning(QObject::tr("请在设备列表中选择设备"));
		return;
	}
	int nUserId = pChannelTmp->DevInfo->Login();
	if (nUserId < 0)
	{

		myHelper::ShowMessageBoxWarning(QObject::tr("连接设备失败"));
		return;
	}
	QString strDevConfigDllName;
	strDevConfigDllName = QString("%1\\JLConfigSetting.dll").arg(g_strPath);
	HINSTANCE dllinstance = ::LoadLibrary(strDevConfigDllName.toLatin1().data());
	if (dllinstance == NULL)
	{
		QMessageBox::warning(NULL, QObject::tr("警告"), QObject::tr("打开DLL文件失败"));
		myHelper::ShowMessageBoxWarning(QObject::tr("打开DLL文件失败"));
		return;
	}
	ShowJLDevLogDialog func;
	func = (ShowJLDevLogDialog)GetProcAddress(dllinstance, "ShowJLDevLogDialog");
	if (func == NULL)
		myHelper::ShowMessageBoxWarning(QObject::tr("dll文件错误"));
	else
	{

		CJLNDevice* pDevInfo = (CJLNDevice*)pChannelTmp->DevInfo;
		long lDevType = 0;
		lDevType = pDevInfo->GetDevInfo()->nType;
		func((long)pDevInfo->GetServerHandle(), lDevType, pDevInfo->GetDevInfo()->szIpAddr);
	}
	//pChannelTmp->DevInfo->Logout();
}
*/
void equimentMgt::on_btnSearchIP_clicked()
{
	ui.treeWidget->collapseAll();
	QString txt = ui.lineEdit_Search->text();
	bool isEmptyTxt = txt.isEmpty();
	bool isEmptyTree = ui.treeWidget->topLevelItemCount(); //非零个为true
	if (isEmptyTxt) {
		QTreeWidgetItemIterator it(ui.treeWidget);
		while (*it) {
			(*it)->setBackground(0, treeeqment->m_itemBrush);
			it++;
		}
		return;
	}
	if (!isEmptyTree) { return; }


#if 0
	int count = ui->treeWidget->topLevelItemCount();
	for (int i = 0; i < count; ++i) {
		QTreeWidgetItem *cItem = ui->treeWidget->topLevelItem(i);
		if (-1 != cItem->text(0).indexOf(txt)) {
			cItem->setBackground(0, Qt::green);
		}
		else {
			cItem->setBackground(0, m_itemBrush);
		}
		searchChild(cItem, txt);
	}
#else

	QTreeWidgetItemIterator it(ui.treeWidget);
	while (*it) {
		QString str = (*it)->text(0);
		if (-1 != str.indexOf(txt)) {
			QTreeWidgetItem *pItem = (*it)->parent();
			if (pItem != NULL) {
				bool isExpanded = pItem->isExpanded();
				if (!isExpanded){
					ui.treeWidget->expandItem(pItem);
				}
			}
			(*it)->setBackground(0, Qt::green);
			treeeqment->parentExpand(*it);
		}
		else{
			(*it)->setBackground(0, treeeqment->m_itemBrush);
		}
		it++;
	}
#endif
}

bool equimentMgt::event(QEvent *e)
{
	CompareEvent *event = static_cast<CompareEvent *>(e);

	if (e->type() == static_cast <QEvent::Type>(CompareEvent::getType(CET_DEVMNG_UPDATELIST)))
	{
		DevItem *item = (DevItem *)event->getItem();
		DisplaySearchDevice(item);
	}
	
	return QWidget::event(event);
}
