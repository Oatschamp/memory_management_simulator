#ifndef virtual_memory_manager_h
#define virtual_memory_manager_h

#include <cstddef>
#include <string>
#include "page_table.h"
#include "cache_level.h"

class virtual_memory_manager {
private:
    std::size_t page_size;
    std::size_t num_frames;

    page_table table;

    std::size_t time_counter;
    std::size_t next_free_frame;

    std::size_t page_hits;
    std::size_t page_faults;

    std::string policy; 

    cache_level* l1;
    cache_level* l2;

    std::size_t choose_victim_page();

public:
    virtual_memory_manager(std::size_t virtual_memory_size,
                           std::size_t physical_memory_size,
                           std::size_t page_size,
                           const std::string& policy);

    void attach_caches(cache_level* l1_cache,
                       cache_level* l2_cache);

    void access(std::size_t virtual_address);

    void print_stats() const;
};

#endif
