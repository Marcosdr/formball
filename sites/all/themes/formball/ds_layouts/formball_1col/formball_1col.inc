<?php

/**
 * @file
 * Display Suite Formball 1-col configuration.
 */

function ds_formball_1col() {
  return array(
    'label' => t('Formball 1-col'),
    'regions' => array(
      'center' => t('Center'),
    ),
    // Uncomment if you want to include a CSS file for this layout (formball_1col.css)
    'css' => TRUE,
    // Uncomment if you want to include a preview for this layout (formball_1col.png)
    'image' => TRUE,
  );
}
