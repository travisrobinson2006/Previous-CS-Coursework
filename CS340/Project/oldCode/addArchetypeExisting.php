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
	//SELECT for CharacterData ID based on user input of name and story, use so we add archetype to correct character
	if(!($stmt = $mysqli->prepare("SELECT CharacterData.ID FROM CharacterData WHERE CharacterData.FirstName=? AND CharacterData.LastName=? AND CharacterData.StoryID=?"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!($stmt->bind_param("ssi",$_POST['FirstName'],$_POST['LastName'],$_POST['StoryID']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->bind_result($characterID)){
		echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	while($stmt->fetch()){
		$charId = $characterID;
	}		
	//Use CharacterData ID from above along with ArchetypeID provided by user to add Archetype to character
	if(!($stmt = $mysqli->prepare("INSERT INTO CharacterIs (CharacterID,ArchetypeID) VALUES (?,?)"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!($stmt->bind_param("ii",$charId,$_POST['ArchetypeID']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	} else {
		echo "Added " . $stmt->affected_rows . " rows to story.";
	}

?>