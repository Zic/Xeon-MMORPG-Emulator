/*
* Aspire Hearthstone
* Copyright (C) 2008 - 2009 AspireDev <http://www.aspiredev.org/>
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

Vehicle::Vehicle(uint64 guid) : Creature(guid)
{
	printf("Vehicle::Vehicle()\n");
	m_vehicleEntry = 0;
	m_passengerCount = 0;
	m_maxPassengers = 0;
	memset( m_vehicleSeats, 0, sizeof(uint32)*8 );
	m_isVehicle = true;
	Initialised = false;
}

Vehicle::~Vehicle()
{
}

void Vehicle::Destructor()
{
	if (m_passengers != NULL)
	{
		free(m_passengers);
		m_passengers = NULL;
	}
	m_passengerCount = 0;
	Creature::Destructor();
}

void Vehicle::Init()
{
	Creature::Init();
}

void Vehicle::InitSeats(uint32 vehicleEntry, PlayerPointer pRider)
{
	m_maxPassengers = 0;
	SetVehicleEntry(vehicleEntry);
	VehicleEntry * ve = dbcVehicle.LookupEntry( vehicleEntry );
	if(!ve)
	{
		DEBUG_LOG("Attempted to create non-existant vehicle %u.\n", vehicleEntry);
		return;
	}

	for( uint32 i = 0; i < 8; ++i )
	{
		if( ve->m_seatID[i] )
		{
			m_vehicleSeats[i] = dbcVehicleSeat.LookupEntry( ve->m_seatID[i] );
			++m_maxPassengers;
		}
	}

	m_passengers = (shared_ptr<Unit>*)malloc(sizeof(shared_ptr<Unit>) * m_maxPassengers);
	memset( m_passengers, 0, sizeof(shared_ptr<Unit>) * m_maxPassengers);
	Initialised = true;

	if( pRider != NULLPLR)
		AddPassenger( pRider );
}

bool Vehicle::Load(CreatureSpawn *spawn, uint32 mode, MapInfo *info)
{
	proto = CreatureProtoStorage.LookupEntry(spawn->entry);
	if(!proto)
		return false;

	if(proto->vehicle_entry != -1)
	{
		m_vehicleEntry = proto->vehicle_entry;
	}
	else
	{
		m_vehicleEntry = 124;
		DEBUG_LOG("Attempted to create vehicle %u with invalid vehicle_entry, defaulting to 124, check your creature_proto table.\n", proto->Id);
	}

	m_maxPassengers = 0;
	VehicleEntry * ve = dbcVehicle.LookupEntry( m_vehicleEntry );
	if(!ve)
	{
		DEBUG_LOG("Attempted to create non-existant vehicle %u.\n", GetVehicleEntry());
		return false;
	}

	for( uint32 i = 0; i < 8; ++i )
	{
		if( ve->m_seatID[i] )
		{
			m_vehicleSeats[i] = dbcVehicleSeat.LookupEntry( ve->m_seatID[i] );
			++m_maxPassengers;
		}
	}

	m_passengers = (shared_ptr<Unit>*)malloc(sizeof(shared_ptr<Unit>) * m_maxPassengers);
	memset( m_passengers, 0, sizeof(shared_ptr<Unit>) * m_maxPassengers);
	Initialised = true;

	return Creature::Load(spawn, mode, info);
}

void Vehicle::SendSpells(uint32 entry, PlayerPointer plr)
{
	list<uint32> avail_spells;
	for(list<AI_Spell*>::iterator itr = GetAIInterface()->m_spells.begin(); itr != GetAIInterface()->m_spells.end(); ++itr)
	{
		if((*itr)->agent == AGENT_SPELL)
			avail_spells.push_back((*itr)->spell->Id);
	}
	list<uint32>::iterator itr = avail_spells.begin();
	
	WorldPacket data(SMSG_PET_SPELLS, GetAIInterface()->m_spells.size() * 4 + 22);
	data << GetGUID();
	data << uint32(0x00000000);//pet family
	data << uint32(0x00000000);//unk
	data << uint32(0x00000101);//bar type

	// Send the actionbar
	for(uint8 i = 1; i < 10; ++i)
	{
		if(itr != avail_spells.end())
		{
			data << uint16((*itr)) << uint8(0) << uint8(i+8);
			++itr;
		}
		else
			data << uint16(0) << uint8(0) << uint8(i+8);
	}

	// Send the rest of the spells.
	data << uint8(avail_spells.size());
	for(itr = avail_spells.begin(); itr != avail_spells.end(); ++itr)
		data << uint16(*itr) << uint16(DEFAULT_SPELL_STATE);
	
	data << uint8(0);
	data << uint8(0);

	plr->GetSession()->SendPacket(&data);
}

void Vehicle::Despawn(uint32 delay, uint32 respawntime)
{
	if(delay)
	{
		sEventMgr.AddEvent(vehicle_shared_from_this(), &Vehicle::Despawn, (uint32)0, respawntime, EVENT_VEHICLE_RESPAWN, delay, 1,0);
		return;
	}

	if(!IsInWorld())
		return;

	if(respawntime)
	{
		/* get the cell with our SPAWN location. if we've moved cell this might break :P */
		MapCell * pCell = m_mapMgr->GetCellByCoords(m_spawnLocation.x, m_spawnLocation.y);
		if(!pCell)
			pCell = m_mapCell;
	
		ASSERT(pCell);
		pCell->_respawnObjects.insert(obj_shared_from_this());
		sEventMgr.RemoveEvents(shared_from_this());
		sEventMgr.AddEvent(m_mapMgr, &MapMgr::EventRespawnVehicle, vehicle_shared_from_this(), pCell, EVENT_VEHICLE_RESPAWN, respawntime, 1, 0);
		Unit::RemoveFromWorld(false);
		m_position = m_spawnLocation;
		m_respawnCell=pCell;
	}
	else
	{
		Unit::RemoveFromWorld(true);
		SafeDelete();
	}
}

void Vehicle::Update(uint32 time)
{
	Creature::Update(time);
}

void Vehicle::SafeDelete()
{
	sEventMgr.RemoveEvents(shared_from_this());
	sEventMgr.AddEvent(vehicle_shared_from_this(), &Vehicle::DeleteMe, EVENT_VEHICLE_SAFE_DELETE, 1000, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
}

void Vehicle::DeleteMe()
{
	if(IsInWorld())
		RemoveFromWorld(false, true);

	Destructor();
}

void Vehicle::AddPassenger(UnitPointer pPassenger)
{
	if(!m_maxPassengers) //how is this happening?
	{
		sLog.outColor(TRED, "Vehicle was not correctly initialised, retrying");
		sLog.outColor(TNORMAL, "\n");
		InitSeats(m_vehicleEntry);
	}

	// Find an available seat
	for(uint8 i = 0; i < m_maxPassengers; ++i)
	{
		if( !m_passengers[i] ) // Found a slot
		{
			_AddToSlot(pPassenger, i );
			break;
		}
	}
}

uint8 Vehicle::GetPassengerSlot(UnitPointer pPassenger)
{
	for(uint8 i = 0; i < m_maxPassengers; ++i)
	{
		if( m_passengers[i] == pPassenger ) // Found a slot
		{
			return i;
			break;
		}
	}
	return 0xFF;
}

void Vehicle::RemovePassenger(UnitPointer pPassenger)
{
	uint8 slot = pPassenger->m_inVehicleSeatId;
	pPassenger->RemoveFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_UNKNOWN_5 | UNIT_FLAG_UNKNOWN_6));

	WorldPacket data(MSG_MOVE_HEARTBEAT, 48);
	data << pPassenger->GetNewGUID();
	data << uint32(MOVEFLAG_FLYING);
	data << uint16(0x40);
	data << getMSTime();
	data << GetPositionX();
	data << GetPositionY();
	data << GetPositionZ();
	data << GetOrientation();
	data << uint32(0);
	pPassenger->SendMessageToSet(&data, false);

	if(pPassenger->IsPlayer())
	{
		PlayerPointer plr = TO_PLAYER(pPassenger);
		if(plr == GetControllingUnit())
		{
			plr->m_CurrentCharm.reset();
			data.Initialize(SMSG_CLIENT_CONTROL_UPDATE);
			data << GetNewGUID() << (uint8)0;
			plr->GetSession()->SendPacket(&data);
		}
		RemoveFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_PLAYER_CONTROLLED_CREATURE | UNIT_FLAG_PLAYER_CONTROLLED));

		plr->SetPlayerStatus(TRANSFER_PENDING);
		plr->m_sentTeleportPosition.ChangeCoords(GetPositionX(), GetPositionY(), GetPositionZ());
		plr->SetPosition(GetPositionX(), GetPositionY(), GetPositionZ(), GetOrientation());
		data.Initialize(MSG_MOVE_TELEPORT_ACK);
		data << plr->GetNewGUID();
		data << plr->m_teleportAckCounter;
		plr->m_teleportAckCounter++;
		data << uint32(MOVEFLAG_FLYING);
		data << uint16(0x40);
		data << getMSTime();
		data << GetPositionX();
		data << GetPositionY();
		data << GetPositionZ();
		data << GetOrientation();
		data << uint32(0);
		plr->GetSession()->SendPacket(&data);

		plr->SetUInt64Value( PLAYER_FARSIGHT, 0 );	

		data.Initialize(SMSG_PET_DISMISS_SOUND);
		data << uint32(m_vehicleSeats[slot]->m_exitUISoundID);
		data << plr->GetPosition();
		plr->GetSession()->SendPacket(&data);

		data.Initialize(SMSG_PET_SPELLS);
		data << uint64(0);
		data << uint32(0);
		plr->GetSession()->SendPacket(&data);
	}
		
	if(slot == 0)
	{
		m_redirectSpellPackets = NULLPLR;
		CombatStatus.Vanished();
		pPassenger->SetUInt64Value( UNIT_FIELD_CHARM, 0 );
		SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, GetCharmTempVal());
		SetUInt64Value(UNIT_FIELD_CHARMEDBY, 0);
		/* update target faction set */
		_setFaction();
		UpdateOppFactionSet();

		//GetAIInterface()->SetAIState(STATE_IDLE);
		GetAIInterface()->WipeHateList();
		GetAIInterface()->WipeTargetList();
		EnableAI();
		//Despawn(0,1000);

		//note: this is not blizz like we should despawn
		//and respawn at spawn point.
		//Well actually this is how blizz wanted it
		//but they couldnt get it to work xD
		GetAIInterface()->MoveTo(m_spawn->x, m_spawn->y, m_spawn->z, m_spawn->o);

		m_controllingUnit.reset();
		for(uint8 i = 0; i < m_maxPassengers; i++)
		{
			if(i != 0 && m_passengers[i])
			{
				RemovePassenger(m_passengers[i]);
			}
		}
	}

	pPassenger->m_CurrentVehicle.reset();
	pPassenger->m_inVehicleSeatId = 0xFF;
	m_passengers[slot].reset();
}

bool Vehicle::HasPassenger(UnitPointer pPassenger)
{
	for(uint8 i = 0; i < m_maxPassengers; ++i)
	{
		if( m_passengers[i] == pPassenger )
			return true;
	}
	return false;
}

void Vehicle::_AddToSlot(UnitPointer pPassenger, uint8 slot)
{
	assert( slot < m_maxPassengers );
	m_passengers[ slot ] = pPassenger;
	pPassenger->m_inVehicleSeatId = slot;
	/* pPassenger->m_transportGuid = GetGUID(); */
	LocationVector v;
	v.x = /* pPassenger->m_TransporterX =*/ m_vehicleSeats[slot]->m_attachmentOffsetX;
	v.y = /* pPassenger->m_TransporterY = */ m_vehicleSeats[slot]->m_attachmentOffsetY;
	v.z = /* pPassenger->m_TransporterZ = */ m_vehicleSeats[slot]->m_attachmentOffsetZ;
	v.o = /* pPassenger->m_TransporterO = */ 0;

	RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SELF_RES);
	// This is where the real magic happens
	if( pPassenger->IsPlayer() )
	{
		PlayerPointer pPlayer = TO_PLAYER(pPassenger);
		//pPlayer->Root();

		if(pPlayer->m_CurrentCharm)
			return;

		//Dismount
		if(pPlayer->m_MountSpellId)
			pPlayer->RemoveAura(pPlayer->m_MountSpellId);
	
		//Remove morph spells
		if(pPlayer->GetUInt32Value(UNIT_FIELD_DISPLAYID)!= pPlayer->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID))
		{
			pPlayer->RemoveAllAurasOfType(SPELL_AURA_TRANSFORM);
			pPlayer->RemoveAllAurasOfType(SPELL_AURA_MOD_SHAPESHIFT);
		}

		//Dismiss any pets
		if(pPlayer->GetSummon())
		{
		if(pPlayer->GetSummon()->GetUInt32Value(UNIT_CREATED_BY_SPELL) > 0)
			pPlayer->GetSummon()->Dismiss(false);				// warlock summon -> dismiss
		else
			pPlayer->GetSummon()->Remove(false, true, true);	// hunter pet -> just remove for later re-call
		}

		pPlayer->m_CurrentVehicle = vehicle_shared_from_this();

		pPlayer->SetFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_UNKNOWN_5 | UNIT_FLAG_UNKNOWN_6));

		//pPlayer->ResetHeartbeatCoords();
		pPlayer->SetUInt64Value(PLAYER_FARSIGHT, GetGUID());

		WorldPacket data3(SMSG_CONTROL_VEHICLE, 0);
		pPlayer->GetSession()->SendPacket(&data3);

		pPlayer->SetPlayerStatus(TRANSFER_PENDING);
		pPlayer->m_sentTeleportPosition.ChangeCoords(GetPositionX(), GetPositionY(), GetPositionZ());

		WorldPacket data(MSG_MOVE_TELEPORT, 68);
		data << pPlayer->GetNewGUID();
		data << pPlayer->m_teleportAckCounter;					// counter
		data << uint32(MOVEFLAG_TAXI);							// transport
		data << uint16(0);										// special flags
		data << uint32(getMSTime());							// time
		data << GetPositionX();									// position vector 
		data << GetPositionY();									// position vector 
		data << GetPositionZ();									// position vector 
		data << GetOrientation();								// orientaion
		// transport part
		data << GetGUID();										// transport guid
		data << v.x;											// transport offsetX
		data << v.y;											// transport offsetY
		data << v.z;											// transport offsetZ
		data << uint32(0);										// transport time
		data << uint8(slot);									// seat
		// end of transport part
		data << uint32(0);
		SendMessageToSet(&data, false);

		data.Initialize(MSG_MOVE_TELEPORT_ACK);
		data << pPlayer->GetNewGUID();
		data << pPlayer->m_teleportAckCounter;					// ack counter
		pPlayer->m_teleportAckCounter++;
		data << uint32(MOVEFLAG_TAXI);							// transport
		data << uint16(0);										// special flags
		data << uint32(getMSTime());							// time
		data << GetPositionX();									// position vector 
		data << GetPositionY();									// position vector 
		data << GetPositionZ();									// position vector 
		data << GetOrientation();								// orientaion
		// transport part
		data << GetGUID();										// transport guid
		data << v.x;											// transport offsetX
		data << v.y;											// transport offsetY
		data << v.z;											// transport offsetZ
		data << uint32(0);										// transport time
		data << uint8(slot);									// seat
		// end of transport part
		data << uint32(0);										// fall time
		pPlayer->GetSession()->SendPacket(&data);

		DisableAI();

		if(slot == 0)
		{
			SetControllingUnit(pPlayer);
			m_redirectSpellPackets = pPlayer;

			SetSpeed(RUN, m_runSpeed);
			SetSpeed(FLY, m_flySpeed);

			// send "switch mover" packet 
			data.Initialize(SMSG_CLIENT_CONTROL_UPDATE);
			data << GetNewGUID() << uint8(1);
			pPlayer->GetSession()->SendPacket(&data);

			pPlayer->m_CurrentCharm = vehicle_shared_from_this();
			pPlayer->SetUInt64Value(UNIT_FIELD_CHARM, GetGUID());
			SetCharmTempVal(GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
			SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, pPlayer->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
			SetUInt64Value(UNIT_FIELD_CHARMEDBY, pPlayer->GetGUID());
			SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED_CREATURE);

			/* update target faction set */
			_setFaction();
			UpdateOppFactionSet();

			SendSpells(GetEntry(), pPlayer);
		}

		data.Initialize(SMSG_PET_DISMISS_SOUND);
		data << uint32(m_vehicleSeats[slot]->m_enterUISoundID);
		data << pPlayer->GetPosition();
		pPlayer->GetSession()->SendPacket(&data);
	}
}

void Vehicle::MoveVehicle(float x, float y, float z, float o) //thanks andy
{
	SetPosition(x, y, z, o, false);
	for (uint8 i=0; i<m_maxPassengers; ++i)
	{
		if (m_passengers[i] != NULL)
			m_passengers[i]->SetPosition(x, y, z, o, false);
	}
}

void Vehicle::setDeathState(DeathState s)
{
	Creature::setDeathState(s);

	for (uint8 i=0; i<m_maxPassengers; ++i)
		if (m_passengers[i] != NULL)
			RemovePassenger(m_passengers[i]);
}

void Vehicle::SetSpeed(uint8 SpeedType, float value)
{
	if( value < 0.1f )
		value = 0.1f;

	uint8 buf[200];
	StackPacket data(SMSG_FORCE_RUN_SPEED_CHANGE, buf, 200);

	if( SpeedType != SWIMBACK )
	{
		data << GetNewGUID();
		data << uint32(0);
		if( SpeedType == RUN )
			data << uint8(1);

		data << value;
	}
	else
	{
		data << GetNewGUID();
		data << uint32(0);
		data << uint8(0);
		data << uint32(getMSTime());
		data << m_position.x;
		data << m_position.y;
		data << m_position.z;
		data << m_position.o;
		data << uint32(0);
		data << value;
	}
	
	switch(SpeedType)
	{
	case RUN:
		{
			data.SetOpcode(SMSG_FORCE_RUN_SPEED_CHANGE);
			m_runSpeed = value;
		}break;
	case RUNBACK:
		{
			data.SetOpcode(SMSG_FORCE_RUN_BACK_SPEED_CHANGE);
			m_backWalkSpeed = value;
		}break;
	case SWIM:
		{
			data.SetOpcode(SMSG_FORCE_SWIM_SPEED_CHANGE);
			m_swimSpeed = value;
		}break;
	case SWIMBACK:
		{
			data.SetOpcode(SMSG_FORCE_SWIM_BACK_SPEED_CHANGE);
			m_backSwimSpeed = value;
		}break;
	case FLY:
		{
			data.SetOpcode(SMSG_FORCE_FLIGHT_SPEED_CHANGE);
			m_flySpeed = value;
		}break;
	default:return;
	}
	
	SendMessageToSet(&data , true);

}

void WorldSession::HandleVehicleDismiss(WorldPacket & recv_data)
{
	if (GetPlayer() == NULL || !GetPlayer()->m_CurrentVehicle)
		return;

	GetPlayer()->m_CurrentVehicle->RemovePassenger(GetPlayer());
}

void WorldSession::HandleSpellClick( WorldPacket & recv_data )
{
	if (GetPlayer() == NULL || GetPlayer()->m_CurrentVehicle)
		return;

    CHECK_PACKET_SIZE(recv_data, 8);

    uint64 guid;
    recv_data >> guid;

	VehiclePointer pVehicle = GetPlayer()->GetMapMgr()->GetVehicle(GET_LOWGUID_PART(guid));
	UnitPointer pPlayer = TO_UNIT(GetPlayer());

	if(!pVehicle)
		return;
	
	if(!pVehicle->GetMaxPassengerCount())
		return;

	if(pVehicle->HasPassenger(pPlayer))
		pVehicle->RemovePassenger(pPlayer);

	pVehicle->AddPassenger(pPlayer);
}