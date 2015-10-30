<?php

require_once(drupal_get_path('module', 'formball_game') . '/game/GameWorld.php');
require_once(drupal_get_path('module', 'formball_game') . '/game/GameRenderer.php');

class Game {

  // instance variables
  public $world;
  protected $renderer;

  public function __construct($my_game, $opponent_game) {
    $this->world = new GameWorld($my_game, $opponent_game);
    $this->renderer = new GameRenderer($this->world);
  }

  public function render() {
    $this->world->update();
    $output = $this->renderer->render();
    return $output;
  }

}

