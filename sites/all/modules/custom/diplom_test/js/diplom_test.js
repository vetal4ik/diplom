(function ($) {

// Store our function as a property of Drupal.behaviors.
    Drupal.behaviors.testTimer = {
        attach: function (context, settings) {
            var seconds = $('.test-timer .value').text();
            var form = $('.test-timer .value').parents('form');
            $('.test-timer .value').countdown({
                until: seconds,
                layout: '{hn}:{mn}:{sn}',
                onExpiry: function () {
                    $('input[name="finish"]', form).click();
                }
            });
        }
    }

}(jQuery));