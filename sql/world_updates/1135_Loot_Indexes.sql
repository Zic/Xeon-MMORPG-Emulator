-- Usable after HS >R1134

ALTER TABLE `creatureloot` DROP COLUMN `index`;
ALTER TABLE `creatureloot` DROP KEY `PRIMARY`, ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `disenchantingloot` DROP COLUMN `index`;
ALTER TABLE `disenchantingloot` DROP KEY `PRIMARY`, ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `fishingloot` DROP COLUMN `index`;
ALTER TABLE `fishingloot` DROP KEY `PRIMARY`, ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `itemloot` DROP COLUMN `index`;
ALTER TABLE `itemloot` DROP KEY `PRIMARY`, ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `millingloot` DROP COLUMN `index`;
ALTER TABLE `millingloot` DROP KEY `PRIMARY`, ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `objectloot` DROP COLUMN `index`;
ALTER TABLE `objectloot` DROP KEY `PRIMARY`, ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `pickpocketingloot` DROP COLUMN `index`;
ALTER TABLE `pickpocketingloot` DROP KEY `PRIMARY`, ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `prospectingloot` DROP COLUMN `index`;
ALTER TABLE `prospectingloot` DROP KEY `PRIMARY`, ADD PRIMARY KEY (`entryid`,`itemid`);
ALTER TABLE `skinningloot` DROP COLUMN `index`;
ALTER TABLE `skinningloot` DROP KEY `PRIMARY`, ADD PRIMARY KEY (`entryid`,`itemid`);
