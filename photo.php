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

if($userid>0)
{
   $size=getimagesize($file_store."p".$fileid);
   $mimetype=$size[5];
   if(!($file_to_send=@fopen($file_store."p".$fileid, "rb")))
   { // Photos live in the same place as the regular files but
     // their names begin with p.
      require("head.inc");
      print("<h1>".$lang['file_corrupted_missing']."</h1>");
      require("tail.inc");
      die();
   }
   header("Content-Type: $mimetype");
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
