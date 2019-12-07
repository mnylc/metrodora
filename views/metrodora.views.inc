<?php
/**
 * @file
 * Views hook implementations.
 */

/**
 * Implements hook_views_data().
 */
function metrodora_views_data() {
  $data = [];
  $data['metrodora_object_qa'] = [
    'table' => [
      'group' => t('Metrodora QA'),
      'base' => [
        'field' => 'pid',
        'title' => t('Metrodora QA'),
        'help' => t('Islandoda Objects QA PID.'),
        'weight' => -10,
      ],
      'join' => [
        'islandora_batch_queue' => [
          'left_field' => 'id',
          'field' => 'pid',
        ],
      ],
    ],
    'pid' => [
      'title' => t('PID of the object.'),
      'help' => t('Islandoda Objects PID.'),
      'relationship' => [
        // The name of the table to join with.
        'base' => 'islandora_batch_queue',
        // The name of the field on the joined table.
        'base field' => 'id',
        'handler' => 'views_handler_relationship',
        'label' => t('PID'),
        'title' => t('PID in Batch Set'),
        'help' => t('More information on this relationship'),
      ],
    ],
    'pid_no_batch' => [
      'title' => t('PID of the object, but not in batch.'),
      'help' => t('Islandoda Objects PID that does not exist in batch queue.'),
      'real field' => 'pid',
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => [
        'handler' => 'views_handler_filter_string',
      ],
      'argument' => [
        'handler' => 'views_handler_argument_string',
      ],
      'sort' => array('handler' => 'views_handler_sort'),
    ],
    'comment' => [
      'title' => t('QA Comment'),
      'field' => [
        'handler' => 'views_handler_field',
        // This is use by the table display plugin.
        'click sortable' => FALSE,
      ],
      'sort' => [
        'handler' => 'views_handler_sort',
      ],
      'filter' => [
        'handler' => 'views_handler_filter_string',
      ],
      'argument' => [
        'handler' => 'views_handler_argument_string',
      ],
    ],
    'good' => [
      'title' => t('Object is good.'),
      'help' => t('Boolean indicating if the Object is good.'),
      'field' => [
        'handler' => 'views_handler_field_boolean',
        'click sortable' => TRUE,
      ],
      'filter' => [
        'handler' => 'views_handler_filter_boolean_operator',
        // Note that you can override the field-wide label.
        'label' => t('Good'),
        // This setting is used by the boolean filter handler, as possible option.
        'type' => 'yes-no',
        // use boolean_field = 1 instead of boolean_field <> 0 in WHERE statement.
        'use equal' => TRUE,
      ],
      'sort' => [
        'handler' => 'views_handler_sort',
      ],
    ],
    'media_missing' => [
      'title' => t('Media Missing.'),
      'help' => t('Boolean indicating if the Object mas Media Missing.'),
      'field' => [
        'handler' => 'views_handler_field_boolean',
        'click sortable' => TRUE,
      ],
      'filter' => [
        'handler' => 'views_handler_filter_boolean_operator',
        // Note that you can override the field-wide label.
        'label' => t('Missing Media'),
        // This setting is used by the boolean filter handler, as possible option.
        'type' => 'yes-no',
        // use boolean_field = 1 instead of boolean_field <> 0 in WHERE statement.
        'use equal' => TRUE,
      ],
      'sort' => [
        'handler' => 'views_handler_sort',
      ],
    ],
    'metadata_missing' => [
      'title' => t('Metadata Missing.'),
      'help' => t('Boolean indicating if the Object has Metadata Missing.'),
      'field' => [
        'handler' => 'views_handler_field_boolean',
        'click sortable' => TRUE,
      ],
      'filter' => [
        'handler' => 'views_handler_filter_boolean_operator',
        // Note that you can override the field-wide label.
        'label' => t('Metadata'),
        // This setting is used by the boolean filter handler, as possible option.
        'type' => 'yes-no',
        // use boolean_field = 1 instead of boolean_field <> 0 in WHERE statement.
        'use equal' => TRUE,
      ],
      'sort' => [
        'handler' => 'views_handler_sort',
      ],
    ],
    'metadata_value_wrong' => [
      'title' => t(
        'Wrong metadata value.'
      ),
      'help' => t(
        'Boolean indicating if the Object has a Wrong metadata value.'
      ),
      'field' => [
        'handler' => 'views_handler_field_boolean',
        'click sortable' => TRUE,
      ],
      'filter' => [
        'handler' => 'views_handler_filter_boolean_operator',
        // Note that you can override the field-wide label.
        'label' => t('Published'),
        // This setting is used by the boolean filter handler, as possible option.
        'type' => 'yes-no',
        // use boolean_field = 1 instead of boolean_field <> 0 in WHERE statement.
        'use equal' => TRUE,
      ],
      'sort' => [
        'handler' => 'views_handler_sort',
      ],
    ],
    'other_issue' => [
      'title' => t('Other issues.'),
      'help' => t('Boolean indicating if the Object has other issues.'),

      'field' => [
        'handler' => 'views_handler_field_boolean',
        'click sortable' => TRUE,
      ],
      'filter' => [
        'handler' => 'views_handler_filter_boolean_operator',
        // Note that you can override the field-wide label.
        'label' => t('Published'),
        // This setting is used by the boolean filter handler, as possible option.
        'type' => 'yes-no',
        // use boolean_field = 1 instead of boolean_field <> 0 in WHERE statement.
        'use equal' => TRUE,
      ],
      'sort' => [
        'handler' => 'views_handler_sort',
      ],
    ],
    'uid' => [
      'title' => t('User ID'),
      'help' => t('ID of the user who QAed the Object.'),
      'field' => [
        'handler' => 'views_handler_field_user',
        'click sortable' => TRUE,
      ],
      'argument' => [
        'handler' => 'views_handler_argument_user_uid',
        'name field' => 'name',
      ],
      'filter' => [
        'title' => t('Name'),
        'handler' => 'views_handler_filter_user_name',
      ],
      'sort' => [
        'handler' => 'views_handler_sort',
      ],
      'relationship' => [
        'base' => 'users',
        'base field' => 'uid',
        'handler' => 'views_handler_relationship',
        'label' => t('QA provider'),
        'title' => t('QA provider'),
        'help' => t('The user who provided the QA.'),
      ],
    ],
  ];
  return $data;
}