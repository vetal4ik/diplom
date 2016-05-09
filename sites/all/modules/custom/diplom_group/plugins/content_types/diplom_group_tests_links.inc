<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Group tests'),
  'description' => t('Display tests of group.'),
  'content_types' => array('diplom_group_test'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_group_test_render',
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
function diplom_group_test_render($subtype, $conf, $args, $context) {
  $group = $context->data;
  $wr = entity_metadata_wrapper('group', $group);
  $test_types = array(
    'field_attestation_test' => t('Attestation test'),
    'field_skill_test' => t('Skill test'),
  );
  $items = array();
  foreach ($test_types as $type_name => $type_title) {
    $test = $wr->{$type_name}->value();
    if (empty($test)) {
      $title = t("Create '@type'.", array('@type' => $type_title));
      $path = "group/{$group->gid}/test/create";
      $options = array('query' => array('test_type' => str_replace('field_', '', $type_name)));
      $items[] = l($title, $path, $options);
    }
    else {
      $title = t("View '@type'.", array('@type' => $type_title));
      $path = "node/{$test->nid}";
      $items[] = l($title, $path);
    }
  }
  if (!empty($items)) {
    $pane = new stdClass();
    $pane->content = theme('item_list', array('items' => $items));
    return $pane;
  }
}
