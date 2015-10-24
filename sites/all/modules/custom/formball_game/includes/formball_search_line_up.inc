<?php

function formball_game_line_up_form($form, &$form_state) {

  // Identify that the elements in 'player_items' are a collection, to
  // prevent Form API from flattening the array when submitted.
  $form['player_items']['#tree'] = TRUE;

  // Fetch the players data from the database, ordered by weight ascending.
  $line_up_players = get_line_up_players();

  // Start building the container for the players and the field lineup
  $form['start_grid'] = array(
    '#type' => 'item',
    '#markup' => '<div class="pure-g clearfix">',
  );

  $form['line_up_players'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'pure-u-1 pure-u-md-1-2',
      ),
    ),
  );


  // Iterate through each line up player.
  foreach($line_up_players as $key_position => $position){
    foreach($position['players'] as $player) {
      $id = $player->nid->value();
      // Create a form entry for this item with unique id as the player id.
      $form['line_up_players'][$id] = array(
        'position' => array(
          '#markup' => '<div class="player-pos-' . strtolower($key_position) .
                       '">' . $key_position . '</div>',
        ),
        'name' => array (
          '#type' => 'link',
          '#title' => $player->field_player_name->value(),
          '#href' => 'player/values/nojs/' . $id,
          '#prefix' => '<div class="player-name">',
          '#suffix' => '</div>',
          '#ajax' => array(
            'effect' => 'fade',
          )),

        'weight' => array(
          '#type' => 'weight',
          '#title' => t('Weight'),
          '#default_value' => $player->field_player_weight->value(),
          '#delta' => 10,
          '#title_display' => 'invisible',
        ),
      );
    }
  }

  $width = '" width="250px">';
  $form['line_up_field'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'pure-u-1 pure-u-md-1-2',
      ),
    ),
  );

  $form['line_up_field']['line_up_3_2_1'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-3-2-1.jpg' . $width,
    '#states' => array(
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '0'),
      ),
    ),
  );
  $form['line_up_field']['line_up_3_1_2'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-3-1-2.jpg' . $width,
    '#states' => array(
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '1'),
      ),
    ),
  );
  $form['line_up_field']['line_up_2_3_1'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-2-3-1.jpg' . $width,
    '#states' => array(
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '2'),
      ),
    ),
  );
  $form['line_up_field']['line_up_2_2_2'] = array(
    '#type' => 'item',
    '#markup' => '<img src="' . drupal_get_path('module', 'formball_game') . '/images/lineup-2-2-2.jpg' . $width,
    '#states' => array(
      // Only show this field when the 'toggle_me' checkbox is enabled.
      'visible' => array(
        ':input[name="line_up_radios"]' => array('value' => '3'),
      ),
    ),
  );

  $form['player_values_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'pure-u-1 pure-u-md-1-2',
      ),
    ),
  );

  $form['player_values_container']['player_values'] = array(
    'values' => array(
      '#markup' => '<div id="game-search-player-values"></div>',
    ),
  );

  $form['line_up_strategy_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'pure-u-1 pure-u-md-1-2',
      ),
    ),
  );

  $form['line_up_strategy_container']['line_up_radios'] = array(
    '#type' => 'radios',
    '#options' => array(
      0 => t('3-2-1'),
      1 => t('3-1-2'),
      2 => t('2-3-1'),
      3 => t('2-2-2'),
    ),
    '#default_value' => 0,
  );

  $form['end_grid'] = array(
    '#type' => 'item',
    '#markup' => '</div>',
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Search Game'));

  return $form;
}


function get_line_up_players(){
  $db = 'field_data_field_player_team';
  $conditions = array(
    'field_player_team_tid' => '12',
  );
  $all_db_players = select_from_db($db, $conditions);

  return select_line_up_players($all_db_players);
}

function select_line_up_players($all_db_players) {
  // Init line-up players array
  $line_up_players = array(
    'GK' => array('players' => array(), 'count' => 1),
    'DF' => array('players' => array(), 'count' => 3),
    'MD' => array('players' => array(), 'count' => 3),
    'FW' => array('players' => array(), 'count' => 2),
  );

  // Grab all player nodes from the db selected players
  $all_players = array();
  foreach($all_db_players as $player) {
    $player_node = node_load($player->entity_id);
    $all_players[] = entity_metadata_wrapper('node', $player_node);
  }

  // Shuffle the players
  if(shuffle($all_players)){
    // Select the line-up players
    foreach($all_players as $player){
      if (isset($player->field_player_position)) {
        // Grab the position the player plays as (GK, DF, MD or FW)
        $position = $player->field_player_position->value()->name;
        $current_count = count($line_up_players[$position]['players']);
        if($current_count < $line_up_players[$position]['count']) {
          define_player_weight($player, $position, $current_count);
          switch ($position) {
            case 'GK':
              $line_up_players['GK']['players'][] = $player;
              break;
            case 'DF':
              $line_up_players['DF']['players'][] = $player;
              break;
            case 'MD':
              $line_up_players['MD']['players'][] = $player;
              break;
            case 'FW':
              $line_up_players['FW']['players'][] = $player;
              break;
          }
        }
      }
    }
  }

  return $line_up_players;
}

/**
 * Defines the weight values for each of the 9 players that form the lineup.
 *
 * @param object $player The player entity object
 * @param string $position GK, DF, MF or FW
 * @param int $count The current count of the players in each position
 */
function define_player_weight(&$player, $position, $count) {
  switch ($position) {
    case 'GK':
      $player->field_player_weight->set(1);
      break;
    case 'DF':
      $player->field_player_weight->set($count + 2);
      break;
    case 'MD':
      if($count === 2) $player->field_player_weight->set(8);
      else $player->field_player_weight->set($count + 5);
      break;
    case 'FW':
      if($count === 1) $player->field_player_weight->set(9);
      else $player->field_player_weight->set(7);
      break;
  }
}

function formball_player_values_ajax($ajax, $player_id) {

  $node = node_load($player_id);
  $player = entity_metadata_wrapper('node', $node);
  $position = $player->field_player_position->value()->name;
  $output = '';

  $output .= '<table>';
  $output .= '<caption class="player-pos-' . strtolower($position) . '">' . $player->field_player_name->value() . '</caption>';
  $output .= '<tbody>';
  $output .= '<tr><td>' . t('SPEED') . '</td><td>' . $player->field_player_speed->value() . '</td></tr>';
  $output .= '<tr><td>' . t('TECHNIC') . '</td><td>' . $player->field_player_technic->value() . '</td></tr>';
  $output .= '<tr><td>' . t('OFFENSE') . '</td><td>' . $player->field_player_offense->value() . '</td></tr>';
  $output .= '<tr><td>' . t('DEFENSE') . '</td><td>' . $player->field_player_defense->value() . '</td></tr>';
  $output .= '<tr><td>' . t('KICK') . '</td><td>' . $player->field_player_kick->value() . '</td></tr>';
  $output .= '</tbody>';
  $output .= '</table>';


  if ($ajax == 'ajax') {

    $commands = array();

    // Ajax command to replace the 'ajax-searching' element with content
    $commands[] = ajax_command_replace('#game-search-player-values', '<div id="game-search-player-values">' . $output . '</div>');

    // Add a visual "changed" marker to the '#ajax-searching' element.
    $commands[] = ajax_command_changed('#game-search-player-values');

    // You have to return a renderable array for the page and ajax callback
    ajax_deliver(array(
      '#type' => 'ajax',
      '#commands' => $commands,
    ));
  }

  else {
    // No ajax, just display the content on a page using renderable array
    return array(
      '#markup' => $output,
    );
  }
}

/**
 * Theme function for the line up players form
 * @param $variables
 */
function theme_formball_game_line_up_form($variables) {
  $form = $variables['form'];
  $rows = array();

  // Iterate over each element in our $form['line-up-players'] array.
  foreach (element_children($form['line_up_players']) as $id) {
    //adding custom class so that it can be identified in the drupal_add_tabledrag call.
    $form['line_up_players'][$id]['weight']['#attributes']['class'] = array('line-up-players-weight');

    $rows[] = array(
      'data' => array(
        drupal_render($form['line_up_players'][$id]['position']),
        drupal_render($form['line_up_players'][$id]['name']),
        drupal_render($form['line_up_players'][$id]['weight']),
      ),
      // To support the tabledrag behaviour, we need to assign each row of the
      // table a class attribute of 'draggable'. This will add the 'draggable'
      // class to the <tr> element for that row when the final table is
      // rendered.
      'class' => array('draggable'),
    );
  }

  $header = array(t('Position'), t('Name'), t('Weight'));
  // id to pass to the drupal_add_tabledrag() function which will
  // be used to identify the <table> element containing our tabledrag form.
  $table_id = 'line-up-players-table';

  $form['line_up_players']['players_list']['table']['#markup'] = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));
  // render any remaining form elements (such as the field lineup).
  $output = drupal_render_children($form);

  // function in order to add the tabledrag.js functionality to the table.
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'line-up-players-weight');
  return $output;

}
