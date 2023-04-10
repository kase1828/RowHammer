#ifndef _TIMER_H
#define _TIMER_H
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
#define CACHE_PAGE_SIZE 4096
#define CACHE_SIZE 2560000 //Arbitrary, bigger than the size of the Cache
//#define V 2
#define __ERROR_CHECK(i) (assert((i)==0))
#define ERROR_REPORT(x,y) {perror(y); return x;}
#define ERROR_CHECK(x,y,z) if ((x) !=0) {perror(z); return y;}

extern uint8_t array[10*CACHE_PAGE_SIZE]; //this is a large array, where 4096 is larger than the cache page size

#ifdef FILE_IO
	extern FILE *F;
#endif

//******************* Methods for the Pthread Counter //
#if TIMER_MODE == 0


void *counter(void *);



uint8_t  _timer(volatile long int *time_difference, uint8_t * address, int *ret); //Measure the time to access and address, measured by global counter
uint8_t  _evict_cache(char *write_space);
uint8_t  int_evict_cache(uint8_t *arr);


#endif




#endif
