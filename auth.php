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

// This file does the password checking and session variable setting
// required to create a logged in session.

// Session stuff, and general paranoia
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
   $loginhost=$_SERVER["SERVER_NAME"];
   if(!isset($userid))
      $userid = 0;
if(!(@ include("settings.inc")))
{
   header("location:".$_SERVER["HTTP_REFERER"]);
   die("Database not configured.");
}

function showerror()
{
   if(mysqli_connect_errno())
   {
      print("Couldn't connect to database.");
      if(@mysqli_error($intranet_db))
         print("Error number " . mysqli_errno($intranet_db) . " (" . mysqli_error($intranet_db) . ")");
   }
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

// Dead simple - connect to the database, run a select query.  If
// the user exists with that password, the userid variable gets
// set and the user is logged in.

if(isset($form_user))
{
// Connect to the database
   $intranet_db = @ mysqli_connect($db_hostname, $db_username, $db_password, $db_name);
   showerror();
   $sql = "SELECT * FROM users WHERE username = '".safe_escape(trim($form_user))."' AND password = $hash_function( '".safe_escape($form_pass)."')";
   $result = @ mysqli_query($intranet_db, $sql);
   showerror();
   if(@ mysqli_num_rows($result) != 0)
   {
      while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
      {
         if($row["enabled"]=='y')
         {
            $userid = $row["userid"];
            $username = $form_user;
            $firstname = $row["firstname"];
            $lastname = $row["lastname"];
         }
         else
         {
            $userid = 0;
            $username = "failed";
            $firstname = "";
            $lastname = "";
            session_destroy();
         }
      }
   }
   elseif(isset($old_hash_function))
   {
      $sql = "SELECT * FROM users WHERE username = '".safe_escape(trim($form_user))."' AND password = $old_hash_function( '".safe_escape($form_pass)."')";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
      if(@ mysqli_num_rows($result) != 0)
      {
         while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
         {
            if($row["enabled"]=='y')
            {
               $userid = $row["userid"];
               $username = $form_user;
               $firstname = $row["firstname"];
               $lastname = $row["lastname"];
            }
            else
            {
               $userid = 0;
               $username = "failed";
               $firstname = "";
               $lastname = "";
               session_destroy();
            }
            $sql = "UPDATE users SET password = $hash_function( '".safe_escape($form_pass)."') WHERE userid = ".$row["userid"];
            $result = @ mysqli_query($intranet_db,$sql);
            $updates = "Updated password from $old_password_function to $password_function";
         }
      }
   }
   else
   {
      $userid = 0;
      $username = "failed";
      $firstname = "";
      $lastname = "";
      session_destroy();
   }
}
else
{
   $userid = 0;
   $username = "logout";
   $firstname = "";
   $lastname = "";
   session_destroy();
}
$_SESSION["userid"]=$userid;
$_SESSION["firstname"]=$firstname;
$_SESSION["lastname"]=$lastname;
$_SESSION["loginhost"]=$loginhost;
$_SESSION["help_keyword"]=$help_keyword;
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<? // This returns to the main system.
if(isset($logout))
{
   print("<META HTTP-EQUIV=\"refresh\" content=\"0;URL=$siteprefix" . "index.php?auth=out\">");
}
else
{
   print("<META HTTP-EQUIV=\"refresh\" content=\"0;URL=$siteprefix" . "index.php?auth=in\">");
}
?>
<title>Authentication</title>
</head>
<body>
<?
print("Authorisation returned: userid=$userid, username=$username.<br>\n");
print("If you aren't automatically returned, click <a href=\"$site_prefix" . "index.php\">here</a><br>\n");
print($updates);
?>
</body>
</html>
