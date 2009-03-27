-- FYI core doesn;t realy care that much about names anyway, but these are the correct names:
# alter table creature_proto change column resistance6 `resistance7` int(30) NOT NULL DEFAULT 0;
# alter table creature_proto change column resistance5 `resistance6` int(30) UNSIGNED NOT NULL DEFAULT 0 ;
# alter table creature_proto change column resistance4 `resistance5` int(30) UNSIGNED NOT NULL DEFAULT 0;
# alter table creature_proto change column resistance3 `resistance4` int(30) UNSIGNED NOT NULL DEFAULT 0;
# alter table creature_proto change column resistance2 `resistance3` int(30) UNSIGNED NOT NULL DEFAULT 0;
# alter table creature_proto change column resistance1 `resistance2` int(30) UNSIGNED NOT NULL DEFAULT 0;
# alter table creature_proto change column armor `resistance1` int(30) UNSIGNED NOT NULL DEFAULT 0;