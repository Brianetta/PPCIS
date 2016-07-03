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

function displayfaq($faqid, $question, $faqcategory)
{
   global $PHP_SELF;
   print("<tr>");
   print("<td class=\"list\">\n");
   print($faqid." <a href=\"$PHP_SELF?callmodule=".rawurlencode($GLOBALS["callmodule"])."&faqnumber=$faqid\">".strip_tags($question)."</a>");
   print("</td>\n");
   print("<td class=\"list\">\n");
   print($faqcategory);
   print("</td>\n");
   print("</tr>\n");
   return(true);
}

if($faqnumber>0)
{ // This section is the part that lets you edit a specific FAQ.
   {
      $sql = "SELECT * FROM faq WHERE faqid = ".$faqnumber;
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
      if((@ mysqli_num_rows($result) != 0) OR ($faqnumber==0))
      {
         {
            $sql = "SELECT * FROM faq WHERE faqid = ".$faqnumber;
            $result = @ mysqli_query($intranet_db,$sql);
            showerror();
         }
         print("<table>");
         $row = @ mysqli_fetch_array($result,MYSQLI_ASSOC);
         print("<tr>");
         print("<th class=\"detail\">");
         print($lang['category'].":</th>");
         print("<th class=\"detail\">");
         foreach($faqc as $categoryid => $name)
         {
            if($categoryid==$row["categoryid"])
               print($name);
         }
         print("</th>\n");
         print("</tr>\n");
         print("<tr>");
         print("<th class=\"detail\">");
         print($lang['question'].":</th><th class=\"detail\"><h2>".$row["question"] . "</h2>\n");
         print("</th>\n");
         print("</tr>\n");
         print("<tr>");
         print("<th class=\"detail\">");
         print($lang['answer'].":</th><td class=\"detail\">\n");
         print(nl2br(strip_tags($row["answer"],$allowed_tags)));
         print("</td>\n");
         print("</tr>\n");
         print("</table>");
      }
      else
      {
         printf("<h1>".$lang['faq_not_exist']."</h1>\n",$faqnumber );
      }
   }
}
else
{ // This section lets you locate a specific FAQ.
   unset($faqnumber);
   print("<form method=\"get\" action=\"$PHP_SELF\">\n");
   print("<input type=\"hidden\" name=\"callmodule\" value=\"$callmodule\">");
   print("<select name=\"category\">\n");
   print("<option value=\"0\">".$lang['all_categories']."</option>\n");
   foreach($faqc as $categoryid => $name)
   {
      print("<option ");
      if($categoryid==$category)
         print("selected ");
      print("value=\"$categoryid\">$name</option>\n");
   }
   print("</select>\n");
   print(" ".$lang['word_search'].":<input type=\"text\" name=\"faqsearch\" value=\"$faqsearch\">");
   print(" ".$lang['faq_number'].":<input type=\"text\" name=\"faqnumber\" value=\"$faqnumber\">");
   print("<input class=\"button\" type=\"submit\" value=\"".$lang['filter']."\">");
   print("</form>\n");

   $sql = "SELECT * FROM faq WHERE 1";
   if ($category > 0)
   {
      $sql .= " AND categoryid=$category";
   }
   if ($faqsearch != "")
   {
      $sql .= " AND question LIKE '%$faqsearch%'";
   }
   $sql .= " ORDER BY faqid";
   if ($faqnumber > 0)
   {
      $sql = "SELECT * FROM faq WHERE faqid=$faqnumber";
   }
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
   if(@ mysqli_num_rows($result) != 0)
   {
   	print("<table>\n");
      while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
      {
         displayfaq($row["faqid"],$row["question"],$faqc[$row["categoryid"]]);
      }
   	print("</table>\n");
   }
   else
   {
      print("<h1>".$lang['no_faqs_found']."</h1>\n");
   }
}

$help_keyword="helpdeskfaq";
if(isset($faqnumber))
{
   if($faqnumber>0)
      $help_keyword.="r";
   else
      $help_keyword.="l";
}
?>
