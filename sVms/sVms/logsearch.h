#ifndef LOGSEARCH_H
#define LOGSEARCH_H

#include <QWidget>
#include "ui_logsearch.h"
#include "table_structs.h"
#include <QCheckBox>
#include "devtreepro.h"

class LogSearch : public QWidget
{
	Q_OBJECT

public:
	LogSearch(QWidget *parent = 0);
	~LogSearch();
	void inittableWidget_Alm();
	int GetCtrlData( int nAlarmConfId, QString sBeginTime, QString sHandleTime, QString sHandleUser);
	static DWORD WINAPI AlarmLogThread(LPVOID lpParam);
	void LogSearchPro();
	void clearCurrtable(QTableWidget *m_table);
	int   AddMsg(int nDevId, TabAlarmConf_t* pAlarmConf);

	QCheckBox *m_checkbox;
	CJLNDevice*  m_pVideoDev;
	TabAlarmVideo_t m_pVideo;
	DevTreePro *m_pTreeDev;
private slots:
	void on_btnLogAlmSearch_clicked();
	void on_btnLogDel_clicked();
	void on_btnClear_clicked();
	void on_btnExport_clicked();
public slots:
	void reflash_text(QString, QString);
		
private:
	Ui::LogSearch ui;
	std::list<TabAlarmLog_t*> m_lstAlarmLog;
	QString m_usrName;
	QString m_Password;
	bool   m_bInitFlag;
	BOOL   m_bRemove;
};

#endif // LOGSEARCH_H
