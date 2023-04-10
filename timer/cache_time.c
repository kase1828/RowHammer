//Version 0.0.4. 
//		New Error Handeling System
//		Functions now return uint8_t instead of char.
//		Experiment with timers using clock function; Explore multiple different timing options
//This program will measure the difference between cache hits and misses
/*
 *Used Macros
 MAIN -- Include the main statement
 V (Verbosity):
 	0 -- no print statements
	1 -- High Verbosity, debugging
	2 -- Less verbose, general use cases

TIMER_MODE:
	0 -- Use Counter in Pthread
        1 -- Use rdtscp intrinsics
	2 -- use time() command;

In the case of the error, a perror will allow us to diagnose a problem, while an assertion fails */ 

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h> //this library, for POSIX Threading
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <emmintrin.h>
#include <x86intrin.h>
#include <errno.h>
#include "timer.h"
//Version 0.0.4 error functionality, using fewer assertions

 uint8_t array[10*CACHE_PAGE_SIZE]; //this is a large array, where 4096 is larger than the cache page size
//extern void* counter(void *);

//******************* Methods for the Pthread Counter //
 volatile uint64_t global_timer = 0; //declare the global counter

int main(int, char **){
	volatile long int cache_t    = 0;
        volatile long int no_cache_t = 0; //used to store the output of the main counter for cached and not_cached_values
	int v = 0;
	asm volatile("mfence");
	usleep(300);
	asm volatile("mfence"); //sometimes the program misreads significantly early on. Try to compensate for that

	char    *cache_bogus= 0;//pointer to array used to clear the cache
	pthread_t mythread;
	pthread_create(&mythread, NULL, counter, NULL); //initialize the timer thread
        if (!mythread) return -1; //ensure the thread was created sucessfully
	cpu_set_t cpuset1; //The cpu_set stores valid cores
	CPU_ZERO(&cpuset1); //clear the CPUSet
	CPU_SET(TARGET_CORE, &cpuset1);
	pthread_setaffinity_np(mythread, sizeof(cpu_set_t), &cpuset1);
	cache_bogus = malloc(CACHE_SIZE);
        if (!cache_bogus) return -3;
        memset(cache_bogus, 0x01, CACHE_SIZE); // Fill the cache with 0xFF’s
	//for(int i=0;i<320;i++) array[i*CACHE_PAGE_SIZE/32] = 1; //initialize the array
	for(int j=0;j<1;j++){
		//usleep(100);
		for(int i=0;i<640;i++) array[i*CACHE_PAGE_SIZE/64] = 1; //load the cache into memory. Prevent copying data directly from the load command
		asm volatile("mfence");
		_timer(&cache_t, &array[j*CACHE_PAGE_SIZE], &v); //measure the time it takes to access the cached data
		_evict_cache(cache_bogus);
		//int_evict_cache(array);
		asm volatile("mfence");
		_timer(&no_cache_t, &array[j*CACHE_PAGE_SIZE], &v); //remeasure the amount of time it takes to access data that's not cached
		printf("%ld,%ld,%ld\n",cache_t, no_cache_t,no_cache_t-cache_t);	
		//usleep(300);

	}
	pthread_cancel(mythread);

	return 0;
}

