//===============================================================================================
// load.c - Project 01
// Author: Josh Duke
// Date: 01.26.2023
//===============================================================================================

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "computer.h"

void load_prog(char *fname, int p_addr)
{
    FILE* userProgram = fopen(fname, "r"); // LOADS FILE NAME GIVEN BY USER.

    if(NULL == userProgram)
    {
        perror("\n\n ERROR #003: User Program cannot be opened or is missing.");
    }

    printf("\n\n Initializing User Program...");
    int iterator = 0;
    while(!feof(userProgram)) // READS TO END OF FILE, SEPERATES VALUES FROM FILE INTO SPECIFIC LOCATIONS FOR PARSING.
    {
        if (iterator >= 0 && iterator < 1) // READ VERY FIRST WORD  ASSIGN TO NUMBER OF INSTRUCTIONS
        {
            fscanf(userProgram, "\n\n%d", &number_of_instructions);
            printf( "\n\n Number of Instructions Read: %d\n\n", number_of_instructions); 
        }
        else if (iterator > 1 && iterator <= 2) // READ SECOND WORD ASSIGN TO NUMBER OF DATA POINTS
        {
            fscanf(userProgram, "\n\n%d", &number_of_data_points);
            printf( "\n Number of Data Points Read: %d\n\n", number_of_data_points);
        }
        else if ( iterator > 2 && iterator <= ((number_of_instructions * 2) + 2)) // READ REST OF FILE AND ASSIGN TO MEM
        {
            fscanf(userProgram, "\n\n%d", &MEM[p_addr]);
            p_addr++;
        }
        else if ( iterator > ((number_of_instructions * 2) + 2)) // READ REST OF FILE ASSIGN TO MEM AS DATA.
        {
            fscanf(userProgram, "\n\n%d", &MEM[p_addr]);
            p_addr++;
        }

        iterator++;
    }

    load_finish(userProgram); // CLOSE FILE

}

void load_finish(FILE *f)
{
    fclose(f); // CLOSE FILE
}
