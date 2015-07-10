<?php
/**
 * @file
 * Abstract base class for context_flag conditions to inherit from.
 * Based on recommendation from joachim in ticket labelled
 *   "inherit from abstract parent?"
 *   https://www.drupal.org/node/2273725
 */

abstract class ContextFlagBase extends context_condition {
  // Define what kind of flags to look for in this instance.
  public $flagType = 'node';
  public function setFlagType($type) {
    $this->flagType = $type;
  }
  // Return the list of flags available for this type.
  public function condition_values() {
    $flags = flag_get_flags($this->flagType);
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  // Options configuration form.
  public function options_form($context) {
    $defaults = $this->fetch_from_context($context, 'options');
    $default_value = isset($defaults[$this->contextSettingName]) ? $defaults[$this->contextSettingName] : FALSE;

    // @TODO: remove debugging code
    dpm('context setting name is ' . $this->contextSettingName);
    dpm('$context');
    dpm($context);
    dpm('$defaults');
    dpm($defaults);
    dpm('$default_value');
    dpm($default_value);

    return _context_flag_requireall_form($this->contextSettingName, $default_value);
  }

  // @TODO: implement get_entity() so that it can be overridden in the condition
  // specific class files. https://www.drupal.org/node/2273725#comment-8810825
  public function get_entity() {
    return false;
  }
  // @TODO: move functionality from _context_flag_requireall_form() here.
  // https://www.drupal.org/node/2273725#comment-8810825
  public function requireAllForm() {
    return false;
  }
}
