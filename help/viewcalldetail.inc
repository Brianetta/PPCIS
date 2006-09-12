<h1>Call manager - call detail</h1>

This page shows you the details of the helpdesk call.  The unique
call number is at the top of the screen, followed by details of
the call's owner, its priority, the date it was logged, its
category and its location.  Beneath this is the original text
that was entered at the time that the call was logged.<br>
<br>
Clicking the link next to the owner's name will take you to the
owner's entry in the user directory.  This is useful for getting
the contact details of the call's owner.<br>
<br>
Next follows a list of the helpdesk staff who have been assigned
to this call, if any.  Then comes the history - any extra information
that has been added, the name of the person who added it, and the
date and time at which they added it.  This is in date order, with
the most recent entry coming at the <?
if($backwards_history)
   print("top");
else
   print("bottom");
?>.
