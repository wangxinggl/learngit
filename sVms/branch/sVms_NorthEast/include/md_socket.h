/**************************************************************************************
 * head file of socket layer
 * AUTHOR: alen.wu
 * DATE: 2007-01-29
 * COPYRIGHT: 
 * DESCRIPTION: The file declares the interfaces to metadata server.
 **************************************************************************************
 */
#ifndef MD_SOCKET_H_
#define MD_SOCKET_H_

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#ifdef WIN32
#include <WinSock.h>
#else //LINUX OR UNIX
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include <string>

#include "md_def.h"

using namespace std;
namespace expara_api
{
class CMdException
{
public:

	/**
	 * constructor and destructor
	 */
	CMdException( S32 iErrCode, const string& strDesc ) :
		m_iErrCode(iErrCode), m_strDesc(strDesc)
	{
		/* null */
	}

	CMdException( const CMdException& oDbEx )
	{
		this->m_iErrCode = oDbEx.m_iErrCode;
		this->m_strDesc = oDbEx.m_strDesc;
	}
	virtual ~CMdException(){}
	S32 error() const {return m_iErrCode; }
	const string& what() const { return m_strDesc; }

private:

	/**
	 * error code
	 */
	S32 m_iErrCode;

	/**
	 * error description
	 */
	string m_strDesc;
};


#define MDSOCK_MAX_RECV_BUFFER		(36*1024)

class MutexGuard
{
public:

	explicit MutexGuard( MD_MUTEX_ID&    mutex ) : m_tMutex(mutex)
	{
#ifdef WIN32
		WaitForSingleObject(m_tMutex, -1);
#else //LINUX OR UNIX
		pthread_mutex_lock(&m_tMutex);
#endif
	}

	virtual ~MutexGuard()
	{
#ifdef WIN32
		ReleaseMutex(m_tMutex);
#else //LINUX OR UNIX
		pthread_mutex_unlock(&m_tMutex);
#endif
	}

private:

	MD_MUTEX_ID& m_tMutex;

};

/**
 * socket encapsulator
 */
class CMdSocket
{
public:

	/**
	 * init windows socket environment
	 */
	static S32 initWSA()
	throw (CMdException);

	/**
	 * constructor and destructor
	 */
	CMdSocket(  );
	virtual ~CMdSocket();


	/**
	 * set server address
	 * @nSvrIp: server ip in network byte order
	 * @nSvrPort: server port in host byte order
	 */
	S32 setSvrAddr( U32 nSvrIp, U16 nSvrPort );

	/**
	 * active open or passive open
	 */
	S32 openConnection( )
	throw (CMdException);


	/**
	 * fining
	 */
	S32 closeConnection();


	/**
	 * send message
	 * @strMsg: message to send
	 * @nMsgLen: message length
	 * return 0 0r -1;
	 */
	S32 sendMsg( const S8* strMsg, U32 nMsgLen )
	throw (CMdException);


	/**
	 * receive message
	 * @strBuf: message buffer
	 * @nBufLen: buffer length
	 * @pTimeOut: time out in seconds
	 * return message length.
	 */
	S32 recvMsg( S8* strBuf, U32& nBufLen,  U32* pTimeOut=0 )
	throw (CMdException);


	/**
	 * set message Head magic content
	 */
	static S32 setHeadMagic( const S8* strHeadMagic, U32 nLen );


	/**
	 * set message tail magic content
	 */
	static S32 setTailMagic( const S8* strTailMagic, U32 nLen );


private:

	/**
	 * socket fd
	 */
	MD_SOCKFD m_nSockFd;

	/**
	 * server ip. network byte order
	 */
	U32 m_nSvrIp;

	/**
	 * server port. host byte order
	 */
	U16 m_nSvrPort;

	/**
	 * head magic content and length
	 */
	static S8 m_strHeadMagic[16];
	static U32 m_nHeadMagicLen;

	/**
	 * tail magic content and length
	 */
	static S8 m_strTailMagic[16];
	static U32 m_nTailMagicLen;

	/**
	 * receiving buffer
	 */
	S8* m_strBuf;

	/**
	 * remain content length in the buffer
	 */
	U32 m_nRemainLen;

	/**
	 * sending mutex
	 */
	MD_MUTEX_ID m_tSendMutex;


private:

	/* prevent assignment and initialization */
	CMdSocket( const CMdSocket& );
	void operator = ( const CMdSocket& );

};

};

#endif

