<?php

function form_train225_startform($form, $form_state) {
  
  $form['simple_information_fieldset'] = array(
    '#type' => 'fieldset',
  );
  
  $form['simple_information_fieldset']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE,
    '#description' => 'Enter your name here',
    '#maxlength' => 40,
  );
  
  $form['simple_information_fieldset']['gender'] = array(
    '#type' => 'radios',
    '#options' => array(
      'male' => t('Males'),
      'female' => t('Females'),
    ),
    '#title' => t('Gender'),
    '#description' => 'Choose you gender',
  );
  
  $form['simple_information_fieldset']['date_of_birth'] = array(
    '#type' => 'date_popup',
    '#date_format' => 'Y-m-d',
    '#title' => t('Day of birth'),
    '#description' => 'Select your birthday',
  );
  
  $form['simple_information_fieldset']['country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country'),
    '#description' => 'Enter your country',
    '#autocomplete_path' => 'train225/autocomplete',
    '#ajax' => array(
      'wrapper' => 'city-fieldset-wrapper',
      'callback' => 'ajax_load_city_option_callback',
    ),
  );
  
  $form['simple_information_fieldset']['city_field'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id="city-fieldset-wrapper">',
    '#suffix' => '</div>',
  );
  
  if (!empty($form_state['values']['country'])) {
    $country_data = $form_state['values']['country'];
    
    $result = get_all_city_by_country($country_data);
    
    $form['simple_information_fieldset']['city_field']['city'] = array(
      '#type' => 'select',
      '#title' => t('City'),
      '#description' => 'Choose your city',
      '#options' => drupal_map_assoc($result),
    );
  }
  
  $form['employee_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Employee ID'),
    '#description' => 'Enter your employee ID',
  );
  
  $form['career'] = array(
    '#title' => 'select',
    '#title' => t('Career'),
    '#description' => 'Choose your career',
    '#option' => drupal_map_assoc(array(t('Developer'), t('Other'))),
  );
  
  $form['documents'] = array(
    '#type' => 'file',
    '#title' => t('Documents'),
    '#description' => 'Upload your documents',
  );
  
  $form['hobbies'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Hobbies'),
    '#description' => 'Choose your hobbies',
    '#options' => drupal_map_assoc(array(t('Swimming'), t('Chatting'), t('Football'), t('Joking'))),
  );
  
  $form['marital_status'] = array(
    '#type' => 'radios',
    '#title' => t('Marital Status'),
    '#description' => 'Choose your marital status',
    '#options' => drupal_map_assoc(array(t('Single'), t('Married'))),
  );
  
  $form['partners_name'] = array(
    '#type' => 'textfield',
    '#title' => t("Partner's Name"),
    '#description' => 'Enter your husband/wife name',
    '#maxlength' => 40,
    '#states' => array(
      'visible' => array(
        'input[name="marital_status"]' => array('value' => t('Married')),
      ),
    ),
  );
  
  $form['note'] = array(
    '#type' => 'textarea',
    '#title' => t('Note'),
    '#description' => 'Note',
    '#cols' => 20,
    '#maxlength' => 500,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  
  $form['reset'] = array(
    '#type' => 'button',
    '#value' => 'Clear',
    '#button_type' => 'reset',
    '#validate' => array(),
    '#executes_submit_callback' => FALSE,
    '#attributes' => array(
            'onclick' => 'this.form.reset(); return false;',
          ),
  );
  
  return $form;
}

function form_train225_startform_validate($form, &$form_state) {
  
  if (!ctype_alnum($form_state['values']['name'])) {
    form_set_error("name]", t('Name field contains only alpha-numerical and space '));
  }
  
  $file = file_save_upload('documents', array(
    'file_validate_extensions' => array('png pdf jpg txt'),
  ));
  
  $form_state['storage']['documents'] = null;
  
  if ($file) {
    if ($file = file_move($file, 'public://')) {
      $form_state['storage']['documents'] = $file;
    }
    else {
      form_set_error('documents]', t("Failed to write the uploaded file to the site's file folder."));
    }
  } 
  
}


function form_train225_startform_submit($form, $form_state) {
  $message = "Data : Name : " . $form_state['values']['name'] ;
  $message = !empty($form_state['values']['gender']) ? $message . "; Gender : " . $form_state['values']['gender'] : $message;
  $message = !empty($form_state['values']['date_of_birth']) ? $message . "; Birthday : " . $form_state['values']['date_of_birth']['day'] . "/"
                                                    . $form_state['values']['date_of_birth']['month'] . "/" . $form_state['values']['date_of_birth']['year'] : $message;
  $message = !empty($form_state['values']['country']) ? $message . "; Country : " . $form_state['values']['country'] : $message;
  $message = !empty($form_state['values']['city']) ? $message . "; City : " . $form_state['values']['city'] : $message;
  $message = !empty($form_state['values']['employee_id']) ? $message . "; Employee ID : " . $form_state['values']['employee_id'] : $message;
  $message = !empty($form_state['values']['marital_status']) ? $message . "; Marital Status : " . $form_state['values']['marital_status'] : $message;
  $message = !empty($form_state['values']['partners_name']) ? $message . "; Partner's Name : " . $form_state['values']['partners_name'] : $message;
  $hobbies = 0;
  foreach ($form_state['values']['hobbies'] as $key => $item) {
    if (!empty($item)) {
      if (!$hobbies) {
        $hobbies = "; Hobbies : ";
      }
      
      $hobbies = $hobbies . " " . $item;
    }
  }
  $message = $hobbies ? $message . $hobbies : $message;
  $message = !empty($form_state['values']['note']) ? $message . "; Note : " . $form_state['values']['note'] : $message;
  
  $file = $form_state['storage']['documents'];
  if (isset($file)) {
    unset($form_state['storage']['documents']);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    $message = $message . " ;Document file name : " . $file->filename;
  }
  
  drupal_set_message($message);
}

function respone_matched_countries($string) {
  $matches = array();
  
  $sql = "SELECT lo.name FROM location lo WHERE lo.name LIKE '%" . $string . "%' AND lo.location_type = '0'";
  $option = array('target' => 'slave');
  //$total_field_of_this_node = db_query($sql, array(':node_type' => $node->type,), $option);
  $result = db_query($sql);
  foreach ($result->fetchAll() as $key => $item) {
    $matches[$item->name] = check_plain($item->name);
  }
  drupal_json_output($matches);
}

function get_all_city_by_country($country) {
  $id_country = "-1";
  $sql = "SELECT location_id FROM location lo WHERE lo.name LIKE '" . $country . "'";
  $country_id_cache = db_query($sql);
  
  foreach ($country_id_cache->fetchAll() as $key => $item) {
    $id_country = $item->location_id;
  }
  
  $sql = "SELECT name FROM location lo WHERE lo.parent_id = '" . $id_country . "'";
  $result = db_query($sql);
  $respone = array();
  
  foreach ($result->fetchAll() as $key => $item) {
    $respone[$item->name] = check_plain($item->name);
  }
  
  return $respone;
}


function ajax_load_city_option_callback($form, $form_state) {
  return $form['simple_information_fieldset']['city_field'];
}