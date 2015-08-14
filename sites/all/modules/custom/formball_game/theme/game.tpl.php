<?php
  print kpr($form["player_A_1_1"]);
?>

<div id="game-wrapper">
  <div class="game" style="position: relative; width:600px; height: 400px; background-color: green;">
    <div class="elements" style="position: absolute;">
      <?php
      for ($i=0; $i<9; $i++) {
        for($j=0; $j<9; $j++) {
          $row = $i + 1;
          $column = $j + 1;
          ?>
          <div class="player_A_<?php print $i ?>_<?php print $j ?>">
          <?php
            //print render($form["player_A_{$i}_{$j}"]);
          ?>
          </div> <?php

        }
      }

      ?>
    </div>
  </div>
</div>
