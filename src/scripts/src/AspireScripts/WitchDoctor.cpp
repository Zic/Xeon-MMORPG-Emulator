//***This script was released under AspireDev and cannot be redistrubted without giving credits**//
//Title of Script: Jin'roth
//Description of Script: A witch WDoctor Based off Bom'bay
//Author: Aldaus and Spidey
//Credits: None

#include "StdAfx.h"
#include "Setup.h"

//Comment this out to disable visuals
#define SHOWVISUALS

//Visual spell ids
#define VISUAL 34397
#define PVISUAL 28136

//NPC entry
#define WDOCTOR	123445

//Comment this out to make the doctor silent
#define DOCTORCHATTER

class SCRIPT_DECL WDoctor : public GossipScript
{
public:
	void GossipHello(Object * pObject, Player* Plr, bool AutoSend);
	void GossipSelectOption(Object * pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code);
	void GossipEnd(Object * pObject, Player* Plr);
	void Destroy()
	{
		delete this;
	}
};
void WDoctor::GossipHello(Object * pObject, Player* Plr, bool AutoSend)
{
	GossipMenu *Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
	Menu->AddItem(0, "Feeling Low", 1);
	Menu->AddItem(0, "Unsatisfied", 2);
	Menu->AddItem(0, "Parched", 3);
	Menu->AddItem(0, "Too Small", 4);
	Menu->AddItem(0, "Angered", 5);
	Menu->AddItem(0, "Not Feeling Well", 6);
	Menu->AddItem(0, "Unnoticed", 7);
	Menu->AddItem(0, "Lonley", 8);

	if(AutoSend)
		Menu->SendTo(Plr);
}

//Defining Cases
void WDoctor::GossipSelectOption(Object * pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
{
	Creature * pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?((Creature*)pObject):NULL;
	if(pCreature==NULL)
		return;

	GossipMenu * Menu;
	switch(IntId)
	{
		//Feeling Low
		case 1:
		{
#ifdef SHOWVISUALS
			pCreature->CastSpell(Plr, VISUAL, true);
			Plr->CastSpell(Plr, PVISUAL, true);
#endif
#ifdef DOCTORCHATTER
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Ya Mon!" );
#endif
			pCreature->CastSpell(Plr, 40191, 0);
			Plr->Gossip_Complete();
		}break;
		
		//Unsatisfied
		case 2:
		{
#ifdef SHOWVISUALS
			pCreature->CastSpell(Plr, VISUAL, true);
			Plr->CastSpell(Plr, PVISUAL, true);
#endif
#ifdef DOCTORCHATTER
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Better Mon?" );
#endif
			pCreature->CastSpell(Plr, 228, 0);
			Plr->Gossip_Complete();
		}break;
			 
		//Parched
		case 3:
		{
#ifdef SHOWVISUALS
			pCreature->CastSpell(Plr, VISUAL, true);
			Plr->CastSpell(Plr, PVISUAL, true);
#endif
#ifdef DOCTORCHATTER
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Thirsty Mon?" );
#endif
			pCreature->CastSpell(Plr, 29006, 0);
			Plr->Gossip_Complete();
		}break;

		//Too Small
		case 4:
		{
#ifdef SHOWVISUALS
			pCreature->CastSpell(Plr, VISUAL, true);
			Plr->CastSpell(Plr, PVISUAL, true);
#endif
#ifdef DOCTORCHATTER
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Aha!" );
#endif
			pCreature->CastSpell(Plr, 25462, 0);
			Plr->Gossip_Complete();
		}break;

		//Angered
		case 5:
		{
#ifdef SHOWVISUALS
			pCreature->CastSpell(Plr, VISUAL, true);
			Plr->CastSpell(Plr, PVISUAL, true);
#endif
#ifdef DOCTORCHATTER
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Chill Mon!" );
#endif
			Plr->CastSpell(Plr, 16325, 0);
			Plr->Gossip_Complete();
		}break;

		//Not Feeling Well
		case 6:
		{
#ifdef SHOWVISUALS
			pCreature->CastSpell(Plr, VISUAL, true);
			Plr->CastSpell(Plr, PVISUAL, true);
#endif
#ifdef DOCTORCHATTER
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "I make ya feel better mon!" );
#endif
			Plr->CastSpell(Plr, 43776, 0);
			Plr->Gossip_Complete();
		}break;

		//Unnoticed
		case 7:
		{
#ifdef SHOWVISUALS
			pCreature->CastSpell(Plr, VISUAL, true);
			Plr->CastSpell(Plr, PVISUAL, true);
#endif
#ifdef DOCTORCHATTER
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Aha!" );
#endif
			pCreature->CastSpell(Plr, 24723, 0);
			Plr->Gossip_Complete();
		}break;

		//Lonley
		case 8:
		{
#ifdef SHOWVISUALS
			pCreature->CastSpell(Plr, VISUAL, true);
			Plr->CastSpell(Plr, PVISUAL, true);
#endif
#ifdef DOCTORCHATTER
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "I do what I can mon!" );
#endif
			Plr->CastSpell(Plr, 29066, 0);
			Plr->Gossip_Complete();
		}break;

	}//switch
}

void WDoctor::GossipEnd(Object * pObject, Player* Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void SetupWDoctor(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new WDoctor();
	mgr->register_gossip_script(WDOCTOR, gs);
}