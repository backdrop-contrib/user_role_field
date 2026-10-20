<?php

/**
 * @file
 * Administer user roles on fields.
 */

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
  $field = (array) field_info_field($field_name);
  if (empty($field)) {
    return;
  }

  // Enhance the field settings form with role visibility.
  $roles = user_roles(TRUE);

  $form['field']['settings']['user_role_field'] = array(
    '#type' => 'fieldset',
    '#title' => t('Role visibility'),
  );
  $form['field']['settings']['user_role_field']['roles'] = array(
    '#title' => t('Roles'),
    '#type' => 'checkboxes',
    '#checkall' => TRUE,
    '#options' => $roles,
    '#default_value' => _user_role_field_roles($field),
    '#description' => t('Use these options to make a field visible for a specific role (or hide, if "Reverse" is checked). If no role is set, the field is visible to all roles. Does not affect visibility on user registration form.'),
    '#weight' => 100,
  );
  $form['field']['settings']['user_role_field']['negate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reverse (NOT)'),
    '#default_value' => $field['settings']['user_role_field']['negate'] ?? 0,
    '#weight' => 101,
  );

  // Hide the option to non-privileged users.
  if (!user_access('administer user field roles')) {
    $form['field']['settings']['user_role_field']['roles']['#type'] = 'value';
    $form['field']['settings']['user_role_field']['roles']['#value'] = $form['field']['settings']['user_role_field']['roles']['#default_value'];
    $form['field']['settings']['user_role_field']['negate']['#type'] = 'value';
    $form['field']['settings']['user_role_field']['negate']['#value'] = $form['field']['settings']['user_role_field']['negate']['#default_value'];
  }
}
