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
#include "Strike.h"

Striker::Striker(Unit* pAttacker, Unit* pVictim, uint32 weapon_damage_type, SpellEntry* ability, int32 add_damage, int32 pct_dmg_mod, uint32 exclusive_damage, bool disable_proc, bool skip_hit_check )
{
	this->pAttacker = pAttacker;
	this->pVictim = pVictim;
	this->weapon_damage_type = weapon_damage_type;
	this->ability = ability;
	this->add_damage = add_damage;
	this->pct_dmg_mod = pct_dmg_mod;
	this->exclusive_damage = exclusive_damage;
	this->disable_proc = disable_proc;
	this->skip_hit_check = skip_hit_check;

	vsk = 0;
	diffVcapped = 0;
	diffAcapped = 0;
	SubClassSkill = 0;

	hitchance = 0;
	dodge = 0;
	parry = 0;
	block = 0;
}

uint32 Striker::GetSpellDidHitResult(){
	GetAttackerVictimSkills();
	FillHitChances();
	//==========================================================================================
	//==============================One Roll Processing=========================================
	//==========================================================================================
	//--------------------------------cummulative chances generation----------------------------
	float chances[4];
	chances[0]=std::max(0.0f,100.0f-hitchance);
	chances[1]=chances[0]+dodge;
	chances[2]=chances[1]+parry;
	chances[3]=chances[2]+block;

	//--------------------------------roll------------------------------------------------------
	float Roll = RandomFloat(100.0f);
	uint32 r = 0;
	while (r<4&&Roll>chances[r])
	{
		r++;
	}

	uint32 roll_results[5] = { SPELL_DID_HIT_MISS,SPELL_DID_HIT_DODGE,SPELL_DID_HIT_DEFLECT,SPELL_DID_HIT_BLOCK,SPELL_DID_HIT_SUCCESS };
	return roll_results[r];
}
void Striker::Deal(){
//==========================================================================================
//==============================Unacceptable Cases Processing===============================
//==========================================================================================
	if(!pVictim->isAlive() || !pAttacker->isAlive()  || pAttacker->IsStunned() || pAttacker->IsPacified() || pAttacker->IsFeared())
		return;
	if(!isAttackable(pAttacker,pVictim,false)){
		if(pAttacker->IsPlayer())
			static_cast< Player* >( pAttacker )->GetSession()->OutPacket(SMSG_ATTACKSWING_CANT_ATTACK);
		return;
	}
	if(!pAttacker->isInFront(pVictim))
		if(pAttacker->IsPlayer())
		{
			static_cast< Player* >( pAttacker )->GetSession()->OutPacket(SMSG_ATTACKSWING_BADFACING);
			return;
		}
//==========================================================================================
//==============================Variables Initialization====================================
//==========================================================================================
	dealdamage dmg			  = {0,0,0};
	
	Item * it = NULL;
	
	float glanc              = 0.0f;
	float crit				 = 0.0f;
	float crush              = 0.0f;

	uint32 targetEvent		 = 0;
	uint32 hit_status		 = 0;

	uint32 blocked_damage	 = 0;
	int32  realdamage		 = 0;

	uint32 vstate			 = 1;
	uint32 aproc			 = 0;
	uint32 vproc			 = 0;
	   
	backAttack				 = pAttacker->isInBack( pVictim );
	bool disable_dR			 = false;

	vsk = 0;
	diffVcapped = 0;
	diffAcapped = 0;
	SubClassSkill = 0;

	hitchance = 0;
	dodge = 0;
	parry = 0;
	block = 0;
	
	GetAttackerVictimSkills();

	if(!skip_hit_check )
	{
		FillHitChances();
	} else{
		hitchance = 100.0f;
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}

	if(ability)
		dmg.school_type = ability->School;
	else
	{
		if (pAttacker->GetTypeId() == TYPEID_UNIT)
			dmg.school_type = static_cast< Creature* >( pAttacker )->BaseAttackType;
		else
			dmg.school_type = SCHOOL_NORMAL;
	}

	if( pAttacker->IsPlayer() )
	{	  
		switch( weapon_damage_type )
		{
		case MELEE:   // melee main hand weapon
			if (it && it->GetProto())
				dmg.school_type = it->GetProto()->Damage[0].Type;
			break;
		case OFFHAND: // melee offhand weapon (dualwield)
			hit_status |= HITSTATUS_DUALWIELD;//animation
			if (it && it->GetProto())
				dmg.school_type = it->GetProto()->Damage[0].Type;
			break;
		case RANGED:  // ranged weapon
			if (it && it->GetProto())
				dmg.school_type = it->GetProto()->Damage[0].Type;
			break;
		}
		crit = pAttacker->GetFloatValue(PLAYER_CRIT_PERCENTAGE);
	}
	else
	{
		crit = 5.0f; //will be modified later
	}

//--------------------------------crushing blow chance--------------------------------------
	if(pVictim->IsPlayer()&&!pAttacker->IsPlayer()&&!ability && !dmg.school_type)
	{
		if(diffVcapped>=15.0f)
			crush = -15.0f+2.0f*diffVcapped; 
		else 
			crush = 0.0f;
	}
//--------------------------------glancing blow chance--------------------------------------
	if(pAttacker->IsPlayer()&&!pVictim->IsPlayer()&&!ability)
	{
		glanc = 10.0f + diffAcapped;
		if(glanc<0)
			glanc = 0.0f;
	}
//==========================================================================================
//==============================Advanced Chances Modifications==============================
//==========================================================================================
//--------------------------------by talents------------------------------------------------
	if(pVictim->IsPlayer())
	{
		if( weapon_damage_type != RANGED )
		{
			crit += static_cast< Player* >(pVictim)->res_M_crit_get();
		}
		else 
		{
			crit += static_cast< Player* >(pVictim)->res_R_crit_get(); //pAttacker could be ability but in that case we overwrite the value
		}
	}
	crit += (float)(pVictim->AttackerCritChanceMod[0]);
//--------------------------------by skill difference---------------------------------------



	crit += pVictim->IsPlayer() ? vsk * 0.04f : min( vsk * 0.2f, 0.0f ); 

	if(ability && ability->SpellGroupType)
	{
		SM_FFValue(pAttacker->SM_CriticalChance,&crit,ability->SpellGroupType);
	}
//--------------------------------by ratings------------------------------------------------
	crit -= pVictim->IsPlayer() ? static_cast< Player* >(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) : 0.0f;
	if(crit<0) crit=0.0f;
	

//--------------------------------by damage type and by weapon type-------------------------
	if( weapon_damage_type == RANGED ) 
	{
		glanc=0.0f;
	}

//--------------------------------by victim state-------------------------------------------
	if(pVictim->IsPlayer()&&pVictim->GetStandState()) //every not standing state is >0
	{
		crush = 0.0f;
		crit = 100.0f;
	}

//==========================================================================================
//==============================One Roll Processing=========================================
//==========================================================================================
//--------------------------------cummulative chances generation----------------------------
	float chances[7];
	chances[0]=std::max(0.0f,100.0f-hitchance);
	chances[1]=chances[0]+dodge;
	chances[2]=chances[1]+parry;
	chances[3]=chances[2]+glanc;
	chances[4]=chances[3]+block;
	chances[5]=chances[4]+crit;
	chances[6]=chances[5]+crush;
//--------------------------------roll------------------------------------------------------
	float Roll = RandomFloat(100.0f);
	uint32 r = 0;
	while (r<7&&Roll>chances[r])
	{
		r++;
	}
//--------------------------------postroll processing---------------------------------------
	uint32 abs = 0;

	switch(r)
	{ 
//--------------------------------miss------------------------------------------------------
	case 0:
		hit_status |= HITSTATUS_MISS;
		// dirty ai agro fix
		if(pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetAIInterface()->GetNextTarget() == NULL)
			pVictim->GetAIInterface()->AttackReaction(pAttacker, 1, 0);
		break;
//--------------------------------dodge-----------------------------------------------------
	case 1:
		// dirty ai agro fix
		if(pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetAIInterface()->GetNextTarget() == NULL)
			pVictim->GetAIInterface()->AttackReaction(pAttacker, 1, 0);

		CALL_SCRIPT_EVENT(pVictim, OnTargetDodged)(pAttacker);
		CALL_SCRIPT_EVENT(pAttacker, OnDodged)(pAttacker);
		targetEvent = 1;
		vstate = DODGE;
		vproc |= PROC_ON_DODGE_VICTIM;
		pVictim->Emote(EMOTE_ONESHOT_PARRYUNARMED);			// Animation
		//allmighty warrior overpower
		if( pAttacker->IsPlayer() && static_cast< Player* >( pAttacker )->getClass() == WARRIOR )
		{
			static_cast< Player* >( pAttacker )->AddComboPoints( pVictim->GetGUID(), 1 );
			static_cast< Player* >( pAttacker )->UpdateComboPoints();
			if( !sEventMgr.HasEvent( static_cast< Player* >( pAttacker ), EVENT_COMBO_POINT_CLEAR_FOR_TARGET ) )
				sEventMgr.AddEvent( static_cast< Player* >( pAttacker ), &Player::NullComboPoints, (uint32)EVENT_COMBO_POINT_CLEAR_FOR_TARGET, (uint32)5000, (uint32)1, (uint32)0 );
			else
				sEventMgr.ModifyEventTimeLeft( static_cast< Player* >( pAttacker ), EVENT_COMBO_POINT_CLEAR_FOR_TARGET, 5000 ,0 );
		}
		pVictim->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_DODGE_BLOCK);	//SB@L: Enables spells requiring dodge
		if(!sEventMgr.HasEvent(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE))
			sEventMgr.AddEvent(pVictim,&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_DODGE_BLOCK,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000,1,0);
		else sEventMgr.ModifyEventTimeLeft(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000,0);
		break;
//--------------------------------parry-----------------------------------------------------
	case 2:
		// dirty ai agro fix
		if(pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetAIInterface()->GetNextTarget() == NULL)
			pVictim->GetAIInterface()->AttackReaction(pAttacker, 1, 0);

		CALL_SCRIPT_EVENT(pVictim, OnTargetParried)(pAttacker);
		CALL_SCRIPT_EVENT(pAttacker, OnParried)(pAttacker);
		targetEvent = 3;
		vstate = PARRY;
		pVictim->Emote(EMOTE_ONESHOT_PARRYUNARMED);			// Animation
		if(pVictim->IsPlayer())
		{
			pVictim->SetFlag( UNIT_FIELD_AURASTATE,AURASTATE_FLAG_PARRY );	//SB@L: Enables spells requiring parry
			if(!sEventMgr.HasEvent( pVictim, EVENT_PARRY_FLAG_EXPIRE ) )
				sEventMgr.AddEvent( pVictim, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_PARRY,EVENT_PARRY_FLAG_EXPIRE, 5000, 1, 0 );
			else 
				sEventMgr.ModifyEventTimeLeft( pVictim, EVENT_PARRY_FLAG_EXPIRE, 5000 );
			if( static_cast< Player* >( pVictim )->getClass() == 1 || static_cast< Player* >( pVictim )->getClass() == 4 )//warriors for 'revenge' and rogues for 'riposte'
			{
				pVictim->SetFlag( UNIT_FIELD_AURASTATE,AURASTATE_FLAG_DODGE_BLOCK );	//SB@L: Enables spells requiring dodge
				if(!sEventMgr.HasEvent( pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE ) )
					sEventMgr.AddEvent( pVictim, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_DODGE_BLOCK, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000, 1, 0 );
				else 
					sEventMgr.ModifyEventTimeLeft( pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000 );
			}
		}
		break;
//--------------------------------not miss,dodge or parry-----------------------------------
	default:
		hit_status |= HITSTATUS_HITANIMATION;//hit animation on victim
		if( pVictim->SchoolImmunityList[0] )
			vstate = IMMUNE;		
		else
		{
//--------------------------------state proc initialization---------------------------------
			vproc |= PROC_ON_ANY_DAMAGE_VICTIM;			
			if( weapon_damage_type != RANGED )
			{
				aproc |= PROC_ON_MELEE_ATTACK;
				vproc |= PROC_ON_MELEE_ATTACK_VICTIM;
			}
			else
			{
				aproc |= PROC_ON_RANGED_ATTACK;
				vproc |= PROC_ON_RANGED_ATTACK_VICTIM;
				if(ability && ability->Id==3018 && pAttacker->IsPlayer() && pAttacker->getClass()==HUNTER)
					aproc |= PROC_ON_AUTO_SHOT_HIT;
			}
//--------------------------------base damage calculation-----------------------------------
			if(exclusive_damage)
				dmg.full_damage = exclusive_damage;
			else
			{
				if( weapon_damage_type == MELEE && ability )
					dmg.full_damage = CalculateDamage( pAttacker, pVictim, MELEE, ability->SpellGroupType, ability );
				else			
					dmg.full_damage = CalculateDamage( pAttacker, pVictim, weapon_damage_type, 0, ability );
			}

			if( pct_dmg_mod > 0 )
				dmg.full_damage = float2int32( dmg.full_damage *  ( float( pct_dmg_mod) / 100.0f ) );

			dmg.full_damage += add_damage;

			if(ability && ability->SpellGroupType)
			{	
				SM_FIValue(((Unit*)pAttacker)->SM_FDamageBonus,&dmg.full_damage,ability->SpellGroupType);
				SM_PIValue(((Unit*)pAttacker)->SM_PDamageBonus,&dmg.full_damage,ability->SpellGroupType);
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
				int spell_flat_modifers=0;
				int spell_pct_modifers=0;
				SM_FIValue(((Unit*)pAttacker)->SM_FDamageBonus,&spell_flat_modifers,ability->SpellGroupType);
				SM_FIValue(((Unit*)pAttacker)->SM_PDamageBonus,&spell_pct_modifers,ability->SpellGroupType);
				if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
					printf("!!!!!spell dmg bonus mod flat %d , spell dmg bonus pct %d , spell dmg bonus %d, spell group %u\n",spell_flat_modifers,spell_pct_modifers,dmg.full_damage,ability->SpellGroupType);
#endif
			}
			dmg.full_damage += pVictim->DamageTakenMod[dmg.school_type];
			if( weapon_damage_type == RANGED )
			{
				dmg.full_damage += pVictim->RangedDamageTaken;
			}
			
			if( ability && ability->MechanicsType == MECHANIC_BLEEDING )
				disable_dR = true; 
			
			//float summaryPCTmod = (pVictim->DamageTakenPctMod[dmg.school_type] / 100.0f) + (GetDamageDonePctMod( dmg.school_type ) / 100.0f) + 1;

			//a bit dirty fix
			/*if( ability != NULL && ability->NameHash == SPELL_HASH_SHRED )
			{
				summaryPCTmod *= 1 + pVictim->ModDamageTakenByMechPCT[MECHANIC_BLEEDING];
			}*/

			//dmg.full_damage = (dmg.full_damage < 0) ? 0 : float2int32(dmg.full_damage*summaryPCTmod);

			// burlex: fixed this crap properly
			float inital_dmg = float(dmg.full_damage);
			float dd_mod = pAttacker->GetDamageDonePctMod( dmg.school_type );
			if( pVictim->DamageTakenPctMod[dmg.school_type] != 1.0f )
				dmg.full_damage += float2int32( ( inital_dmg * pVictim->DamageTakenPctMod[ dmg.school_type ] ) - inital_dmg );

			if( dd_mod > 0.0f )
				dmg.full_damage += float2int32( ( inital_dmg * dd_mod) - inital_dmg );

			if( ability != NULL && ability->NameHash == SPELL_HASH_SHRED )
				dmg.full_damage += float2int32( ( inital_dmg * (1 + pVictim->ModDamageTakenByMechPCT[MECHANIC_BLEEDING]) ) - inital_dmg );

			//pet happiness state dmg modifier
			if( pAttacker->IsPet() && !static_cast<Pet*>(pAttacker)->IsSummon() )
				dmg.full_damage = ( dmg.full_damage <= 0 ) ? 0 : float2int32( dmg.full_damage * static_cast< Pet* >( pAttacker )->GetHappinessDmgMod() );

			if(dmg.full_damage < 0)
				dmg.full_damage = 0;
//--------------------------------check for special hits------------------------------------
			switch(r)
			{
//--------------------------------glancing blow---------------------------------------------
			case 3:
				{
					float low_dmg_mod = 1.5f - (0.05f * diffAcapped);
					if(pAttacker->getClass() == MAGE || pAttacker->getClass() == PRIEST || pAttacker->getClass() == WARLOCK) //casters = additional penalty.
					{
						low_dmg_mod -= 0.7f;
					}
					if(low_dmg_mod<0.01)
						low_dmg_mod = 0.01f;
					if(low_dmg_mod>0.91)
						low_dmg_mod = 0.91f;
					float high_dmg_mod = 1.2f - (0.03f * diffAcapped);
					if(pAttacker->getClass() == MAGE || pAttacker->getClass() == PRIEST || pAttacker->getClass() == WARLOCK) //casters = additional penalty.
					{
						high_dmg_mod -= 0.3f;
					}
					if(high_dmg_mod>0.99)
						high_dmg_mod = 0.99f;
					if(high_dmg_mod<0.2)
						high_dmg_mod = 0.2f;

					float damage_reduction = (high_dmg_mod + low_dmg_mod) / 2.0f;
					if(damage_reduction > 0)
					{
							dmg.full_damage = float2int32(damage_reduction * float(dmg.full_damage));
					}
					hit_status |= HITSTATUS_GLANCING;
				}
				break;
//--------------------------------block-----------------------------------------------------
			case 4:
				{
					Item* shield = static_cast< Player* >( pVictim )->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
					if( shield != NULL )
					{
						targetEvent = 2;
						pVictim->Emote(EMOTE_ONESHOT_PARRYSHIELD);// Animation

						if( shield->GetProto()->InventoryType == INVTYPE_SHIELD )
						{
							float block_multiplier = ( 100.0f + float( static_cast< Player* >( pVictim )->m_modblockabsorbvalue ) ) / 100.0f;
							if( block_multiplier < 1.0f )block_multiplier = 1.0f;

							blocked_damage = float2int32( (float( shield->GetProto()->Block ) + ( float( static_cast< Player* >( pVictim )->m_modblockvaluefromspells + pVictim->GetUInt32Value( PLAYER_RATING_MODIFIER_BLOCK ) )) + ( ( float( pVictim->GetUInt32Value( UNIT_FIELD_STAT0 ) ) / 20.0f ) - 1.0f ) ) * block_multiplier);
						}
						else
						{
							blocked_damage = 0;
						}

						if(dmg.full_damage <= (int32)blocked_damage)
						{
							CALL_SCRIPT_EVENT(pVictim, OnTargetBlocked)(pAttacker, blocked_damage);
							CALL_SCRIPT_EVENT(pAttacker, OnBlocked)(pVictim, blocked_damage);
							vstate = BLOCK;
							vproc |= PROC_ON_BLOCK_VICTIM;
						}
						if( pVictim->IsPlayer() )//not necessary now but we'll have blocking mobs in future
						{            
							pVictim->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_DODGE_BLOCK);	//SB@L: Enables spells requiring dodge
							if(!sEventMgr.HasEvent(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE))
								sEventMgr.AddEvent(pVictim,&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_DODGE_BLOCK,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000,1,0);
							else 
								sEventMgr.ModifyEventTimeLeft(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000);
						}
					}
				}
				break;
//--------------------------------critical hit----------------------------------------------
			case 5:
				{
					hit_status |= HITSTATUS_CRICTICAL;
					int32 dmgbonus = dmg.full_damage;
					//sLog.outString( "DEBUG: Critical Strike! Full_damage: %u" , dmg.full_damage );
					if(ability && ability->SpellGroupType)
					{
						int32 dmg_bonus_pct = 100;
						SM_FIValue(pAttacker->SM_PCriticalDamage,&dmg_bonus_pct,ability->SpellGroupType);
						dmgbonus = float2int32( float(dmgbonus) * (float(dmg_bonus_pct)/100.0f) );
					}
					
					//sLog.outString( "DEBUG: After CritMeleeDamageTakenPctMod: %u" , dmg.full_damage );
					if(pAttacker->IsPlayer())
					{
						if( weapon_damage_type != RANGED )
						{
							float critextra=float(static_cast< Player* >( pAttacker )->m_modphyscritdmgPCT);
							dmg.full_damage += int32((float(dmg.full_damage)*critextra/100.0f));
						}
						if(!pVictim->IsPlayer())
							dmg.full_damage += float2int32(dmg.full_damage*static_cast< Player* >( pAttacker )->IncreaseCricticalByTypePCT[((Creature*)pVictim)->GetCreatureName() ? ((Creature*)pVictim)->GetCreatureName()->Type : 0]);
					//sLog.outString( "DEBUG: After IncreaseCricticalByTypePCT: %u" , dmg.full_damage );
					}

					dmg.full_damage += dmgbonus;

					if( weapon_damage_type == RANGED )
						dmg.full_damage = dmg.full_damage - float2int32(dmg.full_damage * pAttacker->CritRangedDamageTakenPctMod[dmg.school_type]) / 100;
					else 
						dmg.full_damage = dmg.full_damage - float2int32(dmg.full_damage * pAttacker->CritMeleeDamageTakenPctMod[dmg.school_type]) / 100;

					if(pVictim->IsPlayer())
					{
						//Resilience is a special new rating which was created to reduce the effects of critical hits against your character.
						float dmg_reduction_pct = 2.0f * static_cast< Player* >(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) / 100.0f;
						if( dmg_reduction_pct > 1.0f )
							dmg_reduction_pct = 1.0f; //we cannot resist more then he is criticalling us, there is no point of the critical then :P
						dmg.full_damage = float2int32( dmg.full_damage - dmg.full_damage*dmg_reduction_pct );
						//sLog.outString( "DEBUG: After Resilience check: %u" , dmg.full_damage );
					}
					
					pVictim->Emote(EMOTE_ONESHOT_WOUNDCRITICAL);
					vproc |= PROC_ON_CRIT_HIT_VICTIM;
					aproc |= PROC_ON_CRIT_ATTACK;
					if( weapon_damage_type == RANGED )
					{
						vproc |= PROC_ON_RANGED_CRIT_ATTACK_VICTIM;
						aproc |= PROC_ON_RANGED_CRIT_ATTACK;
					}

					if(pAttacker->IsPlayer())
					{
						pAttacker->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_CRITICAL);	//SB@L: Enables spells requiring critical strike
						if(!sEventMgr.HasEvent(pAttacker,EVENT_CRIT_FLAG_EXPIRE))
							sEventMgr.AddEvent((Unit*)pAttacker,&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_CRITICAL,EVENT_CRIT_FLAG_EXPIRE,5000,1,0);
						else sEventMgr.ModifyEventTimeLeft(pAttacker,EVENT_CRIT_FLAG_EXPIRE,5000);
					}

					CALL_SCRIPT_EVENT(pVictim, OnTargetCritHit)(pAttacker, float(dmg.full_damage));
					CALL_SCRIPT_EVENT(pAttacker, OnCritHit)(pVictim, float(dmg.full_damage));
				}
				break;
//--------------------------------crushing blow---------------------------------------------
			case 6:
				hit_status |= HITSTATUS_CRUSHINGBLOW;
				dmg.full_damage = (dmg.full_damage * 3) >> 1;
				break;
//--------------------------------regular hit-----------------------------------------------
			default:
				break;	
			}
//==========================================================================================
//==============================Post Roll Damage Processing=================================
//==========================================================================================
//--------------------------absorption------------------------------------------------------
			uint32 dm = dmg.full_damage;
			abs = pVictim->AbsorbDamage(dmg.school_type,(uint32*)&dm);
		
			if(dmg.full_damage > (int32)blocked_damage)
			{
				uint32 sh = pVictim->ManaShieldAbsorb(dmg.full_damage);
//--------------------------armor reducing--------------------------------------------------
				if(sh)
				{
					dmg.full_damage -= sh;
					if(dmg.full_damage && !disable_dR)
						pAttacker->CalculateResistanceReduction(pVictim,&dmg, ability);
					dmg.full_damage += sh;
					abs+=sh;
				}
				else if(!disable_dR)
					pAttacker->CalculateResistanceReduction(pVictim,&dmg, ability);	
			}

			if(abs)
				vproc |= PROC_ON_ABSORB;

			if (dmg.school_type == SCHOOL_NORMAL)
			{
				abs+=dmg.resisted_damage;
				dmg.resisted_damage=0;
			}

			realdamage = dmg.full_damage-abs-dmg.resisted_damage-blocked_damage;
			if(realdamage < 0)
			{
				realdamage = 0;
				vstate = IMMUNE;
				hit_status |= HITSTATUS_ABSORBED;
			}
		}
		break;
	}

//==========================================================================================
//==============================Post Roll Special Cases Processing==========================
//==========================================================================================
//--------------------------special states processing---------------------------------------
	if(pVictim->GetTypeId() == TYPEID_UNIT)
	{
		if(pVictim->GetAIInterface() && (pVictim->GetAIInterface()->getAIState()== STATE_EVADE ||
										(pVictim->GetAIInterface()->GetIsSoulLinked() && pVictim->GetAIInterface()->getSoullinkedWith() != pAttacker)))
		{
			vstate = EVADE;
			realdamage = 0;
			dmg.full_damage = 0;
			dmg.resisted_damage = 0;
		}
	}
	if(pVictim->GetTypeId() == TYPEID_PLAYER && static_cast< Player* >(pVictim)->GodModeCheat == true)
	{
		dmg.resisted_damage = dmg.full_damage; //godmode
	}
//--------------------------dirty fixes-----------------------------------------------------
	//vstate=1-wound,2-dodge,3-parry,4-interrupt,5-block,6-evade,7-immune,8-deflect	
	// the above code was remade it for reasons : damage shield needs moslty same flags as handleproc + dual wield should proc too ?
	if( !disable_proc)// && weapon_damage_type != OFFHAND )
    {
		pAttacker->HandleProc(aproc,pVictim, ability,realdamage,abs,weapon_damage_type + 1); //maybe using dmg.resisted_damage is better sometimes but then if using godmode dmg is resisted instead of absorbed....bad
		pAttacker->m_procCounter = 0;

		pVictim->HandleProc(vproc,pAttacker, ability,realdamage,abs,weapon_damage_type + 1);
		pVictim->m_procCounter = 0;

		if(realdamage > 0)
		{
			pVictim->HandleProcDmgShield(vproc,pAttacker);
			pAttacker->HandleProcDmgShield(aproc,pVictim);
		}
	}
//--------------------------spells triggering-----------------------------------------------
	if(realdamage > 0 && ability == 0)
	{
		if( pAttacker->IsPlayer() && static_cast< Player* >( pAttacker )->m_onStrikeSpells.size() )
		{
			SpellCastTargets targets;
			targets.m_unitTarget = pVictim->GetGUID();
			targets.m_targetMask = 0x2;
			Spell* cspell;

			// Loop on hit spells, and strike with those.
			for( map< SpellEntry*, pair< uint32, uint32 > >::iterator itr = static_cast< Player* >( pAttacker )->m_onStrikeSpells.begin();
				itr != static_cast< Player* >( pAttacker )->m_onStrikeSpells.end(); ++itr )
			{
				if( itr->second.first )
				{
					// We have a *periodic* delayed spell.
					uint32 t = getMSTime();
					if( t > itr->second.second )  // Time expired
					{
						// Set new time
						itr->second.second = t + itr->second.first;
					}

					// Cast.
					cspell = new Spell(pAttacker, itr->first, true, NULL);
					cspell->prepare(&targets);
				}
				else
				{
					cspell = new Spell(pAttacker, itr->first, true, NULL);
					cspell->prepare(&targets);
				}			
			}
		}

		if( pAttacker->IsPlayer() && static_cast< Player* >( pAttacker )->m_onStrikeSpellDmg.size() )
		{
			map< uint32, OnHitSpell >::iterator it2 = static_cast< Player* >( pAttacker )->m_onStrikeSpellDmg.begin();
			map< uint32, OnHitSpell >::iterator itr;
			uint32 min_dmg, max_dmg, range, dmg;
			for(; it2 != static_cast< Player* >( pAttacker )->m_onStrikeSpellDmg.end(); )
			{
				itr = it2;
				++it2;

				min_dmg = itr->second.mindmg;
				max_dmg = itr->second.maxdmg;
				range = min_dmg - max_dmg;
				dmg = min_dmg;
				if(range) range += RandomUInt(range);

				pAttacker->SpellNonMeleeDamageLog(pVictim, itr->second.spellid, dmg, true);
			}
		}

		// refresh judgements
		// TODO: find the opcode to refresh the aura or just remove it and re add it
		// rather than fuck with duration
		// DONE: Remove + readded it :P
		for( uint32 x = MAX_POSITIVE_AURAS; x <= MAX_AURAS; x++ )
		{
			if( pVictim->m_auras[x] != NULL && pVictim->m_auras[x]->GetUnitCaster() != NULL && pVictim->m_auras[x]->GetUnitCaster()->GetGUID() == pAttacker->GetGUID() && pVictim->m_auras[x]->GetSpellProto()->buffIndexType == SPELL_TYPE_INDEX_JUDGEMENT )
			{
				Aura * aur = pVictim->m_auras[x];
				SpellEntry * spinfo = aur->GetSpellProto();
				aur->Remove();
				Spell * sp = new Spell( pAttacker , spinfo , true , NULL );
				SpellCastTargets tgt;
				tgt.m_unitTarget = pVictim->GetGUID();
				sp->prepare( &tgt );
				/*pVictim->m_auras[x]->SetDuration( 20000 ); // 20 seconds?
				sEventMgr.ModifyEventTimeLeft( pVictim->m_auras[x], EVENT_AURA_REMOVE, 20000 );
			
				// We have to tell the target that the aura has been refreshed.
				if( pVictim->IsPlayer() )
				{
					WorldPacket data( 5 );
					data.SetOpcode( SMSG_UPDATE_AURA_DURATION );
					data << (uint8)pVictim->m_auras[x]->GetAuraSlot() << 20000;
					static_cast< Player* >( pVictim )->GetSession()->SendPacket( &data );
				}
				*/
				// However, there is also an opcode that tells the caster that the aura has been refreshed.
				// pAttacker isn't implemented anywhere else in the source, so I can't work on that part :P
				// (The 'cooldown' meter on the target frame that shows how long the aura has until expired does not get reset)=
				// I would say break; here, but apparently in Ascent, one paladin can have multiple judgements on the target. No idea if pAttacker is blizzlike or not.
			}
		}

	}
	
//==========================================================================================
//==============================Data Sending================================================
//==========================================================================================
	WorldPacket data(SMSG_ATTACKERSTATEUPDATE, 70);
	//0x4--dualwield,0x10 miss,0x20 absorbed,0x80 crit,0x4000 -glancing,0x8000-crushing
	//only for melee!

	if( !ability )
	{
		if( dmg.full_damage > 0 )
		{
			if( dmg.full_damage == (int32)abs )
				hit_status |= HITSTATUS_ABSORBED;
			else if (dmg.full_damage <= (int32)dmg.resisted_damage)
			{
				hit_status |= HITSTATUS_RESIST;
				dmg.resisted_damage = dmg.full_damage;
			}
		}

		if( dmg.full_damage < 0 )
			dmg.full_damage = 0;

		if( realdamage < 0 )
			realdamage = 0;

		data << (uint32)hit_status;   
		data << pAttacker->GetNewGUID();
		data << pVictim->GetNewGUID();
		
		data << (uint32)realdamage;		 // Realdamage;
		data << (uint8)1;				   // Damage type counter / swing type

		data << (uint32)g_spellSchoolConversionTable[dmg.school_type];				  // Damage school
		data << (float)dmg.full_damage;	 // Damage float
		data << (uint32)dmg.full_damage;	// Damage amount
		data << (uint32)abs;// Damage absorbed
		data << (uint32)dmg.resisted_damage;				  // Damage resisted

		data << (uint32)vstate;			 // new victim state
		data << (uint32)0x03e8;					// can be 0,1000 or -1
		data << (uint32)0;				  // unknown
		data << (uint32)blocked_damage;	 // Damage amount blocked
		//data << (uint32) 0;

		pAttacker->SendMessageToSet(&data, pAttacker->IsPlayer());
	}
	else
	{
		if( realdamage > 0 )//FIXME: add log for miss,block etc for ability and ranged
		{
			// here we send "dmg.resisted_damage" for "AbsorbedDamage", "0" for "ResistedDamage", and "false" for "PhysicalDamage" even though "School" is "SCHOOL_NORMAL"   o_O
			pAttacker->SendSpellNonMeleeDamageLog( pAttacker, pVictim, ability->Id, realdamage, dmg.school_type, dmg.resisted_damage, 0, false, blocked_damage, ( ( hit_status & HITSTATUS_CRICTICAL ) != 0 ), true );
		}
		//FIXME: add log for miss,block etc for ability and ranged
		//example how it works
		//SendSpellLog(pAttacker,pVictim,ability->Id,SPELL_LOG_MISS);
	}

	if(ability && realdamage==0)
	{	
		pAttacker->SendSpellLog(pAttacker,pVictim,ability->Id,SPELL_LOG_RESIST);
	}
//==========================================================================================
//==============================Damage Dealing==============================================
//==========================================================================================

	if(pAttacker->IsPlayer() && ability)
		static_cast< Player* >( pAttacker )->m_casted_amount[dmg.school_type]=(uint32)(realdamage+abs);
	if(realdamage)
	{
		pAttacker->DealDamage(pVictim, realdamage, 0, targetEvent, 0);
		//pVictim->HandleProcDmgShield(PROC_ON_MELEE_ATTACK_VICTIM,pAttacker);
//		HandleProcDmgShield(PROC_ON_MELEE_ATTACK_VICTIM,pVictim);

		if(pVictim->GetCurrentSpell())
			pVictim->GetCurrentSpell()->AddTime(0);
	}
	else
	{		
		// have to set attack target here otherwise it wont be set
		// because dealdamage is not called.
		//setAttackTarget(pVictim);
	}
//==========================================================================================
//==============================Post Damage Dealing Processing==============================
//==========================================================================================
//--------------------------durability processing-------------------------------------------
	if(pVictim->IsPlayer())
	{
		static_cast< Player* >( pVictim )->GetItemInterface()->ReduceItemDurability();
		if( !pAttacker->IsPlayer() )
		{
			Player *pr = static_cast< Player* >( pVictim );
			if( Rand( pr->GetSkillUpChance( SKILL_DEFENSE ) * sWorld.getRate( RATE_SKILLCHANCE ) ) )
			{
				pr->_AdvanceSkillLine( SKILL_DEFENSE, float2int32( 1.0f * sWorld.getRate(RATE_SKILLRATE)));
				pr->UpdateChances();
			}
		}
		else
		{
			 static_cast< Player* >( pAttacker )->GetItemInterface()->ReduceItemDurability();
		}
	}
	else
	{
		if(pAttacker->IsPlayer())//not pvp
		{
			static_cast< Player* >( pAttacker )->GetItemInterface()->ReduceItemDurability();
			Player* pr = static_cast< Player* >( pAttacker );
			if( Rand( pr->GetSkillUpChance( SubClassSkill) * sWorld.getRate( RATE_SKILLCHANCE ) ) )
			{
				pr->_AdvanceSkillLine( SubClassSkill, float2int32( 1.0f * sWorld.getRate(RATE_SKILLRATE)));
				//pr->UpdateChances();
			}
		}
	}
	//--------------------------rage processing-------------------------------------------------
	//http://www.wowwiki.com/Formulas:Rage_generation

	if( dmg.full_damage && pAttacker->IsPlayer() && pAttacker->GetPowerType() == POWER_TYPE_RAGE && !ability)
	{
		float val;
		float level = (float)pAttacker->getLevel();

		// Conversion Value
		float c = 0.0091107836f * level * level + 3.225598133f * level + 4.2652911f;

		// Hit Factor
		float f = ( weapon_damage_type == OFFHAND ) ? 1.75f : 3.5f;

		if( hit_status & HITSTATUS_CRICTICAL )
			f *= 2.0f;

		float s = 1.0f;

		// Weapon speed (normal)
		Item* weapon = ( static_cast< Player* >( pAttacker )->GetItemInterface())->GetInventoryItem( INVENTORY_SLOT_NOT_SET, ( weapon_damage_type == OFFHAND ? EQUIPMENT_SLOT_OFFHAND : EQUIPMENT_SLOT_MAINHAND ) );
		if( weapon == NULL )
		{
			if( weapon_damage_type == OFFHAND )
				s = pAttacker->GetUInt32Value( UNIT_FIELD_BASEATTACKTIME_01 ) / 1000.0f;
			else
				s = pAttacker->GetUInt32Value( UNIT_FIELD_BASEATTACKTIME ) / 1000.0f;
		}
		else
		{
			uint32 entry = weapon->GetEntry();
			ItemPrototype* pProto = ItemPrototypeStorage.LookupEntry( entry );
			if( pProto != NULL )
			{
				s = pProto->Delay / 1000.0f;
			}
		}

		val = ( 7.5f * dmg.full_damage / c + f * s ) / 2.0f;;
		val *= ( 1 + ( static_cast< Player* >( pAttacker )->rageFromDamageDealt / 100.0f ) );
		val *= 10;

		//float r = ( 7.5f * dmg.full_damage / c + f * s ) / 2.0f;
		//float p = ( 1 + ( static_cast< Player* >( pAttacker )->rageFromDamageDealt / 100.0f ) );
		//sLog.outDebug( "Rd(%i) d(%i) c(%f) f(%f) s(%f) p(%f) r(%f) rage = %f", realdamage, dmg.full_damage, c, f, s, p, r, val );

		pAttacker->ModUnsigned32Value( UNIT_FIELD_POWER2, (int32)val );
		if( pAttacker->GetUInt32Value( UNIT_FIELD_POWER2 ) > 1000 )
			pAttacker->ModUnsigned32Value( UNIT_FIELD_POWER2, 1000 - pAttacker->GetUInt32Value( UNIT_FIELD_POWER2 ) );

	}
		
	pAttacker->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_START_ATTACK);
//--------------------------extra strikes processing----------------------------------------
	if(!pAttacker->m_extraAttackCounter)
	{
		int32 extra_attacks = pAttacker->m_extraattacks;
		pAttacker->m_extraAttackCounter = true;
		pAttacker->m_extraattacks = 0;

		while(extra_attacks > 0)
		{
			extra_attacks--;
			pAttacker->Strike( pVictim, weapon_damage_type, NULL, 0, 0, 0, false, false);
		}

		pAttacker->m_extraAttackCounter = false;
	}

	if(pAttacker->m_extrastriketargets)
	{
		int32 m_extra = pAttacker->m_extrastriketargets;
		int32 m_temp = pAttacker->m_extrastriketargets;
		pAttacker->m_extrastriketargets = 0;

		for(set<Object*>::iterator itr = pAttacker->m_objectsInRange.begin(); itr != pAttacker->m_objectsInRange.end() && m_extra; ++itr)
		{
			if(m_extra == 0)
				break;
			if (!(*itr) || (*itr) == pVictim || !(*itr)->IsUnit())
				continue;


			if(pAttacker->CalcDistance(*itr) < 10.0f && isAttackable(pAttacker, (*itr)) && (*itr)->isInFront(pAttacker) && !((Unit*)(*itr))->IsPacified())
			{
				pAttacker->Strike( static_cast< Unit* >( *itr ), weapon_damage_type, ability, add_damage, pct_dmg_mod, exclusive_damage, false ,false );
				--m_extra;
			}
		}
		pAttacker->m_extrastriketargets = m_temp;
	}
}

void Striker::GetAttackerVictimSkills()
{
	int32 self_skill;
	int32 victim_skill;
	SubClassSkill	 = SKILL_UNARMED;
	uint32 vskill            = 0;
	Item * it = NULL;
	//==========================================================================================
	//==============================Victim Skill Base Calculation===============================
	//==========================================================================================
	if( pVictim->IsPlayer() )
	{
		vskill = static_cast< Player* >( pVictim )->_GetSkillLineCurrent( SKILL_DEFENSE );
		victim_skill = float2int32( vskill + static_cast< Player* >( pVictim )->CalcRating( PLAYER_RATING_MODIFIER_DEFENCE ) );
	}
	//--------------------------------mob defensive chances-------------------------------------
	else
	{
		victim_skill = pVictim->getLevel() * 5;
		if(pVictim->m_objectTypeId == TYPEID_UNIT) 
		{ 
			Creature * c = (Creature*)(pVictim);
			if(c&&c->GetCreatureName()&&c->GetCreatureName()->Rank == ELITE_WORLDBOSS)
			{
				victim_skill = std::max(victim_skill,((int32)pAttacker->getLevel()+3)*5); //used max to avoid situation when lowlvl hits boss.
			}
		} 
	}
	//==========================================================================================
	//==============================Attacker Skill Base Calculation=============================
	//==========================================================================================
	if(pAttacker->IsPlayer())
	{	  
		self_skill = 0;
		Player* pr = static_cast< Player* >( pAttacker ); 

		switch( weapon_damage_type )
		{
		case MELEE:   // melee main hand weapon
			it = pAttacker->disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL ) );
			break;
		case OFFHAND: // melee offhand weapon (dualwield)
			it = pAttacker->disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL ) );
			break;
		case RANGED:  // ranged weapon
			it = pAttacker->disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_RANGED_SKILL ) );
			break;
		}
		if(it && it->GetProto())
			SubClassSkill = GetSkillByProto(it->GetProto()->Class,it->GetProto()->SubClass);
		else
			SubClassSkill = SKILL_UNARMED;

		if(SubClassSkill==SKILL_FIST_WEAPONS) 
			SubClassSkill = SKILL_UNARMED;

		//chances in feral form don't depend on weapon skill
		if(pr->IsInFeralForm()) 
		{
			uint8 form = pr->GetShapeShift();
			if(form == FORM_CAT || form == FORM_BEAR || form == FORM_DIREBEAR)
			{
				SubClassSkill = SKILL_FERAL_COMBAT;
				// Adjust skill for Level * 5 for Feral Combat
				self_skill += pr->getLevel() * 5;
			}
		}
		self_skill += pr->_GetSkillLineCurrent(SubClassSkill);
	}
	else
	{
		self_skill = pAttacker->getLevel() * 5;
		if(pAttacker->m_objectTypeId == TYPEID_UNIT) 
		{ 
			Creature * c = (Creature*)(pAttacker);
			if(c&&c->GetCreatureName()&&c->GetCreatureName()->Rank == ELITE_WORLDBOSS)
				self_skill = std::max(self_skill,((int32)pVictim->getLevel()+3)*5);//used max to avoid situation when lowlvl hits boss.
		} 
	}


	//<THE SHIT> to avoid Linux bug. 
	diffVcapped = (float)self_skill;
	if(int32(pVictim->getLevel()*5)>victim_skill)
		diffVcapped -=(float)victim_skill;
	else
		diffVcapped -=(float)(pVictim->getLevel()*5);

	diffAcapped = (float)victim_skill;
	if(int32(pAttacker->getLevel()*5)>self_skill)
		diffAcapped -=(float)self_skill;
	else
		diffAcapped -=(float)(pAttacker->getLevel()*5);
	//<SHIT END>

	vsk = (float)self_skill - (float)victim_skill;
}

void Striker::FillHitChances()
{
	Item * it = NULL;

	float hitmodifier = 0;
	if( pVictim->IsPlayer() )
	{
		if( weapon_damage_type != RANGED && !backAttack )
		{
			//--------------------------------block chance----------------------------------------------
			block = pVictim->GetFloatValue(PLAYER_BLOCK_PERCENTAGE); //shield check already done in Update chances
			//--------------------------------dodge chance----------------------------------------------
			if( pVictim->m_stunned <= 0 ) 
			{
				dodge = pVictim->GetFloatValue( PLAYER_DODGE_PERCENTAGE );
			}
			//--------------------------------parry chance----------------------------------------------
			if( pVictim->can_parry && !pVictim->disarmed )
			{
				if( static_cast< Player* >( pVictim )->HasSpell( 3127 ) || static_cast< Player* >( pVictim )->HasSpell( 18848 ) )
				{
					parry = pVictim->GetFloatValue( PLAYER_PARRY_PERCENTAGE );
				}
			}
		}
	}
	//--------------------------------mob defensive chances-------------------------------------
	else
	{
		if( weapon_damage_type != RANGED && !backAttack && pVictim->m_stunned <= 0)
			dodge = pVictim->GetUInt32Value(UNIT_FIELD_STAT1) / 14.5f; // what is pAttacker value?
	}

	if(pAttacker->IsPlayer())
	{	
		Player* pr = static_cast< Player* >( pAttacker );
		hitmodifier = pr->GetHitFromMeleeSpell();  

		switch( weapon_damage_type )
		{
		case MELEE:   // melee main hand weapon
			hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );
			break;
		case OFFHAND: // melee offhand weapon (dualwield)
			hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );
			break;
		case RANGED:  // ranged weapon
			hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_RANGED_HIT );
			break;
		}
	}
	//--------------------------------by talents------------------------------------------------
	if(pVictim->IsPlayer()){
		if(weapon_damage_type == RANGED)
			hitmodifier += static_cast< Player* >(pVictim)->m_resist_hit[1];
		else
			hitmodifier += static_cast< Player* >(pVictim)->m_resist_hit[0];
	}


	//--------------------------------by damage type and by weapon type-------------------------
	if( weapon_damage_type == RANGED ) 
	{
		dodge=0.0f;
		parry=0.0f;
	}
	else if(pAttacker->IsPlayer())
	{
		it = static_cast< Player* >( pAttacker )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
		if( it != NULL && it->GetProto()->InventoryType == INVTYPE_WEAPON && !ability )//dualwield to-hit penalty
		{
			hitmodifier -= 19.0f;
		}
	}

	//--------------------------------by skill difference---------------------------------------
	if(vsk < 0){
		dodge = std::max( 0.0f, dodge - vsk * 0.04f );
		if( parry )
			parry = std::max( 0.0f, parry - vsk * 0.04f );
		if( block )
			block = std::max( 0.0f, block - vsk * 0.04f );
	}

	if( pVictim->IsPlayer() ){
		if( vsk > 0 )
			hitchance = std::max( hitchance, 95.0f + vsk * 0.02f);
		else
			hitchance = std::max( hitchance, 95.0f + vsk * 0.04f);
	}else{
		if(vsk >= -10 && vsk <= 10)
			hitchance = std::max( hitchance, 95.0f + vsk * 0.1f);
		else
			hitchance = std::max( hitchance, 93.0f + (vsk - 10.0f) * 0.4f);
	}
	hitchance += hitmodifier;

//--------------------------------by ratings------------------------------------------------
	if (pAttacker->IsPlayer())
	{
		hitchance += (weapon_damage_type == RANGED) ? static_cast< Player* >(pAttacker)->CalcRating( PLAYER_RATING_MODIFIER_RANGED_HIT ) : static_cast< Player* >(pAttacker)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );
		float expertise_bonus = static_cast< Player* >(pAttacker)->CalcRating( PLAYER_RATING_MODIFIER_EXPERTISE );
		if(weapon_damage_type == MELEE)
			expertise_bonus += static_cast< Player* >(pAttacker)->GetUInt32Value(PLAYER_EXPERTISE);
		else if(weapon_damage_type == OFFHAND)
			expertise_bonus += static_cast< Player* >(pAttacker)->GetUInt32Value(PLAYER_OFFHAND_EXPERTISE);
		dodge -= expertise_bonus;
		if(dodge<0) dodge=0.0f;
		parry -= expertise_bonus;
		if(parry<0) parry=0.0f;
	}

	if( ability && ability->SpellGroupType )
	{
		SM_FFValue( pAttacker->SM_FHitchance, &hitchance, ability->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		float spell_flat_modifers=0;
		SM_FFValue(SM_FHitchance,&spell_flat_modifers,ability->SpellGroupType);
		if(spell_flat_modifers!=0 )
			printf("!!!!!spell resist mod flat %f,  spell resist bonus %f, spell group %u\n",spell_flat_modifers,hitchance,ability->SpellGroupType);
#endif
	}
	//Hackfix for Surprise Attacks
	if(  pAttacker->IsPlayer() && ability && static_cast< Player* >( pAttacker )->m_finishingmovesdodge && ability->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE)
			dodge = 0.0f;
	
	if( ability != NULL && ability->Attributes & ATTRIBUTES_CANT_BE_DPB )
	{
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}
	
//--------------------------------by victim state-------------------------------------------
	if(pVictim->IsPlayer()&&pVictim->GetStandState()) //every not standing state is >0
	{
		hitchance = 100.0f;
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}

	if(backAttack)
	{
		//From the gametips:
		//|cffffd100Tip:|r Players cannot dodge, parry, or block attacks that come from behind them.
		if(pVictim->IsPlayer())
		{
			//However mobs can dodge attacks from behind
			dodge = 0.0f;
		}
		parry = 0.0f;
		block = 0.0f;
	}
}

Striker::~Striker(void)
{
}
