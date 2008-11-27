SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for worldstates
-- ----------------------------
CREATE TABLE `worldstates` (
  `MapId` int(10) NOT NULL,
  `Index` int(10) NOT NULL,
  `Value` int(10) NOT NULL,
  `ZoneRef` int(10) NOT NULL,
  `FactionRef` int(10) NOT NULL,
  KEY `MapId` (`MapId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
