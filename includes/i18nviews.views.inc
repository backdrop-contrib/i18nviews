<?php

/**
 * Implementation of hook_views_data().
 */
function i18nviews_views_data() {
  $data['node']['content_negotiation'] = array(
    'group' => t('Node translation'),
    'title' => t('Content negotiation'),
    'help' => t('Removes the nodes that are not valid according to the content selection mode.'),
    'filter' => array(
      'handler' => 'i18nviews_filter_handler_content_negotiation',
    ),
  );
  return $data;
}

/**
 * Implementation of hook_views_data_alter().
 */
function i18nviews_views_data_alter(&$data) {
  // Replace term_data handlers.
  $data['term_data']['name']['field']['handler'] = 'i18nviews_handler_field_taxonomy';
  $data['term_data']['description']['field']['handler'] = 'i18nviews_handler_field_term_description';
  $data['term_node']['tid']['field']['handler'] = 'i18nviews_handler_field_term_node_tid';
  $data['term_node']['tid']['argument']['handler'] = 'i18nviews_handler_argument_term_node_tid';
  $data['term_node']['tid']['filter']['handler'] = 'i18nviews_handler_filter_term_node_tid';
  $data['node']['term_node_tid_depth']['argument']['handler'] = 'i18nviews_handler_argument_term_node_tid_depth';

  // Add i18n language field to term_data.
  $data['term_data']['language'] = array(
    'group' => t('Term translation'),
    'title' => t('Language'),
    'help' => t('The language the term is in.'),
    'field' => array(
      'handler' => 'i18nviews_handler_field_term_language',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'i18nviews_handler_filter_term_language',
    ),
    'argument' => array(
      'handler' => 'i18nviews_handler_argument_term_language',
    ),
  );
}


/**
 * Implementation of hook_views_plugins().
 */
function i18nviews_views_plugins() {
  $path = drupal_get_path('module', 'i18nviews') . '/includes';
  $ret = array(
    'module' => 'i18nviews',
    'localization' => array(
      'i18nstrings' => array(
        'title' => t('Internationalization Views'),
        'help' => t("Use the locale system as implemented by the Views translation module."),
        'handler' => 'i18nviews_plugin_localization_i18nstrings',
        'path' => $path,
      ),
    ),
    'argument validator' => array(
      'i18n_taxonomy_term' => array(
        'title' => t('Taxonomy term (i18n)'),
        'help' => t("Use the locale to interpret arguments."),
        'handler' => 'i18nviews_plugin_argument_validate_i18n_taxonomy_term',
        'path' => $path,
        'parent' => 'taxonomy_term',
      ),
    ),
  );
  return $ret;
}
