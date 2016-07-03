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

// This is a two-section script.  One part performs directory struture
// listing, the other performs file details information.  They are
// seperated by a big, simple if statement.

function parent_recurse($tfolder)
{ // Crawl up the directory tree to list the ancestors.
   global $lang;
   global $intranet_db;
   global $recurse_count;
   global $folder;
   global $PHP_SELF;
   if($tfolder<>0)
   {
      $sql = "SELECT folderid,name,parent FROM folders WHERE folderid = $tfolder";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
      if(@ mysqli_num_rows($result) != 0)
      {
         while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
         {
            parent_recurse($row["parent"]);
            print("<ul class=\"folder_open\">\n");
            print("<li>\n");
            $recurse_count++; // Counting the list tags we've opened
            if($folder==$tfolder)
               print($row["name"]."\n");
            else
               print("<a href=\"$PHP_SELF?folder=".$row["folderid"]."\">".$row["name"]."</a>\n");
         }
      }
      else
      {
         print("<span class=\"message\">".$lang['this_folder_doesnt_exist']."</span>");
         $folder=0;
      }
   }
   else
   {
      print("<ul class=\"folder_open\">\n");
      print("<li>\n");
      $recurse_count++; // Counting the list tags we've opened
      if($folder==0)
         print($lang['root']."\n");
      else
         print("<a href=\"$PHP_SELF?folder=0\">".$lang['root']."</a>\n");
   }
}

// Build a hash of team names for the security lists
$sql = "SELECT teamid,name FROM teams ORDER BY name";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      $teamhash[$row["teamid"]]=$row["name"];
   }
}
else
{
   $teamhash[1]=$lang['no_teams_available'];
}

// Get the user's team for security checking
$sql = "SELECT team FROM userteams WHERE userid=$userid";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
if(@ mysqli_num_rows($result) != 0)
{
   $i=0;
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      $userteam[$i]=$row["team"];
      $i++;
   }
}

// Get the user's admin status for files first, and set $filesadmin
$sql = "SELECT files FROM userflags WHERE userid = $userid";
$result = @ mysqli_query($intranet_db,$sql);
showerror();
$filesadmin=FALSE;
if(@ mysqli_num_rows($result) != 0)
{
   while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
   {
      if($row["files"] == 'y')
      {
         $filesadmin=TRUE;
      }
   }
}

// Make any changes submitted by the form in this script from before
if(isset($modfile) and $filesadmin)
{
   $sql = "UPDATE files SET filename='".safe_escape($modfilename)."', mimetype='".safe_escape($modtype)."', synopsis='".safe_escape($modsynopsis)."', folder=\"$newfolder\" WHERE fileid=$fileid";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
}
// Add a team to the security list if requested
if(isset($addsecure) and $filesadmin and isset($add_team))
{
   $sql = "INSERT INTO filesecurity (fileid, teamid) VALUES ($fileid, $add_team)";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
}
// Remove a team to the security list if requested
if(isset($delsecure) and $filesadmin)
{
   $sql = "DELETE FROM filesecurity WHERE fileid=$fileid AND teamid=$del_team";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
}
// Delete the file if requested
if(isset($delfile) and $filesadmin)
{
   if($delconf=="confirm")
   {
      $sql = "SELECT folder FROM files WHERE fileid = $fileid";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
      if(@ mysqli_num_rows($result) != 0)
      {
         while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
         {
            $folder=$row["folder"];
            $sql = "DELETE FROM files WHERE fileid=$fileid LIMIT 1";
            $dresult = @ mysqli_query($intranet_db,$sql);
            showerror();
            $sql = "DELETE FROM filesecurity WHERE fileid=$fileid";
            $dresult = @ mysqli_query($intranet_db,$sql);
            showerror();
            if (is_writeable($file_store.$fileid))
            {
               unlink($file_store.$fileid);
            }
            unset($fileid);
         }
      }
   }
}
// Rename or move this folder if requested
if(isset($modfolder) and $filesadmin)
{
   $modname=trim($modname);
   if(strlen($modname)>1)
   {
      $sql = "UPDATE folders SET name='".safe_escape($modname)."', parent=$modparent WHERE folderid=$folder";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
   }
}
// Add new child folder if requested
if(isset($addfolder) and $filesadmin)
{
   if(isset($modname))
   {
      $modname=trim($modname);
      if(strlen($modname)>1)
      {
         $sql = "INSERT INTO folders (name,parent) VALUES ('".safe_escape($modname)."',$folder)";
         $result = @ mysqli_query($intranet_db,$sql);
         showerror();
      }
   }
}
// Delete folder if requested and if empty
if(isset($delfolder) and $filesadmin)
{
   $emptyfolder = TRUE; // Assume it's empty, then check...
   $sql = "SELECT COUNT(*) FROM folders WHERE parent=$folder";
   $result = @ mysqli_query($intranet_db,$sql);
   $row = mysqli_fetch_array($result,MYSQLI_NUM);
   if($row[0] > 0)
   { // This folder has chilren which are folders
      $emptyfolder = FALSE;
   }
   $sql = "SELECT COUNT(*) FROM files WHERE folder=$folder";
   $result = @ mysqli_query($intranet_db,$sql);
   $row = mysqli_fetch_array($result,MYSQLI_NUM);
   if($row[0] > 0)
   { // This folder has chilren which are files
      $emptyfolder = FALSE;
   }
   if($emptyfolder)
   {
      $sql = "DELETE FROM folders WHERE folderid=$folder LIMIT 1";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
   }
}

// Check the validity of $fileid if set, get its details and
// determine how secure it is.
if(isset($fileid))
{
   if(!(is_numeric($fileid)))
   {
      unset($fileid);
   }
   else
   {
      $sql = "SELECT fileid,filename,size,mimetype,folder,synopsis FROM files WHERE fileid = $fileid ORDER BY filename";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
      if(@ mysqli_num_rows($result) != 0)
      {
         while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
         {
            $folder=$row["folder"];
            $filename=$row["filename"];
            $filesize=$row["size"];
            $filetype=$row["mimetype"];
            $filesynopsis=nl2br($row["synopsis"]);
         }
      }
      else
      {
         print("<h1>".$lang['file_not_exist']."</h1>");
         unset($fileid);
      }
      // I re-use my query variables, so this is outside the above
      // if statement.  If the file doesn't exist, this has no impact
      // anyway, as the COUNT(*) should return zero, unless for some
      // reason there's duff data in the filesecurity table.
      $sql = "SELECT COUNT(*) FROM filesecurity WHERE fileid=$fileid";
      $result = @ mysqli_query($intranet_db,$sql);
      $securefile = TRUE; // This must be true
      $row = mysqli_fetch_array($result,MYSQLI_NUM);
      if($row[0] > 0)
      { // This file has one or more security records
         $sql = "SELECT teamid FROM filesecurity WHERE fileid=$fileid";
         $result = @ mysqli_query($intranet_db,$sql);
         while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
         { // Check to see if our team is on the list
            if(!empty($userteam))
               foreach($userteam as $teamtest)
                  if($row["teamid"]==$teamtest)
                     $securefile = FALSE;
         }
      }
      else // There is no access list, there is no restriction.
         $securefile = FALSE;
   }
}

// Current folder.  If not set, set to 0, which is assumed to be root,
// or get from current file record.
// If the DB has a folder with unique ID of 0, it will never be seen,
// which is no problem as it will also never be used.
if(!(isset($folder)))
{
   $folder=0;
}

if(!(is_numeric($folder)))
{
   $folder=0;
}

if(isset($edit) and $filesadmin)
   $showedit=TRUE; // Simplifies the ifs for the changes form.
   // Basically, this appears a lot.  If true, there's a form control.
   // If false, there isn't.
else
   $showedit=FALSE;

if(isset($fileid))
{ // mode is file details
   require("filedetails.inc");
}
else
{ // mode is directory listing
   $recurse_count=0;
   parent_recurse($folder);

   if($showedit)
      $help_keyword="filelista";
   else
      $help_keyword="filelist";

   // Find and print children
   $sql = "SELECT folderid,name FROM folders WHERE parent = $folder ORDER BY name";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
   if(@ mysqli_num_rows($result) != 0)
   {
      print("<ul class=\"folder\">");
      while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
      {
         print("<li>");
         print("<a href=\"$PHP_SELF?folder=".$row["folderid"]."\">".$row["name"]."</a><br>\n");
         print("</li>");
      }
      print("</ul>");
      $children = TRUE; // I use this later
   }
   else
      $children = FALSE;// I use this later

   // Close all the list tags that just got opened.
   for(;$recurse_count>0;$recurse_count--)
   {
      print("</li>\n</ul>\n");
   }

   // Print name of current folder
   if($folder<>0)
   {
      $sql = "SELECT folderid,name,parent FROM folders WHERE folderid = $folder";
      $result = @ mysqli_query($intranet_db,$sql);
      showerror();
      if(@ mysqli_num_rows($result) != 0)
      {
         while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
         {
            print("<h1>".$row["name"]."</h1><br>\n");
            printf("<i>".$lang['this_is_folder']."</i><br>\n",$folder);
            if($showedit)
            {
               print("<table>\n");
               print("<tr>");
               print("<form method=\"post\" id=\"modfolder\" action=\"$PHP_SELF\">\n");
               print("<td class=\"right\">");
               print($lang['rename'].":");
               print("</td>");
               print("<td>");
               print("<input type=\"text\" name=\"modname\" value=\"".$row["name"]."\"><br>\n");
               print("</td>");
               print("</tr>");
               print("<tr>");
               print("<td class=\"right\">");
               print($lang['move_to_folder'].":");
               print("</td>");
               print("<td>");
               print("<select name=\"modparent\"><br>\n");
               $sql = "select folders.folderid, if(parents.parent IS NULL,if(folders.parent = 0,concat('".safe_escape($lang["root"])." - ',folders.name),concat(parents.name,' - ',folders.name)),concat(' - ',parents.name,' - ',folders.name)) as name from folders left join folders as parents on parents.folderid = folders.parent order by parents.parent,folders.parent,folderid";
               print("<option value=\"0\">(0) ".$lang["root"]."</option>\n");
               $subresult = @ mysqli_query($intranet_db,$sql);
               showerror();
               if(@ mysqli_num_rows($subresult) != 0)
               {
                  while($folders = @ mysqli_fetch_array($subresult,MYSQLI_ASSOC))
                  {
                     if($folders["folderid"] == $row["parent"])
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
               print("</tr>");
               print("<tr>");
               print("<td class=\"centered\" colspan=\"2\" >");
               print("<input type=\"hidden\" name=\"folder\" value=\"$folder\">\n");
               print("<input class=\"button\" type=\"submit\" name=\"modfolder\" value=\"".$lang['modify_folder']."\">\n");
               print("</td>");
               print("</form>");
               print("</tr>");
               print("<tr>");
               print("<form method=\"post\" id=\"addfolder\" action=\"$PHP_SELF\">\n");
               print("<td class=\"right\">");
               print("<input class=\"button\" type=\"submit\" name=\"addfolder\" value=\"".$lang['add_new_folder'].":\">\n");
               print("<input type=\"hidden\" name=\"folder\" value=\"$folder\">\n");
               print("</td>");
               print("<td>");
               print("<input type=\"text\" name=\"modname\"><br>\n");
               print("</td>");
               print("</form>");
               print("</tr>");
               print("</table>");
            }
            else
            {
               if ($filesadmin)
                  print("<a href=\"$PHP_SELF?folder=$folder&edit=yes\">".$lang['adjust_folder']."</a><br>\n");
            }
         }
      }
      else
      {
         printf("<h1>".$lang['folder_not_exist']."</h1>\n",$row["folderid"]);
      }
   }
   else
   {
      print("<h1>".$lang['root']."</h1>\n");
      printf("<i>".$lang['this_is_folder']."</i><br>\n",$folder);
      if($filesadmin and $showedit)
      {
         print("<form method=\"post\" id=\"addfolder\" action=\"$PHP_SELF\">\n");
         print("<input class=\"button\" type=\"submit\" name=\"addfolder\" value=\"".$lang['add_new_folder'].":\">\n");
         print("<input type=\"hidden\" name=\"folder\" value=\"$folder\">\n");
         print("<input type=\"text\" name=\"modname\"><br>\n");
         print("</form>");
      }
      else
      {
         if ($filesadmin)
            print("<a href=\"$PHP_SELF?folder=$folder&edit=yes\">".$lang['adjust_folder']."</a><br>\n");
      }
   }
   if($filesadmin)
   {
      if(strlen($_FILES["uploadfile"]["name"])>0)
      { // This bit is to make file uploads work if register_globals is off.
         $uploadfile = $_FILES["uploadfile"]["tmp_name"];
         $uploadfile_name = $_FILES["uploadfile"]["name"];
         $uploadfile_size = $_FILES["uploadfile"]["size"];
         $uploadfile_type = $_FILES["uploadfile"]["type"];
      }
      if(isset($uploadfile))
      {
         if($uploadfile_size>0)
         {
            if(is_uploaded_file($uploadfile))
            {
               $sql = "INSERT INTO files (filename,size,mimetype,folder,synopsis,datestamp) VALUES ('$uploadfile_name',$uploadfile_size,'$uploadfile_type',$folder,'".safe_escape(strip_tags($synopsis,"<br>$allowed_tags"))."',".time().")";
               $result = @ mysqli_query($intranet_db,$sql);
               showerror();
               move_uploaded_file($uploadfile,$file_store.mysqli_insert_id($intranet_db));
               printf("<span class=\"message\">".$lang['file_name_size']."</span><br>\n",$uploadfile_name,$uploadfile_size);
               printf("<span class=\"message\">".$lang['file_mime_type']."</span><br>\n",$uploadfile_type);
               printf("<span class=\"message\">".$lang['file_uploaded']."</span><br>\n",mysqli_insert_id($intranet_db));
            }
            else
            {
               print("<span class=\"message\">File upload failed</span><br>\n");
            }
         }
      }
   }
   $sql = "SELECT fileid,filename,size,mimetype,datestamp FROM files WHERE folder = $folder ORDER BY filename";
   $result = @ mysqli_query($intranet_db,$sql);
   showerror();
   if(@ mysqli_num_rows($result) != 0)
   {
      print("<table>\n");
      print("<tr>");
      print("<th class=\"list\">".$lang['filename']."</th>");
      print("<th class=\"list\">".$lang['date']."</th>");
      print("<th class=\"list\">".$lang['size']."</th>");
      print("<th class=\"list\">&nbsp;</th>\n");
      print("<th class=\"list\">&nbsp;</th>\n");
      print("<th class=\"list\">&nbsp;</th>\n");
      print("</tr>");
      while($row = @ mysqli_fetch_array($result,MYSQLI_ASSOC))
      {
         $sql = "SELECT COUNT(*) FROM filesecurity WHERE fileid=".$row["fileid"];
         $sub_result = @ mysqli_query($intranet_db,$sql);
         $securefile = TRUE; // This must be true
         $row = mysqli_fetch_array($sub_result,MYSQLI_NUM);
         if($row[0] > 0)
         { // This file has one or more security records
            $sql = "SELECT teamid FROM filesecurity WHERE fileid=".$row["fileid"];
            $sub_result = @ mysqli_query($intranet_db,$sql);
            while($srow = @ mysqli_fetch_array($sub_result,MYSQLI_ASSOC))
            { // Check to see if our team is on the list
               if(!empty($userteam))
                  foreach($userteam as $teamtest)
                     if($srow["teamid"]==$teamtest)
                        $securefile = FALSE;
            }
         }
         else // There is no access list, there is no restriction.
            $securefile = FALSE;
         print("<tr>");
         print("<td class=\"list\">".$row["filename"]."</td>");
         print("<td class=\"list\">".date($lang['date_format'],$row["datestamp"])."</td>");
         if($securefile)
            print("<td class=\"list\" colspan=\"3\">(".$row["size"]." ".$lang['bytes'].")</td>");
         else
         {
            print("<td class=\"list\">(".$row["size"]." ".$lang['bytes'].")</td>");
            print("<td class=\"list_center\"><a href=\"fetchfile.php?fileid=".$row["fileid"]."&mimetype=*/*\">".$lang['download']."</a></td>\n");
            print("<td class=\"list_center\"><a href=\"fetchfile.php?fileid=".$row["fileid"]."\" target=\"_blank\">".$lang['open_file']."</a></td>\n");
         }
         print("<td class=\"list_center\"><a href=\"$PHP_SELF?fileid=".$row["fileid"]."\">".$lang['details']."</a></td>\n");
         print("</tr>");
      }
      print("</table>");
   }
   else
   {
      if($filesadmin and !$children and $showedit)
      {
         print("<form method=\"post\" id=\"delfolder\" action=\"$PHP_SELF\">\n");
         print("<input type=\"hidden\" name=\"folder\" value=\"$folder\">");
         print("<input class=\"button\" type=\"submit\" name=\"delfolder\" value=\"".$lang['delete_empty_folder']."\"><br>");
         print("</form>");
      }
      else
         print("Folder is empty.<br>\n");
   }
   if($filesadmin)
   { // File admins can upload new files.
      // Create upload form
      print("<form enctype=\"multipart/form-data\" action=\"$PHP_SELF?folder=$folder\" method=\"post\">\n");
      print("<input type=\"hidden\" name=\"MAX_FILE_SIZE\" value=\"20000000\">\n");
      print($lang['upload_a_file'].": <input name=\"uploadfile\" type=\"file\"><br>\n");
      print($lang['enter_keywords'].":<br>\n");
      print("<textarea name=\"synopsis\" rows=\"10\" cols=\"60\"></textarea><br>\n");
      print("<input class=\"button\" type=\"submit\" value=\"".$lang['upload_file']."\">\n");
      print("</form>\n");
   }
}

// Put some shortcut fields in, so that users can go directly
// to a given file or folder by its unique record ID
print("<table>");
print("<tr><td class=\"centered\">");
print("<form method=\"get\" id=\"filezoom\" action=\"$PHP_SELF\">\n");
print("<i>".$lang['zoom_folder'].":</i> <input name=\"folder\" type=\"text\" size=\"5\" value=\"$folder\">");
print("<input class=\"button\" type=\"submit\" name=\"zoom\" value=\"".$lang['zoom']."\"></form>\n");
print("</td><td class=\"centered\">");
print("<form method=\"get\" id=\"filezoom\" action=\"$PHP_SELF\">\n");
print("<i>".$lang['zoom_file'].":</i> <input name=\"fileid\" type=\"text\" size=\"5\" value=\"$fileid\">");
print("<input class=\"button\" type=\"submit\" name=\"zoom\" value=\"".$lang['zoom']."\"></form>\n");
print("</td></tr></table>");
?>
