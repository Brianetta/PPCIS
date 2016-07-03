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

// This file is a module which builds the second layer helpdesk menu
// and includes other files in order to fulfill the functions
// selected from that menu.

require("head.inc");

if($userid==0)
{
   print("<h1>".$lang['need_logged_in_helpdesk']."</h1>");
   require("tail.inc");
   die("");
}

unset($helpdeskadmin);
// Set a variable so we know the rights of the logged in user
$sql = "SELECT helpdesk FROM userflags WHERE userid = $userid";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      if($row["helpdesk"]=="y")
      {
         $helpdeskadmin=true;
      }
      else
      {
         $helpdeskadmin=false;
      }
   }
}

// Build the second layer menu, based on user rights
unset($module);
$module[$lang['manage_calls']]="viewcalls.inc";
$module[$lang['log_new_call']]="logcall.inc";
$module[$lang['search']]="helpsearch.inc";
$module[$lang['faq']]="helpdeskfaq.inc";
if($helpdeskadmin)
   $module[$lang['edit_faqs']]="faqadmin.inc";

if(!(isset($callmodule)))
   $callmodule=$lang['manage_calls'];

// Build an array to cache all the users' names in the users table
$sql = "SELECT userid, firstname, lastname FROM users ORDER BY lastname";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      $userhash[$row["userid"]]=$row["firstname"]." ".$row["lastname"];
      $userrevhash[$row["userid"]]=$row["lastname"].", ".$row["firstname"];
   }
}

// Build an array to cache all the faq categories
$sql = "SELECT * FROM faqcategory ORDER BY name";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      $faqc[$row["categoryid"]]=$row["name"];
   }
}
else
{
   $faqc[1]=$lang['no_categories_defined'];
}

// Build an array to cache all the call categories
$sql = "SELECT * FROM callcategory ORDER BY name";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      $callc[$row["categoryid"]]=$row["name"];
   }
}
else
{
   $callc[1]=$lang['no_categories_defined'];
}

// Build an array to cache all the locations
$sql = "SELECT * FROM locations ORDER BY name";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      $locations[$row["locationid"]]=$row["name"];
   }
}
else
{
   $locations[1]=$lang['no_locations_defined'];
}

// Hard-coded array of call priorities.
$priority[0]=$lang['waiting'];
$priority[1]=$lang['immediate'];
$priority[2]=$lang['very_important'];
$priority[3]=$lang['important'];
$priority[4]=$lang['standard'];
$priority[5]=$lang['less_important'];
$priority[6]=$lang['not_important'];
$priority[9]=$lang['parked'];
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
<? // Include the relevant file as selected from the menu
if(isset($valid))
{
   require($module["$callmodule"]);
}
require("tail.inc");
?>
