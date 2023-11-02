#ifndef PCB

#include "heap_manager.h"
#include "stack_manager.h"

/// PCB stands for Process Control Block (also known as Process Structure)
typedef struct pcb *pcb;
struct pcb
{
    heap_manager _heap_manager;
    stack_manager _stack_manager;
    int pid;
    int size;
};

pcb new_pcb(int pid, addr_t heap_address, addr_t stack_address, size_t size);

#endif