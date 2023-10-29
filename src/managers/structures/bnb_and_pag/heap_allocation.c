#include <stdlib.h>
#include "heap_allocation.h"

heap_allocation new_heap_allocation(addr_t pointer, size_t size)
{
    heap_allocation allocation = (heap_allocation)malloc(sizeof(struct heap_allocation));

    allocation->pointer = pointer;
    allocation->size= size;
    
    return allocation;
}