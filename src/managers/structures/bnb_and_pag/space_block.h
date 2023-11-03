#ifndef SPACE_BLOCK

#include "../../../memory.h"

typedef struct space_block *space_block;
struct space_block
{
    addr_t start;
    addr_t end;
    size_t size;
};

void validate_bounds(addr_t start, addr_t end);
space_block new_space_block(addr_t start, addr_t end);

#endif