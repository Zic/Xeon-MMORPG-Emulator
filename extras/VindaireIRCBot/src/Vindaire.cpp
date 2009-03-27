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
using namespace std;
CLog Log;
int main()
{
	Config.MainConfig.SetSource("./vindaire.conf");
	printf("Vindaire Hearthstone IRC Bot\n");
	printf("By Valroft of http://aspiredev.org\n");
	printf("This program is licensed under the GNU Affero GPL.\n");
	printf("-------------------------------------------------------");
	Log.Notice("Vindaire", "Starting up...");

#ifdef WIN32
	// WSA Setup
	WSADATA info;
	WSAStartup(MAKEWORD(2,0), &info);
#endif

	std::string server = Config.MainConfig.GetStringDefault("IRC", "Server", "");
	uint32 port = Config.MainConfig.GetIntDefault("IRC", "Port", 6667);
	
	new IRCSession(server, port);
	return 0;
}

