/*
MySQL Data Transfer
Target Database: Hearthstone_characters
Date: 03/02/2009 01:29:58
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for account_data
-- ----------------------------
CREATE TABLE `account_data`(
`acct` int(30) NOT NULL ,
`uiconfig0` blob DEFAULT NULL ,
`uiconfig1` blob DEFAULT NULL ,
`uiconfig2` blob DEFAULT NULL ,
`uiconfig3` blob DEFAULT NULL ,
`uiconfig4` blob DEFAULT NULL ,
`uiconfig5` blob DEFAULT NULL ,
`uiconfig6` blob DEFAULT NULL ,
`uiconfig7` blob DEFAULT NULL ,
`uiconfig8` blob DEFAULT NULL ,
PRIMARY KEY (`acct`),
UNIQUE KEY `a` (`acct`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for account_forced_permissions
-- ----------------------------
CREATE TABLE `account_forced_permissions`(
`login` varchar(50) NOT NULL ,
`permissions` varchar(100) NOT NULL ,
PRIMARY KEY (`login`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for achievements
-- ----------------------------
CREATE TABLE `achievements`(
`player` int(11) NOT NULL ,
`achievementid` int(11) NOT NULL DEFAULT 0 ,
`progress` varchar(256) DEFAULT NULL ,
`completed` int(11) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`player`, `achievementid`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for arenateams
-- ----------------------------
CREATE TABLE `arenateams`(
`id` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`type` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`leader` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`name` varchar(24) NOT NULL ,
`emblemstyle` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`emblemcolour` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`borderstyle` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bordercolor` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`backgroundcolor` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`rating` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`data` varchar(24) NOT NULL ,
`ranking` int(10) UNSIGNED NOT NULL ,
`player_data1` varchar(32) NOT NULL ,
`player_data2` varchar(32) NOT NULL ,
`player_data3` varchar(32) NOT NULL ,
`player_data4` varchar(32) NOT NULL ,
`player_data5` varchar(32) NOT NULL ,
`player_data6` varchar(32) NOT NULL ,
`player_data7` varchar(32) NOT NULL ,
`player_data8` varchar(32) NOT NULL ,
`player_data9` varchar(32) NOT NULL ,
`player_data10` varchar(32) NOT NULL ,
PRIMARY KEY (`id`),
UNIQUE KEY `name` (`name`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for auctions
-- ----------------------------
CREATE TABLE `auctions`(
`auctionId` int(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
`auctionHouse` int(32) UNSIGNED NOT NULL DEFAULT 1 ,
`item` bigint(10) UNSIGNED NOT NULL ,
`owner` bigint(10) UNSIGNED NOT NULL ,
`buyout` int(32) UNSIGNED NOT NULL ,
`time` int(32) UNSIGNED NOT NULL ,
`bidder` bigint(10) UNSIGNED NOT NULL ,
`bid` int(32) NOT NULL ,
`deposit` int(32) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`auctionId`),
KEY `auctionHouse` (`auctionHouse`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for banned_names
-- ----------------------------
CREATE TABLE `banned_names`(
`name` varchar(30) NOT NULL ,
PRIMARY KEY (`name`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for characters
-- ----------------------------
CREATE TABLE `characters`(
`guid` int(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
`acct` int(10) UNSIGNED NOT NULL ,
`name` varchar(21) NOT NULL DEFAULT '' ,
`race` tinyint(3) UNSIGNED NOT NULL ,
`class` tinyint(3) UNSIGNED NOT NULL ,
`gender` tinyint(3) UNSIGNED NOT NULL ,
`custom_faction` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`level` tinyint(3) UNSIGNED NOT NULL ,
`xp` int(10) UNSIGNED NOT NULL ,
`exploration_data` longtext NOT NULL ,
`skills` longtext NOT NULL ,
`watched_faction_index` bigint(30) NOT NULL DEFAULT 0 ,
`selected_pvp_title` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`available_pvp_titles1` bigint(30) UNSIGNED NOT NULL DEFAULT 0 ,
`available_pvp_titles2` bigint(30) UNSIGNED NOT NULL ,
`gold` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`ammo_id` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`available_prof_points` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`available_talent_points` int(3) UNSIGNED NOT NULL DEFAULT 0 ,
`current_hp` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`current_power` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`pvprank` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bytes` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bytes2` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`player_flags` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`player_bytes` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`positionX` float NOT NULL DEFAULT 0 ,
`positionY` float NOT NULL DEFAULT 0 ,
`positionZ` float NOT NULL DEFAULT 0 ,
`orientation` float NOT NULL DEFAULT 0 ,
`mapId` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`zoneId` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`taximask` longtext NOT NULL ,
`banned` int(40) NOT NULL ,
`banReason` varchar(50) NOT NULL ,
`timestamp` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`online` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`bindpositionX` float NOT NULL DEFAULT 0 ,
`bindpositionY` float NOT NULL DEFAULT 0 ,
`bindpositionZ` float NOT NULL DEFAULT 0 ,
`bindmapId` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bindzoneId` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`isResting` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`restState` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`restTime` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`playedtime` longtext NOT NULL ,
`deathstate` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`TalentResetTimes` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`first_login` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`forced_rename_pending` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`arenaPoints` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`totalstableslots` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`instance_id` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`entrypointmap` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`entrypointx` float NOT NULL DEFAULT 0 ,
`entrypointy` float NOT NULL DEFAULT 0 ,
`entrypointz` float NOT NULL DEFAULT 0 ,
`entrypointo` float NOT NULL DEFAULT 0 ,
`entrypointinstance` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`taxi_path` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`taxi_lastnode` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`taxi_mountid` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`transporter` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`transporter_xdiff` float NOT NULL DEFAULT 0 ,
`transporter_ydiff` float NOT NULL DEFAULT 0 ,
`transporter_zdiff` float NOT NULL DEFAULT 0 ,
`spells` longtext NOT NULL ,
`deleted_spells` longtext NOT NULL ,
`reputation` longtext NOT NULL ,
`actions` longtext NOT NULL ,
`auras` longtext NOT NULL ,
`finished_quests` longtext NOT NULL ,
`finished_daily_quests` longtext NOT NULL ,
`honorRolloverTime` int(30) NOT NULL DEFAULT 0 ,
`killsToday` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`killsYesterday` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`killsLifeTime` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`honorToday` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`honorYesterday` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`honorPoints` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`difficulty` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`Glyphs` longtext NOT NULL ,
`need_talent_reset` int(3) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for characters_insert_queue
-- ----------------------------
CREATE TABLE `characters_insert_queue`(
`guid` int(10) UNSIGNED NOT NULL ,
`acct` int(10) UNSIGNED NOT NULL ,
`name` varchar(21) NOT NULL ,
`race` tinyint(3) UNSIGNED NOT NULL ,
`class` tinyint(3) UNSIGNED NOT NULL ,
`gender` tinyint(3) UNSIGNED NOT NULL ,
`custom_faction` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`level` tinyint(3) UNSIGNED NOT NULL ,
`xp` int(10) UNSIGNED NOT NULL ,
`exploration_data` longtext NOT NULL ,
`skills` longtext NOT NULL ,
`watched_faction_index` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`selected_pvp_title` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`available_pvp_titles` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`gold` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`ammo_id` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`available_prof_points` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`available_talent_points` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`current_hp` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`current_power` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`pvprank` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bytes` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bytes2` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`player_flags` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`player_bytes` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`positionX` float NOT NULL DEFAULT 0 ,
`positionY` float NOT NULL DEFAULT 0 ,
`positionZ` float NOT NULL DEFAULT 0 ,
`orientation` float NOT NULL DEFAULT 0 ,
`mapId` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`zoneId` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`taximask` longtext NOT NULL ,
`banned` int(40) NOT NULL ,
`banReason` varchar(50) NOT NULL ,
`timestamp` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`online` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`bindpositionX` float NOT NULL DEFAULT 0 ,
`bindpositionY` float NOT NULL DEFAULT 0 ,
`bindpositionZ` float NOT NULL DEFAULT 0 ,
`bindmapId` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bindzoneId` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`isResting` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`restState` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`restTime` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`playedtime` longtext NOT NULL ,
`deathstate` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`TalentResetTimes` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`first_login` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`forced_rename_pending` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`arenaPoints` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`totalstableslots` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`instance_id` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`entrypointmap` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`entrypointx` float NOT NULL DEFAULT 0 ,
`entrypointy` float NOT NULL DEFAULT 0 ,
`entrypointz` float NOT NULL DEFAULT 0 ,
`entrypointo` float NOT NULL DEFAULT 0 ,
`entrypointinstance` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`taxi_path` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`taxi_lastnode` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`taxi_mountid` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`transporter` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`transporter_xdiff` float NOT NULL DEFAULT 0 ,
`transporter_ydiff` float NOT NULL DEFAULT 0 ,
`transporter_zdiff` float NOT NULL DEFAULT 0 ,
`spells` longtext NOT NULL ,
`deleted_spells` longtext NOT NULL ,
`reputation` longtext NOT NULL ,
`actions` longtext NOT NULL ,
`auras` longtext NOT NULL ,
`finished_quests` longtext NOT NULL ,
`honorPointsToAdd` int(11) NOT NULL ,
`killsToday` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`killsYesterday` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`killsLifeTime` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`honorToday` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`honorYesterday` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`honorPoints` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`difficulty` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`),
UNIQUE KEY `name` (`name`),
KEY `acct` (`acct`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for charters
-- ----------------------------
CREATE TABLE `charters`(
`charterId` int(10) UNSIGNED NOT NULL ,
`chartertype` int(10) NOT NULL DEFAULT 0 ,
`leaderGuid` int(20) UNSIGNED NOT NULL DEFAULT 0 ,
`guildName` varchar(32) NOT NULL DEFAULT '' ,
`itemGuid` bigint(40) UNSIGNED NOT NULL DEFAULT 0 ,
`signer1` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`signer2` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`signer3` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`signer4` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`signer5` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`signer6` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`signer7` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`signer8` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`signer9` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`charterId`),
UNIQUE KEY `leaderGuid` (`leaderGuid`),
UNIQUE KEY `guildName` (`guildName`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='InnoDB free: 11264 kB; InnoDB free: 18432 kB';

-- ----------------------------
-- Table structure for clientaddons
-- ----------------------------
CREATE TABLE `clientaddons` (
`id` int(10) NOT NULL auto_increment,
`name` varchar(50) default NULL,
`crc` bigint(50) default NULL,
`banned` int(1) NOT NULL default '0',
`showinlist` int(1) NOT NULL default '0',
PRIMARY KEY  (`id`),
KEY `index` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for command_overrides
-- ----------------------------
CREATE TABLE `command_overrides` (
`command_name` varchar(100) NOT NULL,
`access_level` varchar(10) NOT NULL,
PRIMARY KEY  (`command_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for corpses
-- ----------------------------
CREATE TABLE `corpses`(
`guid` bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`positionX` float NOT NULL DEFAULT 0 ,
`positionY` float NOT NULL DEFAULT 0 ,
`positionZ` float NOT NULL DEFAULT 0 ,
`orientation` float NOT NULL DEFAULT 0 ,
`zoneId` int(11) NOT NULL DEFAULT 38 ,
`mapId` int(11) NOT NULL DEFAULT 0 ,
`instanceId` int(11) NOT NULL DEFAULT 0 ,
`data` longtext NOT NULL ,
PRIMARY KEY (`guid`),
KEY `b` (`mapId`),
KEY `c` (`instanceId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for gm_tickets
-- ----------------------------
CREATE TABLE `gm_tickets`(
`guid` int(6) NOT NULL DEFAULT 0 ,
`name` varchar(200) NOT NULL DEFAULT '' ,
`level` int(6) NOT NULL DEFAULT 0 ,
`type` int(2) NOT NULL DEFAULT 0 ,
`posX` float NOT NULL DEFAULT 0 ,
`posY` float NOT NULL DEFAULT 0 ,
`posZ` float NOT NULL DEFAULT 0 ,
`message` text NOT NULL ,
`timestamp` text DEFAULT NULL ,
PRIMARY KEY (`guid`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for groups
-- ----------------------------
DROP TABLE IF EXISTS `groups`;
CREATE TABLE `groups`(
`group_id` int(30) NOT NULL ,
`group_type` tinyint(2) NOT NULL ,
`subgroup_count` tinyint(2) NOT NULL ,
`loot_method` tinyint(2) NOT NULL ,
`loot_threshold` tinyint(2) NOT NULL ,
`difficulty` int(30) NOT NULL DEFAULT 0 ,
`assistant_leader` int(30) NOT NULL DEFAULT 0 ,
`main_tank` int(30) NOT NULL DEFAULT 0 ,
`main_assist` int(30) NOT NULL DEFAULT 0 ,
`group1member1` int(50) NOT NULL ,
`group1member2` int(50) NOT NULL ,
`group1member3` int(50) NOT NULL ,
`group1member4` int(50) NOT NULL ,
`group1member5` int(50) NOT NULL ,
`group2member1` int(50) NOT NULL ,
`group2member2` int(50) NOT NULL ,
`group2member3` int(50) NOT NULL ,
`group2member4` int(50) NOT NULL ,
`group2member5` int(50) NOT NULL ,
`group3member1` int(50) NOT NULL ,
`group3member2` int(50) NOT NULL ,
`group3member3` int(50) NOT NULL ,
`group3member4` int(50) NOT NULL ,
`group3member5` int(50) NOT NULL ,
`group4member1` int(50) NOT NULL ,
`group4member2` int(50) NOT NULL ,
`group4member3` int(50) NOT NULL ,
`group4member4` int(50) NOT NULL ,
`group4member5` int(50) NOT NULL ,
`group5member1` int(50) NOT NULL ,
`group5member2` int(50) NOT NULL ,
`group5member3` int(50) NOT NULL ,
`group5member4` int(50) NOT NULL ,
`group5member5` int(50) NOT NULL ,
`group6member1` int(50) NOT NULL ,
`group6member2` int(50) NOT NULL ,
`group6member3` int(50) NOT NULL ,
`group6member4` int(50) NOT NULL ,
`group6member5` int(50) NOT NULL ,
`group7member1` int(50) NOT NULL ,
`group7member2` int(50) NOT NULL ,
`group7member3` int(50) NOT NULL ,
`group7member4` int(50) NOT NULL ,
`group7member5` int(50) NOT NULL ,
`group8member1` int(50) NOT NULL ,
`group8member2` int(50) NOT NULL ,
`group8member3` int(50) NOT NULL ,
`group8member4` int(50) NOT NULL ,
`group8member5` int(50) NOT NULL ,
`timestamp` int(30) NOT NULL ,
PRIMARY KEY  (`group_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for guild_bankitems
-- ----------------------------
CREATE TABLE `guild_bankitems`(
`guildId` int(30) NOT NULL ,
`tabId` int(30) NOT NULL ,
`slotId` int(30) NOT NULL ,
`itemGuid` int(30) NOT NULL ,
PRIMARY KEY (`guildId`, `tabId`, `slotId`),
KEY `a` (`guildId`),
KEY `b` (`tabId`),
KEY `c` (`slotId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for guild_banklogs
-- ----------------------------
CREATE TABLE `guild_banklogs`(
`log_id` int(30) NOT NULL ,
`guildid` int(30) NOT NULL ,
`tabid` bigint(30) NOT NULL ,
`action` bigint(30) NOT NULL ,
`player_guid` bigint(30) NOT NULL ,
`item_entry` bigint(30) NOT NULL ,
`stack_count` bigint(30) NOT NULL ,
`timestamp` bigint(30) NOT NULL ,
PRIMARY KEY (`log_id`, `guildid`),
KEY `a` (`log_id`),
KEY `b` (`guildid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for guild_banktabs
-- ----------------------------
CREATE TABLE `guild_banktabs`(
`guildId` int(30) NOT NULL ,
`tabId` int(30) NOT NULL ,
`tabName` varchar(200) NOT NULL ,
`tabIcon` varchar(200) NOT NULL ,
PRIMARY KEY (`guildId`, `tabId`),
KEY `a` (`guildId`),
KEY `b` (`tabId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for guild_data
-- ----------------------------
CREATE TABLE `guild_data`(
`guildid` int(30) NOT NULL ,
`playerid` int(30) NOT NULL ,
`guildRank` int(30) NOT NULL ,
`publicNote` varchar(300) NOT NULL ,
`officerNote` varchar(300) NOT NULL ,
`lastWithdrawReset` int(30) NOT NULL DEFAULT 0 ,
`withdrawlsSinceLastReset` int(30) NOT NULL DEFAULT 0 ,
`lastItemWithdrawReset0` int(30) NOT NULL DEFAULT 0 ,
`itemWithdrawlsSinceLastReset0` int(30) NOT NULL DEFAULT 0 ,
`lastItemWithdrawReset1` int(30) NOT NULL DEFAULT 0 ,
`itemWithdrawlsSinceLastReset1` int(30) NOT NULL DEFAULT 0 ,
`lastItemWithdrawReset2` int(30) NOT NULL DEFAULT 0 ,
`itemWithdrawlsSinceLastReset2` int(30) NOT NULL DEFAULT 0 ,
`lastItemWithdrawReset3` int(30) NOT NULL DEFAULT 0 ,
`itemWithdrawlsSinceLastReset3` int(30) NOT NULL DEFAULT 0 ,
`lastItemWithdrawReset4` int(30) NOT NULL DEFAULT 0 ,
`itemWithdrawlsSinceLastReset4` int(30) NOT NULL DEFAULT 0 ,
`lastItemWithdrawReset5` int(30) NOT NULL DEFAULT 0 ,
`itemWithdrawlsSinceLastReset5` int(30) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`playerid`, `guildRank`),
UNIQUE KEY `guildid` (`guildid`, `playerid`),
KEY `a` (`guildid`),
KEY `b` (`playerid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for guild_logs
-- ----------------------------
CREATE TABLE `guild_logs`(
`log_id` int(30) NOT NULL ,
`guildid` int(30) NOT NULL ,
`timestamp` int(30) NOT NULL ,
`event_type` int(30) NOT NULL ,
`misc1` int(30) NOT NULL ,
`misc2` int(30) NOT NULL ,
`misc3` int(30) NOT NULL ,
PRIMARY KEY  (`log_id`,`guildid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for guild_ranks
-- ----------------------------
CREATE TABLE `guild_ranks`(
`guildId` int(6) UNSIGNED NOT NULL ,
`rankId` int(1) NOT NULL DEFAULT 0 ,
`rankName` varchar(255) NOT NULL DEFAULT '' ,
`rankRights` int(3) UNSIGNED NOT NULL DEFAULT 0 ,
`goldLimitPerDay` int(30) NOT NULL DEFAULT 0 ,
`bankTabFlags0` int(30) NOT NULL DEFAULT 0 ,
`itemStacksPerDay0` int(30) NOT NULL DEFAULT 0 ,
`bankTabFlags1` int(30) NOT NULL DEFAULT 0 ,
`itemStacksPerDay1` int(30) NOT NULL DEFAULT 0 ,
`bankTabFlags2` int(30) NOT NULL DEFAULT 0 ,
`itemStacksPerDay2` int(30) NOT NULL DEFAULT 0 ,
`bankTabFlags3` int(30) NOT NULL DEFAULT 0 ,
`itemStacksPerDay3` int(30) NOT NULL DEFAULT 0 ,
`bankTabFlags4` int(30) NOT NULL DEFAULT 0 ,
`itemStacksPerDay4` int(30) NOT NULL DEFAULT 0 ,
`bankTabFlags5` int(30) NOT NULL DEFAULT 0 ,
`itemStacksPerDay5` int(30) NOT NULL DEFAULT 0 ,
PRIMARY KEY  (`guildId`,`rankId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for guilds
-- ----------------------------
CREATE TABLE `guilds`(
`guildId` bigint(20) NOT NULL AUTO_INCREMENT ,
`guildName` varchar(32) NOT NULL DEFAULT '' ,
`leaderGuid` bigint(20) NOT NULL DEFAULT 0 ,
`emblemStyle` int(10) NOT NULL DEFAULT 0 ,
`emblemColor` int(10) NOT NULL DEFAULT 0 ,
`borderStyle` int(10) NOT NULL DEFAULT 0 ,
`borderColor` int(10) NOT NULL DEFAULT 0 ,
`backgroundColor` int(10) NOT NULL DEFAULT 0 ,
`guildInfo` varchar(1024) NOT NULL ,
`motd` varchar(1024) NOT NULL ,
`createdate` int(30) NOT NULL DEFAULT 0 ,
`bankTabCount` int(30) NOT NULL DEFAULT 0 ,
`bankBalance` int(30) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guildId`),
UNIQUE KEY `guildId` (`guildId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for instances
-- ----------------------------
CREATE TABLE `instances`(
`id` int(30) NOT NULL ,
`mapid` int(30) NOT NULL ,
`creation` int(30) NOT NULL ,
`expiration` int(30) NOT NULL ,
`killed_npc_guids` text NOT NULL ,
`difficulty` int(30) NOT NULL ,
`creator_group` int(30) NOT NULL ,
`creator_guid` int(30) NOT NULL ,
PRIMARY KEY  (`id`),
KEY `a` (`mapid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for mailbox
-- ----------------------------
CREATE TABLE `mailbox`(
`message_id` int(30) NOT NULL DEFAULT 0 ,
`message_type` int(30) NOT NULL DEFAULT 0 ,
`player_guid` int(30) NOT NULL DEFAULT 0 ,
`sender_guid` int(30) NOT NULL DEFAULT 0 ,
`subject` varchar(255) NOT NULL DEFAULT '' ,
`body` varchar(4096) NOT NULL ,
`money` int(30) NOT NULL DEFAULT 0 ,
`attached_item_guids` varchar(200) NOT NULL DEFAULT '' ,
`cod` int(30) NOT NULL DEFAULT 0 ,
`stationary` int(30) NOT NULL DEFAULT 0 ,
`expiry_time` int(30) NOT NULL DEFAULT 0 ,
`delivery_time` int(30) NOT NULL DEFAULT 0 ,
`copy_made` int(30) NOT NULL DEFAULT 0 ,
`read_flag` int(30) NOT NULL DEFAULT 0 ,
`deleted_flag` int(30) NOT NULL default '0',
PRIMARY KEY  (`message_id`),
KEY `b` (`player_guid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for mailbox_insert_queue
-- ----------------------------
DROP TABLE IF EXISTS `mailbox_insert_queue`;
CREATE TABLE `mailbox_insert_queue`(
`sender_guid` int(30) NOT NULL ,
`receiver_guid` int(30) NOT NULL ,
`subject` varchar(200) NOT NULL ,
`body` varchar(500) NOT NULL ,
`stationary` int(30) NOT NULL ,
`money` int(30) NOT NULL ,
`item_id` int(30) NOT NULL ,
`item_stack` int(30) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for news_timers
-- ----------------------------
DROP TABLE IF EXISTS `news_timers`;
CREATE TABLE `news_timers`(
`id` int(10) UNSIGNED NOT NULL ,
`time` int(10) UNSIGNED NOT NULL ,
PRIMARY KEY (`id`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for playercooldowns
-- ----------------------------
CREATE TABLE `playercooldowns`(
`player_guid` int(30) NOT NULL ,
`cooldown_type` int(30) NOT NULL ,
`cooldown_misc` int(30) NOT NULL ,
`cooldown_expire_time` int(30) NOT NULL ,
`cooldown_spellid` int(30) NOT NULL ,
`cooldown_itemid` int(30) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for playeritems
-- ----------------------------
CREATE TABLE `playeritems`(
`ownerguid` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`guid` bigint(10) NOT NULL AUTO_INCREMENT ,
`entry` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`wrapped_item_id` int(30) NOT NULL DEFAULT 0 ,
`wrapped_creator` int(30) NOT NULL DEFAULT 0 ,
`creator` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`count` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`charges` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`flags` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`randomprop` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`randomsuffix` int(30) DEFAULT 0 ,
`itemtext` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`durability` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`containerslot` int(11) DEFAULT '-1' ,
`slot` int(10) NOT NULL DEFAULT 0 ,
`enchantments` longtext NOT NULL ,
PRIMARY KEY (`guid`),
KEY `ownerguid` (`ownerguid`),
KEY `itemtext` (`itemtext`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for playeritems_insert_queue
-- ----------------------------
CREATE TABLE `playeritems_insert_queue`(
`ownerguid` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`guid` int(10) NOT NULL AUTO_INCREMENT ,
`entry` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`wrapped_item_id` int(30) NOT NULL DEFAULT 0 ,
`wrapped_creator` int(30) NOT NULL DEFAULT 0 ,
`creator` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`count` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`charges` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`flags` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`randomprop` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`randomsuffix` int(30) NOT NULL ,
`itemtext` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`durability` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`containerslot` int(11) NOT NULL DEFAULT '-1' ,
`slot` tinyint(4) NOT NULL DEFAULT 0 ,
`enchantments` longtext NOT NULL ,
PRIMARY KEY (`guid`),
KEY `ownerguid` (`ownerguid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- ----------------------------
-- Table structure for playerpets
-- ----------------------------
CREATE TABLE `playerpets`(
`ownerguid` bigint(20) NOT NULL DEFAULT 0 ,
`petnumber` int(11) NOT NULL DEFAULT 0 ,
`name` varchar(21) NOT NULL DEFAULT '' ,
`entry` bigint(20) NOT NULL DEFAULT 0 ,
`fields` longtext NOT NULL ,
`xp` int(11) NOT NULL DEFAULT 0 ,
`active` tinyint(1) NOT NULL DEFAULT 1 ,
`level` int(11) NOT NULL DEFAULT 0 ,
`happiness` int(11) NOT NULL DEFAULT 0 ,
`actionbar` varchar(200) NOT NULL DEFAULT '' ,
`happinessupdate` int(11) NOT NULL DEFAULT 0 ,
`summon` int(11) NOT NULL DEFAULT 0 ,
`loyaltypts` int(11) NOT NULL DEFAULT 0 ,
`loyaltyupdate` int(11) NOT NULL DEFAULT 0 ,
PRIMARY KEY  (`ownerguid`,`petnumber`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for playerpetspells
-- ----------------------------
CREATE TABLE `playerpetspells`(
`ownerguid` bigint(100) NOT NULL DEFAULT 0 ,
`petnumber` int(100) NOT NULL DEFAULT 0 ,
`spellid` int(100) NOT NULL DEFAULT 0 ,
`flags` int(4) NOT NULL default '0',
KEY `a` (`ownerguid`),
KEY `b` (`petnumber`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for playerskills
-- ----------------------------
CREATE TABLE `playerskills`(
`player_guid` int(11) NOT NULL DEFAULT 0 ,
`skill_id` int(11) NOT NULL DEFAULT 0 ,
`type` int(11) NOT NULL ,
`currentlvl` int(11) NOT NULL DEFAULT 1 ,
`maxlvl` int(11) NOT NULL DEFAULT 1 ,
PRIMARY KEY (`player_guid`, `skill_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for playerskills_insert_queue
-- ----------------------------
CREATE TABLE `playerskills_insert_queue`(
`player_guid` int(11) NOT NULL DEFAULT 0 ,
`skill_id` int(11) NOT NULL DEFAULT 0 ,
`type` int(11) NOT NULL ,
`currentlvl` int(11) NOT NULL DEFAULT 1 ,
`maxlvl` int(11) NOT NULL DEFAULT 1 ,
PRIMARY KEY (`player_guid`, `skill_id`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for playersummonspells
-- ----------------------------
CREATE TABLE `playersummonspells`(
`ownerguid` bigint(20) NOT NULL DEFAULT 0 ,
`entryid` bigint(4) NOT NULL DEFAULT 0 ,
`spellid` int(4) NOT NULL default '0',
KEY `a` (`ownerguid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for prestartqueries
-- ----------------------------
CREATE TABLE `prestartqueries`(
`Query` varchar(8192) NOT NULL ,
`SingleShot` int(1) UNSIGNED NOT NULL DEFAULT 1 ,
`Seq` int(11) NOT NULL AUTO_INCREMENT ,
PRIMARY KEY (`Seq`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for questlog
-- ----------------------------
CREATE TABLE `questlog`(
`player_guid` int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`quest_id` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`slot` int(20) UNSIGNED NOT NULL DEFAULT 0 ,
`time_left` int(10) NOT NULL DEFAULT 0 ,
`explored_area1` int(20) UNSIGNED NOT NULL DEFAULT 0 ,
`explored_area2` int(20) NOT NULL DEFAULT 0 ,
`explored_area3` int(20) UNSIGNED NOT NULL DEFAULT 0 ,
`explored_area4` int(20) UNSIGNED NOT NULL DEFAULT 0 ,
`mob_kill1` int(20) NOT NULL DEFAULT 0 ,
`mob_kill2` int(20) NOT NULL DEFAULT 0 ,
`mob_kill3` int(20) NOT NULL DEFAULT 0 ,
`mob_kill4` int(20) NOT NULL DEFAULT 0 ,
`slain` int(20) NOT NULL DEFAULT 0 ,
PRIMARY KEY  (`player_guid`,`quest_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for questlog_insert_queue
-- ----------------------------
CREATE TABLE `questlog_insert_queue`(
`player_guid` int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`quest_id` int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`slot` int(20) UNSIGNED NOT NULL DEFAULT 0 ,
`time_left` int(10) NOT NULL DEFAULT 0 ,
`explored_area1` int(20) UNSIGNED NOT NULL DEFAULT 0 ,
`explored_area2` int(20) NOT NULL DEFAULT 0 ,
`explored_area3` int(20) UNSIGNED NOT NULL DEFAULT 0 ,
`explored_area4` int(20) UNSIGNED NOT NULL DEFAULT 0 ,
`mob_kill1` int(20) NOT NULL DEFAULT 0 ,
`mob_kill2` int(20) NOT NULL DEFAULT 0 ,
`mob_kill3` int(20) NOT NULL DEFAULT 0 ,
`mob_kill4` int(20) UNSIGNED ZEROFILL NOT NULL DEFAULT 00000000000000000000 ,
`slain` int(20) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`player_guid`, `quest_id`)) TYPE=MyISAM;

-- ----------------------------
-- Table structure for server_settings
-- ----------------------------
CREATE TABLE `server_settings`(
`setting_id` varchar(200) NOT NULL ,
`setting_value` bigint(50) NOT NULL ,
PRIMARY KEY  (`setting_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for social_friends
-- ----------------------------
CREATE TABLE `social_friends`(
`character_guid` int(30) NOT NULL ,
`friend_guid` int(30) NOT NULL ,
`note` varchar(100) NOT NULL ,
PRIMARY KEY (`character_guid`, `friend_guid`),
KEY `a` (`character_guid`),
KEY `b` (`friend_guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for social_ignores
-- ----------------------------
CREATE TABLE `social_ignores`(
`character_guid` int(30) NOT NULL ,
`ignore_guid` int(30) NOT NULL ,
PRIMARY KEY (`character_guid`, `ignore_guid`),
KEY `a` (`character_guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tutorials
-- ----------------------------
DROP TABLE IF EXISTS `tutorials`;
CREATE TABLE `tutorials`(
`playerId` bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`tut0` bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`tut1` bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`tut2` bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`tut3` bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`tut4` bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`tut5` bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`tut6` bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`tut7` bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY  (`playerId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for worldstate_save_data
-- ----------------------------
DROP TABLE IF EXISTS `worldstate_save_data`;
CREATE TABLE `worldstate_save_data`(
`setting_id` varchar(50) NOT NULL ,
`setting_value` varchar(200) NOT NULL ,
PRIMARY KEY  (`setting_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records 
-- ----------------------------
