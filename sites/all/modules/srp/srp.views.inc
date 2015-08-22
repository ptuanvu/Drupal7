<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 * Implementation of hook_views_plugins().
 */
function views_data_export_views_plugins() {
  $path = drupal_get_path('module', 'srp');

  $style_defaults = array(
    'path' => $path . '/plugins',
    'parent' => 'srp',
    'theme' => 'srp',
    'theme path' => $path . '/theme',
    'theme file' => 'srp.theme.inc',
    'uses row plugin' => FALSE,
    'uses fields' => TRUE,
    'uses options' => TRUE,
    'type' => 'srp',
  );

  return array(
    'display' => array (
      'srp' => array(
        'title' => t('Data export'),
        'help' => t('Export the view results to a file. Can handle very large result sets.'),
        'path' => $path . '/plugins',
        'handler' => 'srp_plugin_display_export',
        'parent' => 'feed',
        'uses hook menu' => TRUE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'admin' => t('Data export'),
        'help topic' => 'display-srp-data-export',
      ),
    ),
    'style' => array(
      'srp' => array(
        // this isn't really a display but is necessary so the file can
        // be included.
        'no ui' => TRUE,
        'handler' => 'srp_plugin_style_export',
        'path' => $path . '/plugins',
        'theme path' => $path . '/theme',
        'theme file' => 'srp.theme.inc',
        'type' => 'normal',
      ),
      'srp_csv' => array(
        'title' => t('CSV file'),
        'help' => t('Display the view as a comma separated list.'),
        'handler' => 'srp_plugin_style_export_csv',
        // Views Data Export element that will be used to set additional headers when serving the feed.
        'export headers' => array('Content-type' => 'text/csv; charset=utf-8'),
        // Views Data Export element mostly used for creating some additional classes and template names.
        'export feed type' => 'csv',
        'export feed text' => 'CSV',
        'export feed file' => '%view.csv',
        'export feed icon' => drupal_get_path('module', 'srp') . '/images/csv.png',
        'additional themes' => array(
          'srp_csv_header' => 'style',
          'srp_csv_body' => 'style',
          'srp_csv_footer' => 'style',
        ),
        'additional themes base' => 'srp_csv',
      ) + $style_defaults,
    )
  );
}
