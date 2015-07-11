<?php
/**
 * @file
 * Context integration for Flags applied to nodes.
 */

/**
 * Node Active Flag condition.
 */
class ContextFlagNodeActive extends ContextFlagBase {
  public function __construct() {
    $this->setContextSettingName('flag_node_active');
    $this->setFlagType('node');
  }
  // Context check execution.
  function execute() {
    if ($this->condition_used()) {
      $obj_page = menu_get_object();
      if (!empty($obj_page->nid)) {
        $flags = $this->getFlagsForType();
        $arr_flags = array();
        foreach ($flags as $flag) {
          $obj_flag = flag_get_flag($flag->name);
          $arr_flags[$flag->name] = $obj_flag->is_flagged($obj_page->nid);
        }
        foreach ($this->get_contexts() as $context) {
          $options = $this->fetch_from_context($context, 'options');
          $require_all = isset($options[$this->contextSettingName]) ? $options[$this->contextSettingName] : FALSE;
          $arr_trigger_flags = $context->conditions[$this->contextSettingName]['values'];
          if (!$require_all) {
            foreach ($arr_trigger_flags as $flag_name) {
              if ($arr_flags[$flag_name]) {
                $this->condition_met($context);
              }
            }
          }
          else {
            $is_all_active = TRUE;
            foreach ($arr_trigger_flags as $delta => $flag_name) {
              if (!$arr_flags[$delta]) {
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
