-- this field is needed for ingame account ban.
ALTER TABLE `accounts` ADD `banreason` VARCHAR(512) AFTER `banned`;

/* full table
CREATE TABLE `accounts` (
	`acct` int(5) NOT NULL AUTO_INCREMENT,
	`login` varchar(32) NOT NULL DEFAULT '',
	`password` varchar(255) NOT NULL DEFAULT '',
	`SessionKey` varchar(255) NOT NULL DEFAULT '',
	`gm` varchar(15) NOT NULL DEFAULT '0',
	`flags` int(11) NOT NULL DEFAULT '24',
	`banned` tinyint(1) NOT NULL DEFAULT '0',
	`banreason` varchar(512) DEFAULT NULL,
	`lastlogin` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
	`lastip` varchar(15) NOT NULL DEFAULT '',
	`forceLanguage` varchar(5) NOT NULL DEFAULT 'enUS',
	`email` varchar(32) DEFAULT NULL,
	`muted` int(30) NOT NULL DEFAULT '0',
	PRIMARY KEY (`acct`),
	UNIQUE KEY `login` (`login`)
) ENGINE=MyISAM AUTO_INCREMENT=4233 DEFAULT CHARSET=utf8
*/