<?php
/**
 * Created by PhpStorm.
 * User: monster
 * Date: 12/08/2015
 * Time: 10:11
 */

/**
 * Implements hook_views_default_views().
 */
function train227_views_default_views()
{
  $views = array();

  $view = new view();
  $view->name = 'employee_form';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'employee';
  $view->human_name = 'Employee Form';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Employee Form';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Employee Ex Table: Employee rela users */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'employee';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Employee Ex Table: Employee ID */
  $handler->display->display_options['fields']['employee_id']['id'] = 'employee_id';
  $handler->display->display_options['fields']['employee_id']['table'] = 'employee';
  $handler->display->display_options['fields']['employee_id']['field'] = 'employee_id';
  /* Field: Employee Ex Table: Birthday */
  $handler->display->display_options['fields']['dayofbirth']['id'] = 'dayofbirth';
  $handler->display->display_options['fields']['dayofbirth']['table'] = 'employee';
  $handler->display->display_options['fields']['dayofbirth']['field'] = 'dayofbirth';
  /* Field: Employee Ex Table: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'employee';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  /* Field: Employee Ex Table: Employee ID */
  $handler->display->display_options['fields']['employee_id_1']['id'] = 'employee_id_1';
  $handler->display->display_options['fields']['employee_id_1']['table'] = 'employee';
  $handler->display->display_options['fields']['employee_id_1']['field'] = 'employee_id';
  /* Field: Employee Ex Table: Fullname */
  $handler->display->display_options['fields']['fullname']['id'] = 'fullname';
  $handler->display->display_options['fields']['fullname']['table'] = 'employee';
  $handler->display->display_options['fields']['fullname']['field'] = 'fullname';
  /* Field: Employee Ex Table: Gender */
  $handler->display->display_options['fields']['gender']['id'] = 'gender';
  $handler->display->display_options['fields']['gender']['table'] = 'employee';
  $handler->display->display_options['fields']['gender']['field'] = 'gender';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Author name';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  $views[$view->name] = $view;
  return $views;
}