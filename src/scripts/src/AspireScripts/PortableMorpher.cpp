//***This script was released under AspireDev and cannot be redistrubted without giving credits**//
//Title of Script: Portable Morpher
//Description of Script: Morphs the player into a few different creatures using a item.
//Author: Aldaus
//Credits: Daikenkaiking - For giving me the idea =]

#include "StdAfx.h"
#include "Setup.h"

#define MORPHER 123455

class SCRIPT_DECL Morpher : public GossipScript
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

void Morpher::GossipHello(Object* pObject, Player * Plr, bool AutoSend)
{
	GossipMenu *Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, Plr);
	Menu->AddItem(0, "Goblin", 1);
	Menu->AddItem(0, "Felguard", 2);
	Menu->AddItem(0, "Broken", 3);
	Menu->AddItem(0, "Ogre", 4);
	Menu->AddItem(0, "Pirate", 5);
	Menu->AddItem(0, "Skeleton", 6);
	Menu->AddItem(2, "Demorph", 7);

   if(AutoSend)
	   Menu->SendTo(Plr);
}

//Defining Cases
void Morpher::GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
{
	switch(IntId)
	{
		case 0:
		{
			GossipHello(pObject, Plr, true);
		}break;

		case 1: //Goblin
		{
			Plr->SetUInt32Value(UNIT_FIELD_DISPLAYID, 7109);
		}break;		

		case 2: //FelGuard
		{
			Plr->SetUInt32Value(UNIT_FIELD_DISPLAYID, 18287);
		}break;

		case 3: //Broken
		{
			Plr->SetUInt32Value(UNIT_FIELD_DISPLAYID, 21105);
		}break;

		case 4: //Ogre
		{
			Plr->SetUInt32Value(UNIT_FIELD_DISPLAYID, 1122);
		}break;

		case 5: //Pirate
		{
			Plr->SetUInt32Value(UNIT_FIELD_DISPLAYID, 2347);
		}break;

		case 6: //Skeleton
		{
			Plr->SetUInt32Value(UNIT_FIELD_DISPLAYID, 17970);
		}break;

		case 7: //Demorphing :p
		{
			Plr->DeMorph();
		}break;

	}//switch
	Plr->Emote(EMOTE_ONESHOT_CHEER);
	Plr->Gossip_Complete();
};

void Morpher::GossipEnd(Object * pObject, Player* Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void SetupMorpher(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new Morpher();
	mgr->register_item_gossip_script(MORPHER, gs);
}