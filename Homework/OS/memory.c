//===============================================================================================
// memory.c - Project 01
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

int mem_init(int M)
{
    MEM = (int*)malloc(M * sizeof(int)); // INITIALIZES MEM TO CONFIG.SYS FILE SIZE | DEFAULT MEM[128]
    printf("\n\n Success! Memory Initialized!");
}

int mem_read(int mAddrData)
{
    registers.MAR = mAddrData;
    registers.MBR = MEM[registers.MAR]; // TAKE ADDRESS ASSIGN TO MAR, LOOK UP MEM[MAR], MOVE TO MBR;
    return registers.MBR;
}

int mem_write(int mbrData)
{
    MEM[registers.MAR] = mbrData; // TAKE IN MBR, SET MEM[MAR] to MBR

    return MEM[registers.MAR];
}
