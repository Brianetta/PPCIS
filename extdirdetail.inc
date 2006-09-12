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

// This file displays all of the details of a given external contact.
// It is included from another file, which is responsible for
// supplying most of the variables used herein.

// Build an array to cache all the contact types
$sql = "SELECT * FROM contacttype ORDER BY description";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   while($row = @ mysql_fetch_array($result))
   {
      $ctype[$row["contacttype"]]=$row["description"];
   }
}
else
{
   $ctype[1]=$lang['no_contact_type_defined'];
}


$sql = "SELECT * FROM externalcontact WHERE ref = ".safe_escape($showuserid);
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   print("<table>");
   while($row = @ mysql_fetch_array($result))
   {
      print("<tr>");
      print("<th colspan=\"3\"><h2>");
      print($row["firstname"] . " " . $row["surname"]);
      if(isset($row["title"]))
         print(" - ".$row["title"]);
      print("</h2>".$ctype[$row["contacttype"]]."</th>");
      print("</tr>\n");
      print("<tr>\n");
      print("<th class=\"detail\">".$lang['telephone_number']."</th>\n");
      print("<th class=\"detail\">".$lang['company']."</th>\n");
      print("<th class=\"detail\">".$lang['fax']."</th>\n");
      print("</th>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"detail\">");
      if(isset($row["telephone"]))
      {
         print($row["telephone"]);
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>");
      print("<td class=\"detail\">");
      if(isset($row["company"]))
      {
         print($row["company"]);
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>");
      print("<td class=\"detail\">");
      if(isset($row["fax"]))
      {
         print($row["fax"]);
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td colspan=\"3\">&nbsp;</td>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<th class=\"detail\">".$lang['email_address']."</th>\n");
      print("<th class=\"detail\">".$lang['website']."</th>\n");
      print("<th class=\"detail\">".$lang['address']."</th>\n");
      print("</tr>\n");
      print("<td class=\"detail\">");
      if(isset($row["email"]))
      {
         print("<a href=\"mailto:". $row["firstname"] . " " . $row["surname"] . " <" . $row["email"] . ">\">" . $row["email"] ."</a>");
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>");
      print("<td class=\"detail\">");
      if(isset($row["website"]))
      {
         print("<a href=\"".$row["website"]."\">".$row["website"]."</a>");
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>");
      print("<td class=\"detail\">");
      if(isset($row["address1"]))
         print($row["address1"]."<br>\n");
      if(isset($row["address2"]))
         print($row["address2"]."<br>\n");
      if(isset($row["address3"]))
         print($row["address3"]."<br>\n");
      if(isset($row["town"]))
         print($row["town"]."<br>\n");
      if(isset($row["county"]))
         print($row["county"]."<br>\n");
      if(isset($row["postcode"]))
         print($row["postcode"]."<br>\n");
      print("</td>");
      print("</tr>\n");
   }
   print("</table>");
}
else
{
   printf("<span class=\"message\">".$lang['contact_not_in_ext_dir']."</span>",$showuserid);
}
$help_keyword="extdirdetail";
?>
