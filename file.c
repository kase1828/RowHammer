#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *rowhammer(void *input)
{
	while(1) {
		printf("x = %d\n", *(int *)input);
		printf("hammering...\n");
		sleep(1);
	}

	return 0;
}

void *check(void *input)
{
	sleep(5);
	printf("x = %d\n", *(int *)input);
	printf("checking...\n");
	return NULL;
}

int main()
{
	printf("starting\n");

	int x = 5; 
	int *ptr = &x;

	pthread_t pthread_hammer;
	pthread_t pthread_check;

	pthread_create(&pthread_hammer, NULL, rowhammer, ptr);
	pthread_create(&pthread_check, NULL, check, ptr);

	pthread_join(pthread_check, NULL);
	printf("read disturb found\n");

	pthread_cancel(pthread_hammer);
	printf("exiting\n");

	return 0;
}
