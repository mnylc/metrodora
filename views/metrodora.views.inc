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
      'title' => t('Boolean indicating if the Object is good.'),
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
    'media_missing' => [
      'title' => t('Boolean indicating if the Object mas Media Missing.'),
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
    'metadata_missing' => [
      'title' => t('Boolean indicating if the Object has Metadata Missing.'),
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
    'metadata_value_wrong' => [
      'title' => t(
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
      'title' => t('Boolean indicating if the Object has other issues.'),
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