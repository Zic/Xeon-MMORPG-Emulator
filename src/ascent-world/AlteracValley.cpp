/*
 * Ascent MMORPG Server
 * Copyright (C) 2005-2008 Ascent Team <http://www.ascentemu.com/>
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


void AlteracValley::OnCreate()
{
	// Alliance Gate
	GameObject *gate = SpawnGameObject(180255, 30, 1284.597290f, 1281.166626f, -15.977916f, 0.706859f, 32, 114, 1.5799990f);
	gate->SetFloatValue(GAMEOBJECT_ROTATION,0.0129570f);
	gate->SetFloatValue(GAMEOBJECT_ROTATION_01,-0.0602880f);
	gate->SetFloatValue(GAMEOBJECT_ROTATION_02,0.3449600f);
	gate->SetFloatValue(GAMEOBJECT_ROTATION_03,0.9365900f);
	gate->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
	gate->PushToWorld(m_mapMgr);
	m_gates.push_back(gate);

	// horde gate
	gate = SpawnGameObject(180256, 30, 708.0902710f, 708.4479370f, -17.3898964f, -2.3910990f, 32, 114, 1.5699990f);
	gate->SetFloatValue(GAMEOBJECT_ROTATION,0.0502910f);
	gate->SetFloatValue(GAMEOBJECT_ROTATION_01,0.0151270f);
	gate->SetFloatValue(GAMEOBJECT_ROTATION_02,0.9292169f);
	gate->SetFloatValue(GAMEOBJECT_ROTATION_03,-0.3657840f);
	gate->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
	gate->PushToWorld(m_mapMgr);
	m_gates.push_back(gate);

	// spawn the h/a base spirit guides
//	AddSpiritGuide(SpawnSpiritGuide(NoBaseGYLocations[0][0],NoBaseGYLocations[0][1],NoBaseGYLocations[0][2], 0.0f, 0));
//	AddSpiritGuide(SpawnSpiritGuide(NoBaseGYLocations[1][0],NoBaseGYLocations[1][1],NoBaseGYLocations[1][2], 0.0f, 1));
}

void AlteracValley::OnStart()
{
	for(uint32 i = 0; i < 2; ++i) {
		for(set<Player*>::iterator itr = m_players[i].begin(); itr != m_players[i].end(); ++itr) {
			(*itr)->RemoveAura(BG_PREPARATION);
		}
	}

	// open gates
	for(list<GameObject*>::iterator itr = m_gates.begin(); itr != m_gates.end(); ++itr)
	{
		(*itr)->SetUInt32Value(GAMEOBJECT_FLAGS, 64);
		(*itr)->SetUInt32Value(GAMEOBJECT_STATE, 0);
	}

	/* correct? - burlex */
	PlaySoundToAll(SOUND_BATTLEGROUND_BEGIN);

	m_started = true;
}

AlteracValley::AlteracValley(MapMgr * mgr, uint32 id, uint32 lgroup, uint32 t) : CBattleground(mgr,id,lgroup,t)
{
	uint32 i;

	m_playerCountPerTeam=40;

	for(i = 0; i < 2; ++i)
	{
		m_scores[i] = 600;
	}
}

AlteracValley::~AlteracValley()
{
}

void AlteracValley::HookOnPlayerDeath(Player * plr)
{
	DecrementReinforcements(plr->GetTeam(), 1);
	plr->m_bgScore.Deaths++;
	UpdatePvPData();
}

void AlteracValley::HookOnMount(Player * plr)
{
	// nothing in this BG
}

void AlteracValley::HookOnPlayerKill(Player * plr, Unit * pVictim)
{
	if(pVictim->IsPlayer())
	{
		plr->m_bgScore.KillingBlows++;
		UpdatePvPData();
	}
}

void AlteracValley::HookOnHK(Player * plr)
{
	plr->m_bgScore.HonorableKills++;
	UpdatePvPData();
}

void AlteracValley::OnAddPlayer(Player * plr)
{
	if(!m_started && plr->IsInWorld())
		plr->CastSpell(plr, BG_PREPARATION, true);
}

void AlteracValley::OnRemovePlayer(Player * plr)
{
	plr->RemoveAura(BG_PREPARATION);
}

void AlteracValley::HookFlagDrop(Player * plr, GameObject * obj)
{
}

void AlteracValley::HookFlagStand(Player * plr, GameObject * obj)
{
}

LocationVector AlteracValley::GetStartingCoords(uint32 Team)
{
	if(Team)
		return LocationVector(684.75629f, 681.945007f, -12.915456f, 0.881211f);
	else
		return LocationVector(1314.932495f, 1311.246948f, -9.00952f,3.802896f);
}

void AlteracValley::HookOnAreaTrigger(Player * plr, uint32 id)
{
}

bool AlteracValley::HookHandleRepop(Player * plr)
{
	return true;
}

void AlteracValley::DecrementReinforcements(uint32 teamId, uint32 amt)
{
	if(teamId >= 2 || amt <= 0) return;

	m_scores[teamId]-= amt;
	if (m_scores[teamId] < 0)
		m_scores[teamId] = 0;

	if (m_scores[teamId] == 0)
	{
		// Team won!
	}
}

void AlteracValley::SetScore(uint32 teamId, uint32 score)
{
	if(teamId < 2 && score >= 0 && !m_ended && m_started)
	{
		m_scores[teamId] = score;
//		SetWorldState(teamId ? WSG_CURRENT_HORDE_SCORE : WSG_CURRENT_ALLIANCE_SCORE, score);
	}
}
