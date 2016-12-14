<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","wolfordj-db","jC39X2rJKFt9prbp","wolfordj-db");

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<body>
<div>
	<table>
		<tr>
			<td>Battlestar People</td>
		</tr>
		<tr>
			<td>Name</td>
			<td>Age</td>
			<td>Homeworld</td>
		</tr>
<?php
if(!($stmt = $mysqli->prepare("SELECT bsg_people.fname, bsg_people.age, bsg_planets.name FROM bsg_people INNER JOIN bsg_planets ON bsg_people.homeworld = bsg_planets.id WHERE bsg_planets.id = ?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!($stmt->bind_param("i",$_POST['Homeworld']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($name, $age, $homeworld)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $name . "\n</td>\n<td>\n" . $age . "\n</td>\n<td>\n" . $homeworld . "\n</td>\n</tr>";
}
$stmt->close();
?>
	</table>
</div>

</body>
</html>