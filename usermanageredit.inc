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

// This file allows useradmins and directoryadmins to alter the directory
// entry of a specified user.  Sorry it's such a mess.  Roughly the first
// half of the code will update the user's records when the forms are submitted.
// Roughly the second half of the code is the form and the database code to
// provide the default values.  This code submits to itself.

if(strlen($_FILES["uploadfile"]["name"])>0)
{ // This bit is to make file uploads work if register_globals is off.
   $uploadfile = $_FILES["uploadfile"]["tmp_name"];
   $uploadfile_name = $_FILES["uploadfile"]["name"];
   $uploadfile_size = $_FILES["uploadfile"]["size"];
   $uploadfile_type = $_FILES["uploadfile"]["type"];
}
if(isset($uploadfile))
{
   if($uploadfile_size>0 and isset($photo_userid))
   {
      if(is_uploaded_file($uploadfile))
      {
         move_uploaded_file($uploadfile,$file_store."p".$photo_userid);
         print("<span class=\"message\">".$lang['photo_uploaded']."</span><br>\n");
      }
      else
      {
         print("<span class=\"message\">".$lang['photo_upload_failed']."</span><br>\n");
      }
   }
}

if(isset($delphoto) and isset($delconf))
{
   if (is_writeable($file_store."p".$photo_userid))
   {
      if(unlink($file_store."p".$photo_userid))
      {
         printf("<span class=\"message\">".$lang['user_deleted_photo']."</span><br>\n",$photo_userid);
      }
   }
}

if(isset($mod_userid))
{ // Here we clean up the data.  Empty strings are turned to NULLS, strings are escaped.
   if($mod_title <> "")
   {
      $mod_title = "'".safe_escape($mod_title)."'";
   } else {
      $mod_title = "NULL";
   }
   if($mod_firstname <> "")
   {
      $mod_firstname = "'".safe_escape($mod_firstname)."'";
   } else {
      $mod_firstname = "NULL";
   }
   if($mod_lastname <> "")
   {
      $mod_lastname = "'".safe_escape($mod_lastname)."'";
   } else {
      $mod_lastname = "NULL";
   }
   if($mod_email <> "")
   {
      $mod_email = "'".safe_escape($mod_email)."'";
   } else {
      $mod_email = "NULL";
   }
   if($mod_telephone <> "")
   {
      $mod_telephone = "'".safe_escape($mod_telephone)."'";
   } else {
      $mod_telephone = "NULL";
   }
   if($mod_mobile <> "")
   {
      $mod_mobile = "'".safe_escape($mod_mobile)."'";
   } else {
      $mod_mobile = "NULL";
   }
   if($mod_post <> "")
   {
      $mod_post = "'".safe_escape($mod_post)."'";
   } else {
      $mod_post = "NULL";
   }
   if($mod_location <> "NULL") $mod_location = safe_escape($mod_location);
   if($mod_manager <> "NULL") $mod_manager = safe_escape($mod_manager);
   if($mod_info <> "")
   {
      $mod_info = "'".safe_escape($mod_info)."'";
   } else {
      $mod_info = "NULL";
   }
   $sql = "UPDATE users SET firstname = $mod_firstname, lastname = $mod_lastname WHERE userid = $mod_userid";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
   $sql = "REPLACE INTO userdirectory (userid, title, post, location, email, manager, telephone, mobile, info) VALUES ($mod_userid, $mod_title, $mod_post, $mod_location, $mod_email, $mod_manager, $mod_telephone, $mod_mobile, $mod_info)";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
   print("<span class=\"message\">".$lang['user_successfully_amended']."</span>");
}
if(isset($makexdir))
{
   $sql = "DELETE FROM userdirectory WHERE userid = $makexdir";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
   print("<span class=\"message\">".$lang['user_successfully_removed from directory'] ."</span>");
}
$sql = "SELECT *,users.userid AS userid FROM users LEFT JOIN  userdirectory ON users.userid = userdirectory.userid WHERE users.userid = ".safe_escape($showuserid);
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   print("<table>");
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      print("<form method=\"post\" id=\"usermod\" action=\"admin.php?callmodule=".rawurlencode($callmodule)."&showuserid=".$row["userid"]."\">\n");
      print("<input type=\"hidden\" name=\"mod_userid\" value=\"".$row["userid"]."\">");
      print("<tr>");
      print("<th colspan=\"2\"><h2>");
      print($lang['modifying_user'].": ");
      print($row["firstname"] . " " . $row["lastname"] ."</h2></th>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['title']."</td>");
      print("<td><input size=\"25\" type=\"text\" name=\"mod_title\" value=\"" . $row["title"] ."\"></td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['firstname']."</td>");
      print("<td><input size=\"25\" type=\"text\" name=\"mod_firstname\" value=\"" . $row["firstname"] ."\"></td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['lastname']."</td>");
      print("<td><input size=\"25\" type=\"text\" name=\"mod_lastname\" value=\"" . $row["lastname"] ."\"></td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td colspan=\"2\">&nbsp;</td>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['email_address']."</td>");
      print("<td><input size=\"25\" type=\"text\" name=\"mod_email\" value=\"" . $row["email"] ."\"></td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['telephone_number']."</td>");
      print("<td><input size=\"25\" type=\"text\" name=\"mod_telephone\" value=\"" . $row["telephone"] ."\"></td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['mobile_number']."</td>");
      print("<td><input size=\"25\" type=\"text\" name=\"mod_mobile\" value=\"" . $row["mobile"] ."\"></td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td colspan=\"2\">&nbsp;</td>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['post']."</td>");
      print("<td><input size=\"25\" type=\"text\" name=\"mod_post\" value=\"" . $row["post"] ."\"></td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['location']."</td>\n");
      print("<td>\n");
      $sql = "SELECT * FROM locations ORDER BY name";
      $sub_result = @ mysqli_query($intranet_db,$sql);
      showerror();
      print("<select name=\"mod_location\">\n");
      print("<option label=\"".$lang['nowhere']."\" value=\"NULL\">".$lang['nowhere']."</option>");
      if(@ mysqli_num_rows($sub_result) != 0)
      {
         while($sub_row = @ mysqli_fetch_array($sub_result,MYSQLI_ASSOC))
         {
            if($row["location"]==$sub_row["locationid"])
            {
               print("<option selected label=\"".$sub_row["name"]."\" value=\"".$sub_row["locationid"]."\">");
               print($sub_row["name"]."</option>");
            }
            else
            {
               print("<option label=\"".$sub_row["name"]."\" value=\"".$sub_row["locationid"]."\">");
               print($sub_row["name"]."</option>");
            }
         }
      }
      print($sub_row["name"]);
      print("</select>");
      print("</td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['manager']."</td>");
      print("<td>");
      $sql = "SELECT * FROM users ORDER BY lastname";
      $sub_result = @ mysqli_query($intranet_db,$sql);
      showerror();
      print("<select name=\"mod_manager\">\n");
      print("<option label=\"".$lang['nobody']."\" value=\"NULL\">".$lang['nobody']."</option>");
      if(@ mysqli_num_rows($sub_result) != 0)
      {
         while($sub_row = @ mysqli_fetch_array($sub_result,MYSQLI_ASSOC))
         {
            if($row["manager"]==$sub_row["userid"])
            {
               print("<option selected label=\"".$sub_row["lastname"].", ".$sub_row["firstname"]."\" value=\"".$sub_row["userid"]."\">");
               print($sub_row["lastname"].", ".$sub_row["firstname"]."</option>");
            }
            else
            {
               print("<option label=\"".$sub_row["lastname"].", ".$sub_row["firstname"]."\" value=\"".$sub_row["userid"]."\">");
               print($sub_row["lastname"].", ".$sub_row["firstname"]."</option>\n");
            }
         }
      }
      print("</select>");
      print("</td>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['info']."</td>");
      print("<td>");
      print("<textarea rows=\"5\" cols=\"30\" name=\"mod_info\">".$row["info"]."</textarea>\n");
      print("</td>");
      print("</tr>\n");
      print("<tr>\n");
      printf("<td class=\"centered\" colspan=\"2\"><INPUT value=\"".$lang['save_details_to_directory_for_user']."\" class=\"button\" type=\"submit\"></td>\n",$showuserid);
      print("</tr>\n");
      print("</form>\n");
   }
   print("<form method=\"post\" id=\"userexd\" action=\"admin.php?callmodule=".rawurlencode($callmodule)."&showuserid=$showuserid\">\n");
	print("<tr>");
	print("<td colspan=\"2\" class=\"centered\">");
   print("<INPUT name=\"makexdir\" value=\"$showuserid\" type=\"hidden\">\n");
   printf("<INPUT value=\"".$lang['remove_details_from_directory_for_user']."\" class=\"button\" type=\"submit\">\n",$showuserid);
	print("</td>");
	print("</tr>");
   print("</form>");
	print("<tr>");
	print("<td colspan=\"2\" class=\"centered\">");
   // Create photograph upload form
   print("<form enctype=\"multipart/form-data\" action=\"$PHP_SELF?callmodule=$callmodule&showuserid=$showuserid\" method=\"post\">\n");
   print("<input type=\"hidden\" name=\"MAX_FILE_SIZE\" value=\"20000000\">\n");
   print("<input type=\"hidden\" name=\"photo_userid\" value=\"$showuserid\">\n");
   print($lang['upload_a_photo'].": <input name=\"uploadfile\" type=\"file\"><br>\n");
   print("<input class=\"button\" type=\"submit\" value=\"".$lang['upload_photo']."\">\n");
   print("</form>\n");
	print("</td>");
	print("</tr>");
	print("<tr>");
	print("<td colspan=\"2\" class=\"centered\">");
   // Create photograph delete form
   print("<form enctype=\"multipart/form-data\" action=\"$PHP_SELF?callmodule=$callmodule&showuserid=$showuserid\" method=\"post\">\n");
   print("<input type=\"hidden\" name=\"photo_userid\" value=\"$showuserid\">\n");
   print($lang['tick_confirm_delete'].":<input type=\"checkbox\" name=\"delconf\" value=\"confirm\">\n");
   print("<input class=\"button\" type=\"submit\" name=\"delphoto\" value=\"".$lang['delete_photo']."\">\n");
   print("</form>\n");
	print("</td>");
	print("</tr>");
   print("</table>");
}
else
{
   printf("<span class=\"message\">".$lang['user_not_on_system'] ."</span>",$showuserid);
}

$help_keyword="usermanageredit";
?>
