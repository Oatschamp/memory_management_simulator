#ifndef statistics_h
#define statistics_h

#include <cstddef>
#include "memory_block.h"

struct statistics {
    std::size_t total_memory;
    std::size_t used_memory;
    std::size_t free_memory;

    std::size_t internal_fragmentation;
    double external_fragmentation;

    int allocation_success;
    int allocation_failure;

    double memory_utilization;
};

statistics compute_statistics(memory_block* head,
std::size_t total_memory,
int allocation_success,
int allocation_failure);

#endif
