#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <errno.h>
#define _GNU_SOURCE

#define L1_SIZE (16384) // 16 KB
#define L2_SIZE (524288) // 512 KB 

int main() {

        printf("start\n");

	u_int64_t a[16384 / 16]; // 8 KB
	u_int64_t b[16384 / 4]; // 32 KB
	u_int64_t c[524288 / 4]; // 1 MB
	u_int64_t num;

        clock_t begin;
        clock_t end;
        double time_spent;

	// fill a
        for (u_int64_t i = 0; i < L1_SIZE / 16; i++) {
                a[i] = rand();
        }

	begin = clock();

        // time read
        for (u_int64_t i = 0; i < L1_SIZE / 16; i=i+8) {
                num = a[i];
        }

        end = clock();

	begin = clock();

        // time read
        for (u_int64_t i = 0; i < L1_SIZE / 16; i=i+8) {
                num = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("L1 read:   %f\n",time_spent);		

	// fill L1
	for (u_int64_t i = 0; i < L1_SIZE / 4; i++) {
                b[i] = rand();
        }

        begin = clock();

	// time read
        for (u_int64_t i = 0; i < L1_SIZE / 16; i=i+8) {
                num = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("L2 read:   %f\n",time_spent);

	// fill L1
        for (u_int64_t i = 0; i < L1_SIZE / 4; i++) {
                b[i] = rand();
        }

	// fill L2
	for (u_int64_t i = 0; i < L2_SIZE / 4; i++) {
                c[i] = rand();
        }

        begin = clock();

	// time read
        for (u_int64_t i = 0; i < L1_SIZE / 16; i=i+8) {
                num = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("Main read: %f\n",time_spent);

	return  0;

}
