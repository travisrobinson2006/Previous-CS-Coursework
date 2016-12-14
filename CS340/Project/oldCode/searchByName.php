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
if(empty($_POST['LastName']))
{
	if(!($stmt = $mysqli->prepare("SELECT CharacterData.FirstName, CharacterData.LastName, CharacterArchetype.Type, OriginStory.Type, Story.Title
		FROM CharacterData 
		INNER JOIN OriginStory ON OriginStory.ID = CharacterData.OriginStoryID 
		INNER JOIN Story ON Story.ID = CharacterData.StoryID 
		INNER JOIN CharacterIs ON CharacterIs.CharacterID=CharacterData.ID
		INNER JOIN CharacterArchetype ON CharacterIs.ArchetypeID=CharacterArchetype.ID
		WHERE CharacterData.FirstName = ?"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;}
	if(!($stmt->bind_param("s",$_POST['FirstName'])))
	{
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
}

else if(!empty($_POST['LastName']))
{
	if(!($stmt = $mysqli->prepare("SELECT CharacterData.FirstName, CharacterData.LastName, CharacterArchetype.Type, OriginStory.Type, Story.Title
		FROM CharacterData 
		INNER JOIN OriginStory ON OriginStory.ID = CharacterData.OriginStoryID 
		INNER JOIN Story ON Story.ID = CharacterData.StoryID 
		INNER JOIN CharacterIs ON CharacterIs.CharacterID=CharacterData.ID
		INNER JOIN CharacterArchetype ON CharacterIs.ArchetypeID=CharacterArchetype.ID
		WHERE CharacterData.FirstName = ? AND CharacterData.LastName = ?"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;}
	if(!($stmt->bind_param("ss",$_POST['FirstName'],$_POST['LastName'])))
	{
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
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