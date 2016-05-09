<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Group test result(chart)'),
  'description' => t('Result chart.'),
  'content_types' => array('diplom_quiz_group_result_chart'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_group_test_render',
  'edit form' => 'diplom_create_question_form',
  'required context' => new ctools_context_required(t('Group'), 'group'),
);

/**
 * 'Edit form' callback for the content type.
 */
function diplom_group_test_result_cahart_form($form, &$form_state) {
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
function diplom_create_question_form_submit($form, &$form_state) {
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
function diplom_group_test_render($subtype, $conf, $args, $context) {
  $group = $context->data;
  $wr = entity_metadata_wrapper('group', $group);
  $field_name = "field_{$conf['test_type']}";
  if (!($node = $wr->{$field_name}->value())) {
    // Create object to create question.
    $node = new stdClass;
    $node->type = 'quiz';
    $node->language = LANGUAGE_NONE;
  }

  // Necessary form state args to build form.
  $form_state = array();
  $form_state['build_info'] = array(
    'args' => array($node),
    'test_type' => $conf['test_type'],
    'group' => $group,
  );

  // Use module_load_include so that caches and stuff can know to load this.
  form_load_include($form_state, 'inc', 'node', 'node.pages');
  $content_pane = new stdClass();
  $content_pane->content = drupal_build_form('quiz_node_form', $form_state);
  return $content_pane;
}
