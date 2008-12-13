#include "StdAfx.h"
SocketMgr *pSocketMgr = NULL;

SimpleSocket::SimpleSocket()
{
	m_fd = 0;
	m_sendCount = 0;
	m_sendPerPeriod = Config.MainConfig.GetIntDefault("IRC", "LinesPerSecond", 3);
	m_lastSendTime = time(NULL);
	InitializeCriticalSection(&buffer_lock);
}

SimpleSocket::~SimpleSocket()
{
	DeleteCriticalSection(&buffer_lock);
}

void SimpleSocket::UpdateQueue()
{
	time_t nt = time(NULL);
	uint32 c = 0;
	if( m_lastSendTime == nt )
		return;

	m_lastSendTime = nt;
	EnterCriticalSection(&buffer_lock);
	while( m_sendQueue.size() )
	{
		c++;
		m_outBuf.append(m_sendQueue.front().c_str(), m_sendQueue.front().length());
		m_sendQueue.pop_front();
		if( c >= m_sendPerPeriod )
			break;
	}
	LeaveCriticalSection(&buffer_lock);
	m_sendCount = c;
}

void SimpleSocket::SendLine(string line)
{
	if( m_sendCount >= m_sendPerPeriod )
	{
		m_sendQueue.push_back(line);
		return;
	}

	EnterCriticalSection(&buffer_lock);
	m_outBuf.append(line.c_str(), line.length());
	LeaveCriticalSection(&buffer_lock);
	m_sendCount++;
}

void SimpleSocket::SendForcedLine(string line)
{
	EnterCriticalSection(&buffer_lock);
	m_outBuf.append(line.c_str(), line.length());
	LeaveCriticalSection(&buffer_lock);
}

bool SimpleSocket::HasLine()
{
	bool ret = false;
	EnterCriticalSection(&buffer_lock);
	if( m_inBuf.find("\n") != string::npos )
		ret = true;		
	LeaveCriticalSection(&buffer_lock);
	return ret;
}

string SimpleSocket::GetLine()
{
	// can probably be optimized /lazy

	string ret;
	char c;
	string::size_type i;

	EnterCriticalSection(&buffer_lock);
	for( ;; )
	{
		c = m_inBuf[0];
		m_inBuf.erase(0, 1);

		if( c == '\n' )
			break;
		
		ret.append(&c, 1);
	}
	LeaveCriticalSection(&buffer_lock);
	return ret;
}

/*void SimpleSocket::WipeBuffers()
{
	buffer = "";
	m_full = false;
	SendBuffer.clear();
}*/

bool SimpleSocket::Connect(string host, uint32 port)
{
	if(m_fd) // We already have an existing socket
		return false;

	// Populate the socket handle
	m_fd = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, WSA_FLAG_OVERLAPPED);

	struct hostent * ci = gethostbyname(host.c_str());
	if(ci == 0)
		return false;

	m_client.sin_family = ci->h_addrtype;
	m_client.sin_port = ntohs((u_short)port);
	memcpy(&m_client.sin_addr.s_addr, ci->h_addr_list[0], ci->h_length);

	u_long arg = 0;
	ioctlsocket(m_fd, FIONBIO, &arg);

	if(connect(m_fd, (const sockaddr*)&m_client, sizeof(m_client)) == -1)
	{
		m_fd = NULL;
		return false;
	}

	arg = 1;
	ioctlsocket(m_fd, FIONBIO, &arg);

	if( pSocketMgr == NULL )
		pSocketMgr = new SocketMgr;

	pSocketMgr->AddSocket(this);

	return true;
}

void SimpleSocket::Disconnect()
{
	shutdown(m_fd, SD_BOTH);
	closesocket(m_fd);
	m_fd = NULL;
}

void SocketMgr::AddSocket(SimpleSocket *pSocket)
{
	EnterCriticalSection(&socket_lock);
	m_sockets.insert(pSocket);
	LeaveCriticalSection(&socket_lock);
}

void SocketMgr::RemoveSocket(SimpleSocket *pSocket)
{
	EnterCriticalSection(&socket_lock);
	m_sockets.erase(pSocket);
	LeaveCriticalSection(&socket_lock);
}

SocketMgr::SocketMgr()
{
	Thread *p = new Thread(this);
	p->start();

	InitializeCriticalSection(&socket_lock);
}

void SocketMgr::Update()
{
	fd_set read_set;
	fd_set write_set;
	fd_set exception_set;
	set<SimpleSocket*>::iterator itr;
	SimpleSocket *s;
	int res;
	int max_fd = 0;
	char buffer[65000];

	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 50000;			// 50ms
	

	for( ;; )
	{
		FD_ZERO(&read_set);
		FD_ZERO(&write_set);
		FD_ZERO(&exception_set);

		EnterCriticalSection(&socket_lock);
		for( itr = m_sockets.begin(); itr != m_sockets.end(); ++itr )
		{
			if( (*itr)->m_fd >= max_fd )
				max_fd = (*itr)->m_fd + 1;

			if( (*itr)->m_outBuf.size() > 0 )
				FD_SET((*itr)->m_fd, &write_set);
			else
				FD_SET((*itr)->m_fd, &read_set);
		}
		LeaveCriticalSection(&socket_lock);
		
		res = select(max_fd, &read_set, &write_set, &exception_set, &tv);

		EnterCriticalSection(&socket_lock);
		for( itr = m_sockets.begin(); itr != m_sockets.end(); )
		{
			s = *itr;
			++itr;

			if( FD_ISSET(s->m_fd, &exception_set) )
			{
				s->m_fd = NULL;
				continue;
			}

			if( FD_ISSET(s->m_fd, &read_set) )
			{
				res = recv(s->m_fd, buffer, 65000, 0);
				if( res <= 0 )
				{
					s->m_fd = NULL;
					continue;
				}

				EnterCriticalSection(&s->buffer_lock);
				s->m_inBuf.append(buffer, res);
				LeaveCriticalSection(&s->buffer_lock);
			}

			if( FD_ISSET(s->m_fd, &write_set) && s->m_outBuf.size() )
			{
				EnterCriticalSection(&s->buffer_lock);
				res = send(s->m_fd, s->m_outBuf.c_str(), s->m_outBuf.size(), 0);
				if( res <= 0 )
				{
					LeaveCriticalSection(&s->buffer_lock);
					s->m_fd = NULL;
					continue;
				}

				s->m_outBuf.erase(0, res);
				LeaveCriticalSection(&s->buffer_lock);
			}
		}

		LeaveCriticalSection(&socket_lock);
	}
}

