#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "common_threads.h"

void* mythread(void *arg);
 

int main(int argc, char *argv[]) {                    

	int *ret;
    if (argc != 1) {
	fprintf(stderr, "usage: main\n");
	exit(1);
    }

    printf("main: begin\n");

    pthread_t p1, p2;
    Pthread_create(&p1, NULL, mythread, "A"); 
    Pthread_create(&p2, NULL, mythread, "B");

    // join waits for the threads to finish
    Pthread_join(p1, (void**) &ret); 
	printf("returned by th A: %d \n", *ret);
    Pthread_join(p2, NULL); 

    printf("main: end\n");
    return 0;
}

void* mythread(void* arg) {
	char *a = (char *) arg;
	int *ret;

	ret = malloc(sizeof(int));
	*ret = 9999;
    printf("Thread %s\n", a);
	pthread_exit(ret);	
    return NULL;
}
