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
#include "Unit.h"
using namespace std;

//#define DEG2RAD (M_PI/180.0)
#define M_PI		3.14159265358979323846
#define M_H_PI		1.57079632679489661923
#define M_Q_PI		0.785398163397448309615

Object::Object() : m_position(0,0,0,0), m_spawnLocation(0,0,0,0)
{
#ifdef SHAREDPTR_DEBUGMODE
	printf("Object::Object()\n");
#endif
	m_phaseAura = NULLAURA;
	m_phaseMode = 1;
	m_mapId = 0;
	m_zoneId = 0;

	m_uint32Values = 0;
	m_objectUpdated = false;
	m_sharedPtrDestructed = false;

	m_valuesCount = 0;

	//official Values
	m_walkSpeed = 2.5f;
	m_runSpeed = 7.0f;
	m_base_runSpeed = m_runSpeed;
	m_base_walkSpeed = m_walkSpeed;

	m_flySpeed = 7.0f;
	m_backFlySpeed = 4.5f;

	m_backWalkSpeed = 4.5f;	// this should really be named m_backRunSpeed
	m_swimSpeed = 4.722222f;
	m_backSwimSpeed = 2.5f;
	m_turnRate = 3.141593f;

	m_mapMgr = NULLMAPMGR;
	m_mapCell = 0;

	mSemaphoreTeleport = false;

	dynObj = NULLDYN;

	m_faction = NULL;
	m_factionDBC = NULL;

	m_instanceId = 0;
	Active = false;
	m_inQueue = false;
	m_extensions = NULL;
	m_loadedFromDB = false;
	m_loot.gold = 0;
	m_looted = false;
	m_isVehicle = false;

	m_objectsInRange.clear();
	m_inRangePlayers.clear();
	m_oppFactsInRange.clear();
}

Object::~Object( )
{
#ifdef SHAREDPTR_DEBUGMODE
	printf("Object::~Object()\n");
#endif

	if( !m_sharedPtrDestructed )
	{
		Log.Error("SharedPtr", "Failure to call Object Destructor method on deletion.");
#ifdef WIN32
		CStackWalker cw;
		cw.ShowCallstack();
#endif
	}
}

void Object::Init()
{
}

void Object::Destructor()
{
	m_sharedPtrDestructed = true;

	if(m_objectTypeId != TYPEID_ITEM)
		ASSERT(!m_inQueue);

	if (IsInWorld() && m_objectTypeId != TYPEID_ITEM && m_objectTypeId != TYPEID_CONTAINER)
	{
		RemoveFromWorld(false);
	}

	// for linux
	m_instanceId = -1;
	m_objectTypeId=TYPEID_UNUSED;

	if( m_extensions != NULL )
		delete m_extensions;

#ifdef SHAREDPTR_DEBUGMODE
	//ObjectPointer blah = obj_shared_from_this();
	// breakpoint this for further debugging
	printf("Object::Destructor()\n");
#endif
}

void Object::SetPhase(int32 phase)
{
	m_phaseMode = phase;
}

void Object::EnablePhase(int32 phaseMode)
{
	m_phaseMode |= phaseMode;
}

void Object::DisablePhase(int32 phaseMode)
{
	m_phaseMode &= ~phaseMode;
}

void Object::_Create( uint32 mapid, float x, float y, float z, float ang )
{
	m_mapId = mapid;
	m_position.ChangeCoords(x, y, z, ang);
	m_spawnLocation.ChangeCoords(x, y, z, ang);
	m_lastMapUpdatePosition.ChangeCoords(x,y,z,ang);
}

uint32 Object::BuildCreateUpdateBlockForPlayer(ByteBuffer *data, PlayerPointer target)
{
	uint8 flags = 0;
	uint32 flags2 = 0;

	uint8 updatetype = UPDATETYPE_CREATE_OBJECT;
	if(m_objectTypeId == TYPEID_CORPSE)
	{
		if(m_uint32Values[CORPSE_FIELD_DISPLAY_ID] == 0)
			return 0;
	}

	// any other case
	switch(m_objectTypeId)
	{
		// items + containers: 0x8
	case TYPEID_ITEM:
	case TYPEID_CONTAINER:
		flags = 0x18;
		break;
		
		// player/unit: 0x68 (except self)
	case TYPEID_UNIT:
		flags = 0x70;
		break;

	case TYPEID_PLAYER:
		flags = 0x70;
		break;

		// gameobject/dynamicobject
	case TYPEID_GAMEOBJECT:
	case TYPEID_DYNAMICOBJECT:
	case TYPEID_CORPSE:
		flags = 0x58;
		break;
	}

	if(GetTypeFromGUID() == HIGHGUID_TYPE_VEHICLE)
		flags |= 0x80;

	if(target == obj_shared_from_this())
	{
		// player creating self
		flags |= 0x01;
		updatetype = UPDATETYPE_CREATE_YOURSELF;
	}

	// gameobject stuff
	if(m_objectTypeId == TYPEID_GAMEOBJECT)
	{
		switch(GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPE_ID))
		{
			case GAMEOBJECT_TYPE_MO_TRANSPORT:  
				{
					if(GetTypeFromGUID() != HIGHGUID_TYPE_TRANSPORTER)
						return 0;   // bad transporter
					else
						flags = 0x5A;
				}break;

			case GAMEOBJECT_TYPE_TRANSPORT:
				{
					/* deeprun tram, etc */
					flags = 0x5A;
				}break;

			case GAMEOBJECT_TYPE_DUEL_ARBITER:
				{
					// duel flags have to stay as updatetype 3, otherwise
					// it won't animate
					updatetype = UPDATETYPE_CREATE_YOURSELF;
				}break;
		}
	}

	// build our actual update
	*data << updatetype;

	// we shouldn't be here, under any circumstances, unless we have a wowguid..
	ASSERT(m_wowGuid.GetNewGuidLen());
	*data << m_wowGuid;
	
	*data << m_objectTypeId;

	_BuildMovementUpdate(data, flags, flags2, target);

	// we have dirty data, or are creating for ourself.
	UpdateMask updateMask;
	updateMask.SetCount( m_valuesCount );
	_SetCreateBits( &updateMask, target );

	// this will cache automatically if needed
	_BuildValuesUpdate( data, &updateMask, target );

	// update count: 1 ;)
	return 1;
}

//That is dirty fix it actually creates update of 1 field with
//the given value ignoring existing changes in fields and so on
//usefull if we want update this field for certain players
//NOTE: it does not change fields. This is also very fast method
WorldPacket *Object::BuildFieldUpdatePacket( uint32 index,uint32 value)
{
   // uint64 guidfields = GetGUID();
   // uint8 guidmask = 0;
	WorldPacket * packet=new WorldPacket(1500);
	packet->SetOpcode( SMSG_UPDATE_OBJECT );
	
	*packet << (uint32)1;//number of update/create blocks
	*packet << (uint8)0;//unknown

	*packet << (uint8) UPDATETYPE_VALUES;		// update type == update
	*packet << GetNewGUID();

	uint32 mBlocks = index/32+1;
	*packet << (uint8)mBlocks;
	
	for(uint32 dword_n=mBlocks-1;dword_n;dword_n--)
	*packet <<(uint32)0;

	*packet <<(((uint32)(1))<<(index%32));
	*packet << value;
	
	return packet;
}

void Object::BuildFieldUpdatePacket(PlayerPointer Target, uint32 Index, uint32 Value)
{
	ByteBuffer buf(500);

	BuildFieldUpdatePacket(&buf, Index, Value);
	Target->PushUpdateData(&buf, 1);
}

void Object::BuildFieldUpdatePacket(ByteBuffer * buf, uint32 Index, uint32 Value)
{
	*buf << uint8(UPDATETYPE_VALUES);
	*buf << GetNewGUID();

	uint32 mBlocks = Index/32+1;
	*buf << (uint8)mBlocks;

	for(uint32 dword_n=mBlocks-1;dword_n;dword_n--)
		*buf <<(uint32)0;

	*buf <<(((uint32)(1))<<(Index%32));
	*buf << Value;
}

uint32 Object::BuildValuesUpdateBlockForPlayer(ByteBuffer *data, PlayerPointer target)
{
	UpdateMask updateMask;
	updateMask.SetCount( m_valuesCount );
	_SetUpdateBits( &updateMask, target );
	for(uint32 x = 0; x < m_valuesCount; ++x)
	{
		if(updateMask.GetBit(x))
		{
			*data << (uint8) UPDATETYPE_VALUES;		// update type == update
			ASSERT(m_wowGuid.GetNewGuidLen());
			*data << m_wowGuid;

			_BuildValuesUpdate( data, &updateMask, target );
			return 1;
		}
	}

	return 0;
}

uint32 Object::BuildValuesUpdateBlockForPlayer(ByteBuffer * buf, UpdateMask * mask )
{
	// returns: update count
	*buf << (uint8) UPDATETYPE_VALUES;		// update type == update

	ASSERT(m_wowGuid.GetNewGuidLen());
	*buf << m_wowGuid;

	_BuildValuesUpdate( buf, mask, NULLPLR );

	// 1 update.
	return 1;
}

void Object::DestroyForPlayer(PlayerPointer target) const
{
	if(!target || target->GetSession() == 0) return;

	WorldPacket data(SMSG_DESTROY_OBJECT, 8);
	data << GetGUID();

	target->GetSession()->SendPacket( &data );
}


///////////////////////////////////////////////////////////////
/// Build the Movement Data portion of the update packet
/// Fills the data with this object's movement/speed info
/// TODO: rewrite this stuff, document unknown fields and flags
uint32 TimeStamp();

void Object::_BuildMovementUpdate(ByteBuffer * data, uint8 flags, uint32 flags2, PlayerPointer target )
{
	ByteBuffer *splinebuf = (m_objectTypeId == TYPEID_UNIT) ? target->GetAndRemoveSplinePacket(GetGUID()) : 0;
	*data << (uint8)flags;

	PlayerPointer pThis = NULLPLR;
	if(m_objectTypeId == TYPEID_PLAYER)
	{
		pThis = plr_shared_from_this();
		if(target == obj_shared_from_this())
		{
			// Updating our last speeds.
			pThis->UpdateLastSpeeds();
		}
	}

	if (flags & 0x20)
	{
		if(pThis && pThis->m_TransporterGUID != 0)
			flags2 |= 0x200;
		else if(m_objectTypeId==TYPEID_UNIT && creature_shared_from_this()->m_transportGuid != 0 && creature_shared_from_this()->m_transportPosition != NULL)
			flags2 |= 0x200;
		else if (IsUnit() && unit_shared_from_this()->m_CurrentVehicle != NULL)
			flags2 |= 0x200;

		if(splinebuf)
		{
			flags2 |= 0x08000001;	   //1=move forward
			if(GetTypeId() == TYPEID_UNIT)
			{
				if( unit_shared_from_this()->GetAIInterface()->m_moveRun == false)
					flags2 |= 0x100;	//100=walk
			}			
		}

		if(GetTypeId() == TYPEID_UNIT)
		{
			//		 Don't know what this is, but I've only seen it applied to spirit healers.
			//		 maybe some sort of invisibility flag? :/

			switch(GetEntry())
			{
			case 6491:  // Spirit Healer
			case 13116: // Alliance Spirit Guide
			case 13117: // Horde Spirit Guide
				{
					flags2 |= 0x10000000;
				}break;
			}
		
			if( unit_shared_from_this()->GetAIInterface()->IsFlying())
//				flags2 |= 0x800; //in 2.3 this is some state that i was not able to decode yet
				flags2 |= 0x400; //Zack : Teribus the Cursed had flag 400 instead of 800 and he is flying all the time 
			if( creature_shared_from_this()->proto && creature_shared_from_this()->proto->extra_a9_flags)
			{
				if(!(flags2 & 0x0200))
					flags2 |= creature_shared_from_this()->proto->extra_a9_flags;
			}
/*			if(GetGUIDHigh() == HIGHGUID_WAYPOINT)
			{
				if(GetUInt32Value(UNIT_FIELD_STAT0) == 768)		// flying waypoint
					flags2 |= 0x800;
			}*/
		}

		*data << (uint32)flags2;

		*data << (uint16)0;

		*data << getMSTime(); // this appears to be time in ms but can be any thing

		// this stuff:
		//   0x01 -> Enable Swimming?
		//   0x04 -> ??
		//   0x10 -> disables movement compensation and causes players to jump around all the place
		//   0x40 -> disables movement compensation and causes players to jump around all the place

		/*static uint8 fl = 0x04;
		*data << uint8(fl);		// wtf? added in 2.3.0*/
		/*if(target==this)
			*data<<uint8(0x53);
		else
			*data<<uint8(0);*/
		//*data << uint8(0x1);
	}

	if (flags & 0x40)
	{
		if(flags & 0x2)
		{
			*data << (float)m_position.x;
			*data << (float)m_position.y;
			*data << (float)m_position.z;
			*data << (float)m_position.o;
		}
		else
		{
			*data << m_position;
			*data << m_position.o;
		}

		if(flags & 0x20 && flags2 & 0x0200)
		{
			if (IsUnit() && unit_shared_from_this()->m_CurrentVehicle != NULL)
			{
				UnitPointer pUnit = unit_shared_from_this();
				VehiclePointer vehicle = unit_shared_from_this()->m_CurrentVehicle;

				if (pUnit->m_inVehicleSeatId != 0xFF && vehicle->m_vehicleSeats[pUnit->m_inVehicleSeatId] != NULL)
				{
					*data << pUnit->m_CurrentVehicle->GetGUID();
					*data << vehicle->m_vehicleSeats[pUnit->m_inVehicleSeatId]->m_attachmentOffsetX;
					*data << vehicle->m_vehicleSeats[pUnit->m_inVehicleSeatId]->m_attachmentOffsetY;
					*data << vehicle->m_vehicleSeats[pUnit->m_inVehicleSeatId]->m_attachmentOffsetZ;
					*data << float(0.0f);
					*data << uint32(0);
					*data << pUnit->m_inVehicleSeatId;
				}
				else
				{
					*data << uint64(0);
					*data << float(0);
					*data << float(0);
					*data << float(0);
					*data << float(0);
					*data << uint32(0);
					*data << uint8(0);
				}
			}
			else if(pThis)
			{
				*data << pThis->m_TransporterGUID;
				*data << pThis->m_TransporterX << pThis->m_TransporterY << pThis->m_TransporterZ << pThis->m_TransporterO;
				*data << pThis->m_TransporterUnk << uint8(0);
			}
			else if(m_objectTypeId==TYPEID_UNIT && creature_shared_from_this()->m_transportPosition != NULL)
			{
				*data << creature_shared_from_this()->m_transportGuid;
				*data << uint32(HIGHGUID_TYPE_TRANSPORTER);
				*data << creature_shared_from_this()->m_transportPosition->x << creature_shared_from_this()->m_transportPosition->y << 
					creature_shared_from_this()->m_transportPosition->z << creature_shared_from_this()->m_transportPosition->o;
				*data << float(0.0f);
			}
		}
	}

	if (flags & 0x20)
	{
		*data << (uint32)0;
	}

	if (flags & 0x20 && flags2 & 0x2000)
	{
		*data << (float)0;
		*data << (float)1.0;
		*data << (float)0;
		*data << (float)0;
	}

	if (flags & 0x20)
	{
		*data << m_walkSpeed;	 // walk speed
		*data << m_runSpeed;	  // run speed
		*data << m_backWalkSpeed; // backwards walk speed
		*data << m_swimSpeed;	 // swim speed
		*data << m_backSwimSpeed; // backwards swim speed
		*data << m_flySpeed;		// fly speed
		*data << m_backFlySpeed;	// back fly speed
		*data << m_turnRate;	  // turn rate
		*data << float(7);
	}

	if(splinebuf)
	{
		data->append(*splinebuf);
		delete splinebuf;
	}

	if(flags & 0x8)
	{
		*data << GetUInt32Value(OBJECT_FIELD_GUID);
		if(flags & 0x10)
			*data << GetUInt32Value(OBJECT_FIELD_GUID + 1);
	}
	else if(flags & 0x10)
		*data << GetUInt32Value(OBJECT_FIELD_GUID);

	if(flags & 0x2)
	{
		if(target)
		{
			/*int32 m_time = TimeStamp() - target->GetSession()->m_clientTimeDelay;
			m_time += target->GetSession()->m_moveDelayTime;
			*data << m_time;*/
			*data << getMSTime();
		}
		else
            *data << getMSTime();
	}
	
	if (flags & 0x80)
	{
			*data << vehicle_shared_from_this()->GetVehicleEntry() << float(0.0f); //facing adjustment
	}
}

//=======================================================================================
//  Creates an update block with the values of this object as
//  determined by the updateMask.
//=======================================================================================
void Object::_BuildValuesUpdate(ByteBuffer * data, UpdateMask *updateMask, PlayerPointer target)
{
	bool reset = false;

	uint32 oldState = 0;
	if(updateMask->GetBit(OBJECT_FIELD_GUID) && target)	   // We're creating.
	{
		CreaturePointer pThis = creature_shared_from_this();
		if(m_objectTypeId == TYPEID_UNIT && pThis->m_taggingPlayer)		// tagged group will have tagged player
		{
			// set tagged visual
			if( (pThis->m_taggingGroup != 0 && target->m_playerInfo->m_Group != NULL && target->m_playerInfo->m_Group->GetID() == pThis->m_taggingGroup) ||
				(pThis->m_taggingPlayer == target->GetLowGUID()) )
			{
				m_uint32Values[UNIT_DYNAMIC_FLAGS] |= U_DYN_FLAG_TAPPED_BY_PLAYER;
				if( pThis->m_loot.HasItems() )
					m_uint32Values[UNIT_DYNAMIC_FLAGS] |= U_DYN_FLAG_LOOTABLE;
			}
			else
			{
				m_uint32Values[UNIT_DYNAMIC_FLAGS] |= U_DYN_FLAG_TAGGED_BY_OTHER;
			}

			updateMask->SetBit(UNIT_DYNAMIC_FLAGS);
			reset = true;
		}

		if(target && GetTypeId() == TYPEID_GAMEOBJECT)
		{
			shared_ptr<GameObject>go = gob_shared_from_this();
			GameObjectInfo *info;
			info = go->GetInfo();
			if(info && info->InvolvedQuestCount && info->InvolvedQuestIds[0])
			{
				for(uint32 v = 0; v < info->InvolvedQuestCount; ++v)
				{
					if( target->GetQuestLogForEntry(info->InvolvedQuestIds[v]) != NULL )
					{
						m_uint32Values[GAMEOBJECT_DYNAMIC] = GO_DYNFLAG_QUEST;
						uint32 state = GetUInt32Value(GAMEOBJECT_BYTES_1);
						oldState = state;
						uint8 * v = (uint8*)&state;
						v[GAMEOBJECT_BYTES_STATE] = 1;
						m_uint32Values[GAMEOBJECT_BYTES_1] = state;
						m_uint32Values[GAMEOBJECT_FLAGS] &= ~GO_FLAG_IN_USE;

						updateMask->SetBit(GAMEOBJECT_BYTES_1);
						updateMask->SetBit(GAMEOBJECT_DYNAMIC);
						updateMask->SetBit(GAMEOBJECT_FLAGS);

						reset = true;
						break;
					}
				}
			}
		}
	}

	WPAssert( updateMask && updateMask->GetCount() == m_valuesCount );
	uint32 bc;
	uint32 values_count;
	if( m_valuesCount > ( 2 * 0x20 ) )//if number of blocks > 2->  unit and player+item container
	{
		bc = updateMask->GetUpdateBlockCount();
		values_count = (uint32)min( bc * 32, m_valuesCount );

	}
	else
	{
		bc=updateMask->GetBlockCount();
		values_count=m_valuesCount;
	}

	*data << (uint8)bc;
	data->append( updateMask->GetMask(), bc*4 );
	  
	for( uint32 index = 0; index < values_count; ++index )
	{
		if( updateMask->GetBit( index ) )
		{
			*data << m_uint32Values[ index ];
			updateMask->UnsetBit( index );
		}
	}

	if(reset)
	{
		switch(GetTypeId())
		{
		case TYPEID_UNIT:
			m_uint32Values[UNIT_DYNAMIC_FLAGS] &= ~(U_DYN_FLAG_TAGGED_BY_OTHER | U_DYN_FLAG_LOOTABLE | U_DYN_FLAG_TAPPED_BY_PLAYER);
			break;
		case TYPEID_GAMEOBJECT:
			m_uint32Values[GAMEOBJECT_DYNAMIC] = 0;
			m_uint32Values[GAMEOBJECT_FLAGS] |= GO_FLAG_IN_USE;
			m_uint32Values[GAMEOBJECT_BYTES_1] = oldState;
			break;
		}
	}

}

void Object::BuildHeartBeatMsg(WorldPacket *data) const
{
	data->Initialize(MSG_MOVE_HEARTBEAT);

	*data << GetGUID();

	*data << uint32(0); // flags
	*data << uint32(0); // mysterious value #1

	*data << m_position;
	*data << m_position.o;
}

WorldPacket * Object::BuildTeleportAckMsg(const LocationVector & v)
{
	///////////////////////////////////////
	//Update player on the client with TELEPORT_ACK
	if( IsInWorld() )		// only send when inworld
		plr_shared_from_this()->SetPlayerStatus( TRANSFER_PENDING );

	WorldPacket * data = new WorldPacket(MSG_MOVE_TELEPORT_ACK, 80);
	*data << GetNewGUID();

	//First 4 bytes = no idea what it is
	*data << uint32(2); // flags
	*data << uint32(0); // mysterious value #1
	*data << uint16(0);

	*data << float(0);
	*data << v;
	*data << v.o;
	*data << uint16(2);
	*data << uint8(0);
	return data;
}

bool Object::SetPosition(const LocationVector & v, bool allowPorting /* = false */)
{
	bool updateMap = false, result = true;

	if (m_position.x != v.x || m_position.y != v.y)
		updateMap = true;

	m_position = const_cast<LocationVector&>(v);

	if (!allowPorting && v.z < -500)
	{
		m_position.z = 500;
		DEBUG_LOG( "setPosition: fell through map; height ported" );

		result = false;
	}

	if (IsInWorld() && updateMap)
	{
		m_mapMgr->ChangeObjectLocation(obj_shared_from_this());
	}

	return result;
}

bool Object::SetPosition( float newX, float newY, float newZ, float newOrientation, bool allowPorting )
{
	bool updateMap = false, result = true;

	//if (m_position.x != newX || m_position.y != newY)
		//updateMap = true;
	if(m_lastMapUpdatePosition.Distance2DSq(newX, newY) > 4.0f)		/* 2.0f */
		updateMap = true;

	m_position.ChangeCoords(newX, newY, newZ, newOrientation);

	if (!allowPorting && newZ < -500)
	{
		m_position.z = 500;
		DEBUG_LOG( "setPosition: fell through map; height ported" );

		result = false;
	}

	if (IsInWorld() && updateMap)
	{
		m_lastMapUpdatePosition.ChangeCoords(newX,newY,newZ,newOrientation);
		m_mapMgr->ChangeObjectLocation(obj_shared_from_this());

		if( m_objectTypeId == TYPEID_PLAYER && plr_shared_from_this()->GetGroup() && plr_shared_from_this()->m_last_group_position.Distance2DSq(m_position) > 25.0f ) // distance of 5.0
		{
            plr_shared_from_this()->GetGroup()->HandlePartialChange( PARTY_UPDATE_FLAG_POSITION, plr_shared_from_this() );
		}	
	}

	return result;
}

void Object::SetRotation( uint64 guid )
{
	WorldPacket data(SMSG_AI_REACTION, 12);
	data << guid;
	data << uint32(2);
	SendMessageToSet(&data, false);
}

void Object::OutPacketToSet(uint16 Opcode, uint16 Len, const void * Data, bool self)
{
	if(self && m_objectTypeId == TYPEID_PLAYER)
		plr_shared_from_this()->GetSession()->OutPacket(Opcode, Len, Data);

	if(!IsInWorld())
		return;

	unordered_set<PlayerPointer  >::iterator itr = m_inRangePlayers.begin();
	unordered_set<PlayerPointer  >::iterator it_end = m_inRangePlayers.end();
	int gm = ( m_objectTypeId == TYPEID_PLAYER ? player_shared_from_this()->m_isGmInvisible : 0 );
	for(; itr != it_end; ++itr)
	{
		ASSERT((*itr)->GetSession());
		if( gm )
		{
			if( (*itr)->GetSession()->GetPermissionCount() > 0 )
				(*itr)->GetSession()->OutPacket(Opcode, Len, Data);
		}
		else
		{
			(*itr)->GetSession()->OutPacket(Opcode, Len, Data);
		}
	}
}

void Object::SendMessageToSet(WorldPacket *data, bool bToSelf,bool myteam_only)
{
	if(bToSelf && m_objectTypeId == TYPEID_PLAYER)
	{
		plr_shared_from_this()->GetSession()->SendPacket(data);		
	}

	if(!IsInWorld())
		return;

	unordered_set<PlayerPointer  >::iterator itr = m_inRangePlayers.begin();
	unordered_set<PlayerPointer  >::iterator it_end = m_inRangePlayers.end();
	bool gminvis = (m_objectTypeId == TYPEID_PLAYER ? player_shared_from_this()->m_isGmInvisible : false);
	//Zehamster: Splitting into if/else allows us to avoid testing "gminvis==true" at each loop...
	//		   saving cpu cycles. Chat messages will be sent to everybody even if player is invisible.
	if(myteam_only)
	{
		uint32 myteam=plr_shared_from_this()->GetTeam();
		if(gminvis && data->GetOpcode()!=SMSG_MESSAGECHAT)
		{
			for(; itr != it_end; ++itr)
			{
				ASSERT((*itr)->GetSession());
				if((*itr)->GetSession()->GetPermissionCount() > 0 && (*itr)->GetTeam()==myteam && PhasedCanInteract(*itr))
					(*itr)->GetSession()->SendPacket(data);
			}
		}
		else
		{
			for(; itr != it_end; ++itr)
			{
				ASSERT((*itr)->GetSession());
				if((*itr)->GetTeam()==myteam && PhasedCanInteract(*itr))
					(*itr)->GetSession()->SendPacket(data);
			}
		}
	}
	else
	{
		if(gminvis && data->GetOpcode()!=SMSG_MESSAGECHAT)
		{
			for(; itr != it_end; ++itr)
			{
				ASSERT((*itr)->GetSession());
				if((*itr)->GetSession()->GetPermissionCount() > 0 && PhasedCanInteract(*itr))
					(*itr)->GetSession()->SendPacket(data);
			}
		}
		else
		{
			for(; itr != it_end; ++itr)
			{
				ASSERT((*itr)->GetSession());
				if( PhasedCanInteract(*itr) )
					(*itr)->GetSession()->SendPacket(data);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
/// Fill the object's Update Values from a space deliminated list of values.
void Object::LoadValues(const char* data)
{
	// thread-safe ;) strtok is not.
	std::string ndata = data;
	std::string::size_type last_pos = 0, pos = 0;
	uint32 index = 0;
	uint32 val;
	do 
	{
		// prevent overflow
		if(index >= m_valuesCount)
		{
			break;
		}
		pos = ndata.find(" ", last_pos);
		val = atol(ndata.substr(last_pos, (pos-last_pos)).c_str());
		if(m_uint32Values[index] == 0)
			m_uint32Values[index] = val;
		last_pos = pos+1;
		++index;
	} while(pos != std::string::npos);
}

void Object::_SetUpdateBits(UpdateMask *updateMask, PlayerPointer target) const
{
	*updateMask = m_updateMask;
}


void Object::_SetCreateBits(UpdateMask *updateMask, PlayerPointer target) const
{
	/*for( uint16 index = 0; index < m_valuesCount; index++ )
	{
		if(GetUInt32Value(index) != 0)
			updateMask->SetBit(index);
	}*/
	for(uint32 i = 0; i < m_valuesCount; ++i)
		if(m_uint32Values[i] != 0)
			updateMask->SetBit(i);
}

void Object::AddToWorld()
{
	shared_ptr<MapMgr> mapMgr = sInstanceMgr.GetInstance(obj_shared_from_this());
	if(!mapMgr)
		return; //instance add failed

	if( IsPlayer() )
	{
		// battleground checks
		PlayerPointer p = plr_shared_from_this();
		if( p->m_bg == NULL && mapMgr->m_battleground != NULL )
		{
			// player hasn't been registered in the battleground, ok.
			// that means we re-logged into one. if it's an arena, don't allow it!
			// also, don't allow them in if the bg is full.

			if( /*( mapMgr->m_battleground->IsArena() && mapMgr->m_battleground->HasStarted() ) ||*/
				( !mapMgr->m_battleground->CanPlayerJoin(p) ) && !p->bGMTagOn )	// above check isn't needed, done in Arena::CanPlayerJoin.
			{
				//p->EjectFromInstance();
				return;
			}
		}
	}

	m_mapMgr = mapMgr;
	m_inQueue = true;

	mapMgr->AddObject(obj_shared_from_this());

	// correct incorrect instance id's
	m_instanceId = m_mapMgr->GetInstanceID();

	mSemaphoreTeleport = false;
}

void Object::AddToWorld(shared_ptr<MapMgr> pMapMgr)
{
	if(!pMapMgr)
		return; //instance add failed

	m_mapMgr = pMapMgr;
	m_inQueue = true;

	pMapMgr->AddObject(obj_shared_from_this());

	// correct incorrect instance id's
	m_instanceId = pMapMgr->GetInstanceID();

	mSemaphoreTeleport = false;
}

//Unlike addtoworld it pushes it directly ignoring add pool
//this can only be called from the thread of mapmgr!!!
void Object::PushToWorld(shared_ptr<MapMgr>mgr)
{
	if(!mgr/* || (m_mapMgr != NULL && m_mapCell != NULL) */)
		return; //instance add failed

	m_mapId=mgr->GetMapId();
	m_instanceId = mgr->GetInstanceID();

	m_mapMgr = mgr;
	OnPrePushToWorld();

	mgr->PushObject(obj_shared_from_this());

	// correct incorrect instance id's
	mSemaphoreTeleport = false;
	m_inQueue = false;
   
	event_Relocate();
	
	// call virtual function to handle stuff.. :P
	OnPushToWorld();
}

void Object::RemoveFromWorld(bool free_guid)
{
	// clear loot
	ClearLoot();
	if(dynObj != 0)
		dynObj->Remove();

	ASSERT(m_mapMgr);
	shared_ptr<MapMgr> m = m_mapMgr;
	m_mapMgr = NULLMAPMGR;

	mSemaphoreTeleport = true;

	m->RemoveObject(obj_shared_from_this(), free_guid);
	
	// remove any spells / free memory
	sEventMgr.RemoveEvents(shared_from_this(), EVENT_UNIT_SPELL_HIT);

	// update our event holder
	event_Relocate();
}

//! Set uint32 property
void Object::SetUInt32Value( const uint32 index, const uint32 value )
{
	ASSERT( index < m_valuesCount );
	// save updating when val isn't changing.
	if(m_uint32Values[index] == value)
		return;

	m_uint32Values[ index ] = value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}

	// Group update handling
	if(m_objectTypeId == TYPEID_PLAYER)
	{
		if(IsInWorld())
		{
			Group* pGroup = player_shared_from_this()->GetGroup();
			if( pGroup != NULL )
				pGroup->HandleUpdateFieldChange( index, player_shared_from_this() );
		}

#ifdef OPTIMIZED_PLAYER_SAVING
		switch(index)
		{
		case UNIT_FIELD_LEVEL:
		case PLAYER_XP:
			player_shared_from_this()->save_LevelXP();
			break;

		case PLAYER_FIELD_COINAGE:
			player_shared_from_this()->save_Gold();
			break;
		}
#endif
	}
}

/*
//must be in %
void Object::ModPUInt32Value(const uint32 index, const int32 value, bool apply )
{
	ASSERT( index < m_valuesCount );
	int32 basevalue = (int32)m_uint32Values[ index ];
	if(apply)
		m_uint32Values[ index ] += ((basevalue*value)/100);
	else
		m_uint32Values[ index ] = (basevalue*100)/(100+value);

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated )
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}
}
*/
uint32 Object::GetModPUInt32Value(const uint32 index, const int32 value)
{
	ASSERT( index < m_valuesCount );
	int32 basevalue = (int32)m_uint32Values[ index ];
	return ((basevalue*value)/100);
}

void Object::ModUnsigned32Value(uint32 index, int32 mod)
{
	ASSERT( index < m_valuesCount );
	if(mod == 0)
		return;

	m_uint32Values[ index ] += mod;
	if( (int32)m_uint32Values[index] < 0 )
		m_uint32Values[index] = 0;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}

	if(m_objectTypeId == TYPEID_PLAYER)
	{
#ifdef OPTIMIZED_PLAYER_SAVING
		switch(index)
		{
		case UNIT_FIELD_LEVEL:
		case PLAYER_XP:
			player_shared_from_this()->save_LevelXP();
			break;

		case PLAYER_FIELD_COINAGE:
			player_shared_from_this()->save_Gold();
			break;
		}
#endif
	}
}

void Object::ModSignedInt32Value(uint32 index, int32 value )
{
	ASSERT( index < m_valuesCount );
	if(value == 0)
		return;

	m_uint32Values[ index ] += value;
	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}

	if(m_objectTypeId == TYPEID_PLAYER)
	{
#ifdef OPTIMIZED_PLAYER_SAVING
		switch(index)
		{
		case UNIT_FIELD_LEVEL:
		case PLAYER_XP:
			player_shared_from_this()->save_LevelXP();
			break;

		case PLAYER_FIELD_COINAGE:
			player_shared_from_this()->save_Gold();
			break;
		}
#endif
	}
}

void Object::ModFloatValue(const uint32 index, const float value )
{
	ASSERT( index < m_valuesCount );
	m_floatValues[ index ] += value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}
}
//! Set uint64 property
void Object::SetUInt64Value( const uint32 index, const uint64 value )
{
	assert( index + 1 < m_valuesCount );
	if(m_uint32Values[index] == GUID_LOPART(value) && m_uint32Values[index+1] == GUID_HIPART(value))
		return;

	m_uint32Values[ index ] = *((uint32*)&value);
	m_uint32Values[ index + 1 ] = *(((uint32*)&value) + 1);

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );
		m_updateMask.SetBit( index + 1 );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}
}

//! Set float property
void Object::SetFloatValue( const uint32 index, const float value )
{
	ASSERT( index < m_valuesCount );
	if(m_floatValues[index] == value)
		return;

	m_floatValues[ index ] = value;
	
	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}
}


void Object::SetFlag( const uint32 index, uint32 newFlag )
{
	ASSERT( index < m_valuesCount );

	//no change -> no update
	if((m_uint32Values[ index ] & newFlag)==newFlag)
		return;

	m_uint32Values[ index ] |= newFlag;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}

	// we're modifying an aurastate, so we need to update the auras.
	if( index == UNIT_FIELD_AURASTATE )
	{
		UnitPointer u = unit_shared_from_this();
		for(uint32 i = 0; i < MAX_AURAS+MAX_POSITIVE_AURAS; ++i)
		{
			if( u->m_auras[i] && !u->m_auras[i]->m_applied) // try to apply
				u->m_auras[i]->ApplyModifiers(true);

			if( u->m_auras[i] && u->m_auras[i]->m_applied) // try to remove, if we lack the aurastate
				u->m_auras[i]->RemoveIfNecessary();
		}
	}
}


void Object::RemoveFlag( const uint32 index, uint32 oldFlag )
{
	ASSERT( index < m_valuesCount );

	//no change -> no update
	if((m_uint32Values[ index ] & oldFlag)==0)
		return;

	m_uint32Values[ index ] &= ~oldFlag;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}

	// we're modifying an aurastate, so we need to update the auras.
	if( index == UNIT_FIELD_AURASTATE )
	{
		UnitPointer u = unit_shared_from_this();
		for(uint32 i = 0; i < MAX_AURAS+MAX_POSITIVE_AURAS; ++i)
		{
			if( u->m_auras[i] && !u->m_auras[i]->m_applied) // try to apply
				u->m_auras[i]->ApplyModifiers(true);

			if( u->m_auras[i] && u->m_auras[i]->m_applied) // try to remove, if we lack the aurastate
				u->m_auras[i]->RemoveIfNecessary();
		}
	}
}

////////////////////////////////////////////////////////////

float Object::CalcDistance(ObjectPointer Ob)
{
	return CalcDistance(GetPositionX(), GetPositionY(), GetPositionZ(), Ob->GetPositionX(), Ob->GetPositionY(), Ob->GetPositionZ());
}
float Object::CalcDistance(float ObX, float ObY, float ObZ)
{
	return CalcDistance(GetPositionX(), GetPositionY(), GetPositionZ(), ObX, ObY, ObZ);
}
float Object::CalcDistance(ObjectPointer Oa, ObjectPointer Ob)
{
	return CalcDistance(Oa->GetPositionX(), Oa->GetPositionY(), Oa->GetPositionZ(), Ob->GetPositionX(), Ob->GetPositionY(), Ob->GetPositionZ());
}
float Object::CalcDistance(ObjectPointer Oa, float ObX, float ObY, float ObZ)
{
	return CalcDistance(Oa->GetPositionX(), Oa->GetPositionY(), Oa->GetPositionZ(), ObX, ObY, ObZ);
}

float Object::CalcDistance(float OaX, float OaY, float OaZ, float ObX, float ObY, float ObZ)
{
	float xdest = OaX - ObX;
	float ydest = OaY - ObY;
	float zdest = OaZ - ObZ;
	return sqrtf(zdest*zdest + ydest*ydest + xdest*xdest);
}

float Object::calcAngle( float Position1X, float Position1Y, float Position2X, float Position2Y )
{
	float dx = Position2X-Position1X;
	float dy = Position2Y-Position1Y;
	double angle=0.0f;

	// Calculate angle
	if (dx == 0.0)
	{
		if (dy == 0.0)
			angle = 0.0;
		else if (dy > 0.0)
			angle = M_PI * 0.5 /* / 2 */;
		else
			angle = M_PI * 3.0 * 0.5/* / 2 */;
	}
	else if (dy == 0.0)
	{
		if (dx > 0.0)
			angle = 0.0;
		else
			angle = M_PI;
	}
	else
	{
		if (dx < 0.0)
			angle = atanf(dy/dx) + M_PI;
		else if (dy < 0.0)
			angle = atanf(dy/dx) + (2*M_PI);
		else
			angle = atanf(dy/dx);
	}

	// Convert to degrees
	angle = angle * float(180 / M_PI);

	// Return
	return float(angle);
}

float Object::calcRadAngle( float Position1X, float Position1Y, float Position2X, float Position2Y )
{
	double dx = double(Position2X-Position1X);
	double dy = double(Position2Y-Position1Y);
	double angle=0.0;

	// Calculate angle
	if (dx == 0.0)
	{
		if (dy == 0.0)
			angle = 0.0;
		else if (dy > 0.0)
			angle = M_PI * 0.5/*/ 2.0*/;
		else
			angle = M_PI * 3.0 * 0.5/*/ 2.0*/;
	}
	else if (dy == 0.0)
	{
		if (dx > 0.0)
			angle = 0.0;
		else
			angle = M_PI;
	}
	else
	{
		if (dx < 0.0)
			angle = atan(dy/dx) + M_PI;
		else if (dy < 0.0)
			angle = atan(dy/dx) + (2*M_PI);
		else
			angle = atan(dy/dx);
	}

	// Return
	return float(angle);
}

float Object::getEasyAngle( float angle )
{
	while ( angle < 0 ) {
		angle = angle + 360;
	}
	while ( angle >= 360 ) {
		angle = angle - 360;
	}
	return angle;
}

bool Object::inArc(float Position1X, float Position1Y, float FOV, float Orientation, float Position2X, float Position2Y )
{
	float angle = calcAngle( Position1X, Position1Y, Position2X, Position2Y );
	float lborder = getEasyAngle( ( Orientation - (FOV*0.5f/*/2*/) ) );
	float rborder = getEasyAngle( ( Orientation + (FOV*0.5f/*/2*/) ) );
	//DEBUG_LOG("Orientation: %f Angle: %f LeftBorder: %f RightBorder %f",Orientation,angle,lborder,rborder);
	if(((angle >= lborder) && (angle <= rborder)) || ((lborder > rborder) && ((angle < rborder) || (angle > lborder))))
	{
		return true;
	}
	else
	{
		return false;
	}
} 

bool Object::isInFront(ObjectPointer target)
{
	// check if we facing something ( is the object within a 180 degree slice of our positive y axis )

    double x = target->GetPositionX() - m_position.x;
    double y = target->GetPositionY() - m_position.y;

    double angle = atan2( y, x );
    angle = ( angle >= 0.0 ) ? angle : 2.0 * M_PI + angle;
	angle -= m_position.o;

    while( angle > M_PI)
        angle -= 2.0 * M_PI;

    while(angle < -M_PI)
        angle += 2.0 * M_PI;

	// replace M_PI in the two lines below to reduce or increase angle

    double left = -1.0 * ( M_PI / 2.0 );
    double right = ( M_PI / 2.0 );

    return( ( angle >= left ) && ( angle <= right ) );
}

bool Object::isInBack(ObjectPointer target)
{
	if(CalcDistance(target) < 0.5f)
		return false; 

	// check if we are behind something ( is the object within a 180 degree slice of our negative y axis )

	double x = target->GetPositionX() - m_position.x;
	double y = target->GetPositionY() - m_position.y;

	double angle = atan2( y, x );
	angle = ( angle >= 0.0 ) ? angle : 2.0 * M_PI + angle;
	angle -= target->GetOrientation();

	while( angle > M_PI)
		angle -= 2.0 * M_PI;

	while(angle < -M_PI)
		angle += 2.0 * M_PI;

	// replace M_H_PI in the two lines below to reduce or increase angle

	double left = -1.0 * ( M_H_PI / 2.0 );
	double right = ( M_H_PI / 2.0 );

	return( ( angle >= left ) && ( angle <= right ) );
}

bool Object::isInArc(ObjectPointer target , float angle) // angle in degrees
{
	return inArc( GetPositionX() , GetPositionY() , angle , GetOrientation() , target->GetPositionX() , target->GetPositionY() );
}

bool Object::isInRange(ObjectPointer target, float range)
{
	float dist = CalcDistance( target );
	return( dist <= range );
}

bool Object::IsPet()
{
	if( GetTypeId() != TYPEID_UNIT )
		return false;

	if( unit_shared_from_this()->m_isPet && m_uint32Values[UNIT_FIELD_CREATEDBY] != 0 && m_uint32Values[UNIT_FIELD_SUMMONEDBY] != 0 )
		return true;

	return false;
}

void Object::_setFaction()
{
	FactionTemplateDBC* factT = NULL;

	if(GetTypeId() == TYPEID_UNIT || GetTypeId() == TYPEID_PLAYER)
	{
		factT = dbcFactionTemplate.LookupEntry(GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	}
	else
	if(GetTypeId() == TYPEID_GAMEOBJECT)
	{
		factT = dbcFactionTemplate.LookupEntry(GetUInt32Value(GAMEOBJECT_FACTION));
	}

	if(!factT)
	{
		return;
	}
	m_faction = factT;
	m_factionDBC = dbcFaction.LookupEntry(factT->Faction);
}

void Object::UpdateOppFactionSet()
{
	m_oppFactsInRange.clear();
	for(Object::InRangeSet::iterator i = GetInRangeSetBegin(); i != GetInRangeSetEnd(); ++i)
	{
		if (((*i)->GetTypeId() == TYPEID_UNIT) || ((*i)->GetTypeId() == TYPEID_PLAYER) || ((*i)->GetTypeId() == TYPEID_GAMEOBJECT))
		{
			if (isHostile(obj_shared_from_this(), (*i)))
			{
				if(!(*i)->IsInRangeOppFactSet(obj_shared_from_this()))
					(*i)->m_oppFactsInRange.insert(obj_shared_from_this());
				if (!IsInRangeOppFactSet((*i)))
					m_oppFactsInRange.insert((*i));
				
			}
			else
			{
				if((*i)->IsInRangeOppFactSet(obj_shared_from_this()))
					(*i)->m_oppFactsInRange.erase(obj_shared_from_this());
				if (IsInRangeOppFactSet((*i)))
					m_oppFactsInRange.erase((*i));
			}
		}
	}
}

void Object::EventSetUInt32Value(uint32 index, uint32 value)
{
	SetUInt32Value(index,value);
}

void Object::DealDamage(shared_ptr<Unit>pVictim, uint32 damage, uint32 targetEvent, uint32 unitEvent, uint32 spellId, bool no_remove_auras)
{
	PlayerPointer plr = NULLPLR;

	if( !pVictim || !pVictim->isAlive() || !pVictim->IsInWorld() || !IsInWorld() )
		return;
	if( pVictim->GetTypeId() == TYPEID_PLAYER && TO_PLAYER( pVictim )->GodModeCheat == true )
		return;
	if( pVictim->IsSpiritHealer() )
		return;
	
	if( pVictim->GetStandState() )//not standing-> standup
	{
		pVictim->SetStandState( STANDSTATE_STAND );//probably mobs also must standup
	}

	// This one is easy. If we're attacking a hostile target, and we're not flagged, flag us.
	// Also, you WONT get flagged if you are dueling that person - FiShBaIt
	if( pVictim->IsPlayer() && IsPlayer() )
	{
		if( isHostile( obj_shared_from_this(), pVictim ) && TO_PLAYER( pVictim )->DuelingWith != player_shared_from_this() )
			player_shared_from_this()->SetPvPFlag();
	}
	//If our pet attacks  - flag us.
	if( pVictim->IsPlayer() && IsPet() )
	{
		PlayerPointer owner = TO_PLAYER( pet_shared_from_this()->GetPetOwner() );
		if( owner != NULL )
			if( owner->isAlive() && TO_PLAYER( pVictim )->DuelingWith != owner )
				owner->SetPvPFlag();		
	}

	if(!no_remove_auras)
	{
		//zack 2007 04 24 : root should not remove self (and also other unknown spells)
		if(spellId)
		{
			pVictim->RemoveAurasByInterruptFlagButSkip(AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN,spellId);
			if(Rand(35.0f))
				pVictim->RemoveAurasByInterruptFlagButSkip(AURA_INTERRUPT_ON_UNUSED2,spellId);
		}
		else
		{
			pVictim->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN);
			if(Rand(35.0f))
				pVictim->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_UNUSED2);
		}
	}

	if(IsUnit())
	{
		if( unit_shared_from_this() != pVictim && pVictim->IsPlayer() && IsPlayer() && plr_shared_from_this()->m_hasInRangeGuards )
		{
			plr_shared_from_this()->SetGuardHostileFlag(true);
			plr_shared_from_this()->CreateResetGuardHostileFlagEvent();
		}

/*		if(!pVictim->isInCombat() && pVictim->IsPlayer())
			sHookInterface.OnEnterCombat( TO_PLAYER( pVictim ), unit_shared_from_this() );

		if(IsPlayer() && ! player_shared_from_this()->isInCombat())
			sHookInterface.OnEnterCombat( player_shared_from_this(), player_shared_from_this() );*/
			
		if(IsPet())
			plr = pet_shared_from_this()->GetPetOwner();
		else if(IsPlayer())
			plr = player_shared_from_this();

		if(plr != NULL && plr->GetTypeId() == TYPEID_PLAYER && pVictim->GetTypeId() == TYPEID_UNIT) // Units can't tag..
			TO_CREATURE(pVictim)->Tag(plr);

		// Pepsi1x1: is this correct obj_shared_from_this()
		if( pVictim != 
			unit_shared_from_this() )
		{
			// Set our attack target to the victim.
			unit_shared_from_this()->CombatStatus.OnDamageDealt( pVictim, damage );
		}
	}

        ///Rage
        float val;

		if( pVictim->GetPowerType() == POWER_TYPE_RAGE 
			&& pVictim != unit_shared_from_this()
			&& pVictim->IsPlayer())
		{
			float level = (float)pVictim->getLevel();
			float c = 0.0091107836f * level * level + 3.225598133f * level + 4.2652911f;
			uint32 rage = pVictim->GetUInt32Value( UNIT_FIELD_POWER2 );
			val = 2.5f * damage / c;
			rage += float2int32(val) * 10;
			if( rage > pVictim->GetUInt32Value(UNIT_FIELD_MAXPOWER2) )
				rage = pVictim->GetUInt32Value(UNIT_FIELD_MAXPOWER2);
			
			pVictim->SetUInt32Value(UNIT_FIELD_POWER2, rage);
			pVictim->SendPowerUpdate();
		}

	if( pVictim->IsPlayer() )
	{
		PlayerPointer pThis = TO_PLAYER(pVictim);
		if(pThis->cannibalize)
		{
			sEventMgr.RemoveEvents(pVictim, EVENT_CANNIBALIZE);
			pThis->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
			pThis->cannibalize = false;
		}
	}

	//* BATTLEGROUND DAMAGE COUNTER *//
	if( pVictim != unit_shared_from_this() )
	{
		if( IsPlayer() )
		{
			plr = player_shared_from_this();
		}
		else if( IsPet() )
		{
			plr = pet_shared_from_this()->GetPetOwner();
			if( plr != NULL && plr->GetMapMgr() == GetMapMgr() )
				plr = NULLPLR;
		}

		if( plr != NULL && plr->m_bg != NULL && plr->GetMapMgr() == GetMapMgr() )
		{
			plr->m_bgScore.DamageDone += damage;
			plr->m_bg->UpdatePvPData();
		}
	}
   
	uint32 health = pVictim->GetUInt32Value(UNIT_FIELD_HEALTH );

	if(health <= damage && pVictim->IsPlayer() && pVictim->getClass() == ROGUE && TO_PLAYER(pVictim)->m_lastCheatDeath + 60000 < (uint32)UNIXTIME)
	{
		PlayerPointer plrVictim = TO_PLAYER(pVictim);
		uint32 rank = plrVictim->m_cheatDeathRank;

		uint32 chance = rank == 3 ? 100 : rank * 33;
		if(Rand(chance))
		{
			// Proc that cheating death!
			SpellEntry *spellInfo = dbcSpell.LookupEntry(45182);
			SpellPointer spell = shared_ptr<Spell>(new Spell(pVictim,spellInfo,true,NULLAURA));
			SpellCastTargets targets;
			targets.m_unitTarget = pVictim->GetGUID();
			spell->prepare(&targets);
			TO_PLAYER(pVictim)->m_lastCheatDeath = (uint32)UNIXTIME;

			// Why return? So this damage isn't counted. ;)
			// On official, it seems Blizzard applies it's Cheating Death school absorb aura for 1 msec, but it's too late
			// for us by now.
			return;
		}
	}

	/*------------------------------------ DUEL HANDLERS --------------------------*/
	if((pVictim->IsPlayer()) && (IsPlayer()) && TO_PLAYER(pVictim)->DuelingWith == player_shared_from_this() ) //Both Players
	{
		if((health <= damage) && player_shared_from_this()->DuelingWith != NULL)
		{
			//Player in Duel and Player Victim has lost
			uint32 NewHP = pVictim->GetUInt32Value(UNIT_FIELD_MAXHEALTH)/100;

			if(NewHP < 5) 
				NewHP = 5;

			//Set there health to 1% or 5 if 1% is lower then 5
			pVictim->SetUInt32Value(UNIT_FIELD_HEALTH, NewHP);
			//End Duel
			player_shared_from_this()->EndDuel(DUEL_WINNER_KNOCKOUT);
			plr_shared_from_this()->GetAchievementInterface()->HandleAchievementCriteriaWinDuel();
			TO_PLAYER(pVictim)->GetAchievementInterface()->HandleAchievementCriteriaLoseDuel();

			// surrender emote
			pVictim->Emote(EMOTE_ONESHOT_BEG);			// Animation

			return;		  
		}
	}

	if((pVictim->IsPlayer()) && (IsPet())) 
	{
		if((health <= damage) && TO_PLAYER(pVictim)->DuelingWith == pet_shared_from_this()->GetPetOwner())
		{
			PlayerPointer petOwner = pet_shared_from_this()->GetPetOwner();
			if(petOwner)
			{
				//Player in Duel and Player Victim has lost
				uint32 NewHP = pVictim->GetUInt32Value(UNIT_FIELD_MAXHEALTH)/100;
				if(NewHP < 5) NewHP = 5;
				
				//Set there health to 1% or 5 if 1% is lower then 5
				pVictim->SetUInt32Value(UNIT_FIELD_HEALTH, NewHP);
				//End Duel
				petOwner->EndDuel(DUEL_WINNER_KNOCKOUT);
				return;
			}
		}
	}
	/*------------------------------------ DUEL HANDLERS END--------------------------*/

	bool isCritter = false;
	if(pVictim->GetTypeId() == TYPEID_UNIT && TO_CREATURE(pVictim)->GetCreatureName())
	{
			if(TO_CREATURE(pVictim)->GetCreatureName()->Type == CRITTER)
				isCritter = true;
	}

	/* -------------------------- HIT THAT CAUSES VICTIM TO DIE ---------------------------*/
	if ((isCritter || health <= damage) )
	{
		//warlock - seed of corruption
		if( IsUnit() )
		{
			if( IsPlayer() && pVictim->IsUnit() && !pVictim->IsPlayer() && m_mapMgr->m_battleground && m_mapMgr->m_battleground->GetType() == BATTLEGROUND_ALTERAC_VALLEY )
				TO_ALTERACVALLEY(m_mapMgr->m_battleground)->HookOnUnitKill( plr_shared_from_this(), pVictim );
			SpellEntry *killerspell;
			if( spellId )
				killerspell = dbcSpell.LookupEntry( spellId );
			else killerspell = NULL;
			pVictim->HandleProc( PROC_ON_DIE, unit_shared_from_this(), killerspell );
			pVictim->m_procCounter = 0;
			unit_shared_from_this()->HandleProc( PROC_ON_TARGET_DIE, pVictim, killerspell );
			unit_shared_from_this()->m_procCounter = 0;
		}
		// check if pets owner is combat participant
		bool owner_participe = false;
		if( IsPet() )
		{
			PlayerPointer owner = pet_shared_from_this()->GetPetOwner();
			if( owner != NULL && pVictim->GetAIInterface()->getThreatByPtr( owner ) > 0 )
				owner_participe = true;
		}
		/* victim died! */
		if( pVictim->IsPlayer() )
		{
			// let's see if we have shadow of death
			if( !pVictim->FindPositiveAuraByNameHash(SPELL_HASH_SHADOW_OF_DEATH) && TO_PLAYER( pVictim)->HasSpell( 49157 ) ) //check for shadow of death
			{
				SpellEntry* sorInfo = dbcSpell.LookupEntry(54223);
				if( sorInfo != NULL )
				{
					SpellPointer sor = shared_ptr<Spell>(new Spell( pVictim, sorInfo, true, NULLAURA ));
					SpellCastTargets targets;
					targets.m_unitTarget = pVictim->GetGUID();
					sor->prepare(&targets);
					return;
				}
			}

			TO_PLAYER( pVictim )->KillPlayer();
			/* Remove all Auras */
			pVictim->EventDeathAuraRemoval();
			/* Set victim health to 0 */
			pVictim->SetUInt32Value(UNIT_FIELD_HEALTH, 0);

			if( IsCreature() )
			{
				TO_PLAYER(pVictim)->GetAchievementInterface()->HandleAchievementCriteriaKilledByCreature( creature_shared_from_this()->GetUInt32Value(OBJECT_FIELD_ENTRY) );
			}
			else if(IsPlayer())
			{
				TO_PLAYER(pVictim)->GetAchievementInterface()->HandleAchievementCriteriaKilledByPlayer();
			}
		}
		else
		{
			pVictim->setDeathState( JUST_DIED );
			pVictim->GetAIInterface()->HandleEvent( EVENT_LEAVECOMBAT, unit_shared_from_this(), 0);
			/* Remove all Auras */
			pVictim->EventDeathAuraRemoval();
			/* Set victim health to 0 */
			pVictim->SetUInt32Value(UNIT_FIELD_HEALTH, 0);
		}

		if( pVictim->IsPlayer() && (!IsPlayer() || pVictim == unit_shared_from_this() ) )
		{
			TO_PLAYER( pVictim )->DeathDurabilityLoss(0.10);
		}

		/* Zone Under Attack */
        MapInfo * pMapInfo = WorldMapInfoStorage.LookupEntry(GetMapId());
        if( pMapInfo && pMapInfo->type == INSTANCE_NULL && !pVictim->IsPlayer() && !pVictim->IsPet() && ( IsPlayer() || IsPet() ) )
		{
			// Only NPCs that bear the PvP flag can be truly representing their faction.
			if( TO_CREATURE(pVictim)->IsPvPFlagged() )
			{
				PlayerPointer pAttacker = NULLPLR;
				if( IsPet() )
					pAttacker = pet_shared_from_this()->GetPetOwner();
				else if(IsPlayer())
					pAttacker = player_shared_from_this();

				if( pAttacker != NULL)
                {
				    uint8 teamId = (uint8)pAttacker->GetTeam();
				    if(teamId == 0) // Swap it.
					    teamId = 1;
				    else
					    teamId = 0;
				    uint32 AreaID = pVictim->GetMapMgr()->GetAreaID(pVictim->GetPositionX(), pVictim->GetPositionY());
				    if(!AreaID)
					    AreaID = pAttacker->GetZoneId(); // Failsafe for a shitty TerrainMgr

				    if(AreaID)
				    {
					    WorldPacket data(SMSG_ZONE_UNDER_ATTACK, 4);
					    data << AreaID;
					    sWorld.SendFactionMessage(&data, teamId);
				    }
                }
			}
		}
		
		if(pVictim->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT) > 0)
		{
			if(pVictim->GetCurrentSpell())
			{
				SpellPointer spl = pVictim->GetCurrentSpell();
				for(int i = 0; i < 3; i++)
				{
					if(spl->m_spellInfo->Effect[i] == SPELL_EFFECT_PERSISTENT_AREA_AURA)
					{
						shared_ptr<DynamicObject>dObj = GetMapMgr()->GetDynamicObject(pVictim->GetUInt32Value(UNIT_FIELD_CHANNEL_OBJECT));
						if(!dObj)
							return;
						WorldPacket data(SMSG_GAMEOBJECT_DESPAWN_ANIM, 8);
						data << dObj->GetGUID();
						dObj->SendMessageToSet(&data, false);
						dObj->RemoveFromWorld(true);
						dObj->Destructor();
						dObj = NULLDYN; // deleted!
					}
				}
				if(spl->m_spellInfo->ChannelInterruptFlags == 48140) spl->cancel();
			}
		}

		/* Stop victim from attacking */
		if( IsUnit() )
			pVictim->smsg_AttackStop( unit_shared_from_this() );

		if( pVictim->GetTypeId() == TYPEID_PLAYER )
			TO_PLAYER( pVictim )->EventAttackStop();

		if(pVictim->IsPlayer())
		{
			uint32 self_res_spell = TO_PLAYER( pVictim )->SoulStone;
			TO_PLAYER( pVictim )->SoulStone = TO_PLAYER( pVictim )->SoulStoneReceiver = 0;

			if( !self_res_spell && TO_PLAYER( pVictim )->bReincarnation )
			{
				SpellEntry* m_reincarnSpellInfo = dbcSpell.LookupEntry( 20608 );
				if( TO_PLAYER( pVictim )->Cooldown_CanCast( m_reincarnSpellInfo ) )
				{
					uint32 ankh_count = TO_PLAYER( pVictim )->GetItemInterface()->GetItemCount( 17030 );
					if( ankh_count )
						self_res_spell = 21169;
				}
			}
			pVictim->SetUInt32Value( PLAYER_SELF_RES_SPELL, self_res_spell );
			TO_UNIT(pVictim)->Dismount();
		}

		// Wipe our attacker set on death
		UnitPointer pKiller = pVictim->CombatStatus.GetKiller();
		pVictim->CombatStatus.Vanished();

		//		 sent to set. don't send it to the party, becuase if they're out of
		//		 range they won't know this guid exists -> possible 132.

		/*if (this->IsPlayer())
			if( player_shared_from_this()->InGroup() )
				player_shared_from_this()->GetGroup()->SendPartyKillLog( this, pVictim );*/

		/* Stop Unit from attacking */
		if( IsPlayer() )
			player_shared_from_this()->EventAttackStop();
	   
		if( IsUnit() )
		{
			CALL_SCRIPT_EVENT( obj_shared_from_this(), OnTargetDied )( pVictim );
			unit_shared_from_this()->smsg_AttackStop( pVictim );
		
			/* Tell Unit that it's target has Died */
			unit_shared_from_this()->addStateFlag( UF_TARGET_DIED );

			// We will no longer be attacking this target, as it's dead.
			//unit_shared_from_this()->setAttackTarget(NULL);
		}
		//so now we are completely dead
		//lets see if we have spirit of redemption
		if( pVictim->IsPlayer() )
		{
			if( TO_PLAYER( pVictim)->HasSpell( 20711 ) ) //check for spirit of Redemption
			{
				SpellEntry* sorInfo = dbcSpell.LookupEntry(27827);
				if( sorInfo != NULL )
				{
					SpellPointer sor = shared_ptr<Spell>(new Spell( pVictim, sorInfo, true, NULLAURA ));
					SpellCastTargets targets;
					targets.m_unitTarget = pVictim->GetGUID();
					sor->prepare(&targets);
				}
			}
		}
		/* -------------------------------- HONOR + BATTLEGROUND CHECKS ------------------------ */
		plr = NULLPLR;
		if( pKiller && pKiller->IsPlayer() )
			plr = TO_PLAYER( pKiller );
		else if(pKiller && pKiller->IsPet())
			plr = TO_PET( pKiller )->GetPetOwner();
		
		if( plr != NULL)
		{
			if( plr->m_bg != NULL )
				plr->m_bg->HookOnPlayerKill( plr, pVictim );

			if( pVictim->IsPlayer() )
			{
				sHookInterface.OnKillPlayer( plr, TO_PLAYER( pVictim ) );
				if(plr->getLevel() > pVictim->getLevel())
				{
					unsigned int diff = plr->getLevel() - pVictim->getLevel();
					if( diff <= 8 )
					{
						HonorHandler::OnPlayerKilledUnit(plr, pVictim);
						plr->SetFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_LASTKILLWITHHONOR );
					}
					else
						plr->RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_LASTKILLWITHHONOR );
				}
				else
				{
					HonorHandler::OnPlayerKilledUnit( plr, pVictim );
					plr->SetFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_LASTKILLWITHHONOR );
				}
			}
			else
			{
				// REPUTATION
				if( !isCritter )
					plr->Reputation_OnKilledUnit( pVictim, false );

				plr->RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_LASTKILLWITHHONOR );
			}
		}
		/* -------------------------------- HONOR + BATTLEGROUND CHECKS END------------------------ */

		uint64 victimGuid = pVictim->GetGUID();

		// only execute loot code if we were tagged
		if( pVictim->GetTypeId() == TYPEID_UNIT && TO_CREATURE(pVictim)->m_taggingPlayer != 0 )
		{
			// fill loot vector
			TO_CREATURE(pVictim)->GenerateLoot();

			// update visual.
			TO_CREATURE(pVictim)->UpdateLootAnimation();
		}

		// player loot for battlegrounds
		if( pVictim->GetTypeId() == TYPEID_PLAYER )
		{
			// set skinning flag, this is the "remove insignia"
			if( TO_PLAYER(pVictim)->m_bg != NULL && TO_PLAYER(pVictim)->m_bg->SupportsPlayerLoot() )
			{
				pVictim->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
				TO_PLAYER(pVictim)->m_insigniaTaken = false;
			}
		}

		if(pVictim->GetTypeId() == TYPEID_UNIT)
		{
			pVictim->GetAIInterface()->OnDeath( obj_shared_from_this() );
			if(GetTypeId() == TYPEID_PLAYER)
			{
				WorldPacket data(SMSG_PARTYKILLLOG, 16);
				data << GetGUID() << pVictim->GetGUID();
				SendMessageToSet(&data, true);
			}			

			// it Seems that pets some how dont get a name and cause a crash here
			//bool isCritter = (pVictim->GetCreatureName() != NULL)? pVictim->GetCreatureName()->Type : 0;

			//---------------------------------looot-----------------------------------------  
			
			if( GetTypeId() == TYPEID_PLAYER && 
				pVictim->GetUInt64Value( UNIT_FIELD_CREATEDBY ) == 0 && 
				pVictim->GetUInt64Value( OBJECT_FIELD_CREATED_BY ) == 0 &&
				!pVictim->IsPet() )
			{
				// TODO: lots of casts are bad make a temp member pointer to use for batches like this
				// that way no local loadhitstore and its just one assignment 

				// Is this player part of a group
				if( player_shared_from_this()->InGroup() )
				{
					//Calc Group XP
					player_shared_from_this()->GiveGroupXP( pVictim, player_shared_from_this() );
					//TODO: pet xp if player in group
				}
				else
				{
					uint32 xp = CalculateXpToGive( pVictim, unit_shared_from_this() );
					if( xp > 0 )
					{
						player_shared_from_this()->GiveXP( xp, victimGuid, true );
						if( player_shared_from_this()->GetSummon() && player_shared_from_this()->GetSummon()->GetUInt32Value( UNIT_CREATED_BY_SPELL ) == 0 )
						{
							xp = CalculateXpToGive( pVictim, player_shared_from_this()->GetSummon() );
							if( xp > 0 )
								player_shared_from_this()->GetSummon()->GiveXP( xp );
						}
					}
				}

				// Achievement: on kill unit
				if( !pVictim->IsPlayer() && IsPlayer() )
				{
					PlayerPointer pThis = plr_shared_from_this();
					pThis->GetAchievementInterface()->HandleAchievementCriteriaKillCreature( pVictim->GetUInt32Value(OBJECT_FIELD_ENTRY) );
				}

				if( pVictim->GetTypeId() != TYPEID_PLAYER )
					sQuestMgr.OnPlayerKill( player_shared_from_this(), TO_CREATURE( pVictim ) );
			}
			else /* is Creature or shared_ptr<GameObject>*/
			{
				/* ----------------------------- PET XP HANDLING -------------- */
				if( owner_participe && IsPet() && !pVictim->IsPet() )
				{
					PlayerPointer petOwner = pet_shared_from_this()->GetPetOwner();
					if( petOwner != NULL && petOwner->GetTypeId() == TYPEID_PLAYER )
					{
						if( petOwner->InGroup() )
						{
							//Calc Group XP
							unit_shared_from_this()->GiveGroupXP( pVictim, petOwner );
							//TODO: pet xp if player in group
						}
						else
						{
							uint32 xp = CalculateXpToGive( pVictim, petOwner );
							if( xp > 0 )
							{
								petOwner->GiveXP( xp, victimGuid, true );
								if( !pet_shared_from_this()->IsSummon() )
								{
									xp = CalculateXpToGive( pVictim, pet_shared_from_this() );
									if( xp > 0 )
										pet_shared_from_this()->GiveXP( xp );
								}
							}
						}
					}
					if( petOwner != NULL && pVictim->GetTypeId() != TYPEID_PLAYER && 
						pVictim->GetTypeId() == TYPEID_UNIT )
						sQuestMgr.OnPlayerKill( petOwner, TO_CREATURE( pVictim ) );
				}
				/* ----------------------------- PET XP HANDLING END-------------- */

				/* ----------------------------- PET DEATH HANDLING -------------- */
				if( pVictim->IsPet() )
				{
					// dying pet looses 1 happiness level
					if( !TO_PET( pVictim )->IsSummon() )
					{
						uint32 hap = TO_PET( pVictim )->GetUInt32Value( UNIT_FIELD_POWER5 );
						hap = hap - PET_HAPPINESS_UPDATE_VALUE > 0 ? hap - PET_HAPPINESS_UPDATE_VALUE : 0;
						TO_PET( pVictim )->SetUInt32Value( UNIT_FIELD_POWER5, hap );
					}
					
					TO_PET( pVictim )->DelayedRemove( false, true );
					
					//remove owner warlock soul link from caster
					PlayerPointer owner = TO_PET( pVictim )->GetPetOwner();
					if( owner != NULL )
						owner->EventDismissPet();
				}
				/* ----------------------------- PET DEATH HANDLING END -------------- */
				else if( pVictim->GetUInt64Value( UNIT_FIELD_CHARMEDBY ) )
				{
					//remove owner warlock soul link from caster
					shared_ptr<Unit>owner=pVictim->GetMapMgr()->GetUnit( pVictim->GetUInt64Value( UNIT_FIELD_CHARMEDBY ) );
					if( owner != NULL && owner->IsPlayer())
						TO_PLAYER( owner )->EventDismissPet();
				}
			}
		}
		else if( pVictim->GetTypeId() == TYPEID_PLAYER )
		{
			
			/* -------------------- RESET BREATH STATE ON DEATH -------------- */
			TO_PLAYER( pVictim )->m_UnderwaterTime = 0;
			TO_PLAYER( pVictim )->m_UnderwaterState = 0;
			TO_PLAYER( pVictim )->m_BreathDamageTimer = 0;
			TO_PLAYER( pVictim )->m_SwimmingTime = 0;

			/* -------------------- KILL PET WHEN PLAYER DIES ---------------*/
			if( TO_PLAYER( pVictim )->GetSummon() != NULL )
			{
				if( pVictim->GetUInt32Value( UNIT_CREATED_BY_SPELL ) > 0 )
					TO_PLAYER( pVictim )->GetSummon()->Dismiss( true );
				else
					TO_PLAYER( pVictim )->GetSummon()->Remove( true, true, true );
			}
			/* -------------------- KILL PET WHEN PLAYER DIES END---------------*/
		}
		else DEBUG_LOG("DealDamage for Unknown Object.");
	}
	else /* ---------- NOT DEAD YET --------- */
	{
		if(pVictim != unit_shared_from_this() /* && updateskill */)
		{
			// Send AI Reaction UNIT vs UNIT
			if( GetTypeId() ==TYPEID_UNIT )
			{
				unit_shared_from_this()->GetAIInterface()->AttackReaction( pVictim, damage, spellId );
			}
			
			// Send AI Victim Reaction
			if( IsPlayer() || GetTypeId() == TYPEID_UNIT )
			{
				if( pVictim->GetTypeId() != TYPEID_PLAYER )
				{
					TO_CREATURE( pVictim )->GetAIInterface()->AttackReaction( unit_shared_from_this(), damage, spellId );
				}
			}
		}
		
		// TODO: Mark victim as a HK
		/*if( TO_PLAYER( pVictim )->GetCurrentBattleground() != NULL && player_shared_from_this()->GetCurrentBattleground() != NULL)
		{
			
		}*/	

		pVictim->SetUInt32Value( UNIT_FIELD_HEALTH, health - damage );
	}
}

void Object::SpellNonMeleeDamageLog(shared_ptr<Unit>pVictim, uint32 spellID, uint32 damage, bool allowProc, bool static_damage, bool no_remove_auras)
{
//==========================================================================================
//==============================Unacceptable Cases Processing===============================
//==========================================================================================
	if(!pVictim || !pVictim->isAlive())
		return;

	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellID );
	if(!spellInfo)
        return;

	if (IsPlayer() && !player_shared_from_this()->canCast(spellInfo))
		return;
//==========================================================================================
//==============================Variables Initialization====================================
//========================================================================================== 
	uint32 school = spellInfo->School;
	float res = float(damage);
	uint32 aproc = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_SPELL_LAND;
	uint32 vproc = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_ANY_DAMAGE_VICTIM | PROC_ON_SPELL_HIT_VICTIM;
	bool critical = false;
	float dmg_reduction_pct;

	float res_after_spelldmg;

	UnitPointer caster = NULLUNIT;
	if( IsUnit() )
		caster = unit_shared_from_this();

//==========================================================================================
//==============================+Spell Damage Bonus Calculations============================
//==========================================================================================
//------------------------------by stats----------------------------------------------------
	if( IsUnit() && !static_damage )
	{
		caster->RemoveAurasByInterruptFlag( AURA_INTERRUPT_ON_START_ATTACK );

		res += caster->GetSpellBonusDamage( pVictim, spellInfo, ( int )res, false );
		res_after_spelldmg = res;
//==========================================================================================
//==============================Post +SpellDamage Bonus Modifications=======================
//==========================================================================================
		if( res < 0 )
			res = 0;
		else if( spellInfo->spell_can_crit == true )
		{
//------------------------------critical strike chance--------------------------------------	
			// lol ranged spells were using spell crit chance
			float CritChance;
			if( spellInfo->is_ranged_spell )
			{

				if( IsPlayer() )
				{
					CritChance = GetFloatValue( PLAYER_RANGED_CRIT_PERCENTAGE );
					if( pVictim->IsPlayer() )
						CritChance += TO_PLAYER(pVictim)->res_R_crit_get();

					CritChance += (float)(pVictim->AttackerCritChanceMod[spellInfo->School]);
				}
				else
				{
					CritChance = 5.0f; // static value for mobs.. not blizzlike, but an unfinished formula is not fatal :)
				}
				if( pVictim->IsPlayer() )
				CritChance -= TO_PLAYER(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_RANGED_CRIT_RESILIENCE );
			}
			else if( spellInfo->is_melee_spell )
			{
				// Same shit with the melee spells, such as Judgement/Seal of Command
				if( IsPlayer() )
				{
					CritChance = GetFloatValue(PLAYER_CRIT_PERCENTAGE);
				}
				if( pVictim->IsPlayer() )
				{
					CritChance += TO_PLAYER(pVictim)->res_R_crit_get(); //this could be ability but in that case we overwrite the value
				}
				// Resilience
				CritChance -= pVictim->IsPlayer() ? TO_PLAYER(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) : 0.0f;
				// Victim's (!) crit chance mod for physical attacks?
				CritChance += (float)(pVictim->AttackerCritChanceMod[0]);

			}
			else
			{
				CritChance = caster->spellcritperc + caster->SpellCritChanceSchool[school] + pVictim->AttackerCritChanceMod[school];
				if( caster->IsPlayer() && ( pVictim->m_rooted - pVictim->m_stunned ) )	
					CritChance += TO_PLAYER( caster )->m_RootedCritChanceBonus;

				if( spellInfo->SpellGroupType )
				{
					SM_FFValue(caster->SM[SMT_CRITICAL][0], &CritChance, spellInfo->SpellGroupType);
					SM_PFValue(caster->SM[SMT_CRITICAL][1], &CritChance, spellInfo->SpellGroupType);
	#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
					float spell_flat_modifers=0;
					SM_FFValue(caster->SM[SMT_CRITICAL][1],&spell_flat_modifers,spellInfo->SpellGroupType);
					if(spell_flat_modifers!=0)
						printf("!!!!spell critchance mod flat %f ,spell group %u\n",spell_flat_modifers,spellInfo->SpellGroupType);
	#endif
				}
				if( pVictim->IsPlayer() )
				CritChance -= TO_PLAYER(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE );
			}
			if( CritChance < 0 ) CritChance = 0;
			if( CritChance > 95 ) CritChance = 95;
			critical = Rand(CritChance);
			//sLog.outString( "SpellNonMeleeDamageLog: Crit Chance %f%%, WasCrit = %s" , CritChance , critical ? "Yes" : "No" );
			AuraPointer fs = NULLAURA;
			if(spellInfo->NameHash == SPELL_HASH_LAVA_BURST && (fs = pVictim->FindNegativeAuraByNameHash(SPELL_HASH_FLAME_SHOCK)) != NULLAURA)
			{
				critical = true;
				if(caster && !caster->HasAura(55447))	// Glyph of Flame Shock
					fs->Remove();
			}
//==========================================================================================
//==============================Spell Critical Hit==========================================
//==========================================================================================
			if (critical)
			{		
				int32 critical_bonus = 100;
				if( spellInfo->SpellGroupType )
					SM_FIValue( caster->SM[SMT_CRITICAL_DAMAGE][1], &critical_bonus, spellInfo->SpellGroupType );

				if( critical_bonus > 0 )
				{
					// the bonuses are halved by 50% (funky blizzard math :S)
					float b;
					if( spellInfo->School == 0 || spellInfo->is_melee_spell || spellInfo->is_ranged_spell )		// physical || hackfix SoCommand/JoCommand
						b = ( ( float(critical_bonus) ) / 100.0f ) + 1.0f;
					else
						b = ( ( float(critical_bonus) / 2.0f ) / 100.0f ) + 1.0f;

					res	*= b;

					if( pVictim->IsPlayer() )
					{
						dmg_reduction_pct = 2.2f * TO_PLAYER(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE );
						if( dmg_reduction_pct > 0.33f )
							dmg_reduction_pct = 0.33f; // 3.0.3

						res = res - res * dmg_reduction_pct;
					}
					
				}

				pVictim->Emote( EMOTE_ONESHOT_WOUNDCRITICAL );
				aproc |= PROC_ON_SPELL_CRIT_HIT;
				vproc |= PROC_ON_SPELL_CRIT_HIT_VICTIM;
			}
		}
	}
//==========================================================================================
//==============================Post Roll Calculations======================================
//==========================================================================================
	// Special cases

	if( spellInfo->NameHash == SPELL_HASH_ICE_LANCE &&
	    (( pVictim->HasFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_FROZEN)) ||
		(caster && caster->m_frozenTargetCharges > 0))) 
	{
		res *= 3; //Ice Lance deals 3x damage if target is frozen
	}

	if (caster)
	{
		if (caster->m_frozenTargetCharges > 0 && spellInfo->School == SCHOOL_FROST)
		{
			caster->m_frozenTargetCharges--;
			if (caster->m_frozenTargetCharges <= 0)
				caster->RemoveAura(caster->m_frozenTargetId);
		}

		// [Mage] Torment the Weak
		if ((spellInfo->SpellGroupType[0] & 0x100821 || spellInfo->SpellGroupType[1] & 0x8000) &&
		    caster->m_dmgToSnaredTargets > 0 && pVictim->m_speedModifier < 0)
		{
			res*= caster->m_dmgToSnaredTargets;
		}

		// [Mage] Hot Streak
		if (!(aproc & PROC_ON_SPELL_CRIT_HIT))
			caster->m_hotStreakCount = 0;
	}

//------------------------------absorption--------------------------------------------------	
	uint32 ress=(uint32)res;
	uint32 abs_dmg = pVictim->AbsorbDamage(school, &ress, dbcSpell.LookupEntryForced(spellID));
	uint32 ms_abs_dmg= pVictim->ManaShieldAbsorb(ress, dbcSpell.LookupEntryForced(spellID));
	if (ms_abs_dmg)
	{
		if(ms_abs_dmg > ress)
			ress = 0;
		else
			ress-=ms_abs_dmg;

		abs_dmg += ms_abs_dmg;
	}

	if(ress < 0) ress = 0;

	res=(float)ress;
	dealdamage dmg;
	dmg.school_type = school;
	dmg.full_damage = ress;
	dmg.resisted_damage = 0;
	
	if(res <= 0) 
		dmg.resisted_damage = dmg.full_damage;

	//------------------------------resistance reducing-----------------------------------------	
	float res_before_resist = res;
	if(res > 0 && IsUnit())
	{
		unit_shared_from_this()->CalculateResistanceReduction(pVictim,&dmg,spellInfo,0.0f);
		if((int32)dmg.resisted_damage > dmg.full_damage)
			res = 0;
		else
			res = float(dmg.full_damage - dmg.resisted_damage);
	}
	//------------------------------special states----------------------------------------------
	if(pVictim->GetTypeId() == TYPEID_PLAYER && TO_PLAYER(pVictim)->GodModeCheat == true)
	{
		res = 0;
		dmg.resisted_damage = dmg.full_damage;
	}

	// Paladin: Blessing of Sacrifice, and Warlock: Soul Link
	if( pVictim->m_damageSplitTarget.active)
	{
		res = (float)pVictim->DoDamageSplitTarget((uint32)res, school, false);
	}
	
//==========================================================================================
//==============================Data Sending ProcHandling===================================
//==========================================================================================
	SendSpellNonMeleeDamageLog(obj_shared_from_this(), pVictim, spellID, float2int32(res), school, abs_dmg, dmg.resisted_damage, false, 0, critical, IsPlayer());

	int32 ires = float2int32(res);
	if( ires > 0 )
	{
		// only deal damage if its >0
		DealDamage( pVictim, float2int32( res ), 2, 0, spellID );
	}
	else
	{
		// we still have to tell the combat status handler we did damage so we're put in combat
		if( IsUnit() )
			unit_shared_from_this()->CombatStatus.OnDamageDealt(pVictim, 1);
	}
	
	if( IsUnit() && allowProc && spellInfo->Id != 25501 )
	{
		pVictim->HandleProc( vproc, unit_shared_from_this(), spellInfo, float2int32( res ) );
		pVictim->m_procCounter = 0;
		unit_shared_from_this()->HandleProc( aproc, pVictim, spellInfo, float2int32( res ) );
		unit_shared_from_this()->m_procCounter = 0;
	}
	if( IsPlayer() )
	{
			player_shared_from_this()->m_casted_amount[school] = ( uint32 )res;
	}

	

	if( (dmg.full_damage == 0 && abs_dmg) == 0 )
    {
        //Only pushback the victim current spell if it's not fully absorbed
        if( pVictim->GetCurrentSpell() )
            pVictim->GetCurrentSpell()->AddTime( school );
    }

//==========================================================================================
//==============================Post Damage Processing======================================
//==========================================================================================
	if( (int32)dmg.resisted_damage == dmg.full_damage && !abs_dmg )
	{
		//Magic Absorption
		if( pVictim->IsPlayer() )
		{
			if( TO_PLAYER( pVictim )->m_RegenManaOnSpellResist )
			{
				PlayerPointer pl = TO_PLAYER( pVictim );
				uint32 maxmana = pl->GetUInt32Value( UNIT_FIELD_MAXPOWER1 );

				//TODO: wtf is this ugly mess of casting bullshit
				uint32 amount = uint32(float( float(maxmana)*pl->m_RegenManaOnSpellResist));

				pVictim->Energize( pVictim, 29442, amount, POWER_TYPE_MANA );
			}
		}
	}
	if( school == SHADOW_DAMAGE )
	{
		if( IsPlayer() && unit_shared_from_this()->isAlive() && plr_shared_from_this()->getClass() == PRIEST )
			plr_shared_from_this()->VampiricSpell(float2int32(res), pVictim);

		if( pVictim->isAlive() && IsUnit() )
		{
			//Shadow Word:Death
			if( spellID == 32379 || spellID == 32996 ) 
			{
				uint32 damage = (uint32)( res + abs_dmg );
				uint32 absorbed = unit_shared_from_this()->AbsorbDamage( school, &damage, dbcSpell.LookupEntryForced(spellID) );
				DealDamage( unit_shared_from_this(), damage, 2, 0, spellID );
				SendSpellNonMeleeDamageLog( obj_shared_from_this(), unit_shared_from_this(), spellID, damage, school, absorbed, 0, false, 0, false, IsPlayer() );
			}
		}
	}

	// Rage
	/*if( dmg.full_damage && this->IsUnit() && pVictim->IsPlayer() && pVictim->GetPowerType() == POWER_TYPE_RAGE && pVictim->CombatStatus.IsInCombat() )
	{
		float val;
		float level = (float)unit_shared_from_this()->getLevel();

		// Conversion Value
		float c = 0.0091107836f * level * level + 3.225598133f * level + 4.2652911f;

		val = 2.5f * dmg.full_damage / c;
		val *= 10;

		//DEBUG_LOG( "Rd(%i) d(%i) c(%f) rage = %f", realdamage, dmg.full_damage, c, val );

		pVictim->ModUnsigned32Value( UNIT_FIELD_POWER2, (int32)val );
		if( pVictim->GetUInt32Value( UNIT_FIELD_POWER2) > 1000 )
			pVictim->ModUnsigned32Value( UNIT_FIELD_POWER2, 1000 - pVictim->GetUInt32Value( UNIT_FIELD_POWER2 ) );

	}*/
}

//*****************************************************************************************
//* SpellLog packets just to keep the code cleaner and better to read
//*****************************************************************************************

void Object::SendSpellLog(ObjectPointer Caster, ObjectPointer Target, uint32 Ability, uint8 SpellLogType)
{
	if ((!Caster || !Target) && Ability)
		return;

	WorldPacket data(SMSG_SPELLLOGMISS,28);
	data << Ability;										// spellid
	data << Caster->GetGUID();							  // caster / player
	data << (uint8)1;									   // unknown but I think they are const
	data << (uint32)1;									  // unknown but I think they are const
	data << Target->GetGUID();							  // target
	data << SpellLogType;								   // spelllogtype
	Caster->SendMessageToSet(&data, true);
}


void Object::SendSpellNonMeleeDamageLog( ObjectPointer Caster, UnitPointer Target, uint32 SpellID, uint32 Damage, uint8 School, uint32 AbsorbedDamage, uint32 ResistedDamage, bool PhysicalDamage, uint32 BlockedDamage, bool CriticalHit, bool bToset )
{
	if ((!Caster || !Target) && SpellID)
		return;
	uint32 overkill = Target->computeOverkill(Damage);

	WorldPacket data(SMSG_SPELLNONMELEEDAMAGELOG,40);
	data << Target->GetNewGUID();
	data << Caster->GetNewGUID();
	data << SpellID;                    // SpellID / AbilityID
	data << Damage;                     // All Damage
	data << uint32(overkill);			// Overkill
	data << uint8(g_spellSchoolConversionTable[School]);                     // School
	data << AbsorbedDamage;             // Absorbed Damage
	data << ResistedDamage;             // Resisted Damage
	data << uint8(PhysicalDamage);      // Physical Damage (true/false)
	data << uint8(0);                   // unknown or it binds with Physical Damage
	data << BlockedDamage;		     // Physical Damage (true/false)
	data << uint8(CriticalHit ? 7 : 5);                   // unknown const
	data << uint32(0);

	Caster->SendMessageToSet( &data, bToset );
}

int32 Object::event_GetInstanceID()
{
	// return -1 for non-inworld.. so we get our shit moved to the right thread
	if(!IsInWorld())
		return -1;
	else
		return m_instanceId;
}

void Object::EventSpellHit(SpellPointer pSpell)
{
	if( !IsInWorld() )
	{
		pSpell = NULLSPELL;
		return;
	}

	pSpell->cast(false);
}


bool Object::CanActivate()
{
	switch(m_objectTypeId)
	{
	case TYPEID_UNIT:
		{
			if(!IsPet())
				return true;
		}break;

	case TYPEID_GAMEOBJECT:
		{
			if(gob_shared_from_this()->HasAI() && GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPE_ID) != GAMEOBJECT_TYPE_TRAP)
				return true;
		}break;
	}

	return false;
}

void Object::Activate(shared_ptr<MapMgr> mgr)
{
	switch(m_objectTypeId)
	{
	case TYPEID_UNIT:
		if(IsVehicle())
			mgr->activeVehicles.insert(vehicle_shared_from_this());
		else
			mgr->activeCreatures.insert(creature_shared_from_this());
		break;

	case TYPEID_GAMEOBJECT:
		mgr->activeGameObjects.insert(gob_shared_from_this());
		break;
	}

	Active = true;
}

void Object::Deactivate(shared_ptr<MapMgr> mgr)
{
	switch(m_objectTypeId)
	{
	case TYPEID_UNIT:
		if(IsVehicle())
		{
			// check iterator
			if( mgr->__vehicle_iterator != mgr->activeVehicles.end() && (*mgr->__vehicle_iterator) == vehicle_shared_from_this() )
				++mgr->__vehicle_iterator;

			mgr->activeVehicles.erase(vehicle_shared_from_this());
		}
		else
		{
			// check iterator
			if( mgr->__creature_iterator != mgr->activeCreatures.end() && (*mgr->__creature_iterator) == creature_shared_from_this() )
				++mgr->__creature_iterator;

			mgr->activeCreatures.erase(creature_shared_from_this());
		}
		break;

	case TYPEID_GAMEOBJECT:
		// check iterator
		if( mgr->__gameobject_iterator != mgr->activeGameObjects.end() && (*mgr->__gameobject_iterator) == gob_shared_from_this() )
			++mgr->__gameobject_iterator;

		mgr->activeGameObjects.erase(gob_shared_from_this());
		break;
	}
	Active = false;
}

void Object::SetByte(uint32 index, uint32 index1,uint8 value)
{
	ASSERT( index < m_valuesCount );
	// save updating when val isn't changing.
	uint8 * v =&((uint8*)m_uint32Values)[index*4+index1];
	
	if(*v == value)
		return;

	*v = value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}

}

void Object::SetZoneId(uint32 newZone)
{
	m_zoneId = newZone;
	if( m_objectTypeId == TYPEID_PLAYER && player_shared_from_this()->GetGroup() )
		player_shared_from_this()->GetGroup()->HandlePartialChange( PARTY_UPDATE_FLAG_ZONEID, player_shared_from_this() );
}

void Object::PlaySoundToSet(uint32 sound_entry)
{
	WorldPacket data(SMSG_PLAY_SOUND, 4);
	data << sound_entry;
	SendMessageToSet(&data, true);
}

void Object::_SetExtension(const string& name, void* ptr)
{
	if( m_extensions == NULL )
		m_extensions = new ExtensionSet;

	m_extensions->insert( make_pair( name, ptr ) );
}


void Object::SendAttackerStateUpdate( UnitPointer Target, dealdamage *dmg, uint32 realdamage, uint32 abs, uint32 blocked_damage, uint32 hit_status, uint32 vstate )
{
	if (!Target || !dmg)
		return;

	WorldPacket data(SMSG_ATTACKERSTATEUPDATE, 70);

	if (hit_status & HITSTATUS_BLOCK)
	{
		hit_status|= 0x800000;
	}

	uint32 overkill = Target->computeOverkill(realdamage);

	data << (uint32)hit_status;   
	data << GetNewGUID();
	data << Target->GetNewGUID();

	data << (uint32)realdamage;			// Realdamage;
	data << (uint32)overkill;			// Overkill
	data << (uint8)1;					// Damage type counter / swing type

	data << (uint32)g_spellSchoolConversionTable[dmg->school_type];				  // Damage school
	data << (float)dmg->full_damage;		// Damage float
	data << (uint32)dmg->full_damage;	// Damage amount

	if(hit_status & HITSTATUS_ABSORBED)
	{
		data << (uint32)abs;				// Damage absorbed
	}
	if(hit_status & HITSTATUS_RESIST)
	{
		data << (uint32)dmg->resisted_damage;	// Damage resisted
	}

	data << (uint8)vstate;				// new victim state
	if(hit_status & HITSTATUS_BLOCK)
		data << (uint32)0;				// can be 0,1000 or -1
	else
		data << (uint32)0x3e8;			// can be 0,1000 or -1

	if (hit_status & 0x00800000)
	{
		data << (uint32)0;				// unknown
	}
	if(hit_status & HITSTATUS_BLOCK)
	{
		data << (uint32)blocked_damage;	 // Damage amount blocked
	}
	data << (uint32)0;					// Unknown

	SendMessageToSet(&data, IsPlayer());
}

void Object::SetByteFlag(const uint32 index, const uint32 flag, uint8 newFlag)
{
	if( HasByteFlag(index,flag,newFlag))
		return;

	SetByte(index, flag, GetByte(index,flag)|newFlag);

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}
}

void Object::RemoveByteFlag(const uint32 index, const uint32 flag, uint8 checkFlag)
{
	if( !HasByteFlag(index,flag,checkFlag))
		return;

	SetByte(index,flag, GetByte(index,flag) & ~checkFlag );

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(obj_shared_from_this());
			m_objectUpdated = true;
		}
	}
}

bool Object::HasByteFlag(const uint32 index, const uint32 flag, uint8 checkFlag)
{
	if( GetByte(index,flag) & checkFlag )
		return true;
	else
		return false;
}

bool Object::IsInLineOfSight(ObjectPointer pObj)
{
	if (GetMapMgr() && GetMapMgr()->IsCollisionEnabled())
		return (CollideInterface.CheckLOS( GetMapId(), GetPositionX(), GetPositionY(), GetPositionZ() + 2.0f, pObj->GetPositionX(), pObj->GetPositionY(), pObj->GetPositionZ() + 2.0f) );
	else
		return true;
}

bool Object::PhasedCanInteract(ObjectPointer pObj)
{
	bool ret = false;

	if( m_phaseMode == ALL_PHASES || pObj->m_phaseMode == ALL_PHASES ) // -1: All phases. But perhaps this should be limited to GameObjects?
		ret = true;

	if( pObj->m_phaseMode & m_phaseMode || pObj->m_phaseMode == m_phaseMode )
		ret = true;

	PlayerPointer pObjI = IsPlayer() ? plr_shared_from_this() : NULLPLR;
	PlayerPointer pObjII = pObj->IsPlayer() ? TO_PLAYER(pObj) : NULLPLR;
	if( IsPet() ) 
		pObjI = pet_shared_from_this()->GetPetOwner();
	if( pObj->IsPet() )
		pObjII = TO_PET(pObj)->GetPetOwner();

	// Hack for Acherus: Horde/Alliance can't see each other!
	if( pObjI && pObjII && GetMapId() == 609 && ( TO_PLAYER(pObj)->GetTeam() != plr_shared_from_this()->GetTeam() ) )
	{
		return false;
	}

	return ret;
}

// Returns the base cost of a spell
int32 Object::GetSpellBaseCost(SpellEntry *sp)
{
	float cost;
	if( sp->ManaCostPercentage && IsUnit() )//Percentage spells cost % of !!!BASE!!! mana
	{
		if( sp->powerType==POWER_TYPE_MANA)
			cost = GetUInt32Value(UNIT_FIELD_BASE_MANA) * (sp->ManaCostPercentage / 100.0f);
		else
			cost = GetUInt32Value(UNIT_FIELD_BASE_HEALTH) * (sp->ManaCostPercentage / 100.0f);
	}
	else 
	{
		cost = (float)sp->manaCost;
	}

	return float2int32(cost); // Truncate zeh decimals!
}
