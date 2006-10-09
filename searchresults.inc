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

// This file performs the actual searching done in filesearch.inc and
// displays the results.
// Build a hash of team names for the security lists
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

// Get the user's team for security checking
$sql = "SELECT team FROM userteams WHERE userid=$userid";
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

// Get the user's admin status for files first, and set $filesadmin
$sql = "SELECT files FROM userflags WHERE userid = $userid";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
$filesadmin=FALSE;
if(@ mysql_num_rows($result) != 0)
{
   while($row = @ mysql_fetch_array($result))
   {
      if($row["files"] == 'y')
      {
         $filesadmin=TRUE;
      }
   }
}

// Search the database and print the results
print("<h1>".$lang['search_results']."</h1>");
$sql = "SELECT fileid,filename,size,mimetype,datestamp,folder FROM files WHERE 1";
if(strlen($s_filename)!=0)
{
   $searchterms = explode(' ',$s_filename);
   foreach($searchterms as $searchterm)
   {
      $sql .= " and filename LIKE '%".$searchterm."%' ";
   }
}
if(strlen($s_synopsis)!=0)
{
   $searchterms = explode(' ',$s_synopsis);
   foreach($searchterms as $searchterm)
   {
      $sql .= " and synopsis LIKE '%".$searchterm."%' ";
   }
}
$sql .= " ORDER BY filename";
$result = @ mysql_query($sql, $intranet_db);
if(mysql_error())
   showerror();
printf("<h2>".$lang['your_query_found_num_files']."</h2>",mysql_num_rows($result));
if(@ mysql_num_rows($result) != 0)
{
   print("<table>\n");
   print("<tr>");
   print("<th class=\"list\">".$lang['filename']." (".$lang['italics_indicates_restricted_file'].")</th>");
   print("<th class=\"list\">".$lang['date']."</th>");
   print("<th class=\"list\">".$lang['size']."</th>");
   print("<th class=\"list\">".$lang['zoom']."</th>\n");
   print("<th class=\"list\">".$lang['zoom']."</th>\n");
   print("</tr>\n");
   while($row = @ mysql_fetch_array($result))
   {
      $sql = "SELECT COUNT(*) FROM filesecurity WHERE fileid=".$row["fileid"];
      $sub_result = @ mysql_query($sql, $intranet_db);
      $securefile = TRUE; // This must be true
      if(@ mysql_result($sub_result, 0) > 0)
      { // This file has one or more security records
         $sql = "SELECT teamid FROM filesecurity WHERE fileid=".$row["fileid"];
         $sub_result = @ mysql_query($sql, $intranet_db);
         while($srow = @ mysql_fetch_array($sub_result))
         { // Check to see if our team is on the list
            if(isset($userteam))
               foreach($userteam as $teamtest)
                  if($srow["teamid"]==$usertest)
                     $securefile = FALSE;
         }
      }
      else // There is no access list, there is no restriction.
         $securefile = FALSE;
      print("<tr>\n");
      if($securefile)
      {
         print("<td class=\"list\"><i>".$row["filename"]."</i></td>");
      }
      else
      {
         print("<td class=\"list\">".$row["filename"]."</td>");
      }
      print("<td class=\"list\">".date($lang['date_format'],$row["datestamp"])."</td>");
      print("<td class=\"list\">".$row["size"]." ".$lang['bytes']."</td>");
      print("<td class=\"list\"><a title=\"".$row["filename"]."\" href=\"$PHP_SELF?fileid=".$row["fileid"]."\">".$lang['file']." ".$row["fileid"]."</a></td>\n");
      print("<td class=\"list\"><a href=\"$PHP_SELF?folder=".$row["folder"]."\">".$lang['folder']." ".$row["folder"]."</a></td>\n");
      print("</tr>\n");
   }
   print("</table>\n");
}
