typedef struct stack_string StackString;

StackString* stack_string_create(void);
StackString* stack_string_push(StackString* stack_string, char* data);
char* stack_string_pop(StackString** stack_string);
char* stack_string_peep(StackString* stack_string);
int stack_string_is_empty(StackString* stack_string);
void stack_string_free(StackString** stack_string);
void stack_string_display(StackString* stack_string);