<?php
/**
 * @file context_flag_condition.user.inc
 * Provides Context integration for Flags applied to users.
 */

/**
 * User Page Active Flag condition.
 */
class user_page_active extends context_condition {
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
      // check if this flag is active for this display.
      $flags = flag_get_flags('user');
      $arr_flags = array();
      $obj_user = menu_get_object('user');
      if ($obj_user) {
        foreach($flags as $flag) {
          $obj_flag = flag_get_flag($flag->name);
          $arr_flags[$flag->name] = $obj_flag->is_flagged($obj_user->uid);
        }
        // trigger results
        foreach ($this->get_contexts() as $context) {
          $arr_trigger_flags = $context->conditions['user_page_active']['values'];
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
// class user_page_inactive extends context_condition {
//   function condition_values() {
//     $flags = flag_get_flags('user');
//     $values = array();
//     foreach ($flags as $flag) {
//       $values[$flag->name] = $flag->title;
//     }
//     return $values;
//   }
//   function execute() {
//     if ($this->condition_used()) {
//       // check if this flag is inactive for this display.
//       // trigger results
//       foreach ($this->get_contexts() as $context) {
//         // $this->condition_met($context);
//       }
//     }
//   }
// }

/**
 * Current logged in user has active flag.
 */
class user_account_active extends context_condition {
  function condition_values() {
    $flags = flag_get_flags('user');
    $values = array();
    foreach ($flags as $flag) {
      $values[$flag->name] = $flag->title;
    }
    return $values;
  }
  function execute($account) {
    if ($this->condition_used() && !empty($account->uid)) {
      // check if this flag is active for this display.
      $flags = flag_get_flags('user');
      $arr_flags = array();
      foreach($flags as $flag) {
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
// class user_account_inactive extends context_condition {
//   function condition_values() {
//     $flags = flag_get_flags('user');
//     $values = array();
//     foreach ($flags as $flag) {
//       $values[$flag->name] = $flag->title;
//     }
//     return $values;
//   }
//   function execute() {
//     if ($this->condition_used() && !empty($account->uid)) {
//       // check if this flag is inactive for this display.
//       $flags = flag_get_flags('user');
//       $arr_flags = array();
//       foreach($flags as $flag) {
//         $obj_flag = flag_get_flag($flag->name);
//         $arr_flags[$flag->name] = $obj_flag->is_flagged($account->uid);
//       }
//       // trigger results
//       foreach ($this->get_contexts() as $context) {
//         $arr_trigger_flags = $context->conditions['user_account_inactive']['values'];
//         foreach ($arr_trigger_flags as $flag_name) {
//           if (!$arr_flags[$flag_name]) {
//             $this->condition_met($context);
//           }
//         }
//       }
//     }
//   }
// }
