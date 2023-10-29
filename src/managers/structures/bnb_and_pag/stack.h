#ifndef STACK

#include "../bool.h"
#include "bilinked_node.h"

typedef struct stack *stack;
struct stack
{
    bilinked_node top;
    int count;
};

stack new_stack();
byte peek_stack(stack _stack);
byte pop_stack(stack);
byte peek_stack(stack);
void push_stack(stack, byte);
#endif