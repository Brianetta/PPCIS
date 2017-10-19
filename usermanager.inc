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

// This file is like a central switch-box, choosing which admin code to include
// based on what variables exist.  This file includes usermanagerflags.inc,
// please check out the comment in that file about security.

if(isset($showuserid))
{
  require("usermanageredit.inc");
}
elseif(isset($showuserflags))
{
  require("usermanagerflags.inc");
}
elseif(isset($showuserpass))
{
  require("usermanagerpass.inc");
}
elseif(isset($deleteuser))
{
  require("deleteuser.inc");
}
elseif(isset($showteams))
{
  require("usermanagerteams.inc");
}
else
{
  require("usermanagerlist.inc");
}
?>
