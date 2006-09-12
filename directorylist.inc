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

// This file produces the list of users, with links to individual records,
// such that logged in users can view the contents of a user's
// directory entry.  It submits data to the file it is included from,
// which uses the variables set here to show the relevant user or
// the relevant filtered list of users.

?>
<table>
<tr>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=A">A</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=B">B</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=C">C</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=D">D</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=E">E</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=F">F</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=G">G</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=H">H</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=I">I</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=J">J</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=K">K</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=L">L</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=M">M</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=N">N</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=O">O</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=P">P</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=Q">Q</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=R">R</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=S">S</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=T">T</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=U">U</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=V">V</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=W">W</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=X">X</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=Y">Y</a></th>
<th class=alphabet width="3.84615%"><a href="<?print($PHP_SELF)?>?callmodule=<?print(rawurlencode($callmodule));?>&last=Z">Z</a></th>
</tr>
</table>
<table>
<form method="get" id="search" action="<?print($PHP_SELF)?>">
<tr>
<td><?=$lang['firstname']?>:</td>
<td><input size="10" name="first" type="text" value="<?print($first);?>"></td>
<td><?=$lang['lastname']?>:</td>
<td><input size="10" name="last" type="text" value="<?print($last);?>"></td>
<td><?=$lang['team']?>:</td>
<td>
<?
   $sql = "SELECT * FROM teams ORDER BY name";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   print("<select name=\"team\">\n");
   print("<option label=\"".$lang['any_team']."\" value=\"0\">".$lang['any_team']."</option>");
   print("<option");
   if ($team == "NULL")
      print(" selected");
   print(" label=\"".$lang['alone']."\" value=\"NULL\">".$lang['alone']."</option>");
   if(@ mysql_num_rows($result) != 0)
   {
      while($row = @ mysql_fetch_array($result))
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
<td><?=$lang['info']?>:</td>
<td><input size="10" name="info" type="text" value="<?print($info);?>"></td>
<td><input type="hidden" name="callmodule" value="<?=$callmodule?>"><input class="button" type="submit" value="<?=$lang['search']?>"></td>
</tr>
</form>
</table>
<?
$sql = "SELECT *,users.userid as userid FROM users, userdirectory LEFT JOIN userteams ON users.userid=userteams.userid WHERE ";
if(isset($last))
   $sql .= "lastname LIKE '" . safe_escape($last) . "%' AND ";
if(isset($first))
   $sql .= "firstname LIKE '" . safe_escape($first) . "%' AND ";
if($team == "NULL")
   $sql .= "team IS NULL AND ";
elseif ($team > 0)
   $sql .= "team = " . safe_escape($team) . " AND ";
$sql .= "users.userid = userdirectory.userid";
if(strlen($info)!=0)
{
   $searchterms = explode(' ',$info);
   foreach($searchterms as $searchterm)
   {
      $sql .= " and info LIKE '%".$searchterm."%' ";
   }
}
$sql .= " GROUP BY users.userid ORDER BY lastname, firstname";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   print("<table>\n");
   print("<tr>\n");
   print("<th class=\"list\">".$lang['name']."</th>\n");
   print("<th class=\"list\">".$lang['telephone_number']."</th>\n");
   print("<th class=\"list\">".$lang['mobile_number']."</th>\n");
   print("<th class=\"list\">".$lang['email_address']."</th>\n");
   print("<th class=\"list\">&nbsp;</th>\n");
   print("</tr>\n");
   while($row = @ mysql_fetch_array($result))
   {
      if(!(isset($row["lastname"]))) $row["lastname"] = "&nbsp;";
      if(!(isset($row["telephone"]))) $row["telephone"] = "&nbsp;";
      if(!(isset($row["mobile"]))) $row["mobile"] = "&nbsp;";
      if($row["lastname"]=="") $row["lastname"] = "&nbsp;";
      if($row["telephone"]=="") $row["telephone"] = "&nbsp;";
      if($row["mobile"]=="") $row["mobile"] = "&nbsp;";
      print("<tr>\n");
      print("<td class=\"list\">" . $row["firstname"] . " " . $row["lastname"] . "</td>\n");
      print("<td class=\"list\">" . $row["telephone"] . "</td>\n");
      print("<td class=\"list\">" . $row["mobile"] . "</td>\n");
      if(isset($row["email"]))
      {
         print("<td class=\"list_center\"><a href=\"mailto:". $row["firstname"] . " " . $row["lastname"] . " <" . $row["email"] . ">\">".$lang['email']."</a></td>\n");
      }
      else
      {
         print("<td class=\"list_center\">".$lang['none']."</td>\n");
      }
      print("<td class=\"list_center\"><a href=\"$siteprefix" . "directory.php?showuserid=" . $row["userid"] . "\">".$lang['details']."</a></td>\n");
      print("</tr>\n");
   }
   print("</table>\n");
   print("</td>\n</tr>\n</table>\n");
}
$help_keyword="directorylist";
?>
