<?php
/**
 * @file
 * formball_ft_players.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function formball_ft_players_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function formball_ft_players_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function formball_ft_players_node_info() {
  $items = array(
    'player' => array(
      'name' => t('Player'),
      'base' => 'node_content',
      'description' => t('Football players of the game, not the users. With descriptive data of their position, team, skills, etc.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
