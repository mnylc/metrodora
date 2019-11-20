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
  module_load_include('inc','metrodora','includes/db');
  $current_entry = metrodora_qa_get($pid);
  // Returns boolean if it fails.
  $current_entry = is_array($current_entry) ? $current_entry : [];
  $comment = isset($current_entry['comment']) ? $current_entry['comment'] : '';
  unset($current_entry['pid']);
  unset($current_entry['comment']);
  unset($current_entry['uid']);

  $qadefaults = count($current_entry) ? array_keys(array_filter($current_entry)):[];

  $qaoptions = array(
    'good' => t('Object looks good!'),
    'media_missing' => t('Media has problems.'),
    'metadata_missing' => t('Metadata is incomplete.'),
    'metadata_value_wrong' => t('One/more-than-one Metadata value is wrong.'),
    'other_issue' => t('There are other issues'),
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
    '#default_value' => $qadefaults,
  );
  $form['comment'] = array(
    '#title' => t('Add a comment'),
    '#type' => 'textfield',
    '#size' => '45',
    '#maxlength' => '254',
    '#description' => t('This field is optional.'),
    '#default_value' => $comment,
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
  module_load_include('inc','metrodora','includes/db');
  global $user;
  $uid = $user->uid;
  $data = array(
    'comment' => trim($form_state['values']['comment']),
    'good' => $form_state['values']['qa']['good'] ? 1 : 0,
    'media_missing' => $form_state['values']['qa']['media_missing'] ? 1 : 0,
    'metadata_missing' => $form_state['values']['qa']['metadata_missing'] ? 1 : 0,
    'metadata_value_wrong' => $form_state['values']['qa']['metadata_value_wrong'] ? 1 : 0,
    'other_issue' => $form_state['values']['qa']['other_issue'] ? 1 : 0,
    'uid' => $uid
   );

  $status = metrodora_qa_merge_object($form_state['values']['pid'], $data);
  switch ($status) {
    case 1:
      drupal_set_message('Thanks for your feedback!', 'status');
      break;
    case 2:
      drupal_set_message('Feedback on this Object was updated!', 'status');
      break;
    case 0:
      drupal_set_message('Ups. Something went wrong storing your feedback.', 'error');
      break;
    default:
  }

}