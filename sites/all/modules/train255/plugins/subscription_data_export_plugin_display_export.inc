<?php

/**
 * @file
 * Contains the bulk export display plugin.
 *
 * This allows views to be rendered in parts by batch API.
 */

public class subscription_data_export_plugin_display_export extends views_plugin_display_feed {
  /**
   * Define the option for this view.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['use_batch'] = array('default' => 'batch');
    $options['items_per_page'] = array('default' => '0');
    $options['return_path'] = array('default' => '');
    $options['style_plugin']['default'] = 'subscription_data_export_csv';

    // This is the default size of a segment when doing a batched export.
    $options['segment_size']['default'] = 20;

    if (isset($options['defaults']['default']['items_per_page'])) {
      $options['defaults']['default']['items_per_page'] = FALSE;
    }

    return $options;
  }

  /**
   * Provide the summary for page options in the views UI.
   *
   * This output is returned as an array.
   */
  function options_summary(&$categories, &$options) {
    // It is very important to call the parent function here:
    parent::options_summary($categories, $options);

    $categories['page']['title'] = t('Data export settings');

    $options['use_batch'] = array(
      'category' => 'page',
      'title' => t('Batched export'),
      'value' => ($this->get_option('use_batch') == 'batch' ? t('Yes') : t('No')),
    );

    if (!$this->is_compatible() && $this->get_option('use_batch')) {
      $options['use_batch']['value'] .= ' <strong>' . t('(Warning: incompatible)') . '</strong>';
    }
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_form($form, $form_state);

    switch ($form_state['section']) {
      case 'use_batch':
        $form['#title'] .= t('Batched export');
        $form['use_batch'] = array(
          '#type' => 'radios',
          '#description' => t(''),
          '#default_value' => $this->get_option('use_batch'),
          '#options' => array(
            'no_batch' => t('Export data all in one segment. Possible time and memory limit issues.'),
            'batch' => t('Export data in small segments to build a complete export. Recommended for large exports sets (1000+ rows)'),
          ),
        );
        // Allow the administrator to configure the number of items exported per batch.
        $form['segment_size'] = array(
          '#type' => 'select',
          '#title' => t('Segment size'),
          '#description' => t('If each row of your export consumes a lot of memory to render, then reduce this value. Higher values will generally mean that the export completes in less time but will have a higher peak memory usage.'),
          '#options' => drupal_map_assoc(range(1, 500)),
          '#default_value' => $this->get_option('segment_size'),
          '#process' => array('ctools_dependent_process'),
          '#dependency' => array(
            'radio:use_batch' => array('batch')
          ),
        );
        $form['return_path'] = array(
          '#title' => t('Return path'),
          '#type' => 'textfield',
          '#description' => t('Return path after the batched operation, leave empty for default. This path will only be used if the export URL is visited directly, and not by following a link when attached to another view display.'),
          '#default_value' => $this->get_option('return_path'),
          '#dependency' => array(
            'radio:use_batch' => array('batch')
          ),
        );
        if (!$this->is_compatible()) {
          $form['use_batch']['#disabled'] = TRUE;
          $form['use_batch']['#default_value'] = 'no_batch';
          $form['use_batch']['message'] = array (
            '#type' => 'markup',
            '#markup' => theme('views_data_export_message', array('message' => t('The underlying database (!db_driver) is incompatible with the batched export option and it has been disabled.', array('!db_driver' => $this->_get_database_driver())), 'type' => 'warning')),
            '#weight' => -10,
          );
        }
        break;

      case 'cache':
        // We're basically going to disable using cache plugins, by disabling
        // the UI.
        if (isset($form['cache']['type']['#options'])) {
          foreach ($form['cache']['type']['#options'] as $id => $v) {
            if ($id != 'none') {
              unset($form['cache']['type']['#options'][$id]);
            }
            $form['cache']['type']['#description'] = t("Views data export isn't currently compatible with caching plugins.");
          }
        }
        break;

    }
  }

  function options_submit($form, &$form_state) {
    parent::options_submit($form, $form_state);
    switch($form_state['section']) {
      case 'use_batch':
        $this->set_option('use_batch', $form_state['values']['use_batch']);
        $this->set_option('segment_size', $form_state['values']['segment_size']);
        $this->set_option('return_path', $form_state['values']['return_path']);
        break;
    }
  }

  function get_option($option) {
    // Force people to never use caching with Views data export. Sorry folks,
    // but it causes too many issues for our workflow. If you really want to add
    // caching back, then you can subclass this display handler and override
    // this method to add it back.
    if ($option == 'cache') {
      return array('type' => 'none');
    }

    return parent::get_option($option);
  }
  /**
   * Checks the driver of the database underlying
   * this query and returns FALSE if it is imcompatible
   * with the approach taken in this display.
   * Basically mysql & mysqli will be fine, pg will not
   */
  function is_compatible() {
    $incompatible_drivers = array (
      //'pgsql',
    );
    $db_driver = $this->_get_database_driver();
    return !in_array($db_driver, $incompatible_drivers);
  }

  function render() {
    parent::render();
  }

  function query() {
    parent::query();
  }

  function execute() {
    parent::execute();
  }

  function preview() {
    parent::preview();
  }

}