#include "bilinked_node.h"

bilinked_node new_bilinked_node(byte value, bilinked_node previous, bilinked_node next)
{
    bilinked_node _bilinked_node = (bilinked_node)malloc(sizeof(struct bilinked_node));

    _bilinked_node->value = value;
    _bilinked_node->previous = previous;
    _bilinked_node->next = next;

    return _bilinked_node;
}
