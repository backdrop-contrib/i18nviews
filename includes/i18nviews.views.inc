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
  // Replace taxonomy_term_data handlers.

  // TAXONOMY TERM
  // tid field (translated)
  $data['taxonomy_term_data']['tid_i18n'] = array(
    'title' => t('Term ID (translated)'),
    'help' => t('The translated taxonomy term ID.'),
    'argument' => array(
      'handler' => 'i18nviews_handler_argument_numeric',
      'name field' => 'name',
      'zero is null' => TRUE,
    ),
    'filter' => array(
      'title' => t('Term (translated)'),
      'help' => t('Taxonomy term chosen from autocomplete or select widget.'),
      'handler' => 'i18nviews_handler_filter_term_node_tid',
      'hierarchy table' => 'taxonomy_term_hierarchy',
      'numeric' => TRUE,
    ),
  );

  // Add Term name field (translated)
  $data['taxonomy_term_data']['name_i18n'] = array(
    'title' => t('Name (translated)'),
    'help' => t('The translated taxonomy term name.'),
    'field' => array(
      //'handler' => 'views_handler_field_taxonomy',
      'handler' => 'i18nviews_handler_field_taxonomy_term_name',
      'click sortable' => TRUE,
    ),
    // TODO currently almost impossible, JOIN to i18n_string table needed
    /*
    'sort' => array(
      //'handler' => 'views_handler_sort',
      'handler' => 'i18nviews_handler_sort_taxonomy_term_name',
    ),
    */
    'filter' => array(
      //'handler => 'views_handler_filter_string',
      'handler' => 'i18nviews_handler_filter_taxonomy_term_name',
      'help' => t('Translated taxonomy term name.'),
    ),
    'argument' => array(
      //'handler => 'views_handler_argument_string',
      'handler' => 'i18nviews_handler_argument_taxonomy_term_name',
      'help' => t('Translated taxonomy term name.'),
      'many to one' => TRUE,
      'empty field name' => t('Uncategorized'),
    ),
  );

  // Add term description (translated)
  $data['taxonomy_term_data']['description_i18n'] = array(
    'title' => t('Term description (translated)'),
    'help' => t('The translated description associated with a taxonomy term.'),
    'field' => array(
      //'handler' => 'views_handler_field_markup',
      'handler' => 'i18nviews_handler_field_taxonomy_term_description',
      'format' => array('field' => 'format'),
    ),
  );

  // Add i18n language field to taxonomy_term_data. No clash.
  $data['taxonomy_term_data']['language'] = array(
    'group' => t('Taxonomy term'),
    'title' => t('Language'),
    'help' => t('The language the term is in.'),
    'field' => array(
      'handler' => 'i18nviews_handler_field_taxonomy_term_language',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'i18nviews_handler_filter_taxonomy_term_language',
    ),
    'argument' => array(
      'handler' => 'i18nviews_handler_argument_taxonomy_term_language',
    ),
  );

  // NODE
  $data['node']['term_node_tid_i18n'] = array(
    'title' => t('Taxonomy terms on node (translated)'),
    'help' => t('Relate nodes to taxonomy terms, specifiying which vocabulary or vocabularies to use. This relationship will cause duplicated records if there are multiple terms.'),
    'field' => array(
      'title' => t('All taxonomy terms (translated)'),
      'help' => t('Display all taxonomy terms associated with a node from specified vocabularies.'),
      //'handler' => 'views_handler_field_term_node_tid',
      'handler' => 'i18nviews_handler_field_taxonomy_term_node_tid',
      'no group by' => TRUE,
    ),
  );

  $data['node']['term_node_tid_depth_i18n'] = array(
    'help' => t('Display content if it has the selected taxonomy terms, or children of the selected terms. Due to additional complexity, this has fewer options than the versions without depth.'),
    'real field' => 'nid',
    'argument' => array(
      'title' => t('Has taxonomy term ID (with depth, translated)'),
      //'handler' => views_handler_argument_term_node_tid_depth_modifier
      'handler' => 'i18nviews_handler_argument_term_node_tid_depth',
      'accept depth modifier' => TRUE,
      // use regular (non-i18n) depth modifier term_node_tid_depth_modifier
    ),
    'filter' => array(
      'title' => t('Has taxonomy terms (with depth, translated)'),
      //'handler' => 'views_handler_filter_term_node_tid_depth',
      'handler' => 'i18nviews_handler_filter_term_node_tid_depth',
    ),
  );

  $data['node']['term_node_tid_depth_modifier_i18n'] = array(
    'title' => t('Has taxonomy term ID depth modifier (translated)'),
    'help' => t('Allows the "depth" for Taxonomy: Term ID (with depth) to be modified via an additional contextual filter value.'),
    'argument' => array(
      //'handler' => 'views_handler_argument_term_node_tid_depth_modifier',
      'handler' => 'i18nviews_handler_argument_term_node_tid_depth_modifier',
    ),
  );

  // NODE INDEX
  // @todo This stuff needs to move to a node field since
  // really it's all about nodes.
  // tid field
  $data['taxonomy_index']['tid_i18n'] = array(
    'group' => t('Content'),
    'title' => t('Has taxonomy term ID (translated)'),
    'help' => t('Display content if it has the selected taxonomy terms.'),
    'argument' => array(
      //'handler' => 'views_handler_argument_term_node_tid',
      'handler' => 'i18nviews_handler_argument_taxonomy_term_node_tid',
      'name table' => 'taxonomy_term_data',
      'name field' => 'name',
      'empty field name' => t('Uncategorized'),
      'numeric' => TRUE,
      'skip base' => 'taxonomy_term_data',
    ),
    'filter' => array(
      'title' => t('Has taxonomy term (translated)'),
      //'handler' => 'views_handler_filter_term_node_tid',
      'handler' => 'i18nviews_handler_filter_taxonomy_term_node_tid',
      'hierarchy table' => 'taxonomy_term_hierarchy',
      'numeric' => TRUE,
      'skip base' => 'taxonomy_term_data',
      'allow empty' => TRUE,
    ),
  );

  // TODO CHECK this is missing in 7.x-3.x
  /*
  //$data['term_index']['tid']['field']['handler'] = 'i18nviews_handler_field_term_index_tid';
  // original views_handler_argument_term_node_tid
  $data['term_index']['tid']['argument']['handler'] = 'i18nviews_handler_argument_term_index_tid';
  // original views_handler_filter_term_node_tid
  $data['term_index']['tid']['filter']['handler'] = 'i18nviews_handler_filter_term_index_tid';
  // TODO CHECK this is missing in 7.x-3.x
  //$data['node']['term_index_tid_depth']['argument']['handler'] = 'i18nviews_handler_argument_term_index_tid_depth';
  */
}

/**
 * Implementation of hook_field_views_data().
 *
 * modules/field.views.inc field_views_data()
 */
function i18nviews_field_views_data(&$result, &$field, $module) {
  // modules/taxonomy.views.inc taxonomy_field_views_data()
  // provide translated variant
  if ($module=='taxonomy') {
    // TODO CHECK
    //dsm(func_get_args());
  }
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
