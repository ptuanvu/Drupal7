<?php

/**
 * @file
 * Theme related functions for processing our output style plugins.
 *
 * Views bug: http://drupal.org/node/593336
 */


/**
 * Theme a status message
 */
function theme_srp_message($var) {
  $output = '';
  $output .= '<div class="messages status ' . $var['type'] . '">';
  $output .= $var['message'];
  $output .= '</div>';
  return $output;
}

/**
 * Theme a feed link.
 *
 * This theme function uses the theme pattern system to allow it to be
 * overidden in a more specific manner. The options for overiding this include
 * providing per display id; per type; per display id and per type.
 *
 * e.g.
 * For the view "export_test" with the display "page_1" and the type "csv" you
 * would have the following options.
 *   views_data_export_feed_icon__export_test__page_1__csv
 *   views_data_export_feed_icon__export_test__page_1
 *   views_data_export_feed_icon__export_test__csv
 *   views_data_export_feed_icon__page_1__csv
 *   views_data_export_feed_icon__page_1
 *   views_data_export_feed_icon__csv
 *   views_data_export_feed_icon
 *
 * @ingroup themeable
 */
function theme_srp_feed_icon($variables) {
  extract($variables, EXTR_SKIP);
  $url_options = array('html' => TRUE);
  if ($query) {
    $url_options['query'] = $query;
  }
  $image = theme('image', array('path' => $image_path, 'alt' => $text, 'title' => $text));
  return l($image, $url, $url_options);
}

/**
 * Theme callback for the export complete page.
 *
 * @param $file
 *  Link to output file
 */
function theme_srp_complete_page($variables) {
  extract($variables, EXTR_SKIP);
  drupal_set_title(t('Subscription data export successful'));
  drupal_add_html_head(array('#tag' => 'meta', '#attributes' => array('http-equiv' =>"Refresh", 'content' => '3;url='. $file)), 'srp_download');
  $output = '';
  $output .= '<p>';
  $output .= t('Your export has been created. View/download the file <a href="@link">here</a> (will automatically download in 3 seconds.)', array('@link' => $file));
  $output .= '</p>';

  if (!empty($return_url)) {
    $output .= '<p>';
    $output .= l(t('Return to previous page'), $return_url);
    $output .= '</p>';
  }
  return $output;
}


function template_preprocess_srp(&$vars) {
  $vars['header'] = $vars['rows']['header'];
  $vars['body'] = $vars['rows']['body'];
  $vars['footer'] = $vars['rows']['footer'];

  $view     = $vars['view'];
  $fields   = &$view->field;
}

function template_preprocess_srp_csv_header(&$vars) {
  _views_data_export_header_shared_preprocess($vars);

  // Make sure we catch saved options that are misspelled. LEGACY
  if (isset($vars['options']['seperator'])) {
    $vars['options']['separator'] = $vars['options']['seperator'];
  }
  // Support old misspelled templates. LEGACY
  $vars['seperator'] =
    $vars['separator'] = $vars['options']['separator'];

  // Special handling when quoted values are involved.
  if ($vars['options']['quote']) {
    $wrap = '"';
    $replace_value = '""';
  }
  else {
    $wrap = '';
    $replace_value = '';
  }

  // Format header values.
  foreach ($vars['header'] as $key => $value) {
    $output = decode_entities($value);
    $output = (empty($vars['options']['keep_html'])) ? strip_tags($output) : $output;
    if (!empty($vars['options']['trim'])) {
      $output = trim($output);
    }
    if (!empty($vars['options']['encoding']) && function_exists('iconv')) {
      switch($vars['options']['encoding']) {
        case 'utf8_decode':
          $converted = utf8_decode($output);
          break;
        default:
          $converted = iconv("UTF-8", $vars['options']['encoding'], $output);
          break;
      }
      if ($converted !== FALSE) {
        $output = $converted;
      }
    }
    $vars['header'][$key] = $wrap . str_replace('"', $replace_value, $output) . $wrap;
  }
}

function template_preprocess_srp_csv_body(&$vars) {
  _views_data_export_body_shared_preprocess($vars);

  // Make sure we catch saved options that are misspelled. LEGACY
  if (isset($vars['options']['seperator'])) {
    $vars['options']['separator'] = $vars['options']['seperator'];
  }
  // Support old misspelled templates. LEGACY
  $vars['seperator'] =
    $vars['separator'] = $vars['options']['separator'];

  // Special handling when quoted values are involved.
  if ($vars['options']['quote']) {
    $wrap = '"';
    $replace_value = '""';
  }
  else {
    $wrap = '';
    $replace_value = '';
  }

  // Format row values.
  foreach ($vars['themed_rows'] as $i => $values) {
    foreach ($values as $j => $value) {
      $output = decode_entities($value);
      $output = (empty($vars['options']['keep_html'])) ? strip_tags($output) : $output;
      if (!empty($vars['options']['trim'])) {
        $output = trim($output);
      }

      if (!empty($vars['options']['encoding']) && function_exists('iconv')) {
        switch($vars['options']['encoding']) {
          case 'utf8_decode':
            $converted = utf8_decode($output);
            break;
          default:
            $converted = iconv("UTF-8", $vars['options']['encoding'], $output);
            break;
        }
        if ($converted !== FALSE) {
          $output = $converted;
        }
      }
      if (!empty($vars['options']['replace_newlines'])) {
        $output = str_replace("\n", $vars['options']['newline_replacement'], $output);
      }
      $vars['themed_rows'][$i][$j] = $wrap . str_replace('"', $replace_value, $output) . $wrap;
    }
  }
}

/**
 * Preprocess csv output template.
 */
function template_preprocess_srp_csv(&$vars) {
  // TODO Replace items with themed_rows.
  _views_data_export_shared_preprocess($vars);

  // Make sure we catch saved options that are misspelled. LEGACY
  if (isset($vars['options']['separator'])) {
    $vars['options']['separator'] = $vars['options']['seperator'];
  }
  // Support old misspelled templates. LEGACY
  $vars['seperator'] =
    $vars['separator'] = $vars['options']['separator'];

  // Special handling when quoted values are involved.
  if ($vars['options']['quote']) {
    $wrap = '"';
    $replace_value = '""';
  }
  else {
    $wrap = '';
    $replace_value = '';
  }

  // Format header values.
  foreach ($vars['header'] as $key => $value) {
    $output = decode_entities(strip_tags($value));
    if ($vars['options']['trim']) {
      $output = trim($output);
    }
    if (!empty($vars['options']['encoding']) && function_exists('iconv')) {
      switch($vars['options']['encoding']) {
        case 'ASCII':
          $converted = iconv("UTF-8", "ASCII//TRANSLIT", $output);
          if ($converted !== FALSE) {
            $output = $converted;
          }
          break;
      }
    }
    $vars['header'][$key] = $wrap . str_replace('"', $replace_value, $output) . $wrap;
  }

  // Format row values.
  foreach ($vars['themed_rows'] as $i => $values) {
    foreach ($values as $j => $value) {
      $output = decode_entities(strip_tags($value));
      if ($vars['options']['trim']) {
        $output = trim($output);
      }
      if (!empty($vars['options']['encoding']) && function_exists('iconv')) {
        switch($vars['options']['encoding']) {
          case 'ASCII':
            $converted = iconv("UTF-8", "ASCII//TRANSLIT", $output);
            if ($converted !== FALSE) {
              $output = $converted;
            }
            break;
        }
      }
      $vars['themed_rows'][$i][$j] = $wrap . str_replace('"', $replace_value, $output) . $wrap;
    }
  }
}

/**
 * Shared helper function for export preprocess functions.
 */
function _srp_header_shared_preprocess(&$vars) {
  $view     = $vars['view'];
  $fields   = &$view->field;

  $vars['header'] = array();
  foreach ($fields as $key => $field) {
    if (empty($field->options['exclude'])) {
      $vars['header'][$key] = check_plain($field->label());
    }
  }

}

/**
 * Shared helper function for export preprocess functions.
 */
function _srp_body_shared_preprocess(&$vars) {
  $view     = $vars['view'];
  $fields   = &$view->field;
  $hide_empty_support = !empty($vars['hide_empty_support']);

  $rows = $vars['rows'];

  $vars['themed_rows'] = array();
  $keys = array_keys($fields);
  foreach ($rows as $num => $row) {
    $vars['themed_rows'][$num] = array();

    foreach ($keys as $id) {
      if (empty($fields[$id]->options['exclude'])) {
        $content = $view->style_plugin->rendered_fields[$num][$id];

        if ($hide_empty_support && !empty($fields[$id]->options['hide_empty'])) {
          if ($fields[$id]->is_value_empty($content, $fields[$id]->options['empty_zero'])) {
            continue;
          }
        }

        $vars['themed_rows'][$num][$id] = $content;
      }
    }
  }
}
