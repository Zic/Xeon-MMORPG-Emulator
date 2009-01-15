/*
SQLyog Community Edition- MySQL GUI v5.32
Host - 6.0.7-alpha-community : Database - ncdbnew
*********************************************************************
Server version : 6.0.7-alpha-community
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

/*Table structure for table `millingloot` */

DROP TABLE IF EXISTS `millingloot`;

CREATE TABLE `millingloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(11) unsigned NOT NULL DEFAULT '0',
  `itemid` int(11) unsigned NOT NULL DEFAULT '0',
  `percentchance` float NOT NULL DEFAULT '0',
  `heroicpercentchance` float DEFAULT '0',
  `mincount` int(30) DEFAULT '1',
  `maxcount` int(30) DEFAULT '1',
  `ffa_loot` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`)
) ENGINE=MyISAM AUTO_INCREMENT=65 DEFAULT CHARSET=utf8;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
