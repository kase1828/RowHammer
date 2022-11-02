#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct thread_args {
	int *addr1;
	int *addr2;
};


/*
put addr1 into X9
put addr2 into X10
for i := 0 to N − 1 do
   STR X0, [X9]
   STR X0, [X10]
   DC CVAC, X9
   DC CVAC, X10
   DSB 0xB
*/


void *rowhammer(void *input)
{
	struct thread_args *args = input;
	printf("addr1: %p\n",(void*) args->addr1);
	printf("addr2: %p\n",(void*) args->addr2);

	// put add1 into x9
	asm ("mov x9, %0;"
	:"=r"(args->addr1)
	:
	:);

	// put addr2 into x10
	asm ("mov x10, %0;"
	:"=r"(args->addr2)
	:
	:);

	// loop
	while(1) {

		asm(
			"STR X0, [X9]\t\n"
			"STR X0, [X10]\t\n"
			"DC CVAC, X9\t\n"
			"DC CVAC, X10\t\n"
			"DSB 0xB\t\n"
		);

		sleep(1);
	}

	return 0;
}

void *check(void *input)
{
	struct thread_args *args = input;
        printf("addr1: %p\n",(void*) args->addr1);
        printf("addr2: %p\n",(void*) args->addr2);

	sleep(5);
	printf("x = %d\n", *(int *)input);
	printf("checking...\n");
	return NULL;
}

int main()
{
	printf("starting...\n");

	int x = 5;
	int y = 7; 

	struct thread_args *args = malloc (sizeof (struct thread_args));
	args->addr1 = &x;
	args->addr2 = &y;

	pthread_t pthread_hammer;
	pthread_t pthread_check;

	pthread_create(&pthread_hammer, NULL, rowhammer, args);
	pthread_create(&pthread_check, NULL, check, args);

	pthread_join(pthread_check, NULL);
	printf("read disturb found\n");

	pthread_cancel(pthread_hammer);
	printf("exiting...\n");

	return 0;
}
