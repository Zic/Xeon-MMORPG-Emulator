REPLACE INTO `areatriggers` VALUES ('4162', '0', '1', '0', 'Silithus, Hive\'Zora, Alliance Camp', '-7142.04', '1397.92', '4.32689', '0', '0', '1');
REPLACE INTO `areatriggers` VALUES ('4168', '0', '1', '0', 'Silithus, Hive Regal, Horde Camp', '-7588.48', '756.806', '-16.4248', '0', '0', '1');

UPDATE `creature_proto` SET `npcflags`='129' WHERE `entry` in ('18564', '18581');

DELETE FROM gameobject_spawns WHERE `Map` = 530 AND `entry` in (182529, 182527, 182528);
DELETE FROM gameobject_spawns WHERE `Map` = 530 AND `entry` in (182523, 182522);
REPLACE INTO `gameobject_names` VALUES ('182522', '29', '6834', 'Zangarmarsh Banner', '60', '11515', '2527', '2528', '0', '0', '11813', '11812', '11805', '11804', '11808', '11809', '80', '2529', '1', '5', '300', '600', '1', '0', '0', '0', '0', '0');
REPLACE INTO `gameobject_names` VALUES ('182523', '29', '6834', 'Zangarmarsh Banner', '60', '11515', '2533', '2534', '0', '0', '11816', '11817', '11807', '11806', '11814', '11815', '80', '2535', '1', '5', '300', '600', '1', '0', '0', '0', '0', '0');
UPDATE `gameobject_names` SET `Type`='1' WHERE (`entry`='182527');
UPDATE `gameobject_names` SET `Type`='1' WHERE (`entry`='182529');
UPDATE `gameobject_names` SET `Type`='1' WHERE (`entry`='182528');

delete from gameobject_spawns where entry = 181597;

REPLACE INTO `graveyards` VALUES ('142', '248.339', '7084.93', '36.6211', '0', '3521', '0', '530', '4', 'Twin Spire Ruins');

REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2647','1','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2648','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2649','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2652','1','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2560','1','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2646','1','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2557','1','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2650','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2558','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2644','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2555','0','');

REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2651','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2559','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2645','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2556','0','');

REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2527','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2528','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2533','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2534','0','');

REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2655','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2658','0','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2656','1','');
REPLACE INTO `worldstate_template` (`mapid`,`zone_mask`,`faction_mask`,`field_number`,`initial_value`,`comment`) VALUES ('530','3521','-1','2657','1','');