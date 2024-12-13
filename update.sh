#!/bin/bash

source .env # for API_BASE_URL and PROJECT_ID

GET_TASKS_ENDPOINT="$API_BASE_URL/projects/$PROJECT_ID/tasks?user=kavish"

TODAYS_DAY=$1
TOMMORROWS_DAY=$(expr $TODAYS_DAY + 1)
echo $TODAYS_DAY
echo $TOMMORROWS_DAY
TASKS_RESPONSE=$(curl -s -X GET "$GET_TASKS_ENDPOINT")
# ACTIVE_TASK_ID=$(echo "$TASKS_RESPONSE" | jq -r --arg DAY "$TODAYS_DAY" '.[] | select(.name | contains($DAY)) | .id')
# QUEUED_TASK_ID=$(echo "$TASKS_RESPONSE" | jq -r --arg DAY "$TOMMORROWS_DAY" '.[] | select(.name | contains($DAY)) | .id')
# UPDATE_DATA='{"status": "true"}'

# UPDATE_RESPONSE=$(curl -s -X PUT "$API_BASE_URL/tasks/$ACTIVE_TASK_ID/active?user=kavish" -d "$UPDATE_DATA")
# UPDATE_RESPONSE=$(curl -s -X PUT "$API_BASE_URL/tasks/$QUEUED_TASK_ID/queued?user=kavish" -d "$UPDATE_DATA")
