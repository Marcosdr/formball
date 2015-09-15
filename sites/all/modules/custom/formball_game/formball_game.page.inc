<?php

function formball_game_page() {
  $build = array(
    'header' => array(
      '#type' => 'markup',
      '#markup' => 'Here goes the game elements',
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

  //kpr($form_state);
  $session_id = session_id();
  $player_id = substr($session_id, 0, 7);


  // Grab or set the variable that stores the players moves
  $player_moves = variable_get('player_moves', array());

  //kpr($player_moves);
  //create array for players checkboxes
  $players = array('A', 'B');

  /* Logic to create form with appropriate checkboxes and its positions on table */
  foreach ($players as $player){
    for ($i=0; $i<9; $i++) {
      for($j=0; $j<5; $j++) {
        $row = $i + 1;
        $column = $j + 1;
        $key = 'player_' . $player . '_' . $row . '_' . $column;
        // create 4 checkboxes on even rows, 5 on odd
        if($i % 2 == 1 && $j == 4) break;
        // Validate if player moves is an array, aka, contain moves to set the default value
        $moves = is_array($player_moves["player $player"])? $player_moves["player $player"] : array('');
        $form[$key] = array(
          '#title' => '',
          '#type' => 'checkbox',
          '#default_value' => in_array($key, $moves),
          '#attributes' => array(
            'class' => array('input-' . $key, 'form-checkbox'),
          ),
        );
      }
    }
  }

  /* Create array for Ball positions */
  $options = array();
  for ($i=0; $i<9; $i++) {
    for ($j = 0; $j < 5; $j++) {
      $row = $i + 1;
      $column = $j + 1;
      $options["ball_{$row}_{$column}"] = "ball_{$row}_{$column}";
    }
  }

  $form['ball'] = [
    '#title' => '',
    '#type' => 'radios',
    '#options' => $options,
  ];

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

  // Grab the players moves from the validation form
  $player_moves = $form_state['storage']['player_moves'];

  // Store the array in the database variable to grab when page refreshes
  variable_set('player_moves', $player_moves);

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