<?php
class views_handler_field_employee_name extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    $options['capitalize'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['capitalize'] = array(
      '#type' => 'checkbox',
      '#title' => t('Capitalize'),
      '#description' => 'If checked, the employee name will be capitalized',
      '#default_value' => $this->options['capitalize'],
    );

    parent::options_form($form, $form_state);
  }

  function render($values) {
    $value = $this->get_value($values);

    if ($this->options['capitalize']) {
      $value = strtoupper($value);
    }

    return $value;
  }
}