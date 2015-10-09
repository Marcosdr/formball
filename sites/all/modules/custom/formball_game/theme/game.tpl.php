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


//      foreach ($form['boxes']['#value'] as $key=>$box){
//
//        $checked = $form[$box->getName()]['#value'] == 1 ? 'checked' : '';
//        print '
//                <div class="' . $box->getName() .'" style="' .
//          'position: absolute; ' .
//          'top: ' . $box->pos_y . '%; ' .
//          'left: '. $box->pos_x . '%;">' .
//          '<input id="' . $form[$box->getName()]['#id'] .
//          '" class="' . implode(" ", $form[$box->getName()]['#attributes']['class']) .
//          '" type="' . $form[$box->getName()]['#type'] .
//          '" value="' . $form[$box->getName()]['#value'] .
//          '" name="' . $form[$box->getName()]['#name'] .
//          '" ' . $checked .
//          '></input>' .
//          '<label for="' . $form[$box->getName()]['#id'] . '"><span></span></label>' .
//          '</div>';
//         // Hide the form elements from rendering after calling
//         // drupal_render_children($form) at the bottom of this page
//        hide($form[$box->getName()]);
//      }

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



//      foreach ($form['ball']['#value'] as $key=>$ball){
//        print '
//            <div class="' . $ball->getName() . '" style="' .
//          'position: absolute; ' .
//          'top: ' . $ball->pos_y . '%; ' .
//          'left: '. $ball->pos_x . '%;">' .
//
//          '<input id="' . $form['ball'][$ball->getName()]['#id'] .
//          '" type="' . $form['ball'][$ball->getName()]['#type'] .
//          '" value="' . $form['ball'][$ball->getName()]['#value'] .
//          '" name="' . $form['ball'][$ball->getName()]['#name'] .
//          '"></input>' .
//          '<label for="' . $form['ball'][$ball->getName()]['#id'] . '"></label>' .
//
//          '</div>';
//        hide($form['ball']);
//      }


      print ('<div style="position:relative;">');

      print ('</div>');

      ?>
    </div>
  </div>
  <?php print render($form['submit']); ?>
  <!-- Render any remaining elements, such as hidden inputs. -->
  <?php print drupal_render_children($form); ?>
</div>
