#include "StdAfx.h"
#include "Setup.h"

#define SEXCHANGEKIT	90008

class SCRIPT_DECL sexchange : public GossipScript
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

void sexchange::GossipHello(Object* pObject, Player * Plr, bool AutoSend)
{
	GossipMenu * Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 0, Plr);
	Menu->AddItem(1, "Usable only once! Effect is reversible only if you buy another kit");
	Menu->AddItem(0, "Change sex", 1);
	if(AutoSend)
		Menu->SendTo(Plr);
};

void sexchange::GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
{
	switch(IntId)
	{
		case 0:
		{
			GossipHello(pObject, Plr, true);
		}break;

		case 1:
		{   
			Plr->setGender(Plr->getGender() ? 0 : 1);
			Plr->GetItemInterface()->RemoveItemAmt(SEXCHANGEKIT, 1);
			Plr->BroadcastMessage("Sex changed! Relog to see the effect!");
		}break;

	}
};

void sexchange::GossipEnd(Object * pObject, Player* Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void Setupsexchange(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new sexchange();
	mgr->register_item_gossip_script(SEXCHANGEKIT, gs);
}