<?php

/**
 * @file
 * Plugin to provide access control based for check empty field.
 */

/**
 * Plugins for check paid empty field.
 */
$plugin = array(
  'title' => t('Empty field'),
  'callback' => 'diplom_group_field_access_callback',
  'settings form' => 'diplom_group_field_form',
  'summary' => 'diplom_group_field_access_summary',
  'required context' => new ctools_context_required(t('Group'), 'group'),
);

/**
 * Settings form.
 */
function diplom_group_empty_field_form($form, &$form_state, $conf) {
  // User fields name.
  $options = db_select('field_config_instance', 'fci')
    ->fields('fci', array('field_name'))
    ->condition('fci.entity_type', 'group')
    ->condition('fci.deleted', 0)
    ->execute()
    ->fetchCol();

  $form['settings']['fields'] = array(
     '#type' => 'select',
     '#title' => t('Selected'),
     '#options' => array_combine($options, $options),
     '#multiple' => TRUE,
     '#default_value' => $conf['fields'],
   );
  return $form;
}

/**
 * Check for access.
 */
function diplom_group_field_access_callback($conf, $context) {
  $group = $context->data;
  foreach ($conf['fields'] as $field) {
    if(!empty($group->$field)) {
      return FALSE;
    }
  }
  return TRUE;
}

/**
 * Summary callback of the plugin.
 */
function diplom_group_field_access_summary($conf, $context) {
  return t('Empty field');
}
