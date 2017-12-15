<html>
	<header><title>GW2 Dailies</title></header>
	<body>
		<?php
			$data=file_get_contents("https://api.guildwars2.com/v2/achievements/daily");
			$result=json_decode($data);

			echo "<br>LVL 80 PVE dailies<br>";
			foreach($result->pve as $daily)
			{
				$datatwo=file_get_contents("https://api.guildwars2.com/v2/achievements?ids=$daily->id");
				$resulttwo=json_decode($datatwo);
				if($daily->level->max==80)
					echo $resulttwo[0]->name."<br>";
			}
			
			echo "<br>LVL 80 PVP dailies<br>";
			foreach($result->pvp as $daily)
			{
				$datatwo=file_get_contents("https://api.guildwars2.com/v2/achievements?ids=$daily->id");
				$resulttwo=json_decode($datatwo);
				if($daily->level->max==80)
					echo $resulttwo[0]->name."<br>";
			}

			echo "<br>LVL 80 WVW dailies<br>";
			foreach($result->wvw as $daily)
			{
				$datatwo=file_get_contents("https://api.guildwars2.com/v2/achievements?ids=$daily->id");
				$resulttwo=json_decode($datatwo);
				if($daily->level->max==80)
					echo $resulttwo[0]->name."<br>";
			}

			echo "<br>LVL 80 Fractals dailies<br>";
			foreach($result->fractals as $daily)
			{
				$datatwo=file_get_contents("https://api.guildwars2.com/v2/achievements?ids=$daily->id");
				$resulttwo=json_decode($datatwo);
				if($daily->level->max==80)
					echo $resulttwo[0]->name."<br>";
			}

			echo "<br>LVL 80 Special dailies<br>";
			foreach($result->special as $daily)
			{
				$datatwo=file_get_contents("https://api.guildwars2.com/v2/achievements?ids=$daily->id");
				$resulttwo=json_decode($datatwo);
				if($daily->level->max==80)
					echo $resulttwo[0]->name."<br>";
			}
			
		?>
	</body)
</html>