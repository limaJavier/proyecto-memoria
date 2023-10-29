#include <stdio.h>
#include <stdlib.h>
#include "stack_manager.h"

stack_manager new_stack_manager(int from, int to)
{
    if(from >= to)
        fprintf(stderr,"\"to\" must be strictly greater than \"from\""), exit(1);
        
    int stack_size = to - from;
    stack_manager manager = (stack_manager)malloc(sizeof(struct stack_manager));
    manager->physical_address = to;
    manager->size = stack_size;
    manager->_stack = new_stack();
}

bool push_stack_manager(stack_manager manager, byte value, int* pointer)
{
    if(manager->_stack->count >= manager->size)
        return FALSE;

    *pointer = manager->physical_address - manager->_stack->count;
    push_stack(manager->_stack, value);
    return TRUE;
}

bool pop_stack_manager(stack_manager manager, byte* value)
{
    if(manager->_stack->count == 0)
        return FALSE;

    *value = pop_stack(manager->_stack);
    return TRUE;
}