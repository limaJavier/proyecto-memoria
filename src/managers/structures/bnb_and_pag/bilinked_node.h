#ifndef BILINKED_NODE

#include "../../../memory.h"

typedef struct bilinked_node *bilinked_node;
struct bilinked_node
{
    byte value;
    bilinked_node previous;
    bilinked_node next;
};

bilinked_node new_bilinked_node(byte value, bilinked_node previous, bilinked_node next);
#endif