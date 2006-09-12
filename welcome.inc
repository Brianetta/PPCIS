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

// This file should be included in any module which is called by index.php or
// auth.php as the default module.  Its only purpose is to let the user know
// the result of their login or logout attempt.  It can be require()ed at
// any point of the file where the text will be visible.

if(isset($auth))
{
   if($auth=="in")
   {
      if($userid>0)
      {
         printf("<span class=\"message\">".$lang['welcome_successful_login']."</span><br>\n",$firstname);
      }
      else
      {
         print("<span class=\"message\">".$lang['username_password_incorrect']."</span><br>\n");
      }
   }
   else
   {
      print("<span class=\"message\">".$lang['you_logged_out']."</span><br>\n");
   }
}
?>
