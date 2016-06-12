<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Group links.'),
  'description' => t('Display links of group.'),
  'content_types' => array('diplom_group_link'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_group_links_render',
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
function diplom_group_links_render($subtype, $conf, $args, $context) {
  global $user;
  $gid = $context->data->gid;
  $group_membership = $context->data->getMember($user->uid);
  $items = array(
    'skill-test' => l(t('Skill test'), "group/{$gid}/skill-test"),
    'attestation-test' => l(t('Attestation test'), "group/{$gid}/attestation-test"),
    'feedback' => l(t('Feedback'), "group/{$gid}/feedback"),
  );
  if (in_array('teacher', $group_membership->roles)) {
    $items['questions'] = l(t('Questions'), "group/{$gid}/questions");
  }

  $pane = new stdClass();
  $pane->content = theme('item_list', array('items' => $items));
  return $pane;
}
