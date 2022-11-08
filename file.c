#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct thread_args {

	int *addr1;
	int *addr2;

	int z0;
	int m8, m7, m6, m5, m4, m3, m2, m1;
	int p1, p2, p3, p4, p5, p6, p7, p8;
};

void *rowhammer(void *input)
{
	struct thread_args *args = input;

	asm volatile ("mov x9, %0;"
	:"=r"(args->addr1)
	:
	:);

	asm volatile ("mov x10, %0;"
	:"=r"(args->addr2)
	:
	:);

	while(1) {

		asm volatile (
			"STR X0, [X9]\t\n"
			"STR X0, [X10]\t\n"
			"DC CVAC, X9\t\n"
			"DC CVAC, X10"
			//"DSB 0xB"
		);

	}

	return 0;
}

void *check(void *input)
{
	sleep(1);
	struct thread_args *args = input;

	args->m8 = (int) *(args->addr1 - 8);
	args->m7 = (int) *(args->addr1 - 7);
	args->m6 = (int) *(args->addr1 - 6);
	args->m5 = (int) *(args->addr1 - 5);
	args->m4 = (int) *(args->addr1 - 4);
	args->m3 = (int) *(args->addr1 - 3);
	args->m2 = (int) *(args->addr1 - 2);
	args->m1 = (int) *(args->addr1 - 1);
	args->z0 = (int) *(args->addr1);
	args->p1 = (int) *(args->addr1 + 1);
	args->p2 = (int) *(args->addr1 + 2);
	args->p3 = (int) *(args->addr1 + 3);
	args->p4 = (int) *(args->addr1 + 4);
	args->p5 = (int) *(args->addr1 + 5);
	args->p6 = (int) *(args->addr1 + 6);
	args->p7 = (int) *(args->addr1 + 7);
	args->p8 = (int) *(args->addr1 + 8);

	while(1) {

		if ((int) *(args->addr1 - 8) != args->m8) break;
		if ((int) *(args->addr1 - 7) != args->m7) break;
		if ((int) *(args->addr1 - 6) != args->m6) break;
		if ((int) *(args->addr1 - 5) != args->m5) break;
		if ((int) *(args->addr1 - 4) != args->m4) break;
		if ((int) *(args->addr1 - 3) != args->m3) break;
		if ((int) *(args->addr1 - 2) != args->m2) break;
		if ((int) *(args->addr1 - 1) != args->m1) break;
		if ((int) *(args->addr1) != args->z0) break;
		if ((int) *(args->addr1 + 1) != args->p1) break;
		if ((int) *(args->addr1 + 2) != args->p2) break;
		if ((int) *(args->addr1 + 3) != args->p3) break;
		if ((int) *(args->addr1 + 4) != args->p4) break;
		if ((int) *(args->addr1 + 5) != args->p5) break;
		if ((int) *(args->addr1 + 6) != args->p6) break;
		if ((int) *(args->addr1 + 7) != args->p7) break;
		if ((int) *(args->addr1 + 8) != args->p8) break;
	}

	return 0;
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
	printf("hammering...\n");

	pthread_create(&pthread_check, NULL, check, args);

	pthread_join(pthread_check, NULL);
	printf("read disturb found\n");

	pthread_cancel(pthread_hammer);
	printf("exiting...\n");

	return 0;
}
