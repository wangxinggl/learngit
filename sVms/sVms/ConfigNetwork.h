#pragma once

#include <QWidget>
#include "ui_ConfigNetwork.h"
#include "VideoNetAPI.h"
#include <QDialog>
#include "Device/JLNDevice.h"

#pragma execution_character_set("utf-8") 

class ConfigNetwork : public QDialog
{
	Q_OBJECT

public:
	ConfigNetwork(QWidget *parent = Q_NULLPTR);
	~ConfigNetwork();
	void init();
	void GetNetWorkConfigInfo();
	void InitDlgInfo(SDK_CONFIG_NET_COMMON *pNetCommon, SDK_NetDNSConfig *pNetDNS, SDK_NetDHCPConfigAll *pNetDHCP, SDK_NetOrderConfig *pNetOrder, SDK_NetOrderFunction *pNetOrderFunc);
	void OnCHECKDHCPEnable();
	void CleaAll();
	void SaveNetCfgInfo();
	DWORD IPV4StringToInteger(QString& IP);
	void SetNetWorkConfigInfo(SDK_CONFIG_NET_COMMON *pNetCommon, SDK_NetDNSConfig *pNetDNS, SDK_NetDHCPConfigAll *pNetDHCP);
	void OnBtnLogout();

public:
	CJLNDevice* m_pDevObj;
private slots:
	void on_btnClose_clicked();
	void on_btnSave_clicked();
	void on_btnUpGrade_clicked();
	void on_lineEdit_MAC6_textChanged(const QString &arg1);
	void on_lineEdit_TCPPORT_textChanged(const QString &arg1);
	void on_lineEdit_HTTPPORT_textChanged(const QString &arg1);
	void on_btnDownSave_clicked();
	void on_checkBox_DHCPEnable_clicked();
	void on_btnDNSSave_clicked();
	void on_btnIPSave_clicked();
private:
	Ui::ConfigNetwork ui;
	bool	m_bDHCP;
	bool	m_bHightLoadDown;
	QString	m_EditMac1;
	QString	m_EditMac2;
	QString	m_EditMac3;
	QString	m_EditMac4;
	QString	m_EditMac5;
	QString	m_EditMac6;
	SDK_CONFIG_NET_COMMON m_pNetCommon;
	SDK_NetDNSConfig m_pNetDNS;
	SDK_NetDHCPConfigAll m_pNetDHCP;
	SDK_NetOrderConfig m_pNetOrder;
	SDK_NetOrderFunction m_pNetOrderFunc;
};
