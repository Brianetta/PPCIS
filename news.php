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

// This file is a module which builds the second layer news menu
// and includes other files in order to fulfill the functions
// selected from that menu.

unset($auto_authorise_news); // No hacking your way past here.  It's either set
                             // from settings.inc or nowhere at all.
require("head.inc");

if(!(isset($auto_authorise_news))) // Line's missing from settings.inc
   $auto_authorise_news=FALSE;

// Build an array to cache the news topics
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
   $topiclist[1]="No topics defined";
}

// Function to display just the headlines, with a link to the article
function newshead($news_headline, $news_date, $name, $url, $article, $sticky)
{
   global $lang;
   global $allowed_tags;
   $news_date = date($lang['date_format'], $news_date);
   print("<table>\n");
   print("<tr>");
   print("<th class=\"headline\" width=\"35%\">\n");
   print(strip_tags($news_headline,"<i>"));
   print("</th>\n");
   print("<th class=\"headline\">\n");
   print($name);
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
   print("<th class=\"headline_center\" width=\"10%\">\n");
   print("<a href=\"$url\">".$lang['VIEW']."</a>");
   print("</th>\n");
   print("<th class=\"print\" width=\"10%\">\n");
   print("<a target=\"_BLANK\" href=\"newsprint.php?article=$article\">".$lang['PRINT']."</a>");
   print("</th>\n");
   print("</tr>\n");
   print("</table>\n");
   return(true);
}

// Function to display a single article in full
function newsitem($news_headline, $news_body, $news_topic, $news_date, $name, $url="", $article, $sticky)
{
   global $topiclist;
   global $lang;
   global $allowed_tags;
   $news_body = strip_tags($news_body,$allowed_tags);
   preg_match_all('/IMAGE[0-9]*HERE/',$news_body,$news_images);
   foreach($news_images[0] as $key => $value)
   {
      $news_images[0][$key] = str_replace('IMAGE','<img src="fetchfile.php?fileid=',$news_images[0][$key]);
      $news_images[0][$key] = str_replace('HERE','">',$news_images[0][$key]);
      $news_body = preg_replace('/IMAGE[0-9]*HERE/',$news_images[0][$key],$news_body,1);
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
   print("<th class=\"print\" width=\"10%\">\n");
   print("<a target=\"_BLANK\" href=\"newsprint.php?article=$article\">".$lang['PRINT']."</a>");
   print("</th>\n");
   print("</tr>\n");
   print("<tr>\n");
   print("<td colspan=3>\n");
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

unset($module);
// Build the second layer menu
$module[$lang['latest_news']]="newscurrent.inc";
if($userid<>0)
{
   $module[$lang['submit_new_article']]="newssubmit.inc";
}
$module[$lang['all_news_articles']]="newsarchive.inc";
if(!(isset($callmodule)))
   $callmodule=$lang['latest_news'];
?>

      <table border="0" cellpadding="0" cellspacing="1" width="100%">
        <tr>
        <?
          $mod_percent=100 / count($module);
          foreach($module as $mod_tag=>$mod_file) // Render the second layer menu
          {
            if($callmodule==$mod_tag)
            {
               $valid=true;
               print("<th class=\"module_selected\" width=\"$mod_percent%\">");
            }
            else
            {
               print("<th class=\"module\" width=\"$mod_percent%\">");
            }
            print("<a class=\"module\"  href=\"$PHP_SELF?callmodule=".rawurlencode($mod_tag)."\">$mod_tag</a></th>\n");
          }
        ?>
        </tr>
      </table>
      <? // Include the relevant file depending on the menu selection
        require("welcome.inc"); // Because this module is the one that index.php loads up.
      if(isset($valid))
      {
         require($module["$callmodule"]);
      }
      ?>

<?
require("tail.inc");
?>
