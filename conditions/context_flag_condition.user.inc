<?php
/**
 * @file
 * Provides Context integration for Flags applied to users.
 */

/**
 * User Page Active Flag condition.
 */
class ContextFlagUserPageActive extends context_condition {
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
    $context_setting_name = 'flag_user_page_active';
    $defaults = $this->fetch_from_context($context, 'options');
    $default_value = isset($defaults[$context_setting_name]) ? $defaults[$context_setting_name] : FALSE;
    return _context_flag_requireall_form($context_setting_name, $default_value);
  }
  // Context check execution.
  function execute() {
    if ($this->condition_used()) {
      // check if this flag is active for this display.
      $flags = flag_get_flags('user');
      $arr_flags = array();
      $obj_user = menu_get_object('user');
      if ($obj_user) {
        foreach ($flags as $flag) {
          $obj_flag = flag_get_flag($flag->name);
          $arr_flags[$flag->name] = $obj_flag->is_flagged($obj_user->uid);
        }
        // trigger results.
        foreach ($this->get_contexts() as $context) {
          $arr_trigger_flags = $context->conditions['flag_user_page_active']['values'];
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

/**
 * Current logged in user has active flag.
 */
class ContextFlagUserAccountActive extends context_condition {
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
    $context_setting_name = 'flag_user_account_active';
    $defaults = $this->fetch_from_context($context, 'options');
    $default_value = isset($defaults[$context_setting_name]) ? $defaults[$context_setting_name] : FALSE;
    return _context_flag_requireall_form($context_setting_name, $default_value);
  }
  // Context check execution.
  function execute($account) {
    if ($this->condition_used() && !empty($account->uid)) {
      // check if this flag is active for this display.
      $flags = flag_get_flags('user');
      $arr_flags = array();
      foreach ($flags as $flag) {
        $obj_flag = flag_get_flag($flag->name);
        $arr_flags[$flag->name] = $obj_flag->is_flagged($account->uid);
      }
      // trigger results
      foreach ($this->get_contexts() as $context) {
        $arr_trigger_flags = $context->conditions['user_account_active']['values'];
        foreach ($arr_trigger_flags as $flag_name) {
          if ($arr_flags[$flag_name]) {
            $this->condition_met($context);
          }
        }
      }
    }
  }
}

/**
 * Current logged in user does not have active flag.
 * TODO: Make this work.
 */
/*
class ContextFlagUserAccountInactive extends context_condition {
  function condition_values() {
    $flags = flag_get_flags('user');
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  function execute() {
    if ($this->condition_used() && !empty($account->uid)) {
      // check if this flag is inactive for this display.
      $flags = flag_get_flags('user');
      $arr_flags = array();
      foreach ($flags as $flag) {
        $obj_flag = flag_get_flag($flag->name);
        $arr_flags[$flag->name] = $obj_flag->is_flagged($account->uid);
      }
      // trigger results
      foreach ($this->get_contexts() as $context) {
        $arr_trigger_flags = $context->conditions['user_account_inactive']['values'];
        foreach ($arr_trigger_flags as $flag_name) {
          if (!$arr_flags[$flag_name]) {
            $this->condition_met($context);
          }
        }
      }
    }
  }
}
*/
