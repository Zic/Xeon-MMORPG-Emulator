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

// Some credit goes to summit and it's devs, as I've seen their implimentation
// And based some things off of the data they had

#ifndef WorldStateHandler_H
#define WorldStateHandler_H

#define FactionRef_ALL -1
#define ZoneRef_ALL -1
//#define WORLDSTATE_ENABLED // Until this is finished this define controls whether this is enabled or not

class MapMgr;

struct WorldStateData
{
	uint32 Value;
	int32 Zone; // Int32 to allow negative values
	int32 Faction; // same here
};

class WorldStateHandler
{
	public:
		WorldStateHandler(MapMgr &mgr);
		~WorldStateHandler();

		// WorldState Handling
		WorldStateData *InitializeWorldState(uint32 Index, uint32 Val, int32 ZoneRef = ZoneRef_ALL, int32 FactionRef = FactionRef_ALL);
		void UpdateWorldState(uint32 Index, uint32 Val);
		void SendWorldStates(Player *Plr);

		// Database
		void Load();

	private:
		MapMgr &m_Map;
		std::map<uint32, WorldStateData*> worldStates;

	protected:
		void SendWorldStatePacket(WorldStateData *wState, WorldPacket *Data);
};

#endif // WorldStateHandler_H