<?php
/**
 * @file
 * An array of preprocessors to fill variables for templates and helper
 * functions to make theming easier.
 */

/**
 * Preprocess 'livreshebdo_newsletter_popup2' theme.
 */
function template_preprocess_livreshebdo_newsletter_popup2(&$vars) {
  global $user;
  $vars['email'] = $user->mail;
  $vars['message'] = t('Thank you for your subscription.<br /> Letter will be sent to the address');
}

/**
 * Preprocess 'livreshebdo_newsletter_popup3' theme.
 */
function template_preprocess_livreshebdo_newsletter_popup3(&$vars) {
  $vars['message'] = t('Your request has been taken into account.<br /> We hope to see you again very soon among our subscribers.');
}
