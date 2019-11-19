<?php

/**
 * @file
 * Theme/theme.inc.
 *
 * Theme functions.
 */

/**
 * Theme function for the metrodor slideshow widget block.
 */
function template_preprocess_metrodora_slideshow_widget(array &$variables) {

  module_load_include('inc', 'islandora_solr', 'query_processor');

  //select?facet=true&facet.mincount=2&facet.limit=20&facet.field=RELS_EXT_hasModel_uri_ms&facet.field=ancestors_models_ms&facet.field=ancestors_ms&qf=dc.title^5+dc.subject^2+dc.description^2+dc.creator^2++mods_identifier_ms^1+dc.contributor^1+dc.type&fq=-RELS_EXT_isConstituentOf_uri_mt:[*+TO+*]&fq=RELS_EXT_isViewableByUser_literal_ms:"dpino"+OR+RELS_EXT_isViewableByRole_literal_ms:"authenticated+user"+OR+RELS_EXT_isViewableByRole_literal_ms:"administrator"+OR+RELS_EXT_isViewableByRole_literal_ms:"islandora"+OR+((*:*+-RELS_EXT_isViewableByUser_literal_ms:[*+TO+*])+AND+(*:*+-RELS_EXT_isViewableByRole_literal_ms:[*+TO+*]))&version=1.2&wt=json&json.nl=map&q=*:*&start=0&rows=20&indent=on&debugQuery=true
  $image_pids = [];

  $query_processor = new IslandoraSolrQueryProcessor();
  $query = '*:*';
  $query_processor->buildQuery($query);

  $query_processor->solrParams['fl'] = 'PID, fgs_label_s, RELS_EXT_isMemberOfCollection_uri_s';
  $query_processor->solrParams['fq'][] = 'fedora_datastream_version_OBJ_SIZE_ms:[* TO 0}';
  $query_processor->solrParams['fq'][] = 'RELS_EXT_hasModel_uri_ms:"info:fedora/islandora_sp_large_image"';
  try {
    $query_processor->executeQuery(FALSE);
    $solr_results = $query_processor->islandoraSolrResult['response'];
    dpm($solr_results);
    if ($solr_results['numFound'] > 1) {
      dpm($solr_results);
    }
  } catch (Exception $exception) {
    dpm($exception->getMessage());
  }
  $variables['images'] = [];
}


