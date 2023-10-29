#include "stdio.h"

#include "./structures/bnb_and_pag/memory_manager.h"
#include "bnb_manager.h"

static memory_manager manager;
// Available resources
// m_size() => Size of the memory

// Esta función se llama cuando se inicializa un caso de prueba. Debes tener en cuenta reinicializar aquellas estructuras globales extras que utilices en caso de ser necesario.
void m_bnb_init(int argc, char **argv)
{
  int memory_size = m_size();
  manager = new_memory_manager(memory_size);
}

// Reserva un espacio en el heap de tamaño 'size' y establece un puntero al
// inicio del espacio reservado.
int m_bnb_malloc(size_t size, ptr_t *out)
{
  pcb process = manager->current_process;
  heap_manager heap = process->_heap_manager;

  addr_t address;
  if (!malloc_heap(heap, size, &address))
    return FALSE;
  (*out).size = size;
  (*out).addr = address;
  return TRUE;
}

// Libera un espacio de memoria dado un puntero.
int m_bnb_free(ptr_t ptr)
{
  pcb process = manager->current_process;
  heap_manager heap = process->_heap_manager;

  if (!free_heap(heap, ptr.addr))
    return FALSE;
  return TRUE;
}

// Agrega un elemento al stack
int m_bnb_push(byte val, ptr_t *out)
{
  pcb process = manager->current_process;
  stack_manager _stack = process->_stack_manager;
  
  addr_t pointer;
  if (!push_stack_manager(_stack, val, &pointer))
    return FALSE;
  (*out).addr = pointer;

  return TRUE;
}

// Quita un elemento del stack
int m_bnb_pop(byte *out)
{
  pcb process = manager->current_process;
  stack_manager _stack = process->_stack_manager;

  if (!pop_stack_manager(_stack, out))
    return FALSE;
  return TRUE;
}

// Carga el valor en una dirección determinada
int m_bnb_load(addr_t addr, byte *out)
{
  pcb process = manager->current_process;
  heap_manager heap = process->_heap_manager;

  if (!load_from_heap(heap, addr, out))
    return FALSE;
  return TRUE;
}

// Almacena un valor en una dirección determinada
int m_bnb_store(addr_t addr, byte val)
{
  pcb process = manager->current_process;
  heap_manager heap = process->_heap_manager;

  if (!store_to_heap(heap, addr, val))
    return FALSE;
  return TRUE;
}

// Notifica un cambio de contexto al proceso 'next_pid'
void m_bnb_on_ctx_switch(process_t process)
{
  change_process_memory_manager(manager, process);
}

// Notifica que un proceso ya terminó su ejecución
void m_bnb_on_end_process(process_t process)
{
  end_process_memory_manager(manager, process);
}
