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

// This is the downloader for the library.  It selects the details
// of the file ffrom the database, and then opens the disk file
// which contains the body (its filename being the same as the
// database index number) and prints it to output, after sending
// headers for filename and MIME type.

ob_start(4096);
set_time_limit(0);

// Session stuff, and general paranoia
   extract($_SERVER);
   extract($_REQUEST);
   if(isset($userid))
   {
      unset($userid);
      unset($username);
      unset($firstname);
      unset($lastname);
   }
   session_name('PPCIS');
   session_start();
   $loginhost=$_SESSION["loginhost"];
   $help_keyword=$_SESSION["help_keyword"];
   if(!isset($userid))
      $userid = 0;
   $userid=$_SESSION["userid"];
   $firstname=$_SESSION["firstname"];
   $lastname=$_SESSION["lastname"];
   $help_keyword=$_SESSION["help_keyword"];
   if($loginhost != $SERVER_NAME)
   { // This session was created on another vhost
      unset($userid);
      unset($firstname);
      unset($lastname);
   }
   if(!isset($userid))
      $userid = 0;

require("settings.inc");

// Connect to the database
if(!($intranet_db = @ mysqli_connect($db_hostname, $db_username, $db_password, $db_name)))
{
   die("Database problem");
}

// Get user's preferences
$sql = "SELECT stylesheet,language FROM users LEFT JOIN preferences USING (userid) WHERE users.userid = $userid";
$result = @ mysqli_query($intranet_db,$sql);
$row = mysqli_fetch_array($result,MYSQLI_ASSOC);
// Set variables (hiding warning; there might not be any!)
if(!empty($row))
   extract($row);
// Check language, and if necessary set default
if(strlen($language)<1)
   $language = $default_lang;
require("languages/$language.inc");
// Check stylesheet, and if necessary set default
if(strlen($stylesheet)<1)
{
   foreach($stylesheets as $find_sheet)
   {
      $stylesheet = $find_sheet;
      break;
   }
}

if($userid>0)
{
   // Get the user's team for security checking
   $sql = "SELECT team FROM userteams WHERE userid=$userid";
   $result = @ mysqli_query($intranet_db,$sql);
   if (mysqli_error($intranet_db))
      die("Database problem");
   if(@ mysqli_num_rows($result) != 0)
   {
      $i=0;
      while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
      {
         $userteam[$i]=$row["team"];
         $i++;
      }
   }
   // Check the validity of $fileid if set and
   // determine how secure it is.
   $sql = "SELECT filename,mimetype FROM files WHERE fileid = $fileid ORDER BY filename";
   $result = @ mysqli_query($intranet_db,$sql);
   if (mysqli_error($intranet_db))
 	   die("Database problem");
   if(@ mysqli_num_rows($result) != 0)
   {
      while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
      {
         $filename=$row["filename"];
         if (!isset($mimetype))
         {
            $mimetype = $row["mimetype"];
         }
      }
   }
   else
   {
      require("head.inc");
      print("<h1>".$lang['file_not_exist']."</h1>");
      require("tail.inc");
      die();
   }
   // I re-use my query variables, so this is outside the above
   // if statement.  If the file doesn't exist, this has no impact
   // anyway, as the COUNT(*) should return zero, unless for some
   // reason there's duff data in the filesecurity table.
   $sql = "SELECT COUNT(*) FROM filesecurity WHERE fileid=$fileid";
   $result = @ mysqli_query($intranet_db,$sql);
   $securefile = TRUE; // This must be true
   $row = mysqli_fetch_array($result,MYSQLI_NUM);
   if($row[0] > 0)
   { // This file has one or more security records
      $sql = "SELECT teamid FROM filesecurity WHERE fileid=$fileid";
      $result = @ mysqli_query($intranet_db,$sql);
      while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
      { // Check to see if our team is on the list
         foreach($userteam as $teamtest)
            if($row["teamid"]==$teamtest)
               $securefile = FALSE;
      }
   }
   else // There is no access list, there is no restriction.
      $securefile = FALSE;
   if($securefile)
   {
      require("head.inc");
      print("<h1>".$lang['file_insufficient_privileges']."</h1>");
      require("tail.inc");
      die();
   }
   if(!($file_to_send=@fopen($file_store.$fileid, "rb")))
   {
      require("head.inc");
      print("<h1>".$lang['file_corrupted_missing']."</h1>");
      require("tail.inc");
      die();
   }
   header("Content-Type: $mimetype");
   header("Content-Disposition: filename=\"$filename\"");
   header("Cache-Control: ");// If used in SSL, IE has a bug where
   header("Pragma: ");       // it can't connect without these lines
   header("Content-length: ".(string)(filesize($file_store.$fileid)));
   session_write_close();
   while(!feof($file_to_send))
   {
      print(fread($file_to_send,64));
   }
   fclose($file_to_send);
}
else
{
   require("head.inc");
   print("<h1>".$lang['file_insufficient_privileges']."</h1>");
   require("tail.inc");
}
?>
