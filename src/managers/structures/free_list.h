#ifndef FREE_LIST
#include "linked_node.h"
typedef struct free_list *free_list;
struct free_list
{
    linked_node head;
    linked_node tail;
    int count;
};

typedef int *(*get_space_action)(free_list, int);

// General-linked-list method
free_list new_free_list();

// Fundamental free-list methods
void initialize_free_list(free_list list, size_t total_size);
int *get_space_free_list(free_list list, size_t size, get_space_action get_space);
void return_space_free_list(free_list list, int start, int end);

// Auxiliary free-list method
int *first_fit(free_list list, int size);

#endif