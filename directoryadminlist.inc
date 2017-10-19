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

// This file produces the list of users, with links to individual records,
// such that directoryadmin users can alter the contents of a user's
// directory entry.  It submits data to the file it is included from,
// which uses the variables set here to show the relevant user or
// the relevant filtered list of users.

?>
<table border="0" cellpadding="0" cellspacing="1" width="100%">
<tr>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=A">A</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=B">B</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=C">C</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=D">D</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=E">E</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=F">F</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=G">G</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=H">H</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=I">I</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=J">J</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=K">K</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=L">L</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=M">M</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=N">N</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=O">O</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=P">P</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=Q">Q</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=R">R</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=S">S</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=T">T</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=U">U</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=V">V</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=W">W</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=X">X</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=Y">Y</a></th>
<th class=alphabet width="3.84615%"><a href="<?php print($PHP_SELF)?>?callmodule=<?php print(rawurlencode($callmodule));?>&last=Z">Z</a></th>
</tr>
</table>
<table>
<form method="get" id="search" action="<?php print($PHP_SELF)?>">
<tr>
<td><?=$lang['firstname']?>:</td>
<td><input size="20" name="first" type="text" value="<?php print($first);?>"></td>
<td><?=$lang['lastname']?>:</td>
<td><input size="20" name="last" type="text" value="<?php print($last);?>"></td>
<td><?=$lang['team']?>:</td>
<td>
<?php
   $sql = "SELECT * FROM teams ORDER BY name";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
   print("<select name=\"team\">\n");
   print("<option label=\"".$lang['any_team']."\" value=\"0\">".$lang['any_team']."</option>");
   print("<option");
   if ($team == "NULL")
      print(" selected");
   print(" label=\"".$lang['alone']."\" value=\"NULL\">".$lang['alone']."</option>");
   if(@ mysqli_num_rows($result) != 0)
   {
      while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
      {
         if($team==$row["teamid"])
         {
            print("<option selected label=\"".$row["name"]."\" value=\"".$row["teamid"]."\">");
            print($row["name"]."</option>");
         }
         else
         {
            print("<option label=\"".$row["name"]."\" value=\"".$row["teamid"]."\">");
            print($row["name"]."</option>");
         }
         print($row["name"]);
      }
   }
   print("</select>");
?>
</td>
<td><input type="hidden" name="callmodule" value="<?php print($callmodule);?>"><input class="button" type="submit" value="<?=$lang['search']?>"></td>
</tr>
</form>
</table>
<?php
if(isset($first)) // Get rid of empty search strings, as they mess stuff up.
{
   if($first=="")
      unset($first);
}
if(isset($last))
{
   if($last=="")
      unset($last);
}

// Build select statement, incorporating search variables.
$sql = "SELECT *,users.userid AS userid FROM users ";
$sql .="LEFT JOIN userdirectory ON users.userid = userdirectory.userid ";
$sql .="LEFT JOIN userteams ON users.userid = userteams.userid ";
$where = "WHERE 1 ";
if(isset($last))
   $where = $where . "AND lastname LIKE '" . safe_escape($last) . "%' ";
if(isset($first))
   $where = $where . "AND firstname LIKE '" . safe_escape($first) . "%' ";
if(isset($team))
{
   if($team == "NULL")
      $where = $where . "AND team IS NULL ";
   if ($team > 0)
      $where = $where . "AND team = " . safe_escape($team) . " ";
}
$sql = $sql . $where . "GROUP BY users.userid ORDER BY lastname, firstname";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0) // Render a nice table of users.
{
   print("<table>\n");
   print("<tr>\n");
   print("<th class=\"list\">".$lang['userid']."</th>\n");
   print("<th class=\"list\">".$lang['username']."</th>\n");
   print("<th class=\"list\">".$lang['name']."</th>\n");
   print("<th class=\"list\">".$lang['directory']."</th>\n");
   print("</tr>\n");
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      print("<tr>\n");
      print("<td class=\"list\">" . $row["userid"] . "</td>\n");
      print("<td class=\"list\">" . $row["username"] . "</td>\n");
      print("<td class=\"list\">" . $row["lastname"] . ", " . $row["firstname"] . "</td>\n");
      print("<td class=\"list_center\"><a href=\"$siteprefix" . "admin.php?callmodule=".rawurlencode($callmodule)."&showuserid=" . $row["userid"] . "\">".$lang['modify']."</a></td>\n");
      print("</tr>\n");
   }
   print("</table>\n");
}
$help_keyword="directoryadminlist";
?>
