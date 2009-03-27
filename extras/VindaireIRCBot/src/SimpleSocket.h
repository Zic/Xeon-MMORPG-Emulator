#ifndef _SIMPLE_SOCKET_H
#define _SIMPLE_SOCKET_H

#include "StdAfx.h"

class SimpleSocket
{
	friend class SocketMgr;
public:
	SimpleSocket();
	~SimpleSocket();

	bool Connect(string host, uint32 port);
	void Disconnect();

	bool IsConnected() { return m_fd != NULL; }

	void SendLine(string line);
	void SendForcedLine(string line);

	bool HasLine();
	string GetLine();
	void UpdateQueue();

protected:
	bool m_full;
	string buffer;
	SOCKET m_fd;
	sockaddr_in m_client;

	CRITICAL_SECTION buffer_lock;
	string m_outBuf;
	string m_inBuf;

	deque<string> m_sendQueue;
	uint32 m_sendPerPeriod;
	uint32 m_sendCount;
	time_t m_lastSendTime;
};

class SocketMgr : public IRunnable
{
public:
	SocketMgr();

	void AddSocket(SimpleSocket *pSocket);
	void RemoveSocket(SimpleSocket *pSocket);

	void Update();

protected:
	typedef set<SimpleSocket*> SocketSet;
	CRITICAL_SECTION socket_lock;
	SocketSet m_sockets;
};

#endif