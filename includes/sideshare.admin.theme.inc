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
function theme_sideshare_buttons_list($variables = NULL) {
  $out = '';
  $out .= '<div>' . l(t('Add New Button'), 'admin/config/sideshare/buttons/add') . '</div>';
  $buttons = unserialize(variable_get('sideshare_buttons', ''));
  if (is_array($buttons) && count($buttons)) {
    usort($buttons, "sideshare_cmp_up");
    foreach ( $buttons as $key => $value ) {
      $row = array();
      $row[] = array(
          'data' => ($value->enabled ? t('Yes') : t('No')),
      );
      $row[] = array(
          'data' => $value->name,
      );
      $row[] = array(
          'data' => $value->big_button,
      );
      $row[] = array(
          'data' => $value->small_button,
      );
      $row[] = array(
          'data' => $value->weight,
      );
      $row[] = array(
          'data' => l(t('Edit'), 'admin/config/sideshare/button/edit/' . $value->machine_name) . ' | ' . l(t('Delete'), 'admin/config/sideshare/button/del/' . $value->machine_name),
      );
      $rows[] = $row;
    }
  }
  if (isset($rows) && count($rows)) {
    $header = array(
        t('Enabled'),
        t('Name'),
        t('Big Button'),
        t('Small Button'),
        t('Weight'),
        t('Actions'),
    );
    $out .= theme('table', array(
        'header' => $header,
        'rows' => $rows,
    ));
  }
  else {
    $out .= '<b>' . t('No data') . '</b>';
  }
  return $out;
}
