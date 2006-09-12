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

// This file is a simple form with basic password sanity checking
// to allow the creation of new users.  All records inserted into
// the users table have the password field encrypted with the MySQL
// password() function.

print("<table>");
if(isset($create))
{
   $sql = "SELECT * FROM users";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   if(@ mysql_num_rows($result) != 0)
   {
      while($row = @ mysql_fetch_array($result))
      {
         if($row["username"]==$mod_username)
         {
            printf("<span class=\"message\">".$lang['username_already_in_use_by']."</span>",$mod_username,$row["firstname"],$row["lastname"]);
            $duplicate=true;
         }
      }
      if($mod_username=="")
      {
         print("<span class=\"message\">".$lang['you_need_to_specify_username']."</span>");
         $duplicate=true;
      }
   }
   if (!(isset($duplicate)))
   {
      if($mod_passwd==$mod_confirm) 
      {
         $mod_passwd = safe_escape($mod_passwd);
         $mod_username = safe_escape($mod_username);
         $mod_firstname = safe_escape($mod_firstname);
         $mod_lastname = safe_escape($mod_lastname);
         $sql = "INSERT INTO users (username, password, firstname, lastname) VALUES ('$mod_username', $hash_function('$mod_passwd'), '$mod_firstname', '$mod_lastname')";
         $result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
         print("<span class=\"message\">".$lang['account_successfully_created']."</span>");
      }
      else
      {
         print("<span class=\"message\">".$lang['password_mismatch']."</span>");
      }
   }
}
print("<form method=\"post\" id=\"usermod\" action=\"admin.php?callmodule=".urlencode($lang['new_user'])."&create=yes\">\n");
print("<tr>");
print("<th colspan=\"2\"><h2>");
print($lang['create_new_user']);
print("</th>\n");
print("</tr>\n");
print("<tr>\n");
print("<td class=\"right\">".$lang['username'].":</td>\n");
print("<td><input type=\"text\" size=\"10\" name=\"mod_username\"></td>\n");
print("</tr>\n");
print("<tr>\n");
print("<td class=\"right\">".$lang['firstname'].":</td>\n");
print("<td><input type=\"text\" size=\"25\" name=\"mod_firstname\" value=\"$mod_firstname\"></td>\n");
print("</tr>\n");
print("<tr>\n");
print("<td class=\"right\">".$lang['lastname'].":</td>\n");
print("<td><input type=\"text\" size=\"25\" name=\"mod_lastname\" value=\"".$mod_lastname."\"></td>\n");
print("</tr>\n");
print("<tr>\n");
print("<td class=\"right\">".$lang['enter_password'].":</td>\n");
print("<td><input type=\"password\" name=\"mod_passwd\"></td>\n");
print("</tr>\n");
print("<tr>\n");
print("<td class=\"right\">".$lang['confirm_password'].":</td>\n");
print("<td><input type=\"password\" name=\"mod_confirm\"></td>\n");
print("</tr>\n");
print("<tr>\n");
print("<td colspan=\"2\">&nbsp;</td>\n");
print("</tr>\n");
print("<tr>\n");
print("<td class=\"centered\" colspan=\"2\"><INPUT value=\"".$lang['create_new_user']."\" class=\"button\" type=\"submit\"></td>\n");
print("</tr>\n");
print("</form>\n");
print("</table>");

$help_keyword="newuser";
?>
