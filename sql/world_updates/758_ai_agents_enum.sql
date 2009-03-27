 
ALTER TABLE ai_agents CHANGE type type VARCHAR(50) NOT NULL DEFAULT '';
ALTER TABLE ai_agents CHANGE spelltype spelltype VARCHAR(50) NOT NULL DEFAULT '';
ALTER TABLE ai_agents CHANGE targettype targettype VARCHAR(50) NOT NULL DEFAULT '';
 
UPDATE ai_agents SET type = 'SPELL' WHERE type = 0;
UPDATE ai_agents SET type = 'MELEE' WHERE type = 1;
UPDATE ai_agents SET type = 'RANGED' WHERE type = 2;
UPDATE ai_agents SET type = 'FLEE' WHERE type = 3;
UPDATE ai_agents SET type = 'SPELL' WHERE type = 4;
UPDATE ai_agents SET type = 'CALLFORHELP' WHERE type = 5;
 
UPDATE ai_agents SET spelltype = 'ROOT' WHERE spelltype = 0;
UPDATE ai_agents SET spelltype = 'ROOT' WHERE spelltype = 1;
UPDATE ai_agents SET spelltype = 'HEAL' WHERE spelltype = 2;
UPDATE ai_agents SET spelltype = 'STUN' WHERE spelltype = 3;
UPDATE ai_agents SET spelltype = 'FEAR' WHERE spelltype = 4;
UPDATE ai_agents SET spelltype = 'SILENCE' WHERE spelltype = 5;
UPDATE ai_agents SET spelltype = 'CURSE' WHERE spelltype = 6;
UPDATE ai_agents SET spelltype = 'AOEDAMAGE' WHERE spelltype = 7;
UPDATE ai_agents SET spelltype = 'DAMAGE' WHERE spelltype = 8;
UPDATE ai_agents SET spelltype = 'SUMMON' WHERE spelltype = 9;
UPDATE ai_agents SET spelltype = 'BUFF' WHERE spelltype = 10;
UPDATE ai_agents SET spelltype = 'DEBUFF' WHERE spelltype = 11;
 
UPDATE ai_agents SET targettype = 'RANDOMTARGET' WHERE targettype = 0;
UPDATE ai_agents SET targettype = 'RANDOMTARGET' WHERE targettype = 1;
UPDATE ai_agents SET targettype = 'TARGETLOCATION' WHERE targettype = 2;
UPDATE ai_agents SET targettype = 'CREATURELOCATION' WHERE targettype = 3;
UPDATE ai_agents SET targettype = 'SELF' WHERE targettype = 4;
UPDATE ai_agents SET targettype = 'OWNER' WHERE targettype = 5;
 
ALTER TABLE ai_agents CHANGE type type enum('MELEE','RANGED','FLEE','SPELL','CALLFORHELP') NOT NULL DEFAULT 'SPELL'; 
ALTER TABLE ai_agents CHANGE spelltype spelltype enum('ROOT','HEAL','STUN','FEAR','SILENCE','CURSE','AOEDAMAGE','DAMAGE','SUMMON','BUFF','DEBUFF') NOT NULL DEFAULT 'ROOT';
ALTER TABLE ai_agents CHANGE targettype targettype enum('RANDOMTARGET','TARGETLOCATION','CREATURELOCATION','SELF','OWNER') NOT NULL DEFAULT 'RANDOMTARGET';

UPDATE ai_agents SET targettype = 'RANDOMTARGET' WHERE targettype = -1;