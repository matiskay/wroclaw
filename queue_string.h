typedef struct queue_string QueueString;

QueueString* queue_string_create(void);
void queue_string_insert(QueueString* queue_string, char* string);
char* queue_string_pop(QueueString* queue_string);
int queue_string_is_empty(QueueString* queue_string);
void queue_string_free(QueueString* queue_string);
void queue_string_display(QueueString* queue_string);
int queue_string_number_of_elements(QueueString* queue_string);
int queue_string_equal(QueueString* queue_string_first, QueueString* queue_string_second);
