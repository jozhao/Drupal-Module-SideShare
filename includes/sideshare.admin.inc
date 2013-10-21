<?php

/**
 * @file
 * module admin.
 */

// Load form helper.
module_load_include('inc', 'sideshare', 'includes/sideshare.admin.form');

/**
 * Form builder: Configure the sideshare system.
 */
function _sideshare_settings() {
  $form = array();
  $form = array_merge($form, _subform_sideshare_display());
  
  // Customize.
  $form['sideshare_customize'] = array(
      '#type' => 'fieldset',
      '#weight' => 3,
      '#title' => t('Customize'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE
  );
  
  $form['sideshare_customize']['sideshare_twitter_username'] = array(
      '#type' => 'textfield',
      '#title' => t('Twitter Username'),
      '#size' => 60,
      '#default_value' => variable_get('sideshare_twitter_username', '')
  );
  
  return system_settings_form($form);
}

/**
 * Form builder: Buttons management.
 */
function _sideshare_button_management() {
  $form = _subform_sideshare_buttons();
  return system_settings_form($form);
}

/**
 * Provide a single block from the administration menu as a page.
 */
function _sideshare_admin_menu_block_page() {
  $item = menu_get_item();
  if ($content = system_admin_menu_block($item)) {
    $output = theme('admin_block_content', array(
        'content' => $content
    ));
  }
  else {
    $output = t('You do not have any administrative items.');
  }
  return $output;
}
