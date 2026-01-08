#include "virtual_memory_manager.h"
#include <iostream>
#include <limits>

virtual_memory_manager::virtual_memory_manager(
    std::size_t vm_size,
    std::size_t pm_size,
    std::size_t psize,
    const std::string& pol)
    : page_size(psize),
      num_frames(pm_size / psize),
      table(vm_size / psize),
      time_counter(0),
      next_free_frame(0),
      page_hits(0),
      page_faults(0),
      policy(pol),
      l1(nullptr),
      l2(nullptr)
{
}

void virtual_memory_manager::attach_caches(cache_level* l1_cache,
                                           cache_level* l2_cache)
{
    l1 = l1_cache;
    l2 = l2_cache;
}

std::size_t virtual_memory_manager::choose_victim_page()
{
    std::size_t victim = 0;

    if (policy == "fifo") {
        std::size_t oldest = std::numeric_limits<std::size_t>::max();
        for (std::size_t i = 0; i < table.entries.size(); i++) {
            if (table.entries[i].valid &&
                table.entries[i].loaded_at < oldest) {
                oldest = table.entries[i].loaded_at;
                victim = i;
            }
        }
    }
    else if (policy == "lru") {
        std::size_t least = std::numeric_limits<std::size_t>::max();
        for (std::size_t i = 0; i < table.entries.size(); i++) {
            if (table.entries[i].valid &&
                table.entries[i].last_used < least) {
                least = table.entries[i].last_used;
                victim = i;
            }
        }
    }

    return victim;
}

void virtual_memory_manager::access(std::size_t virtual_address)
{
    time_counter++;

    std::size_t page = virtual_address / page_size;
    std::size_t offset = virtual_address % page_size;

    page_table_entry& entry = table.entries[page];

    if (entry.valid) {
        page_hits++;
        entry.last_used = time_counter;
    } else {
        page_faults++;

        if (next_free_frame < num_frames) {
            entry.frame = next_free_frame++;
        } else {
            std::size_t victim_page = choose_victim_page();
            entry.frame = table.entries[victim_page].frame;
            table.entries[victim_page].valid = false;
        }

        entry.valid = true;
        entry.loaded_at = time_counter;
        entry.last_used = time_counter;
    }

    std::size_t physical_address =
        entry.frame * page_size + offset;

    if (l1 && !l1->access(physical_address)) {
        if (l2) {
            l2->access(physical_address);
        }
    }
}

void virtual_memory_manager::print_stats() const
{
    std::cout << "page hits: " << page_hits << "\n";
    std::cout << "page faults: " << page_faults << "\n";
}
