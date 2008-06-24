//========================
//  Plastic Surgeon Kit
//    Made by Spidey
//------------------------
//  For more fun scripts
//   visit AspireDev.org
//========================

#include "StdAfx.h"
#include "Setup.h"

#define SURGEONKIT 90005

#ifdef WIN32
#pragma warning(disable:4305)        // warning C4305: 'argument' : truncation from 'double' to 'float'
#endif

class SCRIPT_DECL Surgeon : public GossipScript
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

void Surgeon::GossipHello(Object* pObject, Player * Plr, bool AutoSend)
{
	GossipMenu * Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 0, Plr);
	uint8 pr = Plr->getRace();
	uint8 pc = Plr->getClass();
	uint32 pf = Plr->GetTeam();
	if(pf == 1 && pr != RACE_BLOODELF && pc != WARRIOR && pc != SHAMAN && pc != DRUID)
		Menu->AddItem(0, "Blood Elf", 10);
	if(pf == 0 && pr != RACE_DRAENEI && pc != WARLOCK && pc != ROGUE && pc != DRUID)
		Menu->AddItem(0, "Draenei", 11);
	if(pf == 0 && pr != RACE_DWARF && pc != WARLOCK && pc != SHAMAN && pc != MAGE && pc != DRUID)
		Menu->AddItem(0, "Dwarf", 3);
	if(pf == 0 && pr != RACE_GNOME && (pc == WARRIOR || pc == ROGUE || pc == MAGE || pc == WARLOCK))
		Menu->AddItem(0, "Gnome", 7);
	if(pf == 0 && pr != RACE_HUMAN && pc != DRUID && pc != SHAMAN && pc != HUNTER)
		Menu->AddItem(0, "Human", 1);
	if(pf == 0 && pr != RACE_NIGHTELF && pc != MAGE && pc != PALADIN && pc != SHAMAN && pc != WARLOCK)
		Menu->AddItem(0, "Night Elf", 4);
	if(pf == 1 && pr != RACE_ORC && pc != MAGE && pc != PALADIN && pc != PRIEST && pc != DRUID)
		Menu->AddItem(0, "Orc", 2);
	if(pf == 1 && pr != RACE_TAUREN && (pc == WARRIOR || pc == SHAMAN || pc == HUNTER || pc == DRUID))
		Menu->AddItem(0, "Tauren", 6);
	if(pf == 1 && pr != RACE_TROLL && pc != WARLOCK && pc != PALADIN && pc != DRUID)
		Menu->AddItem(0, "Troll", 8);
	if(pf == 1 && pr != RACE_UNDEAD && pc != SHAMAN && pc != PALADIN && pc != HUNTER && pc != DRUID)
		Menu->AddItem(0, "Undead", 5)
	Menu->AddItem(1, "I've changed my mind", 100);
	if(AutoSend)
		Menu->SendTo(Plr);
};

void Surgeon::GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
{
	GossipMenu * Menu;
	switch(IntId)
	{
		case 0:
		{
			GossipHello(pObject, Plr, true);
		}break;
		case 100:
		{
			Plr->Gossip_Complete();
		}break;

		default:
		{
			Plr->setRace((uint8)IntId);
			Plr->GetItemInterface()->RemoveItemAmt(SURGEONKIT, 1);
			Plr->Gossip_Complete();
			Plr->BroadcastMessage("Race change complete. Relog to see the effect.");
		}break;

	}
};

void Surgeon::GossipEnd(Object * pObject, Player* Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void SetupSurgeon(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new Surgeon();
	mgr->register_item_gossip_script(SURGEONKIT, gs);
}