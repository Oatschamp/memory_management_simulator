#ifndef page_table_entry_h
#define page_table_entry_h

#include <cstddef>

struct page_table_entry {
    bool valid;
    std::size_t frame;
    std::size_t last_used;   
    std::size_t loaded_at;   

    page_table_entry()
        : valid(false),
          frame(0),
          last_used(0),
          loaded_at(0) {}
};

#endif
