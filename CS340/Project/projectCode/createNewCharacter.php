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
	//test if FirstName submission is empty; cannot be NULL, but when nothing is input for user, white space is inserted
	//if empty, inform user of error

	if(empty($_POST['FirstName']))
	{
		echo "Character First Name Cannot Be Empty";
	}
	//else add new user inputed value
	else
	{
		//Create CharacterData entry based on user input
		if(!($stmt = $mysqli->prepare("INSERT INTO CharacterData (FirstName,LastName,StoryID,OriginStoryID) VALUES (?,?,?,?)"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("ssii",$_POST['FirstName'],$_POST['LastName'],$_POST['StoryID'],$_POST['OriginStoryID']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
		}
		//retrieve CharacterData ID from new entry
		$newID = mysqli_insert_id($mysqli);
		
		//using new ID and user selected ArchetypeID, give character archetype, ie create new entry in CharacterIs table
		if(!($stmt = $mysqli->prepare("INSERT INTO CharacterIs (CharacterID,ArchetypeID) VALUES ($newID,?)"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("i",$_POST['ArchetypeID']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
		} else {
			echo "Added " . $stmt->affected_rows . " rows to CharacterData.";
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