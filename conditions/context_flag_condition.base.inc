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
    $default_value = isset($defaults[$this->contextSettingName]) ? $defaults[$this->contextSettingName] : FALSE;

    // @TODO: remove debugging code
    dpm('DEBUGGING CODE: ContextFlagBase...');
    dpm('context setting name is ' . $this->contextSettingName);
    dpm('$context');
    dpm($context);
    dpm('$defaults');
    dpm($defaults);
    dpm('$default_value');
    dpm($default_value);

    return $this->requireAllForm($this->contextSettingName, $default_value);
  }

  // @TODO: implement get_entity() so that it can be overridden in the condition
  // specific class files. https://www.drupal.org/node/2273725#comment-8810825
  public function get_entity() { return false; }

  // Controls for the "Require All Flags" form modifier.
  public function requireAllForm($setting, $value = FALSE) {
    $form = array(
      $setting => array(
        '#title' => t('Require all flags'),
        '#type' => 'checkbox',
        '#description' => t('Trigger this context only when ALL selections are active.'),
        '#default_value' => $value,
        '#prefix' => '<hr>',
      ),
    );
    return $form;
  }
}
