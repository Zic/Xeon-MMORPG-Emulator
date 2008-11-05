/*
 * Ascent MMORPG Server
 * Copyright (C) 2005-2008 Ascent Team <http://www.ascentemu.com/>
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

bool ChatHandler::HandleSetBGScoreCommand(const char* args, WorldSession *m_session)
{
	CBattleground * bg = m_session->GetPlayer()->m_bg;
	if(!bg)
	{
		RedSystemMessage(m_session, "You need to be inside BG to use this command.");
		return true;
	}
	uint32 teamId = 0;
	uint32 score = 0;
	if( sscanf(args, "%u %u", &teamId, &score) != 2 || teamId > 1)
		return false;
	bg->SetScore(teamId, score);
	return true;
}

bool ChatHandler::HandleStartBGCommand(const char *args, WorldSession *m_session)
{
	if(m_session->GetPlayer()->m_bg && sEventMgr.HasEvent(m_session->GetPlayer()->m_bg, EVENT_BATTLEGROUND_COUNTDOWN))
	{
		sEventMgr.RemoveEvents(m_session->GetPlayer()->m_bg, EVENT_BATTLEGROUND_COUNTDOWN);
		m_session->GetPlayer()->m_bg->Start();
	}
	return true;
}

bool ChatHandler::HandlePauseBGCommand(const char *args, WorldSession *m_session)
{
	return true;
}

bool ChatHandler::HandleBGInfoCommnad(const char *args, WorldSession *m_session)
{
	return true;
}

bool ChatHandler::HandleBattlegroundCommand(const char* args, WorldSession *m_session)
{
	uint32 type = atoi(args);
	if(type != 2 && type != 3 && type != 4 && type != 5 && type != 7)
		return false;

	Player * plr = getSelectedChar(m_session, true);
	if(!plr) return true;
	BattlegroundManager.HandleBattlegroundListPacket(plr->GetSession(), atoi(args));
	return true;
}

bool ChatHandler::HandleSetWorldStateCommand(const char* args, WorldSession *m_session)
{
	uint32 id,val;
	if(sscanf(args,"%u %u", &id,&val)!=2)
		return false;

	if(m_session->GetPlayer()->m_bg)
		m_session->GetPlayer()->m_bg->SetWorldState(id,val);

	return true;
}

bool ChatHandler::HandlePlaySoundCommand(const char* args, WorldSession *m_session)
{
	uint32 sound = 0;
	if(sscanf(args,"%u", &sound) != 1)
		return false;
	if(m_session->GetPlayer()->m_bg)
		m_session->GetPlayer()->m_bg->PlaySoundToAll(sound);
	return true;
}

bool ChatHandler::HandleSetBattlefieldStatusCommand(const char* args, WorldSession *m_session)
{
	uint32 type = atoi(args);
	BattlegroundManager.SendBattlefieldStatus(m_session->GetPlayer(), 1, type, 0 , 0, m_session->GetPlayer()->GetMapId(),0);
	return true;
}

bool ChatHandler::HandleBattlegroundExitCommand(const char* args, WorldSession* m_session)
{
	Player * plr = m_session->GetPlayer();
	if(plr->m_bg && plr->IsInWorld())
		plr->m_bg->RemovePlayer(plr, false);
	return true;
}

bool ChatHandler::HandleBattlegroundForcestartCommand(const char* args, WorldSession* m_session)
{
	BattlegroundManager.EventQueueUpdate(true);
	return true;
}
