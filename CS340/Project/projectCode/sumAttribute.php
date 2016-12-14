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
			<td>Fandom People</td>
		</tr>
		<tr>
			<!--trim white space, use user selected attributes/table columns to determine what table headers should be-->
			<td><?php echo trim($_POST['StoryAttribute']);?></td>
			<td><?php echo trim($_POST['CharacterAttribute']);?></td>
			<td>Count</td>

		</tr>	
<?php
	//trim white space off, blank user input text fields input white space instead of NULL--can affect comparisons
	$characterAttribute=trim($_POST['CharacterAttribute']);
	$storyAttribute=trim($_POST['StoryAttribute']);
	//if characterAttribute and story attribute are both selected to be origin story, tell user that's not allowed
	if($characterAttribute === $storyAttribute)
	{
		echo "Error: Cannot Use Origin Story for Both Story And Character Attributes\n";
	}
	//if genre and archetype selected for search, list number of each archetype in that genre
	else if(strcmp($storyAttribute,"Genre") == 0 && strcmp($characterAttribute,"Character Archetype") == 0)
	{
		if(!($stmt = $mysqli->prepare("SELECT Genre.Type, ArchetypeCounts.Type,ArchetypeCounts.Counts FROM Genre
			INNER JOIN Story ON Story.GenreID=Genre.ID
			INNER JOIN (SELECT CharacterArchetype.Type, COUNT(CharacterData.ID)AS `Counts`, CharacterData.StoryID FROM CharacterArchetype
			INNER JOIN CharacterIs ON CharacterIs.ArchetypeID=CharacterArchetype.ID
			INNER JOIN CharacterData ON CharacterData.ID=CharacterIs.CharacterID
			GROUP BY CharacterArchetype.Type) AS ArchetypeCounts ON ArchetypeCounts.StoryID=Story.ID
			ORDER BY Genre.Type Asc;
		"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($genre, $archetype , $count)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $genre . "\n</td>\n<td>\n" . $archetype . "\n</td>\n<td>\n" . $count . "\n</td>\n<td>\n";
		}
		$stmt->close();
	}
	//if genre and number of characters selected for search, list number of characters in that genre
	else if(strcmp($storyAttribute,"Genre") == 0 && strcmp($characterAttribute,"Number of Characters") == 0)
	{
		if(!($stmt = $mysqli->prepare("SELECT Genre.Type,COUNT(CharacterData.ID) FROM CharacterData
			INNER JOIN Story ON CharacterData.StoryID=Story.ID
			INNER JOIN Genre ON Genre.ID=Story.GenreID
			GROUP BY Genre.Type;
		"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($genre, $count)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $genre . "\n</td>\n<td>\n" . $count . "\n</td>\n<td>\n";
		}
		$stmt->close();
	}
	//if genre and origin story selected for search, list number of each origin story in that genre
	else if(strcmp($storyAttribute,"Genre") == 0 && strcmp($characterAttribute,"Origin Story") == 0)
	{
		if(!($stmt = $mysqli->prepare("SELECT Genre.Type, OriginStoryCounts.Type,OriginStoryCounts.Counts FROM Genre
			INNER JOIN Story ON Story.GenreID=Genre.ID
			INNER JOIN (SELECT OriginStory.Type, COUNT(CharacterData.ID)AS `Counts`, CharacterData.StoryID FROM OriginStory
			INNER JOIN CharacterData ON CharacterData.OriginStoryID=OriginStory.ID
			GROUP BY OriginStory.Type) AS OriginStoryCounts ON OriginStoryCounts.StoryID=Story.ID
			ORDER BY Genre.Type Asc;
		"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($genre, $archetype , $count)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $genre . "\n</td>\n<td>\n" . $archetype . "\n</td>\n<td>\n" . $count . "\n</td>\n<td>\n";
		}
		$stmt->close();
	}
	//if origin story and archetype selected for search, list number of each archetype with that origin story
	else if(strcmp($storyAttribute,"Origin Story") == 0 && strcmp($characterAttribute,"Character Archetype") == 0)
	{
		if(!($stmt = $mysqli->prepare("SELECT OriginStory.Type, ArchetypeCounts.Type,ArchetypeCounts.Counts FROM OriginStory
			INNER JOIN CharacterData ON CharacterData.OriginStoryID=OriginStory.ID
			INNER JOIN (SELECT CharacterArchetype.Type, COUNT(CharacterData.ID)AS `Counts`, CharacterData.ID FROM CharacterArchetype
			INNER JOIN CharacterIs ON CharacterIs.ArchetypeID=CharacterArchetype.ID
			INNER JOIN CharacterData ON CharacterData.ID=CharacterIs.CharacterID
			GROUP BY CharacterArchetype.Type) AS ArchetypeCounts ON ArchetypeCounts.ID=CharacterData.ID
			ORDER BY OriginStory.Type Asc;
		"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($originStory, $archetype, $count)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $originStory . "\n</td>\n<td>\n" . $archetype . "\n</td>\n<td>\n" . $count . "\n</td>\n<td>\n";
		}
		$stmt->close();
	}
	//if origin story and number of characters selected for search, list number of characters with that origin story
	else if(strcmp($storyAttribute,"Origin Story") == 0 && strcmp($characterAttribute,"Number of Characters") == 0)
	{
		if(!($stmt = $mysqli->prepare("SELECT OriginStory.Type,COUNT(CharacterData.ID) FROM CharacterData
			INNER JOIN OriginStory ON CharacterData.OriginStoryID=OriginStory.ID
			GROUP BY OriginStory.Type;
		"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($genre, $count)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $genre . "\n</td>\n<td>\n" . $count . "\n</td>\n<td>\n";
		}
		$stmt->close();
	}
	//if story and archetype selected for search, list number of each archetype in that story
	else if(strcmp($storyAttribute,"Story") == 0 && strcmp($characterAttribute,"Character Archetype") == 0)
	{
		if(!($stmt = $mysqli->prepare("SELECT Story.Title, ArchetypeCounts.Type,ArchetypeCounts.Counts FROM Story
			INNER JOIN CharacterData ON CharacterData.StoryID=Story.ID
			INNER JOIN (SELECT CharacterArchetype.Type, COUNT(CharacterData.ID)AS `Counts`, CharacterData.ID FROM CharacterArchetype
			INNER JOIN CharacterIs ON CharacterIs.ArchetypeID=CharacterArchetype.ID
			INNER JOIN CharacterData ON CharacterData.ID=CharacterIs.CharacterID
			GROUP BY CharacterArchetype.Type) AS ArchetypeCounts ON ArchetypeCounts.ID=CharacterData.ID
			ORDER BY Story.Title Asc;
		"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($story, $archetype, $count)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $story . "\n</td>\n<td>\n" . $archetype . "\n</td>\n<td>\n" . $count . "\n</td>\n<td>\n";
		}
		$stmt->close();
	}
	//if story and number of characters selected for search, list number of characters in that story
	else if(strcmp($storyAttribute,"Story") == 0 && strcmp($characterAttribute,"Number of Characters") == 0)
	{
		if(!($stmt = $mysqli->prepare("SELECT Story.Title,COUNT(CharacterData.ID) FROM CharacterData
			INNER JOIN Story ON CharacterData.StoryID=Story.ID
			GROUP BY Story.Title;
		"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($story, $count)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $story . "\n</td>\n<td>\n" . $count . "\n</td>\n<td>\n";
		}
		$stmt->close();
	}
	//if story and origin story selected for search, list number of characters who possess each origin story in that story
	else if(strcmp($storyAttribute,"Story") == 0 && strcmp($characterAttribute,"Origin Story") == 0)
	{
		if(!($stmt = $mysqli->prepare("SELECT Story.Title, OriginStoryCounts.Type,OriginStoryCounts.Counts FROM Story
			INNER JOIN (SELECT OriginStory.Type, COUNT(CharacterData.ID)AS `Counts`, CharacterData.StoryID FROM OriginStory
			INNER JOIN CharacterData ON CharacterData.OriginStoryID=OriginStory.ID
			GROUP BY OriginStory.Type) AS OriginStoryCounts ON OriginStoryCounts.StoryID=Story.ID
			ORDER BY Story.Title Asc;
		"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($story, $originStory , $count)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $story . "\n</td>\n<td>\n" . $originStory . "\n</td>\n<td>\n" . $count . "\n</td>\n<td>\n";
		}
		$stmt->close();
	}
	else
	{
		echo "Unkown error";
	}
?>
	</table>
</div>
<!--back button to return to main project page and refresh data-->
<div>
	<form method="post" action="project.php">
		<input type="submit" value="Go Back" />
	</form>
</div>