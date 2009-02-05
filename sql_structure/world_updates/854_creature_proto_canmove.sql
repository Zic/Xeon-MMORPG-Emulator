/*
This mask limits creatures movement to:
LIMIT_ROOT 	0x0 	Creauture can't move at all
LIMIT_ROOT 	0x1 	Creature can only move on land
LIMIT_ROOT 	0x2 	Creature can only move in water
LIMIT_ROOT 	0x4 	Creature can only fly in the air

Use 7 to allow all types. Note that rooted target can't be moved with AI or waypoints

Note that this is not 100% reliable yet, as maps extractor isn't 100% reliable.
currently core accepts 0 and 7 (root/free movement)
*/
alter table `creature_proto` add column `CanMove` int  DEFAULT '7' NOT NULL  after `vehicle_entry`;