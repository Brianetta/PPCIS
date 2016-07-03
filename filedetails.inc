<?
   $help_keyword="filedetail";
   print("<a href=\"$PHP_SELF?folder=$folder\">".$lang['return_folder_listing']."</a>");
   if($showedit)
   {
      print("<form method=\"post\" id=\"filemod\" action=\"$PHP_SELF?fileid=$fileid\">");
      $help_keyword="filedetaila";
   }
   print("<table>");
   print("<tr>");
   print("<th class=\"detail\" colspan=\"4\">");
   print("<h2>$filename</h2>");
   printf("<i>".$lang['this_is_file']."</i><br>\n",$fileid);
   if($showedit)
      print($lang['rename'].": <input type=\"text\" name=\"modfilename\" value=\"$filename\">");
   print("</th>");
   print("</tr>\n");
   print("<tr>\n");
   if($showedit)
   {
      print("<td class=\"detail_mid_center\"><b>".$lang['move_to_folder'].":</b> </td><td class=\"detail_mid_center\">");
      print("<select name=\"newfolder\"><br>\n");
      print("<option value=\"0\">(0) ".$lang['root']."</option>\n");
      $sql = "select folders.folderid, if(parents.parent IS NULL,if(folders.parent = 0,concat('".safe_escape($lang['root'])." - ',folders.name),concat(parents.name,' - ',folders.name)),concat(' - ',parents.name,' - ',folders.name)) as name from folders left join folders as parents on parents.folderid = folders.parent order by parents.parent,folders.parent,folderid";
      $subresult = @ mysqli_query($intranet_db,$sql);
      showerror();
      if(@ mysqli_num_rows($subresult) != 0)
      {
         while($folders = @ mysqli_fetch_array($subresult,MYSQLI_ASSOC))
         {
            if($folders["folderid"] == $folder)
            {
               $selected=" selected";
            }
            else
            {
               $selected="";
            }
            print("<option$selected value=\"".$folders["folderid"]."\">(".$folders["folderid"].") ".$folders["name"]."</option>\n");
         }
      }
      print("</select\n");
      print("</td>");
      print("</td>");
   }
   else
   {
      print("<td class=\"detail_mid_center\"><b>".$lang['size'].":</b></td>\n");
      print("<td class=\"detail_mid_center\">$filesize ".$lang['bytes']."</td>\n");
   }
   print("<td class=\"detail_mid_center\"><b>".$lang['mime_type'].":</b></td>\n");
   if($showedit)
      print("<td class=\"detail_mid_center\"><input type=\"text\" name=\"modtype\" value=\"$filetype\"></td>\n");
   else
      print("<td class=\"detail_mid_center\">$filetype</td>\n");
   print("</tr>\n");
   if(!$showedit and !$securefile)
   {
      print("<tr>\n");
      print("<td class=\"detail_mid_center\" colspan=\"2\"><a href=\"fetchfile.php?fileid=$fileid&mimetype=*/*\">".$lang['download_save']."</a></td>\n");
      print("<td class=\"detail_mid_center\" colspan=\"2\"><a href=\"fetchfile.php?fileid=$fileid\" target=\"_blank\">".$lang['open_file_new_win']."</a></td>\n");
      print("</tr>\n");
   }
   print("<tr>\n");
   print("<td class=\"detail\" colspan=\"4\">\n");
   print("<br>");
   if($showedit)
   {
      print("<textarea name=\"modsynopsis\" rows=\"10\" cols=\"60\">");
      print(strip_tags($filesynopsis,$allowed_tags));
   }
   else
   {
      print(strip_tags($filesynopsis,"<br>$allowed_tags"));
   }
   if($showedit)
      print("</textarea>\n");
   print("<br><br>\n");
   print("</td>");
   print("</tr>\n");
   if($showedit)
   {
      print("<tr>\n");
      print("<td class=\"centered\" colspan=\"4\">");
      print("<input class=\"button\" type=\"submit\" name=\"modfile\" value=\"".$lang['submit_changes']."\">\n");
      print("</form>\n");
      print("</td>\n");
      print("</tr>\n");
      print("<tr>\n");
      print("<td class=\"centered\" colspan=\"4\">");
      print("<form method=\"post\" id=\"addsecure\" action=\"$PHP_SELF\">");
      print("<select name=\"add_team\">\n");
   	$sql = "SELECT teams.teamid,name FROM teams LEFT JOIN filesecurity ON  teams.teamid=filesecurity.teamid AND fileid=$fileid WHERE fileid IS NULL";
   	$result = @ mysqli_query($intranet_db,$sql);
   	showerror();
   	if(mysqli_num_rows($result)>0)
   	{
      	while($row=@ mysqli_fetch_array($result,MYSQLI_ASSOC))
      	{
         	print("<option label=\"".$row["name"]."\" value=\"".$row["teamid"]."\">");
         	print($row["name"]);
         	print("</option>");
      	}
		}
      print("</select>");
      print("<input class=\"button\" type=\"submit\" name=\"addsecure\" value=\"".$lang['add_team_secure']."\">");
      print("<input type=\"hidden\" name=\"fileid\" value=\"$fileid\">");
      print("</td>\n");
      print("</tr>\n");
   }
   else
   {
      if($filesadmin)
      {
         print("<tr>\n");
         print("<td class=\"centered\" colspan=\"4\">");
         print("<a href=\"files.php?fileid=$fileid&edit=yes\">".$lang['adjust_file']."</a>");
         print("</td>\n");
         print("</tr>\n");
      }
   }
   $sql = " SELECT fileid, teamid FROM filesecurity WHERE fileid=$fileid";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
   if(mysqli_num_rows($result)>0)
   {
      while($row=@ mysqli_fetch_array($result,MYSQLI_ASSOC))
      {
         print("<tr>\n");
         print("<td class=\"right\" colspan=\"2\">");
         if($showedit)
         {
            print("<form method=\"post\" id=\"delsecure\" action=\"$PHP_SELF\">\n");
            print("<input class=\"button\" type=\"submit\" name=\"delsecure\" value=\"".$lang['remove_team_secure']."-->\">\n");
            print("<input type=\"hidden\" name=\"fileid\" value=\"$fileid\">");
            print("<input type=\"hidden\" name=\"del_team\" value=\"".$row["teamid"]."\">");
            print("</form>");
         }
         else
            print($lang['allowed_team'].": ");
         print("</td>\n");
         print("<td colspan=\"2\">");
         print($teamhash[$row["teamid"]]);
         print("</td>\n");
         print("</tr>\n");
      }
   }
   else
   {
      print("<tr>\n");
      print("<td class=\"centered\" colspan=\"4\">");
      print($lang['file_not_restricted']);
      print("</td>\n");
      print("</tr>\n");
   }
   if($showedit)
   {
      print("<tr>\n");
      print("<td colspan=\"4\">");
      print("<form method=\"post\" id=\"filedel\" action=\"$PHP_SELF\">\n");
      print($lang['tick_confirm_delete'].":<input type=\"checkbox\" name=\"delconf\" value=\"confirm\">\n");
      print("<input class=\"button\" type=\"submit\" name=\"delfile\" value=\"".$lang['delete_file']."\">\n");
      print("<input type=\"hidden\" name=\"fileid\" value=\"$fileid\">\n");
      print("</form>");
      print("</td>\n");
      print("</tr>\n");
   }
   print("</table>\n");
?>
