<?php
/**
 * @file context_flag_condition.comment.inc
 * Provides Context integration for Flags applied to comments.
 */

/**
 * Comment Active Flag condition.
 */
class comment_active extends context_condition {
  function condition_values() {
    $flags = flag_get_flags('comment');
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
 * Comment Inactive Flag condition.
 */
// class comment_inactive extends context_condition {
//   function condition_values() {
//     $flags = flag_get_flags('comment');
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