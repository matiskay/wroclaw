#include <stdlib.h>
#include <stdio.h>
#include "stack_string.h"

#define STACK_CAPACITY 100
#define STRING_LENGTH 256

struct stack_string {
  int index;
  char data[STACK_CAPACITY][STRING_LENGTH];
};

StackString* stack_string_create() {
  StackString* stack;
  stack = (StackString*) malloc(sizeof(stack));
  stack->index = 0;
  return stack;
}

void stack_string_push(StackString* stack, char* data) {
  int c;
  c = 0;

  stack->index++;

  while (data[c] != '\0') {
    stack->data[stack->index][c] = data[c];
    c++;
  }

  stack->data[stack->index][c] = '\0';
}

char* stack_string_peep(StackString* stack) {
  return stack->data[stack->index];
}

char* stack_string_pop(StackString* stack) {
  char* result;
  result = stack->data[stack->index];
  stack->index--;
  return result;
}

void stack_string_free(StackString* stack) {
  free(stack);
}

int stack_string_is_empty(StackString* stack) {
  return (stack->index != 0);
}
