<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Add course'),
  'description' => t('Display link to add course.'),
  'content_types' => array('diplom_add_group_link'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_add_group_link_render',
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
function diplom_add_group_link_render($subtype, $conf, $args, $context) {
  $pane = new stdClass();
  $pane->content = l(t('Add course'), 'group/add/courses');
  return $pane;
}
