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

require("head.inc");

function parent_recurse($tfolder)
{ // Crawl up the directory tree to list the ancestors.
	global $fix;
   global $lang;
   global $intranet_db;
	global $circle_path;
	global $no_check_again;
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
				if(isset($circle_path[$row["folderid"]]))
				{
					print("<span class=\"message\">Folder $tfolder is linked to itself through ". (string)(sizeof($circle_path)-1) ." other folders");
					foreach($circle_path as $key => $value)
					{
						$no_check_again[$key] = 1;
						if($key != $tfolder)
							print(" - $key");
					}
					print("</span><br>");
					if($fix=='yes')
					{
						$sql = "UPDATE folders SET parent=0 WHERE folderid=".$row["folderid"];
						$repair = mysqli_query($intranet_db,$sql);
						print("<br>\n(fixing)\n");
					}
					return 1;
				}
				else
				{
					$circle_path[$tfolder]=1;
            	if(parent_recurse($row["parent"]) == 2)
					{
						if(isset($circle_path[$tfolder]))
							unset($circle_path[$tfolder]);
					}
				}
         }
      }
		if(isset($circle_path[$tfolder]))
			unset($circle_path[$tfolder]);
   }
   else
   {
		return(0);
   }
}


print("<h1>Data integrity check</h1>");

print("<h2>Users</h2>");
$sql = "SELECT userflags.userid AS dead_user FROM userflags LEFT JOIN users ON users.userid=userflags.userid WHERE users.userid IS NULL";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found rights for non-existent user ".$row["dead_user"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "DELETE FROM userflags WHERE userid=".$row["dead_user"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No unattached rights found.<br>");
}

$sql = "SELECT userdirectory.userid AS dead_user FROM userdirectory LEFT JOIN users ON users.userid=userdirectory.userid WHERE users.userid IS NULL";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found directory entry for non-existent user ".$row["dead_user"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "DELETE FROM userdirectory WHERE userid=".$row["dead_user"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No unattached directory entries found.<br>");
}

$sql = "SELECT preferences.userid AS dead_user FROM preferences LEFT JOIN users ON users.userid=preferences.userid WHERE users.userid IS NULL";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found preferences for non-existent user ".$row["dead_user"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "DELETE FROM preferences WHERE userid=".$row["dead_user"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No unattached preferences found.<br>");
}

$sql = "SELECT userteams.userid AS dead_user,team FROM userteams LEFT JOIN users ON users.userid=userteams.userid WHERE users.userid IS NULL";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found team ".$row["team"]." for non-existent user ".$row["dead_user"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "DELETE FROM userteams WHERE userid=".$row["dead_user"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No unattached team memberships (missing user) found.<br>");
}

$sql = "SELECT userid,team FROM userteams LEFT JOIN teams ON teamid=team WHERE teamid IS NULL";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found non-existent team ".$row["team"]." for user ".$row["userid"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "DELETE FROM userteams WHERE team=".$row["team"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No unattached team memberships (missing team) found.<br>");
}

print("<h2>Files</h2>");
$sql = "SELECT filesecurity.fileid AS dead_file FROM filesecurity LEFT JOIN files ON files.fileid=filesecurity.fileid WHERE files.fileid IS NULL";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found secure team list for non-existent file ".$row["dead_file"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "DELETE FROM filesecurity WHERE fileid=".$row["dead_file"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No unattached secure lists (missing file) found.<br>");
}

$sql = "SELECT filesecurity.teamid AS dead_team FROM filesecurity LEFT JOIN teams ON teams.teamid=filesecurity.teamid WHERE teams.teamid IS NULL";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found secure team list for non-existent team ".$row["dead_team"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "DELETE FROM filesecurity WHERE teamid=".$row["dead_team"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No unattached secure lists (missing team) found.<br>");
}

$sql = "SELECT fileid AS orphan,folder AS dead_folder FROM files LEFT JOIN folders ON folderid=folder WHERE folderid IS NULL AND folder != 0";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found file ".$row["orphan"]." in non-existent folder ".$row["dead_folder"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "UPDATE files SET folder=0 WHERE fileid=".$row["orphan"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No orphaned files found.<br>");
}

$sql = "SELECT folders.folderid AS orphan,folders.parent AS dead_folder FROM folders LEFT JOIN folders AS parents ON folders.parent=parents.folderid WHERE parents.folderid IS NULL AND folders.parent != 0";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found folder ".$row["orphan"]." in non-existent folder ".$row["dead_folder"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "UPDATE folders SET parent=0 WHERE folderid=".$row["orphan"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}

$sql = "SELECT folderid FROM folders";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		if(
			(!isset($circle_path[$row["folderid"]]))
			AND
			(!isset($no_check_again[$row["folderid"]]))
		)
			parent_recurse($row["folderid"]);
	}
}
else
{
	print("No folders found.<br>");
}

print("<h2>Helpdesk</h2>");
$sql = "SELECT historyid,history.callid AS callid FROM history LEFT JOIN helpdesk ON history.callid=helpdesk.callid WHERE helpdesk.callid IS NULL";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
   while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found unattached history event ".$row["historyid"]." for non-existent call ".$row["callid"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "DELETE FROM history WHERE historyid=".$row["historyid"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No unattached history events found.<br>");
}

$sql = "SELECT callid,assignees.userid AS dead_user  FROM assignees LEFT JOIN users ON users.userid=assignees.userid WHERE users.userid IS NULL";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found non-existent user ".$row["dead_user"]." assigned to call ".$row["callid"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "DELETE FROM assignees WHERE userid=".$row["dead_user"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No unattached history events (missing user) found.<br>");
}

$sql = "SELECT assignees.callid AS dead_call,userid FROM assignees LEFT JOIN helpdesk ON helpdesk.callid=assignees.callid WHERE helpdesk.callid IS NULL";
$result = mysqli_query($intranet_db,$sql);
if(mysqli_num_rows($result)>0)
{
	while($row = mysqli_fetch_array($result,MYSQLI_ASSOC))
	{
		print("<span class=\"message\">Found user ".$row["userid"]." assigned to non-existant call ".$row["dead_call"]."</span><br>");
		if($fix=='yes')
		{
			$sql = "DELETE FROM assignees WHERE callid=".$row["dead_call"];
			$repair = mysqli_query($intranet_db,$sql);
			print("<br>\n(fixing)\n");
		}
	}
}
else
{
	print("No unattached history events (missing call) found.<br>");
}

print("<br><br><a href=\"$PHP_SELF?fix=yes\">Click here to fix these errors</a>");

require("tail.inc");
?>
