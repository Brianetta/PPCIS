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

// This is a three-section script.  One part performs a search function, and
// is found in filesearch.inc, one part performs directory struture
// listing, the other performs file details information.  The latter two are
// seperated by a big, simple if statement.  The search is seperated by the
// second layer menu.

require("head.inc");


if($userid==0)
{
   print("<h1>".$lang['need_logged_in_files']."</h1>");
   require("tail.inc");
   die("");
}

// Build the second layer menu
unset($module);
$module[$lang['file_browser']]="filebrowser.inc";
$module[$lang['search_for_file']]="filesearch.inc";
if(!(isset($callmodule)))
   $callmodule=$lang['file_browser'];
?>

<table>
<tr>
<?
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
     print("<a class=\"module\"  href=\"$PHP_SELF?callmodule=".rawurlencode($mod_tag)."\">$mod_tag</a></td>\n");
  }
?>
</tr>
</table>
<?
   foreach($module as $modulename => $modulefile)
      if($modulename==$callmodule)
      {
         require($modulefile);
      }

require("tail.inc");
?>
