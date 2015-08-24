<?php
/**
 * Created by PhpStorm.
 * User: monster
 * Date: 23/08/2015
 * Time: 11:27
 */

class srp_plugin_display_export extends views_plugin_display_feed {
  function option_definition() {
    $options = parent::option_definition();

    $options['use_batch'] = array(
      'default' => 'no_batch',
    );

    $options['items_per_page'] = array(
      'default' => 0
    );

    $options['return_path'] = array(
      'default' => ''
    );

    $options['segment_size'] = array(
      'default' => 20
    );

    if (isset($options['defaults']['default']['items_per_page'])) {
      $options['defaults']['default']['items_per_page'] = FALSE;
    }
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['use_batch'] = array(
      '#type' => 'radios',
      '#title' => 'Use Batch?',
      '#description' => 'Check use batch if you wana use batch to export your data',
      '#options' => array(
        'no_batch' => t('Do not use batch'),
        'batch' => t('Use batch'),
      ),
      '#default_value' => $this->get_option('use_batch'),
    );

    $form['segment_size'] = array(
      '#type' => 'select',
      '#title' => t('Segment Size'),
      '#description' => 'Choose segment size',
      '#options' => drupal_map_assoc(range(1, 500)),
      '#default_value' => $this->get_option('segment_size'),
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array(
        'radio:use_batch' => array('batch')
      )
    );

    $form['return_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Return path'),
      '#description' => 'Return page when exporting done',
      '#default_value' => $this->get_option('return_path'),
      '#dependency' => array(
        'radio:use_batch' => array('batch'),
      )
    );
  }

  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);
    $this->set_option('use_batch', $form_state['values']['use_batch']);
    $this->set_option('segment_size', $form_state['values']['segment_size']);
    $this->set_option('return_path', $form_state['values']['return_path']);
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

  function defaultable_sections($section = NULL) {
    if (in_array($section, array('items_per_page', 'offset', 'use_pager', 'pager_element',))) {
      return FALSE;
    }

    return parent::defaultable_sections($section);
  }

  function get_style_type() { return 'srp'; }

}