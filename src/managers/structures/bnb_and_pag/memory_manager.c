#include "memory_manager.h"

memory_manager new_memory_manager(int memory_size)
{
    memory_manager manager = (memory_manager)malloc(sizeof(struct memory_manager));

    manager->space_list = new_free_list();
    manager->physical_memory = (byte *)malloc(memory_size * sizeof(byte));
    manager->current_process = NULL;
    manager->size = memory_size;

    manager->processes = (pcb *)malloc(memory_size * sizeof(pcb));
    for (int i = 0; i < memory_size; i++)
        manager->processes[i] = NULL;

    return manager;
}

pcb find_process(memory_manager manager, int pid)
{
    pcb process = NULL;
    for (int i = 0; i < manager->size; i++)
        if (manager->processes[i]->pid == pid)
            return process;
    return process;
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

bool remove_process(memory_manager manager, int pid)
{
    for (int i = 0; i < manager->size; i++)
    {
        if (manager->processes[i]->pid == pid)
        {
            manager->processes[i] = NULL;
            return TRUE;
        }
    }
    return FALSE;
}

pcb create_process_bnb(memory_manager manager, int pid, int size)
{
    int *bounds = get_space_free_list(manager->space_list, size, first_fit);
    pcb process = new_pcb(pid, bounds[0], bounds[1], size);
    return process;
}

void change_process_memory_manager(memory_manager manager, process_t in_process)
{
    pcb process = find_process(manager, in_process.pid);

    if (process == NULL)
    {
        process = create_process_bnb(manager, in_process.pid, in_process.program->size);
        manager->current_process = process;
        if (!add_process(manager, process))
            fprintf(stderr, "Out of memory"), exit(1);
    }
    else
    {
        manager->current_process = process;
    }
}

void end_process_memory_manager(memory_manager manager, process_t in_process)
{
    if (!remove_process(manager, in_process.pid))
        fprintf(stderr, "Process was not found"), exit(1);
}
