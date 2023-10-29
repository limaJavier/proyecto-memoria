#ifndef HEAP_ALLOCATION

#include "../../../memory.h"

typedef struct heap_allocation *heap_allocation;
struct heap_allocation
{
    addr_t pointer;
    size_t size;
};
heap_allocation new_heap_allocation(addr_t pointer, size_t size);
#endif