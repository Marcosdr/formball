<?php

/**
 * Add unique class (mlid) to all menu items.
 */
function formball_preprocess_links($variables) {
  if($variables['attributes']['id'] == 'main-menu-links'){
    $variables['links']
    kpr($variables);
  }
}