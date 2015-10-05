<?php

require_once(drupal_get_path('module', 'formball_game') . '/game/gameElements/GameUser.php');
require_once(drupal_get_path('module', 'formball_game') . '/game/gameElements/GameOpponent.php');
require_once(drupal_get_path('module', 'formball_game') . '/game/gameElements/Field.php');

class GameWorld {

  protected $session_id;
  protected $game_user;
  protected $game_opponent;
  protected $field;

  public function __construct() {
    $this->session_id = session_id();
    $this->game_user = new GameUser($this->session_id);
    $this->game_opponent = new GameOpponent($this->game_user);
    $this->field = new Field();
  }

  /**
   * @return \Field
   */
  public function getField() {
    return $this->field;
  }


}