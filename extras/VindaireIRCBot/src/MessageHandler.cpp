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

void IRCSession::HandleSuccessfulAuth(IRCMessage& recvData)
{
	// We're good to go.
	mConnState = CONN_REGISTERED;
	Log.Notice("IRCSession", "Authentication successful.");
	mServerRealName = recvData.hostmask;

	// Nickserv identification
	if(mUseNickServ)
	{
		Log.Notice("NickServ", "Sending NickServ identification.");
		SendChatMessage( PRIVMSG, "NickServ", "identify %s", mNickServPassword.c_str());
	}

	// Join the default channels
	std::map<string,string>::iterator itr = mChannelList.begin();
	for(; itr != mChannelList.end(); itr++)
	{
		string join = itr->first;
		if(itr->second != "")
			join += " " + itr->second;

		WriteLine("JOIN %s", join.c_str());
	}
}

void IRCSession::HandleMotdStart(IRCMessage& recvData)
{
	// The MOTD is coming 
	mHasFullMotd = false;
	mLastMotd = "";
}

void IRCSession::HandleMotd(IRCMessage& recvData)
{
	// Part of the MOTD, append it to the rest.
	if(mHasFullMotd)
		return;

	mLastMotd += recvData.args + NEWLINE;
}

void IRCSession::HandleMotdStop(IRCMessage& recvData)
{
	// The MOTD is over.
	Log.Notice("IRCSession", "Server Message of the Day received.");
	mHasFullMotd = true;
}

void IRCSession::HandleNotice(IRCMessage& recvData)
{
	Log.Color(TRED);
	printf("%s", recvData.source_nick.c_str());
	Log.Color(TYELLOW);
	printf(" sends notice: ");
	Log.Color(TNORMAL);
	printf("%s%s", recvData.args.c_str(), NEWLINE);
}

void IRCSession::HandlePrivmsg(IRCMessage& recvData)
{
	Log.Color(TYELLOW);
	printf("[%s] <%s> %s%s", recvData.target.c_str(), recvData.source_nick.c_str(), recvData.args.c_str(), NEWLINE);
	Log.Color(TNORMAL);

	// It's a command!
	if(recvData.args.substr(0, 1) != "!")
		return;

	if(mAntiSpamTicker + 2500 > GetTickCount())
		return;

	mAntiSpamTicker = GetTickCount();

	uint32 firstSpace = (uint32)recvData.args.find(' ');
	if(firstSpace == 0)
		firstSpace = (uint32)recvData.args.length();

	string cmd = string(strlwr((char*)recvData.args.substr(1, firstSpace - 1).c_str()));
	if(cmd == "2v2" || cmd == "3v3" || cmd == "5v5")
	{
		uint32 stype = 0;
		if(cmd == "3v3")
			stype = 1;
		else if(cmd == "5v5")
			stype = 2;

		QueryResult * result = mSQLConn->Query("SELECT ranking,name,rating FROM arenateams WHERE type = %u ORDER BY ranking ASC LIMIT 5", stype);
		if(result)
		{
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "+---+---------------------------+--------+");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "|#  |         Team Name         | Rating |");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "+---+---------------------------+--------+");
			do 
			{
				uint32 rank = result->Fetch()[0].GetUInt32();
				string name = result->Fetch()[1].GetString();
				uint32 rating = result->Fetch()[2].GetUInt32();

				SendChatMessage(PRIVMSG, recvData.target.c_str(), "|#%u | %25s |  %u  |", rank, name.c_str(), rating);
			} while(result->NextRow());
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "+---+---------------------------+--------+");
			delete result;
		}
		return;
	}

	if(cmd == "tophks")
	{
		QueryResult * result = mSQLConn->Query("SELECT name,killsLifeTime FROM characters ORDER BY killsLifeTime DESC LIMIT 5");
		if(result)
		{
			uint32 place = 1;
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "+---+--------------+-------+");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "| # |   Character  | Kills |");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "+---+--------------+-------+");
			do 
			{
				string name = result->Fetch()[0].GetString();
				uint32 kills = result->Fetch()[1].GetUInt32();

				SendChatMessage(PRIVMSG, recvData.target.c_str(), "| %u | %12s | %5u |", place, name.c_str(), kills);
				place++;
			} while(result->NextRow());
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "+---+--------------+-------+");
			delete result;
		}
		return;
	}

	if(cmd == "info")
	{
		// Really? Stop looking here. If you're going to edit this, at least don't steal credit.
		//  - Valroft
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "I am %s, an IRC bot programmed by Valroft of AspireDev to integrate with Ascent-based servers.", mNickName.c_str());
		return;
	}

	if(cmd == "online")
	{
		QueryResult * query = mSQLConn->Query("SELECT COUNT(*) FROM characters WHERE online > 0");
		if(query)
		{
			uint32 result = query->Fetch()[0].GetUInt32();
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "There are currently %u players online.", result);
			delete query;
		}
		query = mSQLConn->Query("SELECT COUNT(*) FROM characters WHERE online > 0 AND (race = 1 OR race = 3 OR race = 4 OR race = 7 OR race = 11)");
		if(query)
		{
			uint32 result = query->Fetch()[0].GetUInt32();
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "There are currently %u Alliance players online.", result);
			delete query;
		}
		query = mSQLConn->Query("SELECT COUNT(*) FROM characters WHERE online > 0 AND (race = 2 OR race = 5 OR race = 6 OR race = 8 OR race = 10)");
		if(query)
		{
			uint32 result = query->Fetch()[0].GetUInt32();
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "There are currently %u Horde players online.", result);
			delete query;
		}
		return;
	}

	if(cmd == "guildinfo")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		string guildname = mSQLConn->EscapeString(recvData.args.substr(firstSpace+1));
		
		QueryResult * result = mSQLConn->Query("SELECT guildId, guildName, leaderGuid, motd FROM guilds WHERE guildName = '%s'", guildname.c_str());
		if(result)
		{
			// Get the nameeee.
			uint32 guildid = result->Fetch()[0].GetUInt32();
			guildname = result->Fetch()[1].GetString();
			uint32 guid = result->Fetch()[2].GetUInt32();
			string motd = result->Fetch()[3].GetString();
			string leader = "UNKNOWN";
			QueryResult * result2 = mSQLConn->Query("SELECT name FROM characters WHERE guid = '%u'", guid);
			if(result2)
			{
				leader = result2->Fetch()[0].GetString();
				delete result2;
				result2 = NULL;
			}

			uint32 members = 1;
			result2 = mSQLConn->Query("SELECT COUNT(*) FROM guild_data WHERE guildid = %u", guildid);
			if(result2)
			{
				members = result2->Fetch()[0].GetUInt32();
				delete result2;
				result2 = NULL;
			}

			SendChatMessage( PRIVMSG, recvData.target.c_str(), "%s currently has %u members and is lead by %s. Their guild message of the day is: \"%s\".", guildname.c_str(), members, leader.c_str(), motd.c_str());

			delete result;
		}
	}

	if(cmd == "teaminfo")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		string teamname = mSQLConn->EscapeString(recvData.args.substr(firstSpace+1));
		QueryResult * result = mSQLConn->Query("SELECT leader,ranking,rating,type FROM arenateams WHERE name = '%s'", teamname.c_str());
		if(result)
		{
			do 
			{
				uint32 leaderguid = result->Fetch()[0].GetUInt32();
				uint32 ranking = result->Fetch()[1].GetUInt32();
				uint32 rating = result->Fetch()[2].GetUInt32();
				uint32 ttype = result->Fetch()[3].GetUInt32();
				string stype = "2v2";
				if(ttype == 1)
					stype = "3v3";
				else if(ttype == 2)
					stype = "5v5";

				// Now, we need the leader's name. :(
				QueryResult * result2 = mSQLConn->Query("SELECT name FROM characters WHERE guid = %u", leaderguid);
				if(!result2) return;

				string leadername = result2->Fetch()[0].GetString();

				SendChatMessage(PRIVMSG, recvData.target.c_str(), "%s is a %s team owned by %s with a rating of %u and is rated #%u in it's bracket.", teamname.c_str(), stype.c_str(), leadername.c_str(), rating, ranking);
			} while(result->NextRow());
			delete result;
		}
		else
		{
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "I can't find an arena team with that name.");
		}
	}

	if(cmd == "playerinfo")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		string player = mSQLConn->EscapeString(recvData.args.substr(firstSpace+1));
		QueryResult * result = mSQLConn->Query("SELECT level,race,class,killsLifeTime,gender,online FROM characters WHERE name = '%s'", player.c_str());
		if(result)
		{
			do 
			{
				string name = player;
				uint32 level = result->Fetch()[0].GetUInt32();
				uint32 raceid = result->Fetch()[1].GetUInt32();
				uint32 classid = result->Fetch()[2].GetUInt32();
				uint32 kills = result->Fetch()[3].GetUInt32();
				uint32 gender = result->Fetch()[4].GetUInt32();
				bool online = (result->Fetch()[5].GetUInt32() > 0);

				string races[] = { "", "human", "orc", "dwarf", "night elf", "undead", "tauren", "gnome", "troll", "", "blood elf", "draenei"};
				string classes[] = { "", "warrior", "paladin", "hunter", "rogue", "priest", "death knight", "shaman", "mage", "warlock", "", "druid" };

				SendChatMessage(PRIVMSG, recvData.target.c_str(), "%s is a level %u %s %s with %u honorable kills. %s is currently %s.", name.c_str(), level, races[raceid].c_str(), classes[classid].c_str(), kills, name.c_str(), online ? "online" : "offline");
			} while(result->NextRow());
			delete result;
		}
		else
		{
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "I could find no character with that name.");
		}
	}
	if(cmd == "roll")
	{
		uint32 result = mRandGenerator->randInt(100);
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "You roll a %u!", result);
	}
}

void IRCSession::HandlePing(IRCMessage& recvData)
{
	// Ping? Pong!
	WriteLine("PONG :%s", recvData.args.c_str());
	Log.Notice("IRCSession", "Ping? Pong!");
}

void IRCSession::HandlePong(IRCMessage& recvData)
{
	// Ping? Pong!
	WriteLine("PONG :%s", recvData.args.c_str());
	Log.Notice("IRCSession", "Ping? Pong!");
}

void IRCSession::HandleKick(IRCMessage& recvData)
{
	string kickedby = recvData.source_nick;
	string channel = recvData.argv[0];
	string kicked = recvData.argv[1];
	string reason = "";
	if(recvData.argc >= 3)
		reason = recvData.argv[2];

	// Were we kicked? Attempt to rejoin
	if(kicked == mNickName)
	{
		WriteLineForce("JOIN %s", recvData.target.c_str());
		Log.Color(TRED);
		printf("%s kicked me from %s for reason: \"%s\"\n", kickedby.c_str(), channel.c_str(), reason.c_str());
		Log.Color(TNORMAL);
	}
	else
	{
		printf("%s was kicked from %s by %s for \"%s\"\n", kicked.c_str(), channel.c_str(), kickedby.c_str(), reason.c_str());
	}
}

void IRCSession::HandleNick(IRCMessage& recvData)
{
	Log.Color(TRED);
	printf("%s", recvData.source_nick.c_str());
	Log.Color(TWHITE);
	printf(" changed his nick to: ");
	Log.Color(TRED);
	printf("%s\n", recvData.args.c_str());
	Log.Color(TNORMAL);
}