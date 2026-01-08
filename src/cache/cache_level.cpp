#include "cache_level.h"
#include <iostream>
#include <limits>

cache_level::cache_level(std::string level_name,
                         std::size_t csize,
                         std::size_t bsize,
                         std::size_t assoc,
                         const std::string& pol)
    : name(level_name),
      cache_size(csize),
      block_size(bsize),
      associativity(assoc),
      time_counter(0),
      hits(0),
      misses(0),
      policy(pol)
{
    num_sets = cache_size / (block_size * associativity);
    for (std::size_t i = 0; i < num_sets; i++) {
        sets.emplace_back(associativity);
    }
}

std::size_t cache_level::get_set_index(std::size_t address) const
{
    return (address / block_size) % num_sets;
}

std::size_t cache_level::get_tag(std::size_t address) const
{
    return address / (block_size * num_sets);
}

int cache_level::choose_victim(cache_set& set)
{
    int victim = 0;

    if (policy == "fifo") {
        std::size_t oldest = std::numeric_limits<std::size_t>::max();
        for (std::size_t i = 0; i < set.lines.size(); i++) {
            if (!set.lines[i].valid) return i;
            if (set.lines[i].inserted_at < oldest) {
                oldest = set.lines[i].inserted_at;
                victim = i;
            }
        }
    }
    else if (policy == "lru") {
        std::size_t least = std::numeric_limits<std::size_t>::max();
        for (std::size_t i = 0; i < set.lines.size(); i++) {
            if (!set.lines[i].valid) return i;
            if (set.lines[i].last_used < least) {
                least = set.lines[i].last_used;
                victim = i;
            }
        }
    }
    else if (policy == "lfu") {
        std::size_t least = std::numeric_limits<std::size_t>::max();
        for (std::size_t i = 0; i < set.lines.size(); i++) {
            if (!set.lines[i].valid) return i;
            if (set.lines[i].frequency < least) {
                least = set.lines[i].frequency;
                victim = i;
            }
        }
    }

    return victim;
}

bool cache_level::access(std::size_t address)
{
    time_counter++;

    std::size_t set_index = get_set_index(address);
    std::size_t tag = get_tag(address);

    cache_set& set = sets[set_index];

    for (auto& line : set.lines) {
        if (line.valid && line.tag == tag) {
            hits++;
            line.last_used = time_counter;
            line.frequency++;
            return true;
        }
    }

    misses++;

    int victim = choose_victim(set);
    cache_line& line = set.lines[victim];

    line.valid = true;
    line.tag = tag;
    line.last_used = time_counter;
    line.frequency = 1;
    line.inserted_at = time_counter;

    return false;
}

void cache_level::print_stats() const
{
    std::cout << name << " hits: " << hits << "\n";
    std::cout << name << " misses: " << misses << "\n";
    double ratio = (hits + misses) == 0 ? 0.0 :
                   (double)hits / (hits + misses);
    std::cout << name << " hit ratio: " << ratio * 100 << "%\n";
}
