/**
 * @file
 * JavaScript to autosubmit the game form after X ammount of time
 */

(function ($) {
  Drupal.behaviors.formball_game = {
    attach: function (context, settings) {
      // Autorefresh settings from the settings variables
      var $refresh = Drupal.settings.formball_refresh.autorefresh;
      var $refresh_time = Drupal.settings.formball_refresh.autorefresh_time * 1000;

      if($refresh == 1) {
        window.setInterval(function(){ submitform(); }, $refresh_time);
        function submitform(){
          document.forms["formball-game-form"].submit();
        }
      }
    }
  }
})(jQuery);


/* IKOS WAY
(function ($) {
  Drupal.behaviors.installAutoSubmit = {

    attach: function (context, settings) {

      // add onclick handler for auto-submit
      $('#edit-auto-submit').click(function() {
        var $this = $(this);

        if ($this.attr('checked')) {
          // auto-submit is now checked, so start the countdown
          $('#auto-submit-description').show();
          Drupal.behaviors.installAutoSubmit.tick();
        }
        else {
          // unchecked, so stop countdown
          var t = $('#auto-submit-countdown').data('t');
          clearTimeout(t);
          // hide the auto submit message
          $('#auto-submit-description').hide();
        }
      });

      // onclick handler for submit button
      $('#edit-submit').click(function() {
        var $this = $(this);

        // Replace the button with some text
        $this.val('Stand by...');

        // Hide the auto submit.
        $('.form-item-auto-submit').hide();

        // Submit the form
        $('form')[0].submit();

        // Disable the button.
        $this.attr("disabled","disabled");

        // Allow the click event to fall through.
        return true;
      });

      // Check all checkboxes.
      $('body').find(':checkbox').attr('checked', 'checked');

      // Un-check the Update module checkbox.
      $('#edit-update-status-module-1').attr( "checked", "" );

      // Start countdown.
      this.tick();
    },

    tick: function() {
      var seconds = parseInt($('#auto-submit-countdown').html());

      seconds -= 1;
      if (seconds <= 0) {
        $('#auto-submit-description').hide();
        $('#edit-submit').click();
      }
      else {
        $('#auto-submit-countdown').html(seconds);
        // Scheduling another call of this function in 1s
        var t = setTimeout(Drupal.behaviors.installAutoSubmit.tick, 1000);
        $('#auto-submit-countdown').data('t', t);
      }
    }

  }

})(jQuery);
*/

/* TOTAL

(function ($) {
  // Matching the segment boxes to have even height
  Drupal.behaviors.mymoduleSidrBehavior = {
    attach: function (context, settings) {

      var $segments = new Array();
      var $width = $(document).width();
      var $sm = 568;
      var $lg = 1024;

      // 2 rows, affecting the height of just the first 2 segment boxes
      if($width >= $sm && $width < $lg) {
        $segments.push($('#segment-1').height());
        $segments.push($('#segment-2').height());
        // Grab the largest value from the segments array
        var $max_height = Math.max.apply(Math, $segments);
        // and apply to segment boxes depending on the document size
        $('#segment-1').height($max_height);
        $('#segment-2').height($max_height);
      }
      // 1 row affecting the height of all segment boxes
      if($width >= $lg) {
        // grab all segment heights and save them into the segments array
        $('.segment-link').each(function() {
          $segments.push($(this).height());
        });
        // Grab the largest value from the segments array
        var $max_height = Math.max.apply(Math, $segments);
        // and apply to segment boxes depending on the document size
        $('.segment-link').each(function() {
          $(this).height($max_height);
        });
      }
    }};
})(jQuery);

*/