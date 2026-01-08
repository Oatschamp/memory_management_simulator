#include "statistics.h"
#include <algorithm>

statistics compute_statistics(memory_block* head,
std::size_t total_memory,
int allocation_success,
int allocation_failure)

{
    statistics stats{};
    stats.total_memory = total_memory;
    stats.used_memory = 0;
    stats.free_memory = 0;
    stats.internal_fragmentation = 0;  
    stats.allocation_success = allocation_success;
    stats.allocation_failure = allocation_failure;

    std::size_t largest_free_block = 0;

    memory_block* current = head;
    while (current != nullptr) {
        if (current->free) {
            stats.free_memory += current->size;
            largest_free_block =
                std::max(largest_free_block, current->size);
        } else {
            stats.used_memory += current->size;
        }
        current = current->next;
    }

    if (stats.free_memory > 0) {
        stats.external_fragmentation =
            1.0 - (double)largest_free_block / stats.free_memory;
    } else {
        stats.external_fragmentation = 0.0;
    }

    if (total_memory > 0) {
        stats.memory_utilization =
            (double)stats.used_memory / total_memory;
    } else {
        stats.memory_utilization = 0.0;
    }

    return stats;
}
