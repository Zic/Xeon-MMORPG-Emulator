/*
MySQL Data Transfer
Target Database: HS_characters
Date: 17/01/2009 13:16:47
*/

ALTER TABLE `groups` ADD COLUMN `GroupInstanceID` int(30) UNSIGNED NOT NULL DEFAULT 0 AFTER `main_assist`;
ALTER TABLE `instances` ADD COLUMN `active_members` text NOT NULL AFTER `creator_guid`;
