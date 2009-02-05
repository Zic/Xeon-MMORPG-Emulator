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
