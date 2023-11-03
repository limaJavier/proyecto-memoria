#ifndef HEAP_MANAGER

#include "../../../memory.h"
#include "free_list.h"
#include "bool.h"
#include "heap_allocation.h"
typedef struct heap_manager *heap_manager;
struct heap_manager
{
    free_list space_list;
    // To remove
    // byte *virtual_heap;
    heap_allocation *allocations;
    addr_t physical_address;
    size_t size;
};

heap_manager new_heap_manager(addr_t from, addr_t to);
bool malloc_heap(heap_manager, size_t, addr_t *);
bool free_heap(heap_manager, addr_t);
bool store_to_heap(heap_manager, addr_t, addr_t *);
bool load_from_heap(heap_manager, addr_t, addr_t *);

#endif