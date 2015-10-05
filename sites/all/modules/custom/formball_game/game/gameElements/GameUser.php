<?php


class GameUser {

  private $player;
  private $moves;

  public function __construct($session_id) {
    $this->player = search_game('sid', $session_id);
    $player_moves = unserialize($this->player->moves);
    $this->moves = array_pop($player_moves);
  }




  /**
   * @return NULL
   */
  public function getPlayer() {
    return $this->player;
  }

  /**
   * @param NULL $player
   */
  public function setPlayer($player) {
    $this->player = $player;
  }

  /**
   * @return mixed
   */
  public function getMoves() {
    return $this->moves;
  }

  /**
   * @param mixed $moves
   */
  public function setMoves($moves) {
    $this->moves = $moves;
  }




}