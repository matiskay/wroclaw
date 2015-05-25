typedef struct stack_float StackFloat;

StackFloat* stack_float_create(void);
void stack_float_push(StackFloat* s, float data);
float stack_float_pop(StackFloat* s);
float stack_float_peep(StackFloat* s);
int stack_float_is_empty(StackFloat* s);
void stack_float_free(StackFloat* s);
