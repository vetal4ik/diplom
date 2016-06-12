<?php

/**
 * @file
 * Ctools content type plugin file.
 */

// Read by ctools.
$plugin = array(
  'title' => t('Group test result(chart)'),
  'description' => t('Result chart.'),
  'content_types' => array('diplom_quiz_group_result_chart'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_group_test_result_chart_render',
  'edit form' => 'diplom_group_test_result_chart_form',
  'required context' => new ctools_context_required(t('Group'), 'group'),
);

/**
 * 'Edit form' callback for the content type.
 */
function diplom_group_test_result_chart_form($form, &$form_state) {
  $allowed_types = list_allowed_values(field_info_field('field_test_type'));
  $conf = $form_state['conf'];
  $form['test_type'] = array(
    '#type' => 'select',
    '#title' => t('Test type'),
    '#options' => $allowed_types,
    '#required' => TRUE,
    '#default_value' => isset($conf['test_type']) ? $conf['test_type'] : '',
  );

  return $form;
}

/**
 * Submit callback for the example_text_edit_form().
 */
function diplom_group_test_result_chart_form_submit($form, &$form_state) {
  $form_state['conf']['test_type'] = $form_state['values']['test_type'];
}

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
function diplom_group_test_result_chart_render($subtype, $conf, $args, $context) {
  $group = $context->data;
  $wr = entity_metadata_wrapper('group', $group);
  $field_name = "field_{$conf['test_type']}";
  $node = $wr->{$field_name}->value();
  $request = db_select('quiz_node_results', 'r')
    ->fields('r', array('score'))
    ->condition('r.nid', $node->nid)
    ->execute();

  $ranges = array(
    '1-34' => 'F',
    '35-59' => 'FX',
    '60-63' => 'E',
    '64-73' => 'D',
    '74-81' => 'C',
    '82-89' => 'B',
    '90-100' => 'A',
  );
  $ranges_count = array();
  while ($score = $request->fetchAssoc()) {
    $score = $score['score'];
    foreach ($ranges as $range => $label) {
      list($from, $to) = explode('-', $range);
      if ($from <= $score && $score <= $to) {
        $ranges_count[$label] = isset($ranges_count[$label]) ? $ranges_count[$label]++ : 1;
        break;
      }
    }
  }


  if (!empty($ranges_count)) {
    $settings['chart']['chartOne'] = array(
      'header' => array_keys($ranges_count),
      'rows' => array(array_values($ranges_count)),
      'columns' => array('Result'),
      'chartType' => 'PieChart',
      'containerId' => 'test-result-chart',
      'options' => array(
        'forceIFrame' => FALSE,
        'title' => 'Result',
        'width' => 800,
        'height' => 400
      )
    );
    draw_chart($settings);
    $pane = new stdClass();
    $pane->content = '<div id="test-result-chart"></div>';
    return $pane;
  }
}
