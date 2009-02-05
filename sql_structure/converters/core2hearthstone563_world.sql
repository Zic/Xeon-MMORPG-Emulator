/* Alter table in target */
ALTER TABLE `ai_agents` 
  CHANGE `targettype` `targettype_overwrite` int(11)   NOT NULL DEFAULT '-1' after `spelltype`,
  CHANGE `cooldown` `cooldown_overwrite` int(11)   NOT NULL DEFAULT '-1' after `targettype_overwrite`,
	CHANGE `floatMisc1` `floatMisc1` float   NOT NULL DEFAULT '0' after `cooldown_overwrite`;

/* Alter table in target */
ALTER TABLE `ai_threattospellid` 
	ADD COLUMN `modcoef` float   NOT NULL DEFAULT '1' after `mod`, COMMENT='';

RENAME TABLE `areatrigger_extra` TO `areatriggers`;

/* Alter table in target */
ALTER TABLE `creature_spawns` 
  CHANGE `bytes` `bytes0` int(30)   NOT NULL DEFAULT '0' after `flags`, 
	CHANGE `bytes2` `bytes2` int(30)   NOT NULL DEFAULT '0' after `bytes0`;

/* Alter table in target */
ALTER TABLE `creature_staticspawns` 
	ADD COLUMN `bytes0` int(30)   NOT NULL DEFAULT '0' after `flags`, 
	ADD COLUMN `bytes1` int(30)   NOT NULL DEFAULT '0' after `bytes0`, 
	CHANGE `bytes2` `bytes2` int(30)   NOT NULL DEFAULT '0' after `bytes1`, 
	CHANGE `emote_state` `emote_state` int(30)   NOT NULL DEFAULT '0' after `bytes2`, 
	CHANGE `npc_respawn_link` `npc_respawn_link` int(30)   NOT NULL DEFAULT '0' after `emote_state`, 
	DROP COLUMN `bytes`, COMMENT='';

/* Alter table in target */
ALTER TABLE `items`  
	CHANGE `dmg_min1` `dmg_min1` float   NOT NULL DEFAULT '0' after `stat_value10`, 
	CHANGE `dmg_max1` `dmg_max1` float   NOT NULL DEFAULT '0' after `dmg_min1`, 
	CHANGE `dmg_type1` `dmg_type1` int(30)   NOT NULL DEFAULT '0' after `dmg_max1`, 
	CHANGE `dmg_min2` `dmg_min2` float   NOT NULL DEFAULT '0' after `dmg_type1`, 
	CHANGE `dmg_max2` `dmg_max2` float   NOT NULL DEFAULT '0' after `dmg_min2`, 
	CHANGE `dmg_type2` `dmg_type2` int(30)   NOT NULL DEFAULT '0' after `dmg_max2`, 
	CHANGE `dmg_min3` `dmg_min3` float   NOT NULL DEFAULT '0' after `dmg_type2`, 
	CHANGE `dmg_max3` `dmg_max3` float   NOT NULL DEFAULT '0' after `dmg_min3`, 
	CHANGE `dmg_type3` `dmg_type3` int(30)   NOT NULL DEFAULT '0' after `dmg_max3`, 
	CHANGE `dmg_min4` `dmg_min4` float   NOT NULL DEFAULT '0' after `dmg_type3`, 
	CHANGE `dmg_max4` `dmg_max4` float   NOT NULL DEFAULT '0' after `dmg_min4`, 
	CHANGE `dmg_type4` `dmg_type4` int(30)   NOT NULL DEFAULT '0' after `dmg_max4`, 
	CHANGE `dmg_min5` `dmg_min5` float   NOT NULL DEFAULT '0' after `dmg_type4`, 
	CHANGE `dmg_max5` `dmg_max5` float   NOT NULL DEFAULT '0' after `dmg_min5`, 
	CHANGE `dmg_type5` `dmg_type5` int(30)   NOT NULL DEFAULT '0' after `dmg_max5`, 
	CHANGE `armor` `armor` int(30)   NOT NULL DEFAULT '0' after `dmg_type5`, 
	CHANGE `holy_res` `holy_res` int(30)   NOT NULL DEFAULT '0' after `armor`, 
	CHANGE `fire_res` `fire_res` int(30)   NOT NULL DEFAULT '0' after `holy_res`, 
	CHANGE `nature_res` `nature_res` int(30)   NOT NULL DEFAULT '0' after `fire_res`, 
	CHANGE `frost_res` `frost_res` int(30)   NOT NULL DEFAULT '0' after `nature_res`, 
	CHANGE `shadow_res` `shadow_res` int(30)   NOT NULL DEFAULT '0' after `frost_res`, 
	CHANGE `arcane_res` `arcane_res` int(30)   NOT NULL DEFAULT '0' after `shadow_res`, 
	CHANGE `delay` `delay` int(30)   NOT NULL DEFAULT '0' after `arcane_res`, 
	CHANGE `ammo_type` `ammo_type` int(30)   NOT NULL DEFAULT '0' after `delay`, 
	CHANGE `range` `range` float   NOT NULL DEFAULT '0' after `ammo_type`, 
	CHANGE `spellid_1` `spellid_1` int(30)   NOT NULL DEFAULT '0' after `range`, 
	CHANGE `spelltrigger_1` `spelltrigger_1` int(30)   NOT NULL DEFAULT '0' after `spellid_1`, 
	CHANGE `spellcharges_1` `spellcharges_1` int(30)   NOT NULL DEFAULT '0' after `spelltrigger_1`, 
	CHANGE `spellcooldown_1` `spellcooldown_1` int(30)   NOT NULL DEFAULT '0' after `spellcharges_1`, 
	CHANGE `spellcategory_1` `spellcategory_1` int(30)   NOT NULL DEFAULT '0' after `spellcooldown_1`, 
	CHANGE `spellcategorycooldown_1` `spellcategorycooldown_1` int(30)   NOT NULL DEFAULT '0' after `spellcategory_1`, 
	CHANGE `spellid_2` `spellid_2` int(30)   NOT NULL DEFAULT '0' after `spellcategorycooldown_1`, 
	CHANGE `spelltrigger_2` `spelltrigger_2` int(30)   NOT NULL DEFAULT '0' after `spellid_2`, 
	CHANGE `spellcharges_2` `spellcharges_2` int(30)   NOT NULL DEFAULT '0' after `spelltrigger_2`, 
	CHANGE `spellcooldown_2` `spellcooldown_2` int(30)   NOT NULL DEFAULT '0' after `spellcharges_2`, 
	CHANGE `spellcategory_2` `spellcategory_2` int(30)   NOT NULL DEFAULT '0' after `spellcooldown_2`, 
	CHANGE `spellcategorycooldown_2` `spellcategorycooldown_2` int(30)   NOT NULL DEFAULT '0' after `spellcategory_2`, 
	CHANGE `spellid_3` `spellid_3` int(30)   NOT NULL DEFAULT '0' after `spellcategorycooldown_2`, 
	CHANGE `spelltrigger_3` `spelltrigger_3` int(30)   NOT NULL DEFAULT '0' after `spellid_3`, 
	CHANGE `spellcharges_3` `spellcharges_3` int(30)   NOT NULL DEFAULT '0' after `spelltrigger_3`, 
	CHANGE `spellcooldown_3` `spellcooldown_3` int(30)   NOT NULL DEFAULT '0' after `spellcharges_3`, 
	CHANGE `spellcategory_3` `spellcategory_3` int(30)   NOT NULL DEFAULT '0' after `spellcooldown_3`, 
	CHANGE `spellcategorycooldown_3` `spellcategorycooldown_3` int(30)   NOT NULL DEFAULT '0' after `spellcategory_3`, 
	CHANGE `spellid_4` `spellid_4` int(30)   NOT NULL DEFAULT '0' after `spellcategorycooldown_3`, 
	CHANGE `spelltrigger_4` `spelltrigger_4` int(30)   NOT NULL DEFAULT '0' after `spellid_4`, 
	CHANGE `spellcharges_4` `spellcharges_4` int(30)   NOT NULL DEFAULT '0' after `spelltrigger_4`, 
	CHANGE `spellcooldown_4` `spellcooldown_4` int(30)   NOT NULL DEFAULT '0' after `spellcharges_4`, 
	CHANGE `spellcategory_4` `spellcategory_4` int(30)   NOT NULL DEFAULT '0' after `spellcooldown_4`, 
	CHANGE `spellcategorycooldown_4` `spellcategorycooldown_4` int(30)   NOT NULL DEFAULT '0' after `spellcategory_4`, 
	CHANGE `spellid_5` `spellid_5` int(30)   NOT NULL DEFAULT '0' after `spellcategorycooldown_4`, 
	CHANGE `spelltrigger_5` `spelltrigger_5` int(30)   NOT NULL DEFAULT '0' after `spellid_5`, 
	CHANGE `spellcharges_5` `spellcharges_5` int(30)   NOT NULL DEFAULT '0' after `spelltrigger_5`, 
	CHANGE `spellcooldown_5` `spellcooldown_5` int(30)   NOT NULL DEFAULT '0' after `spellcharges_5`, 
	CHANGE `spellcategory_5` `spellcategory_5` int(30)   NOT NULL DEFAULT '0' after `spellcooldown_5`, 
	CHANGE `spellcategorycooldown_5` `spellcategorycooldown_5` int(30)   NOT NULL DEFAULT '0' after `spellcategory_5`, 
	CHANGE `bonding` `bonding` int(30)   NOT NULL DEFAULT '0' after `spellcategorycooldown_5`, 
	CHANGE `description` `description` varchar(255)  COLLATE latin1_swedish_ci NOT NULL DEFAULT '' after `bonding`, 
	CHANGE `page_id` `page_id` int(30)   NOT NULL DEFAULT '0' after `description`, 
	CHANGE `page_language` `page_language` int(30)   NOT NULL DEFAULT '0' after `page_id`, 
	CHANGE `page_material` `page_material` int(30)   NOT NULL DEFAULT '0' after `page_language`, 
	CHANGE `quest_id` `quest_id` int(30)   NOT NULL DEFAULT '0' after `page_material`, 
	CHANGE `lock_id` `lock_id` int(30)   NOT NULL DEFAULT '0' after `quest_id`, 
	CHANGE `lock_material` `lock_material` int(30)   NOT NULL DEFAULT '0' after `lock_id`, 
	CHANGE `sheathID` `sheathID` int(30)   NOT NULL DEFAULT '0' after `lock_material`, 
	CHANGE `randomprop` `randomprop` int(30)   NOT NULL DEFAULT '0' after `sheathID`, 
	CHANGE `unk203_1` `unk203_1` int(11)   NOT NULL DEFAULT '0' after `randomprop`, 
	CHANGE `block` `block` int(30)   NOT NULL DEFAULT '0' after `unk203_1`, 
	CHANGE `itemset` `itemset` int(30)   NOT NULL DEFAULT '0' after `block`, 
	CHANGE `MaxDurability` `MaxDurability` int(30)   NOT NULL DEFAULT '0' after `itemset`, 
	CHANGE `ZoneNameID` `ZoneNameID` int(30)   NOT NULL DEFAULT '0' after `MaxDurability`, 
	CHANGE `mapid` `mapid` int(30)   NULL after `ZoneNameID`, 
	CHANGE `bagfamily` `bagfamily` int(30)   NOT NULL DEFAULT '0' after `mapid`, 
	CHANGE `TotemCategory` `TotemCategory` int(30)   NULL after `bagfamily`, 
	CHANGE `socket_color_1` `socket_color_1` int(30)   NULL after `TotemCategory`, 
	CHANGE `unk201_3` `unk201_3` int(30)   NOT NULL DEFAULT '0' after `socket_color_1`, 
	CHANGE `socket_color_2` `socket_color_2` int(30)   NULL after `unk201_3`, 
	CHANGE `unk201_5` `unk201_5` int(30)   NOT NULL DEFAULT '0' after `socket_color_2`, 
	CHANGE `socket_color_3` `socket_color_3` int(30)   NULL after `unk201_5`, 
	CHANGE `unk201_7` `unk201_7` int(30)   NOT NULL DEFAULT '0' after `socket_color_3`, 
	CHANGE `socket_bonus` `socket_bonus` int(30)   NULL after `unk201_7`, 
	CHANGE `GemProperties` `GemProperties` int(30)   NULL after `socket_bonus`, 
	CHANGE `ReqDisenchantSkill` `ReqDisenchantSkill` int(30)   NOT NULL DEFAULT '-1' after `GemProperties`, 
	CHANGE `unk2` `unk2` int(30)   NOT NULL DEFAULT '0' after `ReqDisenchantSkill`, COMMENT='';

/* Create table in target */
CREATE TABLE `news_announcements`(
	`id` int(30) unsigned NOT NULL  auto_increment , 
	`faction_mask` int(30) NOT NULL  , 
	`message_text` varchar(500) COLLATE utf8_general_ci NOT NULL  , 
	PRIMARY KEY (`id`) 
) ENGINE=MyISAM DEFAULT CHARSET='utf8';


/* Alter table in target */
ALTER TABLE `playercreateinfo` 
	ADD COLUMN `BaseRunic` int(10) unsigned   NOT NULL DEFAULT '0' after `BaseEnergy`, 
	CHANGE `attackpower` `attackpower` int(10) unsigned   NOT NULL DEFAULT '0' after `BaseRunic`, 
	CHANGE `mindmg` `mindmg` float   NOT NULL DEFAULT '0' after `attackpower`, 
	CHANGE `maxdmg` `maxdmg` float   NOT NULL DEFAULT '0' after `mindmg`, COMMENT='';

/* Create table in target */
CREATE TABLE `professiondiscoveries`(
	`SpellId` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`SpellToDiscover` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`SkillValue` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`Chance` float NOT NULL  DEFAULT '0' , 
	PRIMARY KEY (`SpellId`,`SpellToDiscover`) 
) ENGINE=MyISAM DEFAULT CHARSET='utf8';


/* Alter table in target */
ALTER TABLE `quests` 
	CHANGE `LimitTime` `LimitTime` int(10) unsigned   NOT NULL DEFAULT '0' after `RequiredRepValue`, 
	CHANGE `SpecialFlags` `SpecialFlags` int(10) unsigned   NOT NULL DEFAULT '0' after `LimitTime`, 
	CHANGE `PrevQuestId` `PrevQuestId` int(10) unsigned   NOT NULL DEFAULT '0' after `SpecialFlags`, 
	CHANGE `NextQuestId` `NextQuestId` int(10) unsigned   NOT NULL DEFAULT '0' after `PrevQuestId`, 
	CHANGE `srcItem` `srcItem` int(10) unsigned   NOT NULL DEFAULT '0' after `NextQuestId`, 
	CHANGE `SrcItemCount` `SrcItemCount` int(10) unsigned   NOT NULL DEFAULT '0' after `srcItem`, 
	CHANGE `Title` `Title` char(255)  COLLATE latin1_swedish_ci NOT NULL after `SrcItemCount`, 
	CHANGE `Details` `Details` text  COLLATE utf8_unicode_ci NOT NULL after `Title`, 
	CHANGE `Objectives` `Objectives` text  COLLATE utf8_unicode_ci NOT NULL after `Details`, 
	CHANGE `CompletionText` `CompletionText` text  COLLATE utf8_unicode_ci NOT NULL after `Objectives`, 
	CHANGE `IncompleteText` `IncompleteText` text  COLLATE utf8_unicode_ci NOT NULL after `CompletionText`, 
	CHANGE `EndText` `EndText` text  COLLATE utf8_unicode_ci NOT NULL after `IncompleteText`, 
	CHANGE `ObjectiveText1` `ObjectiveText1` text  COLLATE utf8_unicode_ci NOT NULL after `EndText`, 
	CHANGE `ObjectiveText2` `ObjectiveText2` text  COLLATE utf8_unicode_ci NOT NULL after `ObjectiveText1`, 
	CHANGE `ObjectiveText3` `ObjectiveText3` text  COLLATE utf8_unicode_ci NOT NULL after `ObjectiveText2`, 
	CHANGE `ObjectiveText4` `ObjectiveText4` text  COLLATE utf8_unicode_ci NOT NULL after `ObjectiveText3`, 
	CHANGE `ReqItemId1` `ReqItemId1` int(10) unsigned   NOT NULL DEFAULT '0' after `ObjectiveText4`, 
	CHANGE `ReqItemId2` `ReqItemId2` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqItemId1`, 
	CHANGE `ReqItemId3` `ReqItemId3` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqItemId2`, 
	CHANGE `ReqItemId4` `ReqItemId4` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqItemId3`, 
	CHANGE `ReqItemCount1` `ReqItemCount1` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqItemId4`, 
	CHANGE `ReqItemCount2` `ReqItemCount2` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqItemCount1`, 
	CHANGE `ReqItemCount3` `ReqItemCount3` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqItemCount2`, 
	CHANGE `ReqItemCount4` `ReqItemCount4` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqItemCount3`, 
	CHANGE `ReqKillMobOrGOId1` `ReqKillMobOrGOId1` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqItemCount4`, 
	CHANGE `ReqKillMobOrGOId2` `ReqKillMobOrGOId2` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqKillMobOrGOId1`, 
	CHANGE `ReqKillMobOrGOId3` `ReqKillMobOrGOId3` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqKillMobOrGOId2`, 
	CHANGE `ReqKillMobOrGOId4` `ReqKillMobOrGOId4` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqKillMobOrGOId3`, 
	CHANGE `ReqKillMobOrGOCount1` `ReqKillMobOrGOCount1` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqKillMobOrGOId4`, 
	CHANGE `ReqKillMobOrGOCount2` `ReqKillMobOrGOCount2` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqKillMobOrGOCount1`, 
	CHANGE `ReqKillMobOrGOCount3` `ReqKillMobOrGOCount3` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqKillMobOrGOCount2`, 
	CHANGE `ReqKillMobOrGOCount4` `ReqKillMobOrGOCount4` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqKillMobOrGOCount3`, 
	CHANGE `ReqCastSpellId1` `ReqCastSpellId1` int(11)   NOT NULL DEFAULT '0' after `ReqKillMobOrGOCount4`, 
	CHANGE `ReqCastSpellId2` `ReqCastSpellId2` int(11)   NOT NULL DEFAULT '0' after `ReqCastSpellId1`, 
	CHANGE `ReqCastSpellId3` `ReqCastSpellId3` int(11)   NOT NULL DEFAULT '0' after `ReqCastSpellId2`, 
	CHANGE `ReqCastSpellId4` `ReqCastSpellId4` int(11)   NOT NULL DEFAULT '0' after `ReqCastSpellId3`, 
	CHANGE `RewChoiceItemId1` `RewChoiceItemId1` int(10) unsigned   NOT NULL DEFAULT '0' after `ReqCastSpellId4`, 
	CHANGE `RewChoiceItemId2` `RewChoiceItemId2` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemId1`, 
	CHANGE `RewChoiceItemId3` `RewChoiceItemId3` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemId2`, 
	CHANGE `RewChoiceItemId4` `RewChoiceItemId4` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemId3`, 
	CHANGE `RewChoiceItemId5` `RewChoiceItemId5` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemId4`, 
	CHANGE `RewChoiceItemId6` `RewChoiceItemId6` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemId5`, 
	CHANGE `RewChoiceItemCount1` `RewChoiceItemCount1` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemId6`, 
	CHANGE `RewChoiceItemCount2` `RewChoiceItemCount2` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemCount1`, 
	CHANGE `RewChoiceItemCount3` `RewChoiceItemCount3` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemCount2`, 
	CHANGE `RewChoiceItemCount4` `RewChoiceItemCount4` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemCount3`, 
	CHANGE `RewChoiceItemCount5` `RewChoiceItemCount5` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemCount4`, 
	CHANGE `RewChoiceItemCount6` `RewChoiceItemCount6` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemCount5`, 
	CHANGE `RewItemId1` `RewItemId1` int(10) unsigned   NOT NULL DEFAULT '0' after `RewChoiceItemCount6`, 
	CHANGE `RewItemId2` `RewItemId2` int(10) unsigned   NOT NULL DEFAULT '0' after `RewItemId1`, 
	CHANGE `RewItemId3` `RewItemId3` int(10) unsigned   NOT NULL DEFAULT '0' after `RewItemId2`, 
	CHANGE `RewItemId4` `RewItemId4` int(10) unsigned   NOT NULL DEFAULT '0' after `RewItemId3`, 
	CHANGE `RewItemCount1` `RewItemCount1` int(10) unsigned   NOT NULL DEFAULT '0' after `RewItemId4`, 
	CHANGE `RewItemCount2` `RewItemCount2` int(10) unsigned   NOT NULL DEFAULT '0' after `RewItemCount1`, 
	CHANGE `RewItemCount3` `RewItemCount3` int(10) unsigned   NOT NULL DEFAULT '0' after `RewItemCount2`, 
	CHANGE `RewItemCount4` `RewItemCount4` int(10) unsigned   NOT NULL DEFAULT '0' after `RewItemCount3`, 
	CHANGE `RewRepFaction1` `RewRepFaction1` int(10) unsigned   NOT NULL DEFAULT '0' after `RewItemCount4`, 
	CHANGE `RewRepFaction2` `RewRepFaction2` int(10) unsigned   NOT NULL DEFAULT '0' after `RewRepFaction1`, 
	ADD COLUMN `RewRepFaction3` int(10) unsigned   NOT NULL DEFAULT '0' after `RewRepFaction2`, 
	ADD COLUMN `RewRepFaction4` int(10) unsigned   NOT NULL DEFAULT '0' after `RewRepFaction3`, 
	ADD COLUMN `RewRepFaction5` int(10) unsigned   NOT NULL DEFAULT '0' after `RewRepFaction4`, 
	CHANGE `RewRepValue1` `RewRepValue1` int(10)   NOT NULL DEFAULT '0' after `RewRepFaction5`, 
	CHANGE `RewRepValue2` `RewRepValue2` int(10)   NOT NULL DEFAULT '0' after `RewRepValue1`, 
	ADD COLUMN `RewRepValue4` int(10) unsigned   NOT NULL DEFAULT '0' after `RewRepValue2`, 
	ADD COLUMN `RewRepValue5` int(10) unsigned   NOT NULL DEFAULT '0' after `RewRepValue4`, 
	ADD COLUMN `RewRepValue6` int(10) unsigned   NOT NULL DEFAULT '0' after `RewRepValue5`, 
	CHANGE `RewRepLimit` `RewRepLimit` int(10) unsigned   NOT NULL DEFAULT '0' after `RewRepValue6`, 
	CHANGE `RewTitle` `RewardTitle` int(10)   NOT NULL DEFAULT '0' after `RewRepLimit`, 
	CHANGE `RewMoney` `RewMoney` int(10)   NOT NULL DEFAULT '0' after `RewardTitle`, 
	CHANGE `RewXP` `RewXP` int(10) unsigned   NOT NULL DEFAULT '0' after `RewMoney`, 
	CHANGE `RewSpell` `RewSpell` int(10) unsigned   NOT NULL DEFAULT '0' after `RewXP`, 
	CHANGE `CastSpell` `CastSpell` int(10) unsigned   NOT NULL DEFAULT '0' after `RewSpell`, 
	CHANGE `PointMapId` `PointMapId` int(10) unsigned   NOT NULL DEFAULT '0' after `CastSpell`, 
	CHANGE `PointX` `PointX` float   NOT NULL DEFAULT '0' after `PointMapId`, 
	CHANGE `PointY` `PointY` float   NOT NULL DEFAULT '0' after `PointX`, 
	CHANGE `PointOpt` `PointOpt` int(10) unsigned   NOT NULL DEFAULT '0' after `PointY`, 
	CHANGE `RequiredMoney` `RequiredMoney` int(10)   NOT NULL after `PointOpt`, 
	CHANGE `ExploreTrigger1` `ExploreTrigger1` int(10) unsigned   NOT NULL DEFAULT '0' after `RequiredMoney`, 
	CHANGE `ExploreTrigger2` `ExploreTrigger2` int(10) unsigned   NOT NULL DEFAULT '0' after `ExploreTrigger1`, 
	CHANGE `ExploreTrigger3` `ExploreTrigger3` int(10) unsigned   NOT NULL DEFAULT '0' after `ExploreTrigger2`, 
	CHANGE `ExploreTrigger4` `ExploreTrigger4` int(10) unsigned   NOT NULL DEFAULT '0' after `ExploreTrigger3`, 
	CHANGE `RequiredQuest1` `RequiredQuest1` int(10) unsigned   NOT NULL DEFAULT '0' after `ExploreTrigger4`, 
	CHANGE `RequiredQuest2` `RequiredQuest2` int(10) unsigned   NOT NULL DEFAULT '0' after `RequiredQuest1`, 
	CHANGE `RequiredQuest3` `RequiredQuest3` int(10) unsigned   NOT NULL DEFAULT '0' after `RequiredQuest2`, 
	CHANGE `RequiredQuest4` `RequiredQuest4` int(10) unsigned   NOT NULL DEFAULT '0' after `RequiredQuest3`, 
	CHANGE `ReceiveItemId1` `ReceiveItemId1` int(10) unsigned   NOT NULL DEFAULT '0' after `RequiredQuest4`, 
	CHANGE `ReceiveItemId2` `ReceiveItemId2` int(10) unsigned   NOT NULL DEFAULT '0' after `ReceiveItemId1`, 
	CHANGE `ReceiveItemId3` `ReceiveItemId3` int(10) unsigned   NOT NULL DEFAULT '0' after `ReceiveItemId2`, 
	CHANGE `ReceiveItemId4` `ReceiveItemId4` int(10) unsigned   NOT NULL DEFAULT '0' after `ReceiveItemId3`, 
	CHANGE `ReceiveItemCount1` `ReceiveItemCount1` int(10) unsigned   NOT NULL DEFAULT '0' after `ReceiveItemId4`, 
	CHANGE `ReceiveItemCount2` `ReceiveItemCount2` int(10) unsigned   NOT NULL DEFAULT '0' after `ReceiveItemCount1`, 
	CHANGE `ReceiveItemCount3` `ReceiveItemCount3` int(10) unsigned   NOT NULL DEFAULT '0' after `ReceiveItemCount2`, 
	CHANGE `ReceiveItemCount4` `ReceiveItemCount4` int(10) unsigned   NOT NULL DEFAULT '0' after `ReceiveItemCount3`, 
	CHANGE `IsRepeatable` `IsRepeatable` int(11)   NOT NULL DEFAULT '0' after `ReceiveItemCount4`, 
	DROP COLUMN `SuggestedPlayers`, 
	DROP COLUMN `ReqKillPlayer`, 
	DROP COLUMN `RewBonusHonor`, 
	DROP COLUMN `RewTalents`, COMMENT='';

/* Alter table in target */
ALTER TABLE `reputation_instance_onkill` 
	CHANGE `mob_rep_limit` `mob_rep_limit` int(30)   NOT NULL after `mob_rep_reward`, 
	CHANGE `boss_rep_reward` `boss_rep_reward` int(30)   NOT NULL after `mob_rep_limit`, 
	CHANGE `boss_rep_limit` `boss_rep_limit` int(30)   NOT NULL after `boss_rep_reward`, 
	CHANGE `faction_change_alliance` `faction_change_alliance` int(30)   NOT NULL after `boss_rep_limit`, 
	CHANGE `faction_change_horde` `faction_change_horde` int(30)   NOT NULL after `faction_change_alliance`, 
	DROP COLUMN `mob_rep_reward_heroic`, 
	DROP COLUMN `mob_rep_limit_heroic`, 
	DROP COLUMN `boss_rep_reward_heroic`, 
	DROP COLUMN `boss_rep_limit_heroic`, COMMENT='';

/* Create table in target */
CREATE TABLE `spellfixes`(
	`spellId` int(30) NOT NULL  DEFAULT '0' , 
	`procFlags` int(30) NOT NULL  DEFAULT '0' , 
	`procChance` int(30) NOT NULL  DEFAULT '0' , 
	`procCharges` int(30) NOT NULL  DEFAULT '0' , 
	`effect0ClassMask0` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`effect0ClassMask1` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`effect0ClassMask2` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`effect1ClassMask0` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`effect1ClassMask1` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`effect1ClassMask2` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`effect2ClassMask0` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`effect2ClassMask1` int(10) unsigned NOT NULL  DEFAULT '0' , 
	`effect2ClassMask2` int(10) unsigned NOT NULL  DEFAULT '0' , 
	PRIMARY KEY (`spellId`) 
) ENGINE=MyISAM DEFAULT CHARSET='latin1';


/* Alter table in target */
ALTER TABLE `vendors` 
	CHANGE `extended_cost` `extended_cost` int(11)   NOT NULL DEFAULT '0' after `inctime`, COMMENT='';

/* Create table in target */
CREATE TABLE `worldbroadcast`(
	`entry` int(11) unsigned NOT NULL  auto_increment , 
	`text` varchar(255) COLLATE utf8_unicode_ci NOT NULL  , 
	`percent` int(3) NOT NULL  DEFAULT '100' , 
	PRIMARY KEY (`entry`) 
) ENGINE=MyISAM DEFAULT CHARSET='utf8';


/* Create table in target */
CREATE TABLE `worldbroadcast_localized`(
	`entry` int(11) NOT NULL  , 
	`language_code` varchar(5) COLLATE latin1_swedish_ci NOT NULL  , 
	`text` varchar(255) COLLATE utf8_unicode_ci NOT NULL  , 
	PRIMARY KEY (`entry`) 
) ENGINE=MyISAM DEFAULT CHARSET='utf8';


/* Alter table in target */
ALTER TABLE `worldmap_info` 
	ADD COLUMN `collision` tinyint(3) unsigned   NOT NULL DEFAULT '1' after `required_checkpoint`, COMMENT='';

/* Create table in target */
CREATE TABLE `worldmap_info_localized`(
	`entry` int(11) NOT NULL  , 
	`language_code` varchar(5) COLLATE latin1_swedish_ci NOT NULL  , 
	`text` varchar(255) COLLATE utf8_unicode_ci NOT NULL  , 
	PRIMARY KEY (`entry`) 
) ENGINE=MyISAM DEFAULT CHARSET='latin1';


/* Create table in target */
CREATE TABLE `worldstate_template`(
	`mapid` int(11) NOT NULL  , 
	`zone_mask` int(30) NOT NULL  , 
	`faction_mask` int(30) NOT NULL  , 
	`field_number` int(30) unsigned NOT NULL  , 
	`initial_value` int(30) NOT NULL  , 
	`comment` varchar(200) COLLATE utf8_general_ci NOT NULL  , 
	PRIMARY KEY (`field_number`) 
) ENGINE=MyISAM DEFAULT CHARSET='utf8';
INSERT INTO worldstate_template(mapid, zone_mask, faction_mask, field_number, initial_value, comment) VALUES(-1, -1, -1, 3901, 4, 'ARENA_SEASON_COUNT');
INSERT INTO worldstate_template(mapid, zone_mask, faction_mask, field_number, initial_value, comment) VALUES(-1, -1, -1, 3191, 4, 'ARENA_SEASON_STATE; 0 = finished; else started');
INSERT INTO `worldstate_template` VALUES (530,3483,-1,2476,0,'WORLDSTATE_HELLFIRE_ALLIANCE_TOWERS_CONTROLLED'),(530,3483,-1,2478,0,'WORLDSTATE_HELLFIRE_HORDE_TOWERS_CONTROLLED'),(530,3483,-1,2490,1,'WORLDSTATE_HELLFIRE_TOWER_DISPLAY_ALLIANCE'),(530,3483,-1,2489,1,'WORLDSTATE_HELLFIRE_TOWER_DISPLAY_HORDE'),(530,3483,-1,2473,0,'WORLDSTATE_HELLFIRE_PVP_CAPTURE_BAR_DISPLAY'),(530,3483,-1,2474,0,'WORLDSTATE_HELLFIRE_PVP_CAPTURE_BAR_VALUE'),(530,3483,-1,2472,1,'WORLDSTATE_HELLFIRE_STADIUM_NEUTRAL'),(530,3483,-1,2471,0,'WORLDSTATE_HELLFIRE_STADIUM_ALLIANCE'),(530,3483,-1,2470,0,'WORLDSTATE_HELLFIRE_STADIUM_HORDE'),(530,3483,-1,2482,1,'WORLDSTATE_HELLFIRE_OVERLOOK_NEUTRAL'),(530,3483,-1,2480,0,'WORLDSTATE_HELLFIRE_OVERLOOK_ALLIANCE'),(530,3483,-1,2481,0,'WORLDSTATE_HELLFIRE_OVERLOOK_HORDE'),(530,3483,-1,2485,1,'WORLDSTATE_HELLFIRE_BROKENHILL_NEUTRAL'),(530,3483,-1,2483,0,'WORLDSTATE_HELLFIRE_BROKENHILL_ALLIANCE'),(530,3483,-1,2484,0,'WORLDSTATE_HELLFIRE_BROKENHILL_HORDE'),(530,3518,-1,2502,0,'WORLDSTATE_HALAA_GUARD_DISPLAY_ALLIANCE'),(530,3518,-1,2503,0,'WORLDSTATE_HALAA_GUARD_DISPLAY_HORDE'),(530,3518,-1,2491,0,'WORLDSTATE_HALAA_GUARDS_REMAINING'),(530,3518,-1,2493,0,'WORLDSTATE_HALAA_GUARDS_REMAINING_MAX');


/* Drop in Second database */
DROP TABLE `worldstates`; 

/* Create table in target */
CREATE TABLE `worldstring_tables`(
	`entry` int(11) NOT NULL  auto_increment , 
	`text` varchar(255) COLLATE utf8_unicode_ci NOT NULL  , 
	PRIMARY KEY (`entry`) 
) ENGINE=MyISAM DEFAULT CHARSET='latin1';


/* Create table in target */
CREATE TABLE `worldstring_tables_localized`(
	`entry` int(11) NOT NULL  , 
	`language_code` varchar(5) COLLATE latin1_swedish_ci NOT NULL  , 
	`text` varchar(255) COLLATE utf8_unicode_ci NOT NULL  , 
	PRIMARY KEY (`entry`) 
) ENGINE=MyISAM DEFAULT CHARSET='latin1';

REPLACE INTO itempetfood(entry, food_type) VALUES(30610, 1);