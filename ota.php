/************************************************************
  @ Module     : ESP32 OTA basic
                 (checking time of the file in server) source.
  @ Language   : PHP
by MD tanvir shakil
************************************************************/


<?php
$filename = 'YOUR_BINARY_FILE';
if (file_exists($filename)) {
  echo filemtime($filename) ;
}
?>
