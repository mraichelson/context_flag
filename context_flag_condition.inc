<?php
/**
 * @file context_flag_condition.inc
 */

/**
 * Active Flag condition.
 */
class flag_active extends context_condition {
  function condition_values() {
    $flags = flag_get_flags();
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  function execute() {}
}

/**
 * Inactive Flag condition.
 */
class flag_inactive extends context_condition {
  function condition_values() {
    $flags = flag_get_flags();
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  function execute() {}
}
