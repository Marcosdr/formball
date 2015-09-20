(function ($) {
  // Matching the segment boxes to have even height
  Drupal.behaviors.formball_game = {
    attach: function (context, settings) {

      // Function to search for a game, if it hasn't found any within X ammount of seconds
      // Then send a message for game not found
      // if it has, redirect players to the appropriate page
      $.fn.start_game = function(path) {
        //alert(path);
        //setTimeout(function() {
        //
        //}, 3000)
      }

    }};
})(jQuery);
