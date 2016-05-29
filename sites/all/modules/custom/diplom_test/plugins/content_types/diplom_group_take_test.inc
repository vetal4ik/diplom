<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Group take test'),
  'description' => t('Form to take test.'),
  'content_types' => array('diplom_quiz_take_group'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_group_take_test_render',
  'edit form' => 'diplom_group_take_test_form',
  'required context' => new ctools_context_required(t('Group'), 'group'),
);

/**
 * 'Edit form' callback for the content type.
 */
function diplom_group_take_test_form($form, &$form_state) {
  $allowed_types = list_allowed_values(field_info_field('field_test_type'));
  $conf = $form_state['conf'];
  $form['test_type'] = array(
    '#type' => 'select',
    '#title' => t('Test type'),
    '#options' => $allowed_types,
    '#required' => TRUE,
    '#default_value' => isset($conf['test_type']) ? $conf['test_type'] : '',
  );

  return $form;
}

/**
 * Submit callback for the example_text_edit_form().
 */
function diplom_group_take_test_form_submit($form, &$form_state) {
  $form_state['conf']['test_type'] = $form_state['values']['test_type'];
}

/**
 * Render callback function.
 *
 * @param mixed $subtype
 *   Content subtype; not used.
 * @param mixed $conf
 *   Pane configuration.
 * @param mixed $args
 *   Arguments? Whatever. Not used.
 * @param mixed $context
 *   Not used.
 *
 * @return object
 *   Rendered pane.
 */
function diplom_group_take_test_render($subtype, $conf, $args, $context) {
  global $user;
  $content_pane = new stdClass();
  $content_pane->content = '';

  $group = entity_metadata_wrapper('group', $context->data);
  $field = 'field_' . $conf['test_type'];
  $test = $group->{$field}->value();
  $result = diplom_test_get_user_result($test, $user->uid);
  if ($result->is_evaluated) {
    $output = t('Your score: @score', array('@score' => $result->score));
  }
  else {
    $form_state = array();
    $form_state['build_info'] = array(
      'args' => array(),
      'test' => $test,
      'result' => $result,
    );
    $output = drupal_build_form('diplom_test_task_form', $form_state);
  }
  $content_pane = new stdClass();
  $content_pane->content = $output;
  return $content_pane;
}
