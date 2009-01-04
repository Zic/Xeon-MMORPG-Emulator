#include "StdAfx.h"
#include "Setup.h"

class MidsummerRibbonPoleAI : public GameObjectAIScript
{
public:
	MidsummerRibbonPoleAI(GameObjectPointer obj) : GameObjectAIScript(obj) {}
	void OnActivate(PlayerPointer  pPlayer)
	{
		SpellCastTargets ct;
		SpellPointer ps;
		SpellEntry *spe = dbcSpell.LookupEntryForced(29727);
		if( spe == NULL )
			return;

		ct.m_unitTarget = _gameobject->GetGUID();
		ct.m_targetMask = TARGET_FLAG_OBJECT;
		ps = SpellPointer(new Spell(pPlayer, spe, false, NULLAURA));
		ps->prepare(&ct);
	}

	static GameObjectAIScript *Create(GameObjectPointer obj) { return new MidsummerRibbonPoleAI(obj); }
};

bool TestRibbonPoleChannel(uint32 i, AuraPointer pAura, bool apply)
{
	if(i == 0)
	{
		UnitPointer pTarget = pAura->GetTarget();
		if( pTarget != NULL )
		{
			if( apply )
				pTarget->CastSpell(pTarget, 45406, true);
			else
				pTarget->RemoveAura(45406);
		}
	}

	return true;
}

bool TriggerRibbonDance(uint32 i, SpellPointer pSpell)
{
	if( pSpell->u_caster != NULL && i == 0 )
	{
		AuraPointer pAura = pSpell->u_caster->FindAura(29175);
		if( pAura != NULL )
		{
			// increase duration by 3 minutes, capping at 60 minutes
			uint32 dur = pAura->GetDuration() / 1000;
			if( dur < (TIME_MINUTE * 60) )
			{
				dur += (TIME_MINUTE * 3);
				if( dur >= (TIME_MINUTE * 60) )
					dur = (TIME_MINUTE * 60);

				pAura->SetTimeLeft(dur * 1000);
			}
		}
		else
		{
			// add the aura (default 3 mins)
			pSpell->u_caster->CastSpell(pSpell->u_caster, 29175, true);
		}
	}

	return true;
}

void SetupMidsummer(ScriptMgr *mgr)
{
	mgr->register_gameobject_script(181605, &MidsummerRibbonPoleAI::Create);
	mgr->register_dummy_aura(29727, &TestRibbonPoleChannel);
	mgr->register_dummy_spell(29715, &TriggerRibbonDance);

	// hackfix this
	SpellEntry *spe = dbcSpell.LookupEntryForced(29715);
	if( spe != NULL )
	{
		spe->EffectImplicitTargetA[0] = 1;
		spe->EffectImplicitTargetA[1] = 0;
		spe->EffectImplicitTargetA[2] = 0;

		spe->EffectImplicitTargetB[0] = 0;
		spe->EffectImplicitTargetB[1] = 0;
		spe->EffectImplicitTargetB[2] = 0;
	}
}
