/*
 * made by jajcer
 */

#ifndef _SOTA_H
#define _SOTA_H

static const float SOTAStartLocations[2][3] = {
	{ 1601.004395f, -105.182663f, 8.873691f }, //attackers
	{ 922.102234f, -111.102646f, 97.178421f }, //defenders
};

class StrandOfTheAncients : public CBattleground
{
public:
	StrandOfTheAncients(MapMgrPointer mgr, uint32 id, uint32 lgroup, uint32 t);
	~StrandOfTheAncients();
	virtual void Init();

	void HookOnPlayerDeath(PlayerPointer plr);
	void HookFlagDrop(PlayerPointer plr, GameObjectPointer obj);
	void HookFlagStand(PlayerPointer plr, GameObjectPointer obj);
	void HookOnMount(PlayerPointer plr);
	void HookOnAreaTrigger(PlayerPointer plr, uint32 id);
	bool HookHandleRepop(PlayerPointer plr);
	void OnAddPlayer(PlayerPointer plr);
	void OnRemovePlayer(PlayerPointer plr);
	void OnCreate();
	void HookOnPlayerKill(PlayerPointer plr, UnitPointer pVictim);
	void HookOnHK(PlayerPointer plr);
	void HookOnShadowSight();
	LocationVector GetStartingCoords(uint32 Team);

	static BattlegroundPointer Create(MapMgrPointer m, uint32 i, uint32 l, uint32 t) { return shared_ptr<StrandOfTheAncients>(new StrandOfTheAncients(m, i, l, t)); }

	const char * GetName() { return "Strand of the Ancients"; }
	void OnStart();

	bool SupportsPlayerLoot() { return true; }
	bool HookSlowLockOpen(GameObjectPointer pGo, PlayerPointer pPlayer, shared_ptr<Spell> pSpell);

	void HookGenerateLoot(PlayerPointer plr, CorpsePointer pCorpse);

	void SetIsWeekend(bool isweekend);
	void SetTime(uint32 secs, uint32 WorldState);
	uint32 GetRoundTime(){ return RoundTime; };
	void SetRoundTime(uint32 secs){ RoundTime = secs; };
	void TimeTick();
	void PrepareRound();
protected:
	uint32 Attackers; // 0 - horde / 1 - alliance
	uint32 BattleRound;
	uint32 RoundTime;
};

#endif		// _SOTA_H
