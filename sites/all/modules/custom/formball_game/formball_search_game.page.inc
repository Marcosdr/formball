<?php


function formball_search_game_page() {
  $build = array(
    'header' => array(
      '#type' => 'markup',
      '#markup' => 'Click below to search for available games',
    ),
    'game_search' => drupal_get_form('formball_search_game_form'),
  );
  return $build;
}

/**
 * Form containing the Search Game button
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */

function formball_search_game_form($form, &$form_state) {
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Search Game',
  );

  return $form;
}

/**
 * Submit function for the formball_search_game_form()
 */
function formball_search_game_form_submit($form, &$form_state) {

  create_new_game();
}

/**
 * Set an entry in the formball_games db with active search on
 */
function create_new_game() {

  global $user;

  db_insert('formball_games')
    ->fields(array(
      'sid' => user_is_logged_in() ? $user->sid : session_id(),
      'uid' => $user->uid,
      'search_state' => TRUE,
      'timestamp' => REQUEST_TIME,
    ))
    ->execute();
}