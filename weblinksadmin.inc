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
// in the webcategory table.

$sql = "SELECT * FROM webcategory ORDER BY name";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      $webc[$row["categoryid"]]=$row["name"];
   }
}
else
{
   $webc[1]="No categories defined";
}

if(isset($mod_title))
{
   if(isset($mod_link))
   {
      $sql = "UPDATE weblinks SET title='".safe_escape($mod_title)."',url='".safe_escape($mod_url)."',description='".safe_escape($mod_description)."',category=$mod_category WHERE linkid=$mod_link";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
   }
   if(isset($del_link))
   {
      $sql = "DELETE FROM weblinks WHERE linkid='$del_link' LIMIT 1";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
   }
   if(isset($ins_link))
      if($mod_title!="")
      {
         $sql = "INSERT INTO weblinks (title,url,description,category) VALUES ('".safe_escape($mod_title)."','".safe_escape($mod_url)."','".safe_escape($mod_description)."',$mod_category)";
         $result = @ mysqli_query($intranet_db,$sql);
         showerror();
      }
}

print("<table>\n");
print("<tr><td colspan=\"6\"><i>".$lang['take_care_no_confirm']."</i></td></tr>\n");
$sql = "SELECT * FROM weblinks ORDER BY title";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
print("<tr><th class=\"list\">".$lang['name']."</th><th class=\"list\">".$lang['url']."</th><th class=\"list\">".$lang['description']."</th><th class=\"list\">".$lang['category']."</th><th class=\"list\" colspan=\"2\">&nbsp;</th></tr>\n");
print("<tr>\n");
print("<form id=\"loc".$row["linkid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
print("<td class=\"list\">\n");
print("<input type=\"hidden\" name=\"ins_link\" value=\"yes\">\n");
print("<input type=\"text\" size=\"25\" name=\"mod_title\" value=\"\">");
print("</td>\n");
print("<td class=\"list\">\n");
print("<input type=\"text\" size=\"25\" name=\"mod_url\" value=\"http://\">");
print("</td>\n");
print("<td class=\"list\">\n");
print("<input type=\"text\" size=\"25\" name=\"mod_description\" value=\"\">");
print("</td>\n");
print("<td class=\"list\">\n");
print("<select name=\"mod_category\">\n");
foreach($webc as $category => $name)
{
   if($row["category"]==$webc)
   {
      print("<option selected label=\"$name\" value=\"$categoryid\">$name</option>\n");
   }
   else
   {
      print("<option label=\"$name\" value=\"$category\">$name</option>\n");
   }
}
print("</select>\n");
print("</td>\n");
print("<td class=\"list\" colspan=\"2\">\n");
print("<input class=\"button\" type=\"submit\" value=\"".$lang['add_new']."\">");
print("</td>\n");
print("</tr>\n");
print("</form>");

if(@ mysqli_num_rows($result) != 0)
{

   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      print("<tr>\n");
      print("<form id=\"loc".$row["linkid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
      print("<td class=\"list\">\n");
      print("<input type=\"hidden\" name=\"mod_link\" value=\"".$row["linkid"]."\">\n");
      print("<input type=\"text\" size=\"25\" name=\"mod_title\" value=\"".$row["title"]."\">");
      print("</td>\n");
      print("<td class=\"list\">\n");
      print("<input type=\"text\" size=\"25\" name=\"mod_url\" value=\"".$row["url"]."\">");
      print("</td>\n");
      print("<td class=\"list\">\n");
      print("<input type=\"text\" size=\"25\" name=\"mod_description\" value=\"".$row["description"]."\">");
      print("</td>\n");
      print("<td class=\"list\">\n");
      print("<select name=\"mod_category\">\n");
      foreach($webc as $category => $name)
      {
         if($row["category"]==$category)
         {
            print("<option selected label=\"$name\" value=\"$category\">$name</option>\n");
         }
         else
         {
            print("<option label=\"$name\" value=\"$category\">$name</option>\n");
         }
      }
      print("</select>\n");
      print("</td>\n");
      print("<td class=\"list\">\n");
      print("<input class=\"button\" type=\"submit\" value=\"".$lang['modify']."\">");
      print("</td>\n");
      print("</form>");
      print("<form id=\"dloc".$row["linkid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
      print("<td class=\"list\">\n");
      print("<input type=\"hidden\" name=\"del_link\" value=\"".$row["linkid"]."\">\n");
      print("<input type=\"hidden\" name=\"mod_title\" value=\"".$row["name"]."\">\n");
      print("<input class=\"button\" type=\"submit\" value=\"".$lang['delete']."\">");
      print("</td>\n");
      print("</form>");
      print("</tr>\n");
   }
}
print("</table>\n");

$help_keyword="weblinksadmin";
?>
