<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Answer field'),
  'description' => t('Field to set answers of question.'),
  'required context' => new ctools_context_required(t('Form'), 'node_form'),
  'category' => array(t('Diplom'), -9),
  'render callback' => 'diplom_question_answer_field_render',
  'edit form' => 'diplom_question_answer_field_form',
);

function diplom_question_answer_field_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');
  $block->delta = 'title-options';
  if (isset($context->form)) {
    if (!empty($context->form['alternatives'])) {
      $block->content = $context->form['alternatives'];
      unset($context->form['alternatives']);
    }
  }
  return $block;
}

function diplom_question_answer_field_form($form, &$form_state) {
  return $form;
}
