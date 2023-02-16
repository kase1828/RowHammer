#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#define _GNU_SOURCE

#define CACHE_SIZE (1024 * 1024 * 4) // 1MB

#define N (1024*4)

unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

static __inline__ unsigned long long rdtsc(void)
{
    __asm__ __volatile__ ("RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%rax", "rbx", "rcx", "rdx");
}

static __inline__ unsigned long long rdtsc1(void)
{
    __asm__ __volatile__ ("RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
            "%rax", "rbx", "rcx", "rdx");
}

int main(int argc, char* argv[])
{
    uint64_t start, end;

    rdtsc();
    malloc(N);
    rdtsc1();

    start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );

    printf("cycles spent in allocating %d bytes of memory: %llu\n",N, end - start);

    return 0;
}
/*
int main() {

	printf("start\n");
	int num = 5;
	printf("start\n");
	int a[CACHE_SIZE]; 
*/
//	char *cache = malloc(CACHE_SIZE);

//	if (cache == NULL) {
//		printf("Error: failed to allocate memory\n");
//		return 0;
//	}

	//memset(cache, 0xFF, CACHE_SIZE); // Fill the cache with 0xFF's
/*
	printf("loop\n");

	for (int i = 0; i < CACHE_SIZE; i++) {
		a[i] = i;	
	}

	int b;

	for (int i = 0; i < CACHE_SIZE; i++) {
		b = a[i];	
	}


	printf("Cache filled successfully\n");
*/
//	free(cache);
/*
	usleep(10);

	int z;
	z = num;

	int x;

	clock_t begin = clock();

	x = num;

	clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("time spent: %f\n",time_spent);

	return 0;
}*/
