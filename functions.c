#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "stack_string.h"

#define ASCII_CODE_EMPTY_SPACE ' '
#define ASCII_CODE_END_OF_STRING '\0'
#define DEBUG 0

/**
 * TODO: Change comments to slash star. Hint: grep -nR '//' .
 */

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
QueueString* parser(char* expression) {
  char string[128];
  int string_index = 0;
  int index;
  QueueString* queue_string;
  queue_string = queue_string_create();

  /*
  printf("Hello from parser. \n");
  printf("Value %s \n", expression);

  printf("Value %c \n", expression[0]);
  */
  

  for (index = 0; expression[index] != ASCII_CODE_END_OF_STRING; index++) {

    if (is_single_string_operator(expression[index]) || is_parentesis(expression[index])) {

      /* Avoid empty spaces as tokens */
      if (string_index >= 1) {
        string[string_index] = ASCII_CODE_END_OF_STRING;

        queue_string_insert(queue_string, string);

        if (DEBUG) {
          printf("(1) Current Token:   %s --- %lu \n", string, strlen(string));
        }
        string_index = 0;
      }

      // Process string operator and continue to next iteration
      string[string_index] = expression[index];
      string[string_index + 1] = ASCII_CODE_END_OF_STRING;
      queue_string_insert(queue_string, string);

      if (DEBUG) {
        printf("(2) Operators ---> Current Token:   %s --- %lu \n", string, strlen(string));
      }

      string_index = 0;
      continue;
    }

    if (expression[index] == ASCII_CODE_EMPTY_SPACE && string_index != 0) {
      //printf("Value %c at index %i and integer value %d \n", expression[index], index, expression[index]);
      string[string_index] = ASCII_CODE_END_OF_STRING;
      queue_string_insert(queue_string, string);

      if (DEBUG) {
        printf("(3) Current Token:   %s --- %lu \n", string, strlen(string));
      }

      string_index = 0;
    }

    // Don't count empty spaces
    if (expression[index] != ASCII_CODE_EMPTY_SPACE) {
      string[string_index] = expression[index];
      string_index++;
    }
  }

  // Process the final string
  if (expression[index] == ASCII_CODE_END_OF_STRING) {
    // Exclude empty strings
    if (string_index > 0) {
      string[string_index] = ASCII_CODE_END_OF_STRING;
      queue_string_insert(queue_string, string);

      if (DEBUG) {
        printf("(3) Current Token:   %s -- %lu \n", string, strlen(string));
      }
      string_index = 0;
    }
  }

  if (DEBUG) {
    printf("Current queue_string: \n");
    queue_string_display(queue_string);
    printf("Number of elements of queue_string inside function %d \n", queue_string_number_of_elements(queue_string));
  }

  return queue_string;
}

QueueString* polish_parser(QueueString* queue_expression) {
  char* data;

  QueueString* queue_string_output;
  StackString* stack_string_operators;

  queue_string_output = queue_string_create();
  stack_string_operators = stack_string_create();

  /*
  queue_string_display(queue_expression);
  */

  while (! queue_string_is_empty(queue_expression)) {
    data = queue_string_pop(queue_expression);

    if (strcmp(data, "(") == 0) {
      stack_string_push(stack_string_operators, data);

    } else if (strcmp(data, ")") == 0) {
      while (strcmp(stack_string_peep(stack_string_operators), "(") != 0) {
        queue_string_insert(queue_string_output, stack_string_pop(stack_string_operators));
      }
      data = stack_string_pop(stack_string_operators);
    } else if (strcmp(data, "+") == 0 || strcmp(data, "-") == 0
              || strcmp(data, "*") == 0 || strcmp(data, "/") == 0
              || strcmp(data, "sqrt") == 0) {

      while (stack_string_is_empty(stack_string_operators) == 0
            && (precedence(data) <= precedence(stack_string_peep(stack_string_operators)))) {
        queue_string_insert(queue_string_output, stack_string_pop(stack_string_operators));
      }

      stack_string_push(stack_string_operators, data);

      if (DEBUG) {
        printf("-----> Operators:   %s \n", stack_string_peep(stack_string_operators));
      }

    } else {
      queue_string_insert(queue_string_output, data);
    }
  }

  // Push the remaining operators.
  while (stack_string_is_empty(stack_string_operators) == 0) {
    data = stack_string_pop(stack_string_operators);
    if (strcmp(data, "(") != 0 && strcmp(data, ")") != 0) {
      queue_string_insert(queue_string_output, data);
    }
  }

  /* Parse only the reaming operators */
  while (stack_string_is_empty(stack_string_operators) == 0) {
    if (strcmp(data, "+") == 0 || strcmp(data, "-") == 0
              || strcmp(data, "*") == 0 || strcmp(data, "/") == 0
              || strcmp(data, "sqrt") == 0) {
      queue_string_insert(queue_string_output, stack_string_pop(stack_string_operators));
    }
    stack_string_pop(stack_string_operators);
  }

  /*
  stack_string_push(stack_string_operators, data);
  */

  /*
  while (!stack_string_is_empty(stack_string_operators)) {
    printf("value in the stack:   %s\n", stack_string_pop(stack_string_operators));
  }
  */

  /*
  printf("Polish Notation Result:   \n");
  queue_string_display_inline(queue_string_output);
  printf("\n");
  */
  return queue_string_output;
}

float polish_evaluation(QueueString *queue_expression) {
  return 0.0;
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


int is_parentesis(char character) {
  switch (character) {
    case '(':
    case ')':
      return 1;
  }
  return 0;
}

int precedence(char* string) {
  if (strcmp(string, "(") == 0) {
    return 1;
  } else if (strcmp(string, "+") == 0 || strcmp(string, "-") == 0) {
    return 2;
  } else if (strcmp(string, "*") == 0 || strcmp(string, "/") == 0) {
    return 3;
  } else if (strcmp(string, "sqrt") == 0) {
    return 4;
  }
  
  return -1;
}
