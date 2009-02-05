/*
MySQL Data Transfer
Target Database: HS_worlddata
Date: 18/01/2009 00:45:12
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for item_quest_association
-- ----------------------------
CREATE TABLE `item_quest_association` (
  `item` int(11) NOT NULL DEFAULT '0',
  `quest` int(11) NOT NULL DEFAULT '0',
  `item_count` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`item`,`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Quest System';

