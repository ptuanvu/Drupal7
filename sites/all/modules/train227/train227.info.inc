<?php
/**
 * Implements hook_entity_property_info().
 */
function train227_entity_property_info_alter(&$info)
{

  $properties = &$info['employee']['properties'];

  $properties['eid'] = array(
    'label' => t('EID'),
    'type' => 'integer',
    'description' => t('Primary key EID'),
    'schema field' => 'eid',
  );

  $properties['employee_id'] = array(
    'label' => t('Employee ID'),
    'type' => 'text',
    'description' => t('Employee ID'),
    'schema field' => 'employee_id',
  );

  $properties['gender'] = array(
    'label' => t('Gender'),
    'type' => 'text',
    'description' => t('Gender'),
    'schema field' => 'gender',
  );

  $properties['fullname'] = array(
    'label' => t('Fullname'),
    'type' => 'text',
    'description' => t('Fullname'),
    'schema field' => 'fullname',
  );
  $properties['dayofbirth'] = array(
    'label' => t('Day of birth'),
    'type' => 'text',
    'description' => t('Day of birth field'),
    'schema field' => 'dayofbirth',
  );
  $properties['created'] = array(
    'label' => t('Created'),
    'type' => 'integer',
    'description' => t("The employee's created time."),
    'schema field' => 'created',
  );
  $properties['type'] = array(
    'label' => t('Type'),
    'type' => 'text',
    'description' => t('Bundle type'),
    'schema field' => 'type',
  );

  $properties['uid'] = array(
    'type' => 'user',
    'label' => t('Created User'),
    'description' => 'Created User',
 //   'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'uid',
  );
 // return $properties;
}

