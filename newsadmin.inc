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

// This file allows news admin users to view all news articles, authorised
// or not, and to edit, authorise and/or delete any articles.

$sql = "SELECT * FROM newstopic ORDER BY name";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   while($row = @ mysql_fetch_array($result))
   {
      $topiclist[$row["topicid"]]=$row["name"];
   }
}
else
{
   $topiclist[1]=$lang['no_topics_defined'];
}

function newshead($news_headline, $news_date, $name, $url, $authed=FALSE)
{
   global $lang;
   $news_date = date($lang['date_format'], $news_date);
   print("<table>\n");
   print("<tr>");
   print("<th class=\"headline\" width=\"35%\">\n");
   print(strip_tags($news_headline));
   print("</th>\n");
   print("<th class=\"headline\">\n");
   if($authed) print("<i>[");
   print("$name");
   if($authed) print("]</i>");
   print("</th>\n");
   print("<th class=\"headline_right\">\n");
   print($news_date);
   print("</th>\n");
   print("<th width=\"10%\">\n");
   print("<a href=\"$url\">".$lang['details']."</a>");
   print("</th>\n");
   print("</tr>\n");
   print("</table>\n");
   return(true);
}

function newsitem($news_headline, $news_body, $news_topic, $news_date, $name, $url="", $sticky)
{
   global $topiclist;
   global $lang;
   global $allowed_tags;
   global $file_store;
   $news_body = strip_tags($news_body,$allowed_tags);
   preg_match_all('/IMAGE[0-9]*HERE/',$news_body,$news_images);
   foreach($news_images[0] as $key => $value)
   {
      $fileid = str_replace('HERE','',str_replace('IMAGE','',$value));
      if($news_image_info = getimagesize($file_store . $fileid))
      {
         $news_images[0][$key] = str_replace('IMAGE',"<img ${news_image_info[3]} src=\"fetchfile.php?fileid=",$news_images[0][$key]);
         $news_images[0][$key] = str_replace('HERE','">',$news_images[0][$key]);
         $news_body = preg_replace('/IMAGE[0-9]*HERE/',$news_images[0][$key],$news_body,1);
      }
      else
      {
         $news_body = preg_replace('/IMAGE[0-9]*HERE/',$lang['image_broken'],$news_body,1);
      }
   }
   $news_date = date($lang['date_format'], $news_date);
   print("<table>\n");
   print("<tr>");
   print("<th class=\"headline\">\n");
   print($topiclist[$news_topic]);
   print("</th>\n");
   print("<th class=\"headline_right\">\n");
   if ($sticky)
   {
      print $lang['sticky'];
   }
   else
   {
      print($news_date);
   }
   print("</th>\n");
   print("</tr>\n");
   print("</table>\n");
   print("</th>\n");
   print("</tr>\n");
   print("<td colspan=\"2\">\n");
   print("<h1>".strip_tags($news_headline)."</h1>");
   print(nl2br(strip_tags($news_body,"$allowed_tags<img>")));
   if(($url<>"") and ($url<>"http://"))
      print("<br>\n<br>\n".$lang['related_link'].": <a href=\"$url\">$url</a>");
   print("<br>\n<br>\n<i>".$lang['submitted_by']." $name</i><br>\n<br>\n");
   print("\n</td>\n");
   print("</tr>\n");
   print("</table>\n");
   return(true);
}

if(!(isset($startarticle)))
   $startarticle="0";
$startarticlenum=(intval($startarticle));
$startarticlenum=($startarticlenum-($startarticlenum%30));
$startarticle=strval($startarticlenum);
$sql = "SELECT * FROM news LEFT JOIN users ON users.userid = news.authorid ORDER BY news.subdate DESC";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
$num_articles = @ mysql_num_rows($result);

if(isset($select))
{
   if(isset($authorise))
   {
      if(isset($url) and ($url<>"") and ($url<>"http://"))
      {
         $url=trim($url);
         $nurl="'".safe_escape($url)."'";
      } else {
         $nurl="NULL";
      }
      $sql = "UPDATE news SET authdate=".time().", headline='".safe_escape($headline)."', topic=$topic, body='".safe_escape($body)."', url=$nurl";
      if(isset($stickycheck))
         $sql .= ", sticky='y'";
      else
         $sql .= ", sticky='n'";
      $sql .= " WHERE articleid=$select";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
   }
   elseif(isset($delete))
   {
      $sql = "DELETE FROM news WHERE articleid=$select LIMIT 1";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
   }
   else
   {
      $sql = "SELECT * FROM news LEFT JOIN users ON users.userid = news.authorid WHERE articleid=$select";
      $result = @ mysql_query($sql, $intranet_db);
      if (mysql_error())
         showerror();
      if(@ mysql_num_rows($result) != 0)
      {
         while($row = @ mysql_fetch_array($result))
         {
            if(!isset($url))
               if($row["url"]=="")
                  $url="http://";
               else
                  $url=$row["url"];
            if(isset($body)) $row["body"]=$body;
            if(isset($topic)) $row["topic"]=$topic;
            if(isset($headline)) $row["headline"]=$headline;
            newsitem($row["headline"], $row["body"], $row["topic"], $row["subdate"], $row["firstname"]." ".$row["lastname"], $url,$row["sticky"]=='y');
            print("<form method=\"post\" id=\"news_authorise\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."&startarticle=$startarticle&select=$select\">");
            print("<table>\n");
            print("<tr>");
            print("<th class=\"headline\">\n");
            print($lang['headline'].":<input name=\"headline\" type=\"text\" size=\"50\" value=\"".stripslashes($row["headline"])."\">\n");
            print("<select name=\"topic\">\n");
            foreach($topiclist as $topicid => $name)
            {
               if($topicid==$row["topic"])
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
            print($lang['check_here_to_make_sticky']."<input type=\"checkbox\" ");
            if(isset($stickycheck))
               print("checked ");
            else
               if($row["sticky"]=="y" and !(isset($newnews)))
                  print("checked ");
            print("name=\"stickycheck\"><br><br>");
            print($lang['article_text'].":<br><textarea name=\"body\" rows=\"20\" cols=\"60\">".strip_tags(stripslashes($row["body"]),$allowed_tags)."</textarea>");
            print("<br>\n".$lang['optional_url'].":<br><input name=\"url\" type=\"text\" size=\"60\" value=\"$url\">");
            print("\n</td>\n");
            print("</tr>\n");
            print("</table>\n");
            print($lang['if_happy_check_this_authorise']."<input type=\"checkbox\" name=\"authorise\"><br><br>");
            print($lang['check here to delete']."<input type=\"checkbox\" name=\"delete\"><br><br>");
            print($lang['click_authorise_to_preview_warning']."<br><input class=\"button\" type=\"submit\" name=\"newnews\" value=\"authorise\"><br>");
            print("</form>");
         }
      }
   }
}

if($num_articles>30)
{
   print("<table><tr>\n");
   print("<td width=\"10%\">");
   if($startarticlenum>29)
      print("<a href=\"$PHP_SELF?callmodule=".urlencode($lang['news_admin'])."&startarticle=".($startarticlenum-30)."\">&lt;-NEWER</a> ");
   else
      print("&lt;-NEWER");
   print("</td>\n");
   for($page=1; $page <= (1 + ($num_articles - 1) / 30); $page++)
   {
      print("<b>");
      if(($page*30-$startarticlenum)==30)
      {
         print("<td>");
         print("$page");
         print("</td>\n");
      }
      else
      {
         print("<td>");
         print("<a href=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."&startarticle=".(($page-1)*30)."\">$page</a>");
         print("</td>\n");
      }
      print("</b>");
   }
   print("<td width=\"10%\">");
   if($startarticlenum<($num_articles-29))
      print("<a href=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."&startarticle=".($startarticlenum+30)."\">OLDER-&gt;</a> ");
   else
      print("OLDER-&gt;");
   print("</td>\n");
   print("</tr></table>\n");
}

$sql = "SELECT * FROM news LEFT JOIN users ON users.userid = news.authorid ORDER BY news.subdate DESC,news.articleid DESC LIMIT ".strval($startarticlenum).",30";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   print($lang['not_yet_authorised_articles_look_like_this']);
   while($row = @ mysql_fetch_array($result))
   {
      if(isset($row["authdate"]))
         newshead($row["headline"], $row["subdate"], $row["firstname"]." ".$row["lastname"], "$PHP_SELF?callmodule=".urlencode($lang['news_admin'])."&startarticle=$startarticle&select=".$row["articleid"], FALSE);
      else
         newshead($row["headline"], $row["subdate"], $row["firstname"]." ".$row["lastname"], "$PHP_SELF?callmodule=".urlencode($lang['news_admin'])."&startarticle=$startarticle&select=".$row["articleid"], TRUE);
   }
}

$help_keyword="newsadmin";
?>
