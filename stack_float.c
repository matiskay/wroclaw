#include <stdlib.h>
#include "stack_float.h"

struct stack_float_node {
    float value;
    struct stack_float_node* next;
};

StackFloat* stack_float_create() {
    return NULL;
}

StackFloat* stack_float_create_node() {
    StackFloat* stack;

    stack = (StackFloat*) malloc(sizeof(StackFloat));
    stack->next = NULL;

    return stack;
}

StackFloat* stack_float_push(StackFloat* stack, float data) {
    StackFloat* node;

    node = stack_float_create_node();
    node->value = data;
    node->next = stack;

    return node;
}

float stack_float_peep(StackFloat* stack) {
    return stack->value;
}

// The value of the stack is not changing
float stack_float_pop(StackFloat** stack) {
    float result;

    StackFloat* current_stack_node;

    result = (*stack)->value;

    current_stack_node = *stack;
    *stack = current_stack_node->next;
    stack_float_free_node(current_stack_node);

    return result;
}

void stack_float_free(StackFloat** stack) {
    StackFloat* aux_stack_node;

    for (aux_stack_node = *stack; aux_stack_node != NULL; aux_stack_node = aux_stack_node->next) {
        StackFloat* current_node = aux_stack_node;
        (*stack) = current_node->next;
        stack_float_free_node(current_node);
    }
}

void stack_float_free_node(StackFloat* stack) {
    free(stack);
}

int stack_float_is_empty(StackFloat* stack) {
    if (stack == NULL) {
        return 1;
    }

    return 0;
}
