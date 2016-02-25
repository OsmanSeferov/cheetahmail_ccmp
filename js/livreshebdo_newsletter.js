(function($) {
  Drupal.behaviors.LivresHebdoNewsletterSubscriberForm = {
    attach: function(context, settings) {
      var handler = function() {
        return false;
      }

      // Customize comment form jQuery validator.
      // Other method and configs are provided by Clientside Validation module.
      $('div.form-newsletter form').each(function() {
        if(typeof $(this).validate == 'function') {
          $(this).validate({
            highlight: function(element, errorClass, validClass) {
            },
            unhighlight: function(element, errorClass, validClass) {
              $(element).parents().find("label[for=" + element.id + "]").find("span.warning-info").remove();
              $(element).parents().find("label[for=" + element.id + "]").find("span.error").removeClass('error').addClass('valide');
            },
            errorPlacement : function(error, element) {
              return false;
            },
            invalidHandler: function(form, validator) {
              $('div.form-newsletter form').find('label span').remove();
              for (i = 0; i < validator.errorList.length; i++) {
                var element = validator.errorList[i].element;
                var message = '<span class="error"><span class="warning-info"><span class="top"></span><span class="txt">' + validator.errorList[i].message + '</span></span></span>';
                $("label[for=" + element.id + "]").append(message);
              }
              $("div.form-newsletter .top .btn-check").unbind('click', handler);
            },
            submitHandler: function(form) {
              form.submit();
            }
          });
        }
      });
      $("a.open-popup").click(function() {
        var _lightbox = $("#newsletter-popup1");
        _lightbox.html(Drupal.t("Loading..."));
      });
      $("div.form-newsletter form .check-list .form-checkbox").change(function(){
        $(this).parent().parent().find("span.warning-info").remove();
        $(this).parent().parent().find("span.error").removeClass('error').addClass('valide');
      });
      $("div.form-newsletter form .row-submit input").mousedown(function(){
        $("div.form-newsletter .top .btn-check").bind('click', handler);
      });
    }
  };
  $.fn.afterLoadNewsletterContent = function() {
    var _lightbox = $("#newsletter-popup1");
    var _fader = $('div.lightbox-fader');
    _lightbox.shownFlag = true;
    $('.lightbox-fader').css('display', 'block'); 
    $('a.close').click(function() {
      _lightbox.fadeOut(400, function() {
        _fader.fadeOut(300);
        _lightbox.find('input[type="text"], input[type="password"]').val('');
        _lightbox.find('.messages').html('');
        _lightbox.find('span.error, span.valide').hide();
      });
      return false;
    });
    $.fn.simpleLightbox.positionLightbox(_lightbox);
  }
})(jQuery);

(function($) {
  $(document).ready(function() {
	// Automatic open popups.
	jQuery('a.automatic-open, a.newsleter-subscribe-popup').hide();
	setTimeout(function() {
	  jQuery('a.automatic-open').click();
	}, 500);

  if (window.location.hash) {
    var hash = window.location.hash.substring(1);
    if (hash == 'newsletter') {
      setTimeout(function() {
        jQuery('a.newsletter-subscribe-popup').click();
      }, 500);
    }
  }
});
})(jQuery);
