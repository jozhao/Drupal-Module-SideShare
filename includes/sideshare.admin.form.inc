<?php

/**
 * @file
 * Admin forms.
 */

/**
 * Sub Form builder: Share buttons.
 */
function _subform_sideshare_buttons() {
  $form['sideshare_buttons'] = array(
      '#type' => 'fieldset',
      '#title' => t('Share Buttons'),
      '#description' => t(''),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
  );
  $form['sideshare_buttons']['list'] = array(
      '#theme' => 'sideshare_buttons_list',
      '#weight' => 0,
  );
  return $form;
}

/**
 * Sub Form builder: Display.
 */
function _subform_sideshare_display() {
  // Sideshare display rules.
  $form['sideshare_display'] = array(
      '#type' => 'fieldset',
      '#weight' => 1,
      '#title' => t('Display conditions'),
      '#description' => t('Add sideshare widget to the following content types.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
  );
  $form['sideshare_display']['nodetypes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Content Types'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
  );
  $node_types = node_type_get_types();
  $node_names = node_type_get_names();
  if (is_array($node_names) && count($node_names)) {
    foreach ( $node_names as $key => $value ) {
      $form['sideshare_display']['nodetypes']['sideshare_posts_' . $node_types[$key]->type . '_enabled'] = array(
          '#type' => 'checkbox',
          '#title' => t('Automatically add sideshare to content type @value (only affects content type @value)', array(
              '@value' => $value,
          )),
          '#default_value' => variable_get('sideshare_posts_' . $node_types[$key]->type . '_enabled', TRUE),
      );
    }
  }
  return $form;
}

/**
 * Form builder: create buttons.
 */
function _sideshare_button_add($form, &$form_state, $edit = array()) {
  $button = new stdClass();
  $button->button_name = '';
  $button->button_machine_name ='';
  $button->button_codes = '';
  $button->button_icon  = '';
  $button->button_enabled = '';
  $button->button_weight = '';
  $form['button_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => $button->button_name,
      '#maxlength' => 255,
      '#required' => TRUE,
  );
  $form['button_machine_name'] = array(
      '#type' => 'machine_name',
      '#default_value' => $button->button_machine_name,
      '#maxlength' => 21,
      '#machine_name' => array(
          'exists' => 'sideshare_button_machine_name_load',
          'source' => array('button_name'),
      )
  );
  $form['button_codes'] = array(
      '#title' => t('Button share codes'),
      '#type' => 'textarea',
      '#description' => t('Share codes such as url or javascript codes'),
      '#wysiwyg' => FALSE,
      '#required' => TRUE,
      '#default_value' => $button->button_codes,
  );
  $form['button_icon'] = array(
      '#title' => t('Upload button/icon'),
      '#type' => 'managed_file',
      '#description' => t('Allowed extensions: gif png jpg jpeg'),
      '#default_value' => $button->button_icon,
      '#required' => FALSE,
      '#upload_validators' => array(
          'file_validate_extensions' => array(
              'gif png jpg jpeg',
          ),
          // Pass the maximum file size in bytes
          'file_validate_size' => array(1 * 1024 * 1024),
      ),
      '#upload_location' => 'public://sideshare/icons/',
  );
  $form['button_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enabled'),
      '#default_value' => $button->button_enabled,
  );
  
  $form['button_weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#delta' => 50,
      '#default_value' => $button->button_weight,
  );
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
  );
  return $form;
}

/**
 * Submit handler for hook_addbutton().
 */
function _sideshare_button_add_submit($form, &$form_state) {
  $buttons = unserialize(variable_get('sideshare_buttons', ''));
  
  $buttons[$form_state['values']['button_machine_name']] = new stdClass();
  $buttons[$form_state['values']['button_machine_name']]->button_machine_name = $form_state['values']['button_machine_name'];
  $buttons[$form_state['values']['button_machine_name']]->button_name = $form_state['values']['button_name'];
  $buttons[$form_state['values']['button_machine_name']]->button_codes = $form_state['values']['button_codes'];
  $buttons[$form_state['values']['button_machine_name']]->button_icon = $form_state['values']['button_icon'];
  $buttons[$form_state['values']['button_machine_name']]->button_enabled = $form_state['values']['button_enabled'];
  $buttons[$form_state['values']['button_machine_name']]->button_weight = $form_state['values']['button_weight'];
  
  variable_set('sideshare_buttons', serialize($buttons));
  // Return to buttons page.
  $form_state['redirect'] = 'admin/config/sideshare/buttons/';
}

/**
 * Callback to load existing machine name.
 */
function sideshare_button_machine_name_load($name) {
  $buttons = unserialize(variable_get('sharebar_buttons', ''));
  if (array_key_exists($name, $buttons)) {
    $button[] = $buttons[$name]->machine_name;
    return reset($button);
  }
}
