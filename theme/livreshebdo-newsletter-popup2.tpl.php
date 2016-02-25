<?php
/**
 * @file
 * Default theme implementation to display a newsletter subscribe popup.
 */
?>
<a class="open-popup automatic-open" href="#newsletter-popup2"></a>
<div class="newsletter-popup" id="newsletter-popup2">
  <a href="#" class="close">close</a>
  <h3><?php print t('Subscribe to newsletter'); ?></h3>
  <p><?php print $message; ?></p>
  <p><a href="mailto:<?php print $email; ?>"><?php print $email; ?></a></p>
  <div class="btn">
    <a class="btn-close" href="#"><?php print t('Close'); ?></a>
  </div>
</div>
