<?php
/**
 * Created by PhpStorm.
 * User: monster
 * Date: 23/08/2015
 * Time: 11:27
 */

class srp_plugin_display_export extends views_plugin_display_feed {

  public $batched_execution_state;
  var $weight_field_alias = '';
  var $field_aliases = array();
  var $_output_file = '';

  var $srp_cached_view_loaded;
  var $errors = array();

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

  function render() {
    if (!$this->is_batched()) {
      $result = parent::render();
      if (empty($this->view->live_preview)) {
        $this->add_http_headers();
      }
      return $result;
    }

    $this->view->build();

    switch($this->batched_execution_state->batch_state) {
      case SRP_BODY:
        $output = $this->view->style_plugin->render_body();
        break;
      case SRP_HEADER:
        $output = $this->view->style_plugin->render_header();
        break;
      case SRP_FOOTER:
        $output = $this->view->style_plugin->render_footer();
        break;
    }

    return $output;
  }

  function add_http_headers() {
    // Ask the style plugin to add any HTTP headers if it wants.
    if (method_exists($this->view->style_plugin, 'add_http_headers')) {
      $this->view->style_plugin->add_http_headers();
    }
  }

  function is_batched() {
    if ($this->get_option('use_batch') == 'batch') {
      return TRUE;
    }
    return FALSE;
  }

  function defaultable_sections($section = NULL) {
    if (in_array($section, array('items_per_page', 'offset', 'use_pager', 'pager_element',))) {
      return FALSE;
    }

    return parent::defaultable_sections($section);
  }

  function get_style_type() { return 'srp'; }

  function query() {

    if (!$this->is_batched()) {
      return parent::query();
    }

    // Make the query distinct if the option was set.
    if ($this->get_option('distinct')) {
      $this->view->query->set_distinct();
    }

    if (!empty($this->batched_execution_state->batch_state) && !empty($this->batched_execution_state->sandbox['weight_field_alias'])) {

      switch ($this->batched_execution_state->batch_state) {
        case SRP_BODY:
        case SRP_HEADER:
        case SRP_FOOTER:
          // Tell views its been executed.
          $this->view->executed = TRUE;

          // Grab our results from the index, and push them into the view result.
          // TODO: Handle external databases.
          $result = db_query_range('SELECT * FROM {' . $this->index_tablename() . '} ORDER BY ' . $this->batched_execution_state->sandbox['weight_field_alias'] . ' ASC', 0, $this->get_option('segment_size'));
          $this->view->result = array();
          foreach ($result as $item_hashed) {
            $item = new stdClass();
            // We had to shorten some of the column names in the index, restore
            // those now.
            foreach ($item_hashed as $hash => $value) {
              if (isset($this->batched_execution_state->sandbox['field_aliases'][$hash])) {
                $item->{$this->batched_execution_state->sandbox['field_aliases'][$hash]} = $value;
              }
              else {
                $item->{$hash} = $value;
              }
            }
            // Push the restored $item in the views result array.
            $this->view->result[] = $item;
          }
          $this->view->_post_execute();
          break;
      }
    }
  }

  function preview() {
    if (!$this->is_batched()) {
      // Can replace with return parent::preview() when views 2.12 lands.
      if (!empty($this->view->live_preview)) {
        // Change the items per page.
        $this->view->set_items_per_page(20);
        // Force a pager to be used.
        $this->set_option('pager', array('type' => 'some', 'options' => array()));
        return '<p>' . t('A maximum of 20 items will be shown here, all results will be shown on export.') . '</p><pre>' . check_plain($this->view->render()) . '</pre>';
      }
      return $this->view->render();
    }
    return '';
  }

  function execute() {
    if (!$this->is_batched()) {
      return parent::execute();
    }

    // Try and get a batch context if possible.
    $eid = !empty($_GET['eid']) ? $_GET['eid'] :
      (!empty($this->batched_execution_state->eid) ? $this->batched_execution_state->eid : FALSE);
    if ($eid) {
      $this->batched_execution_state = srp_get($eid);
    }

    // First time through
    if (empty($this->batched_execution_state)) {
      $output = $this->execute_initial();
    }

    // Last time through
    if ($this->batched_execution_state->batch_state == SRP_FINISHED) {
      $output = $this->execute_final();
    }
    // In the middle of processing
    else {
      $output = $this->execute_normal();
    }

    //Ensure any changes we made to the database sandbox are saved
    srp_update($this->batched_execution_state);

    return $output;

  }


  function execute_initial() {
    $this->batched_execution_state = srp_new($this->view->name, $this->view->current_display, $this->outputfile_create());
    srp_view_store($this->batched_execution_state->eid, $this->view);

    $this->initialize_index();
    $this->batched_execution_state->sandbox['max'] = db_query('SELECT COUNT(*) FROM {' . $this->index_tablename() . '}')->fetchField();

    list($usec, $sec) = explode(' ', microtime());
    $this->batched_execution_state->sandbox['started'] = (float) $usec + (float) $sec;

    $querystring = array(
      'eid' => $this->batched_execution_state->eid,
      'return-url' => NULL,
    );

    if ($this->get_option('return_path')) {
      $querystring['return-url'] = $this->get_option('return_path');
    }
    else if (!empty($_GET['attach']) && isset($this->view->display[$_GET['attach']])) {
      // Get the path of the attached display:
      $querystring['return-url'] = $this->view->get_url(NULL, $this->view->display[$_GET['attach']]->handler->get_path());
    }

    $batch = array(
      'operations' => array (
        array('_srp_batch_process', array($this->batched_execution_state->eid, $this->view->current_display,  $this->view->get_exposed_input())),
      ),
      'title' => t('Building export'),
      'init_message' => t('Export is starting up.'),
      'progress_message' => t('Exporting @percentage% complete,'),
      'error_message' => t('Export has encountered an error.'),
    );

    srp_update($this->batched_execution_state);

    $final_destination = $this->view->get_url();
    $batch['view_name'] = $this->view->name;
    $batch['exposed_filters'] = $this->view->get_exposed_input();
    $batch['display_id'] = $this->view->current_display;
    $batch['eid'] = $this->batched_execution_state->eid;
    $batch_redirect = array($final_destination, array('query' => $querystring));
    drupal_alter('srp_batch', $batch, $batch_redirect);

    if (!empty($batch)) {
      batch_set($batch);
      // batch_process exits
      batch_process($batch_redirect);
    }
  }

  function file_load($fid) {
    return file_load($fid);
  }

  function index_tablename() {
    return SRP_INDEX_TABLE_PREFIX . $this->batched_execution_state->eid;
  }

  function initialize_index() {
    $view = &$this->view;
    $view->build();

    $query_class = 'srp_plugin_query_rest_batched';

    $query = new $query_class();
    foreach($view->query as $property => $value) {
      $query->$property = $value;
    }

    $view->query = $query;
    $view->execute();
  }

  function execute_final() {
    if (!empty($_GET['download'])) {
      $this->transfer_file();
    } else {
      $this->remove_index();
      return $this->render_complete();
    }
  }

  function remove_index() {
    $ret = array();
    if (db_table_exists($this->index_tablename())) {
      db_drop_table($this->index_tablename());
    }
  }

  function render_complete() {
    $return_path = empty($_GET['return-url']) ? '' : $_GET['return-url'];

    $query = array(
      'download' => 1,
      'eid' => $this->batched_execution_state->eid,
    );

    return theme('srp_complete_page', array(
      'file' => url($this->view->get_url(), array('query' => $query)),
      'errors' => $this->errors,
      'return-url' => $return_path,
    ));
  }

  function execute_normal() {
    $output = $this->view->render();
    $this->outputfile_write($output);

    $state = &$this->batched_execution_state;
    $sandbox = &$state->sandbox;

    switch($state->batch_state) {
      case SRP_BODY:
        if (count($this->view->result) && ($sandbox['weight_field_alias'])) {
          $last = end($this->view->result);
          db_delete($this->index_tablename())
            ->condition($sandbox['weight_field_alias'], $last->{$sandbox['weight_field_alias']}, '<=')
            ->execute();

          //Upgrade progress
          $progress = db_query('SELECT COUNT(*) FROM {' . $this->index_tablename() . '}')->fetchField();
          // TODO: These next few lines are messy, clean them up.
          $progress = 0.99 - ($progress / $sandbox['max'] * 0.99);
          $progress = ((int)floor($progress * 100000));
          $progress = $progress / 100000;
          $sandbox['finished'] = $progress;
        } else {
          $progress = 0.99;
          $state->batch_state = SRP_FOOTER;
        }
        break;
      case SRP_HEADER:
        $sandbox['finished'] = 0;
        $state->batch_state = SRP_BODY;
        break;

      case SRP_FOOTER:
        $sandbox['finished'] = 1;
        $state->batch_state = SRP_FINISHED;
        break;

    }
    $sandbox['message'] = $this->compute_time_remaining($sandbox['started'], $sandbox['finished']);
  }

  function compute_time_remaining($started, $finished) {
    list($usec, $sec) = explode(' ', microtime());
    $now = (float) $usec + (float) $sec;
    $diff = round(($now - $started), 0);
    // So we've taken $diff seconds to get this far.
    if ($finished > 0) {
      $estimate_total = $diff / $finished;
      $stamp = max(1, $estimate_total - $diff);
      // Round up to nearest 30 seconds.
      $stamp = ceil($stamp / 30) * 30;
      // Set the message in the batch context.
      return t('Time remaining: about @interval.', array('@interval' => format_interval($stamp)));
    }
  }

  function outputfile_create() {
    $dir = variable_get('srp_directory', 'temporary://views_plugin_display');

    // Make sure the directory exists first.
    if (!file_prepare_directory($dir, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      $this->abort_export(t('Could not create temporary directory for result export (@dir). Check permissions.', array ('@dir' => $dir)));
    }

    $path = drupal_tempnam($dir, 'srp');

    // Save the file into the DB.
    $file = $this->file_save_file($path);

    return $file->fid;
  }

  function outputfile_path() {
    if (empty($this->_output_file)) {
      if (!empty($this->batched_execution_state->fid)) {
        // Return the filename associated with this file.
        $this->_output_file = $this->file_load($this->batched_execution_state->fid);
      }
      else {
        return NULL;
      }
    }
    return $this->_output_file->uri;
  }

  function outputfile_write($string) {
    $output_file = $this->outputfile_path();
    if (file_put_contents($output_file, $string, FILE_APPEND) === FALSE) {
      $this->abort_export(t('Could not write to temporary output file for result export (@file). Check permissions.', array ('@file' => $output_file)));
    }
  }

  function abort_export($errors) {
    // Just cause the next batch to do the clean-up
    if (!is_array($errors)) {
      $errors = array($errors);
    }
    foreach ($errors as $error) {
      drupal_set_message($error . ' ['. t('Export Aborted') . ']', 'error');
    }
    $this->batched_execution_state->batch_state = SRP_FINISHED;
  }

  function file_save_file($filepath) {
    return file_save_data('', $filepath, FILE_EXISTS_REPLACE);
  }

  function transfer_file() {
    // Build the view so we can set the headers.
    $this->view->build();
    // Arguments can cause the style to not get built.
    if (!$this->view->init_style()) {
      $this->view->build_info['fail'] = TRUE;
    }
    // Set the headers.
    $this->add_http_headers();
    file_transfer($this->outputfile_path(), array());
  }


  function field_aliases_create(&$view) {
    $all_aliases = array();
    foreach ($view->query->fields as $field) {
      if (strlen($field['alias']) > 32) {
        $all_aliases['a' . md5($field['alias'])] = $field['alias'];
      }
      else {
        $all_aliases[$field['alias']] = $field['alias'];
      }
    }
    return $all_aliases;
  }

  /**
   * Create an alias for the weight field in the index.
   *
   * This method ensures that it isn't the same as any other alias in the
   * supplied view's fields.
   */
  function _weight_alias_create(&$view) {
    $alias = 'vde_weight';
    $all_aliases = array();
    foreach ($view->query->fields as $field) {
      $all_aliases[] = $field['alias'];
    }
    // Keep appending '_' until we are unique.
    while (in_array($alias, $all_aliases)) {
      $alias .= '_';
    }
    return $alias;
  }

  function generate_value($value, $fields) {
    $row = array();
    foreach ($fields as $key => $item) {
      if (isset($value[$key])) {
        $row[$key] = $value[$key];
      }
    }

    return $row;
  }
}


class srp_plugin_query_rest_batched extends  subscription_rest_package_plugin_query {
  function execute(&$view) {
    $display_handler = &$view->display_handler;
    $external = FALSE;

    $query = $view->build_info['query'];
    $count_query = $view->build_info['count_query'];

    $data_infomations = array(
      'id' => 'bigint(20)',
      'code' => 'varchar(50)',
      'name' => 'varchar(255)',
      'amount' => 'varchar(255)',
      'month' => 'int(11)',
      'telco' => 'varchar(255)',
      'status' => 'varchar(50)',
      'sms_code' => 'varchar(50)',
      'created_at' => 'varchar(50)',
      'updated_at' => 'varchar(50)',
    );

    if ($query) {
      $view->init_pager();
      $this->pager->query();
      $start = microtime(TRUE);
      try {
        $display_handler->batched_execution_state->sandbox['weight_field_alias'] = $display_handler->_weight_alias_create($view);
        $display_handler->batched_execution_state->sandbox['field_aliases'] = $display_handler->field_aliases_create($view);
        $select_aliases = array();
        foreach ($display_handler->batched_execution_state->sandbox['field_aliases'] as $hash => $alias) {
          $select_aliases[] = "cl.$alias AS $hash";
        }
        $url = 'http://localhost:8181/subscription-rest/package/search';
        $headers = array();
        $filter = $query;

        $options = array(
          'method' => 'POST',
          'data' => !empty($filter) ? json_encode($filter) : '{}',
          'headers' => $headers,
        );
        $respone = drupal_http_request($url, $options);
        $json_output = json_decode($respone->data, true);

        $sql2 = 'CREATE TABLE ' . $display_handler->index_tablename() . '( vde_weight BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,';
        $fields = $view->query->fields;
        foreach ($fields as $key_name => $value_item) {
          $sql2 .= $key_name . ' ' . $data_infomations[$key_name] . ',';
        }
        $sql2 = substr($sql2, 0, -1);
        $sql2 .= ') ENGINE=InnoDB AUTO_INCREMENT=1700 DEFAULT CHARSET=utf8';

        db_query($sql2);
        foreach($json_output['list'] as $key => $item) {
          $row_value = $display_handler->generate_value($item, $fields);
          db_insert($display_handler->index_tablename())
            ->fields($row_value)
            ->execute();
        }
        $view->result = array();
        $this->pager->post_execute($view->result);
        if ($this->pager->use_pager()) {
          $view->total_rows = $this->pager->get_total_items();
        }
        db_add_unique_key($display_handler->index_tablename(), $display_handler->batched_execution_state->sandbox['weight_field_alias'], array($display_handler->batched_execution_state->sandbox['weight_field_alias']));
      }
      catch (Exception $e) {
        $view->result = array();
        debug('Exception: ' . $e->getMessage());
      }
    }
    $view->execute_time = microtime(TRUE) - $start;
  }
}