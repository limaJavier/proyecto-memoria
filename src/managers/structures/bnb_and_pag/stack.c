#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack new_stack()
{
    stack _stack = (stack)malloc(sizeof(struct stack));
    _stack->top = NULL;
    _stack->count = 0;

    return _stack;
}

byte peek_stack(stack _stack)
{
    if (_stack->count == 0)
        fprintf(stderr, "Stack's empty"), exit(1);
    return _stack->top->value;
}

void push_stack(stack _stack, byte value)
{
    if (_stack->count == 0)
    {
        _stack->top = new_bilinked_node(value, NULL, NULL);
        _stack->count++;
    }
    else
    {
        bilinked_node top = _stack->top;
        top->next = new_bilinked_node(value, top, NULL);
        _stack->top = top->next;
        _stack->count++;
    }
}

byte pop_stack(stack _stack)
{
    if (_stack->count == 0)
        fprintf(stderr, "Stack's empty"), exit(1);

    bilinked_node top = _stack->top;
    byte value = top->value;

    if (_stack->count == 1)
    {
        _stack->top = NULL;
    }
    else
    {
        bilinked_node previous = top->previous;
        previous->next = NULL;
        _stack->top = previous;
    }

    _stack->count--;
    free(top);
    return value;
}