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
function metrodora_qa_block(AbstractObject $object = NULL) {

  $object = $object ? $object : menu_get_object('islandora_object', 2);
  $output = '';
  if ($object) {
    $pid = $object->id;
    $output = drupal_get_form('metrodora_qa_form',$pid);
  }
  return $output;
}

function metrodora_qa_form($form, &$form_state, $pid = NULL) {
  if (!$pid) {
    return [];
  }
  $qaoptions = array(
    'all_good' => t('Object looks good.'),
    'media_missing' => t('Media is missing.'),
    'metadata_missing' => t('Metadata is incomplete.'),
    'metadata_wrong' => t('One/More than one Metadata Value is wrong.'),
    'other_wrong' => t('There is another issue'),
  );

  # the drupal checkboxes form field definition
  $form['pid'] =  array(
    '#type' => 'value',
    '#default_value' => $pid,
  );

  $form['qa'] = array(
    '#type' => 'checkboxes',
    '#options' => $qaoptions,
    '#required' => TRUE,
  );
  $form['comment'] = array(
    '#title' => t('Add a comment'),
    '#type' => 'textfield',
    '#size' => '45',
    '#maxlength' => '254',
    '#description' => t('This field is optional'),
    '#options' => $qaoptions,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#default_value' => 'Lets us know!',
  );
  return $form;
}


/**
 * Metrodora QA form submit function.
 */
function metrodora_qa_form_submit($form, &$form_state) {
  // You need the have Devel module enabled for dpm() to work.
  dpm($form_state);
}