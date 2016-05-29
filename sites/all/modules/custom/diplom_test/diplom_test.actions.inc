<?php

/**
 * Implements hook_action_info().
 */
function diplom_test_action_info() {
  $actions = array();
  $actions['diplom_test_add_question_to_quiz'] = array(
    'type' => 'node',
    'label' => t('Add questions to test'),
    'configurable' => TRUE,
    'vbo_configurable' => TRUE,
  );
  $actions['diplom_test_remove_question_from_quiz'] = array(
    'type' => 'node',
    'label' => t('Remove questions from test'),
    'configurable' => TRUE,
    'vbo_configurable' => TRUE,
  );
  $actions['diplom_test_remove_test_result'] = array(
    'type' => 'quiz_result',
    'label' => t('Remove result from test'),
    'configurable' => FALSE,
    'vbo_configurable' => FALSE,
  );
  $actions['diplom_test_question_required'] = array(
    'type' => 'quiz_question_relationship',
    'label' => t('Make required'),
    'configurable' => FALSE,
    'vbo_configurable' => FALSE,
  );
  $actions['diplom_test_question_random'] = array(
    'type' => 'quiz_question_relationship',
    'label' => t('Make random'),
    'configurable' => FALSE,
    'vbo_configurable' => FALSE,
  );
  return $actions;
}

/**
 * Form of 'Add questions to test' action to select group test.
 */
function diplom_test_add_question_to_quiz_form($context) {
  return diplom_test_group_quiz_form($context);
}

/**
 * Submit function of 'Add questions to test' action.
 */
function diplom_test_add_question_to_quiz_submit($form, $form_state) {
  return array('test' => $form_state['values']['test']);
}

/**
 * Action function to add question to test.
 */
function diplom_test_add_question_to_quiz($question, $context) {
  module_load_include('inc', 'multichoice', 'multichoice.classes');
  $test_wrapper = entity_metadata_wrapper('node', $context['test']);
  $test_vid = $test_wrapper->vid->value();
  $test_nid = $test_wrapper->nid->value();
  $conditions = array(
    'parent_nid'  => $test_nid,
    'parent_vid' => $test_vid,
    'child_nid' => $question->nid,
    'child_vid' => $question->vid,
  );
  if (!($entity_load = entity_load('quiz_question_relationship', FALSE, $conditions))) {
    $question_wrapper = new MultichoiceQuestion($question);
    $question_wrapper->saveRelationships($test_nid, $test_vid);
    quiz_update_max_score_properties(array($test_nid));
  }
}


/**
 * Form of 'Remove questions from test' action to select group test.
 */
function diplom_test_remove_question_from_quiz_form($context) {
  return diplom_test_group_quiz_form($context);
}

/**
 * Submit function of 'Remove questions from test' action.
 */
function diplom_test_remove_question_from_quiz_submit($form, $form_state) {
  return array('test' => $form_state['values']['test']);
}

/**
 * Action function to remove question from test.
 */
function diplom_test_remove_question_from_quiz($question, $context) {
  if (!empty($context['test'])) {
    module_load_include('inc', 'multichoice', 'multichoice.classes');
    db_delete('quiz_node_relationship')
      ->condition('parent_nid', $context['test'])
      ->condition('child_nid', $question->nid)
      ->execute();
    quiz_update_max_score_properties(array($context['test']));
  }
}

/**
 * Generate form to select group test.
 */
function diplom_test_group_quiz_form($context) {
  $gid = $context['view']->args[0];
  $wr = entity_metadata_wrapper('group', $gid);
  $test_types = array('field_attestation_test', 'field_skill_test');
  $options = array();
  foreach ($test_types as $type_name) {
    if ($test = $wr->{$type_name}->value()) {
      $options[$test->nid] = $test->title;
    }
  }
  return array(
    'test' => array(
      '#title' => t('Test'),
      '#type' => 'select',
      '#options' => $options,
      '#required' => TRUE,
    ),
  );
}

/**
 * Action function to remove result.
 */
function diplom_test_remove_test_result($result, $context) {
  entity_delete('quiz_result', $result->result_id);
}

/**
 * Action function to make question required.
 */
function diplom_test_question_required($relationship, $context) {
  $relationship->question_status = QUIZ_QUESTION_ALWAYS;
  $relationship->save();
}

/**
 * Action function to make question random.
 */
function diplom_test_question_random($relationship, $context) {
  $relationship->question_status = QUIZ_QUESTION_RANDOM;
  $relationship->save();
}
