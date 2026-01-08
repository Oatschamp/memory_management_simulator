#ifndef memory_manager_h
#define memory_manager_h

#include "buddy/buddy_allocator.h"
#include <cstddef>
#include <unordered_map>
#include "physical_memory.h"
#include "allocator.h"

class memory_manager {
private:
    int allocation_success;
    int allocation_failure; 
    std::size_t buddy_internal_fragmentation;

    physical_memory memory;
    allocator* current_allocator;

    buddy_allocator* buddy;
    bool use_buddy;
    
    std::unordered_map<int, memory_block*> allocated_blocks;

public:
    memory_manager(std::size_t memory_size);

    void set_allocator(allocator* alloc);

    int malloc_block(std::size_t size);
    void free_block(int block_id);

    memory_block* get_head() const;
    std::size_t get_total_size() const;

    void dump_memory() const;
    void print_stats() const;
    void set_buddy_allocator(buddy_allocator* buddy_alloc);

};

#endif
