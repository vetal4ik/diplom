<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Group feedback link.'),
  'description' => t('Display feedback link of group.'),
  'content_types' => array('diplom_group_test_link'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_group_feedback_link_render',
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
function diplom_group_feedback_link_render($subtype, $conf, $args, $context) {
  $group = $context->data;
  $pane = new stdClass();
  $pane->content = theme('html_tag', array(
      'element' => array(
          '#tag' => 'div',
          '#attributes' => array(
              'class' => 'activities-sidbar',
          ),
          '#value' => l(t('Feedback'), "group/{$group->gid}/feedback"),
      ),
  ));
  return $pane;
}
