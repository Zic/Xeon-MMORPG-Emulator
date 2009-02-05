/* Create table in target */
CREATE TABLE `achievements` (
  `idx` int(11) NOT NULL auto_increment,
  `player` int(11) NOT NULL,
  `achievementid` int(11) NOT NULL,
  `progress` varchar(255) NOT NULL,
  `completed` int(11) NOT NULL,
  PRIMARY KEY  (`idx`),
  UNIQUE KEY `c` (`player`,`achievementid`),
  KEY `a` (`player`),
  KEY `b` (`achievementid`)
) ENGINE=MyISAM AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;


/* Alter table in target */
ALTER TABLE `characters` 
	CHANGE `name` `name` varchar(21)  COLLATE latin1_swedish_ci NOT NULL after `acct`, 
	CHANGE `race` `race` smallint(3) unsigned   NOT NULL after `name`, 
	CHANGE `class` `class` smallint(3) unsigned   NOT NULL after `race`, 
	CHANGE `gender` `gender` tinyint(1) unsigned   NOT NULL after `class`, 
	CHANGE `level` `level` int(3) unsigned   NOT NULL after `custom_faction`, 
	CHANGE `xp` `xp` int(30) unsigned   NOT NULL after `level`, 
	CHANGE `watched_faction_index` `watched_faction_index` bigint(40) unsigned   NOT NULL after `skills`, 
	CHANGE `selected_pvp_title` `selected_pvp_title` int(30) unsigned   NOT NULL after `watched_faction_index`, 
	CHANGE `available_pvp_titles` `available_pvp_titles` int(30) unsigned   NOT NULL DEFAULT '0' after `selected_pvp_title`, 
	CHANGE `gold` `gold` int(30) unsigned   NOT NULL after `available_pvp_titles`, 
	CHANGE `ammo_id` `ammo_id` int(30) unsigned   NOT NULL after `gold`, 
	CHANGE `available_prof_points` `available_prof_points` int(30) unsigned   NOT NULL after `ammo_id`, 
	CHANGE `available_talent_points` `available_talent_points` int(30) unsigned   NOT NULL after `available_prof_points`, 
	CHANGE `current_hp` `current_hp` int(30) unsigned   NOT NULL after `available_talent_points`, 
	CHANGE `current_power` `current_power` int(30) unsigned   NOT NULL after `current_hp`, 
	CHANGE `pvprank` `pvprank` int(30) unsigned   NOT NULL after `current_power`, 
	CHANGE `bytes` `bytes` int(30) unsigned   NOT NULL after `pvprank`, 
	CHANGE `bytes2` `bytes2` int(30) unsigned   NOT NULL after `bytes`, 
	CHANGE `player_flags` `player_flags` int(30) unsigned   NOT NULL after `bytes2`, 
	CHANGE `player_bytes` `player_bytes` int(30) unsigned   NOT NULL after `player_flags`, 
	CHANGE `banned` `banned` int(40)   NOT NULL after `taximask`, 
	CHANGE `banReason` `banReason` varchar(255)  COLLATE latin1_swedish_ci NULL after `banned`, 
	CHANGE `timestamp` `timestamp` text  COLLATE latin1_swedish_ci NULL after `banReason`, 
	CHANGE `forced_rename_pending` `forced_rename_pending` int(30)   NOT NULL after `first_login`, 
	CHANGE `killsLifeTime` `killsLifeTime` int(10)   NULL DEFAULT '0' after `killsYesterday`, COMMENT='';

/* Alter table in target */
ALTER TABLE `gm_tickets`  
	DROP COLUMN `deleted`, 
	DROP COLUMN `assignedto`;

/* Create table in target */
CREATE TABLE `news_timers`(
	`id` int(10) unsigned NOT NULL  , 
	`time` int(10) unsigned NOT NULL  , 
	PRIMARY KEY (`id`) 
) ENGINE=MyISAM DEFAULT CHARSET='latin1';


/* Alter table in target */
ALTER TABLE `playeritems_insert_queue` 
	ADD COLUMN `type` int(11)   NOT NULL after `enchantments`, COMMENT='';

/* Alter table in target */
ALTER TABLE `playerpets` 
	DROP COLUMN `reset_time`, 
	DROP COLUMN `reset_cost`, COMMENT='';

/* Create table in target */
CREATE TABLE `playersummons`(
	`ownerguid` int(11) unsigned NOT NULL  DEFAULT '0' , 
	`entry` int(11) unsigned NOT NULL  DEFAULT '0' , 
	`name` varchar(64) COLLATE utf8_general_ci NOT NULL  , 
	KEY `a`(`ownerguid`) 
) ENGINE=MyISAM DEFAULT CHARSET='utf8';


/* Alter table in target */
ALTER TABLE `server_settings` 
	CHANGE `setting_value` `setting_value` int(10) unsigned   NOT NULL after `setting_id`, COMMENT='';

/* Create table in target */
CREATE TABLE `worldstate_save_data`(
	`setting_id` varchar(50) COLLATE utf8_general_ci NOT NULL  , 
	`setting_value` varchar(200) COLLATE utf8_general_ci NOT NULL  , 
	PRIMARY KEY (`setting_id`) 
) ENGINE=MyISAM DEFAULT CHARSET='utf8';