<?php

class Box {
  private $name;
  private $type;
  private $hasPlayer;
  public $pos_x;
  public $pos_y;

  public function __construct($player, $row, $column, $posX, $posY) {
    $this->name = 'player_' . $player . '_' . $row . '_' . $column;
    $this->player = $player;
    $this->hasPlayer = FALSE;
    $this->type = $player;
    $this->pos_x = $posX;
    $this->pos_y = $posY;
  }

  /**
   * @return String
   */
  public function getName() {
    return $this->name;
  }

  /**
   * @return String
   */
  public function is_type() {
    return $this->type;
  }

  /**
   * @return bool
   */
  public function has_player() {
    return $this->hasPlayer;
  }


}