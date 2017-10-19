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

// This file performs the actual searching done in helpsearch.inc and
// displays the results.
// Build a hash of team names for the security lists
$sql = "SELECT teamid,name FROM teams ORDER BY name";
$result = @ mysqli_query($intranet_db,$sql);
showerror();

// Get the user's team for security checking
$sql = "SELECT team FROM userteams WHERE userid=$userid";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   $i=0;
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      $userteam[$i]=$row["team"];
      $i++;
   }
}

// Search the database and print the results
print("<h1>".$lang['search_results']."</h1>");
$sql = "SELECT *,helpdesk.callid AS hcallid,description,firstname,lastname,date FROM helpdesk LEFT JOIN history ON helpdesk.callid=history.callid LEFT JOIN users ON helpdesk.ownerid=users.userid WHERE 1";
if(strlen($s_terms)!=0)
{
   $searchterms = explode(' ',$s_terms);
   foreach($searchterms as $searchterm)
   {
      $sql .= " and description LIKE '%".$searchterm."%' ";
   }
}
$sql .= " OR 1";
if(strlen($s_terms)!=0)
{
   $searchterms = explode(' ',$s_terms);
   foreach($searchterms as $searchterm)
   {
      $sql .= " and body LIKE '%".$searchterm."%' ";
   }
}
$sql .= " GROUP BY hcallid ORDER BY date DESC";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
printf("<h2>".$lang['your_query_found_num_calls']."</h2>",mysqli_num_rows($result));
if(@ mysqli_num_rows($result) != 0)
{
   print("<table>\n");
   print("<tr>");
   print("<th class=\"list\">".$lang['call']."</th>\n");
   print("<th class=\"list\">".$lang['description']." (".$lang['italics_indicates_closed_call'].")</th>");
   print("<th class=\"list\">".$lang['owner']."</th>");
   print("<th class=\"list\">".$lang['date']."</th>");
   print("</tr>\n");
   while($row=mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      print("<tr>\n");
      print("<td class=\"list\"><a href=\"$PHP_SELF?callid=".$row["hcallid"]."\">".str_pad($row["hcallid"],4,"0",STR_PAD_LEFT)."</a></td>\n");
      $limit=50;
      if(strlen($row['closedate']>0))
      {
         $row['description'] = stripslashes($row['description']);
         if(strlen($row['description'])<$limit)
            print("<td class=\"list\"><i>".$row["description"]."</i></td>");
         else
            print("<td class=\"list\"><i>".substr($row["description"],0,$limit-3)."...</i></td>");
      }
      else
      {
         if(strlen($row['description'])<$limit)
            print("<td class=\"list\">".$row["description"]."</td>");
         else
            print("<td class=\"list\">".substr($row["description"],0,$limit-3)."...</td>");
      }
      print("<td class=\"list\">".$row["firstname"].' '.$row["lastname"]."</td>");
      print("<td class=\"list\">".date($lang['short_date_format'],$row["date"])."</td>");
      print("</tr>\n");
   }
   print("</table>\n");
}
