/*
   SunPlusPlus_full_Aspire.sql
   This file contains every SQL query needed by our blizzlike scripts
UPDATED BY NECCTA FOR ASPIRE
*/


/* GOSSIP SCRIPTS */
-- Skorn Whitecloud's Flag
UPDATE `creature_proto` SET `npcflags` = `npcflags`|'1' WHERE (`entry`='3052');

-- Trenton Lighthammer Gossip
DELETE FROM npc_gossip_textid WHERE (`creatureid`='7804');
INSERT INTO `npc_gossip_textid` (`creatureid`,`textid`) VALUES ('7804','1758');
UPDATE `creature_proto` SET `npcflags` = `npcflags`|'1' WHERE (`entry`='7804');

UPDATE `creature_proto` SET `npcflags` = `npcflags`|'1' WHERE entry IN (19910,15105,20118,16696,2804,20272,20269,19908,15102,14981,14982,2302,10360,3890);   -- Warsong Gulch Battlemasters Flag
UPDATE `creature_proto` SET `npcflags` = `npcflags`|'1' WHERE entry IN (20273,16694,20274,15007,19855,19905,20120,15008,857,907,12198,14990,15006,14991);   -- Arathi Basin Battlemasters Flag
UPDATE `creature_proto` SET `npcflags` = `npcflags`|'1' WHERE entry IN (347,19907,16695,20271,20119,19906,20276,7410,12197,5118,15106,15103,14942);      -- Alterac Valley Battlemasters Flag
UPDATE `creature_proto` SET `npcflags` = `npcflags`|'1' WHERE entry IN (20388,20385,20390,20383,22013,22015,20362,20381,20374,20386,20382,20384);      -- Eye of the Storm Battlemasters Flag
-- Guards Flag
UPDATE `creature_proto` SET `npcflags` = `npcflags`|'1' WHERE entry IN (1423,68,1976,4262,5624,3571,16222,16733,20674,3296,3084,3222,3224,3220,3219,3217,3215,3218,3221,3223,3212,5953,5725,1738,1746,1745,1743,1744,1742,5595,727,16221,18038,19687,18568,18549,1652,1496);


/* INSTANCE SCRIPTS */


/* Karazhan */

-- Opera Stage Right Door should be closed by default, whoever sniffed NCDB GO's in kara, did it after the instance was fully cleared.
UPDATE `gameobject_spawns` set `State`='1' WHERE `entry`='184279';
-- Berthold Flag Fix
UPDATE `creature_proto` set `npcflags`=`npcflags`|1 WHERE `entry`= 16153;


/* The Eye */

-- remove void reaver agent
DELETE FROM ai_agents WHERE entry=19516;

/* Dark Portal event */

DELETE FROM `creature_spawns` WHERE entry = 18625;
DELETE FROM `creature_proto` WHERE entry = 18625;
DELETE FROM `creature_names` WHERE entry = 18625;
INSERT INTO `creature_names` (`entry`, `name`, `subname`, `info_str`, `Flags1`, `type`, `family`, `rank`, `unk4`, `spelldataid`, `male_displayid`, `female_displayid`, `male_displayid2`, `female_displayid2`, `unknown_float1`, `unknown_float2`, `civilian`, `leader`) VALUES ('18625','Dark Portal Event Trigger',' ','','0','10','0','0','0','0',169,0,0,0,'1','1','0',0);
INSERT INTO `creature_proto` (`entry`, `minlevel`, `maxlevel`, `faction`, `minhealth`, `maxhealth`, `mana`, `scale`, `npcflags`, `attacktime`, `mindamage`, `maxdamage`, `rangedattacktime`, `rangedmindamage`, `rangedmaxdamage`, `mountdisplayid`, `equipmodel1`, `equipinfo1`, `equipslot1`, `equipmodel2`, `equipinfo2`, `equipslot2`, `equipmodel3`, `equipinfo3`, `equipslot3`, `respawntime`, `armor`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `combat_reach`, `bounding_radius`, `auras`, `boss`, `money`, `invisibility_type`, `death_state`, `walk_speed`, `run_speed`, `fly_speed`, `extra_a9_flags`) VALUES ('18625','70','70','35','1000000','1000000','0','0','1758','1000','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0',0,'0','0','2.5','8','14',0);
INSERT INTO `creature_spawns` (`entry`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `movetype`, `displayid`, `faction`, `flags`, `bytes`, `bytes2`, `emote_state`, `npc_respawn_link`, `channel_spell`, `channel_target_sqlid`, `channel_target_sqlid_creature`) VALUES (18625,530,'-263.719','1101.18','73.7167','4.64415',0,'169',35,33554432,0,0,0,0,0,0,0);


/* The Deadmines */

UPDATE `gameobject_spawns` SET `flags` = '1' WHERE `entry` IN ('13965','16400','16399');
DELETE FROM `creature_spawns` WHERE `entry` = '643';


/* Black Temple */

-- Warlord Kalithresh

INSERT INTO `creature_spawns` (`entry`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `movetype`, `displayid`, `faction`, `flags`, `bytes`, `bytes2`, `emote_state`, `npc_respawn_link`, `channel_spell`, `channel_target_sqlid`, `channel_target_sqlid_creature`, `standstate`) VALUES
(17954,545,'-107.059','-543.903','8.27027','5.89921',0,'17423',14,0,16908544,4097,0,0,0,0,0,0),
(17954,545,'-80.7551','-550.946','8.27027','3.80482',0,'17423',14,0,16908544,4097,0,0,0,0,0,0),
(17954,545,'-96.2409','-571.375','8.27027','2.3911',0,'17423',14,0,16908544,4097,0,0,0,0,0,0),
(17954,545,'-74.3098','-520.419','8.25508','4.61263',0,'17423',14,256,0,0,0,0,0,0,0,0),
(17954,545,'-116.221','-520.14','8.19892','5.12707',0,'17423',14,256,0,0,0,0,0,0,0,0),
(17954,545,'-76.881','-489.165','8.23619','2.10328',0,'17423',14,256,0,0,0,0,0,0,0,0),
(17954,545,'-113.184','-488.599','8.19631','6.13473',0,'17423',14,256,0,0,0,0,0,0,0,0);

-- Shadowy Constructs (Teron Gorefiend encounter)

-- Illidan Encounter

REPLACE INTO `creature_names` (`entry`, `name`, `subname`, `info_str`, `Flags1`, `type`, `family`, `rank`, `unk4`, `spelldataid`, `male_displayid`, `female_displayid`, `male_displayid2`, `female_displayid2`, `unknown_float1`, `unknown_float2`, `civilian`, `leader`) VALUES 
(30000, 'Trigger', ' ', '', 0, 0, 0, 0, 0, 0, 15294, 0, 0, 0, 1, 1, 0, 0),
(30001, 'Door Event Trigger', ' ', '', 0, 0, 0, 0, 0, 0, 15294, 0, 0, 0, 1, 1, 0, 0);

REPLACE INTO `creature_proto` (`entry`, `minlevel`, `maxlevel`, `faction`, `minhealth`, `maxhealth`, `mana`, `scale`, `npcflags`, `attacktime`, `mindamage`, `maxdamage`, `rangedattacktime`, `rangedmindamage`, `rangedmaxdamage`, `mountdisplayid`, `equipmodel1`, `equipinfo1`, `equipslot1`, `equipmodel2`, `equipinfo2`, `equipslot2`, `equipmodel3`, `equipinfo3`, `equipslot3`, `respawntime`, `armor`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `combat_reach`, `bounding_radius`, `auras`, `boss`, `money`, `invisibility_type`, `death_state`, `walk_speed`, `run_speed`, `fly_speed`, `extra_a9_flags`) VALUES 
(30000, 70, 70, 1825, 100000, 100000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '0', 0, 0, 0, 0, 2.5, 8, 14, 0),
(30001, 70, 70, 35, 100000, 100000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '0', 0, 0, 0, 0, 2.5, 8, 14, 0);

DELETE FROM `creature_spawns` WHERE entry IN (22990, 22996, 22997, 23336, 30001);
INSERT INTO `creature_spawns` (`entry`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `movetype`, `displayid`, `faction`, `flags`, `bytes`, `bytes2`, `emote_state`, `npc_respawn_link`, `channel_spell`, `channel_target_sqlid`, `channel_target_sqlid_creature`) VALUES 
(22990, 564, 661.563, 305.711, 271.689, 0.00628138, 4, 20681, 1858, 256, 0, 1, 0, 0, 0, 0, 0),
(30001, 564, 771.5, 304.7, 319, 3.10568, 0, 15294, 35, 0, 0, 0, 0, 0, 0, 0, 0);

REPLACE INTO `gameobject_names` (entry, Type, DisplayID, Name, spellfocus, sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8, sound9, unknown1, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8, unknown9, unknown10, unknown11, unknown12, unknown13, unknown14) VALUES 
(185905, 0, 7388, "Gate", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(200000, 0, 7421, 'BT_ILLIDAN_DOOR_RIGHT', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(200001, 0, 7422, 'BT_ILLIDAN_DOOR_LEFT', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `gameobject_spawns` WHERE entry in (185905, 200000, 200001);
INSERT INTO `gameobject_spawns` (Entry, map, position_x, position_y, position_z, Facing, orientation1, orientation2, orientation3, orientation4, State, Flags, Faction, Scale, stateNpcLink) VALUES 
(185905, 564, 774.7, 304.6, 314.85, 1.53, 0, 0, 0.706767, 0.707446, 1, 1, 0, 1, 0),
(200000, 564, 745.07, 241.802, 354.292, 0.79225, 0, 0, 0.385846, 0.922563, 0, 1, 0, 1, 0),
(200001, 564, 744.829, 369.276, 354.324, 2.35855, 0, 0, 0.92433, 0.381594, 0, 1, 0, 1, 0);

-- Essence of Desire
DELETE FROM `creature_spawns` WHERE entry = 23419;
-- Essence of Anger
DELETE FROM `creature_spawns` WHERE entry = 23420;

/* Naxxramas */

-- Kel'thuzad Encounter

REPLACE INTO `creature_names` (`entry`, `name`, `subname`, `info_str`, `Flags1`, `type`, `family`, `rank`, `unk4`, `spelldataid`, `male_displayid`, `female_displayid`, `male_displayid2`, `female_displayid2`, `unknown_float1`, `unknown_float2`, `civilian`, `leader`) VALUES  (30002, 'The Lich King', ' ', '', 0, 0, 0, 0, 0, 0, 15294, 0, 0, 0, 1, 1, 0, 0);

REPLACE INTO `creature_proto` (`entry`, `minlevel`, `maxlevel`, `faction`, `minhealth`, `maxhealth`, `mana`, `scale`, `npcflags`, `attacktime`, `mindamage`, `maxdamage`, `rangedattacktime`, `rangedmindamage`, `rangedmaxdamage`, `mountdisplayid`, `equipmodel1`, `equipinfo1`, `equipslot1`, `equipmodel2`, `equipinfo2`, `equipslot2`, `equipmodel3`, `equipinfo3`, `equipslot3`, `respawntime`, `armor`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `combat_reach`, `bounding_radius`, `auras`, `boss`, `money`, `invisibility_type`, `death_state`, `walk_speed`, `run_speed`, `fly_speed`, `extra_a9_flags`) VALUES  (30002, 70, 70, 14, 100000, 100000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '0', 0, 0, 0, 0, 2.5, 8, 14, 0);

REPLACE INTO `creature_spawns` (`entry`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `movetype`, `displayid`, `faction`, `flags`, `bytes`, `bytes2`, `emote_state`, `npc_respawn_link`, `channel_spell`, `channel_target_sqlid`, `channel_target_sqlid_creature`) VALUES (30002, 533, 3767.58, -5117.15, 174.49, 2.95544, 0, 15294, 14, 33554432, 0, 0, 0, 0, 0, 0, 0);

REPLACE INTO `gameobject_names` (`entry`, `Type`, `DisplayID`, `Name`, `spellfocus`, `sound1`, `sound2`, `sound3`, `sound4`, `sound5`, `sound6`, `sound7`, `sound8`, `sound9`, `unknown1`, `unknown2`, `unknown3`, `unknown4`, `unknown5`, `unknown6`, `unknown7`, `unknown8`, `unknown9`, `unknown10`, `unknown11`, `unknown12`, `unknown13`, `unknown14`) VALUES 
(181228, 0, 6675, 'KelThuzad Door', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(181640, 7, 6690, 'Doodad_kelthuzad_throne02', 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(200002, 0, 6770, 'KELTHUZAD_WINDOW_PORTAL', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `gameobject_spawns` WHERE Entry IN (181640, 181228, 200002);
INSERT INTO `gameobject_spawns` (`Entry`, `map`, `position_x`, `position_y`, `position_z`, `Facing`, `orientation1`, `orientation2`, `orientation3`, `orientation4`, `State`, `Flags`, `Faction`, `Scale`, `stateNpcLink`) VALUES 
(181640, 533, 3762.47, -5116.29, 143.861, 2.95281, 0, 0, 0.995549, 0.0942488, 1, 1, 0, 1, 0),
(181228, 533, 3635.44, -5090.33, 143.205, 1.38302, 0, 0, 0.637702, 0.770283, 0, 1, 0, 1, 0),
(200002, 533, 3700, -5186.52, 152.211, 1.44024, 0, 0, 0.659474, 0.751728, 1, 1, 0, 1, 0),
(200002, 533, 3761.43, -5174.22, 151.833, 2.15482, 0, 0, 0.880735, 0.47361, 1, 1, 0, 1, 0),
(200002, 533, 3731.97, -5026.51, 154.339, 4.47667, 0, 0, 0.785346, -0.619056, 1, 1, 0, 1, 0),
(200002, 533, 3784.51, -5062.25, 153.354, 3.69184, 0, 0, 0.962392, -0.271665, 1, 1, 0, 1, 0);

-- Sapphiron Encounter

DELETE FROM `gameobject_spawns` WHERE entry = 181225;
REPLACE INTO `creature_names` (`entry`, `name`, `subname`, `info_str`, `Flags1`, `type`, `family`, `rank`, `unk4`, `spelldataid`, `male_displayid`, `female_displayid`, `male_displayid2`, `female_displayid2`, `unknown_float1`, `unknown_float2`, `civilian`, `leader`) VALUES
('50011','Sapphiron',' ','0','0','0','0','0','0','0',13069,0,0,0,'1','1','0',0),
('50010','Sapphiron Frost Breath Trigger',' ','0','0','0','0','0','0','0',13069,0,0,0,'1','1','0',0),
('50012','Sapphiron',' ','0','0','0','0','0','0','0',13069,0,0,0,'1','1','0',0),
('50013','Sapphiron',' ','0','0','0','0','0','0','0',13069,0,0,0,'1','1','0',0);
REPLACE INTO `creature_proto` (`entry`, `minlevel`, `maxlevel`, `faction`, `minhealth`, `maxhealth`, `mana`, `scale`, `npcflags`, `attacktime`, `attacktype`, `mindamage`, `maxdamage`, `rangedattacktime`, `rangedmindamage`, `rangedmaxdamage`, `mountdisplayid`, `equipmodel1`, `equipinfo1`, `equipslot1`, `equipmodel2`, `equipinfo2`, `equipslot2`, `equipmodel3`, `equipinfo3`, `equipslot3`, `respawntime`, `armor`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `combat_reach`, `bounding_radius`, `auras`, `boss`, `money`, `invisibility_type`, `death_state`, `walk_speed`, `run_speed`, `fly_speed`, `extra_a9_flags`) VALUES
('50010','70','70','21','100000','100000','0','1','0','10000',0,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0',0,'0','0','1.5','1.5','1.5',0),
('50011','70','70','21','100000','100000','0','1','0','10000',0,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0',0,'0','0','0','0','0',0),
('50012','70','70','21','100000','100000','0','3','0','10000',0,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0',0,'0','0','0','0','0',0),
('50013','70','70','21','100000','100000','0','1','0','10000',0,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0',0,'0','0','0','0','0',0);
REPLACE INTO `gameobject_names` (`entry`, `Type`, `DisplayID`, `Name`, `spellfocus`, `sound1`, `sound2`, `sound3`, `sound4`, `sound5`, `sound6`, `sound7`, `sound8`, `sound9`, `unknown1`, `unknown2`, `unknown3`, `unknown4`, `unknown5`, `unknown6`, `unknown7`, `unknown8`, `unknown9`, `unknown10`, `unknown11`, `unknown12`, `unknown13`, `unknown14`) VALUES
('181225','0','6695','Frostwyrm Waterfall Door','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `gameobject_spawns` (`Entry`, `map`, `position_x`, `position_y`, `position_z`, `Facing`, `orientation1`, `orientation2`, `orientation3`, `orientation4`, `State`, `Flags`, `Faction`, `Scale`, `stateNpcLink`) VALUES
('181225','533','3536.9','-5159.75','143.666','4.51997','0','0','0.771762','-0.635911','0','1','0','1','0');


/* Magtheridon's Lair */

-- must be filled with Triggers deleted in NCDB

REPLACE INTO `creature_names` (`entry`, `name`, `subname`, `info_str`, `Flags1`, `type`, `family`, `rank`, `unk4`, `spelldataid`, `male_displayid`, `female_displayid`, `male_displayid2`, `female_displayid2`, `unknown_float1`, `unknown_float2`, `civilian`, `leader`) VALUES
('17376','Hellfire Raid Trigger',' ','','0','10','0','0','0','0',18783,13069,0,0,'1.35','1','0',0),
('17474','Target Trigger',' ','','0','10','0','0','0','0',169,15435,0,0,'1.35','1','0',0),
('133338','Magtheridon Encounter Trigger',' ','','0','10','0','0','0','0',169,0,0,0,'1','1','0',0);

REPLACE INTO `creature_proto` (`entry`, `minlevel`, `maxlevel`, `faction`, `minhealth`, `maxhealth`, `mana`, `scale`, `npcflags`, `attacktime`, `attacktype`, `mindamage`, `maxdamage`, `rangedattacktime`, `rangedmindamage`, `rangedmaxdamage`, `mountdisplayid`, `equipmodel1`, `equipinfo1`, `equipslot1`, `equipmodel2`, `equipinfo2`, `equipslot2`, `equipmodel3`, `equipinfo3`, `equipslot3`, `respawntime`, `armor`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `combat_reach`, `bounding_radius`, `auras`, `boss`, `money`, `invisibility_type`, `death_state`, `walk_speed`, `run_speed`, `fly_speed`, `extra_a9_flags`) VALUES
('17376','1','1','35','1','1','0','1','0','1500',0,'3','3.87','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','2','1','0','0',0,'0','0','2.5','8','14',0),
('17474','1','1','35','1','1','0','1','0','1400',0,'3','3.87','0','0','0','0','0','0','0','0','0','0','0','0','0','0','20','0','0','0','0','0','0','1','1','0','0',0,'0','0','2.5','8','14',0),
('133338','70','70','35','1000000','1000000','0','0','1758','1000','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0',0,'0',0,'0','2.5','8','14',0);

DELETE FROM `creature_spawns` WHERE entry IN (17376, 17474, 133338) AND map = 544;
INSERT INTO `creature_spawns` (`entry`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `movetype`, `displayid`, `faction`, `flags`, `bytes`, `bytes2`, `emote_state`, `npc_respawn_link`, `channel_spell`, `channel_target_sqlid`, `channel_target_sqlid_creature`, `standstate`) VALUES
(17376,544,'8.79722','-19.4801','2.53646','3.07178',12,'13069',114,0,16777472,4097,0,0,0,0,0,0),
(17474,544,'13.1331','2.75793','-0.312492','0.264242',12,'15435',35,0,16777472,4097,0,0,0,0,0,0),
(17376,544,'9.3589','23.2286','2.34895','3.89208',12,'13069',114,0,16777472,4097,0,0,0,0,0,0),
(17474,544,'-12.1116','1.01105','-0.303638','6.08346',12,'15435',35,0,16777472,4097,0,0,0,0,0,0),
(17474,544,'-11.3749','-29.1214','-0.312463','4.99445',12,'15435',35,0,16777472,4097,0,0,0,0,0,0),
(17474,544,'-7.10759','25.524','-0.312497','5.1917',12,'15435',35,0,16777472,4097,0,0,0,0,0,0),
(17474,544,'-3.11093','29.1424','-0.31249','5.67216',12,'15435',35,0,16777472,4097,0,0,0,0,0,0),
(17376,544,'-31.471','-34.156','2.3351','1.06465',12,'13069',114,0,16777472,4097,0,0,0,0,0,0),
(17376,544,'-54.2772','2.34374','2.40456','1.3439',12,'13069',114,0,16777472,4097,0,0,0,0,0,0),
(17474,544,'-37.1834','-19.4914','-0.312451','5.05616',12,'15435',35,0,16777472,4097,0,0,0,0,0,0),
(17376,544,'-31.8918','38.4303','2.28647','5.07891',12,'13069',114,0,16777472,4097,0,0,0,0,0,0),
(17474,544,'-29.691','29.643','-0.034676','0.478655',12,'15435',35,0,16777472,4097,0,0,0,0,0,0),
(133338,544,'-16.6199','2.19251','-0.405228','2.98687',0,'169',35,33554432,0,0,0,0,0,0,0,0);

REPLACE INTO `gameobject_names` (`entry`, `Type`, `DisplayID`, `Name`, `spellfocus`, `sound1`, `sound2`, `sound3`, `sound4`, `sound5`, `sound6`, `sound7`, `sound8`, `sound9`, `unknown1`, `unknown2`, `unknown3`, `unknown4`, `unknown5`, `unknown6`, `unknown7`, `unknown8`, `unknown9`, `unknown10`, `unknown11`, `unknown12`, `unknown13`, `unknown14`) VALUES
('181713','10','6896','Manticron Cube','0','0','0','65536','0','0','0','0','0','0','30420','0','0','1','0','0','0','0','0','0','0','0','0','0'),
('183847','0','7093','Doodad_HF_Mag_door01','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
('184634','0','7206','Magtheridon Column 003','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
('184635','0','7206','Magtheridon Column 002','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
('184636','0','7206','Magtheridon Column 004','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
('184637','0','7206','Magtheridon Column 005','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
('184638','0','7206','Magtheridon Column 000','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
('184639','0','7206','Magtheridon Column 001','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
('184653','0','7208','Doodad_Hellfire_Raid_FX01','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');

DELETE FROM `gameobject_spawns` WHERE entry IN (181713, 183847, 184634, 184635, 184636, 184637, 184638, 184639, 184653) AND map = 544;
INSERT INTO `gameobject_spawns` (`Entry`, `map`, `position_x`, `position_y`, `position_z`, `Facing`, `orientation1`, `orientation2`, `orientation3`, `orientation4`, `State`, `Flags`, `Faction`, `Scale`, `stateNpcLink`) VALUES
('184635','544','19.0966','-29.2772','0.133036','-1.26399','0','0','-0.590754','0.806852','1','32','1375','1','0'),
('184638','544','-60.8202','-21.9269','-0.03026','3.08278','0','0','0.999568','0.029401','1','32','1375','1','0'),
('184639','544','-29.7699','-43.4445','-0.522461','-2.37604','0','0','0.927631','-0.373497','1','32','1375','1','0'),
('181713','544','8.89169','-19.392','0.630908','2.44346','0','0','0.939693','0.34202','1','0','0','1.5','0'),
('181713','544','-31.4977','-34.0832','0.630935','1.22173','0','0','0.573576','0.819152','1','0','0','1.5','0'),
('184634','544','17.7522','34.5464','0.144816','0.179666','0','0','0.089712','0.995968','1','32','1375','1','0'),
('184653','544','0','0','0','3.14159','0','0','1','-4.37114E-8','1','32','1375','1','0'),
('183847','544','-72.5866','1.559','0','3.14159','0','0','1','-4.37114E-8','0','32','1375','1','0'),
('184636','544','-30.8852','46.6723','-0.497104','1.23468','0','0','0.578867','0.815422','1','32','1375','1','0'),
('184637','544','-60.2491','27.9361','-0.018443','1.94711','0','0','0.826891','0.562362','1','32','1375','1','0'),
('181713','544','9.39513','23.2389','0.630891','-2.49582','0','0','0.948324','-0.317305','1','0','0','1.5','0'),
('181713','544','-54.2302','2.32818','0.630945','0.0174533','0','0','0.00872654','0.999962','1','0','0','1.5','0'),
('181713','544','-31.7948','38.3964','0.630919','-1.20428','0','0','0.566406','-0.824126','1','0','0','1.5','0');

UPDATE `gameobject_spawns` SET Flags = 0 WHERE Entry = 181713 AND map = 544;


/* The Mechanar */

REPLACE INTO `creature_names` (`entry`, `name`, `subname`, `info_str`, `Flags1`, `type`, `family`, `rank`, `unk4`, `spelldataid`, `male_displayid`, `female_displayid`, `male_displayid2`, `female_displayid2`, `unknown_float1`, `unknown_float2`, `civilian`, `leader`) VALUES
('50000','Nether Bomb',' ','','0','0','0','0','0','0',13069,0,0,0,'1','1','0',0);
REPLACE INTO `creature_proto` (`entry`, `minlevel`, `maxlevel`, `faction`, `minhealth`, `maxhealth`, `mana`, `scale`, `npcflags`, `attacktime`, `attacktype`, `mindamage`, `maxdamage`, `rangedattacktime`, `rangedmindamage`, `rangedmaxdamage`, `mountdisplayid`, `equipmodel1`, `equipinfo1`, `equipslot1`, `equipmodel2`, `equipinfo2`, `equipslot2`, `equipmodel3`, `equipinfo3`, `equipslot3`, `respawntime`, `armor`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `combat_reach`, `bounding_radius`, `auras`, `boss`, `money`, `invisibility_type`, `death_state`, `walk_speed`, `run_speed`, `fly_speed`, `extra_a9_flags`) VALUES
('50000','70','70','168','100000','100000','100000','1','0','20000',0,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0',0,'0','0','2.5','8','14',0);


/* Shadowfang Keep */

UPDATE `gameobject_spawns` SET `flags` = '1' WHERE `entry` = '18972';
UPDATE `gameobject_spawns` SET `flags` = '1' WHERE `entry` = '18971';


/* Ragefire Chasm */

DELETE FROM `creature_spawns` WHERE `entry`= 10268;
DELETE FROM `creature_spawns` WHERE `entry`= 10268;
DELETE FROM `creature_spawns` WHERE `entry`= 8996 AND `map`= 389;
REPLACE INTO `creature_names` (`entry`, `name`, `subname`, `info_str`, `Flags1`, `type`, `family`, `rank`, `unk4`, `spelldataid`, `male_displayid`, `female_displayid`, `male_displayid2`, `female_displayid2`, `unknown_float1`, `unknown_float2`, `civilian`, `leader`) VALUES 
(500000, 'Voidwalker', 'Searing Blade Warlock Minion', ' ', 0, 3, 16, 0, 0, 0, 1132, 0, 0, 0, 1.4, 0.77, 0, 0);
REPLACE INTO `creature_proto` (`entry`, `minlevel`, `maxlevel`, `faction`, `minhealth`, `maxhealth`, `mana`, `scale`, `npcflags`, `attacktime`, `attacktype`, `mindamage`, `maxdamage`, `rangedattacktime`, `rangedmindamage`, `rangedmaxdamage`, `mountdisplayid`, `equipmodel1`, `equipinfo1`, `equipslot1`, `equipmodel2`, `equipinfo2`, `equipslot2`, `equipmodel3`, `equipinfo3`, `equipslot3`, `respawntime`, `armor`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `combat_reach`, `bounding_radius`, `auras`, `boss`, `money`, `invisibility_type`, `death_state`, `walk_speed`, `run_speed`, `fly_speed`, `extra_a9_flags`) VALUES 
(500000, 17, 17, 554, 460, 460, 4439, 1, 0, 1870, 0, 14, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0.8, 0, 0, 0, 0, 0, 2.5, 8, 14, 0);


/* Blackrock Spire */

-- Gizrul
DELETE FROM `creature_spawns` WHERE `entry`=('10268');
-- Warchied Rend Blackhand
DELETE FROM `creature_spawns` WHERE `entry`=('10268');


/* Serpentshrine Caverns */

-- Leotheras the Blind event
DELETE FROM `creature_spawns` WHERE entry IN (21875, 21812);

-- Lady Vashj event
REPLACE INTO `gameobject_names` (`entry`, `Type`, `DisplayID`, `Name`, `spellfocus`, `sound1`, `sound2`, `sound3`, `sound4`, `sound5`, `sound6`, `sound7`, `sound8`, `sound9`, `unknown1`, `unknown2`, `unknown3`, `unknown4`, `unknown5`, `unknown6`, `unknown7`, `unknown8`, `unknown9`, `unknown10`, `unknown11`, `unknown12`, `unknown13`, `unknown14`) VALUES
(185051, 0, 7265, 'Shield Generator', 0, 1718, 131072, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `gameobject_spawns` WHERE entry=185051;
INSERT INTO `gameobject_spawns` (`Entry`, `map`, `position_x`, `position_y`, `position_z`, `Facing`, `orientation1`, `orientation2`, `orientation3`, `orientation4`, `State`, `Flags`, `Faction`, `Scale`, `stateNpcLink`) VALUES
(185051, 548, 49.256, -902.354, 42.9769, 3.93902, 0, 0, 0.929729, -0.368245, 1, 0, 0, 1.5, 0),
(185051, 548, 49.687, -944.406, 42.7324, 2.31089, 0, 0, 0.914975, 0.403512, 1, 0, 0, 1.5, 0),
(185051, 548, 10.4122, -944.613, 42.8262, 0.817042, 0, 0, 0.39257, 0.919722, 1, 0, 0, 1.5, 0),
(185051, 548, 9.78695, -902.882, 42.9, 5.4399, 0, 0, 0.382205, -0.924078, 1, 0, 0, 1.5, 0);

-- Karathress event
DELETE FROM `creature_spawns` WHERE Entry=22820;

/* QUEST SCRIPTS */

/*They're Alive! Maybe... */
REPLACE INTO `quests` (`entry`, `ZoneId`, `sort`, `flags`, `MinLevel`, `questlevel`, `Type`, `RequiredRaces`, `RequiredClass`, `RequiredTradeskill`, `RequiredTradeskillValue`, `RequiredRepFaction`, `RequiredRepValue`, `LimitTime`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `srcItem`, `SrcItemCount`, `Title`, `Details`, `Objectives`, `CompletionText`, `IncompleteText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqKillMobOrGOId1`, `ReqKillMobOrGOId2`, `ReqKillMobOrGOId3`, `ReqKillMobOrGOId4`, `ReqKillMobOrGOCount1`, `ReqKillMobOrGOCount2`, `ReqKillMobOrGOCount3`, `ReqKillMobOrGOCount4`, `ReqCastSpellId1`, `ReqCastSpellId2`, `ReqCastSpellId3`, `ReqCastSpellId4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction4`, `RewRepFaction5`, `RewRepFaction6`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewRepValue6`, `RewRepLimit`, `RewMoney`, `RewXP`, `RewSpell`, `CastSpell`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `RequiredMoney`, `ExploreTrigger1`, `ExploreTrigger2`, `ExploreTrigger3`, `ExploreTrigger4`, `RequiredQuest1`, `RequiredQuest2`, `RequiredQuest3`, `RequiredQuest4`, `ReceiveItemId1`, `ReceiveItemId2`, `ReceiveItemId3`, `ReceiveItemId4`, `ReceiveItemCount1`, `ReceiveItemCount2`, `ReceiveItemCount3`, `ReceiveItemCount4`, `IsRepeatable`) VALUES
(9670, 3525, 0, 136, 16, 19, 0, 1101, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 'They''re Alive! Maybe...', 'It was a bloody mess, $N;. We were ambushed by a large pack of these spiders. Their progenitor descended upon us with incredible speed and wrapped us up in cocoons.$B$BAfter we were webbed, she began to lay eggs near us. We were to be food for her young! FOOD!$B$BI managed to cut my way out and escape but I will not leave the others behind. So far I''ve been unsuccessful in nearing the pass. Would you lend a hand?$B$BDestroy those cocoons! Hopefully some of our team is still alive!', 'Researcher Cornelius has asked that you free 5 Expedition Researchers.', 'You rescued over half the team! Word of your deed will definitely get back to Blood Watch and the exarch. Thanks again, $N;.', '', '', 'Expedition Researcher Freed', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 17681, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 26017, 0, 0, 0, 1, 0, 0, 0, 930, 0, 0, 0, 0, 0, 250, 0, 0, 0, 0, 0, 0, 1450, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

/* Great Bear Spirit  5929,5930*/
UPDATE quests SET flags=8, Type=0, SpecialFlags=64, EndText="Seek out the Great Bear Spirit and learn what it has to share with you about the nature of the bear.", ObjectiveText1="Talk to the Great Bear Spirit", ReqKillMobOrGOId1=11956, ReqKillMobOrGOCount1=1 WHERE entry=5929;
UPDATE quests SET flags=8, Type=0, SpecialFlags=64, EndText="Seek out the Great Bear Spirit and learn what it has to share with you about the nature of the bear.", ObjectiveText1="Talk to the Great Bear Spirit", ReqKillMobOrGOId1=11956, ReqKillMobOrGOCount1=1 WHERE entry=5930;

/* Body and Heart 6001,6002 */
UPDATE quests SET flags=8, Type=0, SpecialFlags=64, EndText="Face Lunaclaw and earn the strength of body and heart it possesses.", ObjectiveText1="Face Lunaclaw and earn the strength of body and heart it possesses.", ReqKillMobOrGOId1=12144, ReqKillMobOrGOCount1=1 WHERE entry=6001;
UPDATE quests SET flags=8, Type=0, SpecialFlags=64, EndText="Face Lunaclaw and earn the strength of body and heart it possesses.", ObjectiveText1="Face Lunaclaw and earn the strength of body and heart it possesses.", ReqKillMobOrGOId1=12144, ReqKillMobOrGOCount1=1 WHERE entry=6002;


/* Arcane Disturbances */

-- Change for Gameobject "TEMP Shrine of Remulos"
UPDATE `gameobject_names` SET `spellfocus` = '1390' WHERE `entry` = 300142;



/* Laying Waste to the Unwanted */

-- Gameobjects
DELETE FROM `gameobject_spawns` WHERE `entry` = '300152';

REPLACE INTO `gameobject_names` (entry, Type, DisplayID, Name, spellfocus, sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8, sound9, unknown1, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8, unknown9, unknown10, unknown11, unknown12, unknown13, unknown14) VALUES (300152, 8, 0, "TEMP Blade Throwers", 1399, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

INSERT INTO `gameobject_spawns` (Entry, map, position_x, position_y, position_z, Facing, orientation1, orientation2, orientation3, orientation4, State, Flags, Faction, Scale, stateNpcLink) VALUES
  (300152, 530, "-155.181", "2517.65", "43.5829", "3.28096", 0, 0, "0.997573", "-0.0696277", 1, 0, 0, 1, 0),
  (300152, 530, "-152.651", "2661.57", "44.8859", "2.94499", 0, 0, "0.995172", "0.098145", 1, 0, 0, 1, 0),
  (300152, 530, "-174.245", "2772.8", "32.3732", "3.28096", 0, 0, "0.997573", "-0.0696288", 1, 0, 0, 1, 0),
  (300152, 530, "-166.082", "2818.61", "29.2268", "2.93059", 0, 0, "0.99444", "0.105307", 1, 0, 0, 1, 0);
  


-- Gameobjects
DELETE FROM `gameobject_spawns` WHERE `entry` = '300150';

REPLACE INTO `gameobject_names`
  (entry, Type, DisplayID, Name, spellfocus, sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8, sound9, unknown1, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8, unknown9, unknown10, unknown11, unknown12, unknown13, unknown14)
VALUES
  (300150, 8, 0, "Zeth\'Gor must Burn Alliance", 1447, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

INSERT INTO `gameobject_spawns`
  (Entry, map, position_x, position_y, position_z, Facing, orientation1, orientation2, orientation3, orientation4, State, Flags, Faction, Scale, stateNpcLink)
VALUES
  (300150, 530, "-822.39", "2031.01", "39.25", 0, 0, 0, 0, 0, 1, 0, 0, 1, 0),
  (300150, 530, "-1153.73", "2107.55", "68.1", 0, 0, 0, 0, 0, 1, 0, 0, 1, 0),
  (300150, 530, "-897.39", "1920.97", "66.93", 0, 0, 0, 0, 0, 1, 0, 0, 1, 0),
  (300150, 530, "-977.39", "1877.65", "94.81", 0, 0, 0, 0, 0, 1, 0, 0, 1, 0);

-- Gameobjects
DELETE FROM `gameobject_spawns` WHERE `entry` IN ('300116', '300151');

REPLACE INTO `gameobject_names`
  (entry, Type, DisplayID, Name, spellfocus, sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8, sound9, unknown1, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8, unknown9, unknown10, unknown11, unknown12, unknown13, unknown14)
VALUES
  (300116, 8, 0, "TEMP Bleeding Hollow Forge", 1443, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
  (300151, 8, 0, "Zeth\'Gor must Burn Horde", 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

INSERT INTO `gameobject_spawns`
  (Entry, map, position_x, position_y, position_z, Facing, orientation1, orientation2, orientation3, orientation4, State, Flags, Faction, Scale, stateNpcLink)
VALUES
  (300116, 530, "-898.93", "1964.52", "68.76", 0, 0, 0, 0, 0, 1, 0, 0, 1, 0),
  (300151, 530, "-1137.05", "1970.16", "74.0588", "4.14273", 0, 0, "0.877311", "-0.479923", 1, 0, 0, 1, 0),
  (300151, 530, "-940.713", "1920.26", "69.2312", "5.87628", 0, 0, "0.202053", "-0.979375", 1, 0, 0, 1, 0),
  (300151, 530, "-1155.45", "2061.87", "68.5052", "0.682613", 0, 0, "0.334718", "0.942318", 1, 0, 0, 1, 0),
  (300151, 530, "-1052.76", "2007.01", "66.9565", "1.07435", 0, 0, "0.51171", "0.859158", 1, 0, 0, 1, 0);



/* The Bait for Lar'korwi (4292) */

UPDATE `gameobject_names` SET `Type`='8',`spellfocus`='603' WHERE (`entry`='169217');
UPDATE `gameobject_names` SET `Type`='8',`spellfocus`='604' WHERE (`entry`='169216');

DELETE FROM `creature_spawns` WHERE `entry`='9684';

/* Disrupt Their Reinforcements (10144/10208) */

UPDATE `gameobject_names` SET `Type`='10' WHERE (`entry`='184289');
UPDATE `gameobject_names` SET `Type`='10' WHERE (`entry`='184290');
UPDATE `gameobject_names` SET `Type`='10' WHERE (`entry`='184415');
UPDATE `gameobject_names` SET `Type`='10' WHERE (`entry`='184414');

DELETE FROM `creature_names` WHERE (`entry` = '184289');
DELETE FROM `creature_names` WHERE (`entry` = '184290');
DELETE FROM `creature_names` WHERE (`entry` = '184415');
DELETE FROM `creature_names` WHERE (`entry` = '184414');

INSERT INTO `creature_names` (`entry`,`name`,`subname`,`info_str`,`male_displayid`,`female_displayid`) VALUES ('184289','Port Kruul',' ','','0','0');
INSERT INTO `creature_names` (`entry`,`name`,`subname`,`info_str`,`male_displayid`,`female_displayid`) VALUES ('184290','Port Xilus',' ','','0','0');
INSERT INTO `creature_names` (`entry`,`name`,`subname`,`info_str`,`male_displayid`,`female_displayid`) VALUES ('184415','Port Kaalez',' ','','0','0');
INSERT INTO `creature_names` (`entry`,`name`,`subname`,`info_str`,`male_displayid`,`female_displayid`) VALUES ('184414','Port Grimh',' ','','0','0');

/* Misc */

-- Sickly Gazelle & Sickly Deer
UPDATE `creature_proto` SET `auras`='19502' WHERE `entry`=12296;
UPDATE `creature_proto` SET `auras`='19502' WHERE `entry`=12298;



-- Claw of the Raven God

DELETE FROM `gameobject_names` WHERE `entry`='185554';
DELETE FROM `gameobject_names` WHERE `entry`='300154';

INSERT INTO `gameobject_names` VALUES ('185554', '10', '7363', 'The Raven\'s Claw', '1732', '196608', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');
INSERT INTO `gameobject_names` VALUES ('300154', '10', '4891', 'The Raven\'s Claw', '1732', '196608', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');

DELETE FROM `gameobject_spawns` WHERE `Entry`='185554';
DELETE FROM `gameobject_spawns` WHERE `Entry`='300154';

INSERT INTO `gameobject_spawns`
  (Entry, map, position_x, position_y, position_z, Facing, orientation1, orientation2, orientation3, orientation4, State, Flags, Faction, Scale, stateNpcLink)
VALUES
  (185554, 556, "-86.6862", "287.625", "26.4832", "2.27127", 0, 0, 0, 0, 1, 0, 0, 1, 0);
  
DELETE FROM `creature_spawns` WHERE `entry`='23035';

-- Thuk the Defiant
DELETE FROM `creature_spawns` WHERE `entry`='22920';
INSERT INTO `creature_spawns`
   (`entry`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `movetype`, `displayid`, `faction`, `flags`, `bytes`, `bytes2`, `emote_state`, `npc_respawn_link`, `channel_spell`, `channel_target_sqlid`, `channel_target_sqlid_creature`, `standstate`)
VALUES
   (22920, 530, 3989.09, 6071.56, 266.417, 3.79819, 0, 20863, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `gameobject_spawns` WHERE `entry`='185512';
INSERT INTO `gameobject_spawns`
   (`Entry`, `map`, `position_x`, `position_y`, `position_z`, `Facing`, `orientation1`, `orientation2`, `orientation3`, `orientation4`, `State`, `Flags`, `Faction`, `Scale`, `stateNpcLink`)
VALUES
   (185512, 530, 3989.07, 6071.52, 266.415, -2.14675, 0, 0, 0.878817, -0.477159, 1, 32, 0, 3, 0);
   
-- To Legion Hold
-- Intercept their reinforcements

DELETE FROM `gameobject_spawns` WHERE `Entry` IN (300112, 550000);
DELETE FROM `gameobject_names` WHERE `entry` IN (300112, 550000);
INSERT INTO `gameobject_names`
   (`entry`, `Type`, `DisplayID`, `Name`, `spellfocus`, `sound1`, `sound2`, `sound3`, `sound4`, `sound5`, `sound6`, `sound7`, `sound8`, `sound9`, `unknown1`, `unknown2`, `unknown3`, `unknown4`, `unknown5`, `unknown6`, `unknown7`, `unknown8`, `unknown9`, `unknown10`, `unknown11`, `unknown12`, `unknown13`, `unknown14`)
VALUES
   (300112, 8, 0, 'TEMP Legion Communication Device', 1438, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
   (550000, 8, 0, 'Ship Sail', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

INSERT INTO `gameobject_spawns`
   (`Entry`, `map`, `position_x`, `position_y`, `position_z`, `Facing`, `orientation1`, `orientation2`, `orientation3`, `orientation4`, `State`, `Flags`, `Faction`, `Scale`, `stateNpcLink`)
VALUES
   (550000, 530, 13200.2, -7049.18, 3.83852, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0),
   (550000, 530, 3319.42, -6988.78, 4.00299, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0),
   (550000, 530, 13274.5, -7145.43, 4.77029, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0),
   (300112, 530, -3300.61, 2927.43, 173.612, 5.35918, 0, 0, 0.44574, -0.895162, 1, 0, 0, 1, 0);



/* OTHER QUERIES */

-- Gruuls Lair, Black Temple, Tempest Keep, Magtheridons Lair, Karazhan, This Does NOT eat ur cpu up, so dont worry(tested it)
UPDATE `worldmap_info` SET `viewingDistance`='250' WHERE `entry` in ('565','564','550','544','532');
-- Serpentshrine Cavern Viewing Distance
UPDATE `worldmap_info` SET `viewingDistance`='250' WHERE `entry` = 548;
-- Wailing Caverns Viewing Distance
UPDATE `worldmap_info` SET `viewingDistance`='4000' WHERE `entry` = 43;