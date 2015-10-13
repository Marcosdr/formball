<?php
/**
 * @file
 * Series of utility functions to ease the process of grabbing data
 * that is often asked for in other files/functions of this module
 */


/**
 * search_game()
 * Searches for a game from the formball_games db
 * given a condition and a value
 *
 * @param string $condition
 * @param bool|TRUE $value
 * @return NULL/mixed
 */

function search_game($condition = '', $value = '') {

  $game = NULL;
  $condition_check = ":$condition";

  // value may be 0 (!=) but condition cannot evaluate to 0 (!==)
  if($condition !== '' && $value != ''){
    $result = db_query_range("
      SELECT * FROM {formball_games}
      WHERE $condition = $condition_check
      ORDER BY timestamp DESC", 0, 1, array($condition_check => $value)
    );

    // Fetch next row as a stdClass object.
    if($result && $result->rowCount() > 0) {
      $game = $result->fetchObject();
    }
  }

  return $game;
}

/**
 * Search for a game field in the DB
 *
 * @param string $field
 * @param string $condition
 * @param string $value
 * @return null
 */
function search_game_field($field = '', $condition = '', $value = '') {
  $result = NULL;
  $game = search_game($condition, $value);
  if($game) {
    $result = $game->$field;
  }
  return $result;
}

/**
 * Update a field or fields in the game db and object
 *
 * @param $player
 * @param array $fields
 * @param string $condition_key
 * @param string $condition_value
 */
function update_game_field($player, $fields = array(), $condition_key = '', $condition_value = '') {
  db_update('formball_games')
    ->fields($fields)
    ->condition($condition_key, $condition_value)
    ->execute();

  if($player != NULL) {
    foreach($fields as $key => $value) {
      $player->$key = $value;
    }
  }
}

/**
 * Handy function to change the player state in the db
 * ex: SEARCH to PLAY, PLAY to GAMEOVER, etc.
 * @param $player
 * @param $new_state
 */
function update_state( $player, $new_state ) {
  update_game_field( $player, array('state' => $new_state), 'sid', $player->sid );
}

/**
 * Resets the id column to 1
 */

function reset_id() {
  mysql_query("ALTER TABLE `formball_games` AUTO_INCREMENT=1");
}

/**
 *
 * Select elements from a database based on conditions
 *
 * @param $db
 * @param array $conditions
 * @return array of elements selected
 */
function select_from_db($db, $conditions = array()) {
  $result = array();
  $query = db_select($db, 'db')
	->fields('db');
  foreach($conditions as $condition=>$value) {
    $query->condition($condition, $value);
  }
  $result_set = $query->execute();
  foreach($result_set as $row) {
	$result[] = $row;
  }
  return $result;
}