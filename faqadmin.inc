<?php
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

// This file allows helpdesk staff to edit and add FAQs in the database.  It has the
// same search facilities as the user version.

function displayfaq($faqid, $question, $faqcategory)
{
   global $PHP_SELF;
   print("<tr>");
   print("<td class=\"list\">\n");
   print($faqid." <a href=\"$PHP_SELF?callmodule=".rawurlencode($GLOBALS["callmodule"])."&editfaq=$faqid\">".strip_tags($question)."</a>");
   print("</td>\n");
   print("<td class=\"list\">\n");
   print($faqcategory);
   print("</td>\n");
   print("</tr>\n");
   return(true);
}

if(isset($editfaq))
{ // This section is the part that lets you edit a specific FAQ.
   if(isset($faqdelete))
   { // This section is for deleting a FAQ.
      $sql = "DELETE FROM faq WHERE faqid = ".$editfaq." LIMIT 1";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
      printf("<span class=\"message\">".$lang['faq_deleted']."</span>\n",$editfaq);
   }
   else
   {
      $sql = "SELECT * FROM faq WHERE faqid = ".$editfaq;
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
      if((@ mysqli_num_rows($result) != 0) OR ($editfaq==0))
      {
         if(isset($faqmodify))
         {
            if($editfaq>0)
            {
               $sql = "UPDATE faq SET categoryid='$mod_category', question='".safe_escape($mod_question)."', answer='".safe_escape($mod_answer)."' WHERE faqid = ".$editfaq;
               $result = @ mysqli_query($intranet_db,$sql);
               showerror();
            }
            else
            {
               $sql = "INSERT INTO faq (question, answer, categoryid) VALUES ('".safe_escape($mod_question)."','".safe_escape($mod_answer)."', $mod_category)";
               $result = @ mysqli_query($intranet_db,$sql);
               showerror();
               $editfaq = mysqli_insert_id($intranet_db);
            }
            $sql = "SELECT * FROM faq WHERE faqid = ".$editfaq;
            $result = @ mysqli_query($intranet_db,$sql);
            showerror();
         }
         print("<form method=\"post\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."&editfaq=".$editfaq."\">\n");
         print("<table>");
         $row = @ mysqli_fetch_array($result,MYSQLI_ASSOC);
         print("<tr>");
         print("<td>");
         print("Category:</td>");
         print("<td>");
         print("<select name=\"mod_category\">\n");
         foreach($faqc as $categoryid => $name)
         {
            print("<option ");
            if($categoryid==$row["categoryid"])
               print("selected ");
            print("value=\"$categoryid\">$name</option>\n");
         }
         print("</select>\n");
         print("</td>\n");
         print("</tr>\n");
         print("<tr>");
         print("<td>");
         print($lang['question'].":</td><td><input type=\"text\" size=\"80\" name=\"mod_question\" value=\"".$row["question"] . "\"><br>\n");
         print("</td>\n");
         print("</tr>\n");
         print("<tr>");
         print("<td>");
         print($lang['answer'].":</td><td><textarea name=\"mod_answer\" rows=\"10\" cols=\"80\">".$row["answer"]."</textarea><br>\n");
         print("</td>\n");
         print("</tr>\n");
         print("<tr>");
         print("<td class=\"centered\" colspan=\"2\">");
         if($editfaq>0)
         {
            printf("<input class=\"button\" type=\"submit\" name=\"modify\" value=\"".$lang['modify_faq']."\"><br>\n",$editfaq);
            printf("<input class=\"button\" type=\"submit\" name=\"faqdelete\" value=\"".$lang['delete_faq']."\"><br>\n",$editfaq);
         }
         else
         {
            print("<input class=\"button\" type=\"submit\" name=\"modify\" value=\"".$lang['create_faq']."\"><br>\n");
         }
         print("<input type=\"hidden\" name=\"faqmodify\" value=\"$editfaq\"><br>\n");
         print("</td>\n");
         print("</tr>\n");
         print("</table>");
         print("</form>\n");
      }
      else
      {
         printf("<span class=\"message\">".$lang['faq_not_exist']."</span><br>\n",$editfaq);
      }
   }
}
else
{ // This section lets you locate a specific FAQ for editing.
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

   print("<table>\n");
   displayfaq(0, $lang['create_faq'],$lang['new']);
   print("</table>\n");

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
         //print((".$faqc[$row["categoryid"]].") ".$row["question"]."<br>\n");
         //print($row["answer"]."<br>\n<hr>\n");
         displayfaq($row["faqid"],$row["question"],$faqc[$row["categoryid"]]);
      }
   	print("</table>\n");
   }
   else
   {
      print("<h1>".$lang['no_faqs_found']."</h1>\n");
   }
}

$help_keyword="faqadmin";
if(isset($editfaq))
{
   if($editfaq>0)
      $help_keyword.="m";
   else
      $help_keyword.="c";
}
?>
