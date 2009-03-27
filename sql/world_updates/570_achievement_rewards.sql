
-- Table "achievement_rewards" DDL

CREATE TABLE `achievement_rewards` (
  `achievementid` int(10) unsigned NOT NULL,
  `title_alliance` int(10) unsigned NOT NULL,
  `title_horde` int(10) unsigned NOT NULL,
  `itemid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`achievementid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
