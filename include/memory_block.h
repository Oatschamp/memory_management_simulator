#ifndef memory_block_h
#define memory_block_h

#include <cstddef>

struct memory_block {
    std::size_t start;      
    std::size_t size;       
    bool free;              
    int block_id;           

    memory_block* prev;     
    memory_block* next;     

    memory_block(std::size_t start_addr, std::size_t block_size)
        : start(start_addr),
          size(block_size),
          free(true),
          block_id(-1),
          prev(nullptr),
          next(nullptr) {}
};

#endif
