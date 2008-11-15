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

Unit::Unit()
{
	m_chain = NULL;
	m_attackTimer = 0;
	m_attackTimer_1 = 0;
	m_duelWield = false;

	m_fearmodifiers = 0;
	m_state = 0;
	m_special_state = 0;
	m_deathState = ALIVE;
	m_currentSpell = NULL;
	m_meleespell = 0;
	m_addDmgOnce = 0;
	m_TotemSlots[0] = NULL;
	m_TotemSlots[1] = NULL;
	m_TotemSlots[2] = NULL;
	m_TotemSlots[3] = NULL;
	m_TotemSlots[4] = NULL;
	m_ObjectSlots[0] = 0;
	m_ObjectSlots[1] = 0;
	m_ObjectSlots[2] = 0;
	m_ObjectSlots[3] = 0;
	m_silenced = 0;
	disarmed   = false;

	// Pet
	m_isPet = false;
	
	//DK:modifiers
	PctRegenModifier = 0;
	for( uint32 x = 0; x < 4; x++ )
	{
		PctPowerRegenModifier[x] = 1;
	}
	m_speedModifier = 1.0f;
	m_slowdown = 0;
	m_mountedspeedModifier=0;
	m_maxSpeed = 0;
	for(uint32 x=0;x<NUM_MECHANIC;x++)
	{
		MechanicsDispels[x]=0;
		MechanicsResistancesPCT[x]=0;
		ModDamageTakenByMechPCT[x]=0;
	}

	//SM
	SM_CriticalChance=0;
	SM_FDur=0;//flat
	SM_PDur=0;//pct
	SM_FRadius=0;
	SM_FRange=0;
	SM_PCastTime=0;
	SM_FCastTime=0;
	SM_PCriticalDamage=0;
	SM_FDOT=0;
	SM_PDOT=0;
	SM_FEffectBonus=0;
	SM_PEffectBonus=0;
	SM_FDamageBonus=0;
	SM_PDamageBonus=0;
	SM_PSPELL_VALUE=0;
	SM_FSPELL_VALUE=0;
	SM_FHitchance=0;
	SM_PRange=0;//pct
	SM_PRadius=0;
	SM_PAPBonus=0;
	SM_PCost=0;
	SM_FCost=0;
	SM_FAdditionalTargets=0;
	SM_PJumpReduce=0;
	SM_FSpeedMod=0;
	SM_PNonInterrupt=0;
	SM_FPenalty=0;
	SM_PPenalty=0;
	SM_FCooldownTime = 0;
	SM_PCooldownTime = 0;
	SM_FChanceOfSuccess = 0;
	SM_FRezist_dispell = 0;
	SM_PRezist_dispell = 0;
	SM_PThreatReduced = 0;

	m_pacified = 0;
	m_interruptRegen = 0;
	m_resistChance = 0;
	m_powerRegenPCT = 0;
	RAPvModifier=0;
	APvModifier=0;
	stalkedby=0;

	m_extraattacks = 0;
	m_stunned = 0;
	m_manashieldamt=0;
	m_rooted = 0;
	m_triggerSpell = 0;
	m_triggerDamage = 0;
	m_canMove = 0;
	m_noInterrupt = 0;
	m_modlanguage = -1;
	m_magnetcaster = 0;
	
	critterPet = NULL;
	summonPet = NULL;

	m_useAI = false;
	for(uint32 x=0;x<10;x++)
	{
		dispels[x]=0;
		CreatureAttackPowerMod[x] = 0;
		CreatureRangedAttackPowerMod[x] = 0;
	}
	//REMIND:Update these if you make any changes
	CreatureAttackPowerMod[UNIT_TYPE_MISC] = 0;
	CreatureRangedAttackPowerMod[UNIT_TYPE_MISC] = 0;
	CreatureAttackPowerMod[11] = 0;
	CreatureRangedAttackPowerMod[11] = 0;

	m_invisible = false;
	m_invisFlag = INVIS_FLAG_NORMAL;

	for(int i = 0; i < INVIS_FLAG_TOTAL; i++)
	{
		m_invisDetect[i] = 0;
	}

	m_stealthLevel = 0;
	m_stealthDetectBonus = 0;
	m_stealth = 0;
	m_can_stealth = true;

	for(uint32 x=0;x<5;x++)
		BaseStats[x]=0;

	m_H_regenTimer = 2000;
	m_P_regenTimer = 2000;

	//	if(GetTypeId() == TYPEID_PLAYER) //only player for now
	//		CalculateActualArmor();

	m_aiInterface = new AIInterface();
	m_aiInterface->Init(this, AITYPE_AGRO, MOVEMENTTYPE_NONE);

	m_emoteState = 0;
	m_oldEmote = 0;	
	
	BaseDamage[0]=0;
	BaseOffhandDamage[0]=0;
	BaseRangedDamage[0]=0;
	BaseDamage[1]=0;
	BaseOffhandDamage[1]=0;
	BaseRangedDamage[1]=0;

	m_CombatUpdateTimer = 0;
	for(uint32 x=0;x<7;x++)
	{
		SchoolImmunityList[x] = 0;
		BaseResistance[x] = 0;
		HealDoneMod[x] = 0;
		HealDonePctMod[x] = 0;
		HealTakenMod[x] = 0;
		HealTakenPctMod[x] = 0;
		DamageTakenMod[x] = 0;
		DamageDoneModPCT[x]= 0;
		SchoolCastPrevent[x]=0;
		DamageTakenPctMod[x] = 1;
		SpellCritChanceSchool[x] = 0;
		PowerCostMod[x] = 0;
		PowerCostPctMod[x] = 0; // armor penetration & spell penetration
		AttackerCritChanceMod[x]=0;
		CritMeleeDamageTakenPctMod[x]=0;
		CritRangedDamageTakenPctMod[x]=0;
	}
	DamageTakenPctModOnHP35 = 1;
	RangedDamageTaken = 0;

	for(int i = 0; i < 5; i++)
	{
		m_detectRangeGUID[i] = 0;
		m_detectRangeMOD[i] = 0;
	}

	trackStealth = false;

	m_threatModifyer = 0;
	m_generatedThreatModifyer = 0;
	memset(m_auras, 0, (MAX_AURAS+MAX_PASSIVE_AURAS)*sizeof(Aura*));
	
	// diminishing return stuff
	memset(m_diminishAuraCount, 0, DIMINISHING_GROUPS);
	memset(m_diminishCount, 0, DIMINISHING_GROUPS*2);
	memset(m_diminishTimer, 0, DIMINISHING_GROUPS*2);
	memset(m_auraStackCount, 0, MAX_AURAS);
	m_diminishActive = false;
	dynObj = 0;
	pLastSpell = 0;
	m_flyspeedModifier = 0;
	bInvincible = false;
	m_redirectSpellPackets = 0;
	can_parry = false;
	bProcInUse = false;
	spellcritperc = 0;

	polySpell = 0;
	RangedDamageTaken = 0;
	m_procCounter = 0;
	m_extrastriketargets = 0;
	m_damgeShieldsInUse = false;
//	fearSpell = 0;
	m_extraAttackCounter = false;
	CombatStatus.SetUnit(this);
	m_temp_summon=false;
	m_chargeSpellsInUse=false;
	m_spellsbusy=false;
	m_interruptedRegenTime = 0;

	trigger_on_stun = 0;
	trigger_on_stun_chance = 100;
	trigger_on_chill = 0;
	trigger_on_chill_chance = 100;
}

Unit::~Unit()
{  
	RemoveAllAuras();

	if (m_chain)
		m_chain->RemoveUnit(this);
	if(SM_CriticalChance != 0) delete [] SM_CriticalChance ;
	if(SM_FDur != 0) delete [] SM_FDur ;//flat
	if(SM_PDur != 0) delete [] SM_PDur ;//pct
	if(SM_FRadius != 0) delete [] SM_FRadius ;
	if(SM_FRange != 0) delete [] SM_FRange ;
	if(SM_PCastTime != 0) delete [] SM_PCastTime ;
	if(SM_FCastTime != 0) delete [] SM_FCastTime ;
	if(SM_PCriticalDamage != 0) delete [] SM_PCriticalDamage ;
	if(SM_FDOT != 0) delete [] SM_FDOT ;
	if(SM_PDOT != 0) delete [] SM_PDOT ;
	if(SM_PEffectBonus != 0) delete [] SM_PEffectBonus ;
    if(SM_FEffectBonus != 0) delete [] SM_FEffectBonus ;
	if(SM_FDamageBonus != 0) delete [] SM_FDamageBonus ;
	if(SM_PDamageBonus != 0) delete [] SM_PDamageBonus ;
	if(SM_PSPELL_VALUE != 0) delete [] SM_PSPELL_VALUE ;
	if(SM_FSPELL_VALUE != 0) delete [] SM_FSPELL_VALUE ;
	if(SM_FHitchance != 0) delete [] SM_FHitchance ;
	if(SM_PRange != 0) delete [] SM_PRange ;//pct
	if(SM_PRadius != 0) delete [] SM_PRadius ;
	if(SM_PAPBonus != 0) delete [] SM_PAPBonus ;
	if(SM_PCost != 0) delete [] SM_PCost ;
	if(SM_FCost != 0) delete [] SM_FCost ;
	if(SM_FAdditionalTargets != 0) delete [] SM_FAdditionalTargets ;
	if(SM_PJumpReduce != 0) delete [] SM_PJumpReduce ;
	if(SM_FSpeedMod != 0) delete [] SM_FSpeedMod ;
	if(SM_PNonInterrupt != 0) delete [] SM_PNonInterrupt ;
	if(SM_FPenalty != 0) delete [] SM_FPenalty ;
	if(SM_PPenalty != 0) delete [] SM_PPenalty ;
	if(SM_FCooldownTime != 0) delete [] SM_FCooldownTime ;
	if(SM_PCooldownTime != 0) delete [] SM_PCooldownTime ;
	if(SM_FChanceOfSuccess != 0) delete [] SM_FChanceOfSuccess ;
	if(SM_FRezist_dispell != 0) delete [] SM_FRezist_dispell ;
	if(SM_PRezist_dispell != 0) delete [] SM_PRezist_dispell ;
	if(SM_PThreatReduced != 0) delete [] SM_PThreatReduced ;

	delete m_aiInterface;

	/*for(int i = 0; i < 4; i++)
		if(m_ObjectSlots[i])
			delete m_ObjectSlots[i];*/

	if(m_currentSpell)
		m_currentSpell->cancel();
}

void Unit::Update( uint32 p_time )
{
	_UpdateSpells( p_time );

	if(!isDead())
	{
		//-----------------------POWER & HP REGENERATION-----------------
/* Please dont do temp fixes. Better report to me. Thx. Shady */
        if( p_time >= m_H_regenTimer )
		    RegenerateHealth();
	    else
		    m_H_regenTimer -= p_time;

		if( p_time >= m_P_regenTimer )
		{
			RegeneratePower( false );
			m_interruptedRegenTime=0;
		}
		else
		{
			m_P_regenTimer -= p_time;
			if (m_interruptedRegenTime)
			{
				if(p_time>=m_interruptedRegenTime)
					RegeneratePower( true );
				else
					m_interruptedRegenTime -= p_time;
			}
		}


		if(m_aiInterface != NULL && m_useAI)
			m_aiInterface->Update(p_time);

		if(m_diminishActive)
		{
			uint32 count = 0;
			for(uint32 x = 0; x < DIMINISHING_GROUPS; ++x)
			{
				// diminishing return stuff
				if(m_diminishTimer[x] && !m_diminishAuraCount[x])
				{
					if(p_time >= m_diminishTimer[x])
					{
						// resetting after 15 sec
						m_diminishTimer[x] = 0;
						m_diminishCount[x] = 0;
					}
					else
					{
						// reducing, still.
						m_diminishTimer[x] -= p_time;
						++count;
					}
				}
			}
			if(!count)
				m_diminishActive = false;
		}

/*		//if health changed since last time. Would be perfect if it would work for creatures too :)
		if(m_updateMask.GetBit(UNIT_FIELD_HEALTH))
			EventHealthChangeSinceLastUpdate();*/
	}
}

bool Unit::canReachWithAttack(Unit *pVictim)
{
//	float targetreach = pVictim->GetFloatValue(UNIT_FIELD_COMBATREACH);
	float selfreach = m_floatValues[UNIT_FIELD_COMBATREACH];
	float targetradius = pVictim->m_floatValues[UNIT_FIELD_BOUNDINGRADIUS];
	float selfradius = m_floatValues[UNIT_FIELD_BOUNDINGRADIUS];
	float targetscale = pVictim->m_floatValues[OBJECT_FIELD_SCALE_X];
	float selfscale = m_floatValues[OBJECT_FIELD_SCALE_X];

	if( GetMapId() != pVictim->GetMapId() )
		return false;

	float distance = sqrt(GetDistanceSq(pVictim));
	float attackreach = (((targetradius*targetscale) + selfreach) + (((selfradius*selfradius)*selfscale)+1.50f));

	//formula adjustment for player side.
	if( IsPlayer() )
	{
		if( attackreach <= 8 && attackreach >= 5 && targetradius >= 1.80f)
			attackreach = 11; //giant type units

		if( attackreach > 11)
			attackreach = 11; //distance limited to max 11 yards attack range //max attack distance

		if( attackreach < 5 )
			attackreach = 5; //normal units with too small reach.

		//range can not be less than 5 yards - this is normal combat range, SCALE IS NOT SIZE

		// latency compensation!!
		// figure out how much extra distance we need to allow for based on our movespeed and latency.
		if( pVictim->IsPlayer() && static_cast< Player* >( pVictim )->m_isMoving )
		{
			// this only applies to PvP.
			uint32 lat = static_cast< Player* >( pVictim )->GetSession() ? static_cast< Player* >( pVictim )->GetSession()->GetLatency() : 0;

			// if we're over 500 get fucked anyway.. your gonna lag! and this stops cheaters too
			lat = ( lat > 500 ) ? 500 : lat;

			// calculate the added distance
			attackreach += ( m_runSpeed * 0.001f ) * float( lat );
		}

		if( static_cast< Player* >( this )->m_isMoving )
		{
			// this only applies to PvP.
			uint32 lat = static_cast< Player* >( this )->GetSession() ? static_cast< Player* >( this )->GetSession()->GetLatency() : 0;

			// if we're over 500 get fucked anyway.. your gonna lag! and this stops cheaters too
			lat = ( lat > 500) ? 500 : lat;

			// calculate the added distance
			attackreach += ( m_runSpeed * 0.001f ) * float( lat );
		}
	}
	return ( distance <= attackreach );
}

void Unit::GiveGroupXP(Unit *pVictim, Player *PlayerInGroup)
{
	if(!PlayerInGroup) 
		return;
	if(!pVictim) 
		return;
	if(!PlayerInGroup->InGroup()) 
		return;
	Group *pGroup = PlayerInGroup->GetGroup();
	uint32 xp;
	if(!pGroup) 
		return;

	//Get Highest Level Player, Calc Xp and give it to each group member
	Player *pHighLvlPlayer = NULL;
	Player *pGroupGuy = NULL;
	  int active_player_count=0;
	Player *active_player_list[MAX_GROUP_SIZE_RAID];//since group is small we can afford to do this ratehr then recheck again the whole active player set
	int total_level=0;
	float xp_mod = 1.0f;

/*	if(pGroup->GetGroupType() == GROUP_TYPE_RAID)
	{   //needs to change
		//Calc XP
		xp = CalculateXpToGive(pVictim, PlayerInGroup);
		xp /= pGroup->MemberCount();

		GroupMembersSet::iterator itr;
		for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++)
		{
			for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				if((*itr)->getLevel() < sWorld.LevelCap)
					(*itr)->GiveXP(xp, pVictim->GetGUID(), true);
			}
		}
	}
	else if(pGroup->GetGroupType() == GROUP_TYPE_PARTY) */
	//change on 2007 04 22 by Zack
	//we only take into count players that are near us, on same map
	GroupMembersSet::iterator itr;
	pGroup->Lock();
	for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++) {
		for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
		{
			pGroupGuy = (*itr)->m_loggedInPlayer;
			if( pGroupGuy && 
				pGroupGuy->isAlive() && 
//				PlayerInGroup->GetInstanceID()==pGroupGuy->GetInstanceID() &&
				pVictim->GetMapMgr() == pGroupGuy->GetMapMgr() && 
				pGroupGuy->GetDistanceSq(pVictim)<100*100
				)
			{
				active_player_list[active_player_count]=pGroupGuy;
				active_player_count++;
				total_level += pGroupGuy->getLevel();
				if(pHighLvlPlayer)
				{
					if(pGroupGuy->getLevel() > pHighLvlPlayer->getLevel())
						pHighLvlPlayer = pGroupGuy;
				}
				else 
					pHighLvlPlayer = pGroupGuy;
			}
		}
	}
	pGroup->Unlock();
	if(active_player_count<1) //killer is always close to the victim. This should never execute
	{
		if(PlayerInGroup == 0)
		{
			PlayerInfo * pleaderinfo = pGroup->GetLeader();
			if(!pleaderinfo->m_loggedInPlayer)
				return;

			PlayerInGroup = pleaderinfo->m_loggedInPlayer;
		}

		xp = CalculateXpToGive(pVictim, PlayerInGroup);
		PlayerInGroup->GiveXP(xp, pVictim->GetGUID(), true);
	}
	else
	{
		if( pGroup->GetGroupType() == GROUP_TYPE_PARTY)
		{
			if(active_player_count==3)
				xp_mod=1.1666f;
			else if(active_player_count==4)
				xp_mod=1.3f;
			else if(active_player_count==5)
				xp_mod=1.4f;
			else xp_mod=1;//in case we have only 2 members ;)
		}
		else if(pGroup->GetGroupType() == GROUP_TYPE_RAID)
			xp_mod=0.5f;

		if(pHighLvlPlayer == 0)
		{
			PlayerInfo * pleaderinfo = pGroup->GetLeader();
			if(!pleaderinfo->m_loggedInPlayer)
				return;

			pHighLvlPlayer = pleaderinfo->m_loggedInPlayer;
		}

		xp = CalculateXpToGive(pVictim, pHighLvlPlayer);
		//i'm not sure about this formula is correct or not. Maybe some brackets are wrong placed ?
		for(int i=0;i<active_player_count;i++)
			active_player_list[i]->GiveXP( float2int32(((xp*active_player_list[i]->getLevel()) / total_level)*xp_mod), pVictim->GetGUID(), true );
	}
		/* old code start before 2007 04 22
		GroupMembersSet::iterator itr;
		for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++)
		{
			for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				pGroupGuy = (*itr);
				if(pGroupGuy)
				{
					if(pHighLvlPlayer)
					{
						if(pGroupGuy->getLevel() > pHighLvlPlayer->getLevel())
						{
							pHighLvlPlayer = pGroupGuy;
						}
					}
					else
						pHighLvlPlayer = pGroupGuy;
				}
			}
		}

		//Calc XP
		xp = CalculateXpToGive(pVictim, pHighLvlPlayer);
		uint32 giveXP = 0;

		for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++)
		{
			for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				pGroupGuy = (*itr);
				giveXP = xp * pGroupGuy->getLevel() / (pHighLvlPlayer->getLevel() + pGroupGuy->getLevel());
				if(pGroupGuy->getLevel() < sWorld.LevelCap)
					pGroupGuy->GiveXP(giveXP, pVictim->GetGUID(), true);
			}
		}
	}*/
}

void Unit::HandleProc( uint32 flag, Unit* victim, SpellEntry* CastingSpell, uint32 dmg, uint32 abs , uint32 weapon_damage_type)
{
	++m_procCounter;
	bool can_delete = !bProcInUse; //if this is a nested proc then we should have this set to TRUE by the father proc
	bProcInUse = true; //locking the proc list

	std::list< uint32 > remove;
	std::list< struct ProcTriggerSpell >::iterator itr,itr2;
	for( itr = m_procSpells.begin(); itr != m_procSpells.end(); )  // Proc Trigger Spells for Victim
	{
		itr2 = itr;
		++itr;
		if( itr2->deleted )
		{
			if( can_delete )
				m_procSpells.erase( itr2 );
			continue;
		}

		uint32 origId = itr2->origId;
		if( CastingSpell != NULL )
		{
			//this is to avoid spell proc on spellcast loop. We use dummy that is same for both spells
			//if( CastingSpell->Id == itr2->spellId )
			if( CastingSpell->Id == itr2->origId || CastingSpell->Id == itr2->spellId )
			{
				//printf("WOULD CRASH HERE ON PROC: CastingId: %u, OrigId: %u, SpellId: %u\n", CastingSpell->Id, itr2->origId, itr2->spellId);
				continue;
			}
		}
		SpellEntry* ospinfo = dbcSpell.LookupEntry( origId );//no need to check if exists or not since we were not able to register this trigger if it would not exist :P
		
		//this requires some specific spell check,not yet implemented
		if( itr2->procFlags & flag )
		{
			if(itr2->weapon_damage_type > 0 && itr2->weapon_damage_type < 3 && 
				itr2->weapon_damage_type != weapon_damage_type)
					continue; // This spell should proc only from other hand attacks

			uint32 spellId = itr2->spellId;
			if( itr2->procFlags & PROC_ON_CAST_SPECIFIC_SPELL )
			{

				if( CastingSpell == NULL )
					continue;
				
				//this is wrong, dummy is too common to be based on this, we should use spellgroup or something
				SpellEntry* sp = dbcSpell.LookupEntry( spellId );
				if( sp->dummy != CastingSpell->dummy )
				{
					if( !ospinfo->School )
						continue;
					if( ospinfo->School != CastingSpell->School )
						continue;
					if( CastingSpell->EffectImplicitTargetA[0] == 1 || 
						CastingSpell->EffectImplicitTargetA[1] == 1 || 
						CastingSpell->EffectImplicitTargetA[2] == 1) //Prevents school based procs affecting caster when self buffing
						continue;
				}
				else
					if( sp->dummy == 1 )
						continue;
			}

			uint32 proc_Chance = itr2->procChance;
			SpellEntry* spe  = dbcSpell.LookupEntry( spellId );

			// feral = no procs (need a better way to do this)
			/*if( this->IsPlayer() && static_cast<Player*>(this)->GetShapeShift() )
			{
				if( spe->NameHash == SPELL_HASH_LIGHTNING_SPEED ) // mongoose
					continue;
				else if( spe->NameHash == SPELL_HASH_HOLY_STRENGTH ) //crusader
					continue;
			}*/
			//Custom procchance modifications based on equipped weapon speed.
			if( this->IsPlayer() && spe != NULL && (
				spe->NameHash == SPELL_HASH_MAGTHERIDON_MELEE_TRINKET || 
				spe->NameHash == SPELL_HASH_ROMULO_S_POISON || 
				spe->NameHash == SPELL_HASH_BLACK_TEMPLE_MELEE_TRINKET || 
				spe->NameHash == SPELL_HASH_FROSTBRAND_ATTACK || spellId == 16870  || spellId == 31803) )
			{
				float ppm = 1.0f;
				switch( spe->NameHash )
				{
					case SPELL_HASH_MAGTHERIDON_MELEE_TRINKET:
						ppm = 1.5f;
						break; // dragonspine trophy
					case SPELL_HASH_ROMULO_S_POISON:
						ppm = 1.5f;
						break; // romulo's
					case SPELL_HASH_BLACK_TEMPLE_MELEE_TRINKET:
						ppm = 1.0f;
						break; // madness of the betrayer
					case SPELL_HASH_FROSTBRAND_ATTACK:
						ppm = 9.0f;
						break; // Frostbrand Weapon
				}
				switch( spellId )
				{
					case 16870:
						ppm = 2.0f;
						break; //druid: clearcasting
					case 31803:
						ppm = 20.0f;
						break; //paladin: Holy Vengeance
				}

				/*Item * mh = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
				Item * of = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
				
				if( mh != NULL && of != NULL )
				{
					float mhs = float( mh->GetProto()->Delay );
					float ohs = float( of->GetProto()->Delay );
					proc_Chance = FL2UINT( ( mhs + ohs ) * 0.001f * ppm / 0.6f );
				}
				else if( mh != NULL )
				{
					float mhs = float( mh->GetProto()->Delay );
					proc_Chance = float2int32( mhs * 0.001f * ppm / 0.6f );
				}
				else
					proc_Chance = 0;*/
				Item *weapon = NULL;
				if(static_cast< Player* >( this )->GetItemInterface())
				{
					if(weapon_damage_type == 1)
						weapon = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
					else if(weapon_damage_type == 2)
						weapon = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
				}
				if(weapon && weapon->GetProto())
				{
					float speed = float( weapon->GetProto()->Delay );
					proc_Chance = float2int32( speed * 0.001f * ppm / 0.6f );
				}

				if( static_cast< Player* >( this )->IsInFeralForm() )
				{
					if( static_cast< Player* >( this )->GetShapeShift() == FORM_CAT )
					{
						proc_Chance = FL2UINT( ppm / 0.6f );
					}
					else if( static_cast< Player* >( this )->GetShapeShift() == FORM_BEAR || static_cast< Player* >( this )->GetShapeShift() == FORM_DIREBEAR )
					{
						proc_Chance = FL2UINT( ppm / 0.24f );
					}
				}
			}

			SM_FIValue( SM_FChanceOfSuccess, (int32*)&proc_Chance, ospinfo->SpellGroupType );
			if( spellId && Rand( proc_Chance ) )
			{
				SpellCastTargets targets;
				if( itr2->procFlags & PROC_TARGET_SELF )
					targets.m_unitTarget = GetGUID();
				else 
					targets.m_unitTarget = victim->GetGUID();
				/* hmm whats a reasonable value here */
				if( m_procCounter > 40 )
				{
					/* something has proceed over 10 times in a loop :/ dump the spellids to the crashlog, as the crashdump will most likely be useless. */
					// BURLEX FIX ME!
					//OutputCrashLogLine("HandleProc %u SpellId %u (%s) %u", flag, spellId, sSpellStore.LookupString(sSpellStore.LookupEntry(spellId)->Name), m_procCounter);
					return;
				}

				//check if we can trigger due to time limitation
				if( ospinfo->proc_interval )
				{
					uint32 now_in_ms=getMSTime();
					if( itr2->LastTrigger + ospinfo->proc_interval > now_in_ms )
						continue; //we can't trigger it yet.
					itr2->LastTrigger = now_in_ms; // consider it triggered
				}
				//since we did not allow to remove auras like these with interrupt flag we have to remove them manually.
				if( itr2->procFlags & PROC_REMOVEONUSE )
					RemoveAura( origId );
				int dmg_overwrite = 0;

				//these are player talents. Fuckem they pull the emu speed down 
				if( IsPlayer() )
				{
					uint32 talentlevel = 0;
					switch( origId )
					{
						//mace specialization
						case 12284:	{talentlevel = 1;}break;
						case 12701:	{talentlevel = 2;}break;
						case 12702:	{talentlevel = 3;}break;
						case 12703:	{talentlevel = 4;}break;
						case 12704:	{talentlevel = 5;}break;

						//Unbridled Wrath
						case 12999:	{talentlevel = 1;}break;
						case 13000:	{talentlevel = 2;}break;
						case 13001:	{talentlevel = 3;}break;
						case 13002:	{talentlevel = 4;}break;
					}

					switch( spellId )
					{
						case 14189: //Seal Fate
						case 16953: //Blood Frenzy
						{
							if( !this->IsPlayer() || 
								!CastingSpell || 
								CastingSpell->Id == 14189 ||
								CastingSpell->Id == 16953 )
								continue;
							if( CastingSpell->Effect[0] != 80 &&
								CastingSpell->Effect[1] != 80 &&
								CastingSpell->Effect[2] != 80 &&
								CastingSpell->NameHash != SPELL_HASH_MANGLE__CAT_ )
								continue;
						}break;
						case 17106: //druid intencity
						{
							if( CastingSpell->Id != 5229 )//enrage
								continue;
						}break;
						case 31616:
						{
							//yep, another special case: Nature's grace
							if( GetHealthPct() > 30 )
								continue;
						}break;
						case 37309:
						{
							if( !this->IsPlayer() )
								continue;
							if( static_cast< Player* >( this )->GetShapeShift() != FORM_BEAR ||
								static_cast< Player* >( this )->GetShapeShift() != FORM_DIREBEAR )
								continue;
						}break;
						case 37310:
						{
							if( !this->IsPlayer() || static_cast< Player* >( this )->GetShapeShift() != FORM_CAT )
								continue;
						}break;
                        case 34754: //holy concentration
                        {

							if( CastingSpell->NameHash != SPELL_HASH_FLASH_HEAL &&
								CastingSpell->NameHash != SPELL_HASH_BINDING_HEAL &&
								CastingSpell->NameHash != SPELL_HASH_GREATER_HEAL )
								continue;
						}break;
						case 5530:
						{
							//warrior/rogue mace specialization can trigger only when using maces
							Item* it;
							if(weapon_damage_type < 1 || weapon_damage_type > 2)
									continue;
							if( static_cast< Player* >( this )->GetItemInterface() )
							{
								it = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND + weapon_damage_type - 1 );
								if( it != NULL && it->GetProto() )
								{
									uint32 reqskill = GetSkillByProto( it->GetProto()->Class, it->GetProto()->SubClass );
									if( reqskill != SKILL_MACES && reqskill != SKILL_2H_MACES )
										continue;
								}
								else
									continue; //no weapon no joy
							}
							else
								continue; //no weapon no joy
							//let's recalc chance to cast since we have a full 100 all time on this one
							//how lame to get talentpointlevel for this spell :(
							//float chance=it->GetProto()->Delay*100*talentlevel/60000;
							float chance = float( it->GetProto()->Delay ) * float( talentlevel ) / 600.0f;
							if( !Rand( chance ) )
								continue;
						}break;
						case 16459:
						{
							//sword specialization
							if( static_cast< Player* >( this )->GetItemInterface())
							{
								if(weapon_damage_type < 1 || weapon_damage_type > 2)
									continue;
								Item* it = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND + weapon_damage_type - 1 );
								if( it != NULL && it->GetProto() )
								{
									uint32 reqskill=GetSkillByProto( it->GetProto()->Class, it->GetProto()->SubClass );
									if( reqskill != SKILL_SWORDS && reqskill != SKILL_2H_SWORDS )
										continue;
								}
								else
									continue; //no weapon no joy
							}
							else
								continue; //no weapon no joy
						}break;
						case 12721:
						{
							//deep wound requires a melee weapon
							Item* it;
							if( static_cast< Player* >( this )->GetItemInterface())
							{
								it = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
								if( it != NULL && it->GetProto() )
								{
									//class 2 means weapons ;)
									if( it->GetProto()->Class != 2 )
										continue;
								}
								else continue; //no weapon no joy
							}
							else continue; //no weapon no joy
						}break;
						//warrior - Blood Frenzy
						case 30069:
						case 30070:
						{
							if( CastingSpell == NULL )
								continue;
								if( CastingSpell->NameHash != SPELL_HASH_REND && 
									CastingSpell->NameHash != SPELL_HASH_DEEP_WOUNDS )
									continue;
						}break;
						//warrior - Unbridled Wrath
						case 12964:
						{
							//let's recalc chance to cast since we have a full 100 all time on this one
							Item* it;
							if( static_cast< Player* >( this )->GetItemInterface() )
							{
								it = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
								if( !( it != NULL && it->GetProto() ) )
									continue; //no weapon no joy
							}
							else
								continue; //no weapon no joy
							//float chance=float(it->GetProto()->Delay)*float(talentlevel)/600.0f;
							float chance = float( it->GetProto()->Delay ) * float(talentlevel ) / 300.0f; //zack this had a very low proc rate. Kinda liek a waisted talent
							uint32 myroll = RandomUInt( 100 );
							if( myroll > chance )
								continue;
						}break;
/*						//disabled by zack until finished : this needs to get trigered on trap trigger and not trap cast
						// hunter - Entrapment
						case 19185:
						{
							if( CastingSpell == NULL )
								continue;
								//only trigger effect for specified spells
								if( CastingSpell->NameHash!=SPELL_HASH_BACKSTAB && //immolation trap
									CastingSpell->NameHash!=SPELL_HASH_SINISTER_STRIKE && //frost trap
									CastingSpell->NameHash!=SPELL_HASH_SHIV && //shiv
									CastingSpell->NameHash!=SPELL_HASH_GOUGE ) //gouge
									continue;
						}break;*/
						// Mage ignite talent only for fire dmg
						case 12654:
						{
							if( CastingSpell == NULL )
								continue;
							if( CastingSpell->School != SCHOOL_FIRE )
								continue;
						}break;
						//rogue - blade twisting
						case 31125:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								if( CastingSpell->NameHash != SPELL_HASH_BACKSTAB && //backstab
									CastingSpell->NameHash != SPELL_HASH_SINISTER_STRIKE && //sinister strike
									CastingSpell->NameHash != SPELL_HASH_SHIV && //shiv
									CastingSpell->NameHash != SPELL_HASH_GOUGE ) //gouge
									continue;
							}break;
						//warlock - Improved Shadow Bolt
						case 17794:
						case 17798:
						case 17797:
						case 17799:
						case 17800:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								if( CastingSpell->NameHash!=SPELL_HASH_SHADOW_BOLT)//shadow bolt								
									continue;
							}break;
						// warlock - Improved Drain Soul
						case 18371:
							{
								//null check was made before like 2 times already :P
								dmg_overwrite = ( ospinfo->EffectBasePoints[2] + 1 ) * GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) / 100;
							}break;
						// warlock - Unstable Affliction
						case 43523:
							{
								//null check was made before like 2 times already :P
								dmg_overwrite = ( ospinfo->EffectBasePoints[0] + 1 ) * 9;
							}break;
						//warlock soul link
						case 25228:
							{
								//we need a pet for this, else we do not trigger it at all
								if( IsPlayer() )
									continue;
								Unit* new_caster;
								if( static_cast< Player* >( this )->GetSummon() )
									new_caster = static_cast< Player* >( this )->GetSummon();
								else if( GetUInt64Value( UNIT_FIELD_CHARM ) )
									new_caster = GetMapMgr()->GetUnit( GetUInt64Value( UNIT_FIELD_CHARM ) );
								else
									new_caster = NULL;
								if( new_caster != NULL && new_caster->isAlive() )
								{
									SpellEntry* spellInfo = dbcSpell.LookupEntry( 25228 ); //we already modified this spell on server loading so it must exist
									Spell* spell = new Spell( new_caster, spellInfo, true, NULL );
									spell->forced_basepoints[0] = dmg;
									SpellCastTargets targets;
									targets.m_unitTarget = GetGUID();
									spell->prepare( &targets );
								}
								continue;
							}break;
						//warlock - Nighfall
						case 17941:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								if( CastingSpell->NameHash != SPELL_HASH_CORRUPTION && //Corruption
									CastingSpell->NameHash != SPELL_HASH_DRAIN_LIFE )//Drain Life								
									continue;
							}break;
/*                        //warlock - Demonic Knowledge
                        case 39576:
                            {
                                if( CastingSpell == NULL )
                                    continue;
                                if( CastingSpell->Effect[0] != 56 )
                                    continue;
                                Pet* ps = static_cast< Player* >( this )->GetSummon();
                                if( ps == NULL)
                                    return;//no pet
                                int32 val;
                                SpellEntry *parentproc= dbcSpell.LookupEntry( origId );
                                val = parentproc->EffectBasePoints[0] + 1;
                                val = val * (ps->GetUInt32Value( UNIT_FIELD_STAT2 ) + ps->GetUInt32Value( UNIT_FIELD_STAT3 ) );
                                SpellEntry *spellInfo = dbcSpell.LookupEntry( 39576 );
                                Spell *spell = new Spell( this, spellInfo ,true, NULL );
                                spell->forced_basepoints[0] = ( val / 100 );
                                SpellCastTargets targets;
                                targets.m_unitTarget = GetGUID();
                                spell->prepare( &targets );
                                continue;
                            }break;*/
						//mage - Arcane Blast proc
						case 36032:
							{
								if( CastingSpell == NULL )
									continue;
								if( CastingSpell->NameHash != SPELL_HASH_ARCANE_BLAST ) //Arcane Blast
									continue;
							}break;
						//warlock - Shadow Embrace
						case 32386:
						case 32388:
						case 32389:
						case 32390:
						case 32391:
							{
								if( CastingSpell == NULL )
									continue;
								else
								{
									if( CastingSpell->NameHash != SPELL_HASH_FIRE_SHIELD_II && // Corruption
										CastingSpell->NameHash != SPELL_HASH_CURSE_OF_AGONY && //CoA
										CastingSpell->NameHash != SPELL_HASH_SIPHON_LIFE && //Siphon Life
										CastingSpell->NameHash != SPELL_HASH_SEED_OF_CORRUPTION ) //SoC
										continue;
								}
							}break;
						//warlock - Aftermath
						case 18118:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								skilllinespell* skillability = objmgr.GetSpellSkill(CastingSpell->Id);
								if( !skillability )
									continue;
								if( skillability->skilline != SKILL_DESTRUCTION )
									continue;
							}break;
						//warlock - Nether Protection
						case 30300:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
									continue;
								if( CastingSpell->School!=SCHOOL_FIRE &&
									CastingSpell->School!=SCHOOL_SHADOW)
									continue;
							}break;
						//warlock - Soul Leech
						//this whole spell should get rewriten. Uses bad formulas, bad trigger method, spell is rewriten ...
						case 30294:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								uint32 amount;
								switch( CastingSpell->NameHash )
								{
									case SPELL_HASH_SHADOW_BOLT: //Shadow Bolt
									case SPELL_HASH_SOUL_FIRE: //Soul Fire
									case SPELL_HASH_INCINERATE: //Incinerate
									case SPELL_HASH_SEARING_PAIN: //Searing Pain
									case SPELL_HASH_CONFLAGRATE: //Conflagrate
									{
										amount = CastingSpell->EffectBasePoints[0]+1;
									}break;
									case SPELL_HASH_SHADOWBURN: //Shadowburn
									{
										amount = CastingSpell->EffectBasePoints[1]+1;
									}break;
									default:
										amount=0;
								}
								if(!amount)
									continue;
								SpellEntry *spellInfo = dbcSpell.LookupEntry(spellId );
								if(!spellInfo)
									continue;
								Spell *spell = new Spell(this, spellInfo ,true, NULL);
								spell->SetUnitTarget(this);
								spell->Heal(amount*(ospinfo->EffectBasePoints[0]+1)/100);
								delete spell;
								continue;
							}break;
						//warlock - pyroclasm
						case 18093:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								if( CastingSpell->NameHash != SPELL_HASH_RAIN_OF_FIRE && //Rain of Fire
									CastingSpell->NameHash != SPELL_HASH_HELLFIRE_EFFECT && //Hellfire
									CastingSpell->NameHash != SPELL_HASH_SOUL_FIRE ) //Soul Fire
									continue;
							}break;
						//mage - Improved Scorch
						case 22959:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								if( CastingSpell->NameHash != SPELL_HASH_SCORCH ) //Scorch
									continue;
							}break;
						//mage - Combustion
						case 28682:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING)
									|| CastingSpell->School != SCHOOL_FIRE )
									continue;
								if( flag & PROC_ON_SPELL_CRIT_HIT )
								{
									itr2->procCharges++;
									if( itr2->procCharges >= 3 ) //whatch that number cause it depends on original stack count !
									{
										RemoveAllAuraByNameHash( SPELL_HASH_COMBUSTION );
										RemoveAllAuraByNameHash( SPELL_HASH_COMBUSTION_PROC );
									}
									continue;
								}
							}break;
						//priest - Misery
						case 33200:
						case 33199:
						case 33198:
						case 33197:
						case 33196:
							{
								if( CastingSpell == NULL )
									continue;
								else
								{
									if( CastingSpell->NameHash != SPELL_HASH_MIND_FLAY && // Mind Flay
										CastingSpell->NameHash != SPELL_HASH_SHADOW_WORD__PAIN && //SW:P
										CastingSpell->NameHash != SPELL_HASH_VAMPIRIC_TOUCH ) //SoC
										continue;
								}
							}break;
						//priest - Shadow Weaving
						case 15258:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								if( CastingSpell->School != SCHOOL_SHADOW || !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) ) //we need damaging spells for this, so we suppose all shadow spells casted on target are dmging spells = Wrong
									continue;
							}break;
						//priest - Inspiration
						case 15363:
						case 14893:
						case 15357:
							{
								if( !CastingSpell || !( CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) )
									continue;
							}
							break;
						//priest - Blessed Recovery
                        case 27813:
                        case 27817:
                        case 27818:
                            {
                                if(!IsPlayer() || !dmg)
                                    continue;
                                SpellEntry *parentproc= dbcSpell.LookupEntry(origId);
                                SpellEntry *spellInfo = dbcSpell.LookupEntry(spellId);
								if (!parentproc || !spellInfo)
									continue;
								int32 val = parentproc->EffectBasePoints[0] + 1;
                                Spell *spell = new Spell(this, spellInfo ,true, NULL);
                                spell->forced_basepoints[0] = (val*dmg)/300; //per tick
                                SpellCastTargets targets;
                                targets.m_unitTarget = GetGUID();
                                spell->prepare(&targets);
                                continue;
                            }break;
						//shaman - Healing Way
						case 29203:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								if( CastingSpell->NameHash != SPELL_HASH_HEALING_WAVE ) //healing wave
									continue;
							}break;
						//shaman - Elemental Devastation
						case 29177:
						case 29178:
						case 30165:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								if( !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING)) //healing wave
									continue;
							}break;
						//shaman - Elemental Focus - Clearcasting
						case 16246:
							{
								if(origId == 39805)
									continue; // Lightning Overload Proc is already free
								if(CastingSpell->NameHash != SPELL_HASH_LIGHTNING_BOLT &&
									CastingSpell->NameHash != SPELL_HASH_CHAIN_LIGHTNING &&
									CastingSpell->NameHash != SPELL_HASH_EARTH_SHOCK &&
									CastingSpell->NameHash != SPELL_HASH_FLAME_SHOCK &&
									CastingSpell->NameHash != SPELL_HASH_FROST_SHOCK)
									continue;
							}break;
						//shaman - windfury weapon
						case 8232:
						case 8235:
						case 10486:
						case 16362:
						case 25505:
							{
								if(!IsPlayer() || weapon_damage_type < 1 || weapon_damage_type > 2)
									continue;
								Item * mh = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND + weapon_damage_type -1);
								if( mh == NULL)
									continue;
								float mhs = float( mh->GetProto()->Delay );
								// Calculate extra AP bonus damage
								uint32 extra_dmg=float2int32(mhs * (ospinfo->EffectBasePoints[0]+1) /14000.0f);
								Strike( victim, weapon_damage_type-1, spe, extra_dmg, 0, 0, false, false );
								Strike( victim, weapon_damage_type-1, spe, extra_dmg, 0, 0, false, false );
								spellId = 33010; // WF animation
							}break;
						//rogue - Ruthlessness
						case 14157:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//we need a finishing move for this 
								if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE) || victim==this)
									continue;
							}break;
						//rogue - Relentless Strikes
						case 14181:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								int32 proc_Chance;
								//chance is based actually on combopoint count and not 100% always 
								if( CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE && IsPlayer())
									proc_Chance = static_cast< Player* >( this )->m_comboPoints*ospinfo->EffectBasePoints[1];
								else continue;
								if(!Rand(proc_Chance))
									continue;
							}break;
						//rogue - Find Weakness
						case 31234:
						case 31235:
						case 31236:
						case 31237:
						case 31238:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE))
									continue;
							}break;
						//rogue - Initiative
						case 13977:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//we need a Ambush, Garrote, or Cheap Shot
								if( CastingSpell == NULL )
									continue;

								if( CastingSpell->NameHash != SPELL_HASH_CHEAP_SHOT && //Cheap Shot
									CastingSpell->NameHash != SPELL_HASH_AMBUSH && //Ambush
									CastingSpell->NameHash != SPELL_HASH_GARROTE )  //Garrote
									continue;
							}break;
						//Priest - Shadowguard
						case 28377:
						case 28378:
						case 28379:
						case 28380:
						case 28381:
						case 28382:
						case 28385:
							{
								if( CastingSpell && ( this == victim || !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) ) ) //no self casts allowed or beneficial spells
									continue;//we can proc on ranged weapons too
							}break;
						//Priest - blackout
						case 15269:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								if( CastingSpell->School != SCHOOL_SHADOW || !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
									continue;
							}break;
						//warrior - improved berserker rage 
						case 23690:
						case 23691:
							{
								if( !CastingSpell || CastingSpell->NameHash != SPELL_HASH_BERSERKER_RAGE )
									continue;
							}break;
						//mage - Arcane Concentration 
						case 12536:
							{
								//requires damageing spell
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
									continue;
							}break;
						//mage - Improved Blizzard
						case 12484:
						case 12485:
						case 12486:
							{
								if( CastingSpell == NULL )
									continue;
								if( CastingSpell->NameHash != SPELL_HASH_BLIZZARD || victim == this ) //Blizzard
									continue;
							}break;
						//mage - Master of Elements
						case 29077:
							{
								if( CastingSpell == NULL )
									continue;
								if( CastingSpell->School!=SCHOOL_FIRE && CastingSpell->School!=SCHOOL_FROST) //fire and frost criticals
									continue;
								dmg_overwrite = CastingSpell->manaCost * ( ospinfo->EffectBasePoints[0] + 1 ) / 100;
							}break;
						//Hunter - Thrill of the Hunt
						case 34720:
							{
								if( CastingSpell == NULL )
									continue;
								dmg_overwrite = CastingSpell->manaCost * 40 / 100;
							}break;
						//priest - Reflective Shield 
						case 33619:
							{
								//requires Power Word: Shield active
								int power_word_id = HasAurasWithNameHash( SPELL_HASH_POWER_WORD__SHIELD );
								if( !power_word_id )
									continue;//this should not ocur unless we made a fuckup somewhere
								//make a direct strike then exit rest of handler
								int tdmg = abs * ( ospinfo->EffectBasePoints[0] + 1 ) / 100;
								//somehow we should make this not caused any threat (tobedone)
								SpellNonMeleeDamageLog( victim, power_word_id, tdmg, false, true );
								continue;
							}break;
						//rogue - improved sprint
						case 30918:
							{
								if( CastingSpell == NULL )
									continue;
								if( CastingSpell->NameHash != SPELL_HASH_SPRINT || victim != this ) //sprint
									continue;
							}break;
						//rogue - combat potency
						case 35542:
						case 35545:
						case 35546:
						case 35547:
						case 35548:
							{
								if( !IsPlayer() || !dmg )
									continue;
								//this needs offhand weapon
								Item* it = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
								if( it == NULL || it->GetProto()->InventoryType != INVTYPE_WEAPON || weapon_damage_type != 2)
									continue;
							}break;
						//paladin - Seal of Blood
						case 31893:
							{
								//we loose health depending on father of trigger spell when trigering this effect
								int32 healthtoloose = ospinfo->EffectBasePoints[1] * GetUInt32Value( UNIT_FIELD_BASE_HEALTH ) / 100;
								if( healthtoloose > (int32)GetUInt32Value( UNIT_FIELD_HEALTH ) )
									SetUInt32Value( UNIT_FIELD_HEALTH, 1 );
								else
									ModUnsigned32Value( UNIT_FIELD_HEALTH, -healthtoloose );
							}break;
						//paladin - Improved Lay on Hands
						case 20233:
						case 20236:
							{
								if( CastingSpell == NULL )
									continue;
								if( CastingSpell->NameHash != SPELL_HASH_LAY_ON_HANDS )
									continue;
							}break;
						//paladin - Spiritual Attunement
						case 31786:
							{
								if( CastingSpell == NULL )
									continue;
								//trigger only on heal spell cast by NOT us
								if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) || this == victim )
									continue; 
							}break;
						//paladin - Light's Grace
						case 31834:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								if( CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT )
									continue; 
							}break;
						//paladin - Eye for an Eye
						case 25997:
							{
								if( victim == this )
									continue; //not self casted crits
								//requires damageing spell
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
									continue;
								dmg_overwrite = ( dmg *  (ospinfo->EffectBasePoints[0] + 1 )) / 100 ; //only half dmg
								int32 half_health = this->GetUInt32Value(UNIT_FIELD_HEALTH) >> 1;
								if( dmg_overwrite > half_health )
									dmg_overwrite = half_health ;
							}break;
						//paladin - Blessed Life
						case 31828:
							{
								//we should test is damage is from enviroment or not :S
								ModUnsigned32Value(UNIT_FIELD_HEALTH,dmg/2);
								continue; //there is no visual for this ?
							}break;
							//paladin - sanctified judgement
							case 31930:
							{
								//!! not working since we use post even hook and seal disapears before event
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								if(	CastingSpell->NameHash != SPELL_HASH_JUDGEMENT )
									continue;
								if( !IsPlayer() )
									continue; //great, we can only make this for players 
								Player* c = static_cast< Player* >( this );
								//printf("is there a seal on the player ? %u \n",c->Seal);
								if( !c->Seal )
									continue; //how the hack did we manage to cast judgement without a seal ?
								SpellEntry *spellInfo = dbcSpell.LookupEntry( c->Seal ); //null pointer check was already made
								if( !spellInfo )
									continue;	//now this is getting freeky, how the hell did we manage to create this bug ?
								dmg_overwrite = spellInfo->manaCost / 2 ; //only half dmg
								//printf("is there a seal on the player ? %u \n",dmg_overwrite);
							}break;
						//Energized
						case 43751:
							{
								if( CastingSpell == NULL )
									continue;
								if(	CastingSpell->NameHash != SPELL_HASH_LIGHTNING_BOLT )
									continue;
							}break;
						// Resilient
						case 46089:
						case 43839:
						case 43848:
						case 43849:
							{
								if( CastingSpell == NULL )
									continue;
								if(	(origId==46097 || origId==43860 || origId==43861 || origId==43862)&&
									(CastingSpell->NameHash == SPELL_HASH_EARTH_SHOCK || 
									CastingSpell->NameHash == SPELL_HASH_FROST_SHOCK || 
									CastingSpell->NameHash == SPELL_HASH_FLAME_SHOCK))
									break;
								if(	(origId==43859 || origId==43858 || origId==43857 || origId==46096)&&
									CastingSpell->NameHash == SPELL_HASH_STORMSTRIKE)
									break;
							}continue;
						// Totem of the Third Wind
						case 42371:
						case 34132:
						case 46099:
						case 43729:
							{
								if( CastingSpell == NULL )
									continue;
								if(CastingSpell->NameHash != SPELL_HASH_LESSER_HEALING_WAVE)
									continue;
							}break;
						// Ancestral Fortitude
						case 16237:
						case 16177:
						case 16236:
						{
							if( CastingSpell == NULL )
								continue;
							if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) )
								continue;
						}break;
						// Flametongue Totem
						case 25555:
						case 16389:
						case 10523:
						case 8248:
						case 8253:
						// Flametongue Weapon
						case 8026:
						case 8028:
						case 8029:
						case 10445:
						case 16343:
						case 16344:
						case 25488:
						{
							if(spellId == 25555 ||
								spellId == 16389 ||
								spellId == 10523 ||
								spellId == 8248 ||
								spellId == 8253)
									spellId = 16368;	// Flametongue Totem proc
							else
								spellId = 29469;	// Flametongue Weapon proc
							Item * mh = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND + weapon_damage_type - 1 );
				
							if( mh != NULL)
							{
								float mhs = float( mh->GetProto()->Delay );
								dmg_overwrite = FL2UINT( mhs * 0.001f * (spe->EffectBasePoints[0] + 1)/88 );
							}
							else
								continue;
						}break;
						//Spell Haste Trinket
						case 33370:
							{
								if( CastingSpell == NULL )
									continue;
								if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
									continue;
							}break;
						// Fathom-Brooch of the Tidewalker proc
						case 37243:
							{
								if( !CastingSpell )
									continue;
								if( CastingSpell->School != SCHOOL_NATURE )
									continue;
							}break;
						//shaman - Lightning Overload
						case 39805:
							{
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//trigger on lightning and chain lightning. Spell should be identical , well maybe next time :P
								if(	CastingSpell->NameHash == SPELL_HASH_LIGHTNING_BOLT || CastingSpell->NameHash == SPELL_HASH_CHAIN_LIGHTNING )
								{
									spellId = CastingSpell->Id;
									origId = 39805;
									dmg_overwrite = (CastingSpell->EffectBasePoints[0] + 1) / 2; //only half dmg
								}
								else continue;
							}break;
						//item - Band of the Eternal Sage
						case 35084:
							{
								if( CastingSpell == NULL )
									continue;
								if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) ) //requires offensive spell. ! might not cover all spells
									continue;
							}break;
						// druid - Celestial Focus
						case 16922:
							{
								if( CastingSpell == NULL )
									continue;
								if( CastingSpell->NameHash != SPELL_HASH_STARFIRE )
									continue;
							}break;
						case 37565: //setbonus
							{
								if (!CastingSpell || CastingSpell->NameHash != SPELL_HASH_FLASH_HEAL)
									continue;
							}break;
						//SETBONUSES
						case 37379:
							{
								if (!CastingSpell || CastingSpell->School != SCHOOL_SHADOW || !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
									continue;
							}break;
						case 37378:
							{
								if (!CastingSpell || CastingSpell->School != SCHOOL_FIRE || !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
									continue;
							}break;
						case 39950:
							{
								if (!CastingSpell ||  !(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
									continue;
							}break;
						case 37234:
						case 37214:
						case 37601:
							{
								if (!CastingSpell ||  !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
									continue;
							}break;
						case 37237:
							{
								if (!CastingSpell || CastingSpell->NameHash != SPELL_HASH_LIGHTNING_BOLT)
									continue;
							}break;
						case 37193:
							{
								if (!CastingSpell || CastingSpell->NameHash != SPELL_HASH_HOLY_SHIELD)
									continue;
							}break;
						case 37196:
						case 43838:
							{
								if (!CastingSpell)
									continue;
								if (CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_THE_CRUSADER &&
									CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_JUSTICE &&
									CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_LIGHT &&
									CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_WISDOM &&
									CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_RIGHTEOUSNESS &&
									CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_BLOOD &&
									CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_VENGEANCE &&
									CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_COMMAND)
									continue;
							}break;
						case 43837:
							{
								if (!CastingSpell || (CastingSpell->NameHash != SPELL_HASH_FLASH_OF_LIGHT && CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT))
									continue;
							}break;
						case 37529:
							{
								if (!CastingSpell || CastingSpell->NameHash != SPELL_HASH_OVERPOWER)
									continue;
							}break;
						case 37517:
							{
								if (!CastingSpell || CastingSpell->Id == 37517 || CastingSpell->NameHash != SPELL_HASH_REVENGE)
									continue; 
							}break;
						//SETBONUSES END
							//http://www.wowhead.com/?item=32493 Ashtongue Talisman of Shadows
						case 40480:
							{
								if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_CORRUPTION )
									continue; 
							}break;

							//http://www.wowhead.com/?item=32496  Memento of Tyrande
						case 37656: //dont say damaging spell but EACH time spell is casted there is a chance (so can be healing spell)
							{
								if( CastingSpell == NULL )
									continue;
							}break;

							//http://www.wowhead.com/?item=32488 Ashtongue Talisman of Insight
						case 40483:
							{
								if( CastingSpell == NULL )
									continue;
								if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
									continue;
							}break;

							//http://www.wowhead.com/?item=32487 Ashtongue Talisman of Swiftness
						case 40487:
							{
								if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_STEADY_SHOT)
									continue; 
							}break;

							//http://www.wowhead.com/?item=32485 Ashtongue Talisman of Valor
						case 40459:
							{
								if( CastingSpell == NULL || (CastingSpell->NameHash != SPELL_HASH_MORTAL_STRIKE || CastingSpell->NameHash != SPELL_HASH_BLOODTHIRST || CastingSpell->NameHash != SPELL_HASH_SHIELD_SLAM))
									continue; 
							}break;

						//item - Band of the Eternal Restorer 
						case 35087:
							{
								if( CastingSpell == NULL )
									continue;
								if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING)) //requires healing spell.
									continue;
							}break;

							//http://www.wowhead.com/?item=32486 Ashtongue Talisman of Equilibrium
						case 40452: //Mangle has a 40% chance to grant 140 Strength for 8 sec
							{
								if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_MANGLE__BEAR_ || CastingSpell->NameHash != SPELL_HASH_MANGLE__CAT_)
									continue; 
							}break;
						case 40445: //Starfire has a 25% chance to grant up to 150 spell damage for 8 sec
							{
								if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_STARFIRE)
									continue; 
							}break;
						case 40446: //Rejuvenation has a 25% chance to grant up to 210 healing for 8 sec
							{
								if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_REJUVENATION)
									continue; 
							}break;

							//http://www.wowhead.com/?item=32490 Ashtongue Talisman of Acumen
						case 40441: //Each time your Shadow Word: Pain deals damage, it has a 10% chance to grant you 220 spell damage for 10 sec
							{
								if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_SHADOW_WORD__PAIN)
									continue; 
							}break;

							//http://www.wowhead.com/?item=32490 Ashtongue Talisman of Acumen
						case 40440: //Each time your Renew heals, it has a 10% chance to grant you 220 healing for 5 sec
							{
								if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_RENEW)
									continue; 
							}break;

							//http://www.wowhead.com/?item=32492 Ashtongue Talisman of Lethality
						case 40461:
							{
								if( CastingSpell == NULL )
									continue;
								//we need a finishing move for this 
								if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE) || victim==this)
									continue;
							}break;
						case 37445: //using a mana gem grants you 225 spell damage for 15 sec
							{
								if (!CastingSpell || CastingSpell->NameHash != SPELL_HASH_REPLENISH_MANA)
									continue; 
							}break;

/*						//paladin - illumination
						case 18350:
							{
								continue; //disabled until finished
								if( CastingSpell == NULL )
									continue;//this should not ocur unless we made a fuckup somewhere
								//only trigger effect for specified spells
								if( CastingSpell->NameHash!=666 && //Holy light
									CastingSpell->NameHash!=666 && //Flash of light
									CastingSpell->NameHash!=666 ) //Holy shock
									continue;
							}break;*/
					}
				}
				if(spellId==17364 || spellId==32175 || spellId==32176) // Stormstrike fix
					continue;
				if(spellId==22858 && isInBack(victim)) //retatliation needs target to be not in front. Can be casted by creatures too
					continue;
				SpellEntry *spellInfo = dbcSpell.LookupEntry(spellId );
				Spell *spell = new Spell(this, spellInfo ,true, NULL);
				spell->forced_basepoints[0] = dmg_overwrite;
				spell->ProcedOnSpell = CastingSpell;
				//Spell *spell = new Spell(this,spellInfo,false,0,true,false);
				if(spellId==974||spellId==32593||spellId==32594) // Earth Shield handler
				{
					spell->pSpellId = itr2->spellId;
					Player * Caster = NULL;
					if(GET_TYPE_FROM_GUID(itr2->caster) == HIGHGUID_TYPE_PLAYER)
						Caster = GetMapMgr()->GetPlayer( GUID_LOPART(itr2->caster) );
					if(Caster)
					{
						spell->p_caster = Caster;
						spell->u_caster = static_cast< Unit* >( Caster );
					}
					spell->SetUnitTarget( this );
					spell->SpellEffectDummy(0);
					delete spell;
					continue;
				}
				spell->pSpellId=origId;
				spell->prepare(&targets);
			}//not always we have a spell to cast
		}
	}

	m_chargeSpellsInUse=true;
	std::map<uint32,struct SpellCharge>::iterator iter,iter2;
	iter=m_chargeSpells.begin();
	while(iter!= m_chargeSpells.end())
	{
		iter2=iter++;
		if(iter2->second.count)
		{
			if((iter2->second.ProcFlag & flag))
			{
				//Fixes for spells that dont lose charges when dmg is absorbd
				if(iter2->second.ProcFlag==680&&dmg==0) continue;
				if(CastingSpell)
				{

					SpellCastTime *sd = dbcSpellCastTime.LookupEntry(CastingSpell->CastingTimeIndex);
					if(!sd) continue; // this shouldnt happen though :P
					//if we did not proc these then we should not remove them
					if( CastingSpell->Id == iter2->second.spellId)
						continue;
					switch(iter2->second.spellId)
					{
					//Shaman - Shamanistic Focus
					case 43339:
						{
							if( CastingSpell->NameHash != SPELL_HASH_EARTH_SHOCK &&
								CastingSpell->NameHash != SPELL_HASH_FLAME_SHOCK &&
								CastingSpell->NameHash != SPELL_HASH_FROST_SHOCK )
								continue;
						}break;
					case 12043:
						{
							//Presence of Mind and Nature's Swiftness should only get removed
							//when a non-instant and bellow 10 sec. Also must be nature :>
//							if(!sd->CastTime||sd->CastTime>10000) continue;
							if(sd->CastTime==0)
								continue;
						}break;
					case 17116: //Shaman - Nature's Swiftness
					case 16188:
						{
//							if( CastingSpell->School!=SCHOOL_NATURE||(!sd->CastTime||sd->CastTime>10000)) continue;
							if( CastingSpell->School!=SCHOOL_NATURE||(sd->CastTime==0)) continue;
						}break;
					case 16166:
						{
							if(!(CastingSpell->School==SCHOOL_FIRE||CastingSpell->School==SCHOOL_FROST||CastingSpell->School==SCHOOL_NATURE))
								continue;
						}break;
					case 14177: //cold blood will get removed on offensive spell
						{
							if(victim==this || isFriendly(this, victim))
								continue;
						}break;
					}
				}
				if(iter2->second.lastproc!=0)
				{
					if(iter2->second.procdiff>3000)
					{
						//--(iter2->second.count);
						RemoveAura(iter2->second.spellId);
					}
				}
				else
				{
					//--(iter2->second.count);		// done in Aura::Remove
					this->RemoveAura(iter2->second.spellId);
				}
			}
		}
		if(!iter2->second.count)
		{
			m_chargeSpells.erase(iter2);
		}
	}

	for(;!m_chargeSpellRemoveQueue.empty();)
	{
		iter = m_chargeSpells.find(m_chargeSpellRemoveQueue.front());
		if(iter != m_chargeSpells.end())
		{
			if(iter->second.count>1)
				--iter->second.count;
			else
				m_chargeSpells.erase(iter);
		}
		m_chargeSpellRemoveQueue.pop_front();
	}

	m_chargeSpellsInUse=false;
	if(can_delete) //are we the upper level of nested procs ? If yes then we can remove the lock
		bProcInUse = false;
}

//damage shield is a triggered spell by owner to atacker
void Unit::HandleProcDmgShield(uint32 flag, Unit* attacker)
{
	//make sure we do not loop dmg procs
	if(this==attacker || !attacker)
		return;
	if(m_damgeShieldsInUse)
		return;
	m_damgeShieldsInUse = true;
	//charges are already removed in handleproc
	WorldPacket data(24);
	std::list<DamageProc>::iterator i;
	std::list<DamageProc>::iterator i2;
	for(i = m_damageShields.begin();i != m_damageShields.end();)     // Deal Damage to Attacker
	{
		i2 = i++; //we should not proc on proc.. not get here again.. not needed.Better safe then sorry.
		if(	(flag & (*i2).m_flags) )
		{
			if(PROC_MISC & (*i2).m_flags)
			{
				data.Initialize(SMSG_SPELLDAMAGESHIELD);
				data << this->GetGUID();
				data << attacker->GetGUID();
				data << (*i2).m_damage;
				data << (*i2).m_school;
				SendMessageToSet(&data,true);
				this->DealDamage(attacker,(*i2).m_damage,0,0,(*i2).m_spellId);
			}
			else
			{
				SpellEntry	*ability=dbcSpell.LookupEntry((*i2).m_spellId);
				this->Strike( attacker, RANGED, ability, 0, 0, (*i2).m_damage, true, false );
			}
		}
	}
	m_damgeShieldsInUse = false;
}

/*
void Unit::HandleProcSpellOnSpell(Unit* Victim,uint32 damage,bool critical)
{
}
*/
bool Unit::isCasting()
{
	return (m_currentSpell != NULL);
}

bool Unit::IsInInstance()
{
	MapInfo *pMapinfo = WorldMapInfoStorage.LookupEntry(this->GetMapId());
	if(pMapinfo)
		return (pMapinfo->type != INSTANCE_NULL);

	return false;
}

void Unit::RegenerateHealth()
{
	m_H_regenTimer = 2000;//set next regen time 

	if(!isAlive())
		return;

	// player regen
	if(this->IsPlayer())
	{
		// These only NOT in combat
		if(!CombatStatus.IsInCombat())
		{
			static_cast< Player* >( this )->RegenerateHealth(false);
		}
		else
			static_cast< Player* >( this )->RegenerateHealth(true);
	}
	else
	{
		// Only regen health out of combat
		if(!CombatStatus.IsInCombat())
			static_cast<Creature*>(this)->RegenerateHealth();
	}
}

void Unit::RegeneratePower(bool isinterrupted)
{
    // This is only 2000 IF the power is not rage
	if (isinterrupted)
		m_interruptedRegenTime =2000;
	else
		m_P_regenTimer = 2000;//set next regen time 

	if(!isAlive())
		return;

	// player regen
	if(this->IsPlayer())
	{
		uint32 powertype = GetPowerType();
		switch(powertype)
		{
		case POWER_TYPE_MANA:
			static_cast< Player* >( this )->RegenerateMana(isinterrupted);
			break;
		case POWER_TYPE_ENERGY:
			static_cast< Player* >( this )->RegenerateEnergy();
			break;

		case POWER_TYPE_RAGE:
			{
				// These only NOT in combat
				if(!CombatStatus.IsInCombat())
				{
					if (static_cast< Player* >( this )->HasAura(29131))
					{
						m_P_regenTimer = 3000;
						static_cast< Player* >( this )->LoseRage(0);
					}
					else
					{
						m_P_regenTimer = 3000;
						static_cast< Player* >( this )->LoseRage(30);
					}
				}
				else
				{
					if (static_cast< Player* >( this )->HasAura(12296))
					{
						m_P_regenTimer = 3000;
						static_cast< Player* >( this )->LoseRage(-10);
					}
				}

			}break;
		}
		
		/*

		There is a problem here for druids.
		Druids when shapeshifted into bear have 2 power with different regen timers
		a) Mana (which regenerates while shapeshifted
		b) Rage

		Mana has a regen timer of 2 seconds
		Rage has a regen timer of 3 seconds

		I think the only viable way of fixing this is to have 2 different timers
		to check each individual power.

		Atm, mana is being regen at 3 seconds while shapeshifted...

		*/


		// druids regen mana when shapeshifted
		if(getClass() == DRUID && powertype != POWER_TYPE_MANA)
			static_cast< Player* >( this )->RegenerateMana(isinterrupted);
	}
	else
	{
		uint32 powertype = GetPowerType();
		switch(powertype)
		{
		case POWER_TYPE_MANA:
			static_cast<Creature*>(this)->RegenerateMana();
			break;
		case POWER_TYPE_FOCUS:
			static_cast<Creature*>(this)->RegenerateFocus();
			break;
		}
	}
}

double Unit::GetResistanceReducion(Unit *pVictim, uint32 school)
{
	double reduction = 0.0;
	uint32 resistance = pVictim->GetResistance(school);
	if(school == 0) // physical
	{
		float ArmorReduce = 0.0f;
		if(this->IsPlayer())
			ArmorReduce = PowerCostPctMod[0]; //Armor penetration

		if(ArmorReduce >= resistance)		// fully penetrated :O
			return 0;
		
		if(getLevel() < 60) reduction = double(resistance - ArmorReduce) / double(resistance+400+(85*getLevel()));
		else if(getLevel() > 59 && getLevel() < 70) reduction = double(resistance - ArmorReduce) / double(resistance-22167.5+(467.5*getLevel()));
		else reduction = double(resistance - ArmorReduce) / double(resistance+10557.5);
		
	} else { // non-physical
		int32 RResist = float2int32( float(pVictim->GetResistance( school ) + ((pVictim->getLevel() > getLevel()) ? (pVictim->getLevel() - this->getLevel()) * 5 : 0)) - PowerCostPctMod[school] ); 
		reduction = (double)(RResist) / (double)(getLevel() * 5) * 0.75f;
	}
	if(reduction > 0.75) reduction = 0.75;
	else if(reduction < 0) reduction = 0;

	return reduction;
}

void Unit::CalculateResistanceReduction(Unit *pVictim,dealdamage * dmg, SpellEntry* ability)
{
	double reduction = GetResistanceReducion(pVictim, dmg->school_type);
	
	// only for physical or non binary spells
	if(reduction>0 && !(dmg->school_type && ability && Spell::IsBinary(ability)))
		(*dmg).resisted_damage = (uint32)(((*dmg).full_damage)*reduction);
	else 
		(*dmg).resisted_damage=0; 
}

uint32 Unit::GetSpellDidHitResult( Unit* pVictim, uint32 weapon_damage_type, SpellEntry* ability )
{
	Striker* striker = new Striker(this, pVictim, weapon_damage_type, ability, 0, 0, 0, false, false );
	uint32 result = striker->GetSpellDidHitResult();
	delete striker;
	return result;
}

void Unit::Strike( Unit* pVictim, uint32 weapon_damage_type, SpellEntry* ability, int32 add_damage, int32 pct_dmg_mod, uint32 exclusive_damage, bool disable_proc, bool skip_hit_check )
{
	Striker* striker = new Striker(this, pVictim, weapon_damage_type, ability, add_damage, pct_dmg_mod, exclusive_damage, disable_proc, skip_hit_check );
	striker->Deal();
	delete striker;
}	


void Unit::smsg_AttackStop(Unit* pVictim)
{
	if(!pVictim)
		return;

	WorldPacket data(SMSG_ATTACKSTOP, 24);
	if(m_objectTypeId==TYPEID_PLAYER)
	{
		data << pVictim->GetNewGUID();
		data << uint8(0);
		data << uint32(0);
		static_cast< Player* >( this )->GetSession()->SendPacket( &data );
		data.clear();
	}

	data << GetNewGUID();
	data << pVictim->GetNewGUID();
	data << uint32(0);
	SendMessageToSet(&data, true );

	//pVictim->CombatStatus.RemoveAttacker(this, GetGUID()); // Shouldn't get out of combat that easily
	//CombatStatus.RemoveAttackTarget(pVictim);
}

void Unit::smsg_AttackStop(uint64 victimGuid)
{
	WorldPacket data(20);
	data.Initialize( SMSG_ATTACKSTOP );
	data << GetNewGUID();
	FastGUIDPack(data, victimGuid);
	data << uint32( 0 );
	SendMessageToSet(&data, IsPlayer());
}

void Unit::smsg_AttackStart(Unit* pVictim)
{
	if(GetTypeId() != TYPEID_PLAYER) 
		return;

	Player* pThis = static_cast< Player* >( this );

	// Prevent user from ignoring attack speed and stopping and start combat really really fast
	/*if(!isAttackReady())
		setAttackTimer(uint32(0));
	else if(!canReachWithAttack(pVictim))
	{
		setAttackTimer(uint32(500));
		//pThis->GetSession()->OutPacket(SMSG_ATTACKSWING_NOTINRANGE);
	}
	else if(!isInFront(pVictim))
	{
		setAttackTimer(uint32(500));
		//pThis->GetSession()->OutPacket(SMSG_ATTACKSWING_NOTINRANGE);
	}*/

	// Send out ATTACKSTART
	WorldPacket data(SMSG_ATTACKSTART, 16);
	data << GetGUID();
	data << pVictim->GetGUID();
	SendMessageToSet(&data, true);
	sLog.outDebug( "WORLD: Sent SMSG_ATTACKSTART" );

	// FLAGS changed so other players see attack animation
	//	addUnitFlag(UNIT_FLAG_COMBAT);
	//	setUpdateMaskBit(UNIT_FIELD_FLAGS );
	if(pThis->cannibalize)
	{
		sEventMgr.RemoveEvents(pThis, EVENT_CANNIBALIZE);
		pThis->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
		pThis->cannibalize = false;
	}
}

void Unit::AddAura(Aura *aur)
{
#ifdef FLY_MOUNTS_OL_ONLY
	if( m_mapId != 530 )
	{
		for( uint32 i = 0; i < 3; ++i )
		{
			// Can't use flying auras in non-outlands.
			if( aur->GetSpellProto()->EffectApplyAuraName[i] == 208 || aur->GetSpellProto()->EffectApplyAuraName[i] == 207 )
			{
				delete aur;
				return;
			}
		}
	}
#endif

	if( aur->GetSpellProto()->School && SchoolImmunityList[aur->GetSpellProto()->School] )
	{
		delete aur;
		return;
	}

    if( !aur->IsPassive() )
	{
		//uint32 aurName = aur->GetSpellProto()->Name;
		//uint32 aurRank = aur->GetSpellProto()->Rank;
		uint32 maxStack = aur->GetSpellProto()->maxstack;
		if( aur->GetSpellProto()->procCharges > 0 )
			maxStack=aur->GetSpellProto()->procCharges;
		if( IsPlayer() && static_cast< Player* >( this )->stack_cheat )
			maxStack = 999;

		SpellEntry * info = aur->GetSpellProto();
		//uint32 flag3 = aur->GetSpellProto()->Flags3;

		AuraCheckResponse acr;
		WorldPacket data( 21 );
		bool deleteAur = false;

		//check if we already have this aura by this caster -> update duration
		// Nasty check for Blood Fury debuff (spell system based on namehashes is bs anyways)
		if( !info->always_apply )
		{
			uint32 f = 0;
			for( uint32 x = 0; x < MAX_AURAS; x++ )
			{
				if( m_auras[x] )
				{
					if(	m_auras[x]->GetSpellProto()->Id != aur->GetSpellId() && 
						( aur->pSpellId != m_auras[x]->GetSpellProto()->Id ) //if this is a proc spell then it should not remove it's mother : test with combustion later
						)
					{
						// Check for auras by specific type.
						// Check for auras with the same name and a different rank.
						
						if(info->buffType > 0 && m_auras[x]->GetSpellProto()->buffType & info->buffType && maxStack == 0)
							deleteAur = HasAurasOfBuffType(info->buffType, aur->m_casterGuid,0);
						else
						{
							acr = AuraCheck(info->NameHash, info->RankNumber, m_auras[x],aur->GetCaster());
							if(acr.Error == AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT)
								deleteAur = true;
							else if(acr.Error == AURA_CHECK_RESULT_LOWER_BUFF_PRESENT)
							{
								// remove the lower aura
								m_auras[x]->Remove();

								// no more checks on bad ptr
								continue;
							}
						}					   
					}
					else if( m_auras[x]->GetSpellId() == aur->GetSpellId() ) // not the best formula to test this I know, but it works until we find a solution
					{
						if( !aur->IsPositive() && m_auras[x]->m_casterGuid != aur->m_casterGuid && maxStack == 0)
							continue;
						f++;
						//if(maxStack > 1)
						{
							//update duration,the same aura (update the whole stack whenever we cast a new one)
							m_auras[x]->SetDuration(aur->GetDuration());
							sEventMgr.ModifyEventTimeLeft(m_auras[x], EVENT_AURA_REMOVE, aur->GetDuration());
							if(maxStack <= 1)
							{
								m_auras[x]->UpdateModifiers();
								if(this->IsPlayer())
								{
									data.Initialize(SMSG_UPDATE_AURA_DURATION);
									data << (uint8)m_auras[x]->m_visualSlot <<(uint32) aur->GetDuration();
									((Player*)this)->GetSession()->SendPacket(&data);
								}
								
								data.Initialize(SMSG_SET_AURA_SINGLE);
								data << GetNewGUID() << m_auras[x]->m_visualSlot << uint32(m_auras[x]->GetSpellProto()->Id) << uint32(aur->GetDuration()) << uint32(aur->GetDuration());
								SendMessageToSet(&data,false);
							}
						}
						if(maxStack <= f)
						{
							deleteAur = true;
							break;
						}
					}
				}
			}
		}

		if(deleteAur)
		{
			sEventMgr.RemoveEvents(aur);
			delete aur;
			return;
		}
	}
			
	////////////////////////////////////////////////////////
	if(aur->GetSpellProto()->SpellGroupType && m_objectTypeId == TYPEID_PLAYER)
	{
		int32 speedmod=0;
		SM_FIValue(SM_FSpeedMod,&speedmod,aur->GetSpellProto()->SpellGroupType);
		if(speedmod)
		{
			m_speedModifier *= (speedmod / 100.0f + 1);
			UpdateSpeed();
		}
	}
	////////////////////////////////////////////////////////

	if( aur->m_auraSlot != 0xffffffff )
		m_auras[aur->m_auraSlot] = NULL;
	
	aur->m_auraSlot=255;
	aur->ApplyModifiers(true);
	
	if(!aur->IsPassive())
	{	
		aur->AddAuraVisual();
		if(aur->m_auraSlot==255)
		{
			//add to invisible slot
			for(uint32 x=MAX_AURAS;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
			{
				if(!m_auras[x])
				{
					m_auras[x]=aur;
					aur->m_auraSlot=x;
					break;
				}
			}
			if(aur->m_auraSlot == 255)
			{
				sLog.outError("Aura error in active aura. ");
				// for next loop.. lets kill the fucker
				aur->Remove();
				return;
			} 

			// add visual
			AddAuraVisual(aur->GetSpellId(), 1, aur->IsPositive());
		}
		else
		{
			m_auras[aur->m_auraSlot]=aur;
		}
	}
	else
	{
        if((aur->m_spellProto->AttributesEx & 1024))
        {
            aur->AddAuraVisual();
        }
		for(uint32 x=MAX_AURAS;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
		{
			if(!m_auras[x])
			{
				m_auras[x]=aur;
				aur->m_auraSlot=x;
				break;
			}
		}
		if(aur->m_auraSlot==255)
		{
			sLog.outError("Aura error in passive aura. removing. SpellId: %u", aur->GetSpellProto()->Id);
			// for next loop.. lets kill the fucker
			aur->Remove();
			return;
		}
	}

	// We add 500ms here to allow for the last tick in DoT spells. This is a dirty hack, but at least it doesn't crash like my other method.
	// - Burlex
	if(aur->GetDuration() > 0)
	{
		sEventMgr.AddEvent(aur, &Aura::Remove, EVENT_AURA_REMOVE, aur->GetDuration() + 500, 1,
			EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT | EVENT_FLAG_DELETES_OBJECT);
	}

	aur->RelocateEvents();

	// Reaction from enemy AI
	if(!aur->IsPositive() && aur->IsCombatStateAffecting())	  // Creature
	{
		Unit * pCaster = aur->GetUnitCaster();
		if(pCaster && isAlive())
		{
			pCaster->CombatStatus.OnDamageDealt(this);

			if(m_objectTypeId == TYPEID_UNIT)
				m_aiInterface->AttackReaction(pCaster, 1, aur->GetSpellId());
		}
		/*if(isAlive() && CanAgroHash(aur->m_spellProto->NameHash)) //no threat for hunter's mark
		{
			Unit * pCaster = aur->GetUnitCaster();
			if(!pCaster) return;

			addAttacker(pCaster);

			GetAIInterface()->AttackReaction(pCaster, 1, aur->GetSpellId());
		}*/
	}

	if (aur->GetSpellProto()->AuraInterruptFlags & AURA_INTERRUPT_ON_INVINCIBLE)
	{
		Unit * pCaster = aur->GetUnitCaster();
		if(pCaster)
		{
			pCaster->RemoveStealth();
			pCaster->RemoveInvisibility();
			pCaster->RemoveAllAuraByNameHash(SPELL_HASH_ICE_BLOCK);
			pCaster->RemoveAllAuraByNameHash(SPELL_HASH_DIVINE_SHIELD);
			pCaster->RemoveAllAuraByNameHash(SPELL_HASH_BLESSING_OF_PROTECTION);
		}
	}
}

bool Unit::RemoveAura(Aura *aur)
{
	aur->Remove();
	return true;
}

bool Unit::RemoveAura(uint32 spellId)
{//this can be speed up, if we know passive \pos neg
	for(uint32 x=0;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId()==spellId)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAuras(uint32 * SpellIds)
{
	if(!SpellIds || *SpellIds == 0)
		return false;

	uint32 x=0,y;
	bool res = false;
	for(;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
	{
		if(m_auras[x])
		{
			for(y=0;SpellIds[y] != 0;++y)
			{
				if(m_auras[x]->GetSpellId()==SpellIds[y])
				{
					m_auras[x]->Remove();
					res = true;
				}
			}
		}
	}
	return res;
}

bool Unit::RemoveAura(uint32 spellId, uint64 guid)
{   
	for(uint32 x=0;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId()==spellId && m_auras[x]->m_casterGuid == guid)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAuraByNameHash(uint32 namehash)
{
	for(uint32 x=0;x<MAX_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAuraPosByNameHash(uint32 namehash)
{
	for(uint32 x=0;x<MAX_POSITIVE_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAuraNegByNameHash(uint32 namehash)
{
	for(uint32 x=MAX_POSITIVE_AURAS;x<MAX_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAllAuras(uint32 spellId, uint64 guid)
{   
	bool res = false;
	for(uint32 x=0;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId()==spellId)
			{
				if (!guid || m_auras[x]->m_casterGuid == guid)
				{
					m_auras[x]->Remove();
					res = true;
				}
			}
		}
	}
	return res;
}

bool Unit::RemoveAllAuraByNameHash(uint32 namehash)
{
	bool res = false;
	for(uint32 x=0;x<MAX_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				res=true;
			}
		}
	}
	return res;
}

bool Unit::RemoveAllPosAuraByNameHash(uint32 namehash)
{
	bool res = false;
	for(uint32 x=0;x<MAX_POSITIVE_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				res=true;
			}
		}
	}
	return res;
}

bool Unit::RemoveAllNegAuraByNameHash(uint32 namehash)
{
	bool res = false;
	for(uint32 x=MAX_POSITIVE_AURAS;x<MAX_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				res=true;
			}
		}
	}
	return res;
}

void Unit::RemoveNegativeAuras()
{
	for(uint32 x=MAX_POSITIVE_AURAS;x<MAX_AURAS;x++)
	{
		if(m_auras[x])
		{
            if(m_auras[x]->GetSpellProto()->Flags4 & CAN_PERSIST_AND_CASTED_WHILE_DEAD)
                continue;
            else
            {
			    m_auras[x]->Remove();
            }
		}
	}
}

void Unit::RemoveAllAuras()
{
	for(uint32 x=0;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
	{
		if(m_auras[x])
		{
			m_auras[x]->Remove();
		}
	}
}

//ex:to remove morph spells
void Unit::RemoveAllAuraType(uint32 auratype)
{
    for(uint32 x=0;x<MAX_AURAS;x++)
    {
		if(m_auras[x])
		{
			SpellEntry *proto=m_auras[x]->GetSpellProto();
			if(proto->EffectApplyAuraName[0]==auratype || proto->EffectApplyAuraName[1]==auratype || proto->EffectApplyAuraName[2]==auratype)
				RemoveAura(m_auras[x]->GetSpellId());//remove all morph auras containig to this spell (like wolf motph also gives speed)
		}
    }
}

bool Unit::SetAurDuration(uint32 spellId,Unit* caster,uint32 duration)
{
	Aura*aur=FindAura(spellId,caster->GetGUID());
	if(!aur)
		return false;
	aur->SetDuration(duration);
	sEventMgr.ModifyEventTimeLeft(aur, EVENT_AURA_REMOVE, duration);
			
	if(this->IsPlayer())
	{
		WorldPacket data(5);
		data.SetOpcode(SMSG_UPDATE_AURA_DURATION);
		data << (uint8)(aur)->GetAuraSlot() << duration;
		static_cast< Player* >( this )->GetSession()->SendPacket( &data );
	}

	WorldPacket data(SMSG_SET_AURA_SINGLE,21);
	data << GetNewGUID() << aur->m_visualSlot << uint32(spellId) << uint32(duration) << uint32(duration);
	SendMessageToSet(&data,false);
			
	return true;
}

bool Unit::SetAurDuration(uint32 spellId,uint32 duration)
{
	Aura*aur=FindAura(spellId);

	if(!aur) 
		return false;
	

	aur->SetDuration(duration);
	sEventMgr.ModifyEventTimeLeft(aur, EVENT_AURA_REMOVE, duration);
		
	if(this->IsPlayer())
	{
		WorldPacket data(5);
		data.SetOpcode(SMSG_UPDATE_AURA_DURATION);
		data << (uint8)(aur)->GetAuraSlot() << duration;
		static_cast< Player* >( this )->GetSession()->SendPacket( &data );
	}
	WorldPacket data(SMSG_SET_AURA_SINGLE,21);
	data << GetNewGUID() << aur->m_visualSlot << uint32(spellId) << uint32(duration) << uint32(duration);
	SendMessageToSet(&data,false);


	return true;
}


Aura* Unit::FindAuraPosByNameHash(uint32 namehash)
{
	for(uint32 x=0;x<MAX_POSITIVE_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				return m_auras[x];
			}
		}
	}
	return NULL;
}

Aura* Unit::FindAura(uint32 spellId)
{
	for(uint32 x=0;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId()==spellId)
			{
				return m_auras[x];
			}
		}
	}
	return NULL;
}

Aura* Unit::FindAura(uint32 spellId, uint64 guid)
{
	for(uint32 x=0;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId() == spellId && m_auras[x]->m_casterGuid == guid)
			{
				return m_auras[x];
			}
		}
	}
	return NULL;
}

uint32 Unit::GetAuraCount(uint32 spellId)
{
	uint32 count = 0;
	for(uint32 x = 0; x < MAX_AURAS; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->Id == spellId)
		{
			++count;
		}
	}
	return count;
}

void Unit::_UpdateSpells( uint32 time )
{
	/* to avoid deleting the current spell */
	if(m_currentSpell != NULL)
	{
		m_spellsbusy=true;
		m_currentSpell->update(time);
		m_spellsbusy=false;
	}
}

void Unit::castSpell( Spell * pSpell )
{
	// check if we have a spell already casting etc
	if(m_currentSpell && pSpell != m_currentSpell)
	{
		if(m_spellsbusy)
		{
			// shouldn't really happen. but due to spell sytem bugs there are some cases where this can happen.
			sEventMgr.AddEvent(this,&Unit::CancelSpell,m_currentSpell,EVENT_UNK,1,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}
		else
			m_currentSpell->cancel();
	}

	m_currentSpell = pSpell;
	pLastSpell = pSpell->m_spellInfo;
}

int32 Unit::GetSpellDmgBonus(Unit *pVictim, SpellEntry *spellInfo,int32 base_dmg, bool isdot)
{
	int32 plus_damage = 0;
	Unit* caster = this;
	uint32 school = spellInfo->School;

	if( spellInfo->c_is_flags & SPELL_FLAG_IS_NOT_USING_DMG_BONUS )
		return 0;

	if( caster->IsPlayer() )
	{
		for(uint32 a = 0; a < 6; a++)
			plus_damage += float2int32(static_cast< Player* >(caster)->SpellDmgDoneByAttribute[a][school] * float(caster->GetUInt32Value(UNIT_FIELD_STAT0 + a)));
	}
//------------------------------by school---------------------------------------------------
	plus_damage += caster->GetDamageDoneMod(school);
	plus_damage += pVictim->DamageTakenMod[school];
//------------------------------by victim type----------------------------------------------
	if(((Creature*)pVictim)->GetCreatureName() && caster->IsPlayer()&& !pVictim->IsPlayer())
		plus_damage += static_cast< Player* >(caster)->IncreaseDamageByType[((Creature*)pVictim)->GetCreatureName()->Type];
//==========================================================================================
//==============================+Spell Damage Bonus Modifications===========================
//==========================================================================================
//------------------------------by cast duration--------------------------------------------
	float dmgdoneaffectperc = 1.0f;
	if( spellInfo->Dspell_coef_override >= 0 && !isdot )
		plus_damage = float2int32( float( plus_damage ) * spellInfo->Dspell_coef_override );
	else if( spellInfo->OTspell_coef_override >= 0 && isdot )
		plus_damage = float2int32( float( plus_damage ) * spellInfo->OTspell_coef_override );
	else
	{
		//Bonus to DD part
		if( spellInfo->fixed_dddhcoef >= 0 && !isdot )
			plus_damage = float2int32( float( plus_damage ) * spellInfo->fixed_dddhcoef );
		//Bonus to DoT part
		else if( spellInfo->fixed_hotdotcoef >= 0 && isdot )
		{
			plus_damage = float2int32( float( plus_damage ) * spellInfo->fixed_hotdotcoef );
			if( caster->IsPlayer() )
			{
				int durmod = 0;
				SM_FIValue(caster->SM_FDur, &durmod, spellInfo->SpellGroupType);
				plus_damage += float2int32( float( plus_damage * durmod ) / 15000.0f );
			}
		}
		//In case we dont fit in previous cases do old thing
		else
		{
			plus_damage = float2int32( float( plus_damage ) * spellInfo->casttime_coef );
			float td = float( GetDuration( dbcSpellDuration.LookupEntry( spellInfo->DurationIndex ) ));
			if( spellInfo->NameHash == SPELL_HASH_MOONFIRE || spellInfo->NameHash == SPELL_HASH_IMMOLATE || spellInfo->NameHash == SPELL_HASH_ICE_LANCE || spellInfo->NameHash == SPELL_HASH_PYROBLAST )
				plus_damage = float2int32( float( plus_damage ) * float( 1.0f - ( ( td / 15000.0f ) / ( ( td / 15000.0f ) + dmgdoneaffectperc ) ) ) );
		}
	}

	//------------------------------by downranking----------------------------------------------
	//DOT-DD (Moonfire-Immolate-IceLance-Pyroblast)(Hack Fix)

	if(spellInfo->baseLevel > 0 && spellInfo->maxLevel > 0)
	{
		float downrank1 = 1.0f;
		if(spellInfo->baseLevel < 20)
		    downrank1 = 1.0f - (20.0f - float (spellInfo->baseLevel) ) * 0.0375f;
		float downrank2 = ( float(spellInfo->maxLevel + 5.0f) / float(static_cast< Player* >(caster)->getLevel()) );
		if(downrank2 >= 1 || downrank2 < 0)
		        downrank2 = 1.0f;
		dmgdoneaffectperc *= downrank1 * downrank2;
	}
//==========================================================================================
//==============================Bonus Adding To Main Damage=================================
//==========================================================================================
	int32 bonus_damage = float2int32(plus_damage * dmgdoneaffectperc);

	//bonus_damage +=pVictim->DamageTakenMod[school]; Bad copy-past i guess :P
	if(spellInfo->SpellGroupType)
	{
		int penalty_pct=0;
		SM_FIValue(caster->SM_PPenalty, &penalty_pct, spellInfo->SpellGroupType);
		bonus_damage += bonus_damage*penalty_pct/100;
		SM_FIValue(caster->SM_FPenalty, &bonus_damage, spellInfo->SpellGroupType);
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		int spell_flat_modifers=0;
		int spell_pct_modifers=0;
		SM_FIValue(caster->SM_FPenalty,&spell_flat_modifers,spellInfo->SpellGroupType);
		SM_FIValue(caster->SM_PPenalty,&spell_pct_modifers,spellInfo->SpellGroupType);
		if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
			printf("!!!!!spell dmg bonus(p=24) mod flat %d , spell dmg bonus(p=24) pct %d , spell dmg bonus %d, spell group %u\n",spell_flat_modifers,spell_pct_modifers,bonus_damage,spellInfo->SpellGroupType);
#endif
		SM_FIValue(caster->SM_FDamageBonus, &bonus_damage, spellInfo->SpellGroupType);
		int dmg_bonus_pct=0;
		SM_FIValue(caster->SM_PDamageBonus,&dmg_bonus_pct,spellInfo->SpellGroupType);
		bonus_damage += (base_dmg+bonus_damage)*dmg_bonus_pct/100;
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		spell_flat_modifers=0;
		spell_pct_modifers=0;
		SM_FIValue(caster->SM_FDamageBonus,&spell_flat_modifers,spellInfo->SpellGroupType);
		SM_FIValue(caster->SM_PDamageBonus,&spell_pct_modifers,spellInfo->SpellGroupType);
		if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
			printf("!!!!!spell dmg bonus mod flat %d , spell dmg bonus pct %d , spell dmg bonus %d, spell group %u\n",spell_flat_modifers,spell_pct_modifers,bonus_damage,spellInfo->SpellGroupType);
#endif
	}
//------------------------------by school----------------------------------------------
	float summaryPCTmod = caster->GetDamageDonePctMod(school)-1; //value is initialized with 1
	summaryPCTmod += pVictim->DamageTakenPctMod[school]-1;//value is initialized with 1
	summaryPCTmod += caster->DamageDoneModPCT[school];	// BURLEX FIXME
	summaryPCTmod += pVictim->ModDamageTakenByMechPCT[spellInfo->MechanicsType];
	int32 res = (int32)((base_dmg+bonus_damage)*summaryPCTmod + bonus_damage); // 1.x*(base_dmg+bonus_damage) == 1.0*base_dmg + 1.0*bonus_damage + 0.x*(base_dmg+bonus_damage) -> we add the returned value to base damage so we do not add it here (function returns bonus only)
return res;
}

void Unit::InterruptSpell()
{
	if(m_currentSpell)
	{
		//ok wtf is this
		//m_currentSpell->SendInterrupted(SPELL_FAILED_INTERRUPTED);
		//m_currentSpell->cancel();
		if(m_spellsbusy)
		{
			// shouldn't really happen. but due to spell sytem bugs there are some cases where this can happen.
			sEventMgr.AddEvent(this,&Unit::CancelSpell,m_currentSpell,EVENT_UNK,1,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			m_currentSpell=NULL;
		}
		else
			m_currentSpell->cancel();
	}
}

void Unit::DeMorph()
{
	// hope it solves it :)
	uint32 displayid = this->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID);
	this->SetUInt32Value(UNIT_FIELD_DISPLAYID, displayid);
}

void Unit::Emote(EmoteType emote)
{
	if(emote == 0)
		return;

	WorldPacket data(SMSG_EMOTE, 12);
	data << uint32(emote);
	data << this->GetGUID();
	SendMessageToSet (&data, true);
}

void Unit::SendChatMessageToPlayer(uint8 type, uint32 lang, const char *msg, Player *plr)
{
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo *ci = (m_objectTypeId == TYPEID_UNIT) ? ((Creature*)this)->creature_info : NULL;

	if(ci == NULL || plr == NULL)
		return;

	UnitNameLength = strlen((char*)ci->Name) + 1;
	MessageLength = strlen((char*)msg) + 1;

	WorldPacket data(SMSG_MESSAGECHAT, 35 + UnitNameLength + MessageLength);
	data << type;
	data << lang;
	data << GetGUID();
	data << uint32(0);			// new in 2.1.0
	data << uint32(UnitNameLength);
	data << ci->Name;
	data << uint64(0);
	data << uint32(MessageLength);
	data << msg;
	data << uint8(0x00);
	plr->GetSession()->SendPacket(&data);
}

void Unit::SendChatMessageAlternateEntry(uint32 entry, uint8 type, uint32 lang, const char * msg)
{
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo *ci;

	ci = CreatureNameStorage.LookupEntry(entry);
	if(!ci)
		return;

	UnitNameLength = strlen((char*)ci->Name) + 1;
	MessageLength = strlen((char*)msg) + 1;

	WorldPacket data(SMSG_MESSAGECHAT, 35 + UnitNameLength + MessageLength);
	data << type;
	data << lang;
	data << GetGUID();
	data << uint32(0);			// new in 2.1.0
	data << uint32(UnitNameLength);
	data << ci->Name;
	data << uint64(0);
	data << uint32(MessageLength);
	data << msg;
	data << uint8(0x00);
	SendMessageToSet(&data, true);
}

void Unit::SendChatMessage(uint8 type, uint32 lang, const char *msg)
{
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo *ci = (m_objectTypeId == TYPEID_UNIT) ? ((Creature*)this)->creature_info : NULL;

	if(ci == NULL)
		return;

	UnitNameLength = strlen((char*)ci->Name) + 1;
	MessageLength = strlen((char*)msg) + 1;

	WorldPacket data(SMSG_MESSAGECHAT, 35 + UnitNameLength + MessageLength);
	data << type;
	data << lang;
	data << GetGUID();
	data << uint32(0);			// new in 2.1.0
	data << uint32(UnitNameLength);
	data << ci->Name;
	data << uint64(0);
	data << uint32(MessageLength);
	data << msg;
	data << uint8(0x00);
	SendMessageToSet(&data, true);
}

void Unit::WipeHateList()
{ 
	GetAIInterface()->WipeHateList(); 
}
void Unit::ClearHateList()
{
	GetAIInterface()->ClearHateList();
}

void Unit::WipeTargetList() 
{ 
	GetAIInterface()->WipeTargetList(); 
}

void Unit::AddInRangeObject(Object* pObj)
{
	if((pObj->GetTypeId() == TYPEID_UNIT) || (pObj->GetTypeId() == TYPEID_PLAYER))
	{
		if( isHostile( this, (Unit*)pObj ) )
			m_oppFactsInRange.insert(pObj);

		// commented - this code won't work anyway due to objects getting added in range before they are created - burlex
		/*if( GetTypeId() == TYPEID_PLAYER )
		{
			if( static_cast< Player* >( this )->InGroup() )
			{
				if( pObj->GetTypeId() == TYPEID_UNIT )
				{
					if(((Creature*)pObj)->Tagged)
					{
						if( static_cast< Player* >( this )->GetGroup()->HasMember( pObj->GetMapMgr()->GetPlayer( (uint32)((Creature*)pObj)->TaggerGuid ) ) )
						{
							uint32 Flags;
							Flags = ((Creature*)pObj)->m_uint32Values[UNIT_DYNAMIC_FLAGS];
							Flags |= U_DYN_FLAG_TAPPED_BY_PLAYER;
							ByteBuffer buf1(500);
							((Creature*)pObj)->BuildFieldUpdatePacket(&buf1, UNIT_DYNAMIC_FLAGS, Flags);
							static_cast< Player* >( this )->PushUpdateData( &buf1, 1 );
						}
					}
				}
			}
		}		*/
	}

	Object::AddInRangeObject(pObj);
}//427

void Unit::OnRemoveInRangeObject(Object* pObj)
{
	m_oppFactsInRange.erase(pObj);

	if(pObj->GetTypeId() == TYPEID_UNIT || pObj->GetTypeId() == TYPEID_PLAYER)
	{
		/*if(m_useAI)*/

		Unit *pUnit = static_cast<Unit*>(pObj);
		GetAIInterface()->CheckTarget(pUnit);

		if(GetUInt64Value(UNIT_FIELD_CHARM) == pObj->GetGUID())
			if(m_currentSpell)
				m_currentSpell->cancel();

        Object::OnRemoveInRangeObject(pObj);
        if(critterPet == pObj)
		{
			critterPet->SafeDelete();
			critterPet = 0;
		}
	}
    else
    {
        Object::OnRemoveInRangeObject(pObj);
    }
}

void Unit::ClearInRangeSet()
{
	Object::ClearInRangeSet();
}

//Events
void Unit::EventAddEmote(EmoteType emote, uint32 time)
{
	m_oldEmote = GetUInt32Value(UNIT_NPC_EMOTESTATE);
	SetUInt32Value(UNIT_NPC_EMOTESTATE,emote);
	sEventMgr.AddEvent(this, &Creature::EmoteExpire, EVENT_UNIT_EMOTE, time, 1,0);
}

void Unit::EmoteExpire()
{
	SetUInt32Value(UNIT_NPC_EMOTESTATE, m_oldEmote);
	sEventMgr.RemoveEvents(this, EVENT_UNIT_EMOTE);
}


uint32 Unit::GetResistance(uint32 type)
{
	return GetUInt32Value(UNIT_FIELD_RESISTANCES+type);
}

void Unit::MoveToWaypoint(uint32 wp_id)
{
	if(this->m_useAI && this->GetAIInterface() != NULL)
	{
		AIInterface *ai = GetAIInterface();
		WayPoint *wp = ai->getWayPoint(wp_id);
		if(!wp)
		{
			sLog.outString("WARNING: Invalid WP specified in MoveToWaypoint.");
			return;
		}

		ai->m_currentWaypoint = wp_id;
		if(wp->flags!=0)
			ai->m_moveRun = true;
		ai->MoveTo(wp->x, wp->y, wp->z, 0);
	}
}

int32 Unit::GetDamageDoneMod(uint32 school)
{
	if( this->IsPlayer() )
	   return (int32)GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS + school ) - (int32)GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + school );
	else
	   return static_cast< Creature* >( this )->ModDamageDone[school];
}
	
float Unit::GetDamageDonePctMod(uint32 school)
{
   if(this->IsPlayer())
	   return m_floatValues[PLAYER_FIELD_MOD_DAMAGE_DONE_PCT+school];
	else
	   return ((Creature*)this)->ModDamageDonePct[school];
}

void Unit::CalcDamage()
{
	if( IsPlayer() )
		static_cast< Player* >( this )->CalcDamage();
	else
	{
	float r;
	float delta;
	float mult;
	
	float ap_bonus = float(GetAP())/14000.0f;

		float bonus = ap_bonus*GetUInt32Value(UNIT_FIELD_BASEATTACKTIME);
	
		delta = float(((Creature*)this)->ModDamageDone[0]);
		mult = float(((Creature*)this)->ModDamageDonePct[0]);
		r = BaseDamage[0]*mult+delta+bonus;
		// give some diversity to pet damage instead of having a 77-78 damage range (as an example)
		SetFloatValue(UNIT_FIELD_MINDAMAGE,r > 0 ? ( IsPet() ? r * 0.9f : r ) : 0 );
		r = BaseDamage[1]*mult+delta+bonus;
		SetFloatValue(UNIT_FIELD_MAXDAMAGE, r > 0 ? ( IsPet() ? r * 1.1f : r ) : 0 );
	
	//	SetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE,BaseRangedDamage[0]*mult+delta);
	//	SetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE,BaseRangedDamage[1]*mult+delta);
  
	}	
}

//returns absorbed dmg
uint32 Unit::ManaShieldAbsorb(uint32 dmg)
{
	if(!m_manashieldamt)
		return 0;
	//mana shield group->16. the only

	uint32 mana = GetUInt32Value(UNIT_FIELD_POWER1);
	int32 effectbonus = SM_PEffectBonus ? SM_PEffectBonus[16] : 0;

	int32 potential = (mana*50)/((100+effectbonus));
	if(potential>m_manashieldamt)
		potential = m_manashieldamt;

	if((int32)dmg<potential)
		potential = dmg;

	uint32 cost = (potential*(100+effectbonus))/50;

	SetUInt32Value(UNIT_FIELD_POWER1,mana-cost);
	m_manashieldamt -= potential;
	if(!m_manashieldamt)
		RemoveAura(m_manaShieldId);
	return potential;	
}

void Unit::VampiricEmbrace(uint32 dmg,Unit* tgt)
{
	if(!IsPlayer())
		return;//just in case
	int32 perc = 15;
	SM_FIValue(SM_FSPELL_VALUE,&perc,4);
	uint32 heal = (dmg*perc) / 100;
	this->Heal(this,15286,heal);

	SubGroup* pGroup = static_cast< Player* >( this )->GetGroup() ?
		static_cast< Player* >( this )->GetGroup()->GetSubGroup( static_cast< Player* >( this )->GetSubGroup() ) : NULL;

	if( pGroup != NULL )
	{
		GroupMembersSet::iterator itr;
		static_cast< Player* >( this )->GetGroup()->Lock();
		for(itr = pGroup->GetGroupMembersBegin(); itr != pGroup->GetGroupMembersEnd(); ++itr)
		{
			Player *p = (*itr)->m_loggedInPlayer;
			if(!p || p==this || !p->isAlive())
				continue;
			this->Heal(p,15286,heal);
		}
		static_cast< Player* >( this )->GetGroup()->Unlock();
	}

}

// based of vampiric embrace code
void Unit::VampiricTouch(uint32 dmg,Unit* tgt)
{
        if(!IsPlayer() || this->getClass() == WARRIOR || this->getClass() == ROGUE)
                return;//just in case
        
        int32 perc = 5;
        //SM_FIValue(SM_FSPELL_VALUE,&perc,4);
		if(perc*dmg<0)
			return;
        uint32 man = (dmg*perc) / 100;
		this->Energize(this,34919,man,POWER_TYPE_MANA);
    
		SubGroup* pGroup = static_cast< Player* >( this )->GetGroup() ?
			static_cast< Player* >( this )->GetGroup()->GetSubGroup( static_cast< Player* >( this )->GetSubGroup() ) : NULL;

		if( pGroup != NULL )
        {
                GroupMembersSet::iterator itr;
				static_cast< Player* >( this )->GetGroup()->Lock();
                for(itr = pGroup->GetGroupMembersBegin(); itr != pGroup->GetGroupMembersEnd(); ++itr)
                {
                        if(!(*itr)->m_loggedInPlayer || (*itr)->m_loggedInPlayer == this)
                                continue;
                        Player *p = (*itr)->m_loggedInPlayer;
                        if(!p->isAlive() || p->getClass()==WARRIOR || p->getClass() == ROGUE || p==this)
                                continue;
						this->Energize(p,34919,man,POWER_TYPE_MANA);
                }
				static_cast< Player* >( this )->GetGroup()->Unlock();
        }
}

// grep: Remove any AA spells that aren't owned by this player.
//		 Otherwise, if he logs out and in and joins another group,
//		 he'll apply it to them.
/*
void Unit::RemoveAllAreaAuras()
{
	AuraList::iterator itr,it1;
	for(itr = m_auras.begin();itr!=m_auras.end();)
	{
		it1 = itr++;
		if(((*it1)->m_spellProto->Effect[0] == SPELL_EFFECT_APPLY_AREA_AURA ||
			(*it1)->m_spellProto->Effect[1] == SPELL_EFFECT_APPLY_AREA_AURA ||
			(*it1)->m_spellProto->Effect[2] == SPELL_EFFECT_APPLY_AREA_AURA) && (*it1)->GetCaster() != this)
		{
			(*it1)->Remove();
			m_auras.erase(it1);
		} 
	}
}
*/
uint32 Unit::AbsorbDamage( uint32 School, uint32* dmg )
{
	if( dmg == NULL )
		return 0;

	SchoolAbsorb::iterator i, j;
	uint32 abs = 0;
	for( i = Absorbs[School].begin(); i != Absorbs[School].end(); )
	{
		if( (int32)(*dmg) >= (*i)->amt)//remove this absorb
		{
			(*dmg) -= (*i)->amt;
			abs += (*i)->amt;
			j = i++;

			if( i != Absorbs[School].end() )
			{
				while( (*i)->spellid == (*j)->spellid )
				{
					++i;
					if( i == Absorbs[School].end() )
						break;
				}
			}
			
			this->RemoveAura((*j)->spellid); //,(*j)->caster);
			if(!*dmg)//absorbed all dmg
				break;		
		}
		else //absorb full dmg
		{
			abs += *dmg;
			(*i)->amt -= *dmg;
			*dmg=0;
			break;
		}
	}
	
	return abs;
}

bool Unit::setDetectRangeMod(uint64 guid, int32 amount)
{
	int next_free_slot = -1;
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == 0 && next_free_slot == -1)
		{
			next_free_slot = i;
		}
		if(m_detectRangeGUID[i] == guid)
		{
			m_detectRangeMOD[i] = amount;
			return true;
		}
	}
	if(next_free_slot != -1)
	{
		m_detectRangeGUID[next_free_slot] = guid;
		m_detectRangeMOD[next_free_slot] = amount;
		return true;
	}
	return false;
}

void Unit::unsetDetectRangeMod(uint64 guid)
{
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == guid)
		{
			m_detectRangeGUID[i] = 0;
			m_detectRangeMOD[i] = 0;
		}
	}
}

int32 Unit::getDetectRangeMod(uint64 guid)
{
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == guid)
		{
			return m_detectRangeMOD[i];
		}
	}
	return 0;
}

void Unit::SetStandState(uint8 standstate)
{
	SetByte( UNIT_FIELD_BYTES_1, 0, standstate );
	if( standstate == STANDSTATE_STAND )//standup
		RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_STAND_UP);

	if( m_objectTypeId == TYPEID_PLAYER )
		static_cast< Player* >( this )->GetSession()->OutPacket( SMSG_STANDSTATE_CHANGE_ACK, 1, &standstate );
}

void Unit::RemoveAurasByInterruptFlag(uint32 flag)
{
	Aura * a;
	for(uint32 x=0;x<MAX_AURAS;x++)
	{
		a = m_auras[x];
		if(a == NULL)
			continue;
		
		//some spells do not get removed all the time only at specific intervals
		if((a->m_spellProto->AuraInterruptFlags & flag) && !(a->m_spellProto->procFlags & PROC_REMOVEONUSE))
		{
			a->Remove();
			m_auras[x] = NULL;
		}
	}
}

bool Unit::HasAuraVisual(uint32 visualid)
{
	for(uint32 x=0;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
	if(m_auras[x] && m_auras[x]->GetSpellProto()->SpellVisual==visualid)
	{
		return true;
	}

	return false;
}

bool Unit::HasAura(uint32 spellid)
{
	for(uint32 x=0;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()== spellid)
		{
			return true;
		}

		return false;
}


void Unit::DropAurasOnDeath()
{
	for(uint32 x=0;x<MAX_AURAS;x++)
    {
        if(m_auras[x])
        {
            if(m_auras[x] && m_auras[x]->GetSpellProto()->Flags4 & CAN_PERSIST_AND_CASTED_WHILE_DEAD)
                continue;
            else
	        {
		        m_auras[x]->Remove();
	        }
        }
    }
}

void Unit::UpdateSpeed()
{
	if(GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID) == 0)
	{
		m_runSpeed = m_base_runSpeed * m_speedModifier;
	}
	else
	{
		m_runSpeed = m_base_runSpeed*(1.0f + ((float)m_mountedspeedModifier)/100.0f);
		if(m_speedModifier < 1.0f)
			m_runSpeed *= m_speedModifier;
	}

	

	m_flySpeed = PLAYER_NORMAL_FLIGHT_SPEED*(1.0f + ((float)m_flyspeedModifier)/100.0f);

	// Limit speed due to effects such as http://www.wowhead.com/?spell=31896 [Judgement of Justice]
	if( m_maxSpeed && m_runSpeed > m_maxSpeed )
	{
		m_runSpeed = m_maxSpeed;
	}

	if(IsPlayer())
	{
		if(((Player*)this)->m_changingMaps)
			static_cast< Player* >( this )->resend_speed = true;
		else
		{
			static_cast< Player* >( this )->SetPlayerSpeed(RUN, m_runSpeed);
			static_cast< Player* >( this )->SetPlayerSpeed(FLY, m_flySpeed);
		}
	}
}

bool Unit::HasActiveAura(uint32 spellid)
{
	for(uint32 x=0;x<MAX_AURAS;x++)
	if(m_auras[x] && m_auras[x]->GetSpellId()==spellid)
	{
		return true;
	}

	return false;
}

bool Unit::HasActiveAura(uint32 spellid,uint64 guid)
{
	for(uint32 x=0;x<MAX_AURAS;x++)
	if(m_auras[x] && m_auras[x]->GetSpellId()==spellid && m_auras[x]->m_casterGuid==guid)
	{
		return true;
	}

	return false;
}

void Unit::EventSummonPetExpire()
{
	if(summonPet)
	{
		if(summonPet->GetEntry() == 7915)//Goblin Bomb
		{
			SpellEntry *spInfo = dbcSpell.LookupEntry(13259);
			if(!spInfo)
				return;

			Spell*sp=new Spell(summonPet,spInfo,true,NULL);
			SpellCastTargets tgt;
			tgt.m_unitTarget=summonPet->GetGUID();
			sp->prepare(&tgt);
		}
		else
		{
			summonPet->RemoveFromWorld(false, true);
			delete summonPet;
			summonPet = NULL;
		}
	}
	sEventMgr.RemoveEvents(this, EVENT_SUMMON_PET_EXPIRE);
}

void Unit::CastSpell(Unit* Target, SpellEntry* Sp, bool triggered)
{
	if( Sp == NULL )
		return;

	Spell *newSpell = new Spell(this, Sp, triggered, 0);
	SpellCastTargets targets(0);
	if(Target)
	{
		targets.m_unitTarget |= TARGET_FLAG_UNIT;
		targets.m_unitTarget = Target->GetGUID();
	}
	else
	{
		newSpell->GenerateTargets(&targets);
	}
	newSpell->prepare(&targets);
}

void Unit::CastSpell(Unit* Target, uint32 SpellID, bool triggered)
{
	SpellEntry * ent = dbcSpell.LookupEntry(SpellID);
	if(ent == 0) return;

	CastSpell(Target, ent, triggered);
}

void Unit::CastSpell(uint64 targetGuid, SpellEntry* Sp, bool triggered)
{
	if( Sp == NULL )
		return;

	SpellCastTargets targets(targetGuid);
	Spell *newSpell = new Spell(this, Sp, triggered, 0);
	newSpell->prepare(&targets);
}

void Unit::CastSpell(uint64 targetGuid, uint32 SpellID, bool triggered)
{
	SpellEntry * ent = dbcSpell.LookupEntry(SpellID);
	if(ent == 0) return;

	CastSpell(targetGuid, ent, triggered);
}
void Unit::CastSpellAoF(float x,float y,float z,SpellEntry* Sp, bool triggered)
{
	if( Sp == NULL )
		return;

	SpellCastTargets targets;
	targets.m_destX = x;
	targets.m_destY = y;
	targets.m_destZ = z;
	targets.m_targetMask=TARGET_FLAG_DEST_LOCATION;
	Spell *newSpell = new Spell(this, Sp, triggered, 0);
	newSpell->prepare(&targets);
}

void Unit::PlaySpellVisual(uint64 target, uint32 spellVisual)
{
	WorldPacket data(SMSG_PLAY_SPELL_VISUAL, 12);
	data << target << spellVisual;
	SendMessageToSet(&data, true);
}

void Unit::Root()
{
	this->m_special_state |= UNIT_STATE_ROOT;

	if(m_objectTypeId == TYPEID_PLAYER)
	{
		static_cast< Player* >( this )->SetMovement(MOVE_ROOT, 1);
	}
	else
	{
		m_aiInterface->m_canMove = false;
		m_aiInterface->StopMovement(1);
	}
}

void Unit::Unroot()
{
	this->m_special_state &= ~UNIT_STATE_ROOT;

	if(m_objectTypeId == TYPEID_PLAYER)
	{
		static_cast< Player* >( this )->SetMovement(MOVE_UNROOT, 5);
	}
	else
	{
		m_aiInterface->m_canMove = true;
	}
}

void Unit::RemoveAurasByBuffType(uint32 buff_type, const uint64 &guid, uint32 skip)
{
	uint64 sguid = buff_type >= SPELL_TYPE_BLESSING ? guid : 0;

	for(uint32 x=0;x<MAX_AURAS;x++)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->buffType & buff_type && m_auras[x]->GetSpellId()!=skip)
			if(!sguid || (sguid && m_auras[x]->m_casterGuid == sguid))
				m_auras[x]->Remove();
	}
}

void Unit::RemoveAurasByBuffIndexType(uint32 buff_index_type, const uint64 &guid)
{
	for(uint32 x=0;x<MAX_AURAS;x++)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->buffIndexType == buff_index_type)
			if(!guid || (guid && m_auras[x]->m_casterGuid == guid))
				m_auras[x]->Remove();
	}
}

bool Unit::HasAurasOfBuffType(uint32 buff_type, const uint64 &guid,uint32 skip)
{
	uint64 sguid = (buff_type == SPELL_TYPE_BLESSING) ? guid : 0;

	for(uint32 x=0;x<MAX_AURAS;x++)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->buffType & buff_type && m_auras[x]->GetSpellId()!=skip)
			if(!sguid || (m_auras[x]->m_casterGuid == sguid))
				return true;
	}

	return false;
}

AuraCheckResponse Unit::AuraCheck(uint32 name_hash, uint32 rank, Object *caster)
{
	AuraCheckResponse resp;

	// no error for now
	resp.Error = AURA_CHECK_RESULT_NONE;
	resp.Misc  = 0;

	// look for spells with same namehash
	for(uint32 x=0;x<MAX_AURAS;x++)
	{
//		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash && m_auras[x]->GetCaster()==caster)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
		{
			// we've got an aura with the same name as the one we're trying to apply
			resp.Misc = m_auras[x]->GetSpellProto()->Id;

			// compare the rank to our applying spell
			if(m_auras[x]->GetSpellProto()->RankNumber > rank)
				resp.Error = AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT;
			else
				resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;

			// we found something, save some loops and exit
			break;
		}
	}

	// return it back to our caller
	return resp;
}

AuraCheckResponse Unit::AuraCheck(uint32 name_hash, uint32 rank, Aura* aur, Object *caster)
{
	AuraCheckResponse resp;

	// no error for now
	resp.Error = AURA_CHECK_RESULT_NONE;
	resp.Misc  = 0;

	// look for spells with same namehash
//	if(aur->GetSpellProto()->NameHash == name_hash && aur->GetCaster()==caster)
	if(aur->GetSpellProto()->NameHash == name_hash)
	{
		// we've got an aura with the same name as the one we're trying to apply
		resp.Misc = aur->GetSpellProto()->Id;

		// compare the rank to our applying spell
		if(aur->GetSpellProto()->RankNumber > rank)
			resp.Error = AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT;
		else
			resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;
	}

	// return it back to our caller
	return resp;
}

void Unit::OnPushToWorld()
{
	for(uint32 x = 0; x < MAX_AURAS+MAX_PASSIVE_AURAS; ++x)
	{
		if(m_auras[x] != 0)
			m_auras[x]->RelocateEvents();
	}
}

void Unit::RemoveFromWorld(bool free_guid)
{
	CombatStatus.OnRemoveFromWorld();
	if(critterPet != 0)
	{
		critterPet->RemoveFromWorld(false, true);
		delete critterPet;
		critterPet = 0;
	}

	if(dynObj != 0)
		dynObj->Remove();

	for(uint32 i = 0; i < 4; ++i)
	{
		if(m_ObjectSlots[i] != 0)
		{
			GameObject * obj = m_mapMgr->GetGameObject(m_ObjectSlots[i]);
			if(obj)
				obj->ExpireAndDelete();

			m_ObjectSlots[i] = 0;
		}
	}

	Object::RemoveFromWorld(free_guid);


	for(uint32 x = 0; x < MAX_AURAS+MAX_PASSIVE_AURAS; ++x)
	{
		if(m_auras[x] != 0)
		{
			if( m_auras[x]->m_deleted )
			{
				m_auras[x] = NULL;
				continue;
			}

			m_auras[x]->RelocateEvents();
		}
	}
	m_aiInterface->WipeReferences();
}

void Unit::RemoveAurasByInterruptFlagButSkip(uint32 flag, uint32 skip)
{
	Aura * a;
	for(uint32 x=0;x<MAX_AURAS;x++)
	{
		a = m_auras[x];
		if(a == 0)
			continue;

		//some spells do not get removed all the time only at specific intervals
		if((a->m_spellProto->AuraInterruptFlags & flag) && (a->m_spellProto->Id != skip) && a->m_spellProto->proc_interval==0)
		{
			//the black sheeps of sociaty
			if(a->m_spellProto->AuraInterruptFlags & AURA_INTERRUPT_ON_CAST_SPELL)
			{
				switch(a->GetSpellProto()->Id)
				{
					//priest - surge of light
					case 33151:
						{
							//our luck. it got trigered on smite..we do not remove it just yet
							if( m_currentSpell && m_currentSpell->m_spellInfo->NameHash == SPELL_HASH_SMITE )
								continue;

							//this spell gets removed only when casting smite
						    SpellEntry *spi = dbcSpell.LookupEntry( skip );
							if( spi && spi->NameHash != SPELL_HASH_SMITE )
								continue;
						}break;
					case 34936:		// Backlash
						{
							SpellEntry *spi = dbcSpell.LookupEntry( skip );
							if( spi && spi->NameHash != SPELL_HASH_SHADOW_BOLT && spi->NameHash != SPELL_HASH_INCINERATE )
								continue;
						}break;

					case 17941: //Shadow Trance
						{
							SpellEntry *spi = dbcSpell.LookupEntry( skip );
							if( spi && spi->NameHash != SPELL_HASH_SHADOW_BOLT )
								continue;
						}break;
					case 18708: //Fel Domination
						{
							SpellEntry *spi = dbcSpell.LookupEntry( skip );
							if( spi && spi->NameHash != SPELL_HASH_SUMMON_IMP &&
								spi->NameHash != SPELL_HASH_SUMMON_VOIDWALKER &&
								spi->NameHash != SPELL_HASH_SUMMON_SUCCUBUS &&
								spi->NameHash != SPELL_HASH_SUMMON_FELHUNTER &&
								spi->NameHash != SPELL_HASH_SUMMON_FELGUARD )
								continue;
						}break;
					case 36563: //Shadowstep
						{
							if(skip == 36554)
								continue;  // We just got triggered, not removing yet
						}break;
				}
			}
			a->Remove();
		}
	}
}

int Unit::HasAurasWithNameHash(uint32 name_hash)
{
	for(uint32 x = 0; x < MAX_AURAS; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
			return m_auras[x]->m_spellProto->Id;
	}

	return 0;
}

bool Unit::HasNegativeAuraWithNameHash(uint32 name_hash)
{
	for(uint32 x = MAX_POSITIVE_AURAS; x < MAX_AURAS; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
			return true;
	}

	return false;
}

bool Unit::HasNegativeAura(uint32 spell_id)
{
	for(uint32 x = MAX_POSITIVE_AURAS; x < MAX_AURAS; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->Id == spell_id)
			return true;
	}

	return false;
}

bool Unit::IsPoisoned()
{
	for(uint32 x = 0; x < MAX_AURAS+MAX_PASSIVE_AURAS; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_POISON)
			return true;
	}

	return false;
}

uint32 Unit::AddAuraVisual(uint32 spellid, uint32 count, bool positive)
{
	int32 free = -1;
	uint32 start = positive ? 0 : MAX_POSITIVE_AURAS;
	uint32 end_  = positive ? MAX_POSITIVE_AURAS : MAX_AURAS;

	for(uint32 x = start; x < end_; ++x)
	{
		if(free == -1 && m_uint32Values[UNIT_FIELD_AURA+x] == 0)
			free = x;

		if(m_uint32Values[UNIT_FIELD_AURA+x] == spellid)
		{
			// Increase count of this aura.
			ModAuraStackCount(x, count);
			return free;
		}
	}

	if(free == -1) return 0xFF;

	uint8 flagslot = (free / 4);
	uint32 value = GetUInt32Value((uint16)(UNIT_FIELD_AURAFLAGS + flagslot));

	/*uint8 aurapos = (free & 7) << 2;
	uint32 setflag = AFLAG_SET;
	if(positive)
		setflag = 0xD;

	uint32 value1 = (uint32)setflag << aurapos;
	value |= value1;*/
	uint8 aurapos = (free%4)*8;
	value &= ~(0xFF<<aurapos);
	if(positive)
		value |= (0x1F<<aurapos);
	else
		value |= (0x09<<aurapos);

	SetUInt32Value((uint16)(UNIT_FIELD_AURAFLAGS + flagslot), value);
	SetUInt32Value(UNIT_FIELD_AURA + free, spellid);
	ModAuraStackCount(free, 1);
	SetAuraSlotLevel(free, positive);
	
	return free;
}

void Unit::SetAuraSlotLevel(uint32 slot, bool positive)
{
	uint32 index = slot / 4;
	uint32 val = m_uint32Values[UNIT_FIELD_AURALEVELS + index];
	uint32 bit = (slot % 4) * 8;
	val &= ~(0xFF << bit);
	if(positive)
		val |= (0x46 << bit);
	else
		val |= (0x19 << bit);
	
	SetUInt32Value(UNIT_FIELD_AURALEVELS + index, val);
}

void Unit::RemoveAuraVisual(uint32 spellid, uint32 count)
{
	for(uint32 x = 0; x < MAX_AURAS; ++x)
	{
		if(m_uint32Values[UNIT_FIELD_AURA+x] == spellid)
		{
			// Decrease count of this aura.
			int test = ModAuraStackCount(x, -(int32)count);
			if(test == 0)
			{
				// Aura has been removed completely.
				uint8 flagslot = (x/4);
				uint32 value = GetUInt32Value((uint16)(UNIT_FIELD_AURAFLAGS + flagslot));
				/*uint8 aurapos = (x & 7) << 2;
				uint32 value1 = ~( (uint32)0xF << aurapos );
				value &= value1;*/
				uint8 aurapos = (x%4)*8;
				value &= ~(0xFF<<aurapos);
				SetUInt32Value(UNIT_FIELD_AURAFLAGS + flagslot,value);
				SetUInt32Value(UNIT_FIELD_AURA + x, 0);
				SetAuraSlotLevel(x, false);
			}			
		}
	}
}

uint32 Unit::ModAuraStackCount(uint32 slot, int32 count)
{
	uint32 index = (slot >> 2);
	uint32 byte  = (slot % 4);
	uint32 val   = m_uint32Values[UNIT_FIELD_AURAAPPLICATIONS+index];

	// shouldn't happen
	uint32 ac;

	if(count < 0 && m_auraStackCount[slot] < abs(count))
	{
		m_auraStackCount[slot] = ac = 0;
	}
	else
	{
		m_auraStackCount[slot] += count;
		ac = (m_auraStackCount[slot] > 0) ? m_auraStackCount[slot] - 1 : 0;
	}

	val &= ~(0xFF << byte * 8);
	val |= (ac << byte * 8);

	SetUInt32Value(UNIT_FIELD_AURAAPPLICATIONS+index, val);
	return m_auraStackCount[slot];
}

void Unit::RemoveAurasOfSchool(uint32 School, bool Positive, bool Immune)
{
	for(uint32 x = 0; x < MAX_AURAS; ++x)
	{
		if(m_auras[x]  && m_auras[x]->GetSpellProto()->School == School && (!m_auras[x]->IsPositive() || Positive) && (!Immune && m_auras[x]->GetSpellProto()->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY))
			m_auras[x]->Remove();
	}
}

void Unit::EnableFlight()
{
	if(m_objectTypeId != TYPEID_PLAYER || ((Player*)this)->m_changingMaps)
	{
		WorldPacket data(SMSG_MOVE_SET_FLY, 13);
		data << GetNewGUID();
		data << uint32(2);
		SendMessageToSet(&data, true);

		if( IsPlayer() )
		{
			static_cast< Player* >( this )->m_setflycheat = true;
		}
	}
	else
	{
		WorldPacket * data = new WorldPacket(SMSG_MOVE_SET_FLY, 13);
		*data << GetNewGUID();
		*data << uint32(2);
		SendMessageToSet(data, false);
		static_cast< Player* >( this )->z_axisposition = 0.0f;
		static_cast< Player* >( this )->delayedPackets.add( data );
		static_cast< Player* >( this )->m_setflycheat = true;
	}
}

void Unit::DisableFlight()
{
	if(m_objectTypeId != TYPEID_PLAYER || ((Player*)this)->m_changingMaps)
	{
		WorldPacket data(SMSG_MOVE_SET_UNFLY, 13);
		data << GetNewGUID();
		data << uint32(5);
		SendMessageToSet(&data, true);

		if( IsPlayer() )
			static_cast< Player* >( this )->m_setflycheat = false;
	}
	else
	{
		WorldPacket * data = new WorldPacket( SMSG_MOVE_SET_UNFLY, 13 );
		*data << GetNewGUID();
		*data << uint32(5);
		SendMessageToSet(data, false);
		static_cast< Player* >( this )->z_axisposition = 0.0f;
		static_cast< Player* >( this )->delayedPackets.add( data );
		static_cast< Player* >( this )->m_setflycheat = false;
	}
}

bool Unit::IsDazed()
{
	for(uint32 x = 0; x < MAX_AURAS; ++x)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->HasMechanic(MECHANIC_ENSNARED))
				return true;
		}
	}

	return false;

}

void Unit::UpdateVisibility()
{
	ByteBuffer buf(2500);
	InRangeSet::iterator itr, it3;
	uint32 count;
	bool can_see;
	bool is_visible;
	Player *pl;
	Object * pObj;
	Player * plr;

	if( m_objectTypeId == TYPEID_PLAYER )
	{
		plr = static_cast< Player* >( this );
		for( Object::InRangeSet::iterator itr = m_objectsInRange.begin(); itr != m_objectsInRange.end();)
		{
			pObj = (*itr);
			++itr;

			can_see = plr->CanSee(pObj);
			is_visible = plr->GetVisibility(pObj, &it3);
			if(can_see)
			{
				if(!is_visible)
				{
					buf.clear();
					count = pObj->BuildCreateUpdateBlockForPlayer( &buf, plr );
					plr->PushCreationData(&buf, count);
					plr->AddVisibleObject(pObj);
				}
			}
			else
			{
				if(is_visible)
				{
					pObj->DestroyForPlayer(plr);
					plr->RemoveVisibleObject(it3);
				}
			}

			if( pObj->GetTypeId() == TYPEID_PLAYER )
			{
				pl = static_cast< Player* >( pObj );
				can_see = pl->CanSee( plr );
				is_visible = pl->GetVisibility( plr, &it3 );
				if( can_see )
				{
					if(!is_visible)
					{
						buf.clear();
						count = plr->BuildCreateUpdateBlockForPlayer( &buf, pl );
						pl->PushCreationData(&buf, count);
						pl->AddVisibleObject(plr);
					}
				}
				else
				{
					if(is_visible)
					{
						plr->DestroyForPlayer(pl);
						pl->RemoveVisibleObject(it3);
					}
				}
			}
		}
	}
	else			// For units we can save a lot of work
	{
		for(set<Player*>::iterator it2 = GetInRangePlayerSetBegin(); it2 != GetInRangePlayerSetEnd(); ++it2)
		{
			can_see = (*it2)->CanSee(this);
			is_visible = (*it2)->GetVisibility(this, &itr);
			if(!can_see)
			{
				if(is_visible)
				{
					DestroyForPlayer(*it2);
					(*it2)->RemoveVisibleObject(itr);
				}
			}
			else
			{
				if(!is_visible)
				{
					buf.clear();
					count = BuildCreateUpdateBlockForPlayer(&buf, *it2);
					(*it2)->PushCreationData(&buf, count);
					(*it2)->AddVisibleObject(this);
				}
			}
		}
	}
}

void Unit::RemoveSoloAura(uint32 type)
{
	switch(type)
	{
		case 1:// Polymorph
		{
			if(!polySpell) return;
			if(HasActiveAura(polySpell))
				RemoveAura(polySpell);
		}break;
/*		case 2:// Sap
		{
			if(!sapSpell) return;
			if(HasActiveAura(sapSpell))
				RemoveAura(sapSpell);
		}break;
		case 3:// Fear (Warlock)
		{
			if(!fearSpell) return;
			if(HasActiveAura(fearSpell))
				RemoveAura(fearSpell);
		}break;*/
		default:
			{
			sLog.outDebug("Warning: we are trying to remove a soloauratype that has no handle");
			}break;
	}
}

void Unit::EventHealthChangeSinceLastUpdate()
{
	int pct = GetHealthPct();
	if(pct<35)
	{
		uint32 toset=AURASTATE_FLAG_HEALTH35;
		if(pct<20)
			toset |= AURASTATE_FLAG_HEALTH20;
		else
			RemoveFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_HEALTH20);
		SetFlag(UNIT_FIELD_AURASTATE,toset);
	}
	else
		RemoveFlag(UNIT_FIELD_AURASTATE , AURASTATE_FLAG_HEALTH35 | AURASTATE_FLAG_HEALTH20);
}

int32 Unit::GetAP()
{
    int32 baseap = GetUInt32Value(UNIT_FIELD_ATTACK_POWER) + GetUInt32Value(UNIT_FIELD_ATTACK_POWER_MODS);
    float totalap = float(baseap)*(GetFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER)+1);
	if(totalap>=0)
		return float2int32(totalap);
	return	0;
}

int32 Unit::GetRAP()
{
    int32 baseap = GetUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER) + GetUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER_MODS);
    float totalap = float(baseap)*(GetFloatValue(UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER)+1);
	if(totalap>=0)
		return float2int32(totalap);
	return	0;
}

bool Unit::GetSpeedDecrease()
{
	int32 before = m_slowdown;
	m_slowdown = 0;
	map< uint32, int32 >::iterator itr = speedReductionMap.begin();
	for(; itr != speedReductionMap.end(); ++itr)
		m_slowdown = (int32)min( m_slowdown, itr->second );

	if(m_slowdown<=-100)
		m_slowdown = -99; //do not walk backwards and prevent division by zero

	//save bandwidth :P
	if(m_slowdown != before)
	{
		m_speedModifier /= before / 100.0f + 1;
		m_speedModifier *= m_slowdown / 100.0f + 1;
		return true;
	}
	return false;
}

void Unit::EventCastSpell(Unit * Target, SpellEntry * Sp)
{
	Spell * pSpell = new Spell(Target, Sp, true, NULL);
	SpellCastTargets targets(Target->GetGUID());
	pSpell->prepare(&targets);
}

void Unit::SetFacing(float newo)
{
	SetOrientation(newo);
	/*WorldPacket data(40);
	data.SetOpcode(MSG_MOVE_SET_FACING);
	data << GetNewGUID();
	data << (uint32)0; //flags
	data << (uint32)0; //time
	data << GetPositionX() << GetPositionY() << GetPositionZ() << newo;
	data << (uint32)0; //unk
	SendMessageToSet( &data, false );*/

	/*WorldPacket data(SMSG_MONSTER_MOVE, 60);
	data << GetNewGUID();
	data << m_position << getMSTime();
	data << uint8(4) << newo;
	data << uint32(0x00000000);		// flags
	data << uint32(0);				// time
	data << m_position;				// position
	SendMessageToSet(&data, true);*/
	m_aiInterface->SendMoveToPacket(m_position.x,m_position.y,m_position.z,m_position.o,1,0x100); // MoveFlags = 0x100 (run)
}

//guardians are temporary spawn that will inherit master faction and will folow them. Apart from that they have their own mind
Unit* Unit::create_guardian(uint32 guardian_entry,uint32 duration,float angle)
{
	CreatureProto * proto = CreatureProtoStorage.LookupEntry(guardian_entry);
	CreatureInfo * info = CreatureNameStorage.LookupEntry(guardian_entry);
	if(!proto || !info)
	{
		sLog.outDetail("Warning : Missing summon creature template %u !",guardian_entry);
		return NULL;
	}
	float m_fallowAngle=angle;
	float x = GetPositionX()+(3*(cosf(m_fallowAngle+GetOrientation())));
	float y = GetPositionY()+(3*(sinf(m_fallowAngle+GetOrientation())));
	float z = GetPositionZ();
	Creature * p = GetMapMgr()->CreateCreature(guardian_entry);
	p->SetInstanceID(GetMapMgr()->GetInstanceID());
	p->Load(proto, x, y, z);
	p->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, GetGUID());
    p->SetUInt64Value(UNIT_FIELD_CREATEDBY, GetGUID());
    p->SetZoneId(GetZoneId());
	p->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE,GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	p->_setFaction();

	p->GetAIInterface()->Init(p,AITYPE_PET,MOVEMENTTYPE_NONE,this);
	p->GetAIInterface()->SetUnitToFollow(this);
	p->GetAIInterface()->SetUnitToFollowAngle(m_fallowAngle);
	p->GetAIInterface()->SetFollowDistance(3.0f);

	p->PushToWorld(GetMapMgr());

	sEventMgr.AddEvent(p, &Creature::SummonExpire, EVENT_SUMMON_EXPIRE, duration, 1,0);

	return p;//lol, will compiler make the pointer conversion ?

}

float Unit::get_chance_to_daze(Unit *target)
{
//	if(GetTypeId()!=TYPEID_UNIT)
//		return 0.0f;
	float attack_skill = float( getLevel() ) * 5.0f;
	float defense_skill;
	if( target->IsPlayer() )
		defense_skill = float( static_cast< Player* >( target )->_GetSkillLineCurrent( SKILL_DEFENSE, false ) );
	else defense_skill = float( target->getLevel() * 5 );
	if( !defense_skill )
		defense_skill = 1;
	float chance_to_daze = attack_skill * 20 / defense_skill;//if level is equal then we get a 20% chance to daze
	chance_to_daze = chance_to_daze * std::min(target->getLevel() / 30.0f, 1.0f );//for targets below level 30 the chance decreses
	if( chance_to_daze > 40 )
		return 40.0f;
	else
		return chance_to_daze;
}

void CombatStatusHandler::ClearMyHealers()
{
	// this is where we check all our healers
	HealedSet::iterator i;
	Player * pt;
	for(i = m_healers.begin(); i != m_healers.end(); ++i)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*i);
		if(pt != NULL)
			pt->CombatStatus.RemoveHealed(m_Unit);
	}

	m_healers.clear();
}

void CombatStatusHandler::WeHealed(Unit * pHealTarget)
{
	if(pHealTarget->GetTypeId() != TYPEID_PLAYER || m_Unit->GetTypeId() != TYPEID_PLAYER || pHealTarget == m_Unit)
		return;

	if(pHealTarget->CombatStatus.IsInCombat())
	{
		m_healed.insert(pHealTarget->GetLowGUID());
		pHealTarget->CombatStatus.m_healers.insert(m_Unit->GetLowGUID());
	}

	UpdateFlag();
}

void CombatStatusHandler::RemoveHealed(Unit * pHealTarget)
{
	m_healed.erase(pHealTarget->GetLowGUID());
	UpdateFlag();
}

void CombatStatusHandler::UpdateFlag()
{
	bool n_status = InternalIsInCombat();
	if(n_status != m_lastStatus)
	{
		m_lastStatus = n_status;
		if(n_status)
		{
			//printf(I64FMT" is now in combat.\n", m_Unit->GetGUID());
			m_Unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			if(!m_Unit->hasStateFlag(UF_ATTACKING)) m_Unit->addStateFlag(UF_ATTACKING);
		}
		else
		{
			//printf(I64FMT" is no longer in combat.\n", m_Unit->GetGUID());
			m_Unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			if(m_Unit->hasStateFlag(UF_ATTACKING)) m_Unit->clearStateFlag(UF_ATTACKING);

			// remove any of our healers from combat too, if they are able to be.
			ClearMyHealers();
		}
	}
}

bool CombatStatusHandler::InternalIsInCombat()
{
	if(m_healed.size() > 0)
		return true;

	if(m_attackTargets.size() > 0)
		return true;

	if(m_attackers.size() > 0)
		return true;

	return false;
}

void CombatStatusHandler::AddAttackTarget(const uint64& guid)
{
	if(guid == m_Unit->GetGUID())
		return;

	m_attackTargets.insert(guid);
	//printf("Adding attack target "I64FMT" to "I64FMT"\n", guid, m_Unit->GetGUID());
	if(m_Unit->GetTypeId() == TYPEID_PLAYER &&
		m_primaryAttackTarget != guid)			// players can only have one attack target.
	{
		if(m_primaryAttackTarget)
			ClearPrimaryAttackTarget();

		m_primaryAttackTarget = guid;
	}

	UpdateFlag();
}

void CombatStatusHandler::ClearPrimaryAttackTarget()
{
	//printf("ClearPrimaryAttackTarget for "I64FMT"\n", m_Unit->GetGUID());
	if(m_primaryAttackTarget != 0)
	{
		Unit * pt = m_Unit->GetMapMgr()->GetUnit(m_primaryAttackTarget);
		if(pt != NULL)
		{
			// remove from their attacker set. (if we have no longer got any DoT's, etc)
			if(!IsAttacking(pt))
			{
				pt->CombatStatus.RemoveAttacker(m_Unit, m_Unit->GetGUID());
				m_attackTargets.erase(m_primaryAttackTarget);
			}
			
			m_primaryAttackTarget = 0;
		}
		else
		{
			m_attackTargets.erase(m_primaryAttackTarget);
			m_primaryAttackTarget = 0;
		}
	}

	UpdateFlag();
}

bool CombatStatusHandler::IsAttacking(Unit * pTarget)
{
	// check the target for any of our DoT's.
	for(uint32 i = MAX_POSITIVE_AURAS; i < MAX_AURAS; ++i)
	{
		if(pTarget->m_auras[i] != NULL)
		{
			if(m_Unit->GetGUID() == pTarget->m_auras[i]->m_casterGuid && pTarget->m_auras[i]->IsCombatStateAffecting())
				return true;
		}
	}

	// place any additional checks here
	return false;
}

void CombatStatusHandler::RemoveAttackTarget(Unit * pTarget)
{
	// called on aura remove, etc.
	AttackerMap::iterator itr = m_attackTargets.find(pTarget->GetGUID());
	if(itr == m_attackTargets.end())
		return;

	if(!IsAttacking(pTarget))
	{
		//printf("Removing attack target "I64FMT" on "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());
		m_attackTargets.erase(itr);
		if(m_primaryAttackTarget == pTarget->GetGUID())
			m_primaryAttackTarget = 0;

		UpdateFlag();
	}
	/*else
		printf("Cannot remove attack target "I64FMT" from "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());*/
}

void CombatStatusHandler::RemoveAttacker(Unit * pAttacker, const uint64& guid)
{
	AttackerMap::iterator itr = m_attackers.find(guid);
	if(itr == m_attackers.end())
		return;

	if( (!pAttacker) || (!pAttacker->CombatStatus.IsAttacking(m_Unit)) )
	{
		//printf("Removing attacker "I64FMT" from "I64FMT"\n", guid, m_Unit->GetGUID());
		m_attackers.erase(itr);
		UpdateFlag();
	}
	/*else
	{
		printf("Cannot remove attacker "I64FMT" from "I64FMT"\n", guid, m_Unit->GetGUID());
	}*/
}

void CombatStatusHandler::OnDamageDealt(Unit * pTarget)
{
	// we added an aura, or dealt some damage to a target. they need to have us as an attacker, and they need to be our attack target if not.
	//printf("OnDamageDealt to "I64FMT" from "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());
	if(pTarget == m_Unit)
		return;

	if(!pTarget->isAlive())
		return;

	AttackerMap::iterator itr = m_attackTargets.find(pTarget->GetGUID());
	if(itr == m_attackTargets.end())
		AddAttackTarget(pTarget->GetGUID());
	itr = pTarget->CombatStatus.m_attackers.find(m_Unit->GetGUID());
	if(itr == pTarget->CombatStatus.m_attackers.end())
		pTarget->CombatStatus.AddAttacker(m_Unit->GetGUID());
	// update the timeout
	m_Unit->CombatStatusHandler_ResetPvPTimeout();
}

void CombatStatusHandler::AddAttacker(const uint64& guid)
{
	m_attackers.insert(guid);
	UpdateFlag();
}

void CombatStatusHandler::ClearAttackers()
{
		// this is a FORCED function, only use when the reference will be destroyed.
	AttackerMap::iterator itr = m_attackTargets.begin();

	Unit * pt;
	for(; itr != m_attackTargets.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetUnit(*itr);
		if(pt)
		{
			pt->CombatStatus.m_attackers.erase(m_Unit->GetGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	for(itr = m_attackers.begin(); itr != m_attackers.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetUnit(*itr);
		if(pt)
		{
			pt->CombatStatus.m_attackTargets.erase(m_Unit->GetGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	m_attackers.clear();
	m_attackTargets.clear();
	m_primaryAttackTarget = 0;
	UpdateFlag();
}

void CombatStatusHandler::ClearHealers()
{
	HealedSet::iterator itr = m_healed.begin();
	Player * pt;
	for(; itr != m_healed.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*itr);
		if(pt)
		{
			pt->CombatStatus.m_healers.erase(m_Unit->GetLowGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	for(itr = m_healers.begin(); itr != m_healers.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*itr);
		if(pt)
		{
			pt->CombatStatus.m_healed.erase(m_Unit->GetLowGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	m_healed.clear();
	m_healers.clear();
	UpdateFlag();
}

void CombatStatusHandler::OnRemoveFromWorld()
{
	ClearAttackers();
	ClearHealers();
}

void Unit::CombatStatusHandler_ResetPvPTimeout()
{
	if(!IsPlayer())
		return;

	m_lock.Acquire();
	EventMap::iterator itr = m_events.find(EVENT_ATTACK_TIMEOUT);
	if(itr != m_events.end())
	{
		for(; itr != m_events.upper_bound(EVENT_ATTACK_TIMEOUT); ++itr)
		{
			if(!itr->second->deleted)
			{
				itr->second->currTime = 5000;
				m_lock.Release();
				return;
			}
		}
	}

	// yay for recursive mutexes
	sEventMgr.AddEvent(this, &Unit::CombatStatusHandler_UpdatePvPTimeout, EVENT_ATTACK_TIMEOUT, 5000, 1, 0);
	m_lock.Release();
}

void Unit::CombatStatusHandler_UpdatePvPTimeout()
{
	CombatStatus.TryToClearAttackTargets();	
}

void Unit::Heal(Unit *target, uint32 SpellId, uint32 amount)
{//Static heal
	if(!target || !SpellId || !amount)
		return;

	uint32 ch=target->GetUInt32Value(UNIT_FIELD_HEALTH);
	uint32 mh=target->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
	if(mh!=ch)
	{
		ch += amount;
		if(ch > mh)
		{
			target->SetUInt32Value(UNIT_FIELD_HEALTH, mh);
			amount += mh-ch;
		}
		else 
			target->SetUInt32Value(UNIT_FIELD_HEALTH, ch);

		WorldPacket data(SMSG_HEALSPELL_ON_PLAYER,25);
		data << target->GetNewGUID();
		data << this->GetNewGUID();
		data << uint32(SpellId);  
		data << uint32(amount);   
		data << uint8(0);
		this->SendMessageToSet(&data,true);
	}
}
void Unit::Energize(Unit* target,uint32 SpellId, uint32 amount,uint32 type)
{//Static energize
	if(!target || !SpellId || !amount)
		return;
	uint32 cm=target->GetUInt32Value(UNIT_FIELD_POWER1+type);
	uint32 mm=target->GetUInt32Value(UNIT_FIELD_MAXPOWER1+type);
	if(mm!=cm)
	{
		cm += amount;
		if(cm > mm)
		{
			target->SetUInt32Value(UNIT_FIELD_POWER1+type, mm);
			amount += mm-cm;
		}
		else 
			target->SetUInt32Value(UNIT_FIELD_POWER1+type, cm);

		WorldPacket datamr(SMSG_HEALMANASPELL_ON_PLAYER, 30);
		datamr << target->GetNewGUID();
		datamr << this->GetNewGUID();
		datamr << uint32(SpellId);
		datamr << uint32(0);
		datamr << uint32(amount);
		this->SendMessageToSet(&datamr,true);
	}
}

void Unit::InheritSMMods(Unit *inherit_from)
{
	if(inherit_from->SM_CriticalChance)
	{
		if(SM_CriticalChance==0)
			SM_CriticalChance = new int32[SPELL_GROUPS];
		memcpy(SM_CriticalChance,inherit_from->SM_CriticalChance,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FDur)
	{
		if(SM_FDur==0)
			SM_FDur = new int32[SPELL_GROUPS];
		memcpy(SM_FDur,inherit_from->SM_FDur,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PDur)
	{
		if(SM_PDur==0)
			SM_PDur = new int32[SPELL_GROUPS];
		memcpy(SM_PDur,inherit_from->SM_PDur,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRadius)
	{
		if(SM_PRadius==0)
			SM_PRadius = new int32[SPELL_GROUPS];
		memcpy(SM_PRadius,inherit_from->SM_PRadius,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FRadius)
	{
		if(SM_FRadius==0)
			SM_FRadius = new int32[SPELL_GROUPS];
		memcpy(SM_FRadius,inherit_from->SM_FRadius,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FRange)
	{
		if(SM_FRange==0)
			SM_FRange = new int32[SPELL_GROUPS];
		memcpy(SM_FRange,inherit_from->SM_FRange,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCastTime)
	{
		if(SM_PCastTime==0)
			SM_PCastTime = new int32[SPELL_GROUPS];
		memcpy(SM_PCastTime,inherit_from->SM_PCastTime,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FCastTime)
	{
		if(SM_FCastTime==0)
			SM_FCastTime = new int32[SPELL_GROUPS];
		memcpy(SM_FCastTime,inherit_from->SM_FCastTime,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCriticalDamage)
	{
		if(SM_PCriticalDamage==0)
			SM_PCriticalDamage = new int32[SPELL_GROUPS];
		memcpy(SM_PCriticalDamage,inherit_from->SM_PCriticalDamage,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FDOT)
	{
		if(SM_FDOT==0)
			SM_FDOT = new int32[SPELL_GROUPS];
		memcpy(SM_FDOT,inherit_from->SM_FDOT,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PDOT)
	{
		if(SM_PDOT==0)
			SM_PDOT = new int32[SPELL_GROUPS];
		memcpy(SM_PDOT,inherit_from->SM_PDOT,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FEffectBonus)
	{
		if(SM_FEffectBonus==0)
			SM_FEffectBonus = new int32[SPELL_GROUPS];
		memcpy(SM_FEffectBonus,inherit_from->SM_FEffectBonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PEffectBonus)
	{
		if(SM_PEffectBonus==0)
			SM_PEffectBonus = new int32[SPELL_GROUPS];
		memcpy(SM_PEffectBonus,inherit_from->SM_PEffectBonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FDamageBonus)
	{
		if(SM_FDamageBonus==0)
			SM_FDamageBonus = new int32[SPELL_GROUPS];
		memcpy(SM_FDamageBonus,inherit_from->SM_FDamageBonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PDamageBonus)
	{
		if(SM_PDamageBonus==0)
			SM_PDamageBonus = new int32[SPELL_GROUPS];
		memcpy(SM_PDamageBonus,inherit_from->SM_PDamageBonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PSPELL_VALUE)
	{
		if(SM_PSPELL_VALUE==0)
			SM_PSPELL_VALUE = new int32[SPELL_GROUPS];
		memcpy(SM_PSPELL_VALUE,inherit_from->SM_PSPELL_VALUE,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FSPELL_VALUE)
	{
		if(SM_FSPELL_VALUE==0)
			SM_FSPELL_VALUE = new int32[SPELL_GROUPS];
		memcpy(SM_FSPELL_VALUE,inherit_from->SM_FSPELL_VALUE,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FHitchance)
	{
		if(SM_FHitchance==0)
			SM_FHitchance = new int32[SPELL_GROUPS];
		memcpy(SM_FHitchance,inherit_from->SM_FHitchance,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRange)
	{
		if(SM_PRange==0)
			SM_PRange = new int32[SPELL_GROUPS];
		memcpy(SM_PRange,inherit_from->SM_PRange,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRadius)
	{
		if(SM_PRadius==0)
			SM_PRadius = new int32[SPELL_GROUPS];
		memcpy(SM_PRadius,inherit_from->SM_PRadius,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PAPBonus)
	{
		if(SM_PAPBonus==0)
			SM_PAPBonus = new int32[SPELL_GROUPS];
		memcpy(SM_PAPBonus,inherit_from->SM_PAPBonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCost)
	{
		if(SM_PCost==0)
			SM_PCost = new int32[SPELL_GROUPS];
		memcpy(SM_PCost,inherit_from->SM_PCost,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FCost)
	{
		if(SM_FCost==0)
			SM_FCost = new int32[SPELL_GROUPS];
		memcpy(SM_FCost,inherit_from->SM_FCost,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FAdditionalTargets)
	{
		if(SM_FAdditionalTargets==0)
			SM_FAdditionalTargets = new int32[SPELL_GROUPS];
		memcpy(SM_FAdditionalTargets,inherit_from->SM_FAdditionalTargets,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PJumpReduce)
	{
		if(SM_PJumpReduce==0)
			SM_PJumpReduce = new int32[SPELL_GROUPS];
		memcpy(SM_PJumpReduce,inherit_from->SM_PJumpReduce,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FSpeedMod)
	{
		if(SM_FSpeedMod==0)
			SM_FSpeedMod = new int32[SPELL_GROUPS];
		memcpy(SM_FSpeedMod,inherit_from->SM_FSpeedMod,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PNonInterrupt)
	{
		if(SM_PNonInterrupt==0)
			SM_PNonInterrupt = new int32[SPELL_GROUPS];
		memcpy(SM_PNonInterrupt,inherit_from->SM_PNonInterrupt,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FPenalty)
	{
		if(SM_FPenalty==0)
			SM_FPenalty = new int32[SPELL_GROUPS];
		memcpy(SM_FPenalty,inherit_from->SM_FPenalty,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FCooldownTime)
	{
		if(SM_FCooldownTime==0)
			SM_FCooldownTime = new int32[SPELL_GROUPS];
		memcpy(SM_FCooldownTime,inherit_from->SM_FCooldownTime,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCooldownTime)
	{
		if(SM_PCooldownTime==0)
			SM_PCooldownTime = new int32[SPELL_GROUPS];
		memcpy(SM_PCooldownTime,inherit_from->SM_PCooldownTime,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FChanceOfSuccess)
	{
		if(SM_FChanceOfSuccess==0)
			SM_FChanceOfSuccess = new int32[SPELL_GROUPS];
		memcpy(SM_FChanceOfSuccess,inherit_from->SM_FChanceOfSuccess,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FRezist_dispell)
	{
		if(SM_FRezist_dispell==0)
			SM_FRezist_dispell = new int32[SPELL_GROUPS];
		memcpy(SM_FRezist_dispell,inherit_from->SM_FRezist_dispell,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRezist_dispell)
	{
		if(SM_PRezist_dispell==0)
			SM_PRezist_dispell = new int32[SPELL_GROUPS];
		memcpy(SM_PRezist_dispell,inherit_from->SM_PRezist_dispell,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PThreatReduced)
	{
		if(SM_PThreatReduced==0)
			SM_PThreatReduced = new int32[SPELL_GROUPS];
		memcpy(SM_PThreatReduced,inherit_from->SM_PThreatReduced,sizeof(int)*SPELL_GROUPS);
	}
}

void CombatStatusHandler::TryToClearAttackTargets()
{
	AttackerMap::iterator i, i2;
	Unit * pt;

	for(i = m_attackTargets.begin(); i != m_attackTargets.end();)
	{
		i2 = i++;
		pt = m_Unit->GetMapMgr()->GetUnit(*i2);
		if(pt == NULL)
		{
			m_attackTargets.erase(i2);
			continue;
		}

		RemoveAttackTarget(pt);
		pt->CombatStatus.RemoveAttacker(m_Unit,m_Unit->GetGUID());
	}
}

void CombatStatusHandler::AttackersForgetHate()
{
	AttackerMap::iterator i, i2;
	Unit * pt;

	for(i = m_attackTargets.begin(); i != m_attackTargets.end();)
	{
		i2 = i++;
		pt = m_Unit->GetMapMgr()->GetUnit(*i2);
		if(pt == NULL)
		{
			m_attackTargets.erase(i2);
			continue;
		}

		if(pt->GetAIInterface())
			pt->GetAIInterface()->RemoveThreatByPtr(m_Unit);
	}
}

void Unit::CancelSpell(Spell * ptr)
{
	if(ptr)
		ptr->cancel();
	else if(m_currentSpell)
		m_currentSpell->cancel();
}

void Unit::EventStrikeWithAbility(uint64 guid, SpellEntry * sp, uint32 damage)
{
	Unit * victim = m_mapMgr ? m_mapMgr->GetUnit(guid) : NULL;
	if(victim)
		Strike( victim, RANGED, sp, 0, 0, 0, false, true );
}

void Unit::DispelAll(bool positive)
{
	for(uint32 i = 0; i < MAX_AURAS; ++i)
	{
		if(m_auras[i]!=NULL)
			if((m_auras[i]->IsPositive()&&positive)||!m_auras[i]->IsPositive())
				m_auras[i]->Remove();
	}
}

/* bool Unit::RemoveAllAurasByMechanic (renamed from MechanicImmunityMassDispel)
- Removes all auras on this unit that are of a specific mechanic.
- Useful for things like.. Apply Aura: Immune Mechanic, where existing (de)buffs are *always supposed* to be removed.
- I'm not sure if this goes here under unit.
* Arguments:
	- uint32 MechanicType
		*

* Returns;
	- False if no buffs were dispelled, true if more than 0 were dispelled.
*/
bool Unit::RemoveAllAurasByMechanic( uint32 MechanicType , uint32 MaxDispel = -1 , bool HostileOnly = true )
{
	//sLog.outString( "Unit::MechanicImmunityMassDispel called, mechanic: %u" , MechanicType );
	uint32 DispelCount = 0;
	for(uint32 x = ( HostileOnly ? MAX_POSITIVE_AURAS : 0 ) ; x < MAX_AURAS ; x++ ) // If HostileOnly = 1, then we use aura slots 40-56 (hostile). Otherwise, we use 0-56 (all)
		{
			if( DispelCount >= MaxDispel && MaxDispel > 0 )
			return true;

			if( m_auras[x] )
			{
					if( m_auras[x]->HasMechanic( MechanicType )) // Remove all mechanics of type MechanicType (my english goen boom)
					{
						//sLog.outString( "Removed aura. [AuraSlot %u, SpellId %u]" , x , m_auras[x]->GetSpellId() );
						// TODO: Stop moving if fear was removed.
						m_auras[x]->Remove(); // EZ-Remove
						DispelCount ++;
					}
					else if( MechanicType == MECHANIC_ENSNARED ) // if got immunity for slow, remove some that are not in the mechanics
					{
						for( int i=0 ; i<3 ; i++ )
						{
							// SNARE + ROOT
							if( m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_DECREASE_SPEED || m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_ROOT )
							{
								m_auras[x]->Remove();
								break;
							}
						}
					}
			}
		}
	return ( DispelCount == 0 );
}

void Unit::setAttackTimer(int32 time, bool offhand)
{
	if(!time)
		time = offhand ? m_uint32Values[UNIT_FIELD_BASEATTACKTIME_01] : m_uint32Values[UNIT_FIELD_BASEATTACKTIME];

	time = std::max(1000,float2int32(float(time)*GetFloatValue(UNIT_MOD_CAST_SPEED)));
	if(time>300000)		// just in case.. shouldn't happen though
		time=offhand ? m_uint32Values[UNIT_FIELD_BASEATTACKTIME_01] : m_uint32Values[UNIT_FIELD_BASEATTACKTIME];

	if(offhand)
		m_attackTimer_1 = getMSTime() + time;
	else
		m_attackTimer = getMSTime() + time;
}

bool Unit::isAttackReady(bool offhand)
{
	if(offhand)
		return (getMSTime() >= m_attackTimer_1) ? true : false;
	else
		return (getMSTime() >= m_attackTimer) ? true : false;
}

void Unit::ReplaceAIInterface(AIInterface *new_interface) 
{ 
	delete m_aiInterface;	//be carefull when you do this. Might screw unit states !
	m_aiInterface = new_interface; 
}

void UnitChain::AddUnit(Unit* u)
{
	m_units.insert(u);
	u->m_chain = this;
}
 
void UnitChain::RemoveUnit(Unit* u)
{
	m_units.erase(u);
	u->m_chain = NULL;
 
	if (m_units.size() == 0 && !m_persist)
		delete this;
}

void Unit::RemoveStealth()
{
	if( m_stealth != 0 )
	{
		RemoveAura( m_stealth );
		m_stealth = 0;
	}
}

void Unit::RemoveInvisibility()
{
	if( m_invisibility != 0 )
	{
		RemoveAura( m_invisibility );
		m_invisibility = 0;
	}
}

//what is an Immobilize spell ? Have to add it later to spell effect handler
void Unit::EventStunOrImmobilize()
{
	if( trigger_on_stun )
	{
		if( trigger_on_stun_chance < 100 && !Rand( trigger_on_stun_chance ) )
			return;

		CastSpell(this, trigger_on_stun, true);
	}
}

// Proc on chill effects (such as frostbolt slow effect)
void Unit::EventChill(Unit *proc_target)
{
	if ( this == proc_target || proc_target == NULL )
		return; //how and why would we chill ourselfs

	if( trigger_on_chill )
	{
		if( trigger_on_chill_chance < 100 && !Rand( trigger_on_chill_chance ) )
			return;

		CastSpell(proc_target, trigger_on_chill, true);
	}
}

void Unit::SetTriggerStunOrImmobilize(uint32 newtrigger,uint32 new_chance)
{
	trigger_on_stun = newtrigger;
	trigger_on_stun_chance = new_chance;
}

void Unit::SetTriggerChill(uint32 newtrigger,uint32 new_chance)
{
	trigger_on_chill = newtrigger;
	trigger_on_chill_chance = new_chance;
}
