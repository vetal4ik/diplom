<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Create question'),
  'description' => t('Form to create question.'),
  'content_types' => array('diplom_question_create'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_create_question_render',
  'edit form' => 'diplom_create_question_form',
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
function diplom_create_question_render($subtype, $conf, $args, $context) {
  $group = $context->data;

  // Create object to create question.
  $node = new stdClass;
  $node->type = 'multichoice';
  $node->language = LANGUAGE_NONE;

  // Necessary form state args to build form.
  $form_state = array();
  $form_state['build_info'] = array(
    'args' => array($node),
    'group' => $group,
  );

  // Use module_load_include so that caches and stuff can know to load this.
  form_load_include($form_state, 'inc', 'node', 'node.pages');
  
  $content_pane = new stdClass();
  $content_pane->content = drupal_build_form('multichoice_node_form', $form_state);
  return $content_pane;
}
