-- Convert gm tickets
ALTER TABLE gm_tickets ADD type int(2) NOT NULL AFTER level;

-- Convert characters
ALTER TABLE characters DROP finisheddailies;

-- Why does ArcEmu even have this field? What a waste
ALTER TABLE groups DROP instanceids;

-- Player pets need to be converted, too!
ALTER TABLE playerpets DROP reset_time;
ALTER TABLE playerpets DROP reset_cost;
ALTER TABLE playerpets DROP spellid;

-- Drop table: instanceids, dunno wtf it's even used for
DROP TABLE instanceids;

-- Fix the instances table
ALTER TABLE instances DROP persistent;

