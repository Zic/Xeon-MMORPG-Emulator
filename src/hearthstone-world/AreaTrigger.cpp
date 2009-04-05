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
	AREA_TRIGGER_FAILURE_IN_QUEUE		= 13,
};

const char * AreaTriggerFailureMessages[] = {
	"-",
	"This instance is currently not available",                                         //AREA_TRIGGER_FAILURE_UNAVAILABLE	
	"You must have the \"Burning Crusade\" expansion to access this content.",          //AREA_TRIGGER_FAILURE_NO_BC				
	"Heroic mode currently not available for this instance.",                           //AREA_TRIGGER_FAILURE_NO_HEROIC		
	"You must be in a raid group to pass through here.",                                //AREA_TRIGGER_FAILURE_NO_RAID			
	"You must complete the quest \"%s\" to pass through here.",                         //AREA_TRIGGER_FAILURE_NO_ATTUNE_Q	
	"You must have item \"%s\" to pass through here.",                                  //AREA_TRIGGER_FAILURE_NO_ATTUNE_I	
	"You must have reached level %u before you can pass through here.",                 //AREA_TRIGGER_FAILURE_LEVEL				
	"You must be in a party to pass through here.",                                     //AREA_TRIGGER_FAILURE_NO_GROUP			
	"You do not have a required key(s) \"%s\" to pass through here.",                   //AREA_TRIGGER_FAILURE_NO_KEY				
	"You must have reached level %u before you can enter heroic mode.",                 //AREA_TRIGGER_FAILURE_LEVEL_HEROIC	
	"Don\'t have any idea why you can\'t pass through here.",                           //AREA_TRIGGER_FAILURE_NO_CHECK			
	"You must have the \"Wrath of the Lich King\" expansion to access this content.",   //AREA_TRIGGER_FAILURE_NO_WOTLK			
	"You are in queue for this raid group.",                                            //AREA_TRIGGER_FAILURE_IN_QUEUE
};

uint32 CheckTriggerPrerequsites(AreaTrigger * pAreaTrigger, WorldSession * pSession, PlayerPointer pPlayer, MapInfo * pMapInfo)
{
	if(pAreaTrigger->required_level && pPlayer->getLevel() < pAreaTrigger->required_level)
		return AREA_TRIGGER_FAILURE_LEVEL;

	if(!pMapInfo || !pMapInfo->HasFlag(WMI_INSTANCE_ENABLED))
		return AREA_TRIGGER_FAILURE_UNAVAILABLE;

	if(!pSession->HasFlag(ACCOUNT_FLAG_XPACK_01) && pMapInfo->HasFlag(WMI_INSTANCE_XPACK_01))
		return AREA_TRIGGER_FAILURE_NO_BC;

	// These can be overridden by cheats/GM
	if(!pPlayer->triggerpass_cheat)
	{
		if( (pMapInfo->type == INSTANCE_RAID || pMapInfo->type == INSTANCE_MULTIMODE ) && !pPlayer->GetGroup())
			return AREA_TRIGGER_FAILURE_NO_GROUP;

		if( pPlayer->iInstanceType >= MODE_HEROIC && pMapInfo->type != INSTANCE_MULTIMODE && pMapInfo->type != INSTANCE_NULL)
			return AREA_TRIGGER_FAILURE_NO_HEROIC;

		if( pMapInfo->type == INSTANCE_RAID && pPlayer->GetGroup()->GetGroupType() != GROUP_TYPE_RAID )
			return AREA_TRIGGER_FAILURE_NO_RAID;

		if( pMapInfo && pMapInfo->required_quest && !( pPlayer->HasFinishedDailyQuest(pMapInfo->required_quest) || pPlayer->HasFinishedDailyQuest(pMapInfo->required_quest)))
			return AREA_TRIGGER_FAILURE_NO_ATTUNE_Q;

		if(pMapInfo && pMapInfo->required_item && !pPlayer->GetItemInterface()->GetItemCount(pMapInfo->required_item, true))
			return AREA_TRIGGER_FAILURE_NO_ATTUNE_I;

		if( pPlayer->iInstanceType >= MODE_HEROIC && pMapInfo->type == INSTANCE_MULTIMODE && 
			!pPlayer->GetItemInterface()->GetItemCount(pMapInfo->heroic_key[0], false) && 
			!pPlayer->GetItemInterface()->GetItemCount(pMapInfo->heroic_key[1], false))
			return AREA_TRIGGER_FAILURE_NO_KEY;

		if(pPlayer->getLevel()<(pMapInfo->HasFlag(WMI_INSTANCE_XPACK_02) ? 80 : 70) && pPlayer->iInstanceType>=MODE_HEROIC && pMapInfo->type != INSTANCE_NULL)
			return AREA_TRIGGER_FAILURE_LEVEL_HEROIC;
	}
	else
		return AREA_TRIGGER_FAILURE_OK;

	//Raid queue
	if( pMapInfo->type == INSTANCE_RAID || ( pPlayer->iInstanceType >= MODE_HEROIC && pMapInfo->type == INSTANCE_MULTIMODE ) )
	{
		if( ! pPlayer->triggerpass_cheat && pPlayer->m_playerInfo && pMapInfo->playerlimit >= 5 &&
			(int32)((pMapInfo->playerlimit - 5)/5) < pPlayer->m_playerInfo->subGroup)
			return AREA_TRIGGER_FAILURE_IN_QUEUE;
	}

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
							string temp_msg[2];
							string tmp_msg;
							for(uint32 i = 0; i < 2; ++i) 
							{
								if (pMi->heroic_key[i] && _player->GetItemInterface()->GetItemCount(pMi->heroic_key[i], false)==0)
								{
									ItemPrototype * pKey = ItemPrototypeStorage.LookupEntry(pMi->heroic_key[i]);
									if(pKey)
										temp_msg[i] += pKey->Name1;
									else
										temp_msg[i] += "UNKNOWN";
								}
							}
							tmp_msg += temp_msg[0];
							if(temp_msg[0].size() && temp_msg[1].size())
								tmp_msg += "\" and \"";
							tmp_msg += temp_msg[1];

							snprintf(msg, 200, pReason, tmp_msg.c_str());
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

				uint32 InstanceID = 0;
				MapInfo * pMi = WorldMapInfoStorage.LookupEntry(pAreaTrigger->Mapid);

				// Do not handle Hyjal Inn (trigger 4319) as an instance,
				// since we need a unique mapid when generating our instance_id.
				if( id != 4319 && pMi && ( pMi->type == INSTANCE_RAID || _player->iInstanceType >= MODE_HEROIC && pMi->type == INSTANCE_MULTIMODE ) )
				{
					//Do we have a saved instance we should use?
					Instance * in = sInstanceMgr.GetSavedInstance( pMi->mapid,_player->GetLowGUID() );
					if( in && in->m_instanceId )
						InstanceID = in->m_instanceId;
					else //no saved instances found, try to find an active intance for the group we are in.
					{
						InstanceMap::iterator itr;
						InstanceMap * instancemap = sInstanceMgr.GetInstancesForMap( pMi->mapid );
						if( instancemap )
						{
							for( itr = instancemap->begin(); itr != instancemap->end(); ++itr )
							{
								in = itr->second;
								if( in->m_mapMgr && in->m_mapMgr->HasPlayers() ) //some instances are inside another
								{
									PlayerPointer firstplr = sInstanceMgr.GetFirstPlayer(in);
									if( firstplr != NULL  && firstplr->GetGroup() == _player->GetGroup() )
									{
										if (_player->GetGroup()->GetGroupInstanceID() != firstplr->GetGroup()->GetGroupInstanceID())
										{
											Log.Warning("InstanceMgr","Group inside instance %d didn't set the GroupInstanceID for map %d [%s], old_instanceID = %d",
												in->m_instanceId, in->m_mapId, in->m_mapInfo->name, firstplr->GetGroup()->GetGroupInstanceID() );
											_player->GetGroup()->SetGroupInstanceID(in->m_instanceId);
										}
										InstanceID = in->m_instanceId;
										break;
									}
								}
							}
						}
					}
					// Set current InstanceID for player (or 0 if no instances found)
					_player->SetInstanceID(InstanceID);
				}

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
