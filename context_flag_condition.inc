<?php
/**
 * @file context_flag_condition.inc
 */

/**
 * Node Active Flag condition.
 */
class node_active extends context_condition {
  function condition_values() {
    $flags = flag_get_flags();
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
        $flags = flag_get_flags();
        $arr_flags = array();
        foreach($flags as $flag) {
          $obj_flag = flag_get_flag($flag->name);
          $arr_flags[$flag->name] = $obj_flag->is_flagged($obj_page->nid);
        }
        foreach ($this->get_contexts() as $context) {
          $arr_trigger_flags = $context->conditions['node_active']['values'];
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
 * Node Inactive Flag condition.
 */
class node_inactive extends context_condition {
  function condition_values() {
    $flags = flag_get_flags();
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
        $flags = flag_get_flags();
        $arr_flags = array();
        foreach($flags as $flag) {
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
