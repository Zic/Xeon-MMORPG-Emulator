//***This script was released under AspireDev and cannot be redistrubted without giving credits**//
//Title of Script: Portable Teleporter
//Description of Script: Teleports people to major citys with a item teleporter.
//Author: Aldaus
//Credits: To Mesmer for helping me fix the combat check.

#include "StdAfx.h"
#include "Setup.h"

#define WARPER 123456

//Defining Pwarper
class SCRIPT_DECL Pwarper : public GossipScript
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

void Pwarper::GossipHello(Object* pObject, Player * Plr, bool AutoSend)
{
	if(Plr->CombatStatus.IsInCombat())
	{
			Plr->BroadcastMessage("You are in combat!");
			return;
	}	

	GossipMenu *Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, Plr);
	if(Plr->GetTeam() == 0)
	{
		Menu->AddItem(0, "Stormwind", 50);
		Menu->AddItem(0, "Ironforge", 51);
		Menu->AddItem(0, "Exodar", 52);
		Menu->AddItem(0, "Darnassus", 53);
	}
	else
	{
		Menu->AddItem(0, "Orgrimar", 54);
		Menu->AddItem(0, "Thunder Bluff", 55);
		Menu->AddItem(0, "Silvermoon City", 56);
		Menu->AddItem(0, "Undercity", 57);
	}
	Menu->AddItem(0, "Shattrath", 58);

	if(AutoSend)
		Menu->SendTo(Plr);
}

//Defining Cases
void Pwarper::GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
{
	switch(IntId)
	{
		case 50:
		{   //Stormwind
			if(Plr->GetTeam() == 0)
				Plr->SafeTeleport(0, 0, -8831.61f, 622.666f, 93.7787f, 0);
		}break;

		case 51:
		{   //Ironforge
			if(Plr->GetTeam() == 0)
				Plr->SafeTeleport(0, 0, -4804.45f, -1101.14f, 498.807f, 0);
		}break;

		case 52:
		{   //Exodar
			if(Plr->GetTeam() == 0)
				Plr->SafeTeleport(530, 0, -3796.24f, -11710.9f, -105.45f, 0);
		}break;

		case 53:
		{   //Darnassus
			if(Plr->GetTeam() == 0)
				Plr->SafeTeleport(1, 0, 9952.07f, 2278.46f, 1341.39f, 0);
		}break;

		case 54:
		{   //Orgrimmar
			if(Plr->GetTeam() == 1)
				Plr->SafeTeleport(1, 0, 1499.55f, -4406.91f, 23.1642f, 0);
		}break;

		case 55:
		{   //Thunder Bluff
			if(Plr->GetTeam() == 1)
				Plr->SafeTeleport(1, 0, -1195.88f, -56.5582f, 160.034f, 0);
		}break;

		case 56:
		{   //Silvermoon City
			if(Plr->GetTeam() == 1)
				Plr->SafeTeleport(530, 0, 9492.45f, -7279.12f, 14.3036f, 0);
		}break;
					
		case 57:
		{   //Undercity
			if(Plr->GetTeam() == 1)
				Plr->SafeTeleport(0, 0, 1615.1f, 239.786f, -62.0774f, 0);
		}break;
					
		case 58:
		{   //Shattrath
			Plr->SafeTeleport(530, 0, -1852, 5432, -11, 0);
		}break;
	}//switch
	Plr->Gossip_Complete();
};

void Pwarper::GossipEnd(Object * pObject, Player* Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void SetupPwarper(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new Pwarper();
	mgr->register_item_gossip_script(WARPER, gs);
}