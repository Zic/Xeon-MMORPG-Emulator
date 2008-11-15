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

WorldStateHandler::WorldStateHandler(MapMgr &mgr) : m_Map(mgr)
{
	Load();
}

WorldStateHandler::~WorldStateHandler()
{
	map<uint32, WorldStateData*>::iterator Itr;
	for(Itr = worldStates.begin(); Itr != worldStates.end(); Itr++)
		delete Itr->second;
}

WorldStateData *WorldStateHandler::InitializeWorldState(uint32 Index, uint32 Val, int32 ZoneRef, int32 FactionRef)
{
	map<uint32, WorldStateData*>::iterator Itr = worldStates.find(Index);

	if(Itr == worldStates.end())
	{
		WorldStateData *Data = new WorldStateData;
		Data->Value = Val;
		Data->Faction = FactionRef;
		Data->Zone = ZoneRef;
		worldStates.insert(make_pair(Index, Data));
		return Data;
	}
	else
	{
		Itr->second->Value = Val;
		Itr->second->Faction = FactionRef;
		Itr->second->Zone = ZoneRef;
		return Itr->second;
	}
	return NULL;
}

void WorldStateHandler::UpdateWorldState(uint32 Index, uint32 Val)
{
	WorldStateData *wState;
	map<uint32, WorldStateData*>::iterator Itr = worldStates.find(Index);
	if(Itr == worldStates.end()) // Updating a non-existant wordstate? hmm..ok
		wState = InitializeWorldState(Index, Val);
	else
	{
		wState = Itr->second;
		wState->Value = Val;
	}

	if(wState == NULL) // in the realm of all possibilities it could happen.
		return;
	WorldPacket data(SMSG_UPDATE_WORLD_STATE, 10); // most likely not correct
	data << Index << Val;
	SendWorldStatePacket(wState, &data);
}

void WorldStateHandler::SendWorldStatePacket(WorldStateData *wState, WorldPacket *Data)
{
	PlayerStorageMap::iterator Itr;
	for(Itr = m_Map.m_PlayerStorage.begin(); Itr != m_Map.m_PlayerStorage.end(); Itr++)
	{
		Player *Plr = Itr->second;
		uint8 Team = Plr->GetTeam() == 0 ? 0 : 1;
		
		if(Plr->GetSession() == NULL)
			continue;
		if(wState->Faction != FactionRef_ALL && wState->Faction != Team)
			continue;
		if(wState->Zone != ZoneRef_ALL && wState->Zone != Plr->GetAreaID())
			continue;

		Plr->GetSession()->SendPacket(Data);
	}
}

void WorldStateHandler::SendWorldStates(Player *Plr)
{
	WorldPacket data(SMSG_INIT_WORLD_STATES, (worldStates.size() * 8) + 32);
	map<uint32, WorldStateData*>::iterator Itr;
	uint8 Team = Plr->GetTeam() == 0 ? 0 : 1;

	data << m_Map.GetMapId();
	data << Plr->GetZoneId();
	data << Plr->GetAreaID();

	for(Itr = worldStates.begin(); Itr != worldStates.end(); Itr++)
	{
		if(Plr->GetSession() == NULL)
			continue;
		if(Itr->second->Faction != FactionRef_ALL && Itr->second->Faction != Team)
			continue;
		if(Itr->second->Zone != ZoneRef_ALL && Itr->second->Zone != Plr->GetAreaID())
			continue;
		data << Itr->first << Itr->second->Value;
	}
	Plr->GetSession()->SendPacket(&data);	
}


// Database
void WorldStateHandler::Load()
{
	QueryResult *Result = WorldDatabase.Query("SELECT * FROM `worldstates` WHERE `MapId` = '%u'", m_Map.GetMapId());
	if(Result)
	{
		do
		{
			WorldStateData *Data = new WorldStateData;
			Field *Fields = Result->Fetch();
			Data->Value = Fields[2].GetUInt32();
			Data->Zone = Fields[3].GetUInt32();
			Data->Faction = Fields[4].GetUInt32();
			worldStates.insert(make_pair(Fields[1].GetUInt32(), Data));
		}while(Result->NextRow());
		WorldDatabase.FreeQueryResult(Result);	
	}
}