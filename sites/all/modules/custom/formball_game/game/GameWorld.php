<?php

require_once(drupal_get_path('module', 'formball_game') . '/game/gameElements/Team.php');
require_once(drupal_get_path('module', 'formball_game') . '/game/gameElements/Field.php');

class GameWorld {

  public $teams;
  protected $field;

  public function __construct($my_game, $opponent_game) {
    $this->field = new Field();
    $this->teams = array(
      'player' => new Team($my_game, $this->field),
      'opponent' => new Team($opponent_game, $this->field),
    );
  }

  // Update the players and field elements accordingly
  public function update() {
    $this->teams['player']->update($this->field);
  }

  /**
   * @return \Field
   */
  public function getField() {
    return $this->field;
  }


}