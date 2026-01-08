#include "memory_manager.h"
#include "statistics.h"
#include <iostream>


memory_manager::memory_manager(std::size_t memory_size)
    : memory(memory_size),
      current_allocator(nullptr),
      buddy(nullptr),
      use_buddy(false),
      allocation_success(0),
      allocation_failure(0),
      buddy_internal_fragmentation(0)
{
}


void memory_manager::set_buddy_allocator(buddy_allocator* buddy_alloc)
{
    buddy = buddy_alloc;
    use_buddy = true;
}

void memory_manager::set_allocator(allocator* alloc)
{
    current_allocator = alloc;
}

int memory_manager::malloc_block(std::size_t size)
{
    if (use_buddy && buddy != nullptr) {
        buddy_block b = buddy->allocate(size);
        if (b.size == 0) {
            allocation_failure++;
            return -1;
        }

        allocation_success++;
        buddy_internal_fragmentation += (b.size - size);

        static int next_id = 1;
        return next_id++;
    }


    if (current_allocator == nullptr) {
        std::cout << "allocator not set\n";
        return -1;
    }

    memory_block* block =
        current_allocator->allocate(memory.get_head(), size);

    if (block == nullptr) {
        allocation_failure++;
        return -1;
    }

    allocation_success++;
    allocated_blocks[block->block_id] = block;
    return block->block_id;
}


void memory_manager::free_block(int block_id)
{
    if (use_buddy) {
        std::cout << "buddy block freed (id=" << block_id << ")\n";
        return;
    }

    auto it = allocated_blocks.find(block_id);
    if (it == allocated_blocks.end()) {
        std::cout << "invalid block id\n";
        return;
    }

    memory_block* block = it->second;
    current_allocator->deallocate(block);
    allocated_blocks.erase(it);
}


memory_block* memory_manager::get_head() const
{
    return memory.get_head();
}

std::size_t memory_manager::get_total_size() const
{
    return memory.get_total_size();
}

void memory_manager::dump_memory() const
{
    memory_block* current = memory.get_head();

    while (current != nullptr) {
        std::size_t start = current->start;
        std::size_t end = current->start + current->size - 1;

        if (current->free) {
            std::cout << "[0x" << std::hex << start
                      << " - 0x" << end << "] FREE\n";
        } else {
            std::cout << "[0x" << std::hex << start
                      << " - 0x" << end << "] USED (id="
                      << std::dec << current->block_id << ")\n";
        }

        current = current->next;
    }

    std::cout << std::dec;
}


void memory_manager::print_stats() const
{
    statistics stats = compute_statistics(
        memory.get_head(),
        memory.get_total_size(),
        allocation_success,
        allocation_failure
    );

    std::cout << "total memory: " << stats.total_memory << "\n";
    std::cout << "used memory: " << stats.used_memory << "\n";
    std::cout << "free memory: " << stats.free_memory << "\n";
    if (use_buddy) {
        std::cout << "internal fragmentation: "<< buddy_internal_fragmentation << "\n";
    }
    std::cout << "memory utilization: "
              << stats.memory_utilization * 100 << "%\n";
    std::cout << "external fragmentation: "
              << stats.external_fragmentation * 100 << "%\n";
    std::cout << "allocation success: "
              << stats.allocation_success << "\n";
    std::cout << "allocation failure: "
              << stats.allocation_failure << "\n";
}
