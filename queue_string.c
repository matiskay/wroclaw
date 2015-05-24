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

void queue_string_display(QueueString* queue) {
  int counter;

  counter = 1;

  while(! queue_string_is_empty(queue)) {

    printf("%d.- %s \n", counter, queue_string_pop(queue));

    counter++;
  }
}

int queue_string_is_empty(QueueString* queue) {
  return (queue->current_position == 0);
}

void queue_string_free(QueueString* queue) {
  free(queue);
}
