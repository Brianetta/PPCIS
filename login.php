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

// Not totally necessary, this script, but can be included as a module
// if the main banner area is modified and does not have a login form.

require("head.inc");

?>
<h2><?=$lang['enter_username_password']?>:</h2>
<form target="" method="post" name="framelogin" action="auth.php">
<table>
<tr>
<td>
<b><?=$lang['username']?>:</b>
</td>
<td>
<input type="text" name="form_user" value="" class="textfield">
</td>
</tr>
<tr>
<td>
<b><?=$lang['password']?>:</b>
</td>
<td>
<input type="password" name="form_pass" value="" class="textfield">
</td>
</tr>
<tr>
<td colspan="2"><INPUT value="<?=$lang['login']?>" class="button" type="submit"></button></td>
</tr>
</table>
</form>
<?
require("tail.inc");
?>
