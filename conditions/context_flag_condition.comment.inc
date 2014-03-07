<?php
/**
 * @file
 * Provides Context integration for Flags applied to comments.
 */

/**
 * Comment Active Flag condition.
 */
class ContextFlagCommentActive extends context_condition {
  // Context condition values.
  function condition_values() {
    $flags = flag_get_flags('comment');
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  // Context form modifications.
  function options_form($context) {
    $context_setting_name = 'flag_comment_active';
    $defaults = $this->fetch_from_context($context, 'options');
    $default_value = isset($defaults[$context_setting_name]) ? $defaults[$context_setting_name] : FALSE;
    return _context_flag_requireall_form($context_setting_name, $default_value);
  }
  // Context check execution.
  function execute() {
    if ($this->condition_used()) {
      // check if this flag is active for this display.
      // trigger results.
      foreach ($this->get_contexts() as $context) {
        // $this->condition_met($context);
      }
    }
  }
}

/**
 * Comment Inactive Flag condition.
 */
/*
class ContextFlagCommentInactive extends context_condition {
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
*/
