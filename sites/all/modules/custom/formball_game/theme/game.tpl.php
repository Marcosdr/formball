<div id="game-wrapper">
  <div id="game-board">
    <div id="game-elements">
      <?php

      foreach ($form as $key => $checkbox) {
        if (strpos($key, 'box_') !== FALSE) {
          print render($form[$key]);
        }
      }

      foreach($form['ball'] as $key => $ball) {
        if (strpos($key, 'ball_') !== FALSE) {
          print render($form['ball'][$key]);
        }
      }
      hide($form['ball']);

      ?>
    </div>
  </div>
  <?php print render($form['submit']); ?>
  <!-- Render any remaining elements, such as hidden inputs. -->
  <?php print drupal_render_children($form); ?>
</div>
