-- unusued
ALTER TABLE `ai_agents` DROP COLUMN `event`;

/* Optional configuration with enumerated fields.
CREATE TABLE `ai_agents` (
  `entry` int(11) unsigned NOT NULL DEFAULT '0',
  `type` enum('MELEE','RANGED','FLEE','SPELL','CALLFORHELP') NOT NULL DEFAULT 'SPELL',
  `chance` int(11) unsigned NOT NULL DEFAULT '0',
  `maxcount` int(11) unsigned NOT NULL DEFAULT '0',
  `spell` int(11) unsigned NOT NULL DEFAULT '0',
  `spelltype` enum('ROOT','HEAL','STUN','FEAR','SILENCE','CURSE','AOEDAMAGE','DAMAGE','SUMMON','BUFF','DEBUFF') NOT NULL DEFAULT 'ROOT',
  `targettype` enum('RANDOMTARGET','TARGETLOCATION','CREATURELOCATION','SELF','OWNER') NOT NULL DEFAULT 'RANDOMTARGET',
  `cooldown` int(8) NOT NULL DEFAULT '0',
  `floatMisc1` float NOT NULL DEFAULT '0',
  `Misc2` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`,`type`,`spell`),
  UNIQUE KEY `a` (`entry`,`spell`,`type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='AI System';
/*