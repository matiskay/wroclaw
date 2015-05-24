#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

#define ASCII_CODE_EMPTY_SPACE ' '
#define ASCII_CODE_END_OF_STRING '\0'
/* Lessons:
 *    * If you work with string check always the length of the string. The empty spaces can
 *    lead to bugs.
 */

/**
 * TODO: Check if the token is an operator
 */

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

    if (is_single_string_operator(expression[index])) {

      /* Avoid empty spaces as tokens */
      if (string_index > 1) {
        string[string_index] = ASCII_CODE_END_OF_STRING;
        printf("Current Token:   %s --- %lu \n", string, strlen(string));
        string_index = 0;
      }

      // Process string operator and continue to next iteration
      string[string_index] = expression[index];
      string[string_index + 1] = ASCII_CODE_END_OF_STRING;
      printf("Operators ---> Current Token:   %s --- %lu \n", string, strlen(string));
      string_index = 0;
      continue;
    }

    if (expression[index] == ASCII_CODE_EMPTY_SPACE && string_index != 0) {
      //printf("Value %c at index %i and integer value %d \n", expression[index], index, expression[index]);
      string[string_index] = ASCII_CODE_END_OF_STRING;

      printf("Current Token:   %s --- %lu \n", string, strlen(string));
      string_index = 0;
    }

    // Don't count empty spaces
    if (expression[index] != ASCII_CODE_EMPTY_SPACE) {
      string[string_index] = expression[index];
      printf(" --> Current value of the string %c at index %i and integer value %d \n", string[string_index], string_index, string[string_index]);
      //printf("Value %c at index %i and integer value %d \n", expression[index], index, expression[index]);
      string_index++;
    }
  }

  // Process the final string
  if (expression[index] == ASCII_CODE_END_OF_STRING) {
    string[string_index] = ASCII_CODE_END_OF_STRING;

    printf("Current Token:   %s -- %lu \n", string, strlen(string));
    string_index = 0;
  }
}

int is_single_string_operator(char character) {
  switch (character) {
    case '+':
    case '-':
    case '*':
    case '/':
      return 1;
  }
  return 0;
}
