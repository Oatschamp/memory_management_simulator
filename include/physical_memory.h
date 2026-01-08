#ifndef physical_memory_h
#define physical_memory_h

#include <cstddef>
#include <vector>
#include "memory_block.h"

class physical_memory {
private:
    std::size_t total_size;
    std::vector<char> memory;      
    memory_block* head;             

public:
    physical_memory(std::size_t size);
    ~physical_memory();

    memory_block* get_head() const;
    std::size_t get_total_size() const;
};

#endif
