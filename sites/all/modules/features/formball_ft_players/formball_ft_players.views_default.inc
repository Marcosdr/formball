<?php
/**
 * @file
 * formball_ft_players.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function formball_ft_players_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'players_all';
  $view->description = 'View all players in the site';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Players All';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Players All';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Team */
  $handler->display->display_options['fields']['field_player_team']['id'] = 'field_player_team';
  $handler->display->display_options['fields']['field_player_team']['table'] = 'field_data_field_player_team';
  $handler->display->display_options['fields']['field_player_team']['field'] = 'field_player_team';
  /* Field: Content: Position */
  $handler->display->display_options['fields']['field_player_position']['id'] = 'field_player_position';
  $handler->display->display_options['fields']['field_player_position']['table'] = 'field_data_field_player_position';
  $handler->display->display_options['fields']['field_player_position']['field'] = 'field_player_position';
  /* Field: Content: Number */
  $handler->display->display_options['fields']['field_player_number']['id'] = 'field_player_number';
  $handler->display->display_options['fields']['field_player_number']['table'] = 'field_data_field_player_number';
  $handler->display->display_options['fields']['field_player_number']['field'] = 'field_player_number';
  $handler->display->display_options['fields']['field_player_number']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Speed */
  $handler->display->display_options['fields']['field_player_speed']['id'] = 'field_player_speed';
  $handler->display->display_options['fields']['field_player_speed']['table'] = 'field_data_field_player_speed';
  $handler->display->display_options['fields']['field_player_speed']['field'] = 'field_player_speed';
  $handler->display->display_options['fields']['field_player_speed']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Offense */
  $handler->display->display_options['fields']['field_player_offense']['id'] = 'field_player_offense';
  $handler->display->display_options['fields']['field_player_offense']['table'] = 'field_data_field_player_offense';
  $handler->display->display_options['fields']['field_player_offense']['field'] = 'field_player_offense';
  $handler->display->display_options['fields']['field_player_offense']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Defense */
  $handler->display->display_options['fields']['field_player_defense']['id'] = 'field_player_defense';
  $handler->display->display_options['fields']['field_player_defense']['table'] = 'field_data_field_player_defense';
  $handler->display->display_options['fields']['field_player_defense']['field'] = 'field_player_defense';
  $handler->display->display_options['fields']['field_player_defense']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Technic */
  $handler->display->display_options['fields']['field_player_technic']['id'] = 'field_player_technic';
  $handler->display->display_options['fields']['field_player_technic']['table'] = 'field_data_field_player_technic';
  $handler->display->display_options['fields']['field_player_technic']['field'] = 'field_player_technic';
  $handler->display->display_options['fields']['field_player_technic']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Kick */
  $handler->display->display_options['fields']['field_player_kick']['id'] = 'field_player_kick';
  $handler->display->display_options['fields']['field_player_kick']['table'] = 'field_data_field_player_kick';
  $handler->display->display_options['fields']['field_player_kick']['field'] = 'field_player_kick';
  $handler->display->display_options['fields']['field_player_kick']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'player' => 'player',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'players-all';
  $export['players_all'] = $view;

  return $export;
}
