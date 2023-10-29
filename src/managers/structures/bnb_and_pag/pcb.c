#include <stdlib.h>
#include "pcb.h"

pcb new_pcb(int pid, int heap_address, int stack_address, int size)
{
    pcb _pcb = (pcb)malloc(sizeof(struct pcb));

    _pcb->pid = pid;
    _pcb->size = size;
    _pcb->_heap_manager = new_heap_manager(heap_address, heap_address + size / 2);
    _pcb->_stack_manager = new_stack_manager(stack_address - size / 2, stack_address);

    return _pcb;
}