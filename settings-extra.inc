
// Available stylesheets - paths must be relative to web root
$stylesheets["Default grey"]="ppcis.css";
$stylesheets["Bad demonstration of colours"]="real.css";

// Available languages - english, then a code name
// The code name must match the name of a .inc file in /languages
$lang_available["English"] = "english";

// Default language
$default_lang = 'english';

// Hash function used on passwords (should be a valid MySQL function)
// Valid values are password (the old default), md5 and sha1.  sha1
// is recommended, password is not recommended as it can change.
$hash_function = 'sha1';

// Previous hash function - not required unless you're upgrading
// from one password hash function to another.  PPCIS will insert
// the re-hashed password into the user table on successful login.
$old_hash_function = 'password';

