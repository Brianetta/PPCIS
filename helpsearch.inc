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

// This file allows users to search the library for files according to
// various criteria, such as filename, modification time and synopsis.

// If there is a submitted search, do the searching and display the results.

if ($searching=="yes")
{
   require("helpsearchresults.inc");
}

// File search form
print("<table>\n");
print("<form method=\"post\" id=\"usermod\" action=\"$PHP_SELF?callmodule=".rawurlencode($callmodule)."\">\n");
print("<input type=\"hidden\" name=\"searching\" value=\"yes\">");
print("<tr>");
print("<th colspan=\"2\"><h2>");
print($lang['helpdesk_search']);
print("</h2></th>");
print("</tr>\n");
print("<tr>\n");
print("<td class=\"right\">".$lang['description'].' / '.$lang['history'].":</td>");
print("<td><input type=\"text\" size=\"30\" name=\"s_terms\" value=\"$s_terms\"></td>");
print("</tr>\n");
print("<tr>\n");
print("<td class=\"centered\" colspan=\"2\"><input name=\"s_submit\" class=\"button\" type=\"submit\" value=\"".$lang['search']."\"></td>");
print("</tr>\n");
print("</form>\n");
print("</table>\n");

$help_keyword="filesearch";
?>
