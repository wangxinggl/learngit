#pragma once

#include <list>
#include "sqlite3x.hpp"
#include "sqlite3.h"
#include "table_structs.h"
#include "Utils.h"
#include "mlog.h"

using sqlite3x::sqlite3_connection;
using sqlite3x::sqlite3_command;
using sqlite3x::sqlite3_reader;
using sqlite3x::sqlite3_transaction;

#define MAX_PATH          260

class CDB
{
public:
	CDB();
	virtual~ CDB();
	int Init(const char* szFile, int nType = 0);
	int Destroy();
	int AddUser(const char* szUserName,const char* szPassword);	//����û�
	int CheckUser(const char* szUserName,const char* szPassword);  //��֤�û���¼��Ϣ
	
private:

	
	
	sqlite3_connection m_conn;
	char m_szDBPath[MAX_PATH];			//A1600Client.db·��

	int m_nCmpInfoSize;				//�ܼ�¼��
	bool m_bExit;
	char m_szJVTIACDBPath[MAX_PATH];	//JVTAC.db·��
	
	sqlite3* m_dbJVTIAC;
};