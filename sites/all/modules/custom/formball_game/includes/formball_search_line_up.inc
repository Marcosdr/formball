<?php

function formball_line_up_form($form, &$form_state) {

  // Identify that the elements in 'player_items' are a collection, to
  // prevent Form API from flattening the array when submitted.
  $form['player_items']['#tree'] = TRUE;

  // Fetch the players data from the database, ordered by weight ascending.
  $players = get_line_up_players();

  $player_output = array();
  foreach($players as $type => $player_set) {
    foreach($player_set as $player){
      $output = $type . " ";
      $output .= $player->field_player_number[LANGUAGE_NONE][0]['value'] . " ";
      $output .= $player->field_player_name[LANGUAGE_NONE][0]['value'];
      $player_output[] = $output;
    }

  }
  $attributes = array(
    'id' => 'my-custom-listing',
    'class' => 'custom-class another-custom-class',
  );

  $width = '" width="250px">';

  $form['start_grid'] = array(
    '#type' => 'item',
    '#markup' => '<div class="pure-g clearfix">',
  );

  $form['players'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'pure-u-1 pure-u-md-1-2',
      ),
    ),
  );

  $form['players']['line_up_players'] = array(
    '#type' => 'item',
    '#markup' => theme_item_list(array(
      'items' => $player_output,
      'title' => 'players',
      'type' => 'ul',
      'attributes' => $attributes,
    )),
  );

  $form['line_up'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'pure-u-1 pure-u-md-1-2',
      ),
    ),
  );

  $form['line_up']['line_up_3_2_1'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-3-2-1.jpg' . $width,
    '#states' => array(
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '0'),
      ),
    ),
  );
  $form['line_up']['line_up_3_1_2'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-3-1-2.jpg' . $width,
    '#states' => array(
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '1'),
      ),
    ),
  );
  $form['line_up']['line_up_2_3_1'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-2-3-1.jpg' . $width,
    '#states' => array(
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '2'),
      ),
    ),
  );
  $form['line_up']['line_up_2_2_2'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-2-2-2.jpg' . $width,
    '#states' => array(
      // Only show this field when the 'toggle_me' checkbox is enabled.
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '3'),
      ),
    ),
  );
  $form['line_up']['line_up_radios'] = array(
    '#type' => 'radios',
    '#options' => array(
      0 => t('3-2-1'),
      1 => t('3-1-2'),
      2 => t('2-3-1'),
      3 => t('2-2-2'),
    ),
  );
  $form['end_grid'] = array(
    '#type' => 'item',
    '#markup' => '</div>',
  );

  return $form;
}


function get_line_up_players(){
  $db = 'field_data_field_player_team';
  $conditions = array(
    'field_player_team_tid' => '12',
  );
  $all_players = select_from_db($db, $conditions);

  return select_line_up_players($all_players);
}

function select_line_up_players($players_type) {
  $players = array();
  foreach($players_type as $player) {
    $players[] = node_load($player->entity_id);
  }

  $all_players = array(
    'gk' => array(),
    'df' => array(),
    'md' => array(),
    'fw' => array(),
  );

  foreach($players as $player){
    if (isset($player->field_player_position)) {
      $position = taxonomy_term_load($player->field_player_position[LANGUAGE_NONE][0]['tid']);
    }
    switch($position->name) {
      case 'GK':
        $all_players['gk'][] = $player;
        break;
      case 'DF':
        $all_players['df'][] = $player;
        break;
      case 'MD':
        $all_players['md'][] = $player;
        break;
      case 'FW':
        $all_players['fw'][] = $player;
        break;
    }
  }
  $line_up = array(
    'gk' => array(),
    'df' => array(),
    'md' => array(),
    'fw' => array(),
  );

  $num_players = array(
    'gk' => 1,
    'df' => 3,
    'md' => 3,
    'fw' => 2,
  );
  foreach($num_players as $type => $num) {
    for($i=0;$i<$num;$i++) {
      $rand_keys = array_rand($all_players[$type], $num);
      if($type == 'gk') {
        $line_up[$type][] = $all_players[$type][$rand_keys];
      }
      else {
        $line_up[$type][] = $all_players[$type][$rand_keys[$i]];
      }
    }
  }
  return $line_up;
}

/**
 * Theme function for the line up players form
 * @param $variables
 */
function theme_formball_line_up_form($variables) {

}