<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Add question link'),
  'description' => t('Display link to add question.'),
  'content_types' => array('diplom_add_group_question_link'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_add_group_question_link_render',
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
function diplom_add_group_question_link_render($subtype, $conf, $args, $context) {
  $gid = $context->data->gid;
  $pane = new stdClass();
  $pane->content = l(t('Add question'), "group/{$gid}/question-create");
  return $pane;
}
