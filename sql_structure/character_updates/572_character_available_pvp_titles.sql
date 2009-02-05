ALTER TABLE `characters` MODIFY `available_pvp_titles` bigint(40) not null;
ALTER TABLE characters ADD COLUMN `available_pvp_titles2` bigint(40) not null after available_pvp_titles, 
  COMMENT='Second 64 bits mask of known player titles';