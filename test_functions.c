#include <stdio.h>
#include "minunit.h"
#include "functions.h"

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

static char * test_precedence_no_defined() {
  mu_assert("test_precedence_no_defined failed: \n   error, test_parser 1 != 1", precedence("p") == -1);
  return 0;
}

static char * test_precedence_multipy() {
  mu_assert("test_precedence_multipy failed: \n   error, test_parser 1 != 1", precedence("*") == 3);
  return 0;
}

static char * test_precedence_sum() {
  mu_assert("test_precedence_sum failed: \n   error, test_parser 1 != 1", precedence("+") == 2);
  return 0;
}

static char * test_precedence_sqrt() {
  mu_assert("test_precedence_sqrt failed: \n   error, test_parser 1 != 1", precedence("sqrt") == 4);
  return 0;
}

static char * test_polish_parser() {
  
  char expression[256] = "2.0 + 3.0";
  QueueString* queue; 
  QueueString* queue_final; 

  queue = queue_string_create();

  queue_final = queue_string_create();
  queue_string_insert(queue_final, "2.0");
  queue_string_insert(queue_final, "+");
  queue_string_insert(queue_final, "3.0");

  queue = parser(expression);
  polish_parser(queue);
  mu_assert("test_polish_parser failed: \n   error, test_parser 1 != 1", 1 == 1);
  return 0;
}

static char * test_parser() {
  //char expression[256] = "2 + 3";
  //char expression[256] = "2.0 + 3.0";
  //char expression[256] = "2.0+3.0";
  //char expression[256] = "2.0+ 3.0 - 4.0";
  //char expression[256] = "2.0 + 3.0 - 4.0";
  //char expression[256] = "2.0+3.0-4.0";
  //char expression[256] = "(4.0 + 5.0)";
  //char expression[256] = "sqrt((53 + 21) * 2 – sqrt(29 + 3 * 25))";
  
  char expression[256] = "2.0 sqrt";
  QueueString* queue; 
  QueueString* queue_final; 

  queue = queue_string_create();

  queue_final = queue_string_create();
  queue_string_insert(queue_final, "2.0");
  queue_string_insert(queue_final, "sqrt");


  queue = parser(expression);
  mu_assert("test_parser failed: \n   error, test_parser 1 != 1", queue_string_equal(queue, queue_final) == 1);
  return 0;
}

static char * test_parser_sqrt_and_parentesis_expression() {
  char expression[256] = "sqrt(4.0 + (5.0 - 2.0))";
  
  QueueString* queue; 
  QueueString* queue_final; 

  queue = queue_string_create();

  queue_final = queue_string_create();

  queue_string_insert(queue_final, "sqrt");
  queue_string_insert(queue_final, "(");
  queue_string_insert(queue_final, "4.0");
  queue_string_insert(queue_final, "+");
  queue_string_insert(queue_final, "(");
  queue_string_insert(queue_final, "5.0");
  queue_string_insert(queue_final, "-");
  queue_string_insert(queue_final, "2.0");
  queue_string_insert(queue_final, ")");
  queue_string_insert(queue_final, ")");

  queue = parser(expression);

  /*
  queue_string_display(queue);
  queue_string_display(queue_final);
  */

  mu_assert("test_parser_complex_expression failed: \n   error, test_parser 1 != 1", queue_string_equal(queue, queue_final) == 1);
  return 0;
}

static char * test_parser_complex_expression() {
  //char expression[256] = "2 + 3";
  //char expression[256] = "2.0 + 3.0";
  //char expression[256] = "2.0+3.0";
  //char expression[256] = "2.0+ 3.0 - 4.0";
  //char expression[256] = "2.0 + 3.0 - 4.0";
  //char expression[256] = "2.0+3.0-4.0";
  //char expression[256] = "(4.0 + 5.0)";
  char expression[256] = "sqrt((53 + 21) * 2 - sqrt(29 + 3 * 25))";
  
  QueueString* queue; 
  QueueString* queue_final; 

  queue = queue_string_create();

  queue_final = queue_string_create();

  queue_string_insert(queue_final, "sqrt");
  queue_string_insert(queue_final, "(");
  queue_string_insert(queue_final, "(");
  queue_string_insert(queue_final, "53");
  queue_string_insert(queue_final, "+");
  queue_string_insert(queue_final, "21");
  queue_string_insert(queue_final, ")");
  queue_string_insert(queue_final, "*");
  queue_string_insert(queue_final, "2");
  queue_string_insert(queue_final, "-");
  queue_string_insert(queue_final, "sqrt");
  queue_string_insert(queue_final, "(");
  queue_string_insert(queue_final, "29");
  queue_string_insert(queue_final, "+");
  queue_string_insert(queue_final, "3");
  queue_string_insert(queue_final, "*");
  queue_string_insert(queue_final, "25");
  queue_string_insert(queue_final, ")");
  queue_string_insert(queue_final, ")");

  queue = parser(expression);

  /*
  printf("number of elements queue %d \n", queue_string_number_of_elements(queue));
  printf("number of elements queue final %d \n", queue_string_number_of_elements(queue_final));

  queue_string_display(queue);
  queue_string_display(queue_final);
  */

  mu_assert("test_parser_complex_expression failed: \n   error, test_parser 1 != 1", queue_string_equal(queue, queue_final) == 1);
  return 0;
}


static char * test_parser_simple_expression() {
  char expression[256] = "2 + 3";
  
  QueueString* queue; 
  QueueString* queue_final; 

  queue = queue_string_create();

  queue_final = queue_string_create();

  queue_string_insert(queue_final, "2");
  queue_string_insert(queue_final, "+");
  queue_string_insert(queue_final, "3");

  queue = parser(expression);

  mu_assert("test_parser_simple_expression failed: \n   error, test_parser 1 != 1", queue_string_equal(queue, queue_final) == 1);
  return 0;
}

static char * test_unit() {
  mu_assert("test_unit failed: \n   error, test_unit 1 != 1", 1 == 1);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_unit);
  mu_run_test(test_parser);
  mu_run_test(test_parser_complex_expression);
  mu_run_test(test_parser_simple_expression);
  mu_run_test(test_parser_sqrt_and_parentesis_expression);
  mu_run_test(test_polish_parser);
  mu_run_test(test_precedence_sum);
  mu_run_test(test_precedence_sqrt);
  mu_run_test(test_precedence_multipy);
  mu_run_test(test_precedence_no_defined);
  return 0;
}

int main(int argc, char **argv) {
  char *result = all_tests();

  printf(KMAG "---> Testing functions.c \n" RESET);

  if (result != 0) {
    printf("   -_-_-_-_-_-_-_,------,      o \n");
    printf("   _-_-_-_-_-_-_-|   /\\_/\\ \n");
    printf("   -_-_-_-_-_-_-~|__( X .X)  +     + \n");
    printf("   _-_-_-_-_-_-_- \"\"  \"\" \n");
    printf(KRED "✗ %s \n" RESET, result);
  }
  else {
    printf("   -_-_-_-_-_-_-_,------,      o \n");
    printf("   _-_-_-_-_-_-_-|   /\\_/\\ \n");
    printf("   -_-_-_-_-_-_-~|__( ^ .^)  +     + \n");
    printf("   _-_-_-_-_-_-_-  \"\"  \"\" \n");
    printf(KGRN "   ✓ ALL TESTS PASSED \n" RESET);
  }
  printf(KCYN "   Summary:\n      Number of tests run: %d\n" RESET, tests_run);
  return result != 0;
}
