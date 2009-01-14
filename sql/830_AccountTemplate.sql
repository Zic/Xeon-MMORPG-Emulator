/*
MySQL Data Transfer
Target Database: heartstone_accounts
Date: 14/01/2009 19:59:20
*/

-- ----------------------------
-- Table structure for accounts
-- ----------------------------
CREATE TABLE `accounts` (
  `acct` int(5) NOT NULL auto_increment,
  `login` varchar(32) NOT NULL default '',
  `password` varchar(32) NOT NULL default '',
  `Encrypted_Password` varchar(255) NOT NULL default '',
  `gm` varchar(10) NOT NULL default '0',
  `flags` int(11) NOT NULL default '8',
  `banned` tinyint(1) NOT NULL default '0',
  `lastlogin` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `lastip` varchar(15) NOT NULL default '',
  `forceLanguage` varchar(5) NOT NULL default 'enUS',
  `email` varchar(32) default NULL,
  `muted` int(30) NOT NULL default '0',
  PRIMARY KEY  (`acct`),
  UNIQUE KEY `login` (`login`)
) ENGINE=MyISAM AUTO_INCREMENT=20008828 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for ipbans
-- ----------------------------
CREATE TABLE `ipbans` (
  `ip` varchar(128) collate utf8_unicode_ci NOT NULL,
  `time` int(30) NOT NULL default '0',
  `expire` int(30) NOT NULL default '0',
  PRIMARY KEY  (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

