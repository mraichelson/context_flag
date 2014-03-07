<?php
/**
 * @file
 * Provides Context integration for Flags applied to comments.
 */

/**
 * Comment Active Flag condition.
 */
class ContextFlagCommentActive extends context_condition {
  // Name used for the context setting value with the options_form.
  public $contextSettingName = 'flag_comment_active';
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
    $defaults = $this->fetch_from_context($context, 'options');
    $default_value = isset($defaults[$this->contextSettingName]) ? $defaults[$this->contextSettingName] : FALSE;
    return _context_flag_requireall_form($this->contextSettingName, $default_value);
  }
  // Context check execution.
  function execute() {
    if ($this->condition_used()) {
      // Check if this flag is active for this display.
      // Trigger results.
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
      // Check if this flag is active for this display.
      // Trigger results
      foreach ($this->get_contexts() as $context) {
        // $this->condition_met($context);
      }
    }
  }
}
*/
