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
	<table>
		<tr>
			<td>Fandom People</td>
		</tr>
		<tr>
			<td>Name</td>
			<td>Origin Story</td>
			<td>Story</td>

		</tr>
<?php
if(!($stmt = $mysqli->prepare("SELECT CharacterData.FirstName, CharacterData.LastName, OriginStory.Type, Story.Title FROM CharacterData INNER JOIN OriginStory ON OriginStory.ID = CharacterData.OriginStoryID INNER JOIN Story ON Story.ID = CharacterData.StoryID"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($firstName, $lastName, $originStory, $storyTitle)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $firstName . " " . $lastName . "\n</td>\n<td>\n" . $originStory . "\n</td>\n<td>\n" . $storyTitle . "\n</td>\n</tr>";
}
$stmt->close();
?>
	</table>
</div>

<div>
	<div class="form">
		<form method="post" action="sumAttribute.php">
			<fieldset class="internalColor">
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

<div>
	<fieldset>
		<legend>Database Filters</legend>
			
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
	
			<div class="form">
				<form method="post" action="createNewOriginStory.php">
					<fieldset class="internalColor">
						<legend>Create New Origin Story</legend>
						<p> Origin Type: <input type="text" name="Type"/></p>
					</fieldset>
					<input type="submit" value="Create" />
				</form>
			</div>

			<div class="form">
				<form method="post" action="createNewArchetype.php">
					<fieldset class="internalColor">
						<legend>Create New Archetype</legend>
						<p> Genre Type: <input type="text" name="Type"/></p>
					</fieldset>
					<input type="submit" value="Create" />
				</form>
			</div>

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

			<div class="form">
				<form method="post" action="addArchetypeExisting.php">
					<fieldset class="internalColor">
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

			<div class="form">
				<form method="post" action="deleteCharacter.php">
					<fieldset class="internalColor">
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