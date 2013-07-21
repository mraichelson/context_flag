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
  function execute() {
    // menu_get_object()
    // flag_properties_get_flagging_boolean($entity, array $options, $name, $entity_type, $property_info)
  }
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
