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
  module_load_include('inc', 'islandora', 'includes/authtokens');
  module_load_include('inc', 'islandora_openseadragon', 'includes/utilities');

  //select?facet=true&facet.mincount=2&facet.limit=20&facet.field=RELS_EXT_hasModel_uri_ms&facet.field=ancestors_models_ms&facet.field=ancestors_ms&qf=dc.title^5+dc.subject^2+dc.description^2+dc.creator^2++mod$
  $image_pids = [];
  $random_string = uniqid();
  $query_processor = new IslandoraSolrQueryProcessor();
  $query = '*:*';
  $query_processor->buildQuery($query);

  $query_processor->solrParams['fl'] = 'PID, fgs_label_s, RELS_EXT_isMemberOfCollection_uri_s';
  $query_processor->solrParams['fq'][] = '-fedora_datastream_version_OBJ_SIZE_ms:[* TO 0}';
  // Only get images 1Mb in size
  $query_processor->solrParams['fq'][] = 'fedora_datastream_latest_OBJ_SIZE_ms:[1024000 TO *]';
  $query_processor->solrParams['fq'][] = 'RELS_EXT_hasModel_uri_ms:"info:fedora/islandora:sp_large_image_cmodel"';
  $query_processor->solrParams['sort']= "random_{$random_string} ASC";
  $query_processor->solrStart = 0;
  $query_processor->solrLimit = 10;
  try {
    $query_processor->executeQuery(FALSE);
    $solr_results = $query_processor->islandoraSolrResult['response'];
    if ($solr_results['numFound'] > 1) {

      foreach($solr_results['objects'] as $key => &$solrobject) {
        $token = islandora_get_object_token($solrobject['PID'], 'OBJ', $uses = 1);
        $info = islandora_openseadragon_tile_source($solrobject['PID'], 'OBJ', $token);
        $info = substr($info, 0,strlen($info)- strlen('info.json'));
        //$info = $info . 'full/,500/0/default.jpg';
        $info = $info . 'pct:10,10,80,80/,500/0/default.jpg';
        $solrobject['iiif_url'] = $info;
      }
      $variables['objects'] = $solr_results['objects'];
    }
    else {
      $variables['objects'] = [];
    }
  } catch (Exception $exception) {
    dpm($exception->getMessage());
  }

}



