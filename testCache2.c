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

	u_int64_t a[1024 * 1024 / 8];
	u_int64_t b[1024 * 1024 / 8];
	u_int64_t c[1024 * 1024 / 8];
	u_int64_t d[1024 * 1024 / 8];
	u_int64_t e[1024 * 1024 / 8];
	u_int64_t f[1024 * 1024 / 8];

	clock_t begin;
	clock_t end;
	double time_spent;

	begin = clock();

	for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                a[i] = -i;
        }

        end = clock();
        time_spent = (double)(end - begin);

	printf("fill a: %f\n",time_spent);

	begin = clock();

	for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                b[i] = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

	printf("read a: %f\n",time_spent);

	begin = clock();

	for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                c[i] = -i;
        }

        end = clock();
        time_spent = (double)(end - begin);

	printf("fill c: %f\n",time_spent);

	begin = clock();

	for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                d[i] = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

	printf("read a: %f\n",time_spent);

	begin = clock();

	for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                e[i] = -i;
        }

        end = clock();
        time_spent = (double)(end - begin);

	printf("fill e: %f\n",time_spent);

	begin = clock();

	for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                f[i] = e[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

	printf("read e: %f\n",time_spent);

	return 0;
}
