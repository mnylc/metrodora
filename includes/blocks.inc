<?PHP

/**
 * @file
 * Holds block definitions for the islandora matomo module.
 */

/**
 * Constructs the metrodora slideshow block for islandora objects.
 *
 * @param \AbstractObject|NULL $object
 *   If supplied the object to create the block for.
 *
 * @return array
 *   Renderable array for the block.
 * @throws \Exception
 */
function metrodora_slideshow_block() {

  $widget = theme('metrodora_slideshow_widget', []);
  $output = '';
  $output .= $widget;
      if (!empty($output)) {
        return ['#markup' => $output];
      }
}
