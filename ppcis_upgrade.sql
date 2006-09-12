ALTER TABLE `files` ADD `datestamp` INT( 11 ) DEFAULT '0' NOT NULL ;
ALTER TABLE `history` ADD `system` ENUM( 'y', 'n' ) DEFAULT 'n' NOT NULL ;
ALTER TABLE `news` ADD `sticky` ENUM( 'y', 'n' ) DEFAULT 'n' NOT NULL ;
CREATE TABLE `preferences` (
 `userid` INT( 10 ) NOT NULL ,
 `stylesheet` VARCHAR( 20 ) ,
 `language` VARCHAR( 20 ) 
);
ALTER TABLE `userdirectory` ADD `info` TEXT;
ALTER TABLE `users` ADD `guest` ENUM( 'y', 'n' ) DEFAULT 'n' NOT NULL ;
CREATE TABLE userteams(
	linkid int( 10 ) NOT NULL AUTO_INCREMENT ,
	userid int( 10 ) NOT NULL default '0',
	team int( 10 ) NOT NULL default '0',
	PRIMARY KEY ( linkid ) ,
	KEY userid( userid ) ,
	KEY team( team ) 
) TYPE = MYISAM 
INSERT INTO `userteams` (
 `userid` ,
 `team`
) SELECT `userid`,`team` FROM `userdirectory`;
ALTER TABLE `userdirectory` DROP `team`;
