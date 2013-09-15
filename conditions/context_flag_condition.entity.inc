<?php
/**
 * @file context_flag_condition.entity.inc
 * Provides Context integration for Flags applied to entities.
 */

/**
 * Entity Active Flag condition.
 */
class entity_active extends context_condition {
  function condition_values() {
    $flags = flag_get_flags('entity');
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  function execute() {
    if ($this->condition_used()) {
      // check if this flag is active for this display.
      // trigger results
      foreach ($this->get_contexts() as $context) {
        // $this->condition_met($context);
      }
    }
  }
}

/**
 * Entity Inactive Flag condition.
 */
// class entity_inactive extends context_condition {
//   function condition_values() {
//     $flags = flag_get_flags('entity');
//     $values = array();
//     foreach ($flags as $flag) {
//       $values[$flag->name] = $flag->title;
//     }
//     return $values;
//   }
//   function execute() {
//     if ($this->condition_used()) {
//       // check if this flag is active for this display.
//       // trigger results
//       foreach ($this->get_contexts() as $context) {
//         // $this->condition_met($context);
//       }
//     }
//   }
// }