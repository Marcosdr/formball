<?php

class Player {

  private $team;
  private $id;
  private $name;
  private $number;
  private $position;
  private $coordinate = array();
  private $cards = array();
  private $skills = array();
  private $has_ball = false;

  public function __construct($player, $number) {
    $this->number = $number;
    $player_node = node_load($player['id']);
    $this->player_init_values($player_node);
  }

  private function player_init_values($player_node) {
    $player = entity_metadata_wrapper('node', $player_node);
    $this->id = $player->nid->value();
    $this->name = $player->field_player_name->value();
    $this->position = $player->field_player_position->value();
    $this->team = $player->field_player_team->value();

    $this->skills = array(
      'speed' => $player->field_player_speed->value(),
      'offense' => $player->field_player_offense->value(),
      'defense' => $player->field_player_defense->value(),
      'technic' => $player->field_player_technic->value(),
      'kick' => $player->field_player_kick->value(),
    );

    $this->cards = array(
      'yellow' => 0,
      'red' => 0,
    );
  }

  public function get_skill_value($skill) {
    if(property_exists($this, $skill)) {
      return $this->skills[$skill];
    }
    else return null;
  }

  /**
   * Sets the player's skills dynamically during the game
   * @param array $new_skills An array of new skills to be set to the player
   */
  public function set_skills_value($new_skills) {
    foreach($new_skills as $skill => $value) {
      if(property_exists($this, $skill)) {
        $this->$skill = $value;
      }
    }
  }

  public function has_yellow_card() {
    return count($this->cards['yellow'] === 1);
  }

  public function has_red_card() {
    return $this->cards['red'] === 1;
  }

  public function add_yellow_card() {
    $this->cards['yellow']++;
  }

  public function send_off_player() {
    $this->cards['red'] = 1;
  }

  // SETTERS

  /**
   * @param array $coordinate
   */
  public function setCoordinate($x, $y) {
    $this->coordinate = array(
      'row' => $x,
      'col' => $y,
    );
  }

  // GETTERS

  /**
   * @return mixed
   */
  public function getId() {
    return $this->id;
  }

  /**
   * @return mixed
   */
  public function getName() {
    return $this->name;
  }

  /**
   * @return mixed
   */
  public function getPosition() {
    return $this->position;
  }

  /**
   * @return array
   */
  public function getCards() {
    return $this->cards;
  }

  /**
   * @return array
   */
  public function getSkills() {
    return $this->skills;
  }

  /**
   * @return boolean
   */
  public function has_ball() {
    return $this->has_ball;
  }

  /**
   * @return array
   */
  public function getCoordinate() {
    return $this->coordinate;
  }

}