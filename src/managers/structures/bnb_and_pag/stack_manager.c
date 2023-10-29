#include <stdio.h>
#include <stdlib.h>
#include "stack_manager.h"

stack_manager new_stack_manager(addr_t from, addr_t to)
{
    if(from >= to)
        fprintf(stderr,"\"to\" must be strictly greater than \"from\""), exit(1);
        
    size_t stack_size = to - from;
    stack_manager manager = (stack_manager)malloc(sizeof(struct stack_manager));
    manager->physical_address = to;
    manager->size = stack_size;
    manager->_stack = new_stack();

    return manager;
}

bool push_stack_manager(stack_manager manager, byte value, addr_t* pointer)
{
    if(manager->_stack->count >= manager->size)
        return TRUE;

    *pointer = manager->physical_address - manager->_stack->count;
    push_stack(manager->_stack, value);
    return FALSE;
}

bool pop_stack_manager(stack_manager manager, byte* value)
{
    if(manager->_stack->count == 0)
        return FALSE;

    *value = pop_stack(manager->_stack);
    return TRUE;
}