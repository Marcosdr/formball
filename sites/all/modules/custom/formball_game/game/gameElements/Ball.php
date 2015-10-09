<?php

class Ball {
  private $name;
  private $has_ball;
  public $pos_x;
  public $pos_y;

  public function __construct($row, $column, $posX = 0, $posY = 0) {
    $this->name = 'ball_' . $row . '_' . $column;
    $this->has_ball = FALSE;
    $this->pos_x = $posX;
    $this->pos_y = $posY;
  }

  /**
   * @return string
   */
  public function getName() {
    return $this->name;
  }

  /**
   * @return bool
   */
  public function has_ball() {
    return $this->has_ball;
  }

}