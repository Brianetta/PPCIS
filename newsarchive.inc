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

// This file displays a paged list of all articles with the exception of
// the first ten, when filtering is taken into account.  The idea is
// that for a given filter, the first ten will appear on the main news
// page, and all the older articles will be here as "archived".

function fmod_x($x,$y)
{
   if ($y==0)
      return $x;
   $i = floor($x/$y);
   return $x - $i*$y;
}

if(!(isset($topic)))$topic="0";
print("<form method=\"post\" id=\"news_submit\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
print("<select name=\"topic\">\n");
print("<option label=\"".$lang['all_news_topics']."\" value=\"0\">".$lang['all_news_topics']."</option>\n");
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
print("<input class=\"button\" type=\"submit\" name=\"topicfilter\" value=\"".$lang['filter']."\">");
print("</form>\n");

if(!(isset($startarticle)))
   $startarticle="0";
$startarticlenum=(intval($startarticle));
$startarticlenum=($startarticlenum-($startarticlenum%30));
$startarticle=strval($startarticlenum);
$sql = "SELECT * FROM news LEFT JOIN users ON users.userid = news.authorid WHERE news.authdate IS NOT NULL";
if($topic<>"0") $sql .= " AND news.topic=$topic";
$sql .= " ORDER BY sticky,news.subdate DESC";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
$num_articles = @ mysql_num_rows($result);

if(isset($select))
{
   $sql = "SELECT * FROM news LEFT JOIN users ON users.userid = news.authorid WHERE news.authdate IS NOT NULL AND articleid=$select";
   $result = @ mysql_query($sql, $intranet_db);
   if (mysql_error())
      showerror();
   if(@ mysql_num_rows($result) != 0)
   {
      while($row = @ mysql_fetch_array($result))
      {
         newsitem($row["headline"], $row["body"], $row["topic"], $row["subdate"], $row["firstname"]." ".$row["lastname"], $row["url"], $row["articleid"],$row["sticky"]=='y');
      }
   }
}

if($num_articles>30)
{
   print("<table><tr>\n");
   print("<td class=\"pager\">");
   if($startarticlenum>29)
      print("<a href=\"$PHP_SELF?callmodule=".$lang['all_news_articles']."&startarticle=".($startarticlenum-30)."\">&lt;-".$lang['NEWER']."</a> ");
   else
      print("&lt;-".$lang['NEWER']);
   print("</td>\n");
   for($page=1; $page <= (1 + ($num_articles - 1) / 30); $page++)
   {
      print("<b>");
      if(($page*30-$startarticlenum)==30)
      {
         print("<td class=\"pager\" width=\"" . (int)(100/(max(30,fmod_x(30,($num_calls/60)))+2)) . "%\">");
         print("$page");
         print("</td>\n");
      }
      else
      {
         print("<td class=\"pager\" width=\"" . (int)(100/(max(30,fmod_x(30,($num_calls/60)))+2)) . "%\">");
         print("<a href=\"$PHP_SELF?callmodule=".$lang['all_news_articles']."&startarticle=".(($page-1)*30)."\">$page</a>");
         print("</td>\n");
      }
      print("</b>");
      if(($page-(floor($page/30)*30)) == 0)
         print("<td class=\"pager\" width=\"" . (int)(100/32) . "%\">&nbsp;</td></tr><tr><td class=\"pager\" width=\"" . (int)((100/max(30,fmod_x(30,($num_calls/60)))+2)) . "%\">&nbsp;</td>");
   }
   print("<td class=\"pager\">");
   if($startarticlenum<($num_articles-29))
      print("<a href=\"$PHP_SELF?callmodule=".$lang['all_news_articles']."&startarticle=".($startarticlenum+30)."\">".$lang['OLDER']."-&gt;</a> ");
   else
      print($lang['OLDER']."-&gt;");
   print("</td>\n");
   print("</tr></table>\n");
}

$sql = "SELECT * FROM news LEFT JOIN users ON users.userid = news.authorid WHERE news.authdate IS NOT NULL";
if($topic<>"0") $sql .= " AND news.topic=$topic";
$sql .= " ORDER BY sticky,news.subdate DESC,news.articleid DESC LIMIT ".strval($startarticlenum).",30";
$result = @ mysql_query($sql, $intranet_db);
if (mysql_error())
   showerror();
if(@ mysql_num_rows($result) != 0)
{
   while($row = @ mysql_fetch_array($result))
   {
      newshead($row["headline"], $row["subdate"], $row["firstname"]." ".$row["lastname"], "news.php?callmodule=".$lang['all_news_articles']."&startarticle=$startarticle&select=".$row["articleid"],$row["articleid"],$row["sticky"]=='y');
   }
}
$help_keyword="newsarchive";
?>
