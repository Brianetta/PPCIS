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

// This file displays all of the details of a given user if that user
// has a record in userdirectory.  It is included from another file,
// which is responsible for supplying most of the variables used herein.

$sql = "SELECT * FROM users, userdirectory WHERE users.userid = ".safe_escape($showuserid)." AND users.userid = userdirectory.userid ORDER BY lastname, firstname";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   print("<table>");
   while($row = @ mysql_fetch_array($result))
   {
      print("<tr>");
      print("<th colspan=\"4\"><h2>");
      if(isset($row["title"]))
         print($row["title"] . " ");
      print($row["firstname"] . " " . $row["lastname"] ."</h2></th>");
      print("</tr>\n");
      print("<tr>\n");
      print("<th class=\"detail\">".$lang['telephone_number']."</th>\n");
      print("<th class=\"detail\">".$lang['mobile_number']."</th>\n");
      print("<th colspan=\"2\" class=\"detail\">".$lang['email_address']."</th>\n");
      print("</th>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"detail_center\">");
      if(isset($row["telephone"]))
      {
         print($row["telephone"]);
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>");
      print("<td class=\"detail_center\">");
      if(isset($row["mobile"]))
      {
         print($row["mobile"]);
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>");
      print("<td colspan=\"2\" class=\"detail_center\">");
      if(isset($row["email"]))
      {
         print("<a href=\"mailto:". $row["firstname"] . " " . $row["lastname"] . " <" . $row["email"] . ">\">" . $row["email"] ."</a>");
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td colspan=\"4\">&nbsp;</td>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<th class=\"detail\">".$lang['post']."</th>\n");
      print("<th class=\"detail\">".$lang['manager']."</th>\n");
      print("<th class=\"detail\">".$lang['location']."</th>\n");
      print("<th class=\"detail\">".$lang['teams']."</th>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"detail_center\">");
      if(isset($row["post"]))
      {
         print($row["post"]);
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>");
      print("<td class=\"detail_center\">");
      if(isset($row["manager"]))
      {
         $sql = "SELECT * FROM users WHERE userid = " . $row["manager"];
         $sub_result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
         if(@ mysql_num_rows($result) != 0)
         {
            while($sub_row = @ mysql_fetch_array($sub_result))
            print($sub_row["firstname"] . " " . $sub_row["lastname"]);
         }
         else
         {
            print("Non-existent manager");
         }
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>\n");
      print("<td class=\"detail_center\">");
      if(isset($row["location"]))
      {
         $sql = "SELECT * FROM locations WHERE locationid = " . $row["location"];
         $sub_result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
         if(@ mysql_num_rows($result) != 0)
         {
            while($sub_row = @ mysql_fetch_array($sub_result))
            print($sub_row["name"]);
         }
         else
         {
            print($lang['non_location']);
         }
      }
      else
      {
         print("&nbsp;");
      }
      print("</td>");
      print("<td class=\"detail_center\">");
      {
         $sql = "SELECT name FROM teams,userteams WHERE userid = " . safe_escape($showuserid) . " AND teamid=team";
         $sub_result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
         if(@ mysql_num_rows($sub_result) > 0)
         {
            while($sub_row = @ mysql_fetch_array($sub_result))
               print($sub_row["name"]."<br>");
         }
         else
         {
            print($lang['alone']);
         }
      }
      print("</td>");
      print("</tr>\n");
      print("<tr>\n");
      print("<td colspan=\"4\">&nbsp;</td>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<th class=\"detail\" colspan=\"3\">".$lang['info']."</th>\n");
      print("<th class=\"detail\" colspan=\"1\">".$lang['photo']."</th>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"detail\" colspan=\"3\">".nl2br(strip_tags($row["info"],$allowed_tags))."</td>\n");
      if($size = @ getimagesize($file_store."p".$row["userid"]))
      {
         print("<td colspan=\"1\" width=\"".$size[0]."\" class=\"detail_center\">");
         print("<img src=\"photo.php?fileid=".$row["userid"]."\" alt=\"".$row["firstname"]." ".$row["lastname"]."\" ".$size[3].">\n");
      }
      else
      {
         print("<td colspan=\"1\" class=\"detail_center\">");
         print($lang['no_photo']);
      }
      print("</td>\n");
      print("</td>");
      print("</tr>\n");
   }
   print("</table>");
}
else
{
   printf("<span class=\"message\">".$lang['user_not_in_directory']."</span>",$showuserid );
}
$help_keyword="directorydetail";
?>
