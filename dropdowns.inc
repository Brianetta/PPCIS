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

// This file uses multiple forms to allow admins to alter the rows
// in the locations and the teams tables.

if(isset($mod_name))
{
   if(isset($mod_locationid))
   {
      $sql = "UPDATE locations SET name='".safe_escape($mod_name)."' WHERE locationid='$mod_locationid'";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
   }
   if(isset($mod_teamid))
   {
      $sql = "UPDATE teams SET name='".safe_escape($mod_name)."' WHERE teamid='$mod_teamid'";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
   }
   if(isset($del_locationid))
   {
      $sql = "DELETE FROM locations WHERE locationid='$del_locationid' LIMIT 1";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
   }
   if(isset($del_teamid))
   {
      $sql = "DELETE FROM teams WHERE teamid='$del_teamid' LIMIT 1";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
   }
   if(isset($ins_locationid))
      if($mod_name!="")
      {
         $sql = "INSERT INTO locations (name) VALUES ('".safe_escape($mod_name)."')";
         $result = @ mysqli_query($intranet_db,$sql);
         showerror();
      }
   if(isset($ins_teamid))
      if($mod_name!="")
      {
         $sql = "INSERT INTO teams (name) VALUES ('".safe_escape($mod_name)."')";
         $result = @ mysqli_query($intranet_db,$sql);
         showerror();
      }
}

print("<table>\n");
print("<tr><td colspan=\"2\"><i>".$lang['take_care_no_confirm']."</i></td></tr>\n");
print("<tr><td class=\"page_div\">\n");
print("<table>\n");
print("<tr><td class=\"centered\" colspan=\"3\"><b>".$lang['teams']."</b></td></tr>\n");
$sql = "SELECT * FROM teams ORDER BY name";
$result = @ mysqli_query($intranet_db,$sql);
showerror();

print("<tr>\n");
print("<form id=\"loc".$row["teamid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
print("<td class=\"right\">\n");
print("<input type=\"hidden\" name=\"ins_teamid\" value=\"yes\">\n");
print("<input type=\"text\" size=\"25\" name=\"mod_name\" value=\"\">");
print("</td>\n");
print("<td colspan=\"2\">\n");
print("<input class=\"button\" type=\"submit\" value=\"".$lang['add_new']."\">");
print("</td>\n");
print("</tr>\n");
print("</form>");

if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      print("<tr>\n");
      print("<form id=\"loc".$row["teamid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
      print("<td class=\"right\">\n");
      print("<input type=\"hidden\" name=\"mod_teamid\" value=\"".$row["teamid"]."\">\n");
      print("<input type=\"text\" size=\"25\" name=\"mod_name\" value=\"".$row["name"]."\">");
      print("</td>\n");
      print("<td>\n");
      print("<input class=\"button\" type=\"submit\" value=\"".$lang['rename']."\">");
      print("</td>\n");
      print("</form>");
      print("<form id=\"dloc".$row["teamid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
      print("<td>\n");
      print("<input type=\"hidden\" name=\"del_teamid\" value=\"".$row["teamid"]."\">\n");
      print("<input type=\"hidden\" name=\"mod_name\" value=\"".$row["name"]."\">\n");
      print("<input class=\"button\" type=\"submit\" value=\"".$lang['delete']."\">");
      print("</td>\n");
      print("</form>");
      print("</tr>\n");
   }
}
print("</table>\n");
print("</td>\n");

print("<td class=\"page_div\">\n");
print("<table>\n");
print("<tr><td class=\"centered\" colspan=\"3\"><b>".$lang['locations']."</b></td></tr>\n");
$sql = "SELECT * FROM locations ORDER BY name";
$result = @ mysqli_query($intranet_db,$sql);
showerror();

print("<tr>\n");
print("<form id=\"loc".$row["locationid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
print("<td class=\"right\">\n");
print("<input type=\"hidden\" name=\"ins_locationid\" value=\"yes\">\n");
print("<input type=\"text\" size=\"25\" name=\"mod_name\" value=\"\">");
print("</td>\n");
print("<td colspan=\"2\">\n");
print("<input class=\"button\" type=\"submit\" value=\"".$lang['add_new']."\">");
print("</td>\n");
print("</tr>\n");
print("</form>");

if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      print("<tr>\n");
      print("<form id=\"loc".$row["locationid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
      print("<td class=\"right\">\n");
      print("<input type=\"hidden\" name=\"mod_locationid\" value=\"".$row["locationid"]."\">\n");
      print("<input type=\"text\" size=\"25\" name=\"mod_name\" value=\"".$row["name"]."\">");
      print("</td>\n");
      print("<td>\n");
      print("<input class=\"button\" type=\"submit\" value=\"".$lang['rename']."\">");
      print("</td>\n");
      print("</form>\n");
      print("<form id=\"delloc".$row["locationid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
      print("<td>\n");
      print("<input type=\"hidden\" name=\"del_locationid\" value=\"".$row["locationid"]."\">\n");
      print("<input type=\"hidden\" name=\"mod_name\" value=\"".$row["name"]."\">\n");
      print("<input class=\"button\" type=\"submit\" value=\"".$lang['delete']."\">");
      print("</td>\n");
      print("</form>\n");
      print("</tr>\n");
   }
}
print("</table>\n");
print("</td></tr>\n");
print("<table>\n");

$help_keyword="dropdowns";
?>
