#ifndef buddy_allocator_h
#define buddy_allocator_h

#include <map>
#include <list>
#include <cstddef>

struct buddy_block {
    std::size_t start;
    std::size_t size;
};

class buddy_allocator {
private:
    std::size_t total_size;
    std::map<std::size_t, std::list<buddy_block>> free_lists;

    std::size_t round_up_power_of_two(std::size_t size);
    std::size_t get_buddy_address(std::size_t addr, std::size_t size);

public:
    buddy_allocator(std::size_t memory_size);

    buddy_block allocate(std::size_t size);
    void deallocate(buddy_block block);

    void dump_free_lists() const;
};

#endif
