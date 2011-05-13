<?php

class i18nviews_filter_handler_content_negotiation extends views_handler_filter {
  function query() {
    $this->ensure_my_table();
    i18n_select(TRUE);
    if (!empty($where)) {
      $this->query->add_where($this->options['group'], $where);
    }
  }

  /**
   * Disable i18n select again after running the query.
   */
  function post_execute(&$values) {
    i18n_select(FALSE);
  }


  function option_definition() {
    $options = parent::option_definition();
    $options['operator']['default'] = '';
    $options['value']['default'] = '';
    return $options;
  }
}
