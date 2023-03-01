#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <errno.h>
#define _GNU_SOURCE

#define CACHE_SIZE (1024 * 1024) // 1MB

int main() {

        printf("start\n");

	u_int64_t a[CACHE_SIZE / 32];
	u_int64_t b[CACHE_SIZE / 8];
	u_int64_t a1[CACHE_SIZE / 32];
	u_int64_t a2[CACHE_SIZE / 32];
	u_int64_t num;

	clock_t begin;
	clock_t end;
	double time_spent;

	for (u_int64_t i = 0; i < CACHE_SIZE / 32; i++) {
                a[i] = rand();
        }

	begin = clock();

	for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                a1[i] = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

	printf("a1 time: %f\n",time_spent);

	for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                b[i] = rand();
        }

	begin = clock();

	for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                a2[i] = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

	printf("a2 time: %f\n",time_spent);

	return 0;
}
