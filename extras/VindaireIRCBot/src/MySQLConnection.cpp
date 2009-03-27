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

#include "StdAfx.h"

MySQLConnection::MySQLConnection(string host, string user, string password)
{
	handle = mysql_init( NULL );
	mysql_real_connect(handle, host.c_str(), user.c_str(), password.c_str(), "", 3306, "", 0);
	if(!handle)
	{
		Log.Notice("mySQL", "Error connecting to database on %s", host.c_str());
		return;
	}

	mHost = host;
	mUser = user;
	mPassword = password;
}

MySQLConnection::~MySQLConnection()
{

}

void MySQLConnection::Execute(string query)
{
	//dunno what it does ...leaving untouched 
	int result = mysql_query(handle, query.c_str());

	if(result > 0)
	{
		uint32 errnom = mysql_errno(handle);
		const char * reason = mysql_error(handle);
		Log.Notice("MySQL", "Query Failed: %s\nReason: %s", query.c_str(), reason);

		// Errors which require us to reconnect.
		if(errnom == 2006 || errnom == 2008 || errnom == 2013 || errnom == 2055)
		{
			handle = mysql_init(NULL);
			mysql_real_connect(handle, mHost.c_str(), mUser.c_str(), mPassword.c_str(), "", 3306, "", 0);
			if(!handle)
				return;

			UseDatabase(mDatabase);

			Execute(query);
		}
	}
}

void MySQLConnection::QueryASync(mySQLCallback callback, const char * query, ...)
{
	char sql[16384];
	va_list vlist;
	va_start(vlist, query);
	vsnprintf(sql, 16384, query, vlist);
	va_end(vlist);

	string querystring = string(sql);

	ASyncQuery * pQuery = new ASyncQuery;
	pQuery->callback = callback;
	pQuery->query = querystring;

	AsynchronousQueries.push_back(pQuery);
}

QueryResult* MySQLConnection::Query(const char * query, ...)
{
	char sql[16384];
	va_list vlist;
	va_start(vlist, query);
	vsnprintf(sql, 16384, query, vlist);
	va_end(vlist);

	string querystring = string(sql);

	Execute(querystring);
	QueryResult * res;
	MYSQL_RES * pRes = mysql_store_result( handle );
	uint32 uRows = (uint32)mysql_affected_rows( handle );
	uint32 uFields = (uint32)mysql_field_count( handle );

	if( uRows == 0 || uFields == 0 || pRes == 0 )
	{
		if( pRes != NULL )
			mysql_free_result( pRes );

		return NULL;
	}

	res = new QueryResult( pRes, uFields, uRows );
	res->NextRow();

	return res;
}

string MySQLConnection::EscapeString(string Escape)
{
	char a2[16384] = {0};
	const char * ret;
	if(mysql_real_escape_string(handle, a2, Escape.c_str(), (unsigned long)Escape.length()) == 0)
		ret = Escape.c_str();
	else
		ret = a2;

	return string(ret);
}

void MySQLConnection::UseDatabase(string database)
{
	mysql_select_db(handle, database.c_str());
	mDatabase = database;
}

void MySQLConnection::Update()
{
	while(true)
	{
		if(AsynchronousQueries.size() > 0)
		{
			ASyncQuery * pQuery = AsynchronousQueries.front();
			AsynchronousQueries.pop_front();

			QueryResult * pResult = Query(pQuery->query.c_str());
			if(pResult)
			{
				pQuery->callback(pResult);
			}
		}

		Sleep(100);
	}
}