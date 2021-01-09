#pragma once

#include <QDialog>
#include "ui_StreamSet.h"
#include <map>
#include "Configsetting.h"
#include <QComboBox>
#include "devtreepro.h"
#include "myhelper.h"
#include "AnalyseVideoAreaDlg.h"

using namespace std;
#pragma execution_character_set("utf-8") 

class StreamSet : public QDialog
{
	Q_OBJECT

public:
	StreamSet(QWidget *parent = Q_NULLPTR);
	~StreamSet();
	void InitDlgUI();
	void InitChannel();
	void InitResolution();
	void InitDlgInfo(int lChannel);
	void GetDlgInfo(int iChannel);
	long GetChannelConfigInfo(long lChannel);

	long SetCodeFormat(long lCompression);	//获取编码算法
	long GetCodeFormat(long lIndex);

	long SetResolutionIndex(long lResolution);	//获取分辨率
	long GetResolutionIndex(long lIndex);

	long SetExpandResolutionIndex1(long lResolution);
	long GetExpandResolutionIndex(long lIndex);

private slots:
	void on_comboBox_ChanNo_activated(int index);
	void on_btnSave_clicked();
	void on_btnUpGrade_clicked();
	void on_btnClose_clicked();

	void on_comboBox_CodeFormat_activated(int index);
	void on_comboBox_Expand_activated(int index);

public:
	bool m_bMultiStream;
	CJLNDevice* m_pDevObj;
	SDK_CONFIG_NORMAL* m_pstConfigNormal;		//普通配置页结构体												  
	SDK_EncodeConfigAll_SIMPLIIFY* m_pstCfgEncodeAll;/// 全通道编码配置

private:
	Ui::StreamSet ui;
	
	map<int, QString> m_mapCaptureComp;				//编码算法
	SResolution m_resolution[SDK_CAPTURE_SIZE_NR];	//分辨率
	int m_maxBitRate[SDK_CAPTURE_SIZE_NR];
	
};
