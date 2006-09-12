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

// This file simply outputs a sorted list, filterable by category, of all the
// record in the weblinks table.  The namesare made into HTML links to the URLs.

if(!(isset($category)))$category="0";
print("<form method=\"post\" id=\"web_submit\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
print("<select name=\"webcat\">\n");
print("<option label=\"".$lang['all_categories']."\" value=\"0\">".$lang['all_categories']."</option>\n");
$sql = "SELECT * FROM webcategory ORDER BY name";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   while($row = @ mysql_fetch_array($result))
   {
      if($row["categoryid"]==$webcat)
      {
         print("<option selected label=\"".$row["name"]."\" value=\"".$row["categoryid"]."\">".$row["name"]."</option>\n");
      }
      else
      {
         print("<option label=\"".$row["name"]."\" value=\"".$row["categoryid"]."\">".$row["name"]."</option>\n");
      }
   }
}
print("</select>\n");
print("<input class=\"button\" type=\"submit\" name=\"topicfilter\" value=\"".$lang['filter']."\">");
print("</form>\n");

$sql = "SELECT * FROM weblinks LEFT JOIN webcategory ON weblinks.category = webcategory.categoryid ";
$where = "";
if(isset($webcat))
   if($webcat!=0)
      $where = $where . "weblinks.category = $webcat ";
if($where<>"") $where="WHERE ".$where;
$sql = $sql . $where . "ORDER BY title";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   print("<table>\n");
   print("<tr>\n");
   print("<th class=\"list\">".$lang['name']."</th>\n");
   print("<th class=\"list\">".$lang['url']."</th>\n");
   print("<th class=\"list\">".$lang['description']."</th>\n");
   print("<th class=\"list\">".$lang['category']."</th>\n");
   print("</tr>\n");
   while($row = @ mysql_fetch_array($result))
   {
      if(strlen($row["name"])==0)
         $row["name"]=$lang['no_categories_defined'];
      print("<tr>\n");
      $surl=$row["url"];
      print("<td class=\"list\"><a href=\"$surl\">" . $row["title"] . "</a></td>\n");
      print("<td class=\"list\">$surl</td>\n");
      print("<td class=\"list\">" . $row["description"] . "</td>\n");
      print("<td class=\"list_center\">" . $row["name"] . "</td>\n");
      print("</tr>\n");
   }
   print("</table>\n");
}
$help_keyword="webdirectory";
?>
