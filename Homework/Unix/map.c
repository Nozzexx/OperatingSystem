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

// Print out the usage of the program and exit.
void Usage(char*);

// Block size in bytes
#define BSIZE 4096

int 
main(int argc, char** argv) 
{
  int32_t fd;

  // input checking 
  if (argc != 3)
    Usage(argv[0]);

  // open input file

  //printf(argv[1]);
  //printf("\n %s", argv[2]); 

  fd = open(argv[1], O_RDWR);

  //printf("File Descriptor: %d", fd);
  if (fd == -1) {
    perror("Open failed");
    exit(EXIT_FAILURE);
  }
  // use fstat to get file size
  struct stat buffer; // Set up struct to define buffer size for fstat.
  fstat(fd, &buffer);
  off_t fileSize = buffer.st_size;
  // call mmap to map the file to memory. See man page for mmap
  // suggested usage: mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0)
  // assign the return value of mmap to  pointer variable arr 
  // arr[i] is the ith byte of the file

  uint8_t *arr = mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);

  // Error Handling per man page. If mmap returns value of -1
  // and it is equal to array variable then error in mapping has occured.
  if(arr == MAP_FAILED)
  {
    printf("MMAP has Failed.\n");
    return 1;
  }

  // Assume the file to consists of sequence of unsigned 8 bit integer (uint8_t)
  // find the smallest element in the block # specified by argv[2]
  // print the result

  uint8_t unsign = arr[0];
  int i; // Iterator for 'for' loop.
  int blockNum = atoi(argv[2]);  // Convert Block Number Char entered by user to Int.
  int blockMaximum = BSIZE * (blockNum + 1); // Calculate Block's Maximum Byte Size.
  int blockMinimum = blockMaximum - (BSIZE); // Calculate Block's Minimum Byte Size.


  // 'For' Loop  that runs through each byte in the memory mapped file and determines the minimum value.
  for(i = blockMinimum; i < blockMaximum; i++)
  {
    if (arr[i] < unsign)
    {
      unsign = arr[i];
      
    }
  }

  // Prints out the minimum value.
  printf("\nMinimum value in block %s is %d\n\n", argv[2], unsign); 
  close(fd);
  return EXIT_SUCCESS;
}

void 
Usage(char* s) 
{
  fprintf(stderr, "Usage: %s filename block_num \n", s);
  exit(EXIT_FAILURE);
}
