#include "allocator.h"
#include <cstddef>

class first_fit_allocator : public allocator {
public:
    memory_block* allocate(memory_block* head, std::size_t size) override {
        memory_block* current = head;

        while (current != nullptr) {
            if (current->free && current->size >= size) {
                // split block if there is extra space
                if (current->size > size) {
                    memory_block* new_block =
                        new memory_block(current->start + size,
                                         current->size - size);

                    new_block->next = current->next;
                    new_block->prev = current;

                    if (current->next != nullptr) {
                        current->next->prev = new_block;
                    }

                    current->next = new_block;
                    current->size = size;
                }

                current->free = false;
                current->block_id = generate_block_id();
                return current;
            }
            current = current->next;
        }

        return nullptr; // allocation failed
    }

    void deallocate(memory_block* block) override {
        if (block == nullptr) return;

        block->free = true;
        block->block_id = -1;

        // coalesce with next block
        if (block->next != nullptr && block->next->free) {
            memory_block* next_block = block->next;
            block->size += next_block->size;
            block->next = next_block->next;

            if (next_block->next != nullptr) {
                next_block->next->prev = block;
            }

            delete next_block;
        }

        // coalesce with previous block
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
