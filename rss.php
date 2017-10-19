<?php
// Copyright 2002 Brian Ronald.  All rights reserved.
// Portable PHP/MySQL Corporate Intranet System
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

//////////////////////////////////////////////////////////////////////////////

// This file is a module which builds the second layer news menu
// and includes other files in order to fulfill the functions
// selected from that menu.

unset($auto_authorise_news); // No hacking your way past here.  It's either set
                             // from settings.inc or nowhere at all.
extract($_SERVER);

if (!empty($_GET))
{
   extract($_GET);
}
else if (!empty($HTTP_GET_VARS))
{
   extract($HTTP_GET_VARS);
}

if (!empty($_POST))
{
   extract($_POST);
}
if (!empty($_FILES))
{
   extract($_FILES);
}
else if (!empty($HTTP_POST_VARS))
{
   extract($HTTP_POST_VARS);
}
else if (!empty($HTTP_POST_FILES))
{
   extract($HTTP_POST_FILES);
}

unset($userid);    // The only script that doesn't get these
unset($firstname); // four variables from the session is
unset($lastname);  // auth.php - and this isn't auth.php.
unset($loginhost); // This last one's for vhost protection
session_name('PPCIS');
session_start();
$userid=$_SESSION["userid"];
$firstname=$_SESSION["firstname"];
$lastname=$_SESSION["lastname"];
$loginhost=$_SESSION["loginhost"];
$help_keyword=$_SESSION["help_keyword"];
if($loginhost != $SERVER_NAME)
{ // This session was created on another vhost
   unset($userid);
   unset($firstname);
   unset($lastname);
}
if(!isset($userid))
   $userid = 0;
@ include("settings.inc");

$asc2uni = Array();
for($i=128;$i<256;$i++){
  $asc2uni[chr($i)] = "&#x".dechex($i).";";   
}

function XMLStrFormat($str){
  global $asc2uni;
  $str = str_replace("&", "&amp;", $str);
  $str = str_replace("<", "&lt;", $str); 
  $str = str_replace(">", "&gt;", $str); 
  $str = str_replace("'", "&apos;", $str);  
  $str = str_replace("\"", "&quot;", $str); 
  $str = str_replace("\r", "", $str);
  $str = strtr($str,$asc2uni);
  return $str;
}

?>
<?php print('<?php xml version="1.0" encoding="ISO-8859-1" ?>');?>

<rss version="2.0">
<channel>
<title><?=$sitename?></title>
<name><?=$sitename?></name>
<description><?=$sitename?></description>
<link>http://<?=$_SERVER['SERVER_NAME'] . $siteprefix . "news.php"?></link>
<?php
// Connect to the database
if(!($intranet_db = @ mysqli_connect($db_hostname, $db_username, $db_password, $db_name)))
{
showerror();
}

// Build an array to cache the news topics
$sql = "SELECT * FROM newstopic ORDER BY name";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      $topiclist[$row["topicid"]]=$row["name"];
   }
}
else
{
   $topiclist[1]="No topics defined";
}

function safe_escape($str) 
{
   if (1 == (int) ini_get("magic_quotes_gpc"))
   {
      return $str;
   }
   else
   {
      return addslashes($str);
   }
}

/**
 * close all open xhtml tags at the end of the string
 *
 * @author Milian Wolff <http://milianw.de>
 * @param string $html
 * @return string
 */
function closetags($html){
  #put all opened tags into an array
  preg_match_all("#<([a-z]+)( .*)?(?!/)>#iU",$html,$result);
  $openedtags=$result[1];

  #put all closed tags into an array
  preg_match_all("#</([a-z]+)>#iU",$html,$result);
  $closedtags=$result[1];
  $len_opened = count($openedtags);
  # all tags are closed
  if(count($closedtags) == $len_opened){
    return $html;
  }
  $openedtags = array_reverse($openedtags);
  # close tags
  for($i=0;$i<$len_opened;$i++) {
    if (!in_array($openedtags[$i],$closedtags)){
      $html .= '</'.$openedtags[$i].'>';
    } else {
      unset($closedtags[array_search($openedtags[$i],$closedtags)]);
    }
  }
  return $html;
}

                                
// Function to display a single article in full
function newsitem($news_headline, $news_body, $news_topic, $news_date, $name, $url="")
{
   $limit=1024;
   global $topiclist;
   global $siteprefix;
   global $sitename;
   $news_date = date("r", $news_date);
   print("<item>\n");
   print('<title>'.XMLStrFormat($news_headline)."</title>\n");
   print("<category>".$topiclist[$news_topic]."</category>\n");
   print("<description>");
   if(strlen($news_body)<$limit)
      print(XMLStrFormat(closetags("$news_body"))."\n");
   else
      print(XMLStrFormat(substr(closetags("$news_body"),0,$limit-3))."...\n");
   print("&lt;br /&gt;&lt;i&gt;$name&lt;/i&gt;");
   print("</description>\n");
   print("<link>http://" . $_SERVER['SERVER_NAME'] . $siteprefix . "news.php?callmodule=All%20news%20articles&amp;select=$url</link>\n");
   print("<pubDate>$news_date</pubDate>\n");
   print("</item>\n");
   return(true);
}

$sql = "SELECT * FROM news LEFT JOIN users ON users.userid = news.authorid WHERE news.authdate IS NOT NULL ORDER BY news.subdate DESC LIMIT 10";

$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      newsitem($row["headline"], $row["body"], $row["topic"], $row["subdate"], $row["firstname"]." ".$row["lastname"], $row["articleid"]);
   }
}

$_SESSION["userid"]=$userid;
$_SESSION["firstname"]=$firstname;
$_SESSION["lastname"]=$lastname;
$_SESSION["loginhost"]=$loginhost;
$_SESSION["help_keyword"]=$help_keyword;
require("version.inc");
?>
</channel>
</rss>
