<?php
/**
 * @file
 * formball_import_settings.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function formball_import_settings_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}
