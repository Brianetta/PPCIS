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

// This file lets the admin user to alter the details of an external
// contact, referenced by the badly named "showuserid" variable.  Many
// variables are set by the file that includes this one.

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

// If a form has been submitted, update the database
if(isset($mod_delete))
{
   $sql="DELETE FROM externalcontact WHERE ref='$showuserid' LIMIT 1";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   else
      print("<span class=\"message\">".$lang['ext_dir_success_remove']."</span>\n");
}

if(!(isset($showuserid)))
   $showuserid=0;

if(isset($mod_submit))
{
   if($showuserid==0)
   {
      $sql="INSERT INTO externalcontact (firstname, surname, title, telephone, company, email,";
      $sql.="website, fax, address1, address2, address3, town, county, postcode, contacttype) VALUES (";
      if($mod_firstname=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_firstname',";
      if($mod_lastname=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_lastname',";
      if($mod_position=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_position',";
      if($mod_telephone=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_telephone',";
      if($mod_company=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_company',";
      if($mod_email=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_email',";
      if(($mod_website=="") OR ($mod_website=="http://"))
         $sql.=" NULL,";
      else
         $sql.=" '$mod_website',";
      if($mod_fax=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_fax',";
      if($mod_address1=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_address1',";
      if($mod_address2=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_address2',";
      if($mod_address3=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_address3',";
      if($mod_town=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_town',";
      if($mod_county=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_county',";
      if($mod_postcode=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_postcode',";
      if($mod_contacttype=="")
         $sql.=" NULL,";
      else
         $sql.=" '$mod_contacttype'";
      $sql.=" )";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
      else
      {
         print("<span class=\"message\">".$lang['ext_dir_success_add']."</span>\n");
         $showuserid=mysql_insert_id();
      }
   }
   else
   {
      $sql="UPDATE externalcontact SET";
      if($mod_firstname=="")
         $sql.=" firstname=NULL,";
      else
         $sql.=" firstname='$mod_firstname',";
      if($mod_lastname=="")
         $sql.=" surname=NULL,";
      else
         $sql.=" surname='$mod_lastname',";
      if($mod_position=="")
         $sql.=" title=NULL,";
      else
         $sql.=" title='$mod_position',";
      if($mod_telephone=="")
         $sql.=" telephone=NULL,";
      else
         $sql.=" telephone='$mod_telephone',";
      if($mod_company=="")
         $sql.=" company=NULL,";
      else
         $sql.=" company='$mod_company',";
      if($mod_email=="")
         $sql.=" email=NULL,";
      else
         $sql.=" email='$mod_email',";
      if(($mod_website=="") OR ($mod_website=="http://"))
         $sql.=" website=NULL,";
      else
         $sql.=" website='$mod_website',";
      if($mod_fax=="")
         $sql.=" fax=NULL,";
      else
         $sql.=" fax='$mod_fax',";
      if($mod_address1=="")
         $sql.=" address1=NULL,";
      else
         $sql.=" address1='$mod_address1',";
      if($mod_address2=="")
         $sql.=" address2=NULL,";
      else
         $sql.=" address2='$mod_address2',";
      if($mod_address3=="")
         $sql.=" address3=NULL,";
      else
         $sql.=" address3='$mod_address3',";
      if($mod_town=="")
         $sql.=" town=NULL,";
      else
         $sql.=" town='$mod_town',";
      if($mod_county=="")
         $sql.=" county=NULL,";
      else
         $sql.=" county='$mod_county',";
      if($mod_postcode=="")
         $sql.=" postcode=NULL,";
      else
         $sql.=" postcode='$mod_postcode',";
      if($mod_contacttype=="")
         $sql.=" contacttype=NULL";
      else
         $sql.=" contacttype='$mod_contacttype'";
      $sql.=" WHERE ref=$showuserid";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
      else
         print("<span class=\"message\">".$lang['ext_dir_success_modify']."</span><br>\n");
   }
}

// Get current values for the form and build it
$sql = "SELECT * FROM externalcontact WHERE ref = ".safe_escape($showuserid);
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if((@ mysql_num_rows($result) != 0) OR ($showuserid==0))
{
   print("<form method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."&showuserid=".$showuserid."\">\n");
   print("<table>");
   $row = @ mysql_fetch_array($result);
   print("<tr>");
   print("<td class=\"right\">");
   print($lang['firstname'].":</td><td><input type=\"text\" name=\"mod_firstname\" value=\"".$row["firstname"] . "\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">");
   print($lang['lastname']."Last name:</td><td><input type=\"text\" name=\"mod_lastname\" value=\"" . $row["surname"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">");
   print($lang['position'].":</td><td><input type=\"text\" name=\"mod_position\" value=\"".$row["title"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">");
   print($lang['telephone_number'].":</td><td><input type=\"text\" name=\"mod_telephone\" value=\"".$row["telephone"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">");
   print($lang['company'].":</td><td><input type=\"text\" name=\"mod_company\" value=\"".$row["company"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">");
   print($lang['email_address'].":</td><td><input type=\"text\" name=\"mod_email\" value=\"". $row["email"] . "\"><br>\n  ");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">");
   if(isset($row["website"]))
   {
      print($lang['website'].":</td><td><input type=\"text\" name=\"mod_website\" value=\"".$row["website"]."\"><br>\n");
   }
   else
   {
      print($lang['website'].":</td><td><input type=\"text\" name=\"mod_website\" value=\"http://\"><br>\n");
   }
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">");
   print($lang['fax'].":</td><td><input type=\"text\" name=\"mod_fax\" value=\"".$row["fax"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">".$lang['address']." 1:</td>");
   print("<td>");
   print("<input type=\"text\" name=\"mod_address1\" value=\"".$row["address1"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">".$lang['address']." 2:</td>");
   print("<td>");
   print("<input type=\"text\" name=\"mod_address2\" value=\"".$row["address2"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">".$lang['address']." 3:</td>");
   print("<td>");
   print("<input type=\"text\" name=\"mod_address3\" value=\"".$row["address3"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">".$lang['town'].":</td>");
   print("<td>");
   print("<input type=\"text\" name=\"mod_town\" value=\"".$row["town"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">".$lang['county'].":</td>");
   print("<td>");
   print("<input type=\"text\" name=\"mod_county\" value=\"".$row["county"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">".$lang['postcode'].":</td>");
   print("<td>");
   print("<input type=\"text\" name=\"mod_postcode\" value=\"".$row["postcode"]."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"right\">".$lang['type'].":</td>");
   print("<td>");
   print("<select name=\"mod_contacttype\">\n");
   foreach($ctype as $contacttype => $description)
   {
      print("<option ");
      if($contacttype==$mod_contacttype)
        print("selected ");
      print("label=\"$description\" value=\"$contacttype\">$description</option>\n");
   }
   print("</select>\n");
   print("</td>");
   print("</tr>\n");
   print("<tr>");
   print("<td class=\"centered\" colspan=\"2\">");
   print("<input class=\"button\" type=\"submit\" name=\"mod_submit\" value=\"".$lang['submit_changes']."\"><br>\n");
   print("<input class=\"button\" type=\"submit\" name=\"mod_delete\" value=\"".$lang['delete_this_record']."\"><br>\n");
   print("</td>\n");
   print("</tr>\n");
   print("</table>");
   print("</form>\n");
}
else
{
   printf("<span class=\"message\">".$lang['contact_not_in_ext_dir']."</span>",$showuserid );
}

$help_keyword="extdiradminedit";
?>
