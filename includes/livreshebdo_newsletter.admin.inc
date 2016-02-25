<?php

/**
 * Cheetahmail configurations.
 */
function livreshebdo_newsletter_cheetahmail_config($form, &$form_state) {
  $form = array();
  $configs = array();
  $query = db_select('livreshebdo_newsletter_configs', 'lnc')
    ->fields('lnc', array('cid', 'name'));
  $results = $query->execute();
  foreach ($results as $id => $result) {
    $configs[$result->cid] = $result->name;
  }

  if (empty($configs)) {
    drupal_set_message(t('Not found any newsletter configuration. Please create a !link.', array('!link' => l(t('newsletter configuration'), LIVRESHEBDO_NEWSLETTER_ADD_CONFIG_URL))), 'error');
  }
  else {
    asort($configs);

    $form['livreshebdo_newsletter_cheetahmail_config_default'] = array(
      '#type' => 'select',
      '#title' => t('Newsletter configuration'),
      '#options' => $configs,
      '#required' => TRUE,
      '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_config_default', NULL),
    );

    $form['livreshebdo_newsletter_cheetahmail_config_filter'] = array(
      '#type' => 'textfield',
      '#title' => t('Filter ID'),
      '#required' => TRUE,
      '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_config_filter', 0),
    );

    $form['livreshebdo_newsletter_cheetahmail_speed'] = array(
      '#type' => 'select',
      '#title' => t('Speed'),
      '#options' => array(
        'SPEED_INCONNU' => t('Inconnu'),
        'SPEED_0100'    => '100',
        'SPEED_0250'    => '250',
        'SPEED_0500'    => '500',
        'SPEED_1000'    => '1000',
        'SPEED_2000'    => '2000',
        'SPEED_3000'    => '3000',
        'SPEED_4000'    => '4000',
        'SPEED_6000'    => '6000',
        'SPEED_7000'    => '7000',
        'SPEED_8000'    => '8000',
        'SPEED_10000'   => '10000',
        'SPEED_MAX'     => t('Max'),
      ),
      '#required' => TRUE,
      '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_speed', NULL),
      '#description' => t('Enumérateur Speed permettant de définir la vitesse d’envoi de la campagne. La vitesse est exprimée en mails/minute.'),
    );

    $form['livreshebdo_newsletter_cheetahmail_priority'] = array(
      '#type' => 'select',
      '#title' => t('Priority'),
      '#options' => array(
        '1' => t('Haute'),
        '3' => t('Normale'),
        '5' => t('Faible'),
      ),
      '#required' => TRUE,
      '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_priority', NULL),
    );
  }

  return system_settings_form($form);
}

/**
 * Cheetahmail access configuration.
 */
function livreshebdo_newsletter_cheetahmail_access($form, &$form_state) {
  $form = array();
  $form['livreshebdo_newsletter_cheetahmail_login'] = array(
    '#type' => 'textfield',
    '#title' => t('Login'),
    '#required' => TRUE,
    '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_login', NULL),
  );

  $form['livreshebdo_newsletter_cheetahmail_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#required' => TRUE,
    '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_password', NULL),
  );

  $form['livreshebdo_newsletter_cheetahmail_idmlist'] = array(
    '#type' => 'textfield',
    '#title' => t('Idmlist'),
    '#required' => TRUE,
    '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_idmlist', NULL),
  );

  $form['livreshebdo_newsletter_cheetahmail_wsdl_conf'] = array(
    '#type' => 'textfield',
    '#title' => t('wsdl, configs'),
    '#required' => TRUE,
    '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_wsdl_conf', NULL),
  );

  $form['livreshebdo_newsletter_cheetahmail_wsdl_camp'] = array(
    '#type' => 'textfield',
    '#title' => t('wsdl, campaigns'),
    '#required' => TRUE,
    '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_wsdl_camp', NULL),
  );

  $form['livreshebdo_newsletter_cheetahmail_proxy_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Proxy Host'),
    '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_proxy_host', NULL),
  );

  $form['livreshebdo_newsletter_cheetahmail_proxy_port'] = array(
    '#type' => 'textfield',
    '#title' => t('Proxy Port'),
    '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_proxy_port', NULL),
  );

  $form['livreshebdo_newsletter_cheetahmail_debug_ws'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable trace of SOAP calls'),
    '#default_value' => variable_get('livreshebdo_newsletter_cheetahmail_debug_ws', 0),
  );

  return system_settings_form($form);
}

/**
 * Front office interface for newsletter configurations.
 */
function livreshebdo_newsletter_configs_list() {
  $query = db_select('livreshebdo_newsletter_configs', 'lnc')
    ->fields('lnc', array('cid', 'name', 'configs'));
  $results = $query->execute();

  $configs = array();
  foreach ($results as $id => $result) {
    $setting = array(t('<em>@name:</em> "@conf"', array('@name' => 'name', '@conf' => $result->name)));
    if (isset($result->configs) && !empty($result->configs)) {
      foreach (unserialize($result->configs) as $name => $conf) {
        if (in_array($name, array('miroir', 'isDkim'))) {
          $conf = $conf ? 'true' : 'false';
        }
      	if (!empty($conf)) {
      	  $setting[] = t('<em>@name:</em> "@conf"', array('@name' => $name, '@conf' => $conf));
      	}
      }
    }
    $configs[] = array(
      'name' => '<strong>' . $result->name . '</strong>',
      'configs' => theme('item_list', array('items' => $setting)),
      'operations' => theme('item_list', array('items' => array(
        l(t('Edit'), 'admin/config/livreshebdo/newsletter/settings/config/' . $result->cid . '/edit'),
        l(t('Delete'), 'admin/config/livreshebdo/newsletter/settings/config/' . $result->cid . '/delete')
      ))),
    );
  }

  return array(
    '#prefix' => '<div class="clearfix newsletter-configs">' . l('Add newsletter configuration', LIVRESHEBDO_NEWSLETTER_ADD_CONFIG_URL, array('attributes' => array('class' => array('livreshebdo-add-node')))) . '</div>',
    '#theme' => 'table',
    '#header' => array(
      'name' => t('Name'),
      'configs' => t('Configurations'),
      'operations' => NULL,
    ),
    '#rows' => $configs,
    '#empty' => t('No configurations are available'),
  );
}

function livreshebdo_newsletter_config_form($form, &$form_state, $cid = FALSE) {
  $form['#tree'] = TRUE;
  $defaults = NULL;
  if ($cid) {
    $defaults = livreshebdo_newsletter_load_config($cid);
  }

  $form['configs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configurations'),
  );

  $configs = array_merge(
    _livreshebdo_newsletter_cheetahmail_get_default_config_params(),
    isset($defaults->configs) ? unserialize($defaults->configs) : array()
  );

  $configs['name'] = isset($defaults->name) ? $defaults->name : $configs['name'];

  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#maxlength' => 1024,
    '#required' => TRUE,
    '#default_value' => isset($configs['name']) ? $configs['name'] : NULL,
    '#description' => t('Description de la configuration d’envoi'),
  );

  $form['configs']['idMlist'] = array(
    '#type' => 'textfield',
    '#title' => t('idMlist'),
    '#element_validate' => array('element_validate_integer'),
    '#default_value' => isset($configs['idMlist']) ? $configs['idMlist'] : NULL,
    '#required' => TRUE,
    '#description' => t('Identifiant de votre base de données Emailingsolution'),
  );

  if ($configs['idConf'] != -1 && $cid) {
    $form['configs']['idConf'] = array(
      '#type' => 'hidden',
      '#value' => $configs['idConf'],
    );

    $form['configs']['idConf_markup'] = array(
      '#type' => 'item',
      '#required' => TRUE,
      '#title' => t('idConf'),
      '#description' => t('Identifiant de la configuration d’envoi.'),
      '#markup' => $configs['idConf']
    );
  }
  else {
    $form['configs']['idConf'] = array(
      '#type' => 'textfield',
      '#title' => t('idConf'),
      '#element_validate' => array('element_validate_integer'),
      '#default_value' => isset($configs['idConf']) ? $configs['idConf'] : NULL,
      '#required' => TRUE,
      '#description' => t('Identifiant de la configuration d’envoi. Comme il s’agit d’une création, il faut indiquer -1'),
    );
  }

  $form['configs']['mailFrom'] = array(
    '#type' => 'textfield',
    '#title' => t('mailFrom'),
    '#default_value' => isset($configs['mailFrom']) ? $configs['mailFrom'] : NULL,
    '#description' => t('Nom de l’émetteur de la newsletter (s’affiche à la place du mail de provenance)'),
  );

  $form['configs']['mailFromAddr'] = array(
    '#type' => 'textfield',
    '#title' => t('mailFromAddr'),
    '#default_value' => isset($configs['mailFromAddr']) ? $configs['mailFromAddr'] : NULL,
    '#description' => t('Adresse email de provenance'),
    '#required' => TRUE,
  );

  $form['configs']['mailRetNpai'] = array(
    '#type' => 'textfield',
    '#title' => t('mailRetNpai'),
    '#default_value' => isset($configs['mailRetNpai']) ? $configs['mailRetNpai'] : NULL,
    '#description' => t('Adresse email qui sera utilisée pour renvoyer les retours NPAI non gérés par EmailingSolution'),
    '#required' => TRUE,
  );

  $form['configs']['mailReply'] = array(
    '#type' => 'textfield',
    '#title' => t('mailReply'),
    '#default_value' => isset($configs['mailReply']) ? $configs['mailReply'] : NULL,
    '#description' => t('Adresse email de réponse utilisée pour la fonction «reply»'),
    '#required' => TRUE,
  );

  $form['configs']['mailTo'] = array(
    '#type' => 'textfield',
    '#title' => t('mailTo'),
    '#default_value' => isset($configs['mailTo']) ? $configs['mailTo'] : NULL,
    '#description' => t('Chaîne de caractères qui remplacera dans certains logiciels de messagerie l’adresse email du destinataire'),
  );

  $form['configs']['mailDep'] = array(
    '#type'           => 'hidden',
    '#default_value'  => 'RET',
    '#value'          => 'RET'
  );

  $form['configs']['verpSend'] = array(
    '#type' => 'select',
    '#title' => t('verpSend'),
    '#options' => array(
      'Complet' => 'Complet',
      'Sauf_ReplyTo' => 'Sauf ReplyTo',
      'ReturnPath_Seulement' => 'ReturnPath Seulement',
      'Pas_de_traitement' => 'Pas de traitement',
    ),
    '#default_value' => isset($configs['mailDep']) ? $configs['mailDep'] : NULL,
    '#description' => t('Permet de personnaliser l’adresse de redirection fournie par EmailingSolution'),
    '#required' => TRUE,
  );

  $form['configs']['charset'] = array(
    '#type' => 'select',
    '#title' => t('charset'),
    '#options' => array(
      'ISO_2022_jp' => 'ISO_2022_jp',
      'ISO_2022_kr' => 'ISO_2022_kr',
      'ISO_8859_1' => 'ISO_8859_1',
      'ISO_8859_2' => 'ISO_8859_2',
      'ISO_8859_3' => 'ISO_8859_3',
      'ISO_8859_4' => 'ISO_8859_4',
      'ISO_8859_5' => 'ISO_8859_5',
      'ISO_8859_6' => 'ISO_8859_6',
      'ISO_8859_7' => 'ISO_8859_7',
      'ISO_8859_8' => 'ISO_8859_8',
      'ISO_ir_58' => 'ISO_ir_58',
      'ISO_8859_11' => 'ISO_8859_11',
      'UTF_8' => 'UTF_8',
    ),
    '#default_value' => isset($configs['charset']) ? $configs['charset'] : NULL,
    '#description' => t('Correspond à l’encodage qui sera utilisé pour l’envoi de la newsletter'),
    '#required' => TRUE,
  );

  $form['configs']['miroir'] = array(
    '#type' => 'checkbox',
    '#title' => t('miroir'),
    '#default_value' => isset($configs['miroir']) ? $configs['miroir'] : NULL,
    '#description' => t('Indique si le header de la newsletter sera affiché dans la page miroir'),
  );

  $form['configs']['isDkim'] = array(
    '#type' => 'checkbox',
    '#title' => t('isDkim'),
    '#default_value' => isset($configs['isDkim']) ? $configs['isDkim'] : NULL,
    '#description' => t('Indiquez TRUE pour les base DKIM'),
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  if ($cid) {
    $form['#cid'] = $cid;
    $form['cid'] = array(
      '#type' => 'hidden',
      '#value' => $cid,
    );

    $form['actions']['update'] = array(
      '#value' => t('Update'),
      '#type' => 'submit',
    );
    $form['actions']['delete'] = array(
      '#value' => t('Delete'),
      '#type' => 'submit',
      '#suffix' => l(t('Cancel'), 'admin/config/livreshebdo/newsletter/settings'),
      '#attributes' => array('class' => array('button-no')),
      '#weight' => 100,
    );
  }
  else {
    $form['actions']['create'] = array(
      '#value' => t('Create'),
      '#type' => 'submit',
      '#suffix' => l(t('Cancel'), 'admin/config/livreshebdo/newsletter/settings'),
    );
  }

  return $form;
}

function livreshebdo_newsletter_config_form_validate($form, &$form_state) {

  $clicked_button = $form_state['clicked_button']['#value'];

  if (in_array($clicked_button, array(t('Update'), t('Create')))) {
    $client = livreshebdo_newsletter_cheetahmail_client(LIVRESHEBDO_NEWSLETTER_CHEETAHMAIL_TYPE_CONFIG);
    if (!$client) {
      form_set_error('form', t('Unable to connect to Cheetahmail'));
      return;
    }

    $configs = _livreshebdo_newsletter_cheetahmail_get_default_config_params();
    $configs['name'] = $form_state['values']['name'];

    foreach ($form_state['values']['configs'] as $name => $conf) {
      if (in_array($name, array('miroir', 'isDkim'))) {
        $conf = $conf ? TRUE : FALSE;
        $configs[$name] = $conf;
      }
      if (!empty($conf)) {
        $configs[$name] = $conf;
      }
    }

    $params = array('_config' => $configs);

    $tracing_is_enabled = variable_get('livreshebdo_newsletter_cheetahmail_debug_ws', 0);

    switch ($clicked_button) {
      case t('Update') : $method = 'UpdateConfig'; break;
      case t('Create') : $method = 'CreateConfig'; break;
    }

    try {
      $result = $client->$method($params);

      if ($clicked_button == t('Create')) {
        $form_state['values']['configs']['idConf'] = $result->CreateConfigResult;
      }
      else {
        if (!$result->UpdateConfigResult) {
          form_set_error('form', t('Unable to update config: cheetahmail returned an error'));
        }
      }

      if ($tracing_is_enabled) {
        watchdog(
          LIVRESHEBDO_NEWSLETTER_LOG,
          'Cheetahmail: @button config result: !value. Request: !request, response: !response',
          array(
            '@button'   => $clicked_button,
            '!value'    => print_r($result->CreateConfigResult, TRUE),
            '!request'  => htmlentities($client->__getLastRequest()),
            '!response' => htmlentities($client->__getLastResponse())
          )
        );
      }
    }
    catch(SoapFault $e) {
      form_set_error('form', t('Unable to @button config: cheetahmail returned an error @error', array('@error' => $e->getMessage(), '@button' => $clicked_button)));
      watchdog(
        LIVRESHEBDO_NEWSLETTER_LOG,
        'Cheetahmail error: !error. Request: !request, response: !response',
        array(
          '!error'    => $e->getMessage(),
          '!request'  => $tracing_is_enabled ? htmlentities($client->__getLastRequest()) : 'Tracing is disabled',
          '!response' => $tracing_is_enabled ? htmlentities($client->__getLastResponse()): 'Tracing is disabled'
        ),
        WATCHDOG_ERROR
      );
    }

  }
}

function livreshebdo_newsletter_config_form_submit($form, &$form_state) {
  if (isset($form_state['clicked_button']['#value']) && !empty($form_state['clicked_button']['#value'])) {

    switch ($form_state['clicked_button']['#value']) {
      case t('Create'):
        db_insert('livreshebdo_newsletter_configs')
          ->fields(array(
            'name' => $form_state['values']['name'],
            'configs' => serialize($form_state['values']['configs']),
          ))
          ->execute();
        watchdog('livreshebdo_newsletter_configs', 'Newsletter configuration "@name" was created.', array('@name' => $form_state['values']['name']));
        drupal_set_message(t('Newsletter configuration "@name" was created.', array('@name' => $form_state['values']['name'])));
        break;

      case t('Update'):
        db_update('livreshebdo_newsletter_configs')
          ->fields(array(
            'name' => $form_state['values']['name'],
            'configs' => serialize($form_state['values']['configs']),
          ))
          ->condition('cid', $form_state['values']['cid'])
          ->execute();
        watchdog('livreshebdo_newsletter_configs', 'Newsletter configuration "@name" was updated.', array('@name' => $form_state['values']['name']));
        drupal_set_message(t('Newsletter configuration "@name" was updated.', array('@name' => $form_state['values']['name'])));
        break;

      case t('Delete'):
        $form_state['redirect'] = 'admin/config/livreshebdo/newsletter/settings/config/' . $form_state['values']['cid'] . '/delete';
        break;

      default:
        drupal_set_message(t('Operation @op not found.', array('@op' => $form_state['clicked_button']['#value'])));
        break;
    }
  }
  if (!isset($form_state['redirect'])) {
    $form_state['redirect'] = 'admin/config/livreshebdo/newsletter/settings';
  }
}

function livreshebdo_newsletter_config_delete_confirm($form, &$form_state, $cid) {
  $name = db_select('livreshebdo_newsletter_configs')
    ->fields('livreshebdo_newsletter_configs', array('name'))
    ->condition('cid', $cid)
    ->range(0, 1)
    ->execute()
    ->fetchField();

  $form['#cid'] = $cid;
  $form['#name'] = $name;

  $form['cid'] = array('#type' => 'value', '#value' => $cid);
  return confirm_form($form,
    t('Are you sure you want to delete "@title"?', array('@title' => $name)),
    'admin/config/livreshebdo/newsletter/settings',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

function livreshebdo_newsletter_config_delete_confirm_validate($form, &$form_state) {
  if ($client = livreshebdo_newsletter_cheetahmail_client(LIVRESHEBDO_NEWSLETTER_CHEETAHMAIL_TYPE_CONFIG)) {

    $cid = $form['#cid'];

    $defaults = livreshebdo_newsletter_load_config($cid);

    if (!$defaults->configs) {
      form_set_error('form', t('Configuration was not found'));
    }

    $configs = unserialize($defaults->configs);

    $params = array('_IdConf'=> $configs['idConf']);

    $tracing_is_enabled = variable_get('livreshebdo_newsletter_cheetahmail_debug_ws', 0);

    try {
      $result = $client->DeleteConfig($params);

      if (!$result->DeleteConfigResult) {
        form_set_error('form', t('Unable to delete config: cheetahmail returned an error'));
      }

      if ($tracing_is_enabled) {
        watchdog(
          LIVRESHEBDO_NEWSLETTER_LOG,
          'Cheetahmail: delete config result: !value. Request: !request, response: !response',
          array(
            '!value'    => print_r($result->DeleteConfigResult, TRUE),
            '!request'  => htmlentities($client->__getLastRequest()),
            '!response' => htmlentities($client->__getLastResponse())
          )
        );
      }
    }
    catch(SoapFault $e) {
      form_set_error('form', t('Unable to delete config: cheetahmail returned an error @error', array('@error' => $e->getMessage())));
      watchdog(
        LIVRESHEBDO_NEWSLETTER_LOG,
        'Cheetahmail error: !error. Request: !request, response: !response',
        array(
          '!error'    => $e->getMessage(),
          '!request'  => $tracing_is_enabled ? htmlentities($client->__getLastRequest()) : 'Tracing is disabled',
          '!response' => $tracing_is_enabled ? htmlentities($client->__getLastResponse()): 'Tracing is disabled'
        ),
        WATCHDOG_ERROR
      );
    }
  }
  else {
    form_set_error('form', t('Unable to connect to Cheetahmail'));
  }
}

function livreshebdo_newsletter_config_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {

    db_delete('livreshebdo_newsletter_configs')
      ->condition('cid', $form['#cid'])
      ->execute();
    watchdog('livreshebdo_newsletter_configs', 'Newsletter configuration "@name" was deleted.', array('@name' => $form['#name']));
    drupal_set_message(t('Newsletter configuration "@name" was deleted.', array('@name' => $form['#name'])));
  }

  $form_state['redirect'] = 'admin/config/livreshebdo/newsletter/settings';
}
