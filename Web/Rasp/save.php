<?php
if (isset($_POST["data"])) {

	$file = "lastest.log";
	$fp = fopen($file,"w");
	$unique = (string)rand();
	$record = $_POST["data"].$unique;
	fwrite($fp,$record);
	fclose($fp);
	
	if (!file_exists("data/")) {
		mkdir("data/");
		chmod("data/",0775);
	}
	$content = file_get_contents($_FILES["file"]["tmp_name"]);
	file_put_contents("data/data_$unique.wav",$content);
	chmod("data/data.wav",0775);
	echo "Data received.\n";
} else {
	echo "Hello";
}
?>
