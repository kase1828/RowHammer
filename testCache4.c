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
	u_int64_t b[16384 / 4]; // 16 KB
	u_int64_t b2[16384 / 4]; // 16 KB
        u_int64_t c[524288 / 4]; // 512 KB
        u_int64_t num;

        clock_t begin;
        clock_t end;
        double time_spent;

        for (u_int64_t i = 0; i < L1_SIZE / 16; i++) {
                a[i] = rand();
        }

        begin = clock();

        for (u_int64_t i = 0; i < L1_SIZE / 16; i++) {
                num = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("L1 read:   %f\n",time_spent);

	for (u_int64_t i = 0; i < L1_SIZE / 4; i++) {
                b[i] = rand();
        }

        begin = clock();

        for (u_int64_t i = 0; i < L1_SIZE / 16; i++) {
                num = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("L2 read:   %f\n",time_spent);

	for (u_int64_t i = 0; i < L2_SIZE / 4; i++) {
                c[i] = rand();
        }

	for (u_int64_t i = 0; i < L1_SIZE / 4; i++) {
                b2[i] = rand();
        }	

        begin = clock();

        for (u_int64_t i = 0; i < L1_SIZE / 16; i++) {
                num = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("Main read: %f\n",time_spent);

	return  0;

}
