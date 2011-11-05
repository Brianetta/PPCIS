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

// Form to totally remove a user from the system.  Confirmation is not
// required again as the useradmin already clicked delete to get here.

if(isset($mod_userid) && $mod_userid == $userid)
{
   print("<span class=\"message\">You can not delete your own account!</span><br>\n");
}
else if(isset($mod_userid))
{
   $sql = "DELETE FROM users WHERE userid = $mod_userid";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
   {
      showerror();
   } else {
      print("<span class=\"message\">User account number $mod_userid has been successfully deleted.</span><br>\n");
   }
   $sql = "DELETE FROM userdirectory WHERE userid = $mod_userid";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
   {
      showerror();
   } else {
      printf("<span class=\"message\">".$lang['user_deleted_directory']."</span><br>\n",$mod_userid);
   }
   $sql = "DELETE FROM userflags WHERE userid = $mod_userid";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
   {
      showerror();
   } else {
      printf("<span class=\"message\">".$lang['user_deleted_rights']."<br></span>\n",$mod_userid);
   }
   $sql = "DELETE FROM userteams WHERE userid = $mod_userid";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
   {
      showerror();
   } else {
      printf("<span class=\"message\">".$lang['user_deleted_teams']."</span><br>\n",$mod_userid);
   }
   if (is_writeable($file_store.$fileid))
   {
      @ unlink($file_store."p".$fileid);
      printf("<span class=\"message\">".$lang['user_deleted_photo']."</span><br>\n",$mod_userid);
   }
}
else
{
   $sql = "SELECT * FROM users WHERE userid = $deleteuser";
   $result = @ mysql_query($sql, $intranet_db);
   $row = mysql_fetch_array($result);
   if (mysql_error())
      showerror();
   printf("<h2>".$lang['confirm_delete']."</h2>\n".$lang['confirm_delete_user'],$row["firstname"],$row["lastname"]);
   print("<form method=\"post\" id=\"usermod\" action=\"admin.php?callmodule=".rawurlencode($callmodule)."&deleteuser=yes\">\n");
   print("<input type=\"hidden\" name=\"mod_userid\" value=\"$deleteuser\">");
   print("<input class=\"button\" type=\"submit\" name=\"delete\" value=\"".$lang['delete_user']."\">");
   print("</form>\n");
}

$help_keyword="deleteuser";
?>
