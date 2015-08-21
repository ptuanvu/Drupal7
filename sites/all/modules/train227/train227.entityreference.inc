<?php

/**
 * Implements hook_field_formatter_info().
 */
function train227_field_formatter_info()
{
  return array(
    'employee_default' => array(
      'label' => t('Employee Default'),
      'field types' => array('entityreference'),
      'settings' => array(
        'view_mode' => 'tweaky',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function train227_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state)
{
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();

  $entity_info = entity_get_info('employee');
  $vms = $entity_info['view modes'];

  $options = array();
  foreach ($vms as $key => $vm) {
    $options[$key] = $key;
  }

  $element['view_mode'] = array(
    '#type' => 'select',
    '#title' => t('View Mode'),
    '#description' => 'Viewmode of employee',
    '#default_value' => $settings['view_mode'],
    '#options' => $options,
  );

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function train227_field_formatter_settings_summary($field, $instance, $view_mode)
{
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = t('View Mode @vm', array('@vm' => $settings['view_mode']));
  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function train227_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display)
{
  $settings = $display['settings'];
  switch ($display['type']) {
    case 'employee_default' :

      if (!empty($entity->{$instance['field_name']})) {
        $entity_mod = employee_load($entity->{$instance['field_name']}[$langcode][0]['target_id']);

        if (!empty($entity_mod)) {
          $entity->content['employee_info'] = array();
          $entity->content['employee_info'] += employee_view($entity_mod, $settings['view_mode']);
        }
      }

      module_invoke_all('entity_view', $entity, $entity_type, 'default');
      drupal_alter(array('employee_view', 'entity_view'),
        $entity->content, $entity_type);

      break;
  }

  return $entity->content;
}