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

// This file allowsusers with the useradmin right to change the teams that
// any user on the system belongs to.

// Build a hash of team names

if(isset($delteam))
{
   $sql = "DELETE FROM userteams WHERE userid=$showteams AND team=$team";
   $result = @ mysql_query($sql, $intranet_db);
}
if(isset($addteam))
{
   $sql = "INSERT INTO userteams (userid,team) VALUES ($showteams,$team)";
   $result = @ mysql_query($sql, $intranet_db);
}

$sql = "SELECT teamid,name FROM teams ORDER BY name";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   while($row = @ mysql_fetch_array($result))
   {
      $teamhash[$row["teamid"]]=$row["name"];
   }
}
else
{
   $teamhash[1]=$lang['no_teams_available'];
}

$sql = "SELECT firstname,lastname FROM users WHERE userid=$showteams";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) == 1)
{
   $row = @ mysql_fetch_array($result);
   $uname = $row['firstname'].' '.$row['lastname'];
}

// Build a hash of the teams to which the user belongs
$sql = "SELECT team FROM userteams where userid=$showteams";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   $i=0;
   while($row = @ mysql_fetch_array($result))
   {
      $userteam[$i]=$row["team"];
      $i++;
   }
}
else
{
   $userteam[1]="-1";
}

print("<table>");
print("<tr>\n");
printf("<th colspan=\"2\"><h2>".$lang['adjusting_team_membership_for']."</h2></th>",$uname);
print("</tr>\n");
foreach($teamhash as $tteam => $tname)
{
   print("<tr>\n");
   print("<form method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\" id=\"modteam$tteam\">");
   print("<td class=\"right\" width=\"50%\">");
   $in_team=FALSE;
   foreach($userteam as $teamtest)
   {
      if($teamtest==$tteam)
         $in_team=TRUE;
   }
   if($in_team)
   {
      print("<b>$tname</b></td><td><input disabled class=\"button\" type=\"submit\" name=\"addteam\" value=\"".$lang['join']."\"><input class=\"button\" type=\"submit\" name=\"delteam\" value=\"".$lang['part']."\">");
      print("<input type=\"hidden\" name=\"team\" value=\"$tteam\">");
   }
   else
   {
      print("$tname</td><td><input class=\"button\" type=\"submit\" name=\"addteam\" value=\"".$lang['join']."\"><input disabled class=\"button\" type=\"submit\" name=\"delteam\" value=\"".$lang['part']."\">");
      print("<input type=\"hidden\" name=\"team\" value=\"$tteam\">");
   }
   print("<input type=\"hidden\" name=\"showteams\" value=\"$showteams\">");
   print("</td>\n");
   print("</form>");
   print("</tr>\n");
}
print("</table>");

?>
