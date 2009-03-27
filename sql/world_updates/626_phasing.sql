ALTER TABLE creature_spawns ADD COLUMN phase int(10) NOT NULL default '0';
ALTER TABLE gameobject_spawns ADD COLUMN phase int(10) NOT NULL default '0';