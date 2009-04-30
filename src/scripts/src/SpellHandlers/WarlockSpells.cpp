/****************************************************************************
 *
 * SpellHandler Plugin
 * Copyright (c) 2007 Team Ascent
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to Creative Commons,
 * 543 Howard Street, 5th Floor, San Francisco, California, 94105, USA.
 *
 * EXCEPT TO THE EXTENT REQUIRED BY APPLICABLE LAW, IN NO EVENT WILL LICENSOR BE LIABLE TO YOU
 * ON ANY LEGAL THEORY FOR ANY SPECIAL, INCIDENTAL, CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES
 * ARISING OUT OF THIS LICENSE OR THE USE OF THE WORK, EVEN IF LICENSOR HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 */

#include "StdAfx.h"
#include "Setup.h"

#ifdef ASCENT_CORE

class CurseOfDoom : public SpellScript
{
public:
	ADD_SPELL_FACTORY_FUNCTION(CurseOfDoom);
	CurseOfDoom(SpellPointer pSpell) : SpellScript(pSpell) {}
	SpellCastError CanCast(bool tolerate)
	{
		UnitPointer  u_target = _spell->GetUnitTarget();
		if (u_target != NULL && u_target->IsPlayer())
			return SPELL_FAILED_TARGET_IS_PLAYER;

		return SPELL_CANCAST_OK;
	}

	void OnExpire()
	{
		UnitPointer  target=_spell->GetUnitTarget();

		if (target == NULL || !target->isDead())
			return;

		if (RandomUInt(100) < 20)
			target->CastSpell(target, 18662, true);
	}
};

class WarlockPetScaling01 : public SpellScript
{
public:
	ADD_SPELL_FACTORY_FUNCTION(WarlockPetScaling01);
	WarlockPetScaling01(SpellPointer pSpell) : SpellScript(pSpell) {}

	void OnCast()
	{

		if (_spell->u_caster == NULL || !_spell->u_caster->IsPet())
			return;

		Pet* pet=static_cast<Pet*>(_spell->u_caster);

		if (pet->GetOwner() == NULL)
			return;

		uint32 MaxSchoolBonus=0;
		for (int32 i=0; i<7; i++)
			if (pet->GetOwner()->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + i) > MaxSchoolBonus)
				MaxSchoolBonus = pet->GetOwner()->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + i);

		_spell->forced_basepoints[0]=pet->GetOwner()->GetUInt32Value(UNIT_FIELD_STAT2) * 0.3;
		_spell->forced_basepoints[1]=MaxSchoolBonus * 0.57;
		_spell->forced_basepoints[2]=MaxSchoolBonus * 0.15;
	}
};


class SoulShatter : public SpellScript
{
public:
	ADD_SPELL_FACTORY_FUNCTION(SoulShatter);
	SoulShatter(SpellPointer pSpell) : SpellScript(pSpell) {}

	void DummyEffect(uint32 EffectIndex)
	{
		if (_spell->GetUnitTarget() == NULL)
			return;

		_spell->GetUnitTarget()->GetAIInterface()->modThreatByPtr(_spell->u_caster, _spell->GetUnitTarget()->GetAIInterface()->getThreatByPtr(_spell->u_caster) * (_spell->m_spellInfo->EffectBasePoints[EffectIndex] / 100));
	}
};

class DemonicKnowledge : public SpellScript
{
public:
	ADD_SPELL_FACTORY_FUNCTION(DemonicKnowledge);
	int32 amountadded;
	DemonicKnowledge(SpellPointer pSpell) : SpellScript(pSpell) { amountadded=0; }


	void DummyAura(bool apply, Aura* aura)
	{
		if ( aura->GetTarget()->IsPet() )
		{
			UnitPointer  PetOwner;
			if ( static_cast< Pet* >( aura->GetTarget() )->GetPetOwner() )
			{
				PetOwner = static_cast< Pet* >( aura->GetTarget() )->GetPetOwner();

				if (amountadded == 0.0f)
				{
					uint32 val1 = aura->GetTarget()->GetUInt32Value( UNIT_FIELD_STAT2 ); // stamina
					uint32 val2 = aura->GetTarget()->GetUInt32Value( UNIT_FIELD_STAT3 ); // intelect
					uint32 val0 = val1+val2;
					float amount = (float)(val0*aura->mod->m_amount)/100;
					amountadded=amount;
				}

				int32 val;

				if( apply )
					val = (int32)amountadded;
				else
					val = (int32)-amountadded;

				for (uint32 x=0;x<7;x++)
					PetOwner->ModUnsigned32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + x, val);
					
				PetOwner->CalcDamage();
			}
		}
	}
};

#endif

void SetupWarlockSpells(ScriptMgr * mgr)
{
#ifdef ASCENT_CORE
	mgr->register_spell_script(603, &CurseOfDoom::Create);
	mgr->register_spell_script(30910, &CurseOfDoom::Create);
	mgr->register_spell_script(29858, &SoulShatter::Create);
	mgr->register_spell_script(35696, &DemonicKnowledge::Create);
#endif
}

