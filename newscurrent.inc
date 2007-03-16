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

// This file displays the ten most recent news artiles, in full, after
// filtering has been taken into account.  By default, it will display
// the ten most recent articles.  If a topic is selected, it will display
// the ten most recent articles in that topic.  Any older articles can
// be found in the archived news section.

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
$sql = "SELECT * FROM news LEFT JOIN users ON users.userid = news.authorid WHERE news.authdate IS NOT NULL";
if($topic<>"0") $sql .= " AND news.topic=$topic";
$sql .= " ORDER BY sticky,news.subdate DESC LIMIT 10";

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
$help_keyword="newscurrent"
?>
