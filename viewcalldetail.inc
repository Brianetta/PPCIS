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

// This file displays the details of a helpdesk call.  If the logged in user
// is the owner of the call or is a helpdeskadmin user, then it is also a form.
// The owner of the call is able to add history, change location and close the
// call, whilst the helpdeskadmin can also change the owner, priorit and category,
// and can assign/unassign helpdeskadmin staff to the call, and mark themselves
// as active or inactive if they are assigned to the call.
//
// This file is included from both the "manage calls" and the "assigned calls" pages.

$sql = "SELECT * FROM helpdesk WHERE callid=$callid";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   $call = @ mysql_fetch_array($result);
   print("<form method=\"post\" id=\"edit_call\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."&callid=$callid\">");
   print("<table>");
   print("<tr>\n");
   print("<th colspan=\"2\">".$lang['call_number']." ".str_pad($callid,4,"0",STR_PAD_LEFT));
   if(($helpdeskadmin) OR ($call["ownerid"]==$userid))
      print("<br><input class=\"button\" type=\"submit\" name=\"modify_call_b\" value=\"".$lang['apply_changes']."\">\n");
   print("</th>\n");
   print("</tr>\n<tr>\n");
   print("<td><b>".$lang['owner'].":</b></td>\n");
   print("<td>");
   if($helpdeskadmin)
   {
      print("<select name=\"mod_name\">\n");
      foreach($userrevhash as $index => $name)
      {
         if($index==$call["ownerid"])
         {
            print("<option selected label=\"$name\" value=\"$index\">$name</option>\n");
         }
         else
         {
            print("<option label=\"$name\" value=\"$index\">$name</option>\n");
         }
      }
      print("</select>\n");
   }
   else
   {
      print($userhash[$call["ownerid"]]);
   }
   print(" <a href=\"directory.php?showuserid=".$call["ownerid"]."\">[".$userhash[$call["ownerid"]]."]</a>");
   print("</td>\n");
   print("</tr>\n<tr>\n");
   print("<td><b>".$lang['priority'].":</b></td>\n");
   print("<td>");
   if($helpdeskadmin)
   {
      print("<select name=\"mod_priority\">\n");
      foreach($priority as $index => $name)
      {
         print("<option ");
			if($call["priority"]>0)
			{
         	if($index==$call["priority"])
            	print("selected ");
			}
			else
			{
         	if($index==4)
            	print("selected ");
			}
         print("label=\"$name\" value=\"$index\">$name</option>\n");
      }
      print("</select>\n");
   }
   else
   {
      print($priority[$call["priority"]]);
   }
   print("</td>\n");
   print("</tr>\n<tr>\n");
   print("<td><b>".$lang['date'].":</b></td>\n");
   print("<td>".date($lang['long_date_format'],$call["date"])."</td>\n");
   print("</tr>\n<tr>\n");
   print("<td><b>".$lang['category'].":</b></td>\n");
   print("<td>");
   if($helpdeskadmin)
   {
      print("<select name=\"mod_category\">\n");
      foreach($callc as $index => $name)
      {
         print("<option ");
         if($index==$call["category"])
            print("selected ");
         print("label=\"$name\" value=\"$index\">$name</option>\n");
      }
      print("</select>\n");
   }
   else
   {
      print($callc[$call["category"]]);
   }
   print("</td>\n");
   print("</tr>\n<tr>\n");
   print("<td><b>".$lang['location'].":</b></td>\n");
   print("<td>");
   if(($helpdeskadmin) OR ($call["ownerid"]==$userid))
   {
      print("<select name=\"mod_location\">\n");
      foreach($locations as $index => $name)
      {
         print("<option ");
         if($index==$call["locationid"])
            print("selected ");
         print("label=\"$name\" value=\"$index\">$name</option>\n");
      }
      print("</select>\n");
   }
   else
   {
      print($locations[$call["locationid"]]);
   }
   print("</td>\n");
   print("</tr>\n<tr>\n");
   print("<th class=\"detail\" colspan=\"2\">".$lang['call_content'].":</th>");
   print("</tr>\n<tr>\n");
   print("<td class=\"detail\" colspan=\"2\">");
   $call["description"] = strip_tags($call["description"],$allowed_tags);
   preg_match_all('/IMAGE[0-9]*HERE/',$call["description"],$call_images);
   foreach($call_images[0] as $key => $value)
   {
      $fileid = str_replace('HERE','',str_replace('IMAGE','',$value));
      if($call_image_info = getimagesize($file_store . $fileid))
      {
         $call_images[0][$key] = str_replace('IMAGE',"<img ${call_image_info[3]} src=\"fetchfile.php?fileid=",$call_images[0][$key]);
         $call_images[0][$key] = str_replace('HERE','">',$call_images[0][$key]);
         $call["description"] = preg_replace('/IMAGE[0-9]*HERE/',$call_images[0][$key],$call["description"],1);
      }
      else
      {
         $call["description"] = preg_replace('/IMAGE[0-9]*HERE/',$lang['image_broken'],$call["description"],1);
      }
   }
   print(nl2br(strip_tags($call["description"],"$allowed_tags<img>")));
   print("</td>\n");
   print("</tr>\n");
   print("</table>\n");
	print("<p>\n");
   print("<table>");
   print("<tr><th class=\"detail\">".$lang['assigned_to'].":</th></tr>");
   $sql = "SELECT * FROM assignees LEFT JOIN users ON assignees.userid=users.userid WHERE assignees.callid=$callid ORDER BY assignees.active DESC, users.lastname, users.firstname";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   if(@ mysql_num_rows($result) != 0)
   {
      $i=1;
      while($row = @ mysql_fetch_array($result))
      {
         print("<tr>");
         print("<td class=\"detail_mid\">".$userhash[$row["userid"]]);
         if($row["active"]=='Y')
            print(" (".$lang['currently_active'].")");
         if($row["userid"]==$userid)
         {
            print("<br><input type=\"radio\"");
            if($row["active"]=='Y')
               print(" checked");
            print(" name=\"assignee_active\" value=\"Y\">".$lang['active']);
            print("<br><input type=\"radio\"");
            if($row["active"]=='N')
               print(" checked");
            print(" name=\"assignee_active\" value=\"N\">".$lang['inactive']);
         }
         if($helpdeskadmin)
            print("<br><input type=\"checkbox\" name=\"del_assignee\" value=\"".$row["userid"]."\"> <i>".$lang['tick_to_remove_support_staff']."</i>");
         print("</td>\n");
         print("</tr>");
         $assigned[$i]=$row["userid"]; $i++;
      }
   }
   else
   {
      print("<tr>");
      print("<td class=\"detail_mid\">".$lang['no_support_staff_assigned']."</td>\n");
      print("</tr>");
   }
   if($helpdeskadmin)
   {
      print("<tr>");
      print("<td class=\"detail\">");
      print("<select name=\"add_assignee_name\">\n");
      $sql = "SELECT userflags.userid FROM users LEFT JOIN userflags ON userflags.userid=users.userid WHERE userflags.helpdesk='y' ORDER BY users.lastname,users.firstname";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
      if(@ mysql_num_rows($result) != 0)
      {
         print("<option label=\"".$lang['select_to_assign_support_staff']."\" value=\"0\">".$lang['select_to_assign_support_staff']."</option>\n");
         while($row = @ mysql_fetch_array($result))
         {
            $not_already_assigned=true;
            $j=count($assigned);
            for($i=1;$i<=$j;$i++)
            {
               if($assigned[$i]==$row["userid"])
                  $not_already_assigned=false;
            }
            if($not_already_assigned)
            {
               {
                  print("<option label=\"".$userrevhash[$row["userid"]]."\" value=\"".$row["userid"]."\">".$userrevhash[$row["userid"]]."</option>\n");
               }
            }
         }
      }
      print("</select>\n");
      print("</td>\n");
      print("</tr>");
   }
   print("</table>\n");
	print("<p>\n");
   print("<table>");
   print("<tr>\n");
   print("<th class=\"list\">".$lang['history']."</th><th class=\"list\">".$lang['author']."</th><th class=\"list\">".$lang['date']."</th>\n");
   print("</tr>\n");
   $sql = "SELECT * FROM history WHERE callid=$callid ORDER BY histdate";
   if($backwards_history)
      $sql .= " DESC";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   if(@ mysql_num_rows($result) != 0)
   {
      while($row = @ mysql_fetch_array($result))
      {
         print("<tr>");
         $highlight="";
         if($row["system"]=='y')
            $highlight="_highlight";
         preg_match_all('/IMAGE[0-9]*HERE/',$row["body"],$call_images);
         foreach($call_images[0] as $key => $value)
         {
            $fileid = str_replace('HERE','',str_replace('IMAGE','',$value));
            if($call_image_info = getimagesize($file_store . $fileid))
            {
                  $call_images[0][$key] = str_replace('IMAGE','<img src="fetchfile.php?fileid=',$call_images[0][$key]);
                  $call_images[0][$key] = str_replace('HERE','">',$call_images[0][$key]);
                  $row["body"] = preg_replace('/IMAGE[0-9]*HERE/',$call_images[0][$key],$row["body"],1);
            }
            else
            {
               $row["body"] = preg_replace('/IMAGE[0-9]*HERE/',$lang['image_broken'],$$row["body"],1);
            }
         }
         print("<td class=\"list$highlight\">".nl2br($row["body"])."</td>\n");
         print("<td class=\"list$highlight\">".$userhash[$row["userid"]]."</td>\n");
         print("<td class=\"list$highlight\">".date($lang['long_date_format'],$row["histdate"])."</td>\n");
         print("</tr>");
      }
   }
   if(($helpdeskadmin) OR ($call["ownerid"]==$userid))
   {
      print("<tr>\n");
      print("<td class=\"list\">");
      print("<textarea rows=\"3\" cols=\"40\" name=\"mod_history\"></textarea>");
      print("</td>");
      print("<td class=\"list\">");
      print($userhash[$userid]);
      print("</td>");
      print("<td class=\"list\">");
      print(date($lang['date_format'],time()));
      print("</td>");
      print("</tr>\n");
   }
   print("</table>\n");

   if(($helpdeskadmin) OR ($call["ownerid"]==$userid))
   {
      if($call["closedate"]=="")
      {
         print("<i>".$lang['tick_box_to_close_call'].":</i> <input type=\"checkbox\" name=\"mod_closed\">\n");
      }
      else
      {
         printf($lang['this_call_was_closed_on'],date($lang['date_format'],$call["closedate"]));
      }
   }
   else
   {
      if($call["closedate"]!="")
      {
         printf($lang['this_call_was_closed_on'],date($lang['date_format'],$call["closedate"]));
      }
   }
   if(($helpdeskadmin) OR ($call["ownerid"]==$userid))
   {
      print(" <input class=\"button\" type=\"submit\" name=\"modify_call_a\" value=\"".$lang['apply_changes']."\">\n");
      print("<a href=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."&callid=$callid\">".$lang['discard_changes']."</a>");
   }
   print("</form>\n");
}
else
{
   print("<span class=\"message\">".$lang['no_such_call']."</span>\n");
}

$help_keyword="viewcalldetail";
if($helpdeskadmin)
   $help_keyword.="a";
elseif($call["ownerid"]==$userid)
   $help_keyword.="u";
?>
