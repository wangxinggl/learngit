#define  _CRT_SECURE_NO_WARNINGS
#include "ConfigNetwork.h"
#include "myhelper.h"
#include <string>
using namespace std;

#define swap_long(x) (((((unsigned long)(x)) & 0xff000000) >> 24) | \
	((((unsigned long)(x)) & 0x00ff0000) >> 8) | \
	((((unsigned long)(x)) & 0x0000ff00) << 8) | \
	((((unsigned long)(x)) & 0x000000ff) << 24)\
	)
ConfigNetwork::ConfigNetwork(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_bDHCP = false;
	m_bHightLoadDown = false;
	m_EditMac1 = "";
	m_EditMac2 = "";
	m_EditMac3 = "";
	m_EditMac4 = "";
	m_EditMac5 = "";
	m_EditMac6 = "";
	init();
	ui.btnSave->setVisible(false);
}

ConfigNetwork::~ConfigNetwork()
{
}

void ConfigNetwork::init()
{
	CleaAll();
	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setStyleSheet(".ConfigNetwork{border:2px solid black;}");
}

void ConfigNetwork::GetNetWorkConfigInfo()
{
	if (0 != m_pDevObj->m_lUserLoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NET_COMMON NetWorkCfg;

		BOOL bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_SYSNET, 0,
			(char *)&NetWorkCfg, sizeof(SDK_CONFIG_NET_COMMON), &dwRetLen, nWaitTime);
		long longtest = sizeof(SDK_CONFIG_NET_COMMON);
		if (bSuccess && dwRetLen == sizeof(SDK_CONFIG_NET_COMMON))
		{
			SDK_NetDNSConfig NetDNSCfg;
			bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_NET_DNS, 0,
				(char *)&NetDNSCfg, sizeof(SDK_NetDNSConfig), &dwRetLen, nWaitTime);

			if (bSuccess && dwRetLen == sizeof(SDK_NetDNSConfig))
			{
				SDK_NetDHCPConfigAll NetDHPCfg;
				bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_NET_DHCP, 0,
					(char *)&NetDHPCfg, sizeof(SDK_NetDHCPConfigAll), &dwRetLen, nWaitTime);
				if (bSuccess && dwRetLen == sizeof(SDK_NetDHCPConfigAll))
				{
					SDK_NetOrderConfig NetOrder;
					bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_NET_ORDER, 0,
						(char *)&NetOrder, sizeof(SDK_NetOrderConfig), &dwRetLen, nWaitTime);
					if (bSuccess)//&& dwRetLen == sizeof(SDK_NetOrderConfig)
					{
						SDK_NetOrderFunction NetOrderFunc;
						bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_ABILITY_NETORDER, 0,
							(char *)&NetOrderFunc, sizeof(SDK_NetOrderFunction), &dwRetLen, nWaitTime);
						if (bSuccess)
						{
							InitDlgInfo(&NetWorkCfg, &NetDNSCfg, &NetDHPCfg, &NetOrder, &NetOrderFunc);
						}

					}

				}
			}
		}
	}
}

void ConfigNetwork::OnCHECKDHCPEnable()
{
	BOOL nEnable = m_bDHCP;
	ui.lineEdit_NETIP->setEnabled(!nEnable);
	ui.lineEdit_NETIPMASK->setEnabled(!nEnable);
	ui.lineEdit_NETGATEWAY->setEnabled(!nEnable);
}
void ConfigNetwork::InitDlgInfo(SDK_CONFIG_NET_COMMON *pNetCommon, SDK_NetDNSConfig *pNetDNS, SDK_NetDHCPConfigAll *pNetDHCP, SDK_NetOrderConfig *pNetOrder, SDK_NetOrderFunction *pNetOrderFunc)
{
	if (m_pDevObj->m_pDevInfo->nType == SDK_DEV_TYPE_IPC)
	{
		ui.label_Downed->setVisible(false);
		ui.checkBox_HIGHTLOADDOWN->setVisible(false);
		ui.label_chuanshu->setVisible(false);
		ui.comboBox_TRANSFERPOLICY->setVisible(false);
	}
	ui.comboBox_NETCARD->clear();
	ui.comboBox_NETCARD->addItem(QObject::tr("有线网卡"));
	ui.comboBox_NETCARD->setCurrentIndex(0);
	
	ui.comboBox_TRANSFERPOLICY->clear();
	ui.comboBox_TRANSFERPOLICY->addItem(QObject::tr("自适应"));
	ui.comboBox_TRANSFERPOLICY->addItem(QObject::tr("画质优先"));
	ui.comboBox_TRANSFERPOLICY->addItem(QObject::tr("流畅优先"));
	ui.comboBox_TRANSFERPOLICY->setCurrentIndex(pNetCommon->TransferPlan);
	memcpy(&m_pNetCommon, pNetCommon, sizeof(SDK_CONFIG_NET_COMMON));
	memcpy(&m_pNetDHCP, pNetDHCP, sizeof(SDK_NetDHCPConfigAll));
	memcpy(&m_pNetDNS, pNetDNS, sizeof(SDK_NetDNSConfig));
	memcpy(&m_pNetOrder, pNetOrder, sizeof(SDK_NetOrderConfig));
	memcpy(&m_pNetOrderFunc, pNetOrderFunc, sizeof(SDK_NetOrderFunction));
	m_bHightLoadDown = pNetCommon->bUseHSDownLoad;
	ui.checkBox_HIGHTLOADDOWN->setChecked(m_bHightLoadDown);
	m_bDHCP = pNetDHCP->vNetDHCPConfig[0].bEnable;
	ui.checkBox_DHCPEnable->setChecked(m_bDHCP);
	OnCHECKDHCPEnable();
	ui.lineEdit_NETIP->setText(QString("%1.%2.%3.%4").arg(pNetCommon->HostIP.c[0]).arg(pNetCommon->HostIP.c[1]).arg(pNetCommon->HostIP.c[2]).arg(pNetCommon->HostIP.c[3]));
	ui.lineEdit_NETIPMASK->setText(QString("%1.%2.%3.%4").arg(pNetCommon->Submask.c[0]).arg(pNetCommon->Submask.c[1]).arg(pNetCommon->Submask.c[2]).arg(pNetCommon->Submask.c[3]));
	ui.lineEdit_NETGATEWAY->setText(QString("%1.%2.%3.%4").arg(pNetCommon->Gateway.c[0]).arg(pNetCommon->Gateway.c[1]).arg(pNetCommon->Gateway.c[2]).arg(pNetCommon->Gateway.c[3]));
	ui.lineEdit_PRIMARYDNS->setText(QString("%1.%2.%3.%4").arg(pNetDNS->PrimaryDNS.c[0]).arg(pNetDNS->PrimaryDNS.c[1]).arg(pNetDNS->PrimaryDNS.c[2]).arg(pNetDNS->PrimaryDNS.c[3]));
	ui.lineEdit_SECONDARYDNS->setText(QString("%1.%2.%3.%4").arg(pNetDNS->SecondaryDNS.c[0]).arg(pNetDNS->SecondaryDNS.c[1]).arg(pNetDNS->SecondaryDNS.c[2]).arg(pNetDNS->SecondaryDNS.c[3]));

	ui.lineEdit_TCPPORT->setText(QString::number(pNetCommon->TCPPort));
	ui.lineEdit_HTTPPORT->setText(QString::number(pNetCommon->HttpPort));
	//mac
	QString strTemp = pNetCommon->sMac;
	ui.lineEdit_MAC1->setText(strTemp.section(":",0,0));
	ui.lineEdit_MAC2->setText(strTemp.section(":", 1, 1));
	ui.lineEdit_MAC3->setText(strTemp.section(":", 2, 2));
	ui.lineEdit_MAC4->setText(strTemp.section(":", 3, 3));
	ui.lineEdit_MAC5->setText(strTemp.section(":", 4, 4));
	ui.lineEdit_MAC6->setText(strTemp.section(":", 5, 5));
	
	if (!m_pNetOrderFunc.bNetOrder)
	{
		ui.label_chuanshu->setVisible(false);
		ui.comboBox_TRANSFERPOLICY->setVisible(false);
	
	}
}

void ConfigNetwork::on_btnClose_clicked()
{
	close();
}

void ConfigNetwork::CleaAll()
{
	ui.comboBox_TRANSFERPOLICY->clear();
	ui.comboBox_NETCARD->clear();
	ui.lineEdit_TCPPORT->setText("");
	ui.lineEdit_HTTPPORT->setText("");
	ui.lineEdit_MAC1->setText("");
	ui.lineEdit_MAC2->setText("");
	ui.lineEdit_MAC3->setText("");
	ui.lineEdit_MAC4->setText("");
	ui.lineEdit_MAC5->setText("");
	ui.lineEdit_MAC6->setText("");
	ui.checkBox_HIGHTLOADDOWN->setChecked(false);
	OnCHECKDHCPEnable();
	m_bDHCP = FALSE;
	ui.lineEdit_NETIP->setText("0.0.0.0");
	ui.lineEdit_NETGATEWAY->setText("0.0.0.0");
	ui.lineEdit_NETIPMASK->setText("0.0.0.0");
	ui.lineEdit_PRIMARYDNS->setText("0.0.0.0");
	ui.lineEdit_SECONDARYDNS->setText("0.0.0.0");
}

void ConfigNetwork::on_btnSave_clicked()
{
	if (ui.comboBox_NETCARD->currentIndex() != -1)
	{
		SaveNetCfgInfo();
		SetNetWorkConfigInfo(&m_pNetCommon, &m_pNetDNS, &m_pNetDHCP);
	}
}

void ConfigNetwork::SaveNetCfgInfo()
{
	m_pNetCommon.bUseHSDownLoad = m_bHightLoadDown;
	m_pNetDHCP.vNetDHCPConfig[0].bEnable = m_bDHCP;
	m_pNetCommon.TCPPort = ui.lineEdit_TCPPORT->text().toInt();
	m_pNetCommon.HttpPort = ui.lineEdit_HTTPPORT->text().toInt();
	m_pNetCommon.TransferPlan = ui.comboBox_TRANSFERPOLICY->currentIndex();
	DWORD dwIP = IPV4StringToInteger(ui.lineEdit_NETIP->text());
	m_pNetCommon.HostIP.l = swap_long(dwIP);
	DWORD dwIPMask = IPV4StringToInteger(ui.lineEdit_NETIPMASK->text());
	m_pNetCommon.Submask.l = swap_long(dwIPMask);
	DWORD dwGateWay = IPV4StringToInteger(ui.lineEdit_NETGATEWAY->text());
	m_pNetCommon.Gateway.l = swap_long(dwGateWay);
	DWORD dwPrimary = IPV4StringToInteger(ui.lineEdit_PRIMARYDNS->text());
	m_pNetDNS.PrimaryDNS.l = swap_long(dwPrimary);
	DWORD dwSeconddary = IPV4StringToInteger(ui.lineEdit_SECONDARYDNS->text());
	m_pNetDNS.SecondaryDNS.l = swap_long(dwSeconddary);

	QString strMac;
	strMac = ui.lineEdit_MAC1->text() + ":" + ui.lineEdit_MAC2->text() + ":" + ui.lineEdit_MAC3->text()
		+ ":" + ui.lineEdit_MAC4->text() + ":" + ui.lineEdit_MAC5->text() + ":" + ui.lineEdit_MAC6->text();
	strcpy(m_pNetCommon.sMac, strMac.toLocal8Bit().data());
}

DWORD ConfigNetwork::IPV4StringToInteger(QString& IP)
{
	QStringList ips = IP.split(".");
	if (ips.size() == 4){
		return ips.at(3).toInt()
			| ips.at(2).toInt() << 8
			| ips.at(1).toInt() << 16
			| ips.at(0).toInt() << 24;
	}
	return 0;
}

void ConfigNetwork::SetNetWorkConfigInfo(SDK_CONFIG_NET_COMMON *pNetCommon, SDK_NetDNSConfig *pNetDNS, SDK_NetDHCPConfigAll *pNetDHCP)
{
	if (0 != m_pDevObj->m_lUserLoginID && pNetCommon != NULL && pNetDNS != NULL && pNetDHCP != NULL)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NET_COMMON NetWorkCfg;
		BOOL bReboot = FALSE;
		BOOL bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_SYSNET, 0,
			(char *)&NetWorkCfg, sizeof(SDK_CONFIG_NET_COMMON), &dwRetLen, nWaitTime);
		if (bSuccess && dwRetLen == sizeof (SDK_CONFIG_NET_COMMON))
		{
			memcpy(&NetWorkCfg.HostIP, &pNetCommon->HostIP, sizeof(CONFIG_IPAddress));
			memcpy(&NetWorkCfg.Gateway, &pNetCommon->Gateway, sizeof(CONFIG_IPAddress));
			memcpy(&NetWorkCfg.Submask, &pNetCommon->Submask, sizeof(CONFIG_IPAddress));
			NetWorkCfg.TCPPort = pNetCommon->TCPPort;
			NetWorkCfg.HttpPort = pNetCommon->HttpPort;
			strcpy(NetWorkCfg.sMac, pNetCommon->sMac);
			NetWorkCfg.bUseHSDownLoad = pNetCommon->bUseHSDownLoad;
			NetWorkCfg.TransferPlan = pNetCommon->TransferPlan;

			bSuccess = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_SYSNET, 0,
				(char *)&NetWorkCfg, sizeof(SDK_CONFIG_NET_COMMON), nWaitTime);
			if (bSuccess)
			{
				if (bSuccess == VIDEONET_OPT_REBOOT)
				{
					bReboot = TRUE;
				}
				bSuccess = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_NET_DNS, 0,
					(char *)pNetDNS, sizeof(SDK_NetDNSConfig), nWaitTime);
				if (bSuccess)
				{
					if (bSuccess == VIDEONET_OPT_REBOOT)
					{
						bReboot = TRUE;
					}
					bSuccess = VideoNet_SetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_NET_DHCP, 0,
						(char *)pNetDHCP, sizeof(SDK_NetDHCPConfigAll), nWaitTime);

					if (bSuccess)
					{
						if (bSuccess == VIDEONET_OPT_REBOOT)
						{
							bReboot = TRUE;
						}
						if (bReboot == TRUE)
						{
							if (myHelper::ShowMessageBoxQuesion(QObject::tr("是否重启设备？")) == 1)
							{
								bSuccess = VideoNet_ControlDVR(m_pDevObj->m_lUserLoginID, 0, nWaitTime);
								if (bSuccess)
								{
									OnBtnLogout();
								}
								else
								{
									myHelper::ShowMessageBoxError(QObject::tr("重启失败"));
								}
							}
						}
						if (bSuccess > 0)
						{
							myHelper::ShowMessageBoxInfo(QObject::tr("保存配置成功"));
						}
						else if (bSuccess < 0 && bSuccess != VIDEONET_OPT_REBOOT)
						{
							myHelper::ShowMessageBoxInfo(QObject::tr("保存配置失败"));
						}
					}
				}
			}
		}

	}

}

void ConfigNetwork::OnBtnLogout()
{
	//BOOL bRet = VideoNet_Logout(m_LoginID);
}

void ConfigNetwork::on_btnUpGrade_clicked()
{
	CleaAll();
	GetNetWorkConfigInfo();
}



void ConfigNetwork::on_lineEdit_MAC6_textChanged(const QString &arg1)
{
	
	if (arg1.length() > 2)
	{
		
		ui.lineEdit_MAC6->setText( QString(m_pNetCommon.sMac).mid(15));
		
	}
	ui.lineEdit_MAC6->setFocus();
}

void ConfigNetwork::on_lineEdit_TCPPORT_textChanged(const QString &arg1)
{
	if (arg1.toInt() > 65535)
	{
		ui.lineEdit_TCPPORT->setText("65535");
	}
}

void ConfigNetwork::on_lineEdit_HTTPPORT_textChanged(const QString &arg1)
{
	if (arg1.toInt() > 65535)
	{
		ui.lineEdit_TCPPORT->setText("65535");
	}
}

void ConfigNetwork::on_btnDownSave_clicked()
{
	m_pNetCommon.bUseHSDownLoad = m_bHightLoadDown;
	m_pNetDHCP.vNetDHCPConfig[0].bEnable = m_bDHCP;
	m_pNetCommon.TransferPlan = ui.comboBox_TRANSFERPOLICY->currentIndex();
	if (ui.comboBox_NETCARD->currentIndex() != -1)
	{
		SetNetWorkConfigInfo(&m_pNetCommon, &m_pNetDNS, &m_pNetDHCP);
	}
}

void ConfigNetwork::on_btnDNSSave_clicked()
{
	DWORD dwPrimary = IPV4StringToInteger(ui.lineEdit_PRIMARYDNS->text());
	m_pNetDNS.PrimaryDNS.l = swap_long(dwPrimary);
	DWORD dwSeconddary = IPV4StringToInteger(ui.lineEdit_SECONDARYDNS->text());
	m_pNetDNS.SecondaryDNS.l = swap_long(dwSeconddary);
	if (ui.comboBox_NETCARD->currentIndex() != -1)
	{
		SetNetWorkConfigInfo(&m_pNetCommon, &m_pNetDNS, &m_pNetDHCP);
	}

}

void ConfigNetwork::on_btnIPSave_clicked()
{
	DWORD dwIP = IPV4StringToInteger(ui.lineEdit_NETIP->text());
	m_pNetCommon.HostIP.l = swap_long(dwIP);
	DWORD dwIPMask = IPV4StringToInteger(ui.lineEdit_NETIPMASK->text());
	m_pNetCommon.Submask.l = swap_long(dwIPMask);
	DWORD dwGateWay = IPV4StringToInteger(ui.lineEdit_NETGATEWAY->text());
	m_pNetCommon.Gateway.l = swap_long(dwGateWay);
	m_pNetCommon.TCPPort = ui.lineEdit_TCPPORT->text().toInt();
	m_pNetCommon.HttpPort = ui.lineEdit_HTTPPORT->text().toInt();
	QString strMac;
	strMac = ui.lineEdit_MAC1->text() + ":" + ui.lineEdit_MAC2->text() + ":" + ui.lineEdit_MAC3->text()
		+ ":" + ui.lineEdit_MAC4->text() + ":" + ui.lineEdit_MAC5->text() + ":" + ui.lineEdit_MAC6->text();
	strcpy(m_pNetCommon.sMac, strMac.toLocal8Bit().data());
	if (ui.comboBox_NETCARD->currentIndex() != -1)
	{
		SetNetWorkConfigInfo(&m_pNetCommon, &m_pNetDNS, &m_pNetDHCP);
	}
}
void ConfigNetwork::on_checkBox_DHCPEnable_clicked()
{
	BOOL nEnable = !m_bDHCP;
	ui.lineEdit_NETIP->setEnabled(!nEnable);
	ui.lineEdit_NETIPMASK->setEnabled(!nEnable);
	ui.lineEdit_NETGATEWAY->setEnabled(!nEnable);
}