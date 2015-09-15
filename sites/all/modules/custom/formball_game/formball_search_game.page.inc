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