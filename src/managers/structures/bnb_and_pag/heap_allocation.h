#ifndef HEAP_ALLOCATION

typedef struct heap_allocation *heap_allocation;
struct heap_allocation
{
    int pointer;
    int size;
};
heap_allocation new_heap_allocation(int pointer, int size);
#endif