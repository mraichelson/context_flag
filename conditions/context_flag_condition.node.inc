<?php
/**
 * @file context_flag_condition.node.inc
 * Provides Context integration for Flags applied to nodes.
 */

/**
 * Node Active Flag condition.
 */
class node_active extends context_condition {
  function condition_values() {
    $flags = flag_get_flags('node');
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  function options_form($context) {
    $defaults = $this->fetch_from_context($context, 'options');
    $default_value = FALSE;
    if (isset($defaults['flag_node_all'])) {
      $default_value = $defaults['flag_node_all'];
    }
    return array(
      'flag_node_all' => array(
        '#title' => t('Require all flags'),
        '#type' => 'checkbox',
        '#description' => t('Trigger this context only when ALL selections are active.'),
        '#default_value' => $default_value,
      ),
    );
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
          $options = $this->fetch_from_context($context, 'options');
          $require_all = FALSE;
          if (isset($options['flag_node_all'])) {
            $require_all = $options['flag_node_all'];
          }
          // @TODO: make $require_all contexts actually require all.
          // if ($require_all) { dsm('require all'); }
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
// class node_inactive extends context_condition {
//   function condition_values() {
//     $flags = flag_get_flags('node');
//     $values = array();
//     foreach ($flags as $flag) {
//       $values[$flag->name] = $flag->title;
//     }
//     return $values;
//   }
//   function execute() {
//     if ($this->condition_used()) {
//       $obj_page = menu_get_object();
//       if (!empty($obj_page->nid)) {
//         $flags = flag_get_flags('node');
//         $arr_flags = array();
//         foreach ($flags as $flag) {
//           $obj_flag = flag_get_flag($flag->name);
//           $arr_flags[$flag->name] = $obj_flag->is_flagged($obj_page->nid);
//         }
//         foreach ($this->get_contexts() as $context) {
//           $arr_trigger_flags = $context->conditions['node_inactive']['values'];
//           foreach ($arr_trigger_flags as $flag_name) {
//             if (!$arr_flags[$flag_name]) {
//               $this->condition_met($context);
//             }
//           }
//         }
//       }
//     }
//   }
// }
