#include <stdlib.h>
#include <stdio.h>

#include "bool.h"
#include "free_list.h"

free_list new_free_list();
void validate_bounds(int, int);
bool are_bounds_valid_free_list(free_list list, int start, int end);
linked_node search_bounds_free_list(free_list list, int start, int end, int *node_index);
linked_node search_index_free_list(free_list list, int index);
bool insert_bounds_free_list(free_list list, int start, int end);
bool remove_bounds_free_list(free_list list, int start, int end);
bool remove_index_free_list(free_list list, int index);

free_list new_free_list()
{
    free_list _free_list = (free_list)malloc(sizeof(struct free_list));

    _free_list->head = NULL;
    _free_list->tail = NULL;
    _free_list->count = 0;

    return _free_list;
}

bool are_bounds_valid_free_list(free_list list, int start, int end)
{
    validate_bounds(start, end);

    linked_node current_node = list->head;

    // Traversing the free list
    while (current_node != NULL)
    {
        space_block current_block = current_node->block;

        bool matched = current_block->start == start && current_block->end == end;
        bool is_start_contained = current_block->start < start && start < current_block->end;
        bool is_end_contained = current_block->end < start && end < current_block->end;

        // Verifying block
        if (matched || is_start_contained || is_end_contained)
            return FALSE;

        // Moving forward
        current_node = current_node->next;
    }

    return TRUE;
}

linked_node search_bounds_free_list(free_list list, int start, int end, int *node_index)
{
    validate_bounds(start, end);

    linked_node current_node = list->head;

    *node_index = 0;
    // Traversing the free list
    while (current_node != NULL)
    {
        space_block current_block = current_node->block;

        // Verifying block
        if (current_block->start == start && current_block->end == end)
            return current_node;

        // Moving forward
        current_node = current_node->next;
        *node_index += 1;
    }

    return NULL;
}

linked_node search_index_free_list(free_list list, int index)
{
    if (index < 0 || index >= list->count)
        fprintf(stderr, "Index was outside of the bounds of the list"), exit(1);

    linked_node current_node = list->head;
    int i = 0;
    // Traversing the free list
    while (current_node != NULL)
    {
        if (i == index)
            return current_node;

        // Moving forward
        current_node = current_node->next;
        i++;
    }

    return NULL;
}

bool insert_bounds_free_list(free_list list, int start, int end)
{
    if (!are_bounds_valid_free_list(list, start, end))
        return FALSE;

    if (list->count == 0)
    {
        space_block block = new_space_block(start, end);
        list->head = list->tail = new_linked_node(block, NULL);
    }
    else
    {
        space_block block = new_space_block(start, end);
        linked_node tail = list->tail;
        tail->next = new_linked_node(block, NULL);
        list->tail = tail->next;
    }

    list->count++;
    return TRUE;
}

bool remove_bounds_free_list(free_list list, int start, int end)
{
    int node_index;
    linked_node node = search_bounds_free_list(list, start, end, &node_index);

    if (node == NULL)
        return FALSE;

    linked_node previous_node;
    if (node_index == 0)
    {
        if (node->next != NULL)
            list->head = node->next;
        else
            list->head = list->tail = NULL;
    }
    else
    {
        previous_node = search_index_free_list(list, node_index - 1);
        previous_node->next = node->next;
        if (node->next == NULL)
            list->tail = previous_node;
    }

    list->count--;
    free(node);
    return TRUE;
}

bool remove_index_free_list(free_list list, int index)
{
    linked_node node = search_index_free_list(list, index);

    if (node == NULL)
        return FALSE;

    if (index == 0)
    {
        if (node->next != NULL)
            list->head = node->next;
        else
            list->head = list->tail = NULL;
    }
    else
    {
        linked_node previous_node = search_index_free_list(list, index - 1);
        previous_node->next = node->next;
    }

    list->count--;
    free(node);
    return TRUE;
}