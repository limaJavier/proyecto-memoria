#ifndef STACK_MANAGER

#include "../bool.h"
#include "stack.h"

typedef struct stack_manager *stack_manager;
struct stack_manager
{
    addr_t virtual_address;
    addr_t physical_address;
    size_t size;
    size_t count;
};

stack_manager new_stack_manager(addr_t from, addr_t to);
bool push_stack_manager(stack_manager manager, byte value, addr_t *virtual_pointer, addr_t *real_pointer);
bool pop_stack_manager(stack_manager, addr_t*);

#endif