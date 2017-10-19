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

// By default, this is called from the banner, but if the banner is modified
// this script can be included as a module.

require("head.inc");
// Guest users cannot change their own password.
if(isset($mod_userid))
{
   $sql = "SELECT * FROM users WHERE userid = $userid";
   $result = @ mysqli_query($intranet_db, $sql);
   showerror();
   if(@ mysqli_num_rows($result) != 0)
   {
      while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
      {
         if($row["enabled"]=='y' and password_verify($old_password, $row["password"]))
         {
            if(($mod_password==$mod_confirm) AND ($mod_password<>"")) // Make sure new password was typed twice, and isn't null
            {
               if($mod_password <> "") $mod_password = password_hash($mod_password,PASSWORD_DEFAULT);
               $sql = "UPDATE users SET password='$mod_password' WHERE userid = $mod_userid";
               $updateresult = @ mysqli_query($intranet_db,$sql);
               showerror();
               if( @ mysqli_affected_rows($intranet_db) != 0)
               {
                  print("<span class=\"message\">".$lang['your_password_changed']."</span>");
               }
            }
            else
            {
               print("<span class=\"message\">".$lang['password_change_mismatch']."</span>");
            }
         }
         else
         {
            print("<span class=\"message\">".$lang['password_change_wrong']."</span>");
         }
      }
   }
}
$sql = "SELECT * FROM users WHERE userid = $userid and guest = 'n'";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   print("<table>");
   $row = @ mysqli_fetch_array($result,MYSQLI_ASSOC); // Get user info.  User must confirm old password.
   print("<form method=\"post\" id=\"usermod\" action=\"$PHP_SELF\">\n");
   print("<input type=\"hidden\" name=\"mod_userid\" value=\"".$row["userid"]."\">");
   print("<tr>");
   print("<th colspan=\"2\"><h2>");
   print("Modifying user: ");
   print($row["firstname"] . " " . $row["lastname"] ."</h2></th>");
   print("</tr>\n");
   print("<tr>\n");
   print("<td class=\"right\">".$lang['your_username'].":</td>\n");
   print("<td>".$row["username"]."</td>\n");
   print("</tr>\n");
   print("<tr>\n");
   print("<td class=\"right\">".$lang['enter_current_password'].":</td>\n");
   print("<td><input type=\"password\" name=\"old_password\"></td>\n");
   print("</tr>\n");
   print("<tr>\n");
   print("<td class=\"right\">".$lang['enter_new_password'].":</td>\n");
   print("<td><input type=\"password\" name=\"mod_password\"></td>\n");
   print("</tr>\n");
   print("<tr>\n");
   print("<td class=\"right\">".$lang['confirm_new_password'].":</td>\n");
   print("<td><input type=\"password\" name=\"mod_confirm\"></td>\n");
   print("</tr>\n");
   print("<tr>\n");
   print("<td colspan=\"2\">&nbsp;</td>\n");
   print("</tr>\n");
   print("<tr>\n");
   print("<td class=\"centered\" colspan=\"2\"><INPUT value=\"".$lang['set_password']."\" class=\"button\" type=\"submit\"></td>\n");
   print("</tr>\n");
   print("</form>\n");
   print("</table>");
}
else
{
   print("<h2 align=\"center\">".$lang['guests_cant_change_password']."</h2>");
}
$help_keyword="password";

require("tail.inc");
?>
