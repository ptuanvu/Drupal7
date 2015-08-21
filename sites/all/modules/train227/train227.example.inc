<?php

function example_for_query_entity() {
  $query = new EntityFieldQuery();
  $date = new DateTime();

  $datetime_start = new DateTime(date("Y-m-1" ));
  $datetime_end = new DateTime(date("Y-m-t" ));
  // strtotime(date("Y-m-1", strtotime("0 month") ));
  $result = $query
    ->entityCondition('entity_type', 'employee')
    ->propertyCondition('uid', '1', '=')
    ->propertyCondition('created', array($datetime_start->format('U'), $datetime_end->format('U')), 'BETWEEN')
    ->execute();

  if (isset($result['employee'])) {
    $news_items_nids = array_keys($result['employee']);
    $news_items = entity_load('employee', $news_items_nids);
  }
  return employee_view_multiple($news_items);
}