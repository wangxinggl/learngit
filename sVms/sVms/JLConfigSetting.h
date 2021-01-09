#pragma once

#include <QWidget>
#include "ui_JLConfigSetting.h"
#include "devtreepro.h"
#include <QDesktopServices>
#include <QUrl>
#include "Configsetting.h"
#include <map>
#include <QComboBox>
#include <QCheckBox>
#include "AnalyseVideoAreaDlg.h"
#include <Windows.h>
class JLConfigSetting : public QWidget
{
	Q_OBJECT

public:
	JLConfigSetting(QWidget *parent = Q_NULLPTR);
	~JLConfigSetting();
	void initRegionl();
	void initreeWidget();
	void initShieldDetDlg();
	void initConfigChannel();
	void InitDlgInfo(DEV_ATTRIBUTE *pDevAttribute, SDK_MultiLangFunction *PLang);
	void OnBtnLogin();
	BOOL IsIPAvailed(const char* chIPAddr);
	void ShowLoginErrorReason(int nError);
	void GetDeviceConfigInfo();//获取基本数据
	void GetChannelConfigInfo();
	void InitStramInfo(int ChannnelNum, SDK_EncodeConfigAll_SIMPLIIFY *pEncodeSimpl,
		SDK_CONFIG_NORMAL *pNormalCfg, CONFIG_EncodeAbility *pEncodeAbility,
		SDK_CombineEncodeConfigAll *pCmbEncode, SDK_SystemFunction *pSysFunc,
		DEV_ATTRIBUTE *pDevAttribute, SDK_CombEncodeModeAll *pCmbEncodeMode,
		SDK_EncodeStaticParamAll *pEncodeStatic);
	bool StructToWin();
	void InitCombo();
	void InitResData();
	void UpdateCodeFormat(int nStream, QComboBox *m_combox);
	bool NormalStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType);
	bool StructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType, DWORD dwPower, DWORD dwMask = -1, DWORD dwBitrate = -1);
	DWORD GetFreeDspPower(int nChannelNo);
	DWORD GetFreeBitratePower(int nChannelNo);
	DWORD GetExpandUsed();
	DWORD GetMainUsed();
	void GetMaxResolAndRate(int &nResolu, int &nRate, long lFreePower);
	void EnableMainVideo(BOOL bEnable);
	void EnableExpandVideo(BOOL bEnable);
	void AddCmbResolution(QString comboxID, int maxSize, DWORD dwMask);
	void AddCmbFPS(QString comboxID, int maxSize);
	BOOL SetComBoxCurSel(QString m_comboxID, DWORD dwData);
	int NearBitrate(QString m_comboxID, DWORD dwData);
	bool CombineStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType);
	long OnRefresh();
	long GetChannelConfigInfoEX(long m_lChannel);
	void InitDlgInfoEx(long lChannel, int ChannnelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pEncodeSimpl,
		SDK_CONFIG_NORMAL *pNormalCfg, CONFIG_EncodeAbility *pEncodeAbility, SDK_SystemFunction *pSysFunc,
		DEV_ATTRIBUTE *pDevAttribute, SDK_EncodeStaticParam *pEncodeStatic);
	void CleanAll();
	bool AllStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType);
	bool AllWinDataToStruct(int nChannelNum);
	bool WinDataToStruct(SDK_MEDIA_FORMAT &dstFmt, int nEncodeType);
	DWORD GetComboBoxData(QString m_comboxID, int nIndex = -1);
	void SelchangeComboFrame(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType);
	BOOL SetComBoxCurSel(QComboBox *pComboBox, DWORD dwData);
	void SelchangeComboResolution(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType, DWORD dwPower);
	int GetMaxFrame(int nResolution, long lFreePower);
	DWORD GetUsedEnable(QComboBox* nResID, QComboBox* nFrameID, QCheckBox* nEnableID);
	void SelchangeComboBitcontrol(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType);
	void OnCbnSelchangeComChannel();
	long GetDevParam();
	long SetDevParam();
	long ShowChannelParam(long lChannel);
	long SaveChannelParam(long lChannel);
	long getLoginID(){ return m_LoginID; }
	//long EnableWindowAnalyse(BOOL bEnable);
	long StopPlay();
private slots:
	//tree点击事件
	void OnlineTreeViewDoubleClick(const QModelIndex & index);
	void on_btnWeb_clicked();
	void on_btnUpGrade_clicked();
	void setGroupHidden(int index);
	void OnSelchangeComboChanno(const QString &);
	void on_checkBox_F_Audio_clicked();
	void on_checkBox_M_Audio_clicked();
	void on_checkBox_F_Video_clicked();
	void on_comboBox_F_Frame_activated(int index);
	void on_comboBox_F_Image_activated(int index);
	void on_comboBox_F_Resolution_activated(int index);
	void on_comboBox_F_Stream_activated(int index);
	void on_comboBox_F_BitControl_clicked(int index);
	void on_comboBox_M_Resolution_clicked(int index);

	void on_btnRegionl_clicked();
	void on_btnRegionlClear_clicked();
	void on_comboBox_Regionl_activated(int index);
	void on_btnRegionlAll_clicked();
	void on_btnRegionlSet_clicked();
	void on_btnRegionlSave_clicked();
protected:
	void timerEvent(QTimerEvent* event);
public:
	DevTreePro *treeSetting;
	JVT_LONG m_LoginID;
	long  m_lDevType;
private:
	Ui::JLConfigSetting ui;
	TreeData_t *pChannelTmp;
	int LOGIN_TIMER;
	
	int m_nChannelNum;
	int m_streamChannelNum;
	int m_nAlarmInNum;
	int m_nAlarmOutNum;
	int m_nbyChanNum;
	int m_niDigChannel;
	DEV_ATTRIBUTE   m_DevAttribute;   //Device Attribute
	int m_nVideoStandard;
	BOOL m_bInitChannelComboxed;
	int m_nLastChannelNum;
	//视频码流
	SDK_EncodeConfigAll_SIMPLIIFY m_EncodeConfig;
	CONFIG_EncodeAbility m_pEncodeAbility;
	SDK_CombineEncodeConfigAll m_CmbEncodeCfg;
	SDK_CombEncodeModeAll m_CmbEncodeMode;
	SDK_SystemFunction m_SysFunc;
	SDK_CONFIG_ENCODE_SIMPLIIFY m_allData;
	char m_cVersion[64];
	int m_nAudioInNum;
	SResolution m_resolution[SDK_CAPTURE_SIZE_NR];
	int m_maxBitRate[SDK_CAPTURE_SIZE_NR];
	bool	m_bMultiStream;
	map<int, QString> m_mapCaptureComp;
	bool m_bCombineEncode;
	bool m_bCombineSet;
	long        m_lSelChannelNum;

	long m_lVideoWidth;
	long m_lVideoHeight;
	long m_lSelChannel;
	long m_lStreamType;
	int m_nDrawType;
	int 
	BOOL m_bStartCheck;
	BOOL m_bStartAreaSet;
	AnalyseVideoAreaDlg* m_pAnalyseVideoAreaDlg;
	SDK_FA_VI_SHIELDED* m_pFaShielded;
};
