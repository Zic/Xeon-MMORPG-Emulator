-- creature_proto
ALTER TABLE creature_proto DROP spell1;
ALTER TABLE creature_proto DROP spell2;
ALTER TABLE creature_proto DROP spell3;
ALTER TABLE creature_proto DROP spell4;
ALTER TABLE creature_proto DROP spell_flags;

-- creature_spawns
ALTER TABLE creature_spawns DROP bytes1;

-- Unnecessary table
DROP TABLE instance_bosses;

-- Quests
ALTER TABLE quests DROP RewardMoneyAtMaxLevel;
ALTER TABLE quests ADD `RequiredMoney` int(10) NOT NULL AFTER `PointOpt`;
ALTER TABLE quests ADD `RewardTitle` int(10) NOT NULL DEFAULT '0' AFTER `RewRepLimit`;
ALTER TABLE quests DROP IF EXISTS RewRepValue3;
ALTER TABLE quests DROP IF EXISTS RewRepValue4;
ALTER TABLE quests DROP IF EXISTS RewRepValue5;
ALTER TABLE quests DROP IF EXISTS RewRepValue6;
ALTER TABLE quests DROP IF EXISTS RewRepFaction3;
ALTER TABLE quests DROP IF EXISTS RewRepFaction4;
ALTER TABLE quests DROP IF EXISTS RewRepFaction5;
ALTER TABLE quests DROP IF EXISTS RewRepFaction6;