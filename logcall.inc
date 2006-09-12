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

// This form adds a new call to the helpdesk table.  Very simple, it
// calls itself with the log variable set.  If log is set, it adds
// the record and gives the user the call's unique ID.  If not, it
// presents a form for the user to add a call with.
//
// Helpdesk admins can also choose a user other than themselves when
// logging a call; this is to facilitate the logging of helpdesk calls
// by other means, such as by telephone.
//
// Regardless, when a call is successfully logged, an email is generated
// and sent to the person named in the settings.inc file.

if(isset($log))
{
   //show_call($firstname, $lastname, time(), $mod_categoryid, $mod_location, $mod_call);
   print("<h2>".$lang['your_call_logged']."</h2>");
   $log_timestamp=time();
   if(!$helpdeskadmin)
      $mod_name=$userid;
   $sql = "INSERT INTO helpdesk (ownerid, locationid, description, date, category) VALUES ($mod_name, $mod_location, '".safe_escape(strip_tags($mod_call,"<b><i>"))."', $log_timestamp, $mod_categoryid)";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   $row = @ mysql_fetch_array($result);
   $callnumber = mysql_insert_id();
   printf($lang['your_call_number_is'],"<a href=\"helpdesk.php?callmodule=".urlencode($lang['manage_calls'])."&callid=$callnumber\">".str_pad($callnumber,4,"0",STR_PAD_LEFT)."</a>");
   foreach($userhash as $index => $name)
   {
      if($name==$support_notify AND $use_mail)
      {
         $sql = "SELECT email FROM userdirectory WHERE userid=$index";
         $result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
         $recipient = @ mysql_fetch_array($result);
         $subject = $lang['email_support_call_logged']." - ".str_pad($callnumber,4,"0",STR_PAD_LEFT);
         $message  = sprintf($lang['email_user_logged_call'],$userhash[$mod_name]) ;
         $message .= "\n";
         $message .= $lang['email_call_number'].  ": ".str_pad($callnumber,4,"0",STR_PAD_LEFT)."\n";
         $message .= $lang['email_call_location'].": ".$locations[$mod_location]."\n";
         $message .= $lang['email_call_category'].": ".$callc[$mod_categoryid]."\n";
         $message .= $lang['email_call_details']. ":\n\n";
         $message .= strip_tags($mod_call)."\n";
         mail($recipient["email"], $subject, $message, $mailfrom);
      }
   }
}
else
{
   print("<form  method=\"post\" id=\"logcall\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">");
   print("&nbsp;".$lang['call_type'].":&nbsp;");
   print("<select name=\"mod_categoryid\">\n");
   foreach($callc as $categoryid => $name)
   {
      print("<option ");
      if($categoryid==$mod_categoryid)
         print("selected ");
      print("label=\"$name\" value=\"$categoryid\">$name</option>\n");
   }
   print("</select>\n");
   $sql = "SELECT location FROM userdirectory WHERE userid=$userid";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   if(@ mysql_num_rows($result) != 0)
   {
      while($row = @ mysql_fetch_array($result))
      {
         $defaultlocation=$row["location"];
      }
   }
   if(!(isset($mod_location)))
      $mod_location=$defaultlocation;
   if($helpdeskadmin)
   {
      print("&nbsp;".$lang['user'].":&nbsp;");
      print("<select name=\"mod_name\">\n");
      foreach($userrevhash as $index => $name)
      {
         if($index==$userid)
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
      print("<input type=\"hidden\" name=\"mod_name\" value=\"$userid\">\n");
   }
   print("&nbsp;".$lang['location'].":&nbsp;");
   print("<select name=\"mod_location\">\n");
   foreach($locations as $location => $name)
   {
      print("<option ");
      if($location==$mod_location)
         print("selected ");
      print("label=\"$name\" value=\"$location\">$name</option>\n");
   }
   print("</select><br>\n");
   print("<br>".$lang['give_details_of_request']."<br>");
   print("&nbsp;<textarea name=\"mod_call\" rows=\"10\" cols=\"60\">".strip_tags($mod_call,"<b><i><br><p>")."</textarea><br>\n");
   print("&nbsp;<input class=\"button\" type=\"submit\" name=\"log\" value=\"".$lang['log_call']."\">");
   print("</form>\n");
}

$help_keyword="logcall";
if($helpdeskadmin)
   $help_keyword.=a;
?>
