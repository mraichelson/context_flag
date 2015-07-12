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
  // Properties that are required to keep Context functioning properly
  public $plugin = NULL;
  public $title = NULL;
  public $description = NULL;
  // Properties used in context_flag code.
  public $contextSettingName = NULL;
  public $flagType = NULL;
  // Property value setting helper.
  public function setPropertyValue($property, $value) {
    $this->{$property} = $value;    
  }
  // Check if flags are available for messaging on the context_ui form.
  private function hasAvailableFlags() {
    $flags = $this->getFlagsForType();
    if (count($flags) > 0) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
  // Rather than keep forcing this to be written out in every instance where it
  // gets used, provide a shared helper for it.
  public function getFlagsForType() {
    return flag_get_flags($this->flagType);
  }
  // Return the list of flags available for this type.
  // (Naming pattern must comply with existing code from context module.)
  public function condition_values() {
    $values = array();
    if ($this->hasAvailableFlags()) {
      $flags = $this->getFlagsForType();
      foreach ($flags as $flag) {
        $values[$flag->name] = $flag->title;
      }
    }
    else {
      $values[NULL] = t('<b>Attention:</b> No flags of this type are available. (Please add one and try again.)'); 
    }
    return $values;
  }
  // Options configuration form.
  // (Naming pattern must comply with existing code from context module.)
  public function options_form($context) {
    if ($this->hasAvailableFlags()) {
      $defaults = $this->fetch_from_context($context, 'options');
      $default_value = FALSE;
      if (isset($defaults[$this->contextSettingName])) {
        $default_value = $defaults[$this->contextSettingName];
      }
      return $this->requireAllForm($this->contextSettingName, $default_value);
    }
    else {
      return $this->noMatchingFlagsForm($this->contextSettingName);
    }
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
  // Helper for "There are no matching flags to use with this condition" form
  // modifier.
  public function noMatchingFlagsForm($setting) {
    $form = array();
    $form[$setting] = array(
      '#type' => 'item',
      '#title' => t('No matching flags found'),
      '#description' => t('There are no flags of this type available for use.'),
    );
    return $form;
  }
  // Helper for abstracting the logic checking process.
  // This is the "execute" function that context conditions use by default, it
  // triggers the (overrideable) contextFlagConditionCheck().
  public function execute() {
    $this->contextFlagConditionCheck();
  }
  // Stub helper for checking conditions.
  abstract function contextFlagConditionCheck();

}
