#define  _CRT_SECURE_NO_WARNINGS
#include "comparerecord.h"
#include <QVariant>
#include <QMessageBox>
#include <QMutex>
#include <QDateTime>
#include <QDebug>
#include <stdlib.h>
#include <stdio.h>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include "Device/JLNDevice.h"
#include "CompareEvent.h"
#include <QAxObject>
#include <QDesktopServices>
#include <QDir>
#include "myhelper.h"
#include <QObject>
#include <QCoreApplication>
#include "ExcelImport.h"
#include <QVariant>
#include "client.h"

#define PAGE_NUM   50
#define MAX_PLAYBACK_VIEW	8 * 4
#define MAX_PAGE_COLUMN		8
#define MAX_PAGE_ROW		4

#define MAX_READ_COMPARE_NUMBER		10000	//每次最多读10000条比对数据
extern Client* g_pInstance;

QMutex compare_mutex;

CompareRecord::CompareRecord(QWidget *parent)
	: QWidget(parent)
	, m_pBufferIndex(NULL)
	, m_pchIndexBuf(NULL)
	, m_nFinishedNum(0)
{
	ui.setupUi(this);

	initDisplay();
	initExportWidget();
	initImportWidget();
	initCompareWidget();
	initAttendance();
	initSearchButton();
	m_nCheckNum = 0;
	m_iChannel = 0;
	m_iPage = 0;
    m_iPageCount = 0;
	m_pTreeData = NULL;

	ui.dateEdit->setDisplayFormat("yyyy-MM-dd");
	ui.dateEdit->setDateTime(QDateTime::currentDateTime());
	
	ui.dateTimeEdit_BeginAtd->setDisplayFormat("yyyy-MM-dd");
	ui.dateTimeEdit_EndAtd->setDisplayFormat("yyyy-MM-dd");

	ui.treeWidget->setHeaderHidden(true);
	ui.checkBox_Export->setChecked(true);
	
	m_bShowGroup = FALSE; 
	m_bSelectAll = FALSE;

	itemTemp = NULL;
	m_bShowInformation = TRUE;
	m_bOperating = FALSE;
}

CompareRecord::~CompareRecord()
{
	if (m_pchIndexBuf)
	{
		delete m_pchIndexBuf;
		m_pchIndexBuf = NULL;
	}

}

void CompareRecord::initSearchButton()
{
	QPushButton *pSearchButton = new QPushButton(this);

	pSearchButton->setCursor(Qt::PointingHandCursor);
	pSearchButton->setFixedSize(22, 22);
	pSearchButton->setToolTip(QObject::tr("搜索"));
	pSearchButton->setStyleSheet("QPushButton{border-image:url(:/res/SoftIcon/icon_search_normal.png); background:transparent;} \
								QPushButton:hover{border-image:url(:/res/SoftIcon/icon_search_hover.png)} \
								QPushButton:pressed{border-image:url(:/res/SoftIcon/icon_search_press.png)}");
	QMargins margins = ui.lineEdit_Search->textMargins();
	ui.lineEdit_Search->setTextMargins(margins.left(), margins.top(), pSearchButton->width(), margins.bottom());
	ui.lineEdit_Search->setPlaceholderText(QObject::tr("请输入搜索内容"));

	QHBoxLayout *pSearchLayout = new QHBoxLayout();
	pSearchLayout->addStretch();
	pSearchLayout->addWidget(pSearchButton);
	pSearchLayout->setSpacing(0);
	pSearchLayout->setContentsMargins(0, 0, 0, 0);
	ui.lineEdit_Search->setLayout(pSearchLayout);
	connect(pSearchButton, SIGNAL(clicked(bool)), this, SLOT(on_btnSearchIP_clicked()));
}

void CompareRecord::initAttendance()
{
	QStringList header;
	ui.tableWidget_Atd->setColumnCount(9);
	m_nType = ui.comboBox_Attend->currentIndex();
	header << QObject::tr("头像") << QObject::tr("序号") << QObject::tr("姓名") << QObject::tr("编号") << QObject::tr("考勤时间") << QObject::tr("上班状态") << QObject::tr("上班时间") << QObject::tr("下班状态") << QObject::tr("下班时间");
		
	ui.tableWidget_Atd->setHorizontalHeaderLabels(header);
	ui.tableWidget_Atd->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
	ui.tableWidget_Atd->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.tableWidget_Atd->setSortingEnabled(true);
	ui.tableWidget_Atd->horizontalHeader()->setStretchLastSection(true); //就是这个地方
	ui.tableWidget_Atd->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽
	//ui.tableWidget_Atd->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应行高
	
	ui.dateTimeEdit_BeginAtd->setDateTime(QDateTime::currentDateTime());
	ui.dateTimeEdit_EndAtd->setDateTime(QDateTime::currentDateTime());

	ui.lineEdit_Attend->setText(QString::number(0));
	m_nType = 0;
	attend_bQueryStat = false;
	m_pAttendInfo = new SDK_SMART_WB_CONFIG_EX;
	memset(m_pAttendInfo, 0, sizeof(SDK_SMART_WB_CONFIG_EX));
}
bool CompareRecord::GetDevInfo()
{
	return true;
}
void CompareRecord::initCompareWidget()
{
	QStringList header;
	ui.tableWidget->setColumnCount(8);

	header << QObject::tr("库图片") << QObject::tr("抓拍图片") << QObject::tr("姓名") << QObject::tr("编号") 
		<< QObject::tr("名单") << QObject::tr("温度") << QObject::tr("时间") << QObject::tr("详细内容");
	ui.tableWidget->setHorizontalHeaderLabels(header);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.tableWidget->setSortingEnabled(true);
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽
	ui.tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应行高
	
	//设置自动获取系统时间
	QString strBuffer = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	strBuffer = strBuffer.left(11) + "00:00:00";
	QDateTime time = QDateTime::fromString(strBuffer, "yyyy-MM-dd hh:mm:ss");
	ui.dateEdit_RecordBegin->setDateTime(time);
	ui.timeEdit_RecordBegin->setDateTime(time);

	strBuffer = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	strBuffer = strBuffer.left(11) + "23:59:59";
	time = QDateTime::fromString(strBuffer, "yyyy-MM-dd hh:mm:ss");
	ui.dateEdit_RecordEnd->setDateTime(time);
	ui.timeEdit_RecordEnd->setDateTime(time);

	m_bQueryStat = FALSE;
	m_nTotalCount = 0;
}

void CompareRecord::OnTreeReFresh()
{
	m_listTreeData.clear();
	m_pTreeData = NULL;
	ui.treeWidget->clear();
	m_pTreeDev->ShowTreebyType(ui.treeWidget, TRUE);
}

void CompareRecord::initExportWidget()
{
	QStringList header;
	QStringList header_export;
	ui.tableWidget_Export->setColumnCount(7);

	header << QObject::tr("序号") << QObject::tr("图片名称") << QObject::tr("图片索引编号") << QObject::tr("库编号") 
		<<QObject::tr("是否使用")<< QObject::tr("校验码") <<QObject::tr("状态");
	ui.tableWidget_Export->setHorizontalHeaderLabels(header);
	ui.tableWidget_Export->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
	ui.tableWidget_Export->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.tableWidget_Export->setSortingEnabled(true);
	ui.tableWidget_Export->horizontalHeader()->setStretchLastSection(true); //就是这个地方
	ui.tableWidget_Export->setColumnHidden(4, true);
	ui.tableWidget_Export->setColumnHidden(5, true);
	
	connect(ui.tableWidget_Export,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(ExImageinfo(int,int)));


	nCount = 0;
	on_checkBox_White_clicked();
	m_bExport = FALSE;
	m_bBrowse = FALSE;
	downedPath = "D:\\Download";
	ui.lineEdit_downed->setText(downedPath);

	ui.tableWidget_exportView->setColumnCount(2);
	header_export <<QObject::tr("时间")<<QObject::tr("信息");
	ui.tableWidget_exportView->setHorizontalHeaderLabels(header_export);
	ui.tableWidget_exportView->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
	ui.tableWidget_exportView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.tableWidget_exportView->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_exportView->setColumnWidth(0, 180);

	connect(ui.checkBox_All, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));
}

void CompareRecord::initImportWidget()
{
	QStringList header_export;

	m_bImporting = FALSE;
	on_checkBox_Whilte_Import_clicked();

	ui.tableWidget_InPortview->setColumnCount(INPORT_COLUMN_COUNT);
	ui.tableWidget_InPortview->setRowCount(INPORT_ROW_COUNT);
	header_export << QObject::tr("设备名称") << QObject::tr("上传进度") << QObject::tr("状态");
	ui.tableWidget_InPortview->setHorizontalHeaderLabels(header_export);
	ui.tableWidget_InPortview->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
	ui.tableWidget_InPortview->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.tableWidget_InPortview->horizontalHeader()->setStretchLastSection(true);

	//m_bImport = FALSE;
	importMode = 0;
}

void CompareRecord::DisplyFaceExport(SDK_FILEINDEX_INFO *PCofig)
{
	if (PCofig == NULL)
	{
		return;
	}
	
	static int i = 0;
	ui.tableWidget_exportView->setItem(0,0,new QTableWidgetItem(i));
	ui.tableWidget_exportView->setItem(0,1,new QTableWidgetItem(PCofig->name));
	i++;
}
void CompareRecord::initDisplay()
{
	m_listVideoLab.append(ui.labVideo1);
	m_listVideoLab.append(ui.labVideo2);
	m_listVideoLab.append(ui.labVideo3);
	m_listVideoLab.append(ui.labVideo4);
	m_listVideoLab.append(ui.labVideo5);
	m_listVideoLab.append(ui.labVideo6);
	m_listVideoLab.append(ui.labVideo7);
	m_listVideoLab.append(ui.labVideo8);
	m_listVideoLab.append(ui.labVideo9);
	m_listVideoLab.append(ui.labVideo10);
	m_listVideoLab.append(ui.labVideo11);
	m_listVideoLab.append(ui.labVideo12);
	m_listVideoLab.append(ui.labVideo13);
	m_listVideoLab.append(ui.labVideo14);
	m_listVideoLab.append(ui.labVideo15);
	m_listVideoLab.append(ui.labVideo16);
	m_listVideoLab.append(ui.labVideo17);
	m_listVideoLab.append(ui.labVideo18);
	m_listVideoLab.append(ui.labVideo19);
	m_listVideoLab.append(ui.labVideo20);
	m_listVideoLab.append(ui.labVideo21);
	m_listVideoLab.append(ui.labVideo22);
	m_listVideoLab.append(ui.labVideo23);
	m_listVideoLab.append(ui.labVideo24);
	m_listVideoLab.append(ui.labVideo25);
	m_listVideoLab.append(ui.labVideo26);
	m_listVideoLab.append(ui.labVideo27);
	m_listVideoLab.append(ui.labVideo28);
	m_listVideoLab.append(ui.labVideo29);
	m_listVideoLab.append(ui.labVideo30);
	m_listVideoLab.append(ui.labVideo31);
	m_listVideoLab.append(ui.labVideo32);

	m_listTimeLab.append(ui.label_time1);
	m_listTimeLab.append(ui.label_time2);
	m_listTimeLab.append(ui.label_time3);
	m_listTimeLab.append(ui.label_time4);
	m_listTimeLab.append(ui.label_time5);
	m_listTimeLab.append(ui.label_time6);
	m_listTimeLab.append(ui.label_time7);
	m_listTimeLab.append(ui.label_time8);
	m_listTimeLab.append(ui.label_time9);
	m_listTimeLab.append(ui.label_time10);
	m_listTimeLab.append(ui.label_time11);
	m_listTimeLab.append(ui.label_time12);
	m_listTimeLab.append(ui.label_time13);
	m_listTimeLab.append(ui.label_time14);
	m_listTimeLab.append(ui.label_time15);
	m_listTimeLab.append(ui.label_time16);
	m_listTimeLab.append(ui.label_time17);
	m_listTimeLab.append(ui.label_time18);
	m_listTimeLab.append(ui.label_time19);
	m_listTimeLab.append(ui.label_time20);
	m_listTimeLab.append(ui.label_time21);
	m_listTimeLab.append(ui.label_time22);
	m_listTimeLab.append(ui.label_time23);
	m_listTimeLab.append(ui.label_time24);
	m_listTimeLab.append(ui.label_time25);
	m_listTimeLab.append(ui.label_time26);
	m_listTimeLab.append(ui.label_time27);
	m_listTimeLab.append(ui.label_time28);
	m_listTimeLab.append(ui.label_time29);
	m_listTimeLab.append(ui.label_time30);
	m_listTimeLab.append(ui.label_time31);
	m_listTimeLab.append(ui.label_time32);	

	CreateInportWidget();
}
void CompareRecord::initTree()
{
	ui.treeWidget->clear();
	
	m_pTreeDev->ShowTreebyType(ui.treeWidget, TRUE);		
	
	connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(slotItemClicked()));
}

void CompareRecord::on_btnSearch_clicked()
{
	if (m_vecFindResult.size()>0)
	{
		m_vecFindResult.clear();
	}
	int nType = 0;
	 m_TimeBegin = ui.timeEdit_Begin->text();
	 m_TimeEnd = ui.timeEdit_End->text();
	
	dataMsg = ui.dateEdit->text();
	QDateTime m_beginTime = QDateTime::fromString(m_TimeBegin, "hh:mm:ss");
	QDateTime m_endTime = QDateTime::fromString(m_TimeEnd, "hh:mm:ss");
	
	if (m_beginTime.secsTo(m_endTime)  < 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("开始时间不能大于结束时间!"));
		return;
	}

	if (m_pTreeData == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请点击树节点选择设备"));
		return;
	}

	SearchSnap(m_pTreeData->pDevObj->GetDevInfo()->szIpAddr, m_pTreeData->Channel - 1);
	
	SetChannel(m_pTreeData->Channel - 1);
	ShowSearchFile(0, m_pTreeData->Channel - 1);	//显示第一页
}

BOOL CompareRecord::SearchSnap(char* pchDevIP, int nChannel /* = 0 */)
{
	QString strDevIP = QString::fromStdString(pchDevIP);
	FILE* pFileIndex = NULL;	
	char szIndexFile[MAX_PATH] = {0};

	SYSTEMTIME sysStartTime = {0};
	SYSTEMTIME sysEndTime = {0};
	DWORD dwStartTime = 0;
	DWORD dwEndTime = 0;
	if (!m_pchIndexBuf)
	{
		m_pchIndexBuf = new char[MAX_READ_COMPARE_NUMBER * sizeof(SMART_FACE_CMP_QUERY_INFO)];
	}
	memset(m_pchIndexBuf, 0, MAX_READ_COMPARE_NUMBER * sizeof(SMART_FACE_CMP_QUERY_INFO));
	if (strDevIP.length() > 0)
	{
		sprintf_s(m_szSnapPath, "%s/%s/%s/%d", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szSnapPath,dataMsg.toLatin1().data(), strDevIP.toLatin1().data(), nChannel);
		sprintf_s(szIndexFile, "%s/index.ini", m_szSnapPath);
		pFileIndex = fopen(szIndexFile, "rb+");

		int nErr = GetLastError();
		int nOffSet = 0;
		BOOL bEnd = FALSE;
		int nPageNumber = 0;
		int nNumber = 0;
		SMART_FACE_CMP_QUERY_INFO stIndexInfo = { 0 };
		QString strTime;
		QString strPath;
		if(pFileIndex)                
		{
			compare_mutex.lock();
			while (!bEnd)
			{
				nNumber = fread(m_pchIndexBuf, sizeof(SMART_FACE_CMP_QUERY_INFO), MAX_READ_COMPARE_NUMBER, pFileIndex);
				if (nNumber > 0)
				{
					for (int i = 0; i < nNumber; i ++)
					{
						memcpy(&stIndexInfo, m_pchIndexBuf + i * sizeof(SMART_FACE_CMP_QUERY_INFO), sizeof(SMART_FACE_CMP_QUERY_INFO));
						strTime = QString::fromStdString((char*)stIndexInfo.sLibSnapTime);
						
						QString beginTime = dataMsg+" "+m_TimeBegin;
						QString endTime = dataMsg+" "+m_TimeEnd;
						strPath = QString::fromStdString(m_szSnapPath)+QString::fromStdString(stIndexInfo.sSnappicname);
						if (QString::compare(strTime,beginTime) > 0 &&QString::compare(strTime,endTime) < 0&&!strPath.isNull())
						{
							m_vecFindResult.insert(m_vecFindResult.begin(),stIndexInfo);
						}
					}
				}
				else
				{
					m_iPageCount = m_vecFindResult.size() / (MAX_PAGE_COLUMN * MAX_PAGE_ROW) + 1;
					break;
				}

				nOffSet += sizeof(SMART_FACE_CMP_QUERY_INFO)* nNumber;
				fseek(pFileIndex, nOffSet, 0);			
			}

			fclose(pFileIndex);
			compare_mutex.unlock();
		}
	}
	return true;
}
void CompareRecord::ShowSearchFile(int iPage, int nChannel /* = 0 */)
{
	SMART_FACE_CMP_QUERY_INFO* pstFAResult = NULL;
	m_iPage = iPage + 1;	
	char chTime[16] = {0};
	char cpicName[MAX_PATH] = {0};
	QString strPath;
	QString strTime;
	QString strIP;
	SetPageInfo(m_iPage,m_iPageCount);

	compare_mutex.lock();
	int nMaxNum = MAX_PAGE_COLUMN * MAX_PAGE_ROW;
	int nResultSize = m_vecFindResult.size();
	int nCurNumber = iPage * nMaxNum;
	for (int i = 0; i < nMaxNum; i ++)
	{
		if (nResultSize > nCurNumber) 
		{
			pstFAResult = &m_vecFindResult.at(nCurNumber);
			if (pstFAResult)
			{				
				strIP = QString::fromStdString((char*)pstFAResult->cDevName);
				memcpy(chTime, pstFAResult->sLibSnapTime, 10);
				
				sprintf(m_szSnapPath, "%s\\%s\\%s\\%d", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szSnapPath, chTime, strIP.toLatin1().data(), nChannel);
				sprintf(cpicName, "%s\\%s", m_szSnapPath, (char*)pstFAResult->sSnappicname);
				strPath = QString(QLatin1String(cpicName));
				strTime = QString::fromStdString((char*)pstFAResult->sLibSnapTime);
				ShowPicture(strPath, strTime,i);
			}
		}
		else
		{
			break;
		}

		nCurNumber++;
	}
	compare_mutex.unlock();
}


void CompareRecord::treeItemChanged(QTreeWidgetItem *item,int column)
{
	QTreeWidgetItem *parent = item->parent();
	if (parent == NULL){
		return;
	}
	int childCount = parent->childCount();
	for (int i = 0; i < childCount; i++)
	{
		QTreeWidgetItem *childItem = parent->child(i);
		if (childItem->checkState(0) == Qt::Checked)
		{
			QVariant var = item->data(i,Qt::UserRole);
			TreeData_t* pChannel = (TreeData_t *)var.value<void *>();
			if (itemTemp != NULL)
			{
				itemTemp->setCheckState(0, Qt::Unchecked);
			}
		
			itemTemp = item;
			m_pTreeData = pChannel;
			if (m_pTreeData == NULL)
			{
				return;
			}
			m_nCheckNum ++;
		}		
	}
}


void CompareRecord::SetChannel(int iChannel)
{
	m_iChannel = iChannel;
}

void CompareRecord::SetPageInfo(int iPage, int iPageCount)
{
	m_iPage = iPage;
	m_iPageCount = iPageCount;
	ShowPageInfo();
}

void CompareRecord::ShowPageInfo()
{
	ui.lineEdit_page->setText(QString::number(m_iPage));
	ui.label_page->setText(QString::number(m_iPageCount));
}

void CompareRecord::ShowPicture(QString strPath, QString strPicTime,int i)
{
	m_Image.load(strPath);
	if (!m_Image.isNull())
	{
		m_Image.scaled(ui.labVideo1->size(), Qt::KeepAspectRatio);

		m_listVideoLab[i]->setScaledContents(true);
		m_listVideoLab[i]->resize(QSize(m_Image.width(), m_Image.height()));
		m_listVideoLab[i]->setMinimumSize(120, 136);
		m_listVideoLab[i]->setPixmap(QPixmap::fromImage(m_Image));
		m_listTimeLab[i]->setText(strPicTime);
	}
}

void CompareRecord::on_btnPrepage_clicked()
{
	int m_page = ui.lineEdit_page->text().toInt();
	if (m_page <= m_iPageCount &&m_page > 1)
	{
		ShowSearchFile(m_page-2, m_iChannel);
	}
}

void CompareRecord::on_btnNextpage_clicked()
{
	 int m_page = ui.lineEdit_page->text().toInt();
	if (m_page < m_iPageCount &&m_page >= 0)
	{
		ShowSearchFile(m_page, m_iChannel);
	}
}

void CompareRecord::on_btnJump_clicked()
{
	int m_page = ui.lineEdit_page->text().toInt()-1;
	if (m_page < m_iPageCount &&m_page >= 0)
	{
		ShowSearchFile(m_page, m_iChannel);
	}
}

void CompareRecord::on_btnSearchRecord_clicked()
{
	m_nPageCount = 1;
	ShowPageInfoRecord(0);
	m_bQueryStat = TRUE;
	clearCurrAge(ui.tableWidget);

	std::vector<SMART_FACE_CMP_QUERY_INFO*> ::iterator iter;
	if (m_vectorListinfo.size() != 0)
	{
		for (iter = m_vectorListinfo.begin();  iter != m_vectorListinfo.end(); ++iter)
		{
			if (*iter != NULL)
			{
				delete *iter;
				*iter = NULL;
			}
		}
		m_vectorListinfo.clear();
	}
	
	memset(&m_stFindInfo, 0, sizeof(FS_FIND_INFO));
	if (!GetFindInfo(&m_stFindInfo))
	{
		return;
	}
	
	CreateThread(NULL, 0, RQueryThread, this, 0, NULL);
}

DWORD CompareRecord::RQueryThread(LPVOID lPvoid)
{
	CompareRecord *pDlg = (CompareRecord *)lPvoid;
	pDlg->BeginSearch(FLAG_SEARCH_FIRST,1);
	return 0;
}
void CompareRecord::ShowPageInfoRecord(int nPage)
{
	m_nCurPage = nPage;
	ui.lineEdit_CurPage->setText(QString::number(m_nCurPage));
	ui.label_Countpage->setText(QString::number(m_nPageCount));
}

int CompareRecord::BeginSearch(int nFlag, int nPage)
{
	nSourceType = ui.comboBox_query->currentIndex();
	if (nSourceType == 1)
	{
		SearchRecord();
	}
	else
	{
		m_nTotalCount = g_pDatabase->QueryComparison(&m_stFindInfo,m_vectorListinfo);
		if (m_nTotalCount > 0)
		{
			m_nPageCount = (m_nTotalCount / FACE_CMPWEB_PAGENUM) + ((m_nTotalCount % FACE_CMPWEB_PAGENUM) ? 1 : 0);
			if (nFlag == FLAG_SEARCH_FIRST)
			{
				ShowPageInfoRecord(1);
			}
			
			CompareEvent *custevent = new CompareEvent(CET_COMPARISON);
			custevent->setId(1);
			QApplication::postEvent(this,custevent);
			
		}
	}
	return m_nTotalCount;
}

void CompareRecord::SearchRecord()
{
	QString strPageCount;
	BOOL bRet = FALSE;
	JVT_LONG lImExID = 0;
	while(m_bQueryStat)
	{
		if (m_pTreeData->pDevObj->m_lUserLoginID > 0)
		{
			lImExID = m_pTreeData->pDevObj->StartImportAndExport(m_pTreeData->pDevObj->m_lUserLoginID);
		}
		else
		{
			CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
			custevent->setId(3);
			QApplication::postEvent(this, custevent);
			m_bQueryStat = false;
			return;
		}

		if (m_pTreeData->pDevObj->m_lImExID > 0)
		{	
			bRet = m_pTreeData->pDevObj->ProcessListManage(&m_stSmartConfig);
			if (bRet)
			{
				if(::WaitForSingleObject(m_pTreeData->pDevObj->m_hImportWaitEvent, 10000) != WAIT_OBJECT_0)
				{
					m_bQueryStat = false;
					EnterCriticalSection(&m_CriticalSection);
					m_vectorListinfo.clear();
					LeaveCriticalSection(&m_CriticalSection);
					CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
					custevent->setId(2);
					QApplication::postEvent(this, custevent);
					break;
				}
				if (m_nPageCount == 1)
				{
					m_nPageCount = m_stSmartConfig.stCmpInfo.iTotalCount / FACE_CMPWEB_PAGENUM + ((m_stSmartConfig.stCmpInfo.iTotalCount % FACE_CMPWEB_PAGENUM) ? 1:0);
					strPageCount = QString("%1").arg(m_nPageCount);
				}
				if (m_nCurPage <= m_nPageCount)
				{
					m_stSmartConfig.stCmpInfo.iQueryOrPaged = 2;
					m_nCurPage ++;
					m_stSmartConfig.stCmpInfo.iPage = m_nCurPage;
				}
				if (m_nCurPage > m_nPageCount)
				{
					m_bQueryStat = false;
					ShowPageInfoRecord(1);
				}
				ShowPageInfoRecord(m_nPageCount);
			}
			else
			{
				m_bQueryStat = false;
				//QMessageBox::information(this,QObject::tr("警告"),QObject::tr("查询失败!"));
				//myHelper::ShowMessageBoxWarning(QObject::tr("查询失败!"));
				CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
				custevent->setId(1);
				QApplication::postEvent(this, custevent);
			}
		}
		else
		{
			m_bQueryStat = false;
		}
	}
}
BOOL CompareRecord::GetFindInfo(FS_FIND_INFO* pFsFindInfo)
{
	QString strTemp = ""; 
	int nlength = 0;

	QDate DataBegin = ui.dateEdit_RecordBegin->date();
	QDate DataEnd = ui.dateEdit_RecordEnd->date();
	QTime TimeBegin = ui.timeEdit_RecordBegin->time();
	QTime TimeEnd = ui.timeEdit_RecordEnd->time();

	sprintf(pFsFindInfo->StartTime, "%04d-%02d-%02d %02d:%02d:00", DataBegin.year(), DataBegin.month(), DataBegin.day(), TimeBegin.hour(), TimeBegin.minute());
	sprintf(pFsFindInfo->EndTime, "%04d-%02d-%02d %02d:%02d:59", DataEnd.year(), DataEnd.month(), DataEnd.day(), TimeEnd.hour(), TimeEnd.minute());
	if (QString::compare(pFsFindInfo->StartTime, pFsFindInfo->EndTime) > 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("开始时间不能大于结束时间!"));
		return FALSE;
	}
	TreeData_t* pTreeData = NULL;
	GetCheckedTree();
	int nSize = m_listTreeData.size();
	if (nSize == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请勾选设备!"));
		return FALSE;
	}

	strTemp = ui.lineEdit_RecordName->text();
	nlength = strTemp.length();
	if (nlength> 0 && nlength < 32)
	{	
		strcpy((char *)pFsFindInfo->name, strTemp.toLocal8Bit().data());
	}
	strTemp = ui.lineEdit_RecordNumber->text();
	nlength = strTemp.length();
	if (nlength > 0 && nlength < 32)
	{
		strcpy((char*)pFsFindInfo->number, strTemp.toLocal8Bit().data());
	}

	pFsFindInfo->Wbmode = ui.comboBox->currentIndex();
	pFsFindInfo->pagecount = FACE_CMPWEB_PAGENUM;

	for (int i = 0; i < nSize; i ++)
	{
		pTreeData = m_listTreeData.at(i);
		memcpy(pFsFindInfo->fsDevInfo[i].cDeviceIP, pTreeData->pDevObj->m_pDevInfo->szIpAddr, 
			strlen(pTreeData->pDevObj->m_pDevInfo->szIpAddr));
	}

	pFsFindInfo->nDevNumber = nSize;
	pFsFindInfo->flag = FLAG_SEARCH_EXPORT;
	pFsFindInfo->curpage = 1;
	return TRUE;
}

void CompareRecord::on_btnExportIndex_clicked()
{
	if (m_bOperating)
		return;

	int nRet = 0;
	clearCurrAge(ui.tableWidget_Export);
	compare_mutex.lock();
	m_vectorFileInfo.clear();
	compare_mutex.unlock();
	m_bSelectAll = FALSE;
	if (m_pBufferIndex)
	{
		delete[] m_pBufferIndex;
		m_pBufferIndex = NULL;
	}

	if (m_pTreeData == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请点击树节点选择设备!"));
		return;
	}
	if (m_pTreeData->pDevObj->m_lUserLoginID > 0)
	{		
		m_pTreeData->pDevObj->StartImportAndExport(m_pTreeData->pDevObj->m_lUserLoginID);
	}
	else
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("登录设备%1失败!").arg(m_pTreeData->pDevObj->m_pDevInfo->szIpAddr));
		return;
	}

	if (m_pTreeData->pDevObj->m_lImExID > 0)
	{
		memset(&m_stSmarkConfig, 0, sizeof(SDK_SMART_WB_CONFIG_EX));
		m_stSmarkConfig.iOpMode = OUT_INDEX;
		m_stSmarkConfig.iWbmode = m_nOutputIndex;
		nRet = m_pTreeData->pDevObj->ProcessListManage(&m_stSmarkConfig);

		if (nRet <= 0)
		{
			int nRet = VideoNet_GetLastError();
			QString strLog = QObject::tr("导出索引失败:错误码'%1'").arg(nRet);
			//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("导出索引失败:错误码'%1'").arg(nRet));
			myHelper::ShowMessageBoxWarning(strLog);
			AddWBLogInfo(strLog);
		}
		else
		{
			AddWBLogInfo(QObject::tr("正在导出索引……"));
		}


		if (::WaitForSingleObject(m_pTreeData->pDevObj->m_hImportWaitEvent,2000)!=WAIT_OBJECT_0)
		{
			int nRet = VideoNet_GetLastError();
			QString strLog = QObject::tr("导出索引失败:错误码'%1'").arg(nRet);
			//QMessageBox::information(this,QObject::tr("警告"),QObject::tr("导出索引失败:错误码'%1'").arg(nRet));
			myHelper::ShowMessageBoxWarning(strLog);
			AddWBLogInfo(strLog);
		}
		AddWBLogInfo(QObject::tr("结束导出索引"));
	}

}

void CompareRecord::AddWBLogInfo(QString strLog)
{
	
	int RowCont=ui.tableWidget_exportView->rowCount();
	ui.tableWidget_exportView->insertRow(RowCont);//增加一行
	QDateTime local(QDateTime::currentDateTime());
	QString localTime = local.toString("yyyy-MM-dd:hh:mm:ss");
	ui.tableWidget_exportView->setItem(RowCont, 0, new QTableWidgetItem(localTime));
	ui.tableWidget_exportView->setItem(RowCont, 1, new QTableWidgetItem(strLog));
	//RowCont++;
}


void CompareRecord::FaceCallBack(long lSubFaceHandle, char *pBuffer,long lbufsize,SDK_FA_BLACKANDWHITELIST_CONFIG *pConfig,long dwUser)
{
	SDK_FA_BLACKANDWHITELIST_CONFIG *pCofig = pConfig;
	if (pCofig == NULL)
	{
		return;
	}
	if (OUT_INDEX == pCofig->byOutMode)
	{
		 nCount = pCofig->byAllNums;
		//clearCurrAge(ui.tableWidget_Export);
		for (int i = 0; i < nCount ;i++)
		{
			SDK_FILEINDEX_INFO *pInfo = (SDK_FILEINDEX_INFO *)(pBuffer + sizeof(SDK_FILEINDEX_INFO) * i);
		
			m_vectorFileInfo.push_back(*pInfo);
		}
	ExportIndex();
		
	}
	else if (OUT_PICTURE == pCofig->byOutMode)
	{
		char filename[256] = {0};
		QString strLogInfo;
		sprintf( filename, "%s\\%s",downedPath.toLocal8Bit().data(), pCofig->byFileName);
		if ((pCofig->byErrorCode == WB_OK) && (lbufsize > 0))
		{
		
			FILE *m_pFile = fopen(filename, "wb");
			if (m_pFile)
			{
				fwrite(pBuffer , 1,lbufsize,m_pFile);
				fclose(m_pFile);
				m_pFile = NULL;

				strLogInfo = QString::fromLocal8Bit(filename) + QObject::tr("下载成功");
				ShowPicRefresh(QString::fromLocal8Bit(filename));
			}
		}
		else
		{
			strLogInfo = QObject::tr("下载失败");
		}
		AddWBLogInfo(strLogInfo);
	}
	else if (IN_PICTURE_ADD_SNAP == pCofig->byOutMode || OUT_PICTURE_COMP == pCofig->byOutMode)
	{
		QString strLog;
		if ((pCofig->byErrorCode == WB_OK)&& (pBuffer != NULL) && (lbufsize > 0))
		{
			char *pFileBuf = new char[lbufsize];
			memcpy(pFileBuf,pBuffer,lbufsize);
			char filename[128] = {0};
			if (m_bBrowse)
			{				
				strcpy_s(filename,"C:\\00_00_00.jpg");
			} 
			else
			{
				sprintf_s( filename, "%s\\%s",downedPath.toLatin1().data(), pCofig->byFileName);
			}

			strLog = QObject::tr("下载图片") + filename;
			FILE * m_pFile = NULL;
			fopen_s(&m_pFile,filename,"wb");
			if (m_pFile)
			{
				fwrite(pFileBuf, 1,lbufsize ,m_pFile);
				fclose(m_pFile);
				m_pFile = NULL;

				if (pFileBuf != NULL)
				{
					delete pFileBuf;
					pFileBuf = NULL;
				}
				AddWBLogInfo(strLog);
			}
			else
			{
				strLog = QObject::tr("创建文件失败");
				AddWBLogInfo(strLog);
			}
		}
		else
		{
			if (pBuffer == NULL||lbufsize > 0)
			{
				strLog = QObject::tr("导出失败，请检查导出的黑白名单类型是否正确！");
			}
			AddWBLogInfo(strLog);
		}
	}
}

void CompareRecord::on_toolButton_clicked()
{
	downedPath = QFileDialog::getExistingDirectory(this, QObject::tr("请选择路径"), "/");
	if (!downedPath.isEmpty())
	{
		ui.lineEdit_downed->setText(downedPath);
	}
}

void CompareRecord::ShowPicRefresh(QString strPath)
{
	m_Image.load(strPath);
	m_Image.scaled(ui.displayImage->size(),Qt::KeepAspectRatio);
	ui.displayImage->setPixmap(QPixmap::fromImage(m_Image));
}

void CompareRecord::ShowPic_Import(QString strpath)
{
	m_Image.load(strpath);
	m_Image.scaled(ui.dilplay_Import->size(),Qt::KeepAspectRatio);
	ui.dilplay_Import->setPixmap(QPixmap::fromImage(m_Image));
}
void CompareRecord::ExImageinfo(int row,int column)
{
	QTableWidgetItem * item1 = NULL;
	char szFile[64] = { 0 };
	item1 = ui.tableWidget_Export->item(row,1);
	if (item1 == NULL)
	{
		return;
	}
	m_bBrowse = TRUE;
	QByteArray bArray;
	compare_mutex.lock();
	int nfileIndex = ui.tableWidget_Export->item(row,2)->text().toInt();
	QString pFile = ui.tableWidget_Export->item(row,1)->text();
	int nlibindex = ui.tableWidget_Export->item(row,3)->text().toInt();
	int nSysId = ui.tableWidget_Export->item(row, 5)->text().toInt();

	bArray = pFile.toLocal8Bit();
	memcpy(szFile, bArray.data(), bArray.size());
	nfileIndex;

	compare_mutex.unlock();

	memset(&m_stSmarkConfig, 0, sizeof(SDK_SMART_WB_CONFIG_EX));
	m_stSmarkConfig.iOpMode = OUT_PICTURE;
	m_stSmarkConfig.iWbmode = m_nOutputIndex;
	m_stSmarkConfig.iFileIndex = nfileIndex;
	m_stSmarkConfig.iSyslistID = nSysId;
	memcpy(m_stSmarkConfig.sUserID, szFile, strlen(szFile));

	m_pTreeData->pDevObj->ProcessListManage(&m_stSmarkConfig);	
}

void CompareRecord::on_checkBox_White_clicked()
{
	m_nOutputIndex = 2;
	ui.checkBox_White->setCheckState(Qt::Checked);
	ui.checkBox_Black->setCheckState(Qt::Unchecked);
	ui.checkBox_VIP->setCheckState(Qt::Unchecked);	
}

void CompareRecord::on_checkBox_Black_clicked()
{
	m_nOutputIndex = 1;
	ui.checkBox_White->setCheckState(Qt::Unchecked);
	ui.checkBox_Black->setCheckState(Qt::Checked);
	ui.checkBox_VIP->setCheckState(Qt::Unchecked);
}

void CompareRecord::on_checkBox_VIP_clicked()
{
	m_nOutputIndex = 3;
	ui.checkBox_White->setCheckState(Qt::Unchecked);
	ui.checkBox_Black->setCheckState(Qt::Unchecked);
	ui.checkBox_VIP->setCheckState(Qt::Checked);
}

void CompareRecord::on_checkBox_VIP_Import_clicked()
{
	m_bListMod = 3;
	ui.checkBox_Black_Import->setCheckState(Qt::Unchecked);
	ui.checkBox_VIP_Import->setCheckState(Qt::Checked);
	ui.checkBox_Whilte_Import->setCheckState(Qt::Unchecked);
}
void CompareRecord::on_checkBox_Black_Import_clicked()
{
	m_bListMod = 1;
	ui.checkBox_Black_Import->setCheckState(Qt::Checked);
	ui.checkBox_VIP_Import->setCheckState(Qt::Unchecked);
	ui.checkBox_Whilte_Import->setCheckState(Qt::Unchecked);
}
void CompareRecord::on_checkBox_Whilte_Import_clicked()
{
	m_bListMod = 2;
	ui.checkBox_Black_Import->setCheckState(Qt::Unchecked);
	ui.checkBox_VIP_Import->setCheckState(Qt::Unchecked);
	ui.checkBox_Whilte_Import->setCheckState(Qt::Checked);
}

void CompareRecord::onStateChanged(int state)
{
	for (int i = 0; i < ui.tableWidget_Export->rowCount(); i++)
	{
		if(state == Qt::Checked)
		{
			ui.tableWidget_Export->item(i,0)->setCheckState(Qt::Checked);
			m_bSelectAll = TRUE;
		}
		else 
		{
			ui.tableWidget_Export->item(i,0)->setCheckState(Qt::Unchecked);
			m_bSelectAll = FALSE;
		}
	}
}

void CompareRecord::on_btnSearchImage_clicked()
{
	ui.tableWidget_Export->setRowCount(0);
	ui.tableWidget_Export->clearContents();
	compare_mutex.lock();
	QString str = ui.lineEdit_PicName->text();
	QByteArray ba=str.toLocal8Bit();
	char *p = ba.data();
	int len =  m_vectorFileInfo.size();
	int num = 0;
	
	for (int i = 0;i< len;i++)
	{
		char *pstr = m_vectorFileInfo[i].name;
		if (isChildStr(pstr,p))
		{
			int rowcount = ui.tableWidget_Export->rowCount();
			ui.tableWidget_Export->insertRow(rowcount);//增加一行
			check = new QTableWidgetItem();
			check->setCheckState(Qt::Unchecked);

			ui.tableWidget_Export->setItem(rowcount, 0, check); //插入复选框
			ui.tableWidget_Export->setItem(rowcount, 1, new QTableWidgetItem(QString::fromLocal8Bit(m_vectorFileInfo[i].name)));
			ui.tableWidget_Export->setItem(rowcount, 2, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].findex.fileindex)));
			ui.tableWidget_Export->setItem(rowcount, 3, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].findex.libindex)));
			ui.tableWidget_Export->setItem(rowcount, 4, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].enable)));
			ui.tableWidget_Export->setItem(rowcount, 5, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].checksum)));

		}
	}
	
	compare_mutex.unlock();
}

bool CompareRecord::isChildStr(char *pstr,char *p)
{
	bool ret = false;
	char *dst = pstr;
	char *src = p;
	while(*dst != '\0' && *src != '\0')
	{
		if(*dst == *src)
		{
			src++;
		}
		else
		{
			src = p;
		}
		dst++;
	}
	if(*src == '\0')
	{
		ret = true;
	}
	return ret;
}

//void CompareRecord::AddCallBackMessage(char *pBuffer,long lbufsize,SDK_FA_BLACKANDWHITELIST_CONFIG *pParm)
//{
//
//}
//
//void CompareRecord::AddCallBackMessage(char* pBuffer, long lbufsize, SDK_SMART_WB_CONFIG_EX* pParam)
//{
//	QString chErr = NULL;
//	QString strLog = NULL;
//	GetResultCode(pParam->iErrorCode, chErr);
//	if (pParam->iErrorCode == WB_OK)
//	{
//		strLog = chErr;
//	}
//	else
//	{
//		strLog = QObject::tr("导入失败") + ":" + chErr;
//	}
//	AddWBLogInfo(strLog);
//
//}
void CompareRecord::on_btnDowned_clicked()
{
	DWORD dwThreadID = 0;
	HANDLE hThread = CreateThread(NULL, 0, DownLoadPictureThread, this, CREATE_SUSPENDED, &dwThreadID);
	if (hThread != NULL)
	{
		ResumeThread(hThread);//唤醒线程
		CloseHandle(hThread);//关闭线程句柄，线程并不会结束，便于回收资源
		hThread = NULL;
	}
	
}

DWORD WINAPI CompareRecord::DownLoadPictureThread(LPVOID lpParam)
{
	CompareRecord *pDlg = (CompareRecord  *)lpParam;
	pDlg->DownLoadPicturePro();
	return TRUE;
}

void CompareRecord::DownLoadPicturePro()
{
	for (int i = 0; i < nCount; i++)
	{
		if (ui.tableWidget_Export->item(i, 0)->checkState())
		{
			int nfileIndex = ui.tableWidget_Export->item(i, 2)->text().toInt();
			QString pFile = ui.tableWidget_Export->item(i, 1)->text();
			int nlibindex = ui.tableWidget_Export->item(i, 3)->text().toInt();
			int nSysId = ui.tableWidget_Export->item(i, 5)->text().toInt();

			memset(&m_stSmarkConfig, 0, sizeof(SDK_SMART_WB_CONFIG_EX));
			m_stSmarkConfig.iOpMode = OUT_PICTURE;
			m_stSmarkConfig.iWbmode = m_nOutputIndex;
			m_stSmarkConfig.iLibIndex = nlibindex;
			m_stSmarkConfig.iFileIndex = nfileIndex;
			m_stSmarkConfig.iSyslistID = nSysId;
			strcpy(m_stSmarkConfig.sUserID, pFile.toLocal8Bit().data());

			m_pTreeData->pDevObj->ProcessListManage(&m_stSmarkConfig);
		}
	}
}
void CompareRecord::on_btnDelPic_clicked()
{
	if (m_bOperating)
	{
		return;
	}
	m_bExport = TRUE;
	memset(&m_stBWListCofig, 0, sizeof(SDK_FA_BLACKANDWHITELIST_CONFIG));
	DWORD dwThreadID = 0;
	//以挂起模式创建线程
	HANDLE hThread = CreateThread(NULL, 0, DeletePictureThread, this, 0 , &dwThreadID);
	if (hThread != NULL)
	{
		CloseHandle(hThread);//关闭线程句柄，线程并不会结束，便于回收资源
		hThread = NULL;
	}
}
DWORD WINAPI CompareRecord::DeletePictureThread(LPVOID lpParam)
{
	CompareRecord *pDlg = (CompareRecord  *)lpParam;
	pDlg->DeletePicturePro();
	return TRUE;
}

BOOL CompareRecord::DeletePicturePro()
{
	QString strLog = NULL;
	QString strTemp = NULL;
	QString str = NULL;
	QString strC = NULL;
	int nCount = 0;
	int nfileIndex = 0;
	int nlibindex = 0;
	int i = 0;
	int nSysId = 0;
	char *pfile = NULL;

	while (m_bExport)
	{
		memset(&m_stBWListCofig, 0, sizeof(SDK_FA_BLACKANDWHITELIST_CONFIG));
		if (m_pTreeData->pDevObj->m_lUserLoginID < 0)
		{
			break;
		}
		if (m_bSelectAll)	//全部删除
		{
			memset(&m_stSmarkConfig, 0, sizeof(SDK_SMART_WB_CONFIG_EX));
			m_stSmarkConfig.iOpMode = OUT_PICTURE_DELALL;
			m_stSmarkConfig.iWbmode = m_nOutputIndex;

			m_pTreeData->pDevObj->ProcessListManage(&m_stSmarkConfig);
			m_bExport = FALSE;

			WaitForCallBack(0);
		}
		else
		{
			nCount = ui.tableWidget_Export->rowCount();
			for (i = 0; i < nCount; i++)
			{
				
				if (i == (nCount - 1))
				{
					m_bExport = FALSE;
				}
				if (ui.tableWidget_Export->item(i, 0)->checkState() == Qt::Checked && strTemp.length() == 0)
				{
					nfileIndex = ui.tableWidget_Export->item(i, 2)->text().toInt();
					str = ui.tableWidget_Export->item(i, 1)->text();
					QByteArray ba = str.toLocal8Bit();
					pfile = ba.data();
					nlibindex = ui.tableWidget_Export->item(i, 3)->text().toInt();
					nSysId = ui.tableWidget_Export->item(i, 5)->text().toInt();

					memset(&m_stSmarkConfig, 0, sizeof(SDK_SMART_WB_CONFIG_EX));
					m_stSmarkConfig.iOpMode = OUT_PICTURE_DEL;
					m_stSmarkConfig.iWbmode = m_nOutputIndex;
					m_stSmarkConfig.iLibIndex = nlibindex;
					m_stSmarkConfig.iFileIndex = nfileIndex;
					strcpy(m_stSmarkConfig.sUserID, str.toLocal8Bit().data());
					m_stSmarkConfig.iSyslistid = nSysId;

					m_pTreeData->pDevObj->ProcessListManage(&m_stSmarkConfig);

					QString strlog = QObject::tr("删除文件%1").arg(str);
					AddWBLogInfo(strlog);

					WaitForCallBack(i);
				}
			}
		}

	}
	return TRUE;
	
}

void CompareRecord::slotItemClicked()
{
	if (ui.treeWidget->currentItem())
	{
		QString var = ui.treeWidget->currentItem()->text(0);

		QVariant var1 = ui.treeWidget->currentItem()->data(0, Qt::UserRole);

		m_pTreeData = (TreeData_t *)var1.value<void *>();
	}
}


BOOL CompareRecord::WaitForCallBack(int i)
{
	BOOL bRet = FALSE;
	QString strLog = "";
	m_nDeleteErrorCode = WB_OK;
	if (::WaitForSingleObject(m_pTreeData->pDevObj->m_hImportWaitEvent, 5000) == WAIT_OBJECT_0)
	{
		strLog = QObject::tr("删除图片:成功");
		if (WB_OK == m_nDeleteErrorCode)
		{
			bRet = TRUE;
			if (m_bSelectAll)
			{
				ui.tableWidget_Export->setRowCount(0);
				ui.tableWidget_Export->clearContents();
			
				m_vectorFileInfo.clear();
				if (m_pBufferIndex)
				{
					delete[] m_pBufferIndex;
					m_pBufferIndex = NULL;
				}
			}
			else
			{
				ui.tableWidget_Export->setItem(i, 6, new QTableWidgetItem(strLog));
			}
		}
		else
		{
			strLog = QObject::tr("删除图片;失败");
			ui.tableWidget_Export->setItem(i, 6, new QTableWidgetItem(strLog));
		}
	}
	else
	{
		int nRet = VideoNet_GetLastError();
		strLog = QObject::tr("信息返回超时:错误码'%1'").arg(nRet);
		ui.tableWidget_Export->setItem(i, 6, new QTableWidgetItem(strLog));

	}
	AddWBLogInfo(strLog);
	return bRet;
}

void CompareRecord::on_btnClear_clicked()
{
	clearCurrAge(ui.tableWidget_exportView);
	
}

void CompareRecord::on_btnAdd_Import_clicked()
{
	m_strListFileName.clear();
	m_strPicName.clear();
	ui.lineEdit_InportPath->setText("");
	m_strPicPath = QFileDialog::getExistingDirectory(this, "选择目录", "./", QFileDialog::ShowDirsOnly);
	if (m_strPicPath.size() > 0)
	{
		ui.lineEdit_InportPath->setText(m_strPicPath);
		QDir dir(m_strPicPath);
		QStringList nameFilters;
		//nameFilters << "*.jpg" << "*.png";
		nameFilters << "*.jpg";
		m_strListFileName = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
	}
}

void CompareRecord::on_btnInport_Select_clicked()
{
	m_strListFileName.clear();
	m_strPicName.clear();
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle(QObject::tr("打开图片"));
	fileDialog->setDirectory(".");
	fileDialog->setNameFilter(tr("Images(*.jpg)"));
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	fileDialog->setViewMode(QFileDialog::Detail);

	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	if (fileNames.size() > 0)
	{
		m_strPicName = fileNames.at(0); 
		ShowPic_Import(m_strPicName);
	}
}

void CompareRecord::on_btnImport_clicked()
{
	if (m_strPicName.size() == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择图片!"));
		return;
	}
	BeginInport();
}

void CompareRecord::on_btnBatch_Inport_clicked()
{
	if (m_strListFileName.size() == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择图片!"));
		return;
	}
	BeginInport();
}

void CompareRecord::BeginInport()
{
	if (m_bImporting)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("已经正在上传图片!"));
		return;
	}
	int nCheck = GetCheckedTree();
	if (nCheck == 0)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请勾选设备!"));
		return;
	}
	m_nFinishedNum = 0;
	m_bImporting = TRUE;
	DWORD dwThreadID = 0;
	HANDLE hThread = NULL;
	TreeData_t* pTreeData = NULL;

	ClearInportWidget();
	m_mapThreadTreeData.clear();
	for (int i = 0; i < nCheck; i ++)
	{
		//以挂起模式创建线程
		pTreeData = m_listTreeData.at(i);
		ShowInportviewInfo(i, pTreeData->pDevObj);
		HANDLE hThread = CreateThread(NULL, 0, ImportFaceImageProc, this, 0, &dwThreadID);
		m_mapThreadTreeData[dwThreadID] = pTreeData;
		if (hThread != NULL)
		{
			//ResumeThread(hThread);//唤醒线程
			CloseHandle(hThread);//关闭线程句柄，线程并不会结束，便于回收资源
			hThread = NULL;
		}
	}
}

void CompareRecord::ShowInportviewInfo(int nCloumn, CJLNDevice* pDevObj, INPORT_INFO* pInportInfo)
{
	QTableWidgetItem* pQTItem = NULL;
	BOOL bExist = TRUE;
	QString strPos = "";
	if (nCloumn == -1)
	{
		bExist = FALSE;
		//获取设备所在行号
		int  nSize = m_listTreeData.size();
		for (int i = 0; i < nSize; i ++)
		{
			pQTItem = ui.tableWidget_InPortview->item(i, 0);
			if (pQTItem)
			{
				if (memcmp(pQTItem->text().toLocal8Bit().data(), pDevObj->m_pDevInfo->szDevName, strlen(pDevObj->m_pDevInfo->szDevName)) == 0)
				{
					pQTItem = ui.tableWidget_InPortview->item(i, 1);
					if (pQTItem)
					{
						strPos = QString("%1 %").arg(pInportInfo->nPos);
						pQTItem->setText(strPos);
					}
					pQTItem = ui.tableWidget_InPortview->item(i, 2);
					if (pQTItem)
					{
						if (pInportInfo->nTime == 0)
						{
							strPos = QObject::tr("上传成功: %1").arg(QString::fromLocal8Bit(pInportInfo->szPicName));
							pQTItem->setText(strPos);
						}
						else
						{
							strPos = QObject::tr("完成入库: 成功 = %1, 失败 = %2, 耗时 = %3 s").arg(pInportInfo->nSuccess).arg(pInportInfo->nFailed).arg(pInportInfo->nTime);
							pQTItem->setText(strPos);
						}
					}
					break;
				}
			}
		}
	}
	else
	{
		pQTItem = ui.tableWidget_InPortview->item(nCloumn, 0);
		if (!pQTItem)
		{
			pQTItem = m_listInportWidget.at(nCloumn * INPORT_COLUMN_COUNT + 0);
			if (pQTItem)
			{
				ui.tableWidget_InPortview->setItem(nCloumn, 0, pQTItem);
			}
		}
		pQTItem->setText(pDevObj->m_pDevInfo->szDevName);

		pQTItem = ui.tableWidget_InPortview->item(nCloumn, 1);
		if (!pQTItem)
		{
			pQTItem = m_listInportWidget.at(nCloumn * INPORT_COLUMN_COUNT + 1);
			if (pQTItem)
			{
				ui.tableWidget_InPortview->setItem(nCloumn, 1, pQTItem);
			}
		}
		pQTItem->setText(QObject::tr("0 %"));

		pQTItem = ui.tableWidget_InPortview->item(nCloumn, 2);
		if (!pQTItem)
		{
			pQTItem = m_listInportWidget.at(nCloumn * INPORT_COLUMN_COUNT + 2);
			if (pQTItem)
			{
				ui.tableWidget_InPortview->setItem(nCloumn, 2, pQTItem);
			}
		}
		pQTItem->setText(QObject::tr("开始入库"));
	}		
}

DWORD WINAPI CompareRecord::ImportFaceImageProc(LPVOID lpParam)
{
	CompareRecord *pDlg = (CompareRecord *)lpParam;
	pDlg->ImportFaceImage();
	return 0;
}

void CompareRecord::ImportFaceImage()
{
	DWORD dwThreadId = GetCurrentThreadId();
	TreeData_t* pTreeData = m_mapThreadTreeData[dwThreadId];
	if (!pTreeData)
	{
		return;
	}
	QString strLog = "";
	QString strFilePath = "";
	QString strPicName = "";
	QString strFileLog = "";
	QString chErr = "";
	int nRet = 0;
	JVT_LONG lImExId = 0;

	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
	INPORT_INFO* pInportInfo = new INPORT_INFO;
	SDK_SMART_WB_CONFIG_EX* pWBConfig = new SDK_SMART_WB_CONFIG_EX;
	QString strLogFile = "";

	//创建路径
	strLogFile = QString("%1\\ImportLog").arg(QCoreApplication::applicationDirPath());
	QDir dir;
	if (!dir.exists(strLogFile))
	{
		dir.mkpath(strLogFile);
	}
	strLogFile = QString("%1\\ImportLog\\%2.txt").arg(QCoreApplication::applicationDirPath()).arg(pTreeData->pDevObj->m_pDevInfo->szIpAddr);
	FILE* pLogFile = fopen(strLogFile.toLocal8Bit().data(), "ab+");
	DWORD dwTickBegin = GetTickCount();
	DWORD dwTickTime = GetTickCount();
	int nSuccess = 0;
	int nFailed = 0;
	int nTotal = 0;
	int nTime = 0;
	BOOL bBatch = FALSE;	//是否批量
	QStringList listFile;


	memset(pWBConfig, 0, sizeof(SDK_SMART_WB_CONFIG_EX));
	pWBConfig->iOpMode = IN_PICTURE_ADD;
	pWBConfig->iWbmode = m_bListMod;

	//获取入库图片列表
	if (m_strListFileName.size() == 0 && m_strPicName.size() > 0)
	{
		listFile.append(m_strPicName);
	}
	else if (m_strPicName.size() == 0 && m_strListFileName.size() > 0)
	{
		bBatch = TRUE;
		listFile = m_strListFileName;
	}
	nTotal = listFile.size();
	memset(pInportInfo, 0, sizeof(INPORT_INFO));
	pInportInfo->nTotal = nTotal;
	m_bImporting = TRUE;

	while (m_bImporting && nTime < MAX_INPORT_TIME)
	{
		lImExId = pTreeData->pDevObj->StartImportAndExport();
		if (lImExId)
		{
			nTime = 0;
			break;
		}
		nTime += 1;
	}
	if (pTreeData->pDevObj->m_lImExID > 0)
	{
		for (int i = 0; i < nTotal; i++)
		{
			if (!m_bImporting)
			{
				break;
			}
			dwTickTime = GetTickCount();
			if (bBatch)
			{
				strPicName = listFile.at(i);
				strFilePath = QString("%1/%2").arg(m_strPicPath).arg(strPicName);
			}
			else
			{
				strPicName = listFile.at(i);
				strFilePath = strPicName;
			}
			memset(pWBConfig, 0, sizeof(SDK_SMART_WB_CONFIG_EX));
			pWBConfig->iOpMode = IN_PICTURE_ADD;
			pWBConfig->iWbmode = m_bListMod;
			if (GetConfigInfo(strFilePath.toLocal8Bit().data(), bBatch, pWBConfig))
			{
				nRet = pTreeData->pDevObj->ProcessListManage(pWBConfig, strFilePath.toLocal8Bit().data());

				if (nRet <= 0)
				{
					nRet = VideoNet_GetLastError();
					if (nRet == VIDEONET_SDK_FILE_DATA_LARGE_ERROR)
					{
						pTreeData->pDevObj->m_nErrorCode = WB_FILE_BIG;
					}
					else
					{
						pTreeData->pDevObj->m_nErrorCode = nRet;
					}
				}
				else if (::WaitForSingleObject(pTreeData->pDevObj->m_hImportWaitEvent, 5000) != WAIT_OBJECT_0)
				{
					//strLog = QObject::tr("上传失败:信息返回超时,错误码 %1, Index = %2").arg(nRet).arg(i);

					//等待超时重新开启黑白名单链路
					while (m_bImporting && nTime < MAX_INPORT_TIME)
					{
						pTreeData->pDevObj->Logout();
						if (pTreeData->pDevObj->Login() > 0)
						{
							lImExId = pTreeData->pDevObj->StartImportAndExport();
							if (lImExId)
							{
								nTime = 0;
								break;
							}
						}
						nTime += 1;
					}
					i--;
					continue;
				}
			}
			else
			{
				pTreeData->pDevObj->m_nErrorCode = WB_PARA_ERROR;
			}

			ResetEvent(pTreeData->pDevObj->m_hImportWaitEvent);

			GetResultCode(pTreeData->pDevObj->m_nErrorCode, chErr);
			strLog = QString("%1: Index = %2, 耗时: %3 ms").arg(chErr).arg(i).arg(GetTickCount() - dwTickTime);
			if (pTreeData->pDevObj->m_nErrorCode == WB_OK)
			{
				pInportInfo->nSuccess += 1;
			}
			else
			{
				pInportInfo->nFailed += 1;
			}
			pInportInfo->nPos = 100 * (float(pInportInfo->nSuccess + pInportInfo->nFailed) / float(pInportInfo->nTotal));
			memset(pInportInfo->szPicName, 0, 260);
			strcpy(pInportInfo->szPicName, strPicName.toLocal8Bit().data());
			ShowInportviewInfo(-1, pTreeData->pDevObj, pInportInfo);
			if (pLogFile)
			{
				current_date_time = QDateTime::currentDateTime();
				current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
				strFileLog = QString("%1   %2   %3 \r\n").arg(current_date).arg(strLog).arg(strPicName);
				fwrite(strFileLog.toLocal8Bit().data(), 1, strFileLog.toLocal8Bit().size(), pLogFile);
			}
		}
	}
	pInportInfo->nPos = 100;
	pInportInfo->nTime = (GetTickCount() - dwTickBegin) / 1000;
	ShowInportviewInfo(-1, pTreeData->pDevObj, pInportInfo);
	m_nFinishedNum += 1;
	if (pLogFile)
	{
		current_date_time = QDateTime::currentDateTime();
		current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
		strFileLog = QObject::tr("%1   完成入库: 成功 = %2, 失败 = %3, 耗时 = %4 s \r\n").arg(current_date).arg(pInportInfo->nSuccess).arg(pInportInfo->nFailed)
			.arg(pInportInfo->nTime);
		fwrite(strFileLog.toLocal8Bit().data(), 1, strFileLog.toLocal8Bit().size(), pLogFile);
		fclose(pLogFile);
		pLogFile = NULL;
	}
	//所有设备完成入库
	if (m_nFinishedNum >= m_listTreeData.size())
	{
		m_bImporting = FALSE;
	}
	if (pInportInfo)
	{
		delete pInportInfo;
		pInportInfo = NULL;
	}
	if (pWBConfig)
	{
		delete pWBConfig;
		pWBConfig = NULL;
	}
}

int CompareRecord::InsertLogInfo(CJLNDevice* pDevInfo)
{
	if (!pDevInfo)
	{
		return 0;
	}

	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
	int RowCont = ui.tableWidget_InPortview->rowCount();
	ui.tableWidget_InPortview->insertRow(RowCont);//增加一行
	ui.tableWidget_InPortview->setItem(RowCont, 0, new QTableWidgetItem(current_date));
	ui.tableWidget_InPortview->setItem(RowCont, 1, new QTableWidgetItem(QString::fromLocal8Bit(pDevInfo->GetDevInfo()->szDevName)));
	ui.tableWidget_InPortview->setItem(RowCont, 2, new QTableWidgetItem(pDevInfo->GetDevInfo()->szIpAddr));

	return RowCont;
}

BOOL CompareRecord::GetConfigInfo(char* pFileName, BOOL bBatch, SDK_SMART_WB_CONFIG_EX* pWBconfig)
{
	if (!bBatch)
	{
		strcpy(pWBconfig->stUserInfo.name, ui.lineEdit_InportNmae->text().toLocal8Bit().data());
		strcpy(pWBconfig->stUserInfo.usrid, ui.lineEdit_InportNumber->text().toLocal8Bit().data());
		strcpy(pWBconfig->sUserID, ui.lineEdit_InportNumber->text().toLocal8Bit().data());
		strcpy(pWBconfig->stUserInfo.phone, ui.lineEdit_InportPhone->text().toLocal8Bit().data());
		strcpy(pWBconfig->stUserInfo.remark, ui.lineEdit_InportRemark->text().toLocal8Bit().data());
		pWBconfig->stUserInfo.sex = ui.comboBox_InportGender->currentIndex() + 1;
		if (strlen(pWBconfig->stUserInfo.name) <= 0 || strlen(pWBconfig->sUserID) <= 0)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("姓名或编号不能为空!"));
			return FALSE;
		}
		return TRUE;
	}
	bool bFileRet = false;
	char cFileName[MAX_PATH] = {0};
	if (!pFileName)
	{
		return FALSE;
	}

	int i = 0;
	for(i = strlen(pFileName) - 1 ; i > 0 ; i--)
	{
		if(pFileName[i] == '/')
		{
			bFileRet = true;
			break;
		}
	}

	if (bFileRet)
	{		 
		memcpy(cFileName,pFileName + i + 1,strlen(pFileName) - i);
	} 
	else
	{	
		memcpy(cFileName,pFileName,strlen(pFileName));
	}

	//判断名字格式
	char *Fname = cFileName;
	char chName[MAX_PATH] = {0};
	char chUsrId[MAX_PATH] = {0};
	int szlen = strlen(cFileName);
	int isznum = 0;
	int iUsIdNum = 0;
	int iGenderNum = 0;
	for(int szi = 0; szi < szlen; szi++)
	{
		if(*(Fname + szi) == '_' && szi !=0 && szi != szlen-1)
		{
			isznum ++;
			if (isznum == 1)
			{
				memcpy(chName, cFileName, szi);
				iUsIdNum = szi + 1;
			}
			else if (isznum == 2)
			{
				memcpy(chUsrId, cFileName + iUsIdNum, szi - iUsIdNum);
				iGenderNum = szi;
			}
		}
	}
	if(isznum != 2)
	{
		return VIDEONET_SDK_FILE_FORAMAT_ERROR;
	}
	if (strlen(chName) > 63 || strlen(chUsrId) > 31)
	{
		return FALSE;
	}

	memcpy(pWBconfig->stUserInfo.name, chName, strlen(chName));
	memcpy(pWBconfig->stUserInfo.usrid, chUsrId, strlen(chUsrId));
	memcpy(pWBconfig->sUserID, chUsrId, strlen(chUsrId));
	
	if (strstr(cFileName, "男") != NULL)
	{
		pWBconfig->stUserInfo.sex = 1;
	} 
	else
	{
		pWBconfig->stUserInfo.sex = 2;
	}

	return TRUE;
}

void CompareRecord::FaceCallBack_Import(long lSubFaceHandle, char *pBuffer,long lbufsize,SDK_FA_BLACKANDWHITELIST_CONFIG *pConfig,long dwUser)
{
	char chFilename[MAX_PATH] = {0};
	if (IN_PICTURE_ADD == pConfig->byOutMode)			//通过导入图片添加一张黑白名单
	{
		m_nErrorCode = pConfig->byErrorCode;

	}
	else if (IN_PICTURE_ADD_SNAP == pConfig->byOutMode )
	{
		QString strLog;
		if (pConfig->byErrorCode == WB_OK)
		{	
			char *pFileBuf = new char[lbufsize];
			memcpy(pFileBuf,pBuffer,lbufsize);
			char filename[128] = {0};
			sprintf_s( filename, "%s\\%s","d:", pConfig->byFileName);
			strLog = QString::fromLocal8Bit(filename);
			FILE * m_pFile= NULL;
			fopen_s(&m_pFile,filename,"wb");
			if (m_pFile)
			{					
				fwrite(pFileBuf, 1,lbufsize ,m_pFile);
				fclose(m_pFile);
				m_pFile = NULL;

				if (pFileBuf != NULL)
				{
					delete pFileBuf;
					pFileBuf = NULL;
				}
			}
			else
			{
				strLog = QObject::tr("创建文件失败");
				myHelper::ShowMessageBoxWarning(strLog);
			}
		}
	}
}

void CompareRecord::on_btnStop_Import_clicked()
{
	m_bImporting = FALSE;
}

void CompareRecord::SearchEnd(int nPage)
{
	
	SMART_FACE_CMP_QUERY_INFO* pCompareInfo = NULL;
	int nIndex = 0;			//行号
	int nSubIndex = 0;		//列号
	int nVecListSize = m_vectorListinfo.size();

	QString picName;
	QString snapName;
	if (ui.tableWidget->rowCount()>0)
	{
		ui.tableWidget->clearContents();
	}
	if (nPage <= m_nPageCount && nPage >= 1)
	{
		int nStartNum = (nPage - 1)*FACE_CMPWEB_PAGENUM;
		int nEndNum;
		if (nPage == m_nPageCount)
		{
			nEndNum = m_vectorListinfo.size();
		}
		else
		{
			nEndNum = nPage * FACE_CMPWEB_PAGENUM;
		}

		compare_mutex.lock();
		if (nVecListSize < nEndNum)
		{
			compare_mutex.unlock();
			return ;
		}

		QString strSimilarity1 = "%";
		QString strSimilarity = QObject::tr("相似度");
		QString strGuest = QObject::tr("来访次数");
		QString strAge = QObject::tr("年龄");
		QString strGender1 = QObject::tr("性别");
		QString strGlassess1 = QObject::tr("眼镜");
		QString strMask1 = QObject::tr("口罩");
		QString strRace1 = QObject::tr("皮肤");
		QString strBeard1 = QObject::tr("胡子");
		QString strEmotion1 = QObject::tr("表情");
		int nSimilarity = 0;

		
		for (int i = nStartNum ;i < nEndNum ;i++)
		{
			pCompareInfo  = m_vectorListinfo[i];
			nSimilarity = (int)(pCompareInfo->sLibSimilarity * 100);
			if (pCompareInfo != NULL)
			{
				
				LoadPicture(pCompareInfo,picName,snapName);
				nIndex = i - nStartNum;
				
				ui.tableWidget->insertRow(nIndex);//增加一
			
				//qDebug()<<picName<<snapName;
				QLabel * label = new QLabel;
				label->setPixmap(picName);
				label->setAlignment(Qt::AlignHCenter);
				label->setScaledContents(true);
				label->setMinimumSize(30,30);
				QLabel *lib_snap = new QLabel;
				lib_snap->setPixmap(snapName);
				lib_snap->setAlignment(Qt::AlignCenter);
				lib_snap->setScaledContents(true);
				lib_snap->setMinimumSize(30,30);
				ui.tableWidget->setCellWidget(nIndex, 0, label);
				ui.tableWidget->setCellWidget(nIndex,1,lib_snap);
				ui.tableWidget->setItem(nIndex,2,new QTableWidgetItem(QString::fromLocal8Bit(pCompareInfo->sName)));   //姓名

				ui.tableWidget->setItem(nIndex,3,new QTableWidgetItem(QString(QLatin1String(pCompareInfo->sUserID))));  //编号

				QString strMode = g_pInstance->GetModeType(pCompareInfo->sLibMode);
				ui.tableWidget->setItem(nIndex,4,new QTableWidgetItem(strMode));//名单类型

				ui.tableWidget->setItem(nIndex, 5, new QTableWidgetItem(QString("%1").arg(pCompareInfo->fTemperature)));		//温度
				ui.tableWidget->setItem(nIndex,6,new QTableWidgetItem(QString(QLatin1String(pCompareInfo->sLibSnapTime))));  //时间
				
	
				QString strTemp = QString("%1:%2%3, %4:%5, %6:%7, %8:%9, %10:%11, %12:%13, %14:%15, %16:%17, %18:%19")
					.arg(strSimilarity).arg(nSimilarity).arg(strSimilarity1).arg(strGuest).arg(pCompareInfo->nLibGuest).arg(strAge).arg((int)(pCompareInfo->cLibAge)).arg(strGender1).arg(GetAbility((int)(pCompareInfo->cLibGender)))
					.arg(strGlassess1).arg(GetAbility((int)(pCompareInfo->cLibGlasses))).arg(strMask1).arg(GetAbility((int)(pCompareInfo->cLibMask))).arg(strRace1).arg(GetAbility((int)(pCompareInfo->cLibRace))).arg(strBeard1).arg(GetAbility((int)(pCompareInfo->cLibBeard)))
					.arg(strEmotion1).arg(GetAbility((int)(pCompareInfo->cLibEmotion)));
				ui.tableWidget->setItem(nIndex,7,new QTableWidgetItem(strTemp));//详细信息
			}
		}
	}
	compare_mutex.unlock();
}
void CompareRecord::clearCurrAge(QTableWidget *m_table)
{
	int iLen = m_table->rowCount();
	for(int i=0;i<iLen;i++)    
	{        
		m_table->removeRow(0);           
	}
}
void CompareRecord::on_btnCompre_clicked()
{

	
	int strPage = ui.lineEdit_CurPage->text().toInt();
	if (strPage > 1 && strPage <=  m_nPageCount)
	{
		strPage --;
		clearCurrAge(ui.tableWidget);
		ShowPageInfoRecord(strPage);
		CompareEvent *custevent = new CompareEvent(CET_COMPARISON);
		custevent->setId(strPage);
		QApplication::postEvent(this,custevent);
	}
}

void CompareRecord::on_btnComNext_clicked()
{
	
	int strPage = ui.lineEdit_CurPage->text().toInt();
	if (strPage >= 1 && strPage < m_nPageCount)
	{
		strPage++;
		clearCurrAge(ui.tableWidget);
		ShowPageInfoRecord(strPage);
		CompareEvent *custevent = new CompareEvent(CET_COMPARISON);
		custevent->setId(strPage);
		QApplication::postEvent(this,custevent);
		
	}
}

void CompareRecord::on_btnComJump_clicked()
{
	
	int strPage = ui.lineEdit_CurPage->text().toInt();
	if (strPage > 1 && strPage <=  m_nPageCount)
	{
		clearCurrAge(ui.tableWidget);
		ShowPageInfoRecord(strPage);
		CompareEvent *custevent = new CompareEvent(CET_COMPARISON);
		custevent->setId(strPage);
		QApplication::postEvent(this,custevent);
	}
	
}

QString CompareRecord::GetAbility(int nValue)
{
	QString strValue = QObject::tr("无");
	switch (nValue)
	{
	case SF_MAN:		
		strValue = QObject::tr("男");
		break;
	case SF_WOMAN:		
		strValue = QObject::tr("女");
		break;
	case SF_GLASSES:
	case SF_MASK:		
		strValue = QObject::tr("有");
		break;
	case SF_SUNGLASSES:		
		strValue = QObject::tr("太阳镜");
		break;
	case SF_SMILE:		
		strValue = QObject::tr("微笑");
		break;
	case SF_YELLOW:		
		strValue = QObject::tr("黄");
		break;
	case SF_BLACK:		
		strValue = QObject::tr("黑");
		break;
	case SF_WHITE:		
		strValue = QObject::tr("白");
		break;
	case SF_EYE_CLOSE:		
		strValue = QObject::tr("闭");
		break;
	case SF_EYE_OPEN:		
		strValue = QObject::tr("睁");
		break;
	case SF_MOUTH_CLOSE:		
		strValue = QObject::tr("闭");
		break;
	case SF_MOUTH_OPEN:		
		strValue = QObject::tr("开");
		break;
	case SF_BEARD:		
		strValue = QObject::tr("有");
		break;
	case SF_ANGRY:		
		strValue = QObject::tr("生气");
		break;
	case SF_CLAM:		
		strValue = QObject::tr("平静");
		break;
	case SF_DISGUST:		
		strValue = QObject::tr("厌恶");
		break;
	case SF_HAPPY:		
		strValue = QObject::tr("高兴");
		break;
	case SF_SAD:		
		strValue = QObject::tr("难过");
		break;
	case SF_SCARED:		
		strValue = QObject::tr("害怕");
		break;
	case SF_SQUINT:		
		strValue = QObject::tr("斜视");
		break;
	case SF_SCREAM:		
		strValue = QObject::tr("尖叫");
		break;
	case SF_SURPRISED:		
		strValue = QObject::tr("惊讶");
		break;
	default:
		break;

	}
	return strValue;
}

void CompareRecord::LoadPicture(SMART_FACE_CMP_QUERY_INFO* pCompareInfo,QString& strLibPath,QString& strSnapPath)
{
	if (NULL == pCompareInfo)
	{
		return;
	}

	char chTime[16] = {0};
	char cpicName[MAX_PATH] = {0};
	char cLibName[MAX_PATH] = {0};
	char szSnapPath[MAX_PATH] = {0};

	if (nSourceType == 1)
	{
			
		strLibPath = QString("%1\\%2\\%3").arg(QCoreApplication::applicationDirPath() + "/" + "LibPicture").arg(m_pTreeData->pDevObj->m_pDevInfo->szIpAddr).arg(pCompareInfo->sSysListID);
	}
	else
	{
		memcpy(chTime, pCompareInfo->sLibSnapTime, 10);
		sprintf(szSnapPath, "%s\\%s\\%s\\%d", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szSnapPath, chTime, pCompareInfo->cDeviceIP, pCompareInfo->sLibChannelid);
		sprintf_s(cpicName, "%s\\%s", szSnapPath, pCompareInfo->sSnappicname);
		sprintf_s(cLibName, "%s\\%s", szSnapPath, pCompareInfo->sLibPicName);
		strLibPath = QString::fromLocal8Bit(cLibName);
		strSnapPath = QString(QLatin1String(cpicName));
	}
	
}



void CompareRecord::on_btnCompareExport_clicked()
{
	int nSize = m_vectorListinfo.size();
	ui.progressBar->setValue(0);
	if (nSize == 0)
	{
		myHelper::ShowMessageBoxError(QObject::tr("导出失败，数据为空"));
		return;
	}
	char szPicPath[520] = { 0 };
	QString strTemp = "";
	QString title = QString(QObject::tr("日志记录"));
	QString fileName = QFileDialog::getSaveFileName(ui.tableWidget, QObject::tr("保存"),
		QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
		"Excel xlsx(*.xlsx)|*.xlsx||");
	if (fileName != "")
	{
		int nPicWidth = 84;
		float fPos = 0.0;
		if (!ui.checkBox_Export->checkState())
		{
			nPicWidth = 20;
		}
		
		QAxObject *pExcel = new QAxObject;
		if (pExcel->setControl("Excel.Application")) //连接Excel控件
		{
			pExcel->dynamicCall("SetVisible (bool Visible)", "false");//不显示窗体
			pExcel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
			QAxObject *workbooks = pExcel->querySubObject("WorkBooks");//获取工作簿集合
			workbooks->dynamicCall("Add");//新建一个工作簿
			QAxObject *workbook = pExcel->querySubObject("ActiveWorkBook");//获取当前工作簿		
			QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
			int i = 0, colcount = ui.tableWidget->columnCount();
			QAxObject *cell, *col;
			QString columnName;
			int nTemp = 0;

			//列标题
			worksheet->querySubObject("Cells(int,int)", 1, 1)->setProperty("RowHeight", 20);
			for (i = 0; i < colcount; i++)
			{
				columnName = "";
				columnName.append(QChar(i + 'A'));
				columnName.append(":");
				columnName.append(QChar(i + 'A'));
				col = worksheet->querySubObject("Columns(const QString&)", columnName);

				nTemp = (i == 0 || i == 1) ? ((nPicWidth + 20) / 6) : (ui.tableWidget->columnWidth(i) / 6);
				col->setProperty("ColumnWidth", nTemp);
				cell = worksheet->querySubObject("Cells(int,int)", 1, i + 1);
				columnName = ui.tableWidget->horizontalHeaderItem(i)->text();
				cell->dynamicCall("SetValue(const QString&)", columnName);
				cell->querySubObject("Font")->setProperty("Bold", true);
			}
			std::vector<SMART_FACE_CMP_QUERY_INFO*> ::reverse_iterator iter;
			SMART_FACE_CMP_QUERY_INFO* pCompareInfo;
			nTemp = 2;
			char chTime[16] = { 0 };
			QAxObject * shapes = worksheet->querySubObject("Shapes");

			for (iter = m_vectorListinfo.rbegin(); iter != m_vectorListinfo.rend(); ++iter)
			{
				pCompareInfo = *iter;
				if (!pCompareInfo)
				{
					continue;
				}
				worksheet->querySubObject("Cells(int,int)", nTemp, 1)->setProperty("RowHeight", nPicWidth);
				if (ui.checkBox_Export->checkState())
				{
					for (int i = 0; i < 2; i++)
					{
						memset(szPicPath, 0, 520);
						memcpy(chTime, pCompareInfo->sLibSnapTime, 10);
						sprintf(m_szSnapPath, "%s\\%s\\%s\\%d", g_pInstance->m_pDlgSystemSet->m_ClientCfg.szSnapPath, chTime, pCompareInfo->cDeviceIP, pCompareInfo->sLibChannelid);
						if (i == 0 && strlen(pCompareInfo->sLibPicName) > 0)
						{
							sprintf(szPicPath, "%s\\%s", m_szSnapPath, pCompareInfo->sLibPicName);
						}
						else if (i == 1 && strlen(pCompareInfo->sSnappicname) > 0)
						{
							sprintf(szPicPath, "%s\\%s", m_szSnapPath, pCompareInfo->sSnappicname);
						}

						if (PathFileExists(szPicPath))
						{
							shapes->dynamicCall("AddPicture( QString&, bool, bool, double, double, double, double",
								QVariant(QString::fromLocal8Bit(szPicPath)), true, true, 10 + i * (nPicWidth + 20) , (nTemp - 2) * (nPicWidth) + 20, nPicWidth, nPicWidth - 2);
						}
					}
				}
				for (int i = 2; i < colcount;i++)
				{
					GetColumnText(pCompareInfo, i, strTemp);
					worksheet->querySubObject("Cells(int,int)", nTemp,i+1)->dynamicCall("SetValue(const QString&)", strTemp);
				}

				nTemp++;
				fPos =100 * (float)(nTemp - 2) / (float)(nSize);
				ui.progressBar->setValue((int)fPos);
			}
			workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName));//保存至fileName
			workbook->dynamicCall("Close()");//关闭工作簿
			pExcel->dynamicCall("Quit()");//关闭excel
			delete pExcel;
			pExcel = NULL;
			myHelper::ShowMessageBoxInfo(QObject::tr("导出成功"));
		}
		else
		{
			myHelper::ShowMessageBoxError(QObject::tr("错误，未能创建Excel对象，请安装Microsoft Excel"));
		}
	}
	ui.progressBar->setValue(0);
}

void CompareRecord::GetColumnText(SMART_FACE_CMP_QUERY_INFO* pCompareInfo, int nCol, QString &strName)
{
	int nSimilarity = 0;
	QString strGender = QObject::tr("男");
	QString strGlasses = QObject::tr("无");
	QString strMask = QObject::tr("无");
	QString strRace = QObject::tr("黄");
	QString strBeard = QObject::tr("无");
	QString strEmotion = QObject::tr("无");

	QString strSimilarity = "%";
	QString strSimilarity1 = QObject::tr("相似度");
	QString strGuest1 = QObject::tr("来访次数");
	QString strAge1 = QObject::tr("年龄");
	QString strGender1 = QObject::tr("性别");
	QString strGlasses1 = QObject::tr("眼镜");
	QString strMask1 = QObject::tr("口罩");
	QString strRace1 = QObject::tr("皮肤");
	QString strBeard1 = QObject::tr("胡子");
	QString strEmotion1 = QObject::tr("表情");

	switch (nCol)
	{
	case 2:	
		strName = QString::fromLocal8Bit(pCompareInfo->sName);
		break;
	case 3:
		strName = QString(QLatin1String(pCompareInfo->sUserID));
		break;
	case 4:
		strName = g_pInstance->GetModeType(pCompareInfo->sLibMode);
		break;
	case 5:
		strName = QString("%1").arg(pCompareInfo->fTemperature);
		break;
	case 6:
		strName = QString(QLatin1String(pCompareInfo->sLibSnapTime));
		break;
	case 7:
		nSimilarity = (int)(pCompareInfo->sLibSimilarity * 100);
		strName = QString("%1:%2%3, %4:%5, %6:%7, %8:%9, %10:%11, %12:%13, %14:%15, %16:%17, %18:%19")
			.arg(strSimilarity1).arg(nSimilarity).arg(strSimilarity).arg(strGuest1).arg(pCompareInfo->nLibGuest).arg(strAge1).arg((int)(pCompareInfo->cLibAge)).arg(strGender1).arg(GetAbility((int)(pCompareInfo->cLibGender)))
			.arg(strGlasses1).arg(GetAbility((int)(pCompareInfo->cLibGlasses))).arg(strMask1).arg(GetAbility((int)(pCompareInfo->cLibMask))).arg(strRace1).arg(GetAbility((int)(pCompareInfo->cLibRace))).arg(strBeard1).arg(GetAbility((int)(pCompareInfo->cLibBeard)))
			.arg(strEmotion1).arg(GetAbility((int)(pCompareInfo->cLibEmotion)));
		break;
	default:
		break;
	}
}

void CompareRecord::ListManageCallBack_Export(long lSubFaceHandle, char *pBuffer, long lbufsize, SDK_SMART_WB_CONFIG_EX *pConfig, long dwUser)
{

	QString strLogInfo;
	if (pConfig == NULL)
	{
		return;
	}
	if (OUT_INDEX == pConfig->iOpMode)
	{
		nCount = pConfig->iAllNums;
		char* pBufferTemp = new char[nCount * sizeof(SDK_FILEINDEX_INFO)];
		if (pBufferTemp)
		{
			memset(pBufferTemp, 0, nCount * sizeof(SDK_FILEINDEX_INFO));
			memcpy(pBufferTemp, pBuffer, nCount * sizeof(SDK_FILEINDEX_INFO));
			for (int i = 0; i < nCount; i++)
			{
				SDK_FILEINDEX_INFO *pInfo = (SDK_FILEINDEX_INFO *)(pBuffer + sizeof(SDK_FILEINDEX_INFO) * i);
				m_vectorFileInfo.push_back(*pInfo);
			}
			
			ui.tableWidget_Export->setRowCount(0);
			ui.tableWidget_Export->clearContents();
			compare_mutex.lock();
			QString str = ui.lineEdit_PicName->text();
			QByteArray ba = str.toLocal8Bit();
			char *p = ba.data();
			int len = m_vectorFileInfo.size();
			int num = 0;

			for (int i = 0; i < len; i++)
			{
			char *pstr = m_vectorFileInfo[i].name;
			if (isChildStr(pstr, p))
			{
			ui.tableWidget_Export->insertRow(i);//增加一行
			check = new QTableWidgetItem();
			check->setCheckState(Qt::Unchecked);

			ui.tableWidget_Export->setItem(i, 0, check); //插入复选框
			ui.tableWidget_Export->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(m_vectorFileInfo[i].name)));
			ui.tableWidget_Export->setItem(i, 2, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].findex.fileindex)));
			ui.tableWidget_Export->setItem(i, 3, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].findex.libindex)));
			ui.tableWidget_Export->setItem(i, 4, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].enable)));
			ui.tableWidget_Export->setItem(i, 5, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].checksum)));

			}
			}

			compare_mutex.unlock();
		}
		
	}
	else if (OUT_PICTURE == pConfig->iOpMode)
	{
		char filename[128] = { 0 };
		QDir dir;
		if (!dir.exists(downedPath))
		{
			dir.mkpath(downedPath);
		}

		sprintf(filename, "%s/%s", downedPath.toLocal8Bit().data(), pConfig->stUserInfo.picname);
		if ((pConfig->iErrorCode == WB_OK) && (lbufsize > 0))
		{

			FILE *m_pFile = fopen(filename, "wb");
			if (m_pFile)
			{
				fwrite(pBuffer, 1, lbufsize, m_pFile);
				fclose(m_pFile);
				m_pFile = NULL;

				strLogInfo = QString::fromLocal8Bit(filename) + QObject::tr("下载成功");
				ShowPicRefresh(QString::fromLocal8Bit(filename));
			}
		}
		else
		{
			strLogInfo = QObject::tr("下载失败");
		}
		AddWBLogInfo(strLogInfo);
	}
	//else if (OUT_PICTURE_DEL == pConfig->iOpMode || OUT_PICTURE_DELALL == pConfig->iOpMode)//删除
	//{
	//	SetEvent(m_hDeletePictureEvent);
	//}
	else if (IN_PICTURE_ADD_SNAP == pConfig->iOpMode || OUT_PICTURE_COMP == pConfig->iOpMode)
	{
		QString strLog;
		if ((pConfig->iErrorCode == WB_OK) && (pBuffer != NULL) && (lbufsize > 0))
		{
			char *pFileBuf = new char[lbufsize];
			memcpy(pFileBuf, pBuffer, lbufsize);
			char filename[128] = { 0 };
			if (m_bBrowse)
			{
				strcpy_s(filename, "C:\\00_00_00.jpg");
			}
			else
			{
				sprintf_s(filename, "%s\\%s", downedPath.toLatin1().data(), pConfig->stUserInfo.picname);
			}

			strLog = QObject::tr("下载图片") + filename;
			FILE * m_pFile = NULL;
			fopen_s(&m_pFile, filename, "wb");
			if (m_pFile)
			{
				fwrite(pFileBuf, 1, lbufsize, m_pFile);
				fclose(m_pFile);
				m_pFile = NULL;

				if (pFileBuf != NULL)
				{
					delete pFileBuf;
					pFileBuf = NULL;
				}
				AddWBLogInfo(strLog);
			}
			else
			{
				strLog = QObject::tr("创建文件失败");
				AddWBLogInfo(strLog);
			}
		}
		else
		{
			if (pBuffer == NULL || lbufsize > 0)
			{
				strLog = QObject::tr("导出失败，请检查导出的黑白名单类型是否正确！");
			}
			AddWBLogInfo(strLog);
		}
	}
}

void CompareRecord::ListManageCallBack_Inport(long lSubFaceHandle, char *pBuffer, long lbufsize, SDK_SMART_WB_CONFIG_EX *pConfig, long dwUser)
{
	QString strLog = NULL;
	//if (IN_PICTURE_ADD == pConfig->iOpMode)			//通过导入图片添加一张黑白名单
	//{
	//	m_nErrorCode = pConfig->iErrorCode;
	//}
	if (IN_PICTURE_ADD_SNAP == pConfig->iOpMode)
	{
		if (pConfig->iErrorCode == WB_OK)
		{
			char filename[128] = { 0 };
			sprintf(filename, "%s\\%s", "d:", pConfig->stUserInfo.picname);
			strLog = QString::fromLocal8Bit(pConfig->stUserInfo.picname);
			FILE * pFile = NULL;
			pFile = fopen(filename, "wb");
			if (pFile)
			{
				fwrite(pBuffer, 1, lbufsize, pFile);
				fclose(pFile);
				pFile = NULL;
			}
			else
			{
				strLog = QObject::tr("创建文件失败");
			}
		}
	}
}
int CompareRecord::GetResultCode(int nRet, QString& str)
{
	switch (nRet)
	{
	case WB_OK:
		str = QObject::tr("导入成功");
		break;
	case WB_FAILE:
		str = QObject::tr("导入失败");
		break;
	case WB_COLLECT_ERROR:
		str = QObject::tr("导入失败，提取特征值失败");
		break;
	case WB_FILEINDEX_ERROR:
		str = QObject::tr("导入失败，文件名字编号重复");
		break;
	case WB_LIB_FULL:
		str = QObject::tr("导入失败，库满");
		break;
	case WB_ADD_TIME_OUT:
		str = QObject::tr("导入失败，添加超时");
		break;
	case WB_PARA_ERROR:
		str = QObject::tr("导入失败，参数错误");
		break;
	case WB_FILE_BIG:
		str = QObject::tr("导入失败，文件太大");
		break;
	case WB_SPACE_ERROR:
		str = QObject::tr("导入失败，存储空间不足");
		break;
	case WB_FILE_OPEN_ERROR:
		str = QObject::tr("导入失败，文件打开失败");
		break;
	case WB_NO_DBFILE:
		str = QObject::tr("导入失败，没有数据库");
		break;
	case WB_FILE_ERROR:
		str = QObject::tr("导入失败，图片读取失败");
		break;
	case WB_DBFILE_BAD:
		str = QObject::tr("导入失败，数据库文件损坏");
		break;
	case WB_PIC_QUALITY_ERROR:
		str = QObject::tr("导入失败，图片质量差");
		break;
	case WB_FILE_WHSIZE_ERROR:
		str = QObject::tr("导入失败， 图片尺寸错误，宽高不能为奇数");
		break;
	case WB_FILE_FACE_ERROR:
		str = QObject::tr("导入失败，检测人脸失败（没检测到人脸或者检测到多人脸）");
		break;
	case	WB_PIC_FORMAT_ERROR:
		str = QObject::tr("导入失败，图片文件名格式错误或图片大于2M");
		break;
	case	WB_FACE_AREA_ERROR:
		str = QObject::tr("导入失败，人脸区域错误");
		break;
	case	WB_FACE_HAND_ERROR:
		str = QObject::tr("导入失败，算法创建句柄错误");
		break;
	case	WB_FACE_BUSY:
		str = QObject::tr("导入失败，设备忙");
		break;
	default:
		str = QObject::tr("未知错误");
		break;
	}
	return 1;
}

int CompareRecord::FaceWorkListCallBack(char *pBuffer, long lbufsize, void* pAttend)
{
	if (!attend_bQueryStat)
	{
		return 0;
	}
	QString stremp;
	SDK_SMART_WB_CONFIG_EX* pConfig = (SDK_SMART_WB_CONFIG_EX*)pAttend;
	memcpy(&m_stSmartConfig, pConfig, sizeof(SDK_SMART_WB_CONFIG_EX));
	SDK_SMART_PERSON_ATTEND_INFO* pAttendInfo = NULL;

	if (pConfig->iErrorCode == WB_FACE_BUSY)	//设备忙时重新查询
	{
		m_iErrorCode = WB_FACE_BUSY;
	}
	else
	{
		if (pConfig->iErrorCode != WB_OK)
		{
			char chErr[MAX_PATH] = { 0 };
			m_bQueryStat = false;
			GetResultCode(pConfig->iErrorCode, QString::fromLocal8Bit(chErr));
			myHelper::ShowMessageBoxWarning(QString::fromLocal8Bit(chErr));
			return 0;
		}
		if (pConfig->stAttendInfo.iCount == 0)
		{
			stremp = QObject::tr("无数据");
			myHelper::ShowMessageBoxWarning(stremp);
			m_bQueryStat = false;
			return 0;
		}
		if (pConfig->stAttendInfo.iCount == -1)
		{
			stremp = QObject::tr("设备忙");
			myHelper::ShowMessageBoxWarning(stremp);
			m_bQueryStat = false;
			return -1;
		}


		compare_mutex.lock();
		for (int i = 0; i < pConfig->stAttendInfo.iCount; i++)
		{
			pAttendInfo = (SDK_SMART_PERSON_ATTEND_INFO*)(pBuffer + i*sizeof(SDK_SMART_PERSON_ATTEND_INFO));
			m_vListinfo.push_back(*pAttendInfo);
		}
		compare_mutex.unlock();
	}

	return 0;
}

int CompareRecord::CmpRecordCallBack(char *pBuffer, long lbufsize, void* pConfigBuf)
{
	if (!m_bQueryStat)
	{
		return 0;
	}
	SDK_SMART_WB_CONFIG_EX* pConfig = (SDK_SMART_WB_CONFIG_EX*)pConfigBuf;
	memcpy(&m_stSmartConfig, pConfig, sizeof(SDK_SMART_WB_CONFIG_EX));
	SDK_SMART_FACE_CMP_QUERY_INFO* pCompareInfo = NULL;
	SMART_FACE_CMP_QUERY_INFO* pCmpInfo = NULL;
	QString strTemp;
	QString chErr = NULL;

	if (pConfig->iErrorCode != WB_OK)
	{
		GetResultCode(pConfig->iErrorCode, chErr);
		AddWBLogInfo(chErr);
		return -1;
	}
	if (pConfig->stCmpInfo.iCount == 0 || !pBuffer || lbufsize == 0)
	{
		AddWBLogInfo(QObject::tr("没有数据"));
		return 0;
	}
	if (pConfig->stCmpInfo.iCount == -1)
	{
		strTemp = QObject::tr("设备忙");
		AddWBLogInfo(strTemp);
		return -1;
	}

	EnterCriticalSection(&m_CriticalSection);
	for (int i = 0; i < pConfig->stCmpInfo.iCount; i++)
	{
		pCompareInfo = (SDK_SMART_FACE_CMP_QUERY_INFO*)(pBuffer + i * sizeof(SDK_SMART_FACE_CMP_QUERY_INFO));
		pCmpInfo = new SMART_FACE_CMP_QUERY_INFO;
		if (pCmpInfo)
		{
			memset(pCmpInfo, 0, sizeof(SMART_FACE_CMP_QUERY_INFO));
			memcpy(pCmpInfo, pCompareInfo, 308);
			m_vectorListinfo.push_back(pCmpInfo);
		}
	}
	LeaveCriticalSection(&m_CriticalSection);

	return 0;
}


void CompareRecord::on_btnAttendSearch_clicked()
{
	if (!GetDevInfo_Atd())
	{
		return;
	}
	if (m_pTreeData == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请点击树节点选择设备!"));
		return;
	}
	if (attend_bQueryStat)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("正在查询!"));
	}
	clearCurrAge(ui.tableWidget_Atd);
	memset(&m_stSmartConfig, 0, sizeof(SDK_SMART_WB_CONFIG_EX));
	QString strName = ui.lineEdit_Attend_Name->text();
	QString strNum = ui.lineEdit_Attend_No->text();
	strcpy(m_stSmartConfig.stAttendInfo.byStartTime, m_TimeBegin.toLatin1().data());
	strcpy(m_stSmartConfig.stAttendInfo.byEndTime, m_TimeEnd.toLatin1().data());
	strcpy(m_stSmartConfig.stAttendInfo.byName, strName.toLocal8Bit().data());
	strcpy(m_stSmartConfig.stAttendInfo.byUserID, strNum.toLatin1().data());
	m_stSmartConfig.stAttendInfo.iPage = 1;
	m_stSmartConfig.stAttendInfo.iPageCount = PAGE_NUM;
	m_stSmartConfig.stAttendInfo.iQueryStatus = ui.comboBox_Attend_state->currentIndex();
	m_stSmartConfig.stAttendInfo.iQuerySomedayOrStatistic = ui.comboBox_Attend->currentIndex() + 1;
	m_stSmartConfig.stAttendInfo.iQueryOrPaged = 1;
	int nManufacturer = m_pTreeData->pDevObj->GetDevInfo()->nManufacturer;
	
	compare_mutex.lock();
	m_vListinfo.clear();
	compare_mutex.unlock();

	attend_bQueryStat = true;
	
	m_nCurPage = 1;
	m_nCountPage = 0;
	ui.btnAttendSearch->setText(QObject::tr("查询..."));
	ui.btnAttendSearch->setEnabled(false);
	m_stSmartConfig.iOpMode = OUT_ATTENDANCE;
	
	HANDLE   hThreadAttend = CreateThread(NULL, 0, fQueryThread, this, 0, NULL);
	 CloseHandle(hThreadAttend);

	
}

bool CompareRecord::GetDevInfo_Atd()
{
	 m_TimeBegin = ui.dateTimeEdit_BeginAtd->text();
	 m_TimeEnd = ui.dateTimeEdit_EndAtd->text();
	if (QString::compare(m_TimeBegin, m_TimeEnd) > 0)
	{
		//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("开始时间不能大于结束时间!"));
		myHelper::ShowMessageBoxWarning(QObject::tr("开始时间不能大于结束时间!"));
		return false;
	}
	if (m_nCheckNum == 0 || m_pTreeData == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择设备!"));
		return false;
	}	
	return true;
}

DWORD WINAPI CompareRecord::fQueryThread(LPVOID Para)
{
	CompareRecord *pThis = (CompareRecord *)Para;
	pThis->fQueryProc();
	return TRUE;
}

void CompareRecord::fQueryProc()
{
	QString strTemp = NULL;
	BOOL bRet = FALSE;
	QString strPageCount = NULL;
	QString str;
	QString strSearch = NULL;


	while (attend_bQueryStat)
	{
		if (!m_pTreeData)
		{
			attend_bQueryStat = false;
			break;
		}

		if (m_pTreeData->pDevObj->m_lUserLoginID > 0)
		{
			m_pTreeData->pDevObj->StartImportAndExport();
		}
		else
		{
			//QMessageBox::information(this, QObject::tr("提示"), QObject::tr("登录设备'%1'失败").arg(m_pDevInfo->GetDevInfo()->szIpAddr));
			CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
			custevent->setId(3);
			QApplication::postEvent(this, custevent);
			attend_bQueryStat = false;
			break;
		}

		if (m_pTreeData->pDevObj->m_lImExID > 0)
		{
			bRet = m_pTreeData->pDevObj->ProcessListManage(&m_stSmartConfig);
			if (bRet)
			{
				if (::WaitForSingleObject(m_pTreeData->pDevObj->m_hImportWaitEvent, 10000) != WAIT_OBJECT_0)
				{
					attend_bQueryStat = false;
					compare_mutex.lock();
					m_vListinfo.clear();
					compare_mutex.unlock();
					//QMessageBox::information(this, QObject::tr("提示"), QObject::tr("查询超时"));
					//myHelper::ShowMessageBoxWarning(QObject::tr("查询超时!"));
					CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
					custevent->setId(2);
					QApplication::postEvent(this, custevent);
					
					break;
				}

				if (m_iErrorCode != WB_FACE_BUSY)
				{

					if (m_nCurPage == 1)
					{
						m_nCountPage = m_stSmartConfig.stAttendInfo.iTotalCount / PAGE_NUM + ((m_stSmartConfig.stAttendInfo.iTotalCount % PAGE_NUM) ? 1 : 0);
						strPageCount = QString::number(m_nCountPage);
						ui.label_Attend->setText(strPageCount);

					}
					if (m_nCurPage <= m_nCountPage)
					{
						m_stSmartConfig.stAttendInfo.iQueryOrPaged = 2;
						m_nCurPage++;
						m_stSmartConfig.stAttendInfo.iPage = m_nCurPage;
					}
					if (m_nCurPage > m_nCountPage)
					{
						fDownLoadLibPic();
						attend_bQueryStat = false;
						CompareEvent *custeven = new CompareEvent(CET_ATTENDENCE);
						custeven->setId(1);
						QApplication::postEvent(this, custeven);
					}
				}
				m_iErrorCode = WB_OK;
			}
			else
			{
				attend_bQueryStat = false;
				//QMessageBox::information(this, QObject::tr("提示"), QObject::tr("查询失败"));
				CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
				QApplication::postEvent(this, custevent);
				custevent->setId(1);
				//myHelper::ShowMessageBoxWarning(QObject::tr("查询失败!"));
			}
		}
		else
		{
			attend_bQueryStat = false;
		}
	}
	ui.btnAttendSearch->setText(QObject::tr("查询"));
	ui.btnAttendSearch->setEnabled(true);
}

void CompareRecord::fDownLoadLibPic()
{
	BOOL bRet = FALSE;
	SDK_SMART_WB_CONFIG_EX stSmartConfig = { 0 };
	SDK_SMART_PERSON_ATTEND_INFO* pAttendInfo = NULL;
	QString str;
	int nListSize = m_vListinfo.size();
	stSmartConfig.iOpMode = OUT_PICTURE;
	for (int i = 0; i < nListSize; i++)
	{
		pAttendInfo = &m_vListinfo[i];
		stSmartConfig.iWbmode = 2;	//白名单
		stSmartConfig.iFileIndex = pAttendInfo->iSyslistID;
		stSmartConfig.iSyslistID = pAttendInfo->iSyslistID;
		strcpy(stSmartConfig.sUserID, pAttendInfo->byUserID);

		str = QString("%1/%2/%3.jpg").arg(QCoreApplication::applicationDirPath()+"/"+"LibPicture").arg(m_pTreeData->pDevObj->m_pDevInfo->szIpAddr).arg(pAttendInfo->iSyslistID);
		//QFile fileInfo(str);
		//if (!fileInfo.exists())
		//{
			bRet = VideoNet_ListManagementData(m_pTreeData->pDevObj->m_lImExID, (char*)&stSmartConfig, sizeof(SDK_SMART_WB_CONFIG_EX), NULL);
			if (bRet)
			{
				if (::WaitForSingleObject(m_pTreeData->pDevObj->m_hImportWaitEvent, 10000) != WAIT_OBJECT_0)
				{
					attend_bQueryStat = false;
					//QMessageBox::information(this, QObject::tr("提示"), QObject::tr("查询超时"));
					//myHelper::ShowMessageBoxWarning(QObject::tr("查询超时!"));
					CompareEvent *custevent = new CompareEvent(CET_MESSAGEBOX);
					QApplication::postEvent(this, custevent);
					custevent->setId(2);
					break;
				}
				memcpy(pAttendInfo->byDepartment, m_pAttendInfo->stUserInfo.resname, 32);
				memcpy(pAttendInfo->byOffice, m_pAttendInfo->stUserInfo.usrdata1, 32);
			}
		//}
	}
}

void CompareRecord::OnSearchShow(int nPage)
{
	SDK_SMART_PERSON_ATTEND_INFO* pAttenInfo;
	QString picName = NULL;
	int nSubIndex = 0;
	int nIndex = 0;
	int nImage = 0;
	int nVListSize = m_vListinfo.size();
	QString strStateS = NULL;
	QString strStateD = NULL;
	clearCurrAge(ui.tableWidget_Atd);
	if (nPage <= m_nCountPage && nPage >= 1)
	{
		int nStartNum = (nPage - 1) * PAGE_NUM;
		int nEndNum;
		if (nPage == m_nCountPage)
		{
			nEndNum = m_stSmartConfig.stAttendInfo.iTotalCount;
		}
		else
		{
			nEndNum = nPage * PAGE_NUM;
		}

		compare_mutex.lock();
		if (nVListSize < nEndNum)
		{
			compare_mutex.unlock();
			return;
		}
		for (int i = nStartNum; i < nEndNum; i++)
		{
			pAttenInfo = &m_vListinfo[i];
			nIndex = i - nStartNum;
			ui.tableWidget_Atd->insertRow(nIndex);//增加一
			ui.tableWidget_Atd->setRowHeight(nIndex, 120);
			//加载图片
			LoadPicture(pAttenInfo, picName);

			QLabel *lib_snap = new QLabel;
			lib_snap->setPixmap(picName);
			lib_snap->setAlignment(Qt::AlignCenter);
			lib_snap->setScaledContents(true);
			
			ui.tableWidget_Atd->setCellWidget(nIndex, 0, lib_snap);
			ui.tableWidget_Atd->setItem(nIndex, 1, new QTableWidgetItem(QString::number(i)));   //姓名

			ui.tableWidget_Atd->setItem(nIndex, 2, new QTableWidgetItem(QString::fromLocal8Bit(pAttenInfo->byName)));  //编号

			ui.tableWidget_Atd->setItem(nIndex, 3, new QTableWidgetItem(QString::fromLocal8Bit(pAttenInfo->byUserID)));//名单类型

			if (m_nType == 1) //统计
			{
				ui.tableWidget_Atd->setItem(nIndex, 4, new QTableWidgetItem(QString::number(pAttenInfo->iShouldTimes)));
				ui.tableWidget_Atd->setItem(nIndex, 5, new QTableWidgetItem(QString::number(pAttenInfo->iActualTimes)));
				ui.tableWidget_Atd->setItem(nIndex, 6, new QTableWidgetItem(QString::number(pAttenInfo->iNormalNum)));
				ui.tableWidget_Atd->setItem(nIndex, 7, new QTableWidgetItem(QString::number(pAttenInfo->iAbsentNum)));
				ui.tableWidget_Atd->setItem(nIndex, 8, new QTableWidgetItem(QString::number(pAttenInfo->iLateNum)));
				ui.tableWidget_Atd->setItem(nIndex, 9, new QTableWidgetItem(QString::number(pAttenInfo->iEarlyNum)));
			}
			else if (m_nType == 0)
			{
				GetAttendState(pAttenInfo->byOnDutyStat, strStateS);
				GetAttendState(pAttenInfo->byOffDutyStat, strStateD);
			
				ui.tableWidget_Atd->setItem(nIndex, 4, new QTableWidgetItem(QString::fromLocal8Bit(pAttenInfo->byDepartment)));
				ui.tableWidget_Atd->setItem(nIndex, 4, new QTableWidgetItem(QString::fromLocal8Bit(pAttenInfo->byOffice)));
				ui.tableWidget_Atd->setItem(nIndex, 4, new QTableWidgetItem(QString::fromLocal8Bit(pAttenInfo->byCheckOnDate)));
				ui.tableWidget_Atd->setItem(nIndex, 5, new QTableWidgetItem(strStateS));
				ui.tableWidget_Atd->setItem(nIndex, 6, new QTableWidgetItem(QString::fromLocal8Bit(pAttenInfo->byOnDutyTime)));
				ui.tableWidget_Atd->setItem(nIndex, 7, new QTableWidgetItem(strStateD));
				ui.tableWidget_Atd->setItem(nIndex, 8, new QTableWidgetItem(QString::fromLocal8Bit(pAttenInfo->byOffDutyTime)));
				
			}
		}
		ui.lineEdit_Attend->setText(QString::number(nPage));
		compare_mutex.unlock();
	}
}

void CompareRecord::LoadPicture(SDK_SMART_PERSON_ATTEND_INFO* pAttendInfo, QString& libPicName)
{
	if (NULL == pAttendInfo)
	{
		return;
	}

	libPicName = QString("%1\\%2\\%3.jpg").arg(QCoreApplication::applicationDirPath() + "/" + "LibPicture").arg(m_pTreeData->pDevObj->m_pDevInfo->szIpAddr).arg(pAttendInfo->iSyslistID);
	return;
}

void  CompareRecord::on_comboBox_Attend_currentIndexChanged(int index)
{
	m_nType = ui.comboBox_Attend->currentIndex();
	QStringList header;
	if (m_nType == 0)
	{
		ui.tableWidget_Atd->setColumnCount(9);
		header << QObject::tr("头像") << QObject::tr("序号") << QObject::tr("姓名") << QObject::tr("编号") << QObject::tr("考勤时间") << QObject::tr("上班状态") << QObject::tr("上班时间") << QObject::tr("下班状态") << QObject::tr("下班时间");

	}
	else if (m_nType == 1)
	{
		ui.tableWidget_Atd->setColumnCount(10);
		header << QObject::tr("头像") << QObject::tr("序号") << QObject::tr("姓名") << QObject::tr("编号") << QObject::tr("应到次数") << QObject::tr("实际次数") << QObject::tr("正常考勤次数") << QObject::tr("未考勤次数") << QObject::tr("迟到次数")<<QObject::tr("早退次数");
	}
	ui.tableWidget_Atd->setHorizontalHeaderLabels(header);
}

void CompareRecord::GetAttendState(int nState, QString& strState)
{
	
	switch (nState)
	{
	case 0:
		strState = QObject::tr("未考勤");
		break;
	case 1:
		strState = QObject::tr("正常");
		break;
	case 2:
		strState = QObject::tr("迟到");
		break;
	}
	
}

void CompareRecord::on_btnAttendPre_clicked()
{
	int strPage = ui.lineEdit_Attend->text().toInt();
	if (strPage > 1 && strPage <= m_nCountPage)
	{
		strPage--;
		clearCurrAge(ui.tableWidget_Atd);
		CompareEvent *custevent = new CompareEvent(CET_ATTENDENCE);
		custevent->setId(strPage);
		QApplication::postEvent(this, custevent);
	}
}

void CompareRecord::on_btnAttendNext_clicked()
{
	int strPage = ui.lineEdit_Attend->text().toInt();
	if (strPage >= 1 && strPage < m_nCountPage)
	{
		strPage++;
		clearCurrAge(ui.tableWidget_Atd);
		CompareEvent *custevent = new CompareEvent(CET_ATTENDENCE);
		custevent->setId(strPage);
		QApplication::postEvent(this, custevent);
	}
}

void CompareRecord::on_btnAttendJump_clicked()
{
	int strPage = ui.lineEdit_Attend->text().toInt();
	if (strPage >= 1 && strPage <= m_nCountPage)
	{
		clearCurrAge(ui.tableWidget_Atd);
		CompareEvent *custevent = new CompareEvent(CET_ATTENDENCE);
		custevent->setId(strPage);
		QApplication::postEvent(this, custevent);
	}
}

void CompareRecord::on_btnAttendExport_clicked()
{
	if (ui.tableWidget->rowCount() == 0)
	{
		myHelper::ShowMessageBoxError(QObject::tr("导出失败，数据为空"));
		return;
	}

	QString title = QString(QObject::tr("日志记录"));
	QString fileName = QFileDialog::getSaveFileName(ui.tableWidget, QObject::tr("保存"),
		QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
		"Excel 文件(*.xls *.xlsx)");
	if (fileName != "")
	{
		QAxObject *excel = new QAxObject;
		if (excel->setControl("Excel.Application")) //连接Excel控件
		{
			excel->dynamicCall("SetVisible (bool Visible)", "false");//不显示窗体
			excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
			QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
			workbooks->dynamicCall("Add");//新建一个工作簿
			QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
			QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
			int i, j, colcount = ui.tableWidget->columnCount();
			QAxObject *cell, *col;
			//标题行
			cell = worksheet->querySubObject("Cells(int,int)", 1, 1);
			cell->dynamicCall("SetValue(const QString&)", title);
			cell->querySubObject("Font")->setProperty("Size", 18);
			//调整行高
			worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
			//合并标题行
			QString cellTitle;
			cellTitle.append("A1:");
			cellTitle.append(QChar(colcount - 1 + 'A'));
			cellTitle.append(QString::number(1));
			QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
			range->setProperty("WrapText", true);
			range->setProperty("MergeCells", true);
			range->setProperty("HorizontalAlignment", -4108);//xlCenter
			range->setProperty("VerticalAlignment", -4108);//xlCenter
			//列标题
			for (i = 0; i < colcount; i++)
			{
				QString columnName;
				columnName.append(QChar(i + 'A'));
				columnName.append(":");
				columnName.append(QChar(i + 'A'));
				col = worksheet->querySubObject("Columns(const QString&)", columnName);
				col->setProperty("ColumnWidth", ui.tableWidget->columnWidth(i) / 6);
				cell = worksheet->querySubObject("Cells(int,int)", 2, i + 1);
				columnName = ui.tableWidget->horizontalHeaderItem(i)->text();
				cell->dynamicCall("SetValue(const QString&)", columnName);
				cell->querySubObject("Font")->setProperty("Bold", true);
				cell->querySubObject("Interior")->setProperty("Color", QColor(191, 191, 191));
				cell->setProperty("HorizontalAlignment", -4108);//xlCenter
				cell->setProperty("VerticalAlignment", -4108);//xlCenter
			}
			//数据区
			for (i = 0; i < ui.tableWidget->rowCount(); i++){
				for (j = 0; j < colcount; j++)
				{
					worksheet->querySubObject("Cells(int,int)", i + 3, j + 1)->dynamicCall("SetValue(const QString&)", ui.tableWidget->item(i, j) ? ui.tableWidget->item(i, j)->text() : "");
				}
			}
			//画框线
			QString lrange;
			lrange.append("A2:");
			lrange.append(colcount - 1 + 'A');
			lrange.append(QString::number(ui.tableWidget->rowCount() + 2));
			range = worksheet->querySubObject("Range(const QString&)", lrange);
			range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
			range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
			//调整数据区行高
			QString rowsName;
			rowsName.append("2:");
			rowsName.append(QString::number(ui.tableWidget->rowCount() + 2));
			range = worksheet->querySubObject("Range(const QString&)", rowsName);
			range->setProperty("RowHeight", 20);
			workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName));//保存至fileName
			workbook->dynamicCall("Close()");//关闭工作簿
			excel->dynamicCall("Quit()");//关闭excel
			delete excel;
			excel = NULL;
			myHelper::ShowMessageBoxInfo(QObject::tr("导出成功"));
		}
		else
		{

			myHelper::ShowMessageBoxError(QObject::tr("错误，未能创建Excel对象，请安装Microsoft Excel"));
		}
	}
}

void CompareRecord::on_btnExtend_clicked()
{
	static bool v_flag = false;
	if (!v_flag)
	{
		ui.widget_Search->setVisible(false);
		v_flag = true;
		ui.btnExtend->setIcon(QPixmap(":/res/SoftIcon/you.png"));
	}
	else
	{
		ui.widget_Search->setVisible(true);

		v_flag = false;

		ui.btnExtend->setIcon(QPixmap(":/res/SoftIcon/zou.png"));
	}
}

void CompareRecord::on_btnSearchIP_clicked()
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

bool CompareRecord::event(QEvent *e)
{
	CompareEvent *event = static_cast<CompareEvent *>(e);

	if (e->type() == static_cast<QEvent::Type>(CET_ATTENDENCE))
	{
		int attendId = event->getId();
		OnSearchShow(attendId);
	}
	else if (e->type() == static_cast <QEvent::Type>(CET_COMPARISON))
	{
		int searchId = event->getId();
		SearchEnd(searchId);
	}
	
	else if (e->type() == static_cast<QEvent::Type>(CET_MESSAGEBOX))
	{
		int messId = event->getId();
		if (messId == 1)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("查询失败!"));
		}
		else if (messId == 2)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("查询超时!"));
		}
		else if (messId == 3)
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("登录设备 '%1' 失败！").arg(m_pTreeData->pDevObj->m_pDevInfo->szIpAddr));
		}		
	}
	
	return QWidget::event(event);
}


void CompareRecord::ExportIndex()
{	
	for (int i = 0; i < nCount;i++)
	{
		ui.tableWidget_Export->insertRow(i);//增加一行
		check = new QTableWidgetItem();
		check->setCheckState(Qt::Unchecked);
		ui.tableWidget_Export->setItem(i, 0, check); //插入复选框
		ui.tableWidget_Export->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(m_vectorFileInfo[i].name)));
		ui.tableWidget_Export->setItem(i, 2, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].findex.fileindex)));
		ui.tableWidget_Export->setItem(i, 3, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].findex.libindex)));
		ui.tableWidget_Export->setItem(i, 4, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].enable)));
		ui.tableWidget_Export->setItem(i, 5, new QTableWidgetItem(QString::number(m_vectorFileInfo[i].checksum)));
	}	
}

int CompareRecord::GetCheckedTree()
{
	int nCheck = 0; 
	TreeData_t* pTreeData = NULL;
	QTreeWidgetItemIterator it(ui.treeWidget);

	m_listTreeData.clear();
	while (*it)
	{
		if ((*it)->checkState(0))
		{
			QVariant var = (*it)->data(0, Qt::UserRole);
			pTreeData = (TreeData_t *)var.value<void *>();
			if (pTreeData)
			{
				m_listTreeData.push_back(pTreeData);
				++nCheck;
			}
		}
		++it;
	}
	return nCheck;
}

void CompareRecord::CreateInportWidget()
{
	if (m_listInportWidget.size() > 0)
	{
		return;
	}
	QTableWidgetItem* pWidget = NULL;
	int nItem = INPORT_COLUMN_COUNT * INPORT_ROW_COUNT;
	for (int i = 0; i < nItem; i++)
	{
		pWidget = new QTableWidgetItem("");
		if (pWidget)
		{
			m_listInportWidget.append(pWidget);
		}
	}
}

void CompareRecord::UnInitInportWidget()
{
	QTableWidgetItem* pWidget = NULL;
	int nItem = m_listInportWidget.size();
	for (int i = 0; i < nItem; i++)
	{
		pWidget = m_listInportWidget.at(i);
		if (pWidget)
		{
			delete pWidget;
			pWidget = NULL;
		}
	}
	m_listInportWidget.clear();
}

void CompareRecord::ClearInportWidget()
{
	QTableWidgetItem* pWidget = NULL;
	int nItem = INPORT_COLUMN_COUNT * INPORT_ROW_COUNT;
	for (int i = 0; i < nItem; i++)
	{
		pWidget = m_listInportWidget.at(i);
		pWidget->setText("");
	}
}



/*
//Excel表格导入
void CompareRecord::on_btnExcelImport_clicked()
{
	/*m_vectorPersonInfo.clear();
	QString strPeronInfo;
	QString m_file = QFileDialog::getOpenFileName(this, "打开", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "表格文件( *.xlsx)");
	QString Text;
	QAxObject* excel = new QAxObject();
	if (!excel->setControl("Excel.Application"))//判断是否成功连接excel文件
	{
		myHelper::ShowMessageBoxError(QObject::tr("错误，未能创建Excel对象，请安装Microsoft Excel"));
		delete excel;
		excel = NULL;
		return;
	}
	excel->setProperty("Visible", false);
	QAxObject* work_books = excel->querySubObject("WorkBooks");
	work_books->dynamicCall("Open (const QString&)", m_file);
	if (work_books == NULL)
	{
		excel->dynamicCall("Quit(void)"); //退出
		delete excel;
		excel = NULL;
		return;
	}
	QAxObject* work_book = excel->querySubObject("ActiveworkBook");
	if (work_book == NULL)
	{
		work_books->dynamicCall("Close(Boolean)", false); //关闭文件
		excel->dynamicCall("Quit(void)"); //退出
		delete work_books;
		work_books = NULL;
		delete excel;
		excel = NULL;
		return;
	}
	QAxObject* work_sheets = work_book->querySubObject("Worksheets(int)", 1);  //Sheets也可换用WorkSheets
	QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);
	QAxObject *used_range = work_sheet->querySubObject("UsedRange");
	QAxObject *rows = used_range->querySubObject("Rows");
	QAxObject *columns = used_range->querySubObject("Columns");
	int row_count = rows->property("Count").toInt();  //获取行数
	int col_count = columns->property("Count").toInt();  //获取列数

	for (int i = 1; i < row_count; i++)
	{
		for (int j = 0; j < col_count; j++)
		{
			Text = work_sheet->querySubObject("Cells(int,int)", i + 1, j + 1)->dynamicCall("Value").toString();
			if (j == 0 )
			{
				strPeronInfo = Text;
			}
			if (j == 1)
			{
				strPeronInfo = Text +"_" + strPeronInfo;
			}
			else if (j == 2)
			{
				strPeronInfo += "_" + Text + ".jpg";
			}
			else if (j == 3)
			{
				strPeronInfo = Text + "\\" + strPeronInfo;
			}
		}
		m_vectorPersonInfo.push_back(strPeronInfo);
	}

	work_books->dynamicCall("Close(Boolean)", false);
	excel->dynamicCall("Quit(void)"); //退出
	delete work_books;
	work_books = NULL;
	delete excel;
	excel = NULL;
	
	importMode = 1;

	on_btnImport_clicked();

	ExcelImport *m_excelport = new ExcelImport;
	m_excelport->show();
}*/