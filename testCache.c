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

#define CACHE_SIZE (1024 * 1024) // 1MB

int main() {

	printf("start\n");
	int num = 5;
	printf("start\n");
	int a[CACHE_SIZE]; 

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
}
