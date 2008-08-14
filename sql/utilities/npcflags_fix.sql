UPDATE `creature_proto` SET `npcflags` = '1048577' WHERE `entry` IN 
(SELECT `entry` FROM `creature_names` WHERE `subname` LIKE '%Battlemaster%');

update `creature_proto` set `npcflags` = '16384' where `entry` = '6491';