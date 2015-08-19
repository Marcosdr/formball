<?php

/**
 * @file
 * Admin page callback for the formball game module
 */

/**
 * Builds and returns the formball game settings form
 */
function formball_game_admin_settings() {
  $form['formball_game_refresh'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatic page refresh'),
    //'#default_value' => 1,
    '#description' => t('This will enable or disable page refresh every defined period of time'),
  );

  $form['formball_game_refresh_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Refresh time'),
    '#default_value' => 5,
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('Determine the ammount of time in seconds to refresh the page automatically')
  );
  return system_settings_form($form);
}