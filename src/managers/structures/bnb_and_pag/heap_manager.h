#ifndef HEAP_MANAGER

#include "../../../memory.h"
#include "../free_list.h"
#include "../bool.h"
#include "heap_allocation.h"
typedef struct heap_manager *heap_manager;
struct heap_manager
{
    free_list space_list;
    byte *virtual_heap;
    heap_allocation *allocations;
    int physical_address;
    int size;
};

heap_manager new_heap_manager(int from, int to);
bool malloc_heap(heap_manager manager, int size, int *pointer);
bool free_heap(heap_manager manager, int pointer);
bool store_to_heap(heap_manager manager, int pointer, byte value);
bool load_from_heap(heap_manager manager, int pointer, byte *value);

#endif