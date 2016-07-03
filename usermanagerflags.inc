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

// This file allows useradmins to assign or remove rights from other users.
// Access to this form is secured in admin.php, which is important as any
// user who can run this code can assign themselves rights to any of the
// administrative functions of the system.  If you include this (or any
// code which modifies the userflags table) in any other files, be sure to
// bear this in mind.

if(isset($mod_userid))
{
   if($mod_enabled <> "n") $mod_enabled = "y";
   if($mod_useradmin <> "y") $mod_useradmin = "n";
   if($mod_newsadmin <> "y") $mod_newsadmin = "n";
   if($mod_helpdesk <> "y") $mod_helpdesk = "n";
   if($mod_files <> "y") $mod_files = "n";
   if($mod_directoryadmin <> "y") $mod_directoryadmin = "n";
   if($mod_guest <> "y") $mod_guest = "n";

   // Check that we have at least one admin of each type
   $have_admin = 1;
   foreach (array ('useradmin', 'newsadmin', 'helpdesk', 'files', 'directoryadmin') as $i)
   {
      $sql = "SELECT $i FROM users LEFT JOIN userflags ON users.userid = userflags.userid WHERE $i = 'y' AND users.userid != $mod_userid AND enabled = 'y'";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
      $var = "mod_$i";
      if(@ mysqli_num_rows($result) == 0 && ($mod_enabled != 'y' || $$var != 'y'))
         $have_admin = 0;
   }

   $sql = "UPDATE users SET enabled='$mod_enabled',guest='$mod_guest' WHERE userid = $mod_userid";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();

   if ($have_admin == 0)
      print("<span class=\"message\">".$lang['must_have_admin']."</span>");
   else
   {
      $sql = "REPLACE INTO userflags (userid, useradmin, newsadmin, helpdesk, files, directoryadmin) VALUES ($mod_userid, '$mod_useradmin', '$mod_newsadmin', '$mod_helpdesk', '$mod_files', '$mod_directoryadmin')";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
      print("<span class=\"message\">".$lang['user_successfully_amended']."</span>");
   }
}
$sql = "SELECT *,users.userid AS userid FROM users LEFT JOIN userflags ON users.userid = userflags.userid WHERE users.userid = ".safe_escape($showuserflags);
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   print("<table>");
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      print("<form method=\"post\" id=\"usermod\" action=\"admin.php?callmodule=".rawurlencode($callmodule)."&showuserflags=".$row["userid"]."\">\n");
      print("<input type=\"hidden\" name=\"mod_userid\" value=\"".$row["userid"]."\">");
      print("<tr>");
      print("<th colspan=\"2\"><h2>");
      print($lang['modifying_user'].": ");
      print($row["firstname"] . " " . $row["lastname"] ."</h2></th>");
      print("</tr>\n");
      // All the options in this form's selects have easy-to-understand labels.
      // $sel_yes and $sel_no are for choosing the default selected option.
      foreach (array ('enabled'        => 'enabled',
                      'useradmin'      => 'is_admin',
                      'newsadmin'      => 'is_newsadmin',
                      'directoryadmin' => 'is_directoryadmin',
                      'helpdesk'       => 'is_helpdesk',
                      'files'          => 'is_filesadmin',
                      'guest'          => 'is_guest')
                      as $mod => $langkey)
      {
         print("<tr>\n");
         print("<td class=\"right\">".$lang["user_$langkey"]."</td>\n");
         if($row[$mod]=="y")
         {
            $sel_yes=" selected";
            $sel_no="";
         }
         else
         {
            $sel_yes="";
            $sel_no=" selected";
         }
         print("<td><select name=\"mod_$mod\">");
         print("<option$sel_yes label=\"".$lang["user_${langkey}_yes"]."\" value=\"y\">");
         print("".$lang["user_${langkey}_yes"]."</option>");
         print("<option$sel_no label=\"".$lang["user_${langkey}_no"]."\" value=\"n\">\n");
         print("".$lang["user_${langkey}_no"]."</option></select></td>\n");
         print("</tr>\n");
      }
      print("<tr>\n");
      print("<td colspan=\"2\">&nbsp;</td>\n");
      print("</tr>\n");
      print("<tr>\n");
      printf("<td class=\"centered\" colspan=\"2\"><INPUT value=\"".$lang['save_user_rights_for']."\" class=\"button\" type=\"submit\"></td>\n",$showuserflags);
      print("</tr>\n");
      print("</form>\n");
   }
   print("</table>");
}
else
{
   print("<span class=\"message\">User number $showuserflags is not a user on this system.</span>");
}

$help_keyword="usermanagerflags";
?>
