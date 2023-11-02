#include <stdio.h>
#include <stdlib.h>

#include "memory_manager.h"

memory_manager new_memory_manager(size_t memory_size)
{
    memory_manager manager = (memory_manager)malloc(sizeof(struct memory_manager));

    manager->space_list = new_free_list();
    initialize_free_list(manager->space_list, memory_size);

    // manager->physical_memory = (byte *)malloc(memory_size * sizeof(byte));
    manager->current_process = NULL;
    manager->size = memory_size;

    manager->processes = (pcb *)malloc(memory_size * sizeof(pcb));
    for (int i = 0; i < memory_size; i++)
        manager->processes[i] = NULL;

    return manager;
}

pcb find_process(memory_manager manager, int pid)
{
    for (int i = 0; i < manager->size; i++)
        if (manager->processes[i] != NULL && manager->processes[i]->pid == pid)
            return manager->processes[i];
    return NULL;
}

bool add_process(memory_manager manager, pcb process)
{
    for (int i = 0; i < manager->size; i++)
    {
        if (manager->processes[i] == NULL)
        {
            manager->processes[i] = process;
            return TRUE;
        }
    }
    return FALSE;
}

bool remove_process(memory_manager manager, int pid, addr_t **stack_data, addr_t **heap_data)
{
    for (int i = 0; i < manager->size; i++)
    {
        if (manager->processes[i] == NULL)
            continue;
        if (manager->processes[i]->pid == pid)
        {
            pcb process = manager->processes[i];
            (*stack_data)[0] = process->_stack_manager->physical_address;
            (*stack_data)[1] = process->_stack_manager->size;
            (*heap_data)[0] = process->_heap_manager->physical_address;
            (*heap_data)[1] = process->_heap_manager->size;
            manager->processes[i] = NULL;
            return TRUE;
        }
    }
    return FALSE;
}

pcb create_process_bnb(memory_manager manager, int pid, size_t size, addr_t **stack_data, addr_t **heap_data)
{
    addr_t *bounds = get_space_free_list(manager->space_list, size, first_fit);
    pcb process = new_pcb(pid, bounds[0], bounds[1], size);

    (*heap_data)[0] = bounds[0];
    (*heap_data)[1] = bounds[0] + size / 2;
    (*stack_data)[0] = bounds[0] + size / 2;
    (*stack_data)[1] = bounds[1];

    return process;
}

pcb create_process_seg(memory_manager manager, int pid, size_t size, addr_t **stack_data, addr_t **heap_data)
{
    addr_t *heap_bounds = get_space_free_list(manager->space_list, size / 2, first_fit);
    addr_t *stack_bounds = get_space_free_list(manager->space_list, size / 2, first_fit);

    (*stack_data)[0] = stack_bounds[0];
    (*stack_data)[1] = stack_bounds[1];
    (*heap_data)[0] = heap_bounds[0];
    (*heap_data)[1] = heap_bounds[1];

    pcb process = new_pcb(pid, heap_bounds[0], stack_bounds[1], size / 2);
    return process;
}

void change_process_memory_manager(memory_manager manager, process_t in_process, addr_t **stack_data, addr_t **heap_data, bool *created, bool on_bnb)
{
    pcb process = find_process(manager, in_process.pid);

    static int i = 0;
    if (process == NULL)
    {

        if (on_bnb)
            process = create_process_bnb(manager, in_process.pid, in_process.program->size, stack_data, heap_data);
        else
            process = create_process_seg(manager, in_process.pid, in_process.program->size, stack_data, heap_data);

        manager->current_process = process;
        if (!add_process(manager, process))
            fprintf(stderr, "Out of memory"), exit(1);

        *created = TRUE;
    }
    else
    {
        manager->current_process = process;
    }
}

void end_process_memory_manager(memory_manager manager, process_t in_process, addr_t **stack_data, addr_t **heap_data)
{
    if (!remove_process(manager, in_process.pid, stack_data, heap_data))
        fprintf(stderr, "Process was not found"), exit(1);
}
