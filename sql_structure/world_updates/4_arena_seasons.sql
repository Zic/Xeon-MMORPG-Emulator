ALTER TABLE worldstate_template CHANGE COLUMN mapid mapid int4 not null;

INSERT INTO worldstate_template(mapid, zone_mask, faction_mask, field_number, initial_value, comment) VALUES(-1, -1, -1, 3901, 4, 'ARENA_SEASON_COUNT');
INSERT INTO worldstate_template(mapid, zone_mask, faction_mask, field_number, initial_value, comment) VALUES(-1, -1, -1, 3191, 4, 'ARENA_SEASON_STATE; 0 = finished; else started');

