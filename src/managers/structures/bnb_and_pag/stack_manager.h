#ifndef STACK_MANAGER

#include "../bool.h"
#include "stack.h"

typedef struct stack_manager *stack_manager;
struct stack_manager
{
    stack _stack;
    int physical_address;
    int size;
};

stack_manager new_stack_manager(int from, int to);
bool push_stack_manager(stack_manager manager, byte value, int *pointer);
bool pop_stack_manager(stack_manager manager, byte *value);

#endif