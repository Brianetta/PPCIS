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

// This file produces a sorted, filterable list of all the calls currently assigned to the
// logged in user, unless the $closedcall variable is set, in which case it shows all
// the closed calls (replacing the priority with the date of closure).  It
// has links to the individual calls.

function fmod_x($x,$y)
{
   $i = floor($x/$y);
   return $x - $i*$y;
}

print("<table><tr><td>");
print("<form method=\"get\" id=\"filter_submit\" action=\"$PHP_SELF\">\n");
if($helpdeskadmin)
{
   print("<select name=\"filter_name\">\n");
   print("<option label=\"".$lang['all_users']."\" value=\"0\">".$lang['all_users']."</option>\n");
   foreach($userrevhash as $index => $name)
   {
      if($index==$filter_name)
      {
         print("<option selected label=\"$name\" value=\"$index\">$name</option>\n");
      }
      else
      {
         print("<option label=\"$name\" value=\"$index\">$name</option>\n");
      }
   }
   print("</select><br>\n");
   print("<input type=\"hidden\" name=\"callmodule\" value=\"$callmodule\">");
}
else
{
   print("<input type=\"hidden\" name=\"filter_name\" value=\"$userid\">");
   print("<input type=\"hidden\" name=\"callmodule\" value=\"$callmodule\">");
   $filter_name=$userid;
}

if($helpdeskadmin)
{
   if(!isset($filter_assignee))
   {
      $filter_assignee=$userid;
   }
   $sql="SELECT userflags.userid FROM users";
   $sql.=" LEFT JOIN userflags ON userflags.userid=users.userid";
   $sql.=" WHERE userflags.helpdesk='y'";
   $sql.=" ORDER BY users.lastname,users.firstname";
   print("<select name=\"filter_assignee\">\n");
   print("<option label=\"".$lang['all_calls']."\" value=\"0\">".$lang['all_calls']."</option>\n");
   print("<option");
   if($filter_assignee == -1)
   {
      print(" selected");
   }
   print(" label=\"".$lang['none_assigned']."\" value=\"-1\">".$lang['none_assigned']."</option>\n");
   $result = @ mysqli_query($intranet_db,$sql);
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      if($row["userid"]==(int)$filter_assignee)
      {
         print("<option selected label=\"".$lang['assigned_to'].": ".$userrevhash[$userid]."\" value=\"".$row["userid"]."\">".$lang['assigned_to'].": ".$userrevhash[$row["userid"]]."</option>\n");
      }
      else
      {
         print("<option label=\"".$lang['assigned_to'].": ".$userrevhash[$row["userid"]]."\" value=\"".$row["userid"]."\">".$lang['assigned_to'].": ".$userrevhash[$row["userid"]]."</option>\n");
      }
   }
   print("</select><br>");
}

print("</td><td>");

print("<select name=\"filter_location\">\n");
print("<option selected label=\"".$lang['all_locations']."\" value=\"0\">".$lang['all_locations']."</option>\n");
foreach($locations as $index => $name)
{
   if($index==$filter_location)
   {
      print("<option selected label=\"$name\" value=\"$index\">$name</option>\n");
   }
   else
   {
      print("<option label=\"$name\" value=\"$index\">$name</option>\n");
   }
}
print("</select><br>\n");
print("<select name=\"filter_category\">\n");
print("<option selected label=\"".$lang['all_categories']."\" value=\"0\">".$lang['all_categories']."</option>\n");
foreach($callc as $index => $name)
{
   if($index==$filter_category)
   {
      print("<option selected label=\"$name\" value=\"$index\">$name</option>\n");
   }
   else
   {
      print("<option label=\"$name\" value=\"$index\">$name</option>\n");
   }
}
print("</select>\n");
print("</td><td>");
print("<br>".$lang['check_for_closed_calls'].": <input ");
if(isset($closedcall))
   print("checked ");
print("type=\"checkbox\" name=\"closedcall\"><br>\n");
print("<input class=\"button\" type=\"submit\" name=\"filter\" value=\"".$lang['filter']."\">");
print("</form>\n");
print("</td><td>");
print("<form method=\"get\" id=\"call_submit\" action=\"$PHP_SELF\">\n");
print("<input type=\"hidden\" name=\"callmodule\" value=\"$callmodule\">");
print($lang['call_number'].": <input type=\"text\" name=\"callid\" size=\"5\">");
print("<input class=\"button\" type=\"submit\" name=\"Call_go\" value=\"".$lang['get_call_num']."\">");
print("</form>");

if($filter_assignee>0)
{
   if(isset($closedcall))
   {
      $sql = "SELECT * FROM helpdesk LEFT JOIN assignees ON helpdesk.callid=assignees.callid WHERE helpdesk.closedate IS NOT NULL AND assignees.userid=$filter_assignee";
   }
   else
   {
      $sql = "SELECT * FROM helpdesk LEFT JOIN assignees ON helpdesk.callid=assignees.callid WHERE helpdesk.closedate IS NULL AND assignees.userid=$filter_assignee";
   }
}
elseif($filter_assignee==0)
{
   if(isset($closedcall))
   {
      $sql = "SELECT *,helpdesk.callid as callid FROM helpdesk LEFT JOIN assignees ON helpdesk.callid=assignees.callid WHERE helpdesk.closedate IS NOT NULL";
   }
   else
   {
      $sql = "SELECT *,helpdesk.callid as callid FROM helpdesk LEFT JOIN assignees ON helpdesk.callid=assignees.callid WHERE helpdesk.closedate IS NULL";
   }
}
else
{
   if(isset($closedcall))
   {
      $sql = "SELECT *,helpdesk.callid as callid FROM helpdesk LEFT JOIN assignees ON helpdesk.callid=assignees.callid WHERE helpdesk.closedate IS NOT NULL AND assignees.userid IS NULL";
   }
   else
   {
      $sql = "SELECT *,helpdesk.callid as callid FROM helpdesk LEFT JOIN assignees ON helpdesk.callid=assignees.callid WHERE helpdesk.closedate IS NULL AND assignees.userid IS NULL";
   }
}

if($filter_name>0)
{
   $sql .= " AND helpdesk.ownerid=$filter_name";
}
if($filter_location>0)
{
   $sql .= " AND helpdesk.locationid=$filter_location";
}
if($filter_category>0)
{
   $sql .= " AND helpdesk.category=$filter_category";
}
$sql.=" GROUP BY helpdesk.callid";
if(isset($closedcall))
   $sql .= " ORDER BY helpdesk.closedate DESC";
else
   $sql .= " ORDER BY helpdesk.priority, helpdesk.date";
if(!isset($startcallnum))
   $startcallnum=0;
$result = @ mysqli_query($intranet_db,$sql);
showerror();
$num_calls = mysqli_num_rows($result);
$sql .= " LIMIT $startcallnum,60";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
print("</td><td>");
printf("<b>".$lang['num_calls_listed']."</b>",$num_calls );
print("</td></tr>");
print("</table>");

if($num_calls>60)
{
   print("<table><tr>\n");
   print("<td class=\"pager\" width=\"". (int)(100/(max(30,fmod_x(30,($num_calls/60)))+2)) ."%\">");
   if($startcallnum>59)
      print("<a href=\"$PHP_SELF?callmodule=Manage+calls&startcallnum=".($startcallnum-60)."&filter_name=$filter_name&filter_assignee=$filter_assignee&filter_location=$filter_location&filter_category=$filter_category&closedcall=$closedcall\">&lt;-".$lang['NEWER']."</a> ");
   else
      print("&lt;-".$lang['NEWER']);
   print("</td>\n");
   for($page=1; $page <= (1 + ($num_calls - 1) / 60); $page++)
   {
      print("<b>");
      if(($page*60-$startcallnum)==60)
      {
         print("<td class=\"pager\" width=\"" . (int)(100/(max(30,fmod_x(30,($num_calls/60)))+2)) . "%\">");
         print("$page");
         print("</td>\n");
      }
      else
      {
         print("<td class=\"pager\" width=\"" . (int)(100/(max(30,fmod_x(30,($num_calls/60)))+2)) . "%\">");
         print("<a href=\"$PHP_SELF?callmodule=".$lang['manage_calls']."&startcallnum=".(($page-1)*60)."&filter_name=$filter_name&filter_assignee=$filter_assignee&filter_location=$filter_location&filter_category=$filter_category&closedcall=$closedcall\">$page</a>");
         print("</td>\n");
      }
      print("</b>");
      if(($page-(floor($page/30)*30)) == 0)
         print("<td class=\"pager\" width=\"" . (int)(100/32) . "%\">&nbsp;</td></tr><tr><td class=\"pager\" width=\"" . (int)((100/max(30,fmod_x(30,($num_calls/60)))+2)) . "%\">&nbsp;</td>");
   }
   print("<td class=\"pager_right\" width=\"" . (int)((30-$page)*((100/fmod_x(30,($num_calls/60)))-2)) . "%\"");
   if($page>30)
   print(" colspan=\"". ($page-(floor($page/30)*30)) ."\"");
   print(">");
   if($startcallnum<($num_calls-59))
      print("<a href=\"$PHP_SELF?callmodule=Manage+calls&startcallnum=".($startcallnum+60)."&filter_name=$filter_name&filter_assignee=$filter_assignee&filter_location=$filter_location&filter_category=$filter_category&closedcall=$closedcall\">".$lang['OLDER']."-&gt;</a> ");
   else
      print($lang['OLDER']."-&gt;");
   print("</td>\n");
   print("</tr></table>\n");
}

if(@ mysqli_num_rows($result) != 0)
{
   print("<table>\n");
   print("<tr><th class=\"list\">".$lang['call']."</th><th class=\"list\">".$lang['owner']."</th><th class=\"list\">".$lang['date']."</th><th class=\"list\">");
   if(isset($closedcall))
      print($lang['closed']);
   else
      print($lang['priority']);
   print("</th><th class=\"list\">".$lang['category']."</th><th class=\"list\">".$lang['location']."</th><th class=\"list\">".$lang['summary']."</th></tr>\n");
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
		$highlight="";
      if($row["priority"]==9)
         $highlight="_highlight";
      $callbody=strip_tags($row["description"]);
      $limit=50;
      print("<tr>");
      print("<td class=\"list$highlight\"><a href=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."&callid=".$row["callid"]."\">".str_pad($row["callid"],4,"0",STR_PAD_LEFT)."</a></td>\n");
      print("<td class=\"list$highlight\">");
      $sql = "SELECT callid FROM assignees WHERE callid=".$row["callid"];
      $nresult = @ mysqli_query($intranet_db,$sql);
      showerror();
      if(@ mysqli_num_rows($nresult) == 0)
         print("<b>".$userhash[$row["ownerid"]]."</b>");
      else
         print($userhash[$row["ownerid"]]);
      print("</td>\n");
      print("<td class=\"list$highlight\">".date($lang['short_date_format'], $row["date"])."</td>\n");
      if(isset($closedcall))
         print("<td class=\"list$highlight\">".date($lang['short_date_format'], $row["closedate"])."</td>\n");
      else
         print("<td class=\"list_p".$row["priority"]."\">".$priority[$row["priority"]]."</td>\n");
      print("<td class=\"list$highlight\">".$callc[$row["category"]]."</td>\n");
      print("<td class=\"list$highlight\">".$locations[$row["locationid"]]."</td>\n");
      if(strlen($callbody)<$limit)
         print("<td class=\"list$highlight\">$callbody</td>\n");
      else
         print("<td class=\"list$highlight\">".substr($callbody,0,$limit-3)."...</td>\n");
      print("</tr>");
   }
   print("</table>\n");
}
else
{
   print("<span class=\"message\">".$lang['there_are_no_calls']."</span>");
}

$help_keyword="viewcalllist";
?>
