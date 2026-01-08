#ifndef cache_set_h
#define cache_set_h

#include <vector>
#include "cache_line.h"

struct cache_set {
    std::vector<cache_line> lines;

    cache_set(std::size_t associativity)
        : lines(associativity) {}
};

#endif
