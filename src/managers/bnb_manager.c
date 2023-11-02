#include "stdio.h"

#include "./structures/bnb_and_pag/memory_manager.h"
#include "bnb_manager.h"

#define BNB 1

static memory_manager manager;

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

  addr_t virtual_address;
  if (!malloc_heap(heap, size, &virtual_address))
    return FALSE;

  (*out).size = size;
  (*out).addr = virtual_address;
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

  addr_t virtual_pointer;
  addr_t real_pointer;
  if (!push_stack_manager(_stack, val, &virtual_pointer, &real_pointer))
    return FALSE;

  printf("Haban %lld \n", process->pid);
  printf("Matanzas %lld \n", real_pointer);

  m_write(real_pointer, val);
  out->addr = virtual_pointer;

  return TRUE;
}

// Quita un elemento del stack
int m_bnb_pop(byte *out)
{
  pcb process = manager->current_process;
  stack_manager _stack = process->_stack_manager;

  addr_t real_address;
  if (!pop_stack_manager(_stack, &real_address))
    return FALSE;

  printf("Haban %lld \n", process->pid);
  printf("Matanzas %lld \n", real_address);

  *out = m_read(real_address);
  return TRUE;
}

// Carga el valor en una dirección determinada
int m_bnb_load(addr_t addr, byte *out)
{
  pcb process = manager->current_process;
  heap_manager heap = process->_heap_manager;

  addr_t real_pointer;
  if (!load_from_heap(heap, addr, &real_pointer))
    return FALSE;
  (*out) = m_read(real_pointer);
  printf("%d", *out);
  return TRUE;
}

// Almacena un valor en una dirección determinada
int m_bnb_store(addr_t addr, byte val)
{
  pcb process = manager->current_process;
  heap_manager heap = process->_heap_manager;

  addr_t real_address;
  if (!store_to_heap(heap, addr, &real_address))
    return FALSE;
  m_write(real_address, val);

  return TRUE;
}

// Notifica un cambio de contexto al proceso 'next_pid'
void m_bnb_on_ctx_switch(process_t process)
{
  bool created = FALSE;
  addr_t *stack_data = (addr_t *)malloc(2 * sizeof(addr_t));
  addr_t *heap_data = (addr_t *)malloc(2 * sizeof(addr_t));

  change_process_memory_manager(manager, process, &stack_data, &heap_data, &created, BNB);

  // set_curr_owner(process.pid);
  if (created)
  {
    m_set_owner(heap_data[0], heap_data[0] + heap_data[1]);
    m_set_owner(stack_data[0], stack_data[0] + stack_data[1]);
    printf("sadasdsa %lld \n", heap_data[0]);
    printf("sadasdsa %lld \n", heap_data[1]);
    printf("sadasdsa %lld \n", stack_data[0]);
    printf("sadasdsa %lld \n", stack_data[1]);
  }

  printf("Cuba: %d\n", process.pid);
}

// Notifica que un proceso ya terminó su ejecución
void m_bnb_on_end_process(process_t process)
{
  addr_t *stack_data = (addr_t *)malloc(2 * sizeof(addr_t));
  addr_t *heap_data = (addr_t *)malloc(2 * sizeof(addr_t));

  end_process_memory_manager(manager, process, &stack_data, &heap_data);

  m_unset_owner(stack_data[0], stack_data[0] + stack_data[1]);
  m_unset_owner(heap_data[0], heap_data[0] + heap_data[1]);
}
