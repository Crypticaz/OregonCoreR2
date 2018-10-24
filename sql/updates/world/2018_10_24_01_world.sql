DROP TABLE IF EXISTS `spell_area`;
CREATE TABLE `spell_area` (
  `spell`              MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
  `area`               MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
  `quest_start`        MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
  `quest_start_active` TINYINT(1) UNSIGNED NOT NULL DEFAULT '0',
  `quest_end`          MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
  `aura_spell`         MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
  `racemask`           MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
  `gender`             TINYINT(1) UNSIGNED NOT NULL DEFAULT '2',
  `autocast`           TINYINT(1) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY  (`spell`,`area`,`quest_start`,`quest_start_active`,`aura_spell`,`racemask`,`gender`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8;
