#pragma once

#include <QWidget>
#include "ui_Upgrade.h"
#include <QDialog>
#include "AnalyseVideoAreaDlg.h"

enum
{
	upgrade_success = 1,
	upgrade_upgradeing,
	upgrade_failed,
};

class Upgrade : public QDialog
{
	Q_OBJECT

public:
	Upgrade(QWidget *parent = Q_NULLPTR);
	~Upgrade();
	void initUPgradeInfo();
	static void CALL_METHOD UpgradeCallBack(JVT_LONG lLoginID, long lUpgradechannel, int nTotalSize, int nSendSize, JVT_DWORD dwUser);
	long  OnUpgradeStaus(int nPos);
	CJLNDevice* m_pDevObj;

	BOOL m_bSendStatus;
	BOOL m_bUpgradeStatus;

	void EnableBtn(bool bStatus);

private slots:
	void on_btnClose_clicked(); //关闭窗口
	void on_btnSelect_clicked();//选择升级文件
	void on_btnUpgrade_clicked();//升级
	void on_btnRestart_clicked();//重启
	void on_btnRestore_clicked();//恢复出厂设置
	void on_btnFormat_clicked();//格式化

private:
	Ui::Upgrade ui;
	QString upGradeFileName;
	long    m_lUpgradeHandle;

};
