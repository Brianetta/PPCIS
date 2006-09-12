<?
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
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<title><?print($sitename); if($userid>0) print(" - $firstname $lastname
logged in");?></title>
</head>
<body bgcolor="white" text="black">
<?
// Connect to the database
if(!($intranet_db = @ mysql_pconnect($db_hostname, $db_username, $db_password)))
{
showerror();
}
if(!mysql_select_db($db_name, $intranet_db))
{
showerror();
}

// Build an array to cache the news topics
$sql = "SELECT * FROM newstopic ORDER BY name";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   while($row = @ mysql_fetch_array($result))
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
                                
// Function to display a single article in full
function newsitem($news_headline, $news_body, $news_topic, $news_date, $name, $url="")
{
   global $topiclist;
   $news_date = date($lang['date_format'], $news_date);
   print("<table>\n");
   print("<tr>\n");
   print("<td>\n");
   print("<table>\n");
   print("<tr>\n");
   print("<td>\n");
   print("<table>\n");
   print("<tr>");
   print("<td align=\"left\">\n");
   print($topiclist[$news_topic]);
   print("</td>\n");
   print("<td align=\"right\">\n");
   print($news_date);
   print("</td>\n");
   print("</tr>\n");
   print("</table>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>\n");
   print("<td>\n");
   print("<table>\n");
   print("<tr>\n");
   print("<td>\n");
   print("<h1>".strip_tags($news_headline)."</h1>");
   print(nl2br(strip_tags($news_body,"<b><i>")));
   if(($url<>"") and ($url<>"http://"))
      print("<br>\n<br>\nRelated link: <a href=\"$url\">$url</a>");
   print("<br>\n<br>\n<i>Submitted by $name</i><br>\n<br>\n");
   print("\n</td>\n");
   print("</tr>\n");
   print("</table>\n");
   print("</td>\n");
   print("</tr>\n");
   print("</table>\n");
   print("</td>\n");
   print("</tr>\n");
   print("</table>\n");
   return(true);
}

$sql = "SELECT * FROM news LEFT JOIN users ON users.userid = news.authorid WHERE news.authdate IS NOT NULL AND articleid=".safe_escape($article);

$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
showerror();
if(@ mysql_num_rows($result) != 0)
{
   $row = @ mysql_fetch_array($result);
   newsitem($row["headline"], $row["body"], $row["topic"], $row["subdate"], $row["firstname"]." ".$row["lastname"], $row["url"]);
}
else
{
print("<h1>News article error</h1>\n");
print("The news article you wish to view is not available.\n");
}

$_SESSION["userid"]=$userid;
$_SESSION["firstname"]=$firstname;
$_SESSION["lastname"]=$lastname;
$_SESSION["loginhost"]=$loginhost;
$_SESSION["help_keyword"]=$help_keyword;
require("version.inc");
?>
<br>
<br>
<font size="-2">PPCIS version <?echo ppcis_version;?> - Copyright &copy; 2002-<?echo ppcis_year;?>, Brian Ronald.  Distributed under the <a href="license.php">GNU General Public License</a></font>
</body>
</html>
