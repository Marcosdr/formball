<?php
?>

<div id="game-wrapper">
  <div id="game">
    <div class="elements">
      <?php
      for ($i=0; $i<9; $i++) {
        for($j=0; $j<5; $j++) {
          $row = $i + 1;
          $column = $j + 1;
          $player_position = "player_A_{$row}_{$column}";
          if($i % 2 == 1 && $j == 4) break;
          if($form[$player_position]) {
            print render($form[$player_position]);
          } else print ('Missing Player position');
        }
      }
      ?>
    </div>
  </div>
</div>
