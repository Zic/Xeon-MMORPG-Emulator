/* Copyright (C) 2008 Pepsi1x1
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
*/

#include "StdAfx.h"
#include "Setup.h"


class SCRIPT_DECL FreeMoneyNPC : public GossipScript
{
public:
	uint32 AMOUNT;
	void GossipHello(Object * pObject, Player* Plr, bool AutoSend);
	void GossipSelectOption(Object * pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code);
	void GossipEnd(Object * pObject, Player* Plr);
	void GiveGold(Player* Plr, uint32 AMOUNT, string REPLY);
		void Destroy()
		{
		delete this;
		}
};
void FreeMoneyNPC::GossipHello(Object * pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu *Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 30021, Plr);
		Menu->AddItem(0, "1 Gold", 1);
		Menu->AddItem(0, "10 Gold", 2);
		Menu->AddItem(0, "100 Gold", 3);
		Menu->AddItem(0, "1000 Gold", 4);
		Menu->AddItem(0, "10000 Gold", 5);
		Menu->AddItem(0, "Greedy Phat B4stard Gold", 6);
	if(AutoSend)
		Menu->SendTo(Plr);
	}

void FreeMoneyNPC::GossipSelectOption(Object * pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
	{
	Creature * pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?((Creature*)pObject):NULL;
	if(pCreature==NULL)
		return;

	switch(IntId)
	{
		case 1:
		{
			GiveGold(Plr, 10000, "Dont spend it all in one shop!");
			Plr->Gossip_Complete();
			pCreature->Emote(EMOTE_ONESHOT_CHEER);
		}
		break;
		case 2:
		{
			GiveGold(Plr, 100000, "A modest choice my friend!");
			Plr->Gossip_Complete();
			pCreature->Emote(EMOTE_ONESHOT_CHEER);
		}
		break;
		case 3:
		{
			GiveGold(Plr, 1000000, "Go forth my friend and spend!");
			Plr->Gossip_Complete();
			pCreature->Emote(EMOTE_ONESHOT_CHEER);
		}
		break;
		case 4:
		{
			GiveGold(Plr, 10000000, "Have a bag o' sand!");
			Plr->Gossip_Complete();
			pCreature->Emote(EMOTE_ONESHOT_CHEER);
		}
		break;
		case 5:
		{		
			GiveGold(Plr, 100000000, "A big sack of cash!");
			Plr->Gossip_Complete();
			pCreature->Emote(EMOTE_ONESHOT_CHEER);
		}
		break;
		case 6:
		{
			Plr->SetUInt32Value(PLAYER_FIELD_COINAGE,990000000);
			Plr->Gossip_Complete();
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "WOW, but...im considerably richer than yow!");
			pCreature->Emote(EMOTE_ONESHOT_CHEER);
		}
		break;
	}
};

void FreeMoneyNPC::GiveGold(Player * Plr, uint32 AMOUNT, string REPLY)
{
			uint32 currentgold = Plr->GetUInt32Value(PLAYER_FIELD_COINAGE);
			if (currentgold >= 899999999)
				{
				Plr->SetUInt32Value(PLAYER_FIELD_COINAGE,89999999);
				Plr->BroadcastMessage("Money is the root of all evil, you must be BAD...real BAD!");
				Plr->BroadcastMessage("I have set your gold at a reasonable level!");
				}
			else
			{

			uint32 newgold = currentgold + AMOUNT;
			Plr->SetUInt32Value(PLAYER_FIELD_COINAGE,newgold);
			Plr->BroadcastMessage("%s", REPLY.c_str());
			}
}

void FreeMoneyNPC::GossipEnd(Object * pObject, Player* Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void SetupFreeMoneyNPC(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new FreeMoneyNPC();
	mgr->register_gossip_script(30021, gs);
	sLog.outColor(TBLUE, "\nPepsi1x1 Free Money NPC Loaded\nCreated By: Pepsi1x1");
	sLog.outColor(TNORMAL, "\n");
}