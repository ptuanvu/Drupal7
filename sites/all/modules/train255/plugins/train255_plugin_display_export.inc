<?php
/**
 * Created by PhpStorm.
 * User: monster
 * Date: 26/08/2015
 * Time: 09:23
 */

class train255_plugin_display_export extends views_data_export_plugin_display_export {
  /**
   * Called on export initialization.
   *
   * Modifies the view query to insert the results into a table, which we call
   * the 'index', this means we essentially have a snapshot of the results,
   * which we can then take time over rendering.
   *
   * This method is essentially all the best bits of the view::execute() method.
   */
  protected function initialize_index() {
    $view = &$this->view;
    // Get views to build the query.
    $view->build();

    // Change the query object to use our custom one.
    $query_class = 'train255_plugin_query_default_batched';
    $query = new $query_class();
    // Copy the query over:
    foreach ($view->query as $property => $value) {
      $query->$property = $value;
    }
    // Replace the query object.
    $view->query = $query;

    $view->execute();
  }
}

class train255_plugin_query_default_batched extends subscription_rest_package_plugin_query {
  function execute(&$view) {
    $display_handler = &$view->display_handler;
    $external = FALSE;

    $query = $view->build_info['query'];
    $count_query = $view->build_info['count_query'];

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


        $sql = 'CREATE TABLE ' . $display_handler->index_tablename() . '(
        vde_weight BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
        id bigint(20),
        code varchar(50),
        name varchar(255),
        amount varchar(255),
        month int(11),
        telco varchar(255),
        status varchar(50),
        sms_code varchar(50),
        created_at varchar(50),
        updated_at varchar(50)
        ) ENGINE=InnoDB AUTO_INCREMENT=1700 DEFAULT CHARSET=utf8';

        db_query($sql);
        foreach($json_output['list'] as $key => $item) {
          db_insert($display_handler->index_tablename())
            ->fields(array(
              'id' => $item['id'],
              'code' => $item['code'],
              'name' => $item['name'],
              'amount' => $item['amount'],
              'month' => $item['month'],
              'telco' => $item['telco'],
              'status' => $item['status'],
              'sms_code' => $item['sms_code'],
              'created_at' => $item['created_at'],
              'updated_at' => isset($item['updated_at']) ? $item['updated_at'] : ''
            ))
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