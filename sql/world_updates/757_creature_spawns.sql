-- unusued
ALTER TABLE `creature_spawns` DROP COLUMN `respawnNpcLink`;

-- missing
ALTER TABLE `creature_spawns` ADD COLUMN `Bytes1` int(30) NOT NULL default '0' AFTER `Bytes0`;

--moved from proto to spawns, will copy existing values first.
ALTER TABLE `creature_spawns` ADD COLUMN `MountedDisplayID` int(10) NOT NULL default '0' AFTER `standstate`;

UPDATE creature_spawns 
JOIN creature_proto ON creature_proto.entry = creature_spawns.entry
SET creature_spawns.MountedDisplayID = creature_proto.mountdisplayid

ALTER TABLE `creature_proto` DROP COLUMN  `mountdisplayid`;
