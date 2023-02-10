//===============================================================================================
// cpu.c - Project 01
// Author: Josh Duke
// Date: 01.26.2023
//===============================================================================================

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "computer.h"

struct cpu_registers registers;

int cpu_fetch_instruction(int programCounter)
{
    int setBASE = registers.BASE;
    registers.IR0 = MEM[setBASE + programCounter];
    registers.IR1 = MEM[setBASE + programCounter + 1];
}

int cpu_execute_instruction(int opCode, int mAddr)
{

  int dataalue;

  switch(opCode)
  {
    case 1: // Load Constant
    {
        printf("\n\n OPCODE: 01 LOAD + CONSTANT");
        printf("\n CONSTANT: %d", mAddr);

        cpu_mem_address(mAddr); // GET MEM ADDRESS
        registers.AC = mem_read(mAddr); // READ TO MBR ASSIGN TO AC
        break;
    }
    case 2: // Load Memory Address
    {
        printf("\n\n OPCODE: 02 LOAD + MEMORY ADDRESS");
        printf("\n MEM ADDR: %d", mAddr);

        cpu_mem_address(mAddr); // GET MEM ADDRESS
        registers.AC = mem_read(mAddr); // READ TO MBR ASSIGN TO AC
        
        printf("\n\n Data Loaded into AC: %d", registers.AC);
        break;
    }
    case 3: // Add Memory Address
    {
        printf("\n\n OPCODE: 03 ADD + MEMORY ADDRESS");
        printf("\n MEM ADDR: %d", mAddr);

        cpu_mem_address(mAddr); // GET MEM ADDRESS
        registers.AC += mem_read(mAddr); // READ TO MBR ADD TO AC

        printf("\n\n AC: %d", registers.AC);
        break;
    }
    case 4: // Multiply Memory Address
    {
        printf("\n\n OPCODE: 04 MULTIPLY + MEMORY ADDRESS");
        printf("\n MEM ADDR: %d", mAddr);

        cpu_mem_address(mAddr); // GET MEM ADDRESS
        registers.AC *= mem_read(mAddr); // READ TO MBR MULTIPLY TO AC
        break;
    }
    case 5: // Store Memory Address
    {
        int storeVar;
        printf("\n\n OPCODE: 05 STORE + MEMORY ADDRESS");
        printf("\n MEM ADDR: %d", mAddr);

        printf("\n\n Storing AC: %d at Memory Address: %d", registers.AC, mAddr);
        registers.AC  = mem_read(mAddr);
        
        break;
    }
    case 6: // If-Go Memory Address
    {
        printf("\n\n OPCODE: 06 IFGO + MEMORY ADDRESS");
        printf("\n MEM ADDR: %d", mAddr);

        if(registers.AC > 0)
        {
            printf("\n\nValue at Memory Address: %d", MEM[mAddr]);
            break;
        }
        else if (registers.AC == 0)
        {
            printf("Accumulator is zero.");
        }

        break;
    }
    case 7: // Print Null
    {
        printf("\n\n OPCODE: 07 PRINT + NULL");
        printf("\n MEM ADDR: %d", mAddr);

        printf("\n\n AC: %d", registers.AC);
        break;
    }
    case 8: // Sleep Time
    {
        printf("\n\n OPCODE: 08 SLEEP + TIME");
        printf("\n MEM ADDR: %d", mAddr);

        printf("\n\n Sleeping System for %d microseconds.", mAddr);
        usleep(mAddr);
        break;
    }
    case 9: // Shell Code
    {
        printf("\n\n OPCODE: 09 SHELL + CODE");
        printf("\n ACTION CODE: %d", mAddr);

        switch(mAddr)
        {
            case 2:
            {
                shell_command(2); // SHELL COMMAND
                break;
            }
            case 3:
            {
                shell_command(3); // SHELL COMMAND
                break;
            }
            default:
            {
                printf("\n\n ERROR #004: Invalid Action Code. Action Failed.");
                break;
            }
        }
        break;
    }
    case 0: // Exit Null
    {
        printf("\n\n OPCODE: 00 EXIT + NULL");
        printf("\n ACTION CODE: %d", mAddr);

        printf("\n\n NOTICE: Exiting Program....\n\n");
        exit(0);
        break;
    }
    default:
    {
        printf("\n\n OPCODE: 01 LOAD CONSTANT");
        break;

    }
  }
}

int cpu_mem_address(int m_addr) //SETS MAR TO BASE + MEM ADDRESS
{
   registers.MAR = registers.BASE + m_addr;
   
   return registers.MAR;
}

int cpu_operation() // LOOPS THROUGH ALL INSTRUCTIONS UNTIL COMPLETE.
{
   int instructionCount;
   int setBASE = registers.BASE;
   int fetchOp;
   int fetchMem;

    printf("\n\n=============================================================");
    printf("\n                       INSTRUCTION SET                       ");
    printf("\n=============================================================");

   while( (registers.PC) < number_of_instructions * 2)
   {    
        cpu_fetch_instruction(registers.PC); // PULL INSTRUCTION BASED ON PC
        cpu_execute_instruction(registers.IR0, registers.IR1); // EXECUTE INSTRUCTION BASED ON OPCODE AND OPERAND
        registers.PC += 2;
   }

   printf("\n\n=============================================================");

   registers.PC = registers.PC / 2;  // DONE BECAUSE INSTRUCTIONS ARE SPLIT INTO TWO WORDS.
   printf("\n\n Program Counter: %d", registers.PC);
}

