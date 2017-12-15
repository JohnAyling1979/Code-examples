<html>
	<head></head>
	<body style="color:red;background-color:yellow">
		test
		<a href="htmltest.php" target="_blank">count</a>
		<form name="test" id="test" method="post">
			<fieldset>
				<legend>Personal information:</legend>
				Name: <input type="text" size="30" name="name" id="name"><br>
				E-mail: <input type="text" size="30"name="mail" id="mail"><br>
				Date of birth: <input type="date"size="10" name="date" id="date"><br>
				<button type=”submit”>Submit Form</button>
			</fieldset>
		</form>
		
		<?php
			if($_POST)
			{
				print_r($_POST);
				echo "HELLO<br>";
			}
		?>
	</body>
</html>