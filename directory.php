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

// This file is a module which builds the second layer directory menu
// and includes other files in order to fulfill the functions
// selected from that menu.

require("head.inc");
if($userid==0)
{
   print("<h1>".$lang['need_logged_in_directory']."</h1>");
   require("tail.inc");
   die("");
}

// Build the second layer menu
unset($module);
$module[$lang['internal_directory']]="directorylist.inc";
$module[$lang['external_directory']]="extdirlist.inc";
$module[$lang['website_directory']]="webdirectory.inc";
if(!(isset($callmodule)))
   $callmodule=$lang['internal_directory'];

?>

      <table>
        <tr>
        <?php
          $mod_percent=100 / count($module);
          foreach($module as $mod_tag=>$mod_file) // Render the second layer menu
          {
            if($callmodule==$mod_tag)
            {
               $valid=true;
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
          <?php
            switch ($callmodule) // Include the correct file depending on the menu selection
            {
            case $lang['internal_directory']:
               if(isset($showuserid))
               {
                  require("directorydetail.inc");
               }
               else
               {
                  require($module[$lang['internal_directory']]);
               }
               break;
            case $lang['website_directory']:
               require($module[$lang['website_directory']]);
               break;
            default:
               if(isset($showuserid))
               {
                  require("extdirdetail.inc");
               }
               else
               {
                  require($module[$lang['external_directory']]);
               }
            }
          ?>

<?php
require("tail.inc");
?>
