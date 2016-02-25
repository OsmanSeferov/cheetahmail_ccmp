<?php
/**
 * @file
 * newsletter_ct.features.inc
 */

/**
 * Implements hook_node_info().
 */
function newsletter_ct_node_info() {
  $items = array(
    'newsletter' => array(
      'name' => t('Newsletter'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
