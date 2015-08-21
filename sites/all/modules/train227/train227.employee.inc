<?php
function get_all_employee() {
  if (property_exists($GLOBALS['user'], 'login')) {
//    $view = views_get_view('allnodeex');
//    $view->set_display('default');
//
//    $view->set_arguments(array($GLOBALS['user']->name));
//    $view->pre_execute();
//    $view->execute();
//    return $view->render();

//    return views_embed_view('allnodeex', 'default', $GLOBALS['user']->name);
    return views_embed_view('employee_page', 'default', $GLOBALS['user']->name);
  } else {
    return drupal_not_found();
  }

  //print views_embed_view($view, $display, $arg1, $arg2, ...);
}