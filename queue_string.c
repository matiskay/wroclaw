#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue_string.h"

struct queue_string {
    char* value;
    struct queue_string* next;
};

QueueString* queue_string_create() {
    return NULL;
}

QueueString* queue_string_create_node() {
    QueueString* queue_string;
    queue_string = (QueueString*) malloc(sizeof(QueueString));

    queue_string->next = NULL;
    return queue_string;
}


QueueString* queue_string_insert(QueueString* queue, char* string) {
    char* string_copy;

    QueueString* new_queue_node;
    QueueString* aux_queue_node;
    QueueString* aux_queue_node2;

    new_queue_node = queue_string_create_node();


//    printf("value of the string %s \n", string);
    string_copy = malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(string_copy, string);

    new_queue_node->value = string_copy;


//    printf("value of the string in new node %s \n", new_queue_node->value);

    if (queue == NULL) {
        new_queue_node->next = queue;
        return new_queue_node;
    } else {
        // Walk until the end and insert.
        // The last one will be the one we want.
        // The last one is NULL that why we are using a QueueString pointer.
        for (aux_queue_node = queue; aux_queue_node != NULL; aux_queue_node = aux_queue_node->next) {
            aux_queue_node2 = aux_queue_node;
        }

        //printf("aux node queue %s\n", aux_queue_node2->value);

        aux_queue_node2->next = new_queue_node;
        return queue;
    }
}

char* queue_string_pop(QueueString** queue) {
    char* data;
    QueueString* current_queue_node;

    if (*queue == NULL) {
        return NULL;
    }

    if (queue_string_is_empty(*queue)) {
        return NULL;
    }

    // Hard copy a.k.a. This is how things work in C.
    // This is because result = (*stack)->value; means that result is a pointer to the value
    // if the value is wipeout result will be null.
    data = (*queue)->value;

    current_queue_node = *queue;
    *queue = current_queue_node->next;

//    printf("current value in queue -- data %s \n", data);
//    printf("current value in queue %s \n", (*queue)->value);

    free(current_queue_node);

    return data;
}

/**
 * TODO: Refactor this function. The current behaviour deletes all the elements.
 */
void queue_string_display(QueueString* queue) {
    QueueString* aux_queue_node;
    int counter;

    counter = 1;

    for (aux_queue_node = queue; aux_queue_node != NULL; aux_queue_node = aux_queue_node->next) {
        printf("%d.- %s \n", counter, aux_queue_node->value);
        counter++;
    }
}

void queue_string_display_inline(QueueString* queue) {
    QueueString* aux_queue_node;

    for (aux_queue_node = queue; aux_queue_node != NULL; aux_queue_node = aux_queue_node->next) {
        printf("%s ", aux_queue_node->value);
    }
}

int queue_string_is_empty(QueueString* queue) {
    if (queue == NULL) {
        return 1;
    }

    return 0;
}

// Review
void queue_string_free(QueueString** queue) {
    QueueString* aux_stack_node;
    int counter;
    counter = 0;

    for (aux_stack_node = (*queue); aux_stack_node != NULL; aux_stack_node = aux_stack_node->next) {
        QueueString* current_node = (*queue)->next;

        free(*queue);
        *queue = current_node;

        counter++;
    }
    printf("counter %d\n", counter);
}

int queue_string_number_of_elements(QueueString* queue) {
    QueueString* aux_queue_node;
    int number_of_elements;

    number_of_elements = 0;

    for (aux_queue_node = queue; aux_queue_node != NULL; aux_queue_node = aux_queue_node->next) {
        number_of_elements++;
    }

    return number_of_elements;
}

int queue_string_equal(QueueString* queue_string_first, QueueString* queue_string_second) {
    QueueString* aux_queue_string1;
    QueueString* aux_queue_string2;

    if (queue_string_number_of_elements(queue_string_first) != queue_string_number_of_elements(queue_string_second)) {
        return 0;
    }

    aux_queue_string2 = queue_string_second;

    for (aux_queue_string1 = queue_string_first; aux_queue_string1 != NULL; aux_queue_string1 = aux_queue_string1->next) {
        if (strcmp(aux_queue_string1->value, aux_queue_string2->value) != 0) {
            printf("%s != %s \n", aux_queue_string1->value, aux_queue_string2->value);
            return 0;
        }
        aux_queue_string2 = aux_queue_string2->next;
    }

    return 1;
}
