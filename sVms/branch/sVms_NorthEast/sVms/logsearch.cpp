#include "logsearch.h"
#include <QMutex>
#include <QMessageBox>
#include "DB.h"
#include "login.h"
#include <QFileDialog>
#include <QDesktopServices>
#include <QAxObject>
#include "MessBox.h"
#include <QDateTime>

int g_EmapId = 0;
QMutex logAlm_mutex;
LogSearch::LogSearch(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	inittableWidget_Alm();
	ui.dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
	ui.dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

	QString strBuffer = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	strBuffer = strBuffer.left(11) + "00:00:00";
	QDateTime time = QDateTime::fromString(strBuffer, "yyyy-MM-dd hh:mm:ss");
	ui.dateTimeEdit->setDateTime(time);
	ui.dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
	Login *log = new Login();

	connect(log,SIGNAL(SendUserMessage(QString,QString)),this,SLOT(reflash_text(QString,QString)));
	log->sendSignal();

	m_checkbox = new QCheckBox();
	m_checkbox = ui.checkBox;
	m_bRemove = FALSE;
	m_bInitFlag = false;
	
	m_pVideoDev = NULL;
	memset(&m_pVideo, 0, sizeof(m_pVideo));
}

LogSearch::~LogSearch()
{

}


void LogSearch::inittableWidget_Alm()
{
	QStringList header;
	ui.tableWidget_Alm->setColumnCount(4);

	header <<QObject::tr("设备名称")<<QObject::tr("告警源")<<QObject::tr("通道")<<QObject::tr("开始时间");
	ui.tableWidget_Alm->setHorizontalHeaderLabels(header);
	ui.tableWidget_Alm->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
	ui.tableWidget_Alm->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.tableWidget_Alm->setSortingEnabled(true);
	ui.tableWidget_Alm->horizontalHeader()->setStretchLastSection(true); //就是这个地方
	ui.tableWidget_Alm->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽
	ui.tableWidget_Alm->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应行高
}
void LogSearch::on_btnLogAlmSearch_clicked()
{
	
	logAlm_mutex.lock();
	ui.tableWidget_Alm->clearContents();
	clearCurrtable(ui.tableWidget_Alm);
	logAlm_mutex.unlock();
	if (m_lstAlarmLog.size() != 0)
	{
		std::list<TabAlarmLog_t*> ::iterator iter;
		for (iter = m_lstAlarmLog.begin(); iter != m_lstAlarmLog.end(); ++iter)
		{
			if (*iter != NULL)
				delete *iter;
		}
		m_lstAlarmLog.clear();
	}
	QString m_TimeBegin = ui.dateTimeEdit->text();
	QString m_TimeEnd = ui.dateTimeEdit_2->text();

	if (QString::compare(m_TimeBegin, m_TimeEnd) > 0)
	{
		//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("开始时间不能大于结束时间!"));
		myHelper::ShowMessageBoxWarning(QObject::tr("开始时间不能大于结束时间!"));
		return;
	}

	else
	{
		QDateTime m_beginTime = QDateTime::fromString(m_TimeBegin, "yyyy-MM-dd hh:mm:ss");
		QDateTime m_endTime = QDateTime::fromString(m_TimeEnd, "yyyy-MM-dd hh:mm:ss");
		if (m_beginTime.secsTo(m_endTime) > 7 * 24 * 60 * 60)
		{
			//QMessageBox::information(this, QObject::tr("警告"), QObject::tr("时间不能超过7天!"));
			myHelper::ShowMessageBoxWarning(QObject::tr("时间不能超过7天!"));
			return;
		}
	}
	

	DB *db = new DB;
	if (db->QuerryAlarmLog(m_lstAlarmLog, m_TimeBegin, m_TimeEnd) <= 0)
		return;
	ui.btnLogAlmSearch->setEnabled(false);
	ui.btnLogAlmSearch->setText(QObject::tr("搜索中..."));
	

	DWORD dwThreadID = 0;
	HANDLE hThread = CreateThread(NULL, 0, AlarmLogThread, this, CREATE_SUSPENDED, &dwThreadID);
	if (hThread != NULL)
	{
		ResumeThread(hThread);//唤醒线程
		CloseHandle(hThread);//关闭线程句柄，线程并不会结束，便于回收资源
		hThread = NULL;
	}
	
}

DWORD WINAPI LogSearch::AlarmLogThread(LPVOID lpParam)
{
	LogSearch *pDlg = (LogSearch  *)lpParam;
	pDlg->LogSearchPro();
	return TRUE;
}
void LogSearch::LogSearchPro()
{
	
	std::list<TabAlarmLog_t*> ::iterator iter;
	for (iter = m_lstAlarmLog.begin(); iter != m_lstAlarmLog.end(); ++iter)
	{
		GetCtrlData((*iter)->AlarmConfId, (*iter)->szBeginTime, "", "");
	}
	ui.btnLogAlmSearch->setEnabled(true);
	ui.btnLogAlmSearch->setText(QObject::tr("查询"));
}
int LogSearch::GetCtrlData(int nAlarmConfId, QString sBeginTime, QString sHandleTime, QString sHandleUser)
{
	DB *db = new DB;
	int devId, alarmSrc, channel, alarmType, alarmLevel;
	int ix = 0;
	QString szDevName;
	QString szTmp;
	int nColumn = db->getAlarmConfMsg(nAlarmConfId, devId,alarmSrc,channel,alarmType,alarmLevel);
		
	for (int i = 0;i<1;i++)
	{
		for (int j = 0;j < nColumn ;j++)
		{
			if (j == 0)
			{
				int nRow = db->getDevInfo(devId, szDevName);
				if (nRow != 0)
				{
					ix = ui.tableWidget_Alm->rowCount();
					ui.tableWidget_Alm->insertRow(ix);//增加一行
				}
			}
			if (j == 1)
			{
				ui.tableWidget_Alm->setItem(ix, 0, new QTableWidgetItem(szDevName));
			}
			if (j == 2)
			{
				switch (alarmSrc)
				{
				case ALARM_SOURCE_ALARMIN:
					szTmp = QObject::tr("报警输入");
					break;
				case ALARM_SOURCE_MOVING_DETECT:
					szTmp = QObject::tr("移动报警");
					break;
				case ALARM_SOURCE_LOSE_SIGNAL:
					szTmp = QObject::tr("视频丢失");
					break;
				case ALARM_DISK_BAD:
					szTmp = QObject::tr("硬盘损坏");
					break;
				case ALARM_SOURCE_VIDEO_BLIND:
					szTmp = QObject::tr("遮挡报警");
					break;
				case ALARM_EventBrightness:
					szTmp = QObject::tr("亮度异常");
					break;
				case ALARM_EventShelter:
					szTmp = QObject::tr("视频异常");
					break;
				case ALARM_EventCrossLine:
					szTmp = QObject::tr("越界侦测");
					break;
				case ALARM_EventCrossArea:
					szTmp = QObject::tr("区域入侵");
					break;
				case ALARM_EventColor:
					szTmp = QObject::tr("颜色异常");
					break;
				case ALARM_EventSound:
					szTmp = QObject::tr("声音异常");
					break;
				case ALARM_EventLoseOBJ:
					szTmp = QObject::tr("遗留物");
					break;
				default:
					szTmp = "";
					break;
				}
				ui.tableWidget_Alm->setItem(ix, 1, new QTableWidgetItem(szTmp));
			}
			if (j == 3)
			{
				ui.tableWidget_Alm->setItem(ix, 2, new QTableWidgetItem(QString::number(channel)));
			}
			if (j == 4)
			{
				switch (alarmType)
				{
				case AALARM_TYPE_FIRE:
					szTmp = QObject::tr("火警");
					break;
				case ALARM_TYPE_SMOKING:
					szTmp = QObject::tr("烟警");
					break;
				case ALARM_TYPE_INFRARED:
					szTmp = QObject::tr("红外线");
					break;
				case ALARM_TYPE_GAS:
					szTmp = QObject::tr("气体");
					break;
				case ALARM_TYPE_TEMPERATURE:
					szTmp = QObject::tr("温度");
					break;
				case ALARM_TYPE_GATING:
					szTmp = QObject::tr("门控");
					break;
				default:
					szTmp = QObject::tr("无");
					break;
				}
				//ui.tableWidget_Alm->setItem(ix, 3, new QTableWidgetItem(QString::number(channel)));
				ui.tableWidget_Alm->setItem(ix, 3, new QTableWidgetItem(sBeginTime));
			}
			if (j == 5)
			{
				switch (alarmLevel)
				{
				case ALARM_LEVEL_CRITICAL:
					
					break;
				case ALARM_LEVEL_MAJOR:
					
					break;
				case ALARM_LEVEL_MINOR:
				
					break;
				case ALARM_LEVEL_WARNING:
	
					break;
				}
			}
		}
	}

	
	return 0;
}

void LogSearch::on_btnLogDel_clicked()
{
	if(strcmp(m_usrName.toLatin1().data(),"admin") != 0)
	{
		//QMessageBox::information(this,QObject::tr("警告"),QObject::tr("没有权限,请使用admin用户登录!!"));
		myHelper::ShowMessageBoxWarning(QObject::tr("没有权限,请使用admin用户登录!!"));
		return;
	}

	logAlm_mutex.lock();
	QList<QTableWidgetItem*> items = ui.tableWidget_Alm->selectedItems();
	int count = items.count();
	int row = ui.tableWidget_Alm->row(items.at(0));
	QTableWidgetItem *item = items.at(0);
	QTableWidgetItem *itemTime = items.at(3);
	QString sDevName = item->text(); //获取内容
	QString sBeginTime = itemTime->text();
	ui.tableWidget_Alm->removeRow(row);
	logAlm_mutex.unlock();
	int nId = 0;
	if (m_lstAlarmLog.size() != 0)
	{
		std::list<TabAlarmLog_t*> ::iterator iter;
		for (iter = m_lstAlarmLog.begin(); iter != m_lstAlarmLog.end(); ++iter)
		{
			if (strncmp(sBeginTime.toLatin1().data(), (*iter)->szBeginTime, sBeginTime.length()) == 0)
			{
				nId = (*iter)->Id;
				delete (*iter);
				(*iter) = NULL;
				break;
			}
		}
		if (nId != 0)
		{
			DB * db = new DB;
			db->DeleteAlarmLog(nId);
		}
	}
}

void LogSearch::reflash_text(QString UsrName,QString Password)
{
	m_usrName = UsrName;
	m_Password = Password;
}

void LogSearch::clearCurrtable(QTableWidget *m_table)
{
	int iLen = m_table->rowCount();
	for (int i = 0; i < iLen; i++)
	{
		m_table->removeRow(0);
	}
}

void LogSearch::on_btnClear_clicked()
{
	ui.tableWidget_Alm->clearContents();
	clearCurrtable(ui.tableWidget_Alm);
	int nId = 0;
	if (m_lstAlarmLog.size() != 0)
	{
		std::list<TabAlarmLog_t*> ::iterator iter;
		for (iter = m_lstAlarmLog.begin(); iter != m_lstAlarmLog.end(); ++iter)
		{
			delete (*iter);
			(*iter) = NULL;
			
		}
		DB * db = new DB;
		db->DeleteAlarmLog(nId,true);
		
	}
}

void LogSearch::on_btnExport_clicked()
{
	if (ui.tableWidget_Alm->rowCount() == 0)
	{
		myHelper::ShowMessageBoxError(QObject::tr("导出失败，数据为空"));
		return;
	}
	QString title = QString(QObject::tr("日志记录"));
	QString fileName = QFileDialog::getSaveFileName(ui.tableWidget_Alm, QObject::tr("保存"),
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
			int i, j, colcount = ui.tableWidget_Alm->columnCount();
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
				col->setProperty("ColumnWidth", ui.tableWidget_Alm->columnWidth(i) / 6);
				cell = worksheet->querySubObject("Cells(int,int)", 2, i + 1);
				columnName = ui.tableWidget_Alm->horizontalHeaderItem(i)->text();
				cell->dynamicCall("SetValue(const QString&)", columnName);
				cell->querySubObject("Font")->setProperty("Bold", true);
				cell->querySubObject("Interior")->setProperty("Color", QColor(191, 191, 191));
				cell->setProperty("HorizontalAlignment", -4108);//xlCenter
				cell->setProperty("VerticalAlignment", -4108);//xlCenter
			}
			//数据区
			for (i = 0; i < ui.tableWidget_Alm->rowCount(); i++){
				for (j = 0; j < colcount; j++)
				{
					worksheet->querySubObject("Cells(int,int)", i + 3, j + 1)->dynamicCall("SetValue(const QString&)", ui.tableWidget_Alm->item(i, j) ? ui.tableWidget_Alm->item(i, j)->text() : "");
				}
			}
			//画框线
			QString lrange;
			lrange.append("A2:");
			lrange.append(colcount - 1 + 'A');
			lrange.append(QString::number(ui.tableWidget_Alm->rowCount() + 2));
			range = worksheet->querySubObject("Range(const QString&)", lrange);
			range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
			range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
			//调整数据区行高
			QString rowsName;
			rowsName.append("2:");
			rowsName.append(QString::number(ui.tableWidget_Alm->rowCount() + 2));
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

int LogSearch::AddMsg(int nDevId, TabAlarmConf_t* pAlarmConf, TabAlarmVideo_t* pVideo)
{
	DB *db = new DB;
	int nCount;
	int IDX;
	QString strST;
	QString  strAT;
	TCHAR   strLevel[128] = { 0, };
	char szChannel[16];

	if (!m_bInitFlag)
	{
		return 0;
	}
	itoa(pAlarmConf->Channel, szChannel, 10);
	tree = new DevTreePro;
	CBaseDeviceInfo*  devInfo = tree->GetBaseDeviceInfo(-1, nDevId);
	if (devInfo == NULL)
		return 0;

	switch (pAlarmConf->AlarmSource)
	{
	case ALARM_SOURCE_ALARMIN:
		strST = QObject::tr("报警输入");
		break;
	case ALARM_SOURCE_MOVING_DETECT:
		strST = QObject::tr("移动报警");
		break;
	case ALARM_SOURCE_LOSE_SIGNAL:
		strST = QObject::tr("视频丢失");
		break;
	case ALARM_DISK_BAD:
		strST = QObject::tr("硬盘损坏");
		break;
	case ALARM_CRT_SERVER:
		strST = QObject::tr("告警主机");
		break;
	case ALARM_SOURCE_VIDEO_BLIND:
		strST = QObject::tr("遮挡报警");
		break;

	case ALARM_EventBrightness:
		strST = QObject::tr("亮度异常");
		break;
	case ALARM_EventShelter:
		strST = QObject::tr("视频异常");
		break;
	case ALARM_EventCrossLine:
		strST = QObject::tr("越界侦测");
		break;
	case ALARM_EventCrossArea:
		strST = QObject::tr("区域入侵");
		break;
	case ALARM_EventColor:
		strST = QObject::tr("颜色异常");
		break;
	case ALARM_EventSound:
		strST = QObject::tr("声音异常");
		break;
	case ALARM_EventLoseOBJ:
		strST = QObject::tr("遗留物");
		break;
	case ALARM_DISK_LOW:
		strST = QObject::tr("磁盘空间低");
		break;
	default:
		strST = QObject::tr("");
		break;
	}
	switch (pAlarmConf->AlarmType)
	{
	case AALARM_TYPE_FIRE:
		strAT = QObject::tr("火警");
		break;
	case ALARM_TYPE_SMOKING:
		strAT = QObject::tr("烟警");
		break;
	case ALARM_TYPE_INFRARED:
		strAT = QObject::tr("红外线");
		break;
	case ALARM_TYPE_GAS:
		strAT = QObject::tr("气体");
		break;
	case ALARM_TYPE_TEMPERATURE:
		strAT = QObject::tr("温度");
		break;
	case ALARM_TYPE_GATING:
		strAT = QObject::tr("门控");
		break;
		/*case :
		strAT = _T("设备掉线");
		break;
		case :
		strAT = _T("设备上线");
		break;*/
	default:
		//strAT = "无";
		break;
	}

	/*switch (pAlarmConf->AlarmLevel)
	{
	case ALARM_LEVEL_CRITICAL:
		GetPrivateProfileString("SetAlarmDlg", "0005", "Critical", strLevel, 128, g_strLangIniFile);
		break;
	case ALARM_LEVEL_MAJOR:
		GetPrivateProfileString("SetAlarmDlg", "0006", "Major", strLevel, 128, g_strLangIniFile);
		break;
	case ALARM_LEVEL_MINOR:
		GetPrivateProfileString("SetAlarmDlg", "0007", "Minor", strLevel, 128, g_strLangIniFile);
		break;
	case ALARM_LEVEL_WARNING:
		GetPrivateProfileString("SetAlarmDlg", "0008", "Warning", strLevel, 128, g_strLangIniFile);
		break;
	}*/

	QDateTime m_StartTime1 = QDateTime::currentDateTime();
	QString csStartTime = m_StartTime1.toString("yyyy-MM-dd hh:mm:ss");

	logAlm_mutex.lock();
	nCount = ui.tableWidget_Alm->rowCount();
	ui.tableWidget_Alm->insertRow(nCount);//增加一行
	ui.tableWidget_Alm->setItem(nCount, 0, new QTableWidgetItem(QString::fromLocal8Bit(devInfo->GetDevInfo()->szDevName)));
	ui.tableWidget_Alm->setItem(nCount, 1, new QTableWidgetItem(QString::fromLocal8Bit(pAlarmConf->szAlarmName)));
	ui.tableWidget_Alm->setItem(nCount, 2, new QTableWidgetItem(strST));
	ui.tableWidget_Alm->setItem(nCount, 3, new QTableWidgetItem(QString(QLatin1String(szChannel))));
	ui.tableWidget_Alm->setItem(nCount, 4, new QTableWidgetItem(strAT));
	ui.tableWidget_Alm->setItem(nCount, 5, new QTableWidgetItem(csStartTime));
	ui.tableWidget_Alm->setItem(nCount, 6, new QTableWidgetItem(QString(QLatin1String(strLevel))));
	ui.tableWidget_Alm->setItem(nCount, 7, new QTableWidgetItem(QString::number(pAlarmConf->Video)));
	logAlm_mutex.unlock();

	if (pVideo != NULL && m_pVideo.SlaveDevId == pVideo->SlaveDevId)
	{
		if (pVideo->PresetPosId == 0 || m_pVideo.PresetPosId == pVideo->PresetPosId)
			return 0;

		//不用停视频，切换预置点和显示
		QString str, newstr;
		//GetDlgItem(IDC_STATIC3)->GetWindowText(str);
		sscanf(str.toLatin1().data(), "%[^ ]", newstr);
		newstr += "    预置点:";

		TabPresetPos_t tabPresetPos[257]; //0不使用;1~256
		if (db->QueryPrestPos(tabPresetPos, -1, pVideo->PresetPosId) != 1)
			return 0;
		int nPos = tabPresetPos[1].PresetNo;
		//m_pVideoDev->PtzCtrl(m_pWnd->m_hWnd, eGOTO_PRESET, 0, nPos);
		newstr += tabPresetPos[1].szPresetDesc;
		//GetDlgItem(IDC_STATIC3)->SetWindowText(newstr);
		m_pVideo.PresetPosId = pVideo->PresetPosId;
		return 0;
	}

	if (m_bRemove && m_pVideoDev != NULL)
	{
		//m_pVideoDev->CloseChannel(m_pWnd->m_hWnd);
		//m_pWnd->Invalidate();
		m_pVideoDev = NULL;
		m_bRemove = FALSE;
		memset(&m_pVideo, 0, sizeof(m_pVideo));
	}

	if (pVideo != NULL && pVideo->SlaveDevId > 0)
	{
		m_pVideoDev = tree->GetBaseDeviceInfo(pVideo->SlaveDevId, -1);
		if (m_pVideoDev == NULL)
			return 0;
		int nStream = DEVICE_MAIN_STREAM;
		TabChannelInfo_t* pChannel = tree->GetChannelInfo(pVideo->SlaveDevId);
		if (pChannel == NULL)
			return 0;
		int nChannel = pChannel->Channel;
		//m_pVideoDev->OpenChannel(nChannel, nStream, m_pWnd->m_hWnd, 0);
		QString str;
		str = QObject::tr("视频:%1    预置点:").arg( pChannel->szChannelName);
		if (pVideo->PresetPosId > 0)
		{
			TabPresetPos_t tabPresetPos[257]; //0不使用;1~256
			if (db->QueryPrestPos(tabPresetPos, -1, pVideo->PresetPosId) != 1)
				return 0;
			int nPos = tabPresetPos[1].PresetNo;
			//m_pVideoDev->PtzCtrl(m_pWnd->m_hWnd, eGOTO_PRESET, 0, nPos);
			str += tabPresetPos[1].szPresetDesc;
		}
		else
			str += "无";

		
		memcpy(&m_pVideo, pVideo, sizeof(m_pVideo));
		m_bRemove = TRUE;
	}
	
	g_EmapId = pAlarmConf->Emap;
	return  1;

}