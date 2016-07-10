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

// This file allowsusers with the useradmin right to change the username and
// password of any user on the system.  Changing the username does not affect
// anything but what the username has to enter in order to log in, as all
// data relating to the user is linked to the user's unique number, the userid.

if(isset($mod_userid))
{
   if($mod_password==$mod_confirm)
   {
      if($mod_username=="")
      {
         print("<span class=\"message\">".$lang['you_need_to_specify_username']."</span>");
      }
      else
      {
         if($mod_password <> "")
         {
            $mod_password = password_hash($mod_password,PASSWORD_DEFAULT);
            $sql = "UPDATE users SET username='$mod_username', password='$mod_password' WHERE userid = $mod_userid";
            $result = @ mysqli_query($intranet_db,$sql);
            if (mysqli_error($intranet_db))
               print("<span class=\"message\">".$lang['username_already_in_use']."</span>");
               // Couldn't possibly be anything else, right?
            else
               print("<span class=\"message\">".$lang['password_changed']."</span>");
         }
      }
   }
   else
   {
      print("<span class=\"message\">".$lang['password_mismatch']."</span>");
   }
}
$sql = "SELECT * FROM users WHERE userid = ".safe_escape($showuserpass);
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   print("<table>");
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      print("<form method=\"post\" id=\"usermod\" action=\"admin.php?callmodule=".rawurlencode($callmodule)."&showuserpass=".$row["userid"]."\">\n");
      print("<input type=\"hidden\" name=\"mod_userid\" value=\"".$row["userid"]."\">");
      print("<tr>");
      print("<th colspan=\"2\"><h2>");
      print("Modifying user: ");
      print($row["firstname"] . " " . $row["lastname"] ."</h2></th>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['username'].":</td>\n");
      print("<td><input type=\"text\" size=\"10\" name=\"mod_username\" value=\"".$row["username"]."\"></td>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['enter_password'].":</td>\n");
      print("<td><input type=\"password\" name=\"mod_password\"></td>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"right\">".$lang['confirm_password'].":</td>\n");
      print("<td><input type=\"password\" name=\"mod_confirm\"></td>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td colspan=\"2\">&nbsp;</td>\n");
      print("</tr>\n");
      print("<tr>\n");
      printf("<td class=\"centered\" colspan=\"2\"><input value=\"".$lang['set_password_for_user']."\" class=\"button\" type=\"submit\"></td>\n",$showuserpass);
      print("</tr>\n");
      print("</form>\n");
   }
   print("</table>");
}
else
{
   printf("<span class=\"message\">".$lang['user_not_on_system']."</span>",$showuserpass);
}

$help_keyword="usermanagerpass";
?>
