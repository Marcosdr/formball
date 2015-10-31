<?php

require_once(drupal_get_path('module', 'formball_game') . '/game/gameElements/Box.php');
require_once(drupal_get_path('module', 'formball_game') . '/game/gameElements/Ball.php');

class Field {

  private $num_rows = 9;
  private $num_cols = 9;
  private $boxes = array();
  private $balls= array();

  // Positions for boxes and balls
  private $column_pos = 12.5;
  private $row_pos = 12.5;
  private $offset_player_B = 6;
  private $offset_ball_pos = 4;

  public function __construct() {
    $this->createField();
  }

  private function createField() {

    // Set the player boxes
    $players = array('A', 'B');
    foreach ($players as $player_type) {
      for ($i = 0; $i < $this->num_rows; $i++) {
        for ($j = 0; $j < $this->num_cols; $j++) {
          $row = $i + 1;
          $column = $j + 1;
          if($player_type == 'A') $pos_x = $j * $this->column_pos; /* $column * 30 */
          if($player_type == 'B') $pos_x = $j * $this->column_pos + $this->offset_player_B;
          $pos_y = $i * $this->row_pos;
          $this->boxes[$player_type . '_' . $row . '_' . $column] = new Box($player_type, $row, $column, $pos_x, $pos_y);
        }
      }
    }

    // Set the field ball radios
    for ($i=0; $i<$this->num_rows; $i++) {
      for ($j = 0; $j < $this->num_cols; $j++) {
        $row = $i + 1;
        $column = $j + 1;
        $pos_x = $j * $this->column_pos + $this->offset_ball_pos;
        $pos_y = $i * $this->row_pos + 1; // 1 centers the ball vertically
        $this->balls[$row . '_' . $column] = new Ball($row, $column, $pos_x, $pos_y);
      }
    }
  }

  public function get_box_by_coords($row, $col) {
    $key = $row . '_' . $col;
    return $this->boxes[$key];
  }

  /**
   * @return mixed
   */
  public function getBoxes() {
    return $this->boxes;
  }

  /**
   * @return mixed
   */
  public function getBalls() {
    return $this->balls;
  }


}