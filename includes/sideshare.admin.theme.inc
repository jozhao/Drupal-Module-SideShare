<?php

/**
 * @file
 * admin theme.
 */

/**
 * Theme the share buttons admin page.
 *
 * @ingroup themeable
 */
function theme_sideshare_admin_buttons_list($variables = NULL) {
  $out = '';
  $out .= '<div>' . l(t('Add New Button'), 'admin/config/sideshare/buttons/add') . '</div>';
  $buttons = unserialize(variable_get('sideshare_buttons', _sideshare_buttons_default()));
  if (is_array($buttons) && count($buttons)) {
    usort($buttons, "_sideshare_cmp_up");
    foreach ( $buttons as $key => $value ) {
      $row = array();
      $row[] = array(
          'data' => ($value->button_enabled ? t('Yes') : t('No'))
      );
      $row[] = array(
          'data' => $value->button_name
      );
      $row[] = array(
          'data' => _sideshare_display_button($value->button_icon, $value->button_name)
      );
      $row[] = array(
          'data' => $value->button_weight
      );
      $row[] = array(
          'data' => l(t('Edit'), 'admin/config/sideshare/button/edit/' . $value->button_machine_name) . ' | ' . l(t('Delete'), 'admin/config/sideshare/button/del/' . $value->button_machine_name)
      );
      $rows[] = $row;
    }
  }
  if (isset($rows) && count($rows)) {
    $header = array(
        t('Enabled'),
        t('Name'),
        t('Icon'),
        t('Weight'),
        t('Actions')
    );
    $out .= theme('table', array(
        'header' => $header,
        'rows' => $rows
    ));
  }
  else {
    $out .= '<b>' . t('No data') . '</b>';
  }
  return $out;
}
