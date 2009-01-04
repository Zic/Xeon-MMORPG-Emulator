/*
 * Aspire Hearthstone
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


#ifndef _EOTS_H
#define _EOTS_H

#define EOTS_TOWER_COUNT 4
#define EOTS_BUFF_RESPAWN_TIME 90000

class EyeOfTheStorm : public CBattleground
{
public:
	EyeOfTheStorm(shared_ptr<MapMgr> mgr, uint32 id, uint32 lgroup, uint32 t);
	~EyeOfTheStorm();
	virtual void Init();

	void HookOnPlayerDeath(PlayerPointer plr);
	void HookFlagDrop(PlayerPointer plr, shared_ptr<GameObject> obj);
	void HookFlagStand(PlayerPointer plr, shared_ptr<GameObject> obj);
	void HookOnMount(PlayerPointer plr);
	void HookOnAreaTrigger(PlayerPointer plr, uint32 id);
	bool HookHandleRepop(PlayerPointer plr);
	void OnAddPlayer(PlayerPointer plr);
	void OnRemovePlayer(PlayerPointer plr);
	void OnCreate();
	void HookOnPlayerKill(PlayerPointer plr, UnitPointer pVictim);
	void HookOnHK(PlayerPointer plr);
	void HookOnShadowSight();
	void SpawnBuff(uint32 x);
	LocationVector GetStartingCoords(uint32 Team);
	static shared_ptr<CBattleground> Create(shared_ptr<MapMgr> m, uint32 i, uint32 l, uint32 t) { return shared_ptr<EyeOfTheStorm>(new EyeOfTheStorm(m, i, l, t)); }

	const char * GetName() { return "Eye of the Storm"; }
	void OnStart();

	void UpdateCPs();
	void GeneratePoints();

	// returns true if that team won
	bool GivePoints(uint32 team, uint32 points);

	void RespawnCPFlag(uint32 i, uint32 id);		// 0 = Neutral, <0 = Leaning towards alliance, >0 Leaning towards horde

	bool HookSlowLockOpen(shared_ptr<GameObject> pGo, PlayerPointer pPlayer, shared_ptr<Spell>pSpell);
	void DropFlag(PlayerPointer plr);
	void EventResetFlag();
	void RepopPlayersOfTeam(int32 team, CreaturePointer sh);

	/* looooooot */
	bool SupportsPlayerLoot() { return true; }
	void HookGenerateLoot(shared_ptr<Player>plr, shared_ptr<Corpse>pCorpse);

	void SetIsWeekend(bool isweekend);

protected:
	uint32 m_resourceRewards[2];
	int32 m_CPStatus[EOTS_TOWER_COUNT];		
	uint32 m_flagHolder;

	shared_ptr<GameObject> m_standFlag;
	shared_ptr<GameObject> m_dropFlag;

	shared_ptr<GameObject> m_CPStatusGO[EOTS_TOWER_COUNT];
	shared_ptr<GameObject> m_CPBanner[EOTS_TOWER_COUNT];
	shared_ptr<GameObject> m_bubbles[2];
	shared_ptr<GameObject> m_EOTSbuffs[4];

	typedef map<uint32, uint32> EOTSStoredPlayerMap;
	EOTSStoredPlayerMap m_CPStored[EOTS_TOWER_COUNT];
	int32 m_towerCount[2];

	uint32 m_points[2];
	CreaturePointer m_spiritGuides[EOTS_TOWER_COUNT];
};

#endif		// _EOTS_H
