<!--
Travis Robinson
Chelsea Colvin
CS340
Spring 2016
Project Code
-->
<?php
	//Turn on error reporting
	ini_set('display_errors', 'On');
	//Connects to the database
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","robitrav-db","dMD7JvbzBSr4uyHC","robitrav-db");
	if($mysqli->connect_errno)
	{
		echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<head>
	<link rel="stylesheet" href="style.css">
</head>
<body>
<div>
<?php
	//DELETE characterData based on user input of name and story title
	//if last name provided, delete that character
	if(!empty($_POST['LastName']))
	{
		if(!($stmt = $mysqli->prepare("DELETE FROM CharacterData WHERE CharacterData.FirstName=? AND CharacterData.LastName=? AND CharacterData.StoryID=?"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("ssi",$_POST['FirstName'],$_POST['LastName'],$_POST['StoryID']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
		}
		else
		{
			echo "Removed " . $stmt->affected_rows . " rows from CharacterData.";
		}
	}
	//if last name not provided, delete character with that first name
	else if(empty($_POST['LastName']))
	{
		if(!($stmt = $mysqli->prepare("DELETE FROM CharacterData WHERE CharacterData.FirstName=? AND CharacterData.StoryID=?"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("si",$_POST['FirstName'],$_POST['StoryID']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
		}
		else
		{
			echo "Removed " . $stmt->affected_rows . " rows from CharacterData.";
		}
	}
?>
</div>
<!--back button to return to main project page and refresh data-->
<div>
	<form method="post" action="project.php">
		<input type="submit" value="Go Back" />
	</form>
</div>