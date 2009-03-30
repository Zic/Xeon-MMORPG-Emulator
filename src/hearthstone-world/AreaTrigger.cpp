/*
 * Aspire Hearthstone
 * Copyright (C) 2008 - 2009 AspireDev <http://www.aspiredev.org/>
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
void WorldSession::HandleAreaTriggerOpcode(WorldPacket & recv_data)
{
	 if(!_player->IsInWorld()) return;
	CHECK_PACKET_SIZE(recv_data, 4);
	uint32 id ;
	recv_data >> id;
	_HandleAreaTriggerOpcode(id);
}

enum AreaTriggerFailures
{
	AREA_TRIGGER_FAILURE_OK				= 0,
	AREA_TRIGGER_FAILURE_UNAVAILABLE	= 1,
	AREA_TRIGGER_FAILURE_NO_BC			= 2,
	AREA_TRIGGER_FAILURE_NO_HEROIC		= 3,
	AREA_TRIGGER_FAILURE_NO_RAID		= 4,
	AREA_TRIGGER_FAILURE_NO_ATTUNE_Q	= 5,
	AREA_TRIGGER_FAILURE_NO_ATTUNE_I	= 6,
	AREA_TRIGGER_FAILURE_LEVEL			= 7,
	AREA_TRIGGER_FAILURE_NO_GROUP		= 8,
	AREA_TRIGGER_FAILURE_NO_KEY			= 9,
	AREA_TRIGGER_FAILURE_LEVEL_HEROIC	= 10,
	AREA_TRIGGER_FAILURE_NO_CHECK		= 11,
	AREA_TRIGGER_FAILURE_NO_WOTLK		= 12,
};

const char * AreaTriggerFailureMessages[] = {
	"-",
	"This instance is unavailable",
	"You must have The Burning Crusade Expansion to access this content.",
	"Heroic mode unavailable for this instance.",
	"You must be in a raid group to pass through here.",
	"You do not have complete a required quest (%s) to pass through here.",
	"You do not have a required item (%s) to pass through here.",
	"You must be at least level %u to pass through here.",
	"You must be in a party to pass through here.",
	"You do not have a required key (%s) to pass through here.",
	"You do not have the required level (%u) to enter heroic mode.",
	"Did\'t have any idea why you can\'t pass through here lol.",
	"You must have The Lich King Expansion to access this content.",
};

uint32 CheckTriggerPrerequsites(AreaTrigger * pAreaTrigger, WorldSession * pSession, PlayerPointer pPlayer, MapInfo * pMapInfo)
{
	if(pAreaTrigger->required_level && pPlayer->getLevel() < pAreaTrigger->required_level)
		return AREA_TRIGGER_FAILURE_LEVEL;

	if(!pMapInfo || !pMapInfo->HasFlag(WMI_INSTANCE_ENABLED))
		return AREA_TRIGGER_FAILURE_UNAVAILABLE;

	if(pMapInfo->HasFlag(WMI_INSTANCE_XPACK_01) &&
	   !pSession->HasFlag(ACCOUNT_FLAG_XPACK_01) && !pSession->HasFlag(ACCOUNT_FLAG_XPACK_02))
		return AREA_TRIGGER_FAILURE_NO_BC;

	if(!pSession->HasFlag(ACCOUNT_FLAG_XPACK_02) && pMapInfo->HasFlag(WMI_INSTANCE_XPACK_02))
		return AREA_TRIGGER_FAILURE_NO_WOTLK;

	// These can be overridden by cheats/GM
	if(pPlayer->triggerpass_cheat)
		return AREA_TRIGGER_FAILURE_OK;

	if(pPlayer->iInstanceType >= MODE_HEROIC && pMapInfo->type != INSTANCE_MULTIMODE && pMapInfo->type != INSTANCE_NULL)
		return AREA_TRIGGER_FAILURE_NO_HEROIC;

	if(pMapInfo->type == INSTANCE_RAID && (!pPlayer->GetGroup() || (pPlayer->GetGroup() && pPlayer->GetGroup()->GetGroupType() != GROUP_TYPE_RAID)))
		return AREA_TRIGGER_FAILURE_NO_RAID;

	if(pMapInfo->type == INSTANCE_MULTIMODE && !pPlayer->GetGroup())
		return AREA_TRIGGER_FAILURE_NO_GROUP;

	if(pMapInfo && pMapInfo->required_quest && !pPlayer->HasFinishedQuest(pMapInfo->required_quest))
		return AREA_TRIGGER_FAILURE_NO_ATTUNE_Q;

	if(pMapInfo && pMapInfo->required_item && !pPlayer->GetItemInterface()->GetItemCount(pMapInfo->required_item, true))
		return AREA_TRIGGER_FAILURE_NO_ATTUNE_I;

	if (pPlayer->iInstanceType >= MODE_HEROIC && 
			pMapInfo->type == INSTANCE_MULTIMODE && 
			(pMapInfo->heroic_key_1 && !pPlayer->GetItemInterface()->GetItemCount(pMapInfo->heroic_key_1, false)) || 
			(pMapInfo->heroic_key_2 && !pPlayer->GetItemInterface()->GetItemCount(pMapInfo->heroic_key_2, false)))
		return AREA_TRIGGER_FAILURE_NO_KEY;

	if (pPlayer->iInstanceType >= MODE_HEROIC && pMapInfo->type != INSTANCE_NULL && 
			(pPlayer->getLevel() < 70 || pMapInfo->HasFlag(WMI_INSTANCE_XPACK_02) && pPlayer->getLevel() < 80))
		return AREA_TRIGGER_FAILURE_LEVEL_HEROIC;

	return AREA_TRIGGER_FAILURE_OK;
}

void WorldSession::_HandleAreaTriggerOpcode(uint32 id)
{		
	DEBUG_LOG( "WorldSession","HandleAreaTriggerOpcode: %u", id);

	// Are we REALLY here?
	if( !_player->IsInWorld() )
		return;

    // Search quest log, find any exploration quests
	sQuestMgr.OnPlayerExploreArea(GetPlayer(),id);

	AreaTrigger* pAreaTrigger = AreaTriggerStorage.LookupEntry( id );

	sHookInterface.OnAreaTrigger(_player, id);

	// if in BG handle is triggers
	if( _player->m_bg )
	{
		_player->m_bg->HookOnAreaTrigger(_player, id);
		return;
	}

	// Hook for Scripted Areatriggers
	_player->GetMapMgr()->HookOnAreaTrigger(_player, id);

	if( _player->GetSession()->CanUseCommand('z') )
	{
		if( pAreaTrigger != NULL )
			sChatHandler.BlueSystemMessage( this, "[%sSystem%s] |rEntered areatrigger: %s%u (%s).", MSG_COLOR_WHITE, MSG_COLOR_LIGHTBLUE, MSG_COLOR_SUBWHITE, id, pAreaTrigger->Name );
		else
			sChatHandler.BlueSystemMessage( this, "[%sSystem%s] |rEntered areatrigger: %s%u", MSG_COLOR_WHITE, MSG_COLOR_LIGHTBLUE, MSG_COLOR_SUBWHITE, id);
	}

	if( pAreaTrigger == NULL )
	{
		OUT_DEBUG("Missing AreaTrigger: %u", id);
		return;
	}

	switch(pAreaTrigger->Type)
	{
	case ATTYPE_INSTANCE:
		{
			if(_player->GetPlayerStatus() != TRANSFER_PENDING) //only ports if player is out of pendings
			{
				uint32 reason = CheckTriggerPrerequsites(pAreaTrigger, this, _player, WorldMapInfoStorage.LookupEntry(pAreaTrigger->Mapid));
				if(reason != AREA_TRIGGER_FAILURE_OK)
				{
					const char * pReason = AreaTriggerFailureMessages[reason];
					char msg[200];
					WorldPacket data(SMSG_AREA_TRIGGER_MESSAGE, 50);
					data << uint32(0);
                    
					switch (reason)
					{
					case AREA_TRIGGER_FAILURE_LEVEL:
						snprintf(msg,200,pReason,pAreaTrigger->required_level);
						data << msg;
						break;
					case AREA_TRIGGER_FAILURE_NO_ATTUNE_I:
						{
							MapInfo * pMi = WorldMapInfoStorage.LookupEntry(pAreaTrigger->Mapid);
							ItemPrototype * pItem = ItemPrototypeStorage.LookupEntry(pMi->required_item);
							snprintf(msg, 200, pReason, pItem ? pItem->Name1 : "UNKNOWN");
							data << msg;
						}break;
					case AREA_TRIGGER_FAILURE_NO_ATTUNE_Q:
						{
							MapInfo * pMi = WorldMapInfoStorage.LookupEntry(pAreaTrigger->Mapid);
							Quest * pQuest = QuestStorage.LookupEntry(pMi->required_quest);
							snprintf(msg, 200, pReason, pQuest ? pQuest->title : "UNKNOWN");

							data << msg;
						}break;
					case AREA_TRIGGER_FAILURE_NO_KEY:
						{
							MapInfo * pMi = WorldMapInfoStorage.LookupEntry(pAreaTrigger->Mapid);
							std::stringstream temp_msg;
							if (pMi->heroic_key_1 && _player->GetItemInterface()->GetItemCount(pMi->heroic_key_1, false))
							{
								ItemPrototype * pKey = ItemPrototypeStorage.LookupEntry(pMi->heroic_key_1);
								temp_msg << pKey ? pKey->Name1 : "UNKNOWN";
							}
							if (pMi->heroic_key_2 && _player->GetItemInterface()->GetItemCount(pMi->heroic_key_2, false))
							{
								ItemPrototype * pKey = ItemPrototypeStorage.LookupEntry(pMi->heroic_key_2);
								temp_msg << " and " << pKey ? pKey->Name1 : "UNKNOWN";
							}
							snprintf(msg, 200, pReason, temp_msg.str());
							data << msg;
						}break;
					case AREA_TRIGGER_FAILURE_LEVEL_HEROIC:
						{
							MapInfo * pMi = WorldMapInfoStorage.LookupEntry(pAreaTrigger->Mapid);
							snprintf(msg, 200, pReason, pMi->HasFlag(WMI_INSTANCE_XPACK_02) ? 80 : 70);
							data << msg;
						}break;
					default:
						data << pReason;
						break;
					}

					data << uint8(0);
					SendPacket(&data);
					return;
				}

				if( _player->IsMounted())
					TO_UNIT(_player)->Dismount();

				_player->SaveEntryPoint(pAreaTrigger->Mapid);
				_player->SafeTeleport(pAreaTrigger->Mapid, 0, LocationVector(pAreaTrigger->x, pAreaTrigger->y, pAreaTrigger->z, pAreaTrigger->o));
			}
		}break;
	case ATTYPE_QUESTTRIGGER:
		{

		}break;
	case ATTYPE_INN:
		{
			if( _player->IsMounted())
				TO_UNIT(_player)->Dismount();

			// Inn
			if (!_player->m_isResting) 
				_player->ApplyPlayerRestState(true);
		}break;
	case ATTYPE_TELEPORT:
		{
			if( _player->GetPlayerStatus() != TRANSFER_PENDING) //only ports if player is out of pendings
			{
				if( _player->IsMounted() )
					TO_UNIT(_player)->Dismount();

				_player->SaveEntryPoint(pAreaTrigger->Mapid);
				_player->SafeTeleport(pAreaTrigger->Mapid, 0, LocationVector(pAreaTrigger->x, pAreaTrigger->y, pAreaTrigger->z, pAreaTrigger->o));
			}
		}break;
	default:break;
	}
}
