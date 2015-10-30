<?php

class Ball {

  // The current ball position. Ex: ball_row_1_col_2
  private $position;

  // The trayectory the ball is heading to
  private $trayectory;

  // The distance the ball is travelling for
  private $distance;

  // Properties to position the ball radios on the field, for markup.
  private $name;
  public $pos_x;
  public $pos_y;

  public function __construct($row, $column, $posX, $posY) {
    $this->name = 'ball_' . $row . '_' . $column;
    $this->pos_x = $posX;
    $this->pos_y = $posY;
  }

  /**
   * calculate the new position the ball will have in the next page load
   * and set the trayectory and distance data
   */
  public function calculate_new_position() {

  }

  /**
   * @param string $position
   */
  public function setPosition($position) {
    $this->position = $position;
  }

  /**
   * @param array $trayectory
   */
  public function setTrayectory($trayectory) {
    $this->trayectory = $trayectory;
  }

  /**
   * @param int $distance
   */
  public function setDistance($distance) {
    $this->distance = $distance;
  }

  /**
   * @return string
   */
  public function getPosition() {
    return $this->position;
  }

  /**
   * @return array of x and y value trayectory
   */
  public function getTrayectory() {
    return $this->trayectory;
  }

  /**
   * @return int number of distance
   */
  public function getDistance() {
    return $this->distance;
  }

  /**
   * @return string
   */
  public function getName() {
    return $this->name;
  }


}