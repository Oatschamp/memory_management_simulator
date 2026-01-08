#include "allocator.h"
#include <cstddef>

class worst_fit_allocator : public allocator {
public:
    memory_block* allocate(memory_block* head, std::size_t size) override {
        memory_block* current = head;
        memory_block* worst_block = nullptr;

        while (current != nullptr) {
            if (current->free && current->size >= size) {
                if (worst_block == nullptr || current->size > worst_block->size) {
                    worst_block = current;
                }
            }
            current = current->next;
        }

        if (worst_block == nullptr) {
            return nullptr; // allocation failed
        }

        if (worst_block->size > size) {
            memory_block* new_block =
                new memory_block(worst_block->start + size,
                                 worst_block->size - size);

            new_block->next = worst_block->next;
            new_block->prev = worst_block;

            if (worst_block->next != nullptr) {
                worst_block->next->prev = new_block;
            }

            worst_block->next = new_block;
            worst_block->size = size;
        }

        worst_block->free = false;
        worst_block->block_id = generate_block_id();
        return worst_block;
    }

    void deallocate(memory_block* block) override {
        if (block == nullptr) return;

        block->free = true;
        block->block_id = -1;

        // merge with next
        if (block->next != nullptr && block->next->free) {
            memory_block* next_block = block->next;
            block->size += next_block->size;
            block->next = next_block->next;

            if (next_block->next != nullptr) {
                next_block->next->prev = block;
            }

            delete next_block;
        }

        // merge with previous
        if (block->prev != nullptr && block->prev->free) {
            memory_block* prev_block = block->prev;
            prev_block->size += block->size;
            prev_block->next = block->next;

            if (block->next != nullptr) {
                block->next->prev = prev_block;
            }

            delete block;
        }
    }

private:
    int generate_block_id() {
        static int next_id = 1;
        return next_id++;
    }
};
