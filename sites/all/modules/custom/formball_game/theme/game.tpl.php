<div id="game-wrapper">
  <div id="game-board">
    <div id="game-elements">
      <?php

      foreach ($form as $key => $value) {
        if (strpos($key, 'player_') !== FALSE) {
          $checkbox = $form[$key];
          $checked = $checkbox['#value'] == 1 ? 'checked' : '';
          print $checkbox['#prefix'];
          print '<input id="' . $checkbox['#id'] .
            '" class="' . implode($checkbox['#attributes']['class']) .
            '" type="' . $checkbox['#type'] .
            '" value="' . $checkbox['#value'] .
            '" name="' . $checkbox['#name'] .
            '" ' . $checked .
            '></input>';
          print $form[$key]['#suffix'];

          // Hide the form elements from rendering after calling
          // drupal_render_children($form) at the bottom of this page
          hide($checkbox);
        }
      }


      $radios = $form['store']['#value'];
      unset($form['store']);

      foreach ($radios as $radio) {
          $ball = $form['ball'][$radio->id];
          print $radio->prefix;
          print '<input id="' . $ball['#id'] .
            '" type="' . $ball['#type'] .
            '" value="' . $ball['#value'] .
            '" name="' . $ball['#name'] .
            '></input>';
          print $radio->suffix;

          // Hide the form elements from rendering after calling
          // drupal_render_children($form) at the bottom of this page
          hide($form['ball']);
      }
      unset($radios);

      print ('<div style="position:relative;">');

      print ('</div>');

      ?>
    </div>
  </div>
  <?php print render($form['submit']); ?>
  <!-- Render any remaining elements, such as hidden inputs. -->
  <?php print drupal_render_children($form); ?>
</div>
