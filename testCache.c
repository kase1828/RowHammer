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

	int a = 5;

	/*char *cache = malloc(CACHE_SIZE);

	if (cache == NULL) {
		printf("Error: failed to allocate memory\n");
		return 0;
	}

	memset(cache, 0xFF, CACHE_SIZE); // Fill the cache with 0xFF's

	printf("Cache filled successfully\n");

	free(cache);*/

	clock_t begin = clock();

	printf("a: %d\n",a);

	clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("time spent: %f\n",time_spent);

	return 0;
}
