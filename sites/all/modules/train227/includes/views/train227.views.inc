<?php

/**
 * Implements hook_views_data().
 */
function train227_views_data()
{
  $data['employee']['table']['group'] = t('Employee Ex Table');

  $data['employee']['table']['base'] = array(
    'field' => 'eid',
    'title' => t('Employee Ex Table'),
    'weight' => -10,
    'access query tag' => 'view any employee entity',
//    'defaults' => array(
//      'field' => 'fullname',
//    ),
//    'help' => t('Employee table for train246'),
  );

  $data['employee']['table']['entity type'] = 'employee';

  $data['employee']['employee_id'] = array(
    'title' => t('Employee ID'),
    'help' => 'Employee ID field',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'view_handler_soft',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['employee']['fullname'] = array(
    'title' => t('Fullname'),
    'help' => t('The fullname field'),
    'field' => array(
//      'field' => 'fullname',
//      'group' => t('Content'),
//      'handler' => 'views_handler_field',
      'handler' => 'views_handler_field_employee_name',
      'click sortable' => TRUE,
      //'link_to_node default' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'view_handler_soft',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['employee']['dayofbirth'] = array(
    'title' => t('Birthday'),
    'help' => 'Birthday field',
    'field' => array(
      'handler' => 'views_handler_field',
//      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'view_handler_soft',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['employee']['gender'] = array(
    'title' => t('Gender'),
    'help' => 'Gender field',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'view_handler_soft',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['employee']['uid'] = array(
    'title' => t('Author'),
    'help' => 'Author field',
    'relationship' => array(
      'base' => 'users',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Default label for relationship'),
      'title' => t('Employee rela users'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'field' => array(
      'handler' => 'views_handler_field_user',
    ),
  );

  $data['employee']['created'] = array(
    'title' => t('Created'),
    'help' => t('Created day'),
    'field' => array(
      'handler' => 'views_handler_field_date',
//      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}
