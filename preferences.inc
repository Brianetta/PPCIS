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

// This file allows a user to specify their own stylesheet fron the choice
// provided (allowing a company to specify accessible versions of their
// corporate look to those who need them) and alternative languages where
// installed.

// We know that users who aren't logged in or who are guests won't
// be able to include this file
if(isset($update_prefs))
{
   if(isset($stylesheets["$newsheet"]))
      $stylesheet = $stylesheets["$newsheet"];
   if(isset($lang_available["$newlanguage"]))
      $language = $lang_available["$newlanguage"];
   $sql = "REPLACE INTO preferences (userid, stylesheet, language) VALUES ($userid, '$stylesheet', '$language')";
   $result = mysqli_query($intranet_db,$sql);
   if (mysqli_affected_rows($intranet_db) > 1)
      print("<span class=\"message\">Preferences updated</span>");
}
print("<form action=\"$PHP_SELF?callmodule=$callmodule\" method=\"post\" id=\"prefs\">\n");
print("<table>\n<tr>\n<td colspan=\"2\">");
print("<h1>".$lang['your_preferences']."</h1>");
print("</td>\n</tr>\n<tr>\n");

print("<td class=\"right\" width=\"50%\">\n");
print($lang['select_theme'].":");
print("</td>\n");

print("<td>\n");
print("<select name=\"newsheet\">\n");
foreach($stylesheets as $name => $sheet)
{
   if($stylesheet == $sheet)
      print("<option selected value=\"$name\">");
   else
      print("<option value=\"$name\">");
   print("$name");
   print("</option>\n");
}
print("</select>\n");
print("</td>\n");
print("</tr>\n<tr>\n");
print("<td class=\"right\">\n");
print($lang['select_language'].":");
print("</td>\n");

print("<td>\n");
print("<select name=\"newlanguage\">\n");
foreach($lang_available as $name => $code)
{
   if($code==$language)
      print("<option selected value=\"$name\">");
   else
      print("<option value=\"$name\">");
   print("$name");
   print("</option>\n");
}
print("</select>\n");
print("</td>\n");
print("</tr>\n<tr>\n");
print("<td class=\"centered\" colspan=\"2\">\n");
print("<input type=\"submit\" name=\"update_prefs\" value=\"".$lang['set_preferences']."\">");
print("</td>\n");

print("</tr>\n</table>\n");
print("</form>\n");
$help_keyword="preferences";
