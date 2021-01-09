#pragma once

#include <QWidget>
#include "ui_BehaviorAnalyseDlg.h"
#include "devtreepro.h"
#include <QTimerEvent>
#include "Configsetting.h"
#include "myhelper.h"
#include <QDesktopServices>
#include "AnalysisDlg.h"
#include "Upgrade.h"
#include "StreamSet.h"
#include "ParamMeteSet.h"
#include "FaceAlarm.h"
#include "ConfigNetwork.h"
#include "VideoWarning.h"
#include "ImageSet.h"
#include "OrdinarySet.h"

#pragma execution_character_set("utf-8") 

class BehaviorAnalyseDlg : public QWidget
{
	Q_OBJECT

public:
	BehaviorAnalyseDlg(QWidget *parent = Q_NULLPTR);
	~BehaviorAnalyseDlg();
	void initTree();
	void initSearchButton();//设置搜索框样式
	void GetDeviceInfo();
	void GetDeviceConfigInfo();
	void ShowLoginErrorReason(int nError);
	void InitDlgInfo();
	void OnTreeReFresh();
	BOOL CheckDevStatus();		//判断设备状态
	void EnableButton(bool bEnable);
private slots:
	//tree点击事件Button(bool bEnable)
	void OnlineTreeViewDoubleClick(const QModelIndex & index);
	void on_btnEncode_clicked();  //码流设置
	void on_btnWeb_clicked();	  //链接网页
	void on_btnUpGrade_clicked(); //升级	
	void on_btnArea_clicked();
	void on_btnFace_clicked();
	void on_btnWarning_clicked();
	void on_btnNetWork_clicked();
	void searchIP();
	void on_btnVideoWarning_clicked();
	void on_btnImageSet_clicked();
	void on_btnordinarySet_clicked();
public:
	DevTreePro *m_pTreeDev;
	CJLNDevice* m_pDevObj;

	StreamSet *m_pStreamSetDlg;
	Upgrade* m_pUpgradeDlg;
	AnalysisDlg* m_pAnalysisDlg;
	OrdinarySet *m_pOrdinarySetDlg;
	VideoWarning *m_pVideoWarningDlg;
	ImageSet *m_pImageSetDlg;
	ParamMeteSet *m_pParamMeteSetDlg;
	FaceAlarm *m_pAlarmDlg;
	ConfigNetwork *m_pNetworkDlg;

	QPushButton *m_pSearchButton;
	QHBoxLayout *m_pSearchLayout;
private:
	Ui::BehaviorAnalyseDlg ui;

	SDK_CONFIG_NORMAL* m_pstConfigNormal;
	SDK_MultiLangFunction* m_pstLangConfig;
	int m_lDevType;
};
