#ifndef SPACE_BLOCK

#include <stdio.h>
#include <stdlib.h>
typedef struct space_block *space_block;
struct space_block
{
    int start;
    int end;
    int size;
};

void validate_bounds(int start, int end);
space_block new_space_block(int start, int end);

#endif