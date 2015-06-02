#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack_string.h"

#define STRING_LENGTH 256

struct stack_string {
    char value[STRING_LENGTH];
    struct stack_string* next;
};

StackString* stack_string_create() {
    return NULL;
}

StackString* stack_string_push(StackString* stack, char* data) {
    int index;
    StackString* stack_string_node;

    index = 0;

    stack_string_node = (StackString*) malloc(sizeof(StackString));

    while (data[index] != '\0') {
        stack_string_node->value[index] = data[index];
        index++;
    }

    stack_string_node->value[index] = '\0';

    stack_string_node->next = stack;

    return stack_string_node;
}

char* stack_string_peep(StackString* stack) {
    return stack->value;
}

char* stack_string_pop(StackString** stack) {
    char* result;
    StackString* current_stack_node;

    // Hard copy a.k.a. This is how things work in C.
    // This is because result = (*stack)->value; means that result is a pointer to the value
    // if the value is wipeout result will be null.
    result = malloc(sizeof(char) * strlen((*stack)->value));
    strcpy(result, (*stack)->value);

    current_stack_node = *stack;
    *stack = current_stack_node->next;

    free(current_stack_node);

    return result;
}

void stack_string_free(StackString** stack) {
    StackString* aux_stack_node;

    for (aux_stack_node = *stack; aux_stack_node != NULL; aux_stack_node = aux_stack_node->next) {
        StackString* current_node = aux_stack_node;
        (*stack) = current_node->next;
        free(current_node);
    }
}

int stack_string_is_empty(StackString* stack) {
    if (stack == NULL) {
        return 1;
    }

    return 0;
}
