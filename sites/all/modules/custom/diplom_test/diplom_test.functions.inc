<?php

/**
* Close user test result.
*
* @param object $result
*  Quiz object.
* @param object $test
*  quiz_result object.
*
* @return object
*  Updated quiz_result object.
*/
function diplom_test_close_user_result($result, $test) {
  $score = quiz_end_scoring($result->result_id);
  quiz_end_actions($test, $score, array('result_id' => $test->nid));
  unset($_SESSION['quiz'][$test->nid]);
  return entity_load_single('quiz_result', $result->result_id);
}

/**
* Check user result by time.
*
* @param object $result
*  Quiz object.
* @param object $test
*  quiz_result object.
*
* @return bool
*   True if time is over.
*/
function diplom_test_check_user_result($result, $test) {
  return !empty($test->time_limit) && empty($result->time_end)
    && (REQUEST_TIME - $result->time_start) > $test->time_limit;
}

/**
* Get user test result.
*
* @param object $test
*   Quis object.
* @param $uid
*   User id.
*
* @return object
*   User result.
*/
function diplom_test_get_user_result($test, $uid) {
  $result = entity_load('quiz_result', FALSE, array(
  'nid' => $test->nid,
  'vid' => $test->vid,
  'uid' => $uid,
  ));
  $result = !empty($result) ? reset($result) : NULL;

  // If time is over, result will be closed.
  if (!empty($result) && diplom_test_check_user_result($result, $test)) {
  $result = diplom_test_close_user_result($result, $test);
  }

  // If result is not found, will create new result
  if (empty($result)) {
  $result = entity_create('quiz_result', array(
  'nid' => $test->nid,
  'vid' => $test->vid,
  'uid' => $GLOBALS['user']->uid,
  ));
  $result->save();
  $_SESSION['quiz'][$result->nid]['result_id'] = $result->result_id;
  $_SESSION['quiz'][$result->nid]['current'] = 1;
  quiz_take_quiz($test);
  }
  return $result;
}