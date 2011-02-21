<?php

/**
 * Alter the field settings form.
 */
function _user_role_field_field_settings_form_alter(&$form, $form_state, $form_id) {
  // Try to obtain the field name from the form itself.
  if ($form_id == 'field_ui_field_settings_form') {
    $field_name = $form['field']['field_name']['#value'];
  }
  elseif ($form_id == 'field_ui_field_edit_form') {
    $field_name = $form['instance']['field_name']['#value'];
  }
  else {
    return;
  }

  // Try to obtain information about this field.
  $field = field_info_field($field_name);
  if (empty($field)) {
    return;
  }

  // Enhance the field settings form with role visibility
  $roles = user_roles ();
  $form['field']['settings']['user_role_field'] = array(
    '#title' => t('Apply only to'),
    '#type' => 'checkboxes',
    '#checkall' => TRUE,
    '#options' => $roles,
    '#default_value' => _user_role_field_roles($field),
    '#description' => t('Use these options to make a field visible for a specific role. If no role is set, the field is visible to all roles. If the anonymous role is set, the field will show up in the user registration form.'),
    '#weight' => -1,
  );

  // Hide the option to non-privileged users.
  if (!user_access('administer user field roles')) {
    $form['field']['settings']['user_role_field']['#type'] = 'value';
    $form['field']['settings']['user_role_field']['#value'] = $form['field']['settings']['user_role_field']['#default_value'];
  }
}
