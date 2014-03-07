<?php
/**
 * @file
 * Provides Context integration for Flags applied to nodes.
 */

/**
 * Node Active Flag condition.
 */
class ContextFlagNodeActive extends context_condition {
  // Context condition values.
  function condition_values() {
    $flags = flag_get_flags('node');
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  // Context form modifications.
  function options_form($context) {
    $context_setting_name = 'flag_node_active';
    $defaults = $this->fetch_from_context($context, 'options');
    $default_value = isset($defaults[$context_setting_name]) ? $defaults[$context_setting_name] : FALSE;
    return _context_flag_requireall_form($context_setting_name, $default_value);
  }
  // Context check execution.
  function execute() {
    if ($this->condition_used()) {
      $obj_page = menu_get_object();
      if (!empty($obj_page->nid)) {
        $flags = flag_get_flags('node');
        $arr_flags = array();
        foreach ($flags as $flag) {
          $obj_flag = flag_get_flag($flag->name);
          $arr_flags[$flag->name] = $obj_flag->is_flagged($obj_page->nid);
        }
        foreach ($this->get_contexts() as $context) {
          $options = $this->fetch_from_context($context, 'options');
          $require_all = FALSE;
          if (isset($options['flag_node_active'])) {
            $require_all = $options['flag_node_active'];
          }
          $arr_trigger_flags = $context->conditions['node_active']['values'];
          if (!$require_all) {
            foreach ($arr_trigger_flags as $flag_name) {
              if ($arr_flags[$flag_name]) {
                $this->condition_met($context);
              }
            }
          }
          else {
            $is_all_active = TRUE;
            foreach ($arr_flags as $flag_state) {
              if (!$flag_state) {
                $is_all_active = FALSE;
              }
            }
            if ($is_all_active) {
              $this->condition_met($context);
            }
          }
        }
      }
    }
  }
}

/**
 * Node Inactive Flag condition.
 */
/*
class ContextFlagNodeInactive extends context_condition {
  function condition_values() {
    $flags = flag_get_flags('node');
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  function execute() {
    if ($this->condition_used()) {
      $obj_page = menu_get_object();
      if (!empty($obj_page->nid)) {
        $flags = flag_get_flags('node');
        $arr_flags = array();
        foreach ($flags as $flag) {
          $obj_flag = flag_get_flag($flag->name);
          $arr_flags[$flag->name] = $obj_flag->is_flagged($obj_page->nid);
        }
        foreach ($this->get_contexts() as $context) {
          $arr_trigger_flags = $context->conditions['node_inactive']['values'];
          foreach ($arr_trigger_flags as $flag_name) {
            if (!$arr_flags[$flag_name]) {
              $this->condition_met($context);
            }
          }
        }
      }
    }
  }
}
*/
