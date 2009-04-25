-- Fixes npc's saying "0", mistake from some 3rd party database devs should be ''
ALTER TABLE `creature_waypoints` MODIFY `forwardSayText` varchar(256) NOT NULL;
ALTER TABLE `creature_waypoints` MODIFY `backwardSayText` varchar(256) NOT NULL;
UPDATE `creature_waypoints` SET `forwardSayText`='' WHERE  `forwardSayText` = '0';
UPDATE `creature_waypoints` SET `backwardSayText`='' WHERE  `backwardSayText` = '0';