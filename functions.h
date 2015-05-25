#include "queue_string.h"

QueueString* parser(char *);
QueueString* polish_parser(QueueString *);
int is_single_string_operator(char);
int is_parentesis(char);
int precedence(char*);
