<?php
/**
 * @file
 * Context integration for Flags applied to users when viewing user pages.
 */

/**
 * User Page Active Flag condition.
 */
class ContextFlagUserPageActive extends ContextFlagBase {
  // Name used for the context setting value with the options_form.
  public $contextSettingName = 'flag_user_page_active';
  // Define the type of flags to make available.
  public function __construct() {
    $this->setFlagType('user');
  }
  // Context check execution.
  function execute() {
    if ($this->condition_used()) {
      // Check if this flag is active for this display.
      $arr_flags = array();
      $obj_user = menu_get_object('user');
      if ($obj_user) {
        $flags = $this->getFlagsForType();
        foreach ($flags as $flag) {
          $obj_flag = flag_get_flag($flag->name);
          $arr_flags[$flag->name] = $obj_flag->is_flagged($obj_user->uid);
        }
        // Trigger results.
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
