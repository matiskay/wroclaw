#include <stdlib.h>
#include <stdio.h>
#include "stack_float.h"

#define STACK_FLOAT_CAPACITY 50

struct stack_float {
  int index;
  float data[STACK_FLOAT_CAPACITY];
};

StackFloat* stack_float_create() {
  StackFloat* stack;
  stack = (StackFloat *) malloc(sizeof(stack));
  stack->index = 0;
  return stack;
}

void stack_float_push(StackFloat* stack, float data) {
  stack->index++;
  stack->data[stack->index] = data;
}

float stack_float_peep(StackFloat* stack) {
  return stack->data[stack->index];
}

float stack_float_pop(StackFloat* stack) {
  float result;
  result = stack->data[stack->index];
  stack->index--;
  return result;
}

void stack_float_free(StackFloat* stack) {
  free(stack);
}

int stack_float_is_empty(StackFloat* stack) {
  return (stack->index != 0);
}
