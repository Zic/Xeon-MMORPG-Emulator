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
	m_passengerCount = 0;
	m_maxPassengers = 0;
	memset( m_vehicleSeats, 0, sizeof(uint32)*8 );
}

Vehicle::~Vehicle()
{
}

void Vehicle::Destructor()
{
	Creature::Destructor();
}

void Vehicle::Create(CreatureProto * cp, uint32 vehicleEntry, PlayerPointer pRider)
{
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

	if( pRider )
		AddPassenger( pRider );
}

void Vehicle::Update(uint32 time)
{
}

void Vehicle::AddPassenger(UnitPointer pPassenger)
{
	// Find an available seat
	for(uint32 i = 0; i < m_maxPassengers; ++i)
	{
		if( !m_passengers[i] ) // Found a slot
		{
			_AddToSlot(pPassenger, i );
			break;
		}
	}
}

void Vehicle::RemovePassenger(uint32 passengerSlot)
{
}

bool Vehicle::HasPassenger(UnitPointer pPassenger)
{
	for(uint32 i = 0; i < m_maxPassengers; ++i)
	{
		if( m_passengers[i] == pPassenger )
			return true;
	}
	return false;
}

void Vehicle::_AddToSlot(UnitPointer pPassenger, uint32 slot)
{
	assert( slot < m_maxPassengers );
	m_passengers[ slot ] = pPassenger;

	// This is where the real magic happens
	if( pPassenger->IsPlayer() )
	{
		PlayerPointer pPlayer = TO_PLAYER(pPassenger);
		pPlayer->Root();
	}
}