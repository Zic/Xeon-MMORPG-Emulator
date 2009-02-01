/*
MySQL Data Transfer
Target Database: HS_worlddata
Date: 18/01/2009 00:45:12
*/

-- ----------------------------
-- Table structure for items
-- ----------------------------
ALTER TABLE `items` CHANGE `unk203_1` `RandomSuffixId`  int(11) NOT NULL DEFAULT 0 AFTER `randomprop`;
ALTER TABLE `items` CHANGE `gayshit` `ArmorDamageModifier`  int(11) NOT NULL DEFAULT 0 AFTER `ReqDisenchantSkill`;
