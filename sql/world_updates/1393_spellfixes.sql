-- teleport dalaram - items
REPLACE INTO `teleport_coords` VALUE(54406, "Teleport to Dalaran", 571, 5807.75, 588.347, 661.505, 0);

-- teleport dalaram - mage spell
REPLACE INTO `teleport_coords` VALUE(53140, "Teleport to Dalaran", 571, 5807.75, 588.347, 661.505, 0);

-- Windfury Totem
REPLACE INTO totemspells VALUES(8512, 8515, 0, 0);

-- Flametongue Totem
REPLACE INTO totemspells VALUES(8227, 52109, 0, 0);
REPLACE INTO totemspells VALUES(8249, 52110, 0, 0);
REPLACE INTO totemspells VALUES(10526, 52111, 0, 0);
REPLACE INTO totemspells VALUES(16387, 52112, 0, 0);
REPLACE INTO totemspells VALUES(25557, 52113, 0, 0);
REPLACE INTO totemspells VALUES(58649, 58651, 0, 0);
REPLACE INTO totemspells VALUES(58652, 58654, 0, 0);
REPLACE INTO totemspells VALUES(58656, 58655, 0, 0);


-- Elemental Protection Totem
update totemspells set castspell1=8263 where spell=8262;

-- Totem of Wrath
REPLACE INTO totemspells VALUES(30706, 57658, 0, 0);
REPLACE INTO totemspells VALUES(57720, 57660, 0, 0);
REPLACE INTO totemspells VALUES(57721, 57662, 0, 0);
REPLACE INTO totemspells VALUES(57722, 57663, 0, 0);


-- Immolation trap
REPLACE INTO gameobject_names
  (entry, Type, DisplayID, Name, spellfocus, sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8, sound9, unknown1, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8, unknown9, unknown10, unknown11, unknown12, unknown13, unknown14)
VALUES
  (189318, 6, 3074, "Immolation Trap VII", 12, 0, 5, 49053, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  
-- explosive trap
REPLACE INTO gameobject_names
  (entry, Type, DisplayID, Name, spellfocus, sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8, sound9, unknown1, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8, unknown9, unknown10, unknown11, unknown12, unknown13, unknown14)
VALUES
  (189321, 6, 3074, "Explosive Trap V", 12, 0, 5, 49064, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  
-- forced targets (quests mostly)
REPLACE INTO `spell_forced_targets` VALUES(36314, 20132);
REPLACE INTO `spell_forced_targets` VALUES(41291, 22357);
REPLACE INTO `spell_forced_targets` VALUES(38177, 21387);
REPLACE INTO `spell_forced_targets` VALUES(4130, 2760);
REPLACE INTO `spell_forced_targets` VALUES(4131, 2761);
REPLACE INTO `spell_forced_targets` VALUES(4132, 2762);
REPLACE INTO `spell_forced_targets` VALUES(38177, 21387);
REPLACE INTO `spell_forced_targets` VALUES(45072, 25031);
REPLACE INTO `spell_forced_targets` VALUES(45072, 25033);
REPLACE INTO `spell_forced_targets` VALUES(45072, 25030);
REPLACE INTO `spell_forced_targets` VALUES(36310, 20058);

-- spellfocus bugs
update `gameobject_names` set `sound1`=5 where `sound1`<5 AND `Type`=8;

-- master firestone
REPLACE INTO items values
  (40773, 0, 8, -1, "Master Firestone", "", "", "", 7409, 1, 2097216, 0, 0, 0, -1, -1, 56, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54721, 0, -5, 1000, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, -1, 1, "", 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0);

-- campfires
update `gameobject_names` set `spellfocus` = 4 where `name` LIKE "%fire%" AND `type` = 8 AND `spellfocus` = 0;
update `gameobject_names` set `sound2` =  0 where `name` LIKE "%fire%" AND `type` = 8 AND `spellfocus` = 4;

-- mana spring totem
REPLACE INTO totemspells VALUES(58771, 58775, 0, 0);
REPLACE INTO totemspells VALUES(58773, 58776, 0, 0);
REPLACE INTO totemspells VALUES(58774, 58777, 0, 0);

-- Ritual of Souls
DELETE FROM gameobject_names where name="Soul Portal";
DELETE FROM gameobject_names where name="Soulwell";

INSERT INTO gameobject_names
  (entry, Type, DisplayID, Name, spellfocus, sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8, sound9, unknown1, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8, unknown9, unknown10, unknown11, unknown12, unknown13, unknown14)
VALUES
  (181622, 18, 7358, "Soul Portal", 3, 29886, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

INSERT INTO gameobject_names
  (entry, Type, DisplayID, Name, spellfocus, sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8, sound9, unknown1, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8, unknown9, unknown10, unknown11, unknown12, unknown13, unknown14)
VALUES
  (193168, 18, 7358, "Soul Portal", 3, 58889, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

INSERT INTO gameobject_names
  (entry, Type, DisplayID, Name, spellfocus, sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8, sound9, unknown1, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8, unknown9, unknown10, unknown11, unknown12, unknown13, unknown14)
VALUES
  (193169, 22, 7359, "Soulwell", 34150, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

INSERT INTO gameobject_names
  (entry, Type, DisplayID, Name, spellfocus, sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8, sound9, unknown1, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8, unknown9, unknown10, unknown11, unknown12, unknown13, unknown14)
VALUES
  (181621, 22, 7359, "Soulwell", 34130, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);