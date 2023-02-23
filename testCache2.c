#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define CACHE_SIZE (1024 * 1024) // 1MB

#define N (1024*4)

int main() {

	printf("starting\n");

	uint64_t a[CACHE_SIZE * 8];
	uint64_t b[CACHE_SIZE * 8];

	clock_t begin = clock();

	for (uint64_t i = 0; i < CACHE_SIZE * 8; i = i+8) {
                a[i] = i;
        }

        clock_t end = clock();
        double time_spent = (double)(end - begin);

	printf("time spent b: %f\n",time_spent);

	begin = clock();

	for (uint64_t i = 0; i < CACHE_SIZE * 8; i = i+8) {
                b[i] = i;
        }

        end = clock();
        time_spent = (double)(end - begin);

	printf("time spent b: %f\n",time_spent);

	begin = clock();

	for (uint64_t i = 0; i < CACHE_SIZE * 8; i = i+8) {
                a[i] = i;
        }

        end = clock();
        time_spent = (double)(end - begin);

	printf("time spent a: %f\n",time_spent);

	return 0;
}
