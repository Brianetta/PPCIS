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

// This is just enough HTML to close all the tags opened in head.inc, and
// a link to license.php along with the copyright notice displayed at the
// bottom of every page.  According to the GPL, you can make derivative
// works from this intranet system.  If you do, you should alter this notice
// to make it clear that it isn't the version of PPCIS as maintained by the
// original author.  I'd like to be kept credited in the source code as the
// author of the original work on which any derivative is based, if possible.

$_SESSION["userid"]=$userid;
$_SESSION["firstname"]=$firstname;
$_SESSION["lastname"]=$lastname;
$_SESSION["loginhost"]=$loginhost;
$_SESSION["help_keyword"]=$help_keyword;
mysqli_close($intranet_db);

?>
</div>
<span class="copyright"><? printf($lang['_copyright_message'],(string)ppcis_version,(string)ppcis_year); ?></span>
</body>
</html>
