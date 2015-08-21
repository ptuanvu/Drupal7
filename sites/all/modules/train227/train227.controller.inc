<?php

class EmployeeController extends EntityAPIController {
  public function create(array $values = array()) {
    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('employee', $entity);

    $content['employee_id'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' => t('Employee ID'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => $view_mode,
      '#language' => $langcode,
      '#field_name' => 'field_fake_employee_id',
      '#field_type' => 'text',
      '#entity_type' => 'employee',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->employee_id)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->employee_id))
    );
    $content['fullname'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' => t('Fullname'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => $view_mode,
      '#language' => $langcode,
      '#field_name' => 'field_fake_fullname',
      '#field_type' => 'text',
      '#entity_type' => 'employee',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->fullname)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->fullname))
    );
    $content['dayofbirth'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' => t('Birthday'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => $view_mode,
      '#language' => $langcode,
      '#field_name' => 'field_fake_dayofbirth',
      '#field_type' => 'text',
      '#entity_type' => 'employee',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->dayofbirth)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->dayofbirth))
    );
    $content['gender'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' => t('Gender'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => $view_mode,
      '#language' => $langcode,
      '#field_name' => 'field_fake_gender',
      '#field_type' => 'text',
      '#entity_type' => 'employee',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->gender)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->gender))
    );

    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
}