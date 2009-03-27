/*
MySQL Data Transfer
Target Database: HS_characters
Date: 17/01/2009 13:16:47
*/

-- Just in case there are some realy old chars (ascent/antrix)which used , instead of ;
UPDATE characters SET characters.skills = REPLACE(characters.skills,',',';');

-- ----------------------------
-- Table structure for playerskills
-- ----------------------------
CREATE TABLE `playerskills` (
  `player_guid` int(11) NOT NULL DEFAULT '0',
  `skill_id` int(11) NOT NULL DEFAULT '0',
  `type` int(11) NOT NULL,
  `currentlvl` int(11) NOT NULL DEFAULT '1',
  `maxlvl` int(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`player_guid`,`skill_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

