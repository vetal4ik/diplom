<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Group members'),
  'description' => t('View with group members.'),
  'content_types' => array('diplom_group_members'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_group_members_render',
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
function diplom_group_members_render($subtype, $conf, $args, $context) {
  $group = $context->data;
  $view = views_embed_view('group_members', 'group_members_pane', $group->gid);
  if (!empty($view)) {
    $content_pane = new stdClass();
    $content_pane->content = $view;
    return $content_pane;
  }
}
