#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

#define ASCII_CODE_EMPTY_SPACE ' '
#define ASCII_CODE_END_OF_STRING '\0'

/* Preconditions:
 *    * The expression doesn't have to contains spaces at the beginning or at the end.
 *    * The expression is no empty.
 *    * The expression is well defined.
 */
void parser(char* expression) {
  char string[128];
  int string_index = 0;
  int index;

  printf("Hello from parser. \n");
  printf("Value %s \n", expression);

  printf("Value %c \n", expression[0]);
  

  for (index = 0; expression[index] != ASCII_CODE_END_OF_STRING; index++) {

    if (expression[index] == ASCII_CODE_EMPTY_SPACE) {
      //printf("Value %c at index %i and integer value %d \n", expression[index], index, expression[index]);
      string[string_index] = ASCII_CODE_END_OF_STRING;

      printf("Current Token:   %s \n", string);
      string_index = 0;
    }

    string[string_index] = expression[index];
    printf(" --> Current value of the string %c at index %i and integer value %d \n", string[string_index], string_index, string[string_index]);
    //printf("Value %c at index %i and integer value %d \n", expression[index], index, expression[index]);
    string_index++;
  }

  // Process the final string
  if (expression[index] == ASCII_CODE_END_OF_STRING) {
    string[string_index] = ASCII_CODE_END_OF_STRING;

    printf("Current Token:   %s \n", string);
    string_index = 0;
  }
}
