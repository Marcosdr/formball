<?php
require_once(drupal_get_path('module', 'formball_game') . '/includes/formball_utilities.inc');
require_once(drupal_get_path('module', 'formball_game') . '/game/Game.php');

function formball_game_page($arg1) {

  $build = array(
    'header' => array(
      '#type' => 'markup',
      '#markup' => 'Here goes the game ' . $arg1 . ' elements',
    ),
    'game_table' => drupal_get_form('formball_game_form'),

  );
  return $build;
}

/**
 * Form containing the game board and elements
 *
 * @param $form
 * @param $form_submit
 * @return mixed
 */

function formball_game_form($form, &$form_state) {

  // Create an instance of the game
  $game = new Game();

  // Create the players checkboxes
  foreach ($game->world->getField()->getBoxes() as $box){
    $key = $box->getName();

    $form[$key] = array(
      '#title' => '',
      '#type' => 'checkbox',
      '#default_value' => $box->has_player(),
      '#attributes' => array(
        'class' => array('input-' . $key, 'form-checkbox'),
      ),
      '#disabled' => ($box->is_type() !== 'A'),
    );
  }

  // Pass the boxes values to the template
  $form['boxes'] = array(
    '#value' => $game->world->getField()->getBoxes(),
  );

  // Create array for Ball positions
  $options = array();
  foreach ($game->world->getField()->getBalls() as $ball){
    $key = $ball->getName();
    $options[$key] = $key;
  }

  $form['ball'] = [
    '#title' => '',
    '#type' => 'radios',
    '#options' => $options,
  ];

  // Pass the ball values to the template
  $form['balls'] = array(
    '#value' => $game->world->getField()->getBalls(),
  );



  // Get player and opponent data and store them in objects
  /*
  $game->setPlayer(search_game('sid', $session_id));
  $game->setOpponent(search_game('sid', $game->getPlayer()->opponent));


  // Grab latest player moves
  $players = array($player_class, $opponent_class);
  $players_moves = array();
  foreach( $players as $player ) {
    if($player->moves != null) {
      $player_moves = unserialize($player->moves);
      $player_moves = array_pop($player_moves);
      $players_moves["player $player->player"] = $player_moves;
    }
  }
  */
  /* TEMP FOR TESTING */
  //$players_moves['player B'] = 'player_B_1_1';
  /* END TEMP */

  //$players = array('A', 'B');
  /* Logic to create form with appropriate checkboxes and its positions on table */
  /*
  foreach ($players as $player){
    for ($i=0; $i<9; $i++) {
      for($j=0; $j<5; $j++) {
        $row = $i + 1;
        $column = $j + 1;
        $key = 'player_' . $player . '_' . $row . '_' . $column;
        // create 4 checkboxes on even rows, 5 on odd
        if($i % 2 == 1 && $j == 4) break;
        // Validate if player moves is an array, aka, contain moves to set the default value
        $moves = array();
        if(isset($players_moves["player $player"])) {
          $moves = is_array($players_moves["player $player"])? $players_moves["player $player"] : array('');
        }
        $form[$key] = array(
          '#title' => '',
          '#type' => 'checkbox',
          '#default_value' => in_array($key, $moves),
          '#attributes' => array(
            'class' => array('input-' . $key, 'form-checkbox'),
          ),
          '#disabled' => ($player !== $player_class->player),
        );
      }
    }

  }
  */
  /* Create array for Ball positions */
//  $options = array();
//  for ($i=0; $i<9; $i++) {
//    for ($j = 0; $j < 5; $j++) {
//      $row = $i + 1;
//      $column = $j + 1;
//      $options["ball_{$row}_{$column}"] = "ball_{$row}_{$column}";
//    }
//  }

//  $form['ball'] = [
//    '#title' => '',
//    '#type' => 'radios',
//    '#options' => $options,
//  ];

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}

/**
 * Validation for game_board_form()
 */

function formball_game_form_validate($form, &$form_state) {
  // validation criterias here

  // Grab the current player positions (Moves)
  // Store the players moves in an array
  $player_moves = array(
    'player A' => '',
    'player B' => '',
  );

  // check to see which moves has the player done and validate them
  $players = array('A', 'B');
  foreach ($players as $player) {
    for ($i = 0; $i < 9; $i++) {
      for ($j = 0; $j < 5; $j++) {
        if($i % 2 == 1 && $j == 4) break;
        $row = $i + 1;
        $column = $j + 1;
        $key = 'player_' . $player . '_' . $row . '_' . $column;
        if($form_state['values'][$key] == 1 ){
          if ($player == 'A') {
            $player_moves['player A'][] = $key;
          } else $player_moves['player B'][] = $key ;
        }
      }
    }
  }

  $form_state['storage']['player_moves'] = $player_moves;
}


/**
 * Submit function for game_board_form()
 */
function formball_game_form_submit($form, &$form_state) {
  $session_id = session_id();

  $player = search_game_field('player', 'sid', $session_id);
  $player = 'player ' . $player;

  // Grab the players moves from the validation form
  $player_moves = serialize($form_state['storage']['player_moves'][$player]);

  // Store the players moves in the database variable to grab when page refreshes
  $player = NULL;
  update_game_field($player, array('moves' => $player_moves), 'sid', $session_id);

  // Display messages here
  //drupal_set_message(implode(" ", $player_moves));

}

/**
 * Implements hook_theme()
 * Point to the theme for the game elements
 */

function formball_game_theme($existing, $type, $theme, $path){
  $module_path = drupal_get_path('module', 'formball_game');
  $items['formball_game_form'] = array (
    'render element' => 'form',
    'template' => 'game',
    'path' => $module_path . '/theme',
  );
  return $items;
}
