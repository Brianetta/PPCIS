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

// This file is a module which builds the second layer admin menu
// and includes other files in order to fulfill the functions
// selected from that menu.

require("head.inc");

if($userid==0) // User is not logged in
{
   print("<div class=\"main\">");
   print("<h1>".$lang['need_logged_in_admin']."</h1>");
   print("</div>");
   require("tail.inc"); // Close all the open HTML tags
   die(""); // End this script here
}

// Based on the user's rights, taken from userflags, build up the
// second layer menu in the admin module.  This re-uses the module
// array.
unset($module);
$sql = "SELECT userflags.*,guest FROM users LEFT JOIN userflags ON users.userid=userflags.userid WHERE users.userid = $userid";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {  // This bunch of ifs provides nearly all the security.  If it's not assigned to $module, it can't be loaded.
      if($row["guest"]=="n")
      {
         $adminok=true;
         $module[$lang['alter_your_directory']]="usermanageredit.inc";
         $module[$lang['preferences']]="preferences.inc";
         if(!(isset($callmodule)))
         {
            $callmodule=$lang['alter_your_directory'];
         }
     }
      if($row["useradmin"]=="y")
      {
         $adminok=true;
         $module[$lang['user_manager']]="usermanager.inc";
         $module[$lang['new_user']]="newuser.inc";
         $module[$lang['teams_and_locations']]="dropdowns.inc";
         if(!(isset($callmodule)))
         {
            $callmodule=$lang['user_manager'];
         }
      }
      if($row["directoryadmin"]=="y")
      {
         $adminok=true;
         $module[$lang['directory_admin']]="directoryadmin.inc";
         $module[$lang['external_directory_admin']]="extdiradmin.inc";
         $module[$lang['teams_and_locations']]="dropdowns.inc";
         $module[$lang['website_admin']]="weblinksadmin.inc";
         $module[$lang['web_contact_categories']]="webcategories.inc";
         if(!(isset($callmodule)))
         {
            $callmodule=$lang['directory_admin'];
         }
      }
      if($row["newsadmin"]=="y")
      {
         $adminok=true;
         $module[$lang['news_admin']]="newsadmin.inc";
         $module[$lang['news_topics']]="newstopics.inc";
         if(!(isset($callmodule)))
         {
            $callmodule=$lang['news_admin'];
         }
      }
      if($row["helpdesk"]=="y")
      {
         $adminok=true;
         $module[$lang['helpdesk_categories']]="helpdeskcats.inc";
         $module[$lang['teams_and_locations']]="dropdowns.inc";
         if(!(isset($callmodule)))
         {
            $callmodule=$lang['helpdesk_categories'];
         }
      }
      if(!(isset($adminok)))
      {
         $module[$lang['no_admin_available']]="no_admin.inc";
         $callmodule=$lang['no_admin_available'];
      }
   }
}
else
{
   $module[$lang['no_admin_available']]="no_admin.inc";
   $callmodule=$lang['no_admin_available'];
}
?>

      <table>
        <tr>
        <? // Render the menu, highlighting the current option
          $mod_percent=100 / count($module);
          $valid=false;
          foreach($module as $mod_tag=>$mod_file)
          {
            if($callmodule==$mod_tag)
            {
               $valid=true; // Make sure the module is valid for the current user
               print("<th class=\"module_selected\" width=\"$mod_percent%\">");
            }
            else
            {
               print("<th class=\"module\" width=\"$mod_percent%\">");
            }
            print("<a class=\"module\"  href=\"$PHP_SELF?callmodule=".rawurlencode($mod_tag)."\">$mod_tag</a></th>\n");
          }
        ?>
        </tr>
      </table>
          <? // Now we include the module that's currently selected.
            if($callmodule==$lang['alter_your_directory'])
              $showuserid=$userid;
            if(isset($valid))
            {
               print("<div class=\"main\">");
               require($module["$callmodule"]);
               print("</div>");
            }
require("tail.inc");
?>
