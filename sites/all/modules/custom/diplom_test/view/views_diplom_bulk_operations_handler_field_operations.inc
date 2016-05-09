<?php

/**
 * @file
 * Definition of views_handler_filter_string.
 */

/**
 * Basic textfield filter to handle string filtering commands
 * including equality, like, not like, etc.
 *
 * @ingroup views_filter_handlers
 */
class diplom_test_handler_filter_question_test extends views_handler_filter_boolean_operator_string {
  function avalue_form(&$form, &$form_state) {
    if (empty($this->value['value'])) {
      $this->value['value'] = 'All';
    }
    parent::value_form($form, $form_state);
    $form['value'] = array(
      '#type' => 'select',
      '#options' => array(
        'All' => '- Any -',
        'in_32' => ('In test'),
        'not_32' => t('Not in test'),
      ),
      '#default_value' => 'All',
    );
  }

  function query() {
//    if ($this->value['value'] == 'All') {
//      return NULL;
//    }
//    list($op, $qid) = explode('_', $this->value['value']);
//    if (!isset($op, $qid) || in_array($op, array('in', 'not')) || !is_numeric($qid)) {
//      return NULL;
//    }
//    $this->ensure_my_table();
//    $field = "$this->table_alias.$this->real_field";
//    switch ($op) {
//      case 'in':
//        $this->query->add_where($this->options['group'], $field, (int)$qid, '=');
//        break;
//      case 'not':
//        $this->query->add_where($this->options['group'], $field, (int)$qid, '!=');
//        break;
//    }
  }
}
