#include "allocator.h"
#include <cstddef>

class best_fit_allocator : public allocator {
public:
    memory_block* allocate(memory_block* head, std::size_t size) override {
        memory_block* current = head;
        memory_block* best_block = nullptr;

        while (current != nullptr) {
            if (current->free && current->size >= size) {
                if (best_block == nullptr || current->size < best_block->size) {
                    best_block = current;
                }
            }
            current = current->next;
        }

        if (best_block == nullptr) {
            return nullptr; // allocation failed
        }

        if (best_block->size > size) {
            memory_block* new_block =
                new memory_block(best_block->start + size,
                                 best_block->size - size);

            new_block->next = best_block->next;
            new_block->prev = best_block;

            if (best_block->next != nullptr) {
                best_block->next->prev = new_block;
            }

            best_block->next = new_block;
            best_block->size = size;
        }

        best_block->free = false;
        best_block->block_id = generate_block_id();
        return best_block;
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
