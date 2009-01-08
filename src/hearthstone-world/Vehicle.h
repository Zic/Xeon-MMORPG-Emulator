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

#ifndef _VEHICLE_H
#define _VEHICLE_H

class SERVER_DECL Vehicle : public Creature
{
public:
	Vehicle(uint64 guid);
	~Vehicle();
	virtual void Destructor();

	void Create(CreatureProto * cp, uint32 vehicleEntry, PlayerPointer pRider = NULLPLR);
	virtual void Update(uint32 time);

	//---------------------------------------
	// Accessors
	//---------------------------------------
	uint32 GetMaxPassengerCount() { return m_maxPassengers; }
	uint32 GetPassengerCount() { return m_passengerCount; }

	PlayerPointer GetControllingPlayer() { return m_controllingPlayer; }
	//---------------------------------------
	// End accessors
	//---------------------------------------

	void AddPassenger(UnitPointer pPassenger);
	void RemovePassenger(uint32 passengerSlot);
	bool HasPassenger(UnitPointer pPassenger);
	bool IsFull() { return m_passengerCount == m_maxPassengers; }

private:
	void _AddToSlot(UnitPointer pPassenger, uint32 slot);

protected:
	PlayerPointer m_controllingPlayer;

	shared_ptr<Unit>* m_passengers;
	VehicleSeatEntry * m_vehicleSeats[8];

	uint32 m_passengerCount;
	uint32 m_maxPassengers;
};

#endif
