<?php
/**
 * @file
 * Default theme implementation to display a subscribe form.
 */
?>
<div class="cols">
  <div class="col">
    <div class="row">
      <label for="<?php print $form['newsletter_first_name']['#id']; ?>"><?php print $form['newsletter_first_name']['#title']; ?> <span title="<?php print t('This field is required.'); ?>" class="form-required">*</span></label>
      <div class="text-form">
        <?php print render($form['newsletter_first_name']); ?>
      </div>
    </div>
    <div class="row">
      <label for="<?php print $form['newsletter_email']['#id']; ?>"><?php print $form['newsletter_email']['#title']; ?> <span title="<?php print t('This field is required.'); ?>" class="form-required">*</span></label>
      <div class="text-form">
        <?php print render($form['newsletter_email']); ?>
      </div>
    </div>
    <div class="row">
      <label for="<?php print $form['newsletter_password']['#id']; ?>"><?php print $form['newsletter_password']['#title']; ?> <span title="<?php print t('This field is required.'); ?>" class="form-required">*</span></label>
      <div class="text-form">
        <?php print render($form['newsletter_password']); ?>
      </div>
    </div>
  </div>
  <div class="col ar">
    <div class="row">
      <label for="<?php print $form['newsletter_last_name']['#id']; ?>"><?php print $form['newsletter_last_name']['#title']; ?> <span title="<?php print t('This field is required.'); ?>" class="form-required">*</span></label>
      <div class="text-form">
        <?php print render($form['newsletter_last_name']); ?>
      </div>
    </div>
    <div class="row">
      <label for="<?php print $form['newsletter_email_confirm']['#id']; ?>"><?php print $form['newsletter_email_confirm']['#title']; ?> <span title="<?php print t('This field is required.'); ?>" class="form-required">*</span></label>
      <div class="text-form">
        <?php print render($form['newsletter_email_confirm']); ?>
      </div>
    </div>
    <div class="row">
      <label for="<?php print $form['newsletter_password_confirm']['#id']; ?>"><?php print $form['newsletter_password_confirm']['#title']; ?> <span title="<?php print t('This field is required.'); ?>" class="form-required">*</span></label>
      <div class="text-form">
        <?php print render($form['newsletter_password_confirm']); ?>
      </div>
    </div>
  </div>
</div>
<ul class="check-list">
  <li>
    <?php print render($form['newsletter_confirm']); ?>
    <label for="<?php print $form['newsletter_confirm']['#id']; ?>"><?php print $form['newsletter_confirm']['#title']; ?></label>
  </li>
  <li>
    <?php print render($form['newsletter_terms']); ?>
    <label for="<?php print $form['newsletter_terms']['#id']; ?>"><?php print $form['newsletter_terms']['#title']; ?></label>
  </li>
</ul>
<div class="row-submit">
  <?php print render($form['newsletter_submit']); ?>
</div>
<?php print drupal_render_children($form); ?>
