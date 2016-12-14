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
	<!--Create table for character listing-->
	<table>
		<tr>
			<td>Fandom Universe</td>
		</tr>
		<tr>
			<td>Genre Type</td>
			<td>Story Title</td>


		</tr>
<?php
	//SELECT for Genre and Story Title, to retrieve the name of each story in that genre
	if(!($stmt = $mysqli->prepare("SELECT Genre.Type, Story.Title
		FROM Genre 
		INNER JOIN Story ON Story.GenreID = Genre.ID 
		WHERE Genre.ID=?
		"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;}
	if(!($stmt->bind_param("i",$_POST['GenreID'])))
	{
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	if(!$stmt->bind_result($genreType, $storyTitle)){
		echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	while($stmt->fetch()){
		echo "<tr>\n<td>\n" . $genreType . "\n</td>\n<td>\n" . $storyTitle . "\n</td>\n<td>\n";
	}
	$stmt->close();
?>
	</table>
</div>
<!--back button to return to main project page and refresh data-->
<div>
	<form method="post" action="project.php">
		<input type="submit" value="Go Back" />
	</form>
</div>
