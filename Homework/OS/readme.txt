//===============================================================================================
// readme.txt - Project 01
// Author: Josh Duke
// Date: 01.26.2023
//===============================================================================================

COMPILATION:
===========================================================================

Three main ways to compile in order of ease.

EXECUTE
    : Run execute.sh shell script in Linux Console. // THIS METHOD IS ESSENTIALLY THE SAME AS MAKEFILE BUT INCLUDES AUTO EXECUTION.

MAKEFILE
    : Enter make into Linux Console.

GCC
    : Run gcc computer.c load.c shell.c cpu.c memory.c -o computer

===========================================================================

EXECUTION:
===========================================================================

Two ways to Execute in order of ease.

EXECUTE
    : Run ./execute.sh shell script in Linux Console.

LINUX
    : Run ./computer in Linux Console.

===========================================================================

INSTRUCTIONS:
===========================================================================

1. When Program is executed a user interface will be displayed to allow for ease of access.
    - NOTE: Several options were only included for debugging purposes. Option 1 should be your main use case.

        1. Load a user program and set a base integer.
        2. Debug Display of Registers
        3. Debug Display of memory
        4. Debug Console Commands
        0. Exit Application

2. When option 1 has been selected, user will be prompted to enter the name of a user text file that is located in the same directory.
    - See file 'fname' in included directory.
    - After entering the name of the file press space and enter an integer that represents the base value.

    EXAMPLE: >: fname 8

    Filename is 'fname'
    Base Value: 8

3. From here the file is loaded into memory, and processed by the CPU. Instructions will be printed as they are completed and results will be printed as required by the user program.
    - Input will be quite long as CONFIG.Sys value has been set to 128. This can be altered in the config.sys file to make input slightly shorter.

4. Dependant on instructions from the user program, application will either exit (if given exit command) or loop back if no exit command was given.

=========================================================================

ERROR CODES:
=========================================================================

ERROR #001: Config.sys cannot be opened, or is missing. // Config.sys is not in the same directory or does not exist.
ERROR #002: Invalid Input. Please enter a file name and integer. // Input likely not in correct format.
ERROR #003: User Program cannot be opened or is missing. // The name of the file does not exist in the directory, or was misspelled.
ERROR #004: Invalid Action Code. Action Failed. // Shell Action Code was out of bounds. (NOT 2 or 3).

