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

// This settings file is for loading in extra module pages to the system.
// This is an associative array.  The index (in square brackets) is a string
// that will appear on the menu.  The content (after the equals) is the url
// to be loaded by selecting that item on the menu.
//
// A module can be any PHP file that includes head.inc at the start and
// tail.inc at the end.  You could specify any URL instead of a file name,
// and then the menu item would simply act as a link to that URL.

// $module[$lang['login']]="login.php";
// $module[$lang['change_password']]="password.php";
$module[$lang['news']]="news.php";
$module[$lang['directory']]="directory.php";
$module[$lang['helpdesk']]="helpdesk.php";
$module[$lang['admin']]="admin.php";
$module[$lang['files']]="files.php";
$module[$lang['online_help']]="online-help.php";
// $module[$lang['license']]="license.php";

?>
