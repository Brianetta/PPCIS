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

// This file produces the list of external contacts, with links to individual
// records, such that logged in users can view the contents of a contact's
// directory entry.  It submits data to the file it is included from,
// which uses the variables set here to show the relevant contact or
// the relevant filtered list of contacts.

// Build an array to cache all the contact types
$sql = "SELECT * FROM contacttype ORDER BY description";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      $ctype[$row["contacttype"]]=$row["description"];
   }
}
else
{
   $ctype[1]=$lang['no_contact_type_defined'];
}
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
<td><input size="20" name="first" type="text" value="<?print($first);?>"></td>
<td><?=$lang['lastname']?>:</td>
<td><input size="20" name="last" type="text" value="<?print($last);?>"></td>
<td>&nbsp;</td>
</tr><tr>
<td><?=$lang['company']?>:</td>
<td><input size="20" name="comp" type="text" value="<?print($comp);?>"></td>
<td><?=$lang['type']?>:</td>
<td>
<?
print("<select name=\"conttype\">\n");
print("<option label=\"All types\" value=\"0\">".$lang['all_types']."</option>\n");
foreach($ctype as $contacttype => $description)
{
   print("<option ");
   if($contacttype==$conttype)
      print("selected ");
   print("label=\"$description\" value=\"$contacttype\">$description</option>\n");
}
print("</select>\n");
?>
</td>
<td><input type="hidden" name="callmodule" value="<?print($callmodule);?>"><input class="button" type="submit" value="Search"></td>
</tr>
</form>
</table>
<?
$sql = "SELECT ref,firstname,surname,telephone,company,email FROM externalcontact WHERE ";
if(isset($last))
   if($last=="")
      unset($last);
   else
      $sql = $sql . "surname LIKE '" . safe_escape($last) . "%' AND ";
if(isset($first))
   if($first=="")
      unset($first);
   else
      $sql = $sql . "firstname LIKE '" . safe_escape($first) . "%' AND ";
if(isset($comp))
   if($comp=="")
      unset($comp);
   else
      $sql = $sql . "company LIKE '" . safe_escape($comp) . "%' AND ";
if(isset($conttype))
   if($conttype=="" or $conttype=="0")
      unset($conttype);
   else
      $sql = $sql . "(contacttype = " . safe_escape($conttype) . ") AND ";
if($last<>"")
   $sql = $sql . "1 ORDER BY surname, firstname";
else
   $sql = $sql . "1 ORDER BY company, surname, firstname";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   print("<table>\n");
   print("<tr>\n");
   print("<th class=\"list\">".$lang['name']."</th>\n");
   print("<th class=\"list\">".$lang['telephone_number']."</th>\n");
   print("<th class=\"list\">".$lang['company']."</th>\n");
   print("<th class=\"list\">".$lang['email_address']."</th>\n");
   print("<th class=\"list\">&nbsp;</th>\n");
   print("</tr>\n");
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      if(!(isset($row["surname"]))) $row["surname"] = "&nbsp;";
      if(!(isset($row["telephone"]))) $row["telephone"] = "&nbsp;";
      if(!(isset($row["company"]))) $row["company"] = "&nbsp;";
      if($row["surname"]=="") $row["surname"] = "&nbsp;";
      if($row["telephone"]=="") $row["telephone"] = "&nbsp;";
      if($row["company"]=="") $row["company"] = "&nbsp;";
      print("<tr>\n");
      print("<td class=\"list\">" . " " . $row["firstname"] . " " . $row["surname"] . "</td>\n");
      print("<td class=\"list\">" . $row["telephone"] . "</td>\n");
      print("<td class=\"list\">" . $row["company"] . "</td>\n");
      if(isset($row["email"]))
      {
         print("<td class=\"list_center\"><a href=\"mailto:". $row["firstname"] . " " . $row["surname"] . " <" . $row["email"] . ">\">".$lang['email']."</a></td>\n");
      }
      else
      {
         print("<td class=\"list_center\">".$lang['none']."</td>\n");
      }
      print("<td class=\"list_center\"><a href=\"$PHP_SELF?callmodule=External+directory&showuserid=" . $row["ref"] . "\">".$lang['details']."</a></td>\n");
      print("</tr>\n");
   }
   print("</table>\n");
}
$help_keyword="extdirlist";
?>
