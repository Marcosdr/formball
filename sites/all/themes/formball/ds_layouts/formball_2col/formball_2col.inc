<?php

/**
 * @file
 * Display Suite Formball 2-col configuration.
 */

function ds_formball_2col() {
  return array(
    'label' => t('Formball 2-col'),
    'regions' => array(
      'left' => t('Left'),
      'right' => t('Right'),
    ),
    // Uncomment if you want to include a CSS file for this layout (formball_2col.css)
    'css' => TRUE,
    // Uncomment if you want to include a preview for this layout (formball_2col.png)
    'image' => TRUE,
  );
}
