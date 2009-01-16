/*
* Hearthstone World Database Template
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for achievement_rewards
-- ----------------------------
CREATE TABLE `achievement_rewards` (
  `achievementid` int(10) unsigned NOT NULL,
  `title_alliance` int(10) unsigned NOT NULL,
  `title_horde` int(10) unsigned NOT NULL,
  `itemid` int(10) unsigned NOT NULL,
  PRIMARY KEY (`achievementid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Achievement System';;

-- ----------------------------
-- Table structure for ai_agents
-- ----------------------------
CREATE TABLE `ai_agents` (
  `entry` int(11) unsigned NOT NULL DEFAULT '0',
  `type` enum('MELEE','RANGED','FLEE','SPELL','CALLFORHELP') NOT NULL DEFAULT 'SPELL',
  `chance` int(11) unsigned NOT NULL DEFAULT '0',
  `maxcount` int(11) unsigned NOT NULL DEFAULT '0',
  `spell` int(11) unsigned NOT NULL DEFAULT '0',
  `spelltype` enum('ROOT','HEAL','STUN','FEAR','SILENCE','CURSE','AOEDAMAGE','DAMAGE','SUMMON','BUFF','DEBUFF') NOT NULL DEFAULT 'ROOT',
  `targettype` enum('RANDOMTARGET','TARGETLOCATION','CREATURELOCATION','SELF','OWNER') NOT NULL DEFAULT 'RANDOMTARGET',
  `cooldown` int(8) NOT NULL DEFAULT '0',
  `floatMisc1` float NOT NULL DEFAULT '0',
  `Misc2` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`,`type`,`spell`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='AI System';

-- ----------------------------
-- Table structure for ai_threattospellid
-- ----------------------------
CREATE TABLE `ai_threattospellid` (
  `spell` int(11) unsigned NOT NULL DEFAULT '0',
  `mod` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`spell`),
  UNIQUE KEY `a` (`spell`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='AI System';

-- ----------------------------
-- Table structure for areatriggers
-- ----------------------------
CREATE TABLE `areatriggers` (
  `entry` int(11) NOT NULL DEFAULT '0',
  `type` tinyint(3) DEFAULT NULL,
  `map` int(11) DEFAULT NULL,
  `screen` int(11) DEFAULT NULL,
  `name` varchar(100) DEFAULT '0',
  `position_x` float NOT NULL DEFAULT '0',
  `position_y` float NOT NULL DEFAULT '0',
  `position_z` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `required_honor_rank` int(11) NOT NULL DEFAULT '0',
  `required_level` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Trigger System';

-- ----------------------------
-- Table structure for auctionhouse
-- ----------------------------
CREATE TABLE `auctionhouse` (
  `id` int(32) NOT NULL AUTO_INCREMENT,
  `creature_entry` bigint(64) unsigned NOT NULL DEFAULT '0',
  `group` int(32) NOT NULL DEFAULT '0',
  UNIQUE KEY `entryid` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COMMENT='List of Auctioneers';

-- ----------------------------
-- Table structure for banned_names
-- ----------------------------
CREATE TABLE `banned_names` (
  `name` varchar(30) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Banned character names';

-- ----------------------------
-- Table structure for clientaddons
-- ----------------------------
CREATE TABLE `clientaddons` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `crc` bigint(50) DEFAULT NULL,
  `banned` int(1) NOT NULL DEFAULT '0',
  `showinlist` int(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `index` (`name`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COMMENT='Client Addons';

-- ----------------------------
-- Table structure for command_overrides
-- ----------------------------
CREATE TABLE `command_overrides` (
  `command_name` varchar(100) NOT NULL,
  `access_level` varchar(10) NOT NULL,
  PRIMARY KEY (`command_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Commands System';

-- ----------------------------
-- Table structure for creature_formations
-- ----------------------------
CREATE TABLE `creature_formations` (
  `spawn_id` int(30) NOT NULL,
  `target_spawn_id` int(30) NOT NULL,
  `follow_angle` float NOT NULL,
  `follow_dist` float NOT NULL,
  PRIMARY KEY (`spawn_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Creature System';

-- ----------------------------
-- Table structure for creature_names
-- ----------------------------
CREATE TABLE `creature_names` (
  `entry` int(20) unsigned NOT NULL DEFAULT '0',
  `name` varchar(100) NOT NULL,
  `subname` varchar(100) NOT NULL DEFAULT ' ',
  `info_str` varchar(500) NOT NULL,
  `Flags1` int(30) unsigned NOT NULL DEFAULT '0',
  `type` int(30) NOT NULL DEFAULT '0',
  `family` int(30) NOT NULL DEFAULT '0',
  `rank` int(30) NOT NULL DEFAULT '0',
  `unk4` int(30) NOT NULL DEFAULT '0',
  `spelldataid` int(30) NOT NULL DEFAULT '0',
  `male_displayid` int(30) NOT NULL,
  `female_displayid` int(30) NOT NULL,
  `male_displayid2` int(30) NOT NULL DEFAULT '0',
  `female_displayid2` int(30) NOT NULL DEFAULT '0',
  `unknown_float1` float NOT NULL DEFAULT '0',
  `unknown_float2` float NOT NULL DEFAULT '0',
  `civilian` tinyint(30) NOT NULL DEFAULT '0',
  `leader` tinyint(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`),
  UNIQUE KEY `entry` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Creature System';

-- ----------------------------
-- Table structure for creature_names_localized
-- ----------------------------
CREATE TABLE `creature_names_localized` (
  `id` int(30) unsigned NOT NULL,
  `language_code` varchar(5) NOT NULL,
  `name` varchar(100) NOT NULL,
  `subname` varchar(100) NOT NULL,
  PRIMARY KEY (`id`,`language_code`),
  KEY `lol` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Localization System';

-- ----------------------------
-- Table structure for creature_proto
-- ----------------------------
CREATE TABLE `creature_proto` (
  `entry` int(30) unsigned NOT NULL,
  `minlevel` int(30) unsigned NOT NULL,
  `maxlevel` int(30) unsigned NOT NULL,
  `faction` int(30) unsigned NOT NULL DEFAULT '0',
  `minhealth` int(30) unsigned NOT NULL,
  `maxhealth` int(30) unsigned NOT NULL,
  `mana` int(30) unsigned NOT NULL DEFAULT '0',
  `scale` float NOT NULL DEFAULT '0',
  `npcflags` int(30) unsigned NOT NULL DEFAULT '0',
  `attacktime` int(30) unsigned NOT NULL DEFAULT '2000',
  `attacktype` int(4) NOT NULL DEFAULT '0',
  `mindamage` float NOT NULL DEFAULT '0',
  `maxdamage` float NOT NULL DEFAULT '0',
  `rangedattacktime` int(30) unsigned NOT NULL DEFAULT '0',
  `rangedmindamage` float unsigned NOT NULL DEFAULT '0',
  `rangedmaxdamage` float unsigned NOT NULL DEFAULT '0',
  `Item1` int(30) unsigned NOT NULL DEFAULT '0',
  `Item2` int(30) unsigned NOT NULL DEFAULT '0',
  `Item3` int(30) unsigned NOT NULL DEFAULT '0',
  `RespawnTime` int(30) unsigned NOT NULL DEFAULT '0',
  `resistance1` int(30) unsigned NOT NULL DEFAULT '0',
  `resistance2` int(30) unsigned NOT NULL DEFAULT '0',
  `resistance3` int(30) unsigned NOT NULL DEFAULT '0',
  `resistance4` int(30) unsigned NOT NULL DEFAULT '0',
  `resistance5` int(30) unsigned NOT NULL DEFAULT '0',
  `resistance6` int(30) unsigned NOT NULL DEFAULT '0',
  `resistance7` int(30) NOT NULL DEFAULT '0',
  `combat_reach` float NOT NULL DEFAULT '0',
  `bounding_radius` float NOT NULL DEFAULT '0',
  `auras` longtext NOT NULL,
  `boss` int(11) unsigned NOT NULL DEFAULT '0',
  `money` int(30) NOT NULL DEFAULT '0',
  `invisibility_type` int(30) unsigned NOT NULL DEFAULT '0',
  `death_state` int(30) unsigned NOT NULL DEFAULT '0',
  `walk_speed` float NOT NULL DEFAULT '2.5',
  `run_speed` float NOT NULL DEFAULT '8',
  `fly_speed` float NOT NULL DEFAULT '14',
  `extra_a9_flags` int(30) NOT NULL DEFAULT '0',
  `auraimmune_flag` int(10) unsigned NOT NULL DEFAULT '0',
  `vehicle_entry` int(11) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`entry`),
  UNIQUE KEY `ID` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Creature System';;

-- ----------------------------
-- Table structure for creature_quest_finisher
-- ----------------------------
CREATE TABLE `creature_quest_finisher` (
  `id` int(11) unsigned NOT NULL DEFAULT '0',
  `quest` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Quest System';

-- ----------------------------
-- Table structure for creature_quest_starter
-- ----------------------------
CREATE TABLE `creature_quest_starter` (
  `id` int(11) unsigned NOT NULL DEFAULT '0',
  `quest` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Quest System';

-- ----------------------------
-- Table structure for creature_spawns
-- ----------------------------
CREATE TABLE `creature_spawns` (
  `id` int(30) NOT NULL AUTO_INCREMENT,
  `entry` int(30) NOT NULL,
  `map` int(30) NOT NULL,
  `position_x` float NOT NULL,
  `position_y` float NOT NULL,
  `position_z` float NOT NULL,
  `orientation` float NOT NULL,
  `movetype` int(30) NOT NULL DEFAULT '0',
  `displayid` int(30) unsigned NOT NULL DEFAULT '0',
  `faction` int(30) NOT NULL DEFAULT '35',
  `flags` int(30) NOT NULL DEFAULT '0',
  `bytes` int(30) NOT NULL DEFAULT '0',
  `bytes1` int(30) NOT NULL,
  `bytes2` int(30) NOT NULL DEFAULT '0',
  `emote_state` int(30) NOT NULL DEFAULT '0',
  `channel_spell` int(30) unsigned NOT NULL DEFAULT '0',
  `channel_target_sqlid_go` int(30) NOT NULL DEFAULT '0',
  `channel_target_sqlid_creature` int(30) NOT NULL DEFAULT '0',
  `standstate` int(10) NOT NULL DEFAULT '0',
  `MountedDisplayID` int(11) NOT NULL DEFAULT '0',
  `phase` int(11) NOT NULL DEFAULT '1',
  `vehicle` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COMMENT='Spawn System';

-- ----------------------------
-- Table structure for creature_spawns_brewfest
-- ----------------------------
CREATE TABLE `creature_spawns_brewfest` (
  `id` int(30) NOT NULL AUTO_INCREMENT,
  `entry` int(30) NOT NULL,
  `map` int(30) NOT NULL,
  `position_x` float NOT NULL,
  `position_y` float NOT NULL,
  `position_z` float NOT NULL,
  `orientation` float NOT NULL,
  `movetype` int(30) NOT NULL DEFAULT '0',
  `displayid` int(30) unsigned NOT NULL DEFAULT '0',
  `faction` int(30) NOT NULL DEFAULT '35',
  `flags` int(30) NOT NULL DEFAULT '0',
  `bytes` int(30) NOT NULL DEFAULT '0',
  `bytes1` int(30) NOT NULL DEFAULT '0',
  `bytes2` int(30) NOT NULL DEFAULT '0',
  `emote_state` int(30) NOT NULL DEFAULT '0',
  `npc_respawn_link` int(30) NOT NULL DEFAULT '0',
  `channel_spell` int(30) unsigned NOT NULL DEFAULT '0',
  `channel_target_sqlid` int(30) NOT NULL DEFAULT '0',
  `channel_target_sqlid_creature` int(30) NOT NULL DEFAULT '0',
  `standstate` int(10) NOT NULL DEFAULT '0',
  `MounteddisplayID` int(10) NOT NULL DEFAULT '0',
  `Phase` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for creature_staticspawns
-- ----------------------------
CREATE TABLE `creature_staticspawns` (
  `id` int(30) NOT NULL AUTO_INCREMENT,
  `entry` int(30) NOT NULL,
  `map` int(11) NOT NULL DEFAULT '0',
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `o` float NOT NULL,
  `movetype` int(11) NOT NULL DEFAULT '0',
  `displayid` int(11) NOT NULL,
  `factionid` int(11) NOT NULL DEFAULT '0',
  `flags` int(30) NOT NULL DEFAULT '0',
  `bytes` int(30) NOT NULL DEFAULT '0',
  `bytes1` int(30) NOT NULL DEFAULT '0',
  `bytes2` int(30) NOT NULL DEFAULT '0',
  `emote_state` int(11) NOT NULL DEFAULT '0',
  `channel_spell` int(30) NOT NULL DEFAULT '0',
  `channel_target_sqlid_go` int(30) NOT NULL DEFAULT '0',
  `channel_target_sqlid_creature` int(30) NOT NULL DEFAULT '0',
  `MountedDisplayID` int(11) NOT NULL DEFAULT '0',
  `Phase` int(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for creature_waypoints
-- ----------------------------
CREATE TABLE `creature_waypoints` (
  `spawnid` int(10) NOT NULL,
  `waypointid` int(2) NOT NULL DEFAULT '0',
  `position_x` float NOT NULL DEFAULT '0',
  `position_y` float NOT NULL DEFAULT '0',
  `position_z` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `waittime` int(6) NOT NULL DEFAULT '0',
  `flags` int(3) NOT NULL DEFAULT '0',
  `forwardemoteoneshot` int(1) NOT NULL DEFAULT '0',
  `forwardemoteid` int(4) NOT NULL DEFAULT '0',
  `backwardemoteoneshot` int(1) NOT NULL DEFAULT '0',
  `backwardemoteid` int(4) NOT NULL DEFAULT '0',
  `forwardskinid` int(10) NOT NULL DEFAULT '0',
  `backwardskinid` int(10) NOT NULL DEFAULT '0',
  `forwardStandState` int(11) NOT NULL DEFAULT '0',
  `backwardStandState` int(11) NOT NULL DEFAULT '0',
  `forwardSpellToCast` int(11) NOT NULL DEFAULT '0',
  `backwardSpellToCast` int(11) NOT NULL DEFAULT '0',
  `forwardSayText` varchar(1024) NOT NULL DEFAULT '',
  `backwardSaytext` varchar(1024) NOT NULL DEFAULT '',
  PRIMARY KEY (`spawnid`,`waypointid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Creature System';

-- ----------------------------
-- Table structure for creatureloot
-- ----------------------------
CREATE TABLE `creatureloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(11) NOT NULL DEFAULT '0',
  `itemid` int(11) NOT NULL DEFAULT '0',
  `percentchance` float NOT NULL DEFAULT '0',
  `heroicpercentchance` float NOT NULL DEFAULT '0',
  `mincount` int(11) unsigned NOT NULL DEFAULT '1',
  `maxcount` int(11) unsigned NOT NULL DEFAULT '1',
  `ffa_loot` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`),
  UNIQUE KEY `index` (`index`),
  UNIQUE KEY `entryid` (`entryid`,`itemid`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COMMENT='Loot System';

-- ----------------------------
-- Table structure for disenchantingloot
-- ----------------------------
CREATE TABLE `disenchantingloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(10) unsigned NOT NULL DEFAULT '0',
  `itemid` int(10) unsigned NOT NULL DEFAULT '0',
  `percentchance` float NOT NULL DEFAULT '0',
  `heroicpercentchance` float DEFAULT '0',
  `mincount` int(30) DEFAULT '1',
  `maxcount` int(30) DEFAULT '1',
  `ffa_loot` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`),
  UNIQUE KEY `index` (`index`),
  UNIQUE KEY `entryid` (`entryid`,`itemid`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COMMENT='Loot System';

-- ----------------------------
-- Table structure for fishing
-- ----------------------------
CREATE TABLE `fishing` (
  `Zone` int(11) unsigned NOT NULL DEFAULT '0',
  `MinSkill` int(11) unsigned DEFAULT NULL,
  `MaxSkill` int(11) unsigned DEFAULT NULL,
  UNIQUE KEY `Zone` (`Zone`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for fishingloot
-- ----------------------------
CREATE TABLE `fishingloot` (
  `index` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `entryid` int(11) unsigned NOT NULL DEFAULT '0',
  `itemid` int(11) unsigned NOT NULL DEFAULT '0',
  `percentchance` float NOT NULL DEFAULT '0',
  `heroicpercentchance` float NOT NULL DEFAULT '0',
  `mincount` int(11) unsigned NOT NULL DEFAULT '1',
  `maxcount` int(11) unsigned NOT NULL DEFAULT '1',
  `ffa_loot` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`),
  UNIQUE KEY `index` (`index`),
  UNIQUE KEY `entryid` (`entryid`,`itemid`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COMMENT='Loot System';

-- ----------------------------
-- Table structure for gameobject_names
-- ----------------------------
CREATE TABLE `gameobject_names` (
  `entry` int(20) unsigned NOT NULL,
  `Type` int(100) unsigned NOT NULL DEFAULT '0',
  `DisplayID` int(100) unsigned NOT NULL DEFAULT '0',
  `Name` varchar(100) NOT NULL DEFAULT '0',
  `spellfocus` int(30) NOT NULL DEFAULT '0',
  `sound1` int(30) NOT NULL DEFAULT '0',
  `sound2` int(30) NOT NULL DEFAULT '0',
  `sound3` int(30) NOT NULL DEFAULT '0',
  `sound4` int(30) NOT NULL DEFAULT '0',
  `sound5` int(30) NOT NULL DEFAULT '0',
  `sound6` int(30) NOT NULL DEFAULT '0',
  `sound7` int(30) NOT NULL DEFAULT '0',
  `sound8` int(30) NOT NULL DEFAULT '0',
  `sound9` int(30) NOT NULL DEFAULT '0',
  `unknown1` int(30) NOT NULL DEFAULT '0',
  `unknown2` int(30) NOT NULL DEFAULT '0',
  `unknown3` int(30) NOT NULL DEFAULT '0',
  `unknown4` int(30) NOT NULL DEFAULT '0',
  `unknown5` int(30) NOT NULL DEFAULT '0',
  `unknown6` int(30) NOT NULL DEFAULT '0',
  `unknown7` int(30) NOT NULL DEFAULT '0',
  `unknown8` int(30) NOT NULL DEFAULT '0',
  `unknown9` int(30) NOT NULL DEFAULT '0',
  `unknown10` int(30) NOT NULL DEFAULT '0',
  `unknown11` int(30) NOT NULL DEFAULT '0',
  `unknown12` int(30) NOT NULL DEFAULT '0',
  `unknown13` int(30) NOT NULL DEFAULT '0',
  `unknown14` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`),
  UNIQUE KEY `entry` (`entry`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COMMENT='GameObject System';

-- ----------------------------
-- Table structure for gameobject_names_localized
-- ----------------------------
CREATE TABLE `gameobject_names_localized` (
  `entry` int(30) NOT NULL,
  `language_code` varchar(5) NOT NULL,
  `name` varchar(100) NOT NULL,
  PRIMARY KEY (`entry`,`language_code`),
  KEY `lol` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Localization System';

-- ----------------------------
-- Table structure for gameobject_quest_finisher
-- ----------------------------
CREATE TABLE `gameobject_quest_finisher` (
  `id` int(11) unsigned NOT NULL DEFAULT '0',
  `quest` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`quest`),
  UNIQUE KEY `quest` (`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Quest System';

-- ----------------------------
-- Table structure for gameobject_quest_item_binding
-- ----------------------------
CREATE TABLE `gameobject_quest_item_binding` (
  `entry` int(11) NOT NULL DEFAULT '0',
  `quest` int(11) NOT NULL DEFAULT '0',
  `item` int(11) NOT NULL DEFAULT '0',
  `item_count` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`,`quest`,`item`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Quest System';

-- ----------------------------
-- Table structure for gameobject_quest_pickup_binding
-- ----------------------------
CREATE TABLE `gameobject_quest_pickup_binding` (
  `entry` int(11) NOT NULL DEFAULT '0',
  `quest` int(11) NOT NULL DEFAULT '0',
  `required_count` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`,`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Quest System';

-- ----------------------------
-- Table structure for gameobject_quest_starter
-- ----------------------------
CREATE TABLE `gameobject_quest_starter` (
  `id` int(11) unsigned NOT NULL DEFAULT '0',
  `quest` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Quest System';

-- ----------------------------
-- Table structure for gameobject_spawns
-- ----------------------------
CREATE TABLE `gameobject_spawns` (
  `ID` int(30) unsigned NOT NULL AUTO_INCREMENT,
  `Entry` int(10) unsigned NOT NULL DEFAULT '0',
  `Map` int(10) unsigned NOT NULL DEFAULT '0',
  `position_x` float NOT NULL DEFAULT '0',
  `position_y` float NOT NULL DEFAULT '0',
  `position_z` float NOT NULL DEFAULT '0',
  `Facing` float NOT NULL DEFAULT '0',
  `orientation1` float NOT NULL DEFAULT '0',
  `orientation2` float NOT NULL DEFAULT '0',
  `orientation3` float NOT NULL DEFAULT '0',
  `orientation4` float NOT NULL DEFAULT '0',
  `State` int(10) unsigned NOT NULL DEFAULT '0',
  `Flags` int(10) unsigned NOT NULL DEFAULT '0',
  `Faction` int(10) unsigned NOT NULL DEFAULT '0',
  `Scale` float NOT NULL DEFAULT '0',
  `phase` int(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`ID`),
  KEY `Map` (`Map`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8 COMMENT='GameObject System';

-- ----------------------------
-- Table structure for gameobject_staticspawns
-- ----------------------------
CREATE TABLE `gameobject_staticspawns` (
  `id` int(30) NOT NULL AUTO_INCREMENT,
  `entry` int(30) NOT NULL,
  `map` int(11) NOT NULL DEFAULT '0',
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `facing` float NOT NULL,
  `o1` float NOT NULL,
  `o2` float NOT NULL,
  `o3` float NOT NULL,
  `o4` float NOT NULL,
  `state` int(11) NOT NULL DEFAULT '0',
  `flags` int(30) NOT NULL DEFAULT '0',
  `faction` int(11) NOT NULL DEFAULT '0',
  `scale` float NOT NULL,
  `phase` int(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8 COMMENT='GameObject System';

-- ----------------------------
-- Table structure for graveyards
-- ----------------------------
CREATE TABLE `graveyards` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `position_x` float NOT NULL DEFAULT '0',
  `position_y` float NOT NULL DEFAULT '0',
  `position_z` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `zoneid` int(10) unsigned NOT NULL DEFAULT '0',
  `adjacentzoneid` int(10) unsigned NOT NULL DEFAULT '0',
  `mapid` int(10) unsigned NOT NULL DEFAULT '0',
  `faction` int(10) unsigned NOT NULL DEFAULT '0',
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COMMENT='Graveyard System';

-- ----------------------------
-- Table structure for item_quest_association
-- ----------------------------
CREATE TABLE `item_quest_association` (
  `item` int(11) NOT NULL DEFAULT '0',
  `quest` int(11) NOT NULL DEFAULT '0',
  `item_count` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`item`,`quest`),
  UNIQUE KEY `item` (`item`,`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Quest System';

-- ----------------------------
-- Table structure for item_randomprop_groups
-- ----------------------------
CREATE TABLE `item_randomprop_groups` (
  `entry_id` int(30) NOT NULL,
  `randomprops_entryid` int(30) NOT NULL,
  `chance` float NOT NULL,
  PRIMARY KEY (`entry_id`,`randomprops_entryid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Item Random Enchantment System';

-- ----------------------------
-- Table structure for item_randomsuffix_groups
-- ----------------------------
CREATE TABLE `item_randomsuffix_groups` (
  `entry_id` int(30) NOT NULL,
  `randomsuffix_entryid` int(30) NOT NULL,
  `chance` float NOT NULL,
  PRIMARY KEY (`entry_id`,`randomsuffix_entryid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Item Random Enchantment System';

-- ----------------------------
-- Table structure for itemloot
-- ----------------------------
CREATE TABLE `itemloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(11) unsigned NOT NULL DEFAULT '0',
  `itemid` int(11) unsigned NOT NULL DEFAULT '25',
  `percentchance` float NOT NULL DEFAULT '1',
  `heroicpercentchance` float NOT NULL DEFAULT '0',
  `mincount` int(11) unsigned NOT NULL DEFAULT '1',
  `maxcount` int(11) unsigned NOT NULL DEFAULT '1',
  `ffa_loot` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`),
  UNIQUE KEY `entryid` (`entryid`,`itemid`),
  KEY `i_gameobj_loot_entry` (`entryid`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for itempages
-- ----------------------------
CREATE TABLE `itempages` (
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `text` text COLLATE utf8_unicode_ci,
  `next_page` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Item System';

-- ----------------------------
-- Table structure for itempages_localized
-- ----------------------------
CREATE TABLE `itempages_localized` (
  `entry` int(30) NOT NULL,
  `language_code` varchar(5) NOT NULL,
  `text` text NOT NULL,
  PRIMARY KEY (`entry`,`language_code`),
  KEY `a` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Localization System';

-- ----------------------------
-- Table structure for itempetfood
-- ----------------------------
CREATE TABLE `itempetfood` (
  `entry` int(11) NOT NULL,
  `food_type` int(11) NOT NULL,
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for items
-- ----------------------------
CREATE TABLE `items` (
  `entry` int(255) unsigned NOT NULL DEFAULT '0',
  `class` int(30) NOT NULL DEFAULT '0',
  `subclass` int(30) NOT NULL DEFAULT '0',
  `field4` int(10) NOT NULL DEFAULT '0',
  `name1` varchar(255) NOT NULL,
  `name2` varchar(255) NOT NULL DEFAULT '',
  `name3` varchar(255) NOT NULL DEFAULT '',
  `name4` varchar(255) NOT NULL DEFAULT '',
  `displayid` int(70) unsigned NOT NULL DEFAULT '0',
  `quality` int(30) NOT NULL DEFAULT '0',
  `flags` int(30) NOT NULL DEFAULT '0',
  `buyprice` int(30) NOT NULL DEFAULT '0',
  `sellprice` int(30) NOT NULL DEFAULT '0',
  `inventorytype` int(30) NOT NULL DEFAULT '0',
  `allowableclass` int(30) NOT NULL DEFAULT '0',
  `allowablerace` int(30) NOT NULL DEFAULT '0',
  `itemlevel` int(30) NOT NULL DEFAULT '0',
  `requiredlevel` int(30) NOT NULL DEFAULT '0',
  `RequiredSkill` int(30) NOT NULL DEFAULT '0',
  `RequiredSkillRank` int(30) NOT NULL DEFAULT '0',
  `RequiredSkillSubRank` int(30) NOT NULL DEFAULT '0',
  `RequiredPlayerRank1` int(30) NOT NULL DEFAULT '0',
  `RequiredPlayerRank2` int(30) NOT NULL DEFAULT '0',
  `RequiredFaction` int(30) NOT NULL DEFAULT '0',
  `RequiredFactionStanding` int(30) NOT NULL DEFAULT '0',
  `Unique` int(30) NOT NULL DEFAULT '0',
  `maxcount` int(30) NOT NULL DEFAULT '0',
  `ContainerSlots` int(30) NOT NULL DEFAULT '0',
  `stat_type1` int(30) NOT NULL DEFAULT '0',
  `stat_value1` int(30) NOT NULL DEFAULT '0',
  `stat_type2` int(30) NOT NULL DEFAULT '0',
  `stat_value2` int(30) NOT NULL DEFAULT '0',
  `stat_type3` int(30) NOT NULL DEFAULT '0',
  `stat_value3` int(30) NOT NULL DEFAULT '0',
  `stat_type4` int(30) NOT NULL DEFAULT '0',
  `stat_value4` int(30) NOT NULL DEFAULT '0',
  `stat_type5` int(30) NOT NULL DEFAULT '0',
  `stat_value5` int(30) NOT NULL DEFAULT '0',
  `stat_type6` int(30) NOT NULL DEFAULT '0',
  `stat_value6` int(30) NOT NULL DEFAULT '0',
  `stat_type7` int(30) NOT NULL DEFAULT '0',
  `stat_value7` int(30) NOT NULL DEFAULT '0',
  `stat_type8` int(30) NOT NULL DEFAULT '0',
  `stat_value8` int(30) NOT NULL DEFAULT '0',
  `stat_type9` int(30) NOT NULL DEFAULT '0',
  `stat_value9` int(30) NOT NULL DEFAULT '0',
  `stat_type10` int(30) NOT NULL DEFAULT '0',
  `stat_value10` int(30) NOT NULL DEFAULT '0',
  `dmg_min1` float NOT NULL DEFAULT '0',
  `dmg_max1` float NOT NULL DEFAULT '0',
  `dmg_type1` int(30) NOT NULL DEFAULT '0',
  `dmg_min2` float NOT NULL DEFAULT '0',
  `dmg_max2` float NOT NULL DEFAULT '0',
  `dmg_type2` int(30) NOT NULL DEFAULT '0',
  `dmg_min3` float NOT NULL DEFAULT '0',
  `dmg_max3` float NOT NULL DEFAULT '0',
  `dmg_type3` int(30) NOT NULL DEFAULT '0',
  `dmg_min4` float NOT NULL DEFAULT '0',
  `dmg_max4` float NOT NULL DEFAULT '0',
  `dmg_type4` int(30) NOT NULL DEFAULT '0',
  `dmg_min5` float NOT NULL DEFAULT '0',
  `dmg_max5` float NOT NULL DEFAULT '0',
  `dmg_type5` int(30) NOT NULL DEFAULT '0',
  `armor` int(30) NOT NULL DEFAULT '0',
  `holy_res` int(30) NOT NULL DEFAULT '0',
  `fire_res` int(30) NOT NULL DEFAULT '0',
  `nature_res` int(30) NOT NULL DEFAULT '0',
  `frost_res` int(30) NOT NULL DEFAULT '0',
  `shadow_res` int(30) NOT NULL DEFAULT '0',
  `arcane_res` int(30) NOT NULL DEFAULT '0',
  `delay` int(30) NOT NULL DEFAULT '0',
  `ammo_type` int(30) NOT NULL DEFAULT '0',
  `range` float NOT NULL DEFAULT '0',
  `spellid_1` int(30) NOT NULL DEFAULT '0',
  `spelltrigger_1` int(30) NOT NULL DEFAULT '0',
  `spellcharges_1` int(30) NOT NULL DEFAULT '0',
  `spellcooldown_1` int(30) NOT NULL DEFAULT '0',
  `spellcategory_1` int(30) NOT NULL DEFAULT '0',
  `spellcategorycooldown_1` int(30) NOT NULL DEFAULT '0',
  `spellid_2` int(30) NOT NULL DEFAULT '0',
  `spelltrigger_2` int(30) NOT NULL DEFAULT '0',
  `spellcharges_2` int(30) NOT NULL DEFAULT '0',
  `spellcooldown_2` int(30) NOT NULL DEFAULT '0',
  `spellcategory_2` int(30) NOT NULL DEFAULT '0',
  `spellcategorycooldown_2` int(30) NOT NULL DEFAULT '0',
  `spellid_3` int(30) NOT NULL DEFAULT '0',
  `spelltrigger_3` int(30) NOT NULL DEFAULT '0',
  `spellcharges_3` int(30) NOT NULL DEFAULT '0',
  `spellcooldown_3` int(30) NOT NULL DEFAULT '0',
  `spellcategory_3` int(30) NOT NULL DEFAULT '0',
  `spellcategorycooldown_3` int(30) NOT NULL DEFAULT '0',
  `spellid_4` int(30) NOT NULL DEFAULT '0',
  `spelltrigger_4` int(30) NOT NULL DEFAULT '0',
  `spellcharges_4` int(30) NOT NULL DEFAULT '0',
  `spellcooldown_4` int(30) NOT NULL DEFAULT '0',
  `spellcategory_4` int(30) NOT NULL DEFAULT '0',
  `spellcategorycooldown_4` int(30) NOT NULL DEFAULT '0',
  `spellid_5` int(30) NOT NULL DEFAULT '0',
  `spelltrigger_5` int(30) NOT NULL DEFAULT '0',
  `spellcharges_5` int(30) NOT NULL DEFAULT '0',
  `spellcooldown_5` int(30) NOT NULL DEFAULT '0',
  `spellcategory_5` int(30) NOT NULL DEFAULT '0',
  `spellcategorycooldown_5` int(30) NOT NULL DEFAULT '0',
  `bonding` int(30) NOT NULL DEFAULT '0',
  `description` varchar(255) NOT NULL DEFAULT '',
  `page_id` int(30) NOT NULL DEFAULT '0',
  `page_language` int(30) NOT NULL DEFAULT '0',
  `page_material` int(30) NOT NULL DEFAULT '0',
  `quest_id` int(30) NOT NULL DEFAULT '0',
  `lock_id` int(30) NOT NULL DEFAULT '0',
  `lock_material` int(30) NOT NULL DEFAULT '0',
  `sheathID` int(30) NOT NULL DEFAULT '0',
  `randomprop` int(30) NOT NULL DEFAULT '0',
  `unk203_1` int(11) NOT NULL DEFAULT '0',
  `block` int(30) NOT NULL DEFAULT '0',
  `itemset` int(30) NOT NULL DEFAULT '0',
  `MaxDurability` int(30) NOT NULL DEFAULT '0',
  `ZoneNameID` int(30) NOT NULL DEFAULT '0',
  `mapid` int(30) DEFAULT '0',
  `bagfamily` int(30) NOT NULL DEFAULT '0',
  `TotemCategory` int(30) DEFAULT '0',
  `socket_color_1` int(30) DEFAULT '0',
  `unk201_3` int(30) NOT NULL DEFAULT '0',
  `socket_color_2` int(30) DEFAULT '0',
  `unk201_5` int(30) NOT NULL DEFAULT '0',
  `socket_color_3` int(30) DEFAULT '0',
  `unk201_7` int(30) NOT NULL DEFAULT '0',
  `socket_bonus` int(30) DEFAULT '0',
  `GemProperties` int(30) DEFAULT '0',
  `ReqDisenchantSkill` int(30) NOT NULL DEFAULT '-1',
  `gayshit` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`),
  UNIQUE KEY `entry` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for items_localized
-- ----------------------------
CREATE TABLE `items_localized` (
  `entry` int(30) NOT NULL,
  `language_code` varchar(5) NOT NULL,
  `name` varchar(100) NOT NULL,
  `description` varchar(100) NOT NULL,
  PRIMARY KEY (`entry`,`language_code`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Localization System';

-- ----------------------------
-- Table structure for lootrandomprop
-- ----------------------------
CREATE TABLE `lootrandomprop` (
  `entryid` int(11) NOT NULL DEFAULT '0',
  `propid` int(11) NOT NULL DEFAULT '0',
  `percentchance` float NOT NULL,
  PRIMARY KEY (`entryid`,`propid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Loot System';

-- ----------------------------
-- Table structure for map_checkpoint
-- ----------------------------
CREATE TABLE `map_checkpoint` (
  `entry` int(30) NOT NULL,
  `prereq_checkpoint_id` int(30) NOT NULL,
  `creature_id` int(30) NOT NULL,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Map System';

-- ----------------------------
-- Table structure for millingloot
-- ----------------------------
CREATE TABLE `millingloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(11) unsigned NOT NULL DEFAULT '0',
  `itemid` int(11) unsigned NOT NULL DEFAULT '0',
  `percentchance` float NOT NULL DEFAULT '0',
  `heroicpercentchance` float DEFAULT '0',
  `mincount` int(30) DEFAULT '1',
  `maxcount` int(30) DEFAULT '1',
  `ffa_loot` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for news_announcements
-- ----------------------------
CREATE TABLE `news_announcements` (
  `id` int(30) unsigned NOT NULL AUTO_INCREMENT,
  `faction_mask` int(30) NOT NULL,
  `lastTime` int(30) NOT NULL,
  `message_text` varchar(500) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for npc_gossip_textid
-- ----------------------------
CREATE TABLE `npc_gossip_textid` (
  `creatureid` int(30) NOT NULL DEFAULT '0',
  `textid` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`creatureid`),
  UNIQUE KEY `index` (`creatureid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='NPC System';

-- ----------------------------
-- Table structure for npc_monstersay
-- ----------------------------
CREATE TABLE `npc_monstersay` (
  `entry` int(11) NOT NULL,
  `event` int(11) NOT NULL,
  `chance` float NOT NULL,
  `language` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `monstername` longtext,
  `text0` longtext,
  `text1` longtext,
  `text2` longtext,
  `text3` longtext,
  `text4` longtext,
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='NPC System';

-- ----------------------------
-- Table structure for npc_text
-- ----------------------------
CREATE TABLE `npc_text` (
  `entry` int(11) unsigned NOT NULL DEFAULT '0',
  `prob0` float NOT NULL DEFAULT '0',
  `text0_0` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `text0_1` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `lang0` int(10) unsigned NOT NULL default '0',
  `em0_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob1` float NOT NULL DEFAULT '0',
  `text1_0` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `text1_1` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `lang1` int(10) unsigned NOT NULL default '0',
  `em1_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob2` float NOT NULL DEFAULT '0',
  `text2_0` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `text2_1` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `lang2` int(10) unsigned NOT NULL default '0',
  `em2_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob3` float NOT NULL DEFAULT '0',
  `text3_0` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `text3_1` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `lang3` int(10) unsigned NOT NULL default '0',
  `em3_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob4` float NOT NULL DEFAULT '0',
  `text4_0` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `text4_1` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `lang4` int(10) unsigned NOT NULL default '0',
  `em4_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob5` float NOT NULL DEFAULT '0',
  `text5_0` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `text5_1` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `lang5` int(10) unsigned NOT NULL default '0',
  `em5_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob6` float NOT NULL DEFAULT '0',
  `text6_0` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `text6_1` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `lang6` int(10) unsigned NOT NULL default '0',
  `em6_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob7` float NOT NULL DEFAULT '0',
  `text7_0` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `text7_1` longtext character set utf8 collate utf8_unicode_ci NOT NULL,
  `lang7` int(10) unsigned NOT NULL default '0',
  `em7_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_5` int(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for npc_text_localized
-- ----------------------------
CREATE TABLE `npc_text_localized` (
  `entry` int(30) NOT NULL,
  `language_code` varchar(5) NOT NULL,
  `text0` varchar(200) NOT NULL,
  `text0_1` varchar(200) NOT NULL,
  `text1` varchar(200) NOT NULL,
  `text1_1` varchar(200) NOT NULL,
  `text2` varchar(200) NOT NULL,
  `text2_1` varchar(200) NOT NULL,
  `text3` varchar(200) NOT NULL,
  `text3_1` varchar(200) NOT NULL,
  `text4` varchar(200) NOT NULL,
  `text4_1` varchar(200) NOT NULL,
  `text5` varchar(200) NOT NULL,
  `text5_1` varchar(200) NOT NULL,
  `text6` varchar(200) NOT NULL,
  `text6_1` varchar(200) NOT NULL,
  `text7` varchar(200) NOT NULL,
  `text7_1` varchar(200) NOT NULL,
  PRIMARY KEY (`entry`,`language_code`),
  KEY `lol` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Localization System';

-- ----------------------------
-- Table structure for objectloot
-- ----------------------------
CREATE TABLE `objectloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(11) NOT NULL DEFAULT '0',
  `itemid` int(11) NOT NULL DEFAULT '0',
  `percentchance` float NOT NULL DEFAULT '0',
  `heroicpercentchance` float NOT NULL DEFAULT '0',
  `mincount` int(11) unsigned NOT NULL DEFAULT '1',
  `maxcount` int(11) unsigned NOT NULL DEFAULT '1',
  `ffa_loot` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`),
  UNIQUE KEY `entryid_2` (`entryid`,`itemid`),
  KEY `entryid` (`entryid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Loot System';

-- ----------------------------
-- Table structure for petdefaultspells
-- ----------------------------
CREATE TABLE `petdefaultspells` (
  `entry` int(11) NOT NULL DEFAULT '0',
  `spell` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`,`spell`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Pet System';

-- ----------------------------
-- Table structure for pickpocketingloot
-- ----------------------------
CREATE TABLE `pickpocketingloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(11) unsigned NOT NULL DEFAULT '0',
  `itemid` int(11) unsigned NOT NULL DEFAULT '25',
  `percentchance` float NOT NULL DEFAULT '0',
  `heroicpercentchance` float NOT NULL DEFAULT '0',
  `mincount` int(11) unsigned NOT NULL DEFAULT '1',
  `maxcount` int(11) unsigned NOT NULL DEFAULT '1',
  `ffa_loot` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`),
  UNIQUE KEY `entryid` (`entryid`,`itemid`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COMMENT='Loot System';

-- ----------------------------
-- Table structure for playercreateinfo
-- ----------------------------
CREATE TABLE `playercreateinfo` (
  `Index` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `race` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `factiontemplate` int(5) NOT NULL DEFAULT '0',
  `class` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `mapID` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `zoneID` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  `displayID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `BaseStrength` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BaseAgility` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BaseStamina` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BaseIntellect` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BaseSpirit` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BaseHealth` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `BaseMana` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `BaseRage` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `BaseFocus` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `BaseEnergy` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `Runic` mediumint(8) NOT NULL DEFAULT '0',
  `attackpower` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `mindmg` float NOT NULL DEFAULT '0',
  `maxdmg` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`Index`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COMMENT='Player System';

-- ----------------------------
-- Table structure for playercreateinfo_bars
-- ----------------------------
CREATE TABLE `playercreateinfo_bars` (
  `race` tinyint(3) unsigned NOT NULL,
  `class` tinyint(3) unsigned NOT NULL,
  `button` int(10) unsigned NOT NULL,
  `action` int(10) unsigned DEFAULT NULL,
  `type` int(10) unsigned DEFAULT NULL,
  `misc` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`race`,`class`,`button`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Player System';

-- ----------------------------
-- Table structure for playercreateinfo_items
-- ----------------------------
CREATE TABLE `playercreateinfo_items` (
  `indexid` int(4) NOT NULL,
  `protoid` int(4) NOT NULL,
  `slotid` int(10) NOT NULL,
  `amount` int(3) NOT NULL,
  PRIMARY KEY (`indexid`,`protoid`,`slotid`),
  UNIQUE KEY `item` (`indexid`,`protoid`,`slotid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Player System';

-- ----------------------------
-- Table structure for playercreateinfo_skills
-- ----------------------------
CREATE TABLE `playercreateinfo_skills` (
  `indexid` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `skillid` int(10) unsigned NOT NULL DEFAULT '0',
  `level` int(10) unsigned NOT NULL DEFAULT '0',
  `maxlevel` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`indexid`,`skillid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Player System';

-- ----------------------------
-- Table structure for playercreateinfo_spells
-- ----------------------------
CREATE TABLE `playercreateinfo_spells` (
  `indexid` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `spellid` smallint(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`indexid`,`spellid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Player System';

-- ----------------------------
-- Table structure for prestartqueries
-- ----------------------------
CREATE TABLE `prestartqueries` (
  `Query` varchar(1024) NOT NULL,
  `SingleShot` int(1) unsigned NOT NULL DEFAULT '1',
  `Seq` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`Seq`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for professiondiscoveries
-- ----------------------------
CREATE TABLE `professiondiscoveries` (
  `SpellId` int(10) unsigned NOT NULL DEFAULT '0',
  `SpellToDiscover` int(10) unsigned NOT NULL DEFAULT '0',
  `SkillValue` int(10) unsigned NOT NULL DEFAULT '0',
  `Chance` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`SpellId`,`SpellToDiscover`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for prospectingloot
-- ----------------------------
CREATE TABLE `prospectingloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(11) unsigned NOT NULL DEFAULT '0',
  `itemid` int(11) unsigned NOT NULL DEFAULT '25',
  `percentchance` float NOT NULL DEFAULT '100',
  `heroicpercentchance` float DEFAULT '0',
  `mincount` int(30) DEFAULT '1',
  `maxcount` int(30) DEFAULT '1',
  `ffa_loot` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for quests
-- ----------------------------
CREATE TABLE `quests` (
  `entry` int(11) unsigned NOT NULL,
  `ZoneId` int(11) NOT NULL DEFAULT '0',
  `sort` int(11) NOT NULL DEFAULT '0',
  `flags` int(11) unsigned NOT NULL DEFAULT '0',
  `MinLevel` int(11) unsigned NOT NULL DEFAULT '0',
  `questlevel` int(11) unsigned NOT NULL DEFAULT '0',
  `Type` int(11) NOT NULL DEFAULT '0',
  `RequiredRaces` int(11) NOT NULL DEFAULT '0',
  `RequiredClass` int(11) NOT NULL DEFAULT '0',
  `RequiredTradeskill` int(11) NOT NULL DEFAULT '0',
  `RequiredTradeskillValue` int(11) NOT NULL DEFAULT '0',
  `RequiredRepFaction` int(11) NOT NULL DEFAULT '0',
  `RequiredRepValue` int(11) NOT NULL DEFAULT '0',
  `suggestedplayers` int(11) NOT NULL DEFAULT '1',
  `LimitTime` int(11) NOT NULL DEFAULT '0',
  `SpecialFlags` int(11) unsigned NOT NULL DEFAULT '0',
  `PrevQuestId` int(11) unsigned NOT NULL DEFAULT '0',
  `NextQuestId` int(11) unsigned NOT NULL DEFAULT '0',
  `srcItem` int(11) unsigned NOT NULL DEFAULT '0',
  `SrcItemCount` int(11) unsigned NOT NULL DEFAULT '0',
  `Title` text NOT NULL,
  `Details` text NOT NULL,
  `Objectives` text NOT NULL,
  `CompletionText` text NOT NULL,
  `IncompleteText` text NOT NULL,
  `EndText` text NOT NULL,
  `ObjectiveText1` text NOT NULL,
  `ObjectiveText2` text NOT NULL,
  `ObjectiveText3` text NOT NULL,
  `ObjectiveText4` text NOT NULL,
  `ReqItemId1` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemId2` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemId3` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemId4` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemCount1` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemCount2` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemCount3` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemCount4` int(11) unsigned NOT NULL DEFAULT '0',
  `required_kill_player` int(11) NOT NULL DEFAULT '0',
  `ReqKillMobOrGOId1` bigint(11) NOT NULL DEFAULT '0',
  `ReqKillMobOrGOId2` bigint(11) NOT NULL DEFAULT '0',
  `ReqKillMobOrGOId3` bigint(11) NOT NULL DEFAULT '0',
  `ReqKillMobOrGOId4` bigint(11) NOT NULL DEFAULT '0',
  `ReqKillMobOrGOCount1` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqKillMobOrGOCount2` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqKillMobOrGOCount3` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqKillMobOrGOCount4` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqCastSpellId1` int(11) NOT NULL DEFAULT '0',
  `ReqCastSpellId2` int(11) NOT NULL DEFAULT '0',
  `ReqCastSpellId3` int(11) NOT NULL DEFAULT '0',
  `ReqCastSpellId4` int(11) NOT NULL DEFAULT '0',
  `RewChoiceItemId1` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId2` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId3` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId4` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId5` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId6` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount1` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount2` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount3` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount4` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount5` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount6` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemId1` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemId2` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemId3` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemId4` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemCount1` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemCount2` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemCount3` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemCount4` int(11) unsigned NOT NULL DEFAULT '0',
  `RewRepFaction1` int(11) NOT NULL DEFAULT '0',
  `RewRepFaction2` int(11) NOT NULL DEFAULT '0',
  `RewRepFaction3` int(11) NOT NULL DEFAULT '0',
  `RewRepFaction4` int(11) NOT NULL DEFAULT '0',
  `RewRepFaction5` int(11) NOT NULL DEFAULT '0',
  `RewRepValue1` int(11) NOT NULL DEFAULT '0',
  `RewRepValue2` int(11) NOT NULL DEFAULT '0',
  `RewRepValue3` int(11) NOT NULL DEFAULT '0',
  `RewRepValue4` int(11) NOT NULL DEFAULT '0',
  `RewRepValue5` int(11) NOT NULL DEFAULT '0',
  `RewRepLimit` int(11) NOT NULL DEFAULT '0',
  `RewRank` int(11) NOT NULL DEFAULT '0',
  `RewMoney` int(11) NOT NULL DEFAULT '0',
  `Rewhonor` int(11) NOT NULL DEFAULT '0',
  `RewXP` int(11) NOT NULL DEFAULT '0',
  `RewSpell` int(11) NOT NULL DEFAULT '0',
  `RewTalent` int(11) NOT NULL DEFAULT '0',
  `CastSpell` int(11) NOT NULL DEFAULT '0',
  `PointMapId` int(11) NOT NULL DEFAULT '0',
  `PointX` float NOT NULL DEFAULT '0',
  `PointY` float NOT NULL DEFAULT '0',
  `PointOpt` int(2) unsigned NOT NULL DEFAULT '0',
  `RequiredMoney` int(11) NOT NULL DEFAULT '0',
  `ExploreTrigger1` int(11) NOT NULL DEFAULT '0',
  `ExploreTrigger2` int(11) NOT NULL DEFAULT '0',
  `ExploreTrigger3` int(11) NOT NULL DEFAULT '0',
  `ExploreTrigger4` int(11) NOT NULL DEFAULT '0',
  `RequiredQuest1` int(11) NOT NULL DEFAULT '0',
  `RequiredQuest2` int(11) NOT NULL DEFAULT '0',
  `RequiredQuest3` int(11) NOT NULL DEFAULT '0',
  `RequiredQuest4` int(11) NOT NULL DEFAULT '0',
  `RequiredQuest_and_or` int(11) unsigned NOT NULL DEFAULT '0',
  `ReceiveItemId1` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemId2` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemId3` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemId4` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemCount1` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemCount2` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemCount3` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemCount4` int(11) NOT NULL DEFAULT '0',
  `IsRepeatable` int(2) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`)
 ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Quests System';

-- ----------------------------
-- Table structure for quests_localized
-- ----------------------------
CREATE TABLE `quests_localized` (
  `entry` int(30) NOT NULL,
  `language_code` varchar(5) NOT NULL,
  `Title` text NOT NULL,
  `Details` text NOT NULL,
  `Objectives` text NOT NULL,
  `CompletionText` text NOT NULL,
  `IncompleteText` text NOT NULL,
  `EndText` text NOT NULL,
  `ObjectiveText1` text NOT NULL,
  `ObjectiveText2` text NOT NULL,
  `ObjectiveText3` text NOT NULL,
  `ObjectiveText4` text NOT NULL,
  PRIMARY KEY (`entry`,`language_code`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Localization System';

-- ----------------------------
-- Table structure for recall
-- ----------------------------
CREATE TABLE `recall` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `MapId` int(10) unsigned NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8 COMMENT='Tele Command';

-- ----------------------------
-- Table structure for reputation_creature_onkill
-- ----------------------------
CREATE TABLE `reputation_creature_onkill` (
  `creature_id` int(30) NOT NULL,
  `faction_change_alliance` int(30) NOT NULL DEFAULT '0',
  `faction_change_horde` int(30) NOT NULL DEFAULT '0',
  `change_value` int(30) NOT NULL DEFAULT '0',
  `rep_limit` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`creature_id`,`faction_change_alliance`,`faction_change_horde`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Creature System';

-- ----------------------------
-- Table structure for reputation_faction_onkill
-- ----------------------------
CREATE TABLE `reputation_faction_onkill` (
  `faction_id` int(30) NOT NULL,
  `change_factionid_alliance` int(30) NOT NULL,
  `change_deltamin_alliance` int(30) NOT NULL,
  `change_deltamax_alliance` int(30) NOT NULL,
  `change_factionid_horde` int(30) NOT NULL,
  `change_deltamin_horde` int(30) NOT NULL,
  `change_deltamax_horde` int(30) NOT NULL,
  PRIMARY KEY (`faction_id`,`change_factionid_alliance`,`change_factionid_horde`),
  UNIQUE KEY `factindex` (`faction_id`,`change_factionid_alliance`,`change_factionid_horde`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Creature System';

-- ----------------------------
-- Table structure for reputation_instance_onkill
-- ----------------------------
CREATE TABLE `reputation_instance_onkill` (
  `mapid` int(30) NOT NULL,
  `mob_rep_reward` int(30) NOT NULL,
  `mob_rep_limit` int(30) NOT NULL,
  `boss_rep_reward` int(30) NOT NULL,
  `boss_rep_limit` int(30) NOT NULL,
  `faction_change_alliance` int(30) NOT NULL,
  `faction_change_horde` int(30) NOT NULL,
  PRIMARY KEY (`mapid`,`mob_rep_reward`,`boss_rep_reward`)
 ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Creature System';



-- ----------------------------
-- Table structure for skinningloot
-- ----------------------------
CREATE TABLE `skinningloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(10) unsigned NOT NULL DEFAULT '0',
  `itemid` int(10) unsigned NOT NULL DEFAULT '0',
  `percentchance` float NOT NULL DEFAULT '0',
  `heroicpercentchance` float NOT NULL DEFAULT '0',
  `mincount` int(11) unsigned NOT NULL DEFAULT '1',
  `maxcount` int(11) unsigned NOT NULL DEFAULT '1',
  `ffa_loot` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`),
  UNIQUE KEY `index` (`index`),
  UNIQUE KEY `entryid` (`entryid`,`itemid`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for spell_coef_override
-- ----------------------------
CREATE TABLE `spell_coef_override` (
  `id` double default NULL,
  `name` varchar(300) default NULL,
  `Dspell_coef_override` float default NULL,
  `OTspell_coef_override`float default NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Spell System';

-- ----------------------------
-- Table structure for spell_disable
-- ----------------------------
CREATE TABLE `spell_disable` (
  `spellid` int(30) NOT NULL,
  `replacement_spellid` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`spellid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Spell System';


-- ----------------------------
-- Table structure for spell_disable_trainers
-- ----------------------------
CREATE TABLE `spell_disable_trainers` (
  `spellid` int(30) NOT NULL,
  `replacement_spellid` int(30) NOT NULL,
  PRIMARY KEY (`spellid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Trainer System';


-- ----------------------------
-- Table structure for spell_unique_auras
-- ----------------------------
CREATE TABLE `spell_unique_auras` (
  `SpellId` int(30) NOT NULL,
  `AuraGroup` int(30) NOT NULL,
  `AuraGroup2` int(20) NOT NULL DEFAULT '0',
  `UniqueType` int(30) NOT NULL,
  PRIMARY KEY (`SpellId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Spell System';

-- ----------------------------
-- Table structure for spellfixes
-- ----------------------------
CREATE TABLE `spellfixes` (
  `spellId` int(30) NOT NULL DEFAULT '0',
  `procFlags` int(30) NOT NULL DEFAULT '0',
  `procChance` int(30) NOT NULL DEFAULT '0',
  `procCharges` int(30) NOT NULL DEFAULT '0',
  `effect0ClassMask0` bigint(30) NOT NULL DEFAULT '0',
  `effect0ClassMask1` bigint(30) NOT NULL DEFAULT '0',
  `effect0ClassMask2` bigint(30) NOT NULL DEFAULT '0',
  `effect1ClassMask0` bigint(30) NOT NULL DEFAULT '0',
  `effect1ClassMask1` bigint(30) NOT NULL DEFAULT '0',
  `effect1ClassMask2` bigint(30) NOT NULL DEFAULT '0',
  `effect2ClassMask0` bigint(30) NOT NULL DEFAULT '0',
  `effect2ClassMask1` bigint(30) NOT NULL DEFAULT '0',
  `effect2ClassMask2` bigint(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`spellId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for spelloverride
-- ----------------------------
CREATE TABLE `spelloverride` (
  `overrideId` int(30) NOT NULL DEFAULT '0',
  `spellId` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`overrideId`,`spellId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for teleport_coords
-- ----------------------------
CREATE TABLE `teleport_coords` (
  `entry` int(16) NOT NULL DEFAULT '0',
  `name` char(255) NOT NULL DEFAULT '',
  `mapId` int(16) NOT NULL DEFAULT '0',
  `position_x` float NOT NULL DEFAULT '0',
  `position_y` float NOT NULL DEFAULT '0',
  `position_z` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for totemspells
-- ----------------------------
CREATE TABLE `totemspells` (
  `spell` int(10) unsigned NOT NULL DEFAULT '0',
  `castspell1` int(10) unsigned NOT NULL DEFAULT '0',
  `castspell2` int(10) unsigned NOT NULL DEFAULT '0',
  `castspell3` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`spell`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1  COMMENT='Spell System';

-- ----------------------------
-- Table structure for trainer_defs
-- ----------------------------
CREATE TABLE `trainer_defs` (
  `entry` int(11) unsigned NOT NULL DEFAULT '0',
  `required_skill` int(11) unsigned NOT NULL DEFAULT '0',
  `required_skillvalue` int(11) unsigned NOT NULL DEFAULT '0',
  `req_class` int(11) unsigned NOT NULL DEFAULT '0',
  `trainer_type` int(11) unsigned NOT NULL DEFAULT '0',
  `trainer_ui_window_message` text,
  `can_train_gossip_textid` int(11) NOT NULL DEFAULT '0',
  `cannot_train_gossip_textid` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Trainer System';

-- ----------------------------
-- Table structure for trainer_spells
-- ----------------------------
CREATE TABLE `trainer_spells` (
  `entry` int(11) unsigned NOT NULL DEFAULT '0',
  `cast_spell` int(11) unsigned NOT NULL,
  `learn_spell` int(11) NOT NULL DEFAULT '0',
  `spellcost` int(11) unsigned NOT NULL DEFAULT '0',
  `reqspell` int(11) unsigned NOT NULL DEFAULT '0',
  `reqskill` int(11) unsigned NOT NULL DEFAULT '0',
  `reqskillvalue` int(11) unsigned NOT NULL DEFAULT '0',
  `reqlevel` int(11) unsigned NOT NULL DEFAULT '0',
  `deletespell` int(11) unsigned NOT NULL DEFAULT '0',
  `is_prof` tinyint(1) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`,`cast_spell`,`learn_spell`),
  KEY `entry` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Trainer System';

-- ----------------------------
-- Table structure for trainerspelloverride
-- ----------------------------
CREATE TABLE `trainerspelloverride` (
  `spellid` int(10) unsigned NOT NULL DEFAULT '0',
  `cost` int(10) unsigned NOT NULL DEFAULT '0',
  `requiredspell` int(10) unsigned NOT NULL DEFAULT '0',
  `deletespell` int(10) unsigned NOT NULL DEFAULT '0',
  `requiredskill` int(10) unsigned NOT NULL DEFAULT '0',
  `requiredskillvalue` int(10) unsigned NOT NULL DEFAULT '0',
  `reqlevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `requiredclass` int(10) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`spellid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Trainer System';

-- ----------------------------
-- Table structure for transport_creatures
-- ----------------------------
CREATE TABLE `transport_creatures` (
  `transport_entry` int(10) unsigned NOT NULL,
  `creature_entry` int(10) unsigned NOT NULL,
  `position_x` float NOT NULL,
  `position_y` float NOT NULL,
  `position_z` float NOT NULL,
  `orientation` float NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1  COMMENT='Creature Spawn System';

-- ----------------------------
-- Table structure for vendors
-- ----------------------------
CREATE TABLE `vendors` (
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `item` int(10) unsigned NOT NULL DEFAULT '0',
  `amount` int(11) unsigned NOT NULL DEFAULT '0',
  `max_amount` int(11) unsigned NOT NULL DEFAULT '0',
  `inctime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `extendedcost` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`,`item`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='NPC System';



-- ----------------------------
-- Table structure for weather
-- ----------------------------
CREATE TABLE `weather` (
  `zoneId` int(11) unsigned NOT NULL DEFAULT '0',
  `high_chance` int(11) unsigned NOT NULL DEFAULT '0',
  `high_type` int(11) unsigned NOT NULL DEFAULT '0',
  `med_chance` int(11) unsigned NOT NULL DEFAULT '0',
  `med_type` int(11) unsigned NOT NULL DEFAULT '0',
  `low_chance` int(11) unsigned NOT NULL DEFAULT '0',
  `low_type` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`zoneId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Weather System';

-- ----------------------------
-- Table structure for wordfilter_character_names
-- ----------------------------
CREATE TABLE `wordfilter_character_names` (
  `regex_match` varchar(500) NOT NULL,
  `regex_ignore_if_matched` varchar(500) NOT NULL DEFAULT '',
  `type` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`regex_match`,`regex_ignore_if_matched`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for wordfilter_chat
-- ----------------------------
CREATE TABLE `wordfilter_chat` (
  `regex_match` varchar(255) NOT NULL,
  `regex_ignore_if_matched` varchar(255) DEFAULT '',
  `type` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`regex_match`,`regex_ignore_if_matched`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for worldmap_info
-- ----------------------------
CREATE TABLE `worldmap_info` (
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `screenid` int(10) unsigned DEFAULT '0',
  `type` int(10) unsigned DEFAULT '0',
  `maxplayers` int(10) unsigned DEFAULT '0',
  `minlevel` int(10) unsigned DEFAULT '1',
  `repopx` float DEFAULT '0',
  `repopy` float DEFAULT '0',
  `repopz` float DEFAULT '0',
  `repopentry` int(10) unsigned DEFAULT '0',
  `area_name` varchar(100) CHARACTER SET utf8 COLLATE utf8_unicode_ci DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `cooldown` int(10) unsigned NOT NULL DEFAULT '0',
  `lvl_mod_a` int(10) unsigned NOT NULL DEFAULT '0',
  `required_quest` int(10) unsigned NOT NULL DEFAULT '0',
  `required_item` int(10) unsigned NOT NULL DEFAULT '0',
  `heroic_keyid_1` int(30) NOT NULL DEFAULT '0',
  `heroic_keyid_2` int(30) NOT NULL DEFAULT '0',
  `viewingDistance` float NOT NULL DEFAULT '80',
  `required_checkpoint` int(30) NOT NULL DEFAULT '0',
  `collision` int(10) NOT NULL DEFAULT '1',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='World System';

-- ----------------------------
-- Table structure for worldstate_template
-- ----------------------------
CREATE TABLE `worldstate_template` (
  `mapid` int(30) unsigned NOT NULL,
  `zone_mask` int(30) NOT NULL,
  `faction_mask` int(30) NOT NULL,
  `field_number` int(30) unsigned NOT NULL,
  `initial_value` int(30) NOT NULL,
  `comment` varchar(200) NOT NULL,
  PRIMARY KEY (`mapid`,`field_number`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8  COMMENT='World System';

-- ----------------------------
-- Table structure for zoneguards
-- ----------------------------
CREATE TABLE `zoneguards` (
  `zone` int(10) unsigned NOT NULL,
  `horde_entry` int(10) unsigned NOT NULL DEFAULT '0',
  `alliance_entry` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`zone`,`horde_entry`,`alliance_entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1  COMMENT='Guard System';