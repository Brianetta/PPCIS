<?
// Path of PPCIS files from web server root
$siteprefix="/ppcis/";

// Name of web site at top of page
$sitename="Portable PHP/MySQL Corporate Intranet System";

// Optional logo
$sitelogo="ppcis.jpg";

// If logo is set, optional link
$logourl="http://www.ppcis.org/";

// Available stylesheets - paths must be relative to web root
$stylesheets["Default grey"]="ppcis.css";
$stylesheets["Bad demonstration of colours"]="real.css";

// Available languages - english, then a code name
// The code name must match the name of a .inc file in /languages
$lang_available["English"] = "english";
$lang_available["Polska"] = "polish";

// HTML tags allowed in text fields
$allowed_tags="<i><b><span><tt>";

// Default language
$default_lang = 'english';

// Notification email addresses
// News
$news_notify="";
// Helpdesk
$support_notify="";

// Show helpdesk history in reverse order?
$backwards_history=FALSE;

// Skip admin and suthorise all news articles?
$auto_authorise_news=FALSE;

// Absolute path name to Files module directory
// Directory must be read/writable by web server user
$file_store="/mnt/public/intranet/";

// Enable mail notifications?
$use_mail=FALSE;

// Available stylesheets - paths must be relative to web root
$stylesheets["Default grey"]="ppcis.css";
$stylesheets["Bad demonstration of colours"]="real.css";

// Available languages - english, then a code name
// The code name must match the name of a .inc file in /languages
$lang_available["English"] = "english";
$lang_available["US English"] = "american";

// Default language
$default_lang = 'english';

// Use Gravatar?
$gravatar = TRUE;
// Size of Gravatar image
$gravatar_size = 200;

// Hash function used on passwords (should be a valid MySQL function)
// Valid values are password (the old default), md5 and sha1.  sha1
// is recommended, password is not recommended as it can change.
$hash_function = 'sha1';

// Previous hash function - not required unless you're upgrading
// from one password hash function to another.  PPCIS will insert
// the re-hashed password into the user table on successful login.
$old_hash_function = 'password';

// Database settings
// hostname
$db_hostname="localhost";
// database name
$db_name="ppcis";
// database user (must have SELECT, INSERT, UPDATE and DELETE)
$db_username="intranet";
// password for same
$db_password="appdata";

?>
