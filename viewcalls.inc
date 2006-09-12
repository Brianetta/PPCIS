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

// This file decides whether to show a list of all open calls
// to the helpdeskadmin (all callos owned by the logged in user
// otherwise) or whether to show the details of a specific call,
// based on the $callid variable.
//
// It is also where the email to a helpdeskadmin is generated when
// a call is assigned to them.

if(isset($callid))
   if(!is_numeric($callid))
      unset($callid);

if(isset($modify_call_b))
   $modify_call=$modify_call_b;
if(isset($modify_call_a))
   $modify_call=$modify_call_a;
if(isset($modify_call) AND isset($callid))
{
   $sql = "SELECT * FROM helpdesk WHERE callid=$callid";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   if(@ mysql_num_rows($result) != 0)
   {
      $call = @ mysql_fetch_array($result);
   }
   if ($helpdeskadmin)
   {
      $sql = "UPDATE helpdesk SET ownerid=$mod_name, locationid=$mod_location, priority=$mod_priority, category=$mod_category";
      if(isset($mod_closed))
         $sql .= ", closedate=".time();
      $sql .= " WHERE callid=$callid";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
      elseif(isset($mod_closed))
      {
         $sql = "INSERT INTO history (callid, userid, histdate, body, system) VALUES ($callid, $userid, ".time().", '".$lang['call_closed']."','y')";
         $result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
      }
      if (isset($del_assignee))
      {
         $sql = "DELETE FROM assignees WHERE userid=$del_assignee AND callid=$callid";
         $result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
         else
         {
            $sql = "SELECT firstname,lastname FROM users WHERE userid=$del_assignee";
            $result = @ mysql_query($sql, $intranet_db);
            if (mysql_error())
               showerror();
            $name = @ mysql_fetch_array($result);
            $sql = "INSERT INTO history (callid, userid, histdate, body, system) VALUES ($callid, $userid, ".time().", '".$lang['removed_assignment']." - ".$name["firstname"]." ".$name["lastname"]."','y')";
            $result = @ mysql_query($sql, $intranet_db);
            if (mysql_error())
               showerror();
         }
      }
   }
   elseif ($call["ownerid"]==$userid)
   {
      $sql = "UPDATE helpdesk SET locationid=$mod_location";
      if(isset($mod_closed))
         $sql .= ", closedate=".time();
      $sql .= " WHERE callid=$callid";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
      elseif(isset($mod_closed))
      {
         $sql = "INSERT INTO history (callid, userid, histdate, body, system) VALUES ($callid, $userid, ".time().", '".$lang['call_closed']."','y')";
         $result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
      }
   }
   if ($helpdeskadmin)
   {
      if (isset($add_assignee_name) and ($add_assignee_name>0))
      {
         $sql = "INSERT INTO assignees (callid, userid) VALUES ($callid, $add_assignee_name)";
         $result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
         else
         {
            $sql = "SELECT firstname,lastname FROM users WHERE userid=$add_assignee_name";
            $result = @ mysql_query($sql, $intranet_db);
            if (mysql_error())
               showerror();
            $name = @ mysql_fetch_array($result);
            $sql = "INSERT INTO history (callid, userid, histdate, body, system) VALUES ($callid, $userid, ".time().", '".$lang['assigned_support']." - ".$name["firstname"]." ".$name["lastname"]."','y')";
            $result = @ mysql_query($sql, $intranet_db);
            if (mysql_error())
               showerror();
         }
         if($use_mail)
         {
            $sql = "SELECT email FROM userdirectory WHERE userid=$add_assignee_name";
            $result = @ mysql_query($sql, $intranet_db);
            if (mysql_error())
               showerror();
            $recipient = @ mysql_fetch_array($result);
            $subject= $lang['email_support_call_assignment']." - ".str_pad($callid,4,"0",STR_PAD_LEFT);
            $message  = sprintf($lang['email_assigned_call'],$userhash[$userid]);
            $message .="\n\n";
            $message .=$lang['email_call_number']  .": ".str_pad($callid,4,"0",STR_PAD_LEFT)."\n";
            $message .=$lang['email_call_owner']   .": ".$userhash[$mod_name]."\n";
            $message .=$lang['email_call_location'].": ".$locations[$mod_location]."\n";
            $message .=$lang['email_call_category'].": ".$callc[$mod_category]."\n";
            $message .=$lang['url'].": http://$HTTP_HOST$PHP_SELF?callmodule=".rawurlencode($callmodule)."&callid=$callid\n";
            mail($recipient["email"], $subject, $message, $mailfrom);
            $assignee_active='N';
         }
      }
   }
   if (($helpdeskadmin) OR ($call["ownerid"]==$userid))
   {
      if ($mod_history!="")
      {
         $sql = "INSERT INTO history (callid, userid, histdate, body) VALUES ($callid, $userid, ".time().", '".safe_escape(strip_tags($mod_history,"<b><i>"))."')";
         $result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
      }
   }
   if ($helpdeskadmin)
   {
      $sql = "UPDATE assignees SET active='$assignee_active' WHERE userid=$userid AND callid=$callid";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
   }

}

if(isset($callid))
{
   require("viewcalldetail.inc");
}
else
{
   require("viewcalllist.inc");
}
?>
