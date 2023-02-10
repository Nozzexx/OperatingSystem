//----------------------------------------------------------------------
// Author: Josh Duke
// Assignment: #6
// Course: CS 3377.004
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This program counts the number of sentences in a given string and
 * the number of tokens in each sentence.
 * Terminates when user enters BYE
 */

int
main(int argc, char *argv[])
{
	// define the required variables
	char *buffer, *buffer2, *ptr1, *ptr2, *token, *subtoken;
	size_t bufferSize = 32;
	size_t stringCharacters;
	int sentCounter, tokCounter;
	const char delimit[]= "."; // Seperated delimiters for clarity.
	const char subdelimit[] =" ";

	buffer = (char*)malloc(bufferSize * sizeof(char)); // Allocate memory for buffer input string.

	// If Memory Allocation fails exit program.
	if(buffer == NULL)
	{
		perror("Error. Unable to allocate buffer memory.");
		exit(1);
	}

	while (1) {

		// Get Input from user.
		printf("Enter the string: ");

		// use getline() to get the input string
		stringCharacters = getline(&buffer, &bufferSize, stdin);
		printf("------------------------------------------------------------------\n");
		printf("\nSentenced Entered: %s", buffer);
		printf("\n%zu characters were read.\n\n", stringCharacters);

		// The input string consists of several sentences separated by '.'
		// Each sentence consists of several tokens separated by ' ' (space).
		// Using strtok_r() find the number of sentences and the number of tokens
		// in each sentence. HINT: man strtok and look at the sample program at the end.
		for( sentCounter = 1, buffer; ; sentCounter++, buffer = NULL)
		{
			token = strtok_r(buffer, delimit, &ptr1);
			
			if(token == NULL)
				break;
			// If the first token is BYE, break from the while loop (check strcmp/strncmp)
			else if(strcmp(token, "BYE\n") == 0)
			{
				printf("Closing. \n\n");
				printf("------------------------------------------------------------------\n");
				return(0);
			}
			else if (strcmp(token, "\n") == 0)
				break;
			// Take tokens, and tokenize into sub tokens and count.
			for (tokCounter = 0, buffer2 = token; ; tokCounter++, buffer2 = NULL)
			{
				subtoken = strtok_r(buffer2, subdelimit, &ptr2);
				if(subtoken == NULL)
					break;
			}
			// Print the results.
			printf("Sentence %d: Tokens: %d\n", sentCounter, tokCounter);
		}
		//Output Sentence total.
		printf("\nTotal Sentences: %d\n\n", sentCounter - 1); 
		printf("------------------------------------------------------------------\n");
	}

    exit(EXIT_SUCCESS);
}

