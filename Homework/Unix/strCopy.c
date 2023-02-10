#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DEBUG 0

/* 
 * This function copies src string to *dst.
 * Memory for *dst should be allocated
*/
// This function allows us to walk through the string and count the current number of characters, before returning the total.
int stringLength(char* sLength)
{
	int characterCount = 0;
	while (*sLength != '\0')
	{
		characterCount++;
		sLength++;

	}

	return characterCount;
}

void strCopy(char* src, char** dst)
{
	// define required variables
	// Find the length of source (src) string
	// Do not use any library call such as strlen()
	int characterTotal = stringLength(src); // Function above.
	int copyInt = 0; // Integer used to track increments through copy process.

	

	// allocate memory from heap for destination (*dst) string

	*dst = (char*) malloc(sizeof(char) * characterTotal);
	
	// if memory allocation fails print appropriate error message using perror() 
	// and return

	if(*dst == NULL)
	{
		perror("Memory Allocation Failed.");
		return;
	}

	// copy src to *dst. 
	// Do not use any library call such as strcpy()
	// Do not treat str and *dst as arrays. Use pointer arithmetic. (Not sure if str is supposed to mean src? Made assumption here as no str was present.)

	while (copyInt < characterTotal) // While loop through moving source to destination.
	{
		*(*dst + copyInt) = *(src + copyInt);
		copyInt++; // Increment up to character Total.
	}
	
#if DEBUG
	printf("str: %s \n", str);
	printf("str: %s \n", *dst);
#endif
	
	return;
}

