<?php
require_once(drupal_get_path('module', 'formball_game') . '/includes/formball_utilities.inc');
require_once(drupal_get_path('module', 'formball_game') . '/game/Game.php');
require_once(drupal_get_path('module', 'formball_game') . '/game/renderElements/FormElement.php');

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
  $checkboxes = $game->render('boxes');
  foreach ($checkboxes as $checkbox){
    $key = $checkbox->id;

    $form[$key] = array(
      '#title' => '',
      '#type' => 'checkbox',
      '#default_value' => $checkbox->value,
      '#attributes' => array(
        'class' => array('input-' . $key, 'form-checkbox'),
      ),
      '#prefix' => $checkbox->prefix,
      '#suffix' => $checkbox->suffix,
      '#disabled' => $checkbox->is_opponent,
    );
  }


//  foreach ($game->world->getField()->getBoxes() as $box){
//    $key = $box->getName();
//
//    $form[$key] = array(
//      '#title' => '',
//      '#type' => 'checkbox',
//      '#default_value' => $box->has_player(),
//      '#attributes' => array(
//        'class' => array('input-' . $key, 'form-checkbox'),
//      ),
//      '#disabled' => ($box->is_type() !== 'A'),
//    );
//  }

  // Pass the boxes values to the template
//  $form['boxes'] = array(
//    '#value' => $game->world->getField()->getBoxes(),
//  );


  // Create array for Ball positions
  $options = array();
  $radios = $game->render('balls');
  foreach ($radios as $radio){
    $key = $radio->id;
    $options[$key] = $key;
  }


//  foreach ($game->world->getField()->getBalls() as $ball){
//    $key = $ball->getName();
//    $options[$key] = $key;
//  }


  $form['ball'] = array(
    '#title' => '',
    '#type' => 'radios',
    '#options' => $options,
    );

  $form['store'] = array(
    '#type' => 'value',
    '#value' => $radios,
  );



  // Pass the ball values to the template
//  $form['balls'] = array(
//    '#value' => $game->world->getField()->getBalls(),
//  );



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
