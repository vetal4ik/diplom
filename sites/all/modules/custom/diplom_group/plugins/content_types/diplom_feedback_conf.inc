<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Group feedback conf'),
  'description' => t('Form to create/edit group feedback.'),
  'content_types' => array('diplom_group_feedback_conf'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_group_feedback_conf_render',
  'required context' => new ctools_context_required(t('Group'), 'group'),
);


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
function diplom_group_feedback_conf_render($subtype, $conf, $args, $context) {
  $group = $context->data;
  $wr = entity_metadata_wrapper('group', $group);

  if (!($feedback = $wr->field_group_feedback->value())) {
    // Create object to create question.
    $feedback = new stdClass;
    $feedback->type = 'feedback';
    $feedback->language = LANGUAGE_NONE;
  }

  // Necessary form state args to build form.
  $form_state = array();
  $form_state['build_info'] = array(
    'args' => array($feedback),
    'group' => $group,
  );
  form_load_include($form_state, 'inc', 'node', 'node.pages');

  $pane = new stdClass();
  $pane->content = drupal_build_form('feedback_node_form', $form_state);
  return $pane;
}
