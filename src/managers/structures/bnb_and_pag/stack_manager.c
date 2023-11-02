#include <stdio.h>
#include <stdlib.h>
#include "stack_manager.h"

stack_manager new_stack_manager(addr_t from, addr_t to)
{
    if (from >= to)
        fprintf(stderr, "\"to\" must be strictly greater than \"from\""), exit(1);

    size_t stack_size = to - from;
    stack_manager manager = (stack_manager)malloc(sizeof(struct stack_manager));
    manager->physical_address = to;
    manager->size = stack_size;
    manager->virtual_address = stack_size - 1;
    manager->count = 1;

    return manager;
}

bool push_stack_manager(stack_manager manager, byte value, addr_t *virtual_pointer, addr_t *real_pointer)
{
    if (manager->count >= manager->size)
        return FALSE; // Stack overflow

    *virtual_pointer = manager->virtual_address - manager->count;
    *real_pointer = manager->physical_address - manager->count;
    manager->count++; // Pushing
    return TRUE;
}

bool pop_stack_manager(stack_manager manager, addr_t *real_pointer)
{
    if (manager->count == 1)
        return FALSE;

    manager->count--; // Popping
    *real_pointer = manager->physical_address - manager->count;
    return TRUE;
}