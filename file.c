#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SCTLR_EL1_UCI	BIT(26)

struct thread_args {

	int *addr1;
	int *addr2;

	int nums17[17];
};

/*
__asm__ __volatile__
    (
      "\tmrc p15, 0, %0, c1, c0, 0\n"
      : "=r" (sctlr)
      :
      : "memory"
    );
    */

void *rowhammer(void *input)
{
	struct thread_args *args = input;

	/*
	unsigned long temp = -1;
	
	asm volatile ("mov r0, %0;"
	:"=r"(args->addr1)
	:
	:);

	asm volatile ("mov r1, %0;"
	:"=r"(args->addr2)
	:
	:);

	while(1) {

		asm volatile (
			"STR %2, [%0]\t\n"
			"STR %2, [%1]\t\n"
			"DC , %0\t\n"
			"DC , %1"
			//"DSB 0xB"
			::"r" (args->addr1), "r" (args->addr2), "r" (temp)
		);

	}*/

	asm volatile(
          "dc civac, %0\n\t"
          "dc civac, %1\n\t"
          ::"r" (args->addr1), "r" (args->addr2)
        );
        while(1) {
          asm volatile(
            "dc zva, %0\n\t"
            "dc zva, %1\n\t"
            //"dsb 0xb"
            ::"r" (args->addr1), "r" (args->addr2)
          );
	}

	return 0;
}

void *check(void *input)
{
	sleep(1);
	struct thread_args *args = input;

	for (int i = 0; i < 17; i++) {
		args->nums17[i] = (int) *(args->addr1 - 8 + i);
	}

	printf("searcing...\n");
	while(1) {

		for (int i = 0; i < 17; i++) {
			if ((int) *(args->addr1 - 8 + i) != args->nums17[i]) return 0;
		}
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
