<?php
$filename = 'YOUR_BINARY_FILE';
if (file_exists($filename)) {
  echo filemtime($filename) ;
}
?>
