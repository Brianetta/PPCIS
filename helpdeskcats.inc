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

// This file uses multiple forms to allow admins to alter the rows
// in the faqcategory and the callcategory tables.

if(isset($mod_name))
{
   if(isset($mod_faqcid))
   {
      $sql = "UPDATE faqcategory SET name='".safe_escape($mod_name)."' WHERE categoryid='$mod_faqcid'";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
   }
   if(isset($mod_callcid))
   {
      $sql = "UPDATE callcategory SET name='".safe_escape($mod_name)."' WHERE categoryid='$mod_callcid'";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
   }
   if(isset($del_faqcid))
   {
      $sql = "DELETE FROM faqcategory WHERE categoryid='$del_faqcid' LIMIT 1";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
   }
   if(isset($del_callcid))
   {
      $sql = "DELETE FROM callcategory WHERE categoryid='$del_callcid' LIMIT 1";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
   }
   if(isset($ins_faqcid))
      if($mod_name!="")
      {
         $sql = "INSERT INTO faqcategory (name) VALUES ('".safe_escape($mod_name)."')";
         $result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
      }
   if(isset($ins_callcid))
      if($mod_name!="")
      {
         $sql = "INSERT INTO callcategory (name) VALUES ('".safe_escape($mod_name)."')";
         $result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
      }
}

print("<table>\n");
print("<tr><td colspan=\"2\"><i>".$lang['take_care_no_confirm']."</i></td></tr>\n");
print("<tr>");
print("<td class=\"page_div\">\n");
print("<table>\n");
print("<tr><td class=\"centered\" colspan=\"3\"><b>".$lang['call_types']."</b></td></tr>\n");
$sql = "SELECT * FROM callcategory ORDER BY name";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();

print("<tr>\n");
print("<form id=\"loc".$row["categoryid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
print("<td class=\"right\">\n");
print("<input type=\"hidden\" name=\"ins_callcid\" value=\"yes\">\n");
print("<input type=\"text\" size=\"25\" name=\"mod_name\" value=\"\">");
print("</td>\n");
print("<td colspan=\"2\">\n");
print("<input class=\"button\" type=\"submit\" value=\"".$lang['add_new']."\">");
print("</td>\n");
print("</tr>\n");
print("</form>");

if(@ mysql_num_rows($result) != 0)
{
   while($row = @ mysql_fetch_array($result))
   {
      print("<tr>\n");
      print("<form id=\"loc".$row["categoryid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
      print("<td class=\"right\">\n");
      print("<input type=\"hidden\" name=\"mod_callcid\" value=\"".$row["categoryid"]."\">\n");
      print("<input type=\"text\" size=\"25\" name=\"mod_name\" value=\"".$row["name"]."\">");
      print("</td>\n");
      print("<td>\n");
      print("<input class=\"button\" type=\"submit\" value=\"".$lang['rename']."\">");
      print("</td>\n");
      print("</form>");
      print("<form id=\"dloc".$row["categoryid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
      print("<td>\n");
      print("<input type=\"hidden\" name=\"del_callcid\" value=\"".$row["categoryid"]."\">\n");
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
print("<tr><td class=\"centered\" colspan=\"3\"><b>".$lang['faq_categories']."</b></td></tr>\n");
$sql = "SELECT * FROM faqcategory ORDER BY name";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();

print("<tr>\n");
print("<form id=\"loc".$row["categoryid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
print("<td class=\"right\">\n");
print("<input type=\"hidden\" name=\"ins_faqcid\" value=\"yes\">\n");
print("<input type=\"text\" size=\"25\" name=\"mod_name\" value=\"\">");
print("</td>\n");
print("<td colspan=\"2\">\n");
print("<input class=\"button\" type=\"submit\" value=\"".$lang['add_new']."\">");
print("</td>\n");
print("</tr>\n");
print("</form>");

if(@ mysql_num_rows($result) != 0)
{
   while($row = @ mysql_fetch_array($result))
   {
      print("<tr>\n");
      print("<form id=\"loc".$row["categoryid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
      print("<td class=\"right\">\n");
      print("<input type=\"hidden\" name=\"mod_faqcid\" value=\"".$row["categoryid"]."\">\n");
      print("<input type=\"text\" size=\"25\" name=\"mod_name\" value=\"".$row["name"]."\">");
      print("</td>\n");
      print("<td>\n");
      print("<input class=\"button\" type=\"submit\" value=\"".$lang['rename']."\">");
      print("</td>\n");
      print("</form>\n");
      print("<form id=\"delloc".$row["categoryid"]."\" method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
      print("<td>\n");
      print("<input type=\"hidden\" name=\"del_faqcid\" value=\"".$row["categoryid"]."\">\n");
      print("<input type=\"hidden\" name=\"mod_name\" value=\"".$row["name"]."\">\n");
      print("<input class=\"button\" type=\"submit\" value=\"".$lang['delete']."\">");
      print("</td>\n");
      print("</form>\n");
      print("</tr>\n");
   }
}
print("</table>\n");
print("</td>\n");

print("</tr>\n");
print("</table>\n");

$help_keyword="helpdeskcats";
?>
