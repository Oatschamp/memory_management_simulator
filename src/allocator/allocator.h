#ifndef allocator_h
#define allocator_h

#include <cstddef>
#include "memory_block.h"

class allocator {
public:
    virtual ~allocator() = default;
    virtual memory_block* allocate(memory_block* head, std::size_t size) = 0;
    virtual void deallocate(memory_block* block) = 0;
};

#endif
