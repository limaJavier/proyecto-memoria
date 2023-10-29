#ifndef FREE_LIST
#include "linked_node.h"
typedef struct free_list *free_list;
struct free_list
{
    linked_node head;
    linked_node tail;
    int count;
};

free_list new_free_list();

#endif