<?php

/**
 * Form to take test.
 */
function diplom_test_task_form($form, &$form_state) {
  $test = $form_state['build_info']['test'];
  $result = $form_state['build_info']['result'];
  $layout = $result->getLayout();
  $form['#tree'] = TRUE;

  $storage = isset($form_state['storage']) ? $form_state['storage'] : array();

  // Questions count.
  $count = count($layout);
  $form_state['storage']['count'] = $count;

  // Number of question.
  $form_state['storage']['current'] = !empty($storage['current']) ? $storage['current'] : 1;
  $number = $form_state['storage']['current'];

  // Get question form.
  if (isset($layout[$number])) {
    $question = $layout[$number];
    $question_node = node_load($question['nid'], $question['vid']);
    $question = _quiz_question_get_instance($question_node);
    $wr_question = entity_metadata_wrapper('node', $question_node);
    $body_qestion = $wr_question->body->value();
    $element = $question->getAnsweringForm($form_state, $result->result_id);
  }

  if (!empty($test->time_limit)) {
    $value = $test->time_limit - (REQUEST_TIME - $result->time_start);
    $form['timer'] = array(
      '#markup' => theme('test_timer', array('value' => $value)),
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'diplom_test') . '/js/jquery.plugin.min.js',
          drupal_get_path('module', 'diplom_test') . '/js/jquery.countdown.min.js',
          drupal_get_path('module', 'diplom_test') . '/js/diplom_test.js',
        )
      )
    );
  }

  // Build question form.
  $form['question_' . $number] = array(
    '#attributes' => array('id' => 'diplom-test-question'),
    '#type' => 'container',
    'question' => array(
      '#markup' => $body_qestion['safe_value'],
    ),
    'answer' => isset($element['user_answer']) ? $element['user_answer'] : array(),
  );

  // Build buttons.
  $form['buttons']['#type'] = 'actions';
  $form['navigation']['back'] = array(
    '#type' => 'submit',
    '#value' => t('Back'),
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'wrapper' => 'diplom-test-question',
      'callback' => 'diplom_test_task_form_ajax_callback',
    ),
    '#name' => 'back',
  );
  $form['navigation']['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'wrapper' => 'diplom-test-question',
      'callback' => 'diplom_test_task_form_ajax_callback',
    ),
    '#name' => 'next',
  );
  $form['navigation']['finish'] = array(
    '#weight' => 10,
    '#type' => 'submit',
    '#value' => t('Finish'),
    '#limit_validation_errors' => array(),
    '#name' => 'finish',
  );
  return $form;
}

/**
 * Ajax callback function of form to take test.
 */
function diplom_test_task_form_ajax_callback($form, $form_state) {
  $current = &$form_state['storage']['current'];
  return $form['question_' . $current];
}

/**
 * Submit function of form to take test.
 */
function diplom_test_task_form_submit($form, &$form_state) {
  $result = $form_state['build_info']['result'];
  $test = $form_state['build_info']['test'];
  $layout = $result->getLayout();
  $current = &$form_state['storage']['current'];
  $question = $layout[$current];

  // Save result.
  if (!empty($form_state['input']['question_' . $current]['answer'])) {
    // Save question result.
    $answer = $form_state['input']['question_' . $current]['answer'];
    $question_node = node_load($question['nid'], $question['vid']);
    $qi_instance = _quiz_question_response_get_instance($result->result_id, $question_node, array(
      'user_answer' => $answer,
    ));
    $qi_instance->is_skipped = FALSE;
    $qi_instance->save();
    $bare_result = $qi_instance->toBareObject();
    $result->is_doubtful = FALSE;
    quiz_store_question_result($test, $bare_result, array(
      'set_msg' => TRUE,
      'question_data' => array('number' => $current)
    ));
  }
  else {
    // Skip question result.
    $qra = quiz_result_answer_load($result->result_id, $question['nid'], $question['vid']);
    $qra->is_skipped = 1;
    $qra->is_correct = 0;
    $qra->points_awarded = 0;
    $qra->answer_timestamp = REQUEST_TIME;
    entity_save('quiz_result_answer', $qra);
  }

  $action_button = $form_state['triggering_element']['#name'];
  $count = $form_state['storage']['count'];
  switch ($action_button) {
    case 'next':
    case 'back':
      // Set a current number of question.
      if ($action_button == 'next') {
        $current = (++$current > $count) ? 1 : $current;
      }
      else {
        $current = (--$current < 1) ? $count : $current;
      }
      $form_state['rebuild'] = TRUE;
      break;

    case 'finish':
      $result = diplom_test_close_user_result($result, $test);
      $form_state['rebuild'] = FALSE;
      break;
  }

  if (diplom_test_check_user_result($result, $test)) {
    diplom_test_close_user_result($result, $test);
    $form_state['rebuild'] = FALSE;
  }
}