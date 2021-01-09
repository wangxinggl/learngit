#define  _CRT_SECURE_NO_WARNINGS
#include "BehaviorAnalyseDlg.h"

BehaviorAnalyseDlg::BehaviorAnalyseDlg(QWidget *parent)
	: QWidget(parent)
	, m_pstConfigNormal(NULL)
	, m_pDevObj(NULL)
	, m_pTreeDev(NULL)
	, m_pStreamSetDlg(NULL)
	, m_pUpgradeDlg(NULL)
	, m_pAnalysisDlg(NULL)
	, m_pOrdinarySetDlg(NULL)
	, m_pVideoWarningDlg(NULL)
	, m_pImageSetDlg(NULL)
	, m_pParamMeteSetDlg(NULL)
	, m_pAlarmDlg(NULL)
	, m_pNetworkDlg(NULL)
	, m_pSearchButton(NULL)
	, m_pSearchLayout(NULL)
{
	m_pstConfigNormal = new SDK_CONFIG_NORMAL;
	memset(m_pstConfigNormal, 0, sizeof(SDK_CONFIG_NORMAL));

	ui.setupUi(this);
	
	initSearchButton();
	EnableButton(false);
}

BehaviorAnalyseDlg::~BehaviorAnalyseDlg()
{
	if (m_pStreamSetDlg)
	{
		delete m_pStreamSetDlg;
		m_pStreamSetDlg = NULL;
	}
	if (m_pUpgradeDlg)
	{
		delete m_pUpgradeDlg;
		m_pUpgradeDlg = NULL;
	}
	if (m_pAnalysisDlg)
	{
		delete m_pAnalysisDlg;
		m_pAnalysisDlg = NULL;
	}
	if (m_pOrdinarySetDlg)
	{
		delete m_pOrdinarySetDlg;
		m_pOrdinarySetDlg = NULL;
	}
	if (m_pVideoWarningDlg)
	{
		delete m_pVideoWarningDlg;
		m_pVideoWarningDlg = NULL;
	}
	if (m_pImageSetDlg)
	{
		delete m_pImageSetDlg;
		m_pImageSetDlg = NULL;
	}
	if (m_pParamMeteSetDlg)
	{
		delete m_pParamMeteSetDlg;
		m_pParamMeteSetDlg = NULL;
	}
	if (m_pAlarmDlg)
	{
		delete m_pAlarmDlg;
		m_pAlarmDlg = NULL;
	}
	if (m_pNetworkDlg)
	{
		delete m_pNetworkDlg;
		m_pNetworkDlg = NULL;
	}
	if (m_pstConfigNormal)
	{
		delete m_pstConfigNormal;
		m_pstConfigNormal = NULL;
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
}

void BehaviorAnalyseDlg::initTree()
{
	m_pDevObj = NULL;
	ui.treeWidget->clear();
	m_pTreeDev->ShowTreebyType(ui.treeWidget);
	connect(ui.treeWidget, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(OnlineTreeViewDoubleClick(const QModelIndex)));
}

void BehaviorAnalyseDlg::OnTreeReFresh()
{
	EnableButton(false);
	m_pDevObj = NULL;
	ui.treeWidget->clear();
	m_pTreeDev->RefreshDevTree(ui.treeWidget, FALSE);
}

void BehaviorAnalyseDlg::initSearchButton()
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
	connect(m_pSearchButton, SIGNAL(clicked(bool)), this, SLOT(searchIP()));
}

void BehaviorAnalyseDlg::OnlineTreeViewDoubleClick(const QModelIndex & index)
{
	m_pDevObj = NULL;
	TreeData_t* pTreeData = NULL;
	QString str;

	str += QString("%1").arg(index.data().toString());
	QString par = QObject::tr("%1").arg(index.parent().data().toString());
	QVariant var = ui.treeWidget->currentItem()->data(0, Qt::UserRole);
	pTreeData = (TreeData_t *)var.value<void *>();	

	EnableButton(false);
	if (pTreeData && pTreeData->pDevObj)
	{
		m_pDevObj = pTreeData->pDevObj;
		if (m_pDevObj->m_pDevInfo->nSubDevType == SDK_DEV_TYPE_MJIPC)
		{
			m_pDevObj->m_nWidth = 480;
			m_pDevObj->m_nHeight = 768;
		}
		GetDeviceInfo();
	}
}

void BehaviorAnalyseDlg::GetDeviceInfo()
{
	int nError = 0;

	if (m_pDevObj->GetLoginID() > 0)
	{
		GetDeviceConfigInfo();

		EnableButton(true);
	}
}

void BehaviorAnalyseDlg::GetDeviceConfigInfo()
{
	DWORD dwRetLen = 0;
	int nWaitTime = 10000;

	BOOL bSuccess = VideoNet_GetDevConfig(m_pDevObj->m_lUserLoginID, E_SDK_CONFIG_SYSNORMAL, 0,
		(char *)m_pstConfigNormal, sizeof(SDK_CONFIG_NORMAL), &dwRetLen, nWaitTime);
	if (!bSuccess)
	{
	}

	InitDlgInfo();	
}

void BehaviorAnalyseDlg::ShowLoginErrorReason(int nError)
{
	int nErr = VideoNet_GetLastError();
	if (nErr == VIDEONET_PASSWORD_NOT_VALID)
	{
		myHelper::ShowMessageBoxError(QObject::tr("密码错误"));
	}
	else
	{
		myHelper::ShowMessageBoxError(QObject::tr("未知错误"));
	}
}

void BehaviorAnalyseDlg::InitDlgInfo()
{
	ui.label_Num->setText(m_pDevObj->m_stDevInfo.sSerialNumber);

	ui.label_Version->setText(m_pDevObj->m_stDevInfo.sSoftWareVersion);

	ui.label_IP->setText(m_pDevObj->m_pDevInfo->szIpAddr);
	
	ui.label_WebVersion->setText(m_pDevObj->m_stDevInfo.sWebVersion);
}

void BehaviorAnalyseDlg::on_btnEncode_clicked()
{
	if (CheckDevStatus())
	{
		if (!m_pStreamSetDlg)
		{
			m_pStreamSetDlg = new StreamSet;
		}
		m_pStreamSetDlg->m_pDevObj = m_pDevObj;

		m_pStreamSetDlg->m_pstConfigNormal = m_pstConfigNormal;

		m_pStreamSetDlg->InitChannel();
		m_pStreamSetDlg->InitResolution();
		m_pStreamSetDlg->GetChannelConfigInfo(0);
		m_pStreamSetDlg->exec();
	}
}

void BehaviorAnalyseDlg::on_btnordinarySet_clicked()
{
	if (CheckDevStatus())
	{
		if (!m_pOrdinarySetDlg)
		{
			m_pOrdinarySetDlg = new OrdinarySet;
		}
		m_pOrdinarySetDlg->m_pDevObj = m_pDevObj;
		m_pOrdinarySetDlg->m_pstConfigNormal = m_pstConfigNormal;

		m_pOrdinarySetDlg->InitDlgInfo();
		m_pOrdinarySetDlg->exec();
	}
}

void BehaviorAnalyseDlg::on_btnWeb_clicked()
{
	if (m_pDevObj == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择设备"));
		return;
	}
	char szSnapPath[125];
	sprintf(szSnapPath, "%s//%s/%s", "http:", m_pDevObj->m_pDevInfo->szIpAddr, "login.asp");
	QDesktopServices::openUrl(QUrl(QLatin1String(szSnapPath)));
}

void BehaviorAnalyseDlg::on_btnUpGrade_clicked()
{
	if (CheckDevStatus())
	{
		if (!m_pUpgradeDlg)
		{
			m_pUpgradeDlg = new Upgrade;
		}
		m_pUpgradeDlg->m_pDevObj = m_pDevObj;
		m_pUpgradeDlg->initUPgradeInfo();
		m_pUpgradeDlg->exec();
	}

}

void BehaviorAnalyseDlg::on_btnArea_clicked()
{
	if (CheckDevStatus())
	{
		if (!m_pAnalysisDlg)
		{
			m_pAnalysisDlg = new AnalysisDlg;
		}
		m_pAnalysisDlg->m_pDevObj = m_pDevObj;
		m_pAnalysisDlg->init();
		m_pAnalysisDlg->exec();
	}
}

void BehaviorAnalyseDlg::on_btnVideoWarning_clicked()
{
	if (CheckDevStatus())
	{
		if (!m_pVideoWarningDlg)
		{
			m_pVideoWarningDlg = new VideoWarning();
		}
		m_pVideoWarningDlg->m_pDevObj = m_pDevObj;
		m_pVideoWarningDlg->init();
		m_pVideoWarningDlg->exec();
	}
}

void BehaviorAnalyseDlg::on_btnImageSet_clicked()
{
	if (CheckDevStatus())
	{
		if (!m_pImageSetDlg)
		{
			m_pImageSetDlg = new ImageSet;
		}
		m_pImageSetDlg->m_pDevObj = m_pDevObj;
		m_pImageSetDlg->m_nChannelNum = m_pDevObj->m_stDevInfo.byChanNum;
		m_pImageSetDlg->init();
		m_pImageSetDlg->exec();
	}
}

void BehaviorAnalyseDlg::on_btnFace_clicked()
{
	if (CheckDevStatus())
	{
		if (!m_pParamMeteSetDlg)
		{
			m_pParamMeteSetDlg = new ParamMeteSet;
		}
		m_pParamMeteSetDlg->m_pDevObj = m_pDevObj;
		m_pParamMeteSetDlg->OnCbnSelchangeComChannel();
		m_pParamMeteSetDlg->exec();
	}
}


void BehaviorAnalyseDlg::on_btnWarning_clicked()
{
	if (CheckDevStatus())
	{
		if (!m_pAlarmDlg)
		{
			m_pAlarmDlg = new FaceAlarm;
		}
		m_pAlarmDlg->m_pDevObj = m_pDevObj;
		m_pAlarmDlg->OnCbnSelchangeComChannel();
		m_pAlarmDlg->exec();
	}
}

void BehaviorAnalyseDlg::on_btnNetWork_clicked()
{
	if (CheckDevStatus())
	{
		if (!m_pNetworkDlg)
		{
			m_pNetworkDlg = new ConfigNetwork;
		}
		m_pNetworkDlg->m_pDevObj = m_pDevObj;
		m_pNetworkDlg->GetNetWorkConfigInfo();
		m_pNetworkDlg->exec();
	}
}

BOOL BehaviorAnalyseDlg::CheckDevStatus()
{
	BOOL bSuccess = TRUE;
	if (m_pDevObj == NULL)
	{
		myHelper::ShowMessageBoxWarning(QObject::tr("请选择设备"));
		bSuccess = FALSE;
	}
	return bSuccess;
}


void BehaviorAnalyseDlg::EnableButton(bool bEnable)
{
	ui.btnUpGrade->setEnabled(bEnable);
	ui.btnWeb->setEnabled(bEnable);
	ui.btnEncode->setEnabled(bEnable);
	ui.btnArea->setEnabled(bEnable);
	ui.btnWarning->setEnabled(bEnable);
	ui.btnFace->setEnabled(bEnable);
	ui.btnordinarySet->setEnabled(bEnable);
	ui.btnImageSet->setVisible(false);
	ui.btnVideoWarning->setVisible(false);
	ui.btnNetWork->setEnabled(bEnable);
	if (m_pDevObj && m_pDevObj->m_pDevInfo->nType == SDK_DEV_TYPE_NVR)
	{
		ui.btnEncode->setEnabled(false);
		ui.btnArea->setEnabled(false);
		ui.btnWarning->setEnabled(false);
		ui.btnFace->setEnabled(false);
		ui.btnNetWork->setEnabled(false);
	}
}

void BehaviorAnalyseDlg::searchIP()
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