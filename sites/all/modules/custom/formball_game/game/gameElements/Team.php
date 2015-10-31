<?php
require_once(drupal_get_path('module', 'formball_game') . '/game/gameElements/Player.php');

class Team {

  private $name;
  private $players = array();
  private $lineup;
  private $moves;
  private $field;

  public function __construct($team_data, $field = null) {
    $this->field = $field;
    $this->name = $team_data->player;
    $this->set_players($team_data);
    $this->set_team_lineup($team_data);
  }

  private function set_players($team_data) {
    $players_data = unserialize($team_data->players);
    foreach($players_data as $number => $player) {
      $this->players[] = new Player($player, $number);
    }
  }

  private function set_team_lineup($team_data) {
    $this->lineup = $team_data->lineup;
    // debug $this->lineup = '2_2_2';
    $player_positions = array();

    if($this->name === 'A'){
      switch($this->lineup) {
        case '3_2_1':
          $player_positions = array(
            '0' => array(5,1),
            '1' => array(2,3),
            '2' => array(5,2),
            '3' => array(8,3),
            '4' => array(3,4),
            '5' => array(7,4),
            '6' => array(5,5),
          );
          break;
        case '3_1_2':
          $player_positions = array(
            '0' => array(5,1),
            '1' => array(2,3),
            '2' => array(5,2),
            '3' => array(8,3),
            '4' => array(5,4),
            '5' => array(3,5),
            '6' => array(7,5),
          );
          break;
        case '2_3_1':
          $player_positions = array(
            '0' => array(5,1),
            '1' => array(3,2),
            '2' => array(7,2),
            '3' => array(5,3),
            '4' => array(2,4),
            '5' => array(8,4),
            '6' => array(5,5),
          );
          break;
        case '2_2_2':
          $player_positions = array(
            '0' => array(5,1),
            '1' => array(3,2),
            '2' => array(7,2),
            '3' => array(8,4),
            '4' => array(2,4),
            '5' => array(4,5),
            '6' => array(6,5),
          );
          break;
      }
    }
    else if($this->name === 'B'){
      switch($this->lineup) {
        case '3_2_1':
          $player_positions = array(
            '0' => array(5,9),
            '1' => array(2,7),
            '2' => array(5,8),
            '3' => array(8,7),
            '4' => array(3,6),
            '5' => array(7,6),
            '6' => array(5,5),
          );
          break;
        case '3_1_2':
          $player_positions = array(
            '0' => array(5,9),
            '1' => array(2,7),
            '2' => array(5,8),
            '3' => array(8,7),
            '4' => array(5,6),
            '5' => array(3,5),
            '6' => array(7,5),
          );
          break;
        case '2_3_1':
          $player_positions = array(
            '0' => array(5,9),
            '1' => array(3,8),
            '2' => array(7,8),
            '3' => array(5,7),
            '4' => array(2,6),
            '5' => array(8,6),
            '6' => array(5,5),
          );
          break;
        case '2_2_2':
          $player_positions = array(
            '0' => array(5,9),
            '1' => array(3,8),
            '2' => array(7,8),
            '3' => array(8,6),
            '4' => array(2,6),
            '5' => array(4,5),
            '6' => array(6,5),
          );
          break;
      }
    }

    // Set the player coords according to the players positions
    // and the correspondent box to have a player boolean
    foreach($player_positions as $position) {
      $this->players[0]->setCoordinate($position[0], $position[1]);
      $this->field->get_box_by_coords($this->name . '_' . $position[0], $position[1])->setPlayer(true);
    }
  }

  public function update() {

  }

  public function get_player_by_number($player_number) {
    foreach($this->players as $number => $player) {
      if($player_number === $number){
        return $player;
      }
    }
  }

  public function get_player_by_coordinate($player_coords) {
    foreach($this->players as $player) {
      if($player_coords === $player->getCoordinate()){
        return $player;
      }
    }
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

  /**
   * @return mixed
   */
  public function getLineup() {
    return $this->lineup;
  }

  /**
   * @return array
   */
  public function getPlayers() {
    return $this->players;
  }

}