/*
 *					AspireCore
 * Copyright (C) 2008 AspireDev <http://www.aspiredev.org/>
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

AspireMessageHandler *AspireMessageHandler::Inst = NULL;

AspireMessageHandler::AspireMessageHandler()
{
	// incase I ever expand this
}

AspireMessageHandler::~AspireMessageHandler()
{
	KickMsgs.clear();
}

AspireMessageHandler &AspireMessageHandler::GetInst()
{
	if(Inst == NULL)
		Inst = new AspireMessageHandler();
	return *Inst;
}

// Database Interaction

void AspireMessageHandler::MasterDatabaseLoad()
{
	LoadKickMessages();
}

void AspireMessageHandler::LoadKickMessages()
{
	if(KickMsgs.empty() == false)
	{
		kMessageLock.Acquire();
		KickMsgs.clear();
		kMessageLock.Release();
	}

	QueryResult *Result = WorldDatabase.Query("SELECT * FROM `server_kick_messages`");
	if(Result)
	{
		do
		{
			std::string Index, Message;
			Index = Result->Fetch()[0].GetString();
			Message = Result->Fetch()[1].GetString();

			kMessageLock.Acquire();
			KickMsgs.insert(make_pair(Index, Message));
			kMessageLock.Release();

		}while(Result->NextRow());

		WorldDatabase.FreeQueryResult(Result);
	}
}

bool AspireMessageHandler::AddKickMessage(std::string &Index, std::string &Message)
{
	bool Ret = false;
	kMessageLock.Acquire();
	map<std::string, std::string>::iterator Itr = KickMsgs.find(Index);
	if(Itr == KickMsgs.end())
	{
		KickMsgs.insert(make_pair(Index, Message));
		WorldDatabase.Execute("INSERT INTO `server_kick_messages` (`Index`, `Message`) VALUES ('%s', '%s')", WorldDatabase.EscapeString(Index).c_str(), WorldDatabase.EscapeString(Message).c_str());
		Ret = true;
	}
	kMessageLock.Release();
	return Ret;
}

bool AspireMessageHandler::RemoveKickMessage(std::string &Index)
{
	bool Ret = false;
	kMessageLock.Acquire();
	map<std::string, std::string>::iterator Itr = KickMsgs.find(Index);
	if(Itr != KickMsgs.end())
	{
		KickMsgs.erase(Itr);
		WorldDatabase.Execute("DELETE FROM `server_kick_messages` WHERE `Index` = '%s'", WorldDatabase.EscapeString(Index).c_str());
		Ret = true;
	}
	kMessageLock.Release();
	return Ret;
}

std::string AspireMessageHandler::IsPreDefined(std::string &Index)
{
	string Ret = "";
	if(IsEnabled() == false)
		return Ret;
	kMessageLock.Acquire();
	map<std::string, std::string>::iterator Itr = KickMsgs.find(Index);
	if(Itr != KickMsgs.end())
		Ret = Itr->second;
	kMessageLock.Release();
	return Ret;
}