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

#define ARENA_PREPARATION 32727
#define ARENA_WORLD_STATE_LORD_A_PLAYER_COUNT 3000
#define ARENA_WORLD_STATE_LORD_H_PLAYER_COUNT 3001
#define ARENA_WORLD_STATE_BLADES_A_PLAYER_COUNT 2544
#define ARENA_WORLD_STATE_BLADES_H_PLAYER_COUNT 2545
#define ARENA_WORLD_STATE_NAGRAND_A_PLAYER_COUNT 2575
#define ARENA_WORLD_STATE_NAGRAND_H_PLAYER_COUNT 2576
#define GREEN_TEAM 0
#define GOLD_TEAM 1

Arena::Arena(MapMgr * mgr, uint32 id, uint32 lgroup, uint32 t, uint32 players_per_side) : CBattleground(mgr, id, lgroup, t)
{
	m_started = false;
	m_shadowsightspawned = false;
	m_playerCountPerTeam = players_per_side;
	switch(t)
	{
	case BATTLEGROUND_ARENA_5V5:
		m_arenateamtype=2;
		break;

	case BATTLEGROUND_ARENA_3V3:
		m_arenateamtype=1;
		break;
		
	case BATTLEGROUND_ARENA_2V2:
		m_arenateamtype=0;
		break;

	default:
		m_arenateamtype=0;
		break;
	}
	rated_match=false;
	m_teams[0] = m_teams[0] = -1;
}

Arena::~Arena()
{

}

void Arena::OnAddPlayer(Player * plr)
{
	plr->m_deathVision = true;

	// remove all buffs (exclude talents, include flasks)
	for(uint32 x=0;x<MAX_AURAS;x++)
	{
		if(plr->m_auras[x])
		{
			if(plr->m_auras[x] && !plr->m_auras[x]->GetSpellProto()->DurationIndex && plr->m_auras[x]->GetSpellProto()->Flags4 & CAN_PERSIST_AND_CASTED_WHILE_DEAD)
				continue;
			else
			{
				plr->m_auras[x]->Remove();
			}
		}
	}
	plr->GetItemInterface()->RemoveAllConjured();
	plr->ResetAllCooldowns();

	if( !m_started  && plr->IsInWorld())
		plr->CastSpell(plr, ARENA_PREPARATION, true);

	UpdatePlayerCounts();

	if (plr->m_bgIsQueued)
		plr->m_bgIsQueued = false;

	/* Add the green/gold team flag */
	Aura * aura = new Aura(dbcSpell.LookupEntry(plr->GetTeam() ? 35775-plr->m_bgTeam : 32725-plr->m_bgTeam), -1, plr, plr);
	plr->AddAura(aura);
	
	/* Set FFA PvP Flag */
	if(!plr->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_FREE_FOR_ALL_PVP))
		plr->SetFlag(PLAYER_FLAGS, PLAYER_FLAG_FREE_FOR_ALL_PVP);

	/* update arena team stats */
	if(rated_match && plr->m_arenaTeams[m_arenateamtype] != NULL && 
		m_teammembers[plr->GetTeam()].find(plr->GetLowGUID()) == m_teammembers[plr->GetTeam()].end())
	{
		ArenaTeam * t = plr->m_arenaTeams[m_arenateamtype];
		ArenaTeamMember * tp = t->GetMember(plr->m_playerInfo);
		if(m_teams[plr->m_bgTeam] == -1) // If wasn't set yet
		{
			t->m_stat_gamesplayedseason++;
			t->m_stat_gamesplayedweek++;
			m_teams[plr->m_bgTeam] = t->m_id;
		}

		if(tp != NULL)
		{
			tp->Played_ThisWeek++;
			tp->Played_ThisSeason++;
		}

		t->SaveToDB();
		m_teammembers[plr->m_bgTeam].insert(plr->GetLowGUID());
	}
}

void Arena::OnRemovePlayer(Player * plr)
{
	/* remove arena readyness buff */
	plr->m_deathVision = false;
	plr->RemoveAura(ARENA_PREPARATION);
	UpdatePlayerCounts();
	
	plr->RemoveAura(plr->GetTeam() ? 35775-plr->m_bgTeam : 32725-plr->m_bgTeam);
	if(plr->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_FREE_FOR_ALL_PVP))
		plr->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_FREE_FOR_ALL_PVP);
		
	plr->m_bg = NULL;
}

void Arena::HookOnPlayerKill(Player * plr, Unit * pVictim)
{
	plr->m_bgScore.KillingBlows++;
}

void Arena::HookOnHK(Player * plr)
{
	plr->m_bgScore.HonorableKills++;
}

void Arena::HookOnPlayerDeath(Player * plr)
{
	UpdatePlayerCounts();	
}

void Arena::OnCreate()
{
	GameObject * obj;
	switch(m_mapMgr->GetMapId())
	{
		/* loraedeon */
	case 572: {
		obj = SpawnGameObject(185917, 572, 1278.647705f, 1730.556641f, 31.605574f, 1.684245f, 32, 1375, 1.0f);
		obj->SetUInt32Value(GAMEOBJECT_STATE, 1);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_02, 0.746058f);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_03, 0.665881f);
		obj->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
		m_gates.insert(obj);

		obj = SpawnGameObject(185918, 572, 1293.560791f, 1601.937988f, 31.605574f, -1.457349f, 32, 1375, 1.0f);
		obj->SetUInt32Value(GAMEOBJECT_STATE, 1);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_02, -0.665881f);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_03, 0.746058f);
		obj->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
		m_gates.insert(obj);

		SetWorldState(0x0BBA, 0x0001);

			  }break;

		/* blades edge arena */
	case 562: {
		obj = SpawnGameObject(183972, 562, 6177.707520f, 227.348145f, 3.604374f, -2.260201f, 32, 1375, 1.0f);
		obj->SetUInt32Value(GAMEOBJECT_STATE, 1);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_02, 0.90445f);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_03, -0.426569f);
		obj->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
		obj->PushToWorld(m_mapMgr);

		obj = SpawnGameObject(183973, 562, 6189.546387f, 241.709854f, 3.101481f, 0.881392f, 32, 1375, 1.0f);
		obj->SetUInt32Value(GAMEOBJECT_STATE, 1);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_02, 0.426569f);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_03, 0.904455f);
		obj->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
		m_gates.insert(obj);

		obj = SpawnGameObject(183970, 562, 6299.115723f, 296.549438f, 3.308032f, 0.881392f, 32, 1375, 1.0f);
		obj->SetUInt32Value(GAMEOBJECT_STATE, 1);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_02, 0.426569f);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_03, 0.904455f);
		obj->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
		obj->PushToWorld(m_mapMgr);

		obj = SpawnGameObject(183971, 562, 6287.276855f, 282.187714f, 3.810925f, -2.260201f, 32, 1375, 1.0f);
		obj->SetUInt32Value(GAMEOBJECT_STATE, 1);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_02, 0.904455f);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_03, -0.426569f);
		obj->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
		m_gates.insert(obj);

		SetWorldState(0x09F3, 0x0001);
			  }break;

		/* nagrand arena */
	case 559: {
		obj = SpawnGameObject(183979, 559, 4090.064453f, 2858.437744f, 10.236313f, 0.492805f, 32, 1375, 1.0f);
		obj->SetUInt32Value(GAMEOBJECT_STATE, 1);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_02, 0.243916f);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_03, 0.969796f);
		obj->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
		obj->PushToWorld(m_mapMgr);

		obj = SpawnGameObject(183980, 559, 4081.178955f, 2874.970459f, 12.391714f, 0.492805f, 32, 1375, 1.0f);
		obj->SetUInt32Value(GAMEOBJECT_STATE, 1);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_02, 0.243916f);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_03, 0.969796f);
		obj->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
		m_gates.insert(obj);

		obj = SpawnGameObject(183977, 559, 4023.709473f, 2981.776611f, 10.701169f, -2.648788f, 32, 1375, 1.0f);
		obj->SetUInt32Value(GAMEOBJECT_STATE, 1);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_02, 0.969796f);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_03, -0.243916f);
		obj->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
		obj->PushToWorld(m_mapMgr);

		obj = SpawnGameObject(183978, 559, 4031.854248f, 2966.833496f, 12.646200f, -2.648788f, 32, 1375, 1.0f);
		obj->SetUInt32Value(GAMEOBJECT_STATE, 1);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_02, 0.969796f);
		obj->SetFloatValue(GAMEOBJECT_ROTATION_03, -0.243916f);
		obj->SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, 100);
		m_gates.insert(obj);

		SetWorldState(0x0A11, 0x0001);

			  }break;
	}

	/* push gates into world */
	for(set<GameObject*>::iterator itr = m_gates.begin(); itr != m_gates.end(); ++itr)
		(*itr)->PushToWorld(m_mapMgr);

	SetWorldState(0x08D4	,0x0000);
	SetWorldState(0x08D8	,0x0000);
	SetWorldState(0x08D7	,0x0000);
	SetWorldState(0x08D6	,0x0000);
	SetWorldState(0x08D5	,0x0000);
	SetWorldState(0x08D3	,0x0000);
	SetWorldState(0x09F1	,0x0000);
	SetWorldState(0x09F0	,0x0000);
	SetWorldState(0x0C0D	,0x017B);
}

void Arena::OnStart()
{
	/* remove arena readyness buff */
	for(uint32 i = 0; i < 2; ++i) {
		for(set<Player*>::iterator itr = m_players[i].begin(); itr != m_players[i].end(); ++itr) {
			(*itr)->RemoveAura(ARENA_PREPARATION);
		}
	}

	/* open gates */
	for(set<GameObject*>::iterator itr = m_gates.begin(); itr != m_gates.end(); ++itr)
	{
		(*itr)->SetUInt32Value(GAMEOBJECT_FLAGS, 64);
		(*itr)->SetUInt32Value(GAMEOBJECT_STATE, 0);
	}

	m_started = true;

	/* Incase all players left */
	UpdatePlayerCounts();

	/* Play Sound */
	PlaySoundToAll(SOUND_BATTLEGROUND_BEGIN);

	sEventMgr.RemoveEvents(this, EVENT_SHADOW_SIGHT);
	sEventMgr.AddEvent(this, &Arena::SpawnShadowSight, EVENT_SHADOW_SIGHT, 90000, 1,0);
}

void Arena::UpdatePlayerCounts()
{
	if(m_ended)
		return;

	uint32 players[2] = {0,0};
	for(uint32 i = 0; i < 2; ++i) {
		for(set<Player*>::iterator itr = m_players[i].begin(); itr != m_players[i].end(); ++itr) {
			if((*itr)->isAlive())
				players[(*itr)->GetTeam()]++;
		}
	}

	switch(m_mapMgr->GetMapId())
	{
		/* loraedeon */
	case 572:
		SetWorldState(ARENA_WORLD_STATE_LORD_A_PLAYER_COUNT, players[0]);
		SetWorldState(ARENA_WORLD_STATE_LORD_H_PLAYER_COUNT, players[1]);
		break;

		/* blades edge arena */
	case 562:
		SetWorldState(ARENA_WORLD_STATE_BLADES_A_PLAYER_COUNT, players[0]);
		SetWorldState(ARENA_WORLD_STATE_BLADES_H_PLAYER_COUNT, players[1]);
		break;

		/* nagrand arena */
	case 559:
		SetWorldState(ARENA_WORLD_STATE_NAGRAND_A_PLAYER_COUNT, players[0]);
		SetWorldState(ARENA_WORLD_STATE_NAGRAND_H_PLAYER_COUNT, players[1]);
		break;
	}


	if(!m_started)
		return;

	if(players[1] == 0)
		m_winningteam = 0;
	else if(players[0] == 0)
		m_winningteam = 1;
	else
		return;

	Finish();
}

void Arena::Finish()
{
	m_ended = true;
	m_nextPvPUpdateTime = 0;
	UpdatePvPData();
	PlaySoundToAll(m_winningteam ? SOUND_ALLIANCEWINS : SOUND_HORDEWINS);

	sEventMgr.RemoveEvents(this, EVENT_BATTLEGROUND_CLOSE);
	sEventMgr.AddEvent(((CBattleground*)this), &CBattleground::Close, EVENT_BATTLEGROUND_CLOSE, 120000, 1,0);
	ArenaTeam * teams[2];
	teams[0] = objmgr.GetArenaTeamById(m_teams[0]);
	teams[1] = objmgr.GetArenaTeamById(m_teams[1]);
	/* update arena team stats */
	if(rated_match && teams[0] && teams[1])
	{
		for (uint32 i = 0; i < 2; ++i) {
			uint32 j = i ? 0 : 1; // opposing side
			bool outcome;

			outcome = (i == m_winningteam);

			// ---- Elo Rating System ----
			// Expected Chance to Win for Team A vs Team B
			//                     1
			// -------------------------------------------
			//                   (PB - PA)/400
			//              1 + 10

			double power = (int)(teams[j]->m_stat_rating - teams[i]->m_stat_rating) / 400.0f;
			double divisor = pow(((double)(10.0)), power);
			divisor += 1.0;

			double winChance = 1.0 / divisor;
			if (outcome)
			{
				teams[i]->m_stat_gameswonseason++;
				teams[i]->m_stat_gameswonweek++;
			}
			// New Rating Calculation via Elo
			// New Rating = Old Rating + K * (outcome - Expected Win Chance)
			// outcome = 1 for a win and 0 for a loss (0.5 for a draw ... but we cant have that)
			// K is the maximum possible change
			// Through investigation, K was estimated to be 32 (same as chess)
			double multiplier = (outcome ? 1.0 : 0.0) - winChance;
			double deltaRating = 32.0 * multiplier;
			int32 deltaRatingI = long2int32(deltaRating);
			if ( deltaRatingI < 0 && uint32(-deltaRatingI) > teams[i]->m_stat_rating )
				teams[i]->m_stat_rating = 0;
			else
				teams[i]->m_stat_rating += deltaRatingI;
			objmgr.UpdateArenaTeamRankings();	

			for(set<uint32>::iterator itr = m_teammembers[i].begin(); itr != m_teammembers[i].end(); itr++)
			{
				uint32 guid = *itr;
				ArenaTeamMember * tp = teams[i]->GetMemberByGuid(guid);
				if(tp)
				{
					if(outcome)
					{
						tp->Won_ThisWeek++;
						tp->Won_ThisSeason++;
					}
					if ( deltaRatingI < 0 && uint32(-deltaRatingI) > teams[i]->m_stat_rating )
						tp->PersonalRating = 0;
					else
						tp->PersonalRating += deltaRatingI;
					Player * plr = GetMapMgr()->GetPlayer(guid);
					if(plr)
						plr->m_bgScore.Misc1 = 3000 + deltaRatingI; // Trying to save the rating change for result board display
				}
			}
			teams[i]->SaveToDB();
		}
	}

	for(int i = 0; i < 2; i++)
	{
		bool victorious = (i == m_winningteam);
		set<Player*>::iterator itr = m_players[i].begin();
		for(; itr != m_players[i].end(); itr++)
		{
			Player * plr = (Player *)(*itr);
			if(plr != NULL)
				sHookInterface.OnArenaFinish(plr, plr->m_arenaTeams[m_arenateamtype], victorious, rated_match);
		}
	}
}

LocationVector Arena::GetStartingCoords(uint32 Team)
{
	// 559, 562, 572
	/*
	A start
	H start
	Repop
	572 1295.322388 1585.953369 31.605387
	572 1277.105103 1743.956177 31.603209
	572 1286.112061 1668.334961 39.289127

	562 6184.806641 236.643463 5.037095
	562 6292.032227 287.570343 5.003577
	562 6241.171875 261.067322 0.891833

	559 4085.861328 2866.750488 12.417445
	559 4027.004883 2976.964844 11.600499
	559 4057.042725 2918.686523 13.051933
	*/
	switch(m_mapMgr->GetMapId())
	{
		/* loraedeon */
	case 572:
		{
			if(Team)
				return LocationVector(1277.105103f, 1743.956177f, 31.603209f);
			else
				return LocationVector(1295.322388f, 1585.953369f, 31.605387f);
		}break;

		/* blades edge arena */
	case 562:
		{
			if(Team)
				return LocationVector(6292.032227f, 287.570343f, 5.003577f);
			else
				return LocationVector(6184.806641f, 236.643463f, 5.037095f);
		}break;

		/* nagrand arena */
	case 559:
		{
			if(Team)
				return LocationVector(4027.004883f, 2976.964844f, 11.600499f);
			else
				return LocationVector(4085.861328f, 2866.750488f, 12.417445f);
		}break;
	}

	return LocationVector(0,0,0,0);
}

bool Arena::HookHandleRepop(Player * plr)
{
	// 559, 562, 572
	/*
	A start
	H start
	Repop
	572 1295.322388 1585.953369 31.605387
	572 1277.105103 1743.956177 31.603209
	572 1286.112061 1668.334961 39.289127

	562 6184.806641 236.643463 5.037095
	562 6292.032227 287.570343 5.003577
	562 6241.171875 261.067322 0.891833

	559 4085.861328 2866.750488 12.417445
	559 4027.004883 2976.964844 11.600499
	559 4057.042725 2918.686523 13.051933
	*/
	LocationVector dest(0,0,0,0);
	switch(m_mapMgr->GetMapId())
	{
		/* loraedeon */
	case 572: {
			dest.ChangeCoords(1286.112061f, 1668.334961f, 39.289127f);
		}break;

		/* blades edge arena */
	case 562: {
			dest.ChangeCoords(6241.171875f, 261.067322f, 0.891833f);
		}break;

		/* nagrand arena */
	case 559: {
			dest.ChangeCoords(4057.042725f, 2918.686523f, 13.051933f);
		}break;
	}

	plr->SafeTeleport(m_mapMgr->GetMapId(), m_mapMgr->GetInstanceID(), dest);
	return true;
}

void Arena::HookOnAreaTrigger(Player * plr, uint32 id)
{
	uint32 spellid=0;
	int8 buffslot = -1;

	if(!m_started || !m_shadowsightspawned)
		return;

	switch(id) 
	{
		case 4536: //Nagrand
		case 4538: //Blades Edge
		case 4696: //Lordaeron
			buffslot = 0;
			break;

		case 4537: //Nagrand
		case 4539: //Blades Edge
		case 4697: //Lordaeron
			buffslot = 1;
			break;

		default:
			{
				Log.Error("Arena", "Encountered unhandled areatrigger id %u", id);
				return;
			}break;
	}

	if(m_shadowsight[buffslot] != NULL && m_shadowsight[buffslot]->IsInWorld())
	{
		/* apply the spell */
		spellid = m_shadowsight[buffslot]->GetInfo()->sound3;

		/*Despawn and Respawn in 90000ms */
		m_shadowsight[buffslot]->Despawn(90000);
			
		/* cast the spell on the player */
		SpellEntry * sp = dbcSpell.LookupEntryForced(spellid);
		if(sp)
		{
			Spell * pSpell = new Spell(plr, sp, true, NULL);
			SpellCastTargets targets(plr->GetGUID());
			pSpell->prepare(&targets);
		}
	}
}

void Arena::SpawnShadowSight()
{
	switch(m_mapMgr->GetMapId())
	{
		/* ruins of lordaeron */
	case 572:
		m_shadowsight[0] = SpawnGameObject(184663, 572, 1328.72f, 1632.72f, 36.73f, 2.6f, 32, 1375, 1.0f);
		m_shadowsight[0]->SetUInt32Value(GAMEOBJECT_TYPE_ID, 6);
		m_shadowsight[0]->PushToWorld(m_mapMgr);

		m_shadowsight[1] = SpawnGameObject(184664, 572, 1243.306759f, 1699.334354f, 34.87f, 5.7f, 32, 1375, 1.0f);
		m_shadowsight[1]->SetUInt32Value(GAMEOBJECT_TYPE_ID, 6);
		m_shadowsight[1]->PushToWorld(m_mapMgr);
		break;

		/* blades edge arena */
	case 562:
		m_shadowsight[0] = SpawnGameObject(184663, 562, 6248.73f, 274.70f, 11.22f, -2.2f, 32, 1375, 1.0f);
		m_shadowsight[0]->SetUInt32Value(GAMEOBJECT_TYPE_ID, 6);
		m_shadowsight[0]->PushToWorld(m_mapMgr);

		m_shadowsight[1] = SpawnGameObject(184664, 562, 6228.21f, 249.56f, 11.22f, 0.8f, 32, 1375, 1.0f);
		m_shadowsight[1]->SetUInt32Value(GAMEOBJECT_TYPE_ID, 6);
		m_shadowsight[1]->PushToWorld(m_mapMgr);
		break;

		/* nagrand arena */
	case 559:
		m_shadowsight[0] = SpawnGameObject(184663, 559, 4009.19f, 2895.25f, 13.05f, 0.4f, 32, 1375, 1.0f);
		m_shadowsight[0]->SetUInt32Value(GAMEOBJECT_TYPE_ID, 6);
		m_shadowsight[0]->PushToWorld(m_mapMgr);

		m_shadowsight[1] = SpawnGameObject(184664, 559, 4103.33f, 2946.35f, 13.05f, 3.6f, 32, 1375, 1.0f);
		m_shadowsight[1]->SetUInt32Value(GAMEOBJECT_TYPE_ID, 6);
		m_shadowsight[1]->PushToWorld(m_mapMgr);
		break;
	}
	m_shadowsightspawned = true;
	SendChatMessage( CHAT_MSG_BG_EVENT_NEUTRAL, 0, "Shadow Sight powerups have been spawned!" );
}
