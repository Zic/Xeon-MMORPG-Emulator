ALTER TABLE `quests` change column `RewardMoneyAtMaxLevel` `RequiredMoney` int(10) unsigned not null default 0;
ALTER TABLE `creature_proto` DROP column `spell1`;
ALTER TABLE `creature_proto` DROP column `spell2`;
ALTER TABLE `creature_proto` DROP column `spell3`;
ALTER TABLE `creature_proto` DROP column `spell4`;
ALTER TABLE `creature_proto` DROP column `spell_flags`;