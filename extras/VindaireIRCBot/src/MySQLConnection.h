/*
* Vindaire IRC Bot
* Copyright (C) 2008 Valroft <http://www.aspiredev.org/>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef _MYSQL_CONNECTION_H
#define _MYSQL_CONNECTION_H

#include "StdAfx.h"

typedef void(*mySQLCallback)(QueryResult*);
struct ASyncQuery
{
	mySQLCallback callback;
	string query;
};

class MySQLConnection : IRunnable
{
public:
	MySQLConnection(string host, string user, string password);
	~MySQLConnection();

	void UseDatabase(string database);
	void Execute(string query);
	QueryResult* Query(const char * query, ...);

	string EscapeString(string Escape);

	void Update();

	void QueryASync(mySQLCallback callback, const char * query, ...);

protected:
	MYSQL* handle;

	string mHost;
	string mUser;
	string mPassword;
	string mDatabase;

	deque<ASyncQuery*> AsynchronousQueries;
};

#endif