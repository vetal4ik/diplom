<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Create test'),
  'description' => t('Forn to create test.'),
  'content_types' => array('diplom_quiz_create', 'diplom_quiz_edit'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_create_test_render',
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
function diplom_create_test_render($subtype, $conf, $args, $context) {
 $group = $context->data;
  
  module_load_include('inc', 'node', 'node.pages');
  $node = new stdClass;
  $node->type = 'quiz';
  $node->language = LANGUAGE_NONE;

  $form_state = array();
  $form_state['build_info'] = array(
    'args' => array($node),
    'group' => $group,
  );

  $content_pane = new stdClass();
  $content_pane->content = drupal_build_form('diplom_test_action_form', $form_state);
//  $content_pane->content = 'aaa';
  return $content_pane;
}
