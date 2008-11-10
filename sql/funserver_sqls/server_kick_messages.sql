SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for server_kick_messages
-- ----------------------------
CREATE TABLE `server_kick_messages` (
  `Index` varchar(50) NOT NULL,
  `Message` varchar(400) NOT NULL,
  PRIMARY KEY (`Index`),
  UNIQUE KEY `Index` (`Index`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `server_kick_messages` VALUES ('1', 'This is a test message');
INSERT INTO `server_kick_messages` VALUES ('adf', 'This is a second test message');
