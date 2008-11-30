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

void Vehicle::Create(CreatureProto * cp, uint32 vehicleEntry, Player * pRider)
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

	m_passengers = (Unit**)malloc(sizeof(Unit*) * m_maxPassengers);
	memset( m_passengers, 0, sizeof(Unit*) * m_maxPassengers);

	if( pRider )
		AddPassenger( pRider );
}

void Vehicle::Update(uint32 time)
{
}

void Vehicle::AddPassenger(Unit * pPassenger)
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

bool Vehicle::HasPassenger(Unit * pPassenger)
{
	for(uint32 i = 0; i < m_maxPassengers; ++i)
	{
		if( m_passengers[i] == pPassenger )
			return true;
	}
	return false;
}

void Vehicle::_AddToSlot(Unit * pPassenger, uint32 slot)
{
	assert( slot < m_maxPassengers );
	m_passengers[ slot ] = pPassenger;

	// This is where the real magic happens
	if( pPassenger->IsPlayer() )
	{
		Player * pPlayer = TO_PLAYER(pPassenger);
		pPlayer->Root();
	}
}