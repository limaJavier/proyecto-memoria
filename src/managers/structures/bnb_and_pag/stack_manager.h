#ifndef STACK_MANAGER

#include "../bool.h"
#include "stack.h"

typedef struct stack_manager *stack_manager;
struct stack_manager
{
    stack _stack;
    addr_t physical_address;
    size_t size;
};

stack_manager new_stack_manager(addr_t from, addr_t to);
bool push_stack_manager(stack_manager manager, byte value, addr_t *pointer);
bool pop_stack_manager(stack_manager manager, byte *value);

#endif