// UCRemoteConfig.h : UCRemoteConfig DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUCRemoteConfigApp
// �йش���ʵ�ֵ���Ϣ������� UCRemoteConfig.cpp
//

class CUCRemoteConfigApp : public CWinApp
{
public:
	CUCRemoteConfigApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


#define CONFIG_API extern "C" __declspec(dllexport) 

// pDeviceIP -- �豸IP�� iPort -- �˿ڣ� pUser -- �û����� pPassword --���룬 pLan -- ���ԣ� pParent -- �����ھ����
// ����lCOnfigID -- ���ñ�ʶ��1-100��
CONFIG_API long CFG_UC_Init(char *pDeviceIP, int iPort, char *pUser, char *pPassword, char *pLan, LPVOID pParent);


// lCOnfigID -- ���ñ�ʶ
CONFIG_API long CFG_UC_UnInit(long lConfigID);


// lCOnfigID -- ���ñ�ʶ�� rcPos -- ��ʾλ��
// rcPos(0,0,0,0) �رմ���
CONFIG_API long CFG_UC_ShowModelessDlg(long lConfigID, RECT rcPos);

CONFIG_API long CFG_UC_ShowDlg(LPVOID pParent);
CONFIG_API long CFG_UC_CloseDlg();