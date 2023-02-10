#define __STDC_FORMAT_MACROS
#include <stdio.h>     
#include <stdlib.h>   
#include <stdint.h>  
#include <inttypes.h>  
#include <errno.h>     // for EINTR
#include <fcntl.h>     
#include <unistd.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <inttypes.h>
#include "common.h"
#include "common_threads.h"
#include <string.h>

// Print out the usage of the program and exit.
void Usage(char*);
void *tree(void *arg);

//Globals
int64_t fd;
uint64_t *array;
uint64_t nblocks;
uint64_t file_size;
uint64_t block;
uint32_t currHash;
uint32_t firstHash;
uint32_t secondHash;

uint64_t bthreadtotal;
int threadTotal;
int bytesRead; 

uint32_t jenkins_one_at_a_time_hash(const uint8_t* , uint64_t );

//Iterators
int i;
int s;

// block size
#define BSIZE 4096

int 
main(int argc, char** argv) {
  // input checking 
  if (argc != 3)
    Usage(argv[0]);

  //intake number of threads from argv 3
  int mthreads = atoi(argv[2]);
  
  // open input file
  fd = open(argv[1], O_RDWR);
  if (fd == -1) {
    perror("open failed");
    exit(EXIT_FAILURE);
  }
  
  //define buffer for file
  struct stat buff;

  // use fstat to get file size
  //error handling for fstat error (manpage inspired)
  if (fstat(fd, &buff) == -1)
  {
    perror("File info not successfully received.");
  }
    
  file_size = buff.st_size;
  array = malloc(sizeof(*array) * file_size);

  // calculate nblocks 
  nblocks = file_size/BSIZE;
  bthreadtotal = (nblocks / mthreads);
  printf("Number of total blocks = %lu \n", (unsigned long)nblocks);
  printf("Number of total threads = %d \n", mthreads);
  printf("Number of blocks per thread = %lu \n", (unsigned long)bthreadtotal);

  //threadTotal = mthreads;

  double start = GetTime(); 
  // calculate hash value of the input file
  
  pthread_t pthread01;
  Pthread_create(&pthread01, NULL, tree, &mthreads);
  Pthread_join(pthread01, (void **)&currHash);

  double end = GetTime();
  printf("hash value = %lu\n", (unsigned long)currHash);
  printf("time taken = %f \n", (end - start));
  
  close(fd);
  return EXIT_SUCCESS;
}

uint32_t 
jenkins_one_at_a_time_hash(const uint8_t* key, uint64_t length) {
  uint64_t i = 0;
  uint32_t hash = 0;
  while (i != length) {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}

void* 
tree(void* arg) {
  
  int mthreads = *((int *) arg);  //intake height variable

  threadTotal = mthreads;
  
  printf("mThreads Value: %d\n", mthreads);
  printf("threadTotal Value: %d\n", threadTotal);

    s = 1;
    
    for (i = 0; i < threadTotal; i ++)
    {
      uint64_t bytesRead = (nblocks - bthreadtotal * s) * BSIZE;

      printf("Bytes Read: %lu\n", (unsigned long)bytesRead);
      uint64_t *array = mmap(NULL, bthreadtotal*BSIZE, PROT_READ, MAP_PRIVATE, fd, bytesRead);
      if(array == MAP_FAILED)
      {
        printf("MMAP has Failed.\n");
      }

      uint32_t currHash = jenkins_one_at_a_time_hash((const uint8_t*)array, bthreadtotal*BSIZE); 

      printf("Curr Hash Value: %lu\n\n", (unsigned long)currHash);
      s++;
    }
    pthread_exit((void **)&currHash);
    
  return NULL;
}

void 
Usage(char* s) 
{
  fprintf(stderr, "Usage: %s filename num_threads \n", s);
  exit(EXIT_FAILURE);
}























 