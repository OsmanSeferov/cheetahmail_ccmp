<?php
/**
 * @file
 * Default theme implementation to display a newsletter subscribe popup.
 */
?>
<a class="open-popup automatic-open" href="#newsletter-popup3"></a>
<div class="newsletter-popup" id="newsletter-popup3">
  <a href="#" class="close">close</a>
  <h3><?php print t('Unsubscribe from newsletter'); ?></h3>
  <p><?php print $message; ?></p>
  <div class="btn">
    <a class="btn-close" href="#"><?php print t('Close'); ?></a>
  </div>
</div>
