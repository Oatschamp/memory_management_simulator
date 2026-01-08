#include "physical_memory.h"

physical_memory::physical_memory(std::size_t size)
    : total_size(size),
      memory(size, 0),
      head(nullptr)
{
    head = new memory_block(0, total_size);
}

physical_memory::~physical_memory()
{
    memory_block* current = head;
    while (current != nullptr) {
        memory_block* next_block = current->next;
        delete current;
        current = next_block;
    }
}

memory_block* physical_memory::get_head() const
{
    return head;
}

std::size_t physical_memory::get_total_size() const
{
    return total_size;
}
