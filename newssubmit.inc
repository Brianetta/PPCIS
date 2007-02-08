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

// This file contains a form and a preview section to allow users to
// edit and submit their own news articles.  Articles are inserted into
// the news table with their authorised field set to 'n', ready to be
// reviewed by a news admin.

if(!(isset($submit)))
{
   if(!isset($url) or ($url==""))
      $url="http://";
   print("<form method=\"post\" id=\"news_submit\" action=\"$PHP_SELF?callmodule=".urlencode($lang['submit_new_article'])."\">");
   print("<table>\n");
   print("<tr>");
   print("<th class=\"headline\">\n");
   print($lang['headline'].":<input name=\"headline\" type=\"text\" size=\"50\" value=\"".safe_escape($headline)."\">\n");
   print("<select name=\"topic\">\n");
   foreach($topiclist as $topicid => $name)
   {
      if($topic==$topicid)
      {
         print("<option selected label=\"$name\" value=\"$topicid\">$name</option>\n");
      }
      else
      {
         print("<option label=\"$name\" value=\"$topicid\">$name</option>\n");
      }
   }
   print("</select>\n");
   print("</th>\n");
   print("</tr>\n");
   print("</table>\n");
   print("<table>\n");
   print("<tr>\n");
   print("<td>\n");
   print($lang['article_text'].":<br><textarea name=\"body\" rows=\"20\" cols=\"60\">".strip_tags(stripslashes($body),"<b><i><span>")."</textarea>");
   print("<br>\n".$lang['optional_url']."<br><input name=\"url\" type=\"text\" size=\"60\" value=\"$url\">");
   print("\n</td>\n");
   print("</tr>\n");
   print("</table>\n");
   print($lang['if_happy_check_this_submit']."<input type=\"checkbox\" name=\"submit\"><br><br>");
   print($lang['click_submit_to_preview_warning']."<br><input class=\"button\" type=\"submit\" name=\"newnews\" value=\"".$lang['submit_article']."\"><br>");
   print("</form>");
}
else
{
   if(isset($url) and ($url<>"") and ($url<>"http://"))
   { // Code to insert a URL into the SQL statement
      $url=trim($url);
      $nurl=", '".safe_escape($url)."'";
      $urlfield=", url";
   } else {
      $url="";
      $urlfield="";
   }
   if($auto_authorise_news)
   { // If we don't want to bother with news admins authorising news...
      $auth=(time()+5); // Just because it gets run first doesn't mean I like the idea of authorising a news article before it's submitted.
      $nauth=", '".safe_escape($auth)."'";
      $authfield=", authdate";
   } else {
      $auth="";
      $authfield="";
   }
   $sql = "INSERT INTO news (authorid, subdate, headline, topic, body$urlfield$authfield) VALUES ($userid, '".time()."', '".safe_escape(stripslashes($headline))."', $topic, '".safe_escape(strip_tags($body,"<b><i><span>"))."'$nurl$nauth)";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   $articlenumber = mysql_insert_id();
   $sql = "SELECT userid, firstname, lastname FROM users ORDER BY lastname";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   if(@ mysql_num_rows($result) != 0)
   {
      while($row = @ mysql_fetch_array($result))
      {
         $userhash[$row["userid"]]=$row["firstname"]." ".$row["lastname"];
         $userrevhash[$row["userid"]]=$row["lastname"].", ".$row["firstname"];
      }
   }
   foreach($userhash as $index => $name)
   {
      if($name==$news_notify AND $use_mail)
      {
         $sql = "SELECT email FROM userdirectory WHERE userid=$index";
         $result = @ mysql_query($sql, $intranet_db);
         if (mysql_error())
            showerror();
         $recipient = @ mysql_fetch_array($result);
         $subject= $lang['email_news_article_submitted']."- $headline";
         $message  =sprintf($lang['email_user_submitted_article'].":\n",$firstname,$lastname);
         $message .="\n";
         $message .=strip_tags($headline)."\n\n";
         $message .=strip_tags($body)."\n";
         mail($recipient["email"], $subject, $message, $mailfrom);
      }
   }
}

print("<h2>".$lang['preview'].":</h2>");
newsitem(strip_tags(stripslashes($headline)), strip_tags(stripslashes($body),"<b><i><span>"), $topic, time(), $firstname." ".$lastname, $url, 0);
$help_keyword="newssubmit";
?>
