<?php

/**
 * @file
 * Database Helper Functions for Metrodora QA.
 */

/**
 * Delete single QA entry object from the Drupal database .
 *
 * @param string $pid
 *   Object PID to remove from queue.
 */
function metrodora_qa_delete_object($pid) {
  if ($pid !== NULL) {
    $transaction = db_transaction();
    db_delete('metrodora_object_qa')
      ->condition('pid', $pid)
      ->execute();
  }
}

/**
 * Insert or update the data of a queued object.
 *
 * @param string $pid
 *   The object id identifying the queued batch object.
 * @param array $data
 *   all values that go here in the form of
 * array(
 *   'comment' => 'Some comment',
 *   'good' => 0|1,
 *   'media_missing' => 0|1,
 *   'metadata_missing' => 0|1,
 *   'metadata_value_wrong' => 0|1,
 *   'other_issue' => => 0|1,
 *   'uid' => integer
 * );
 */
function metrodora_qa_merge_object($pid, $data) {

  db_merge('metrodora_object_qa')
    ->key(array('pid' => $pid))
    ->fields(
      $data
    )
    ->execute();
}

/**
 * Get the count of qa objects.
 *
 * @param int $set_id
 *   An integer identifying a batch set.
 *
 * @return int
 *   The count of queued objects in the specified batch set.
 */
function metrodora_qa_get_count() {
  $count = db_select('metrodora_object_qa', 'q')
    ->fields('q', array())
    ->countQuery()
    ->execute()
    ->fetchField();
  return $count;
}

