#ifndef _VEHICLE_H
#define _VEHICLE_H

class SERVER_DECL Vehicle : public Creature
{
public:
	Vehicle(uint64 guid);
	~Vehicle();

	void Create(CreatureProto * cp, uint32 vehicleEntry, Player * pRider = NULL);
	virtual void Update(uint32 time);

	//---------------------------------------
	// Accessors
	//---------------------------------------
	uint32 GetMaxPassengerCount() { return m_maxPassengers; }
	uint32 GetPassengerCount() { return m_passengerCount; }

	Player * GetControllingPlayer() { return m_controllingPlayer; }
	//---------------------------------------
	// End accessors
	//---------------------------------------

	void AddPassenger(Unit * pPassenger);
	void RemovePassenger(uint32 passengerSlot);
	bool HasPassenger(Unit * pPassenger);
	bool IsFull() { return m_passengerCount == m_maxPassengers; }

private:
	void _AddToSlot(Unit * pPassenger, uint32 slot);

protected:
	Player * m_controllingPlayer;

	Unit ** m_passengers;
	VehicleSeatEntry * m_vehicleSeats[8];

	uint32 m_passengerCount;
	uint32 m_maxPassengers;
};

#endif
