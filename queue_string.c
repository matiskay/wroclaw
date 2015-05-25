#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue_string.h"

#define QUEUE_CAPACITY 100
#define STRING_LENGTH 256
#define ERROR_EMPTY_QUEUE 10

struct queue_string {
  /* Next element that will be pop */
  int current_position;

  int initial_position;
  char data[QUEUE_CAPACITY][STRING_LENGTH];
};

QueueString* queue_string_create() {
  QueueString* queue_string;
  queue_string = (QueueString*) malloc(sizeof(QueueString));

  queue_string->current_position = 0;
  queue_string->initial_position = 0;
  return queue_string;
}

void queue_string_insert(QueueString* queue, char* string) {
  int next_free_position;
  int c;

  c = 0;

  if (queue->current_position == QUEUE_CAPACITY) {
    printf("You exceed the capacity of the Queue.");
    exit(1);
  }

  next_free_position = (queue->initial_position + queue->current_position) % QUEUE_CAPACITY;

  while (string[c] != '\0') {
    queue->data[next_free_position][c] = string[c];
    c++;
  }

  queue->data[next_free_position][c] = '\0';

  queue->current_position++;
}

char* queue_string_pop(QueueString* queue) {
  char *data;
  if (queue_string_is_empty(queue)) {
    return NULL;
  }

  data = queue->data[queue->initial_position];
  queue->initial_position = (queue->initial_position + 1) % QUEUE_CAPACITY;
  queue->current_position--;

  return data;
}

/**
 * TODO: Refactor this function. The current behaviour deletes all the elements.
 */
void queue_string_display(QueueString* queue) {
  int counter;
  int temp_initial_position;
  int temp_current_position;
  char *data;

  counter = 1;
  temp_initial_position = queue->initial_position;
  temp_current_position = queue->current_position;

  while (queue->current_position) {
    data = queue->data[queue->initial_position];
    queue->initial_position = (queue->initial_position + 1) % QUEUE_CAPACITY;
    queue->current_position--;

    printf("%d.- %s \n", counter, data);
    counter++;
  }

  queue->current_position = temp_current_position;
  queue->initial_position = temp_initial_position;
}

int queue_string_is_empty(QueueString* queue) {
  return (queue->current_position == 0);
}

void queue_string_free(QueueString* queue) {
  free(queue);
}

int queue_string_number_of_elements(QueueString* queue_string) {
  return queue_string->current_position;
}

int queue_string_equal(QueueString* queue_string_first, QueueString* queue_string_second) {

  int temp_initial_position_first;
  int temp_current_position_first;

  int temp_initial_position_second;
  int temp_current_position_second;

  char *data_first;
  char *data_second;

  if (queue_string_number_of_elements(queue_string_first) != queue_string_number_of_elements(queue_string_second)) {
    printf("Problem here in the number of elements \n");
    return 0;
  }

  temp_initial_position_first = queue_string_first->initial_position;
  temp_current_position_first = queue_string_first->current_position;

  temp_initial_position_second = queue_string_second->initial_position;
  temp_current_position_second = queue_string_second->current_position;

  while (queue_string_first->current_position) {
    data_first = queue_string_first->data[queue_string_first->initial_position];
    queue_string_first->initial_position = (queue_string_first->initial_position + 1) % QUEUE_CAPACITY;

    data_second = queue_string_second->data[queue_string_second->initial_position];
    queue_string_second->initial_position = (queue_string_second->initial_position + 1) % QUEUE_CAPACITY;

    if (strcmp(data_first, data_second) != 0) {
      printf("Not equal here \n");
      printf("data_first:   %s \n", data_first);
      printf("data_second:   %s\n", data_second);
      queue_string_first->current_position = temp_current_position_first;
      queue_string_first->initial_position = temp_initial_position_first;

      queue_string_second->current_position = temp_current_position_second;
      queue_string_second->initial_position = temp_initial_position_second;
      return 0;
    }
    queue_string_first->current_position--;
  }

  queue_string_first->current_position = temp_current_position_first;
  queue_string_first->initial_position = temp_initial_position_first;

  queue_string_second->current_position = temp_current_position_second;
  queue_string_second->initial_position = temp_initial_position_second;

  return 1;
}
