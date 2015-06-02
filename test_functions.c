#include <stdio.h>
#include "minunit.h"
#include "functions.h"
#include "math.h"

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

static char * test_polish_evaluation_example2() {
  /* Don't forget to take care of the polish evaluation it will remove all the elements from the queue */
  char expression[256] = "sqrt(5 * 5 - 9)";

  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_parser_complex failed: \n   error, test_parser 1 != 1", fabs(polish_evaluation(queue_polish) -  4.0) < 0.01);
  return 0;
}

static char * test_polish_evaluation_example1() {
  char expression[256] = "(1 + 2) + (3 + 4) + 5";

  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_parser_complex failed: \n   error, test_parser 1 != 1", polish_evaluation(queue_polish) == 15);
  return 0;
}

static char * test_polish_evaluation_elaborated_case() {
  char expression[256] = "1+(2-(3*(4/(5+(6-7)))))";

  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_evaluation_elaborated_case failed: \n   error, test_parser 1 != 1", polish_evaluation(queue_polish) == 0);
  return 0;
}

static char * test_polish_evaluation() {
  char expression[256] = "5 + 3";

  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_parser_complex failed: \n   error, test_parser 1 != 1", polish_evaluation(queue_polish) == 8);
  return 0;
}

static char * test_polish_parser_example_2() {
  char expression[256] = "5 + ( ( 1 + 2 )  * 4 ) - 3";

  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();
  queue_polish_result = queue_string_create();
  /* 21 53 + 2 * 25 3 * 29 + sqrt - sqrt */
  queue_string_insert(queue_polish_result, "5");
  queue_string_insert(queue_polish_result, "1");
  queue_string_insert(queue_polish_result, "2");
  queue_string_insert(queue_polish_result, "+");
  queue_string_insert(queue_polish_result, "4");
  queue_string_insert(queue_polish_result, "*");
  queue_string_insert(queue_polish_result, "+");
  queue_string_insert(queue_polish_result, "3");
  queue_string_insert(queue_polish_result, "-");
  /*
   * queue_string_display(queue_polish_result);
   */

  queue = parser(expression);
  queue_polish = polish_parser(queue);


  /*
  queue_string_display(queue_polish);
  printf("\n----------------\n");
  queue_string_display(queue_polish_result);
  */

  mu_assert("test_polish_parser_complex failed: \n   error, test_parser 1 != 1", queue_string_equal(queue_polish, queue_polish_result) == 1);
  return 0;
}

static char * test_polish_parser_example_4() {
  /**
   * (sqrt(b * b - 4 * a * c) - b) / (2 * a) 
   * ---> b b * 4 a * c * - sqrt b - 2 a * /
   **/
  char expression[256] = "( sqrt ( b * b - 4 * a * c ) - b ) / ( 2 * a )";

  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();
  queue_polish_result = queue_string_create();

  queue_string_insert(queue_polish_result, "b");
  queue_string_insert(queue_polish_result, "b");
  queue_string_insert(queue_polish_result, "*");
  queue_string_insert(queue_polish_result, "4");
  queue_string_insert(queue_polish_result, "a");
  queue_string_insert(queue_polish_result, "*");
  queue_string_insert(queue_polish_result, "c");
  queue_string_insert(queue_polish_result, "*");
  queue_string_insert(queue_polish_result, "-");
  queue_string_insert(queue_polish_result, "sqrt");
  queue_string_insert(queue_polish_result, "b");
  queue_string_insert(queue_polish_result, "-");
  queue_string_insert(queue_polish_result, "2");
  queue_string_insert(queue_polish_result, "a");
  queue_string_insert(queue_polish_result, "*");
  queue_string_insert(queue_polish_result, "/");
  /*
   * queue_string_display(queue_polish_result);
   */

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  /*
  queue_string_display(queue_polish_result);
  printf("\n-------------------\n");
  queue_string_display(queue_polish);
  */

  mu_assert("test_polish_parser_complex failed: \n   error, test_parser 1 != 1", queue_string_equal(queue_polish, queue_polish_result) == 1);
  return 0;
}

static char * test_polish_parser_example_3() {
  char expression[256] = "( 52 + 1 + 2 ) * 4 - 3";

  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();
  queue_polish_result = queue_string_create();
  /* 52 1 + 2 + 4 * 3 - */
  queue_string_insert(queue_polish_result, "52");
  queue_string_insert(queue_polish_result, "1");
  queue_string_insert(queue_polish_result, "+");
  queue_string_insert(queue_polish_result, "2");
  queue_string_insert(queue_polish_result, "+");
  queue_string_insert(queue_polish_result, "4");
  queue_string_insert(queue_polish_result, "*");
  queue_string_insert(queue_polish_result, "3");
  queue_string_insert(queue_polish_result, "-");
  /*
   * queue_string_display(queue_polish_result);
   */

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_parser_complex failed: \n   error, test_parser 1 != 1", queue_string_equal(queue_polish, queue_polish_result) == 1);
  return 0;
}

static char * test_polish_parser_example_1() {
  char expression[256] = "6 * ( 4 + 5 ) - 25 / ( 2 + 3 )";

  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();
  queue_polish_result = queue_string_create();

  queue_string_insert(queue_polish_result, "6");
  queue_string_insert(queue_polish_result, "4");
  queue_string_insert(queue_polish_result, "5");
  queue_string_insert(queue_polish_result, "+");
  queue_string_insert(queue_polish_result, "*");
  queue_string_insert(queue_polish_result, "25");
  queue_string_insert(queue_polish_result, "2");
  queue_string_insert(queue_polish_result, "3");
  queue_string_insert(queue_polish_result, "+");
  queue_string_insert(queue_polish_result, "/");
  queue_string_insert(queue_polish_result, "-");
  /*
   * queue_string_display(queue_polish_result);
   */

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_parser_complex failed: \n   error, test_parser 1 != 1", queue_string_equal(queue_polish, queue_polish_result) == 1);
  return 0;
}

static char * test_polish_parser_big_expression() {
  char expression[256] = "sqrt(6 + ( 4 - 1 ) * 2 - 3 / ( 7 + 5 ))";

  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();
  queue_polish_result = queue_string_create();

  queue_string_insert(queue_polish_result, "6");
  queue_string_insert(queue_polish_result, "4");
  queue_string_insert(queue_polish_result, "1");
  queue_string_insert(queue_polish_result, "-");
  queue_string_insert(queue_polish_result, "2");
  queue_string_insert(queue_polish_result, "*");
  queue_string_insert(queue_polish_result, "+");
  queue_string_insert(queue_polish_result, "3");
  queue_string_insert(queue_polish_result, "7");
  queue_string_insert(queue_polish_result, "5");
  queue_string_insert(queue_polish_result, "+");
  queue_string_insert(queue_polish_result, "/");
  queue_string_insert(queue_polish_result, "-");
  queue_string_insert(queue_polish_result, "sqrt");
  /*
   * queue_string_display(queue_polish_result);
   */

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_parser_complex failed: \n   error, test_parser 1 != 1", queue_string_equal(queue_polish, queue_polish_result) == 1);
  return 0;
}

static char * test_polish_parser() {
  char expression[256] = "2.0 + 3.0";
  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();
  queue_polish_result = queue_string_create();

  queue_string_insert(queue_polish_result, "2.0");
  queue_string_insert(queue_polish_result, "3.0");
  queue_string_insert(queue_polish_result, "+");

  /*
  queue_string_display(queue_polish_result);
  */

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_parser failed: \n   error, test_parser 1 != 1", queue_string_equal(queue_polish, queue_polish_result) == 1);
  return 0;
}

static char * test_polish_parser_compose() {
  char expression[256] = "(2.0 + 3.0) + (4.0 + 5.0)";
  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();
  queue_polish_result = queue_string_create();

  queue_string_insert(queue_polish_result, "2.0");
  queue_string_insert(queue_polish_result, "3.0");
  queue_string_insert(queue_polish_result, "+");
  queue_string_insert(queue_polish_result, "4.0");
  queue_string_insert(queue_polish_result, "5.0");
  queue_string_insert(queue_polish_result, "+");
  queue_string_insert(queue_polish_result, "+");

  /*
  queue_string_display(queue_polish_result);
  */

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_parser_compose failed: \n   error, test_parser 1 != 1", queue_string_equal(queue_polish, queue_polish_result) == 1);
  return 0;
}

static char * test_polish_parser_sqrt() {
  char expression[256] = "sqrt(2.0)";
  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();
  queue_polish_result = queue_string_create();

  queue_string_insert(queue_polish_result, "2.0");
  queue_string_insert(queue_polish_result, "sqrt");

  /*
  queue_string_display(queue_polish_result);
  */

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_parser failed: \n   error, test_parser 1 != 1", queue_string_equal(queue_polish, queue_polish_result) == 1);
  return 0;
}

static char * test_polish_parser_parentesis() {
  char expression[256] = "(2.0 + 3.0)";
  QueueString* queue; 
  QueueString* queue_polish; 
  QueueString* queue_polish_result; 

  queue = queue_string_create();
  queue_polish = queue_string_create();
  queue_polish_result = queue_string_create();

  queue_string_insert(queue_polish_result, "2.0");
  queue_string_insert(queue_polish_result, "3.0");
  queue_string_insert(queue_polish_result, "+");

  /*
  queue_string_display(queue_polish_result);
  */

  queue = parser(expression);
  queue_polish = polish_parser(queue);

  mu_assert("test_polish_parser failed: \n   error, test_parser 1 != 1", queue_string_equal(queue_polish, queue_polish_result) == 1);
  return 0;
}

static char * test_parser_parentesis() {
  
  char expression[256] = "6 * (4 + 5) - 25 / ( 2 + 3 )";
  QueueString* queue; 
  QueueString* queue_final; 

  queue = queue_string_create();

  queue_final = queue_string_create();
  queue_string_insert(queue_final, "6");
  queue_string_insert(queue_final, "*");
  queue_string_insert(queue_final, "(");
  queue_string_insert(queue_final, "4");
  queue_string_insert(queue_final, "+");
  queue_string_insert(queue_final, "5");
  queue_string_insert(queue_final, ")");
  queue_string_insert(queue_final, "-");
  queue_string_insert(queue_final, "25");
  queue_string_insert(queue_final, "/");
  queue_string_insert(queue_final, "(");
  queue_string_insert(queue_final, "2");
  queue_string_insert(queue_final, "+");
  queue_string_insert(queue_final, "3");
  queue_string_insert(queue_final, ")");


  queue = parser(expression);
  mu_assert("test_parser failed: \n   error, test_parser 1 != 1", queue_string_equal(queue, queue_final) == 1);
  return 0;
}

static char * test_parser() {
  /*
  char expression[256] = "2 + 3";
  char expression[256] = "2.0 + 3.0";
  char expression[256] = "2.0+3.0";
  char expression[256] = "2.0+ 3.0 - 4.0";
  char expression[256] = "2.0 + 3.0 - 4.0";
  char expression[256] = "2.0+3.0-4.0";
  char expression[256] = "(4.0 + 5.0)";
  char expression[256] = "sqrt((53 + 21) * 2 – sqrt(29 + 3 * 25))";
  */
  
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
  printf("Problem \n");
  queue_string_display(queue);
  printf("\n ------------------ \n");
  queue_string_display(queue_final);
  */

  mu_assert("test_parser_complex_expression failed: \n   error, test_parser 1 != 1", queue_string_equal(queue, queue_final) == 1);
  return 0;
}

static char * test_parser_complex_expression() {
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
  */


  /*
  printf("-------------------------- \n");
  queue_string_display(queue);
  printf("\n ----------------------- \n");
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
  mu_run_test(test_polish_parser_parentesis);
  mu_run_test(test_polish_parser_sqrt);
  mu_run_test(test_polish_parser_compose);
  mu_run_test(test_polish_parser_big_expression);
  mu_run_test(test_polish_parser_example_1);
  mu_run_test(test_polish_parser_example_2);
  mu_run_test(test_polish_parser_example_3);
  mu_run_test(test_polish_parser_example_4);
  mu_run_test(test_parser_parentesis);
  mu_run_test(test_polish_evaluation);
  mu_run_test(test_polish_evaluation_example1);
  mu_run_test(test_polish_evaluation_example2);
  mu_run_test(test_polish_evaluation_elaborated_case);
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
