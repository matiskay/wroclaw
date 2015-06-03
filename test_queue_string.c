#include <stdio.h>
#include <string.h>

#include "minunit.h"
#include "queue_string.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

/*
 * TODO: Add failed test to summary.
 */

int tests_run = 0;

static char * test_queue_string_free() {
    QueueString* queue;
    queue = queue_string_create();
    queue = queue_string_insert(queue, "walter");
    queue = queue_string_insert(queue, "jose");
    queue = queue_string_insert(queue, "ricardo");

    queue_string_free(&queue);

    mu_assert("Failed test_queue_string_free", queue_string_is_empty(queue) == 1);

    queue = queue_string_insert(queue, "walter");
    queue = queue_string_insert(queue, "jose");
    queue = queue_string_insert(queue, "ricardo");

    queue_string_pop(&queue);
    queue_string_pop(&queue);
    queue_string_pop(&queue);

    mu_assert("Failed test_queue_string_free", queue_string_is_empty(queue) == 1);

    return 0;
}

static char * string_copystring_copy() {
    char string[128];

    QueueString* queue1;
    QueueString* queue2;

    queue1 = queue_string_create();
    queue2 = queue_string_create();

    string[0] = 'e';
    string[1] = 'd';
    string[2] = 'g';
    string[3] = 'a';
    string[4] = 'r';
    string[5] = '\0';


    queue1 = queue_string_insert(queue1, string);


    string[0] = 'k';
    string[1] = 'a';
    string[2] = 't';
    string[3] = 'i';
    string[4] = 'a';
    string[5] = 's';
    string[6] = 't';
    string[7] = 'a';
    string[8] = 'r';
    string[9] = '\0';

    queue1 = queue_string_insert(queue1, string);


    string[0] = 'a';
    string[1] = 'b';
    string[2] = 'c';
    string[3] = '\0';

    queue1 = queue_string_insert(queue1, string);


    queue2 = queue_string_insert(queue2, "edgar");
    queue2 = queue_string_insert(queue2, "katiastar");
    queue2 = queue_string_insert(queue2, "abc");

    queue_string_display(queue2);


    mu_assert("string_copystring_copy failed", queue_string_equal(queue1, queue2) == 1);

    queue_string_free(&queue1);

    if (queue1 == NULL) {
        printf("meh");
    }
    mu_assert("string_copystring_copy failed free", queue_string_is_empty(queue1) == 1);
    return 0;
}

static char * test_queue_string_equal() {
    QueueString* queue1;
    QueueString* queue2;

    queue1 = queue_string_create();
    queue2 = queue_string_create();

    queue1 = queue_string_insert(queue1, "edgar");
    queue1 = queue_string_insert(queue1, "juan");
    queue1 = queue_string_insert(queue1, "javier");
    queue1 = queue_string_insert(queue1, "walter");
    queue1 = queue_string_insert(queue1, "diego");
    queue1 = queue_string_insert(queue1, "carlos");

    queue2 = queue_string_insert(queue2, "edgar");
    queue2 = queue_string_insert(queue2, "juan");
    queue2 = queue_string_insert(queue2, "javier");
    queue2 = queue_string_insert(queue2, "walter");
    queue2 = queue_string_insert(queue2, "diego");
    queue2 = queue_string_insert(queue2, "carlos");

    mu_assert("test_queue_string_equal failed", queue_string_equal(queue1, queue2) == 1);
    return 0;
}

static char * test_queue_string_not_equal() {
    QueueString* queue1;
    QueueString* queue2;

    queue1 = queue_string_create();
    queue2 = queue_string_create();

    queue1 = queue_string_insert(queue1, "edgar");
    queue1 = queue_string_insert(queue1, "juan");
    queue1 = queue_string_insert(queue1, "javier");
    queue1 = queue_string_insert(queue1, "walter");
    queue1 = queue_string_insert(queue1, "diego");
    queue1 = queue_string_insert(queue1, "carlos");

    queue2 = queue_string_insert(queue2, "edgar");
    queue2 = queue_string_insert(queue2, "juan");
    queue2 = queue_string_insert(queue2, "javier");
    queue2 = queue_string_insert(queue2, "walter");
    queue2 = queue_string_insert(queue2, "diego");
    queue2 = queue_string_insert(queue2, "carlo");

    mu_assert("test_queue_string_equal failed", queue_string_equal(queue1, queue2) == 0);
    return 0;
}

static char * test_queue_string_not_equal_in_number_of_elements() {
    QueueString* queue1;
    QueueString* queue2;

    queue1 = queue_string_create();
    queue2 = queue_string_create();

    queue1 = queue_string_insert(queue1, "edgar");
    queue1 = queue_string_insert(queue1, "juan");
    queue1 = queue_string_insert(queue1, "javier");
    queue1 = queue_string_insert(queue1, "walter");
    queue1 = queue_string_insert(queue1, "diego");

    queue2 = queue_string_insert(queue2, "edgar");
    queue2 = queue_string_insert(queue2, "juan");
    queue2 = queue_string_insert(queue2, "javier");
    queue2 = queue_string_insert(queue2, "walter");
    queue2 = queue_string_insert(queue2, "diego");
    queue2 = queue_string_insert(queue2, "carlo");

    mu_assert("test_queue_string_equal failed", queue_string_equal(queue1, queue2) == 0);
    return 0;
}

static char * test_queue_string_insert() {
    QueueString* queue;
    queue = queue_string_create();

    queue = queue_string_insert(queue, "edgar");
    queue = queue_string_insert(queue, "juan");
    queue = queue_string_insert(queue, "javier");
    queue = queue_string_insert(queue, "walter");
    queue = queue_string_insert(queue, "diego");
    queue = queue_string_insert(queue, "carlos");
//
    mu_assert("edgar != edgar", strcmp("edgar", queue_string_pop(&queue)) == 0);
    mu_assert("juan != juan", strcmp("juan", queue_string_pop(&queue)) == 0);
    mu_assert("javier != javier", strcmp("javier", queue_string_pop(&queue)) == 0);
    return 0;
}

static char * test_queue_string_number_of_elements() {
    QueueString* queue;
    queue = queue_string_create();

    queue = queue_string_insert(queue, "edgar");
    queue = queue_string_insert(queue, "juan");
    queue = queue_string_insert(queue, "javier");
    queue = queue_string_insert(queue, "walter");
    queue = queue_string_insert(queue, "diego");
    queue = queue_string_insert(queue, "carlos");

    mu_assert("Failed test_queue_string_number_of_elements", queue_string_number_of_elements(queue) == 6);
    return 0;
}

static char * test_queue_string_number_of_elements_counting_again() {
    QueueString* queue;
    queue = queue_string_create();

    queue = queue_string_insert(queue, "edgar");
    queue = queue_string_insert(queue, "juan");
    queue = queue_string_insert(queue, "javier");
    queue = queue_string_insert(queue, "walter");
    queue = queue_string_insert(queue, "diego");
    queue = queue_string_insert(queue, "carlos");
    queue_string_pop(&queue);

    mu_assert("Failed test_queue_string_number_of_elements_counting_again", queue_string_number_of_elements(queue) == 5);
    return 0;
}

static char * test_queue_string_pop() {
    QueueString* queue;
    queue = queue_string_create();

    queue = queue_string_insert(queue, "101010");
    mu_assert("101010 != 101010", strcmp("101010", queue_string_pop(&queue)) == 0);
    return 0;
}

// Implement default behaviour for poping in empty queue.
static char * test_queue_string_pop_in_an_empty_queue_string() {
    QueueString* queue;
    queue = queue_string_create();

    mu_assert("Failed test_queue_string_pop_in_an_empty_queue_string", queue_string_pop(&queue) == NULL);
    return 0;
}

static char * test_queue_string_is_empty() {
    QueueString* queue;
    queue = queue_string_create();

    mu_assert("Failed test_queue_string_is_empty", queue_string_is_empty(queue) == 1);
    return 0;
}

static char * test_queue_string_is_not_empty() {
    QueueString* queue;
    queue = queue_string_create();
    queue = queue_string_insert(queue, "walter");

    mu_assert("Failed test_queue_string_is_not_empty", queue_string_is_empty(queue) == 0);
    return 0;
}


static char * test_unit() {
    mu_assert("test_unit failed: \n   error, test_unit 1 != 1", 1 == 1);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_unit);
    mu_run_test(test_queue_string_is_empty);
    mu_run_test(test_queue_string_insert);
    mu_run_test(test_queue_string_pop);
    mu_run_test(test_queue_string_is_not_empty);

//    mu_run_test(test_queue_string_pop_in_an_empty_queue_string);

    mu_run_test(test_queue_string_number_of_elements);
    mu_run_test(test_queue_string_number_of_elements_counting_again);
    mu_run_test(test_queue_string_equal);
    mu_run_test(test_queue_string_not_equal);
    mu_run_test(test_queue_string_not_equal_in_number_of_elements);
    mu_run_test(string_copystring_copy);
    mu_run_test(test_queue_string_free);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();

    printf(KMAG "---> Testing queue_string.c \n" RESET);

    if (result != 0) {
        printf("   -_-_-_-_-_-_-_,------,      o \n");
        printf("   _-_-_-_-_-_-_-|   /\\_/\\ \n");
        printf("   -_-_-_-_-_-_-~|__( X .X)  +     + \n");
        printf("   _-_-_-_-_-_-_- \"\"  \"\" \n");
        printf(KRED "   ✗ %s \n" RESET, result);
    }
    else {
        printf("   -_-_-_-_-_-_-_,------,      o \n");
        printf("   _-_-_-_-_-_-_-|   /\\_/\\ \n");
        printf("   -_-_-_-_-_-_-~|__( ^ .^)  +     + \n");
        printf("   _-_-_-_-_-_-_-  \"\"  \"\" \n");
        printf(KGRN "   ✓ ALL TESTS PASSED \n" RESET);
    }

    printf(KCYN "   Summary:\n   Number of tests run: %d\n" RESET, tests_run);
    return result != 0;
}
