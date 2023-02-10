//===============================================================================================
// computer.h - Project 01
// Author: Josh Duke
// Date: 01.26.2023
//===============================================================================================

typedef struct cpu_registers { // CPU REGISTERS

  int PC;
  int IR0;
  int IR1;
  int AC;
  int MAR;
  int MBR;
  int BASE;
  
}cpuRegisters;

typedef struct PCB  // PCB 
{
    int pcb_process_state;
    int pcb_processID;
    struct cpu_registers registers;
    size_t pcb_memory_limit;
    char pcb_accounting_info[128];
}processControlBlock;

enum PROCESS_STATES // PROCESS STATES NOT USED
{
    NEW,
    READY,
    RUNNING,
    WAITING,
    FINSIHED
};

int* MEM; // MEM ARRAY
int M; // MEM SIZE
int number_of_instructions; // NUMBER OF INSTRUCTIONS IN FILE
int number_of_data_points; // NUMBER OF DATA POINTS IN FILE

void boot_system();
void process_init_PCB(char *fname);
void process_set_registers();

void shell_init();
void shell_print_registers();
void shell_print_memory();
void shell_command(int cmd);

void load_prog(char *fname, int p_addr);
void load_finish(FILE *f);

int cpu_fetch_instruction(int programCounter);
int cpu_execute_instruction(int opCode, int mAddr);
int cpu_mem_address(int m_addr);
int cpu_operation();

int mem_init(int M);
int mem_read(int data);
int mem_write(int data);