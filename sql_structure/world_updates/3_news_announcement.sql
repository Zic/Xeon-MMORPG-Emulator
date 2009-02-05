--
-- Table structure for table `news_announcements`
--

DROP TABLE IF EXISTS `news_announcements`;

CREATE TABLE `news_announcements` (
  `id` int(30) unsigned NOT NULL AUTO_INCREMENT,
  `faction_mask` int(30) NOT NULL,
  `message_text` varchar(500) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
