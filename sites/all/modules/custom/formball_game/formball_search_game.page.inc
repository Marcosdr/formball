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
  $my_game = create_new_game();
  $opponent_game = search_for_game();

  if($my_game != NULL && $opponent_game != NULL) {
    set_match($my_game, $opponent_game);
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
    $commands[] = ajax_command_invoke(NULL, 'search_game');

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
      'timestamp' => REQUEST_TIME,
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

function search_for_game($condition = 'search_state', $value = TRUE) {

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
 * Set Game
 * Establishes players and game path to both the current user and his opponent
 */

function set_match($player = NULL, $opponent = NULL) {

  if($player != NULL && $opponent != NULL ) {
    update_game($player, $opponent);
  }
}

/**
 * Update Game
 * Updates the values inside the selected game
 */

function update_game($player, $opponent) {

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

  db_update('formball_games')
    ->fields(array(
      'path' => $path,
      'player' => $player_type,
    ))
    ->condition('sid', $player->sid)
    ->execute();

  db_update('formball_games')
    ->fields(array(
      'path' => $path,
      'player' => $opponent_type,
    ))
    ->condition('sid', $opponent->sid)
    ->execute();
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