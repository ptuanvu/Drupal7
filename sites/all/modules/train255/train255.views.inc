<?php
/**
 * Created by PhpStorm.
 * User: monster
 * Date: 21/08/2015
 * Time: 15:55
 */

/**
 * Implements hook_views_plugins().
 */
function train255_views_plugins()
{
  $path = drupal_get_path('module', 'train255');
  $default_style = array(
    'path' => $path . '/plugins',
    'parent' => 'subscription_data_export',
    'theme' => 'subscription_data_export',
    'theme path' => $path . '/theme',
    'theme file' => 'subscription_data_export.theme.inc',
    'uses row plugin' => FALSE,
    'uses fields' => TRUE,
    'uses options' => TRUE,
    'type' => 'data_export',
  );
  return array(
    'display' => array(
      'subscription_data_export' => array(
        'title' => t('Subscription data export'),
        'help' => t('Export the view results to a file. Can handle very large result sets.'),
        'path' => $path . '/plugins',
        'handler' => 'subscription_data_export_plugin_display_export',
        'parent' => 'feed',
        'uses hook menu' => TRUE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'admin' => t('Data export'),
        'help topic' => 'display-data-export',
      )
    ),
    'style' => array(
      'subscription_data_export' => array(
        'no ui' => TRUE,
        'handler' => 'subscription_data_export_plugin_style_export',
        'path' => $path . '/plugins',
        'theme path' => $path . '/theme',
        'theme file' => 'subscription_data_export.theme.inc',
        'type' => 'normal',
      ),
      'subscription_data_export_csv' => array(
        'title' => t('CSV file'),
        'help' => t('Display the view as a comma separated list.'),
        'handler' => 'subscription_data_export_plugin_style_export_csv',
        // Views Data Export element that will be used to set additional headers when serving the feed.
        'export headers' => array('Content-type' => 'text/csv; charset=utf-8'),
        // Views Data Export element mostly used for creating some additional classes and template names.
        'export feed type' => 'csv',
        'export feed text' => 'CSV',
        'export feed file' => '%view.csv',
        'export feed icon' => drupal_get_path('module', 'views_data_export') . '/images/csv.png',
        'additional themes' => array(
          'views_data_export_csv_header' => 'style',
          'views_data_export_csv_body' => 'style',
          'views_data_export_csv_footer' => 'style',
        ),
        'additional themes base' => 'views_data_export_csv',
      ) + $default_style
    )
  );
}