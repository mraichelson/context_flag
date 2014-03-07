<?php
/**
 * @file
 * Provides Context integration for Flags applied to users when viewing user pages.
 */

/**
 * User Page Active Flag condition.
 */
class ContextFlagUserPageActive extends context_condition {
  // Name used for the context setting value with the options_form.
  public $contextSettingName = 'flag_user_page_active';
  // Context condition values.
  function condition_values() {
    $flags = flag_get_flags('user');
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
      $flags = flag_get_flags('user');
      $arr_flags = array();
      $obj_user = menu_get_object('user');
      if ($obj_user) {
        foreach ($flags as $flag) {
          $obj_flag = flag_get_flag($flag->name);
          $arr_flags[$flag->name] = $obj_flag->is_flagged($obj_user->uid);
        }
        // Trigger results.
        foreach ($this->get_contexts() as $context) {
          $arr_trigger_flags = $context->conditions['user_page_active']['values'];
          foreach ($arr_trigger_flags as $flag_name) {
            if ($arr_flags[$flag_name]) {
              $this->condition_met($context);
            }
          }
        }
      }
    }
  }
}

/**
 * User Page Inactive Flag condition.
 * TODO: Make this work.
 */
/*
class ContextFlagUserPageInactive extends context_condition {
  function condition_values() {
    $flags = flag_get_flags('user');
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  function execute() {
    if ($this->condition_used()) {
      // check if this flag is inactive for this display.
      // trigger results
      foreach ($this->get_contexts() as $context) {
        // $this->condition_met($context);
      }
    }
  }
}
*/
