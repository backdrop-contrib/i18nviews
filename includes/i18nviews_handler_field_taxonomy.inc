<?php

/**
 * Field handler to provide simple renderer that allows linking to a taxonomy
 * term.
 */
class i18nviews_handler_field_taxonomy extends views_handler_field_taxonomy {
  function pre_render(&$values) {
    $tids = array();
    foreach ($values as $key => $value) {
      if (isset($value->{$this->field_alias})) {
        $tids[] = $value->{$this->aliases['tid']};
      }
    }

    $terms = taxonomy_term_load_multiple($tids);
    foreach ($values as $key => $value) {
      if (isset($value->{$this->field_alias})) {
        $tid = $value->{$this->aliases['tid']};
        $values[$key]->{$this->field_alias} = i18n_taxonomy_term_name($terms[$tid]);
      }
    }
  }
}