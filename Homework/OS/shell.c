//===============================================================================================
// shell.c - Project 01
// Author: Josh Duke
// Date: 01.26.2023
//===============================================================================================

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "computer.h"

struct cpu_registers registers;

void shell_init()
{
    //=================================================
    // TODO: SHELL_INIT() REMIANS EMPTY FOR PROJECT 01.
    //=================================================
}

void shell_print_registers() // DISPLAYS REGISTERS
{
    
    printf("\n\n=============================================================");
    printf("\n                      Register Dump                          ");
    printf("\n=============================================================");
    printf("\n\n Register: Contents");
    printf("\n\n BASE: %d", registers.BASE);
    printf("\n\n PC:   %d", registers.PC);
    printf("\n\n IR0:  %d", registers.IR0);
    printf("\n\n IR1:  %d", registers.IR1);
    printf("\n\n AC:   %d", registers.AC);
    printf("\n\n MAR:  %d", registers.MAR);
    printf("\n\n MBR:  %d", registers.MBR);
    printf("\n\n");
    
    return;
}

void shell_print_memory() // DISPLAYS MEMORY ARRAY
{
    printf("\n\n=============================================================");
    printf("\n                      Memory Dump: M = %d                     ", M);
    printf("\n=============================================================");
    printf("\n\n Address: Contents");

    int i;
    for( i = 0; i < 128; i++)
    {
        printf("\n\n %d: %d ", i, MEM[i]);
    }
    printf("\n\n");

    return;
}

void shell_command(int cmd) // EXECUTES SHELL COMMAND
{
    switch(cmd)
    {
        case 2:
        {
            shell_print_registers();
            break;
        }
        case 3:
        {
            shell_print_memory();
            break;
        }
        default:
        {
            printf("\n\n ERROR #004: Invalid Action Code. Action Failed.");
            break;
        }
        break;
    }
}