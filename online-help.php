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

// Simple help system - a keyword is set on each page, and the help button
// calls this script, which includes a file based on the keyword from the
// help directory.  The included files can be plain HTML or can contain
// PHP.

require("head.inc");
print("<h2>".$lang['online_help_system']."</h2>\n");
print("<a href=\"$HTTP_REFERER\">".$lang['click_to_return']."</a><br>\n");
require("help/$help_keyword.inc");
$help_keyword="help_system";
require("tail.inc");
?>
