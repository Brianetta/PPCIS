<h1>General options</h1>

This screen is where you set up all of the miscellaneous options
that PPCIS has to offer.<br>
<br>
The <b>site name</b> is a string that appears in the title bar and at
the top of each page on the system.<br>
<br>
The <b>site logo</b> is the relative path or URL of a graphical image
which will be placed at the top left hand side of each page on
the system.  If the field is left blank, the system will not
attempt to display any image.<br>
<br>
The <b>logo link</b> is a URL which can be linked to by clicking on the
image specified as the site logo.  This option has no effect if
the site logo field is blank.  If this field is left blank, the
logo will not be a hyperlink.<br>
<br>
The <b>file store directory</b> is the local path name of the directory
where the files module keeps the bodies of all the uploaded files.
It is highly recommended that this directory be kept out of the
published web space on the web server, because it must be fully
readable and writeable by the web server.<br>
<br>
If this directory cannot be made available, the files module will not
work.  It is recommended in this case tha the files module should be
disabled.<br>
<br>
To make the changes, click the "Change options" button.  Changes
are made immediately across the entire system.<br>
<?php require("settings_save.inc");?>
