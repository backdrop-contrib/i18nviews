<?php

/**
 * Field handler to provide simple renderer that allows linking to a taxonomy
 * term.
 */
class i18nviews_handler_field_taxonomy_term_name extends views_handler_field_taxonomy {
  function pre_render(&$values) {
    foreach ($values as $key => $value) {
      if (isset($value->{$this->field_alias})) {
        $term = new stdClass();
        $term->tid = $value->{$this->aliases['tid']};
        $term->vid = $value->{$this->aliases['vid']};
        $term->name = $value->{$this->field_alias};
        $values[$key]->{$this->field_alias} = i18n_taxonomy_term_name($term);
      }
    }
  }
}