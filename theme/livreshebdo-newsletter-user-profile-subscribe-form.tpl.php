<?php
/**
 * @file
 * Default theme implementation to display a subscribe form.
 */
?>
<?php print render($form['newsletter_subscription']); ?>
<div class="bottom-form">
  <?php print render($form['newsletter_save']); ?>
</div>
<?php print drupal_render_children($form); ?>
