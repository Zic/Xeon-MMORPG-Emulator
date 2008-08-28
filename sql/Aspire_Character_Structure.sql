SET NAMES utf8;

SET SQL_MODE='';
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO';

/*Table structure for table `account_data` */

CREATE TABLE `account_data` (
  `acct` int(30) NOT NULL,
  `uiconfig0` blob,
  `uiconfig1` blob,
  `uiconfig2` blob,
  `uiconfig3` blob,
  `uiconfig4` blob,
  `uiconfig5` blob,
  `uiconfig6` blob,
  `uiconfig7` blob,
  `uiconfig8` blob,
  PRIMARY KEY (`acct`),
  UNIQUE KEY `a` (`acct`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Table structure for table `account_forced_permissions` */

CREATE TABLE `account_forced_permissions` (
  `login` varchar(50) NOT NULL,
  `permissions` varchar(100) NOT NULL,
  PRIMARY KEY (`login`),
  UNIQUE KEY `a` (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Table structure for table `arenateams` */

CREATE TABLE `arenateams` (
  `id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Unique ID',
  `type` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Type: 0-2v2 1-3v3 2-5v5',
  `leader` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Leading character guid',
  `name` varchar(24) COLLATE utf8_unicode_ci NOT NULL DEFAULT '' COMMENT 'Team name',
  `emblemstyle` int(10) unsigned NOT NULL DEFAULT '0',
  `emblemcolour` int(10) unsigned NOT NULL DEFAULT '0',
  `borderstyle` int(10) unsigned NOT NULL DEFAULT '0',
  `bordercolor` int(10) unsigned NOT NULL DEFAULT '0',
  `backgroundcolor` int(10) unsigned NOT NULL DEFAULT '0',
  `rating` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Server Rating',
  `data` varchar(24) COLLATE utf8_unicode_ci NOT NULL COMMENT '(played_week) (won_week) (played_season) (won_season)',
  `ranking` int(10) unsigned NOT NULL COMMENT 'Server Ranking',
  `player_data1` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '(player_guid) (played_week) (won_week) (played_season) (won_season)',
  `player_data2` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '(player_guid) (played_week) (won_week) (played_season) (won_season)',
  `player_data3` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '(player_guid) (played_week) (won_week) (played_season) (won_season)',
  `player_data4` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '(player_guid) (played_week) (won_week) (played_season) (won_season)',
  `player_data5` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '(player_guid) (played_week) (won_week) (played_season) (won_season)',
  `player_data6` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '(player_guid) (played_week) (won_week) (played_season) (won_season)',
  `player_data7` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '(player_guid) (played_week) (won_week) (played_season) (won_season)',
  `player_data8` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '(player_guid) (played_week) (won_week) (played_season) (won_season)',
  `player_data9` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '(player_guid) (played_week) (won_week) (played_season) (won_season)',
  `player_data10` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '(player_guid) (played_week) (won_week) (played_season) (won_season)',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Arena Teams';

/*Table structure for table `auctions` */

CREATE TABLE `auctions` (
  `auctionId` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `auctionHouse` int(10) unsigned NOT NULL,
  `item` bigint(20) unsigned NOT NULL,
  `owner` int(10) unsigned NOT NULL,
  `buyout` int(10) unsigned NOT NULL DEFAULT '0',
  `time` int(10) unsigned NOT NULL,
  `bidder` int(10) unsigned NOT NULL,
  `bid` int(10) unsigned NOT NULL,
  `deposit` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`auctionId`),
  KEY `auctionHouse` (`auctionHouse`),
  KEY `b` (`auctionHouse`)
) ENGINE=MyISAM AUTO_INCREMENT=921 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Auctioned items';

/*Table structure for table `banned_names` */

CREATE TABLE `banned_names` (
  `name` varchar(30) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `characters` */

CREATE TABLE `characters` (
  `guid` int(10) unsigned NOT NULL,
  `acct` int(10) unsigned NOT NULL,
  `name` varchar(21) COLLATE utf8_unicode_ci NOT NULL,
  `race` tinyint(3) unsigned NOT NULL,
  `class` tinyint(3) unsigned NOT NULL,
  `gender` tinyint(3) unsigned NOT NULL,
  `custom_faction` int(10) unsigned NOT NULL DEFAULT '0',
  `level` tinyint(3) unsigned NOT NULL,
  `xp` int(10) unsigned NOT NULL,
  `exploration_data` longtext COLLATE utf8_unicode_ci NOT NULL,
  `skills` longtext COLLATE utf8_unicode_ci NOT NULL,
  `watched_faction_index` int(10) unsigned NOT NULL DEFAULT '0',
  `selected_pvp_title` int(10) unsigned NOT NULL DEFAULT '0',
  `available_pvp_titles` bigint(40) unsigned NOT NULL DEFAULT '0',
  `gold` int(10) unsigned NOT NULL DEFAULT '0',
  `ammo_id` int(10) unsigned NOT NULL DEFAULT '0',
  `available_prof_points` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `available_talent_points` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `current_hp` int(10) unsigned NOT NULL DEFAULT '0',
  `current_power` int(10) unsigned NOT NULL DEFAULT '0',
  `pvprank` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `bytes` int(10) unsigned NOT NULL DEFAULT '0',
  `bytes2` int(10) unsigned NOT NULL DEFAULT '0',
  `player_flags` int(10) unsigned NOT NULL DEFAULT '0',
  `player_bytes` int(10) unsigned NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `mapId` int(10) unsigned NOT NULL DEFAULT '0',
  `zoneId` int(10) unsigned NOT NULL DEFAULT '0',
  `taximask` longtext COLLATE utf8_unicode_ci NOT NULL,
  `banned` int(40) NOT NULL,
  `banReason` varchar(50) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `timestamp` int(10) unsigned NOT NULL DEFAULT '0',
  `online` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `bindpositionX` float NOT NULL DEFAULT '0',
  `bindpositionY` float NOT NULL DEFAULT '0',
  `bindpositionZ` float NOT NULL DEFAULT '0',
  `bindmapId` int(10) unsigned NOT NULL DEFAULT '0',
  `bindzoneId` int(10) unsigned NOT NULL DEFAULT '0',
  `isResting` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `restState` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `restTime` int(10) unsigned NOT NULL DEFAULT '0',
  `playedtime` longtext COLLATE utf8_unicode_ci NOT NULL,
  `deathstate` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `TalentResetTimes` int(10) unsigned NOT NULL DEFAULT '0',
  `first_login` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `forced_rename_pending` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `arenaPoints` int(10) unsigned NOT NULL DEFAULT '0',
  `totalstableslots` int(10) unsigned NOT NULL DEFAULT '0',
  `instance_id` int(10) unsigned NOT NULL DEFAULT '0',
  `entrypointmap` int(10) unsigned NOT NULL DEFAULT '0',
  `entrypointx` float NOT NULL DEFAULT '0',
  `entrypointy` float NOT NULL DEFAULT '0',
  `entrypointz` float NOT NULL DEFAULT '0',
  `entrypointo` float NOT NULL DEFAULT '0',
  `entrypointinstance` int(10) unsigned NOT NULL DEFAULT '0',
  `taxi_path` int(10) unsigned NOT NULL DEFAULT '0',
  `taxi_lastnode` int(10) unsigned NOT NULL DEFAULT '0',
  `taxi_mountid` int(10) unsigned NOT NULL DEFAULT '0',
  `transporter` int(10) unsigned NOT NULL DEFAULT '0',
  `transporter_xdiff` float NOT NULL DEFAULT '0',
  `transporter_ydiff` float NOT NULL DEFAULT '0',
  `transporter_zdiff` float NOT NULL DEFAULT '0',
  `spells` longtext COLLATE utf8_unicode_ci NOT NULL,
  `deleted_spells` longtext COLLATE utf8_unicode_ci NOT NULL,
  `reputation` longtext COLLATE utf8_unicode_ci NOT NULL,
  `actions` longtext COLLATE utf8_unicode_ci NOT NULL,
  `auras` longtext COLLATE utf8_unicode_ci NOT NULL,
  `finished_quests` longtext COLLATE utf8_unicode_ci NOT NULL,
  `honorRolloverTime` int(30) NOT NULL DEFAULT '0',
  `killsToday` int(10) unsigned NOT NULL DEFAULT '0',
  `killsYesterday` int(10) unsigned NOT NULL DEFAULT '0',
  `killsLifeTime` int(10) unsigned NOT NULL DEFAULT '0',
  `honorToday` int(10) unsigned NOT NULL DEFAULT '0',
  `honorYesterday` int(10) unsigned NOT NULL DEFAULT '0',
  `honorPoints` int(10) unsigned NOT NULL DEFAULT '0',
  `difficulty` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`),
  KEY `acct` (`acct`),
  KEY `e` (`online`),
  KEY `banned` (`banned`),
  KEY `br` (`banReason`),
  KEY `name` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Characters';

/*Table structure for table `characters_insert_queue` */

CREATE TABLE `characters_insert_queue` (
  `insert_temp_guid` int(10) unsigned NOT NULL DEFAULT '0',
  `acct` int(10) unsigned NOT NULL DEFAULT '0',
  `name` varchar(21) COLLATE utf8_unicode_ci NOT NULL,
  `race` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `class` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `gender` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `custom_faction` int(30) NOT NULL DEFAULT '0',
  `level` int(10) unsigned NOT NULL DEFAULT '0',
  `xp` int(10) unsigned NOT NULL DEFAULT '0',
  `exploration_data` longtext COLLATE utf8_unicode_ci NOT NULL,
  `skills` longtext COLLATE utf8_unicode_ci NOT NULL,
  `watched_faction_index` int(10) unsigned NOT NULL DEFAULT '0',
  `selected_pvp_title` int(10) unsigned NOT NULL DEFAULT '0',
  `available_pvp_titles` int(10) unsigned NOT NULL DEFAULT '0',
  `gold` int(10) unsigned NOT NULL DEFAULT '0',
  `ammo_id` int(10) unsigned NOT NULL DEFAULT '0',
  `available_prof_points` int(10) unsigned NOT NULL DEFAULT '0',
  `available_talent_points` int(10) unsigned NOT NULL DEFAULT '0',
  `current_hp` int(10) unsigned NOT NULL DEFAULT '0',
  `current_power` int(10) unsigned NOT NULL DEFAULT '0',
  `pvprank` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `bytes` int(10) unsigned NOT NULL DEFAULT '0',
  `bytes2` int(10) unsigned NOT NULL DEFAULT '0',
  `player_flags` int(10) unsigned NOT NULL DEFAULT '0',
  `player_bytes` int(10) unsigned NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `mapId` int(10) unsigned NOT NULL DEFAULT '0',
  `zoneId` int(10) unsigned NOT NULL DEFAULT '0',
  `taximask` longtext COLLATE utf8_unicode_ci NOT NULL,
  `banned` int(40) NOT NULL,
  `banReason` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `timestamp` int(11) NOT NULL,
  `online` int(11) DEFAULT NULL,
  `bindpositionX` float NOT NULL DEFAULT '0',
  `bindpositionY` float NOT NULL DEFAULT '0',
  `bindpositionZ` float NOT NULL DEFAULT '0',
  `bindmapId` int(10) unsigned NOT NULL DEFAULT '0',
  `bindzoneId` int(10) unsigned NOT NULL DEFAULT '0',
  `isResting` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `restState` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `restTime` int(10) unsigned NOT NULL DEFAULT '0',
  `playedtime` longtext COLLATE utf8_unicode_ci NOT NULL,
  `deathstate` int(10) unsigned NOT NULL DEFAULT '0',
  `TalentResetTimes` int(10) unsigned NOT NULL DEFAULT '0',
  `first_login` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `forced_rename_pending` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `publicNote` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `officerNote` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `guildid` int(10) unsigned NOT NULL DEFAULT '0',
  `guildRank` int(10) unsigned NOT NULL DEFAULT '0',
  `arenaPoints` int(10) NOT NULL,
  `totalstableslots` int(10) unsigned NOT NULL DEFAULT '0',
  `instance_id` int(10) unsigned NOT NULL DEFAULT '0',
  `entrypointmap` int(10) unsigned NOT NULL DEFAULT '0',
  `entrypointx` float NOT NULL DEFAULT '0',
  `entrypointy` float NOT NULL DEFAULT '0',
  `entrypointz` float NOT NULL DEFAULT '0',
  `entrypointo` float NOT NULL DEFAULT '0',
  `entrypointinstance` int(10) unsigned NOT NULL DEFAULT '0',
  `taxi_path` int(10) unsigned NOT NULL DEFAULT '0',
  `taxi_lastnode` int(10) unsigned NOT NULL DEFAULT '0',
  `taxi_mountid` int(10) unsigned NOT NULL DEFAULT '0',
  `transporter` int(10) unsigned NOT NULL DEFAULT '0',
  `transporter_xdiff` float NOT NULL DEFAULT '0',
  `transporter_ydiff` float NOT NULL DEFAULT '0',
  `transporter_zdiff` float NOT NULL DEFAULT '0',
  `spells` longtext COLLATE utf8_unicode_ci NOT NULL,
  `deleted_spells` longtext COLLATE utf8_unicode_ci NOT NULL,
  `reputation` longtext COLLATE utf8_unicode_ci NOT NULL,
  `actions` longtext COLLATE utf8_unicode_ci NOT NULL,
  `auras` longtext COLLATE utf8_unicode_ci NOT NULL,
  `finished_quests` longtext COLLATE utf8_unicode_ci NOT NULL,
  `honorPointsToAdd` int(10) NOT NULL,
  `killsToday` int(10) unsigned NOT NULL DEFAULT '0',
  `killsYesterday` int(10) unsigned NOT NULL DEFAULT '0',
  `killsLifeTime` int(10) unsigned NOT NULL DEFAULT '0',
  `honorToday` int(10) unsigned NOT NULL DEFAULT '0',
  `honorYesterday` int(10) unsigned NOT NULL DEFAULT '0',
  `honorPoints` int(10) unsigned NOT NULL DEFAULT '0',
  `difficulty` int(10) unsigned NOT NULL DEFAULT '0',
  UNIQUE KEY `guid` (`insert_temp_guid`),
  KEY `acct` (`acct`),
  KEY `guildid` (`guildid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `charters` */

CREATE TABLE `charters` (
  `charterId` int(10) unsigned NOT NULL,
  `charterType` int(10) unsigned NOT NULL DEFAULT '0',
  `leaderGuid` int(10) unsigned NOT NULL DEFAULT '0',
  `guildName` varchar(32) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `itemGuid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `signer1` int(10) unsigned NOT NULL DEFAULT '0',
  `signer2` int(10) unsigned NOT NULL DEFAULT '0',
  `signer3` int(10) unsigned NOT NULL DEFAULT '0',
  `signer4` int(10) unsigned NOT NULL DEFAULT '0',
  `signer5` int(10) unsigned NOT NULL DEFAULT '0',
  `signer6` int(10) unsigned NOT NULL DEFAULT '0',
  `signer7` int(10) unsigned NOT NULL DEFAULT '0',
  `signer8` int(10) unsigned NOT NULL DEFAULT '0',
  `signer9` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`charterId`),
  UNIQUE KEY `leaderGuid` (`leaderGuid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `corpses` */

CREATE TABLE `corpses` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `zoneId` int(10) unsigned NOT NULL DEFAULT '0',
  `mapId` int(10) unsigned NOT NULL DEFAULT '0',
  `instanceId` int(10) unsigned NOT NULL DEFAULT '0',
  `data` longtext COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`guid`),
  KEY `c` (`instanceId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `gm_tickets` */

CREATE TABLE `gm_tickets` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `name` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `level` int(10) unsigned NOT NULL DEFAULT '0',
  `type` int(10) unsigned NOT NULL DEFAULT '0',
  `posX` float NOT NULL DEFAULT '0',
  `posY` float NOT NULL DEFAULT '0',
  `posZ` float NOT NULL DEFAULT '0',
  `message` text COLLATE utf8_unicode_ci NOT NULL,
  `timestamp` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `groups` */

CREATE TABLE `groups` (
  `group_id` int(10) unsigned NOT NULL,
  `group_type` tinyint(3) unsigned NOT NULL,
  `subgroup_count` tinyint(3) unsigned NOT NULL,
  `loot_method` tinyint(3) unsigned NOT NULL,
  `loot_threshold` tinyint(3) unsigned NOT NULL,
  `difficulty` int(30) NOT NULL DEFAULT '0',
  `assistant_leader` int(30) NOT NULL DEFAULT '0',
  `main_tank` int(30) NOT NULL DEFAULT '0',
  `main_assist` int(30) NOT NULL DEFAULT '0',
  `group1member1` int(10) unsigned NOT NULL,
  `group1member2` int(10) unsigned NOT NULL,
  `group1member3` int(10) unsigned NOT NULL,
  `group1member4` int(10) unsigned NOT NULL,
  `group1member5` int(10) unsigned NOT NULL,
  `group2member1` int(10) unsigned NOT NULL,
  `group2member2` int(10) unsigned NOT NULL,
  `group2member3` int(10) unsigned NOT NULL,
  `group2member4` int(10) unsigned NOT NULL,
  `group2member5` int(10) unsigned NOT NULL,
  `group3member1` int(10) unsigned NOT NULL,
  `group3member2` int(10) unsigned NOT NULL,
  `group3member3` int(10) unsigned NOT NULL,
  `group3member4` int(10) unsigned NOT NULL,
  `group3member5` int(10) unsigned NOT NULL,
  `group4member1` int(10) unsigned NOT NULL,
  `group4member2` int(10) unsigned NOT NULL,
  `group4member3` int(10) unsigned NOT NULL,
  `group4member4` int(10) unsigned NOT NULL,
  `group4member5` int(10) unsigned NOT NULL,
  `group5member1` int(10) unsigned NOT NULL,
  `group5member2` int(10) unsigned NOT NULL,
  `group5member3` int(10) unsigned NOT NULL,
  `group5member4` int(10) unsigned NOT NULL,
  `group5member5` int(10) unsigned NOT NULL,
  `group6member1` int(10) unsigned NOT NULL,
  `group6member2` int(10) unsigned NOT NULL,
  `group6member3` int(10) unsigned NOT NULL,
  `group6member4` int(10) unsigned NOT NULL,
  `group6member5` int(10) unsigned NOT NULL,
  `group7member1` int(10) unsigned NOT NULL,
  `group7member2` int(10) unsigned NOT NULL,
  `group7member3` int(10) unsigned NOT NULL,
  `group7member4` int(10) unsigned NOT NULL,
  `group7member5` int(10) unsigned NOT NULL,
  `group8member1` int(10) unsigned NOT NULL,
  `group8member2` int(10) unsigned NOT NULL,
  `group8member3` int(10) unsigned NOT NULL,
  `group8member4` int(10) unsigned NOT NULL,
  `group8member5` int(10) unsigned NOT NULL,
  `timestamp` int(10) unsigned NOT NULL,
  PRIMARY KEY (`group_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `guild_bankitems` */

CREATE TABLE `guild_bankitems` (
  `guildId` int(30) NOT NULL,
  `tabId` int(30) NOT NULL,
  `slotId` int(30) NOT NULL,
  `itemGuid` int(30) NOT NULL,
  PRIMARY KEY (`guildId`,`tabId`,`slotId`),
  KEY `b` (`tabId`),
  KEY `c` (`slotId`),
  KEY `g` (`guildId`),
  KEY `i` (`itemGuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Table structure for table `guild_banklogs` */

CREATE TABLE `guild_banklogs` (
  `log_id` int(30) NOT NULL,
  `guildid` int(30) NOT NULL,
  `tabid` int(30) NOT NULL COMMENT 'tab 6 is money logs',
  `action` int(5) NOT NULL,
  `player_guid` int(30) NOT NULL,
  `item_entry` int(30) NOT NULL,
  `stack_count` int(30) NOT NULL,
  `timestamp` int(30) NOT NULL,
  PRIMARY KEY (`log_id`,`guildid`),
  KEY `b` (`tabid`),
  KEY `g` (`guildid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Table structure for table `guild_banktabs` */

CREATE TABLE `guild_banktabs` (
  `guildId` int(30) NOT NULL,
  `tabId` int(30) NOT NULL,
  `tabName` varchar(200) NOT NULL,
  `tabIcon` varchar(200) NOT NULL,
  PRIMARY KEY (`guildId`,`tabId`),
  KEY `b` (`tabId`),
  KEY `g` (`guildId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Table structure for table `guild_checkpoints` */

CREATE TABLE `guild_checkpoints` (
  `guildid` int(30) NOT NULL,
  `checkid` int(30) NOT NULL,
  PRIMARY KEY (`guildid`,`checkid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*Table structure for table `guild_data` */

CREATE TABLE `guild_data` (
  `guildid` int(30) NOT NULL,
  `playerid` int(30) NOT NULL,
  `guildRank` int(30) NOT NULL,
  `publicNote` varchar(300) NOT NULL,
  `officerNote` varchar(300) NOT NULL,
  `lastWithdrawReset` int(30) NOT NULL DEFAULT '0',
  `withdrawlsSinceLastReset` int(30) NOT NULL DEFAULT '0',
  `lastItemWithdrawReset0` int(30) NOT NULL DEFAULT '0',
  `itemWithdrawlsSinceLastReset0` int(30) NOT NULL DEFAULT '0',
  `lastItemWithdrawReset1` int(30) NOT NULL,
  `itemWithdrawlsSinceLastReset1` int(30) NOT NULL,
  `lastItemWithdrawReset2` int(30) NOT NULL,
  `itemWithdrawlsSinceLastReset2` int(30) NOT NULL,
  `lastItemWithdrawReset3` int(30) NOT NULL,
  `itemWithdrawlsSinceLastReset3` int(30) NOT NULL,
  `lastItemWithdrawReset4` int(30) NOT NULL,
  `itemWithdrawlsSinceLastReset4` int(30) NOT NULL,
  `lastItemWithdrawReset5` int(30) NOT NULL,
  `itemWithdrawlsSinceLastReset5` int(30) NOT NULL,
  KEY `b` (`playerid`),
  KEY `g` (`guildid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Table structure for table `guild_logs` */

CREATE TABLE `guild_logs` (
  `log_id` int(30) NOT NULL,
  `guildid` int(30) NOT NULL,
  `timestamp` int(30) NOT NULL,
  `event_type` int(30) NOT NULL,
  `misc1` int(30) NOT NULL,
  `misc2` int(30) NOT NULL,
  `misc3` int(30) NOT NULL,
  KEY `b` (`guildid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Table structure for table `guild_ranks` */

CREATE TABLE `guild_ranks` (
  `guildId` int(6) unsigned NOT NULL DEFAULT '0',
  `rankId` int(1) NOT NULL DEFAULT '0',
  `rankName` varchar(255) NOT NULL DEFAULT '',
  `rankRights` int(3) unsigned NOT NULL DEFAULT '0',
  `goldLimitPerDay` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags0` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay0` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags1` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay1` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags2` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay2` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags3` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay3` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags4` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay4` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags5` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay5` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`guildId`,`rankId`),
  KEY `b` (`rankId`),
  KEY `guildid` (`guildId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Table structure for table `guilds` */

CREATE TABLE `guilds` (
  `guildId` bigint(20) NOT NULL AUTO_INCREMENT,
  `guildName` varchar(32) NOT NULL DEFAULT '',
  `leaderGuid` bigint(20) NOT NULL DEFAULT '0',
  `emblemStyle` int(10) NOT NULL DEFAULT '0',
  `emblemColor` int(10) NOT NULL DEFAULT '0',
  `borderStyle` int(10) NOT NULL DEFAULT '0',
  `borderColor` int(10) NOT NULL DEFAULT '0',
  `backgroundColor` int(10) NOT NULL DEFAULT '0',
  `guildInfo` varchar(100) NOT NULL DEFAULT '',
  `motd` varchar(100) NOT NULL DEFAULT '',
  `createdate` int(30) NOT NULL DEFAULT '0',
  `bankTabCount` int(30) NOT NULL DEFAULT '0',
  `bankBalance` int(30) NOT NULL,
  PRIMARY KEY (`guildId`),
  UNIQUE KEY `guildId` (`guildId`)
) ENGINE=MyISAM AUTO_INCREMENT=5284 DEFAULT CHARSET=latin1;

/*Table structure for table `instances` */

CREATE TABLE `instances` (
  `id` int(30) NOT NULL,
  `mapid` int(30) NOT NULL,
  `creation` int(30) NOT NULL,
  `expiration` int(30) NOT NULL,
  `killed_npc_guids` text NOT NULL,
  `difficulty` int(30) NOT NULL,
  `creator_group` int(30) NOT NULL,
  `creator_guid` int(30) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `a` (`id`),
  KEY `b` (`mapid`),
  KEY `c` (`expiration`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Table structure for table `mailbox` */

CREATE TABLE `mailbox` (
  `message_id` int(10) unsigned NOT NULL DEFAULT '0',
  `message_type` int(10) unsigned NOT NULL DEFAULT '0',
  `player_guid` int(10) unsigned NOT NULL DEFAULT '0',
  `sender_guid` int(10) unsigned NOT NULL DEFAULT '0',
  `subject` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `body` longtext COLLATE utf8_unicode_ci NOT NULL,
  `money` int(10) unsigned NOT NULL DEFAULT '0',
  `attached_item_guids` varchar(200) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `cod` int(10) unsigned NOT NULL DEFAULT '0',
  `stationary` int(10) unsigned NOT NULL DEFAULT '0',
  `expiry_time` int(10) unsigned NOT NULL DEFAULT '0',
  `delivery_time` int(10) unsigned NOT NULL DEFAULT '0',
  `copy_made` int(10) unsigned NOT NULL DEFAULT '0',
  `read_flag` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `deleted_flag` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`message_id`),
  KEY `b` (`player_guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `mailbox_insert_queue` */

CREATE TABLE `mailbox_insert_queue` (
  `sender_guid` int(30) NOT NULL,
  `receiver_guid` int(30) NOT NULL,
  `subject` varchar(200) NOT NULL,
  `body` varchar(500) NOT NULL,
  `stationary` int(30) NOT NULL,
  `money` int(30) NOT NULL,
  `item_id` int(30) NOT NULL,
  `item_stack` int(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*Table structure for table `playercooldowns` */

CREATE TABLE `playercooldowns` (
  `player_guid` int(30) NOT NULL,
  `cooldown_type` int(30) NOT NULL COMMENT '0 is spell, 1 is item, 2 is spell category',
  `cooldown_misc` int(30) NOT NULL COMMENT 'spellid/itemid/category',
  `cooldown_expire_time` int(30) NOT NULL COMMENT 'expiring time in unix epoch format',
  `cooldown_spellid` int(30) NOT NULL COMMENT 'spell that cast it',
  `cooldown_itemid` int(30) NOT NULL COMMENT 'item that cast it'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Table structure for table `playeritems` */

CREATE TABLE `playeritems` (
  `ownerguid` int(10) unsigned NOT NULL DEFAULT '0',
  `guid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `wrapped_item_id` int(30) NOT NULL DEFAULT '0',
  `wrapped_creator` int(30) NOT NULL DEFAULT '0',
  `creator` int(10) unsigned NOT NULL DEFAULT '0',
  `count` int(10) unsigned NOT NULL DEFAULT '0',
  `charges` int(10) unsigned NOT NULL DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `randomprop` int(10) unsigned NOT NULL DEFAULT '0',
  `randomsuffix` int(11) NOT NULL DEFAULT '0',
  `itemtext` int(10) unsigned NOT NULL DEFAULT '0',
  `durability` int(10) unsigned NOT NULL DEFAULT '0',
  `containerslot` int(11) NOT NULL DEFAULT '-1',
  `slot` tinyint(4) NOT NULL DEFAULT '0',
  `enchantments` longtext COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`guid`),
  KEY `b` (`ownerguid`),
  KEY `c` (`itemtext`),
  KEY `cs` (`containerslot`),
  KEY `slot` (`slot`),
  KEY `entry` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `playeritems_insert_queue` */

CREATE TABLE `playeritems_insert_queue` (
  `ownerguid` int(10) unsigned NOT NULL DEFAULT '0',
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `wrapped_item_id` int(30) NOT NULL DEFAULT '0',
  `wrapped_creator` int(30) NOT NULL DEFAULT '0',
  `creator` int(10) unsigned NOT NULL DEFAULT '0',
  `count` int(10) unsigned NOT NULL DEFAULT '0',
  `charges` int(10) unsigned NOT NULL DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `randomprop` int(10) unsigned NOT NULL DEFAULT '0',
  `randomsuffix` int(30) NOT NULL,
  `itemtext` int(10) unsigned NOT NULL DEFAULT '0',
  `durability` int(10) unsigned NOT NULL DEFAULT '0',
  `containerslot` int(11) NOT NULL DEFAULT '-1' COMMENT 'couldnt find this being used in source',
  `slot` tinyint(4) NOT NULL DEFAULT '0',
  `enchantments` longtext COLLATE utf8_unicode_ci NOT NULL,
  KEY `ownerguid` (`ownerguid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `playerpets` */

CREATE TABLE `playerpets` (
  `ownerguid` bigint(20) NOT NULL DEFAULT '0',
  `petnumber` int(11) NOT NULL DEFAULT '0',
  `name` varchar(21) NOT NULL DEFAULT '',
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `fields` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `xp` int(11) NOT NULL DEFAULT '0',
  `active` tinyint(1) NOT NULL DEFAULT '0',
  `level` int(11) NOT NULL DEFAULT '0',
  `happiness` int(10) NOT NULL DEFAULT '0',
  `actionbar` varchar(200) NOT NULL DEFAULT '',
  `happinessupdate` int(11) NOT NULL DEFAULT '0',
  `summon` int(11) NOT NULL DEFAULT '0',
  `loyaltypts` int(11) NOT NULL DEFAULT '0',
  `loyaltyupdate` int(11) NOT NULL DEFAULT '0',
  KEY `b` (`petnumber`),
  KEY `a` (`ownerguid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Table structure for table `playerpetspells` */

CREATE TABLE `playerpetspells` (
  `ownerguid` int(10) unsigned NOT NULL DEFAULT '0',
  `petnumber` int(10) unsigned NOT NULL DEFAULT '0',
  `spellid` int(10) unsigned NOT NULL DEFAULT '0',
  `flags` smallint(5) unsigned NOT NULL DEFAULT '0',
  KEY `b` (`petnumber`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `playersummonspells` */

CREATE TABLE `playersummonspells` (
  `ownerguid` int(10) unsigned NOT NULL DEFAULT '0',
  `entryid` int(10) unsigned NOT NULL DEFAULT '0',
  `spellid` int(10) unsigned NOT NULL DEFAULT '0',
  KEY `b` (`entryid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `questlog` */

CREATE TABLE `questlog` (
  `player_guid` int(10) unsigned NOT NULL DEFAULT '0',
  `quest_id` int(10) unsigned NOT NULL DEFAULT '0',
  `slot` int(10) unsigned NOT NULL DEFAULT '0',
  `time_left` int(10) unsigned NOT NULL DEFAULT '0',
  `explored_area1` int(10) unsigned NOT NULL DEFAULT '0',
  `explored_area2` int(10) unsigned NOT NULL DEFAULT '0',
  `explored_area3` int(10) unsigned NOT NULL DEFAULT '0',
  `explored_area4` int(10) unsigned NOT NULL DEFAULT '0',
  `mob_kill1` int(10) unsigned NOT NULL DEFAULT '0',
  `mob_kill2` int(10) unsigned NOT NULL DEFAULT '0',
  `mob_kill3` int(10) unsigned NOT NULL DEFAULT '0',
  `mob_kill4` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`player_guid`,`quest_id`),
  KEY `d` (`slot`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `server_settings` */

CREATE TABLE `server_settings` (
  `setting_id` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `setting_value` int(11) NOT NULL,
  PRIMARY KEY (`setting_id`),
  UNIQUE KEY `a` (`setting_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*Table structure for table `social_friends` */

CREATE TABLE `social_friends` (
  `character_guid` int(30) NOT NULL,
  `friend_guid` int(30) NOT NULL,
  `note` varchar(100) NOT NULL,
  PRIMARY KEY (`character_guid`,`friend_guid`),
  KEY `a` (`character_guid`),
  KEY `b` (`friend_guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Table structure for table `social_ignores` */

CREATE TABLE `social_ignores` (
  `character_guid` int(30) NOT NULL,
  `ignore_guid` int(30) NOT NULL,
  PRIMARY KEY (`character_guid`,`ignore_guid`),
  KEY `a` (`character_guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Table structure for table `tutorials` */

CREATE TABLE `tutorials` (
  `playerId` int(10) unsigned NOT NULL DEFAULT '0',
  `tut0` int(10) unsigned NOT NULL DEFAULT '0',
  `tut1` int(10) unsigned NOT NULL DEFAULT '0',
  `tut2` int(10) unsigned NOT NULL DEFAULT '0',
  `tut3` int(10) unsigned NOT NULL DEFAULT '0',
  `tut4` int(10) unsigned NOT NULL DEFAULT '0',
  `tut5` int(10) unsigned NOT NULL DEFAULT '0',
  `tut6` int(10) unsigned NOT NULL DEFAULT '0',
  `tut7` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`playerId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

SET SQL_MODE=@OLD_SQL_MODE;