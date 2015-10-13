<?php
  require(drupal_get_path('module', 'formball_game') . '/includes/formball_utilities.inc');

/**
 * Function to create and ajax link in the search page to look for games
 * @return array
 */
function formball_search_game_page() {
  $build = array(
    'line_up_header' => array(
      '#type' => 'markup',
      '#markup' => '<div class="header"><h3>' . t('Select your line up') . '</h3></div>',
    ),

    'line_up_form' => drupal_get_form('line_up_form'),

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

function line_up_form($form, &$form_state) {

  $players = get_line_up_players();
  $player_output = array();
  foreach($players as $type => $player_set) {
    foreach($player_set as $player){
      $output = $type . " ";
      $output .= $player->field_player_number[LANGUAGE_NONE][0]['value'] . " ";
      $output .= $player->field_player_name[LANGUAGE_NONE][0]['value'];
      $player_output[] = $output;
    }
    
  }
  $attributes = array(
    'id' => 'my-custom-listing',
    'class' => 'custom-class another-custom-class',
  );

  $width = '" width="250px">';

  $form['start_grid'] = array(
    '#type' => 'item',
    '#markup' => '<div class="pure-g clearfix">',
  );

  $form['players'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'pure-u-1 pure-u-md-1-2',
      ),
    ),
  );

  $form['players']['line_up_players'] = array(
    '#type' => 'item',
    '#markup' => theme_item_list(array(
      'items' => $player_output,
      'title' => 'players',
      'type' => 'ul',
      'attributes' => $attributes,
    )),
  );

  $form['line_up'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'pure-u-1 pure-u-md-1-2',
      ),
    ),
  );

  $form['line_up']['line_up_3_2_1'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-3-2-1.jpg' . $width,
    '#states' => array(
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '0'),
      ),
    ),
  );
  $form['line_up']['line_up_3_1_2'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-3-1-2.jpg' . $width,
    '#states' => array(
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '1'),
      ),
    ),
  );
  $form['line_up']['line_up_2_3_1'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-2-3-1.jpg' . $width,
    '#states' => array(
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '2'),
      ),
    ),
  );
  $form['line_up']['line_up_2_2_2'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-2-2-2.jpg' . $width,
    '#states' => array(
      // Only show this field when the 'toggle_me' checkbox is enabled.
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '3'),
      ),
    ),
  );
  $form['line_up']['line_up_radios'] = array(
    '#type' => 'radios',
    '#options' => array(
      0 => t('3-2-1'),
      1 => t('3-1-2'),
      2 => t('2-3-1'),
      3 => t('2-2-2'),
    ),
  );
  $form['end_grid'] = array(
    '#type' => 'item',
    '#markup' => '</div>',
  );

  return $form;
}


function get_line_up_players(){
  $db = 'field_data_field_player_team';
  $conditions = array(
    'field_player_team_tid' => '12',
  );
  $players_type = select_from_db($db, $conditions);

  return select_line_up_players($players_type);
}

function select_line_up_players($players_type) {
  $players = array();
  foreach($players_type as $player) {
    $players[] = node_load($player->entity_id);
  }

  $all_players = array(
    'gk' => array(),
    'df' => array(),
    'md' => array(),
    'fw' => array(),
  );

  foreach($players as $player){
    if (isset($player->field_player_position)) {
      $position = taxonomy_term_load($player->field_player_position[LANGUAGE_NONE][0]['tid']);
    }
    switch($position->name) {
      case 'GK':
        $all_players['gk'][] = $player;
        break;
      case 'DF':
        $all_players['df'][] = $player;
        break;
      case 'MD':
        $all_players['md'][] = $player;
        break;
      case 'FW':
        $all_players['fw'][] = $player;
        break;
    }
  }
  $line_up = array(
    'gk' => array(),
    'df' => array(),
    'md' => array(),
    'fw' => array(),
    );

  $num_players = array(
    'gk' => 1,
    'df' => 3,
    'md' => 3,
    'fw' => 2,
    );
  foreach($num_players as $type => $num) {
    for($i=0;$i<$num;$i++) {
      $rand_keys = array_rand($all_players[$type], $num);
      if($type == 'gk') {
        $line_up[$type][] = $all_players[$type][$rand_keys];
      }
      else {
        $line_up[$type][] = $all_players[$type][$rand_keys[$i]];
      }
    }
  }
  return $line_up;
}

function formball_game_preprocess_form_element(&$variables) {
  $element = $variables['element'];

  if ($element['#type'] == 'item') {
    $variables['element']['#attributes']['class'][] = 'caca';
  }

}

/**
 * Formball Search Game
 *
 * 1) Creates the current player game and inserts it into the db
 * 2) Looks for an opponent in the database for a limited ammount of time
 * 3) Sets the match data for both players
 * 4) Verifies that everything is matching before moving forward
 * 5) Redirects both players to the Game page
 *
 * @param $ajax
 * @return array
 */
function formball_search_game_ajax($ajax) {

  //database queries and processing
  $match = FALSE;

  // 1) Creates the current player game and inserts it into the db
  $my_game = create_new_game();

  // 2) Looks for an opponent in the database for a limited amount of time
  $max_search_time = strtotime("+10 seconds"); // Defines the search time limit
  $opponent_game = search_for_game($my_game, $max_search_time);

  //3) Sets the match data for both players
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

    // 4) Verifies that everything is matching before moving forward
    // Trigger our search_game JQuery plugin.
    if($match) {
      if(verify_match_data($my_game, $opponent_game)) {

        // 5) Redirects both players to the Game page
        //$commands[] = ajax_command_invoke(NULL, 'start_game', array($my_game->path));
        $redirect_url = $my_game->path; // 'user'
        ctools_include('ajax');
        ctools_add_js('ajax-responder');
        $commands[] = ctools_ajax_command_redirect($redirect_url);
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
  $session_id = session_id();
  $_SESSION['formball']['lists'] = $session_id;

  global $user;

  $game_id = db_insert('formball_games')
    ->fields(array(
      'sid' => user_is_logged_in() ? $user->sid : $session_id,
      'uid' => $user->uid,
      'state' => 'SEARCH',
      'timestamp' => $_SERVER['REQUEST_TIME_FLOAT'],
    ))
    ->execute();

  // Search for the game just created in the db and return it as an object
  $game = search_game('id', $game_id);

  return $game;
}

/**
 * This is a recursive function
 * Searches for available games from the formball_games db
 * Grabs the game with the oldest timestamp
 *
 * @param string $condition
 * @param bool|TRUE $value
 * @return NULL/mixed
 */

function search_for_game($player = NULL, $timeout = 0,  $condition = 'state', $value = 'SEARCH') {

  // First check if some opponent has already assigned me a game
  // If so, exit the search and continue
  $path = search_game_field('path', 'sid', $player->sid);
  if(!is_null($path)) {
    $opponent = search_game_field('opponent', 'sid', $player->sid);
    $game = search_game('sid', $opponent);
    $player->opponent = $game->sid;
    return $game;
  }

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

  // Remove your own game from the results
  foreach($games as $key => $game) {
    if($player->sid == $game->sid) {
      unset($games[$key]);
    }
  }

  // if it finds an available game, then return it
  if(count($games) > 0 ) {
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
    return $game;
  }

  // If we have been searching for more than X amount of time, return NULL
  // Which will indicate the player that there are no matches available
  if ($timeout <= time()) {
    return NULL;
  }

  // Wait for 2 seconds before calling the function again
  sleep(2);
  return search_for_game($player, $timeout, 'state', 'SEARCH');
}

/**
 * Set Match
 * Establishes players and game path to both the current user and his opponent
 *
 * @param null $player
 * @param null $opponent
 */
function set_match(&$player = NULL, &$opponent = NULL) {

  if($player != NULL && $opponent != NULL) {

    // Check to see if the current player has it's path values already set from the opponent
    $path = search_game_field('path', 'sid', $player->sid);
    if(!is_null($path)) {
      $player_type = search_game_field('player', 'sid', $player->sid);
      // If the values have been updated, then update the current player records
      $fields = array(
        'path' => $path,
        'player' => $player_type,
      );
      update_game_field($player, $fields, 'sid', $player->sid);
    }

    // If the player doesn't have it's data updated, then update his and its opponent
    else {
      $path = 'match/game-';
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

    // After making all the necessary changes, setup the players status to PLAY
    update_state( $player, 'PLAY' );
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
function verify_match_data(&$player = NULL, &$opponent = NULL){
  $proceed = false;

  if($player->opponent == $opponent->sid
  && $opponent->opponent == $player->sid) {
    // verify that both are in PLAY mode, use Sleep here
    $proceed = true;
  }

  return $proceed;
}


