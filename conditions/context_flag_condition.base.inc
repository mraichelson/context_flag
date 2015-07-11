<?php
/**
 * @file
 * Abstract base class for context_flag conditions to inherit from.
 *
 * Based on recommendation from joachim in ticket labelled
 *   "inherit from abstract parent?"
 *   https://www.drupal.org/node/2273725
 */

abstract class ContextFlagBase extends context_condition {
  // Context setting name
  public $contextSettingName = NULL;
  public function setContextSettingName($setting) {
    $this->contextSettingName = $setting;
  }
  // Define what kind of flags to look for in this instance.
  public $flagType = NULL;
  public function setFlagType($type) {
    $this->flagType = $type;
  }
  // Rather than keep forcing this to be written out in every instance where it
  // gets used, provide a shared helper for it.
  public function getFlagsForType() {
    return flag_get_flags($this->flagType);
  }
  // Return the list of flags available for this type.
  public function condition_values() {
    $flags = $this->getFlagsForType();
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  // Options configuration form.
  public function options_form($context) {
    $defaults = $this->fetch_from_context($context, 'options');
    $default_value = FALSE;
    if (isset($defaults[$this->contextSettingName])) {
      $default_value = $defaults[$this->contextSettingName];
    }
    return $this->requireAllForm($this->contextSettingName, $default_value);
  }
  // Controls for the "Require All Flags" options form modifier.
  public function requireAllForm($setting, $value = FALSE) {
    $form = array();
    $form[$setting] = array(
      '#title' => t('Require all flags'),
      '#type' => 'checkbox',
      '#description' => t('Trigger this context only when ALL selections are active.'),
      '#default_value' => $value,
    );
    return $form;
  }
  // @TODO: implement get_entity() so that it can be overridden in the condition
  // specific class files. https://www.drupal.org/node/2273725#comment-8810825
  public function get_entity() { return FALSE; }
}
