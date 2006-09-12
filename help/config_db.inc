<h1>Configuring the database</h1>

In this screen, you must give PPCIS the details of your
MySQL database.  The server should be set to <tt>localhost</tt>
if the MySQL server is running on the same machine as the
web server.<br>
<br>
The database name is the name of the database in which PPCIS
will store its data.  The database user and password must be
created beforehand, and must have at least SELECT, UPDATE,
INSERT and DELETE privileges on that database.<br>
<br>
The password is hidden from casual exposure, but please bear in
mind that it appears in the source in plain text.  The page is
set not to cache, but if you're paranoid about passwords you
might want to clear your browser's cache after using this page.<br>
<br>
To make the changes, click the "Change database details" button.
Changes are made immediately across the entire system.<br>
<?require("settings_save.inc");?>
