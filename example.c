#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define ROUND 140000
#define HAMMER_ROUND 140000
#define CACHE_SIZE (1024 * 1024)
#define L1_SIZE (16384)
#define L2_SIZE (524288)

int mapping_size = 0x1000;

int main(){

    /*utility variables*/
    int selection = 1;
    int number_of_cycles = 1;
    int cycles;
    int found_flag = 0;
    int j;
    unsigned long temporary = 0xFFFFFFFF;

    u_int64_t b2[16384 / 8];
    u_int64_t c[524288 / 8];
    
    void *mapped = mmap(NULL, mapping_size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANON, -1, 0);

    if (mapped == MAP_FAILED){
        printf("failed to allocate memory!\n");
        exit (1);
    }

    /*setting the address to hammer*/
    void* addr1 = (void*) (mapped+mapping_size/2);
    void *addr2 = (void*) (mapped+mapping_size/3);

    /*CACHE/NON CACHE timing tests*/
    printf("Timing of repeated access to same memory location using the cache:\n");

    clock_t begin = clock();

    for (int j = 0; j < ROUND; ++j) {
        asm volatile ("ldr %0, [%1]\n\t" : "=r" (temporary) : "r" (addr1) );
        asm volatile ("ldr %0, [%1]\n\t" : "=r" (temporary) : "r" (addr2) );
    }
    clock_t end = clock();
    printf("cache access time: %lf s\n", (double)(end-begin)/CLOCKS_PER_SEC);

    printf("Timing of repeated access to same memory location flushing the cache:\n");
/*
    begin = clock();
    for (j = 0; j < ROUND; ++j) {
    asm volatile(
        "ldr %2, [%0]\n\t"
        "ldr %2, [%1]\n\t"
        "dc civac, %0\n\t"
        "dc civac, %1\n\t"
        ::"r" (addr1), "r" (addr2), "r" (temporary)
        );
    }
    end = clock();
    printf("memory access time: %lf s\n", (double)(end-begin)/CLOCKS_PER_SEC);
*/

    /*start of actual hammer program*/
    while (1){
        do{
            printf("Select what you want to try: \n1)ZVA \n2)DC CVAC \n3)DC CIVAC \n");
            scanf("%d", &selection);
            if(!(selection == 1 || selection == 2 || selection == 3)){
                printf("Wrong input (%d), Please select a correct value\n", selection);
            }
        } while(!(selection == 1 || selection == 2 || selection == 3));

        printf("Enter number of refresh cycles you want to run the test for:\n");
        scanf("%d", &number_of_cycles);


        //The number of effective cycle for the program to run, e.g. how many refresh cycles should we test
        cycles = HAMMER_ROUND * number_of_cycles;

	int *fill = malloc(CACHE_SIZE);

        switch (selection)
        {
        case 1:

	    for (int i = 0; i < CACHE_SIZE / 4; i++) {
	    	fill[i] = i;
	    }

	    int num;

	    printf("hammering...\n");
 
            for (j = 0; j < cycles; ++j) {
                asm volatile(
                    "str %2, [%0]\n\t"
                    "str %2, [%1]\n\t"
                    ::"r" (addr1), "r" (addr2), "r" (temporary)
              );
		for (u_int64_t i = 0; i < L2_SIZE / 8; i++) {
			c[i] = rand();
		}

		for (u_int64_t i = 0; i < L1_SIZE / 8; i++) {
			b2[i] = rand();
        	}
            }
            break;
/*

        case 2:
            for (j = 0; j < cycles; ++j) {
                asm volatile(
                    "str %2, [%0]\n\t"
                    "str %2, [%1]\n\t"
                    "dc cvac, %0\n\t"
                    "dc cvac, %1\n\t"
                    ::"r" (addr1), "r" (addr2), "r" (temporary)
              );
            }
            break;

        case 3:
            for (j = 0; j < cycles; ++j) {
                asm volatile(
                    "str %2, [%0]\n\t"
                    "str %2, [%1]\n\t"
                    "dc civac, %0\n\t"
                    "dc civac, %1\n\t"
                    ::"r" (addr1), "r" (addr2), "r" (temporary)
              );
            }
             break;
*/
        default:
                printf("Invalid choice.\n");
                return 1;
            break;
        }

        /*test to see if there are any flipped bits*/

        for (int i = 0; i < mapping_size; i++){
            if (*((int8_t*)mapped + i) == 1) {
                printf("Found a bit flip in position : %d\n", i);
                found_flag ++;    
	    }
        }    

        if (!found_flag){
            printf("No bit-flip found :( \n");
        } else{
            printf("%d bit flips found :).\n", found_flag);
        }
    }

    return 0;
}
