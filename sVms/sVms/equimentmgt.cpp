#define  _CRT_SECURE_NO_WARNINGS
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

#include "myhelper.h"
#include "client.h"

#define SEARCH_COLUMN_COUNT		7
#define SEARCH_ROW_COUNT		100

QMutex eqmutex;
extern vector<TabDevInfo_t*>			g_vectorDevInfo;
extern vector<TabChannelInfo_t*>		g_vectorChannelInfo;
extern Client* g_pInstance;


typedef void(__stdcall *ShowJLDevLogDialog)(long lUserID, long lDevType, char *cIP);
equimentMgt::equimentMgt(QWidget *parent)
	: QWidget(parent)
	, m_pTreeDev(NULL)
	, m_pSearchButton(NULL)
	, m_pSearchLayout(NULL)
	, m_pTimerSignal(NULL)
	, m_pModel_manage(NULL)
	, m_pAddDev(NULL)
{
	ui.setupUi(this);
	initForm();
	initSearchButton();	

	m_bClicked = false;	

	m_pTimerSignal = new QTimer(this);
	connect(m_pTimerSignal,SIGNAL(timeout()),this,SLOT(on_btnSearch_clicked()));
	ui.treeWidget->setHeaderHidden(true);

	ui.lineEdit_Usr->setText("admin");
	ui.lineEdit_Pwd->setText("admin.123");
	
	m_bShowGroup = FALSE;
	m_lDevNum = 0;
}

void equimentMgt::OnTreeReFresh()
{
	on_btnRefresh_clicked();
	ui.treeWidget->clear();
	m_pTreeDev->RefreshDevTree(ui.treeWidget, m_bShowGroup);
}

equimentMgt::~equimentMgt()
{
	if (m_pTimerSignal)
	{
		delete m_pTimerSignal;
		m_pTimerSignal = NULL;
	}
	if (m_pSearchButton)
	{
		delete m_pSearchButton;
		m_pSearchButton = NULL;
	}
	if (m_pSearchLayout)
	{
		delete m_pSearchLayout;
		m_pSearchLayout = NULL;
	}
	if (m_pModel_manage)
	{
		delete m_pModel_manage;
		m_pModel_manage = NULL;
	}
	if (m_pAddDev)
	{
		delete m_pAddDev;
		m_pAddDev = NULL;
	}

	ClearWidget();
}

void equimentMgt::initSearchButton()
{
	m_pSearchButton = new QPushButton(this);

	m_pSearchButton->setCursor(Qt::PointingHandCursor);
	m_pSearchButton->setFixedSize(22, 22);
	m_pSearchButton->setToolTip(QObject::tr("搜索"));
	m_pSearchButton->setStyleSheet("QPushButton{border-image:url(:/res/SoftIcon/icon_search_normal.png); background:transparent;} \
	QPushButton:hover{border-image:url(:/res/SoftIcon/icon_search_hover.png)} \
	QPushButton:pressed{border-image:url(:/res/SoftIcon/icon_search_press.png)}");
	QMargins margins = ui.lineEdit_Search->textMargins();
	ui.lineEdit_Search->setTextMargins(margins.left(), margins.top(), m_pSearchButton->width(), margins.bottom());
	ui.lineEdit_Search->setPlaceholderText(QObject::tr("请输入搜索内容"));

	m_pSearchLayout = new QHBoxLayout();
	m_pSearchLayout->addStretch();
	m_pSearchLayout->addWidget(m_pSearchButton);
	m_pSearchLayout->setSpacing(0);
	m_pSearchLayout->setContentsMargins(0, 0, 0, 0);
	ui.lineEdit_Search->setLayout(m_pSearchLayout);

	connect(m_pSearchButton, SIGNAL(clicked(bool)), this, SLOT(on_btnSearchIP_clicked()));
}

void equimentMgt::initTree()
{
	ui.treeWidget->clear();
	
	m_pTreeDev->ShowTreebyType(ui.treeWidget);
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
	
	ui.tableWidget_Eq->setSortingEnabled(true);
	ui.tableWidget_Eq->resizeColumnsToContents();
	ui.tableWidget_Eq->resizeRowsToContents();
	ui.tableWidget_Eq->horizontalHeader()->setStretchLastSection(true); 	

	ui.tableWidget_Eq->setColumnCount(SEARCH_COLUMN_COUNT);
	ui.tableWidget_Eq->setRowCount(SEARCH_ROW_COUNT);
	QStringList header;
	header <<QObject::tr("选择")<<"IP"<<QObject::tr("设备类型")<<QObject::tr("端口") << QObject::tr("MAC地址") <<QObject::tr("视频通道数")<<QObject::tr("子类型");
	ui.tableWidget_Eq->setHorizontalHeaderLabels(header);	
}

void equimentMgt::clearCurrAge(QTableWidget *m_table)
{
	QTableWidgetItem* pWidget = NULL;
	int nItem = SEARCH_COLUMN_COUNT * SEARCH_ROW_COUNT;
	for (int i = 0; i < nItem; i ++)
	{
		pWidget = m_listWidget.at(i);
		if (i % SEARCH_COLUMN_COUNT == 0)
		{
			pWidget->setCheckState(Qt::Unchecked);
		}
		else
		{
			pWidget->setText("");
		}
	}
}
//启动子线程
void equimentMgt::on_btnSearch_clicked()
{
	clearCurrAge(ui.tableWidget_Eq);
	ui.btnSearch->setEnabled(false);
	ui.tableWidget_Eq->setSortingEnabled(false);
	ui.label_Displayonline->setText(QObject::tr("正在搜索设备..."));
	HANDLE   hThreadAttend = CreateThread(NULL, 0, SearchDeviceThread, this, 0, NULL);
	CloseHandle(hThreadAttend);
}

DWORD WINAPI equimentMgt::SearchDeviceThread(LPVOID Para)
{
	equimentMgt *pThis = (equimentMgt *)Para;
	int nRetLength = 0;
	memset(pThis->m_Device, 0, sizeof(pThis->m_Device));
	bool bRet = VideoNet_SearchDevice((char *)&pThis->m_Device, sizeof(pThis->m_Device), &nRetLength, 2000);

	if (bRet && nRetLength > 0)
	{
		pThis->m_lDevNum = nRetLength / sizeof(SDK_CONFIG_NET_COMMON_V2);

		CompareEvent *custevent = new CompareEvent(CET_DEVMNG_UPDATELIST);
		custevent->setItem(&pThis->m_Device);
		QApplication::postEvent(pThis, custevent);
	}
	else
	{
		return -1;
	}
	return 0;
}

void equimentMgt::DisplaySearchDevice(SDK_CONFIG_NET_COMMON_V2* pDevice)
{
	QString strTemp;
	QString strIP;
	int nDeviceType = SDK_DEV_TYPE_IPC;
	QTableWidgetItem* pQTItem;
	int ret = 0;
	for (int i = 0; i < m_lDevNum; i++)
	{
		pQTItem = ui.tableWidget_Eq->item(i, 0);
		if (!pQTItem)
		{
			pQTItem = m_listWidget.at(i * SEARCH_COLUMN_COUNT);
			if (pQTItem)
			{
				ui.tableWidget_Eq->setItem(i, 0, pQTItem); //插入复选框
			}
		}
		pQTItem->setCheckState(Qt::Unchecked);

		strIP = QString("%1.%2.%3.%4").arg(m_Device[i].HostIP.c[0]).arg(m_Device[i].HostIP.c[1]).
			arg(m_Device[i].HostIP.c[2]).arg(m_Device[i].HostIP.c[3]);
		pQTItem = ui.tableWidget_Eq->item(i, 1);
		if (!pQTItem)
		{
			pQTItem = m_listWidget.at(i * SEARCH_COLUMN_COUNT + 1);
			if (pQTItem)
			{
				ui.tableWidget_Eq->setItem(i, 1, pQTItem);
			}
		}
		pQTItem->setText(strIP);

		switch (m_Device[i].DeviceType)
		{
		case SDK_DEV_TYPE_IPC:
		case SDK_DEV_TYPE_POEIPC:
		case SDK_DEV_TYPE_RTSPIPC:
		case SDK_DEV_TYPE_BSIPC:
		case SDK_DEV_TYPE_FPIPC:
		case SDK_DEV_TYPE_CPIPC:
		case SDK_DEV_TYPE_MJIPC:
			strTemp = "JVT IP Camera";
			nDeviceType = SDK_DEV_TYPE_IPC;
			break;
		case SDK_DEV_TYPE_DVR:
			strTemp = "JVT DVR";
			break;
		case SDK_DEV_TYPE_HVR:
			strTemp = "JVT HVR";
			nDeviceType = SDK_DEV_TYPE_HVR;
			break;
		case SDK_DEV_TYPE_NVR:
			strTemp = "JVT NVR";
			nDeviceType = SDK_DEV_TYPE_NVR;
			break;
		default:
			strTemp = "JVT IP Camera";
			nDeviceType = SDK_DEV_TYPE_IPC;
			break;
		}
		pQTItem = ui.tableWidget_Eq->item(i, 2);
		if (!pQTItem)
		{
			pQTItem = m_listWidget.at(i * SEARCH_COLUMN_COUNT + 2);
			if (pQTItem)
			{
				ui.tableWidget_Eq->setItem(i, 2, pQTItem);
			}
		}
		pQTItem->setText(strTemp);

		strTemp = QString("%1").arg(m_Device[i].TCPPort);
		pQTItem = ui.tableWidget_Eq->item(i, 3);
		if (!pQTItem)
		{
			pQTItem = m_listWidget.at(i * SEARCH_COLUMN_COUNT + 3);
			if (pQTItem)
			{
				ui.tableWidget_Eq->setItem(i, 3, pQTItem);
			}
		}
		pQTItem->setText(strTemp);

		strTemp = QString("%1").arg(m_Device[i].sMac);
		pQTItem = ui.tableWidget_Eq->item(i, 4);
		if (!pQTItem)
		{
			pQTItem = m_listWidget.at(i * SEARCH_COLUMN_COUNT + 4);
			if (pQTItem)
			{
				ui.tableWidget_Eq->setItem(i, 4, pQTItem);
			}
		}
		pQTItem->setText(strTemp);

		strTemp = QString("%1").arg(m_Device[i].ChannelNum);
		pQTItem = ui.tableWidget_Eq->item(i, 5);
		if (!pQTItem)
		{
			pQTItem = m_listWidget.at(i * SEARCH_COLUMN_COUNT + 5);
			if (pQTItem)
			{
				ui.tableWidget_Eq->setItem(i, 5, pQTItem);
			}
		}
		pQTItem->setText(strTemp);
		
		strTemp = QString("%1").arg(m_Device[i].DeviceType);
		pQTItem = ui.tableWidget_Eq->item(i, 6);
		if (!pQTItem)
		{
			pQTItem = m_listWidget.at(i * SEARCH_COLUMN_COUNT + 6);
			if (pQTItem)
			{
				ui.tableWidget_Eq->setItem(i, 6, pQTItem);
			}
		}
		pQTItem->setText(strTemp);

	}
	ui.btnSearch->setEnabled(true);
	ui.tableWidget_Eq->setSortingEnabled(true);
	ui.label_Displayonline->setText(QObject::tr("在线设备:%1").arg(m_lDevNum));
}

void equimentMgt::CreateWidget()
{
	if (m_listWidget.size() > 0)
	{
		return;
	}
	QTableWidgetItem* pWidget = NULL;
	int nItem = SEARCH_COLUMN_COUNT * SEARCH_ROW_COUNT;
	for (int i = 0; i < nItem; i ++)
	{
		pWidget = new QTableWidgetItem("");
		if (pWidget)
		{
			m_listWidget.append(pWidget);
		}
	}	
}

void equimentMgt::ClearWidget()
{
	QTableWidgetItem* pWidget = NULL;
	int nItem = m_listWidget.size();
	for (int i = 0; i < nItem; i++)
	{
		pWidget = m_listWidget.at(i);
		if (pWidget)
		{
			delete pWidget;
			pWidget = NULL;
		}
	}
	m_listWidget.clear();
}
//添加设备
void equimentMgt::on_btnAdd_clicked()
{
	AddDeviceInfo(FALSE);
}

void equimentMgt::on_btnAddall_clicked()
{
	AddDeviceInfo(TRUE);
}

int equimentMgt::AddDeviceInfo(BOOL bAll)
{
	int nDevNum = 0;
	if (m_lDevNum <= 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("列表中没有设备!"));
		return nDevNum;
	}
	int nType = SDK_DEV_TYPE_IPC;
	int nCompany = DEVINFO_MANUFACTURER_JL_NEW;
	int channelNum = 0;
	int nSubType = SDK_DEV_TYPE_BSIPC;
	TabDevInfo_t* pDevInfo = NULL;
	TabChannelInfo_t* pChannelInfo = NULL;
	QString str = NULL;
	QByteArray bArray;

	for (int i = 0; i < m_lDevNum; i++)
	{
		if (ui.tableWidget_Eq->item(i, 2)->text() == "JVT NVR")
		{
			nType = SDK_DEV_TYPE_NVR;
			nSubType = SDK_DEV_TYPE_BSIPC;
		}
		else if (ui.tableWidget_Eq->item(i, 2)->text() == "JVT IP Camera")
		{
			nType = SDK_DEV_TYPE_IPC;
			nSubType = ui.tableWidget_Eq->item(i, 6)->text().toInt();
		}

		if ((ui.tableWidget_Eq->item(i, 0)->checkState() && !bAll) || bAll)
		{
			pDevInfo = new TabDevInfo_t;
			memset(pDevInfo, 0, sizeof(TabDevInfo_t));
			pDevInfo->nType = nType;
			pDevInfo->nSubDevType = nSubType;

			str = ui.tableWidget_Eq->item(i, 1)->text();
			bArray = str.toLatin1();
			memcpy(pDevInfo->szIpAddr, bArray.data(), bArray.size());

			pDevInfo->nPort = ui.tableWidget_Eq->item(i, 3)->text().toInt();

			str = ui.lineEdit_Usr->text();
			bArray = str.toLatin1();
			memcpy(pDevInfo->szLoginName, bArray.data(), bArray.size());

			str = ui.lineEdit_Pwd->text();
			bArray = str.toLatin1();
			memcpy(pDevInfo->szPassword, bArray.data(), bArray.size());

			str = ui.tableWidget_Eq->item(i, 1)->text();
			bArray = str.toLatin1();
			memcpy(pDevInfo->szDevName, bArray.data(), bArray.size());

			str = ui.tableWidget_Eq->item(i, 2)->text();
			bArray = str.toLatin1();
			memcpy(pDevInfo->szDevType, bArray.data(), bArray.size());

			pDevInfo->nSubDevType = ui.tableWidget_Eq->item(i, 6)->text().toInt();
			if (strlen(pDevInfo->szDevName) == 0 || strlen(pDevInfo->szIpAddr) == 0)
			{
				myHelper::ShowMessageBoxWarning(QObject::tr("地址信息不能为空"));
				continue;
			}
			bool ret = g_pDatabase->AddDevice(pDevInfo);
			if (!ret)
			{
				myHelper::ShowMessageBoxWarning(QObject::tr("设备%1已经存在").arg(ui.tableWidget_Eq->item(i, 1)->text()));
				continue;
			}
			int DevId = g_pDatabase->getDeviceID(pDevInfo->szIpAddr);
			pDevInfo->nDevId = DevId;
			g_vectorDevInfo.push_back(pDevInfo);

			channelNum = ui.tableWidget_Eq->item(i, 5)->text().toInt();
			for (int j = 0; j < channelNum; j++)
			{
				pChannelInfo = new TabChannelInfo_t;
				memset(pChannelInfo, 0, sizeof(TabChannelInfo_t));
				pChannelInfo->DevId = pDevInfo->nDevId;
				pChannelInfo->Channel = j + 1;
				sprintf(pChannelInfo->szChannelName, "ch%02d", j + 1);
				pChannelInfo->Type = nSubType;
				pChannelInfo->Status = CHANNELINFO_STATUS_OPEN;
				
				if (!g_pDatabase->AddChannelInfo(pChannelInfo))
				{
					myHelper::ShowMessageBoxWarning(QObject::tr("channelinfo信息插入到插入到数据库失败!").arg(pChannelInfo->szChannelName));
					continue;
				}
				pChannelInfo->SlaveDevId = g_pDatabase->GetChannelID(pChannelInfo->DevId, pChannelInfo->Channel);
				g_vectorChannelInfo.push_back(pChannelInfo);
			}
			g_pInstance->AddDevice(pDevInfo);
			nDevNum++;
		}
	}

	if (nDevNum > 0)
	{
		if (g_pInstance->m_TabWidget.m_bPreview != FALSE)
		{
			g_pInstance->m_pPreviewPro->StopAllWatch();
		}

		g_pInstance->OnReFreshOtherTree();
	}
	else if (nDevNum == 0 && !bAll)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择要添加的设备!"));
	}
	return nDevNum;
}

void equimentMgt::on_btnRefresh_clicked()
{
	//设置模型
	if (!m_pModel_manage)
	{
		m_pModel_manage = new QSqlTableModel(this, g_pDatabase->getDB());
	}
	m_pModel_manage->setTable("DevInfo");
	//把model放在view
	ui.tableView_manage->setModel(m_pModel_manage);

	//model显示数据
	m_pModel_manage->select();
	m_pModel_manage->setHeaderData(1,Qt::Horizontal,QObject::tr("IP"));
	m_pModel_manage->setHeaderData(5,Qt::Horizontal,QObject::tr("设备名"));
	
	m_pModel_manage->setEditStrategy(QSqlTableModel::OnManualSubmit);
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
	ui.label_manage->setText(QObject::tr("管理设备:%1").arg(m_pModel_manage->rowCount()));
}

void equimentMgt::on_btnDel_clicked()
{
	if (m_pModel_manage->rowCount() == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("管理的设备为空"));
		return;
	}
	if (myHelper::ShowMessageBoxQuesion(QObject::tr("确定删除设备吗?")) != 1)
		return;

	if (g_pInstance->m_TabWidget.m_bPreview != FALSE)
	{
		g_pInstance->m_pPreviewPro->StopAllWatch();
	}
	int curRow = ui.tableView_manage->currentIndex().row();//选中行
	QAbstractItemModel *modessl = ui.tableView_manage->model();

	QModelIndex indextemp = modessl->index(curRow,0);//遍历第一行的所有列
	QVariant datatemp = modessl->data(indextemp);
	int  nDevId = datatemp.toInt();
	bool ret = g_pDatabase->DelChannelInfo(nDevId);
	if (ret)
	{
		g_pInstance->DeleteDevice(nDevId);
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("删除设备失败!"));
	}
	
	g_pInstance->OnReFreshOtherTree();
}

void equimentMgt::slotRowDoubleClicked()
{
	ui.btnDel->setEnabled(true);
	m_bClicked = true;
}

//清空
void equimentMgt::on_btnClear_clicked()
{
	if (m_pModel_manage->rowCount() == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("管理的设备为空"));
		return;
	}

	if (myHelper::ShowMessageBoxQuesion(QObject::tr("确定删除所有设备吗?")) == 1)
	{
		if (g_pInstance->m_TabWidget.m_bPreview != FALSE)
		{
			g_pInstance->m_pPreviewPro->StopAllWatch();
		}
		g_pDatabase->delAllDevInfo();
		m_pTreeDev->DestroyData(TRUE);
		g_pInstance->OnReFreshOtherTree();
	}
}

void equimentMgt::on_btnaddEq_clicked()
{
	if (!m_pAddDev)
	{
		m_pAddDev = new AddDevice();
	}
	m_pAddDev->show();	
}

void equimentMgt::on_btnModify_clicked()
{
	if (m_pModel_manage->rowCount() == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("管理的设备为空"));
		return;
	}

	if (m_bClicked == false)
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("没有选中设备"));
		myHelper::ShowMessageBoxWarning(QObject::tr("没有选中设备!"));
		return;
	}

	int curRow = ui.tableView_manage->currentIndex().row();//选中行
	QAbstractItemModel *modessl = ui.tableView_manage->model();

	QModelIndex indextemp = modessl->index(curRow, 0);//遍历第一行的所有列
	QVariant datatemp = modessl->data(indextemp);
	int  nDevId = datatemp.toInt();

	indextemp = modessl->index(curRow, 1);//遍历第一行的所有列
	datatemp = modessl->data(indextemp);
	QString strIpAddr = datatemp.toString();

	g_pInstance->ModifyDev(strIpAddr.toLatin1().data());
}

void equimentMgt::on_checkBox_stateChanged(int state)
{
	if (state == Qt::Checked) // "选中"
	{
		m_pTimerSignal->start(1000*60);
	}
	else if(state == Qt::Unchecked) // "半选"
	{
		m_pTimerSignal->stop();
	}	
}

void equimentMgt::on_btnSearchIP_clicked()
{
	ui.treeWidget->collapseAll();
	QString txt = ui.lineEdit_Search->text();
	bool isEmptyTxt = txt.isEmpty();
	bool isEmptyTree = ui.treeWidget->topLevelItemCount(); //非零个为true
	if (isEmptyTxt) {
		QTreeWidgetItemIterator it(ui.treeWidget);
		while (*it) {
			(*it)->setBackground(0, m_pTreeDev->m_itemBrush);
			it++;
		}
		return;
	}
	if (!isEmptyTree) { return; }

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
			m_pTreeDev->parentExpand(*it);
		}
		else{
			(*it)->setBackground(0, m_pTreeDev->m_itemBrush);
		}
		it++;
	}
}

bool equimentMgt::event(QEvent *e)
{
	CompareEvent *event = static_cast<CompareEvent *>(e);

	if (e->type() == static_cast <QEvent::Type>(CET_DEVMNG_UPDATELIST))
	{
		SDK_CONFIG_NET_COMMON_V2* pDevice = (SDK_CONFIG_NET_COMMON_V2*)event->getItem();
		DisplaySearchDevice(pDevice);
	}	
	return QWidget::event(event);
}
