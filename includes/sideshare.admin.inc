<?php

/**
 * @file
 * module admin.
 */

/**
 * Form builder: Configure the sideshare system.
 */
function sideshare_settings() {

	// Sideshare display rules.
	$form['sideshare_display'] = array(
			'#type' => 'fieldset',
			'#weight' => 1,
			'#title' => t('Display'),
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
		foreach ($node_names as $key => $value) {
			$form['sideshare_display']['nodetypes']['sideshare_posts_' . $node_types[$key]->type . '_enabled'] = array(
					'#type' => 'checkbox',
					'#title' => t('Automatically add sideshare to content type @value (only affects content type @value)', array('@value' => $value)),
					'#default_value' => variable_get('sideshare_posts_' . $node_types[$key]->type . '_enabled', TRUE),
			);
		}
	}

	// Customize.
	$form['sideshare_customize'] = array(
			'#type' => 'fieldset',
			'#weight' => 3,
			'#title' => t('Customize'),
			'#collapsible' => TRUE,
			'#collapsed' => TRUE,
	);

	$form['sideshare_customize']['sideshare_twitter_username'] = array(
			'#type' => 'textfield',
			'#title' => t('Twitter Username'),
			'#size' => 60,
			'#default_value' => variable_get('sideshare_twitter_username', 'decarbonise'),
	);

	return system_settings_form($form);
}

/**
 * Provide a single block from the administration menu as a page.
 */
function sideshare_admin_menu_block_page() {
  $item = menu_get_item();
  if ($content = system_admin_menu_block($item)) {
    $output = theme('admin_block_content', array('content' => $content));
  }
  else {
    $output = t('You do not have any administrative items.');
  }
  return $output;
}
