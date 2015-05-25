#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "stack_string.h"

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

static char * test_stack_string_push() {
  StackString * stack;
  stack = stack_string_create();
  stack_string_push(stack, "edgar");

  mu_assert("test_stack_string_push", strcmp(stack_string_peep(stack), "edgar") == 0);
  return 0;
}

static char * test_stack_string_is_empty() {
  StackString * stack;
  stack = stack_string_create();

  mu_assert("test_stack_string_push", stack_string_is_empty(stack) == 1);
  return 0;
}


static char * test_stack_string_is_not_empty() {
  StackString * stack;
  stack = stack_string_create();
  stack_string_push(stack, "edgar");

  mu_assert("test_stack_string_push", stack_string_is_empty(stack) == 0);
  return 0;
}


static char * test_unit() {
  mu_assert("test_unit failed: \n   error, test_unit 1 != 1", 1 == 1);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_unit);
  mu_run_test(test_stack_string_push);
  mu_run_test(test_stack_string_is_empty);
  mu_run_test(test_stack_string_is_not_empty);
  return 0;
}

int main(int argc, char **argv) {
  char *result = all_tests();

  printf(KMAG "---> Testing stack_string.c \n" RESET);

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
