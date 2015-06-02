#include <stdio.h>
#include "functions.h"

/* Add function signatures here */

int main(int argc, char **argv) {

  if (argc != 2) {

    printf( "Usage: %s <mathematical-expression> \n", argv[0]);
  } else {
    QueueString* queue;
    QueueString* queue_polish;

    char *expression;
    float result;

    /* TODO: Check if it's a valid expression */
    expression = argv[1];
    //    expression = "1 + (2 - (3 * ( 4 / ( 5 + ( 6 - 7 )))))";

    queue = queue_string_create();
    queue_polish = queue_string_create();

    queue = parser(expression);

    queue_polish = polish_parser(queue);

    printf("Wroclaw: Another Reverse Polish Notation Calculator \n");
    printf("\n");
    printf("   Expression: %s \n", expression);
    printf("   RPN:   ");

    /* Print the Polish Notation */
    /* TODO: Rename the function to print_polish_notation */

    queue_string_display_inline(queue_polish);
    printf("\n");


    result = polish_evaluation(queue_polish);

    printf("   Result: %2.2f \n", result);

    queue_string_free(queue);
    queue_string_free(queue_polish);
  }

  return 0;
}
