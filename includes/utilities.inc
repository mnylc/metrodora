<?php
/**
 * @file
 * Utility functions used by Metrodora.
 */

/**
 * Get the cmodels that should use the metadata tab.
 */
function metrodora_metadata_tab_cmodels() {
  return array(
    'islandora:sp_pdf',
    'islandora:sp_large_image_cmodel',
    'islandora:bookCModel',
    'islandora:sp_basic_image',
    'fedora-system:FedoraObject-3.0',
  );
}

/**
 * Delivery callback used to download the output of menu callback as XML.
 *
 * @param string $callback_result
 *   The content to download.
 */
function metrodora_mods_download($callback_result) {
  // Delivery callbacks are called even when permissions don't match.
  if (is_int($callback_result)) {
    drupal_deliver_html_page($callback_result);
  }
  else {
    drupal_add_http_header('Content-type', 'text/xml;charset=utf8');
    drupal_add_http_header('Content-length', strlen($callback_result));
    drupal_add_http_header('Content-Disposition', 'attachment; filename="mods.xml"');
    print $callback_result;
    drupal_page_footer();
  }
}

/**
 * Run an XSLT, and return the results.
 *
 * @param array $info
 *   An associative array of parameters, containing:
 *   - input: The input XML in a string.
 *   - xsl: The path to an XSLT file.
 *
 * @return string
 *   The transformed XML, as a string.
 */
function metrodora_mods_run_xsl_transform($info) {
  $xsl = new DOMDocument();
  $xsl->load($info['xsl']);
  $input = new DOMDocument();
  $input->loadXML($info['input']);
  $processor = new XSLTProcessor();
  $processor->importStylesheet($xsl);
  return @$processor->transformToXML($input);
}

/**
 * Grabs MODS off the given object, and returns it with new elements.
 *
 * @param AbstractObject $object
 *   A Fedora object containing a MODS datastream.
 *
 * @return string
 *   The complemented XML, as a string.
 */
function metrodora_mods_complement_elements(AbstractObject $object) {
  if (!isset($object['MODS'])) {
    drupal_not_found();
  }
  // We will add some local repo data to existing MODS.
  $mods_xml = new SimpleXMLElement(trim($object['MODS']->content));
  $metro_data = $mods_xml->addChild("relatedItem");
  $metro_data->addAttribute("type", "host");
  $metro_data->addAttribute("displayLabel", "DCMNY.org Islandora Object");
  $attribs = $metro_data->attributes(
    $ns = 'http://www.w3.org/1999/xlink'
  );
  $metro_data->addAttribute("xlink:href", $GLOBALS['base_url'] . "/islandora/object/" . $object->id, $ns);
  $metro_data->addChild("identifier", $object->id)->addAttribute("type", "local");
  $dom = new DOMDocument();
  $dom->preserveWhiteSpace = FALSE;
  $dom->formatOutput = TRUE;
  $dom->loadXML($mods_xml->asXML());
  return $dom->saveXML();
}

/**
 * Produce HTML representing MARCXML content.
 *
 * First, transforms MODS to MARCXML, and then MARCXML to HTML.
 *
 * @param AbstractObject $object
 *   A Fedora object containing a MODS datastream.
 *
 * @return string
 *   The transformed HTML, as a string.
 */
function metrodora_transform_mods_to_html(AbstractObject $object) {
  return metrodora_mods_run_xsl_transform(array(
    'input' => metrodora_mods_complement_elements($object),
    'xsl' => drupal_get_path('module', 'metrodora') . '/xsl/MODS3-4_HTML_XSLT1.xsl',
  ));
}
