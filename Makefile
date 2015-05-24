all:
	 gcc -c stack_string.c
	 gcc -c main.c
	 gcc -o main stack_string.o main.o

test_stack_string: clean
	 gcc -c stack_string.c
	 gcc -c test_stack_string.c
	 gcc -o test_stack_string stack_string.o test_stack_string.o
	 ./test_stack_string

test_queue_string: clean
	 gcc -c queue_string.c
	 gcc -c test_queue_string.c
	 gcc -o test_queue_string queue_string.o test_queue_string.o
	 ./test_queue_string

test_functions: clean
	 gcc -c functions.c
	 gcc -c test_functions.c
	 gcc -o test_functions functions.o test_functions.o
	 ./test_functions

test:	 test_stack_string test_functions test_queue_string

clean:
	 rm *.out || exit 0

run:
	 gcc -c stack_string.c
	 gcc -c main.c
	 gcc -o main stack_string.o main.o
	 ./main
