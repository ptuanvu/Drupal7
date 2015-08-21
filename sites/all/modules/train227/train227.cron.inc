<?php

/**
 * Implements hook_cron().
 */
function train227_cron()
{
  watchdog('Train227 Cron Processing', 'START');
  try {
    test_blank_employee_id();
  } catch (Exception $e) {
    watchdog('Train227 Cron Processing', 'FAILED');
  }
  watchdog('Train227 Cron Processing', 'FINISH');
}

function test_blank_employee_id() {
  $sql = "SELECT * FROM employee LIMIT 0,100";
  $result = db_query($sql);

  $queue = DrupalQueue::get('blank_employee_id_queue');

  if ($queue->numberOfItems() > 10000) {
    $queue->deleteQueue();
    $queue->createQueue();
  }

  foreach($result->fetchALl() as $key => $item) {

    if ($key % 100 == 0 && $key / 100 >= 1) {
      watchdog('Train227 Cron Processing', 'PROCESSING AT @key , @EmployeeID, Number Item in queue @queue_number', array('@key' => $key, '@EmployeeID' => $item->employee_id, '@queue_number' => $queue->numberOfItems()));
    }
    $queue->createItem($item);
  }
}

/**
 * Implements hook_cron_queue_info().
 */
function train227_cron_queue_info()
{
  $queues['blank_employee_id_queue'] = array(
    'worker callback' => 'blank_employee_id_handler',
    'time' => 1,
  );

  return $queues;
}

function blank_employee_id_handler($item) {
  if (empty($item->employee_id)) {
    watchdog('Blank EID', 'Blank Employee_ID at EID = @eid , Fullname = @fullname', array('@eid' => $item->eid, '@fullname' => $item->fullname));
  }
  if ($item->eid % 100 == 0 && $item->eid / 100 >= 1) {
    watchdog('Train227 Cron Processing', 'HANDLER AT @key , @EmployeeID', array('@key' => $item->eid, '@EmployeeID' => $item->employee_id));
  }
}
