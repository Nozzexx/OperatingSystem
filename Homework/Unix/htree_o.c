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
#include <sys/syscall.h>
#include "common.h"
#include "common_threads.h"


// Print out the usage of the program and exit.
void Usage(char*);
uint32_t jenkins_one_at_a_time_hash(const uint8_t* , uint64_t );

// block size
#define BSIZE 4096

int 
main(int argc, char** argv) 
{
  int32_t fd;
  uint32_t nblocks;
  size_t file_size;


  // input checking 
  if (argc != 3)
    Usage(argv[0]);

  //intake number of threads from argv2
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
  //error handling for fstat
  if (fstat(fd, &buff) == -1)
  {
    perror("File info not successfully received.");
  }

  file_size = buff.st_size;
  
  // calculate nblocks 
  nblocks = file_size/BSIZE;

  printf(" no. of blocks = %u \n", nblocks);
  //-remove
  printf("no. of threads= %d \n", mthreads);

  double start = GetTime();

  // calculate hash value of the input file

  uint8_t *array = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if(array == MAP_FAILED)
  {
    printf("MMAP has Failed.\n");
  }

  uint32_t hash = jenkins_one_at_a_time_hash((const uint8_t*)array, file_size); 

  double end = GetTime();
  printf("hash value = %u \n", hash);
  printf("time taken = %f \n", (end - start));
  close(fd);
  return EXIT_SUCCESS;
}

uint32_t 
jenkins_one_at_a_time_hash(const uint8_t* key, uint64_t length) 
{
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


void 
Usage(char* s) 
{
  fprintf(stderr, "Usage: %s filename num_threads \n", s);
  exit(EXIT_FAILURE);
}
