#include "buddy_allocator.h"
#include <iostream>

buddy_allocator::buddy_allocator(std::size_t memory_size)
    : total_size(memory_size)
{
    free_lists[memory_size].push_back({0, memory_size});
}

std::size_t buddy_allocator::round_up_power_of_two(std::size_t size)
{
    std::size_t power = 1;
    while (power < size) {
        power <<= 1;
    }
    return power;
}

std::size_t buddy_allocator::get_buddy_address(std::size_t addr, std::size_t size)
{
    return addr ^ size;
}

buddy_block buddy_allocator::allocate(std::size_t size)
{
    std::size_t req_size = round_up_power_of_two(size);

    std::size_t current_size = req_size;
    while (free_lists[current_size].empty()) {
        current_size <<= 1;
        if (current_size > total_size) {
            return {static_cast<std::size_t>(-1), 0};
        }
    }

    buddy_block block = free_lists[current_size].front();
    free_lists[current_size].pop_front();

    while (current_size > req_size) {
        current_size >>= 1;
        buddy_block buddy{block.start + current_size, current_size};
        free_lists[current_size].push_back(buddy);
        block.size = current_size;
    }

    return block;
}

void buddy_allocator::deallocate(buddy_block block)
{
    std::size_t addr = block.start;
    std::size_t size = block.size;

    while (true) {
        std::size_t buddy_addr = get_buddy_address(addr, size);
        bool merged = false;

        auto& list = free_lists[size];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->start == buddy_addr) {
                addr = std::min(addr, buddy_addr);
                list.erase(it);
                size <<= 1;
                merged = true;
                break;
            }
        }

        if (!merged) break;
    }

    free_lists[size].push_back({addr, size});
}

void buddy_allocator::dump_free_lists() const
{
    for (const auto& pair : free_lists) {
        std::cout << "block size " << pair.first << ": ";
        for (const auto& block : pair.second) {
            std::cout << "[" << block.start << "] ";
        }
        std::cout << "\n";
    }
}
