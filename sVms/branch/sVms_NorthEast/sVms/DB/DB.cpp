#include <string>
#include "sqlite3.h"
#include "DB.h"

CDB::CDB()
{
	m_nCmpInfoSize = 0;
	
	m_bExit = FALSE;
	
	memset(&m_szDBPath, 0, MAX_PATH);
	memset(&m_szJVTIACDBPath, 0, MAX_PATH);

	m_bExit = FALSE;
}

int CDB::Init(const char* szFile, int nType /* = 0 */)
{
	int nResult = 0;
	char pUTF8[MAX_PATH * 2] = {0};

	//Change_Unicode_UTF8((char*)szFile, strlen(szFile), pUTF8, strlen(szFile) * 2 + 2);
	if (nType)
	{
		nResult = sqlite3_open(pUTF8, &m_dbJVTIAC);
	}
	else
	{
		m_conn.open(pUTF8);
		m_conn.setbusytimeout(5000);
	}
	memcpy(m_szDBPath, pUTF8, strlen(pUTF8) + 1);
	return nResult;
}
int CDB::AddUser(const char* szUserName,const char* szPassword)
{
	sqlite3_reader reader;
	char sql[512];
	sprintf(sql,"select UId from UserInfo where UserName = '%s';",szUserName);
	int nUserId = 0;
	sqlite3_command cmd(m_conn,sql);
	try
	{
		reader = cmd.executereader();
		if(reader.read())
		{
			nUserId = reader.getint(0);

		}
		reader.close();
	}
	catch (const sqlite3x::database_error &ex)
	{
		reader.close();
		return -1;
	}
	if (nUserId > 0)
	{
		//该用户已经存在
		return -2;
	}
	else
	{
		sprintf(sql, "insert into UserInfo values(NULL,'%s','%s');",szUserName,szPassword);
		sqlite3_command cmd(m_conn,sql);
		try
		{
			reader = cmd.executereader();
			if(reader.read())
			{	
				nUserId = reader.getint(0);
			}
			reader.close();
		}
		catch(const sqlite3x::database_error &ex)
		{
			reader.close();
			return -1;
		}
	}
	return nUserId;
}

int CDB::CheckUser(const char* szUserName,const char* szPassword)
{
	sqlite3_reader reader;
	char sql[512];
	sprintf(sql,"select UId from UserInfo where UserName = '%s' and Password = '%s';",szUserName,szPassword);
	int nUserId = 0;
	sqlite3_command cmd(m_conn,sql);
	try
	{
		reader = cmd.executereader();
		if(reader.read())
		{
			nUserId = reader.getint(0);
		}
		reader.close();
	}
	catch (const sqlite3x::database_error &ex)
	{
		reader.close();
		return -1;
	}
	return nUserId;

}

CDB::~CDB()
{
	
}