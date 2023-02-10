//===============================================================================================
// computer.c - Project 01
// Author: Josh Duke
// Date: 01.26.2023
//===============================================================================================

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "computer.h"

struct cpu_registers registers;
struct PCB pcb_main;

int main(int argc, char** argv) 
{
    
    boot_system(); // Boots Hardware (CPU / MEMORY)

    while(1)  // Left in for debug purposes
    {
    int selectionInteger;
    printf("\n\n============================================================="); // USER FACING UI FOR EASE OF USE.
    printf("\n                          MAIN MENU                          ");
    printf("\n=============================================================");
    printf("\n\n Enter an integer to make your selection.");
    printf("\n\n 1. Run User Program");
    printf("\n\n 2. Print Registers // FOR TESTING");
    printf("\n\n 3. Print Memory // FOR TESTING");
    printf("\n\n 4. Enter Shell Command // FOR TESTING");
    printf("\n\n 0. Exit");
    printf("\n\n=============================================================\n\n");
    printf("\n >:");

    scanf("%d", &selectionInteger);

    printf("\n\n Selection Entered: %d\n", selectionInteger);

    

        switch(selectionInteger)    //SWITCH FOR OPTIONS (OPTIONS 2, 3, 4 ARE FOR DEBUG.)
        {
            case 0: // ZERO TO EXIT.
            {
                printf("\n\n Exiting Operating System...\n\n"); 
                return 0;
                break;
            }
            case 1: // ONE TO ENTER FILENAME
            {
                printf("\n\n Please enter a filename that shares the same directory and a BASE size integer, do not include *.txt.");
                printf("\n\n >: ");

                char fname[128];
                int baseInt;
                if (scanf("%123s %d", fname, &baseInt) != 2) //Grab an integer from user and set as registers.BASE update PCB.
                {
                    perror("ERROR #002: Invalid Input. Please enter a file name and integer.");
                } 
                strcat(fname, ".txt");

                registers.BASE = baseInt;
                load_prog(fname, registers.BASE);
                process_init_PCB(fname);
                process_set_registers();
                cpu_operation();
                break;
            }
            case 2: // FOR DEBUG
            {
                printf("\n\n Loading Registers...\n\n");
                shell_print_registers();
                return 0;
            }
            case 3: // FOR DEBUG
            {
                printf("\n\n Dumping Memory...\n\n");
                shell_print_memory();
                return 0;
            }
            case 4: // FOR DEBUG
            {
                printf("\n\n Loading Shell Command Interface...\n\n");
                break;
            }
            default: // FOR INCORRECT INPUT.
            {
                printf("\n\n Invalid Selection. Please try again.\n\n");
                continue;
            }
        }
    }

  return EXIT_SUCCESS;
}

void boot_system() 
{
    printf("\n\n Initializing Boot Sequence..."); // INITIALIZE REGISTERS TO 0 JUST INCASE.
    registers.PC   = 0;
    registers.IR0  = 0;
    registers.IR1  = 0;
    registers.AC   = 0;
    registers.MAR  = 0;
    registers.MBR  = 0;
    registers.BASE = 8;

    M = 0;
    FILE* pointer = fopen("config.sys", "r"); // READ CONFIG FILE

    if(NULL == pointer)
    {
        perror("\n\n ERROR #001: Config.sys cannot be opened, or is missing.");
    }

    printf("\n\n Initializing Memory...");
    while(!feof(pointer)) // READ TO END OF FILE
    {
        fscanf(pointer, "\n\n%d", &M); // SET M TO VALUE FOUND IN FILE.
        printf( "\n\n Success! Memory Size Allocated: %d", M);
        
    }
    load_finish(pointer); // CLOSE FILE

    mem_init(M); // INIALIZE MEM ARRAY TO VALUE FROM CONFIG.SYS

    printf("\n\n Success! Boot Complete!");
}

void process_init_PCB(char *fname)
{
    pcb_main.pcb_process_state = NEW; // PROCESS STATES NOT IN USE.
    pcb_main.pcb_processID = getpid(); // PID 
    pcb_main.registers.BASE = registers.BASE; // SET VALUE OF BASE REGISTER IN PCB
    pcb_main.pcb_memory_limit = sizeof(MEM) / sizeof(MEM[0]); // DETERMINE MEMORY LIMIT FROM MEM ARRAY.
    strcpy(pcb_main.pcb_accounting_info, fname); // SET NAME OF PCB TO FILE NAME.

}

void process_set_registers() // SETS PCB REGISTERS TO CPU REGISTERS
{
    pcb_main.registers.BASE = registers.BASE;
    pcb_main.registers.PC = registers.PC;
    pcb_main.registers.AC = registers.AC;
    pcb_main.registers.IR0 = registers.IR0;
    pcb_main.registers.IR1 = registers.IR1;
    pcb_main.registers.MAR = registers.MAR;
    pcb_main.registers.MBR = registers.MBR;
}

