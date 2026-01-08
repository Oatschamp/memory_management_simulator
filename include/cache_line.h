#ifndef cache_line_h
#define cache_line_h

#include <cstddef>

struct cache_line {
    bool valid;
    std::size_t tag;

    std::size_t last_used;   
    std::size_t frequency;   
    std::size_t inserted_at; 

    cache_line()
        : valid(false),
          tag(0),
          last_used(0),
          frequency(0),
          inserted_at(0) {}
};

#endif
