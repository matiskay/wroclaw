#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "stack_float.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

int tests_run = 0;

static char * test_stack_float_free() {
    StackFloat* stack;
    stack = stack_float_create();

    stack = stack_float_push(stack, 34);
    stack = stack_float_push(stack, 44);
    stack = stack_float_push(stack, 54);
    stack = stack_float_push(stack, 64);
    stack = stack_float_push(stack, 74);

    stack_float_free(&stack);

    mu_assert("error, test_stack_float_free stack_is_empty(stack) != 0", stack_float_is_empty(stack) == 1);
    return 0;
}

static char * test_stack_float_pop() {
    StackFloat* stack;
    stack = stack_float_create();

    stack = stack_float_push(stack, 34);
    stack = stack_float_push(stack, 44);
    stack = stack_float_push(stack, 54);
    stack = stack_float_push(stack, 64);
    stack = stack_float_push(stack, 74);

    mu_assert("error, test_stack_pop stack_pop(stack) != 74", stack_float_pop(&stack) == 74);
    mu_assert("error, test_stack_pop stack_pop(stack) != 64", stack_float_pop(&stack) == 64);
    mu_assert("error, test_stack_pop stack_pop(stack) != 54", stack_float_pop(&stack) == 54);
    mu_assert("error, test_stack_pop stack_pop(stack) != 44", stack_float_pop(&stack) == 44);
    mu_assert("error, test_stack_pop stack_is_empty(stack) != 0", stack_float_is_empty(stack) == 0);
    return 0;
}

static char * test_stack_float_peep() {
  StackFloat* stack;
  stack = stack_float_create();
  stack = stack_float_push(stack, 34);

  mu_assert("error, test_stack_peep stack_peep(stack) != 34", stack_float_peep(stack) == 34);
  mu_assert("error, test_stack_peep stack_is_empty(stack) != 0", stack_float_is_empty(stack) == 0);
  return 0;
}

static char * test_stack_float_is_empty_second_case() {
    StackFloat* stack;
    stack = stack_float_create();
    stack = stack_float_push(stack, 34);

    mu_assert("error, test_empty_stack stack_is_empty(stack) != 0", stack_float_is_empty(stack) == 0);

    stack_float_free(&stack);

    return 0;
}

static char * test_stack_float_is_empty() {
  StackFloat* stack;
  stack = stack_float_create();

  mu_assert("error, test_empty_stack stack_is_empty(stack) != 0", stack_float_is_empty(stack) == 1);

  stack_float_free(&stack);

  return 0;
}


static char * test_unit() {
  mu_assert("test_unit failed: \n   error, test_unit 1 != 1", 1 == 1);
  return 0;
}

static char * all_tests() {
    mu_run_test(test_unit);
    mu_run_test(test_stack_float_pop);
    mu_run_test(test_stack_float_peep);
    mu_run_test(test_stack_float_is_empty);
    mu_run_test(test_stack_float_is_empty_second_case);
    mu_run_test(test_stack_float_free);
    return 0;
}

int main(int argc, char **argv) {
  char *result = all_tests();

  printf(KMAG "---> Testing stack_float.c \n" RESET);

  if (result != 0) {
    printf("   -_-_-_-_-_-_-_,------,      o \n");
    printf("   _-_-_-_-_-_-_-|   /\\_/\\ \n");
    printf("   -_-_-_-_-_-_-~|__( X .X)  +     + \n");
    printf("   _-_-_-_-_-_-_- \"\"  \"\" \n");
    printf(KRED "   ✗ %s \n" RESET, result);
  }
  else {
    printf("   -_-_-_-_-_-_-_,------,      o \n");
    printf("   _-_-_-_-_-_-_-|   /\\_/\\ \n");
    printf("   -_-_-_-_-_-_-~|__( ^ .^)  +     + \n");
    printf("   _-_-_-_-_-_-_-  \"\"  \"\" \n");
    printf(KGRN "   ✓ ALL TESTS PASSED \n" RESET);
  }

  printf(KCYN "   Summary:\n   Number of tests run: %d\n" RESET, tests_run);
  return result != 0;
}
