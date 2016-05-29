<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Group feedback'),
  'description' => t('Show feedback.'),
  'content_types' => array('diplom_group_feedback'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_group_feedback_render',
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
function diplom_group_feedback_render($subtype, $conf, $args, $context) {
  global $user;
  $group = entity_metadata_wrapper('group', $context->data);
  $test = $group->field_skill_test->value();
  $result = entity_load('quiz_result', FALSE, array(
    'nid' => $test->nid,
    'uid' => $user->uid,
    'is_evaluated' => TRUE,
  ));
  if (empty($result)) {
    $output = l(t('Please pass test.'), "group/{$group->gid}");
  }
  else {
    $result = reset($result);
    $feedback_node = $group->field_group_feedback->value();
    $wr_feedback = entity_metadata_wrapper('node', $feedback_node);
    $ranges = $wr_feedback->field_feedback->value();
    foreach ($ranges as $range) {
      $range = entity_metadata_wrapper('field_collection_item', $range);
      $from = $range->field_feedback_from->value();
      $to = $range->field_feedback_to->value();
      $result->score;
      if ($from <= $result->score && $result->score <= $to) {
        $output = $range->field_feedback_body->value();
      }
    }
  }


  $pane = new stdClass();
  $pane->content = $output;
  return $pane;
}
