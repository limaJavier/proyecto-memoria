#ifndef MEMORY_MANAGER

#include "../../../memory.h"
#include "../../../manager.h"
#include "pcb.h"

typedef struct memory_manager *memory_manager;
struct memory_manager
{
    free_list space_list;
    byte *physical_memory;
    pcb *processes;
    pcb current_process;
    size_t size;
};

memory_manager new_memory_manager(size_t memory_size);
void change_process_memory_manager(memory_manager manager, process_t in_process);
void end_process_memory_manager(memory_manager manager, process_t in_process);
#endif