-- MySQL dump 9.11
--
-- Host: localhost    Database: ppcis
-- ------------------------------------------------------
-- Server version	4.0.22

--
-- Table structure for table `assignees`
--

CREATE TABLE assignees (
  taskid int(10) NOT NULL auto_increment,
  callid int(10) NOT NULL default '0',
  userid int(10) NOT NULL default '0',
  active enum('Y','N') NOT NULL default 'N',
  PRIMARY KEY  (taskid),
  KEY userid (userid),
  KEY callid (callid)
) TYPE=MyISAM;

--
-- Dumping data for table `assignees`
--


--
-- Table structure for table `callcategory`
--

CREATE TABLE callcategory (
  categoryid int(10) NOT NULL auto_increment,
  name varchar(25) NOT NULL default '',
  PRIMARY KEY  (categoryid)
) TYPE=MyISAM;

--
-- Dumping data for table `callcategory`
--


--
-- Table structure for table `contacttype`
--

CREATE TABLE contacttype (
  contacttype int(10) NOT NULL auto_increment,
  description varchar(20) default NULL,
  PRIMARY KEY  (contacttype)
) TYPE=MyISAM;

--
-- Dumping data for table `contacttype`
--


--
-- Table structure for table `externalcontact`
--

CREATE TABLE externalcontact (
  ref int(11) NOT NULL auto_increment,
  firstname varchar(25) default NULL,
  surname varchar(25) default NULL,
  title varchar(60) default NULL,
  address1 varchar(80) default NULL,
  address2 varchar(50) default NULL,
  address3 varchar(50) default NULL,
  town varchar(40) default NULL,
  county varchar(25) default NULL,
  postcode varchar(10) default NULL,
  company varchar(50) default NULL,
  email varchar(50) default NULL,
  website varchar(50) default NULL,
  telephone varchar(20) default NULL,
  fax varchar(50) default NULL,
  contacttype int(10) NOT NULL default '0',
  PRIMARY KEY  (ref),
  KEY contacttype (contacttype)
) TYPE=MyISAM;

--
-- Dumping data for table `externalcontact`
--


--
-- Table structure for table `faq`
--

CREATE TABLE faq (
  faqid int(10) NOT NULL auto_increment,
  categoryid int(10) NOT NULL default '0',
  question varchar(255) NOT NULL default '',
  answer longtext NOT NULL,
  PRIMARY KEY  (faqid),
  KEY categoryid (categoryid),
  FULLTEXT KEY question (question,answer)
) TYPE=MyISAM;

--
-- Dumping data for table `faq`
--


--
-- Table structure for table `faqcategory`
--

CREATE TABLE faqcategory (
  categoryid int(10) NOT NULL auto_increment,
  name varchar(25) NOT NULL default '',
  PRIMARY KEY  (categoryid)
) TYPE=MyISAM;

--
-- Dumping data for table `faqcategory`
--


--
-- Table structure for table `files`
--

CREATE TABLE files (
  fileid int(10) NOT NULL auto_increment,
  filename varchar(255) NOT NULL default '',
  size int(10) NOT NULL default '0',
  mimetype varchar(30) NOT NULL default '',
  folder int(10) NOT NULL default '0',
  synopsis text NOT NULL,
  datestamp int(11) NOT NULL default '0',
  PRIMARY KEY  (fileid),
  KEY filename (filename),
  KEY folder (folder)
) TYPE=MyISAM;

--
-- Dumping data for table `files`
--


--
-- Table structure for table `filesecurity`
--

CREATE TABLE filesecurity (
  fileid int(10) NOT NULL default '0',
  teamid int(10) NOT NULL default '0',
  KEY fileid (fileid),
  KEY teamid (teamid)
) TYPE=MyISAM;

--
-- Dumping data for table `filesecurity`
--


--
-- Table structure for table `folders`
--

CREATE TABLE folders (
  folderid int(10) NOT NULL auto_increment,
  name varchar(255) NOT NULL default '',
  parent int(10) NOT NULL default '0',
  PRIMARY KEY  (folderid),
  KEY parent (parent)
) TYPE=MyISAM;

--
-- Dumping data for table `folders`
--


--
-- Table structure for table `helpdesk`
--

CREATE TABLE helpdesk (
  callid int(10) NOT NULL auto_increment,
  ownerid int(10) NOT NULL default '0',
  locationid int(10) NOT NULL default '0',
  description text NOT NULL,
  priority int(1) NOT NULL default '0',
  date int(11) NOT NULL default '0',
  closedate int(11) default NULL,
  category int(10) NOT NULL default '0',
  PRIMARY KEY  (callid),
  KEY ownerid (ownerid,locationid)
) TYPE=MyISAM;

--
-- Dumping data for table `helpdesk`
--


--
-- Table structure for table `history`
--

CREATE TABLE history (
  historyid int(10) NOT NULL auto_increment,
  callid int(10) NOT NULL default '0',
  userid int(10) NOT NULL default '0',
  histdate int(11) default NULL,
  body text NOT NULL,
  system enum('y','n') NOT NULL default 'n',
  PRIMARY KEY  (historyid),
  KEY callid (callid)
) TYPE=MyISAM;

--
-- Dumping data for table `history`
--


--
-- Table structure for table `locations`
--

CREATE TABLE locations (
  locationid int(10) unsigned NOT NULL auto_increment,
  name varchar(25) NOT NULL default '',
  PRIMARY KEY  (locationid)
) TYPE=MyISAM;

--
-- Dumping data for table `locations`
--


--
-- Table structure for table `news`
--

CREATE TABLE news (
  articleid int(10) unsigned NOT NULL auto_increment,
  authorid int(10) unsigned NOT NULL default '0',
  topic int(10) NOT NULL default '1',
  subdate int(11) default '0',
  authdate int(11) default NULL,
  headline varchar(255) NOT NULL default '',
  body text NOT NULL,
  url varchar(50) default NULL,
  sticky enum('y','n') NOT NULL default 'n',
  PRIMARY KEY  (articleid),
  FULLTEXT KEY body (body),
  FULLTEXT KEY headline (headline)
) TYPE=MyISAM;

--
-- Dumping data for table `news`
--


--
-- Table structure for table `newstopic`
--

CREATE TABLE newstopic (
  topicid int(10) NOT NULL auto_increment,
  name varchar(25) NOT NULL default '',
  PRIMARY KEY  (topicid)
) TYPE=MyISAM;

--
-- Dumping data for table `newstopic`
--


--
-- Table structure for table `preferences`
--

CREATE TABLE preferences (
  userid int(10) NOT NULL default '0',
  stylesheet varchar(20) default NULL,
  language varchar(20) default NULL,
  PRIMARY KEY  (userid)
) TYPE=MyISAM;

--
-- Dumping data for table `preferences`
--


--
-- Table structure for table `teams`
--

CREATE TABLE teams (
  teamid int(10) unsigned NOT NULL auto_increment,
  name varchar(50) NOT NULL default '',
  PRIMARY KEY  (teamid)
) TYPE=MyISAM;

--
-- Dumping data for table `teams`
--


--
-- Table structure for table `userdirectory`
--

CREATE TABLE userdirectory (
  userid int(10) unsigned NOT NULL default '0',
  title varchar(25) default NULL,
  post varchar(25) default NULL,
  location int(10) unsigned default NULL,
  email varchar(50) default NULL,
  manager int(10) unsigned default NULL,
  telephone varchar(14) default NULL,
  mobile varchar(14) default NULL,
  info text,
  PRIMARY KEY  (userid),
  KEY team (location,manager)
) TYPE=MyISAM;

--
-- Dumping data for table `userdirectory`
--


--
-- Table structure for table `userflags`
--

CREATE TABLE userflags (
  userid int(10) unsigned NOT NULL default '0',
  useradmin enum('y','n') NOT NULL default 'n',
  newsadmin enum('y','n') NOT NULL default 'n',
  helpdesk enum('y','n') NOT NULL default 'n',
  files enum('y','n') NOT NULL default 'n',
  directoryadmin enum('y','n') NOT NULL default 'n',
  PRIMARY KEY  (userid)
) TYPE=MyISAM;

--
-- Dumping data for table `userflags`
--

INSERT INTO userflags VALUES (1,'y','y','y','y','y');

--
-- Table structure for table `users`
--

CREATE TABLE users (
  userid int(10) unsigned NOT NULL auto_increment,
  username varchar(10) NOT NULL default '',
  password varchar(50) NOT NULL default '',
  firstname varchar(25) NOT NULL default '',
  lastname varchar(25) NOT NULL default '',
  enabled enum('y','n') NOT NULL default 'y',
  guest enum('y','n') NOT NULL default 'n',
  PRIMARY KEY  (userid),
  UNIQUE KEY username (username),
  KEY names (lastname,firstname)
) TYPE=MyISAM;

--
-- Dumping data for table `users`
--

INSERT INTO users VALUES (1,'admin',sha1('istrator'),'system','administrator','y','n');

--
-- Table structure for table `userteams`
--

CREATE TABLE userteams(
	linkid int( 10 ) NOT NULL AUTO_INCREMENT ,
	userid int( 10 ) NOT NULL default '0',
	team int( 10 ) NOT NULL default '0',
	PRIMARY KEY ( linkid ) ,
	KEY userid( userid ) ,
	KEY team( team ) 
) TYPE = MYISAM 
	
--
-- Dumping data for table `userteams`
--


--
-- Table structure for table `webcategory`
--

CREATE TABLE webcategory (
  categoryid int(10) NOT NULL auto_increment,
  name varchar(25) NOT NULL default '',
  PRIMARY KEY  (categoryid)
) TYPE=MyISAM;

--
-- Dumping data for table `webcategory`
--


--
-- Table structure for table `weblinks`
--

CREATE TABLE weblinks (
  linkid int(10) NOT NULL auto_increment,
  title varchar(25) NOT NULL default '',
  url varchar(100) NOT NULL default '',
  description varchar(100) NOT NULL default '',
  category int(10) NOT NULL default '0',
  PRIMARY KEY  (linkid),
  KEY category (category)
) TYPE=MyISAM;

--
-- Dumping data for table `weblinks`
--


