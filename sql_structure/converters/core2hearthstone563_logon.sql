ALTER TABLE accounts DROP COLUMN forceLanguage;

ALTER TABLE accounts ADD COLUMN changed int1 unsigned not null default 1;
