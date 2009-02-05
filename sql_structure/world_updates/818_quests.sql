
-- Some quests reward reputation for 5 different factions..
ALTER TABLE quests ADD RewRepFaction5 INT(11) DEFAULT 0 NOT NULL AFTER RewRepFaction2;
ALTER TABLE quests ADD RewRepFaction4 INT(11) DEFAULT 0 NOT NULL AFTER RewRepFaction2;
ALTER TABLE quests ADD RewRepFaction3 INT(11) DEFAULT 0 NOT NULL AFTER RewRepFaction2;
ALTER TABLE quests ADD RewRepValue5 INT(11) DEFAULT 0 NOT NULL AFTER RewRepValue2;
ALTER TABLE quests ADD RewRepValue4 INT(11) DEFAULT 0 NOT NULL AFTER RewRepValue2;
ALTER TABLE quests ADD RewRepValue3 INT(11) DEFAULT 0 NOT NULL AFTER RewRepValue2;

-- Some Quest require all RequiredQuests to be complete (and_or = 0),
-- others will complete if any one of the RequiredQuests is met (and_or = 1)
ALTER TABLE quests ADD RequiredQuest_and_or INT(3) DEFAULT 0 NOT NULL AFTER RequiredQuest4
