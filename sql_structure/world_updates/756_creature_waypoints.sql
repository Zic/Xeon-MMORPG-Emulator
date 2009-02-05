ALTER TABLE `creature_waypoints` ADD COLUMN `orientation` float NOT NULL default '0' AFTER `position_z`;
ALTER TABLE `creature_waypoints` ADD COLUMN `backwardSayText` int(10) unsigned NOT NULL default '0' AFTER `backwardskinid`;
ALTER TABLE `creature_waypoints` ADD COLUMN `forwardSayText` int(10) unsigned NOT NULL default '0' AFTER `backwardskinid`;
ALTER TABLE `creature_waypoints` ADD COLUMN `backwardSpellToCast` int(10) unsigned NOT NULL default '0' AFTER `backwardskinid`;
ALTER TABLE `creature_waypoints` ADD COLUMN `forwardSpellToCast` int(10) unsigned NOT NULL default '0' AFTER `backwardskinid`;
ALTER TABLE `creature_waypoints` ADD COLUMN `backwardStandState` int(10) unsigned NOT NULL default '0' AFTER `backwardskinid`;
ALTER TABLE `creature_waypoints` ADD COLUMN `forwardStandState` int(10) unsigned NOT NULL default '0' AFTER `backwardskinid`;
