#include "StdAfx.h"
#include "Setup.h"

class SCRIPT_DECL PlaguedCritterAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PlaguedCritterAI);
	PlaguedCritterAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

    void OnDied(Unit * mKiller)
    {
		// You're infected now!
        mKiller->CastSpell( mKiller, 43958, true );
    }
};

class SCRIPT_DECL ArgentHealerAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ArgentHealerAI);
	ArgentHealerAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		RegisterAIUpdateEvent( 15000 );
	}

	void OnDied(Unit * mKiller)
	{
		RemoveAIUpdateEvent();
	}

	void AIUpdate()
	{
		// Loop over in-range players, remove the infection, remove zombie form
		set<Player*>::iterator itr = _unit->GetInRangePlayerSetBegin();
		for(; itr != _unit->GetInRangePlayerSetEnd(); ++itr)
		{
			Player * plr = (*itr);
			// We've got some plagues to cure, then?
			if( plr->HasActiveAura( 43958 ) )
			{
				plr->RemoveNegativeAura( 43958 );
				continue;
			}

			if( plr->GetShapeShift() == FORM_ZOMBIE )
			{
				plr->RemoveNegativeAura( 43869 );
				continue;
			}
		}

		// Now cast Holy Nova for the fancy-looking Argent Healer effect
		_unit->CastSpell( _unit, 15237, true );
	}
};

void SetupZombieEvent(ScriptMgr * mgr)
{
	mgr->register_creature_script( 27845, &PlaguedCritterAI::Create); // Plagued Roach
	mgr->register_creature_script( 27855, &PlaguedCritterAI::Create); // Plagued Vermin

	mgr->register_creature_script( 27305, &ArgentHealerAI::Create); // Argent Healer (Alliance)
	mgr->register_creature_script( 31282, &ArgentHealerAI::Create); // Argent Healer (Horde)
}

