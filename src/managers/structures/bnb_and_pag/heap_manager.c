#include <stdio.h>
#include <stdlib.h>
#include "heap_manager.h"

bool is_valid_pointer(heap_manager manager, addr_t pointer)
{
    for (int i = 0; i < manager->size; i++)
    {
        heap_allocation allocation = manager->allocations[i];
        if (allocation == NULL)
            continue;
        if (allocation->pointer <= pointer && pointer < allocation->pointer + allocation->size)
            return TRUE;
    }
    return FALSE;
}

heap_allocation pop_allocation(heap_manager manager, addr_t pointer)
{
    for (int i = 0; i < manager->size; i++)
    {
        heap_allocation allocation = manager->allocations[i];
        if (allocation == NULL)
            continue;
        if (allocation->pointer == pointer)
        {
            manager->allocations[i] = NULL;
            return allocation;
        }
    }

    return NULL;
}

heap_manager new_heap_manager(addr_t from, addr_t to)
{
    if (from >= to)
        fprintf(stderr, "\"to\" must be strictly greater than \"from\""), exit(1);

    size_t heap_size = to - from;
    heap_manager manager = (heap_manager)malloc(sizeof(struct heap_manager));

    manager->space_list = new_free_list();
    initialize_free_list(manager->space_list, heap_size);

    manager->virtual_heap = (byte *)malloc(heap_size * sizeof(byte));

    manager->allocations = (heap_allocation *)malloc(heap_size * sizeof(heap_allocation));
    for (int i = 0; i < heap_size; i++)
        manager->allocations[i] = NULL;

    manager->physical_address = from;
    manager->size = heap_size;

    return manager;
}

void add_allocation(heap_allocation *allocations, size_t size, heap_allocation allocation)
{
    for (int i = 0; i < size; i++)
        if (allocations[i] != NULL && allocations[i]->pointer == allocation->pointer)
            fprintf(stderr, "Pointer already existing"), exit(1);

    for (int i = 0; i < size; i++)
        if (allocations[i] == NULL)
            allocations[i] = allocation;
}

bool malloc_heap(heap_manager manager, size_t size, addr_t *pointer)
{
    addr_t *bounds = get_space_free_list(manager->space_list, size, first_fit);
    if (bounds == NULL)
        return FALSE;

    heap_allocation allocation = new_heap_allocation(bounds[0], bounds[1] - bounds[0]);
    add_allocation(manager->allocations, manager->size, allocation);

    *pointer = bounds[0] + manager->physical_address;
    return TRUE;
}

bool free_heap(heap_manager manager, addr_t pointer)
{
    // Address translation
    addr_t heap_pointer = pointer - manager->physical_address;

    heap_allocation allocation = pop_allocation(manager, heap_pointer);
    if (allocation == NULL)
        return FALSE;

    return_space_free_list(manager->space_list, allocation->pointer, allocation->pointer + allocation->size);
    return TRUE;
}

bool store_to_heap(heap_manager manager, addr_t pointer, byte value)
{
    // Address translation
    addr_t heap_pointer = pointer - manager->physical_address;
    if (!is_valid_pointer(manager, heap_pointer))
        return FALSE;
    manager->virtual_heap[heap_pointer] = value;
    return TRUE;
}

bool load_from_heap(heap_manager manager, addr_t pointer, byte *value)
{
    // Address translation
    addr_t heap_pointer = pointer - manager->physical_address;

    if (!is_valid_pointer(manager, heap_pointer))
        return FALSE;

    *value = manager->virtual_heap[heap_pointer];
    return TRUE;
}