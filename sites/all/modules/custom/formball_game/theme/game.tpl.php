<?php
  //kpr($form['player_A_1_1']);
?>

<div id="game-wrapper">
  <div id="game-board">
    <div id="game-elements">
      <?php
      /* create array for players checkboxes */
      $players = array('A', 'B');

      /* variables that control checkbox positions*/
      $column_pos = 25;
      $row_pos = 12.5;
      $offset_pair_row = 12.5;
      $offset_player_B = 8;

      foreach ($players as $player) {
        for ($i = 0; $i < 9; $i++) {
          for ($j = 0; $j < 5; $j++) {
            $row = $i + 1;
            $column = $j + 1;
            $player_position = "player_{$player}_{$row}_{$column}";

            if ($i % 2 == 1) {
              if($player == 'A') $pos_offset = $j * $column_pos + $offset_pair_row; /* $column * 30 + 15 */
              if($player == 'B') $pos_offset = $j * $column_pos + $offset_pair_row + $offset_player_B;
              if ($j == 4) break;
            }

            else {
              if($player == 'A') $pos_offset = $j * $column_pos; /* $column * 30 */
              if($player == 'B') $pos_offset = $j * $column_pos + $offset_player_B;
            }

            if ($form[$player_position]) {
              print '
                <div class="' . $player_position .'" style="
                  position: absolute;
                  top: ' . $i * $row_pos . '%;
                  left: '. $pos_offset . '%;">' .
                    '<input id="' . $form[$player_position]['#id'] .
                    '" class="' . implode(" ", $form[$player_position]['#attributes']['class']) .
                    '" type="' . $form[$player_position]['#type'] .
                    '" value="' . $form[$player_position]['#value'] .
                    '" name="' . $form[$player_position]['#name'] .
                    '"></input>' .
                    '<label for="' . $form[$player_position]['#id'] . '"></label>' .
                '</div>';

              //print render($form[$player_position]);
            }
            else {
              print ('Missing Player position');
            }
          }
        }
      }
      ?>
    </div>
  </div>
</div>
