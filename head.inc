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

////////////////////////////////////////////////////////////////////////////
//
// This file is included at the top of every .php except auth.php
// Its job is to ensure that the session is correctly set up, to
// provide the title bar of each page (using settings from settings.inc)
// with the name of the currently logged in user, or a login form
// if the user's name isn't set.  There are logout and change
// password lings - just forms so that I could use buttons instead
// of text links.  If this is undesirable, the forms can be removed
// and the files login.php and password.php can be included as modules
// via modules.inc
//
// This file also opens the main HTML table for each page, and builds
// the first layer menu based on the module array set in modules.inc

function showerror()
{
   if(mysql_error())
      print("Error number " . mysql_errno() . " (" . mysql_error() . ")");
   else
      print("Couldn't connect to database.");
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
                                
extract($_SERVER);

// Extract GET and POST variables.  This fixes things for
// PHP installations where php_globals = Off.  This is not
// a security concern, as the code was written with a
// certain degree of paranoia when this was not the default.

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

// Session stuff, general paranoia
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
   if($loginhost != $_SERVER["SERVER_NAME"])
   { // This session was created on another vhost
      unset($userid);
      unset($firstname);
      unset($lastname);
   }
   if(!isset($userid))
      $userid = 0;
   include("version.inc");
   include("settings.inc");
   if($PHP_SELF!=$siteprefix."online-help.php")
      $help_keyword="no_help";

// Connect to the database
if(!($intranet_db = @ mysql_pconnect($db_hostname, $db_username, $db_password)))
{
   showerror();
}
if(!mysql_select_db($db_name, $intranet_db))
{
   showerror();
}

// Get user's preferences
$sql = "SELECT stylesheet,language FROM users LEFT JOIN preferences USING (userid) WHERE users.userid = $userid";
$result = @ mysql_query($sql,$intranet_db);
$row = mysql_fetch_array($result);
// Set variables (hiding warning; there might not be any!)
if(!empty($row))
   extract($row);
// Check language, and if necessary set default
if(strlen($language)<1)
   $language = $default_lang;
require("languages/$language.inc");
require("modules.inc");
// Check stylesheet, and if necessary set default
if(strlen($stylesheet)<1)
{
   foreach($stylesheets as $find_sheet)
   {
      $stylesheet = $find_sheet;
      break;
   }
}
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=<?=$lang['_charset']?>">
<title><?print($sitename); if($userid>0) print(" - $firstname $lastname
logged in");?></title>
<link rel="stylesheet" href="<?=$stylesheet?>" type="text/css">
<link rel="alternate" type="application/rss+xml" title="RSS 2.0" href="/rss.php" />
</head>
<body>
<table>
<tr>
<?
if(isset($sitelogo))
{
   $logo_size = @ getimagesize($sitelogo);
   print("<td class=\"title_left\" width=\"$logo_size[0]\">\n");
   if(isset($logourl)) print("<a href=\"$logourl\">\n");
   print("<img src=\"$sitelogo\" $logo_size[3] alt=\"$sitename\" border=\"0\">\n");
   if(isset($logourl)) print("</a>\n");
   print("</td>\n");
}
?>
<td class="title_middle">
<?
if($userid>0)
{
   printf("$sitename <br>".$lang['logged_in_as'],$firstname,$lastname);
   print("<table>\n");
   print("<tr>\n");
   print("<td class=\"title_middle_sub\">\n");
   print("<form method=\"post\" id=\"framelogout\" action=\"auth.php?logout=yes\">\n");
   print("<input value=\"".$lang['logout']."\" class=\"button\" type=\"submit\">\n");
   print("</form>\n");
   print("</td>\n");
   print("<td class=\"title_middle_sub\">");
   print("<form method=\"get\" id=\"framepassword\" action=\"password.php\">\n");
   print("<input value=\"".$lang['change_password']."\" class=\"button\" type=\"submit\">\n");
   print("</form>\n");
   print("</td>\n");
   print("</tr>\n");
   print("</table>");
}
else
{
   print("$sitename\n");
   print("<form method=\"post\" id=\"framelogin\" action=\"https://tyneside.lug.org.uk/auth.php\">\n");
   print("<table>\n");
   print("<tr>\n");
   print("<td class=\"title_middle_sub_right\">\n");
   print("<b>".$lang['username'].":</b>\n");
   print("</td>\n");
   print("<td class=\"title_middle_sub\">\n");
   print("<input size=\"10\" type=\"text\" name=\"form_user\" value=\"\" class=\"textfield\">\n");
   print("</td>\n");
   print("<td class=\"title_middle_sub_right\">\n");
   print("&nbsp;<b>".$lang['password'].":</b>\n");
   print("</td>\n");
   print("<td class=\"title_middle_sub\">\n");
   print("<input size=\"10\"type=\"password\" name=\"form_pass\" value=\"\" class=\"textfield\">\n");
   print("</td>\n");
   print("<td colspan=\"2\">&nbsp;<input value=\"".$lang['login']."\" class=\"button\" type=\"submit\"></td>\n");
   print("</tr>\n");
   print("</table>\n");
   print("</form>\n");
}
?>
</td>
<td class="title_right">
<?
   print(date($lang['date_format'],time())."<br></font>");
// These next lines make a button that links to the online help system.
// I decided to make it a module, but if the menu gets too cluttered,
// putting in a link or a button here can be convenient.
//                  print("<form method=\"get\" id=\"Help\" action=\"online-help.php\">\n");
//                  print("<INPUT value=\"".$lang['online_help']."\" class=\"button\" type=\"submit\"></td>\n");
//                  print("</form>\n");
?>
</td>
</tr>
</table>
<table>
<tr>
<?
   $mod_percent=100 / count($module);
   foreach($module as $mod_tag=>$mod_file)
   {
      if(($siteprefix . $mod_file)==$PHP_SELF)
      {
         print("<th class=\"module_selected\" width=\"$mod_percent%\">");
      }
      else
      {
         print("<th class=\"module\" width=\"$mod_percent%\">");
      }
      print("<a class=\"module\" href=\"$siteprefix$mod_file\">$mod_tag</a></th>\n");
   }
?>
</tr>
</table>
<div id="main">
