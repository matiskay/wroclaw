#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

/* Add function signatures here */

int main(int argc, char **argv) {
  float result;
  char expression[256] = "(1 + 2) + (3 + 4) + 5";

  QueueString* queue;
  QueueString* queue_polish;

  queue = queue_string_create();
  queue_polish = queue_string_create();

  queue = parser(expression);


  queue_polish = polish_parser(queue);

  printf("The expression is %s \n", expression);
  printf("The Polish Notation for this expression is:   ");
  queue_string_display_inline(queue_polish);
  printf("\n");

  result = polish_evaluation(queue_polish);

  printf("The result is %2.2f \n", result);

  queue_string_free(queue);
  queue_string_free(queue_polish);
  return 0;
}
