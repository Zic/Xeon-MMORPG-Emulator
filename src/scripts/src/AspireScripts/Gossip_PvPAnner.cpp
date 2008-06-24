//==================
// PvP Helper
//   by Spidey
//     AspireDev.org
//==================
#include "StdAfx.h"
#include "Setup.h"

//arena coords
#define ARENAMAPID 0
#define ARENAX -13226.732422
#define ARENAY 231.588669
#define ARENAZ 34.537

#define PVPITEM	1234

class SCRIPT_DECL pvpanner : public GossipScript
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

void pvpanner::GossipHello(Object* pObject, Player * Plr, bool AutoSend)
{
	GossipMenu *Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, Plr);
	Menu->AddItem(0, "Port to the arena", 1);
	Menu->AddItem(0, "Announce your presence", 2);
	Menu->AddItem(0, "Exit menu", 0);
	if(AutoSend)
		Menu->SendTo(Plr);
}




//Defining Cases
void pvpanner::GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
{
	GossipMenu * Menu;
	switch(IntId)
	{
		case 0:
		{   //Main menu
			Plr->Gossip_Complete();
		}break;
				
		case 1:
		{   //Goto Arena
			if(Plr->CombatStatus.IsInCombat())
			{
				Plr->Gossip_Complete();
				return;
			}
			Plr->EventTeleport(ARENAMAPID, ARENAX, ARENAY, ARENAZ);
			Plr->Gossip_Complete();
		}break;
				
		case 2:
		{   //Announce
			char announce[255];
			sprintf(announce, "[|cffff0000PvP Announcer|r]|cff00ff00 %s |r|cffffffff is waiting in the arena for more players.|r", Plr->GetName());
			sWorld.SendWorldText(announce);
			Plr->Gossip_Complete();
		}break;

	}//switch
}

void pvpanner::GossipEnd(Object * pObject, Player* Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void Setuppvpanner(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new pvpanner();
	mgr->register_item_gossip_script(PVPITEM,gs);
}