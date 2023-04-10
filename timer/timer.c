#include "timer.h"

//Timer Library,Version 0.1.0.
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

// uint8_t array[10*CACHE_PAGE_SIZE]; //this is a large array, where 4096 is larger than the cache page size
extern uint8_t array[];
#ifdef FILE_IO
	 FILE *F;
#endif

//******************* Methods for the Pthread Counter //

 extern volatile uint64_t global_timer; //declare the global counter

void *counter(void *){
#if V == 1
	printf("starting the counter ... \n");
#endif
	while(1){
	//	asm volatile("mfence"); //fences improved performance of this method significantly, allowing a slight difference in cache hit an miss time.
	global_timer++;
	//asm volatile("mfence");

	}
}



 uint8_t  _timer(volatile long int *time_difference, uint8_t * address, int *ret){ //Measure the time to access and address, measured by global counter
	 int _local_return = 0; // Prevent inconsistancy caused by passing result by reference in time measurement window
	volatile long int start_time = 0;
	volatile long int time = 0;
	if (!address) ERROR_REPORT(1,"Pointer passed to pthread timer cannot be NULL \n"); //verify that the pointer isn't NULL
#if V == 1
        printf("Using Thread timer \n");
#endif
	global_timer = 0; //set the counter to zero, to prevent overflow
	asm volatile("mfence");
	start_time = global_timer;
	usleep(200); //short delay, Experiment with this value
	_local_return = *address;
	time = global_timer - start_time; //measure the time it takes to read from a location in memory
	asm volatile("mfence");
	*time_difference = time;
#if V == 1
	printf("Time difference is %ld; %ld:%ld \n", *time_difference,start_time, *time_difference+start_time);
#endif
	if (!(*time_difference)) ERROR_REPORT(1,"Time measurement was 0 \n"); //if the start_time is still 0, it was never properly set

	*ret = _local_return;
	return 0;
}
//Evict Data from cache by writing to a large array
uint8_t  _evict_cache(char *write_space){
        if (!write_space) return 3;
        for (int i = 0;i<CACHE_SIZE;i++){
	       	*(write_space+i) +=1; //increment every byte in memory
		if (!i%5) asm volatile("mfence"); //every five iterations use a fence
	}
        //this should replace the actual data with junk in the cache
	asm volatile("mfence");
        return (uint8_t) 0;
}

uint8_t int_evict_cache(uint8_t *arr){
        if (!arr) return 3;
        for (int i = 0;i<10;i++) _mm_clflush(&arr[i*CACHE_PAGE_SIZE]); //increment every byte in memory
        //this should replace the actual data with junk in the cache
        return 0;
}

