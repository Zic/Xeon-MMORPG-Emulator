//---------------------
// Name: Event Teleporter v2
// Author: Spidey
//---------------------

#include "StdAfx.h"
#include "Setup.h"

//If set to true, will enable players to #event while in combat
static bool bypassCombat = false;

static string evon = "#eventon";
static string evoff = "#eventoff";
static string evplr = "#event";

//Default Values
static bool eon = false;
static uint32 emapid = 0;
static float ex = 0.0f;
static float ey = 0.0f;
static float ez = 0.0f;

bool EventChat(Player * pPlayer, uint32 Type, uint32 Lang, const char * Message, const char * Misc)
{
   if(Message == evon && pPlayer->GetSession()->HasGMPermissions())
   {
	  eon = true;
	  ex = pPlayer->GetPositionX();
	  ey = pPlayer->GetPositionY();
	  ez = pPlayer->GetPositionZ();
	  emapid = pPlayer->GetMapId();
	  return false;
   }
   else if(Message == evoff && pPlayer->GetSession()->HasGMPermissions())
   {
	  eon = false;
	  return false;
   }
   else if(Message == evplr)
   {
	  if(eon)
		 if(bypassCombat || !pPlayer->CombatStatus.IsInCombat())
			pPlayer->EventTeleport(emapid, ex, ey, ez);
		 else
			pPlayer->BroadcastMessage("You can't port while in combat.");
	  else
		 pPlayer->BroadcastMessage("There's no active event at the moment.");
	  return false;
   }
   return true;
}

void SetupEventChat(ScriptMgr * mgr)
{
   mgr->register_hook(SERVER_HOOK_EVENT_ON_CHAT, &EventChat);
}