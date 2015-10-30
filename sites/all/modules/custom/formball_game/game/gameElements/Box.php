<?php

class Box {
  private $name;
  private $coordinate;
  private $type;
  private $hasPlayer;

  // Properties to position the box checkboxes on the field, for markup.
  public $pos_x;
  public $pos_y;

  public function __construct($player_type, $row, $column, $posX, $posY) {
    $this->name = 'box_' . $player_type . '_' . $row . '_' . $column;
    $this->coordinate = array(
      'row' => $row,
      'col' => $column,
    );
    $this->pos_x = $posX;
    $this->pos_y = $posY;
    $this->type = $player_type;
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
   * @param mixed $hasPlayer
   */
  public function setPlayer($hasPlayer) {
    $this->hasPlayer = $hasPlayer;
  }

  /**
   * @return bool
   */
  public function has_player() {
    return $this->hasPlayer;
  }

  /**
   * @return array
   */
  public function getCoordinate() {
    return $this->coordinate;
  }

}