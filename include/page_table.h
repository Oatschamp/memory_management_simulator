#ifndef page_table_h
#define page_table_h

#include <vector>
#include "page_table_entry.h"

class page_table {
public:
    std::vector<page_table_entry> entries;

    page_table(std::size_t num_pages)
        : entries(num_pages) {}
};

#endif
