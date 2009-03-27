-- Usable after HS >R1134

ALTER TABLE `creatureloot` DROP COLUMN `index`;
ALTER TABLE `disenchantingloot` DROP COLUMN `index`;
ALTER TABLE `fishingloot` DROP COLUMN `index`;
ALTER TABLE `itemloot` DROP COLUMN `index`;
ALTER TABLE `millingloot` DROP COLUMN `index`;
ALTER TABLE `objectloot` DROP COLUMN `index`;
ALTER TABLE `pickpocketingloot` DROP COLUMN `index`;
ALTER TABLE `prospectingloot` DROP COLUMN `index`;
ALTER TABLE `skinningloot` DROP COLUMN `index`;

ALTER TABLE `creatureloot` ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `disenchantingloot` ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `fishingloot` ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `itemloot` ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `millingloot` ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `objectloot` ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `pickpocketingloot` ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `prospectingloot` ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `skinningloot` ADD PRIMARY KEY (`entryid`,`itemid`);
