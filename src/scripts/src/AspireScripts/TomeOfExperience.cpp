//Title: Tome of Experience
//Description: Either levels you X levels, gives you Y experience, or levels you to level Z.
//Author: Spidey
//Credits: Otixa is the original author, I added more features.
#include "StdAfx.h"
#include "Setup.h"

//TomeType:
//	0 = Gives LEVEL levels
//	1 = Gives XP based on the FORMULA
//	2 = Levels you to NLEVEL
static uint8 TomeType = 0;
#define LEVEL		1
#define FORMULA		Plr->getLevel() * 150 * sWorld.getRate(RATE_XP)
#define NLEVEL		60

#define TOME		12345

class SCRIPT_DECL TomeOfExp : public GossipScript
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

void TomeOfExp::GossipHello(Object* pObject, Player * Plr, bool AutoSend)
{
	GossipMenu *Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 99000, Plr);
	Menu->AddItem(3, "[Read the tome]", 1);
	Menu->AddItem(1, "[Put it back in your bag]", 2);
	if(AutoSend)
		Menu->SendTo(Plr);
}

void TomeOfExp::GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
{
	GossipMenu * Menu;
	switch(IntId)
	{
		case 0:
		{
			GossipHello(pObject, Plr, true);
		}

		case 1:
		{
			switch(TomeType)
			{
				case 0:
				{
					if(Plr->getLevel() + LEVEL > sWorld.m_levelCap)
					{
						LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), sWorld.m_levelCap);
						Plr->ApplyLevelInfo(Info, sWorld.m_levelCap);
					}
				}break;

				case 1:
				{
					Plr->GiveXP(FORMULA, Plr->GetGUID(), true);
				}break;

				case 2:
				{
					LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), NLEVEL);
					Plr->ApplyLevelInfo(Info, NLEVEL);
				}break;
			}
			Plr->GetItemInterface()->RemoveItemAmt(TOME, 1);
			Plr->BroadcastMessage("You have learned much from this ancient tome.");
		}break;
	}
	Plr->Gossip_Complete();
}

void TomeOfExp::GossipEnd(Object * pObject, Player* Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void SetupTomeOfExp(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new TomeOfExp();
	mgr->register_item_gossip_script(TOME, gs);
}
