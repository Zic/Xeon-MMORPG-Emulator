update `gameobject_names` set `spellfocus` = 4 where `name` LIKE "%fire%" AND `type` = 8 AND `spellfocus` = 0;
update `gameobject_names` set `sound2` =  0 where `name` LIKE "%fire%" AND `type` = 8 AND `spellfocus` = 4;
update `gameobject_names` set `sound1`=5 where `sound1`<5 AND `Type`=8;

SET FOREIGN_KEY_CHECKS=0;

DROP TABLE IF EXISTS `spell_coef_override`;
-- ----------------------------
-- Table structure for spell_coef_override
-- ----------------------------
CREATE TABLE `spell_coef_override` (
  `id` int default '0',
  `Dspell_coef_override` float default '0',
  `OTspell_coef_override` float default '0',
  `AP_coef_override` float default '0',
  `RAP_coef_override` float default '0'  
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records 
-- ----------------------------
-- Shadow Bolt
INSERT INTO `spell_coef_override` VALUES ('686', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('695', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('705', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('1088', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('1106', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('7641', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11659', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11660', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11661', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25307', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27209', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47808', '0.8569', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47809', '0.8569', '0', '0', '0');

-- Magma totem
INSERT INTO `spell_coef_override` VALUES ('8187', '0.10', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10579', '0.10', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10580', '0.10', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10581', '0.10', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25550', '0.10', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58732', '0.10', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58735', '0.10', '0', '0', '0');

-- Cricle of Healing
INSERT INTO `spell_coef_override` VALUES ('34861', '0.402', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('34863', '0.402', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('34864', '0.402', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('34865', '0.402', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('34866', '0.402', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48088', '0.402', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48089', '0.402', '0', '0', '0');

-- Dragon's Breath
INSERT INTO `spell_coef_override` VALUES ('31661', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('33041', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('33042', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('33043', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42949', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42950', '0.1936', '0', '0', '0');

-- Fire Nova Totem
INSERT INTO `spell_coef_override` VALUES ('8443', '0.2142', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8504', '0.2142', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8505', '0.2142', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11310', '0.2142', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11311', '0.2142', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25538', '0.2142', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25539', '0.2142', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('61650', '0.2142', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('61654', '0.2142', '0', '0', '0');

-- Earth Shock
INSERT INTO `spell_coef_override` VALUES ('8042', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8044', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8045', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8046', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10412', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10413', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10414', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25454', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49230', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49231', '0.3858', '0', '0', '0');

-- Desperate Prayer
INSERT INTO `spell_coef_override` VALUES ('19236', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19238', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19240', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19241', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19242', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19243', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25437', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48172', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48173', '0.8068', '0', '0', '0');

-- Chain Heal
INSERT INTO `spell_coef_override` VALUES ('1064', '0.8', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10622', '0.8', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10623', '0.8', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25422', '0.8', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25423', '0.8', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('55458', '0.8', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('55459', '0.8', '0', '0', '0');

-- Incinerate
INSERT INTO `spell_coef_override` VALUES ('29722', '0.7139', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('32231', '0.7139', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47837', '0.7139', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47838', '0.7139', '0', '0', '0');

-- Flame Shock
INSERT INTO `spell_coef_override` VALUES ('8050', '0.2142', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8052', '0.2142', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8053', '0.2142', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10447', '0.2142', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10448', '0.2142', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('29228', '0.2142', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25457', '0.2142', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49232', '0.2142', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49233', '0.2142', '0.1', '0', '0');

-- Blizzard
INSERT INTO `spell_coef_override` VALUES ('42208', '0.1437', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42209', '0.1437', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42210', '0.1437', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42211', '0.1437', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42212', '0.1437', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42213', '0.1437', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42198', '0.1437', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42937', '0.1437', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42938', '0.1437', '0', '0', '0');

-- Force of Nature
-- INSERT INTO `spell_coef_override` VALUES ('', '0.035', '0', '0', '0');

-- Healing Stream Totem
INSERT INTO `spell_coef_override` VALUES ('52041', '0.045', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('52046', '0.045', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('52047', '0.045', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('52048', '0.045', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('52049', '0.045', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('52050', '0.045', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58759', '0.045', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58760', '0.045', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58761', '0.045', '0', '0', '0');

-- Shadow Ward
INSERT INTO `spell_coef_override` VALUES ('6229', '0.3', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11739', '0.3', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11740', '0.3', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('28610', '0.3', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47890', '0.3', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47891', '0.3', '0', '0', '0');

-- Arcane Blast
INSERT INTO `spell_coef_override` VALUES ('30451', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42894', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42896', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42897', '0.7143', '0', '0', '0');

-- Regrowth
INSERT INTO `spell_coef_override` VALUES ('8936', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8938', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8939', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8940', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8941', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9750', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9856', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9857', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9858', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26980', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48442', '0.539', '0.188', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48443', '0.539', '0.188', '0', '0');

-- Seal of Light
INSERT INTO `spell_coef_override` VALUES ('20167', '0.15', '0', '0.15', '0');

-- Nourish
INSERT INTO `spell_coef_override` VALUES ('50464', '0.6611', '0', '0', '0');

-- Rain of Fire
INSERT INTO `spell_coef_override` VALUES ('5740', '0.6932', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6219', '0.6932', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11677', '0.6932', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11678', '0.6932', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27212', '0.6932', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47819', '0.6932', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47820', '0.6932', '0', '0', '0');

-- Devouring Plague
INSERT INTO `spell_coef_override` VALUES ('2944', '0', '0.1849', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19276', '0', '0.1849', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19277', '0', '0.1849', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19278', '0', '0.1849', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19279', '0', '0.1849', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19280', '0', '0.1849', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25467', '0', '0.1849', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48299', '0', '0.1849', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48300', '0', '0.1849', '0', '0');

-- Seal of Wisdom
INSERT INTO `spell_coef_override` VALUES ('20168', '0.25', '0', '0', '0');

-- Arcane Missiles
INSERT INTO `spell_coef_override` VALUES ('5143', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5144', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5145', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8416', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8417', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10211', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10212', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25345', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27075', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('38699', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('38704', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42843', '0.2857', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42846', '0.2857', '0', '0', '0');

-- Lifebloom
INSERT INTO `spell_coef_override` VALUES ('33763', '0.6453', '0.09518', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48450', '0.6453', '0.09518', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48451', '0.6453', '0.09518', '0', '0');

-- Renew
INSERT INTO `spell_coef_override` VALUES ('139', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6074', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6075', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6076', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6077', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6078', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10927', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10928', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10929', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25315', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25221', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25222', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48067', '0', '0.36', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48068', '0', '0.36', '0', '0');

-- Siphon Life 3.1 change
-- INSERT INTO `spell_coef_override` VALUES ('', '0', '0.10', '0', '0');

-- Frost Shock
INSERT INTO `spell_coef_override` VALUES ('8056', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8058', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10472', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10473', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25464', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49235', '0.3858', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49236', '0.3858', '0', '0', '0');

-- Tranquility
INSERT INTO `spell_coef_override` VALUES ('740', '0.538', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8918', '0.538', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9862', '0.538', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9863', '0.538', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26983', '0.538', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48446', '0.538', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48447', '0.538', '0', '0', '0');

-- Wrath
INSERT INTO `spell_coef_override` VALUES ('5176', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5177', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5178', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5179', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5180', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6780', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8905', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9912', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26984', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26985', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48459', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48461', '0.5714', '0', '0', '0');

-- Living Bomb
INSERT INTO `spell_coef_override` VALUES ('44457', '0.4', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('55359', '0.4', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('55360', '0.4', '0.2', '0', '0');

-- Flamestrike
INSERT INTO `spell_coef_override` VALUES ('2120', '0.2357', '0.122', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('2121', '0.2357', '0.122', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8422', '0.2357', '0.122', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8423', '0.2357', '0.122', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10215', '0.2357', '0.122', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10216', '0.2357', '0.122', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27086', '0.2357', '0.122', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42925', '0.2357', '0.122', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42926', '0.2357', '0.122', '0', '0');

-- Shadowfury
INSERT INTO `spell_coef_override` VALUES ('30283', '0.1932', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('30413', '0.1932', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('30414', '0.1932', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47846', '0.1932', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47847', '0.1932', '0', '0', '0');

-- Searing Totem
INSERT INTO `spell_coef_override` VALUES ('3606', '0.1667', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6350', '0.1667', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6351', '0.1667', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6352', '0.1667', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10435', '0.1667', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10436', '0.1667', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25530', '0.1667', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58700', '0.1667', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58701', '0.1667', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58702', '0.1667', '0', '0', '0');

-- Curse of Agony
INSERT INTO `spell_coef_override` VALUES ('980', '0', '0.10', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('1014', '0', '0.10', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6217', '0', '0.10', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11711', '0', '0.10', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11712', '0', '0.10', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11713', '0', '0.10', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27218', '0', '0.10', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47863', '0', '0.10', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47864', '0', '0.10', '0', '0');

-- Lightning Shield
INSERT INTO `spell_coef_override` VALUES ('324', '0.33', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('325', '0.33', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('905', '0.33', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('945', '0.33', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8134', '0.33', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10431', '0.33', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10432', '0.33', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25469', '0.33', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25472', '0.33', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49280', '0.33', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49281', '0.33', '0', '0', '0');

-- Seed of Corruption
INSERT INTO `spell_coef_override` VALUES ('27243', '0.2129', '0.25', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47835', '0.2129', '0.25', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47836', '0.2129', '0.25', '0', '0');

-- Flametongue Weapon
INSERT INTO `spell_coef_override` VALUES ('8026', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8028', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8029', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10445', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('16343', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('16344', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25488', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58786', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58787', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58788', '0.1', '0', '0', '0');

-- Frostbrand Weapon
INSERT INTO `spell_coef_override` VALUES ('8034', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8037', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10458', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('16352', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('16353', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25501', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58797', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58798', '0.1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('58799', '0.1', '0', '0', '0');

-- Drain Life
INSERT INTO `spell_coef_override` VALUES ('689', '0.1430', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('699', '0.1430', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('709', '0.1430', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('7651', '0.1430', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11699', '0.1430', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11700', '0.1430', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27219', '0.1430', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27220', '0.1430', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47857', '0.1430', '0', '0', '0');

-- Seal of the Martyr
INSERT INTO `spell_coef_override` VALUES ('53719', '0.25', '0', '0', '0');

-- Riptide
INSERT INTO `spell_coef_override` VALUES ('61295', '0.4', '0.18', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('61299', '0.4', '0.18', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('61300', '0.4', '0.18', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('61301', '0.4', '0.18', '0', '0');

-- Blast Wave
INSERT INTO `spell_coef_override` VALUES ('11113', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('13018', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('13019', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('13020', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('13021', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27133', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('33933', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42944', '0.1936', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42945', '0.1936', '0', '0', '0');

-- Shadowfiend
-- INSERT INTO `spell_coef_override` VALUES ('0', 'Shadowfiend', '0.65', '0', '0', '0');

-- Typhoon
INSERT INTO `spell_coef_override` VALUES ('50516', '0.193', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53223', '0.193', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53225', '0.193', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53226', '0.193', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('61384', '0.193', '0', '0', '0');

-- Mana Shield
INSERT INTO `spell_coef_override` VALUES ('1463', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8494', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8495', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10191', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10192', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10193', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27131', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('43019', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('43020', '0', '0.8053', '0', '0');

-- Health Funnel
INSERT INTO `spell_coef_override` VALUES ('755', '0', '0.4485', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('3698', '0', '0.4485', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('3699', '0', '0.4485', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('3700', '0', '0.4485', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11693', '0', '0.4485', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11694', '0', '0.4485', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11695', '0', '0.4485', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27259', '0', '0.4485', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47856', '0', '0.4485', '0', '0');

-- Searing Pain
INSERT INTO `spell_coef_override` VALUES ('5676', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17919', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17920', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17921', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17922', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17923', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27210', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('30459', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47814', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47815', '0.4293', '0', '0', '0');

-- Curse of Doom
INSERT INTO `spell_coef_override` VALUES ('603', '0', '2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('30910', '0', '2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47867', '0', '2', '0', '0');

-- Lava Burst
INSERT INTO `spell_coef_override` VALUES ('51505', '0.5714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('60043', '0.5714', '0', '0', '0');

-- Greater Heal
INSERT INTO `spell_coef_override` VALUES ('2060', '1.6135', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10963', '1.6135', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10964', '1.6135', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10965', '1.6135', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25314', '1.6135', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25210', '1.6135', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25213', '1.6135', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48062', '1.6135', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48063', '1.6135', '0', '0', '0');

-- Shadow Word: Pain
INSERT INTO `spell_coef_override` VALUES ('589', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('594', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('970', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('992', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('2767', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10892', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10893', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10894', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25367', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25368', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48124', '0', '0.1829', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48125', '0', '0.1829', '0', '0');

-- Fireball
INSERT INTO `spell_coef_override` VALUES ('133', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('143', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('145', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('3140', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8400', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8401', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8402', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10148', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10149', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10150', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10151', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25306', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27070', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('38692', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42832', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42833', '1', '0', '0', '0');

-- Haunt
INSERT INTO `spell_coef_override` VALUES ('48181', '0.4793', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('59161', '0.4793', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('59163', '0.4793', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('59164', '0.4793', '0', '0', '0');

-- Frostbolt
INSERT INTO `spell_coef_override` VALUES ('116', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('205', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('837', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('7322', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8406', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8407', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8408', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10179', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10180', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10181', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25304', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27071', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27072', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('38697', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42841', '0.8143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42842', '0.8143', '0', '0', '0');

-- Soul Fire
INSERT INTO `spell_coef_override` VALUES ('6353', '1.15', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17924', '1.15', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27211', '1.15', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27211', '1.15', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47824', '1.15', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47825', '1.15', '0', '0', '0');

-- Entangling Roots
INSERT INTO `spell_coef_override` VALUES ('339', '0', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('1062', '0', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5195', '0', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5196', '0', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9852', '0', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9853', '0', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26989', '0', '0.1', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53308', '0', '0.1', '0', '0');

-- Unstable Affliction - dot
INSERT INTO `spell_coef_override` VALUES ('30108', '0', '0.20', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('30404', '0', '0.20', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('30405', '0', '0.20', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47841', '0', '0.20', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47843', '0', '0.20', '0', '0');

-- Unstable Affliction - DD
INSERT INTO `spell_coef_override` VALUES ('31117', '1.8', '0', '0', '0');

-- Healing Wave
INSERT INTO `spell_coef_override` VALUES ('331', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('332', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('547', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('913', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('933', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('953', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8005', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10395', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10396', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25357', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25391', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25396', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49272', '1.6106', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49273', '1.6106', '0', '0', '0');

-- Lesser Healing Wave
INSERT INTO `spell_coef_override` VALUES ('8004', '0.8082', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8008', '0.8082', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8010', '0.8082', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10466', '0.8082', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10467', '0.8082', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10468', '0.8082', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25420', '0.8082', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49275', '0.8082', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49276', '0.8082', '0', '0', '0');

-- Rejuvenation
INSERT INTO `spell_coef_override` VALUES ('774', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('1058', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('1430', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('2090', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('2091', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('3627', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8910', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9839', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9840', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9841', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25299', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26981', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26982', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48440', '1.88', '0.37604', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48441', '1.88', '0.37604', '0', '0');

-- Chain Lightning
INSERT INTO `spell_coef_override` VALUES ('421', '0.4', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('930', '0.4', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('2860', '0.4', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10605', '0.4', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25439', '0.4', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25442', '0.4', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49270', '0.4', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49271', '0.4', '0', '0', '0');

-- Frostfire Bolt
INSERT INTO `spell_coef_override` VALUES ('44614', '0.8571', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47610', '0.8571', '0', '0', '0');

-- Flash Heal
INSERT INTO `spell_coef_override` VALUES ('2061', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9472', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9473', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9474', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10915', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10916', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10917', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25233', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25235', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48070', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48071', '0.8068', '0', '0', '0');

-- Holy Light
INSERT INTO `spell_coef_override` VALUES ('635', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('639', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('647', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('1026', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('1042', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('3472', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10328', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10329', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25292', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27135', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27136', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48781', '1.66', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48782', '1.66', '0', '0', '0');

-- Earth Shield
INSERT INTO `spell_coef_override` VALUES ('974', '0.4761', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('32593', '0.4761', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('32594', '0.4761', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49283', '0.4761', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49284', '0.4761', '0', '0', '0');

-- Immolate
INSERT INTO `spell_coef_override` VALUES ('348', '0.2', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('707', '0.2', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('1094', '0.2', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('2941', '0.2', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11665', '0.2', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11667', '0.2', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11668', '0.2', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25309', '0.2', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27215', '0.2', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47810', '0.2', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47811', '0.2', '0.2', '0', '0');

-- Cone of Cold
INSERT INTO `spell_coef_override` VALUES ('120', '0.214', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8492', '0.214', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10159', '0.214', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10160', '0.214', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10161', '0.214', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27087', '0.214', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42930', '0.214', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42931', '0.214', '0', '0', '0');

-- Death Coil
INSERT INTO `spell_coef_override` VALUES ('6789', '0.2140', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17925', '0.2140', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17926', '0.2140', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27223', '0.2140', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47859', '0.2140', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47860', '0.2140', '0', '0', '0');

-- Moonfire
INSERT INTO `spell_coef_override` VALUES ('8921', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8924', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8925', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8926', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8927', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8928', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8929', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8933', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8934', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8935', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26987', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26988', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48462', '0.1515', '0.13', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48463', '0.1515', '0.13', '0', '0');

-- Consecration
INSERT INTO `spell_coef_override` VALUES ('26573', '0.04', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('20116', '0.04', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('20922', '0.04', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('20923', '0.04', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('20924', '0.04', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27173', '0.04', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48818', '0.04', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48819', '0.04', '0', '0', '0');

-- Starfire
INSERT INTO `spell_coef_override` VALUES ('2912', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8949', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8950', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8951', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9875', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9876', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25298', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26986', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48464', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48465', '1', '0', '0', '0');

-- Healing Touch
INSERT INTO `spell_coef_override` VALUES ('5185', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5186', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5187', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5188', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('5189', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6778', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8903', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9758', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9888', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('9889', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25297', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26978', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('26979', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48377', '1.6104', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48378', '1.6104', '0', '0', '0');

-- Prayer of Mending
INSERT INTO `spell_coef_override` VALUES ('41637', '0.8068', '0', '0', '0');

-- Flash of Light
INSERT INTO `spell_coef_override` VALUES ('19750', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19939', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19940', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19941', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19942', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('19943', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27137', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48784', '1', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48785', '1', '0', '0', '0');

-- Smite
INSERT INTO `spell_coef_override` VALUES ('585', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('591', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('598', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('984', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('1004', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6060', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10933', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10934', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25363', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25364', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48122', '0.714', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48123', '0.714', '0', '0', '0');

-- Frost Nova
INSERT INTO `spell_coef_override` VALUES ('122', '0.193', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('856', '0.193', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6131', '0.193', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10230', '0.193', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27088', '0.193', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42917', '0.193', '0', '0', '0');

-- Dark Pact
INSERT INTO `spell_coef_override` VALUES ('18220', '0.96', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('18937', '0.96', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('18938', '0.96', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27265', '0.96', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('59092', '0.96', '0', '0', '0');

-- Mind Flay
INSERT INTO `spell_coef_override` VALUES ('15407', '0', '0.257', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17311', '0', '0.257', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17312', '0', '0.257', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17313', '0', '0.257', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('17314', '0', '0.257', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('18807', '0', '0.257', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25387', '0', '0.257', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48155', '0', '0.257', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48156', '0', '0.257', '0', '0');

-- Wild Growth
INSERT INTO `spell_coef_override` VALUES ('48438', '0', '0.11505', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53248', '0', '0.11505', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53249', '0', '0.11505', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53251', '0', '0.11505', '0', '0');

-- Fire Blast
INSERT INTO `spell_coef_override` VALUES ('2136', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('2137', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('2138', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8412', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8413', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10197', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10199', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27078', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27079', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42872', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42873', '0.4286', '0', '0', '0');

-- Hellfire
INSERT INTO `spell_coef_override` VALUES ('1949', '0', '0.12', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11683', '0', '0.12', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11684', '0', '0.12', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27213', '0', '0.12', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47823', '0', '0.12', '0', '0');

-- Prayer of Healing
INSERT INTO `spell_coef_override` VALUES ('596', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('996', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10960', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10961', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25316', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25308', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48072', '0.8068', '0', '0', '0');

-- Lightning Bolt
INSERT INTO `spell_coef_override` VALUES ('403', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('529', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('548', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('915', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('943', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6041', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10391', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10392', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15207', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15208', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25448', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25449', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49237', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('49238', '0.7143', '0', '0', '0');

-- Holy Fire
INSERT INTO `spell_coef_override` VALUES ('14914', '0.5711', '0.024', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15262', '0.5711', '0.024', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15263', '0.5711', '0.024', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15264', '0.5711', '0.024', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15265', '0.5711', '0.024', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15266', '0.5711', '0.024', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15267', '0.5711', '0.024', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15261', '0.5711', '0.024', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25384', '0.5711', '0.024', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48134', '0.5711', '0.024', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48135', '0.5711', '0.024', '0', '0');

-- Ice Lance
INSERT INTO `spell_coef_override` VALUES ('30455', '0.1429', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42913', '0.1429', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42914', '0.1429', '0', '0', '0');

-- Scorch
INSERT INTO `spell_coef_override` VALUES ('2948', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8444', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8445', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8446', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10205', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10206', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10207', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27073', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27074', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42858', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42859', '0.4286', '0', '0', '0');

-- Arcane Barrage
INSERT INTO `spell_coef_override` VALUES ('44425', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('44780', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('44781', '0.7143', '0', '0', '0');

-- Starfall - DD
INSERT INTO `spell_coef_override` VALUES ('50288', '0.05', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53191', '0.05', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53194', '0.05', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53195', '0.05', '0', '0', '0');

-- Starfall - AOE
INSERT INTO `spell_coef_override` VALUES ('50294', '0.012', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53188', '0.012', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53189', '0.012', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53190', '0.012', '0', '0', '0');

-- Power Word: Shield
INSERT INTO `spell_coef_override` VALUES ('17', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('592', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('600', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('3747', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6065', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6066', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10898', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10899', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10900', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10901', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25217', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25218', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48065', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48066', '0.8068', '0', '0', '0');

-- Vampiric Touch
INSERT INTO `spell_coef_override` VALUES ('34914', '0', '0.4', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('34916', '0', '0.4', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('34917', '0', '0.4', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48159', '0', '0.4', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48160', '0', '0.4', '0', '0');

-- Shadow Word: Death
INSERT INTO `spell_coef_override` VALUES ('32379', '0.4296', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('32996', '0.4296', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48157', '0.4296', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48158', '0.4296', '0', '0', '0');

-- Pyroblast
INSERT INTO `spell_coef_override` VALUES ('11366', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('12505', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('12522', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('12523', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('12524', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('12525', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('12526', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('18809', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27132', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('33938', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42890', '1.15', '0.05', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42891', '1.15', '0.05', '0', '0');

-- Binding Heal
INSERT INTO `spell_coef_override` VALUES ('32546', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48119', '0.8068', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48120', '0.8068', '0', '0', '0');

-- Drain Soul
INSERT INTO `spell_coef_override` VALUES ('1120', '0', '0.4290', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8288', '0', '0.4290', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8289', '0', '0.4290', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11675', '0', '0.4290', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27217', '0', '0.4290', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47855', '0', '0.4290', '0', '0');

-- Shadowburn
INSERT INTO `spell_coef_override` VALUES ('17877', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('18867', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('18868', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('18869', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('18870', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('18871', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27263', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('30546', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47826', '0.4293', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47827', '0.4293', '0', '0', '0');

-- Conflagrate
INSERT INTO `spell_coef_override` VALUES ('17962', '0.4293', '0', '0', '0');

-- Ice Barrier
INSERT INTO `spell_coef_override` VALUES ('11426', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('13031', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('13032', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('13033', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27134', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('33405', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('43038', '0', '0.8053', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('43039', '0', '0.8053', '0', '0');

-- Mind Blast
INSERT INTO `spell_coef_override` VALUES ('8092', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8102', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8103', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8104', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8105', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8106', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10945', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10946', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10947', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25372', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25375', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48126', '0.428', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48127', '0.428', '0', '0', '0');

-- Mind Sear
INSERT INTO `spell_coef_override` VALUES ('49821', '0.7143', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('53022', '0.7143', '0', '0', '0');

-- Corruption
INSERT INTO `spell_coef_override` VALUES ('172', '0', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6222', '0', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('6223', '0', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('7648', '0', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11671', '0', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('11672', '0', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25311', '0', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27216', '0', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47812', '0', '0.2', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('47813', '0', '0.2', '0', '0');

-- Hurricane
INSERT INTO `spell_coef_override` VALUES ('42231', '0.12898', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42232', '0.12898', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42233', '0.12898', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42230', '0.12898', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48466', '0.12898', '0', '0', '0');

-- Insect Swarm
INSERT INTO `spell_coef_override` VALUES ('5570', '0.127', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('24974', '0.127', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('24975', '0.127', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('24976', '0.127', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('24977', '0.127', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27013', '0.127', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48468', '0.127', '0', '0', '0');

-- Arcane Explosion
INSERT INTO `spell_coef_override` VALUES ('1449', '0.2128', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8437', '0.2128', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8438', '0.2128', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('8439', '0.2128', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10201', '0.2128', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('10202', '0.2128', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27080', '0.2128', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27082', '0.2128', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42920', '0.2128', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('42921', '0.2128', '0', '0', '0');

-- Rip
INSERT INTO `spell_coef_override` VALUES ('1079', '0', '0', '0.01', '0');
INSERT INTO `spell_coef_override` VALUES ('9492', '0', '0', '0.01', '0');
INSERT INTO `spell_coef_override` VALUES ('9493', '0', '0', '0.01', '0');
INSERT INTO `spell_coef_override` VALUES ('9752', '0', '0', '0.01', '0');
INSERT INTO `spell_coef_override` VALUES ('9894', '0', '0', '0.01', '0');
INSERT INTO `spell_coef_override` VALUES ('9896', '0', '0', '0.01', '0');
INSERT INTO `spell_coef_override` VALUES ('27008', '0', '0', '0.01', '0');
INSERT INTO `spell_coef_override` VALUES ('49799', '0', '0', '0.01', '0');
INSERT INTO `spell_coef_override` VALUES ('49800', '0', '0', '0.01', '0');

-- Faerie Fire (Feral)
INSERT INTO `spell_coef_override` VALUES ('60089', '0', '0', '0.05', '0');

-- Lacerate
INSERT INTO `spell_coef_override` VALUES ('33745', '0', '0', '0.01', '0');
INSERT INTO `spell_coef_override` VALUES ('48567', '0', '0', '0.01', '0');
INSERT INTO `spell_coef_override` VALUES ('48567', '0', '0', '0.01', '0');

-- Savage Defense
INSERT INTO `spell_coef_override` VALUES ('62606', '0', '0', '0.25', '0');

-- Arcane Shot
INSERT INTO `spell_coef_override` VALUES ('3044', '0', '0', '0', '0.15');
INSERT INTO `spell_coef_override` VALUES ('14281', '0', '0', '0', '0.15');
INSERT INTO `spell_coef_override` VALUES ('14282', '0', '0', '0', '0.15');
INSERT INTO `spell_coef_override` VALUES ('14283', '0', '0', '0', '0.15');
INSERT INTO `spell_coef_override` VALUES ('14284', '0', '0', '0', '0.15');
INSERT INTO `spell_coef_override` VALUES ('14285', '0', '0', '0', '0.15');
INSERT INTO `spell_coef_override` VALUES ('14286', '0', '0', '0', '0.15');
INSERT INTO `spell_coef_override` VALUES ('14287', '0', '0', '0', '0.15');
INSERT INTO `spell_coef_override` VALUES ('27019', '0', '0', '0', '0.15');
INSERT INTO `spell_coef_override` VALUES ('49044', '0', '0', '0', '0.15');
INSERT INTO `spell_coef_override` VALUES ('49045', '0', '0', '0', '0.15');

-- Kill Shot
INSERT INTO `spell_coef_override` VALUES ('53351', '0', '0', '0', '0.40');
INSERT INTO `spell_coef_override` VALUES ('61005', '0', '0', '0', '0.40');
INSERT INTO `spell_coef_override` VALUES ('61006', '0', '0', '0', '0.40');

-- Multi-Shot
INSERT INTO `spell_coef_override` VALUES ('2643', '0', '0', '0', '0.20');
INSERT INTO `spell_coef_override` VALUES ('14288', '0', '0', '0', '0.20');
INSERT INTO `spell_coef_override` VALUES ('14289', '0', '0', '0', '0.20');
INSERT INTO `spell_coef_override` VALUES ('14290', '0', '0', '0', '0.20');
INSERT INTO `spell_coef_override` VALUES ('25294', '0', '0', '0', '0.20');
INSERT INTO `spell_coef_override` VALUES ('27021', '0', '0', '0', '0.20');
INSERT INTO `spell_coef_override` VALUES ('49047', '0', '0', '0', '0.20');
INSERT INTO `spell_coef_override` VALUES ('49048', '0', '0', '0', '0.20');

-- Serpent Sting
INSERT INTO `spell_coef_override` VALUES ('1978', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('13549', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('13550', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('13551', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('13552', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('13553', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('13554', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('13555', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('25295', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('27016', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('49000', '0', '0', '0', '0.04');
INSERT INTO `spell_coef_override` VALUES ('49001', '0', '0', '0', '0.04');

-- Steady Shot
INSERT INTO `spell_coef_override` VALUES ('56641', '0', '0', '0', '0.10');
INSERT INTO `spell_coef_override` VALUES ('34120', '0', '0', '0', '0.10');
INSERT INTO `spell_coef_override` VALUES ('49051', '0', '0', '0', '0.10');
INSERT INTO `spell_coef_override` VALUES ('49052', '0', '0', '0', '0.10');

-- Explosive Shot
INSERT INTO `spell_coef_override` VALUES ('53301', '0', '0', '0', '0.16');
INSERT INTO `spell_coef_override` VALUES ('60051', '0', '0', '0', '0.16');
INSERT INTO `spell_coef_override` VALUES ('60052', '0', '0', '0', '0.16');
INSERT INTO `spell_coef_override` VALUES ('60053', '0', '0', '0', '0.16');

-- Immolation Trap
INSERT INTO `spell_coef_override` VALUES ('13797', '0', '0', '0', '0.02');
INSERT INTO `spell_coef_override` VALUES ('14298', '0', '0', '0', '0.02');
INSERT INTO `spell_coef_override` VALUES ('14299', '0', '0', '0', '0.02');
INSERT INTO `spell_coef_override` VALUES ('14300', '0', '0', '0', '0.02');
INSERT INTO `spell_coef_override` VALUES ('14301', '0', '0', '0', '0.02');
INSERT INTO `spell_coef_override` VALUES ('27024', '0', '0', '0', '0.02');
INSERT INTO `spell_coef_override` VALUES ('49053', '0', '0', '0', '0.02');
INSERT INTO `spell_coef_override` VALUES ('49054', '0', '0', '0', '0.02');

-- Mongoose Bite
INSERT INTO `spell_coef_override` VALUES ('1495', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('14269', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('14270', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('14271', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('36916', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('53339', '0', '0', '0.20', '0');


-- Avenger's Shield
INSERT INTO `spell_coef_override` VALUES ('31935', '0.07', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('32699', '0.07', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('32700', '0.07', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('48826', '0.07', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('48827', '0.07', '0', '0.07', '0');

-- Consecration
INSERT INTO `spell_coef_override` VALUES ('26573', '0', '0.04', '0.04', '0');
INSERT INTO `spell_coef_override` VALUES ('20116', '0', '0.04', '0.04', '0');
INSERT INTO `spell_coef_override` VALUES ('20922', '0', '0.04', '0.04', '0');
INSERT INTO `spell_coef_override` VALUES ('20923', '0', '0.04', '0.04', '0');
INSERT INTO `spell_coef_override` VALUES ('20924', '0', '0.04', '0.04', '0');
INSERT INTO `spell_coef_override` VALUES ('27173', '0', '0.04', '0.04', '0');
INSERT INTO `spell_coef_override` VALUES ('48818', '0', '0.04', '0.04', '0');
INSERT INTO `spell_coef_override` VALUES ('48819', '0', '0.04', '0.04', '0');

-- Exorcism
INSERT INTO `spell_coef_override` VALUES ('879', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('5614', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('5615', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('10312', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('10313', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('10314', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('27138', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('48800', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('48801', '0.15', '0', '0.15', '0');

-- Hammer of Wrath
INSERT INTO `spell_coef_override` VALUES ('24275', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('24274', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('24239', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('27180', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('48805', '0.15', '0', '0.15', '0');
INSERT INTO `spell_coef_override` VALUES ('48806', '0.15', '0', '0.15', '0');

-- Hand of Reckoning
INSERT INTO `spell_coef_override` VALUES ('62124', '0.085', '0', '0', '0');

-- Holy Shield
INSERT INTO `spell_coef_override` VALUES ('20925', '0.09', '0', '0.056', '0');
INSERT INTO `spell_coef_override` VALUES ('20927', '0.09', '0', '0.056', '0');
INSERT INTO `spell_coef_override` VALUES ('20928', '0.09', '0', '0.056', '0');
INSERT INTO `spell_coef_override` VALUES ('27179', '0.09', '0', '0.056', '0');
INSERT INTO `spell_coef_override` VALUES ('48951', '0.09', '0', '0.056', '0');
INSERT INTO `spell_coef_override` VALUES ('48952', '0.09', '0', '0.056', '0');

-- Holy Wrath
INSERT INTO `spell_coef_override` VALUES ('2812', '0.07', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('10318', '0.07', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('27139', '0.07', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('48816', '0.07', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('48817', '0.07', '0', '0.07', '0');

-- Seal of Command
INSERT INTO `spell_coef_override` VALUES ('20424', '0.23', '0', '0', '0');

-- Seal of Blood
INSERT INTO `spell_coef_override` VALUES ('31893', '0', '0.02', '0.03', '0');

-- Seal of Vengeance
INSERT INTO `spell_coef_override` VALUES ('31803', '0', '0.025', '0.05', '0');

-- Seal of Corruption
INSERT INTO `spell_coef_override` VALUES ('53742', '0', '0.025', '0.05', '0');

-- Seal of Righteousnes
INSERT INTO `spell_coef_override` VALUES ('21084', '0.07', '0', '0.039', '0');

-- Judgement of Righteousness
INSERT INTO `spell_coef_override` VALUES ('20187', '0.4', '0', '0.25', '0');

-- Judgement of Blood
INSERT INTO `spell_coef_override` VALUES ('31898', '0.25', '0', '0.16', '0');

-- Judgement of the Martyr
INSERT INTO `spell_coef_override` VALUES ('53726', '0.25', '0', '0.16', '0');

-- Judgement of Vengeance
INSERT INTO `spell_coef_override` VALUES ('31804', '0.22', '0', '0.14', '0');

-- Judgement of Wisdom/Judgement of Light/Judgement of Justice (seals, custom unused spell)
INSERT INTO `spell_coef_override` VALUES ('53733', '0.25', '0', '0.16', '0');

-- Judgement of Light
INSERT INTO `spell_coef_override` VALUES ('20267', '0.10', '0', '0.10', '0');

-- Judgement of Command
INSERT INTO `spell_coef_override` VALUES ('20467', '0.25', '0', '0.16', '0');

-- Sacred Shield
INSERT INTO `spell_coef_override` VALUES ('58597', '0.75', '0', '0', '0');

-- Holy Shock - DMG
INSERT INTO `spell_coef_override` VALUES ('25912', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25911', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25902', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27176', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('33073', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48822', '0.4286', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48823', '0.4286', '0', '0', '0');

-- Holy Shock - HEAL
INSERT INTO `spell_coef_override` VALUES ('25914', '0.81', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25913', '0.81', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25903', '0.81', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27175', '0.81', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('33074', '0.81', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48820', '0.81', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48821', '0.81', '0', '0', '0');

-- Shamanistic Rage
INSERT INTO `spell_coef_override` VALUES ('30824', '0', '0', '0.30', '0');

-- Heroic Throw
INSERT INTO `spell_coef_override` VALUES ('57755', '0', '0', '0.50', '0');

-- Thunder Clap
INSERT INTO `spell_coef_override` VALUES ('6343', '0', '0', '0.12', '0');
INSERT INTO `spell_coef_override` VALUES ('8198', '0', '0', '0.12', '0');
INSERT INTO `spell_coef_override` VALUES ('8204', '0', '0', '0.12', '0');
INSERT INTO `spell_coef_override` VALUES ('8205', '0', '0', '0.12', '0');
INSERT INTO `spell_coef_override` VALUES ('11580', '0', '0', '0.12', '0');
INSERT INTO `spell_coef_override` VALUES ('11581', '0', '0', '0.12', '0');
INSERT INTO `spell_coef_override` VALUES ('25264', '0', '0', '0.12', '0');
INSERT INTO `spell_coef_override` VALUES ('47501', '0', '0', '0.12', '0');
INSERT INTO `spell_coef_override` VALUES ('47502', '0', '0', '0.12', '0');

-- Execute
INSERT INTO `spell_coef_override` VALUES ('5308', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('20658', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('20660', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('20661', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('20662', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('25234', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('25236', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('47470', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('47471', '0', '0', '0.20', '0');

-- Intercept
INSERT INTO `spell_coef_override` VALUES ('20252', '0', '0', '0.12', '0');

-- Victory Rush
INSERT INTO `spell_coef_override` VALUES ('34428', '0', '0', '0.45', '0');

-- Revenge
INSERT INTO `spell_coef_override` VALUES ('6572', '0', '0', '0.207', '0');
INSERT INTO `spell_coef_override` VALUES ('6574', '0', '0', '0.207', '0');
INSERT INTO `spell_coef_override` VALUES ('7379', '0', '0', '0.207', '0');
INSERT INTO `spell_coef_override` VALUES ('11600', '0', '0', '0.207', '0');
INSERT INTO `spell_coef_override` VALUES ('11601', '0', '0', '0.207', '0');
INSERT INTO `spell_coef_override` VALUES ('25288', '0', '0', '0.207', '0');
INSERT INTO `spell_coef_override` VALUES ('25269', '0', '0', '0.207', '0');
INSERT INTO `spell_coef_override` VALUES ('30357', '0', '0', '0.207', '0');
INSERT INTO `spell_coef_override` VALUES ('57823', '0', '0', '0.207', '0');

-- Holy Nova - Heal
INSERT INTO `spell_coef_override` VALUES ('23455', '0.3035', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('23458', '0.3035', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('23459', '0.3035', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27803', '0.3035', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27804', '0.3035', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27805', '0.3035', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25329', '0.3035', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48075', '0.3035', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48076', '0.3035', '0', '0', '0');

-- Holy Nova - Damage
INSERT INTO `spell_coef_override` VALUES ('15237', '0.1606', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15430', '0.1606', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('15431', '0.1606', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27799', '0.1606', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27800', '0.1606', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('27801', '0.1606', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('25331', '0.1606', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48077', '0.1606', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('48078', '0.1606', '0', '0', '0');

-- Penance Heal
INSERT INTO `spell_coef_override` VALUES ('47750', '0.535', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('52983', '0.535', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('52984', '0.535', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('52985', '0.535', '0', '0', '0');

-- Chaos Bolt
INSERT INTO `spell_coef_override` VALUES ('50796', '0.7139', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('59170', '0.7139', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('59171', '0.7139', '0', '0', '0');
INSERT INTO `spell_coef_override` VALUES ('59172', '0.7139', '0', '0', '0');

-- Immolation Aura
INSERT INTO `spell_coef_override` VALUES ('50590', '0.1622', '0', '0', '0');


-- Garrote
INSERT INTO `spell_coef_override` VALUES ('703', '0', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('8631', '0', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('8632', '0', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('8633', '0', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('11289', '0', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('11290', '0', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('26839', '0', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('26884', '0', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('48675', '0', '0', '0.07', '0');
INSERT INTO `spell_coef_override` VALUES ('48676', '0', '0', '0.07', '0');

-- Gouge
INSERT INTO `spell_coef_override` VALUES ('1776', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('1777', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('8629', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('11285', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('11286', '0', '0', '0.20', '0');
INSERT INTO `spell_coef_override` VALUES ('38764', '0', '0', '0.20', '0');

-- Concussion Blow
INSERT INTO `spell_coef_override` VALUES ('12809', '0', '0', '0.75', '0');

-- Shockwave
INSERT INTO `spell_coef_override` VALUES ('46968', '0', '0', '0.75', '0');

-- Bloodthirst
INSERT INTO `spell_coef_override` VALUES ('23881', '0', '0', '0.50', '0');

-- Instant Poison
INSERT INTO `spell_coef_override` VALUES ('8680', '0', '0', '0.10', '0');
INSERT INTO `spell_coef_override` VALUES ('8685', '0', '0', '0.10', '0');
INSERT INTO `spell_coef_override` VALUES ('8689', '0', '0', '0.10', '0');
INSERT INTO `spell_coef_override` VALUES ('11335', '0', '0', '0.10', '0');
INSERT INTO `spell_coef_override` VALUES ('11336', '0', '0', '0.10', '0');
INSERT INTO `spell_coef_override` VALUES ('11337', '0', '0', '0.10', '0');
INSERT INTO `spell_coef_override` VALUES ('26890', '0', '0', '0.10', '0');
INSERT INTO `spell_coef_override` VALUES ('57964', '0', '0', '0.10', '0');
INSERT INTO `spell_coef_override` VALUES ('57965', '0', '0', '0.10', '0');

-- Deadly Poison
INSERT INTO `spell_coef_override` VALUES ('2818', '0', '0', '0.024', '0');
INSERT INTO `spell_coef_override` VALUES ('2819', '0', '0', '0.024', '0');
INSERT INTO `spell_coef_override` VALUES ('11353', '0', '0', '0.024', '0');
INSERT INTO `spell_coef_override` VALUES ('11354', '0', '0', '0.024', '0');
INSERT INTO `spell_coef_override` VALUES ('25349', '0', '0', '0.024', '0');
INSERT INTO `spell_coef_override` VALUES ('26968', '0', '0', '0.024', '0');
INSERT INTO `spell_coef_override` VALUES ('27187', '0', '0', '0.024', '0');
INSERT INTO `spell_coef_override` VALUES ('57969', '0', '0', '0.024', '0');
INSERT INTO `spell_coef_override` VALUES ('57970', '0', '0', '0.024', '0');

-- Wound Poison
INSERT INTO `spell_coef_override` VALUES ('13218', '0', '0', '0.008', '0');
INSERT INTO `spell_coef_override` VALUES ('13222', '0', '0', '0.008', '0');
INSERT INTO `spell_coef_override` VALUES ('13223', '0', '0', '0.008', '0');
INSERT INTO `spell_coef_override` VALUES ('13224', '0', '0', '0.008', '0');
INSERT INTO `spell_coef_override` VALUES ('27189', '0', '0', '0.008', '0');
INSERT INTO `spell_coef_override` VALUES ('57974', '0', '0', '0.008', '0');
INSERT INTO `spell_coef_override` VALUES ('57975', '0', '0', '0.008', '0');

-- Gore
INSERT INTO `spell_coef_override` VALUES ('35290', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('35291', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('35292', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('35293', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('35294', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('35295', '0', '0', '0', '0.125');

-- Lighting Breath
INSERT INTO `spell_coef_override` VALUES ('24844', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('25008', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('25009', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('25010', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('25011', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('25012', '0', '0', '0', '0.125');

-- Claw
INSERT INTO `spell_coef_override` VALUES ('16827', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('16828', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('16829', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('16830', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('16831', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('16832', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('3010', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('3009', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('27049', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('52471', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('52472', '0', '0', '0', '0.125');

-- Poison Spit
INSERT INTO `spell_coef_override` VALUES ('35387', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('35389', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('35392', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('55555', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('55556', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('55557', '0', '0', '0', '0.125');

-- Fire Breath
INSERT INTO `spell_coef_override` VALUES ('34889', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('35323', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('55482', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('55483', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('55484', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('55485', '0', '0', '0', '0.125');

-- Bite
INSERT INTO `spell_coef_override` VALUES ('17253', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('17255', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('17256', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('17257', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('17258', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('17259', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('17260', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('17261', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('27050', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('52473', '0', '0', '0', '0.125');
INSERT INTO `spell_coef_override` VALUES ('52474', '0', '0', '0', '0.125');

-- Scorpid Poison
INSERT INTO `spell_coef_override` VALUES ('24640', '0', '0', '0', '0.015');
INSERT INTO `spell_coef_override` VALUES ('24583', '0', '0', '0', '0.015');
INSERT INTO `spell_coef_override` VALUES ('24586', '0', '0', '0', '0.015');
INSERT INTO `spell_coef_override` VALUES ('24587', '0', '0', '0', '0.015');
INSERT INTO `spell_coef_override` VALUES ('27060', '0', '0', '0', '0.015');
INSERT INTO `spell_coef_override` VALUES ('55728', '0', '0', '0', '0.015');
-- ----------------------------
-- Table structure for spell_forced_targets
-- ----------------------------
DROP TABLE IF EXISTS `spell_forced_targets`;
CREATE TABLE `spell_forced_targets` (
  `spellid` int(8) unsigned NOT NULL,
  `target` int(8) unsigned NOT NULL DEFAULT '0',
  UNIQUE KEY `entry_type_target` (`spellid`,`target`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Spell System';

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `spell_forced_targets` VALUES ('7035', '4251');
INSERT INTO `spell_forced_targets` VALUES ('7036', '4252');
INSERT INTO `spell_forced_targets` VALUES ('7393', '15275');
INSERT INTO `spell_forced_targets` VALUES ('7393', '15276');
INSERT INTO `spell_forced_targets` VALUES ('8283', '4781');
INSERT INTO `spell_forced_targets` VALUES ('8593', '6172');
INSERT INTO `spell_forced_targets` VALUES ('8593', '6177');
INSERT INTO `spell_forced_targets` VALUES ('8593', '17542');
INSERT INTO `spell_forced_targets` VALUES ('9012', '6492');
INSERT INTO `spell_forced_targets` VALUES ('9082', '6492');
INSERT INTO `spell_forced_targets` VALUES ('9232', '3976');
INSERT INTO `spell_forced_targets` VALUES ('9257', '3977');
INSERT INTO `spell_forced_targets` VALUES ('9455', '2163');
INSERT INTO `spell_forced_targets` VALUES ('9712', '2726');
INSERT INTO `spell_forced_targets` VALUES ('9976', '7167');
INSERT INTO `spell_forced_targets` VALUES ('9976', '7168');
INSERT INTO `spell_forced_targets` VALUES ('9976', '8391');
INSERT INTO `spell_forced_targets` VALUES ('10113', '7233');
INSERT INTO `spell_forced_targets` VALUES ('10137', '7233');
INSERT INTO `spell_forced_targets` VALUES ('10260', '2748');
INSERT INTO `spell_forced_targets` VALUES ('10345', '25');
INSERT INTO `spell_forced_targets` VALUES ('10345', '2678');
INSERT INTO `spell_forced_targets` VALUES ('10348', '6225');
INSERT INTO `spell_forced_targets` VALUES ('10348', '6226');
INSERT INTO `spell_forced_targets` VALUES ('10348', '6227');
INSERT INTO `spell_forced_targets` VALUES ('10732', '25');
INSERT INTO `spell_forced_targets` VALUES ('10732', '2678');
INSERT INTO `spell_forced_targets` VALUES ('11402', '7774');
INSERT INTO `spell_forced_targets` VALUES ('11513', '6213');
INSERT INTO `spell_forced_targets` VALUES ('11513', '6329');
INSERT INTO `spell_forced_targets` VALUES ('11637', '6218');
INSERT INTO `spell_forced_targets` VALUES ('11637', '6219');
INSERT INTO `spell_forced_targets` VALUES ('11637', '6220');
INSERT INTO `spell_forced_targets` VALUES ('12151', '5273');
INSERT INTO `spell_forced_targets` VALUES ('12347', '8442');
INSERT INTO `spell_forced_targets` VALUES ('12623', '8443');
INSERT INTO `spell_forced_targets` VALUES ('12699', '5307');
INSERT INTO `spell_forced_targets` VALUES ('12699', '5308');
INSERT INTO `spell_forced_targets` VALUES ('12709', '6218');
INSERT INTO `spell_forced_targets` VALUES ('12709', '6219');
INSERT INTO `spell_forced_targets` VALUES ('12709', '6220');
INSERT INTO `spell_forced_targets` VALUES ('12774', '8662');
INSERT INTO `spell_forced_targets` VALUES ('12938', '7664');
INSERT INTO `spell_forced_targets` VALUES ('12938', '7668');
INSERT INTO `spell_forced_targets` VALUES ('13461', '7664');
INSERT INTO `spell_forced_targets` VALUES ('13951', '2520');
INSERT INTO `spell_forced_targets` VALUES ('13982', '9016');
INSERT INTO `spell_forced_targets` VALUES ('14247', '9376');
INSERT INTO `spell_forced_targets` VALUES ('14250', '9520');
INSERT INTO `spell_forced_targets` VALUES ('14806', '9157');
INSERT INTO `spell_forced_targets` VALUES ('14928', '9503');
INSERT INTO `spell_forced_targets` VALUES ('15281', '9816');
INSERT INTO `spell_forced_targets` VALUES ('15591', '9999');
INSERT INTO `spell_forced_targets` VALUES ('15998', '10221');
INSERT INTO `spell_forced_targets` VALUES ('16007', '7047');
INSERT INTO `spell_forced_targets` VALUES ('16007', '7048');
INSERT INTO `spell_forced_targets` VALUES ('16053', '175321');
INSERT INTO `spell_forced_targets` VALUES ('16378', '10541');
INSERT INTO `spell_forced_targets` VALUES ('16452', '10601');
INSERT INTO `spell_forced_targets` VALUES ('16452', '10602');
INSERT INTO `spell_forced_targets` VALUES ('16629', '1852');
INSERT INTO `spell_forced_targets` VALUES ('17048', '10899');
INSERT INTO `spell_forced_targets` VALUES ('17166', '7583');
INSERT INTO `spell_forced_targets` VALUES ('17166', '10977');
INSERT INTO `spell_forced_targets` VALUES ('17166', '10978');
INSERT INTO `spell_forced_targets` VALUES ('17179', '10508');
INSERT INTO `spell_forced_targets` VALUES ('17190', '10508');
INSERT INTO `spell_forced_targets` VALUES ('17536', '11218');
INSERT INTO `spell_forced_targets` VALUES ('17698', '11197');
INSERT INTO `spell_forced_targets` VALUES ('18666', '10937');
INSERT INTO `spell_forced_targets` VALUES ('19032', '12202');
INSERT INTO `spell_forced_targets` VALUES ('19250', '177668');
INSERT INTO `spell_forced_targets` VALUES ('19952', '11502');
INSERT INTO `spell_forced_targets` VALUES ('21794', '10981');
INSERT INTO `spell_forced_targets` VALUES ('21866', '10990');
INSERT INTO `spell_forced_targets` VALUES ('22906', '10184');
INSERT INTO `spell_forced_targets` VALUES ('23015', '12396');
INSERT INTO `spell_forced_targets` VALUES ('23019', '12396');
INSERT INTO `spell_forced_targets` VALUES ('23359', '5357');
INSERT INTO `spell_forced_targets` VALUES ('23359', '5358');
INSERT INTO `spell_forced_targets` VALUES ('23359', '5359');
INSERT INTO `spell_forced_targets` VALUES ('23359', '5360');
INSERT INTO `spell_forced_targets` VALUES ('23359', '5361');
INSERT INTO `spell_forced_targets` VALUES ('23394', '14601');
INSERT INTO `spell_forced_targets` VALUES ('24322', '14834');
INSERT INTO `spell_forced_targets` VALUES ('26235', '15727');
INSERT INTO `spell_forced_targets` VALUES ('27184', '16044');
INSERT INTO `spell_forced_targets` VALUES ('27190', '16045');
INSERT INTO `spell_forced_targets` VALUES ('27191', '16046');
INSERT INTO `spell_forced_targets` VALUES ('27201', '16047');
INSERT INTO `spell_forced_targets` VALUES ('27202', '16048');
INSERT INTO `spell_forced_targets` VALUES ('27203', '16044');
INSERT INTO `spell_forced_targets` VALUES ('27203', '16045');
INSERT INTO `spell_forced_targets` VALUES ('27203', '16046');
INSERT INTO `spell_forced_targets` VALUES ('27203', '16047');
INSERT INTO `spell_forced_targets` VALUES ('27203', '16048');
INSERT INTO `spell_forced_targets` VALUES ('27517', '16079');
INSERT INTO `spell_forced_targets` VALUES ('28806', '16592');
INSERT INTO `spell_forced_targets` VALUES ('28806', '181288');
INSERT INTO `spell_forced_targets` VALUES ('29120', '16899');
INSERT INTO `spell_forced_targets` VALUES ('29121', '16897');
INSERT INTO `spell_forced_targets` VALUES ('29122', '16898');
INSERT INTO `spell_forced_targets` VALUES ('29339', '15547');
INSERT INTO `spell_forced_targets` VALUES ('29339', '15548');
INSERT INTO `spell_forced_targets` VALUES ('29340', '15547');
INSERT INTO `spell_forced_targets` VALUES ('29340', '15548');
INSERT INTO `spell_forced_targets` VALUES ('29364', '16975');
INSERT INTO `spell_forced_targets` VALUES ('29435', '17034');
INSERT INTO `spell_forced_targets` VALUES ('29612', '16468');
INSERT INTO `spell_forced_targets` VALUES ('29989', '17178');
INSERT INTO `spell_forced_targets` VALUES ('30065', '15688');
INSERT INTO `spell_forced_targets` VALUES ('30098', '17253');
INSERT INTO `spell_forced_targets` VALUES ('30166', '17257');
INSERT INTO `spell_forced_targets` VALUES ('30207', '17257');
INSERT INTO `spell_forced_targets` VALUES ('30410', '17257');
INSERT INTO `spell_forced_targets` VALUES ('30427', '17378');
INSERT INTO `spell_forced_targets` VALUES ('30427', '17407');
INSERT INTO `spell_forced_targets` VALUES ('30427', '17408');
INSERT INTO `spell_forced_targets` VALUES ('30427', '24222');
INSERT INTO `spell_forced_targets` VALUES ('30462', '17404');
INSERT INTO `spell_forced_targets` VALUES ('30834', '17646');
INSERT INTO `spell_forced_targets` VALUES ('30875', '17326');
INSERT INTO `spell_forced_targets` VALUES ('30876', '17326');
INSERT INTO `spell_forced_targets` VALUES ('30877', '17326');
INSERT INTO `spell_forced_targets` VALUES ('30988', '17701');
INSERT INTO `spell_forced_targets` VALUES ('31225', '17768');
INSERT INTO `spell_forced_targets` VALUES ('31326', '15608');
INSERT INTO `spell_forced_targets` VALUES ('31333', '17664');
INSERT INTO `spell_forced_targets` VALUES ('31411', '17886');
INSERT INTO `spell_forced_targets` VALUES ('31412', '17886');
INSERT INTO `spell_forced_targets` VALUES ('31413', '17886');
INSERT INTO `spell_forced_targets` VALUES ('31414', '17886');
INSERT INTO `spell_forced_targets` VALUES ('31532', '17796');
INSERT INTO `spell_forced_targets` VALUES ('31537', '17895');
INSERT INTO `spell_forced_targets` VALUES ('31543', '17798');
INSERT INTO `spell_forced_targets` VALUES ('31736', '17998');
INSERT INTO `spell_forced_targets` VALUES ('31736', '17999');
INSERT INTO `spell_forced_targets` VALUES ('31736', '18000');
INSERT INTO `spell_forced_targets` VALUES ('31736', '18002');
INSERT INTO `spell_forced_targets` VALUES ('31927', '18110');
INSERT INTO `spell_forced_targets` VALUES ('31927', '18142');
INSERT INTO `spell_forced_targets` VALUES ('31927', '18143');
INSERT INTO `spell_forced_targets` VALUES ('31927', '18144');
INSERT INTO `spell_forced_targets` VALUES ('32042', '18161');
INSERT INTO `spell_forced_targets` VALUES ('32042', '18162');
INSERT INTO `spell_forced_targets` VALUES ('32045', '17968');
INSERT INTO `spell_forced_targets` VALUES ('32051', '17968');
INSERT INTO `spell_forced_targets` VALUES ('32052', '17968');
INSERT INTO `spell_forced_targets` VALUES ('32146', '18240');
INSERT INTO `spell_forced_targets` VALUES ('32163', '18247');
INSERT INTO `spell_forced_targets` VALUES ('32164', '18246');
INSERT INTO `spell_forced_targets` VALUES ('32205', '18305');
INSERT INTO `spell_forced_targets` VALUES ('32205', '18306');
INSERT INTO `spell_forced_targets` VALUES ('32205', '18307');
INSERT INTO `spell_forced_targets` VALUES ('32307', '17146');
INSERT INTO `spell_forced_targets` VALUES ('32307', '17147');
INSERT INTO `spell_forced_targets` VALUES ('32307', '17148');
INSERT INTO `spell_forced_targets` VALUES ('32307', '18397');
INSERT INTO `spell_forced_targets` VALUES ('32307', '18658');
INSERT INTO `spell_forced_targets` VALUES ('32314', '18393');
INSERT INTO `spell_forced_targets` VALUES ('32560', '17893');
INSERT INTO `spell_forced_targets` VALUES ('32622', '17545');
INSERT INTO `spell_forced_targets` VALUES ('32623', '18660');
INSERT INTO `spell_forced_targets` VALUES ('32838', '16899');
INSERT INTO `spell_forced_targets` VALUES ('32979', '18818');
INSERT INTO `spell_forced_targets` VALUES ('32979', '19009');
INSERT INTO `spell_forced_targets` VALUES ('32979', '21236');
INSERT INTO `spell_forced_targets` VALUES ('32979', '21237');
INSERT INTO `spell_forced_targets` VALUES ('33067', '18849');
INSERT INTO `spell_forced_targets` VALUES ('33067', '19008');
INSERT INTO `spell_forced_targets` VALUES ('33423', '19139');
INSERT INTO `spell_forced_targets` VALUES ('33424', '19139');
INSERT INTO `spell_forced_targets` VALUES ('33425', '19139');
INSERT INTO `spell_forced_targets` VALUES ('33531', '19067');
INSERT INTO `spell_forced_targets` VALUES ('33532', '19210');
INSERT INTO `spell_forced_targets` VALUES ('33796', '16898');
INSERT INTO `spell_forced_targets` VALUES ('33796', '19727');
INSERT INTO `spell_forced_targets` VALUES ('33805', '19387');
INSERT INTO `spell_forced_targets` VALUES ('33806', '19388');
INSERT INTO `spell_forced_targets` VALUES ('33822', '19394');
INSERT INTO `spell_forced_targets` VALUES ('33924', '19424');
INSERT INTO `spell_forced_targets` VALUES ('34062', '19484');
INSERT INTO `spell_forced_targets` VALUES ('34063', '18688');
INSERT INTO `spell_forced_targets` VALUES ('34239', '19599');
INSERT INTO `spell_forced_targets` VALUES ('34367', '19421');
INSERT INTO `spell_forced_targets` VALUES ('34387', '184289');
INSERT INTO `spell_forced_targets` VALUES ('34387', '184290');
INSERT INTO `spell_forced_targets` VALUES ('34387', '184414');
INSERT INTO `spell_forced_targets` VALUES ('34387', '184415');
INSERT INTO `spell_forced_targets` VALUES ('34397', '20139');
INSERT INTO `spell_forced_targets` VALUES ('34630', '19849');
INSERT INTO `spell_forced_targets` VALUES ('34646', '19866');
INSERT INTO `spell_forced_targets` VALUES ('34646', '19867');
INSERT INTO `spell_forced_targets` VALUES ('34646', '19868');
INSERT INTO `spell_forced_targets` VALUES ('34665', '16880');
INSERT INTO `spell_forced_targets` VALUES ('35016', '20209');
INSERT INTO `spell_forced_targets` VALUES ('35016', '20417');
INSERT INTO `spell_forced_targets` VALUES ('35016', '20418');
INSERT INTO `spell_forced_targets` VALUES ('35063', '20251');
INSERT INTO `spell_forced_targets` VALUES ('35097', '20251');
INSERT INTO `spell_forced_targets` VALUES ('35113', '20333');
INSERT INTO `spell_forced_targets` VALUES ('35113', '20336');
INSERT INTO `spell_forced_targets` VALUES ('35113', '20337');
INSERT INTO `spell_forced_targets` VALUES ('35113', '20338');
INSERT INTO `spell_forced_targets` VALUES ('35176', '20440');
INSERT INTO `spell_forced_targets` VALUES ('35246', '20473');
INSERT INTO `spell_forced_targets` VALUES ('35246', '20475');
INSERT INTO `spell_forced_targets` VALUES ('35246', '20476');
INSERT INTO `spell_forced_targets` VALUES ('35282', '20243');
INSERT INTO `spell_forced_targets` VALUES ('35289', '22963');
INSERT INTO `spell_forced_targets` VALUES ('35372', '20561');
INSERT INTO `spell_forced_targets` VALUES ('35413', '20781');
INSERT INTO `spell_forced_targets` VALUES ('35515', '20454');
INSERT INTO `spell_forced_targets` VALUES ('35683', '20769');
INSERT INTO `spell_forced_targets` VALUES ('35724', '20813');
INSERT INTO `spell_forced_targets` VALUES ('35724', '20814');
INSERT INTO `spell_forced_targets` VALUES ('35724', '20815');
INSERT INTO `spell_forced_targets` VALUES ('35724', '20816');
INSERT INTO `spell_forced_targets` VALUES ('35734', '20899');
INSERT INTO `spell_forced_targets` VALUES ('35771', '20610');
INSERT INTO `spell_forced_targets` VALUES ('35771', '20777');
INSERT INTO `spell_forced_targets` VALUES ('35772', '20774');
INSERT INTO `spell_forced_targets` VALUES ('35782', '20809');
INSERT INTO `spell_forced_targets` VALUES ('36374', '21182');
INSERT INTO `spell_forced_targets` VALUES ('36374', '22401');
INSERT INTO `spell_forced_targets` VALUES ('36374', '22402');
INSERT INTO `spell_forced_targets` VALUES ('36374', '22403');
INSERT INTO `spell_forced_targets` VALUES ('36460', '183805');
INSERT INTO `spell_forced_targets` VALUES ('36460', '183806');
INSERT INTO `spell_forced_targets` VALUES ('36460', '183807');
INSERT INTO `spell_forced_targets` VALUES ('36460', '183808');
INSERT INTO `spell_forced_targets` VALUES ('36852', '21440');
INSERT INTO `spell_forced_targets` VALUES ('36854', '21437');
INSERT INTO `spell_forced_targets` VALUES ('36856', '21436');
INSERT INTO `spell_forced_targets` VALUES ('36857', '21438');
INSERT INTO `spell_forced_targets` VALUES ('36858', '21439');
INSERT INTO `spell_forced_targets` VALUES ('37055', '21512');
INSERT INTO `spell_forced_targets` VALUES ('37076', '17798');
INSERT INTO `spell_forced_targets` VALUES ('37204', '21709');
INSERT INTO `spell_forced_targets` VALUES ('37573', '20021');
INSERT INTO `spell_forced_targets` VALUES ('37689', '21847');
INSERT INTO `spell_forced_targets` VALUES ('37784', '21867');
INSERT INTO `spell_forced_targets` VALUES ('37843', '21899');
INSERT INTO `spell_forced_targets` VALUES ('37853', '15608');
INSERT INTO `spell_forced_targets` VALUES ('37936', '17796');
INSERT INTO `spell_forced_targets` VALUES ('37984', '21940');
INSERT INTO `spell_forced_targets` VALUES ('38020', '21949');
INSERT INTO `spell_forced_targets` VALUES ('38044', '21212');
INSERT INTO `spell_forced_targets` VALUES ('38112', '21212');
INSERT INTO `spell_forced_targets` VALUES ('38202', '18733');
INSERT INTO `spell_forced_targets` VALUES ('38360', '20216');
INSERT INTO `spell_forced_targets` VALUES ('38439', '21648');
INSERT INTO `spell_forced_targets` VALUES ('38444', '17008');
INSERT INTO `spell_forced_targets` VALUES ('38449', '21214');
INSERT INTO `spell_forced_targets` VALUES ('38451', '21214');
INSERT INTO `spell_forced_targets` VALUES ('38452', '21214');
INSERT INTO `spell_forced_targets` VALUES ('38455', '21214');
INSERT INTO `spell_forced_targets` VALUES ('38469', '22137');
INSERT INTO `spell_forced_targets` VALUES ('38469', '22139');
INSERT INTO `spell_forced_targets` VALUES ('38482', '22137');
INSERT INTO `spell_forced_targets` VALUES ('38484', '21246');
INSERT INTO `spell_forced_targets` VALUES ('38530', '22177');
INSERT INTO `spell_forced_targets` VALUES ('38729', '22288');
INSERT INTO `spell_forced_targets` VALUES ('38736', '22288');
INSERT INTO `spell_forced_targets` VALUES ('38762', '21722');
INSERT INTO `spell_forced_targets` VALUES ('38782', '22423');
INSERT INTO `spell_forced_targets` VALUES ('39010', '19264');
INSERT INTO `spell_forced_targets` VALUES ('39043', '22377');
INSERT INTO `spell_forced_targets` VALUES ('39094', '22395');
INSERT INTO `spell_forced_targets` VALUES ('39140', '22418');
INSERT INTO `spell_forced_targets` VALUES ('39141', '17968');
INSERT INTO `spell_forced_targets` VALUES ('39189', '21846');
INSERT INTO `spell_forced_targets` VALUES ('39189', '21859');
INSERT INTO `spell_forced_targets` VALUES ('39219', '22443');
INSERT INTO `spell_forced_targets` VALUES ('39246', '22105');
INSERT INTO `spell_forced_targets` VALUES ('39635', '22996');
INSERT INTO `spell_forced_targets` VALUES ('39849', '22996');
INSERT INTO `spell_forced_targets` VALUES ('39873', '22917');
INSERT INTO `spell_forced_targets` VALUES ('40076', '22884');
INSERT INTO `spell_forced_targets` VALUES ('40309', '23055');
INSERT INTO `spell_forced_targets` VALUES ('40401', '22841');
INSERT INTO `spell_forced_targets` VALUES ('40447', '22841');
INSERT INTO `spell_forced_targets` VALUES ('40468', '22252');
INSERT INTO `spell_forced_targets` VALUES ('40603', '22948');
INSERT INTO `spell_forced_targets` VALUES ('40874', '22841');
INSERT INTO `spell_forced_targets` VALUES ('41268', '23412');
INSERT INTO `spell_forced_targets` VALUES ('41269', '23412');
INSERT INTO `spell_forced_targets` VALUES ('41271', '23412');
INSERT INTO `spell_forced_targets` VALUES ('41295', '23418');
INSERT INTO `spell_forced_targets` VALUES ('42222', '23616');
INSERT INTO `spell_forced_targets` VALUES ('42323', '23720');
INSERT INTO `spell_forced_targets` VALUES ('42356', '23751');
INSERT INTO `spell_forced_targets` VALUES ('42356', '23752');
INSERT INTO `spell_forced_targets` VALUES ('42356', '23753');
INSERT INTO `spell_forced_targets` VALUES ('42411', '4328');
INSERT INTO `spell_forced_targets` VALUES ('42411', '4329');
INSERT INTO `spell_forced_targets` VALUES ('42411', '4331');
INSERT INTO `spell_forced_targets` VALUES ('44132', '24239');
INSERT INTO `spell_forced_targets` VALUES ('44320', '24722');
INSERT INTO `spell_forced_targets` VALUES ('44872', '25158');
INSERT INTO `spell_forced_targets` VALUES ('44969', '24980');
INSERT INTO `spell_forced_targets` VALUES ('44981', '24980');
INSERT INTO `spell_forced_targets` VALUES ('45030', '25003');
INSERT INTO `spell_forced_targets` VALUES ('45115', '25090');
INSERT INTO `spell_forced_targets` VALUES ('45115', '25091');
INSERT INTO `spell_forced_targets` VALUES ('45115', '25092');
INSERT INTO `spell_forced_targets` VALUES ('45191', '25154');
INSERT INTO `spell_forced_targets` VALUES ('45191', '25156');
INSERT INTO `spell_forced_targets` VALUES ('45191', '25157');
INSERT INTO `spell_forced_targets` VALUES ('45203', '24882');
INSERT INTO `spell_forced_targets` VALUES ('45223', '25192');
INSERT INTO `spell_forced_targets` VALUES ('45259', '25213');
INSERT INTO `spell_forced_targets` VALUES ('45351', '17845');
INSERT INTO `spell_forced_targets` VALUES ('45368', '187428');
INSERT INTO `spell_forced_targets` VALUES ('45371', '187431');
INSERT INTO `spell_forced_targets` VALUES ('45389', '25265');
INSERT INTO `spell_forced_targets` VALUES ('45839', '25653');
INSERT INTO `spell_forced_targets` VALUES ('46281', '25882');
INSERT INTO `spell_forced_targets` VALUES ('46474', '25315');
INSERT INTO `spell_forced_targets` VALUES ('46475', '25507');
INSERT INTO `spell_forced_targets` VALUES ('46964', '26391');
