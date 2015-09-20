<?php


function formball_search_game_page() {
  $build = array(
    'header' => array(
      '#type' => 'markup',
      '#markup' => t('Click below to search for available games') . '</br>',
    ),
    'search_game' => array (
      '#type' => 'link',
      '#title' => t('Search Game'),
      '#href' => 'search-game/nojs',
      '#prefix' => '<div class="btn">',
      '#suffix' => '</div><div id="ajax-searching"></div>',
      '#ajax' => array(
        'effect' => 'fade',
      ),
    ),
  );
  return $build;
}

function formball_search_game_ajax($ajax) {
  //database queries and processing
  $match = FALSE;
  $my_game = create_new_game();
  $opponent_game = search_for_game($my_game);

  if($my_game != NULL && $opponent_game != NULL) {
    set_match($my_game, $opponent_game);
    $match = TRUE;
    $output = 'Game On! Player A: ' . $my_game->id . ' vs Player B: ' . $opponent_game->id;
  }
  else $output = 'No Players';

  if ($ajax == 'ajax') {
    $commands = array();

    // Ajax command to replace te 'ajax-searching' element with content
    $commands[] = ajax_command_replace('#ajax-searching', '<div id="ajax-searching">' . $output . '</div>');

    // Add a visual "changed" marker to the '#ajax-searching' element.
    $commands[] = ajax_command_changed('#ajax-searching');

    // Trigger our search_game JQuery plugin.
    if($match) {
      if(verify_match_data($my_game, $opponent_game)) {
        $commands[] = ajax_command_invoke(NULL, 'start_game', array($my_game->path));
      }
    }

    // You have to return a renderable array for the page and ajax callback
    ajax_deliver(array(
      '#type' => 'ajax',
      '#commands' => $commands,
      ));
  }

  else {
    // No ajax, just display the content on a page using renderable array
    return array(
      '#markup' => $output,
    );
  }

}


/**
 * Set an entry in the formball_games db with active search on
 * @return NULL/mixed
 * @throws \Exception
 */
function create_new_game() {

  global $user;

  $game_id = db_insert('formball_games')
    ->fields(array(
      'sid' => user_is_logged_in() ? $user->sid : session_id(),
      'uid' => $user->uid,
      'search_state' => TRUE,
      'timestamp' => $_SERVER['REQUEST_TIME_FLOAT'],
    ))
    ->execute();

  // Search for the game just created in the db and return it as an object
  $game = search_game('id', $game_id);

  return $game;
}

/**
 * Searches for available games from the formball_games db
 * Grabs the game with the oldest timestamp
 *
 * @param string $condition
 * @param bool|TRUE $value
 * @return NULL/mixed
 */

function search_for_game($player = NULL, $condition = 'search_state', $value = TRUE) {

  $game = NULL;
  $condition_check = ":$condition";

  $result = db_query("
    SELECT * FROM {formball_games}
    WHERE $condition = $condition_check
    ORDER BY timestamp DESC", array($condition_check => $value)
  );

  foreach($result as $record) {
    $games[] = $record;
  }

  if(count($games) > 1 ) {
    $game = array_pop($games);
    // Update each player's object and db with it's opponent data
    $fields = array(
      'opponent' => $game->sid,
    );
    update_game_field($player, $fields, 'sid', $player->sid);
    $fields = array(
      'opponent' => $player->sid,
    );
    update_game_field($game, $fields, 'sid', $game->sid);
  }

  return $game;
}

/**
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
 * Set Match
 * Establishes players and game path to both the current user and his opponent
 *
 * @param null $player
 * @param null $opponent
 */
function set_match(&$player = NULL, &$opponent = NULL) {

  if($player != NULL && $opponent != NULL ) {
    update_game($player, $opponent);
  }
}

/**
 * Update Game
 * Updates the values inside the selected game
 */

function update_game(&$player, &$opponent) {

  $path = 'game';
  $path .= drupal_substr($player->sid, 0, 7);
  $path .= drupal_substr($opponent->sid, 0, 7);
  if($player->timestamp < $opponent->timestamp) {
    $player_type = 'A';
    $opponent_type = 'B';
  }
  else {
    $player_type = 'B';
    $opponent_type = 'A';
  }

  // Update the player records
  $fields = array(
    'path' => $path,
    'player' => $player_type,
  );
  update_game_field($player, $fields, 'sid', $player->sid);

  // Update the opponent records
  $fields = array(
    'path' => $path,
    'player' => $opponent_type,
  );
  update_game_field($opponent, $fields, 'sid', $opponent->sid);
}


/**
 * Update a field or fields in the game db and object
 *
 * @param $player
 * @param array $fields
 * @param string $condition_key
 * @param string $condition_value
 */
function update_game_field(&$player, $fields = array(), $condition_key = '', $condition_value = '') {
  db_update('formball_games')
    ->fields($fields)
    ->condition($condition_key, $condition_value)
    ->execute();

  foreach($fields as $key => $value) {
    $player->$key = $value;
  }
}

/**
 * Verify that the match data is correct before proceeding to the js code
 * To redirect both players to the match
 *
 * @param null $player
 * @param null $opponent
 * @return bool
 */
function verify_match_data($player = NULL, $opponent = NULL){
  $proceed = false;

  if($player->opponent == $opponent->sid
  && $opponent->opponent == $player->sid)
    $proceed = true;

  return $proceed;
}

/**
 * Resets the id column to 1
 */

function reset_id() {
  mysql_query("ALTER TABLE `formball_games` AUTO_INCREMENT=1");
}


// Might want to use timer_start instead of time()
// https://api.drupal.org/api/drupal/includes!bootstrap.inc/function/timer_start/7
// https://api.drupal.org/api/drupal/includes!common.inc/function/drupal_http_request/7