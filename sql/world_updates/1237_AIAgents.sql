ALTER TABLE ai_agents CHANGE spelltype spelltype enum('ROOT','HEAL','STUN','FEAR','SILENCE','CURSE','AOEDAMAGE','DAMAGE','SUMMON','BUFF','DEBUFF','INTERRUPT') NOT NULL DEFAULT 'ROOT';
UPDATE ai_agents SET spelltype = 'DEBUFF' where spelltype = 'CURSE';
UPDATE ai_agents SET spelltype = 'INTERRUPT' where spelltype = 'SILENCE';
ALTER TABLE ai_agents CHANGE spelltype spelltype enum('ROOT','DAMAGE','AOEDAMAGE','INTERRUPT','FEAR','STUN','BUFF','DEBUFF','SUMMON','HEAL') NOT NULL DEFAULT 'ROOT';