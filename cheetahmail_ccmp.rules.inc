<?php

/**
 * @file
 * Integration with the rules module
 */

/**
 * Implementation of hook_rules_action_info().
 *
 * @ingroup rules
 */
function livreshebdo_newsletter_rules_action_info() {
  return array(
    'livreshebdo_newsletter_flush_newsletters' => array(
      'base' => 'livreshebdo_newsletter_rules_action_flush_newsletter',
      'label' => t('Clear newsletter URL(s) from the page cache.'),
      'group' => 'LivresHebdo',
    ),
  );
}

/**
 * Expire a URL from the page cache.
 */
function livreshebdo_newsletter_rules_action_flush_newsletter($settings) {
  global $base_root, $base_path;

  if (!module_exists('expire')) {
    // During import process, expire is off
    return;
  }

  $query = new EntityFieldQuery;
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'newsletter_issue')
    ->fieldCondition('field_hidden_newsletter_sent', 'value', 0)
    ->execute();

  foreach ($result['node'] as $node) {
    $node = node_load($node->nid);
    expire_node($node);
  }
}
