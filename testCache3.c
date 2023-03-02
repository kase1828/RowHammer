#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <errno.h>
#define _GNU_SOURCE

#define CACHE_SIZE (16384) // 1MB

int main() {

        printf("start\n");

        u_int64_t a[16384 / 8];
        u_int64_t b[16384 / 8];
        u_int64_t a1[16384 / 8];
        u_int64_t a2[16384 / 8];
        u_int64_t a3[16384 / 8];
        u_int64_t b1[16384 / 8];
        u_int64_t num;

        clock_t begin;
        clock_t end;
        double time_spent;

        for (u_int64_t i = 0; i < 16384 / 8; i++) {
                c[i] = rand();
        }

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                a[i] = rand();
        }

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                a1[i] = a[i];
                //num = a[i];
        }

        begin = clock();

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                num = a1[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("a1 read: %f\n",time_spent);

        printf("%d\n",num);

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                a2[i] = a[i];
                //num = a[i];
        }

        begin = clock();

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                num = a1[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("a1 read after a2: %f\n",time_spent);

        printf("%d\n",num);

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                a2[i] = a[i];
                //num = a[i];
        }

        begin = clock();

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                num = a2[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("a2 read: %f\n",time_spent);

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                b[i] = rand();
        }

        begin = clock();

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                num = a2[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("a2 read after b: %f\n",time_spent);
        printf("%d\n",num);

/*
        begin = clock();

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                b1[i] = b[i];
                //num = b[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("b1 time: %f\n",time_spent);

        begin = clock();

        for (u_int64_t i = 0; i < CACHE_SIZE / 8; i++) {
                a3[i] = a[i];
                //num = a[i];
        }

        end = clock();
        time_spent = (double)(end - begin);

        printf("a3 time: %f\n",time_spent);
*/
        return 0;
}
