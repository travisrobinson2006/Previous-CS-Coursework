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
	<!--create table to display name, archetpye, origin story and story for every character; characters with multiple archetypes will appear more than once-->
	<table>
		<tr>
			<td>Fandom People</td>
		</tr>
		<tr>
			<td>Name</td>
			<td>Character Archetype</td>
			<td>Origin Story</td>
			<td>Story</td>
		</tr>
<?php
	//SELECT for name, origin, archetype and containing story for each character
	if(!($stmt = $mysqli->prepare("SELECT CharacterData.FirstName, CharacterData.LastName, OriginStory.Type, CharacterArchetype.Type, Story.Title FROM CharacterData 
		INNER JOIN OriginStory ON OriginStory.ID = CharacterData.OriginStoryID 
		INNER JOIN Story ON Story.ID = CharacterData.StoryID 
		INNER JOIN CharacterIs ON CharacterIs.CharacterID=CharacterData.ID
		INNER JOIN CharacterArchetype ON CharacterArchetype.ID=CharacterIs.ArchetypeID"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}

	if(!$stmt->execute()){
		echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	if(!$stmt->bind_result($firstName, $lastName, $archetype,$originStory, $storyTitle)){
		echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	while($stmt->fetch()){
		echo "<tr>\n<td>\n" . $firstName . " " . $lastName . "\n</td>\n<td>\n" . $originStory . "\n</td>\n<td>\n" . $archetype . "\n</td>\n<td>\n" . $storyTitle . "\n</td>\n</tr>";
	}
	$stmt->close();
?>
	</table>
</div>
<!--this section contains needed user input and submission buttons for the aggregate function SELECT queries-->
<!--uses special table to populate drop down menus with column names-->
	<div class="form">
		<form method="post" action="sumAttribute.php">
			<fieldset>
				<legend>List Number of Characters with Shared Character Attributes By Story Attribute</legend>
				<select name="StoryAttribute">
				<?php
					if(!($stmt = $mysqli->prepare("SELECT id, StoryAttribute FROM StoryAttribute"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
	
					if(!$stmt->execute()){
						echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->bind_result($StoryAttribute, $StoryAttribute)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					while($stmt->fetch()){
						echo '<option value=" '. $StoryAttribute . ' "> ' . $StoryAttribute . '</option>\n';
					}
					$stmt->close();
				?>
				</select>
				<select name="CharacterAttribute">
				<?php
					if(!($stmt = $mysqli->prepare("SELECT id, CharacterAttribute FROM CharacterAttribute"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
	
					if(!$stmt->execute()){
						echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->bind_result($CharacterAttribute, $CharacterAttribute)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					while($stmt->fetch()){
						echo '<option value=" '. $CharacterAttribute . ' "> ' . $CharacterAttribute . '</option>\n';
					}
					$stmt->close();
				?>
				</select>						
			</fieldset>
			<input type="submit" value="Generate List" />
		</form>
	</div>			
<!--this section contains needed user input and submission buttons for the searchByName SELECT queries-->
<!--SELECT based on user input first name and last name-->
<div>
	<form method="post" action="searchByName.php">
		<fieldset>
			<legend>Search For Character By Name</legend>
			<p> First Name: <input type="text" name="FirstName"/></p>
			<p> Last Name: <input type="text" name="LastName"/></p>			
		</fieldset>
		<input type="submit" value="Search" />
	</form>
</div>
<!--this section contains needed user input and submission buttons for to filter based on various attributes from the DB tables-->
<div>
	<fieldset>
		<legend>Database Filters</legend>
			<!--lists stories by genre type-->
			<div class="form">
				<form method="post" action="listByGenre.php">
					<fieldset class="internalColor">
						<legend>List Story By Genre</legend>
						<select name="GenreID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, Type FROM Genre"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}
	
							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->bind_result($ID, $GenreID)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							while($stmt->fetch()){
							echo '<option value=" '. $ID . ' "> ' . $GenreID . '</option>\n';
							}
							$stmt->close();
							?>
						</select>
					</fieldset>
					<input type="submit" value="Generate List" />
				</form>
			</div>
			<!--lists characters by story-->			
			<div class="form">
				<form method="post" action="listByStory.php">
					<fieldset class="internalColor">
						<legend>List Character By Story</legend>
						<select name="StoryID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, Title FROM Story"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}
	
							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->bind_result($ID, $StoryID)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							while($stmt->fetch()){
							echo '<option value=" '. $ID . ' "> ' . $StoryID . '</option>\n';
							}
							$stmt->close();
							?>
						</select>
					</fieldset>
					<input type="submit" value="Generate List" />
				</form>
			</div>
			<!--lists characters by archeyptes-->
			<div class="form">
				<form method="post" action="listByArchetype.php">
					<fieldset class="internalColor">
					<legend>List Character By Archetype</legend>
						<select name="ArchetypeID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, Type FROM CharacterArchetype"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}

							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->bind_result($ID, $ArchetypeID)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							while($stmt->fetch()){
							echo '<option value=" '. $ID . ' "> ' . $ArchetypeID . '</option>\n';
							}
							$stmt->close();
							?>
						</select>
					</fieldset>
					<input type="submit" value="Generate List" />
				</form>
			</div>
			<!--lists characters by origin story-->
			<div class="form">
				<form method="post" action="listByOriginStory.php">
					<fieldset class="internalColor">
					<legend>List Character By Origin Story</legend>
						<select name="OriginStoryID">
						<?php
							if(!($stmt = $mysqli->prepare("SELECT id, Type FROM OriginStory"))){
								echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
							}

							if(!$stmt->execute()){
								echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->bind_result($ID, $OriginStoryID)){
								echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							while($stmt->fetch()){
							echo '<option value=" '. $ID . ' "> ' . $OriginStoryID . '</option>\n';
							}
							$stmt->close();
							?>
						</select>
					</fieldset>
					<input type="submit" value="Generate List" />
				</form>
			</div>
	</fieldset>
</div>
<!--this section contains all input fields and drop down menus to add data to all tables-->
<div>
	<fieldset>
		<legend>Create New Data</legend>
			<div class="form">
				<form method="post" action="createNewGenre.php">
					<fieldset class="internalColor">
						<legend>Create New Genre</legend>
						<p> Genre Type: <input type="text" name="Type"/></p>
					</fieldset>
				<input type="submit" value="Create" />
				</form>
			</div>
			<!--add a new story, inputing title and selecting genre-->
			<div class="form">
				<form method="post" action="createNewStory.php">
					<fieldset class="internalColor">
						<legend>Create New Story</legend>
						<p> Story Name: <input type="text" name="Title"/></p>
							<select name="GenreID">
							<?php
								if(!($stmt = $mysqli->prepare("SELECT id, Type FROM Genre"))){
									echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
								}
		
								if(!$stmt->execute()){
									echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
								}
								if(!$stmt->bind_result($ID, $GenreID)){
									echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
								}
								while($stmt->fetch()){
								echo '<option value=" '. $ID . ' "> ' . $GenreID . '</option>\n';
								}
								$stmt->close();
								?>
							</select>
					</fieldset>
					<input type="submit" value="Create" />
				</form>
			</div>
			<!--add a new origin story, inputing type-->
			<div class="form">
				<form method="post" action="createNewOriginStory.php">
					<fieldset class="internalColor">
						<legend>Create New Origin Story</legend>
						<p> Origin Type: <input type="text" name="Type"/></p>
					</fieldset>
					<input type="submit" value="Create" />
				</form>
			</div>
			<!--add a new archetype, inputing type-->
			<div class="form">
				<form method="post" action="createNewArchetype.php">
					<fieldset class="internalColor">
						<legend>Create New Archetype</legend>
						<p> Genre Type: <input type="text" name="Type"/></p>
					</fieldset>
					<input type="submit" value="Create" />
				</form>
			</div>
			<!--add a new character, inputing first and last name (optional) as well as story, origin, and a starting archetype-->
			<div class="form">
				<form method="post" action="createNewCharacter.php">
					<fieldset class="internalColor">
						<legend>Create New Character</legend>
						<p> First Name: <input type="text" name="FirstName"/></p>
						<p> Last Name: <input type="text" name="LastName"/></p>
							<select name="StoryID">
								<?php
									if(!($stmt = $mysqli->prepare("SELECT id, Title FROM Story"))){
										echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
									}
	
									if(!$stmt->execute()){
										echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									if(!$stmt->bind_result($ID, $StoryID)){
										echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									while($stmt->fetch()){
										echo '<option value=" '. $ID . ' "> ' . $StoryID . '</option>\n';
									}
									$stmt->close();
								?>
							</select>
							<select name="OriginStoryID">
								<?php
									if(!($stmt = $mysqli->prepare("SELECT id, Type FROM OriginStory"))){
										echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
									}

									if(!$stmt->execute()){
										echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									if(!$stmt->bind_result($ID, $OriginStoryID)){
										echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									while($stmt->fetch()){
										echo '<option value=" '. $ID . ' "> ' . $OriginStoryID . '</option>\n';
									}
									$stmt->close();
								?>
							</select>
							<select name="ArchetypeID">
								<?php
									if(!($stmt = $mysqli->prepare("SELECT id, Type FROM CharacterArchetype"))){
										echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
									}

									if(!$stmt->execute()){
										echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									if(!$stmt->bind_result($ID, $ArchetypeID)){
										echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									while($stmt->fetch()){
										echo '<option value=" '. $ID . ' "> ' . $ArchetypeID . '</option>\n';
									}
									$stmt->close();
								?>
							</select>
					</fieldset>
					<input type="submit" value="Create" />
				</form>
			</div>

	</fieldset>
</div>
<!--this section adds an archetype to an already existing character; user inputs first and last name, selects the story of the character, and selects the desired archetype-->
<!--characters can have multiple archetypes-->
<div class="form">
	<form method="post" action="addArchetypeExisting.php">
		<fieldset class>
			<legend>Add Archetype to Existing Character</legend>
			<p> First Name: <input type="text" name="FirstName"/></p>
			<p> Last Name: <input type="text" name="LastName"/></p>
				<select name="StoryID">
					<?php
						if(!($stmt = $mysqli->prepare("SELECT id, Title FROM Story"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}
	
						if(!$stmt->execute()){
							echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->bind_result($ID, $StoryID)){
							echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						while($stmt->fetch()){
							echo '<option value=" '. $ID . ' "> ' . $StoryID . '</option>\n';
						}
						$stmt->close();
					?>
				</select>
				<select name="ArchetypeID">
					<?php
						if(!($stmt = $mysqli->prepare("SELECT id, Type FROM CharacterArchetype"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}

						if(!$stmt->execute()){
							echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->bind_result($ID, $ArchetypeID)){
							echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						while($stmt->fetch()){
							echo '<option value=" '. $ID . ' "> ' . $ArchetypeID . '</option>\n';
						}
						$stmt->close();
					?>
				</select>
		</fieldset>
		<input type="submit" value="Add Archetype" />
	</form>
</div>
<!--this section allows the deletion of a character; user inputs character name and their story-->
<div class="form">
	<form method="post" action="deleteCharacter.php">
		<fieldset>
			<legend>Delete Character</legend>
			<p> First Name: <input type="text" name="FirstName"/></p>
			<p> Last Name: <input type="text" name="LastName"/></p>
				<select name="StoryID">
					<?php
						if(!($stmt = $mysqli->prepare("SELECT id, Title FROM Story"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}
	
						if(!$stmt->execute()){
							echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->bind_result($ID, $StoryID)){
							echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						while($stmt->fetch()){
							echo '<option value=" '. $ID . ' "> ' . $StoryID . '</option>\n';
						}
						$stmt->close();
					?>
				</select>
		</fieldset>
		<input type="submit" value="Delete Character" />
	</form>
</div>