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
	int AddUser(const char* szUserName,const char* szPassword);	//添加用户
	int CheckUser(const char* szUserName,const char* szPassword);  //验证用户登录信息
	
private:

	
	
	sqlite3_connection m_conn;
	char m_szDBPath[MAX_PATH];			//A1600Client.db路径

	int m_nCmpInfoSize;				//总记录数
	bool m_bExit;
	char m_szJVTIACDBPath[MAX_PATH];	//JVTAC.db路径
	
	sqlite3* m_dbJVTIAC;
};