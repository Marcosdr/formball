<?php
/**
 * @file
 * formball_import_settings.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function formball_import_settings_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_players';
  $feeds_importer->config = array(
    'name' => 'Import players',
    'description' => 'Import players from CSV',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'direct' => FALSE,
        'allowed_extensions' => 'txt csv tsv xml opml',
        'directory' => 'public://feeds',
        'allowed_schemes' => array(
          0 => 'public',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'bundle' => 'player',
        'update_existing' => '1',
        'expire' => '-1',
        'mappings' => array(
          0 => array(
            'source' => 'ID',
            'target' => 'title',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'Name',
            'target' => 'field_player_name',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'Team',
            'target' => 'field_player_team',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Position',
            'target' => 'field_player_position',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'Number',
            'target' => 'field_player_number',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'Speed',
            'target' => 'field_player_speed',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'Offense',
            'target' => 'field_player_offense',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'Defense',
            'target' => 'field_player_defense',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'Technic',
            'target' => 'field_player_technic',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'Kick',
            'target' => 'field_player_kick',
            'unique' => FALSE,
          ),
        ),
        'input_format' => 'plain_text',
        'author' => 0,
        'authorize' => 1,
        'update_non_existent' => 'skip',
        'skip_hash_check' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_players'] = $feeds_importer;

  return $export;
}
