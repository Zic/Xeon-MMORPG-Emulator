//===============
// Friend Porter
//  by Spidey
// AspireDev.org
//===============
#include "StdAfx.h"
#include "Setup.h"

//The cost of the port
#define FRIENDCOST 100000

class SCRIPT_DECL FriendGrab : public GossipScript
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

void FriendGrab::GossipHello(Object * pObject, Player* Plr, bool AutoSend)
{
	if(Plr->GetUInt32Value(PLAYER_FIELD_COINAGE) < FRIENDCOST)
	{
		Plr->BroadcastMessage("You don't have enough gold to teleport to another player.");
		return;
	}
	GossipMenu *Menu;
    objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, Plr);
	Menu->AddItem(1, "Teleport to friend", 1, 1);
	
    if(AutoSend)
        Menu->SendTo(Plr);
}

void FriendGrab::GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
{
    switch(IntId)
    {
		case 0:
		{
			GossipHello(pObject, Plr, true);
		}break;
		case 1:
		{
			if(!Code)
				return;
				
			if(Plr->GetUInt32Value(PLAYER_FIELD_COINAGE) < FRIENDCOST)
				return;

			Player * pTarget = objmgr.GetPlayer(Code, false);
			if(!pTarget)
			{
				Plr->BroadcastMessage("Player does not exist.");
				Plr->Gossip_Complete();
				return;
			}
			if(Plr->CombatStatus.IsInCombat())
			{
				Plr->BroadcastMessage("You cannot teleport while in combat.");
				Plr->Gossip_Complete();
				return;
			}
			if(pTarget->CombatStatus.IsInCombat())
			{
				Plr->BroadcastMessage("Your friend is in combat, you cannot teleport to him now.");
				Plr->Gossip_Complete();
				return;
			}
			if(Plr->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_FREE_FOR_ALL_PVP))
			{
				Plr->BroadcastMessage("You can't port while in a PvP zone.");
				Plr->Gossip_Complete();
				return;
			}
			if(pTarget->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_FREE_FOR_ALL_PVP))
			{
				Plr->BroadcastMessage("You can't port to a player in a PvP zone.");
				Plr->Gossip_Complete();
				return;
			}
			if(pTarget->GetSession()->HasGMPermissions())
			{
				Plr->BroadcastMessage("You cannot port to a Gamemaster.");
				Plr->Gossip_Complete();
				return;
			}
			if(pTarget->GetTeam() != Plr->GetTeam())
			{
				Plr->BroadcastMessage("Player is from the opposing faction.");
				Plr->Gossip_Complete();
				return;
			}
			uint32 pMap = pTarget->GetMapId();
			if(pMap != 0 && pMap != 1 && pMap != 530)
			{
				Plr->BroadcastMessage("Cannot port to a player inside an instance");
				Plr->Gossip_Complete();
				return;
			}
			Plr->SetUInt32Value(PLAYER_FIELD_COINAGE, Plr->GetUInt32Value(PLAYER_FIELD_COINAGE)-FRIENDCOST);
			float pX = pTarget->GetPositionX();
			float pY = pTarget->GetPositionY();
			float pZ = pTarget->GetPositionZ();
			float pO = pTarget->GetOrientation();
			Plr->Gossip_Complete();
			pTarget->BroadcastMessage("%s is porting to your location.", Plr->GetName());
			Plr->EventTeleport(pMap, pX, pY, pZ);
			Plr->SetOrientation(pO);
		}break;
    }
};

void FriendGrab::GossipEnd(Object * pObject, Player* Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void SetupFriendPorter(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new FriendGrab();
	mgr->register_item_gossip_script(61000, gs);
}