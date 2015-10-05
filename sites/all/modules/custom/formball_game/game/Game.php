<?php

require_once(drupal_get_path('module', 'formball_game') . '/game/GameWorld.php');
require_once(drupal_get_path('module', 'formball_game') . '/game/GameRenderer.php');

class Game {

  // instance variables
  public $world;
  protected $renderer;

  public function __construct() {
    $this->world = new GameWorld();
    $this->renderer = new GameRenderer();
  }





}

