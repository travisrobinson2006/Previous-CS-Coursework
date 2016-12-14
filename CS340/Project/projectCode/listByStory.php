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
	<!--Create table for character listing-->
<head>
	<link rel="stylesheet" href="style.css">
</head>
<body>
<div>
	<table>
		<tr>
			<td>Fandom People</td>
		</tr>
		<tr>
			<td>Name</td>
			<td>Archetype</td>
			<td>Origin Story</td>
			<td>Story</td>

		</tr>
		<?php
		//SELECT for character name, archetype, origin story and story title, based on user input story
		if(!($stmt = $mysqli->prepare("SELECT CharacterData.FirstName, CharacterData.LastName, CharacterArchetype.Type, OriginStory.Type, Story.Title
			FROM CharacterData 
			INNER JOIN OriginStory ON OriginStory.ID = CharacterData.OriginStoryID 
			INNER JOIN Story ON Story.ID = CharacterData.StoryID 
			INNER JOIN CharacterIs ON CharacterIs.CharacterID=CharacterData.ID
			INNER JOIN CharacterArchetype ON CharacterIs.ArchetypeID=CharacterArchetype.ID
			WHERE Story.ID=?
			"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;}
		if(!($stmt->bind_param("i",$_POST['StoryID'])))
		{
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($firstName, $lastName, $archetype, $originStory, $storyTitle)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $firstName . " " . $lastName . "\n</td>\n<td>\n" . $archetype . "\n</td>\n<td>\n" . $originStory . "\n</td>\n<td>\n" . $storyTitle . "\n</td>\n</tr>";
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