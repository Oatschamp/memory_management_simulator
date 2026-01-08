#ifndef cache_level_h
#define cache_level_h

#include <vector>
#include <cstddef>
#include <string>
#include "cache_set.h"

class cache_level {
private:
    std::string name;

    std::size_t cache_size;
    std::size_t block_size;
    std::size_t associativity;
    std::size_t num_sets;

    std::vector<cache_set> sets;

    std::size_t time_counter;

    std::size_t hits;
    std::size_t misses;

    std::string policy; 

    std::size_t get_set_index(std::size_t address) const;
    std::size_t get_tag(std::size_t address) const;

    int choose_victim(cache_set& set);

public:
    cache_level(std::string level_name,
                std::size_t cache_size,
                std::size_t block_size,
                std::size_t associativity,
                const std::string& policy);

    bool access(std::size_t address);

    void print_stats() const;
};

#endif
