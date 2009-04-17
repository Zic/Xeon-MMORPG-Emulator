-- Usable after HS >R1176

ALTER TABLE `reputation_instance_onkill` 
ADD COLUMN `mob_rep_reward_heroic` int(30) NOT NULL AFTER `mob_rep_reward`,
ADD COLUMN `mob_rep_limit_heroic` int(30) NOT NULL AFTER `mob_rep_limit`,
ADD COLUMN `boss_rep_reward_heroic` int(30) NOT NULL AFTER `boss_rep_reward`,
ADD COLUMN `boss_rep_limit_heroic` int(30) NOT NULL AFTER `boss_rep_limit`;

-- Don't want 0 values here, so copy existing values for now, should be updated later on.
UPDATE `reputation_instance_onkill` SET
`mob_rep_reward_heroic`= `mob_rep_reward`,
`mob_rep_limit_heroic` = `mob_rep_limit`,
`boss_rep_reward_heroic` = `boss_rep_reward`,
`boss_rep_limit_heroic` = `boss_rep_limit`;