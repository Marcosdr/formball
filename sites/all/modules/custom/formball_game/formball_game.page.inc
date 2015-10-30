<?php
require_once(drupal_get_path('module', 'formball_game') . '/includes/formball_utilities.inc');
require_once(drupal_get_path('module', 'formball_game') . '/game/Game.php');
require_once(drupal_get_path('module', 'formball_game') . '/game/renderElements/FormElement.php');

function formball_game_page($arg1) {

  $build = array(
    'header' => array(
      '#type' => 'markup',
      '#markup' => 'Here goes the game ' . $arg1 . ' elements' .
                    '<br/> session id: ' . session_id(),
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

  $session = session_id();
  $player = search_game('sid', $session);
  $opponent = search_game('sid', $player->opponent);

  // Create an instance of the game and pass the player and opponent object.
  $game = new Game($player, $opponent);

  // Create the players checkboxes
  $form_output = $game->render();
  foreach ($form_output['boxes'] as $checkbox){
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

  // Create array for Ball positions
  $options = array();

  foreach ($form_output['balls'] as $radio){
    $key = $radio->id;
    $options[$key] = $key;
  }

  $form['ball'] = array(
    '#title' => '',
    '#type' => 'radios',
    '#options' => $options,
    );

  $form['store'] = array(
    '#type' => 'value',
    '#value' => $form_output['balls'],
  );


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

  // check to see which moves has the player done and validate them

}


/**
 * Submit function for game_board_form()
 */
function formball_game_form_submit($form, &$form_state) {

}


